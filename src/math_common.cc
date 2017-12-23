//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <cftal/math/elem_func.h>
#include <cftal/std_types.h>
#include <cftal/cast.h>
#include <cmath>

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

            // argument reduction routine for large floats
            int
            __kernel_rem_pio2(float xr[2], float x);

            // same routine as from sun but uses internal tables
            __attribute__((__visibility__("internal")))
            int
            __kernel_rem_pio2(double* x,
                              double* y,
                              int e0,
                              int nx,
                              int prec);

            // the init table for the chunks to used
            extern
            const int init_jk[4];

            // M_PI/2 in 24 bit chunks
            extern
            const double __attribute__((__visibility__("internal")))
                pi_over_2[8];

            // bits of 1/(2*M_PI) in 24 bit chunks, i.e.
            // offset 0: bit [0, 24)*2^(1+24)
            // offset 1: bit [24, 48)*2^(2+24)
            // offset 2: bit [48, 62)*2^(3+24)
            extern
            const int32_t __attribute__((__visibility__("internal")))
            two_over_pi[948];

            // bits of 1/(2*M_PI) in 24 bit chunks,
            // as in two_over_pi but as dbl
            extern
            const double __attribute__((__visibility__("internal")))
            two_over_pi_dbl[948];

        }
    }
}

int cftal::math::impl::
__kernel_rem_pio2(double xr[2], double x)
{
    double ax= std::fabs(x);
    if (ax <= M_PI_4) {
        xr[0] = x;
        xr[1] = 0;
        return 0;
    }
    uint64_t lax=as<uint64_t>(ax);
    if (lax >= 0x7ff0000000000000) {
        // inf or nan --> nan
        xr[0]=xr[1] = x+x;
        return 0;
    }
    // z = scalbn(|x|, ilogb(x)-23)
    int64_t e0= (lax>>52)-1046;
    int64_t lz= lax - (int64_t(e0)<<52);
    double z=as<double>(lz);
    double xi[3];
    for (int i=0; i<2; ++i) {
        xi[i]= int32_t(z);
        z = (z - xi[i])*0x1p24;
    }
    xi[2] = z;
    int32_t nx=3;
    while (xi[nx-1]==0.0)
        --nx;
    int n = __kernel_rem_pio2(xi, xr, e0, nx, 2);
    // x==+-0.0 was handled above
    if (x < 0) {
        xr[0]=-xr[0];
        xr[1]=-xr[1];
        n= -n;
    }
    return n;
}

int cftal::math::impl::
__kernel_rem_pio2(float xr[2], float x)
{
    float ax=std::fabs(x);
    if (ax <= M_PI_4) {
        xr[0] = x;
        xr[1] = 0;
        return 0;
    }
    return x;
}

/*
 * __kernel_rem_pio2(x,y,e0,nx,prec,ipio2)
 * double x[],y[]; int e0,nx,prec; int ipio2[];
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
 * (2/pi) is represented by an array of 24-bit integers in ipio2[].
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
 *
 *      jz      local integer variable indicating the number of
 *              terms of ipio2[] used.
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
 *      jp      jp+1 is the number of terms in PIo2[] needed, jp = jk.
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
 *      f[]     ipio2[] in floating point
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
__kernel_rem_pio2(double* x,
                  double* y,
                  int e0,
                  int nx,
                  int prec)
{
#if 0
    return __kernel_rem_pio2(x, y, e0, nx, prec, two_over_pi);
#else
    const double zero=0.0;
    const double two24=0x1p24;
    const double twon24=0x1p-24;
    const double one=1.0;

    int32_t jz,jx,jv,jp,jk,carry,n,iq[20],i,j,k,m,q0,ih;
    double z,fw,f[20],fq[20],q[20];

    /* initialize jk*/
    jk = init_jk[prec];
    jp = jk;

    /* determine jx,jv,q0, note that 3>q0 */
    jx =  nx-1;
    jv = (e0-3)/24; if(jv<0) jv=0;
    q0 =  e0-24*(jv+1);

    /* set up f[0] to f[jx+jk] where f[jx+jk] = ipio2[jv+jk] */
    j = jv-jx; m = jx+jk;
    for(i=0;i<=m;i++,j++) f[i] = (j<0)? zero : (double) two_over_pi[j];

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
        fw    =  (double)((int32_t)(twon24* z));
        iq[i] =  (int32_t)(z-two24*fw);
        z     =  q[j-1]+fw;
    }

    /* compute n */
    z  = std::scalbn(z,q0);            /* actual value of z */
    z -= 8.0*std::floor(z*0.125);              /* trim off integer >= 8 */
    n  = (int32_t) z;
    z -= (double)n;
    ih = 0;
    if(q0>0) {      /* need iq[jz-1] to determine n */
        i  = (iq[jz-1]>>(24-q0)); n += i;
        iq[jz-1] -= i<<(24-q0);
        ih = iq[jz-1]>>(23-q0);
    }
    else if(q0==0) ih = iq[jz-1]>>23;
    else if(z>=0.5) ih=2;

    if(ih>0) {      /* q > 0.5 */
        n += 1; carry = 0;
        for(i=0;i<jz ;i++) {        /* compute 1-q */
            j = iq[i];
            if(carry==0) {
                if(j!=0) {
                    carry = 1; iq[i] = 0x1000000- j;
                }
            } else  iq[i] = 0xffffff - j;
        }
        if(q0>0) {          /* rare case: chance is 1 in 12 */
            switch(q0) {
            case 1:
                iq[jz-1] &= 0x7fffff; break;
            case 2:
                iq[jz-1] &= 0x3fffff; break;
            }
        }
        if(ih==2) {
            z = one - z;
            if(carry!=0) z -= std::scalbn(one,q0);
        }
    }

    /* check if recomputation is needed */
    if(z==zero) {
        j = 0;
        for (i=jz-1;i>=jk;i--) j |= iq[i];
        if(j==0) { /* need recomputation */
            for(k=1;iq[jk-k]==0;k++);   /* k = no. of terms needed */

            for(i=jz+1;i<=jz+k;i++) {   /* add q[jz+1] to q[jz+k] */
                f[jx+i] = (double) two_over_pi[jv+i];
                for(j=0,fw=0.0;j<=jx;j++) fw += x[j]*f[jx+i-j];
                q[i] = fw;
            }
            jz += k;
            goto recompute;
        }
    }

    /* chop off zero terms */
    if(z==0.0) {
        jz -= 1; q0 -= 24;
        while(iq[jz]==0) { jz--; q0-=24;}
    } else { /* break z into 24-bit if necessary */
        z = std::scalbn(z,-q0);
        if(z>=two24) {
            fw = (double)((int32_t)(twon24*z));
            iq[jz] = (int32_t)(z-two24*fw);
            jz += 1; q0 += 24;
            iq[jz] = (int32_t) fw;
        } else iq[jz] = (int32_t) z ;
    }

    /* convert integer "bit" chunk to floating-point value */
    fw = std::scalbn(one,q0);
    for(i=jz;i>=0;i--) {
        q[i] = fw*(double)iq[i]; fw*=twon24;
    }

    /* compute PIo2[0,...,jp]*q[jz,...,0] */
    for(i=jz;i>=0;i--) {
        for(fw=0.0,k=0;k<=jp&&k<=jz-i;k++) fw += pi_over_2[k]*q[i+k];
        fq[jz-i] = fw;
    }

    /* compress fq[] into y[] */
    switch(prec) {
    case 0:
        fw = 0.0;
        for (i=jz;i>=0;i--) fw += fq[i];
        y[0] = (ih==0)? fw: -fw;
        break;
    case 1:
    case 2: {
#if __FLT_EVAL_METHOD__ != 0
        volatile
#endif
            double fv = 0.0;
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
                double fv = (double)(fq[i-1]+fq[i]);
            fq[i]  += fq[i-1]-fv;
            fq[i-1] = fv;
        }
        for (i=jz;i>1;i--) {
#if __FLT_EVAL_METHOD__ != 0
            volatile
#endif
                double fv = (double)(fq[i-1]+fq[i]);
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
#endif
}

/* initial value for jk */
const int
cftal::math::impl::init_jk[] = {2,3,4,6};

const cftal::int32_t cftal::math::impl::two_over_pi[948]={
    0xa2f983, 0x6e4e44, 0x1529fc, 0x2757d1, 0xf534dd, 0xc0db62,
    0x95993c, 0x439041, 0xfe5163, 0xabdebb, 0xc561b7, 0x246e3a,
    0x424dd2, 0xe00649, 0x2eea09, 0xd1921c, 0xfe1deb, 0x1cb129,
    0xa73ee8, 0x8235f5, 0x2ebb44, 0x84e99c, 0x7026b4, 0x5f7e41,
    0x3991d6, 0x398353, 0x39f49c, 0x845f8b, 0xbdf928, 0x3b1ff8,
    0x97ffde, 0x05980f, 0xef2f11, 0x8b5a0a, 0x6d1f6d, 0x367ecf,
    0x27cb09, 0xb74f46, 0x3f669e, 0x5fea2d, 0x7527ba, 0xc7ebe5,
    0xf17b3d, 0x0739f7, 0x8a5292, 0xea6bfb, 0x5fb11f, 0x8d5d08,
    0x560330, 0x46fc7b, 0x6babf0, 0xcfbc20, 0x9af436, 0x1da9e3,
    0x91615e, 0xe61b08, 0x659985, 0x5f14a0, 0x68408d, 0xffd880,
    0x4d7327, 0x310606, 0x1556ca, 0x73a8c9, 0x60e27b, 0xc08c6b,
    0x47c419, 0xc367cd, 0xdce809, 0x2a8359, 0xc4768b, 0x961ca6,
    0xddaf44, 0xd15719, 0x053ea5, 0xff0705, 0x3f7e33, 0xe832c2,
    0xde4f98, 0x327dbb, 0xc33d26, 0xef6b1e, 0x5ef89f, 0x3a1f35,
    0xcaf27f, 0x1d87f1, 0x21907c, 0x7c246a, 0xfa6ed5, 0x772d30,
    0x433b15, 0xc614b5, 0x9d19c3, 0xc2c4ad, 0x414d2c, 0x5d000c,
    0x467d86, 0x2d71e3, 0x9ac69b, 0x006233, 0x7cd2b4, 0x97a7b4,
    0xd55537, 0xf63ed7, 0x1810a3, 0xfc764d, 0x2a9d64, 0xabd770,
    0xf87c63, 0x57b07a, 0xe71517, 0x5649c0, 0xd9d63b, 0x3884a7,
    0xcb2324, 0x778ad6, 0x23545a, 0xb91f00, 0x1b0af1, 0xdfce19,
    0xff319f, 0x6a1e66, 0x615799, 0x47fbac, 0xd87f7e, 0xb76522,
    0x89e832, 0x60bfe6, 0xcdc4ef, 0x09366c, 0xd43f5d, 0xd7de16,
    0xde3b58, 0x929bde, 0x2822d2, 0xe88628, 0x4d58e2, 0x32cac6,
    0x16e308, 0xcb7de0, 0x50c017, 0xa71df3, 0x5be018, 0x34132e,
    0x621283, 0x014883, 0x5b8ef5, 0x7fb0ad, 0xf2e91e, 0x434a48,
    0xd36710, 0xd8ddaa, 0x425fae, 0xce616a, 0xa4280a, 0xb499d3,
    0xf2a606, 0x7f775c, 0x83c2a3, 0x883c61, 0x78738a, 0x5a8caf,
    0xbdd76f, 0x63a62d, 0xcbbff4, 0xef818d, 0x67c126, 0x45ca55,
    0x36d9ca, 0xd2a828, 0x8d61c2, 0x77c912, 0x142604, 0x9b4612,
    0xc459c4, 0x44c5c8, 0x91b24d, 0xf31700, 0xad43d4, 0xe54929,
    0x10d5fd, 0xfcbe00, 0xcc941e, 0xeece70, 0xf53e13, 0x80f1ec,
    0xc3e7b3, 0x28f8c7, 0x940593, 0x3e71c1, 0xb3092e, 0xf3450b,
    0x9c1288, 0x7b20ab, 0x9fb52e, 0xc29247, 0x2f327b, 0x6d550c,
    0x90a772, 0x1fe76b, 0x96cb31, 0x4a1679, 0xe27941, 0x89dff4,
    0x9794e8, 0x84e6e2, 0x973199, 0x6bed88, 0x365f5f, 0x0efdbb,
    0xb49a48, 0x6ca467, 0x427271, 0x325d8d, 0xb8159f, 0x09e5bc,
    0x25318d, 0x3974f7, 0x1c0530, 0x010c0d, 0x68084b, 0x58ee2c,
    0x90aa47, 0x02e774, 0x24d6bd, 0xa67df7, 0x72486e, 0xef169f,
    0xa6948e, 0xf691b4, 0x5153d1, 0xf20acf, 0x339820, 0x7e4bf5,
    0x6863b2, 0x5f3edd, 0x035d40, 0x7f8985, 0x295255, 0xc06437,
    0x10d86d, 0x324832, 0x754c5b, 0xd4714e, 0x6e5445, 0xc1090b,
    0x69f52a, 0xd56614, 0x9d0727, 0x50045d, 0xdb3bb4, 0xc576ea,
    0x17f987, 0x7d6b49, 0xba271d, 0x296996, 0xacccc6, 0x5414ad,
    0x6ae290, 0x89d988, 0x50722c, 0xbea404, 0x940777, 0x7030f3,
    0x27fc00, 0xa871ea, 0x49c266, 0x3de064, 0x83dd97, 0x973fa3,
    0xfd9443, 0x8c860d, 0xde4131, 0x9d3992, 0x8c70dd, 0xe7b717,
    0x3bdf08, 0x2b3715, 0xa0805c, 0x93805a, 0x921110, 0xd8e80f,
    0xaf806c, 0x4bffdb, 0x0f9038, 0x761859, 0x15a562, 0xbbcb61,
    0xb989c7, 0xbd4010, 0x04f2d2, 0x277549, 0xf6b6eb, 0xbb22db,
    0xaa140a, 0x2f2689, 0x768364, 0x333b09, 0x1a940e, 0xaa3a51,
    0xc2a31d, 0xaeedaf, 0x12265c, 0x4dc26d, 0x9c7a2d, 0x9756c0,
    0x833f03, 0xf6f009, 0x8c402b, 0x99316d, 0x07b439, 0x15200c,
    0x5bc3d8, 0xc492f5, 0x4badc6, 0xa5ca4e, 0xcd37a7, 0x36a9e6,
    0x9492ab, 0x6842dd, 0xde6319, 0xef8c76, 0x528b68, 0x37dbfc,
    0xaba1ae, 0x3115df, 0xa1ae00, 0xdafb0c, 0x664d64, 0xb705ed,
    0x306529, 0xbf5657, 0x3aff47, 0xb9f96a, 0xf3be75, 0xdf9328,
    0x3080ab, 0xf68c66, 0x15cb04, 0x0622fa, 0x1de4d9, 0xa4b33d,
    0x8f1b57, 0x09cd36, 0xe9424e, 0xa4be13, 0xb52333, 0x1aaaf0,
    0xa8654f, 0xa5c1d2, 0x0f3f0b, 0xcd785b, 0x76f923, 0x048b7b,
    0x721789, 0x53a6c6, 0xe26e6f, 0x00ebef, 0x584a9b, 0xb7dac4,
    0xba66aa, 0xcfcf76, 0x1d02d1, 0x2df1b1, 0xc1998c, 0x77adc3,
    0xda4886, 0xa05df7, 0xf480c6, 0x2ff0ac, 0x9aecdd, 0xbc5c3f,
    0x6dded0, 0x1fc790, 0xb6db2a, 0x3a25a3, 0x9aaf00, 0x9353ad,
    0x0457b6, 0xb42d29, 0x7e804b, 0xa707da, 0x0eaa76, 0xa1597b,
    0x2a1216, 0x2db7dc, 0xfde5fa, 0xfedb89, 0xfdbe89, 0x6c76e4,
    0xfca906, 0x70803e, 0x156e85, 0xff87fd, 0x073e28, 0x336761,
    0x86182a, 0xeabd4d, 0xafe7b3, 0x6e6d8f, 0x396795, 0x5bbf31,
    0x48d784, 0x16df30, 0x432dc7, 0x356125, 0xce70c9, 0xb8cb30,
    0xfd6cbf, 0xa200a4, 0xe46c05, 0xa0dd5a, 0x476f21, 0xd21262,
    0x845cb9, 0x496170, 0xe0566b, 0x015299, 0x375550, 0xb7d51e,
    0xc4f133, 0x5f6e13, 0xe4305d, 0xa92e85, 0xc3b21d, 0x3632a1,
    0xa4b708, 0xd4b1ea, 0x21f716, 0xe4698f, 0x77ff27, 0x80030c,
    0x2d408d, 0xa0cd4f, 0x99a520, 0xd3a2b3, 0x0a5d2f, 0x42f9b4,
    0xcbda11, 0xd0be7d, 0xc1db9b, 0xbd17ab, 0x81a2ca, 0x5c6a08,
    0x17552e, 0x550027, 0xf0147f, 0x8607e1, 0x640b14, 0x8d4196,
    0xdebe87, 0x2afdda, 0xb6256b, 0x34897b, 0xfef305, 0x9ebfb9,
    0x4f6a68, 0xa82a4a, 0x5ac44f, 0xbcf82d, 0x985ad7, 0x95c7f4,
    0x8d4d0d, 0xa63a20, 0x5f57a4, 0xb13f14, 0x953880, 0x0120cc,
    0x86dd71, 0xb6dec9, 0xf560bf, 0x11654d, 0x6b0701, 0xacb08c,
    0xd0c0b2, 0x485551, 0x0efb1e, 0xc37295, 0x3b06a3, 0x3540c0,
    0x7bdc06, 0xcc45e0, 0xfa294e, 0xc8cad6, 0x41f3e8, 0xde647c,
    0xd8649b, 0x31bed9, 0xc397a4, 0xd45877, 0xc5e369, 0x13daf0,
    0x3c3aba, 0x461846, 0x5f7555, 0xf5bdd2, 0xc6926e, 0x5d2eac,
    0xed440e, 0x423e1c, 0x87c461, 0xe9fd29, 0xf3d6e7, 0xca7c22,
    0x35916f, 0xc5e008, 0x8dd7ff, 0xe26a6e, 0xc6fdb0, 0xc10893,
    0x745d7c, 0xb2ad6b, 0x9d6ecd, 0x7b723e, 0x6a11c6, 0xa9cff7,
    0xdf7329, 0xbac9b5, 0x5100b7, 0x0db2e2, 0x24ba74, 0x607de5,
    0x8ad874, 0x2c150d, 0x0c1881, 0x94667e, 0x162901, 0x767a9f,
    0xbefdfd, 0xef4556, 0x367ed9, 0x13d9ec, 0xb9ba8b, 0xfc97c4,
    0x27a831, 0xc36ef1, 0x36c594, 0x56a8d8, 0xb5a8b4, 0x0ecccf,
    0x2d8912, 0x34576f, 0x89562c, 0xe3ce99, 0xb920d6, 0xaa5e6b,
    0x9c2a3e, 0xcc5f11, 0x4a0bfd, 0xfbf4e1, 0x6d3b8e, 0x2c86e2,
    0x84d4e9, 0xa9b4fc, 0xd1eeef, 0xc9352e, 0x61392f, 0x442138,
    0xc8d91b, 0x0afc81, 0x6a4afb, 0xd81c2f, 0x84b453, 0x8c994e,
    0xcc2254, 0xdc552a, 0xd6c6c0, 0x96190b, 0xb8701a, 0x649569,
    0x605a26, 0xee523f, 0x0f117f, 0x11b5f4, 0xf5cbfc, 0x2dbc34,
    0xeebc34, 0xcc5de8, 0x605edd, 0x9b8e67, 0xef3392, 0xb817c9,
    0x9b5861, 0xbc57e1, 0xc68351, 0x103ed8, 0x4871dd, 0xdd1c2d,
    0xa118af, 0x462c21, 0xd7f359, 0x987ad9, 0xc0549e, 0xfa864f,
    0xfc0656, 0xae79e5, 0x362289, 0x22ad38, 0xdc9367, 0xaae855,
    0x382682, 0x9be7ca, 0xa40d51, 0xb13399, 0x0ed7a9, 0x480569,
    0xf0b265, 0xa7887f, 0x974c88, 0x36d1f9, 0xb39221, 0x4a827b,
    0x21cf98, 0xdc9f40, 0x5547dc, 0x3a74e1, 0x42eb67, 0xdf9dfe,
    0x5fd45e, 0xa4677b, 0x7aacba, 0xa2f655, 0x23882b, 0x55ba41,
    0x086e59, 0x862a21, 0x834739, 0xe6e389, 0xd49ee5, 0x40fb49,
    0xe956ff, 0xca0f1c, 0x8a59c5, 0x2bfa94, 0xc5c1d3, 0xcfc50f,
    0xae5adb, 0x86c547, 0x624385, 0x3b8621, 0x94792c, 0x876110,
    0x7b4c2a, 0x1a2c80, 0x12bf43, 0x902688, 0x893c78, 0xe4c4a8,
    0x7bdbe5, 0xc23ac4, 0xeaf426, 0x8a67f7, 0xbf920d, 0x2ba365,
    0xb1933d, 0x0b7cbd, 0xdc51a4, 0x63dd27, 0xdde169, 0x19949a,
    0x9529a8, 0x28ce68, 0xb4ed09, 0x209f44, 0xca984e, 0x638270,
    0x237c7e, 0x32b90f, 0x8ef5a7, 0xe75614, 0x08f121, 0x2a9db5,
    0x4d7e6f, 0x5119a5, 0xabf9b5, 0xd6df82, 0x61dd96, 0x023616,
    0x9f3ac4, 0xa1a283, 0x6ded72, 0x7a8d39, 0xa9b882, 0x5c326b,
    0x5b2746, 0xed3400, 0x7700d2, 0x55f4fc, 0x4d5901, 0x8071e0,
    0xe13f89, 0xb295f3, 0x64a8f1, 0xaea74b, 0x38fc4c, 0xeab2bb,
    0x47270b, 0xabc3a7, 0x34ba60, 0x52dd34, 0xf8563a, 0xeb7e8a,
    0x31bb36, 0x5895b7, 0x47f7a9, 0x94c3aa, 0xd39225, 0x1e7f3e,
    0xd8974e, 0xbba94f, 0xd8ae01, 0xe661b4, 0x393d8e, 0xa523aa,
    0x33068e, 0x1633b5, 0x3bb188, 0x1d3a9d, 0x4013d0, 0xcc1be5,
    0xf862e7, 0x3bf28f, 0x39b5bf, 0x0bc235, 0x22747e, 0xa247c0,
    0xd52d1f, 0x19add3, 0x9094df, 0x9311d0, 0xb42b25, 0x496db2,
    0xe264b2, 0x5ef135, 0x3bc6a4, 0x1a4ad0, 0xaac92e, 0x64e886,
    0x573091, 0x982cfb, 0x311b1a, 0x08728b, 0xbdcee1, 0x60e142,
    0xeb641d, 0xd0bba3, 0xe559d4, 0x597b8c, 0x2a4483, 0xf332ba,
    0xf84867, 0x2c8d1b, 0x2fa9b0, 0x50f3dd, 0xf9f573, 0xdb61b4,
    0xfe233e, 0x6c41a6, 0xeea318, 0x775a26, 0xbc5e5c, 0xcea708,
    0x94dc57, 0xe20196, 0xf1e839, 0xbe4851, 0x5d2d2f, 0x4e9555,
    0xd96ec2, 0xe7d755, 0x6304e0, 0xc02e0e, 0xfc40a0, 0xbbf9b3,
    0x7125a7, 0x222dfb, 0xf619d8, 0x838c1c, 0x6619e6, 0xb20d55,
    0xbb5137, 0x79e809, 0xaf9149, 0x0d73de, 0x0b0da5, 0xce7f58,
    0xac1934, 0x724667, 0x7a1a13, 0x9e26bc, 0x4555e7, 0x585cb5,
    0x711d14, 0x486991, 0x480d60, 0x56adab, 0xd62f64, 0x96ee0c,
    0x212ff3, 0x5d6d88, 0xa67684, 0x95651e, 0xab9e0a, 0x4ddefe,
    0x571010, 0x836a39, 0xf8ea31, 0x9e381d, 0xeac8b1, 0xcac96b,
    0x37f21e, 0xd505e9, 0x984743, 0x9fc56c, 0x0331b7, 0x3b8bf8,
    0x86e56a, 0x8dc343, 0x6230e7, 0x93cfd5, 0x6a8f2d, 0x733005,
    0x1af021, 0xa09fcb, 0x7415a1, 0xd56b23, 0x6ff725, 0x2f4bc7,
    0xb8a591, 0x7fac59, 0x5c55de, 0x212c38, 0xb13296, 0x5cff50,
    0x366262, 0xfa7b16, 0xf4d9a6, 0x2acfe7, 0xf07403, 0xd4d604,
    0x6fd916, 0x31b1bf, 0xcbb450, 0x5bd7c8, 0x0ce194, 0x6bd643,
    0x4fd91c, 0xdf4543, 0x5f3453, 0xe2b5aa, 0xc9aec8, 0x131485,
    0xf9d2bf, 0xbadb9e, 0x76f5b9, 0xaf15cf, 0xca3182, 0x14b56d,
    0xe9fe4d, 0x50fc35, 0xf5aed5, 0xa2d0c1, 0xc96057, 0x192eb6,
    0xe91d92, 0x07d144, 0xaea3c6, 0x343566, 0x26d5b4, 0x3161e2,
    0x37f1a2, 0x209eff, 0x958e23, 0x493798, 0x35f4a6, 0x4bdc02,
    0xc2be13, 0xbe80a0, 0x0b72a3, 0x115c5f, 0x1e1bd1, 0x0db4d3,
    0x869e85, 0x96976b, 0x2ac91f, 0x8a26c2, 0x3070f0, 0x041412,
    0xfc9fa5, 0xf72a38, 0x9c6878, 0xe2aa76, 0x50cfe1, 0x559274,
    0x934e38, 0x0a92f7, 0x5533f0, 0xa63db4, 0x399971, 0xe2b755,
    0xa98a7c, 0x008f19, 0xac54d2, 0x2ea0b4, 0xf5f3e0, 0x60c849,
    0xffd269, 0xae52ce, 0x7a5fdd, 0xe9ce06, 0xfb0ae8, 0xa50cce,
    0xea9d3e, 0x3766dd, 0xb834f5, 0x0da090, 0x846f88, 0x4ae3d5,
    0x099a03, 0x2eae2d, 0xfcb40a, 0xfb9b33, 0xe281dd, 0x1b16ba,
    0xd8c0af, 0xd96b97, 0xb52dc9, 0x9c277f, 0x5951d5, 0x21ccd6,
    0xb6496b, 0x584562, 0xb3baf2, 0xa1a5c4, 0x7ca2cf, 0xa9b93d,
    0x7b7b89, 0x483d38, 0x96b03c, 0xc79cb1, 0xd0825d, 0x88edb7,
    0xd38339, 0x0c6e66, 0xe912dc, 0x112034, 0x0de782, 0xa0fee6
};

const double cftal::math::impl::two_over_pi_dbl[948]={
    0x1.99e204p+22, 0x1.b815dp+23, 0x1.57f9ap+19,
    0x1.460db8p+21, 0x1.59bc3p+23, 0x1.89f046p+23,
    0x1.d99ae4p+22, 0x1.2b3b68p+23, 0x1.603fdp+21,
    0x1.57ac06p+23, 0x1.14aaep+23, 0x1.5abbacp+22,
    0x1.eb617ap+23, 0x1.2bd296p+23, 0x1.c0173cp+23,
    0x1.674c3cp+23, 0x1.1f925p+21, 0x1.ac5934p+23,
    0x1.89e35ap+23, 0x1.d71048p+22, 0x1.f276dcp+23,
    0x1.6985cp+19, 0x1.a8d81cp+23, 0x1.a5cabcp+23,
    0x1.65587p+20, 0x1.0d01f6p+23, 0x1.eced68p+23,
    0x1.e698ep+20, 0x1.875c5p+23, 0x1.7525dcp+22,
    0x1.92542cp+23, 0x1.ba70c8p+21, 0x1.c837c8p+21,
    0x1.1c91ap+20, 0x1.544e8cp+23, 0x1.fc3694p+22,
    0x1.267ed2p+23, 0x1.ad44aep+23, 0x1.1d853ep+23,
    0x1.3f5516p+23, 0x1.2b766cp+22, 0x1.9f76b8p+23,
    0x1.d0be8p+20, 0x1.1baa66p+23, 0x1.fdbc6cp+23,
    0x1.efdecp+23, 0x1.661162p+23, 0x1.980304p+23,
    0x1.3d76b2p+23, 0x1.517b1p+20, 0x1.992d6ep+23,
    0x1.dde19ap+23, 0x1.c4cf94p+23, 0x1.cf468p+22,
    0x1.943b8p+20, 0x1.46e92cp+23, 0x1.47535p+21,
    0x1.b9313p+21, 0x1.749408p+21, 0x1.0bd4c2p+23,
    0x1.7f7bacp+22, 0x1.875f88p+22, 0x1.9f4f5cp+23,
    0x1.6f291ap+23, 0x1.45a46p+21, 0x1.ec713p+22,
    0x1.78af8p+17, 0x1.3b0a16p+23, 0x1.145b6p+23,
    0x1.6cdd5p+20, 0x1.8e38ccp+22, 0x1.e96768p+23,
    0x1.70a4bcp+22, 0x1.44ac1p+22, 0x1.721adep+23,
    0x1.b0732ap+23, 0x1.bd5b8ap+23, 0x1.d8262p+20,
    0x1.580612p+23, 0x1.45522cp+23, 0x1.2d578p+17,
    0x1.5a7c8p+19, 0x1.3afac8p+21, 0x1.60cfcp+19,
    0x1.dd2d8cp+22, 0x1.d15602p+23, 0x1.57f7ep+21,
    0x1.028836p+23, 0x1.9efec4p+22, 0x1.3eda9ap+23,
    0x1.e555fcp+22, 0x1.f49a76p+23, 0x1.6538p+19,
    0x1.326ebp+21, 0x1.1cd284p+22, 0x1.5b0c66p+23,
    0x1.ce10e4p+23, 0x1.6f7e28p+22, 0x1.f7df8p+19,
    0x1.a14944p+22, 0x1.c276ccp+23, 0x1.745c6p+22,
    0x1.c6a104p+22, 0x1.451e9cp+23, 0x1.70a6d8p+21,
    0x1.7d2128p+21, 0x1.700bp+18, 0x1.1d1cep+22,
    0x1.80dccp+22, 0x1.2144b4p+22, 0x1.be5956p+23,
    0x1.6a9564p+22, 0x1.1c5d1p+21, 0x1.ef0918p+22,
    0x1.b6cp+10, 0x1.a546c4p+22, 0x1.c1e268p+23,
    0x1.979abp+20, 0x1.3784p+23, 0x1.97c594p+23,
    0x1.a43e98p+22, 0x1.269e62p+23, 0x1.e64be4p+23,
    0x1.fdf22p+23, 0x1.665adep+23, 0x1.98042ap+23,
    0x1.a6f0d8p+23, 0x1.ff5dd2p+23, 0x1.749858p+22,
    0x1.fc4708p+23, 0x1.f9641p+21, 0x1.159be8p+23,
    0x1.a4933cp+23, 0x1.c79d6p+23, 0x1.3e0df6p+23,
    0x1.ca17p+21, 0x1.ad89c4p+23, 0x1.3058e8p+22,
    0x1.a2238p+22, 0x1.ff403p+22, 0x1.645baap+23,
    0x1.8de4d8p+21, 0x1.8f14fp+22, 0x1.29d65ap+23,
    0x1.1ff43cp+23, 0x1.a7fbap+20, 0x1.1795ecp+22,
    0x1.f0989p+22, 0x1.cf1524p+23, 0x1.58532cp+23,
    0x1.a0e898p+21, 0x1.4bdf54p+22, 0x1.484322p+23,
    0x1.a24634p+23, 0x1.61c848p+21, 0x1.5dbc44p+22,
    0x1.61fffp+20, 0x1.8d2064p+23, 0x1.47fdbp+23,
    0x1.c87d2ep+23, 0x1.bf2db4p+23, 0x1.37e69p+22,
    0x1.ca88dcp+22, 0x1.b6cd7cp+23, 0x1.564116p+23,
    0x1.bdbap+16, 0x1.1e954p+23, 0x1.6983dp+23,
    0x1.c8070cp+23, 0x1.4695ap+20, 0x1.d9d1p+16,
    0x1.229cp+23, 0x1.d1bce8p+23, 0x1.11c7ap+21,
    0x1.ab0084p+23, 0x1.60ffp+20, 0x1.b495fp+23,
    0x1.41eea4p+23, 0x1.f97b2cp+22, 0x1.303a08p+23,
    0x1.7dbf48p+23, 0x1.e87dp+22, 0x1.1771ap+22,
    0x1.1dfd48p+22, 0x1.18fdeep+23, 0x1.e0b16ap+23,
    0x1.694976p+23, 0x1.5c146ap+23, 0x1.4499f8p+22,
    0x1.32edb8p+21, 0x1.8b3778p+23, 0x1.534748p+21,
    0x1.a6fc34p+23, 0x1.ac3a32p+23, 0x1.f6ad64p+23,
    0x1.71a3b4p+22, 0x1.4e35dep+23, 0x1.937d26p+23,
    0x1.ebd164p+22, 0x1.2a41eap+23, 0x1.b5d60ep+23,
    0x1.54231cp+22, 0x1.f46bdp+20, 0x1.d1f58ep+23,
    0x1.05292ap+23, 0x1.927554p+23, 0x1.f7db76p+23,
    0x1.e37c4cp+23, 0x1.f27868p+21, 0x1.bdfb5ep+23,
    0x1.733ddcp+23, 0x1.60ec56p+23, 0x1.58937ap+23,
    0x1.9ee77p+23, 0x1.a0d124p+23, 0x1.442bb4p+22,
    0x1.091842p+23, 0x1.d9fce8p+22, 0x1.6750bp+22,
    0x1.bc1fd4p+23, 0x1.2254d8p+23, 0x1.7db05p+21,
    0x1.24827cp+22, 0x1.d2bb44p+23, 0x1.6b2d76p+23,
    0x1.5988p+14, 0x1.14667p+22, 0x1.165fd4p+23,
    0x1.e18858p+23, 0x1.f87cd8p+23, 0x1.15fbe8p+23,
    0x1.fe538p+19, 0x1.16cp+17, 0x1.0a546p+21,
    0x1.ac7d5ap+23, 0x1.3ba94p+20, 0x1.37dfd8p+23,
    0x1.b83d2p+21, 0x1.a31414p+23, 0x1.0c951p+22,
    0x1.6ae9d8p+22, 0x1.f06ccp+20, 0x1.42da9ap+23,
    0x1.536abp+20, 0x1.78338cp+22, 0x1.9ea61p+21,
    0x1.227e5p+23, 0x1.bf746p+20, 0x1.08e79cp+22,
    0x1.16255ep+23, 0x1.f002eap+23, 0x1.f089f2p+23,
    0x1.0659cap+23, 0x1.6f1adap+23, 0x1.49d49ep+23,
    0x1.5dad8p+19, 0x1.bd83fp+20, 0x1.d2efcp+20,
    0x1.d8c62cp+22, 0x1.b251fap+23, 0x1.b877e2p+23,
    0x1.cb8afp+22, 0x1.72ee88p+23, 0x1.5fc0b6p+23,
    0x1.0339b2p+23, 0x1.d47dc8p+22, 0x1.52e79p+22,
    0x1.c0b356p+23, 0x1.9d94b8p+22, 0x1.b7dfbp+20,
    0x1.59b208p+23, 0x1.ce5c16p+23, 0x1.54ccap+21,
    0x1.162d72p+23, 0x1.4701d4p+23, 0x1.f3a3e6p+23,
    0x1.4e672cp+22, 0x1.6379d8p+22, 0x1.643518p+21,
    0x1.ac085p+22, 0x1.6fb3e4p+23, 0x1.069c4p+19,
    0x1.54f872p+23, 0x1.22ee6ap+23, 0x1.d75fp+23,
    0x1.4deb74p+22, 0x1.b64528p+21, 0x1.8b341cp+22,
    0x1.a90bdp+23, 0x1.78295cp+22, 0x1.ab5afp+23,
    0x1.4c0bp+21, 0x1.561f2p+21, 0x1.6c4c14p+22,
    0x1.e747dep+23, 0x1.36d868p+21, 0x1.22042p+19,
    0x1.289de4p+22, 0x1.9a3c6p+19, 0x1.84305ap+23,
    0x1.ea3878p+23, 0x1.000e08p+21, 0x1.d3929p+20,
    0x1.0d8e78p+23, 0x1.0f0508p+22, 0x1.91d248p+22,
    0x1.f39b38p+22, 0x1.edd18p+17, 0x1.6e55bcp+23,
    0x1.6b4a28p+22, 0x1.f6bbfp+23, 0x1.10de8p+23,
    0x1.82b504p+22, 0x1.f487p+21, 0x1.0776ap+19,
    0x1.400078p+22, 0x1.f6806cp+22, 0x1.02684cp+22,
    0x1.355a94p+23, 0x1.bc3438p+21, 0x1.8d8ad4p+23,
    0x1.efb46p+21, 0x1.871694p+23, 0x1.6f5c72p+23,
    0x1.93b5a2p+23, 0x1.f985ep+22, 0x1.0a3746p+23,
    0x1.174eacp+22, 0x1.b4fdap+19, 0x1.3e7dp+22,
    0x1.c65558p+21, 0x1.90fb34p+23, 0x1.a801e8p+22,
    0x1.61318cp+22, 0x1.c2a29ap+23, 0x1.377818p+22,
    0x1.f9b428p+21, 0x1.ef29p+16, 0x1.7e8964p+22,
    0x1.97299cp+22, 0x1.8de418p+21, 0x1.f08d6p+19,
    0x1.55382cp+22, 0x1.a88a04p+23, 0x1.eac0ap+19,
    0x1.b4921ap+23, 0x1.6bc67ep+23, 0x1.4e8094p+23,
    0x1.38be2p+21, 0x1.c2e0b2p+23, 0x1.9427f6p+23,
    0x1.d0b0acp+22, 0x1.e870b4p+22, 0x1.afcea8p+23,
    0x1.52a8bap+23, 0x1.009dp+18, 0x1.952864p+22,
    0x1.b5bf8ep+23, 0x1.3247dp+23, 0x1.3b92a6p+23,
    0x1.dba0b8p+23, 0x1.d58906p+23, 0x1.829f44p+22,
    0x1.343p+23, 0x1.52139ap+23, 0x1.bb2acp+21,
    0x1.65d578p+22, 0x1.96dcap+20, 0x1.8fc0e2p+23,
    0x1.07caap+22, 0x1.ae37dp+22, 0x1.3bbd3ap+23,
    0x1.b3496p+23, 0x1.a5e24p+21, 0x1.421832p+23,
    0x1.496a54p+23, 0x1.523e28p+21, 0x1.3265bcp+23,
    0x1.becfep+19, 0x1.9f5eb8p+22, 0x1.9c9e48p+21,
    0x1.f227ep+19, 0x1.dd525cp+22, 0x1.ec1c6p+20,
    0x1.4bb928p+21, 0x1.541a14p+23, 0x1.4df414p+23,
    0x1.c3a058p+22, 0x1.e9ef94p+23, 0x1.e99eeep+23,
    0x1.1ef5ep+20, 0x1.2c1524p+23, 0x1.312b2cp+23,
    0x1.f745cp+19, 0x1.3678b8p+23, 0x1.8e0a8p+22,
    0x1.96a4a2p+23, 0x1.dd87ep+21, 0x1.0adfeep+23,
    0x1.5f51bap+23, 0x1.0f6e8p+19, 0x1.47649cp+22,
    0x1.38ad92p+23, 0x1.73c0ap+20, 0x1.0132d4p+23,
    0x1.5fb7b6p+23, 0x1.703fd6p+23, 0x1.53ed84p+23,
    0x1.c2922cp+23, 0x1.54bbp+17, 0x1.28239cp+23,
    0x1.0d34a6p+23, 0x1.2ab90cp+23, 0x1.a93618p+21,
    0x1.11ae7cp+22, 0x1.7c156ep+23, 0x1.39f538p+23,
    0x1.9169e8p+23, 0x1.28af78p+23, 0x1.f3abcp+18,
    0x1.dfb6p+16, 0x1.7366dap+23, 0x1.fb4086p+23,
    0x1.febefcp+22, 0x1.ecdbf4p+23, 0x1.9105a2p+23,
    0x1.f4ed7p+20, 0x1.3f67b8p+22, 0x1.866b62p+23,
    0x1.664e28p+21, 0x1.08d1cp+23, 0x1.5e959cp+23,
    0x1.aaa72p+19, 0x1.eb23a2p+23, 0x1.1af18ap+23,
    0x1.e4651ep+23, 0x1.153c52p+23, 0x1.e3534p+18,
    0x1.02e06p+22, 0x1.8c3b98p+21, 0x1.cf2e54p+22,
    0x1.9d6f2p+22, 0x1.a1bcdcp+23, 0x1.8265acp+22,
    0x1.6d444cp+22, 0x1.8aef54p+23, 0x1.570166p+23,
    0x1.0fbb92p+23, 0x1.53e35p+21, 0x1.3291dp+20,
    0x1.9b32cep+23, 0x1.12eb8p+18, 0x1.a86366p+23,
    0x1.9efdc4p+23, 0x1.0ee51cp+23, 0x1.ea4246p+23,
    0x1.0bcf7p+20, 0x1.947044p+22, 0x1.63e86p+21,
    0x1.771894p+22, 0x1.9c0452p+23, 0x1.3618cap+23,
    0x1.6757acp+23, 0x1.f3f098p+21, 0x1.41c966p+23,
    0x1.e1d988p+22, 0x1.afd93ep+23, 0x1.42cep+21,
    0x1.6363e8p+22, 0x1.717acp+19, 0x1.a1cb24p+22,
    0x1.1c5a74p+23, 0x1.57c118p+23, 0x1.6071dcp+23,
    0x1.6beb8p+22, 0x1.4d3928p+23, 0x1.c604fp+22,
    0x1.a521ep+19, 0x1.15b4dp+20, 0x1.512p+22,
    0x1.bc22c8p+22, 0x1.40584p+19, 0x1.22abcep+23,
    0x1.3b748p+17, 0x1.42444p+23, 0x1.72b34cp+23,
    0x1.a47ffp+20, 0x1.3c0a08p+21, 0x1.7125bap+23,
    0x1.a18538p+23, 0x1.d673ep+19, 0x1.cc7dcp+23,
    0x1.a0ca08p+23, 0x1.bfbdf4p+23, 0x1.8b711p+22,
    0x1.df06fp+23, 0x1.0ba504p+22, 0x1.9d1fcp+23,
    0x1.bbbep+19, 0x1.5361c8p+23, 0x1.b5fd44p+23,
    0x1.22bap+18, 0x1.87132p+22, 0x1.d036c2p+23,
    0x1.d03a1p+23, 0x1.f06e5cp+22, 0x1.b7367p+23,
    0x1.750fbp+20, 0x1.8ed70cp+22, 0x1.362fp+19,
    0x1.e54d3cp+23, 0x1.26af24p+23, 0x1.18d5c2p+23,
    0x1.7d0258p+22, 0x1.cce734p+23, 0x1.6b8f5cp+22,
    0x1.d7f78p+20, 0x1.2adeap+21, 0x1.4248cp+20,
    0x1.718d4p+19, 0x1.c7044p+20, 0x1.a067d4p+22,
    0x1.280d58p+22, 0x1.75fda8p+21, 0x1.6898dp+22,
    0x1.3b7f38p+23, 0x1.8b6b4p+20, 0x1.fa2cc2p+23,
    0x1.7eea98p+22, 0x1.e54cep+23, 0x1.5f905p+20,
    0x1.a92aa8p+22, 0x1.436c42p+23, 0x1.e49504p+23,
    0x1.653034p+22, 0x1.da39ap+23, 0x1.9e257p+23,
    0x1.912ep+21, 0x1.4916cp+23, 0x1.b21378p+22,
    0x1.982ddcp+23, 0x1.e8139ep+23, 0x1.77c976p+23,
    0x1.a2ff8p+22, 0x1.50ac68p+21, 0x1.693d04p+23,
    0x1.01a26ep+23, 0x1.d82398p+23, 0x1.9f863cp+22,
    0x1.31f9b8p+21, 0x1.0141f8p+22, 0x1.9a287p+23,
    0x1.d79dfcp+23, 0x1.4457a8p+23, 0x1.5d0bap+19,
    0x1.75e604p+23, 0x1.be196ep+23, 0x1.4a05c8p+21,
    0x1.252f6p+20, 0x1.9e2faap+23, 0x1.d02bep+23,
    0x1.4dd8fcp+23, 0x1.784898p+23, 0x1.1f412p+20,
    0x1.c658f6p+23, 0x1.5088aep+23, 0x1.32cc3p+23,
    0x1.141f3p+23, 0x1.000bb8p+22, 0x1.8d2e18p+22,
    0x1.eb8a5p+20, 0x1.8008ccp+22, 0x1.9ad248p+21,
    0x1.a48d9p+20, 0x1.26f876p+23, 0x1.9b45ccp+22,
    0x1.6745a8p+21, 0x1.463abcp+23, 0x1.6e7f4p+23,
    0x1.8a355p+20, 0x1.3eb24ep+23, 0x1.7665b8p+21,
    0x1.8c9cfp+20, 0x1.23122p+22, 0x1.aa7c4cp+22,
    0x1.ecb118p+21, 0x1.d42ea8p+22, 0x1.272dd6p+23,
    0x1.efee8cp+22, 0x1.bc9a56p+23, 0x1.ad9984p+22,
    0x1.4f69ccp+22, 0x1.487fc4p+22, 0x1.0fb79cp+23,
    0x1.0910c8p+22, 0x1.6f21e2p+23, 0x1.a11b8p+17,
    0x1.939b2p+22, 0x1.e02bcp+19, 0x1.a2fb6p+20,
    0x1.a3e7cp+22, 0x1.cd9bfap+23, 0x1.813a98p+23,
    0x1.7d2468p+23, 0x1.d733bp+22, 0x1.8e834ep+23,
    0x1.3dc854p+23, 0x1.2a29c8p+21, 0x1.e9a65ap+23,
    0x1.69144cp+23, 0x1.7c4edp+22, 0x1.e234c8p+21,
    0x1.7ec02cp+22, 0x1.c103e8p+23, 0x1.d13824p+23,
    0x1.97d72p+22, 0x1.69ec2ap+23, 0x1.107efcp+22,
    0x1.5533fap+23, 0x1.15ed08p+21, 0x1.e65fbcp+23,
    0x1.f9cf4cp+23, 0x1.0e0944p+22, 0x1.83c568p+23,
    0x1.ba0ab4p+22, 0x1.1705fp+23, 0x1.4d2352p+23,
    0x1.21eda8p+22, 0x1.0286p+17, 0x1.14fdbcp+22,
    0x1.8b3e98p+21, 0x1.9fe468p+22, 0x1.945f9p+20,
    0x1.ce76ccp+22, 0x1.a73a82p+23, 0x1.d78bc4p+23,
    0x1.20a668p+22, 0x1.c4f504p+23, 0x1.fd33bap+23,
    0x1.a7e4e8p+23, 0x1.71f304p+23, 0x1.5c852p+23,
    0x1.2ffa7p+20, 0x1.303da8p+21, 0x1.a67a3p+21,
    0x1.f03094p+22, 0x1.a9dbap+21, 0x1.21e4a2p+23,
    0x1.166c3p+20, 0x1.49fbap+20, 0x1.5f1976p+23,
    0x1.e5c0eep+23, 0x1.b22bdcp+23, 0x1.4ba2d4p+23,
    0x1.4a5a44p+23, 0x1.34b4a4p+23, 0x1.756e52p+23,
    0x1.e885d8p+22, 0x1.3c293p+22, 0x1.0db96p+22,
    0x1.137bdep+23, 0x1.0260d2p+23, 0x1.2f51b2p+23,
    0x1.f310d4p+23, 0x1.9bef6ap+23, 0x1.4f2428p+21,
    0x1.a5116cp+22, 0x1.98f168p+23, 0x1.daf31cp+22,
    0x1.308554p+23, 0x1.b2586p+23, 0x1.51532cp+23,
    0x1.18b8ccp+22, 0x1.18fce2p+23, 0x1.bceecp+20,
    0x1.87d474p+22, 0x1.abccap+20, 0x1.72bfcp+18,
    0x1.6c0ceep+23, 0x1.9ef91ap+23, 0x1.6e51c2p+23,
    0x1.efdf26p+23, 0x1.cae1ccp+23, 0x1.a9aabcp+22,
    0x1.fc76b4p+22, 0x1.d70f2cp+22, 0x1.3c01f6p+23,
    0x1.75828ep+23, 0x1.6a3336p+23, 0x1.474c6p+20,
    0x1.24ba94p+23, 0x1.f207b8p+23, 0x1.9924a2p+23,
    0x1.31deecp+22, 0x1.eb3538p+23, 0x1.ac0e4p+21,
    0x1.549d6p+20, 0x1.9aae1cp+23, 0x1.468e5p+20,
    0x1.23a56p+20, 0x1.9be964p+22, 0x1.f7242p+22,
    0x1.9e645ep+23, 0x1.8107f8p+22, 0x1.1ba5c6p+23,
    0x1.78a7ep+19, 0x1.dc721p+21, 0x1.f426ep+23,
    0x1.f2ae6cp+23, 0x1.3c5a4ep+23, 0x1.c6e7bp+21,
    0x1.bdfb0cp+23, 0x1.fd1fdep+23, 0x1.534dd6p+23,
    0x1.8745dp+22, 0x1.f7651cp+22, 0x1.173d82p+23,
    0x1.03fc32p+23, 0x1.98fc54p+23, 0x1.f8065p+22,
    0x1.97afe4p+22, 0x1.4104eap+23, 0x1.1fae42p+23,
    0x1.0ffp+12, 0x1.47e6c2p+23, 0x1.1ad87p+22,
    0x1.04e648p+23, 0x1.49883p+23, 0x1.4f4aap+23,
    0x1.180f8cp+22, 0x1.7774cp+23, 0x1.b02448p+22,
    0x1.e7a378p+23, 0x1.10c6bp+23, 0x1.51448ep+23,
    0x1.82867cp+23, 0x1.0691dp+23, 0x1.34972p+22,
    0x1.61c106p+23, 0x1.68f93ap+23, 0x1.d009c6p+23,
    0x1.419f4p+18, 0x1.847108p+22, 0x1.e45692p+23,
    0x1.219fdp+23, 0x1.8d0908p+22, 0x1.5421e8p+23,
    0x1.a83612p+23, 0x1.5228b8p+22, 0x1.6a83f8p+22,
    0x1.6692cp+19, 0x1.4f1e6p+20, 0x1.6cab1cp+23,
    0x1.3ab2p+17, 0x1.2ae05ep+23, 0x1.d88378p+22,
    0x1.2af3ap+19, 0x1.b83c4p+21, 0x1.bf714p+23,
    0x1.d04eecp+22, 0x1.1c31fp+20, 0x1.364d8p+18,
    0x1.154c6ap+23, 0x1.13f444p+23, 0x1.bf212ap+23,
    0x1.cde5acp+23, 0x1.2a2d6p+23, 0x1.745dccp+22,
    0x1.1af8ap+23, 0x1.9b8d6cp+22, 0x1.281118p+22,
    0x1.d37fbp+21, 0x1.1323cap+23, 0x1.b95628p+21,
    0x1.fb8f74p+23, 0x1.51d9ep+20, 0x1.23ad4p+20,
    0x1.1cd9p+21, 0x1.4622ccp+22, 0x1.a78862p+23,
    0x1.e81a92p+23, 0x1.a375dp+20, 0x1.b9ddfep+23,
    0x1.b7d99p+23, 0x1.efde8cp+22, 0x1.d50bccp+22,
    0x1.bc562p+22, 0x1.c6294ap+23, 0x1.653532p+23,
    0x1.7e80fep+23, 0x1.35b6fp+21, 0x1.de190cp+22,
    0x1.b4ffb6p+23, 0x1.4c86c4p+23, 0x1.2148c8p+21,
    0x1.67b47p+22, 0x1.cf2e5cp+23, 0x1.938e58p+21,
    0x1.5b5eccp+23, 0x1.d98d18p+22, 0x1.d37e22p+23,
    0x1.79955cp+23, 0x1.2de6f4p+23, 0x1.80112cp+23,
    0x1.696966p+23, 0x1.e5642p+23, 0x1.82bc88p+23,
    0x1.af0332p+23, 0x1.d4b02p+22, 0x1.91f454p+22,
    0x1.f9bc0cp+22, 0x1.6630ap+21, 0x1.137778p+23,
    0x1.8f50e6p+23, 0x1.93cc2cp+22, 0x1.aa06f6p+23,
    0x1.74ba7p+22, 0x1.4c03cp+18, 0x1.bafe68p+22,
    0x1.f0567p+23, 0x1.ceef88p+22, 0x1.2ff79ep+23,
    0x1.7b84b6p+23, 0x1.cd1418p+21, 0x1.0775c8p+21,
    0x1.165b24p+22, 0x1.96e8ap+21, 0x1.6d0eap+21,
    0x1.a592d6p+23, 0x1.f523f6p+23, 0x1.5ba17ap+23,
    0x1.0d5b8ap+23, 0x1.7657ap+19, 0x1.bb3ceep+23,
    0x1.d52174p+23, 0x1.4bd88p+17, 0x1.bb56cp+18,
    0x1.cd405p+20, 0x1.58f3c8p+22, 0x1.7b5b3cp+22,
    0x1.5fe1ep+19, 0x1.d56d84p+23, 0x1.688a58p+23,
    0x1.df6788p+21, 0x1.18b4aep+23, 0x1.f61bep+19,
    0x1.0e17dp+21, 0x1.c2bddap+23, 0x1.4de53cp+23,
    0x1.52d37p+21, 0x1.13dd78p+22, 0x1.4abccap+23,
    0x1.eae67ep+23, 0x1.49c2ecp+23, 0x1.bf362p+21,
    0x1.21e0fp+20, 0x1.53b6fap+23, 0x1.953bbcp+23,
    0x1.129a7ap+23, 0x1.4e00bp+20, 0x1.d90a6p+22,
    0x1.99dacp+19, 0x1.84328p+22, 0x1.893d7ap+23,
    0x1.9f0e7ap+23, 0x1.286bbp+23, 0x1.ff8a6p+21,
    0x1.d6fd7p+21, 0x1.bb5b08p+21, 0x1.4257a4p+23,
    0x1.09442p+22, 0x1.57c7fp+20, 0x1.adbddep+23,
    0x1.a84d38p+22, 0x1.e10248p+21, 0x1.6d932p+19,
    0x1.3dd70ep+23, 0x1.6e5a22p+23, 0x1.9337fp+21,
    0x1.826fdp+23, 0x1.ac4af4p+23, 0x1.ae4edcp+23,
    0x1.c7021p+22, 0x1.608582p+23, 0x1.f7e0d4p+23,
    0x1.c3cc9cp+22, 0x1.81bc44p+22, 0x1.c6d138p+21,
    0x1.7ee4p+20, 0x1.2f2c4ep+23, 0x1.1c914p+21,
    0x1.b106dcp+22, 0x1.b8208ep+23, 0x1.bfbeaap+23,
    0x1.86f85ap+23, 0x1.de7c98p+21, 0x1.48a88cp+23,
    0x1.1a5878p+21, 0x1.6d183p+23, 0x1.89304p+18,
    0x1.d8cdf8p+23, 0x1.b50194p+22, 0x1.00ap+13,
    0x1.a066d2p+23, 0x1.577e1cp+23, 0x1.14e54p+19,
    0x1.5024b8p+22, 0x1.5364e8p+22, 0x1.7c635p+22,
    0x1.62d9b4p+23, 0x1.d50c9ep+23, 0x1.8f40d4p+22,
    0x1.555e4p+21, 0x1.b64064p+23, 0x1.182ce8p+23,
    0x1.0ea7e8p+23, 0x1.96ee28p+21, 0x1.3dec94p+23,
    0x1.0c57cp+19, 0x1.3346c8p+23, 0x1.ac5ca4p+23,
    0x1.67157p+22, 0x1.3e4ad2p+23, 0x1.32c166p+23,
    0x1.1096e4p+23, 0x1.f3a748p+22, 0x1.34da64p+22,
    0x1.add874p+22, 0x1.0dda22p+23, 0x1.68b314p+22,
    0x1.c7ce2p+21, 0x1.fc4ac8p+21, 0x1.d2e9cep+23,
    0x1.46ced4p+22, 0x1.418134p+22, 0x1.295244p+23,
    0x1.5f19p+16, 0x1.c374ap+19, 0x1.6212fp+22,
    0x1.d4abap+21, 0x1.740268p+22, 0x1.cfca7p+22,
    0x1.4f769ap+23, 0x1.c6789cp+22, 0x1.4c42p+16,
    0x1.e7a824p+23, 0x1.459468p+21, 0x1.2440ep+23
};

const double cftal::math::impl::pi_over_2[8]={
   1.5707962512969970703125e+00, // 0x3ff921fb, 0x40000000
   7.5497894158615963533521e-08, // 0x3e74442d, 0x00000000
   5.3903025299577647655447e-15, // 0x3cf84698, 0x80000000
   3.2820034158079129412316e-22, // 0x3b78cc51, 0x60000000
   1.2706557530806760734906e-29, // 0x39f01b83, 0x80000000
   1.2293330898111132893224e-36, // 0x387a2520, 0x40000000
   2.7337005381646455962378e-44, // 0x36e38222, 0x80000000
   2.1674168387780481944397e-51  // 0x3569f31d, 0x00000000
};
