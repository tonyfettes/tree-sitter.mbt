import * as Test from "node:test";
import * as Moon from "./moon.ts";
import * as MoonBit from "./moonbit.ts";
import * as TS from "web-tree-sitter";
import * as Fs from "node:fs";
import * as Path from "node:path";

type MoonBitTestExports = {
  test_exp: (language: TS.Language) => MoonBit.Result<MoonBit.Unit, any>;
  test_top: (language: TS.Language) => MoonBit.Result<MoonBit.Unit, any>;
  test_fn_ambiguity: (
    language: TS.Language
  ) => MoonBit.Result<MoonBit.Unit, any>;
  test_concat: (language: TS.Language) => MoonBit.Result<MoonBit.Unit, any>;
  test_ty: (language: TS.Language) => MoonBit.Result<MoonBit.Unit, any>;
  test_id: (language: TS.Language) => MoonBit.Result<MoonBit.Unit, any>;
  test_quantifier: (language: TS.Language) => MoonBit.Result<MoonBit.Unit, any>;
  test_group: (language: TS.Language) => MoonBit.Result<MoonBit.Unit, any>;
  test_case: (language: TS.Language) => MoonBit.Result<MoonBit.Unit, any>;
};

const exports = await Moon.load<MoonBitTestExports>({
  target: "js",
  profile: "release",
});

const wasmBytes = await Fs.promises.readFile(
  Path.join(
    import.meta.dirname,
    ".mooncakes/tonyfettes/tree_sitter_moonbit/tree-sitter-moonbit.wasm"
  )
);

const language = await TS.Language.load(wasmBytes);

for (const [name, func] of Object.entries(exports)) {
  Test.test(name, async () => {
    func(language);
  });
}
