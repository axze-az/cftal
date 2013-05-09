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

#include "libm_util_amd.h"

/* Derived from
   static inline
   void __remainder_piby2f_inline(unsigned long ux, double *r, int *region);
   in libm_inlines_amd.h.  */

/* Given positive argument x, reduce it to the range [-pi/4,pi/4] using
   extra precision, and return the result in r.
   Return value "region" tells how many lots of pi/2 were subtracted
   from x to put it in the range [-pi/4,pi/4], mod 4.
   This method simulates multi-precision floating-point
   arithmetic and is accurate for all 1 <= x < infinity.  */
void
__remainder_piby2d2f(unsigned long ux, double *r, int *region)
{
#define bitsper 36
      unsigned long res[10];
      unsigned long u, carry, mask, mant, nextbits;
      int first, last, i, rexp, xexp, resexp, ltb, determ, bc;
      double dx;
      static const double
        piby2 = 1.57079632679489655800e+00; /* 0x3ff921fb54442d18 */
      static const unsigned long pibits[] =
      {
        0L,
        5215L, 13000023176L, 11362338026L, 67174558139L,
        34819822259L, 10612056195L, 67816420731L, 57840157550L,
        19558516809L, 50025467026L, 25186875954L, 18152700886L
      };

#ifdef DEBUGGING_PRINT
      printf("On entry, ux = %25.20e\n", ux);
#endif

      xexp = (int)(((ux & EXPBITS_DP64) >> EXPSHIFTBITS_DP64) - EXPBIAS_DP64);
      ux = ((ux & MANTBITS_DP64) | IMPBIT_DP64) >> 29;

      /* Now ux is the mantissa bit pattern of x as a long integer */
      mask = 1;
      mask = (mask << bitsper) - 1;

      /* Set first and last to the positions of the first
         and last chunks of 2/pi that we need */
      first = xexp / bitsper;
      resexp = xexp - first * bitsper;
      /* 120 is the theoretical maximum number of bits (actually
         115 for IEEE single precision) that we need to extract
         from the middle of 2/pi to compute the reduced argument
         accurately enough for our purposes */
      last = first + 120 / bitsper;

#ifdef DEBUGGING_PRINT
      printf("first = %d, last = %d\n", first, last);
#endif

      /* Do a long multiplication of the bits of 2/pi by the
         integer mantissa */
#if 0
      for (i = last; i >= first; i--)
        {
          u = pibits[i] * ux + carry;
          res[i - first] = u & mask;
          carry = u >> bitsper;
        }
      res[last - first + 1] = 0;
#else
      /* Unroll the loop. This is only correct because we know
         that bitsper is fixed as 36. */
      res[4] = 0;
      u = pibits[last] * ux;
      res[3] = u & mask;
      carry = u >> bitsper;
      u = pibits[last - 1] * ux + carry;
      res[2] = u & mask;
      carry = u >> bitsper;
      u = pibits[last - 2] * ux + carry;
      res[1] = u & mask;
      carry = u >> bitsper;
      u = pibits[first] * ux + carry;
      res[0] = u & mask;
#endif

      /* Reconstruct the result */
      ltb = (int)((((res[0] << bitsper) | res[1])
                   >> (bitsper - 1 - resexp)) & 7);

      /* determ says whether the fractional part is >= 0.5 */
      determ = ltb & 1;

#ifdef DEBUGGING_PRINT
      printf("ltb = %d (last two bits before binary point"
             " and first bit after)\n", ltb);
      printf("determ = %d (1 means need to negate because the fractional\n"
             "            part of x * 2/pi is greater than 0.5)\n", determ);
#endif

      i = 1;
      if (determ)
        {
          /* The mantissa is >= 0.5. We want to subtract it
             from 1.0 by negating all the bits */
          *region = ((ltb >> 1) + 1) & 3;
          mant = 1;
          mant = ~(res[1]) & ((mant << (bitsper - resexp)) - 1);
          while (mant < 0x0000000000010000)
            {
              i++;
              mant = (mant << bitsper) | (~(res[i]) & mask);
            }
          nextbits = (~(res[i+1]) & mask);
        }
      else
        {
          *region = (ltb >> 1);
          mant = 1;
          mant = res[1] & ((mant << (bitsper - resexp)) - 1);
          while (mant < 0x0000000000010000)
            {
              i++;
              mant = (mant << bitsper) | res[i];
            }
          nextbits = res[i+1];
        }

      /* Normalize the mantissa. The shift value 6 here, determined by
         trial and error, seems to give optimal speed. */
      bc = 0;
      while (mant < 0x0000400000000000)
        {
          bc += 6;
          mant <<= 6;
        }
      while (mant < 0x0010000000000000)
        {
          bc++;
          mant <<= 1;
        }
      mant |= nextbits >> (bitsper - bc);

      rexp = 52 + resexp - bc - i * bitsper;

#ifdef DEBUGGING_PRINT
      printf("Normalised mantissa = 0x%016lx\n", mant);
      printf("Exponent to be inserted on mantissa = rexp = %d\n", rexp);
#endif

      /* Put the result exponent rexp onto the mantissa pattern */
      u = ((unsigned long)rexp + EXPBIAS_DP64) << EXPSHIFTBITS_DP64;
      ux = (mant & MANTBITS_DP64) | u;
      if (determ)
        /* If we negated the mantissa we negate x too */
        ux |= SIGNBIT_DP64;
      PUT_BITS_DP64(ux, dx);

#ifdef DEBUGGING_PRINT
        printf("(x*2/pi) = %25.20e\n", dx);
#endif

      /* x is a double precision version of the fractional part of
         x * 2 / pi. Multiply x by pi/2 in double precision
         to get the reduced argument r. */
      *r = dx * piby2;

#ifdef DEBUGGING_PRINT
      printf(" r = frac(x*2/pi) * pi/2:\n");
      printf(" r = %25.20e\n", *r);
      printf("region = (number of pi/2 subtracted from x) mod 4 = %d\n",
             *region);
#endif
}
