import React from "react";
import { useVSCode } from "../hooks/useVSCode";
import { MatchRange } from "../types";

interface MatchItemProps {
  uri: string;
  range: MatchRange;
  lines: string[];
}

export const MatchItem: React.FC<MatchItemProps> = ({ uri, range, lines }) => {
  const vscode = useVSCode();

  const handleClick = () => {
    vscode.postMessage({
      type: "openMatch",
      uri,
      range,
    });
  };

  return (
    <div className="match-item" onClick={handleClick}>
      <div className="match-content">
        {lines.map((line, i) => (
          <div key={i} className="match-line">
            {i === 0 && <span className="match-text">{line.slice(0, range.start.character)}</span>}
            <span className="match-highlight">
              {line.slice(
                i === 0 ? range.start.character : 0,
                i === lines.length - 1 ? range.end.character : line.length
              )}
            </span>
            {i === lines.length - 1 && (
              <span className="match-text">{line.slice(range.end.character)}</span>
            )}
          </div>
        ))}
      </div>
    </div>
  );
};

export default MatchItem;
