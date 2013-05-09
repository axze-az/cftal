/* Copyright (c) 2006 Free Software Foundation, Inc.

   This file is part of GCC.
   Contributed by Advanced Micro Devices, Inc., 2006.

   GCC is free software; you can redistribute it and/or modify it under
   the terms of the GNU General Public License as published by the Free
   Software Foundation; either version 2, or (at your option) any later
   version.

   In addition to the permissions in the GNU General Public License, the
   Free Software Foundation gives you unlimited permission to link the
   compiled version of this file into combinations with other programs,
   and to distribute those combinations without any restriction coming
   from the use of this file.  (The General Public License restrictions 
   do apply in other respects; for example, they cover modification of
   the file, and distribution when not linked into a combine
   executable.)

   GCC is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
   for more details.

   You should have received a copy of the GNU General Public License
   along with GCC; see the file COPYING.  If not, write to the Free
   Software Foundation, 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA.  */

#ifndef LIBM_UTIL_AMD_H_INCLUDED
#define LIBM_UTIL_AMD_H_INCLUDED 1


/* Compile-time verification that type long is the same size
   as type double (i.e. we are really on a 64-bit machine) */
void check_long_against_double_size(int machine_is_64_bit[(sizeof(long) == sizeof(double))?1:-1]); 


/* Definitions for double functions on 64 bit machines */
#define SIGNBIT_DP64      0x8000000000000000
#define EXPBITS_DP64      0x7ff0000000000000
#define MANTBITS_DP64     0x000fffffffffffff
#define ONEEXPBITS_DP64   0x3ff0000000000000
#define TWOEXPBITS_DP64   0x4000000000000000
#define HALFEXPBITS_DP64  0x3fe0000000000000
#define IMPBIT_DP64       0x0010000000000000
#define QNANBITPATT_DP64  0x7ff8000000000000
#define INDEFBITPATT_DP64 0xfff8000000000000
#define PINFBITPATT_DP64  0x7ff0000000000000
#define NINFBITPATT_DP64  0xfff0000000000000
#define EXPBIAS_DP64      1023
#define EXPSHIFTBITS_DP64 52
#define BIASEDEMIN_DP64   1
#define EMIN_DP64         -1022
#define BIASEDEMAX_DP64   2046
#define EMAX_DP64         1023
#define LAMBDA_DP64       1.0e300
#define MANTLENGTH_DP64   53
#define BASEDIGITS_DP64   15


/* These definitions, used by float functions,
   are for both 32 and 64 bit machines */
#define SIGNBIT_SP32      0x80000000
#define EXPBITS_SP32      0x7f800000
#define MANTBITS_SP32     0x007fffff
#define ONEEXPBITS_SP32   0x3f800000
#define TWOEXPBITS_SP32   0x40000000
#define HALFEXPBITS_SP32  0x3f000000
#define IMPBIT_SP32       0x00800000
#define QNANBITPATT_SP32  0x7fc00000
#define INDEFBITPATT_SP32 0xffc00000
#define PINFBITPATT_SP32  0x7f800000
#define NINFBITPATT_SP32  0xff800000
#define EXPBIAS_SP32      127
#define EXPSHIFTBITS_SP32 23
#define BIASEDEMIN_SP32   1
#define EMIN_SP32         -126
#define BIASEDEMAX_SP32   254
#define EMAX_SP32         127
#define LAMBDA_SP32       1.0e30
#define MANTLENGTH_SP32   24
#define BASEDIGITS_SP32   7

#define CLASS_SIGNALLING_NAN 1
#define CLASS_QUIET_NAN 2
#define CLASS_NEGATIVE_INFINITY 3
#define CLASS_NEGATIVE_NORMAL_NONZERO 4
#define CLASS_NEGATIVE_DENORMAL 5
#define CLASS_NEGATIVE_ZERO 6
#define CLASS_POSITIVE_ZERO 7
#define CLASS_POSITIVE_DENORMAL 8
#define CLASS_POSITIVE_NORMAL_NONZERO 9
#define CLASS_POSITIVE_INFINITY 10

#define OLD_BITS_SP32(x) (*((unsigned int *)&x))
#define OLD_BITS_DP64(x) (*((unsigned long *)&x))

/* Alternatives to the above functions which don't have
   problems when using high optimization levels on gcc */
#define GET_BITS_SP32(x, ux) \
  { \
    volatile union {float f; unsigned int i;} _bitsy; \
    _bitsy.f = (x); \
    ux = _bitsy.i; \
  }
#define PUT_BITS_SP32(ux, x) \
  { \
    volatile union {float f; unsigned int i;} _bitsy; \
    _bitsy.i = (ux); \
     x = _bitsy.f; \
  }

#define GET_BITS_DP64(x, ux) \
  { \
    volatile union {double d; unsigned long i;} _bitsy; \
    _bitsy.d = (x); \
    ux = _bitsy.i; \
  }
#define PUT_BITS_DP64(ux, x) \
  { \
    volatile union {double d; unsigned long i;} _bitsy; \
    _bitsy.i = (ux); \
    x = _bitsy.d; \
  }


/* Processor-dependent floating-point status flags */
#define AMD_F_INEXACT 0x00000020
#define AMD_F_UNDERFLOW 0x00000010
#define AMD_F_OVERFLOW 0x00000008
#define AMD_F_DIVBYZERO 0x00000004
#define AMD_F_INVALID 0x00000001

/* Processor-dependent floating-point precision-control flags */
#define AMD_F_EXTENDED 0x00000300
#define AMD_F_DOUBLE   0x00000200
#define AMD_F_SINGLE   0x00000000

/* Processor-dependent floating-point rounding-control flags */
#define AMD_F_RC_NEAREST 0x00000000
#define AMD_F_RC_DOWN    0x00002000
#define AMD_F_RC_UP      0x00004000
#define AMD_F_RC_ZERO    0x00006000

#endif /* LIBM_UTIL_AMD_H_INCLUDED */
