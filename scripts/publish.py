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
        moon_pkg_json["targets"][source.with_suffix(".wasm-gc.mbt").name] = ["wasm-gc"]
    path.write_text(json.dumps(moon_pkg_json, indent=2))


def generate_wasm_gc_stub(item : str) -> str | None:
    if "pub extern \"c\" fn" in item:
        sig, _ = item.split("=")
        sig = sig.strip()
        if "->" not in sig:
            sig = sig + " -> Unit "
        return f"{signature}{{\n  abort(\"Not implemented\")\n}}"
    elif "pub fn" in item:
        signature, body = item.split("{")
        signature = signature.strip()
        return f"{signature}{{\n  abort(\"Not implemented\")\n}}"
    else:
        return None

class MoonBitFunction:
    signature : str
    return_type : str | None
    body : str

    def __init__(self, signature: str, return_type: str, body: str):
        self.signature = signature
        self.return_type = return_type
        self.body = body

    @staticmethod
    def parse(source : str):
        if "extern \"c\" fn" in source:
            signature, body = source.split("=")
            signature = signature.strip()
        signature, body = source.split("{")
        signature = signature.strip()
        return_type = signature.split("->")[1].strip()
        return MoonBitFunction(signature, return_type, body.strip())


ERROR_REGEX = re.compile(r"->.*!(?P<error_type>\w*)")


def generate_wasm_gc_stub(path: Path):
    source = path.read_text()
    stub_items = []
    for item in source.split("///|"):
        if not item.strip():
            continue
        item = item.strip()
        lines = item.splitlines()
        is_pub = False
        is_fn = False
        for line in lines:
            if line.startswith("pub"):
                is_pub = True
                line = line.removeprefix("pub").strip()
            if line.startswith("fn") or line.startswith("extern \"c\" fn"):
                is_fn = True
        if "pub extern \"c\" fn" in item:
            item = item.replace("extern \"c\"", "").strip()
            sig, _ = item.split("=")
            sig = sig.strip()
            if "->" not in sig:
                sig = sig + "-> Unit "
            stub_items.append(f"""{sig}{{
  abort("Not implemented")
}}""")
        elif "pub fn" in item:
            match = ERROR_REGEX.search(item)
            if match:
                sig = item.split("{")[0]
                stub_items.append(f"""{sig} {{
  let error : {match.group("error_type")} = abort("Not implemented")
  raise error
}}""")
            else:
                sig = item.split("{")[0]
                stub_items.append(f"""{sig} {{
  abort("Not implemented")
}}""")
        elif not is_fn:
            stub_items.append(item)
    stub_items = [
        "///|\n" + item
        for item in stub_items
    ]
    wasm_gc_path = path.with_suffix(".wasm-gc.mbt")
    wasm_gc_path.write_text("\n\n".join(stub_items))
    subprocess.run(["moonfmt", "-w", wasm_gc_path], check=True)

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
        generate_wasm_gc_stub(source)
    set_targets(publish_path / "src" / "moon.pkg.json", sources)
    (publish_path / "src" / ".gitignore").unlink()
    (publish_path / "src" / "tree-sitter.c").unlink()

    subprocess.run(["moon", "check", "--target", "wasm-gc"], cwd=publish_path, check=True)
    shutil.rmtree(publish_path / ".mooncakes")
    shutil.rmtree(publish_path / "target")

    subprocess.run(["moon", "publish"], cwd=publish_path)


if __name__ == "__main__":
    main()
