import React from "react";
import { useVSCode } from "../hooks/useVSCode";
import InputBox from "./InputBox";
import ControlButton from "./ControlButton";

interface ReplaceInputProps {
  value: string;
  onChange: (value: string) => void;
  searchPattern?: string;
  filePattern?: string;
  searchOptions?: {
    includeIgnored: boolean;
  };
}

export const ReplaceInput: React.FC<ReplaceInputProps> = ({
  value,
  onChange,
  searchPattern,
  filePattern,
  searchOptions,
}) => {
  const vscode = useVSCode();

  const handleReplace = () => {
    vscode.postMessage({
      type: "replace",
      value: {
        searchPattern,
        replacePattern: value,
        filePattern,
        ...searchOptions,
      },
    });
  };

  const handleReplaceAll = () => {
    vscode.postMessage({
      type: "replaceAll",
      value: {
        searchPattern,
        replacePattern: value,
        filePattern,
        ...searchOptions,
      },
    });
  };

  const replaceControls = (
    <>
      <ControlButton id="replaceButton" icon="replace" title="Replace" onClick={handleReplace} />
      <ControlButton
        id="replaceAllButton"
        icon="replace-all"
        title="Replace All"
        onClick={handleReplaceAll}
      />
    </>
  );

  return (
    <InputBox
      id="replaceInput"
      placeholder="Replace"
      value={value}
      onChange={onChange}
      className="replace"
      controls={replaceControls}
    />
  );
};

export default ReplaceInput;
