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
    (dst_path / "moon.pkg.json").write_text(
        json.dumps({"native-stub": ["lib.c"], "support-targets": ["native"]}, indent=2)
        + "\n"
    )


if __name__ == "__main__":
    main()
