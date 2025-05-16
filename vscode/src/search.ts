import * as vscode from "vscode";
import type * as Grep from "./grep.worker";
import GrepPath from "./grep.worker.ts?path";
import { Worker } from "worker_threads";

export interface Result {
  uri: vscode.Uri;
  range: vscode.Range;
  context: string[];
}

export interface Options {
  language: string;
  query: string;
  includePattern?: string;
  excludePattern?: string;
}

export class Service {
  private results: Result[];
  private readonly extensionUri: vscode.Uri;
  private worker: Worker | undefined;
  private messageId = 0;
  private textDecoder = new TextDecoder();
  public readonly onResult: vscode.EventEmitter<Result[]>;

  constructor(extensionUri: vscode.Uri) {
    this.extensionUri = extensionUri;
    this.results = [];
    this.onResult = new vscode.EventEmitter();
  }
  private async getWorker(): Promise<Worker> {
    if (this.worker) {
      return this.worker;
    }
    const workerUri = vscode.Uri.joinPath(this.extensionUri, GrepPath);
    const worker = new Worker(workerUri.fsPath);
    await new Promise<void>((resolve) => {
      const onMessage = (event: Grep.Response) => {
        if (event.type === "ready") {
          worker.removeListener("message", onMessage);
          resolve();
        }
      };
      worker.addListener("message", onMessage);
    });
    this.worker = worker;
    return this.worker;
  }
  private async searchText(uri: vscode.Uri, content: string): Promise<void> {
    const worker = await this.getWorker();
    const id = this.messageId++;
    const lines = content.split("\n");
    await new Promise<void>((resolve, reject) => {
      const onMessage = (event: Grep.Response) => {
        if (!("id" in event) || event.id !== id) {
          return;
        }
        if (event.type === "found") {
          const captures = event.captures;
          for (const [_, nodes] of Object.entries(captures)) {
            for (const node of nodes) {
              const startLine = node.range.start.row;
              const endLine = node.range.end.row;
              const startPosition = new vscode.Position(startLine, node.range.start.column);
              const endPosition = new vscode.Position(endLine, node.range.end.column);
              const range = new vscode.Range(startPosition, endPosition);
              this.results.push({
                uri: uri,
                range: range,
                context: lines.slice(startLine, endLine + 1),
              });
            }
          }
          this.onResult.fire(this.results);
        } else if (event.type === "finish") {
          worker.removeListener("message", onMessage);
          resolve();
        } else if (event.type === "error") {
          worker.removeListener("message", onMessage);
          reject(new Error(event.error));
        }
      };
      worker.addListener("message", onMessage);
      worker.postMessage({
        type: "search",
        id: id,
        content: content,
      });
    });
  }
  private async searchFile(uri: vscode.Uri, options: Options): Promise<void> {
    const bytes = await vscode.workspace.fs.readFile(uri);
    const text = this.textDecoder.decode(bytes);
    if (options.includePattern && !uri.fsPath.match(options.includePattern)) {
      return;
    }
    if (options.excludePattern && uri.fsPath.match(options.excludePattern)) {
      return;
    }
    await this.searchText(uri, text);
  }
  private async searchDirectory(uri: vscode.Uri, options: Options): Promise<void> {
    const files = await vscode.workspace.fs.readDirectory(uri);
    for (const [name, type] of files) {
      const fileUri = vscode.Uri.joinPath(uri, name);
      if (type === vscode.FileType.Directory) {
        await this.searchDirectory(fileUri, options);
      } else if (type === vscode.FileType.File) {
        await this.searchFile(fileUri, options);
      }
    }
  }
  private async compileQuery(query: string): Promise<void> {
    const worker = await this.getWorker();
    return new Promise<void>((resolve, reject) => {
      const onMessage = (event: Grep.Response) => {
        if (event.type === "finish") {
          worker.removeListener("message", onMessage);
          resolve();
        } else if (event.type === "error") {
          worker.removeListener("message", onMessage);
          reject(new Error(event.error));
        }
      };
      worker.addListener("message", onMessage);
      worker.postMessage({
        type: "compile",
        id: this.messageId++,
        query: query,
      });
    });
  }
  public async search(uri: vscode.Uri, options: Options): Promise<void> {
    this.clear();
    await this.compileQuery(options.query);
    const stat = await vscode.workspace.fs.stat(uri);
    switch (stat.type) {
      case vscode.FileType.Directory:
        this.searchDirectory(uri, options);
        break;
      case vscode.FileType.File:
        this.searchFile(uri, options);
        break;
    }
  }
  public clear() {
    this.results = [];
    this.onResult.fire(this.results);
  }
}
