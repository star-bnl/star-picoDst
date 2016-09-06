[![Build Status](https://travis-ci.org/star-bnl/star-picoDst.svg?branch=master)](https://travis-ci.org/star-bnl/star-picoDst)


How to build and install the library
======================================

Prerequisites
-------------

- C++ compiler with C++11 support (e.g. g++ >= 4.8.2)
- ROOT (>= 5.34.30), http://root.cern.ch
- cmake (>= 2.8)
- The following STAR libraries/modules (likely incomplete list):

    StarClassLibrary
    StarRoot
    St_base
    StChain
    StEmcRawMaker
    StEmcUtil
    StEvent
    StMuDSTMaker
    StTriggerUtilities
    tables


Build with cmake
----------------

Checkout the code using the following command:

    $ git clone --recursive https://github.com/star-bnl/star-picoDst.git

Compile and build the libraries:

    $ cd star-picoDst/
    $ mkdir build && cd build
    $ cmake -D CMAKE_INSTALL_PREFIX=./ ../
    $ make install

Watch out for dependencies on other STAR libraries when compiling on a system
where the STAR soft is not installed.


Continuous itegration
=====================

We use travis-ci.org to build the `picoDst` libraries on every push to the
star-bnl/star-picoDst repository. See the `.travis.yml` directive file for the
current build instructions. The build matrix includes builds with `g++ 4.8` and
`clang++ 3.4` as well as ROOT v5.34.30 and v6.06.06.


Notes for STAR and RACF users
=============================

If you are building the libraries on the RHIC and ATLAS Computing Facility
(RACF) use `cmake28` command instead of `cmake` since the former corresponds to
a newer version of `cmake`.
