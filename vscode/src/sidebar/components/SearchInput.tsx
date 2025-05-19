import React from "react";
import { SearchOptions } from "../types";
import InputBox from "./InputBox";
import ControlButton from "./ControlButton";

interface SearchInputProps {
  value: string;
  onChange: (value: string) => void;
  options: SearchOptions;
  onOptionsChange: (options: SearchOptions) => void;
  onSearch: () => void;
}

export const SearchInput: React.FC<SearchInputProps> = ({
  value,
  onChange,
  options,
  onOptionsChange,
  onSearch,
}) => {
  const toggleOption = (option: keyof SearchOptions) => {
    onOptionsChange({
      ...options,
      [option]: !options[option],
    });
  };

  const handleKeyDown = (e: React.KeyboardEvent<HTMLTextAreaElement>) => {
    if (e.key === "Enter") {
      // If Shift+Enter is pressed, let the default behavior happen (new line)
      if (!e.shiftKey) {
        e.preventDefault();
        onSearch();
      }
    }
  };

  const searchControls = (
    <>
      <ControlButton
        id="moreOptionsButton"
        icon="ellipsis"
        title="More Options"
        onClick={() => {}}
      />
    </>
  );

  return (
    <InputBox
      id="searchInput"
      placeholder="Search"
      value={value}
      onChange={onChange}
      onKeyDown={handleKeyDown}
      controls={searchControls}
    />
  );
};

export default SearchInput;
