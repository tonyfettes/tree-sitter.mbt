import React, { ReactNode } from "react";

interface InputBoxProps {
  value: string;
  onChange: (value: string) => void;
  placeholder: string;
  id?: string;
  className?: string;
  onKeyUp?: (e: React.KeyboardEvent<HTMLInputElement>) => void;
  controls?: ReactNode;
}

/**
 * A reusable input box component with optional controls
 */
export const InputBox: React.FC<InputBoxProps> = ({
  value,
  onChange,
  placeholder,
  id,
  className = "",
  onKeyUp,
  controls,
}) => {
  const baseClassName = className.includes("replace") ? "replace-input-box" : "search-input-box";

  return (
    <div className={`${baseClassName} ${className}`}>
      <input
        type="text"
        className={className.includes("replace") ? "replace-input" : "search-input"}
        id={id}
        placeholder={placeholder}
        value={value}
        onChange={(e) => onChange(e.target.value)}
        onKeyUp={onKeyUp}
      />
      {controls && <div className="search-controls">{controls}</div>}
    </div>
  );
};

export default InputBox;
