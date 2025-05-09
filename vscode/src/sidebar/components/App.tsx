import React, { useState, useEffect } from "react";
import { useVSCode } from "../hooks/useVSCode";
import SearchHeader from "./SearchHeader";
import SearchInput from "./SearchInput";
import ReplaceInput from "./ReplaceInput";
import SearchOptions from "./SearchOptions";
import SearchResults from "./SearchResults";
import { SearchOptions as SearchOptionsType, Result } from "../types";

const App: React.FC = () => {
  const vscode = useVSCode();
  const [searchPattern, setSearchPattern] = useState("");
  const [replacePattern, setReplacePattern] = useState("");
  const [searchOptions, setSearchOptions] = useState<SearchOptionsType>({
    caseSensitive: false,
    wholeWord: false,
    regex: true,
    includeIgnored: false,
    includePattern: "",
    excludePattern: "node_modules",
  });
  const [results, setResults] = useState<Result[]>([]);
  const [stats, setStats] = useState({ matchCount: 0, fileCount: 0 });
  const [collapsedFiles, setCollapsedFiles] = useState<Record<string, boolean>>({});

  // Handle messages from extension
  useEffect(() => {
    const handleMessage = (event: MessageEvent) => {
      const message = event.data;
      switch (message.type) {
        case "results":
          setResults(message.results);
          setStats(message.stats);

          // Reset collapsed state for all files when new results come in
          const newCollapsedState: Record<string, boolean> = {};

          // Get unique file URIs from results
          const fileUris = new Set<string>();
          message.results.forEach((result: Result) => {
            fileUris.add(result.uri);
          });

          // Set all files to expanded by default
          fileUris.forEach((uri) => {
            newCollapsedState[uri] = false;
          });

          setCollapsedFiles(newCollapsedState);
          break;
      }
    };

    window.addEventListener("message", handleMessage);
    return () => window.removeEventListener("message", handleMessage);
  }, []);

  // Save state when inputs or collapsed state changes
  useEffect(() => {
    vscode.setState({
      searchPattern,
      replacePattern,
      collapsedFiles,
      ...searchOptions,
    });
  }, [searchPattern, replacePattern, searchOptions, collapsedFiles]);

  // Restore state when component mounts
  useEffect(() => {
    const state = vscode.getState();
    if (state) {
      setSearchPattern(state.searchPattern || "");
      setReplacePattern(state.replacePattern || "");
      setSearchOptions({
        caseSensitive: !!state.caseSensitive,
        wholeWord: !!state.wholeWord,
        regex: state.regex !== false, // Default to true
        includeIgnored: !!state.includeIgnored,
        includePattern: state.includePattern || "",
        excludePattern: state.excludePattern || "node_modules",
      });

      // Restore collapsed state if it exists
      if (state.collapsedFiles) {
        setCollapsedFiles(state.collapsedFiles);
      }
    }
  }, []);

  const performSearch = () => {
    if (!searchPattern.trim()) return;

    vscode.postMessage({
      type: "search",
      value: {
        language: "javascript",
        query: searchPattern,
        includePattern: searchOptions.includePattern,
        excludePattern: searchOptions.excludePattern,
      },
    });
  };

  const clearSearch = () => {
    setSearchPattern("");
    setReplacePattern("");
    setResults([]);
    setStats({ matchCount: 0, fileCount: 0 });
    setCollapsedFiles({}); // Clear collapsed state when search is cleared

    vscode.postMessage({
      type: "clear",
    });
  };

  const collapseAll = () => {
    // Create a new object with all files set to collapsed
    const newCollapsedState: Record<string, boolean> = {};

    // Get unique file URIs from results
    const fileUris = new Set<string>();
    results.forEach((result) => {
      fileUris.add(result.uri);
    });

    // Set all files to collapsed
    fileUris.forEach((uri) => {
      newCollapsedState[uri] = true;
    });

    setCollapsedFiles(newCollapsedState);
  };

  const expandAll = () => {
    // Create a new object with all files set to expanded
    const newCollapsedState: Record<string, boolean> = {};

    // Get unique file URIs from results
    const fileUris = new Set<string>();
    results.forEach((result) => {
      fileUris.add(result.uri);
    });

    // Set all files to expanded
    fileUris.forEach((uri) => {
      newCollapsedState[uri] = false;
    });

    setCollapsedFiles(newCollapsedState);
  };

  // Function to toggle collapse state for a specific file
  const toggleFileCollapse = (fileUri: string) => {
    setCollapsedFiles((prev) => ({
      ...prev,
      [fileUri]: !prev[fileUri],
    }));
  };

  return (
    <div className="container">
      <SearchHeader
        onRefresh={performSearch}
        onClear={clearSearch}
        onCollapseAll={collapseAll}
        onExpandAll={expandAll}
      />

      <div className="search-container">
        <SearchInput
          value={searchPattern}
          onChange={setSearchPattern}
          options={searchOptions}
          onOptionsChange={setSearchOptions}
          onSearch={performSearch}
        />

        <ReplaceInput
          value={replacePattern}
          onChange={setReplacePattern}
          searchPattern={searchPattern}
          searchOptions={searchOptions}
        />

        <SearchOptions
          includeIgnored={searchOptions.includeIgnored}
          onIncludeIgnoredChange={(value) =>
            setSearchOptions({ ...searchOptions, includeIgnored: value })
          }
          includePattern={searchOptions.includePattern}
          onIncludePatternChange={(value) =>
            setSearchOptions({ ...searchOptions, includePattern: value })
          }
          excludePattern={searchOptions.excludePattern}
          onExcludePatternChange={(value) =>
            setSearchOptions({ ...searchOptions, excludePattern: value })
          }
        />
      </div>

      <SearchResults
        results={results}
        stats={stats}
        collapsedFiles={collapsedFiles}
        onToggleCollapse={toggleFileCollapse}
      />
    </div>
  );
};

export default App;
