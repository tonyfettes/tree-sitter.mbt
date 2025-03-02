import sys
import os
import subprocess
from pathlib import Path


def main():
    MOON_HOME = os.environ.get("MOON_HOME")
    if MOON_HOME is None:
        print("MOON_HOME is not set")
        sys.exit(1)
    moon_home = Path(MOON_HOME)
    subprocess.run(
        [
            moon_home / "bin/internal/tcc",
            "-O3",
            "-Wall",
            "-Wextra",
            "-Wshadow",
            "-Wpedantic",
            "-Werror=incompatible-pointer-types",
            "-std=c11",
            "-fPIC",
            "-fvisibility=hidden",
            "-Isrc/tree-sitter/lib/src",
            "-Isrc/tree-sitter/lib/src/wasm",
            "-Isrc/tree-sitter/lib/include",
            "-Isrc/tinycc/include",
            f"-I{moon_home}/include",
            "-E",
            "-P",
            "src/tree-sitter.c",
            "-o",
            "src/tree-sitter-lib.c",
        ],
        check=True,
    )


if __name__ == "__main__":
    main()
