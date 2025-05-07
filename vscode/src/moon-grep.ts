import * as VSCode from "vscode";
import * as ChildProcess from "node:child_process";

export interface Result {
  file: string;
  line: number;
  match: string;
  text: string;
}

export interface Options {
  pattern: string;
  filePattern?: string;
  caseSensitive?: boolean;
  wholeWord?: boolean;
  regex?: boolean;
  includeIgnored?: boolean;
}

export default class MoonGrep {
  public async search(
    options: Options,
    workspaceFolders: readonly VSCode.WorkspaceFolder[] | undefined
  ): Promise<Result[]> {
    if (!workspaceFolders || workspaceFolders.length === 0) {
      VSCode.window.showErrorMessage("No workspace folder open to search in.");
      return [];
    }

    const results: Result[] = [];
    const cwd = workspaceFolders[0].uri.fsPath; // Search in the first workspace folder

    const args = this.buildRgArgs(options);
    const ripgrepPath = "rg"; // Assume rg is in PATH

    return new Promise((resolve, reject) => {
      const rgProc = ChildProcess.spawn(ripgrepPath, args, {
        cwd,
        stdio: ["ignore", "pipe", "pipe"],
      });
      let stdout = "";
      let stderr = "";

      rgProc.stdout.on("data", (data) => {
        stdout += data.toString();
      });

      rgProc.stderr.on("data", (data) => {
        stderr += data.toString();
      });

      rgProc.on("close", (code) => {
        if (code === 0 || code === 1) {
          // Ripgrep exits with 1 if no matches are found
          const lines = stdout.split("\n").filter((line) => line.trim() !== "");
          for (const line of lines) {
            try {
              // Ripgrep output format with --json:
              // {"type":"match","data":{"path":{"text":"src/extension.ts"},"lines":{"text":"..."},"line_number":29,"absolute_offset":769,"submatches":[{"match":{"text":"moon-grep.search"},"start":32,"end":48}]}}
              // Ripgrep output format without --json (default):
              // path/to/file:line_number:matched_text
              // For simplicity, we'll parse the default format first.
              // A more robust solution would use --json and parse the JSON output.
              const parts = line.split(":");
              if (parts.length >= 3) {
                const file = parts[0];
                const lineNumber = parseInt(parts[1], 10);
                const matchText = parts.slice(2).join(":"); // Re-join if match text contained colons

                // To get the full line text, we'd ideally need another rg call or read the file.
                // For now, let's use the matched text as the line text for simplicity.
                // A more complete solution would fetch the actual line content.
                results.push({
                  file: file,
                  line: lineNumber,
                  match: matchText,
                  text: matchText, // Placeholder, ideally fetch full line
                });
              }
            } catch (e) {
              console.error("Error parsing ripgrep output line:", line, e);
            }
          }
          resolve(results);
        } else {
          console.error(`Ripgrep process exited with code ${code}`);
          console.error("Ripgrep stderr:", stderr);
          VSCode.window.showErrorMessage(
            `Ripgrep search failed. Error: ${stderr || "Unknown error"}`
          );
          reject(new Error(stderr || `Ripgrep process exited with code ${code}`));
        }
      });

      rgProc.on("error", (err) => {
        console.error("Failed to start ripgrep process.", err);
        VSCode.window.showErrorMessage(
          `Failed to start ripgrep: ${err.message}. Make sure ripgrep (rg) is installed and in your PATH.`
        );
        reject(err);
      });
    });
  }

  private buildRgArgs(options: Options): string[] {
    const args = ["--vimgrep"]; // --vimgrep gives file:line:col:text format, easier to parse initially

    if (options.pattern) {
      // Handle regex mode
      if (options.regex !== false) {
        args.push("-e", options.pattern);
      } else {
        // Escape regex special characters if regex mode is disabled
        args.push("-F", options.pattern);
      }
    } else {
      // Should not happen if UI validates
      throw new Error("Search pattern is required.");
    }

    if (!options.caseSensitive) {
      args.push("-i"); // Case-insensitive
    }

    if (options.wholeWord) {
      args.push("-w"); // Whole word
    }

    if (options.includeIgnored) {
      args.push("--no-ignore"); // Include files that are normally ignored
    }

    if (options.filePattern) {
      // Ripgrep uses globs directly. Multiple -g flags can be used.
      // Example: -g "*.ts" -g "!node_modules/**"
      const patterns = options.filePattern
        .split(",")
        .map((p) => p.trim())
        .filter((p) => p);
      patterns.forEach((p) => args.push("-g", p));
    }

    // Add current workspace folder path
    // rg will search the CWD by default if no path is given.
    // We set CWD when spawning, so no need to add '.' here.

    return args;
  }
}
