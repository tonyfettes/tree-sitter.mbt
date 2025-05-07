import * as vscode from "vscode";
import * as TS from "web-tree-sitter";
import TSJavaScript from "tree-sitter-javascript";

await TS.Parser.init();

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
  public async search(uri: vscode.Uri, options: Options): Promise<void> {
    const uriStat = await vscode.workspace.fs.stat(uri);
    if (uriStat.type === vscode.FileType.Directory) {
      for (const [name] of await vscode.workspace.fs.readDirectory(uri)) {
        const fileUri = vscode.Uri.joinPath(uri, name);
        await this.search(fileUri, options);
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
      this.results.push({
        uri,
        range: new vscode.Range(vsStart, vsEnd),
      });
    }
  }
  private async loadLanguage(name: string): Promise<TS.Language> {
    const language = this.languages.get(name);
    if (language) {
      return language;
    }
    switch (name) {
      case "javascript":
        const language = await TS.Language.load(TSJavaScript);
        this.languages.set(name, language);
        return language;
      default:
        throw new Error(`Language ${name} not supported`);
    }
  }
}
