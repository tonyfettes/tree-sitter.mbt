import React, { ReactNode, useRef, useEffect } from "react";

interface InputBoxProps {
  value: string;
  onChange: (value: string) => void;
  placeholder: string;
  id?: string;
  className?: string;
  onKeyDown?: (e: React.KeyboardEvent<HTMLTextAreaElement>) => void;
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
  onKeyDown,
  controls,
}) => {
  const baseClassName = className.includes("replace") ? "replace-input-box" : "search-input-box";
  const textareaRef = useRef<HTMLTextAreaElement>(null);

  // Function to adjust textarea height based on content
  const adjustHeight = () => {
    const textarea = textareaRef.current;
    if (textarea) {
      // Reset height to auto to get the correct scrollHeight
      textarea.style.height = "auto";
      // Set the height to match the content (with a minimum height)
      const newHeight = Math.max(24, textarea.scrollHeight);
      textarea.style.height = `${newHeight}px`;
    }
  };

  // Adjust height when value changes
  useEffect(() => {
    adjustHeight();
  }, [value]);

  return (
    <div className={`${baseClassName} ${className}`}>
      <textarea
        ref={textareaRef}
        className={className.includes("replace") ? "replace-input" : "search-input"}
        id={id}
        placeholder={placeholder}
        value={value}
        onChange={(e) => {
          onChange(e.target.value);
          // Height will be adjusted in the useEffect
        }}
        onKeyDown={onKeyDown}
        rows={1}
        style={{ resize: "none", overflow: "hidden" }} // Changed to hidden to prevent scrollbar
      />
      {controls && <div className="search-controls">{controls}</div>}
    </div>
  );
};

export default InputBox;
