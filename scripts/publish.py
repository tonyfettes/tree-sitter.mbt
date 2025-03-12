import shutil
from pathlib import Path
import json
import subprocess


def remove_pre_build(path: Path):
    moon_pkg_json = json.loads(path.read_text())
    if "pre-build" in moon_pkg_json:
        moon_pkg_json.pop("pre-build")
        path.write_text(json.dumps(moon_pkg_json, indent=2))


def main():
    publish_path = Path("publish")
    if publish_path.exists():
        shutil.rmtree("publish")

    publish_path.mkdir()
    shutil.copy("moon.mod.json", publish_path / "moon.mod.json")
    shutil.copy("README.md", publish_path / "README.md")
    shutil.copy("LICENSE", publish_path / "LICENSE")
    shutil.copytree("src", publish_path / "src")
    for path in (publish_path / "src").rglob("moon.pkg.json"):
        remove_pre_build(path)
    shutil.rmtree(publish_path / "src/tree-sitter")
    shutil.rmtree(publish_path / "src/tinycc")
    (publish_path / "src/sexp/lexer.mbtx").unlink()
    (publish_path / "src/sexp/parser.mbty").unlink()
    for test_path in (publish_path / "src").rglob("*_test.mbt"):
        test_path.unlink()
    (publish_path / "src/.gitignore").unlink()
    (publish_path / "src/tree-sitter.c").unlink()
    for mbti_path in (publish_path / "src").rglob("*.mbti"):
        mbti_path.unlink()

    subprocess.run(["moon", "publish"], cwd=publish_path)


if __name__ == "__main__":
    main()
