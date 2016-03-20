#if !defined (__MATH_FUNC_F64_H__)
#define __MATH_FUNC_F64_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/t_real.h>
#include <cftal/std_types.h>
#include <cftal/math_common.h>
#include <cftal/math_impl_d_real_constants_f64.h>
#include <cftal/mem.h>
#include <cmath>
#include <iterator>
#include <iostream>

namespace cftal {

    namespace math {

        namespace impl {


        }

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
    xs= _T::sel(is_denom, xs*vf_type(0x1.p53), xs);
    vmi_type i_is_denom= _T::vmf_to_vmi(is_denom);
    eo= _T::sel(i_is_denom, vi_type(-53), eo);
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
        // create m*0x1.0p-1021
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
    xs= _T::sel(is_denom, xs*vf_type(0x1.p53), xs);
    vmi_type i_is_denom= _T::vmf_to_vmi(is_denom);
    eo= _T::sel(i_is_denom, vi_type(-53), eo);
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
    xs= _T::sel(is_denom, xs*vf_type(0x1.p53), xs);
    vmi_type i_is_denom= _T::vmf_to_vmi(is_denom);
    eo= _T::sel(i_is_denom, vi_type(-53), eo);
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
    // const vf_type half[2] = {0.5,-0.5};
    const vf_type ln2hi = 6.93147180369123816490e-01; /* 0x3fe62e42, 0xfee00000 */
    const vf_type ln2lo = 1.90821492927058770002e-10; /* 0x3dea39ef, 0x35793c76 */
    const vf_type invln2 = 1.44269504088896338700e+00; /* 0x3ff71547, 0x652b82fe */
    const vf_type P1   =  1.66666666666666019037e-01; /* 0x3FC55555, 0x5555553E */
    const vf_type P2   = -2.77777777770155933842e-03; /* 0xBF66C16C, 0x16BEBD93 */
    const vf_type P3   =  6.61375632143793436117e-05; /* 0x3F11566A, 0xAF25DE2C */
    const vf_type P4   = -1.65339022054652515390e-06; /* 0xBEBBBD41, 0xC5D26BF1 */
    const vf_type P5   =  4.13813679705723846039e-08; /* 0x3E663769, 0x72BEA4D0 */
    /* expm1(r+c) = expm1(r) + c + expm1(r)*c
                    ~ expm1(r) + c + r*c    */
#if 1
    using ctbl = impl::d_real_constants<d_real<double>, double>;

    vf_type x=xc;
    vf_type kf= rint(vf_type(ctbl::m_1_ln2.h() * x));
    vf_type hi = x - kf * ctbl::m_ln2_cw[0];
    vf_type lo = kf * ctbl::m_ln2_cw[1];
    vf_type xr = hi - lo;
    vf_type cr = (hi-xr)-lo;
    vi_type k= _T::cvt_f_to_i(kf);

    vf_type y=impl::poly(xr, ctbl::native_exp_coeff);
    y *=xr;
    // e^(x,y) ~ e^x + e^x * y + (e^x*y^2)*0.5
    // y=e^x, cr=e^y  -> y + y*cr + 0.5*y*cr^2
    //                   y + cr * (y + 0.5*y *cr)
    y += cr + (xr * cr);
    if (exp_m1 == false) {
        y += 1.0;
    } else {
        // vf_type scale=ldexp(vf_type(1.0), -k);
        vi_type ke= _T::bias - k;
        ke = max(ke, vi_type(1));
        ke = min(ke, vi_type(_T::e_mask));
        vf_type scale=_T::insert_exp(ke);
        y += (vf_type(1.0)-scale);
    }
    y = ldexp(y, k);
    return y;
#else
    vi_type hx= _T::extract_high_word(x);
    vi_type sign= (hx >> 31);
    hx &= 0x7fffffff;

    // vf_type half_sign = copysign(vf_type(0.5), x);
    vi_type k= _T::cvt_f_to_i(invln2*x);
    k = _T::sel(hx >= 0x3ff0a2b2, k, vi_type(1 + sign + sign));
    vf_type kf=_T::cvt_i_to_f(k);
    vf_type hi = x - kf * ln2hi;
    vf_type lo = kf * ln2lo;
    vf_type xr = hi - lo;

    vmi_type i_cmp = hx <= 0x3fd62e42;
    vmf_type f_cmp = _T::vmi_to_vmf(i_cmp);

    k  = _T::sel(i_cmp, vi_type(0), k);
    hi = _T::sel(f_cmp, x, hi);
    lo = _T::sel(f_cmp, vf_type(0), lo);
    xr = _T::sel(f_cmp, x, xr);
    vf_type xx = xr*xr;
    vf_type c = xr - xx*(P1+xx*(P2+xx*(P3+xx*(P4+xx*P5))));
    vf_type y = 1.0 + (xr*c/(2-c) - lo + hi);

    // i_cmp = k == vi_type(0);
    // f_cmp = _T::vmi_to_vmf(i_cmp);
    // y = _T::sel(f_cmp, y, ldexp(y, k));
    y = ldexp(y, k);

    // i_cmp = hx <= 0x3e300000;
    // f_cmp = _T::vmi_to_vmf(i_cmp);
    // y = _T::sel(f_cmp, vf_type(1) + x, y);
    return y;
#endif
#else
    using ctbl = impl::d_real_constants<d_real<double>, double>;

    vmf_type inf_nan= isinf(d) | isnan(d);
    vmf_type finite= ~inf_nan;
    vf_type k_i(0);

    vmf_type d_large = d > ctbl::exp_arg_large;
    vf_type d2=d;
    bool any_of_d_large = any_of(d_large);
    if (any_of_d_large) {
        vf_type dt(_T::sel(d_large, d*vf_type(0.5), d));
        d2=dt;
    }
    // remove exact powers of 2
    vf_type m2= rint(vf_type(d2 * ctbl::m_1_ln2.h()));
    // vf_type r= (d2 - ctbl::m_ln2.h()*m2);
    // subtraction in two steps for higher precision
    vf_type r=d2;
    r = r - m2* ctbl::m_ln2_cw[0];
    r = r - m2* ctbl::m_ln2_cw[1];
    r = r - m2* ctbl::m_ln2_cw[2];
    // reduce arguments further until anything is lt M_LN2/512 ~ 0.0135
    do {
        vmf_type cmp_res = (abs(r) > vf_type(1./64)) & finite;
        if (none_of(cmp_res))
            break;
        k_i += _T::sel(cmp_res, vf_type(1), vf_type(0));
        vf_type d1 = r * vf_type(0.5);
        vf_type d2 = _T::sel(cmp_res, d1, r);
        r = d2;
    } while (1);

    // calculate 1! + x^1/2!+x^2/3! .. +x^7/7!
    vf_type s=impl::poly(r, ctbl::native_exp_coeff);
    // convert to s=x^1/1! + x^2/2!+x^3/3! .. +x^7/7! == expm1(r)
    s = s*r;

    // scale back the 1/k_i reduced value
    do {
        vmf_type cmp_res = k_i > vf_type(0);
        if (none_of(cmp_res))
            break;
        vf_type d1= s * 2.0 + s * s;
        vf_type d2 = _T::sel(cmp_res, d1, s);
        k_i -= vf_type(1);
        s = d2;
    } while (1);
    // const vf_type two(2.0);
    // for (int i=0; i<k_i; ++i)
    //    s = mul_pwr2(s, two) + sqr(s);
    if (exp_m1 == false) {
        s += vf_type(1.0);
    }
    vi_type mi= _T::cvt_f_to_i(m2);
    // scale back
    vf_type res= ldexp(s, mi);
    if (exp_m1 == true) {
        vf_type scale=ldexp(vf_type(1.0), mi);
        res += (scale - vf_type(1.0));
    }
    if (any_of_d_large) {
        vf_type tres(_T::sel(d_large, res*res, res));
        res=tres;
    }
    return res;
#endif
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
