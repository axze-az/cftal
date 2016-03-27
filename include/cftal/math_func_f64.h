#if !defined (__MATH_FUNC_F64_H__)
#define __MATH_FUNC_F64_H__ 1

// This code uses code from sun libm:
/*
 * ====================================================
 * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/t_real.h>
#include <cftal/std_types.h>
#include <cftal/math_common.h>
#include <cftal/math_impl_poly.h>
#include <cftal/math_impl_d_real_constants_f64.h>
#include <cftal/mem.h>
#include <cmath>
#include <iterator>
#include <iostream>
#include <iomanip>

namespace cftal {

    namespace math {

        template <>
        struct func_traits<double, int32_t>
            : public d_real_traits<double> {
            typedef double vf_type;
            typedef int32_t vi_type;
            typedef bool vmf_type;
            typedef bool vmi_type;
            typedef uint32_t mask_type;
            typedef union {
                double _d;
                uint64_t _u;
            } ud_t;

            static constexpr int32_t bias = 0x3ff;
            static constexpr int32_t e_max= 0x3ff;
            static constexpr int32_t e_min= -1022;
            static constexpr int32_t e_mask= 0x7ff;
            static constexpr int32_t bits=52;
            static constexpr int32_t vec_len=1;

            static constexpr double pinf() {
                return std::numeric_limits<double>::infinity();
            }
            static constexpr double ninf() {
                return -std::numeric_limits<double>::infinity();
            }
            static constexpr double nan() {
                return std::numeric_limits<double>::quiet_NaN();
            }
            static
            vmf_type vmi_to_vmf(const vmi_type& mi) {
                return mi;
            }
            static
            vmi_type vmf_to_vmi(const vmf_type& mf) {
                return mf;
            }
            static
            vi_type sel(const vmi_type& msk,
                        const vi_type& t, const vi_type& f) {
                return msk ? t : f;
            }
            static
            vf_type sel(const vmf_type& msk,
                        const vf_type& t, const vf_type& f) {
                return msk ? t : f;
            }
            static
            vf_type gather(const double* p, vi_type idx, int sc) {
                const char* pc=
                    reinterpret_cast<const char*>(p);
                const char* d = pc + idx * sc;
                vf_type r(*reinterpret_cast<const double*>(d));
                return r;
            }
            static
            vf_type insert_exp(const vi_type& e) {
                ud_t t;
                t._u = uint64_t(e) << bits;
                return t._d;
            }
            static
            vi_type extract_exp(const vf_type& d) {
                ud_t t;
                t._d = d;
                return (t._u >> bits) & e_mask;
            }

            static
            vi_type extract_high_word(const vf_type& d) {
                ud_t t;
                t._d = d;
                return vi_type(t._u >>32);
            }

            static
            vi_type extract_low_word(const vf_type& d) {
                ud_t t;
                t._d = d;
                return vi_type(t._u);
            }

            static
            void extract_words(vi_type& low_word, vi_type& high_word,
                               const vf_type& d) {
                ud_t t;
                t._d = d;
                low_word= vi_type(t._u);
                high_word= vi_type(t._u >>32);
            }

            static
            vf_type insert_high_word(const vf_type& d,
                                     const vi_type& w) {
                ud_t t;
                t._d = d;
                uint64_t hh= w;
                t._u = (t._u & 0xFFFFFFFF) | (hh << 32);
                return t._d;
            }

            static
            vf_type insert_low_word(const vf_type& d,
                                    const vi_type& w) {
                ud_t t;
                t._d = d;
                t._u = (t._u & 0xFFFFFFFF00000000ULL) | w;
                return t._d;
            }

            static
            vf_type combine_words(const vi_type& l,
                                  const vi_type& h) {
                vf_type t(insert_low_word(0.0, l));
                return insert_high_word(t, h);
            }

            static
            vf_type cvt_i_to_f(const vi_type& i) {
                return vf_type(i);
            }
            // including rounding to nearest.
            static
            vi_type cvt_f_to_i(const vf_type& f) {
                return f < 0 ?
                           (vi_type)(f - 0.5) :
                    (vi_type)(f + 0.5);
            }
            // including rounding towards zero
            static
            vi_type cvt_rz_f_to_i(const vf_type& f) {
                return (vi_type)f;
            }
        };

        template <typename _T>
        struct func_core<double, _T> {
            typedef typename _T::vf_type vf_type;
            typedef typename _T::vi_type vi_type;
            typedef typename _T::vmf_type vmf_type;
            typedef typename _T::vmi_type vmi_type;

            typedef d_real<vf_type> dvf_type;
            typedef t_real<vf_type> tvf_type;
            typedef func_core<double, _T> my_type;

            // argument reduction for all trigonometric
            // functions, reduction by %pi/2, the low bits
            // of multiple of %pi/2 is returned in the
            // second part of the return type
            static std::pair<dvf_type, vi_type>
            native_reduce_trig_arg_k(arg_t<vf_type> x);

            // calculates sin(xh, xl) in [+0, pi/4]
            static
            vf_type
            __sin_k(arg_t<vf_type> xh, arg_t<vf_type> xl);

            // calculates cos(xh, xl) in [+0, pi/4]
            static
            vf_type
            __cos_k(arg_t<vf_type> xh, arg_t<vf_type> xl);

            // calculates tan(xh, xl) in [+0, pi/4]
            static
            vf_type
            __tan_k(arg_t<vf_type> xh, arg_t<vf_type> xl);

            // core sine, cosine calculation
            static
            void
            native_sin_cos_k(arg_t<vf_type> x,
                             vf_type* s, vf_type* c);

            // core tan calculation
            static
            vf_type
            native_tan_k(arg_t<vf_type> x);

            // native atan2 kernel
            static vf_type
            native_atan2_k(arg_t<vf_type> x,
                           arg_t<vf_type> y);

            static
            vf_type
            native_exp_k(arg_t<vf_type> x, bool exp_m1);

            static
            vf_type
            native_exp2_k(arg_t<vf_type> x);

            static
            vf_type
            native_log_k(arg_t<vf_type> x);

            static vf_type
            pow2i(arg_t<vi_type> vi);
            static vf_type
            ldexp(arg_t<vf_type> x,
                  arg_t<vi_type> e);
            static vf_type
            frexp(arg_t<vf_type> x, vi_type* e);

            static vi_type
            ilogbp1(arg_t<vf_type> x);
            static vi_type
            ilogb(arg_t<vf_type> vf);
        };

    } // end math
} // end cftal

template <typename _T>
inline
typename
cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
pow2i(arg_t<vi_type> vi)
{
    vi_type e(vi + vi_type(_T::bias));
    vf_type r(_T::insert_exp(e));
    vmi_type mi;
    vmf_type mf;
    mi= (vi < vi_type(_T::e_min));
    mf= _T::vmi_to_vmf(mi);
    r= _T::sel(mf, vf_type(0.0), r);
    mi= (vi > vi_type(_T::e_max));
    mf= _T::vmi_to_vmf(mi);
    vf_type inf(_T::pinf());
    r= _T::sel(mf, vf_type(inf), r);
    return r;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
ldexp(arg_t<vf_type> x, arg_t<vi_type> n)
{
    vf_type xs=x;
    using fc=func_constants<double>;
    vmf_type is_denom= abs(x) <= fc::max_denormal;
    vi_type eo=vi_type(0);
    // input denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p54), xs);
    vmi_type i_is_denom= _T::vmf_to_vmi(is_denom);
    eo= _T::sel(i_is_denom, vi_type(-54), eo);
    // split mantissa
    vi_type ml, mh;
    _T::extract_words(ml, mh, xs);
    vi_type xe=((mh>>20) & _T::e_mask) + eo;

    // determine the exponent of the result
    // clamp nn to [-4096, 4096]
    vi_type nn= min(vi_type(4096), max(n, vi_type(-4096)));
    vi_type re= xe + nn;

    // 3 cases exist:
    // 0 < re < 0x7ff normal result
    //     re >= 0x7ff inf result (overflow)
    //     re <= 0 subnormal or 0 (underflow)

    // clear exponent bits from mh
    mh &= vi_type(~0x7ff00000);

    // high part of mantissa for normal results:
    vi_type mhn= mh | ((re & vi_type(_T::e_mask)) << 20);
    vf_type r= _T::combine_words(ml, mhn);

    // overflow handling
    vmi_type i_is_inf = re > vi_type(0x7fe);
    vmf_type f_is_inf = _T::vmi_to_vmf(i_is_inf);
    vf_type r_inf = copysign(vf_type(_T::pinf()), x);
    r = _T::sel(f_is_inf, r_inf, r);

    // underflow handling
    vmi_type i_is_near_z = re < vi_type (1);
    if (any_of(i_is_near_z)) {
        // create m*0x1.0p-1022
        vi_type mhu= mh | vi_type(1<<20);
        vf_type r_u= _T::combine_words(ml, mhu);
        // create a scaling factor, but avoid overflows
        vi_type ue= max(vi_type(re + (_T::bias-1)), vi_type(1));
        vf_type s_u= _T::insert_exp(ue);
        r_u *= s_u;
        vmf_type f_is_near_z = _T::vmi_to_vmf(i_is_near_z);
        r = _T::sel(f_is_near_z, r_u, r);
    }
    // handle special cases:
    r = _T::sel(isinf(x) | isnan(x) | (x==vf_type(0.0)),
                x, r);
    return r;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
frexp(arg_t<vf_type> x, vi_type* ve)
{
    vf_type xs=x;
    using fc=func_constants<double>;
    vmf_type is_denom= abs(x) <= fc::max_denormal;

    vi_type eo=vi_type(0);
    // denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p54), xs);
    vmi_type i_is_denom= _T::vmf_to_vmi(is_denom);
    eo= _T::sel(i_is_denom, vi_type(-54), eo);
    // extract mantissa
    vi_type lo_word, hi_word;
    _T::extract_words(lo_word, hi_word, xs);
    // exponent:
    vi_type e=((hi_word >> 20) & _T::e_mask) + eo;
    // insert exponent
    hi_word = (hi_word & vi_type(0x800fffff)) | vi_type(0x3fe00000);
    // combine low and high word
    vf_type frc(_T::combine_words(lo_word, hi_word));
    // inf, nan, zero
    vmf_type f_inz=isinf(x) | isnan(x) | (x==vf_type(0.0));
    frc = _T::sel(f_inz, x, frc);
    if (ve != nullptr) {
        // remove bias from e
        vmi_type i_inz=_T::vmf_to_vmi(f_inz);
        e -= vi_type(_T::bias-1);
        e= _T::sel(i_inz, vi_type(0), e);
        *ve= e;
    }
    return frc;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vi_type
cftal::math::func_core<double, _T>::
ilogbp1(arg_t<vf_type> x)
{
    vf_type xs=x;
    using fc=func_constants<double>;
    vmf_type is_denom= abs(x) <= fc::max_denormal;
    vi_type eo=vi_type(0);
    // denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p54), xs);
    vmi_type i_is_denom= _T::vmf_to_vmi(is_denom);
    eo= _T::sel(i_is_denom, vi_type(-54), eo);
    // reinterpret as integer
    vi_type hi_word(_T::extract_high_word(xs));
    // exponent:
    vi_type e=((hi_word >> 20) & _T::e_mask) + eo - vi_type(_T::bias-1);
    return e;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vi_type
cftal::math::func_core<double, _T>::
ilogb(arg_t<vf_type> d)
{
    vi_type e(ilogbp1(d) - vi_type(1));
    vmf_type mf= d == 0.0;
    vmi_type mi= _T::vmf_to_vmi(mf);
    e = _T::sel(mi, vi_type(FP_ILOGB0), e);
    mf = isinf(d);
    mi = _T::vmf_to_vmi(mf);
    e = _T::sel(mi, vi_type(0x7fffffff), e);
    mf = isnan(d);
    mi = _T::vmf_to_vmi(mf);
    e = _T::sel(mi, vi_type(FP_ILOGBNAN), e);
    return e;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
native_exp_k(arg_t<vf_type> xc, bool exp_m1)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    vf_type x=xc;
    vf_type kf = rint(vf_type(x * ctbl::m_1_ln2.h()));
    vf_type hi = x - kf * ctbl::m_ln2_cw[0];
    vf_type lo = kf * ctbl::m_ln2_cw[1];
    vf_type xr = hi - lo;
    vi_type k= _T::cvt_f_to_i(kf);

    vf_type y;
    if (exp_m1 == false) {
        // coefficients for native_exp generated by sollya
        // x^10
        const vf_type exp_c10=0x1.6373fdc720fep-25;  // 0x3e66373fdc720fe0
        // x^8
        const vf_type exp_c8=-0x1.bbd415c0fa28dp-20;  // 0xbebbbd415c0fa28d
        // x^6
        const vf_type exp_c6=0x1.1566aaef64906p-14;  // 0x3f11566aaef64906
        // x^4
        const vf_type exp_c4=-0x1.6c16c16beabf5p-9;  // 0xbf66c16c16beabf5
        // x^2
        const vf_type exp_c2=0x1.555555555553dp-3;  // 0x3fc555555555553d
        vf_type xx = xr*xr;
        vf_type c = xr - xx*impl::poly(xx,
                                       exp_c10,
                                       exp_c8,
                                       exp_c6,
                                       exp_c4,
                                       exp_c2);
        y = (xr*c/(2-c) - lo + hi);
        y += 1.0;
        // y = ldexp(y, k);
        vi_type e_two_pow_k=_T::sel(k < vi_type(-1021),
                                    vi_type((_T::bias+1000)+k),
                                    vi_type(_T::bias+k));
        vf_type two_pow_k= _T::insert_exp(e_two_pow_k);
        // kf == 1024 or kf>=-1021
        vf_type yt= _T::sel(kf == vf_type(1024),
                            y * 2.0 * 0x1p1023,
                            y*two_pow_k);
        y = _T::sel(kf < vf_type(-1021),
                    y*two_pow_k*0x1p-1000, yt);
    } else {
        // vf_type e= xr - y;
        vf_type cr = (hi-xr)-lo;
        // coefficients for native_expm1 generated by sollya
        // x^10
        const vf_type expm1_c10=-0x1.afde65291a16bp-23; // 0xbe8afde65291a16b
        // x^8
        const vf_type expm1_c8=0x1.0cfcaba045368p-18; // 0x3ed0cfcaba045368
        // x^6
        const vf_type expm1_c6=-0x1.4ce199ed151c4p-14; // 0xbf14ce199ed151c4
        // x^4
        const vf_type expm1_c4=0x1.a01a019fe6105p-10; // 0x3f5a01a019fe6105
        // x^2
        const vf_type expm1_c2=-0x1.11111111110f5p-5; // 0xbfa11111111110f5
        /* x is now in primary range */
        vf_type hfx = 0.5*xr;
        vf_type hxs = xr*hfx;
        vf_type r1 = 1.0+hxs*impl::poly(hxs,
                                        expm1_c10,
                                        expm1_c8,
                                        expm1_c6,
                                        expm1_c4,
                                        expm1_c2);
        vf_type tt  = 3.0-r1*hfx;
        vf_type e  = hxs*((r1-tt)/(6.0 - xr*tt));
        // if (k == 0)   /* c is 0 */
        //      return x - (x*e-hxs);
        e  = xr*(e-cr) - cr;
        e -= hxs;
        vi_type t= _T::bias - k;
        vf_type two_pow_minus_k=_T::insert_exp(t);
        // xr - e = y --> xr -y = e
        t = _T::bias + k;
        vf_type two_pow_k=_T::insert_exp(t);
        // default cases:
        vf_type ym = _T::sel(kf < vf_type(20),
                             (xr - e + (1.0 - two_pow_minus_k))*two_pow_k,
                             (xr - (e+two_pow_minus_k)+1.0)*two_pow_k);
        // k < 0 || k > 56
        vf_type yt= xr - e  + 1.0;
        yt= _T::sel(kf == vf_type(1024),
                    yt * 2.0 *0x1p1023,
                    yt * two_pow_k);
        yt -= 1.0;
        ym = _T::sel((kf < vf_type(0)) | (kf>vf_type(56)), yt, ym);
        // k == 1
        yt = _T::sel(xr < -0.25, -2.0*(e-(xr+0.5)),1.0+2.0*(xr-e));
        ym = _T::sel(kf == vf_type(1.0), yt, ym);
        // k == -1
        yt = 0.5 *(xr-e) - 0.5;
        ym = _T::sel(kf == vf_type(-1.0), yt, ym);
        // k == 0
        ym = _T::sel(kf == vf_type(0.0), xr-e, ym);
        // x small
        // ym = _T::sel(abs(x) < 0x1p-54, x, ym);
        y = ym;
    }
    return y;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
native_exp2_k(arg_t<vf_type> x)
{
    vf_type kf= rint(vf_type(x));
    vf_type xr = x - kf;
    vi_type k = _T::cvt_f_to_i(kf);
    // using ctbl = impl::d_real_constants<d_real<double>, double>;
    // coefficients for native_exp2
    // x^12
    const vf_type exp2_c12=-0x1.f6550add75802p-36;  // 0xbdbf6550add75802
    // x^11
    const vf_type exp2_c11=0x1.bdfbcf2999f1p-36;  // 0x3dbbdfbcf2999f10
    // x^10
    const vf_type exp2_c10=0x1.01c3a8ab00ccap-31;  // 0x3e001c3a8ab00cca
    // x^9
    const vf_type exp2_c9=0x1.e4d3fcb9d39a5p-28;  // 0x3e3e4d3fcb9d39a5
    // x^8
    const vf_type exp2_c8=0x1.b51ce204b5f0ap-24;  // 0x3e7b51ce204b5f0a
    // x^7
    const vf_type exp2_c7=0x1.62c020e78cce5p-20;  // 0x3eb62c020e78cce5
    // x^6
    const vf_type exp2_c6=0x1.ffcbfeda6320ap-17;  // 0x3eeffcbfeda6320a
    // x^5
    const vf_type exp2_c5=0x1.430912f8c280bp-13;  // 0x3f2430912f8c280b
    // x^4
    const vf_type exp2_c4=0x1.5d87fe7848d65p-10;  // 0x3f55d87fe7848d65
    // x^3
    const vf_type exp2_c3=0x1.3b2ab6fba4d47p-7;  // 0x3f83b2ab6fba4d47
    // x^2
    const vf_type exp2_c2=0x1.c6b08d704a236p-5;  // 0x3fac6b08d704a236
    // x^1
    const vf_type exp2_c1=0x1.ebfbdff82c58fp-3;  // 0x3fcebfbdff82c58f
    // x^0
    const vf_type exp2_c0=0x1.62e42fefa39efp-1;  // 0x3fe62e42fefa39ef
    vf_type y=impl::poly(xr,
                         exp2_c12,
                         exp2_c11,
                         exp2_c10,
                         exp2_c9,
                         exp2_c8,
                         exp2_c7,
                         exp2_c6,
                         exp2_c5,
                         exp2_c4,
                         exp2_c3,
                         exp2_c2,
                         exp2_c1,
                         exp2_c0);
    y *= xr;
    y += 1.0;
    // y=ldexp(y, k);
    vi_type e_two_pow_k=_T::sel(k < vi_type(-1021),
                                vi_type((_T::bias+1000)+k),
                                vi_type(_T::bias+k));
    vf_type two_pow_k= _T::insert_exp(e_two_pow_k);
    // kf == 1024 or kf>=-1021
    vf_type yt= _T::sel(kf == vf_type(1024),
                        y * 2.0 * 0x1p1023,
                        y*two_pow_k);
    y = _T::sel(kf < vf_type(-1021),
                y*two_pow_k*0x1p-1000, yt);

    return y;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
native_log_k(arg_t<vf_type> xc)
{
/* origin: FreeBSD /usr/src/lib/msun/src/e_log.c */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
/* log(x)
 * Return the logarithm of x
 *
 * Method :
 *   1. Argument Reduction: find k and f such that
 *                      x = 2^k * (1+f),
 *         where  sqrt(2)/2 < 1+f < sqrt(2) .
 *
 *   2. Approximation of log(1+f).
 *      Let s = f/(2+f) ; based on log(1+f) = log(1+s) - log(1-s)
 *               = 2s + 2/3 s**3 + 2/5 s**5 + .....,
 *               = 2s + s*R
 *      We use a special Remez algorithm on [0,0.1716] to generate
 *      a polynomial of degree 14 to approximate R The maximum error
 *      of this polynomial approximation is bounded by 2**-58.45. In
 *      other words,
 *                      2      4      6      8      10      12      14
 *          R(z) ~ Lg1*s +Lg2*s +Lg3*s +Lg4*s +Lg5*s  +Lg6*s  +Lg7*s
 *      (the values of Lg1 to Lg7 are listed in the program)
 *      and
 *          |      2          14          |     -58.45
 *          | Lg1*s +...+Lg7*s    -  R(z) | <= 2
 *          |                             |
 *      Note that 2s = f - s*f = f - hfsq + s*hfsq, where hfsq = f*f/2.
 *      In order to guarantee error in log below 1ulp, we compute log
 *      by
 *              log(1+f) = f - s*(f - R)        (if f is not too large)
 *              log(1+f) = f - (hfsq - s*(hfsq+R)).     (better accuracy)
 *
 *      3. Finally,  log(x) = k*ln2 + log(1+f).
 *                          = k*ln2_hi+(f-(hfsq-(s*(hfsq+R)+k*ln2_lo)))
 *         Here ln2 is split into two floating point number:
 *                      ln2_hi + ln2_lo,
 *         where n*ln2_hi is always exact for |n| < 2000.
 *
 * Special cases:
 *      log(x) is NaN with signal if x < 0 (including -INF) ;
 *      log(+INF) is +INF; log(0) is -INF with signal;
 *      log(NaN) is that NaN with no signal.
 *
 * Accuracy:
 *      according to an error analysis, the error is always less than
 *      1 ulp (unit in the last place).
 *
 * Constants:
 * The hexadecimal values are the intended ones for the following
 * constants. The decimal values may be used, provided that the
 * compiler will convert from decimal to binary accurately enough
 * to produce the hexadecimal values shown.
 */
    // const vf_type ln2_hi = 6.93147180369123816490e-01;  /* 3fe62e42 fee00000 */
    // const vf_type ln2_lo = 1.90821492927058770002e-10;  /* 3dea39ef 35793c76 */
    // const vf_type Lg1 = 6.666666666666735130e-01;  /* 3FE55555 55555593 */
    // const vf_type Lg2 = 3.999999999940941908e-01;  /* 3FD99999 9997FA04 */
    // const vf_type Lg3 = 2.857142874366239149e-01;  /* 3FD24924 94229359 */
    // const vf_type Lg4 = 2.222219843214978396e-01;  /* 3FCC71C5 1D8E78AF */
    // const vf_type Lg5 = 1.818357216161805012e-01;  /* 3FC74664 96CB03DE */
    // const vf_type Lg6 = 1.531383769920937332e-01;  /* 3FC39A09 D078C69F */
    // const vf_type Lg7 = 1.479819860511658591e-01;  /* 3FC2F112 DF3E5244 */

    // coefficients for native_log
    // x^14
    const vf_type log_c14=0x1.2f023f03311eep-3;  // 0x3fc2f023f03311ee
    // x^12
    const vf_type log_c12=0x1.39a20d7de709dp-3;  // 0x3fc39a20d7de709d
    // x^10
    const vf_type log_c10=0x1.74663b910e2ddp-3;  // 0x3fc74663b910e2dd
    // x^8
    const vf_type log_c8=0x1.c71c521a6f8abp-3;  // 0x3fcc71c521a6f8ab
    // x^6
    const vf_type log_c6=0x1.24924941dae8ap-2;  // 0x3fd24924941dae8a
    // x^4
    const vf_type log_c4=0x1.999999997ff68p-2;  // 0x3fd999999997ff68
    // x^2
    const vf_type log_c2=0x1.5555555555592p-1;  // 0x3fe5555555555592

    using fc = func_constants<double>;
    vmf_type is_denom=xc <= fc::max_denormal;
    vf_type x=_T::sel(is_denom, xc*0x1p54, xc);
    vi_type k=_T::sel(_T::vmf_to_vmi(is_denom), vi_type(-54), vi_type(0));
    vi_type lx, hx;
    _T::extract_words(lx, hx, x);
    /* reduce x into [sqrt(2)/2, sqrt(2)] */
    hx += 0x3ff00000 - 0x3fe6a09e;
    k += (hx>>20) - 0x3ff;
    hx = (hx&0x000fffff) + 0x3fe6a09e;
    vf_type xr = _T::combine_words(lx, hx);

    vf_type f = xr - 1.0;
    vf_type hfsq = 0.5*f*f;
    vf_type s = f/(2.0+f);
    vf_type z = s*s;
#if 1
    vf_type R = z*impl::poly(z,
                             log_c14,
                             log_c12,
                             log_c10,
                             log_c8,
                             log_c6,
                             log_c4,
                             log_c2);
#else
    // vf_type t1 = w*(Lg2+w*(Lg4+w*Lg6));
    // vf_type t2 = z*(Lg1+w*(Lg3+w*(Lg5+w*Lg7)));
    vf_type w = z*z;
    vf_type t1 = w*impl::poly(w,
                              log_c12,
                              log_c8,
                              log_c4);
    vf_type t2 = z*impl::poly(w,
                              log_c14,
                              log_c10,
                              log_c6,
                              log_c2);
    vf_type R = t2 + t1;
#endif
    vf_type dk = _T::cvt_i_to_f(k);
    using ctbl=impl::d_real_constants<d_real<double>, double>;
    vf_type log_x=s*(hfsq+R) +
                  dk*ctbl::m_ln2_cw[1] - hfsq +
                  f + dk*ctbl::m_ln2_cw[0];
    return log_x;
}


template <typename _T>
inline
std::pair<typename cftal::math::func_core<double, _T>::dvf_type,
          typename cftal::math::func_core<double, _T>::vi_type>
cftal::math::func_core<double, _T>::
native_reduce_trig_arg_k(arg_t<vf_type> x)
{
    using ctbl=impl::d_real_constants<d_real<double>, double>;
    using d_ops=cftal::impl::d_real_ops<vf_type, d_real_traits<vf_type>::fma>;
    vf_type y0, y1;
    vf_type fn= rint(vf_type(x* ctbl::m_2_pi.h()));
#if 0
    y0= d_ops::two_diff((x - fn* ctbl::m_pi_2_cw[0]) - fn*ctbl::m_pi_2_cw[1],
                        fn*ctbl::m_pi_2_cw[2],
                        y1);
    dvf_type d0(y0, y1);
#else
    using d_ops=cftal::impl::d_real_ops<vf_type, d_real_traits<vf_type>::fma>;
    y0= d_ops::two_diff(x, fn* ctbl::m_pi_2_cw[0], y1);
    dvf_type d0(y0, y1);
    d0= d_ops::sub(d0, fn*ctbl::m_pi_2_cw[1]);
    d0= d_ops::sub(d0, fn*ctbl::m_pi_2_cw[2]);
#endif
    vi_type q(_T::cvt_f_to_i(fn));

    const double large_arg=0x1p20;
    vmf_type v_large_arg= vf_type(large_arg) < abs(x);
    if (any_of(v_large_arg)) {
        // reduce the large arguments
        constexpr std::size_t N=_T::NVF();
        constexpr std::size_t NI=_T::NVI();
        struct alignas(N*sizeof(double)) v_d {
            double _sc[N];
        } tf, d0_l, d0_h;
        struct alignas(NI*sizeof(int)) v_i {
            int32_t _sc[NI];
        } ti;
        mem<vf_type>::store(tf._sc, x);
        mem<vi_type>::store(ti._sc, q);
        mem<vf_type>::store(d0_l._sc, d0.l());
        mem<vf_type>::store(d0_h._sc, d0.h());
        for (std::size_t i=0; i<N; ++i) {
            if (large_arg < std::fabs(tf._sc[i])) {
                double y[2];
                ti._sc[i]=impl::__ieee754_rem_pio2(tf._sc[i], y);
                d0_l._sc[i]= y[1];
                d0_h._sc[i]= y[0];
            }
        }
        vf_type rh(mem<vf_type>::load(d0_h._sc, N));
        vf_type rl(mem<vf_type>::load(d0_l._sc, N));
        d0 = dvf_type(rh, rl);
        q = mem<vi_type>::load(ti._sc, NI);
    }
    return std::make_pair(d0, q);
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
__sin_k(arg_t<vf_type> xh, arg_t<vf_type> xl)
{
/* __sin( x, y, iy)
 * kernel sin function on ~[-pi/4, pi/4] (except on -0), pi/4 ~ 0.7854
 * Input x is assumed to be bounded by ~pi/4 in magnitude.
 * Input y is the tail of x.
 *
 * Algorithm
 *      1. Since sin(-x) = -sin(x), we need only to consider positive x.
 *      2. Callers must return sin(-0) = -0 without calling here since our
 *         odd polynomial is not evaluated in a way that preserves -0.
 *         Callers may do the optimization sin(x) ~ x for tiny x.
 *      3. sin(x) is approximated by a polynomial of degree 13 on
 *         [0,pi/4]
 *                               3            13
 *              sin(x) ~ x + S1*x + ... + S6*x
 *         where
 *
 *      |sin(x)         2     4     6     8     10     12  |     -58
 *      |----- - (1+S1*x +S2*x +S3*x +S4*x +S5*x  +S6*x   )| <= 2
 *      |  x                                               |
 *
 *      4. sin(x+y) = sin(x) + sin'(x')*y
 *                  ~ sin(x) + (1-x*x/2)*y
 *         For better accuracy, let
 *                   3      2      2      2      2
 *              r = x *(S2+x *(S3+x *(S4+x *(S5+x *S6))))
 *         then                   3    2
 *              sin(x) = x + (S1*x + (x *(r-y/2)+y))
 */
    // coefficients for native_sin generated by sollya
    // x^12
    const vf_type sin_c12=0x1.5d8e4fd037141p-33;  // 0x3de5d8e4fd037141
    // x^10
    const vf_type sin_c10=-0x1.ae5e54bfd5648p-26;  // 0xbe5ae5e54bfd5648
    // x^8
    const vf_type sin_c8=0x1.71de355f53fb5p-19;  // 0x3ec71de355f53fb5
    // x^6
    const vf_type sin_c6=-0x1.a01a019bf2621p-13;  // 0xbf2a01a019bf2621
    // x^4
    const vf_type sin_c4=0x1.111111110f75ep-7;  // 0x3f8111111110f75e
    // x^2
    const vf_type sin_c2=-0x1.5555555555548p-3;  // 0xbfc5555555555548

    vf_type z = xh*xh;
    vf_type w = z*z;
    vf_type r = sin_c4 + z*(sin_c6 + z*sin_c8) + z*w*(sin_c10 + z*sin_c12);
    vf_type v = z*xh;
    return xh - ((z*(0.5*xl - v*r) - xl) - v*sin_c2);
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
__cos_k(arg_t<vf_type> xh, arg_t<vf_type> xl)
{
/*
 * __cos( x,  y )
 * kernel cos function on [-pi/4, pi/4], pi/4 ~ 0.785398164
 * Input x is assumed to be bounded by ~pi/4 in magnitude.
 * Input y is the tail of x.
 *
 * Algorithm
 *      1. Since cos(-x) = cos(x), we need only to consider positive x.
 *      2. if x < 2^-27 (hx<0x3e400000 0), return 1 with inexact if x!=0.
 *      3. cos(x) is approximated by a polynomial of degree 14 on
 *         [0,pi/4]
 *                                       4            14
 *              cos(x) ~ 1 - x*x/2 + C1*x + ... + C6*x
 *         where the remez error is
 *
 *      |              2     4     6     8     10    12     14 |     -58
 *      |cos(x)-(1-.5*x +C1*x +C2*x +C3*x +C4*x +C5*x  +C6*x  )| <= 2
 *      |                                                      |
 *
 *                     4     6     8     10    12     14
 *      4. let r = C1*x +C2*x +C3*x +C4*x +C5*x  +C6*x  , then
 *             cos(x) ~ 1 - x*x/2 + r
 *         since cos(x+y) ~ cos(x) - sin(x)*y
 *                        ~ cos(x) - x*y,
 *         a correction term is necessary in cos(x) and hence
 *              cos(x+y) = 1 - (x*x/2 - (r - x*y))
 *         For better accuracy, rearrange to
 *              cos(x+y) ~ w + (tmp + (r-x*y))
 *         where w = 1 - x*x/2 and tmp is a tiny correction term
 *         (1 - x*x/2 == w + tmp exactly in infinite precision).
 *         The exactness of w + tmp in infinite precision depends on w
 *         and tmp having the same precision as x.  If they have extra
 *         precision due to compiler bugs, then the extra precision is
 *         only good provided it is retained in all terms of the final
 *         expression for cos().  Retention happens in all cases tested
 *         under FreeBSD, so don't pessimize things by forcibly clipping
 *         any extra precision in w.
 */
    // coefficients for native_cos generated by sollya
    // x^14
    const vf_type cos_c14=-0x1.8f9f637c83b98p-37;  // 0xbda8f9f637c83b98
    // x^12
    const vf_type cos_c12=0x1.1ee9ccb7c6dbap-29;  // 0x3e21ee9ccb7c6dba
    // x^10
    const vf_type cos_c10=-0x1.27e4f7d8e4bf2p-22;  // 0xbe927e4f7d8e4bf2
    // x^8
    const vf_type cos_c8=0x1.a01a019c687a8p-16;  // 0x3efa01a019c687a8
    // x^6
    const vf_type cos_c6=-0x1.6c16c16c14e49p-10;  // 0xbf56c16c16c14e49
    // x^4
    const vf_type cos_c4=0x1.555555555554ap-5;  // 0x3fa555555555554a

    vf_type z  = xh*xh;
    vf_type w  = z*z;
    vf_type r  = z*(cos_c4+z*(cos_c6+z*cos_c8)) +
                 w*w*(cos_c10+z*(cos_c12+z*cos_c14));
    vf_type hz = 0.5*z;
    w  = 1.0-hz;
    return w + (((1.0-w)-hz) + (z*r-xh*xl));
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
__tan_k(arg_t<vf_type> xh, arg_t<vf_type> xl)
{
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
/* tan(x)
 * Return tangent function of x.
 *
 * kernel function:
 *      __tan           ... tangent function on [-pi/4,pi/4]
 *      __rem_pio2      ... argument reduction routine
 *
 * Method.
 *      Let S,C and T denote the sin, cos and tan respectively on
 *      [-PI/4, +PI/4]. Reduce the argument x to y1+y2 = x-k*pi/2
 *      in [-pi/4 , +pi/4], and let n = k mod 4.
 *      We have
 *
 *          n        sin(x)      cos(x)        tan(x)
 *     ----------------------------------------------------------
 *          0          S           C             T
 *          1          C          -S            -1/T
 *          2         -S          -C             T
 *          3         -C           S            -1/T
 *     ----------------------------------------------------------
 *
 * Special cases:
 *      Let trig be any of sin, cos, or tan.
 *      trig(+-INF)  is NaN, with signals;
 *      trig(NaN)    is that NaN;
 *
 * Accuracy:
 *      TRIG(x) returns trig(x) nearly rounded
 */
/* __tan( x, y, k )
 * kernel tan function on ~[-pi/4, pi/4] (except on -0), pi/4 ~ 0.7854
 * Input x is assumed to be bounded by ~pi/4 in magnitude.
 * Input y is the tail of x.
 * Input odd indicates whether tan (if odd = 0) or -1/tan (if odd = 1) is returned.
 *
 * Algorithm
 *      1. Since tan(-x) = -tan(x), we need only to consider positive x.
 *      2. Callers must return tan(-0) = -0 without calling here since our
 *         odd polynomial is not evaluated in a way that preserves -0.
 *         Callers may do the optimization tan(x) ~ x for tiny x.
 *      3. tan(x) is approximated by a odd polynomial of degree 27 on
 *         [0,0.67434]
 *                               3             27
 *              tan(x) ~ x + T1*x + ... + T13*x
 *         where
 *
 *              |tan(x)         2     4            26   |     -59.2
 *              |----- - (1+T1*x +T2*x +.... +T13*x    )| <= 2
 *              |  x                                    |
 *
 *         Note: tan(x+y) = tan(x) + tan'(x)*y
 *                        ~ tan(x) + (1+x*x)*y
 *         Therefore, for better accuracy in computing tan(x+y), let
 *                   3      2      2       2       2
 *              r = x *(T2+x *(T3+x *(...+x *(T12+x *T13))))
 *         then
 *                                  3    2
 *              tan(x+y) = x + (T1*x + (x *(r+y)+y))
 *
 *      4. For x in [0.67434,pi/4],  let y = pi/4 - x, then
 *              tan(x) = tan(pi/4-y) = (1-tan(y))/(1+tan(y))
 *                     = 1 - 2*(tan(y) - (tan(y)^2)/(1+tan(y)))
 */
    // coefficients for native_tan generated by sollya
    // x^28
    const vf_type tan_c28=0x1.b383ec756e9bcp-17;  // 0x3eeb383ec756e9bc
    // x^26
    const vf_type tan_c26=-0x1.0130db8b17991p-16;  // 0xbef0130db8b17991
    // x^24
    const vf_type tan_c24=0x1.4eb08dc3e9d94p-15;  // 0x3f04eb08dc3e9d94
    // x^22
    const vf_type tan_c22=0x1.7bfcf76b92ba3p-16;  // 0x3ef7bfcf76b92ba3
    // x^20
    const vf_type tan_c20=0x1.b758249ad8024p-14;  // 0x3f1b758249ad8024
    // x^18
    const vf_type tan_c18=0x1.f00c849ed9699p-13;  // 0x3f2f00c849ed9699
    // x^16
    const vf_type tan_c16=0x1.35aa5e81e4938p-11;  // 0x3f435aa5e81e4938
    // x^14
    const vf_type tan_c14=0x1.7d9c7ba6c5b48p-10;  // 0x3f57d9c7ba6c5b48
    // x^12
    const vf_type tan_c12=0x1.d6d4390f4ba73p-9;  // 0x3f6d6d4390f4ba73
    // x^10
    const vf_type tan_c10=0x1.226e334845632p-7;  // 0x3f8226e334845632
    // x^8
    const vf_type tan_c8=0x1.664f48909285p-6;  // 0x3f9664f489092850
    // x^6
    const vf_type tan_c6=0x1.ba1ba1b9e5724p-5;  // 0x3faba1ba1b9e5724
    // x^4
    const vf_type tan_c4=0x1.111111111146cp-3;  // 0x3fc111111111146c
    // x^2
    const vf_type tan_c2=0x1.5555555555553p-2;  // 0x3fd5555555555553

    // make xrh positive
    vf_type sgn_x = copysign(vf_type(0.5), xh);
    vmf_type x_is_neg = sgn_x < 0.0;
    vf_type xrh = _T::sel(x_is_neg, -xh, xh);
    vf_type xrl = _T::sel(x_is_neg, -xl, xl);

    using ctbl = impl::d_real_constants<d_real<double>, double>;
    const vf_type large_arg=0.69;
    vmf_type x_large= xrh > large_arg;
    // for xh in [pi/8, pi/4] we replace xh with pi/4 - xh
    xrh = _T::sel(x_large,
                  (ctbl::m_pi_4.h() - xrh) + (ctbl::m_pi_4.l() - xrl) , xrh);
    xrl = _T::sel(x_large, 0, xrl);
    vf_type z = xrh*xrh;
#if 1
    vf_type s= z * xrh;
    vf_type r = s* impl::poly(z,
                              tan_c28,
                              tan_c26,
                              tan_c24,
                              tan_c22,
                              tan_c20,
                              tan_c18,
                              tan_c16,
                              tan_c14,
                              tan_c12,
                              tan_c10,
                              tan_c8,
                              tan_c6,
                              tan_c4);
    r = tan_c2*s + (z *(r+xrl)+ xrl);
    vf_type txy= xrh + r;

    // tan(x+y) = (tan x + tan y)/(1 - tan(x) * tan(y))
    // tan(x-y) = (tan x - tan y)/(1 + tan(x) * tan(y))
    // because xr = pi/4-x --> tan(pi/4) = 1
    // tan(pi/4-x) = (1- tan(x))/(1 + tan(x))
    //             = 1 - 2*(tan(x) - (tan(x)^2)/(1+tan(x)))
    // using d_ops=cftal::impl::d_real_ops<vf_type, d_real_traits<vf_type>::fma>;
    vf_type txyl = 1.0 - 2*(xrh + (r - (txy*txy)/(1.0 +txy)));
    txy = _T::sel(x_large, txyl, txy);
    // restore the sign
    txy = copysign(txy, sgn_x);
    txy = _T::sel(abs(xh) < 0x1p-26, xh, txy);
    return txy;
#else
    /*
     * Break x^5*(T[1]+x^2*T[2]+...) into
     * x^5(T[1]+x^4*T[3]+...+x^20*T[11]) +
     * x^5(x^2*(T[2]+x^4*T[4]+...+x^22*[T12]))
     */
    static const double T[] = {
        3.33333333333334091986e-01, /* 3FD55555, 55555563 */
        1.33333333333201242699e-01, /* 3FC11111, 1110FE7A */
        5.39682539762260521377e-02, /* 3FABA1BA, 1BB341FE */
        2.18694882948595424599e-02, /* 3F9664F4, 8406D637 */
        8.86323982359930005737e-03, /* 3F8226E3, E96E8493 */
        3.59207910759131235356e-03, /* 3F6D6D22, C9560328 */
        1.45620945432529025516e-03, /* 3F57DBC8, FEE08315 */
        5.88041240820264096874e-04, /* 3F4344D8, F2F26501 */
        2.46463134818469906812e-04, /* 3F3026F7, 1A8D1068 */
        7.81794442939557092300e-05, /* 3F147E88, A03792A6 */
        7.14072491382608190305e-05, /* 3F12B80F, 32F0A7E9 */
        -1.85586374855275456654e-05, /* BEF375CB, DB605373 */
        2.59073051863633712884e-05, /* 3EFB2A70, 74BF7AD4 */
    };

    vf_type r = T[1] + w*(T[3] + w*(T[5] + w*(T[7] + w*(T[9] + w*T[11]))));
    vf_type v = z*(T[2] + w*(T[4] + w*(T[6] + w*(T[8] + w*(T[10] + w*T[12])))));
    vf_type s = z * xrh;
    r = xrl + z*(s*(r + v) + xrl) + s*T[0];
    w = xrh + r;

    vf_type sl=1.0;
    vf_type vl=sl - 2.0 * (xrh + (r - w*w/(w + s)));
    vl = _T::sel(xh <0, -vl, v);

    w = _T::sel(x_large, vl, w);
    return w;

#endif
}

template <typename _T>
__attribute__((flatten))
void
cftal::math::func_core<double, _T>::
native_sin_cos_k(arg_t<vf_type> xc, vf_type* ps, vf_type* pc)
{
    std::pair<dvf_type, vi_type> rq(
        native_reduce_trig_arg_k(xc));
    const dvf_type& x= rq.first;
    const vi_type& q= rq.second;

    vf_type s = __sin_k(x.h(), x.l());
    vf_type c= __cos_k(x.h(), x.l());

    vmi_type q_and_2(vi_type(q & vi_type(2))==vi_type(2));
    vmf_type q_and_2_f(_T::vmi_to_vmf(q_and_2));
    vmi_type q_and_1(vi_type(q & vi_type(1))==vi_type(1));
    vmf_type q_and_1_f(_T::vmi_to_vmf(q_and_1));

    // swap sin/cos if q & 1
    vf_type rs(_T::sel(q_and_1_f, c, s));
    vf_type rc(_T::sel(q_and_1_f, s, c));
    // swap signs
    if (ps != nullptr) {
        vf_type fs = _T::sel(q_and_2_f, vf_type(-1.0), vf_type(1.0));
        rs *= fs;
        *ps = rs;
    }
    if (pc != nullptr) {
        vmf_type mt = q_and_2_f ^ q_and_1_f;
        vf_type fc =  _T::sel(mt, vf_type(-1.0), vf_type(1.0));
        rc *= fc;
        *pc= rc;
    }
}

template <typename _T>
__attribute__((flatten))
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
native_tan_k(arg_t<vf_type> xc)
{
    std::pair<dvf_type, vi_type> rq(
        native_reduce_trig_arg_k(xc));
    const dvf_type& x= rq.first;
    const vi_type& q= rq.second;

    // using ctbl=impl::d_real_constants<d_real<double>, double>;
    using d_ops=cftal::impl::d_real_ops<vf_type, d_real_traits<vf_type>::fma>;
    vf_type t = __tan_k(x.h(), x.l());
    vf_type m_inv_t= d_ops::div(vf_type(-1.0), t).h();
    vmi_type q_and_1(vi_type(q & vi_type(1))==vi_type(1));
    vmf_type q_and_1_f(_T::vmi_to_vmf(q_and_1));
    t = _T::sel(q_and_1_f, m_inv_t, t);
    return t;
}


template <typename _T>
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
native_atan2_k(arg_t<vf_type> x, arg_t<vf_type> y)
{
    return 0.0;
}

// Local Variables:
// mode: c++
// end:
#endif
