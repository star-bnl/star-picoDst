[![Build Status](https://travis-ci.org/star-bnl/star-picoDst.svg?branch=master)](https://travis-ci.org/star-bnl/star-picoDst)


How to build and install the library
======================================

Prerequisites
-------------

- C++ compiler with C++11 support (e.g. g++ >= 4.8.2)
- ROOT (>= 5.34.30), http://root.cern.ch

Build with cmake
----------------

Checkout the code using the following command:

    git clone --recursive https://github.com/rnc-lbl/star-picoDst.git

Compile and build libraries:

    cd star-picoDst/
    mkdir build && cd build
    cmake -D CMAKE_INSTALL_PREFIX=./ ../
    make install
