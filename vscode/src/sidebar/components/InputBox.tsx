import React, { ReactNode, useRef, useEffect } from "react";

interface InputBoxProps {
  value: string;
  onChange: (value: string) => void;
  placeholder: string;
  id?: string;
  className?: string;
  onKeyDown?: (e: React.KeyboardEvent<HTMLTextAreaElement>) => void;
  controls?: ReactNode;
  label?: string;
}

/**
 * A reusable input box component with optional controls and label
 * @param value - The current value of the input
 * @param onChange - Function to call when the value changes
 * @param placeholder - Placeholder text for the input
 * @param id - Optional ID for the textarea element
 * @param className - Optional additional CSS class names
 * @param onKeyDown - Optional function to handle key down events
 * @param controls - Optional React node to render as controls
 * @param label - Optional label text to display above the input
 */
export const InputBox: React.FC<InputBoxProps> = ({
  value,
  onChange,
  placeholder,
  id,
  className = "",
  onKeyDown,
  controls,
  label,
}) => {
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
    <div>
      {label && <label className="input-box-label">{label}</label>}
      <div className={`input-box ${className}`}>
        <textarea
          ref={textareaRef}
          className="input-box-textarea"
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
    </div>
  );
};

export default InputBox;
