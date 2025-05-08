import React from "react";
import InputBox from "./InputBox";

interface SearchOptionsProps {
  includeIgnored: boolean;
  onIncludeIgnoredChange: (value: boolean) => void;
  includePattern: string;
  onIncludePatternChange: (value: string) => void;
  excludePattern: string;
  onExcludePatternChange: (value: string) => void;
}

export const SearchOptions: React.FC<SearchOptionsProps> = ({
  includeIgnored,
  onIncludeIgnoredChange,
  includePattern,
  onIncludePatternChange,
  excludePattern,
  onExcludePatternChange,
}) => {
  const includeControls = (
    <button className="file-pattern-browse-button">
      <span className="codicon codicon-file-directory"></span>
    </button>
  );

  const excludeControls = (
    <button
      className={`file-pattern-browse-button ${includeIgnored ? "active" : ""}`}
      onClick={() => onIncludeIgnoredChange(!includeIgnored)}
      title={includeIgnored ? "Exclude Ignored Files" : "Include Ignored Files"}
    >
      <span className="codicon codicon-gear"></span>
    </button>
  );

  return (
    <div className="search-options">
      <div className="file-pattern-section">
        <div className="file-pattern-label">files to include</div>
        <InputBox
          value={includePattern}
          onChange={onIncludePatternChange}
          placeholder=""
          controls={includeControls}
        />

        <div className="file-pattern-label">files to exclude</div>
        <InputBox
          value={excludePattern}
          onChange={onExcludePatternChange}
          placeholder=""
          controls={excludeControls}
        />
      </div>
    </div>
  );
};

export default SearchOptions;
