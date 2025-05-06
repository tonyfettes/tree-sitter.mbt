import * as vscode from "vscode";
import { SearchViewProvider } from "./searchView";
import { MoonGrep, Options, Result } from "./moon-grep";
import { SearchResultsProvider } from "./searchResultsProvider";

export function activate(context: vscode.ExtensionContext) {
  console.log('Congratulations, your extension "moon-grep" is now active!');

  const ripgrepService = new MoonGrep();
  const searchResultsProvider = new SearchResultsProvider();

  // Register the Search View provider
  const searchViewProvider = new SearchViewProvider(context.extensionUri);
  context.subscriptions.push(
    vscode.window.registerWebviewViewProvider(
      SearchViewProvider.viewType,
      searchViewProvider
    )
  );

  // Register the Tree View for search results
  const treeView = vscode.window.createTreeView("moon-grep-searchResultsView", {
    treeDataProvider: searchResultsProvider,
  });

  // Add the tree view to subscriptions so it gets disposed properly
  context.subscriptions.push(treeView);


  // Register the search command
  const searchCommandHandler = async (options: Options) => {
    if (!options || !options.pattern) {
      vscode.window.showInformationMessage(
        "Please enter a search pattern in the Moon Grep view."
      );
      return;
    }
    try {
      vscode.window.withProgress({
        location: vscode.ProgressLocation.Notification,
        title: "Searching with Ripgrep...",
        cancellable: false // Ripgrep can be fast, cancellation might be overkill for v1
      }, async (progress) => {
        const results = await ripgrepService.search(options, vscode.workspace.workspaceFolders);
        searchResultsProvider.refresh(results);
        if (results.length === 0) {
          vscode.window.showInformationMessage(`No results found for "${options.pattern}".`);
        } else {
          // Potentially reveal the results view if it's not visible
          // vscode.commands.executeCommand('workbench.view.extension.moon-grep-sidebar'); // Focus the container
          // vscode.commands.executeCommand('moon-grep-searchResultsView.focus'); // Focus the specific tree view
        }
      });
    } catch (error: any) {
      vscode.window.showErrorMessage(
        `Search failed: ${error.message || "Unknown error"}`
      );
      searchResultsProvider.refresh([]); // Clear results on error
    }
  };

  context.subscriptions.push(
    vscode.commands.registerCommand("moon-grep.search", searchCommandHandler)
  );


  // Original Hello World command (can be removed or kept for testing)
  const disposable = vscode.commands.registerCommand(
    "moon-grep.helloWorld",
    () => {
      vscode.window.showInformationMessage("Hello World from moon-grep!");
    }
  );
  context.subscriptions.push(disposable);
}

export function deactivate() {}
