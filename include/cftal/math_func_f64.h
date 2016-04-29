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
            typedef int64_t vli_type;
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
            vf_type clear_low_word(const vf_type& d) {
                ud_t t;
                t._d = d;
                t._u = (t._u & 0xFFFFFFFF00000000ULL);
                return t._d;
            }

            static
            vli_type as_vli(const vf_type& d) {
                ud_t t;
                t._d =d;
                return t._u;
            }

            static
            vf_type as_vf(const vli_type& u) {
                ud_t t;
                t._u =u;
                return t._d;
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
            using vli_type = typename _T::vli_type;
            using vi2_type = typename _T::vi2_type;
            typedef typename _T::vmf_type vmf_type;
            typedef typename _T::vmi_type vmi_type;
            using vmi2_type = typename _T::vmi2_type;

            typedef d_real<vf_type> dvf_type;
            typedef t_real<vf_type> tvf_type;
            typedef func_core<double, _T> my_type;

            // the exponents are returned in the odd numbered
            // elements of e
            static
            vf_type
            frexp_k(arg_t<vf_type> x, vi2_type* e);

            static
            vf_type
            frexp(arg_t<vf_type> x, vi_type* e);

            // the exponents are returned in the odd numbered
            // elements of e
            static
            vi2_type
            ilogbp1_k(arg_t<vf_type> x);

            static
            vi_type
            ilogbp1(arg_t<vf_type> x);


            static
            vi_type
            ilogb(arg_t<vf_type> vf);

            static
            vf_type
            scale_exp_k(arg_t<vf_type> y, arg_t<vf_type> kf,
                        arg_t<vi2_type> k);

            static
            vf_type
            exp_k_poly(arg_t<vf_type> x);

            static
            vf_type
            exp_k(arg_t<vf_type> x, bool exp_m1);

            static
            vf_type
            exp2_k(arg_t<vf_type> x);

            static
            vf_type
            exp10_k(arg_t<vf_type> x);

            static
            vf_type
            sinh_k(arg_t<vf_type> x);

            static
            vf_type
            cosh_k(arg_t<vf_type> x);

            static
            vf_type
            tanh_k(arg_t<vf_type> x);

            // polynomial approximation of log(1+f) with
            // s = f/(2.0+f) and z = s*s;
            static
            vf_type
            log_k_poly(arg_t<vf_type> z);

            enum log_func {
                c_log_e,
                c_log_2,
                c_log_10
            };

            static
            vf_type
            log_k(arg_t<vf_type> x, log_func f=log_func::c_log_e);

            static
            vf_type
            log1p_k(arg_t<vf_type> x);

            static
            vf_type
            log2_k(arg_t<vf_type> x);

            static
            vf_type
            log10_k(arg_t<vf_type> x);

            // argument reduction for all trigonometric
            // functions, reduction by %pi/2, the low bits
            // of multiple of %pi/2 is returned in the
            // second part of the return type
            static
            std::pair<dvf_type, vi_type>
            reduce_trig_arg_k(arg_t<vf_type> x);

            // calculates sin(xh, xl) in [+0, pi/4]
            static
            vf_type
            __sin_k(arg_t<vf_type> xh, arg_t<vf_type> xl);

            // calculates cos(xh, xl) in [+0, pi/4]
            static
            vf_type
            __cos_k(arg_t<vf_type> xh, arg_t<vf_type> xl);

            // calculates tan(xh, xl) in [+0, pi/4] and
            // returns tan or -1/tan if q & 1
            static
            vf_type
            __tan_k(arg_t<vf_type> xh, arg_t<vf_type> xl,
                    arg_t<vi_type> q);


            // core sine, cosine calculation
            static
            void
            sin_cos_k(arg_t<vf_type> x, vf_type* s, vf_type* c);

            // core tan calculation
            static
            vf_type
            tan_k(arg_t<vf_type> x);

            static
            vf_type
            atan_k(arg_t<vf_type> x);

            static
            vf_type
            atan2_k(arg_t<vf_type> x, arg_t<vf_type> y);

            static
            vf_type
            asin_k_poly(arg_t<vf_type> z2);

            static
            vf_type
            asin_k(arg_t<vf_type> x);

            static
            vf_type
            acos_k(arg_t<vf_type> x);

            static
            vf_type
            asinh_k(arg_t<vf_type> x);

            static
            vf_type
            acosh_k(arg_t<vf_type> x);

            static
            vf_type
            atanh_k(arg_t<vf_type> x);

            static
            vf_type
            hypot_k(arg_t<vf_type> x, arg_t<vf_type> y);

            static
            vf_type
            cbrt_k(arg_t<vf_type> x);

            static vf_type
            pow2i(arg_t<vi_type> vi);

            static
            vf_type
            ldexp_k(arg_t<vf_type> x, arg_t<vi2_type> e);

            static vf_type
            ldexp(arg_t<vf_type> x,
                  arg_t<vi_type> e);

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
ldexp_k(arg_t<vf_type> x, arg_t<vi2_type> n)
{
    vf_type xs=x;
    using fc=func_constants<double>;
    vmf_type is_denom= abs(x) <= fc::max_denormal;
    // input denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p54), xs);
    vmi2_type i_is_denom= _T::vmf_to_vmi2(is_denom);
    vi2_type eo= _T::sel(i_is_denom, vi2_type(-54), vi2_type(0));
    // split mantissa
    vi2_type ml, mh;
    _T::extract_words(ml, mh, xs);
    vi2_type xe=((mh>>20) & _T::e_mask) + eo;

    // determine the exponent of the result
    // clamp nn to [-4096, 4096]
    vi2_type nn= min(vi2_type(4096), max(n, vi2_type(-4096)));
    vi2_type re= xe + nn;

    // 3 cases exist:
    // 0 < re < 0x7ff normal result
    //     re >= 0x7ff inf result (overflow)
    //     re <= 0 subnormal or 0 (underflow)

    // clear exponent bits from mh
    mh &= vi2_type(~0x7ff00000);

    // high part of mantissa for normal results:
    vi2_type mhn= mh | ((re & vi2_type(_T::e_mask)) << 20);
    vf_type r= _T::combine_words(ml, mhn);

    // overflow handling
    vmi2_type i_is_inf = re > vi2_type(0x7fe);
    vmf_type f_is_inf = _T::vmi2_to_vmf(copy_odd_to_even(i_is_inf));
    vf_type r_inf = copysign(vf_type(_T::pinf()), x);
    r = _T::sel(f_is_inf, r_inf, r);

    // underflow handling
    vmi2_type i_is_near_z = copy_odd_to_even(vi2_type(re < vi2_type (1)));
    if (any_of(i_is_near_z)) {
        // create m*0x1.0p-1022
        vi2_type mhu= mh | vi2_type(1<<20);
        vf_type r_u= _T::combine_words(ml, mhu);
        // create a scaling factor, but avoid overflows
        vi2_type ue= max(vi2_type(re + (_T::bias-1)), vi2_type(1));
        vf_type s_u= _T::insert_exp(ue);
        r_u *= s_u;
        vmf_type f_is_near_z = _T::vmi2_to_vmf(i_is_near_z);
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
ldexp(arg_t<vf_type> x, arg_t<vi_type> n)
{
    return ldexp_k(x, _T::vi_to_vi2(n));
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
frexp_k(arg_t<vf_type> x, vi2_type* ve)
{
    vf_type xs=x;
    using fc=func_constants<double>;
    vmf_type is_denom= abs(x) <= fc::max_denormal;
    // denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p54), xs);
    vmi2_type i_is_denom= _T::vmf_to_vmi2(is_denom);
    vi2_type eo= _T::sel(i_is_denom, vi2_type(-54), vi2_type(0));
    // extract mantissa
    vi2_type lo_word, hi_word;
    _T::extract_words(lo_word, hi_word, xs);
    // exponent:
    vi2_type e=((hi_word >> 20) & _T::e_mask) + eo;
    // insert exponent
    hi_word = (hi_word & vi2_type(0x800fffff)) | vi2_type(0x3fe00000);
    // combine low and high word
    vf_type frc(_T::combine_words(lo_word, hi_word));
    // inf, nan, zero
    vmf_type f_inz=isinf(x) | isnan(x) | (x==vf_type(0.0));
    frc = _T::sel(f_inz, x, frc);
    if (ve != nullptr) {
        // remove bias from e
        vmi2_type i_inz=_T::vmf_to_vmi2(f_inz);
        e -= vi2_type(_T::bias-1);
        e= _T::sel(i_inz, vi2_type(0), e);
        *ve= e;
    }
    return frc;
}


template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
frexp(arg_t<vf_type> x, vi_type* ve)
{
    vi2_type e;
    vf_type r=frexp_k(x, &e);
    if (ve) {
        *ve=_T::vi2_odd_to_vi(e);
    }
    return r;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vi2_type
cftal::math::func_core<double, _T>::
ilogbp1_k(arg_t<vf_type> x)
{
    vf_type xs=x;
    using fc=func_constants<double>;
    vmf_type is_denom= abs(x) <= fc::max_denormal;
    // denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p54), xs);
    vmi2_type i_is_denom= _T::vmf_to_vmi2(is_denom);
    vi2_type eo= _T::sel(i_is_denom, vi2_type(-54), vi2_type(0));
    // reinterpret as integer
    vi2_type hi_word, lo_word;
    _T::extract_words(lo_word, hi_word, xs);
    // exponent:
    vi2_type e=((hi_word >> 20) & _T::e_mask) + eo - vi2_type(_T::bias-1);
    return e;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vi_type
cftal::math::func_core<double, _T>::
ilogbp1(arg_t<vf_type> x)
{
    return _T::vi2_odd_to_vi(ilogbp1_k(x));
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vi_type
cftal::math::func_core<double, _T>::
ilogb(arg_t<vf_type> d)
{
    vi2_type e(ilogbp1_k(d) - vi2_type(1));
    vmf_type mf= d == 0.0;
    vmi2_type mi= _T::vmf_to_vmi2(mf);
    e = _T::sel(mi, vi2_type(FP_ILOGB0), e);
    mf = isinf(d);
    mi = _T::vmf_to_vmi2(mf);
    e = _T::sel(mi, vi2_type(0x7fffffff), e);
    mf = isnan(d);
    mi = _T::vmf_to_vmi2(mf);
    e = _T::sel(mi, vi2_type(FP_ILOGBNAN), e);
    return _T::vi2_odd_to_vi(e);
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
scale_exp_k(arg_t<vf_type> ym, arg_t<vf_type> kf, arg_t<vi2_type> k)
{
    vi2_type e_two_pow_k=_T::sel(k < vi2_type(-1021),
                                 vi2_type((_T::bias+1000)+k),
                                 vi2_type(_T::bias+k));
    vf_type two_pow_k= _T::insert_exp(e_two_pow_k);
    // kf == 1024 or kf>=-1021
    vf_type yt= _T::sel(kf == vf_type(1024),
                        ym * 2.0 * 0x1p1023,
                        ym*two_pow_k);
    vf_type y = _T::sel(kf < vf_type(-1021),
                        ym*two_pow_k*0x1p-1000, yt);
    return y;
}


template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
exp_k(arg_t<vf_type> xc, bool exp_m1)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    vf_type x=xc;
    vf_type kf = rint(vf_type(x * ctbl::m_1_ln2.h()));
    vf_type hi = x - kf * ctbl::m_ln2_cw[0];
    vf_type lo = kf * ctbl::m_ln2_cw[1];
    vf_type xr = hi - lo;
    vi_type k= _T::cvt_f_to_i(kf);
    vi2_type k2= _T::vi_to_vi2(k);


    vf_type y;
    if (exp_m1 == false) {
/* exp(x)
 * Returns the exponential of x.
 *
 * Method
 *   1. Argument reduction:
 *      Reduce x to an r so that |r| <= 0.5*ln2 ~ 0.34658.
 *      Given x, find r and integer k such that
 *
 *               x = k*ln2 + r,  |r| <= 0.5*ln2.
 *
 *      Here r will be represented as r = hi-lo for better
 *      accuracy.
 *
 *   2. Approximation of exp(r) by a special rational function on
 *      the interval [0,0.34658]:
 *      Write
 *          R(r**2) = r*(exp(r)+1)/(exp(r)-1) = 2 + r*r/6 - r**4/360 + ...
 *      We use a special Remez algorithm on [0,0.34658] to generate
 *      a polynomial of degree 5 to approximate R. The maximum error
 *      of this polynomial approximation is bounded by 2**-59. In
 *      other words,
 *          R(z) ~ 2.0 + P1*z + P2*z**2 + P3*z**3 + P4*z**4 + P5*z**5
 *      (where z=r*r, and the values of P1 to P5 are listed below)
 *      and
 *          |                  5          |     -59
 *          | 2.0+P1*z+...+P5*z   -  R(z) | <= 2
 *          |                             |
 *      The computation of exp(r) thus becomes
 *                              2*r
 *              exp(r) = 1 + ----------
 *                            R(r) - r
 *                                 r*c(r)
 *                     = 1 + r + ----------- (for better accuracy)
 *                                2 - c(r)
 *      where
 *                              2       4             10
 *              c(r) = r - (P1*r  + P2*r  + ... + P5*r   ).
 *
 *   3. Scale back to obtain exp(x):
 *      From step 1, we have
 *         exp(x) = 2^k * exp(r)
 *
 * Special cases:
 *      exp(INF) is INF, exp(NaN) is NaN;
 *      exp(-INF) is 0, and
 *      for finite argument, only exp(0)=1 is exact.
 *
 * Accuracy:
 *      according to an error analysis, the error is always less than
 *      1 ulp (unit in the last place).
 *
 * Misc. info.
 *      For IEEE double
 *          if x >  709.782712893383973096 then exp(x) overflows
 *          if x < -745.133219101941108420 then exp(x) underflows
 */
        // y = exp(x)
        // r*(y+1)/(y-1)= R
        //     R+r
        // y = ---
        //     R-r
        //
        //     R+r+(-r+r)     R-r + 2 r        2 r
        // y = ----------- = ---------- = 1 + -----
        //        R-r           R -r           R-r
        //
        // using
        // c = r - (R-P0) = r - R + P0
        // R = P0+r-c
        //
        //           2 r              2 r              r P0 - c r-2 r
        // y = 1 + --------- = 1 + -------- = 1 + r - ---------------
        //         P0+r-c-r         P0 - c                P0 -c
        //
        //              c r + 2 r - P0 r            c r + (2 -P0) r
        // y = 1 + r + ----------------- = 1 + r + -----------------
        //                 P0 - c                       P0 - c
        // with P0 = 2
        //               r c
        // y = 1 + r + ------
        //              2 - c
        //
        // coefficients for exp generated by sollya
        // x^2
        const vf_type exp_c2=0x1.5555555555553p-3;
        // x^4
        const vf_type exp_c4=-0x1.6c16c16c09e8bp-9;
        // x^6
        const vf_type exp_c6=0x1.1566ab58f40fap-14;
        // x^8
        const vf_type exp_c8=-0x1.bbd52980f6ff9p-20;
        // x^10
        const vf_type exp_c10=0x1.63ee7b1d252c1p-25;
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
        y= scale_exp_k(y, kf, k2);
    } else {
/* expm1(x)
 * Returns exp(x)-1, the exponential of x minus 1.
 *
 * Method
 *   1. Argument reduction:
 *      Given x, find r and integer k such that
 *
 *               x = k*ln2 + r,  |r| <= 0.5*ln2 ~ 0.34658
 *
 *      Here a correction term c will be computed to compensate
 *      the error in r when rounded to a floating-point number.
 *
 *   2. Approximating expm1(r) by a special rational function on
 *      the interval [0,0.34658]:
 *      Since
 *          r*(exp(r)+1)/(exp(r)-1) = 2+ r^2/6 - r^4/360 + ...
 *      we define R1(r*r) by
 *          r*(exp(r)+1)/(exp(r)-1) = 2+ r^2/6 * R1(r*r)
 *      That is,
 *          R1(r**2) = 6/r *((exp(r)+1)/(exp(r)-1) - 2/r)
 *                   = 6/r * ( 1 + 2.0*(1/(exp(r)-1) - 1/r))
 *                   = 1 - r^2/60 + r^4/2520 - r^6/100800 + ...
 *      We use a special Remez algorithm on [0,0.347] to generate
 *      a polynomial of degree 5 in r*r to approximate R1. The
 *      maximum error of this polynomial approximation is bounded
 *      by 2**-61. In other words,
 *          R1(z) ~ 1.0 + Q1*z + Q2*z**2 + Q3*z**3 + Q4*z**4 + Q5*z**5
 *      where   Q1  =  -1.6666666666666567384E-2,
 *              Q2  =   3.9682539681370365873E-4,
 *              Q3  =  -9.9206344733435987357E-6,
 *              Q4  =   2.5051361420808517002E-7,
 *              Q5  =  -6.2843505682382617102E-9;
 *              z   =  r*r,
 *      with error bounded by
 *          |                  5           |     -61
 *          | 1.0+Q1*z+...+Q5*z   -  R1(z) | <= 2
 *          |                              |
 *
 *      expm1(r) = exp(r)-1 is then computed by the following
 *      specific way which minimize the accumulation rounding error:
 *                             2     3
 *                            r     r    [ 3 - (R1 + R1*r/2)  ]
 *            expm1(r) = r + --- + --- * [--------------------]
 *                            2     2    [ 6 - r*(3 - R1*r/2) ]
 *
 *      To compensate the error in the argument reduction, we use
 *              expm1(r+c) = expm1(r) + c + expm1(r)*c
 *                         ~ expm1(r) + c + r*c
 *      Thus c+r*c will be added in as the correction terms for
 *      expm1(r+c). Now rearrange the term to avoid optimization
 *      screw up:
 *                      (      2                                    2 )
 *                      ({  ( r    [ R1 -  (3 - R1*r/2) ]  )  }    r  )
 *       expm1(r+c)~r - ({r*(--- * [--------------------]-c)-c} - --- )
 *                      ({  ( 2    [ 6 - r*(3 - R1*r/2) ]  )  }    2  )
 *                      (                                             )
 *
 *                 = r - E
 *   3. Scale back to obtain expm1(x):
 *      From step 1, we have
 *         expm1(x) = either 2^k*[expm1(r)+1] - 1
 *                  = or     2^k*[expm1(r) + (1-2^-k)]
 *   4. Implementation notes:
 *      (A). To save one multiplication, we scale the coefficient Qi
 *           to Qi*2^i, and replace z by (x^2)/2.
 *      (B). To achieve maximum accuracy, we compute expm1(x) by
 *        (i)   if x < -56*ln2, return -1.0, (raise inexact if x!=inf)
 *        (ii)  if k=0, return r-E
 *        (iii) if k=-1, return 0.5*(r-E)-0.5
 *        (iv)  if k=1 if r < -0.25, return 2*((r+0.5)- E)
 *                     else          return  1.0+2.0*(r-E);
 *        (v)   if (k<-2||k>56) return 2^k(1-(E-r)) - 1 (or exp(x)-1)
 *        (vi)  if k <= 20, return 2^k((1-2^-k)-(E-r)), else
 *        (vii) return 2^k(1-((E+2^-k)-r))
 *
 * Special cases:
 *      expm1(INF) is INF, expm1(NaN) is NaN;
 *      expm1(-INF) is -1, and
 *      for finite argument, only expm1(0)=0 is exact.
 *
 * Accuracy:
 *      according to an error analysis, the error is always less than
 *      1 ulp (unit in the last place).
 *
 * Misc. info.
 *      For IEEE double
 *          if x >  7.09782712893383973096e+02 then expm1(x) overflow
 *
 * Constants:
 * The hexadecimal values are the intended ones for the following
 * constants. The decimal values may be used, provided that the
 * compiler will convert from decimal to binary accurately enough
 * to produce the hexadecimal values shown.
 */
        // vf_type e= xr - y;
        vf_type cr = (hi-xr)-lo;
#if 1
        // coefficients for expm1 generated by sollya
        // x^2
        const vf_type expm1_c2=-0x1.11111111110f5p-5;
        // x^4
        const vf_type expm1_c4=0x1.a01a019fe6105p-10;
        // x^6
        const vf_type expm1_c6=-0x1.4ce199ed151c4p-14;
        // x^8
        const vf_type expm1_c8=0x1.0cfcaba045368p-18;
        // x^10
        const vf_type expm1_c10=-0x1.afde65291a16bp-23;
#else
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
#endif
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
        vi2_type t= _T::bias - k2;
        vf_type two_pow_minus_k=_T::insert_exp(t);
        // xr - e = y --> xr -y = e
        t = _T::bias + k2;
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

#if 0
template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
exp2_k(arg_t<vf_type> x)
{
    vf_type kf= rint(vf_type(x));
    vf_type xr = x - kf;
    vi_type k = _T::cvt_f_to_i(kf);
    vi2_type k2= _T::vi_to_vi2(k);
    using d_ops=cftal::impl::d_real_ops<vf_type, d_real_traits<vf_type>::fma>;
    const vf_type exp2_coeff_0h= 1.00000000000000000000000000000000000000000000000000000000000000000000000000000000e+00;
    const vf_type exp2_coeff_1h= 6.93147180559945286226763982995180413126945495605468750000000000000000000000000000e-01;
    const vf_type exp2_coeff_1m= 2.32252707959679672649051490733015842599587355338155297834745738327910657972097397e-17;
    const vf_type exp2_coeff_2h= 2.40226506959100721827482516346208285540342330932617187500000000000000000000000000e-01;
    const vf_type exp2_coeff_3h= 5.55041086648215900578584580671304138377308845520019531250000000000000000000000000e-02;
    const vf_type exp2_coeff_4h= 9.61812910762804319786400952807525754906237125396728515625000000000000000000000000e-03;
    const vf_type exp2_coeff_5h= 1.33335581464232499557254207900314213475212454795837402343750000000000000000000000e-03;
    const vf_type exp2_coeff_6h= 1.54035303940709011492546376409507047355873510241508483886718750000000000000000000e-04;
    const vf_type exp2_coeff_7h= 1.52527338126970089408679029374660274243069579824805259704589843750000000000000000e-05;
    const vf_type exp2_coeff_8h= 1.32154862984053035623605715231931867492676246911287307739257812500000000000000000e-06;
    const vf_type exp2_coeff_9h= 1.01780796038756592500041070047805957798914278100710362195968627929687500000000000e-07;
    const vf_type exp2_coeff_10h= 7.05507029307230633997643912732472548654527599865105003118515014648437500000000000e-09;
    const vf_type exp2_coeff_11h= 4.44773021418893734383658657610726219755470367545058252289891242980957031250000000e-10;
    const vf_type exp2_coeff_12h= 2.55076336845529983597825164275696712030960799921786019694991409778594970703125000e-11;
    const vf_type exp2_coeff_13h= 1.08760387004444207865657840778728562684297964668900249307625927031040191650390625e-12;

#if 0
    vf_type xr2= xr*xr;
    vf_type t0 = xr* impl::poly(xr2,
                                exp2_coeff_12h,
                                exp2_coeff_10h,
                                exp2_coeff_8h,
                                exp2_coeff_6h,
                                exp2_coeff_4h,
                                exp2_coeff_2h);

    vf_type t1 = xr2* impl::poly(xr2,
                                 exp2_coeff_13h,
                                 exp2_coeff_11h,
                                 exp2_coeff_9h,
                                 exp2_coeff_7h,
                                 exp2_coeff_5h,
                                 exp2_coeff_3h);
    vf_type t = t0 + t1;
#else
    vf_type t= xr* impl::poly(xr,
                              exp2_coeff_13h,
                              exp2_coeff_12h,
                              exp2_coeff_11h,
                              exp2_coeff_10h,
                              exp2_coeff_9h,
                              exp2_coeff_8h,
                              exp2_coeff_7h,
                              exp2_coeff_6h,
                              exp2_coeff_5h,
                              exp2_coeff_4h,
                              exp2_coeff_3h,
                              exp2_coeff_2h);
#endif
    vf_type h0, l0, h1, l1, h2, l2;
    d_ops::add212(h0, l0, exp2_coeff_1h, exp2_coeff_1m, t);
    // d_ops::muladd212(h1, l1, exp2_coeff_1h, exp2_coeff_1m, xr, h0, l0);
    d_ops::mul122(h1, l1, xr, h0, l0);
    d_ops::add122(h2, l2, exp2_coeff_0h, h1, l1);
    // *exp2_resh = exp2_t_25_0h; *exp2_resm = exp2_t_25_0m;
    vf_type y= h2 /*+ l2 */;
    y= scale_exp_k(y, kf, k2);
    return y;
}
#endif

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
exp2_k(arg_t<vf_type> x)
{
    vf_type kf= rint(vf_type(x));
    vf_type xr = x - kf;
    vi_type k = _T::cvt_f_to_i(kf);
    vi2_type k2= _T::vi_to_vi2(k);
#if 1
    using d_ops=cftal::impl::d_real_ops<vf_type,
                                        d_real_traits<vf_type>::fma>;
    // coefficients for exp2 generated by sollya
    // x^0
    const vf_type exp2_c0=0x1p0;
    // x^1
    const vf_type exp2_c1h=0x1.62e42fefa39efp-1;
    const vf_type exp2_c1l=0x1.ab2948509c47cp-56;
    // x^2
    const vf_type exp2_c2h=0x1.ebfbdff82c58fp-3;
    const vf_type exp2_c2l=-0x1.62e3426db0b0ep-57;
    // x^3
    const vf_type exp2_c3=0x1.c6b08d704a0cp-5;
    // x^4
    const vf_type exp2_c4=0x1.3b2ab6fba4e7dp-7;
    // x^5
    const vf_type exp2_c5=0x1.5d87fe78a6593p-10;
    // x^6
    const vf_type exp2_c6=0x1.430912f86a0fap-13;
    // x^7
    const vf_type exp2_c7=0x1.ffcbfc592d93ep-17;
    // x^8
    const vf_type exp2_c8=0x1.62c02248e2b1ep-20;
    // x^9
    const vf_type exp2_c9=0x1.b5253b40c70dap-24;
    // x^10
    const vf_type exp2_c10=0x1.e4cef92c03702p-28;
    // x^11
    const vf_type exp2_c11=0x1.e8d0ab4597e07p-32;
    // x^12
    const vf_type exp2_c12=0x1.c4c410ba52287p-36;
    // x^13
    const vf_type exp2_c13=0x1.7adaae2b9ca3p-40;
    vf_type y=impl::poly(xr,
                         exp2_c13,
                         exp2_c12,
                         exp2_c11,
                         exp2_c10,
                         exp2_c9,
                         exp2_c8,
                         exp2_c7,
                         exp2_c6,
                         exp2_c5,
                         exp2_c4,
                         exp2_c3);
    y *= xr;
    vf_type ul, uh, vl, vh;
    d_ops::add212(vh, vl, exp2_c2h, exp2_c2l, y);
    d_ops::muladd212(uh, ul, exp2_c1h, exp2_c1l, xr, vh, vl);
    d_ops::mul122(vh, vl, xr, uh, ul);
    d_ops::add122(uh, ul, exp2_c0, vh, vl);
    y = uh;
#else
    // coefficients for exp2 generated by sollya
    // x^11
    const vf_type exp2_c11=0x1.e0fcb9712478dp-36;  // 0x3dbe0fcb9712478d
    // x^10
    const vf_type exp2_c10=0x1.ec5e95ae33395p-32;  // 0x3dfec5e95ae33395
    // x^9
    const vf_type exp2_c9=0x1.e4bb7f1f8891p-28;  // 0x3e3e4bb7f1f88910
    // x^8
    const vf_type exp2_c8=0x1.b5233dce62cf5p-24;  // 0x3e7b5233dce62cf5
    // x^7
    const vf_type exp2_c7=0x1.62c0272e79a1fp-20;  // 0x3eb62c0272e79a1f
    // x^6
    const vf_type exp2_c6=0x1.ffcbfd443c0fap-17;  // 0x3eeffcbfd443c0fa
    // x^5
    const vf_type exp2_c5=0x1.430912f75554ep-13;  // 0x3f2430912f75554e
    // x^4
    const vf_type exp2_c4=0x1.5d87fe7875275p-10;  // 0x3f55d87fe7875275
    // x^3
    const vf_type exp2_c3=0x1.3b2ab6fba51a1p-7;  // 0x3f83b2ab6fba51a1
    // x^2
    const vf_type exp2_c2=0x1.c6b08d704a1d1p-5;  // 0x3fac6b08d704a1d1
    // x^1
    const vf_type exp2_c1=0x1.ebfbdff82c58ep-3;  // 0x3fcebfbdff82c58e
    // x^0
    const vf_type exp2_c0=0x1.62e42fefa39efp-1;  // 0x3fe62e42fefa39ef
    vf_type y=impl::poly(xr,
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
#endif
    y= scale_exp_k(y, kf, k2);
    return y;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
exp10_k(arg_t<vf_type> x)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    vf_type kf = rint(vf_type(x * ctbl::m_1_ld2.h()));
    vf_type hi = x - kf * ctbl::m_ld2_cw[0];
    vf_type lo = kf * ctbl::m_ld2_cw[1];
    vf_type xr = hi - lo;
    vi_type k= _T::cvt_f_to_i(kf);
    vi2_type k2= _T::vi_to_vi2(k);

    // coefficients for exp10 generated by sollya
    // x^11
    const vf_type exp10_c11=0x1.39f0bef55cff2p-15;  // 0x3f039f0bef55cff2
    // x^10
    const vf_type exp10_c10=0x1.f4bda090370fdp-13;  // 0x3f2f4bda090370fd
    // x^9
    const vf_type exp10_c9=0x1.2ecb0d8248d31p-10;  // 0x3f52ecb0d8248d31
    // x^8
    const vf_type exp10_c8=0x1.489b21a9e51cfp-8;  // 0x3f7489b21a9e51cf
    // x^7
    const vf_type exp10_c7=0x1.4116a27b57c86p-6;  // 0x3f94116a27b57c86
    // x^6
    const vf_type exp10_c6=0x1.16e4de81155d6p-4;  // 0x3fb16e4de81155d6
    // x^5
    const vf_type exp10_c5=0x1.a7ed7088f6e97p-3;  // 0x3fca7ed7088f6e97
    // x^4
    const vf_type exp10_c4=0x1.1429ffd23c62fp-1;  // 0x3fe1429ffd23c62f
    // x^3
    const vf_type exp10_c3=0x1.2bd7609fd8f3bp0;  // 0x3ff2bd7609fd8f3b
    // x^2
    const vf_type exp10_c2=0x1.0470591de2af5p1;  // 0x4000470591de2af5
    // x^1
    const vf_type exp10_c1=0x1.53524c73cea6ap1;  // 0x40053524c73cea6a
    // x^0
    const vf_type exp10_c0=0x1.26bb1bbb55516p1;  // 0x40026bb1bbb55516
    vf_type y=impl::poly(xr,
                         exp10_c11,
                         exp10_c10,
                         exp10_c9,
                         exp10_c8,
                         exp10_c7,
                         exp10_c6,
                         exp10_c5,
                         exp10_c4,
                         exp10_c3,
                         exp10_c2,
                         exp10_c1,
                         exp10_c0);
    y *= xr;
    // vf_type cr = (hi-xr)-lo;
    // y += cr + cr *xr;
    y += 1.0;
    y= scale_exp_k(y, kf, k2);
    return y;
}

#if 0
template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
__expo_k(arg_t<vf_type> xc)
{
    // k is such that k*ln2 has minimal relative error and
    // x - kln2 > log(DBL_MIN)
    const uint64_t k = 2043;
    const double kln2 = 0x1.62066151add8bp+10;
    const vf_type scale=bytes8(uint64_t((0x3ffULL + k/2)<<52))._f64;
    vf_type e= exp_k(xc - kln2, false);
    e *= scale * scale;
    return e;
}
#endif

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
sinh_k(arg_t<vf_type> xc)
{
    // for huge arguments:
    // sinh(x) = sgn(x) [e^y + ((e^v)/2 -1)e^y - (e^-v)/2)e^-y]
    // y= |x| -v
    // ln(2) <= v <= ln(3) for base 2
    // ln(2) <= v <= ln(2.125) for other bases
    // (e^v)/2 - 1 < 1/ß
    // chosing v=0.75 (2 bits set)
    // between 1 and overflow of expm(1):
    // sinh (x) = 1/2 (exp(x) - exp(-x))
    //          = (expm1(x) + (expm1(x)/(expm1(x)+1))/2;
    vf_type x = abs(xc);
    using fc=func_constants<double>;
    vmf_type x_huge = x >= fc::exp_hi_inf;
    // between 0 and 1
    // sinh(x) = x + x^3/Q(x^2)
    // coefficients for sinh generated by sollya
    // x^12
    const vf_type sinh_c12=-0x1.22b83d62dda17p-32;  // 0xbdf22b83d62dda17
    // x^10
    const vf_type sinh_c10=-0x1.5ebf4589adb14p-29;  // 0xbe25ebf4589adb14
    // x^8
    const vf_type sinh_c8=0x1.856f26cce41dfp-20;  // 0x3eb856f26cce41df
    // x^6
    const vf_type sinh_c6=-0x1.1af2f7ffd95dcp-13;  // 0xbf21af2f7ffd95dc
    // x^4
    const vf_type sinh_c4=0x1.01767dcf05202p-7;  // 0x3f801767dcf05202
    // x^2
    const vf_type sinh_c2=-0x1.3333333333947p-2;  // 0xbfd3333333333947
    // x^0
    const vf_type sinh_c0=0x1.8000000000001p2;  // 0x4018000000000001
    vf_type x2=x*x;
    vf_type q=impl::poly(x2,
                         sinh_c12,
                         sinh_c10,
                         sinh_c8,
                         sinh_c6,
                         sinh_c4,
                         sinh_c2,
                         sinh_c0);
    vf_type sinh_le_1 = x + (x*x2)/q;
    vf_type xr= _T::sel(x_huge, x - 0.75, x);
    vf_type em=exp_k(xr, true);
    vf_type e= em+1;
    const vf_type e_v_2_m_1 = +5.8500008306337336616565e-02;
    const vf_type e_m_v_2 = +2.3618327637050734457702e-01;
    vf_type sinh_gt_1 = 0.5 * (em + em/e);
    vf_type sinh_huge = e + e_v_2_m_1 * e - e_m_v_2 / e;
    vf_type sinh_x = _T::sel(x<=1.0, sinh_le_1, sinh_gt_1);
    sinh_x = _T::sel(x_huge, sinh_huge, sinh_x);
    vf_type y = copysign(sinh_x, xc);
    return y;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
cosh_k(arg_t<vf_type> xc)
{
    // for really large arguments:
    // cosh(x) = sgn(x) [e^y + ((e^v)/2 -1)e^y + (e^-v)/2)e^-y]
    // y= |x| -v
    // ln(2) <= v <= ln(3) for base 2
    // ln(2) <= v <= ln(2.125) for other bases
    // (e^v)/2 - 1 < 1/ß
    // chosing v=0.75 (2 bits set)
    // between log(2) and overflow of expm(1):
    // cosh (x) = 1/2 (exp(x) + exp(-x))
    //          = 1 + (expm1(x)/(expm1(x)+1))/2;
    vf_type x=abs(xc);
    using fc=func_constants<double>;
    vmf_type x_huge = x >= fc::exp_hi_inf;
    /*
        cosh(x) = 1 + x^2/2 + x^4/24 ...
        cosh(x)-1) = x^2*R
        R= f(x^2)
        cosh(x)-1)/(x^2)= R
    */
    // coefficients for cosh generated by sollya
    // x^12
    const vf_type cosh_c12=0x1.964f333390db1p-37;  // 0x3da964f333390db1
    // x^10
    const vf_type cosh_c10=0x1.1eebdcaab6abbp-29;  // 0x3e21eebdcaab6abb
    // x^8
    const vf_type cosh_c8=0x1.27e4fc7d859cfp-22;  // 0x3e927e4fc7d859cf
    // x^6
    const vf_type cosh_c6=0x1.a01a019f7f3f7p-16;  // 0x3efa01a019f7f3f7
    // x^4
    const vf_type cosh_c4=0x1.6c16c16c16e8ap-10;  // 0x3f56c16c16c16e8a
    // x^2
    const vf_type cosh_c2=0x1.5555555555555p-5;  // 0x3fa5555555555555
    // x^0
    const vf_type cosh_c0=0x1p-1;  // 0x3fe0000000000000
    vf_type xx= x*x;
    vf_type cosh_le_ln2 = 1.0 + xx*impl::poly(xx,
                                              cosh_c12,
                                              cosh_c10,
                                              cosh_c8,
                                              cosh_c6,
                                              cosh_c4,
                                              cosh_c2,
                                              cosh_c0);
    vf_type xr= _T::sel(x_huge, x - 0.75, x);
    vf_type em=exp_k(xr, true);
    vf_type e=em+1;
    const vf_type e_v_2_m_1 = +5.8500008306337336616565e-02;
    const vf_type e_m_v_2 = +2.3618327637050734457702e-01;
    vf_type cosh_gt_ln2 = 0.5 * (e + 1/e);
    vf_type cosh_huge = e + (e_v_2_m_1 * e - e_m_v_2 / e);
    vf_type cosh_x = _T::sel(x <= M_LN2, cosh_le_ln2, cosh_gt_ln2);
    cosh_x = _T::sel(x_huge, cosh_huge, cosh_x);
    return cosh_x;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
tanh_k(arg_t<vf_type> xc)
{
    /* tanh(x) = (exp(x) - exp(-x))/(exp(x) + exp(-x))
     *         = (exp(2*x) - 1)/(exp(2*x) - 1 + 2)
     *         = (1 - exp(-2*x))/(exp(-2*x) - 1 + 2)
     */
    vf_type x= abs(xc);
    // using fc=func_constants<double>;
    vmf_type x_gt_20 = x >= 20.0;
    vf_type tanh_x_gt_20 = 1.0;
    vf_type x2=2.0*x;
    vf_type em1= exp_k(x2, true);
    vmf_type x_gt_ln_3_2= x > 5.493061443340549e-1;
    vf_type tanh_x_gt_ln_3_2 = 1.0 - 2.0/(em1+2);
    // tanh(x) = sgn(x) * x - x^3/(3+ x^2 R(x^2));
    // coefficients for tanh generated by sollya
    // x^12
    const vf_type tanh_c12=0x1.78da6c5903afbp-30;  // 0x3e178da6c5903afb
    // x^10
    const vf_type tanh_c10=-0x1.fb1a90398e3f5p-26;  // 0xbe5fb1a90398e3f5
    // x^8
    const vf_type tanh_c8=0x1.41740f0028d47p-21;  // 0x3ea41740f0028d47
    // x^6
    const vf_type tanh_c6=-0x1.997cb4a4d399p-17;  // 0xbee997cb4a4d3990
    // x^4
    const vf_type tanh_c4=0x1.0a4e1582c48aep-12;  // 0x3f30a4e1582c48ae
    // x^2
    const vf_type tanh_c2=-0x1.767dce4349525p-8;  // 0xbf7767dce4349525
    // x^0
    const vf_type tanh_c0=0x1.3333333333333p0;  // 0x3ff3333333333333
    vf_type xx= x*x;
    vf_type R= impl::poly(xx,
                          tanh_c12,
                          tanh_c10,
                          tanh_c8,
                          tanh_c6,
                          tanh_c4,
                          tanh_c2,
                          tanh_c0);
    vf_type tanh_x_small = x *(1.0 - xx/(3.0 + xx * R));
    vf_type tanh_x = _T::sel(x_gt_ln_3_2, tanh_x_gt_ln_3_2, tanh_x_small);
    tanh_x = _T::sel(x_gt_20, tanh_x_gt_20, tanh_x);

    tanh_x= copysign(tanh_x, xc);
    return tanh_x;
}

template <typename _T>
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
log_k_poly(arg_t<vf_type> z)
{
#if 1
    // coefficients for log generated by sollya
    // x^16
    const vf_type log_c16=0x1.1023dbad18397p-3;  // 0x3fc1023dbad18397
    // x^14
    const vf_type log_c14=0x1.0f4a122846206p-3;  // 0x3fc0f4a122846206
    // x^12
    const vf_type log_c12=0x1.3b21594e6751bp-3;  // 0x3fc3b21594e6751b
    // x^10
    const vf_type log_c10=0x1.745cdb74b755ep-3;  // 0x3fc745cdb74b755e
    // x^8
    const vf_type log_c8=0x1.c71c725c5fa92p-3;  // 0x3fcc71c725c5fa92
    // x^6
    const vf_type log_c6=0x1.249249242ee17p-2;  // 0x3fd249249242ee17
    // x^4
    const vf_type log_c4=0x1.9999999999d59p-2;  // 0x3fd9999999999d59
    // x^2
    const vf_type log_c2=0x1.5555555555555p-1;  // 0x3fe5555555555555
#if 1
    vf_type w = z*z;
    vf_type t1= z*impl::poly(w,
                             log_c14,
                             log_c10,
                             log_c6,
                             log_c2);
    vf_type t2= w*impl::poly(w,
                             log_c16,
                             log_c12,
                             log_c8,
                             log_c4);
    vf_type y = t1+t2;
#else
    vf_type y = z*impl::poly(z,
                             log_c16,
                             log_c14,
                             log_c12,
                             log_c10,
                             log_c8,
                             log_c6,
                             log_c4,
                             log_c2);
#endif
#else
    const vf_type Lg1 = 6.666666666666735130e-01;  /* 3FE55555 55555593 */
    const vf_type Lg2 = 3.999999999940941908e-01;  /* 3FD99999 9997FA04 */
    const vf_type Lg3 = 2.857142874366239149e-01;  /* 3FD24924 94229359 */
    const vf_type Lg4 = 2.222219843214978396e-01;  /* 3FCC71C5 1D8E78AF */
    const vf_type Lg5 = 1.818357216161805012e-01;  /* 3FC74664 96CB03DE */
    const vf_type Lg6 = 1.531383769920937332e-01;  /* 3FC39A09 D078C69F */
    const vf_type Lg7 = 1.479819860511658591e-01;  /* 3FC2F112 DF3E5244 */
    vf_type w = z*z;
    vf_type t1 = w*(Lg2+w*(Lg4+w*Lg6));
    vf_type t2 = z*(Lg1+w*(Lg3+w*(Lg5+w*Lg7)));
    vf_type y = t2 + t1;
#endif
    return y;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
log_k(arg_t<vf_type> xc, log_func func)
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

    using fc = func_constants<double>;
    vmf_type is_denom=xc <= fc::max_denormal;
    vf_type x=_T::sel(is_denom, xc*0x1p54, xc);
    vi2_type k=_T::sel(_T::vmf_to_vmi2(is_denom), vi2_type(-54), vi2_type(0));
    vi2_type lx, hx;
    _T::extract_words(lx, hx, x);
    /* reduce x into [sqrt(2)/2, sqrt(2)] */
    hx += 0x3ff00000 - 0x3fe6a09e;
    k += (hx>>20) - _T::bias;
    hx = (hx&0x000fffff) + 0x3fe6a09e;
    vf_type xr = _T::combine_words(lx, hx);

    vf_type f = xr - 1.0;
    vf_type hfsq = 0.5*f*f;
    vf_type s = f/(2.0+f);
    vf_type z = s*s;

    // split of the polynomial reduces precision
    vf_type R = log_k_poly(z);
    vf_type res;
    vf_type kf = _T::cvt_i_to_f(_T::vi2_odd_to_vi(k));
    if (func == log_func::c_log_e) {
        using ctbl=impl::d_real_constants<d_real<double>, double>;
        vf_type log_x=s*(hfsq+R) +
                    kf*ctbl::m_ln2_cw[1] - hfsq +
                    f + kf*ctbl::m_ln2_cw[0];
        res = log_x;
    } else if (func == log_func::c_log_10) {
        const vf_type
        ivln10hi  = 4.34294481878168880939e-01; /* 0x3fdbcb7b, 0x15200000 */
        const vf_type
        ivln10lo  = 2.50829467116452752298e-11; /* 0x3dbb9438, 0xca9aadd5 */
        const vf_type
        log10_2hi = 3.01029995663611771306e-01; /* 0x3FD34413, 0x509F6000 */
        const vf_type
        log10_2lo = 3.69423907715893078616e-13; /* 0x3D59FEF3, 0x11F12B36 */

        vf_type t = f - hfsq;
        vf_type hi= _T::clear_low_word(t);
        vf_type lo= f - hi -hfsq + s * (hfsq + R);

        vf_type val_hi = hi * ivln10hi;
        vf_type y = kf* log10_2hi;
        vf_type val_lo = kf * log10_2lo + (lo+hi)*ivln10lo + lo*ivln10hi;

        vf_type w= y + val_hi;
        val_lo += (y - w) + val_hi;
        val_hi = w;

        vf_type log10_x = val_lo + val_hi;
        res =log10_x;
    } else if (func == log_func::c_log_2) {
        const vf_type
        ivln2hi = 1.44269504072144627571e+00; /* 0x3ff71547, 0x65200000 */
        const vf_type
        ivln2lo = 1.67517131648865118353e-10; /* 0x3de705fc, 0x2eefa200 */

        vf_type t= f - hfsq;
        vf_type hi= _T::clear_low_word(t);
        vf_type lo= f - hi - hfsq + s * (hfsq + R);
        vf_type val_hi = hi* ivln2hi;
        vf_type val_lo = (lo+hi)*ivln2lo + lo*ivln2hi;

        vf_type y= kf;
        vf_type w= y+ val_hi;
        val_lo += (y-w) + val_hi;
        val_hi = w;

        vf_type log2_x= val_lo + val_hi;
        res = log2_x;
    }
    return res;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
log1p_k(arg_t<vf_type> xc)
{
/* double log1p(double x)
 * Return the natural logarithm of 1+x.
 *
 * Method :
 *   1. Argument Reduction: find k and f such that
 *                      1+x = 2^k * (1+f),
 *         where  sqrt(2)/2 < 1+f < sqrt(2) .
 *
 *      Note. If k=0, then f=x is exact. However, if k!=0, then f
 *      may not be representable exactly. In that case, a correction
 *      term is need. Let u=1+x rounded. Let c = (1+x)-u, then
 *      log(1+x) - log(u) ~ c/u. Thus, we proceed to compute log(u),
 *      and add back the correction term c/u.
 *      (Note: when x > 2**53, one can simply return log(x))
 *
 *   2. Approximation of log(1+f): See log.c
 *
 *   3. Finally, log1p(x) = k*ln2 + log(1+f) + c/u. See log.c
 *
 * Special cases:
 *      log1p(x) is NaN with signal if x < -1 (including -INF) ;
 *      log1p(+INF) is +INF; log1p(-1) is -INF with signal;
 *      log1p(NaN) is that NaN with no signal.
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
 *
 * Note: Assuming log() return accurate answer, the following
 *       algorithm can be used to compute log1p(x) to within a few ULP:
 *
 *              u = 1+x;
 *              if(u==1.0) return x ; else
 *                         return log(u)*(x/(u-1.0));
 *
 *       See HP-15C Advanced Functions Handbook, p.193.
 */
    vf_type x=xc;
    vf_type u= 1+xc;
    vi2_type lu, hu;
    _T::extract_words(lu, hu, u);
    hu += (0x3ff00000 - 0x3fe6a09e);
    vi2_type k=(hu >> 20) - _T::bias;
    vf_type kf= _T::cvt_i_to_f(_T::vi2_odd_to_vi(k));
    /* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
    vf_type c_k_2 = _T::sel(kf >= vf_type(2.0), 1.0-(u-x), x-(u-1.0));
    c_k_2 /= u;
    vf_type c = _T::sel(kf < vf_type(54.0), c_k_2, vf_type(0));
    /* reduce u into [sqrt(2)/2, sqrt(2)] */
    hu = (hu&0x000fffff) + 0x3fe6a09e;
    vf_type nu = _T::combine_words(lu, hu);
    vf_type f= nu -1.0;

    vf_type hfsq = 0.5*f*f;
    vf_type s = f/(2.0+f);
    vf_type z = s*s;
    vf_type R = log_k_poly(z);

    using ctbl=impl::d_real_constants<d_real<double>, double>;
    vf_type log1p_x=s*(hfsq+R) +
                    (kf*ctbl::m_ln2_cw[1]+c) - hfsq +
                    f + kf*ctbl::m_ln2_cw[0];
    log1p_x= _T::sel(abs(x) < 0x1p-53, x, log1p_x);
    return log1p_x;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
log2_k(arg_t<vf_type> xc)
{
/*
 * Return the base 2 logarithm of x.  See log.c for most comments.
 *
 * Reduce x to 2^k (1+f) and calculate r = log(1+f) - f + f*f/2
 * as in log.c, then combine and scale in extra precision:
 *    log2(x) = (f - f*f/2 + r)/log(2) + k
 */
    return log_k(xc, log_func::c_log_2);
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
log10_k(arg_t<vf_type> xc)
{
/*
 * Return the base 10 logarithm of x.  See log.c for most comments.
 *
 * Reduce x to 2^k (1+f) and calculate r = log(1+f) - f + f*f/2
 * as in log.c, then combine and scale in extra precision:
 *    log10(x) = (f - f*f/2 + r)/log(10) + k*log10(2)
 */
    return log_k(xc, log_func::c_log_10);
}

template <typename _T>
inline
std::pair<typename cftal::math::func_core<double, _T>::dvf_type,
          typename cftal::math::func_core<double, _T>::vi_type>
cftal::math::func_core<double, _T>::
reduce_trig_arg_k(arg_t<vf_type> x)
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
    // coefficients for sin generated by sollya
    // x^12
    const vf_type sin_c12=0x1.5d8e62828f329p-33;  // 0x3de5d8e62828f329
    // x^10
    const vf_type sin_c10=-0x1.ae5e5500c1349p-26;  // 0xbe5ae5e5500c1349
    // x^8
    const vf_type sin_c8=0x1.71de355fa53bdp-19;  // 0x3ec71de355fa53bd
    // x^6
    const vf_type sin_c6=-0x1.a01a019bf2b81p-13;  // 0xbf2a01a019bf2b81
    // x^4
    const vf_type sin_c4=0x1.111111110f76p-7;  // 0x3f8111111110f760
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
    // coefficients for cos generated by sollya
    // x^14
    const vf_type cos_c14=-0x1.907385623efccp-37;  // 0xbda907385623efcc
    // x^12
    const vf_type cos_c12=0x1.1eeb57d337cd2p-29;  // 0x3e21eeb57d337cd2
    // x^10
    const vf_type cos_c10=-0x1.27e4fa02e3e6ap-22;  // 0xbe927e4fa02e3e6a
    // x^8
    const vf_type cos_c8=0x1.a01a019f3839p-16;  // 0x3efa01a019f38390
    // x^6
    const vf_type cos_c6=-0x1.6c16c16c168cap-10;  // 0xbf56c16c16c168ca
    // x^4
    const vf_type cos_c4=0x1.5555555555555p-5;  // 0x3fa5555555555555

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
__tan_k(arg_t<vf_type> xh, arg_t<vf_type> xl, arg_t<vi_type> q)
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
    // x^26
    const vf_type tan_c26=0x1.aecf8079c312fp-16;  // 0x3efaecf8079c312f
    // x^24
    const vf_type tan_c24=-0x1.2c5dfc1574263p-16;  // 0xbef2c5dfc1574263
    // x^22
    const vf_type tan_c22=0x1.2807f71e551ffp-14;  // 0x3f12807f71e551ff
    // x^20
    const vf_type tan_c20=0x1.4a74d521b3223p-14;  // 0x3f14a74d521b3223
    // x^18
    const vf_type tan_c18=0x1.022283008da26p-12;  // 0x3f3022283008da26
    // x^16
    const vf_type tan_c16=0x1.3459c2058ca7p-11;  // 0x3f43459c2058ca70
    // x^14
    const vf_type tan_c14=0x1.7dbb3dec83551p-10;  // 0x3f57dbb3dec83551
    // x^12
    const vf_type tan_c12=0x1.d6d2456d3b6b4p-9;  // 0x3f6d6d2456d3b6b4
    // x^10
    const vf_type tan_c10=0x1.226e3dfc1bce7p-7;  // 0x3f8226e3dfc1bce7
    // x^8
    const vf_type tan_c8=0x1.664f48452cb1p-6;  // 0x3f9664f48452cb10
    // x^6
    const vf_type tan_c6=0x1.ba1ba1bb1eaecp-5;  // 0x3faba1ba1bb1eaec
    // x^4
    const vf_type tan_c4=0x1.111111110fffp-3;  // 0x3fc111111110fff0
    // x^2
    const vf_type tan_c2=0x1.5555555555562p-2;  // 0x3fd5555555555562

    // make xrh positive
    vf_type sgn_x = copysign(vf_type(1.0), xh);
    vmf_type x_is_neg = sgn_x < 0.0;
    vf_type xrh = _T::sel(x_is_neg, -xh, xh);
    vf_type xrl = _T::sel(x_is_neg, -xl, xl);

    using ctbl = impl::d_real_constants<d_real<double>, double>;
    const vf_type large_arg=0.6731984257692414;
    vmf_type x_large= xrh > large_arg;
    // for xh in [6/7*pi/4, pi/4] we replace xh with pi/4 - xh
#if 0
    // not required for double precision
    dvf_type dxrl= dvf_type(ctbl::m_pi_4) - dvf_type(xrh, xrl);
    xrh = _T::sel(x_large, dxrl.h(), xrh);
    xrl = _T::sel(x_large, dxrl.l(), xrl);
#else
    xrh = _T::sel(x_large,
                  (ctbl::m_pi_4.h() - xrh) + (ctbl::m_pi_4.l() - xrl) , xrh);
    xrl = _T::sel(x_large, 0, xrl);
#endif
    vf_type z = xrh*xrh;

    vf_type s= z * xrh;
    vf_type r = s* impl::poly(z,
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
    vi2_type t=_T::vi_to_vi2(q);
    vi2_type q1= t & 1;
    vmi2_type qm1= q1 == vi2_type(1);
    vmf_type fqm1= _T::vmi2_to_vmf(qm1);

    // calculate the values for x large including the sign
    s = _T::sel(fqm1, vf_type(-1.0), vf_type(1.0));
    vf_type txyl = s - 2*(xrh + (r - (txy*txy)/(s +txy)));
    txyl *= sgn_x;

    // calculate -1/tan: -1/(xrh +r) has an error to up to 2 ulp
    // use multiprecision arithmetic and one newton raphson step
    vf_type w0 = _T::clear_low_word(txy);
    vf_type w1 = r - (w0 -xrh);
    vf_type a = -1.0/txy;
    vf_type a0 = _T::clear_low_word(a);
    vf_type inv_txy= a0 + a *(1.0 + a0*w0 + a0*w1);
    inv_txy= _T::sel(x_is_neg, -inv_txy, inv_txy);

    // restore the sign
    txy = copysign(txy, sgn_x);

    vf_type tt= _T::sel(fqm1, inv_txy, txy);
    tt = _T::sel(x_large, txyl, tt);
    return tt;
}

template <typename _T>
__attribute__((flatten))
void
cftal::math::func_core<double, _T>::
sin_cos_k(arg_t<vf_type> xc, vf_type* ps, vf_type* pc)
{
    std::pair<dvf_type, vi_type> rq=reduce_trig_arg_k(xc);
    const dvf_type& x= rq.first;
    const vi_type& qh= rq.second;
    vi2_type q=_T::vi_to_vi2(qh);

    vf_type s = __sin_k(x.h(), x.l());
    vf_type c = __cos_k(x.h(), x.l());

    vmi2_type q_and_2(vi2_type(q & vi2_type(2))==vi2_type(2));
    vmf_type q_and_2_f(_T::vmi2_to_vmf(q_and_2));
    vmi2_type q_and_1(vi2_type(q & vi2_type(1))==vi2_type(1));
    vmf_type q_and_1_f(_T::vmi2_to_vmf(q_and_1));

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
tan_k(arg_t<vf_type> xc)
{
    std::pair<dvf_type, vi_type> rq=reduce_trig_arg_k(xc);
    const dvf_type& x= rq.first;
    const vi_type& q= rq.second;
    vf_type t = __tan_k(x.h(), x.l(), q);
    return t;
}

template <typename _T>
__attribute__((flatten))
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
atan_k(arg_t<vf_type> xc)
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
/* atan(x)
 * Method
 *   1. Reduce x to positive by atan(x) = -atan(-x).
 *   2. According to the integer k=4t+0.25 chopped, t=x, the argument
 *      is further reduced to one of the following intervals and the
 *      arctangent of t is evaluated by the corresponding formula:
 *
 *      [0,7/16]      atan(x) = t-t^3*(a1+t^2*(a2+...(a10+t^2*a11)...)
 *      [7/16,11/16]  atan(x) = atan(1/2) + atan( (t-0.5)/(1+t/2) )
 *      [11/16.19/16] atan(x) = atan( 1 ) + atan( (t-1)/(1+t) )
 *      [19/16,39/16] atan(x) = atan(3/2) + atan( (t-1.5)/(1+1.5t) )
 *      [39/16,INF]   atan(x) = atan(INF) + atan( -1/t )
 *
 * Constants:
 * The hexadecimal values are the intended ones for the following
 * constants. The decimal values may be used, provided that the
 * compiler will convert from decimal to binary accurately enough
 * to produce the hexadecimal values shown.
 */
    /* atan(0.5)hi 0x3FDDAC67, 0x0561BB4F */
    const vf_type atan_0_5_hi = 4.63647609000806093515e-01;
    /* atan(0.5)lo 0x3C7A2B7F, 0x222F65E2 */
    const vf_type atan_0_5_lo = 2.26987774529616870924e-17;
     /* atan(1.0)hi 0x3FE921FB, 0x54442D18 */
    const vf_type atan_1_0_hi = 7.85398163397448278999e-01;
    /* atan(1.0)lo 0x3C81A626, 0x33145C07 */
    const vf_type atan_1_0_lo = 3.06161699786838301793e-17;
    /* atan(1.5)hi 0x3FEF730B, 0xD281F69B */
    const vf_type atan_1_5_hi = 9.82793723247329054082e-01;
     /* atan(1.5)lo 0x3C700788, 0x7AF0CBBD */
    const vf_type atan_1_5_lo = 1.39033110312309984516e-17;
     /* atan(inf)hi 0x3FF921FB, 0x54442D18 */
    const vf_type atan_inf_hi = 1.57079632679489655800e+00;
     /* atan(inf)lo 0x3C91A626, 0x33145C07 */
    const vf_type atan_inf_lo = 6.12323399573676603587e-17;

    vf_type x=abs(xc);
    // range reduction
    vmf_type r=x > 7.0/16;
    vf_type atan_hi= _T::sel(r, atan_0_5_hi, vf_type(0.0));
    vf_type atan_lo= _T::sel(r, atan_0_5_lo, vf_type(0.0));
    vf_type t=_T::sel(r, (2.0*x-1.0)/(2.0+x), x);
    r = x>11.0/16;
    atan_hi=_T::sel(r, atan_1_0_hi, atan_hi);
    atan_lo=_T::sel(r, atan_1_0_lo, atan_lo);
    t = _T::sel(r, (x-1.0)/(1.0+x), t);
    r = x>19.0/16;
    atan_hi=_T::sel(r, atan_1_5_hi, atan_hi);
    atan_lo=_T::sel(r, atan_1_5_lo, atan_lo);
    t = _T::sel(r, (x-1.5)/(1.0+1.5*x), t);
    r = x>39.0/16;
    atan_hi=_T::sel(r, atan_inf_hi, atan_hi);
    atan_lo=_T::sel(r, atan_inf_lo, atan_lo);
    t = _T::sel(r, -1.0/x, t);
    /* end of argument reduction */
    // coefficients for atan generated by sollya
    // x^22
    const vf_type atan_c22=-0x1.ddfde1bdc4df5p-7;  // 0xbf8ddfde1bdc4df5
    // x^20
    const vf_type atan_c20=0x1.0db2b953efadcp-5;  // 0x3fa0db2b953efadc
    // x^18
    const vf_type atan_c18=-0x1.6f316582d3499p-5;  // 0xbfa6f316582d3499
    // x^16
    const vf_type atan_c16=0x1.ab20857508674p-5;  // 0x3faab20857508674
    // x^14
    const vf_type atan_c14=-0x1.e166a084a0186p-5;  // 0xbfae166a084a0186
    // x^12
    const vf_type atan_c12=0x1.110c0e8382a67p-4;  // 0x3fb110c0e8382a67
    // x^10
    const vf_type atan_c10=-0x1.3b136b4752d24p-4;  // 0xbfb3b136b4752d24
    // x^8
    const vf_type atan_c8=0x1.745d14cc6606bp-4;  // 0x3fb745d14cc6606b
    // x^6
    const vf_type atan_c6=-0x1.c71c71b971813p-4;  // 0xbfbc71c71b971813
    // x^4
    const vf_type atan_c4=0x1.249249247d972p-3;  // 0x3fc249249247d972
    // x^2
    const vf_type atan_c2=-0x1.99999999997d8p-3;  // 0xbfc99999999997d8
    // x^0
    const vf_type atan_c0=0x1.5555555555555p-2;  // 0x3fd5555555555555
    vf_type t2=t*t;
    vf_type p= t2 * impl::poly(t2,
                               atan_c22,
                               atan_c20,
                               atan_c18,
                               atan_c16,
                               atan_c14,
                               atan_c12,
                               atan_c10,
                               atan_c8,
                               atan_c6,
                               atan_c4,
                               atan_c2,
                               atan_c0);
    vf_type at=  atan_hi - (t * p - atan_lo - t);
    at = copysign(at, xc);
    return at;
}

template <typename _T>
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
atan2_k(arg_t<vf_type> y, arg_t<vf_type> x)
{
    vf_type yx=y/x;
    vf_type t=atan_k(abs(yx));
    vf_type y_s = copysign(vf_type(1.0), y);
    vf_type x_s = copysign(vf_type(1.0), x);

    vmf_type y_lt_0 = y_s < 0.0;
    vmf_type x_lt_0 = x_s < 0.0;
    using ctbl=impl::d_real_constants<d_real<double>, double>;

    // default y>=0, x>=0,
    vf_type at= _T::sel(y_lt_0 & x_lt_0,
                        (t - ctbl::m_pi.l()) - ctbl::m_pi.h(),
                        t);
    at = _T::sel(y_lt_0 & (x_s>=0), -t, at);
    at = _T::sel((y_s >=0) & x_lt_0,
                 ctbl::m_pi.h() - (t - ctbl::m_pi.l()),
                 at);
    return at;
}

template <typename _T>
__attribute__((flatten))
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
asin_k_poly(arg_t<vf_type> x2)
{
    // coefficients for asin generated by sollya
    // x^24
    const vf_type asin_c24=0x1.da6730cd2f17dp-6;  // 0x3f9da6730cd2f17d
    // x^22
    const vf_type asin_c22=-0x1.f07d86ab69793p-7;  // 0xbf8f07d86ab69793
    // x^20
    const vf_type asin_c20=0x1.205df65705ee4p-6;  // 0x3f9205df65705ee4
    // x^18
    const vf_type asin_c18=0x1.60a47cef65a9fp-8;  // 0x3f760a47cef65a9f
    // x^16
    const vf_type asin_c16=0x1.52df0d3428baep-7;  // 0x3f852df0d3428bae
    // x^14
    const vf_type asin_c14=0x1.780cd7f878cbdp-7;  // 0x3f8780cd7f878cbd
    // x^12
    const vf_type asin_c12=0x1.c9d1cecf5113fp-7;  // 0x3f8c9d1cecf5113f
    // x^10
    const vf_type asin_c10=0x1.1c4d1bf9d2019p-6;  // 0x3f91c4d1bf9d2019
    // x^8
    const vf_type asin_c8=0x1.6e8bb2fe232bap-6;  // 0x3f96e8bb2fe232ba
    // x^6
    const vf_type asin_c6=0x1.f1c71c14da09cp-6;  // 0x3f9f1c71c14da09c
    // x^4
    const vf_type asin_c4=0x1.6db6db6e4397cp-5;  // 0x3fa6db6db6e4397c
    // x^2
    const vf_type asin_c2=0x1.3333333332dcdp-4;  // 0x3fb3333333332dcd
    // x^0
    const vf_type asin_c0=0x1.5555555555556p-3;  // 0x3fc5555555555556

    vf_type r=x2*impl::poly(x2,
                            asin_c24,
                            asin_c22,
                            asin_c20,
                            asin_c18,
                            asin_c16,
                            asin_c14,
                            asin_c12,
                            asin_c10,
                            asin_c8,
                            asin_c6,
                            asin_c4,
                            asin_c2,
                            asin_c0);
    return r;
}

template <typename _T>
__attribute__((flatten))
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
asin_k(arg_t<vf_type> xc)
{
/* asin(x)
 * Method :
 *      Since  asin(x) = x + x^3/6 + x^5*3/40 + x^7*15/336 + ...
 *      we approximate asin(x) on [0,0.5] by
 *              asin(x) = x + x*x^2*R(x^2)
 *      where
 *              R(x^2) is a rational approximation of (asin(x)-x)/x^3
 *      and its remez error is bounded by
 *              |(asin(x)-x)/x^3 - R(x^2)| < 2^(-58.75)
 *
 *      For x in [0.5,1]
 *              asin(x) = pi/2-2*asin(sqrt((1-x)/2))
 *      Let y = (1-x), z = y/2, s := sqrt(z), and pio2_hi+pio2_lo=pi/2;
 *      then for x>0.98
 *              asin(x) = pi/2 - 2*(s+s*z*R(z))
 *                      = pio2_hi - (2*(s+s*z*R(z)) - pio2_lo)
 *      For x<=0.98, let pio4_hi = pio2_hi/2, then
 *              f = hi part of s;
 *              c = sqrt(z) - f = (z-f*f)/(s+f)         ...f+c=sqrt(z)
 *      and
 *              asin(x) = pi/2 - 2*(s+s*z*R(z))
 *                      = pio4_hi+(pio4-2s)-(2s*z*R(z)-pio2_lo)
 *                      = pio4_hi+(pio4-2f)-(2s*z*R(z)-(pio2_lo+2c))
 *
 * Special cases:
 *      if x is NaN, return x itself;
 *      if |x|>1, return NaN with invalid signal.
 *
 */
    vf_type x=abs(xc);
    using ctbl=impl::d_real_constants<d_real<double>, double>;
    vmf_type x_lt_1_2= x<0.5;
    vf_type x2= x*x;
    vf_type z= (1-x)*0.5;
    vf_type s= sqrt(z);

    vf_type xr=_T::sel(x_lt_1_2, x2, z);
    vf_type r=asin_k_poly(xr);
    vf_type as0= x + x*r;
    // default: x>0.975
    // vf_type as = ctbl::m_pi_2.h() - (2*(s+s*r) - ctbl::m_pi_2.l());
    // x in [0, 1]
    vf_type f=_T::clear_low_word(s);
    vf_type c= (z-f*f)/(s+f);
    vf_type as1= 0.5 * ctbl::m_pi_2.h() -
        (2*s*r - (ctbl::m_pi_2.l() -2 *c) - (0.5*ctbl::m_pi_2.h()-2*f));
    vf_type as=_T::sel(x_lt_1_2, as0, as1);
    as = copysign(as, xc);
    return as;
}

template <typename _T>
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
acos_k(arg_t<vf_type> xc)
{
/* acos(x)
 * Method :
 *      acos(x)  = pi/2 - asin(x)
 *      acos(-x) = pi/2 + asin(x)
 * For |x|<=0.5
 *      acos(x) = pi/2 - (x + x*x^2*R(x^2))     (see asin.c)
 * For x>0.5
 *      acos(x) = pi/2 - (pi/2 - 2asin(sqrt((1-x)/2)))
 *              = 2asin(sqrt((1-x)/2))
 *              = 2s + 2s*z*R(z)        ...z=(1-x)/2, s=sqrt(z)
 *              = 2f + (2c + 2s*z*R(z))
 *     where f=hi part of s, and c = (z-f*f)/(s+f) is the correction term
 *     for f so that f+c ~ sqrt(z).
 * For x<-0.5
 *      acos(x) = pi - 2asin(sqrt((1-|x|)/2))
 *              = pi - 0.5*(s+s*z*R(z)), where z=(1-|x|)/2,s=sqrt(z)
 *
 * Special cases:
 *      if x is NaN, return x itself;
 *      if |x|>1, return NaN with invalid signal.
 *
 * Function needed: sqrt
 */
    vf_type x= xc;

    vmf_type x_lt_m_1_2 = x < -0.5;
    vmf_type x_gt_1_2 = x>0.5;
    vmf_type abs_x_lt_1_2 = abs(x) < 0.5;

    vf_type z= _T::sel(x_lt_m_1_2, (1.0+x)*0.5, (1.0-x)*0.5);
    vf_type s= sqrt(z);
    vf_type x2=x*x;
    vf_type xr= _T::sel(abs_x_lt_1_2, x2, z);
    vf_type r= asin_k_poly(xr);

    // x in [-0.5, 0.5]
    using ctbl=impl::d_real_constants<d_real<double>, double>;
    vf_type ac = ctbl::m_pi_2.h() - (x - (ctbl::m_pi_2.l()-x*r));
    // x in [-1.0, -0.5]
    vf_type wn = r*s - ctbl::m_pi_2.l();
    vf_type ac1= 2*(ctbl::m_pi_2.h() - (s+wn));
    ac = _T::sel(x_lt_m_1_2, ac1, ac);
    // x in [0.5, 1.0]
    vf_type df= _T::clear_low_word(s);
    vf_type c= (z-df*df)/(s+df);
    vf_type wp= r*s+c;
    vf_type ac2=2*(df+wp);
    ac = _T::sel(x_gt_1_2, ac2, ac);
    return ac;
}

template <typename _T>
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
asinh_k(arg_t<vf_type> xc)
{
    vf_type x=abs(xc);
    using ctbl=impl::d_real_constants<d_real<double>, double>;

    vmf_type x_gt_0x1p28 = x > 0x1p28;
    vf_type add_2_log=_T::sel(x_gt_0x1p28, ctbl::m_ln2.h(), vf_type(0));
    vf_type t= x*x;
    vf_type log_arg=_T::sel(x_gt_0x1p28,
                            x,
                            2.0 * x+ 1.0/(sqrt(vf_type(t+1.0))+x));
    vf_type yl= log_k(log_arg, log_func::c_log_e);
    yl += add_2_log;
    // |x| < 2.0
    vf_type log1p_arg= x+t/(1.0+sqrt(vf_type(1.0+t)));
    vf_type ys= log1p_k(log1p_arg);

    // coefficients for asinh_i0 generated by sollya
    // x^28
    const vf_type asinh_c28=0x1.2e7fa190f24aap-12;  // 0x3f32e7fa190f24aa
    // x^26
    const vf_type asinh_c26=-0x1.6fae32f88c581p-10;  // 0xbf56fae32f88c581
    // x^24
    const vf_type asinh_c24=0x1.bd9b2421a3c06p-9;  // 0x3f6bd9b2421a3c06
    // x^22
    const vf_type asinh_c22=-0x1.74ac40798b658p-8;  // 0xbf774ac40798b658
    // x^20
    const vf_type asinh_c20=0x1.fb46e0238ad74p-8;  // 0x3f7fb46e0238ad74
    // x^18
    const vf_type asinh_c18=-0x1.3988cbff637f5p-7;  // 0xbf83988cbff637f5
    // x^16
    const vf_type asinh_c16=0x1.792385a9ecd1fp-7;  // 0x3f8792385a9ecd1f
    // x^14
    const vf_type asinh_c14=-0x1.c960ae256e00dp-7;  // 0xbf8c960ae256e00d
    // x^12
    const vf_type asinh_c12=0x1.1c4b8741d1bebp-6;  // 0x3f91c4b8741d1beb
    // x^10
    const vf_type asinh_c10=-0x1.6e8b61ec18376p-6;  // 0xbf96e8b61ec18376
    // x^8
    const vf_type asinh_c8=0x1.f1c71920f6a9ap-6;  // 0x3f9f1c71920f6a9a
    // x^6
    const vf_type asinh_c6=-0x1.6db6db60ce7f7p-5;  // 0xbfa6db6db60ce7f7
    // x^4
    const vf_type asinh_c4=0x1.3333333319aap-4;  // 0x3fb3333333319aa0
    // x^2
    const vf_type asinh_c2=-0x1.5555555555438p-3;  // 0xbfc5555555555438
    // x^0
    const vf_type asinh_c0=0x1p0;  // 0x3ff0000000000000

    vf_type yss= x* impl::poly(t,
                               asinh_c28,
                               asinh_c26,
                               asinh_c24,
                               asinh_c22,
                               asinh_c20,
                               asinh_c18,
                               asinh_c16,
                               asinh_c14,
                               asinh_c12,
                               asinh_c10,
                               asinh_c8,
                               asinh_c6,
                               asinh_c4,
                               asinh_c2,
                               asinh_c0);

    ys = _T::sel(x<= M_SQRT2*0.5, yss, ys);

    vf_type ash=_T::sel(x <= 2.0, ys, yl);
    ash = copysign(ash, xc);
    return ash;
}

template <typename _T>
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
acosh_k(arg_t<vf_type> xc)
{
    vf_type x=abs(xc);
    using ctbl=impl::d_real_constants<d_real<double>, double>;

    vmf_type x_gt_0x1p26 = x > 0x1p26;
    vf_type add_2_log=_T::sel(x_gt_0x1p26, ctbl::m_ln2.h(), vf_type(0));
    // vf_type t= x*x;
    vf_type log_arg=_T::sel(x_gt_0x1p26,
                            x,
                            2.0*x - 1.0/(x+sqrt(vf_type(x*x-1))));
    vf_type yl= log_k(log_arg, log_func::c_log_e);
    yl += add_2_log;
    vf_type log1p_arg=x-1 + sqrt(vf_type((x-1)*(x-1)+2*(x-1)));
    vf_type ys=log1p_k(log1p_arg);
    vf_type y= _T::sel(x < 2.0, ys, yl);
    return y;
}

template <typename _T>
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
atanh_k(arg_t<vf_type> xc)
{
    vf_type x=abs(xc);
#if 1
    // atanh(x) = x + 1/3*x^3 + 1/5*x^5
    //          = x + x^3/(3+x^2*Q)
    // coefficients for atanh generated by sollya
    // x^24
    const vf_type atanh_c24=-0x1.eaa6148344bbap-5;  // 0xbfaeaa6148344bba
    // x^22
    const vf_type atanh_c22=0x1.0417e7fd6cf59p-5;  // 0x3fa0417e7fd6cf59
    // x^20
    const vf_type atanh_c20=-0x1.2a5d7ddcd430dp-5;  // 0xbfa2a5d7ddcd430d
    // x^18
    const vf_type atanh_c18=-0x1.62fad3535d34ap-7;  // 0xbf862fad3535d34a
    // x^16
    const vf_type atanh_c16=-0x1.5b0338a3e9188p-6;  // 0xbf95b0338a3e9188
    // x^14
    const vf_type atanh_c14=-0x1.8195465f94a12p-6;  // 0xbf98195465f94a12
    // x^12
    const vf_type atanh_c12=-0x1.d871dc746fcd1p-6;  // 0xbf9d871dc746fcd1
    // x^10
    const vf_type atanh_c10=-0x1.28a9ca813dda7p-5;  // 0xbfa28a9ca813dda7
    // x^8
    const vf_type atanh_c8=-0x1.85fd998f2dda5p-5;  // 0xbfa85fd998f2dda5
    // x^6
    const vf_type atanh_c6=-0x1.12282ad9f2aa5p-4;  // 0xbfb12282ad9f2aa5
    // x^4
    const vf_type atanh_c4=-0x1.aeaa46cdfd4cfp-4;  // 0xbfbaeaa46cdfd4cf
    // x^2
    const vf_type atanh_c2=-0x1.a54d880bb38d5p-3;  // 0xbfca54d880bb38d5
    // x^0
    const vf_type atanh_c0=-0x1.ccccccccccccdp0;  // 0xbffccccccccccccd
    vf_type xx=x*x;
    vf_type Q = impl::poly(xx,
                           atanh_c24,
                           atanh_c22,
                           atanh_c20,
                           atanh_c18,
                           atanh_c16,
                           atanh_c14,
                           atanh_c12,
                           atanh_c10,
                           atanh_c8,
                           atanh_c6,
                           atanh_c4,
                           atanh_c2,
                           atanh_c0);
    vf_type ys= x + x*xx/(3.0 + xx * Q);
    vf_type log1p_arg= 2*(x/(1-x));
    vf_type yl= 0.5*log1p_k(log1p_arg);
    vf_type y=_T::sel(x<=0.5, ys, yl);
    y = copysign(y, xc);
    return y;
#else
    // vf_type s=copysign(vf_type(1.0), xc);

    vf_type log1p_arg= _T::sel(x < 0.5,
                               2*x + 2*x*x/(1-x),
                               2*(x/(1-x)));
    vf_type r=0.5*log1p_k(log1p_arg);
    r=copysign(r, xc);
    return r;
#endif
}

template <typename _T>
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
hypot_k(arg_t<vf_type> x, arg_t<vf_type> y)
{
    vf_type xa=abs(x);
    vf_type ya=abs(y);
    vf_type ma=max(xa, ya);
    vf_type mi=min(xa, ya);

    using d_ops=cftal::impl::d_real_ops<vf_type, d_real_traits<vf_type>::fma>;

    vf_type scale=1.0;
    vf_type factor=1.0;
    // avoid underflows
    vmf_type mi_small= mi < 0x1p-450;
    scale = _T::sel(mi_small, 0x1p-450, scale);
    factor= _T::sel(mi_small, 0x1p450, factor);
    // avoid overflows
    vmf_type ma_large= ma > 0x1p510;
    scale = _T::sel(ma_large, 0x1p700, scale);
    factor= _T::sel(ma_large, 0x1p-700, factor);
    ma *= factor;
    mi *= factor;

    dvf_type sqr_ma=d_ops::sqr(ma);
    dvf_type sqr_mi=d_ops::sqr(mi);
    vf_type r= scale*sqrt(vf_type(sqr_ma.h() + sqr_ma.l() +
                                  sqr_mi.h() + sqr_mi.l()));
    return r;
}

template <typename _T>
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
cbrt_k(arg_t<vf_type> xc)
{
    vf_type xp=abs(xc);
    // m in [0.5, 1)
    const divisor<vi2_type, int32_t> idiv3(3);
    vi2_type e = ilogbp1_k(xp);
    vi2_type e3= e / idiv3;
    // vi2_type r3= remainder(e, vi2_type(3), e3);
    vi2_type r3= e-(e3+e3+e3);
    // select r3c so that r3c [-2,-1,0]
    vmi2_type r3gt0 = r3 > 0;
    vi2_type r3c= _T::sel(r3gt0, r3-3, r3);
    vi2_type e3c= _T::sel(r3gt0, e3+1, e3);
    vi2_type sc= r3c - e;
    vf_type mm0 = ldexp_k(xp, sc);
    // coefficients for cbrt generated by sollya
    // x^6
    const vf_type cbrt_c7=0x1.1c945ac4bf089p2;  // 0x4011c945ac4bf089
    // x^6
    const vf_type cbrt_c6=-0x1.34c534877932dp4;  // 0xc0334c534877932d
    // x^5
    const vf_type cbrt_c5=0x1.196acb85dd1e8p5;  // 0x404196acb85dd1e8
    // x^4
    const vf_type cbrt_c4=-0x1.19a93cd3605b3p5;  // 0xc0419a93cd3605b3
    // x^3
    const vf_type cbrt_c3=0x1.5612ed649a7cp4;  // 0x4035612ed649a7c0
    // x^2
    const vf_type cbrt_c2=-0x1.0d81a6c55aa3dp3;  // 0xc020d81a6c55aa3d
    // x^1
    const vf_type cbrt_c1=0x1.546e2634d62e1p1;  // 0x400546e2634d62e1
    // x^0
    const vf_type cbrt_c0=0x1.0f656f18e9921p-2;  // 0x3fd0f656f18e9921
    // vf_type mm = impl::nth_root_approx<3, vf_type>::v(mm0);
    vf_type mm = impl::poly(mm0,
                            cbrt_c7,
                            cbrt_c6,
                            cbrt_c5,
                            cbrt_c4,
                            cbrt_c3,
                            cbrt_c2,
                            cbrt_c1,
                            cbrt_c0);
    // using step_t= impl::nth_root_halley<3, vf_type, vf_type>;
    // for (uint32_t i=0; i<1; ++i) {
    //    mm= step_t::v(mm, mm0);
    // }
    vf_type s=mm*mm*mm;
    mm = mm -(s - mm0) * mm/(2*s+mm0);
    vi2_type hw, lw;
    _T::extract_words(lw, hw, mm);
    // round mm to 17 bits (including the hidden one)
    // round up if the first bit truncated is set
    hw += hw & 0x00000008;
    hw &= 0xfffffff0;
    mm=_T::combine_words(vi2_type(0), hw);
    s= (mm*mm*mm-mm0)/mm0;
    mm = mm - mm * ((((14.0/81.0) * s -(2.0/9.0))*s)+1.0/3.0)*s;
    mm = ldexp_k(mm, e3c);
    mm = copysign(mm, xc);
    return mm;
}


// Local Variables:
// mode: c++
// end:
#endif
