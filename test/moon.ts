import * as Test from "node:test";
import Fsp from "node:fs/promises";
import Path from "node:path";
import ChildProcess from "node:child_process";

function build(
  target: "js" | "wasm" | "wasm-gc",
  profile: "debug" | "release"
) {
  const args = ["build", "--target", target];
  if (profile === "release") {
    args.push("--release");
  } else {
    args.push("--debug");
  }
  const process = ChildProcess.spawnSync("moon", args, {
    cwd: import.meta.dirname,
    stdio: "inherit",
  });
  if (process.status !== 0) {
    throw process.error;
  }
}

function getExtension(target: "js" | "wasm" | "wasm-gc") {
  switch (target) {
    case "js":
      return "js";
    case "wasm":
    case "wasm-gc":
      return "wasm";
  }
}

type LoadOptions =
  | {
      target: "js";
      profile: "debug" | "release";
      package?: string;
    }
  | {
      target: "wasm" | "wasm-gc";
      profile: "debug" | "release";
      imports: WebAssembly.Imports;
      package?: string;
    };

export async function load<T>(options: LoadOptions): Promise<T> {
  build(options.target, options.profile);
  const extension = getExtension(options.target);
  const packageName = options.package ? Path.basename(options.package) : "test";
  let artifactPathComponents: string[] = [];
  artifactPathComponents.push(
    import.meta.dirname,
    "target",
    options.target,
    options.profile,
    "build"
  );
  if (options.package) {
    artifactPathComponents.push(options.package);
  }
  artifactPathComponents.push(`${packageName}.${extension}`);
  const artifactPath = Path.join(...artifactPathComponents);
  if (options.target === "js") {
    return (await import(artifactPath)) as T;
  } else {
    const wasmBuffer = await Fsp.readFile(artifactPath);
    const { instance } = await WebAssembly.instantiate(
      wasmBuffer,
      options.imports
    );
    return instance.exports as T;
  }
}

export async function test<T>(
  packageName: string | undefined,
  imports: WebAssembly.Imports,
  fn: (exports: T) => void | Promise<void>
): Promise<(context: Test.TestContext) => Promise<void>> {
  return async (context: Test.TestContext) => {
    await context.test(packageName, async () => {
      const targets = ["js", "wasm", "wasm-gc"] as const;
      const profiles = ["debug", "release"] as const;
      const targetExports: T[] = [];
      for (const target of targets) {
        for (const profile of profiles) {
          targetExports.push(
            await load<T>({ target, profile, package: packageName, imports })
          );
        }
      }
      for (const exports of targetExports) {
        await fn(exports);
      }
    });
  };
}
