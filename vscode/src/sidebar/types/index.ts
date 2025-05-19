export interface MatchPosition {
  line: number;
  character: number;
}

export interface MatchRange {
  start: MatchPosition;
  end: MatchPosition;
}

export interface Result {
  uri: string;
  range: MatchRange;
  lines: string[];
}

export interface SearchOptions {
  includeIgnored: boolean;
  includePattern: string;
  excludePattern: string;
}

export interface SearchStats {
  matchCount: number;
  fileCount: number;
}
