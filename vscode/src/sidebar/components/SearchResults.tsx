import React from "react";
import { Result, SearchStats } from "../types";
import FileItem from "./FileItem";
import { useVSCode } from "../hooks/useVSCode";

interface SearchResultsProps {
  results: Result[];
  stats: SearchStats;
  collapsedFiles: Record<string, boolean>;
  onToggleCollapse: (fileUri: string) => void;
}

export const SearchResults: React.FC<SearchResultsProps> = ({
  results,
  stats,
  collapsedFiles,
  onToggleCollapse,
}) => {
  const vscode = useVSCode();

  // Group results by file
  const fileGroups: Record<string, Result[]> = {};
  results.forEach((result) => {
    if (!fileGroups[result.uri]) {
      fileGroups[result.uri] = [];
    }
    fileGroups[result.uri].push(result);
  });

  const handleOpenInEditor = () => {
    vscode.postMessage({
      type: "openInEditor",
      value: {
        results,
      },
    });
  };

  if (results.length === 0) {
    return (
      <div className="no-results" id="noResultsMessage">
        No results found yet. Try searching for something.
      </div>
    );
  }

  return (
    <div className="search-results">
      <div className="search-info">
        <span>
          {stats.matchCount} results in {stats.fileCount} files
        </span>
        <a className="open-editor" onClick={handleOpenInEditor}>
          Open in editor
        </a>
      </div>

      {Object.entries(fileGroups).map(([file, matches]) => (
        <FileItem
          key={file}
          file={file}
          matches={matches}
          collapsed={!!collapsedFiles[file]}
          onToggleCollapse={() => onToggleCollapse(file)}
        />
      ))}
    </div>
  );
};

export default SearchResults;
