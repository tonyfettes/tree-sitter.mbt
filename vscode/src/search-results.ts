import * as vscode from "vscode";
import * as MoonGrep from "./moon-grep";

export class SearchResultsProvider
  implements vscode.TreeDataProvider<GrepItem> {
  public static readonly viewType = "moon-grep-search-results";

  private _onDidChangeTreeData: vscode.EventEmitter<
    GrepItem | undefined | null | void
  > = new vscode.EventEmitter<GrepItem | undefined | null | void>();
  readonly onDidChangeTreeData: vscode.Event<
    GrepItem | undefined | null | void
  > = this._onDidChangeTreeData.event;

  private results: MoonGrep.Result[] = [];

  constructor() {}

  refresh(results: MoonGrep.Result[]): void {
    this.results = results;
    this._onDidChangeTreeData.fire();
  }

  getTreeItem(element: GrepItem): vscode.TreeItem {
    return element;
  }

  getChildren(
    element?: GrepItem
  ): Thenable<GrepItem[]> {
    if (!this.results) {
      return Promise.resolve([]);
    }

    if (element) {
      // If it's a file node, return its matches as children
      if (element.contextValue === "fileNode" && element.filePath) {
        const fileResults = this.results.filter(
          (r) => r.file === element.label // Assuming label is the file path for file nodes
        );
        return Promise.resolve(
          fileResults.map(
            (r) =>
              new GrepItem(
                `${r.line}: ${r.match}`,
                vscode.TreeItemCollapsibleState.None,
                {
                  command: "vscode.open",
                  title: "Open File",
                  arguments: [
                    vscode.Uri.joinPath(vscode.workspace.workspaceFolders![0].uri, r.file),
                    {
                      selection: new vscode.Range(
                        new vscode.Position(r.line - 1, 0),
                        new vscode.Position(r.line - 1, r.text.length)
                      ),
                    },
                  ],
                },
                r.file,
                r.line
              )
          )
        );
      }
      return Promise.resolve([]); // No children for match nodes
    } else {
      // Root level: group by file
      const files = Array.from(new Set(this.results.map((r) => r.file)));
      return Promise.resolve(
        files.map(
          (file) =>
            new GrepItem(
              file,
              vscode.TreeItemCollapsibleState.Expanded,
              undefined,
              file, // Store filePath for context
              undefined,
              "fileNode" // contextValue to identify file nodes
            )
        )
      );
    }
  }
}

export class GrepItem extends vscode.TreeItem {
  constructor(
    public readonly label: string,
    public readonly collapsibleState: vscode.TreeItemCollapsibleState,
    public readonly command?: vscode.Command,
    public readonly filePath?: string,
    public readonly lineNumber?: number,
    public readonly contextValue?: string
  ) {
    super(label, collapsibleState);
    this.tooltip = `${this.filePath || ""}${this.lineNumber ? ":" + this.lineNumber : ""}`;
    this.description = this.filePath && !this.lineNumber ? this.filePath : ""; // Show path for file nodes
    if (this.contextValue === "fileNode") {
        this.iconPath = vscode.ThemeIcon.File;
    } else {
        this.iconPath = new vscode.ThemeIcon("search-result");
    }
  }
}
