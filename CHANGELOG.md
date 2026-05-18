2026-05-18 (2.4.1)
==================

* Fix MSVC build: define `M_PI` fallback in `constants.hpp` so the D-infinity
  and terrain-attribute headers compile under MSVC (#13, #14)
* Add `windows-latest` to the GitHub Actions CI matrix to catch MSVC
  regressions before they reach the conda-forge feedstock (#14)


2026-05-11 (2.4.0)
==================

First release from the [`giswqs/richdem2`](https://github.com/giswqs/richdem2)
fork. The original `r-barnes/richdem` project is no longer actively maintained;
this fork picks up from the last upstream release (2.3.1) and continues
maintenance under the `richdem2` PyPI distribution.

Changes since upstream 2.3.1:

* Rename PyPI distribution from `richdem` to `richdem2` (#4)
* Modernize Python packaging (PEP 621 `pyproject.toml`) and add GitHub Actions
  CI (#2)
* Build platform wheels for PyPI releases via cibuildwheel (#6, #7)
* Fix MSVC build: replace `__builtin_clz` with `_BitScanReverse` (#8)
* Fix MSVC build: replace `__builtin_ffs` with `_BitScanForward` (#9)
* Fix GDAL memory leaks and `ProcessMetadata` loop bug (#10)
* Refresh `pyrichdem` README to acknowledge the fork; bump version past the
  upstream 2.3.1 to unblock conda-forge feedstock updates (#11)


2022-02-11 (2.3.1)
==================

Fix pyrichdem to import all cpp source files correctly
Clean up pyrichdem setup.py
Add .log files to .gitignore

2022-02-09 (2.3.0)
==================

Drop PyBind11 in favour of using pypi's version
Update to doctest v2.4.8

2018-07-13 (2.2.9)
==================

Changed `isnan()` logic in `grid_cell.hpp` to facilitate MSVC compilation.


2018-06-21 (2.2.8)
==================

Release for Zenodo DOI.


2018-06-03 (2.2.7)
==================

Fixes some compilation issues for Windows caused by MSVC not having M_PI by default.


2018-06-02 (2.2.6)
==================

Fixes some compilation issues for Windows.


2018-05-31 (2.2.5)
==================

Travis-CI deployment to Github works.


2018-05-31 (2.2.0)
==================

Includes D4 flow routing, depression filling, and depression breaching
Uses `chrono` for timing instead of `sys/time.h`
Includes Windows compatibility improvements
