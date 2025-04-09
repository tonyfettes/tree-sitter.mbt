import shutil
from pathlib import Path
import json
import subprocess
import re


def remove_pre_build(path: Path):
    moon_pkg_json = json.loads(path.read_text())
    if "pre-build" in moon_pkg_json:
        moon_pkg_json.pop("pre-build")
        path.write_text(json.dumps(moon_pkg_json, indent=2))


def set_targets(path: Path, sources: list[Path]):
    moon_pkg_json = json.loads(path.read_text())
    moon_pkg_json["targets"] = {}
    for source in sources:
        moon_pkg_json["targets"][source.name] = ["native"]
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
    shutil.rmtree(publish_path / "src" / "tree-sitter")
    shutil.rmtree(publish_path / "src" / "grammar" / "moonbit")
    for test_path in (publish_path / "src").rglob("*_test.mbt"):
        test_path.unlink()
    sources = []
    for source in (publish_path / "src").glob("*.mbt"):
        sources.append(source)
    set_targets(publish_path / "src" / "moon.pkg.json", sources)
    (publish_path / "src" / ".gitignore").unlink()
    (publish_path / "src" / "tree-sitter.c").unlink()

    subprocess.run(
        ["moon", "check", "--target", "native"], cwd=publish_path, check=True
    )
    shutil.rmtree(publish_path / ".mooncakes")
    shutil.rmtree(publish_path / "target")

    subprocess.run(["moon", "publish"], cwd=publish_path)


if __name__ == "__main__":
    main()
