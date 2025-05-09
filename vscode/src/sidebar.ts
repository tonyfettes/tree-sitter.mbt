import * as vscode from "vscode";
import type * as Search from "./search";
import { MatchRange } from "./sidebar/types";

export class WebviewViewProvider implements vscode.WebviewViewProvider {
  public static readonly viewType = "moon-grep-search";

  private view?: vscode.WebviewView;
  private service: Search.Service;
  private readonly extensionUri: vscode.Uri;

  constructor(extensionUri: vscode.Uri, service: Search.Service) {
    this.extensionUri = extensionUri;
    this.service = service;
  }

  private static getNonce() {
    let text = "";
    const possible = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for (let i = 0; i < 32; i++) {
      text += possible.charAt(Math.floor(Math.random() * possible.length));
    }
    return text;
  }

  public resolveWebviewView(
    webviewView: vscode.WebviewView,
    _context: vscode.WebviewViewResolveContext,
    _token: vscode.CancellationToken
  ) {
    this.view = webviewView;

    webviewView.webview.options = {
      enableScripts: true,
      localResourceRoots: [this.extensionUri],
    };

    webviewView.webview.html = this._getHtmlForWebview(webviewView.webview);

    webviewView.webview.onDidReceiveMessage(async (data) => {
      switch (data.type) {
        case "search": {
          await this._performSearch(data.value);
          break;
        }
        case "clear": {
          this.service.clear();
          if (this.view) {
            this.view.webview.postMessage({
              type: "results",
              results: [],
              stats: { matchCount: 0, fileCount: 0 },
            });
          }
          break;
        }
        case "openMatch": {
          this._openMatch(data.uri, data.range);
          break;
        }
        case "openInEditor": {
          this._openInEditor(data.value.results);
          break;
        }
      }
    });
  }

  private async _performSearch(options: Search.Options) {
    try {
      vscode.window.withProgress(
        {
          location: vscode.ProgressLocation.Notification,
          title: "Searching with Ripgrep...",
          cancellable: false,
        },
        async (_) => {
          const workspaceFolders = vscode.workspace.workspaceFolders;
          if (!workspaceFolders) {
            vscode.window.showErrorMessage(`Search failed: no workspace folder available`);
            return;
          }
          this.service.onResult.event((results) => {
            if (this.view) {
              this.view.webview.postMessage({
                type: "results",
                results: results.map((result) => {
                  return {
                    uri: vscode.workspace.asRelativePath(result.uri),
                    range: {
                      start: {
                        line: result.range.start.line,
                        character: result.range.start.character,
                      },
                      end: {
                        line: result.range.end.line,
                        character: result.range.end.character,
                      },
                    },
                    lines: result.context,
                  };
                }),
                stats: {
                  matchCount: results.length,
                  fileCount: new Set(results.map((result) => result.uri)).size,
                },
              });
            }
          });
          const promises = workspaceFolders.map((folder) => {
            return this.service.search(folder.uri, options);
          });
          await Promise.all(promises);
        }
      );
    } catch (error: any) {
      vscode.window.showErrorMessage(`Search failed: ${error.message || "Unknown error"}`);
      if (this.view) {
        this.view.webview.postMessage({
          type: "results",
          results: [],
          stats: { matchCount: 0, fileCount: 0 },
        });
      }
    }
  }

  private _openMatch(file: string, range: MatchRange) {
    const workspaceFolder = vscode.workspace.workspaceFolders?.[0];
    if (!workspaceFolder) {
      return;
    }
    const fileUri = vscode.Uri.joinPath(workspaceFolder.uri, file);

    vscode.window.showTextDocument(fileUri, {
      selection: new vscode.Range(
        new vscode.Position(range.start.line, range.start.character),
        new vscode.Position(range.end.line, range.end.character)
      ),
    });
  }

  private _openInEditor(results: Search.Result[]) {
    // This would open the search results in the editor
    // For now, we'll just show a message
    vscode.window.showInformationMessage("Open in editor functionality is coming soon.");
  }

  private _getHtmlForWebview(webview: vscode.Webview): string {
    const nonce = WebviewViewProvider.getNonce();

    const scriptUri = webview.asWebviewUri(
      vscode.Uri.joinPath(this.extensionUri, "sidebar", "index.js")
    );
    const styleUri = webview.asWebviewUri(
      vscode.Uri.joinPath(this.extensionUri, "sidebar", "index.css")
    );

    const cspSource = webview.cspSource;

    return `<!doctype html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta
      http-equiv="Content-Security-Policy"
      content="default-src 'none'; style-src ${cspSource} 'nonce-${nonce}'; script-src 'nonce-${nonce}'; font-src ${cspSource};"
    />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <link rel="stylesheet" href="${styleUri}" nonce="${nonce}" />
    <script nonce="${nonce}" src="${scriptUri}"></script>
    <title>Moon Grep Search</title>
  </head>
  <body>
    <div id="root"></div>
  </body>
</html>`;
  }
}
