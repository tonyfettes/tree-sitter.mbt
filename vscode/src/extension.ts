import vscode from "vscode";
import * as Sidebar from "./sidebar";
import * as Search from "./search";

export async function activate(context: vscode.ExtensionContext) {
  await Search.init();
  const searchService = new Search.Service(context.extensionUri);
  const sidebarWebviewProvider = new Sidebar.WebviewViewProvider(
    context.extensionUri,
    searchService
  );
  context.subscriptions.push(
    vscode.window.registerWebviewViewProvider(
      Sidebar.WebviewViewProvider.viewType,
      sidebarWebviewProvider
    )
  );
}

export function deactivate() {}
