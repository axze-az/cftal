#if !defined (__MATH_FUNC_F64_H__)
#define __MATH_FUNC_F64_H__ 1

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
            static std::pair<vf_type, vi_type>
            native_reduce_trig_arg_k(arg_t<vf_type> x);
            // core sine, cosine calculation
            static void
            native_sin_cos_k(arg_t<vf_type> x,
                             vf_type* s, vf_type* c);

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
#if 1
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    vf_type x=xc;
    vf_type kf= rint(vf_type(ctbl::m_1_ln2.h() * x));
    vf_type hi = x - kf * ctbl::m_ln2_cw[0];
    vf_type lo = kf * ctbl::m_ln2_cw[1];
    vf_type xr = hi - lo;
    vi_type k= _T::cvt_f_to_i(kf);

    vf_type y;
    if (exp_m1 == false) {
#if 1
        const vf_type P5 = 0x1.6373fdc720dadp-25,
            P4= -0x1.bbd415c0fa28bp-20,
            P3= 0x1.1566aaef64906p-14,
            P2= -0x1.6c16c16beabf5p-9,
            P1= 0x1.555555555553dp-3;
        vf_type xx = xr*xr;
        vf_type c = xr - xx*(P1+xx*(P2+xx*(P3+xx*(P4+xx*P5))));
        y = (xr*c/(2-c) - lo + hi);
#else
        vf_type cr = (hi-xr)-lo;
        y=impl::poly(xr, ctbl::native_exp_coeff);
        y *= xr;
        y += cr + (xr * cr);
#endif    
        y += 1.0;
        y = ldexp(y, k);
    } else {
        // vf_type e= xr - y;
        vf_type cr = (hi-xr)-lo;
        const vf_type Q1 = -3.33333333333331316428e-02, /* BFA11111 111110F4 */
            Q2 =  1.58730158725481460165e-03, /* 3F5A01A0 19FE5585 */
            Q3 = -7.93650757867487942473e-05, /* BF14CE19 9EAADBB7 */
            Q4 =  4.00821782732936239552e-06, /* 3ED0CFCA 86E65239 */
            Q5 = -2.01099218183624371326e-07; /* BE8AFDB7 6E09C32D */

        /* x is now in primary range */
        vf_type hfx = 0.5*xr;
        vf_type hxs = xr*hfx;
        vf_type r1 = 1.0+hxs*(Q1+hxs*(Q2+hxs*(Q3+hxs*(Q4+hxs*Q5))));
        vf_type tt  = 3.0-r1*hfx;
        vf_type e  = hxs*((r1-tt)/(6.0 - xr*tt));
        // if (k == 0)   /* c is 0 */
        //      return x - (x*e-hxs);
        e  = xr*(e-cr) - cr;
        e -= hxs;
        // std::cout << std::setprecision(22) << xc << std::endl;
        // std::cout << k << std::endl;
        vi_type t= _T::bias - k;
        // t = max(t, vi_type(1));
        // t = min(t, vi_type(_T::e_mask));
        vf_type two_pow_minus_k=_T::insert_exp(t);
        // xr - e = y --> xr -y = e
        t = _T::bias + k;
        // t = max(t, vi_type(1));
        // t = min(t, vi_type(_T::e_mask));
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
        ym = _T::sel(abs(x) < 0x1p-54, x, ym);
        y = ym;
    }
    return y;
#else
/* origin: FreeBSD /usr/src/lib/msun/src/e_exp.c */
/*
 * ====================================================
 * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
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
    /* expm1(r+c) = expm1(r) + c + expm1(r)*c
                    ~ expm1(r) + c + r*c    */
    // here is the original sun code
    // const vf_type half[2] = {0.5,-0.5};
    // const vf_type ln2hi = 6.93147180369123816490e-01; /* 0x3fe62e42, 0xfee00000 */
    // const vf_type ln2lo = 1.90821492927058770002e-10; /* 0x3dea39ef, 0x35793c76 */
    // const vf_type invln2 = 1.44269504088896338700e+00; /* 0x3ff71547, 0x652b82fe */
    const vf_type P1   =  1.66666666666666019037e-01; /* 0x3FC55555, 0x5555553E */
    const vf_type P2   = -2.77777777770155933842e-03; /* 0xBF66C16C, 0x16BEBD93 */
    const vf_type P3   =  6.61375632143793436117e-05; /* 0x3F11566A, 0xAF25DE2C */
    const vf_type P4   = -1.65339022054652515390e-06; /* 0xBEBBBD41, 0xC5D26BF1 */
    const vf_type P5   =  4.13813679705723846039e-08; /* 0x3E663769, 0x72BEA4D0 */
    
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    vf_type x=xc;
    vf_type kf= rint(vf_type(ctbl::m_1_ln2.h() * x));
    vf_type hi = x - kf * ctbl::m_ln2_cw[0];
    vf_type lo = kf * ctbl::m_ln2_cw[1];
    vf_type xr = hi - lo;
    // vf_type cr = (hi-xr)-lo;
    vi_type k= _T::cvt_f_to_i(kf);

    vf_type xx = xr*xr;
    vf_type c = xr - xx*(P1+xx*(P2+xx*(P3+xx*(P4+xx*P5))));
    vf_type y = (xr*c/(2-c) - lo + hi);

    // y += cr + (xr * cr);
    if (exp_m1 == false) {
        y += 1.0;
    } else {
        vi_type ke= _T::bias - k;
        ke = max(ke, vi_type(1));
        ke = min(ke, vi_type(_T::e_mask));
        vf_type scale=_T::insert_exp(ke);
        y += (vf_type(1.0)-scale);
    }
    // i_cmp = k == vi_type(0);
    // f_cmp = _T::vmi_to_vmf(i_cmp);
    // y = _T::sel(f_cmp, y, ldexp(y, k));
    y = ldexp(y, k);

    // i_cmp = hx <= 0x3e300000;
    // f_cmp = _T::vmi_to_vmf(i_cmp);
    // y = _T::sel(f_cmp, vf_type(1) + x, y);
    return y;
#endif
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
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    vf_type y=impl::poly(xr, ctbl::native_exp2_coeff);
    y *= xr;
    y += 1.0;
    y=ldexp(y, k);
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
    const vf_type Lg1 = 6.666666666666735130e-01;  /* 3FE55555 55555593 */
    const vf_type Lg2 = 3.999999999940941908e-01;  /* 3FD99999 9997FA04 */
    const vf_type Lg3 = 2.857142874366239149e-01;  /* 3FD24924 94229359 */
    const vf_type Lg4 = 2.222219843214978396e-01;  /* 3FCC71C5 1D8E78AF */
    const vf_type Lg5 = 1.818357216161805012e-01;  /* 3FC74664 96CB03DE */
    const vf_type Lg6 = 1.531383769920937332e-01;  /* 3FC39A09 D078C69F */
    const vf_type Lg7 = 1.479819860511658591e-01;  /* 3FC2F112 DF3E5244 */

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
    vf_type w = z*z;
    vf_type t1 = w*(Lg2+w*(Lg4+w*Lg6));
    vf_type t2 = z*(Lg1+w*(Lg3+w*(Lg5+w*Lg7)));
    vf_type R = t2 + t1;
    vf_type dk = _T::cvt_i_to_f(k);
    using ctbl=impl::d_real_constants<d_real<double>, double>;
    vf_type log_x=s*(hfsq+R) + dk*ctbl::m_ln2_cw[1] - hfsq + f + dk*ctbl::m_ln2_cw[0];
    return log_x;
}


template <typename _T>
inline
std::pair<typename cftal::math::func_core<double, _T>::vf_type,
          typename cftal::math::func_core<double, _T>::vi_type>
cftal::math::func_core<double, _T>::
native_reduce_trig_arg_k(arg_t<vf_type> d)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    vmf_type v_large_arg(
        vf_type(ctbl::native_sin_cos_arg_large) < abs(d));

    vf_type qf(rint(vf_type(d * (2 * M_1_PI))));
    vi_type q(_T::cvt_f_to_i(qf));

    vf_type d0(d);
    for (auto b=std::cbegin(ctbl::m_pi_2_cw), e=std::cend(ctbl::m_pi_2_cw);
         b != e; ++b) {
        vf_type t=*b;
        d0 = d0 - qf * t;
    }

    if (any_of(v_large_arg)) {
        // reduce the large arguments
        constexpr std::size_t N=_T::NVF();
        constexpr std::size_t NI=_T::NVI();
        struct alignas(N*sizeof(double)) v_d {
            double _sc[N];
        } tf, d0_l;
        struct alignas(NI*sizeof(int)) v_i {
            int32_t _sc[NI];
        } ti;
        mem<vf_type>::store(tf._sc, d);
        mem<vi_type>::store(ti._sc, q);
        mem<vf_type>::store(d0_l._sc, d0);
        for (std::size_t i=0; i<N; ++i) {
            if (ctbl::native_sin_cos_arg_large < std::fabs(tf._sc[i])) {
                double y[2];
                ti._sc[i]=impl::__ieee754_rem_pio2(tf._sc[i], y);
                d0_l._sc[i]= y[1] + y[0];
            }
        }
        d0 = mem<vf_type>::load(d0_l._sc, N);
        q = mem<vi_type>::load(ti._sc, NI);
    }
    return std::make_pair(d0, q);
}

template <typename _T>
__attribute__((flatten, noinline))
void
cftal::math::func_core<double, _T>::
native_sin_cos_k(arg_t<vf_type> d, vf_type* ps, vf_type* pc)
{
    std::pair<vf_type, vi_type> rq(
        native_reduce_trig_arg_k(d));
    vf_type x= rq.first;
    const vi_type& q= rq.second;

    vf_type x2(x*x);

    using ctbl = impl::d_real_constants<d_real<double>, double>;
    vf_type s = impl::poly(x2, ctbl::native_sin_coeff);
    s = s * x;

    vf_type c= impl::poly(x2, ctbl::native_cos_coeff);

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
