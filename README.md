# cftal

A c++-17 short vector library with faithfully rounded elementary functions.

## Description

Cftal is a c++-17 short vector library with specializations using
intrinsic functions. It contains a library with faithfully rounded
elementary functions and some special functions like erf, erfc,
tgamma, lgamma, j0, y0, j1 and y1 in single and double precision,

Specializations for processors with AVX2 extensions are
implemented. The specializations for processors with AVX512 extension
are not tested.

## Getting Started

### Dependencies

- the reproduction of the used constants in the code requires
  sollya (https://www.sollya.org) and libsollya-dev to build
  extensions to sollya
- the test code uses mpfr (https://www.mpfr.org) and requires
  libmpfr-dev to compile the test programs
- the documentation in the doc directory requires pdflatex
- only linux as build system was tested and
- gcc or clang are the only compilers are used to date

### Configuration

* create a build directory in the root directory of the project

mkdir build

cd build

CC=clang-16 CXX=clang++-16 cmake -DCMAKE_BUILD_TYPE=release ..

or

CC=gcc-13 CXX=g++-13 cmake -DCMAKE_BUILD_TYPE=release ..

### Build and test

During the build a number of test programs are build in ./test and
a pdf containing some documentation is created in ./doc.

## License

This project is licensed under the LGPL v2.1License.
