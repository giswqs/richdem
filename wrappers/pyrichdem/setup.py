import glob
import os
import re
import subprocess
from typing import Optional

from pybind11.setup_helpers import Pybind11Extension
from setuptools import setup
from setuptools.command.build_ext import build_ext as _build_ext

richdem_compile_time: Optional[str] = None
richdem_git_hash: Optional[str] = None

HERE = os.path.dirname(os.path.abspath(__file__))


def find_richdem_source_root() -> str:
    """Locate the richdem C++ source tree, relative to this setup.py.

    Prefer the parent repository (``../..``) when this wrapper is built from
    a full richdem2 checkout. The conda-forge Windows build extracts the
    GitHub source tarball, where the ``lib/richdem`` symlink does not survive,
    so the symlinked path can't be the only way in. Newer setuptools
    versions also reject the symlinked path because it resolves to an
    absolute path once dereferenced. Fall back to ``lib/richdem`` for sdist
    installs: the PyPI tarball ships real copies of the headers and sources
    under that directory and has no parent repo to walk up to.

    Returns:
        A path (relative to this setup.py) of a directory containing
        ``include/richdem`` and ``src`` subtrees.

    Raises:
        RuntimeError: If neither candidate location contains the expected
            ``include/richdem`` and ``src`` subdirectories.
    """
    candidates = [
        os.path.join("..", ".."),
        os.path.join("lib", "richdem"),
    ]
    for candidate in candidates:
        absolute = os.path.join(HERE, candidate)
        if os.path.isdir(
            os.path.join(absolute, "include", "richdem")
        ) and os.path.isdir(os.path.join(absolute, "src")):
            return candidate
    raise RuntimeError(
        "Could not locate the richdem C++ source tree. Looked in: "
        + ", ".join(candidates)
    )


# Compiler specific arguments
BUILD_ARGS = {
    "msvc": ["/std:c++17", "/O2"],
    "gcc": ["-std=c++17", "-g", "-fvisibility=hidden", "-O3", "-Wno-unknown-pragmas"],
    "unix": ["-std=c++17", "-g", "-fvisibility=hidden", "-O3", "-Wno-unknown-pragmas"],
}


class build_ext_compiler_check(_build_ext):
    """Custom build_ext that applies compiler-specific flags."""

    def build_extensions(self):
        compiler = self.compiler.compiler_type
        print(f"COMPILER {compiler}")
        args = BUILD_ARGS.get(compiler, BUILD_ARGS["unix"])
        for ext in self.extensions:
            ext.extra_compile_args = args
            print(f"COMPILER ARGUMENTS: {ext.extra_compile_args}")
        _build_ext.build_extensions(self)


# Capture git information at build time
if richdem_git_hash is None:
    try:
        shash = (
            subprocess.Popen(
                ["git log --pretty=format:'%h' -n 1"],
                shell=True,
                stderr=subprocess.STDOUT,
                stdout=subprocess.PIPE,
            )
            .stdout.readlines()[0]
            .decode("utf8")
            .strip()
        )
        sdate = (
            subprocess.Popen(
                ["git log -1 --pretty='%ci'"],
                shell=True,
                stderr=subprocess.STDOUT,
                stdout=subprocess.PIPE,
            )
            .stdout.readlines()[0]
            .decode("utf8")
            .strip()
        )
        if re.match(r"^[0-9a-z]+$", shash) and re.match(
            r"^[0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2}.*$", sdate
        ):
            richdem_compile_time = sdate
            richdem_git_hash = shash
    except Exception:
        print(
            "Warning! Could not find RichDEM version. "
            "Software will still work, but reproducibility will be compromised."
        )

if richdem_git_hash is None:
    richdem_compile_time = "Unknown"
    richdem_git_hash = "Unknown"

print(f"Using RichDEM hash={richdem_git_hash}, time={richdem_compile_time}")

richdem_root = find_richdem_source_root()

ext_modules = [
    Pybind11Extension(
        "_richdem",
        sorted(
            ["src/pywrapper.cpp"]
            + list(
                glob.glob(
                    os.path.join(richdem_root, "src", "**", "*.cpp"), recursive=True
                )
            )
        ),
        include_dirs=[os.path.join(richdem_root, "include")],
        define_macros=[
            ("DOCTEST_CONFIG_DISABLE", None),
            ("RICHDEM_COMPILE_TIME", f'"\\"{richdem_compile_time}\\""'),
            ("RICHDEM_GIT_HASH", f'"\\"{richdem_git_hash}\\""'),
            ("_USE_MATH_DEFINES", None),
        ],
    ),
]

setup(
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext_compiler_check},
)
