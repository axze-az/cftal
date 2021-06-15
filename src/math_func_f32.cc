//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <cftal/vec.h>
#include <cftal/vec_traits.h>
#include <cftal/math/elem_func.h>
#include <cftal/math/elem_func_core_f32.h>
#include <cftal/types.h>
#include <cftal/as.h>
#include <cstring>

#if __CFTAL_CFG_USE_VF64_FOR_VF32__ > 0
#define USE_FLOAT_KERNEL_REM_PIO2 0
#else
#define USE_FLOAT_KERNEL_REM_PIO2 1
#endif

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

namespace cftal {
    namespace math {
        namespace impl {

            inline
            float
            __scalbn(float x, int32_t ex);

            inline
            float
            __trunc(float x);

            inline
            float
            __floor(float x);

            // same routine as from sun but uses internal tables
            __attribute__((__visibility__("internal")))
            int
            __kernel_rem_pio2(float* x,
                              float* y,
                              int e0,
                              int nx,
                              int prec);

            // the init table for the chunks to use
            extern
            const int init_jk_f32[4];

            // bits of 1/(2*M_PI) in 9 bit chunks, i.e.
            // offset 0: bit [0, 9)*2^(1*9)
            // offset 1: bit [9, 18)*2^(2*9)
            // offset 2: bit [18, 27)*2^(3*9)
            extern
            const int16_t __attribute__((__visibility__("internal")))
                two_over_pi_b9[176];

            // M_PI/2 in 9 bit chunks
            extern
            const float __attribute__((__visibility__("internal")))
                pi_over_2_f32[8];
        }
    }
}

int cftal::math::impl::
__kernel_rem_pio2(float xr[2], float x)
{
    uint32_t ix=as<uint32_t>(x);
    uint32_t iax=ix & not_sign_f32_msk::v.u32();
    float ax=as<float>(iax);
    if (ax <= M_PI_4) {
        xr[0] = x;
        xr[1] = 0;
        return 0;
    }
    if (iax >= exp_f32_msk::v.u32()) {
        // inf or nan --> nan
        xr[0]=xr[1] = x+x;
        return 0;
    }
#if USE_FLOAT_KERNEL_REM_PIO2>0
    // z = scalbn(|x|, ilogb(x)-8)
    int32_t e0= (iax>>exp_shift_f32)-(bias_f32+8); // bias + 8
    int32_t iz= iax - (e0<<exp_shift_f32);
    float z=as<float>(iz);

    float xi[3];
    for (int i=0; i<2; ++i) {
        xi[i]= __trunc(z);
        z = (z - xi[i])*0x1p9f;
    }
    xi[2] = z;
    int32_t nx=3;
    while (xi[nx-1]==0.0)
        --nx;
    int n = __kernel_rem_pio2(xi, xr, e0, nx, 1);
    // x==+-0.0 was handled above
    if (x < 0) {
        xr[0]=-xr[0];
        xr[1]=-xr[1];
        n= -n;
    }
    return n;
#else
    double dx=ax;
    uint64_t lax=as<uint64_t>(dx);
    int64_t e0= (lax>>exp_shift_f64)-(bias_f64+23);
    int64_t lz= lax - (e0<<exp_shift_f64);
    double z=as<double>(lz);
    double xi=int32_t(z);
    double dxr;
    int n= __kernel_rem_pio2(&xi, &dxr, e0, 1, 0);
    if (x < 0.0f) {
        dxr = -dxr;
        n = -n;
    }
    xr[0] = float(dxr);
    xr[1] = float(dxr-double(xr[0]));
    return n;
#endif
}

inline
float
cftal::math::impl::__scalbn(float x, int32_t ex)
{
    using traits_t = cftal::math::func_traits<v1f32, v1s32>;
    using func_t = cftal::math::elem_func<float, traits_t>;
    v1s32 vex=ex;
    return func_t::__mul_two_pow(v1f32(x), vex)();
}

inline
float
cftal::math::impl::__trunc(float x)
{
#if defined (__SSE4_2__)
    const int rm=_MM_FROUND_TO_ZERO|_MM_FROUND_NO_EXC;
    return _mm_cvtss_f32(_mm_round_ps(_mm_set_ss(x), rm));
#else
    return std::trunc(x);
#endif
}

inline
float
cftal::math::impl::__floor(float x)
{
#if defined (__SSE4_2__)
    const int rm=_MM_FROUND_FLOOR|_MM_FROUND_NO_EXC;
    return _mm_cvtss_f32(_mm_round_ps(_mm_set_ss(x), rm));
#else
    return std::floor(x);
#endif
}

/*
 * __kernel_rem_pio2(x,y,e0,nx,prec,ipio2)
 * float x[],y[]; int e0,nx,prec; int ipio2[];
 *
 * __kernel_rem_pio2 return the last three digits of N with
 *              y = x - N*pi/2
 * so that |y| < pi/2.
 *
 * The method is to compute the integer (mod 8) and fraction parts of
 * (2/pi)*x without doing the full multiplication. In general we
 * skip the part of the product that are known to be a huge integer (
 * more accurately, = 0 mod 8 ). Thus the number of operations are
 * independent of the exponent of the input.
 *
 * (2/pi) is represented by an array of 9-bit integers in ipio2[].
 *
 * Input parameters:
 *      x[]     The input value (must be positive) is broken into nx
 *              pieces of 24-bit integers in double precision format.
 *              x[i] will be the i-th 24 bit of x. The scaled exponent
 *              of x[0] is given in input parameter e0 (i.e., x[0]*2^e0
 *              match x's up to 24 bits.
 *
 *              Example of breaking a double positive z into x[0]+x[1]+x[2]:
 *                      e0 = ilogb(z)-23
 *                      z  = scalbn(z,-e0)
 *              for i = 0,1,2
 *                      x[i] = floor(z)
 *                      z    = (z-x[i])*2**24
 *
 *
 *      y[]     ouput result in an array of double precision numbers.
 *              The dimension of y[] is:
 *                      24-bit  precision       1
 *                      53-bit  precision       2
 *                      64-bit  precision       2
 *                      113-bit precision       3
 *              The actual value is the sum of them. Thus for 113-bit
 *              precision, one may have to do something like:
 *
 *              long double t,w,r_head, r_tail;
 *              t = (long double)y[2] + (long double)y[1];
 *              w = (long double)y[0];
 *              r_head = t+w;
 *              r_tail = w - (r_head - t);
 *
 *      e0      The exponent of x[0]
 *
 *      nx      dimension of x[]
 *
 *      prec    an integer indicating the precision:
 *                      0       24  bits (single)
 *                      1       53  bits (double)
 *                      2       64  bits (extended)
 *                      3       113 bits (quad)
 *
 *      ipio2[]
 *              integer array, contains the (24*i)-th to (24*i+23)-th
 *              bit of 2/pi after binary point. The corresponding
 *              floating value is
 *
 *                      ipio2[i] * 2^(-24(i+1)).
 *
 * External function:
 *      double scalbn(), floor();
 *
 *
 * Here is the description of some local variables:
 *
 *      jk      jk+1 is the initial number of terms of ipio2[] needed
 *              in the computation. The recommended value is 2,3,4,
 *              6 for single, double, extended,and quad.
 *              The recommended value should be 3, 4, 4?, 6 for
 *              single, double, double extended and quad
 *
 *      jz      local integer variable indicating the number of
 *              terms of ipio2[] (two_over_pi) used.
 *
 *      jx      nx - 1
 *
 *      jv      index for pointing to the suitable ipio2[] for the
 *              computation. In general, we want
 *                      ( 2^e0*x[0] * ipio2[jv-1]*2^(-24jv) )/8
 *              is an integer. Thus
 *                      e0-3-24*jv >= 0 or (e0-3)/24 >= jv
 *              Hence jv = max(0,(e0-3)/24).
 *
 *      jp      jp+1 is the number of terms in PIo2[] (pi_over_2)
 *              needed, jp = jk.
 *
 *      q[]     double array with integral value, representing the
 *              24-bits chunk of the product of x and 2/pi.
 *
 *      q0      the corresponding exponent of q[0]. Note that the
 *              exponent for q[i] would be q0-24*i.
 *
 *      PIo2[]  double precision array, obtained by cutting pi/2
 *              into 24 bits chunks.
 *
 *      f[]     ipio2[] (two_over_pi) in floating point
 *
 *      iq[]    integer array by breaking up q[] in 24-bits chunk.
 *
 *      fq[]    final product of x*(2/pi) in fq[0],..,fq[jk]
 *
 *      ih      integer. If >0 it indicates q[] is >= 0.5, hence
 *              it also indicates the *sign* of the result.
 *
 */
int cftal::math::impl::
__kernel_rem_pio2(float* x,
                  float* y,
                  int e0,
                  int nx,
                  int prec)
{
    const float zero=0.0f;
    const float two9=0x1p9f;
    const float twon9=0x1p-9f;
    const float one=1.0f;

    int32_t jz,jx,jv,jp,jk,carry,n,iq[20],i,j,k,m,q0,ih;
    float z,fw,f[20],fq[20],q[20];

    std::memset(f, 0, sizeof(f));
    std::memset(fq, 0, sizeof(fq));
    std::memset(q, 0, sizeof(q));
    /* initialize jk*/
    jk = init_jk_f32[prec];
    jp = jk;

    /* determine jx,jv,q0, note that 3>q0 */
    jx =  nx-1;
    jv = (e0-3)/9; if(jv<0) jv=0;
    q0 =  e0-9*(jv+1);

    /* set up f[0] to f[jx+jk] where f[jx+jk] = ipio2[jv+jk] */
    j = jv-jx; m = jx+jk;
    for(i=0;i<=m;i++,j++) f[i] = (j<0)? zero : float(two_over_pi_b9[j]);

    /* compute q[0],q[1],...q[jk] */
    for (i=0;i<=jk;i++) {
        for(j=0,fw=0.0;j<=jx;j++)
            fw += x[j]*f[jx+i-j];
        q[i] = fw;
    }

    jz = jk;
recompute:
    /* distill q[] into iq[] reversingly */
    for(i=0,j=jz,z=q[jz];j>0;i++,j--) {
        fw    =  __trunc(twon9* z);
        iq[i] =  int32_t(z-two9*fw);
        z     =  q[j-1]+fw;
    }

    /* compute n */
    z  = __scalbn(z,q0);            /* actual value of z */
    z -= 8.0f*__floor(z*0.125f);          /* trim off integer >= 8 */
    n  = int32_t(z);
    // z -= (float)n;
    z -= __trunc(z);
    ih = 0;
    if(q0>0) {      /* need iq[jz-1] to determine n */
        i  = (iq[jz-1]>>(9-q0)); n += i;
        iq[jz-1] -= i<<(9-q0);
        ih = iq[jz-1]>>(8-q0);
    }
    else if(q0==0) ih = iq[jz-1]>>8;
    else if(z>=0.5) ih=2;

    if(ih>0) {      /* q > 0.5 */
        n += 1; carry = 0;
        for(i=0;i<jz ;i++) {        /* compute 1-q */
            j = iq[i];
            if(carry==0) {
                if(j!=0) {
                    carry = 1; iq[i] = 0x300- j;
                }
            } else  iq[i] = 0x1ff - j;
        }
        if(q0>0) {          /* rare case: chance is 1 in 12 */
            switch(q0) {
            case 1:
                iq[jz-1] &= 0xff; break;
            case 2:
                iq[jz-1] &= 0x7f; break;
            }
        }
        if(ih==2) {
            z = one - z;
            if(carry!=0) z -= __scalbn(one,q0);
        }
    }

    /* check if recomputation is needed */
    if(z==zero) {
        j = 0;
        for (i=jz-1;i>=jk;i--) j |= iq[i];
        if(j==0) { /* need recomputation */
            for(k=1;iq[jk-k]==0;k++);   /* k = no. of terms needed */

            for(i=jz+1;i<=jz+k;i++) {   /* add q[jz+1] to q[jz+k] */
                f[jx+i] = float(two_over_pi_b9[jv+i]);
                for(j=0,fw=0.0;j<=jx;j++) fw += x[j]*f[jx+i-j];
                q[i] = fw;
            }
            jz += k;
            goto recompute;
        }
    }

    /* chop off zero terms */
    if(z==0.0f) {
        jz -= 1; q0 -= 9;
        while(iq[jz]==0) { jz--; q0-=9;}
    } else { /* break z into 24-bit if necessary */
        z = __scalbn(z,-q0);
        if(z>=two9) {
            fw = __trunc(twon9*z);
            iq[jz] = int32_t(z-two9*fw);
            jz += 1; q0 += 9;
            iq[jz] = int32_t(fw);
        } else iq[jz] = int32_t(z);
    }

    /* convert integer "bit" chunk to floating-point value */
    fw = __scalbn(one,q0);
    for(i=jz;i>=0;i--) {
        q[i] = fw*float(iq[i]); fw*=twon9;
    }

    /* compute PIo2[0,...,jp]*q[jz,...,0] */
    for(i=jz;i>=0;i--) {
        for(fw=0.0f,k=0;k<=jp&&k<=jz-i;k++) fw += pi_over_2_f32[k]*q[i+k];
        fq[jz-i] = fw;
    }

    /* compress fq[] into y[] */
    switch(prec) {
    case 0:
        fw = 0.0f;
        for (i=jz;i>=0;i--) fw += fq[i];
        y[0] = (ih==0)? fw: -fw;
        break;
    case 1:
    case 2: {
#if __FLT_EVAL_METHOD__ != 0
        volatile
#endif
            float fv = 0.0f;
        for (i=jz;i>=0;i--) fv += fq[i];
        y[0] = (ih==0)? fv: -fv;
        fv = fq[0]-fv;
        for (i=1;i<=jz;i++) fv += fq[i];
        y[1] = (ih==0)? fv: -fv;
    }
        break;
    case 3:     /* painful */
        for (i=jz;i>0;i--) {
#if __FLT_EVAL_METHOD__ != 0
            volatile
#endif
                float fv = float(fq[i-1]+fq[i]);
            fq[i]  += fq[i-1]-fv;
            fq[i-1] = fv;
        }
        for (i=jz;i>1;i--) {
#if __FLT_EVAL_METHOD__ != 0
            volatile
#endif
                float fv = float(fq[i-1]+fq[i]);
            fq[i]  += fq[i-1]-fv;
            fq[i-1] = fv;
        }
        for (fw=0.0,i=jz;i>=2;i--) fw += fq[i];
        if(ih==0) {
            y[0] =  fq[0]; y[1] =  fq[1]; y[2] =  fw;
        } else {
            y[0] = -fq[0]; y[1] = -fq[1]; y[2] = -fw;
        }
    }
    return n&7;
}

/* initial value for jk */
const int
cftal::math::impl::init_jk_f32[] = {3, 6, 7, 9};

const cftal::int16_t cftal::math::impl::two_over_pi_b9[176]={
    0x145, 0x1e6, 0x01b, 0x0e4, 0x1c8, 0x105, 0x094, 0x1fc,
    0x04e, 0x15f, 0x08f, 0x153, 0x09b, 0x170, 0x06d, 0x162,
    0x12b, 0x064, 0x1e2, 0x039, 0x008, 0x07f, 0x128, 0x163,
    0x157, 0x17a, 0x1de, 0x056, 0x036, 0x1c9, 0x037, 0x03a,
    0x084, 0x137, 0x097, 0x000, 0x0c9, 0x04b, 0x175, 0x009,
    0x1a3, 0x048, 0x0e7, 0x1e1, 0x1bd, 0x0c7, 0x058, 0x129,
    0x14e, 0x0fb, 0x144, 0x023, 0x0be, 0x14b, 0x15d, 0x144,
    0x109, 0x1a6, 0x0e3, 0x102, 0x0d6, 0x117, 0x1bf, 0x041,
    0x073, 0x047, 0x0b1, 0x198, 0x06a, 0x0ce, 0x0fa, 0x09c,
    0x108, 0x17e, 0x05d, 0x1df, 0x125, 0x00e, 0x18f, 0x1f8,
    0x12f, 0x1ff, 0x0f0, 0x059, 0x101, 0x1fb, 0x197, 0x111,
    0x116, 0x168, 0x053, 0x0d1, 0x1ed, 0x14d, 0x13f, 0x0cf,
    0x04f, 0x12c, 0x04d, 0x174, 0x1e8, 0x18f, 0x1b3, 0x09e,
    0x0bf, 0x1a8, 0x16b, 0x152, 0x0f7, 0x0b1, 0x1f5, 0x1e5,
    0x1e2, 0x1ec, 0x1e8, 0x073, 0x13e, 0x1e2, 0x129, 0x092,
    0x1d4, 0x1af, 0x1da, 0x1fb, 0x023, 0x1e3, 0x0ae, 0x108,
    0x0ac, 0x00c, 0x182, 0x06f, 0x18f, 0x0da, 0x1d5, 0x1f0,
    0x19f, 0x0f0, 0x104, 0x1af, 0x086, 0x187, 0x0d4, 0x1e3,
    0x122, 0x185, 0x0f7, 0x061, 0x161, 0x019, 0x0cc, 0x185,
    0x0be, 0x052, 0x103, 0x084, 0x011, 0x17f, 0x1ec, 0x080,
    0x09a, 0x1cc, 0x139, 0x110, 0x0c0, 0x185, 0x0ab, 0x0ca,
    0x0e7, 0x0a3, 0x04b, 0x00e, 0x04f, 0x0f0, 0x046, 0x06b
};

const float cftal::math::impl::pi_over_2_f32[8]={
   1.570312500000e+00f, // 0x3fc90000
   4.835128784180e-04f, // 0x39fd8000
   3.138557076454e-07f, // 0x34a88000
   6.070877134334e-11f, // 0x2e858000
   6.217248937901e-14f, // 0x298c0000
   6.114900252818e-17f, // 0x248d0000
   8.332686618614e-20f, // 0x1fc4c000
   1.055947750712e-23f  // 0x194c4000
};
