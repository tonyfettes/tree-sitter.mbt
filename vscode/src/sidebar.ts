import * as vscode from "vscode";
import sidebarHtml from "./sidebar/index.html";
import Handlebars, { template } from "handlebars";

export class WebviewViewProvider implements vscode.WebviewViewProvider {
  public static readonly viewType = "moon-grep-search";
  public static readonly template = Handlebars.compile(sidebarHtml);

  private _view?: vscode.WebviewView;
  private readonly _extensionUri: vscode.Uri;

  constructor(extensionUri: vscode.Uri) {
    this._extensionUri = extensionUri;
  }

  public resolveWebviewView(
    webviewView: vscode.WebviewView,
    _context: vscode.WebviewViewResolveContext,
    _token: vscode.CancellationToken
  ) {
    this._view = webviewView;

    webviewView.webview.options = {
      enableScripts: true,
      localResourceRoots: [this._extensionUri],
    };

    webviewView.webview.html = this._getHtmlForWebview(webviewView.webview);

    webviewView.webview.onDidReceiveMessage(async (data) => {
      switch (data.type) {
        case "search": {
          await this._performSearch(data.value);
          break;
        }
        case "replace": {
          await this._performReplace(data.value, false);
          break;
        }
        case "replaceAll": {
          await this._performReplace(data.value, true);
          break;
        }
        case "clear": {
          this._searchResults = [];
          break;
        }
        case "openMatch": {
          this._openMatch(data.value.file, data.value.line);
          break;
        }
        case "openInEditor": {
          this._openInEditor(data.value.results);
          break;
        }
      }
    });
  }

  private async _performSearch(options: Options) {
    if (!options || !options.pattern) {
      vscode.window.showInformationMessage("Please enter a search pattern.");
      return;
    }

    try {
      vscode.window.withProgress(
        {
          location: vscode.ProgressLocation.Notification,
          title: "Searching with Ripgrep...",
          cancellable: false,
        },
        async (progress) => {
          const results = await this._moonGrep.search(options, vscode.workspace.workspaceFolders);

          this._searchResults = results;

          // Send results to webview
          if (this._view) {
            this._view.webview.postMessage({
              type: "results",
              results: results,
              stats: {
                matchCount: results.length,
                fileCount: new Set(results.map((r) => r.file)).size,
              },
            });
          }
        }
      );
    } catch (error: any) {
      vscode.window.showErrorMessage(`Search failed: ${error.message || "Unknown error"}`);

      // Send empty results to webview
      if (this._view) {
        this._view.webview.postMessage({
          type: "results",
          results: [],
          stats: { matchCount: 0, fileCount: 0 },
        });
      }
    }
  }

  private async _performReplace(options: any, replaceAll: boolean) {
    const { searchPattern, replacePattern, filePattern, caseSensitive, wholeWord, regex } = options;

    if (!searchPattern || !replacePattern) {
      vscode.window.showInformationMessage("Please enter both search and replace patterns.");
      return;
    }

    try {
      // For now, we'll just show a message that replace functionality is coming soon
      // In a real implementation, we would use the workspace.fs API to read and write files
      vscode.window.showInformationMessage(
        `Replace ${replaceAll ? "all" : ""} functionality is coming soon.`
      );

      // After replacing, we would re-run the search to update results
      // await this._performSearch({
      //   pattern: searchPattern,
      //   filePattern,
      //   caseSensitive,
      //   wholeWord,
      //   regex
      // });
    } catch (error: any) {
      vscode.window.showErrorMessage(`Replace failed: ${error.message || "Unknown error"}`);
    }
  }

  private _openMatch(file: string, line: number) {
    const workspaceFolder = vscode.workspace.workspaceFolders?.[0];
    if (!workspaceFolder) {
      return;
    }

    const fileUri = vscode.Uri.joinPath(workspaceFolder.uri, file);

    vscode.window.showTextDocument(fileUri, {
      selection: new vscode.Range(
        new vscode.Position(line - 1, 0),
        new vscode.Position(line - 1, 0)
      ),
    });
  }

  private _openInEditor(results: Result[]) {
    // This would open the search results in the editor
    // For now, we'll just show a message
    vscode.window.showInformationMessage("Open in editor functionality is coming soon.");
  }

  private _getHtmlForWebview(webview: vscode.Webview): string {
    const nonce = getNonce();

    const scriptUri = webview.asWebviewUri(
      vscode.Uri.joinPath(this._extensionUri, "dist", "sidebar", "index.js")
    );
    const styleUri = webview.asWebviewUri(
      vscode.Uri.joinPath(this._extensionUri, "dist", "sidebar", "index.css")
    );

    return WebviewViewProvider.template({
      nonce,
      cspSource: webview.cspSource,
      scriptUri: scriptUri.toString(),
      styleUri: styleUri.toString(),
    });
  }
}

function getNonce() {
  let text = "";
  const possible = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  for (let i = 0; i < 32; i++) {
    text += possible.charAt(Math.floor(Math.random() * possible.length));
  }
  return text;
}
