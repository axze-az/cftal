# cftal

A c++-17 template based short vector library with faithfully rounded elementary
functions.

## Description

Cftal is a c++-17 template based short vector library with specializations
using intrinsic functions.
Part of the library are vectorized elementary and special functions
(erf, erfc, tgamma, lgamma, j0, y0, j1 and y1) in single and double precision.
The elementary functions are faithfully rounded.

Specializations for x86 processors with instructions set extensions up to AVX2
are implemented and tested.
The specializations for processors with AVX512 extensions are not tested yet.

## Getting Started

### Dependencies

- the reproduction of the used constants in the code requires
  sollya (https://www.sollya.org), libsollya-dev to build
  extensions to sollya and the maxima (https://maxima.sourceforge.io)
  computer algebra system
- the test code uses mpfr (https://www.mpfr.org) and requires
  libmpfr-dev to compile the programs testing the precision (and speed)
  of the vectorized elementary and special functions
- the documentation in the doc directory requires pdflatex
- only linux as build system was tested and
- gcc or clang are the only compilers are used to date

### Configuration

create a build directory in the root directory of the project, configure and
build

1. mkdir build
2. cd build
3. CC=clang-16 CXX=clang++-16 cmake -DCMAKE_BUILD_TYPE=release ..

You may also use gcc instead of clang:

3. CC=gcc-13 CXX=g++-13 cmake -DCMAKE_BUILD_TYPE=release ..

### Build and test

During the build a number of test programs are built in ./test and
a pdf is created in ./doc containing some documentation.

## License

This project is licensed under the LGPL v2.1License.
