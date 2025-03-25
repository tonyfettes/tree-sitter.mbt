import json
from pathlib import Path
import platform
import subprocess
import os


def macos_flags():
    llvm_prefix = subprocess.run(
        ["brew", "--prefix", "llvm@18"], check=True, text=True, capture_output=True
    ).stdout
    llvm_prefix = llvm_prefix.strip()
    clang_path = Path(llvm_prefix) / "bin" / "clang"
    return {"cc": str(clang_path), "cc-flags": "-g -fsanitize=address"}


def linux_flags():
    return {"cc": "gcc", "cc-flags": "-g -fsanitize=address"}


def windows_flags():
    return {"cc": "cl.exe", "cc-flags": "/fsanitize=address"}


def main():
    subprocess.run(["moon", "check", "--target", "native"], check=True)
    test_path = Path("test")
    flags = None
    if platform.system() == "Linux":
        flags = linux_flags()
    elif platform.system() == "Darwin":
        flags = macos_flags()
    elif platform.system() == "Windows":
        flags = windows_flags()
    if flags is None:
        raise Exception("Unsupported platform")
    moon_pkg_path = test_path / "moon.pkg.json"
    moon_pkg_text = moon_pkg_path.read_text()
    moon_pkg_json = json.loads(moon_pkg_text)
    if "link" not in moon_pkg_json:
        moon_pkg_json["link"] = {}
    moon_pkg_json["link"]["native"] = flags
    moon_pkg_path.write_text(json.dumps(moon_pkg_json, indent=2))
    print("==============================================")
    print("Running test with the following configuration:")
    print("----------------------------------------------")
    print(moon_pkg_path.read_text())
    print("----------------------------------------------")
    env = os.environ.copy()
    env["ASAN_OPTIONS"] = "detect_leaks=1"
    env["LSAN_OPTIONS"] = "suppressions=LSan.supp"
    try:
        subprocess.run(
            ["moon", "test", "--target", "native"], check=True, cwd=test_path, env=env
        )
    finally:
        moon_pkg_path.write_text(moon_pkg_text)


if __name__ == "__main__":
    main()
