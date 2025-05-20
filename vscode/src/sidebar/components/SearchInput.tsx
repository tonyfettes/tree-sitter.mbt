import React from "react";
import InputBox from "./InputBox";

interface SearchInputProps {
  value: string;
  onChange: (value: string) => void;
  onSearch: () => void;
}

export const SearchInput: React.FC<SearchInputProps> = ({ value, onChange, onSearch }) => {
  const handleKeyDown = (e: React.KeyboardEvent<HTMLTextAreaElement>) => {
    if (e.key === "Enter") {
      // If Shift+Enter is pressed, let the default behavior happen (new line)
      if (!e.shiftKey) {
        e.preventDefault();
        onSearch();
      }
    }
  };

  return (
    <InputBox
      id="searchInput"
      placeholder="Search"
      value={value}
      onChange={onChange}
      onKeyDown={handleKeyDown}
    />
  );
};

export default SearchInput;
