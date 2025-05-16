import * as Grep from "../target/js/release/build/grep/grep.js";
import * as TS from "web-tree-sitter";
import TSMoonBit from "../.mooncakes/tonyfettes/tree_sitter_moonbit/tree-sitter-moonbit.wasm";
import { parentPort } from "worker_threads";

interface SearchRequest {
  type: "search";
  id: number;
  content: string;
}

interface CompileRequest {
  type: "compile";
  id: number;
  query: string;
}

export type Request = SearchRequest | CompileRequest;

interface Position {
  row: number;
  column: number;
}

interface Range {
  start: Position;
  end: Position;
}

interface FoundResponse {
  type: "found";
  id: number;
  captures: Record<string, {
    text: string;
    range: Range;
  }[]>;
}

interface FinishResponse {
  type: "finish";
  id: number;
}

interface ErrorResponse {
  type: "error";
  id: number;
  error: any;
}

interface ReadyResponse {
  type: "ready";
}

export type Response = FoundResponse | ErrorResponse | FinishResponse | ReadyResponse;

await TS.Parser.init();

Grep.setup(await TS.Language.load(TSMoonBit));

parentPort?.on("message", (event: Request) => {
  try {
    switch (event.type) {
      case "search": {
        const result = Grep.search(
          event.content,
          (json: string) => {
            parentPort?.postMessage({
              type: "found",
              id: event.id,
              captures: {
                ...JSON.parse(json),
              },
            });
          },
          () => {
            parentPort?.postMessage({
              type: "finish",
              id: event.id,
            });
          }
        );
        if (result.$tag === 0) {
          parentPort?.postMessage({
            type: "error",
            id: event.id,
            error: result._0,
          });
        }
        break;
      }
      case "compile": {
        const result = Grep.compile(event.query);
        if (result.$tag === 0) {
          parentPort?.postMessage({
            type: "error",
            id: event.id,
            error: result._0,
          });
        } else {
          parentPort?.postMessage({
            type: "finish",
            id: event.id,
          });
        }
        break;
      }
    }
  } catch (error) {
    if ("id" in event) {
      parentPort?.postMessage({
        type: "error",
        id: event.id,
        error: error instanceof Error ? error.message : String(error),
      });
    } else {
      parentPort?.postMessage({
        type: "error",
        error: error instanceof Error ? error.message : String(error),
      });
    }
  }
});

parentPort?.postMessage({ type: "ready" });
