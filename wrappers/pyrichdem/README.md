RichDEM2
========

[![PyPI](https://img.shields.io/pypi/v/richdem2.svg)](https://pypi.org/project/richdem2/)
[![CI](https://github.com/giswqs/richdem2/actions/workflows/ci.yml/badge.svg)](https://github.com/giswqs/richdem2/actions/workflows/ci.yml)

> **Note:** This is a maintained fork of the original
> [RichDEM](https://github.com/r-barnes/richdem) project by
> [Richard Barnes](https://github.com/r-barnes). The original package is no
> longer actively maintained. This fork updates the build system, modernizes
> Python packaging, and publishes to PyPI as
> [`richdem2`](https://pypi.org/project/richdem2/). All credit for the core
> algorithms and library design goes to the original author.

Original author: Richard Barnes (rbarnes@umn.edu)
Fork maintainer: [Qiusheng Wu](https://github.com/giswqs)

RichDEM is a set of digital elevation model (DEM) hydrologic analysis tools.
RichDEM uses parallel processing and state of the art algorithms to quickly
process even very large DEMs.

RichDEM offers a variety of flow metrics, such as D8 and D-infinity. It can
flood or breach depressions. It can calculate flow accumulation, slopes,
curvatures, and more.

Please cite RichDEM (see below).


Installation
============

From PyPI:

    pip install richdem2

Then use:

    >>> import richdem

The command:

    >>> help(richdem)

provides all the relevant documentation.


Design Philosophy
=================

The design of RichDEM is guided by these principles:

* **Algorithms will be well-tested.** Every algorithm is verified by a rigorous
  testing procedure.

* **Algorithms will be fast, without compromising safety and accuracy.** The
  algorithms used in RichDEM are state of the art, permitting analyses that
  would take days on other systems to be performed in hours, or even minutes.

* **Algorithms will be available as libraries, whenever possible.** RichDEM is
  designed as a set of header-only C++ libraries, making it easy to include in
  your projects and easy to incorporate into other programming languages.
  RichDEM also includes apps, which are simple wrappers around the algorithms,
  and a limited, but growing, set of algorithms which may have special
  requirements, like MPI, that make them unsuitable as libraries. These are
  available as programs.

* **Programs will have a command-line interface, not a GUI.** Command-line
  interfaces are simple to use and offer extreme flexibility for both users and
  programmers. They are available on every type of operating system. RichDEM
  does not officially support any GUI.

* **Algorithms and programs will be portable.** Linux, Mac, and Windows should
  all be supported.

* **The code will be beautiful.** RichDEM's code utilizes sensible variable
  names and reasonable abstractions to make it easy to understand, use, and
  design algorithms. The code contains extensive internal documentation which is
  DOxygen compatible.

* **Programs and algorithms will provide useful feedback.** Progress bars will
  appear if desired and the output will be optimized for machine parsing.

* **Analyses will be reproducible.** Every time you run a RichDEM command that
  command is logged and timestamped in the output data, along with the version
  of the program you created the output with. Additionally, a history of all
  previous manipulations to the data is kept. Use `rd_view_processing_history`
  to see this.


Citing It
=========

General usage of the library can be cited as:

    Barnes, Richard. 2016. RichDEM: Terrain Analysis Software.
    https://github.com/r-barnes/richdem

An example BibTeX entry is:

    @manual{RichDEM,
      title        = {RichDEM: Terrain Analysis Software},
      author       = {Richard Barnes},
      year         = {2016},
      url          = {https://github.com/r-barnes/richdem},
    }

Users are also encouraged to cite the particular algorithms used. Citations to
these will be printed whenever an app, program, or library function is run.
Although Richard Barnes wrote all of the code in this library, some of the
algorithms were discovered or invented by others, and they deserve credit for
their good work.


Parsable Output
===============

Every line of output from RichDEM begins with one of the following characters,
making it easy to parse with a machine.

 * **A**: Algorithm name

 * **a**: Analysis command: the command line used to run the program

 * **c**: Configuration information: program version, input files, and command
          line options, etc.

 * **C**: Citation for algorithm

 * **d**: Debugging info

 * **E**: Indicates an error condition

 * **i**: I/O: Amount of data loaded from disk

 * **m**: Miscellaneous counts

 * **n**: I/O: Amount of data transferred through a network

 * **p**: Progress information

 * **r**: Amount of RAM used

 * **t**: Timing information: how long stuff took

 * **W**: Indicates a warning


All output data has the form:

    <INDICATOR CHARACTER> <MESSAGE/MEASUREMENT NAME> [= <VALUE> [UNIT]]

The amount of whitespace may vary for aesthetic purposes.


Publications
============
The algorithms used in RichDEM have been published in the following articles.
Every algorithm/program will provide its relevant citation information when run.

* Barnes, R., 2017. Parallel non-divergent flow accumulation for trillion cell
  digital elevation models on desktops or clusters. Environmental Modelling &
  Software 92, 202-212.
  doi:[10.1016/j.envsoft.2017.02.022](https://doi.org/10.1016/j.envsoft.2017.02.022)

* Barnes, R., 2016. Parallel priority-flood depression filling for trillion cell
  digital elevation models on desktops or clusters. Computers & Geosciences 96,
  56-68.
  doi:[10.1016/j.cageo.2016.07.001](https://doi.org/10.1016/j.cageo.2016.07.001)

* Barnes, R., Lehman, C., Mulla, D., 2014a. An efficient assignment of drainage
  direction over flat surfaces in raster digital elevation models. Computers &
  Geosciences 62, 128-135.
  doi:[10.1016/j.cageo.2013.01.009](https://doi.org/10.1016/j.cageo.2013.01.009)

* Barnes, R., Lehman, C., Mulla, D., 2014b. Priority-flood: An optimal
  depression-filling and watershed-labeling algorithm for digital elevation
  models. Computers & Geosciences 62, 117-127.
  doi:[10.1016/j.cageo.2013.04.024](https://doi.org/10.1016/j.cageo.2013.04.024)

* Zhou, G., Sun, Z., Fu, S., 2016. An efficient variant of the Priority-Flood
  algorithm for filling depressions in raster digital elevation models.
  Computers & Geosciences 90, Part A, 87-96.
  doi:[10.1016/j.cageo.2016.02.021](https://doi.org/10.1016/j.cageo.2016.02.021)


Feedback
========

Users are encouraged to report any issues experienced with this fork via
[GitHub Issues](https://github.com/giswqs/richdem2/issues).
