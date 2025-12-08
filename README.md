# cftal

A c++-20 template based short vector library with faithfully rounded
vectorized elementary functions.

## Description

Cftal is a c++-20 template based short vector library with specializations
using intrinsic functions.
The library contains vectorized elementary and some special functions
(erf, erfc, tgamma, lgamma, j0, y0, j1 and y1) which are part of the standard
c++ math library for
- double (binary64),
- single (binary32),
- half (binary16) and
- bfloat16 (brain floating point)

precision arguments and results. The functions are probably faithfully rounded
for double, single and half precision and bfloat16.
The elementary functions for half precision and bfloat16 with one argument are
faithfully rounded (if mpfr rounds correctly).
Tests for a  subset of the numbers for single and double precision show
faithfully rounding compared to mpfr.
The implemented special functions are fully tabulated for half and bfloat16
precision.

Specializations for x86 processors with instructions set extensions up to AVX2
are implemented and tested.
The vector specializations for processors with AVX512 extensions are not 
well tested yet.
AArch64 code is not tested.

The library also contains vectors with variable sizes. These use the
short vectors of the library for their implementation.

## Getting Started

### Dependencies

- the reproduction of the used constants in the code requires
  sollya (https://www.sollya.org), libsollya-dev to build
  extensions to sollya and the maxima (https://maxima.sourceforge.io)
  computer algebra system
- the test code uses mpfr (https://www.mpfr.org) and requires the 
  debian package libmpfr-dev to compile the programs testing the 
  precision (and speed) of the vectorized elementary and special functions, 
  it requires also liblzma-dev for compression of pre-calculated results
  of libmpfr
- the documentation in the doc directory requires pdflatex
- cmake ist the used build system
- only linux as host and target system was tested and
- gcc or clang are the only compilers used to date

### Configuration

Create a build directory in the root directory of the project, change to it,
configure the build system and build:

1. `mkdir build`
2. `cd build`
3. `CC=clang-18 CXX=clang++-18 cmake -DCMAKE_BUILD_TYPE=release ..`
4. `make -j XX` 

You may also use gcc instead of clang:

3. `CC=gcc-15 CXX=g++-15 cmake -DCMAKE_BUILD_TYPE=release ..`

If you want to use vectors of double's for the calculation of some elementary
and special functions for single precision, use

`-DCFTAL_CONFIG_USE_VF64_FOR_VF32=1`

as additional cmake argument.

If you want to use vectors of float16's for the calculation of all elementary
functions for half precision, use

`-DCFTAL_CONFIG_USE_VF32_FOR_VF16=0`

as additional cmake argument. The default is to calculate half precision
functions using vectors of float's.

The compilation to a specific ABI is requested by configuring the library with

`cmake -DCMAKE_BUILD_TYPE=release -DCFTAL_GCC_ARCH=x86-64-v3 ..`

where `x64-64-v3` is one of the possible arguments to `gcc -march=`.
The variable `CFTAL_GCC_ARCH` defaults to `native`.

To enable the experimental AVX512 support configure the library with

`cmake -DCMAKE_BUILD_TYPE=release -DCFTAL_GCC_ARCH=x86-64-v4 -DCFTAL_CONFIG_ENABLE_AVX512=1 ..`

or use

`cmake -DCMAKE_BUILD_TYPE=release -DCFTAL_CONFIG_ENABLE_AVX512=1 ..`

if your processors are avx512 capable.


### Build and test

During the build a number of test programs are built in ./test and
a pdf is created in ./doc containing some documentation.

## License

This project is licensed under the LGPL v2.1 License.
