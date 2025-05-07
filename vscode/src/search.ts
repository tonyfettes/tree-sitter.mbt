import * as vscode from "vscode";
import * as TS from "web-tree-sitter";
import TSJavascript from "tree-sitter-javascript";

console.log("Loading tree-sitter-javascript: ", TSJavascript);

export async function init() {
  console.log("Initializing tree-sitter");
  await TS.Parser.init();
  console.log("Tree-sitter initialized");
}

export interface Result {
  uri: vscode.Uri;
  range: vscode.Range;
}

export interface Options {
  language: string;
  query: string;
}

export class Service {
  private parser: TS.Parser;
  private languages: Map<string, TS.Language>;
  private results: Result[];
  constructor() {
    this.parser = new TS.Parser();
    this.languages = new Map<string, TS.Language>();
    this.results = [];
  }
  public async *search(uri: vscode.Uri, options: Options): AsyncGenerator<Result> {
    const uriStat = await vscode.workspace.fs.stat(uri);
    if (uriStat.type === vscode.FileType.Directory) {
      for (const [name] of await vscode.workspace.fs.readDirectory(uri)) {
        const fileUri = vscode.Uri.joinPath(uri, name);
        yield* this.search(fileUri, options);
      }
      return;
    }
    const bytes = await vscode.workspace.fs.readFile(uri);
    const content = new TextDecoder("utf-8").decode(bytes);
    const language = await this.loadLanguage(options.language);
    this.parser.setLanguage(language);
    const tree = this.parser.parse(content);
    if (!tree) {
      throw new Error("Failed to parse the file");
    }
    const query = new TS.Query(language, options.query);
    const matches = query.matches(tree.rootNode);
    for (const match of matches) {
      const node = match.captures[0].node;
      const tsStart = node.startPosition;
      const tsEnd = node.endPosition;
      const vsStart = new vscode.Position(tsStart.row, tsStart.column);
      const vsEnd = new vscode.Position(tsEnd.row, tsEnd.column);
      const result = {
        uri,
        range: new vscode.Range(vsStart, vsEnd),
      };
      this.results.push(result);
      yield result;
    }
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
        const language = await TS.Language.load(TSJavascript);
        this.languages.set(name, language);
        return language;
      default:
        throw new Error(`Language ${name} not supported`);
    }
  }
}
