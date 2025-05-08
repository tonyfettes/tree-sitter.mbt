import React from "react";
import { Result } from "../types";
import MatchItem from "./MatchItem";
import Codicon from "./Codicon";

interface FileItemProps {
  file: string;
  matches: Result[];
  collapsed: boolean;
  onToggleCollapse: () => void;
}

export const FileItem: React.FC<FileItemProps> = ({
  file,
  matches,
  collapsed,
  onToggleCollapse,
}) => {
  return (
    <div className={`file-item ${collapsed ? "collapsed" : ""}`}>
      <div className="file-header" onClick={onToggleCollapse}>
        <span className="expander">
          <Codicon name={`chevron-${collapsed ? "right" : "down"}`} />
        </span>
        <span className="file-name">{file}</span>
        <span className="match-count">{matches.length}</span>
      </div>
      <div className="match-list">
        {matches.map((match, index) => (
          <MatchItem
            key={`${match.uri}-${index}`}
            uri={match.uri}
            range={match.range}
            lines={match.lines}
          />
        ))}
      </div>
    </div>
  );
};

export default FileItem;
