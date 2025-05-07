import esbuild from "esbuild";
import * as fs from "fs";
import Handlebars from "handlebars";
import * as path from "path";

const production = process.argv.includes("--production");
const watch = process.argv.includes("--watch");
const serve = process.argv.includes("--serve");

const esbuildProblemMatcherPlugin: esbuild.Plugin = {
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

const indexHtmlPlugin = ({
  entryPoint,
  outfile,
}: {
  entryPoint: string;
  outfile: string;
}): esbuild.Plugin => {
  return {
    name: "index-html-plugin",
    setup(build) {
      build.onEnd(async () => {
        const html = await fs.promises.readFile(entryPoint, "utf-8");
        const template = Handlebars.compile(html);
        const output = template({
          styleUri: "./index.css",
          scriptUri: "./index.js",
          nonce: "NONCE",
          cspSource: "CSP_SOURCE",
        });
        await fs.promises.writeFile(outfile, output);
      });
    },
  };
};

async function webviewCtx(path: string): Promise<esbuild.BuildContext> {
  return await esbuild.context({
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
      indexHtmlPlugin({ entryPoint: `src/${path}/index.html`, outfile: `dist/${path}/index.html` }),
    ],
    loader: {
      ".ttf": "file",
    },
  });
}

async function main() {
  const extensionCtx = await esbuild.context({
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
    plugins: [esbuildProblemMatcherPlugin],
    loader: {
      ".html": "text",
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
