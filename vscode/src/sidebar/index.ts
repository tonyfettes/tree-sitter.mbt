import "@vscode/codicons/dist/codicon.css";
import "./index.css";

// Declare the vscode API
declare const acquireVsCodeApi: () => {
  postMessage: (message: any) => void;
  getState: () => any;
  setState: (state: any) => void;
};

interface SearchOptions {
  caseSensitive: boolean;
  wholeWord: boolean;
  regex: boolean;
  includeIgnored: boolean;
}

interface MatchResult {
  file: string;
  line: number;
  text: string;
  match: string;
}

document.addEventListener("DOMContentLoaded", () => {
  // Initialize VSCode API
  const vscode = acquireVsCodeApi();

  // UI Elements
  const searchInput = document.getElementById("searchInput") as HTMLInputElement;
  const replaceInput = document.getElementById("replaceInput") as HTMLInputElement;
  const filePatternInput = document.getElementById("filePatternInput") as HTMLInputElement;
  const searchResults = document.getElementById("searchResults") as HTMLDivElement;
  const noResultsMessage = document.getElementById("noResultsMessage") as HTMLDivElement;

  // Buttons
  const refreshButton = document.getElementById("refreshButton") as HTMLButtonElement;
  const clearButton = document.getElementById("clearButton") as HTMLButtonElement;
  const collapseAllButton = document.getElementById("collapseAllButton") as HTMLButtonElement;
  const expandAllButton = document.getElementById("expandAllButton") as HTMLButtonElement;
  const caseSensitiveButton = document.getElementById("caseSensitiveButton") as HTMLButtonElement;
  const wholeWordButton = document.getElementById("wholeWordButton") as HTMLButtonElement;
  const regexButton = document.getElementById("regexButton") as HTMLButtonElement;
  const includeIgnoredCheckbox = document.getElementById(
    "includeIgnoredCheckbox"
  ) as HTMLInputElement;
  const replaceButton = document.getElementById("replaceButton") as HTMLButtonElement;
  const replaceAllButton = document.getElementById("replaceAllButton") as HTMLButtonElement;

  // Search options state
  const searchOptions: SearchOptions = {
    caseSensitive: false,
    wholeWord: false,
    regex: true,
    includeIgnored: false,
  };

  // Toggle option buttons
  function toggleOptionButton(button: HTMLButtonElement, option: keyof SearchOptions): void {
    button.classList.toggle("active");
    searchOptions[option] = button.classList.contains("active");
  }

  caseSensitiveButton.addEventListener("click", () =>
    toggleOptionButton(caseSensitiveButton, "caseSensitive")
  );
  wholeWordButton.addEventListener("click", () => toggleOptionButton(wholeWordButton, "wholeWord"));
  regexButton.addEventListener("click", () => toggleOptionButton(regexButton, "regex"));
  includeIgnoredCheckbox.addEventListener("change", () => {
    searchOptions.includeIgnored = includeIgnoredCheckbox.checked;
  });

  // Set initial state for regex button (active by default)
  regexButton.classList.add("active");

  // Search action
  function performSearch(): void {
    const pattern = searchInput.value;
    if (!pattern.trim()) {
      return;
    }

    // Show searching indicator
    noResultsMessage.textContent = "Searching...";
    noResultsMessage.style.display = "block";

    vscode.postMessage({
      type: "search",
      value: {
        pattern: pattern,
        filePattern: filePatternInput.value,
        caseSensitive: searchOptions.caseSensitive,
        wholeWord: searchOptions.wholeWord,
        regex: searchOptions.regex,
        includeIgnored: searchOptions.includeIgnored,
      },
    });
  }

  // Replace action
  function performReplace(replaceAll = false): void {
    vscode.postMessage({
      type: replaceAll ? "replaceAll" : "replace",
      value: {
        searchPattern: searchInput.value,
        replacePattern: replaceInput.value,
        filePattern: filePatternInput.value,
        caseSensitive: searchOptions.caseSensitive,
        wholeWord: searchOptions.wholeWord,
        regex: searchOptions.regex,
        includeIgnored: searchOptions.includeIgnored,
      },
    });
  }

  // Event listeners
  searchInput.addEventListener("keyup", (e) => {
    if ((e as KeyboardEvent).key === "Enter") {
      performSearch();
    }
  });

  refreshButton.addEventListener("click", performSearch);
  clearButton.addEventListener("click", () => {
    searchInput.value = "";
    replaceInput.value = "";
    filePatternInput.value = "";
    noResultsMessage.textContent = "No results found yet. Try searching for something.";
    noResultsMessage.style.display = "block";
    searchResults.querySelectorAll(".result-item").forEach((el) => el.remove());

    vscode.postMessage({
      type: "clear",
    });
  });

  replaceButton.addEventListener("click", () => performReplace(false));
  replaceAllButton.addEventListener("click", () => performReplace(true));

  collapseAllButton.addEventListener("click", () => {
    searchResults.querySelectorAll(".file-item").forEach((item) => {
      item.classList.add("collapsed");
    });
  });

  expandAllButton.addEventListener("click", () => {
    searchResults.querySelectorAll(".file-item").forEach((item) => {
      item.classList.remove("collapsed");
    });
  });

  // Toggle file results on click
  searchResults.addEventListener("click", (e) => {
    const target = e.target as HTMLElement;
    const fileHeader = target.closest(".file-header");
    if (fileHeader) {
      const fileItem = fileHeader.parentElement;
      if (fileItem) {
        fileItem.classList.toggle("collapsed");
      }
    }

    const matchItem = target.closest(".match-item") as HTMLElement;
    if (matchItem && matchItem.dataset.file && matchItem.dataset.line) {
      vscode.postMessage({
        type: "openMatch",
        value: {
          file: matchItem.dataset.file,
          line: parseInt(matchItem.dataset.line),
        },
      });
    }
  });

  // Handle messages from extension
  window.addEventListener("message", (event) => {
    const message = event.data;

    switch (message.type) {
      case "results":
        updateSearchResults(message.results, message.stats);
        break;
    }
  });

  // Helper function to escape HTML
  function escapeHtml(str: string): string {
    return str
      .replace(/&/g, "&amp;")
      .replace(/</g, "&lt;")
      .replace(/>/g, "&gt;")
      .replace(/"/g, "&quot;")
      .replace(/'/g, "&#039;");
  }

  // Update search results in the UI
  function updateSearchResults(
    results: MatchResult[],
    stats: { matchCount: number; fileCount: number }
  ): void {
    // Remove existing results except the no-results message
    searchResults.querySelectorAll(".file-item, .search-info").forEach((el) => el.remove());

    // Handle no results
    if (!results || results.length === 0) {
      noResultsMessage.textContent = "No results found.";
      noResultsMessage.style.display = "block";
      return;
    }

    // Hide no results message
    noResultsMessage.style.display = "none";

    // Add search info bar
    const searchInfo = document.createElement("div");
    searchInfo.className = "search-info";
    searchInfo.innerHTML = `
      <span>${stats.matchCount} results in ${stats.fileCount} files</span>
      <a class="open-editor" id="openInEditor">Open in editor</a>
    `;
    searchResults.appendChild(searchInfo);

    // Group results by file
    const fileGroups: Record<string, MatchResult[]> = {};
    results.forEach((result) => {
      if (!fileGroups[result.file]) {
        fileGroups[result.file] = [];
      }
      fileGroups[result.file].push(result);
    });

    // Create file items with their matches
    for (const [file, matches] of Object.entries(fileGroups)) {
      const fileItem = document.createElement("div");
      fileItem.className = "file-item";

      const fileHeader = document.createElement("div");
      fileHeader.className = "file-header";
      fileHeader.innerHTML = `
        <span class="expander"><i class="codicon codicon-chevron-down"></i></span>
        <span class="file-name">${file}</span>
        <span class="match-count">${matches.length}</span>
      `;

      const matchList = document.createElement("div");
      matchList.className = "match-list";

      // Add match items
      matches.forEach((match) => {
        const matchItem = document.createElement("div");
        matchItem.className = "match-item";
        matchItem.dataset.file = match.file;
        matchItem.dataset.line = match.line.toString();

        // Highlight the match within the line
        const escapedMatch = escapeHtml(match.match);
        const escapedText = escapeHtml(match.text);
        const highlightedText = escapedText.replace(
          new RegExp(escapedMatch, "g"),
          `<span class="match-highlight">${escapedMatch}</span>`
        );

        matchItem.innerHTML = `
          <span class="match-line">${match.line}</span>
          <pre class="match-text">${highlightedText}</pre>
        `;

        matchList.appendChild(matchItem);
      });

      fileItem.appendChild(fileHeader);
      fileItem.appendChild(matchList);
      searchResults.appendChild(fileItem);
    }

    // Add event listener for "Open in editor"
    const openInEditorElement = document.getElementById("openInEditor");
    if (openInEditorElement) {
      openInEditorElement.addEventListener("click", () => {
        vscode.postMessage({
          type: "openInEditor",
          value: {
            results: results,
          },
        });
      });
    }
  }

  // Restore state when the webview is restored
  const previousState = vscode.getState();
  if (previousState) {
    searchInput.value = previousState.searchPattern || "";
    replaceInput.value = previousState.replacePattern || "";
    filePatternInput.value = previousState.filePattern || "";

    if (previousState.caseSensitive) {
      caseSensitiveButton.classList.add("active");
      searchOptions.caseSensitive = true;
    }

    if (previousState.wholeWord) {
      wholeWordButton.classList.add("active");
      searchOptions.wholeWord = true;
    }

    if (previousState.regex === false) {
      regexButton.classList.remove("active");
      searchOptions.regex = false;
    }

    if (previousState.includeIgnored) {
      includeIgnoredCheckbox.checked = true;
      searchOptions.includeIgnored = true;
    }
  }

  // Save state when inputs change
  function saveState(): void {
    vscode.setState({
      searchPattern: searchInput.value,
      replacePattern: replaceInput.value,
      filePattern: filePatternInput.value,
      caseSensitive: searchOptions.caseSensitive,
      wholeWord: searchOptions.wholeWord,
      regex: searchOptions.regex,
      includeIgnored: searchOptions.includeIgnored,
    });
  }

  searchInput.addEventListener("input", saveState);
  replaceInput.addEventListener("input", saveState);
  filePatternInput.addEventListener("input", saveState);
  caseSensitiveButton.addEventListener("click", saveState);
  wholeWordButton.addEventListener("click", saveState);
  regexButton.addEventListener("click", saveState);
  includeIgnoredCheckbox.addEventListener("change", saveState);
});
