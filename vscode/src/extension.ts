import * as vscode from "vscode";
import * as Sidebar from "./sidebar";
import * as Search from "./search";

export function activate(context: vscode.ExtensionContext) {
  console.log('Congratulations, your extension "moon-grep" is now active!');

  const SidebarWebviewProvider = new Sidebar.WebviewViewProvider(context.extensionUri);
  context.subscriptions.push(
    vscode.window.registerWebviewViewProvider(
      Sidebar.WebviewViewProvider.viewType,
      SidebarWebviewProvider
    )
  );

  const searchService = new Search.Service();
  const searchCommand = vscode.commands.registerCommand(
    "moon-grep.search",
    async (options: Search.Options) => {
      try {
        for (const folder of vscode.workspace.workspaceFolders || []) {
          const uri = folder.uri;
          await searchService.search(uri, options);
        }
      } catch (error) {
        if (error instanceof Error) {
          vscode.window.showErrorMessage(`Search failed: ${error.message}`);
        } else {
          vscode.window.showErrorMessage("Search failed: Unknown error");
        }
      }
    }
  );
  context.subscriptions.push(searchCommand);

  // Original Hello World command (can be removed or kept for testing)
  const disposable = vscode.commands.registerCommand("moon-grep.helloWorld", () => {
    vscode.window.showInformationMessage("Hello World from moon-grep!");
  });
  context.subscriptions.push(disposable);
}

export function deactivate() {}
