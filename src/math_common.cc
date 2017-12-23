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
    0x1.45f306p+23, 0x1.b9391p+22, 0x1.529fcp+20,
    0x1.3abe88p+21, 0x1.ea69bap+23, 0x1.81b6c4p+23,
    0x1.2b3278p+23, 0x1.0e4104p+22, 0x1.fca2c6p+23,
    0x1.57bd76p+23, 0x1.8ac36ep+23, 0x1.2371dp+21,
    0x1.093748p+22, 0x1.c00c92p+23, 0x1.775048p+21,
    0x1.a32438p+23, 0x1.fc3bd6p+23, 0x1.cb129p+20,
    0x1.4e7ddp+23, 0x1.046beap+23, 0x1.75da2p+21,
    0x1.09d338p+23, 0x1.c09adp+22, 0x1.7df904p+22,
    0x1.cc8ebp+21, 0x1.cc1a98p+21, 0x1.cfa4ep+21,
    0x1.08bf16p+23, 0x1.7bf25p+23, 0x1.d8ffcp+21,
    0x1.2fffbcp+23, 0x1.6603cp+18, 0x1.de5e22p+23,
    0x1.16b414p+23, 0x1.b47db4p+22, 0x1.b3f678p+21,
    0x1.3e5848p+21, 0x1.6e9e8cp+23, 0x1.fb34fp+21,
    0x1.7fa8b4p+22, 0x1.d49ee8p+22, 0x1.8fd7cap+23,
    0x1.e2f67ap+23, 0x1.ce7dcp+18, 0x1.14a524p+23,
    0x1.d4d7f6p+23, 0x1.7ec47cp+22, 0x1.1aba1p+23,
    0x1.580ccp+22, 0x1.1bf1ecp+22, 0x1.aeafcp+22,
    0x1.9f784p+23, 0x1.35e86cp+23, 0x1.da9e3p+20,
    0x1.22c2bcp+23, 0x1.cc361p+23, 0x1.966614p+22,
    0x1.7c528p+22, 0x1.a10234p+22, 0x1.ffb1p+23,
    0x1.35cc9cp+22, 0x1.88303p+21, 0x1.556cap+20,
    0x1.cea324p+22, 0x1.8389ecp+22, 0x1.8118d6p+23,
    0x1.1f1064p+22, 0x1.86cf9ap+23, 0x1.b9d012p+23,
    0x1.541ac8p+21, 0x1.88ed16p+23, 0x1.2c394cp+23,
    0x1.bb5e88p+23, 0x1.a2ae32p+23, 0x1.4fa94p+18,
    0x1.fe0e0ap+23, 0x1.fbf198p+21, 0x1.d06584p+23,
    0x1.bc9f3p+23, 0x1.93edd8p+21, 0x1.867a4cp+23,
    0x1.ded63cp+23, 0x1.7be27cp+22, 0x1.d0f9a8p+21,
    0x1.95e4fep+23, 0x1.d87f1p+20, 0x1.0c83ep+21,
    0x1.f091a8p+22, 0x1.f4ddaap+23, 0x1.dcb4cp+22,
    0x1.0cec54p+22, 0x1.8c296ap+23, 0x1.3a3386p+23,
    0x1.85895ap+23, 0x1.0534bp+22, 0x1.74003p+22,
    0x1.19f618p+22, 0x1.6b8f18p+21, 0x1.358d36p+23,
    0x1.88ccp+14, 0x1.f34adp+22, 0x1.2f4f68p+23,
    0x1.aaaa6ep+23, 0x1.ec7daep+23, 0x1.810a3p+20,
    0x1.f8ec9ap+23, 0x1.54eb2p+21, 0x1.57aeep+23,
    0x1.f0f8c6p+23, 0x1.5ec1e8p+22, 0x1.ce2a2ep+23,
    0x1.5927p+22, 0x1.b3ac76p+23, 0x1.c42538p+21,
    0x1.964648p+23, 0x1.de2b58p+22, 0x1.1aa2dp+21,
    0x1.723ep+23, 0x1.b0af1p+20, 0x1.bf9c32p+23,
    0x1.fe633ep+23, 0x1.a87998p+22, 0x1.855e64p+22,
    0x1.1feebp+22, 0x1.b0fefcp+23, 0x1.6eca44p+23,
    0x1.13d064p+23, 0x1.82ff98p+22, 0x1.9b89dep+23,
    0x1.26cd8p+19, 0x1.a87ebap+23, 0x1.afbc2cp+23,
    0x1.bc76bp+23, 0x1.2537bcp+23, 0x1.41169p+21,
    0x1.d10c5p+23, 0x1.356388p+22, 0x1.96563p+21,
    0x1.6e308p+20, 0x1.96fbcp+23, 0x1.43005cp+22,
    0x1.4e3be6p+23, 0x1.6f806p+22, 0x1.a0997p+21,
    0x1.884a0cp+22, 0x1.4883p+16, 0x1.6e3bd4p+22,
    0x1.fec2b4p+22, 0x1.e5d23cp+23, 0x1.0d292p+22,
    0x1.a6ce2p+23, 0x1.b1bb54p+23, 0x1.097eb8p+22,
    0x1.9cc2d4p+23, 0x1.485014p+23, 0x1.6933a6p+23,
    0x1.e54c0cp+23, 0x1.fddd7p+22, 0x1.078546p+23,
    0x1.1078c2p+23, 0x1.e1ce28p+22, 0x1.6a32bcp+22,
    0x1.7baedep+23, 0x1.8e98b4p+22, 0x1.977fe8p+23,
    0x1.df031ap+23, 0x1.9f0498p+22, 0x1.172954p+22,
    0x1.b6ce5p+21, 0x1.a5505p+23, 0x1.1ac384p+23,
    0x1.df2448p+22, 0x1.42604p+20, 0x1.368c24p+23,
    0x1.88b388p+23, 0x1.13172p+22, 0x1.23649ap+23,
    0x1.e62ep+23, 0x1.5a87a8p+23, 0x1.ca9252p+23,
    0x1.0d5fdp+20, 0x1.f97cp+23, 0x1.99283cp+23,
    0x1.dd9cep+23, 0x1.ea7c26p+23, 0x1.01e3d8p+23,
    0x1.87cf66p+23, 0x1.47c638p+21, 0x1.280b26p+23,
    0x1.f38e08p+21, 0x1.66125cp+23, 0x1.e68a16p+23,
    0x1.38251p+23, 0x1.ec82acp+22, 0x1.3f6a5cp+23,
    0x1.85248ep+23, 0x1.7993d8p+21, 0x1.b5543p+22,
    0x1.214ee4p+23, 0x1.fe76bp+20, 0x1.2d9662p+23,
    0x1.2859e4p+22, 0x1.c4f282p+23, 0x1.13bfe8p+23,
    0x1.2f29dp+23, 0x1.09cdc4p+23, 0x1.2e6332p+23,
    0x1.afb62p+22, 0x1.b2faf8p+21, 0x1.dfb76p+19,
    0x1.69349p+23, 0x1.b2919cp+22, 0x1.09c9c4p+22,
    0x1.92ec68p+21, 0x1.702b3ep+23, 0x1.3cb78p+19,
    0x1.298c68p+21, 0x1.cba7b8p+21, 0x1.c053p+20,
    0x1.0c0dp+16, 0x1.a0212cp+22, 0x1.63b8bp+22,
    0x1.21548ep+23, 0x1.73bap+17, 0x1.26b5e8p+21,
    0x1.4cfbeep+23, 0x1.c921b8p+22, 0x1.de2d3ep+23,
    0x1.4d291cp+23, 0x1.ed2368p+23, 0x1.454f44p+22,
    0x1.e4159ep+23, 0x1.9cc1p+21, 0x1.f92fd4p+22,
    0x1.a18ec8p+22, 0x1.7cfb74p+22, 0x1.aeap+17,
    0x1.fe2614p+22, 0x1.4a92a8p+21, 0x1.80c86ep+23,
    0x1.0d86dp+20, 0x1.92419p+21, 0x1.d5316cp+22,
    0x1.a8e29cp+23, 0x1.b95114p+22, 0x1.821216p+23,
    0x1.a7d4a8p+22, 0x1.aacc28p+23, 0x1.3a0e4ep+23,
    0x1.401174p+22, 0x1.b67768p+23, 0x1.8aedd4p+23,
    0x1.7f987p+20, 0x1.f5ad24p+22, 0x1.744e3ap+23,
    0x1.4b4cbp+21, 0x1.59998cp+23, 0x1.5052b4p+22,
    0x1.ab8a4p+22, 0x1.13b31p+23, 0x1.41c8bp+22,
    0x1.7d4808p+23, 0x1.280eeep+23, 0x1.c0c3ccp+22,
    0x1.3fep+21, 0x1.50e3d4p+23, 0x1.270998p+22,
    0x1.ef032p+21, 0x1.07bb2ep+23, 0x1.2e7f46p+23,
    0x1.fb2886p+23, 0x1.190c1ap+23, 0x1.bc8262p+23,
    0x1.3a7324p+23, 0x1.18e1bap+23, 0x1.cf6e2ep+23,
    0x1.def84p+21, 0x1.59b8a8p+21, 0x1.4100b8p+23,
    0x1.2700b4p+23, 0x1.24222p+23, 0x1.b1d01ep+23,
    0x1.5f00d8p+23, 0x1.2fff6cp+22, 0x1.f207p+19,
    0x1.d86164p+22, 0x1.5a562p+20, 0x1.7796c2p+23,
    0x1.73138ep+23, 0x1.7a802p+23, 0x1.3cb48p+18,
    0x1.3baa48p+21, 0x1.ed6dd6p+23, 0x1.7645b6p+23,
    0x1.542814p+23, 0x1.793448p+21, 0x1.da0d9p+22,
    0x1.99d848p+21, 0x1.a940ep+20, 0x1.5474a2p+23,
    0x1.85463ap+23, 0x1.5ddb5ep+23, 0x1.2265cp+20,
    0x1.3709b4p+22, 0x1.38f45ap+23, 0x1.2ead8p+23,
    0x1.067e06p+23, 0x1.ede012p+23, 0x1.188056p+23,
    0x1.3262dap+23, 0x1.ed0e4p+18, 0x1.5200cp+20,
    0x1.6f0f6p+22, 0x1.8925eap+23, 0x1.2eb718p+22,
    0x1.4b949cp+23, 0x1.9a6f4ep+23, 0x1.b54f3p+21,
    0x1.292556p+23, 0x1.a10b74p+22, 0x1.bcc632p+23,
    0x1.df18ecp+23, 0x1.4a2dap+22, 0x1.bedfep+21,
    0x1.57435cp+23, 0x1.88aef8p+21, 0x1.435cp+23,
    0x1.b5f618p+23, 0x1.99359p+22, 0x1.6e0bdap+23,
    0x1.832948p+21, 0x1.7eacaep+23, 0x1.d7fa38p+21,
    0x1.73f2d4p+23, 0x1.e77ceap+23, 0x1.bf265p+23,
    0x1.840558p+21, 0x1.ed18ccp+23, 0x1.5cb04p+20,
    0x1.88be8p+18, 0x1.de4d9p+20, 0x1.49667ap+23,
    0x1.1e36aep+23, 0x1.39a6cp+19, 0x1.d2849cp+23,
    0x1.497c26p+23, 0x1.6a4666p+23, 0x1.aaafp+20,
    0x1.50ca9ep+23, 0x1.4b83a4p+23, 0x1.e7e16p+19,
    0x1.9af0b6p+23, 0x1.dbe48cp+22, 0x1.22decp+18,
    0x1.c85e24p+22, 0x1.4e9b18p+22, 0x1.c4dcdep+23,
    0x1.d7dep+15, 0x1.612a6cp+22, 0x1.6fb588p+23,
    0x1.74cd54p+23, 0x1.9f9eecp+23, 0x1.d02d1p+20,
    0x1.6f8d88p+21, 0x1.833318p+23, 0x1.deb70cp+22,
    0x1.b4910cp+23, 0x1.40bbeep+23, 0x1.e9018cp+23,
    0x1.7f856p+21, 0x1.35d9bap+23, 0x1.78b87ep+23,
    0x1.b77b4p+22, 0x1.fc79p+20, 0x1.6db654p+23,
    0x1.d12d18p+21, 0x1.355ep+23, 0x1.26a75ap+23,
    0x1.15ed8p+18, 0x1.685a52p+23, 0x1.fa012cp+22,
    0x1.4e0fb4p+23, 0x1.d54ecp+19, 0x1.42b2f6p+23,
    0x1.5090bp+21, 0x1.6dbeep+21, 0x1.fbcbf4p+23,
    0x1.fdb712p+23, 0x1.fb7d12p+23, 0x1.b1db9p+22,
    0x1.f9520cp+23, 0x1.c200f8p+22, 0x1.56e85p+20,
    0x1.ff0ffap+23, 0x1.cf8ap+18, 0x1.9b3b08p+21,
    0x1.0c3054p+23, 0x1.d57a9ap+23, 0x1.5fcf66p+23,
    0x1.b9b63cp+22, 0x1.cb3ca8p+21, 0x1.6efcc4p+22,
    0x1.235e1p+22, 0x1.6df3p+20, 0x1.0cb71cp+22,
    0x1.ab0928p+21, 0x1.9ce192p+23, 0x1.71966p+23,
    0x1.fad97ep+23, 0x1.440148p+23, 0x1.c8d80ap+23,
    0x1.41bab4p+23, 0x1.1dbc84p+22, 0x1.a424c4p+23,
    0x1.08b972p+23, 0x1.2585cp+22, 0x1.c0acd6p+23,
    0x1.5299p+16, 0x1.baaa8p+21, 0x1.6faa3cp+23,
    0x1.89e266p+23, 0x1.7db84cp+22, 0x1.c860bap+23,
    0x1.525d0ap+23, 0x1.87643ap+23, 0x1.b19508p+21,
    0x1.496e1p+23, 0x1.a963d4p+23, 0x1.0fb8bp+21,
    0x1.c8d31ep+23, 0x1.dffc9cp+22, 0x1.000618p+23,
    0x1.6a0468p+21, 0x1.419a9ep+23, 0x1.334a4p+23,
    0x1.a74566p+23, 0x1.4ba5ep+19, 0x1.0be6dp+22,
    0x1.97b422p+23, 0x1.a17cfap+23, 0x1.83b736p+23,
    0x1.7a2f56p+23, 0x1.034594p+23, 0x1.71a82p+22,
    0x1.7552ep+20, 0x1.54009cp+22, 0x1.e028fep+23,
    0x1.0c0fc2p+23, 0x1.902c5p+22, 0x1.1a832cp+23,
    0x1.bd7d0ep+23, 0x1.57eedp+21, 0x1.6c4ad6p+23,
    0x1.a44bd8p+21, 0x1.fde60ap+23, 0x1.3d7f72p+23,
    0x1.3da9ap+22, 0x1.505494p+23, 0x1.6b113cp+22,
    0x1.79f05ap+23, 0x1.30b5aep+23, 0x1.2b8fe8p+23,
    0x1.1a9a1ap+23, 0x1.4c744p+23, 0x1.7d5e9p+22,
    0x1.627e28p+23, 0x1.2a71p+23, 0x1.20ccp+16,
    0x1.0dbae2p+23, 0x1.6dbd92p+23, 0x1.eac17ep+23,
    0x1.1654dp+20, 0x1.ac1c04p+22, 0x1.596118p+23,
    0x1.a18164p+23, 0x1.215544p+22, 0x1.df63cp+19,
    0x1.86e52ap+23, 0x1.d83518p+21, 0x1.aa06p+21,
    0x1.ef7018p+22, 0x1.988bcp+23, 0x1.f4529cp+23,
    0x1.9195acp+23, 0x1.07cfap+22, 0x1.bcc8f8p+23,
    0x1.b0c936p+23, 0x1.8df6c8p+21, 0x1.872f48p+23,
    0x1.a8b0eep+23, 0x1.8bc6d2p+23, 0x1.3dafp+20,
    0x1.e1d5dp+21, 0x1.186118p+22, 0x1.7dd554p+22,
    0x1.eb7ba4p+23, 0x1.8d24dcp+23, 0x1.74babp+22,
    0x1.da881cp+23, 0x1.08f87p+22, 0x1.0f88c2p+23,
    0x1.d3fa52p+23, 0x1.e7adcep+23, 0x1.94f844p+23,
    0x1.ac8b78p+21, 0x1.8bc01p+23, 0x1.1baffep+23,
    0x1.c4d4dcp+23, 0x1.8dfb6p+23, 0x1.821126p+23,
    0x1.d175fp+22, 0x1.655ad6p+23, 0x1.3add9ap+23,
    0x1.edc8f8p+22, 0x1.a84718p+22, 0x1.539feep+23,
    0x1.bee652p+23, 0x1.75936ap+23, 0x1.4402dcp+22,
    0x1.b65c4p+19, 0x1.25d3ap+21, 0x1.81f794p+22,
    0x1.15b0e8p+23, 0x1.60a868p+21, 0x1.83102p+19,
    0x1.28ccfcp+23, 0x1.62901p+20, 0x1.d9ea7cp+22,
    0x1.7dfbfap+23, 0x1.de8aacp+23, 0x1.b3f6c8p+21,
    0x1.3d9ecp+20, 0x1.737516p+23, 0x1.f92f88p+23,
    0x1.3d4188p+21, 0x1.86dde2p+23, 0x1.b62cap+21,
    0x1.5aa36p+22, 0x1.6b5168p+23, 0x1.d999ep+19,
    0x1.6c489p+21, 0x1.a2bb78p+21, 0x1.12ac58p+23,
    0x1.c79d32p+23, 0x1.7241acp+23, 0x1.54bcd6p+23,
    0x1.38547cp+23, 0x1.98be22p+23, 0x1.282ff4p+22,
    0x1.f7e9c2p+23, 0x1.b4ee38p+22, 0x1.64371p+21,
    0x1.09a9d2p+23, 0x1.5369f8p+23, 0x1.a3dddep+23,
    0x1.926a5cp+23, 0x1.84e4bcp+22, 0x1.1084ep+22,
    0x1.91b236p+23, 0x1.5f902p+19, 0x1.a92becp+22,
    0x1.b0385ep+23, 0x1.0968a6p+23, 0x1.19329cp+23,
    0x1.9844a8p+23, 0x1.b8aa54p+23, 0x1.ad8d8p+23,
    0x1.2c3216p+23, 0x1.70e034p+23, 0x1.9255a4p+22,
    0x1.816898p+22, 0x1.dca47ep+23, 0x1.e22fep+19,
    0x1.1b5f4p+20, 0x1.eb97f8p+23, 0x1.6de1ap+21,
    0x1.dd7868p+23, 0x1.98bbdp+23, 0x1.817b74p+22,
    0x1.371ccep+23, 0x1.de6724p+23, 0x1.702f92p+23,
    0x1.36b0c2p+23, 0x1.78afc2p+23, 0x1.8d06a2p+23,
    0x1.03ed8p+20, 0x1.21c774p+22, 0x1.ba385ap+23,
    0x1.42315ep+23, 0x1.18b084p+22, 0x1.afe6b2p+23,
    0x1.30f5b2p+23, 0x1.80a93cp+23, 0x1.f50c9ep+23,
    0x1.f80cacp+23, 0x1.5cf3cap+23, 0x1.b11448p+21,
    0x1.1569cp+21, 0x1.b926cep+23, 0x1.55d0aap+23,
    0x1.c1341p+21, 0x1.37cf94p+23, 0x1.481aa2p+23,
    0x1.626732p+23, 0x1.daf52p+19, 0x1.2015a4p+22,
    0x1.e164cap+23, 0x1.4f10fep+23, 0x1.2e991p+23,
    0x1.b68fc8p+21, 0x1.672442p+23, 0x1.2a09ecp+22,
    0x1.0e7ccp+21, 0x1.b93e8p+23, 0x1.551f7p+22,
    0x1.d3a708p+21, 0x1.0bad9cp+22, 0x1.bf3bfcp+23,
    0x1.7f5178p+22, 0x1.48cef6p+23, 0x1.eab2e8p+22,
    0x1.45ecaap+23, 0x1.1c4158p+21, 0x1.56e904p+22,
    0x1.0dcb2p+19, 0x1.0c5442p+23, 0x1.068e72p+23,
    0x1.cdc712p+23, 0x1.a93dcap+23, 0x1.03ed24p+22,
    0x1.d2adfep+23, 0x1.941e38p+23, 0x1.14b38ap+23,
    0x1.5fd4ap+21, 0x1.8b83a6p+23, 0x1.9f8a1ep+23,
    0x1.5cb5b6p+23, 0x1.0d8a8ep+23, 0x1.890e14p+22,
    0x1.dc3108p+21, 0x1.28f258p+23, 0x1.0ec22p+23,
    0x1.ed30a8p+22, 0x1.a2c8p+20, 0x1.2bf43p+20,
    0x1.204d1p+23, 0x1.1278fp+23, 0x1.c9895p+23,
    0x1.ef6f94p+22, 0x1.847588p+23, 0x1.d5e84cp+23,
    0x1.14cfeep+23, 0x1.7f241ap+23, 0x1.5d1b28p+21,
    0x1.63267ap+23, 0x1.6f97ap+19, 0x1.b8a348p+23,
    0x1.8f749cp+22, 0x1.bbc2d2p+23, 0x1.9949ap+20,
    0x1.2a535p+23, 0x1.46734p+21, 0x1.69da12p+23,
    0x1.04fa2p+21, 0x1.95309cp+23, 0x1.8e09cp+22,
    0x1.1be3fp+21, 0x1.95c878p+21, 0x1.1deb4ep+23,
    0x1.ceac28p+23, 0x1.1e242p+19, 0x1.54eda8p+21,
    0x1.35f9bcp+22, 0x1.446694p+22, 0x1.57f36ap+23,
    0x1.adbf04p+23, 0x1.877658p+22, 0x1.1b0bp+17,
    0x1.3e7588p+23, 0x1.434506p+23, 0x1.b7b5c8p+22,
    0x1.ea34e4p+22, 0x1.537104p+23, 0x1.70c9acp+22,
    0x1.6c9d18p+22, 0x1.da68p+23, 0x1.dc0348p+22,
    0x1.57d3fp+22, 0x1.356404p+22, 0x1.00e3cp+23,
    0x1.c27f12p+23, 0x1.652be6p+23, 0x1.92a3c4p+22,
    0x1.5d4e96p+23, 0x1.c7e26p+21, 0x1.d56576p+23,
    0x1.1c9c2cp+22, 0x1.57874ep+23, 0x1.a5d3p+21,
    0x1.4b74dp+22, 0x1.f0ac74p+23, 0x1.d6fd14p+23,
    0x1.8dd9bp+21, 0x1.6256dcp+22, 0x1.1fdea4p+22,
    0x1.298754p+23, 0x1.a7244ap+23, 0x1.e7f3ep+20,
    0x1.b12e9cp+23, 0x1.77529ep+23, 0x1.b15c02p+23,
    0x1.ccc368p+23, 0x1.c9ec7p+21, 0x1.4a4754p+23,
    0x1.98347p+21, 0x1.633b5p+20, 0x1.dd8c4p+21,
    0x1.d3a9dp+20, 0x1.004f4p+22, 0x1.9837cap+23,
    0x1.f0c5cep+23, 0x1.df9478p+21, 0x1.cdadf8p+21,
    0x1.7846ap+19, 0x1.13a3fp+21, 0x1.448f8p+23,
    0x1.aa5a3ep+23, 0x1.9add3p+20, 0x1.2129bep+23,
    0x1.2623ap+23, 0x1.68564ap+23, 0x1.25b6c8p+22,
    0x1.c4c964p+23, 0x1.7bc4d4p+22, 0x1.de352p+21,
    0x1.a4adp+20, 0x1.55925cp+23, 0x1.93a218p+22,
    0x1.5cc244p+22, 0x1.3059f6p+23, 0x1.88d8dp+21,
    0x1.0e516p+19, 0x1.7b9dc2p+23, 0x1.838508p+22,
    0x1.d6c83ap+23, 0x1.a17746p+23, 0x1.cab3a8p+23,
    0x1.65ee3p+22, 0x1.522418p+21, 0x1.e66574p+23,
    0x1.f090cep+23, 0x1.6468d8p+21, 0x1.7d4d8p+21,
    0x1.43cf74p+22, 0x1.f3eae6p+23, 0x1.b6c368p+23,
    0x1.fc467cp+23, 0x1.b10698p+22, 0x1.dd463p+23,
    0x1.dd6898p+22, 0x1.78bcb8p+23, 0x1.9d4e1p+23,
    0x1.29b8aep+23, 0x1.c4032cp+23, 0x1.e3d072p+23,
    0x1.7c90a2p+23, 0x1.74b4bcp+22, 0x1.3a5554p+22,
    0x1.b2dd84p+23, 0x1.cfaeaap+23, 0x1.8c138p+22,
    0x1.805c1cp+23, 0x1.f8814p+23, 0x1.77f366p+23,
    0x1.c4969cp+22, 0x1.116fd8p+21, 0x1.ec33bp+23,
    0x1.071838p+23, 0x1.986798p+22, 0x1.641aaap+23,
    0x1.76a26ep+23, 0x1.e7a024p+22, 0x1.5f2292p+23,
    0x1.ae7bcp+19, 0x1.61b4ap+19, 0x1.9cfebp+23,
    0x1.583268p+23, 0x1.c9199cp+22, 0x1.e8684cp+22,
    0x1.3c4d78p+23, 0x1.15579cp+22, 0x1.6172d4p+22,
    0x1.c4745p+22, 0x1.21a644p+22, 0x1.20358p+22,
    0x1.5ab6acp+22, 0x1.ac5ec8p+23, 0x1.2ddc18p+23,
    0x1.097f98p+21, 0x1.75b62p+22, 0x1.4ced08p+23,
    0x1.2aca3cp+23, 0x1.573c14p+23, 0x1.377bf8p+22,
    0x1.5c404p+22, 0x1.06d472p+23, 0x1.f1d462p+23,
    0x1.3c703ap+23, 0x1.d59162p+23, 0x1.9592d6p+23,
    0x1.bf90fp+21, 0x1.aa0bd2p+23, 0x1.308e86p+23,
    0x1.3f8ad8p+23, 0x1.98db8p+17, 0x1.dc5fcp+21,
    0x1.0dcad4p+23, 0x1.1b8686p+23, 0x1.88c39cp+22,
    0x1.279faap+23, 0x1.aa3cb4p+22, 0x1.ccc014p+22,
    0x1.af021p+20, 0x1.413f96p+23, 0x1.d05684p+22,
    0x1.aad646p+23, 0x1.bfdc94p+22, 0x1.7a5e38p+21,
    0x1.714b22p+23, 0x1.feb164p+22, 0x1.715778p+22,
    0x1.0961cp+21, 0x1.62652cp+23, 0x1.73fd4p+22,
    0x1.b3131p+21, 0x1.f4f62cp+23, 0x1.e9b34cp+23,
    0x1.567f38p+21, 0x1.e0e806p+23, 0x1.a9ac08p+23,
    0x1.bf6458p+22, 0x1.8d8df8p+21, 0x1.9768ap+23,
    0x1.6f5f2p+22, 0x1.9c328p+19, 0x1.af590cp+22,
    0x1.3f647p+22, 0x1.be8a86p+23, 0x1.7cd14cp+22,
    0x1.c56b54p+23, 0x1.935d9p+23, 0x1.31485p+20,
    0x1.f3a57ep+23, 0x1.75b73cp+23, 0x1.dbd6e4p+22,
    0x1.5e2b9ep+23, 0x1.946304p+23, 0x1.4b56dp+20,
    0x1.d3fc9ap+23, 0x1.43f0d4p+22, 0x1.eb5daap+23,
    0x1.45a182p+23, 0x1.92c0aep+23, 0x1.92eb6p+20,
    0x1.d23b24p+23, 0x1.f451p+18, 0x1.5d478cp+23,
    0x1.a1ab3p+21, 0x1.36adap+21, 0x1.8b0f1p+21,
    0x1.bf8d1p+21, 0x1.04f7f8p+21, 0x1.2b1c46p+23,
    0x1.24de6p+22, 0x1.afa53p+21, 0x1.2f7008p+22,
    0x1.857c26p+23, 0x1.7d014p+23, 0x1.6e546p+19,
    0x1.15c5fp+20, 0x1.e1bd1p+20, 0x1.b69a6p+19,
    0x1.0d3d0ap+23, 0x1.2d2ed6p+23, 0x1.5648f8p+21,
    0x1.144d84p+23, 0x1.83878p+21, 0x1.05048p+18,
    0x1.f93f4ap+23, 0x1.ee547p+23, 0x1.38d0fp+23,
    0x1.c554ecp+23, 0x1.433f84p+22, 0x1.5649dp+22,
    0x1.269c7p+23, 0x1.525eep+19, 0x1.54cfcp+22,
    0x1.4c7b68p+23, 0x1.cccb88p+21, 0x1.c56eaap+23,
    0x1.5314f8p+23, 0x1.1e32p+15, 0x1.58a9a4p+23,
    0x1.7505ap+21, 0x1.ebe7cp+23, 0x1.832124p+22,
    0x1.ffa4d2p+23, 0x1.5ca59cp+23, 0x1.e97f74p+22,
    0x1.d39c0cp+23, 0x1.f615dp+23, 0x1.4a199cp+23,
    0x1.d53a7cp+23, 0x1.bb36e8p+21, 0x1.7069eap+23,
    0x1.b412p+19, 0x1.08df1p+23, 0x1.2b8f54p+22,
    0x1.33406p+19, 0x1.757168p+21, 0x1.f96814p+23,
    0x1.f73666p+23, 0x1.c503bap+23, 0x1.b16bap+20,
    0x1.b1815ep+23, 0x1.b2d72ep+23, 0x1.6a5b92p+23,
    0x1.384efep+23, 0x1.654754p+22, 0x1.0e66bp+21,
    0x1.6c92d6p+23, 0x1.611588p+22, 0x1.6775e4p+23,
    0x1.434b88p+23, 0x1.f28b3cp+22, 0x1.53727ap+23,
    0x1.edee24p+22, 0x1.20f4ep+22, 0x1.2d6078p+23,
    0x1.8f3962p+23, 0x1.a104bap+23, 0x1.11db6ep+23,
    0x1.a70672p+23, 0x1.8dcccp+19, 0x1.d225b8p+23,
    0x1.12034p+20, 0x1.bcf04p+19, 0x1.41fdccp+23
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
