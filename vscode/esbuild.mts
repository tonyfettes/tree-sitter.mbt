import ESBuild from "esbuild";
import * as Fs from "node:fs";
import * as Path from "path";
import * as Module from "node:module";

const production = process.argv.includes("--production");
const watch = process.argv.includes("--watch");
const serve = process.argv.includes("--serve");

const esbuildProblemMatcherPlugin: ESBuild.Plugin = {
  name: "esbuild-problem-matcher",

  setup(build) {
    build.onStart(() => {
      console.log("[watch] build started");
    });
    build.onEnd((result) => {
      result.errors.forEach(({ text, location }) => {
        console.error(`✘ [ERROR] ${text}`);
        if (!location) {
          return;
        }
        console.error(`    ${location.file}:${location.line}:${location.column}:`);
      });
      console.log("[watch] build finished");
    });
  },
};

const webviewHtmlPlugin = ({
  entryPoint,
  outfile,
}: {
  entryPoint: string;
  outfile: string;
}): ESBuild.Plugin => {
  return {
    name: "webview-html-plugin",
    setup(build) {
      build.onEnd(async () => {
        const html = await Fs.promises.readFile(entryPoint, "utf-8");
        const output = html
          .replaceAll(/{{styleUri}}/g, "./index.css")
          .replaceAll(/{{scriptUri}}/g, "./index.js")
          .replaceAll(/{{nonce}}/g, "NONCE")
          .replaceAll(/{{cspSource}}/g, "CSP_SOURCE");
        await Fs.promises.writeFile(outfile, output);
      });
    },
  };
};

function findPackage(path: string): string | undefined {
  const packageJSON = Module.findPackageJSON(path, import.meta.url);
  if (!packageJSON) {
    return undefined;
  }
  return Path.dirname(packageJSON);
}

function findTreeSitterWasm(path: string, name?: string): string | undefined {
  const wasmName = name || path;
  const packageJSON = Module.findPackageJSON(path, import.meta.url);
  if (!packageJSON) {
    return undefined;
  }
  const packageDir = Path.dirname(packageJSON);
  const wasmPath = Path.join(packageDir, `${wasmName}.wasm`);
  if (Fs.existsSync(wasmPath)) {
    return wasmPath;
  }
  return undefined;
}

const treeSitterPlugin: ESBuild.Plugin = {
  name: "tree-sitter-plugin",
  setup(build) {
    build.onResolve({ filter: /tree-sitter-javascript/ }, (args): ESBuild.OnResolveResult => {
      const wasmPath = findTreeSitterWasm(args.path);
      if (!wasmPath) {
        throw new Error(`Could not find tree-sitter-wasm for ${args.path}`);
      }
      return {
        path: wasmPath,
      };
    });
    build.onResolve({ filter: /web-tree-sitter/ }, (args) => {
      const packageDir = findPackage(args.path);
      if (!packageDir) {
        throw new Error(`Could not find package for ${args.path}`);
      }
      return {
        path: Path.join(packageDir, "tree-sitter.cjs")
      }
    });
    build.onEnd(async () => {
      const wasmPath = findTreeSitterWasm("web-tree-sitter", "tree-sitter");
      if (!wasmPath) {
        throw new Error(`Could not find tree-sitter-wasm for web-tree-sitter`);
      }
      let outdir: string | undefined = undefined;
      if (build.initialOptions.outdir) {
        outdir = build.initialOptions.outdir;
      } else if (build.initialOptions.outfile) {
        outdir = Path.dirname(build.initialOptions.outfile);
      }
      if (!outdir) {
        throw new Error(`Could not find outdir for web-tree-sitter`);
      }
      await Fs.promises.copyFile(wasmPath, Path.join(outdir, "tree-sitter.wasm"));
    });
  },
};

async function webviewCtx(path: string): Promise<ESBuild.BuildContext> {
  return await ESBuild.context({
    entryPoints: [`src/${path}/index.ts`],
    bundle: true,
    format: "iife",
    minify: production,
    sourcemap: !production,
    sourcesContent: false,
    platform: "browser",
    outfile: `dist/${path}/index.js`,
    logLevel: "silent",
    plugins: [
      esbuildProblemMatcherPlugin,
      webviewHtmlPlugin({
        entryPoint: `src/${path}/index.html`,
        outfile: `dist/${path}/index.html`,
      }),
    ],
    loader: {
      ".ttf": "file",
    },
  });
}

async function main() {
  const extensionCtx = await ESBuild.context({
    entryPoints: ["src/extension.ts"],
    bundle: true,
    format: "cjs",
    minify: production,
    sourcemap: !production,
    sourcesContent: false,
    platform: "node",
    outfile: "dist/extension.js",
    external: ["vscode"],
    logLevel: "silent",
    plugins: [esbuildProblemMatcherPlugin, treeSitterPlugin],
    loader: {
      ".html": "text",
      ".wasm": "file",
    },
  });
  const sidebarCtx = await webviewCtx("sidebar");

  if (watch) {
    await Promise.all([extensionCtx.watch(), sidebarCtx.watch()]);
    if (serve) {
      const { hosts, port } = await sidebarCtx.serve({
        servedir: "dist/sidebar",
      });
      for (const host of hosts) {
        console.log(`Serving sidebar on http://${host}:${port}`);
      }
    }
  } else {
    await Promise.all([extensionCtx.rebuild(), sidebarCtx.rebuild()]);
    await Promise.all([extensionCtx.dispose(), sidebarCtx.dispose()]);
  }
}

main().catch((e) => {
  console.error(e);
  process.exit(1);
});
