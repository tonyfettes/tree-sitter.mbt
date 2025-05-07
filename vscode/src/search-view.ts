import * as vscode from "vscode";
import * as Handlebars from "handlebars";
import searchViewHtml from "./search-view.html";

export class SearchViewProvider implements vscode.WebviewViewProvider {
  public static readonly viewType = "moon-grep-search";

  private _view?: vscode.WebviewView;

  constructor(private readonly _extensionUri: vscode.Uri) {}

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
          const { pattern, filePattern, caseSensitive, wholeWord } = data.value;
          vscode.commands.executeCommand("moon-grep.search", {
            pattern,
            filePattern,
            caseSensitive,
            wholeWord,
          });
          break;
        }
      }
    });
  }

  private _getHtmlForWebview(webview: vscode.Webview): string {
    const nonce = getNonce();
    const template = Handlebars.compile(searchViewHtml);
    const data = {
      cspSource: webview.cspSource,
      nonce: nonce,
    };
    return template(data);
  }
}

function getNonce() {
  let text = "";
  const possible =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  for (let i = 0; i < 32; i++) {
    text += possible.charAt(Math.floor(Math.random() * possible.length));
  }
  return text;
}
