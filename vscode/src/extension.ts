import * as vscode from "vscode";
import { WebviewViewProvider } from "./search";
import MoonGrep, { Options } from "./moon-grep";

export function activate(context: vscode.ExtensionContext) {
  console.log('Congratulations, your extension "moon-grep" is now active!');

  const moonGrep = new MoonGrep();

  // Register the Search View provider
  const searchViewProvider = new WebviewViewProvider(context.extensionUri);
  context.subscriptions.push(
    vscode.window.registerWebviewViewProvider(WebviewViewProvider.viewType, searchViewProvider)
  );

  // Register the search command
  const searchCommandHandler = async (options: Options) => {
    if (!options || !options.pattern) {
      vscode.window.showInformationMessage("Please enter a search pattern in the Moon Grep view.");
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
          const results = await moonGrep.search(options, vscode.workspace.workspaceFolders);

          if (results.length === 0) {
            vscode.window.showInformationMessage(`No results found for "${options.pattern}".`);
          } else {
            // Focus the search view
            vscode.commands.executeCommand("moon-grep-search.focus");
          }
        }
      );
    } catch (error: any) {
      vscode.window.showErrorMessage(`Search failed: ${error.message || "Unknown error"}`);
    }
  };

  context.subscriptions.push(
    vscode.commands.registerCommand("moon-grep.search", searchCommandHandler)
  );

  // Original Hello World command (can be removed or kept for testing)
  const disposable = vscode.commands.registerCommand("moon-grep.helloWorld", () => {
    vscode.window.showInformationMessage("Hello World from moon-grep!");
  });
  context.subscriptions.push(disposable);
}

export function deactivate() {}
