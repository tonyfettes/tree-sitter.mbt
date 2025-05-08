import * as vscode from "vscode";
import * as TS from "web-tree-sitter";
import TSJavascript from "tree-sitter-javascript";
import * as ChildProcess from "child_process";

export async function init() {
  await TS.Parser.init();
}

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
  private parser: TS.Parser;
  private languages: Map<string, TS.Language>;
  private results: Result[];
  private readonly extensionUri: vscode.Uri;
  public readonly onResult: vscode.EventEmitter<Result[]>;
  constructor(extensionUri: vscode.Uri) {
    this.extensionUri = extensionUri;
    this.parser = new TS.Parser();
    this.languages = new Map<string, TS.Language>();
    this.results = [];
    this.onResult = new vscode.EventEmitter();
  }
  public async search(uri: vscode.Uri, options: Options): Promise<void> {
    const args = [options.query, uri.fsPath];
    const child = ChildProcess.spawn(
      "/Users/haoxiang/Workspace/moonbit/feihaoxiang/moonbit-tree-sitter/bin/target/native/release/build/grep/grep.exe",
      args
    );
    const fileSet: Map<vscode.Uri, string[]> = new Map();
    const textDecoder = new TextDecoder();
    let buffer = "";
    child.stdout.on("data", async (data) => {
      buffer += data;
      const lines = buffer.split("\n");
      if (lines.length < 2) {
        return;
      }
      const lastIndex = lines.length - 1;
      buffer = lines[lastIndex];
      for (const line of lines.slice(0, lastIndex)) {
        const json = JSON.parse(line);
        console.log("Search: json", json);
        const uri = vscode.Uri.parse(`file://${json.path}`);
        let lines = fileSet.get(uri);
        if (lines === undefined) {
          const fileBytes = await vscode.workspace.fs.readFile(uri);
          const fileText = textDecoder.decode(fileBytes);
          lines = fileText.split("\n");
          fileSet.set(uri, lines);
        }
        const startLine = json.start.row;
        const endLine = json.end.row;
        const start = new vscode.Position(startLine, json.start.column);
        const end = new vscode.Position(endLine, json.end.column);
        const range = new vscode.Range(start, end);
        this.results.push({
          uri: uri,
          range: range,
          context: lines.slice(startLine, endLine + 1),
        });
        this.onResult.fire(this.results);
      }
    });
    let stderr: string | undefined = undefined;
    child.stderr.on("data", (data) => {
      if (!stderr) {
        stderr = data;
      } else {
        stderr += data;
      }
    });
    await new Promise<void>((resolve, reject) => {
      child.on("close", (code) => {
        if (code !== 0) {
          if (stderr !== undefined) {
            reject(new Error(stderr));
          } else {
            reject(new Error(`moon-grep exited with ${code}`));
          }
        } else {
          resolve();
        }
      });
    });
  }
  public clear() {
    this.results = [];
  }
  private async loadLanguage(name: string): Promise<TS.Language> {
    const language = this.languages.get(name);
    if (language) {
      return language;
    }
    switch (name) {
      case "javascript":
        const language = await TS.Language.load(
          vscode.Uri.joinPath(this.extensionUri, "dist", TSJavascript).fsPath
        );
        if (!language) {
          throw new Error(`Failed to load language ${name} from ${TSJavascript}`);
        }
        this.languages.set(name, language);
        return language;
      default:
        throw new Error(`Language ${name} not supported`);
    }
  }
}
