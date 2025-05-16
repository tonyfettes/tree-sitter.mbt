import * as vscode from "vscode";
import * as Wasm from "@vscode/wasm-wasi/v1";

export interface Result {
  uri: vscode.Uri;
  range: vscode.Range;
  captures: Record<
    string,
    {
      range: vscode.Range;
    }[]
  >;
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
  private readonly textDecoder = new TextDecoder();
  public readonly onResult: vscode.EventEmitter<Result[]>;
  constructor(extensionUri: vscode.Uri) {
    this.extensionUri = extensionUri;
    this.results = [];
    this.onResult = new vscode.EventEmitter();
  }
  public async searchText(uri: vscode.Uri, options: Options, content: string): Promise<void> {
    const wasm: Wasm.Wasm = await Wasm.Wasm.load();
    const contentLines = content.split("\n");
    const request = {
      id: crypto.randomUUID(),
      method: "search",
      params: {
        query: options.query,
        content: content,
      },
    };
    const grepUri = vscode.Uri.joinPath(this.extensionUri, "grep.wasm");
    const grepBytes = await vscode.workspace.fs.readFile(grepUri);
    const grepWasm = await WebAssembly.compile(grepBytes);
    const child = await wasm.createProcess("moon-grep", grepWasm, {
      stdio: {
        in: { kind: "pipeIn" },
        out: { kind: "pipeOut" },
        err: { kind: "pipeOut" },
      },
    });
    if (!child.stdin) {
      throw new Error("Child process stdin is not available");
    }
    await child.stdin.write(JSON.stringify(request) + "\n");
    if (!child.stdout) {
      throw new Error("Child process stdout is not available");
    }
    let buffer = "";
    child.stdout.onData(async (data) => {
      buffer += this.textDecoder.decode(data);
      const stdoutLines = buffer.split("\n");
      if (stdoutLines.length < 2) {
        return;
      }
      const lastIndex = stdoutLines.length - 1;
      buffer = stdoutLines[lastIndex];
      for (const line of stdoutLines.slice(0, lastIndex)) {
        let json: any;
        try {
          json = JSON.parse(line);
        } catch (e) {
          console.error("Failed to parse JSON:", line);
          continue;
        }
        if (!("result" in json)) {
          console.error('Missing "result" in JSON:', json);
          continue;
        }
        const startLine = json.result.range.start.row;
        const endLine = json.result.range.end.row;
        const start = new vscode.Position(startLine, json.result.range.start.column);
        const end = new vscode.Position(endLine, json.result.range.end.column);
        const range = new vscode.Range(start, end);
        this.results.push({
          uri: uri,
          range: range,
          context: contentLines.slice(startLine, endLine + 1),
          captures: {},
        });
        this.onResult.fire(this.results);
      }
    });
    const status = await child.run();
    if (status !== 0) {
      throw new Error(`Child process exited with status ${status}`);
    }
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
    await this.searchText(uri, options, text);
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
  public async search(uri: vscode.Uri, options: Options): Promise<void> {
    this.clear();
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
