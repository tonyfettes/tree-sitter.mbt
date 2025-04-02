#!/usr/bin/env python3

from pathlib import Path
import shutil
import json


def main():
    src_path = Path("src")
    dst_path = src_path / "tree-sitter-lib"
    if dst_path.exists():
        shutil.rmtree(dst_path)
    shutil.copytree(src_path / "tree-sitter" / "lib" / "src", dst_path)
    shutil.copytree(
        src_path / "tree-sitter" / "lib" / "include" / "tree_sitter",
        dst_path / "tree_sitter",
    )
    lib_c_path = dst_path / "lib.c"
    lib_c_text = lib_c_path.read_text()
    stub_path = src_path / "tree-sitter.c"
    stub_text = stub_path.read_text()
    (dst_path / "lib.c").write_text(lib_c_text + stub_text)
    (dst_path / "moon.pkg.json").write_text(
        json.dumps(
            {"native-stub": ["lib.c"], "support-targets": ["native"]},
            indent=2,
        )
        + "\n"
    )


if __name__ == "__main__":
    main()
