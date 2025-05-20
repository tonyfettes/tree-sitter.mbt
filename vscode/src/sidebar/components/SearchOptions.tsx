import React from "react";
import InputBox from "./InputBox";
import ControlButton from "./ControlButton";

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
    <ControlButton icon="book" title="Search only in Open Editors" onClick={() => {}} />
  );

  const excludeControls = (
    <ControlButton
      icon="gear"
      className={includeIgnored ? "active" : ""}
      onClick={() => onIncludeIgnoredChange(!includeIgnored)}
      title={includeIgnored ? "Exclude Ignored Files" : "Include Ignored Files"}
    />
  );

  return (
    <div className="search-options">
      <div className="file-pattern-section">
        <InputBox
          value={includePattern}
          onChange={onIncludePatternChange}
          placeholder=""
          controls={includeControls}
          label="files to include"
        />

        <InputBox
          value={excludePattern}
          onChange={onExcludePatternChange}
          placeholder=""
          controls={excludeControls}
          label="files to exclude"
        />
      </div>
    </div>
  );
};

export default SearchOptions;
