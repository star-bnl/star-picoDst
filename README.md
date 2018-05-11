[![Build Status](https://travis-ci.org/star-bnl/star-picoDst.svg?branch=master)](https://travis-ci.org/star-bnl/star-picoDst)


`star-picoDst` provides C++ libraries to support IO of compact data structures
used in analysis of physics data collected by the STAR experiment. The code is
organized in two libraries:

- `StPicoDstMaker` library is used to convert STAR data written in `muDst`
format to `picoDst`

- `StPicoEvent` library supplies the data structures to write to or read from
individual branches in ROOT trees. An effort is made to make this library
independent of any external code to allow standalone analysis in diverse user
environments.


# How to build and install the libraries

## Prerequisites

Checkout the code from the `star-picoDst`
[repository](https://github.com/star-bnl/star-picoDst), e.g.:

    git clone https://github.com/star-bnl/star-picoDst.git

Several external tools listed below along with their minimal version numbers are
required to build the STAR libraries:

- cmake 3.2 (GNU make is usually used by default on Linux and Mac OS)
- C++ compiler with C++11 support (e.g. g++ 4.8.5)
- ROOT 5.34.30, http://root.cern.ch
- `StPicoDstMaker` depends on the following libraries/modules from the STAR
software library [star-cvs](https://github.com/star-bnl/star-cvs):

  `StarClassLibrary, StarRoot, St_base, StChain, StEmcRawMaker, StEmcUtil,
   StEvent, StMuDSTMaker, StTriggerUtilities, tables`


## Build `picoDst` libraries

The `StPicoEvent` library does not depend on any external code from the STAR
software repository. After cloning `star-picoDst` one can build just that
library by running `make` with the appropriate target:

    cd star-picoDst/
    mkdir build && cd build
    cmake ../
    make StPicoEvent

It is also possible to compile all targets including the `StPicoDstMaker` but
you need to help cmake to find the STAR soft on your system by specifying the
`STAR_ROOT` parameter. Assuming the STAR soft is installed in
`/some/path/to/star/packages/` and contains `lib` and `include` subdirectories
with compiled libraries and .h header files respectively run `cmake` as:

    cmake -D STAR_ROOT=/some/path/to/star/packages/ ../

Alternatively, one can set environment variables `STAR` and `STAR_HOST_SYS` to
the appropriate values. The `STAR_ROOT` path in this case will be set internally
to `$STAR/.$STAR_HOST_SYS` just like on the interactive STAR RACF nodes.


# Continuous integration

We use travis-ci.org to build the `picoDst` libraries on every push to the
star-bnl/star-picoDst repository. See the `.travis.yml` directive file for the
current build instructions. The build matrix includes builds with `g++ 4.8` and
`clang++ 3.4` as well as ROOT v5.34.30 and v6.06.06.
