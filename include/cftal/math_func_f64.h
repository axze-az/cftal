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


#include <boost/math/special_functions/erf.hpp>

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

            using d_ops=cftal::impl::d_real_ops<vf_type,
                                                d_real_traits<vf_type>::fma>;
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

            // calculates exp(x*x*sign(s))
            static
            vf_type
            expxx_k(arg_t<vf_type> x, arg_t<vf_type> s);

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


            // error function for [0, 0.75]
            static
            vf_type
            __erf_k_0_75(arg_t<vf_type> x);

            static
            vf_type
            erf_k(arg_t<vf_type> x);

            static
            vf_type
            erfc_k(arg_t<vf_type> x);

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
    vf_type xr = hi - kf * ctbl::m_ln2_cw[1];
    vi_type k= _T::cvt_f_to_i(kf);
    vi2_type k2= _T::vi_to_vi2(k);
#if 1
    // [-0.3465735912322998046875, 0.3465735912322998046875] : | p - f | <= 2^-67.5
    // coefficients for exp generated by sollya
    // x^0 : +0x8p-3
    const vf_type exp_c0=+1.0000000000000000000000e+00;
    // x^1 : +0x8p-3
    const vf_type exp_c1=+1.0000000000000000000000e+00;
    // x^2 : +0x8p-4
    const vf_type exp_c2=+5.0000000000000000000000e-01;
    // x^3 : +0xa.aaaaaaaaaaaa8p-6
    const vf_type exp_c3=+1.6666666666666665741481e-01;
    // x^4 : +0xa.aaaaaaaaaaacp-8
    const vf_type exp_c4=+4.1666666666666685170384e-02;
    // x^5 : +0x8.888888888961p-10
    const vf_type exp_c5=+8.3333333333340843529502e-03;
    // x^6 : +0xb.60b60b60a81p-13
    const vf_type exp_c6=+1.3888888888873365812238e-03;
    // x^7 : +0xd.00d00cfa88cc8p-16
    const vf_type exp_c7=+1.9841269839039331096715e-04;
    // x^8 : +0xd.00d00d6b5b978p-19
    const vf_type exp_c8=+2.4801587348902822885563e-05;
    // x^9 : +0xb.8ef1e87f8178p-22
    const vf_type exp_c9=+2.7557322326013787452785e-06;
    // x^10 : +0x9.3f26623e02258p-25
    const vf_type exp_c10=+2.7557252167692825528943e-07;
    // x^11 : +0xd.72da4d99cea7p-29
    const vf_type exp_c11=+2.5050050656095725290235e-08;
    // x^12 : +0x8.fc5bcb2f9e01p-32
    const vf_type exp_c12=+2.0921639307947645130620e-09;
    // x^13 : +0xb.675e3ad02de48p-36
    const vf_type exp_c13=+1.6594686285988114700473e-10;
#if 1
    vf_type xx=xr*xr;
    vf_type i=impl::poly(xx,
                         exp_c13,
                         exp_c11,
                         exp_c9,
                         exp_c7,
                         exp_c5);
    vf_type j=impl::poly(xx,
                         exp_c12,
                         exp_c10,
                         exp_c8,
                         exp_c6,
                         exp_c4);
    vf_type y=i*xr + j;
    y = impl::poly(xr, y, 
                   exp_c3,
                   exp_c2);
#else
    vf_type y=impl::poly(xr,
                         exp_c13,
                         exp_c12,
                         exp_c11,
                         exp_c10,
                         exp_c9,
                         exp_c8,
                         exp_c7,
                         exp_c6,
                         exp_c5,
                         exp_c4,
                         exp_c3,
                         exp_c2);
#endif
    // correction for errors in argument reduction
    vf_type dx = hi-xr;
    vf_type cr = dx - kf * ctbl::m_ln2_cw[1];
    vf_type yee= cr + cr*xr;
    if (exp_m1 == false) {
        y = impl::poly(xr, y,
                       exp_c1);
        vf_type ye;
        impl::eft_poly(y, ye, xr, y,
                       exp_c0);
        ye += yee;
        y += ye;
        y = scale_exp_k(y, kf, k2);
    } else {
        vf_type ye;
        y = y*xr;
        y = d_ops::two_sum(y, exp_c1, ye);
        impl::eft_poly_si(y, ye, xr, y, ye, exp_c0);
        ye += yee;
        // 2^kf = 2*2^s ; s = kf/2
        vf_type scale = scale_exp_k(vf_type(0.5), kf, k2);
        // e^x-1 = 2*(y * 2^s - 0.5 * 2^s)
        impl::eft_poly_si(y, ye, scale, y, ye, vf_type(-0.5));
        y *= 2;
        y  = y + 2*ye;
    }
    return y;
#else
    vf_type y;
    if (exp_m1 == false) {
        // exp(x) = 1 + 2x/(2-x+x^2*P(x^2)
        //                    x [x - x^2 * P]
        //        = 1 + x + ------------------
        //                    2 - [x - x^2 * P]
        // [0, 0.3465735912322998046875] : | p - f | <= 2^-56.578125
        // coefficients for expn generated by sollya
        // x^0 : +0xa.aaaaaaaaaaaa8p-6
        const vf_type expn_c0=+1.6666666666666665741481e-01;
        // x^2 : -0xb.60b60b60af088p-12
        const vf_type expn_c2=-2.7777777777762209694690e-03;
        // x^4 : +0x8.ab355dd7070ep-17
        const vf_type expn_c4=+6.6137566063822030622971e-05;
        // x^6 : -0xd.debafedf4fbdp-23
        const vf_type expn_c6=-1.6534377129482213292548e-06;
        // x^8 : +0xb.3469aa5968fdp-28
        const vf_type expn_c8=+4.1740899259070261892474e-08;
        // x^10 : -0x8.b38f6a7d59358p-33
        const vf_type expn_c10=-1.0129771083725208005378e-09;
        vf_type xx= xr*xr;
        vf_type P= impl::poly(xx,
                              expn_c10,
                              expn_c8,
                              expn_c6,
                              expn_c4,
                              expn_c2,
                              expn_c0);
        vf_type br= xr- xx*P;
        vf_type dx= hi - xr;
        vf_type cr = dx - kf * ctbl::m_ln2_cw[1];
        y = cr + cr*xr;
        y += (xr*br)/(2.0-br);
        y += xr;
        y += 1;
        y = scale_exp_k(y, kf, k2);
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
        vf_type dx = (hi-xr);
        vf_type cr = dx - kf * ctbl::m_ln2_cw[1];
#if 1
        // coefficients for expm1 generated by sollya
        // x^2 : -0x8.88888888887a8p-8
        const vf_type expm1_c2=-3.3333333333333138581711e-02;
        // x^4 : +0xd.00d00cff30828p-13
        const vf_type expm1_c4=+1.5873015872554529798882e-03;
        // x^6 : -0xa.670ccf68a8e2p-17
        const vf_type expm1_c6=-7.9365075820909145119103e-05;
        // x^8 : +0x8.67e55d0229b4p-21
        const vf_type expm1_c8=+4.0082185537485440587381e-06;
        // x^10 : -0xd.7ef32948d0b58p-26
        const vf_type expm1_c10=-2.0110454926619305237525e-07;
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
        vf_type e  = (hxs*(r1-tt))/(6.0 - xr*tt);
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
                    yt * 2.0 * 0x1p1023,
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
#endif
}


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
    // [-0.5, 0.5] : | p - f | <= 2^-59.609375
    // coefficients for exp2 generated by sollya
    // x^0 : +0x8p-3
    const vf_type exp2_c0=+1.0000000000000000000000e+00;
    // x^1 : +0xb.17217f7d1cf78p-4
    const vf_type exp2_c1=+6.9314718055994528622676e-01;
    // x^2 : +0xf.5fdeffc162c78p-6
    const vf_type exp2_c2=+2.4022650695910072182748e-01;
    // x^3 : +0xe.35846b8250df8p-8
    const vf_type exp2_c3=+5.5504108664823352536910e-02;
    // x^4 : +0x9.d955b7dd26c18p-10
    const vf_type exp2_c4=+9.6181291076280536062049e-03;
    // x^5 : +0xa.ec3ff3c39a9p-13
    const vf_type exp2_c5=+1.3333558145974325204186e-03;
    // x^6 : +0xa.184897c53f1e8p-16
    const vf_type exp2_c6=+1.5403530394041297008935e-04;
    // x^7 : +0xf.fe5fec34fccep-20
    const vf_type exp2_c7=+1.5252734340662214742711e-05;
    // x^8 : +0xb.16010b4ff2958p-23
    const vf_type exp2_c8=+1.3215486327474599750610e-06;
    // x^9 : +0xd.a90da9dddc17p-27
    const vf_type exp2_c9=+1.0177764847202988218759e-07;
    // x^10 : +0xf.268f31ca5926p-31
    const vf_type exp2_c10=+7.0550583650248132384382e-09;
    // x^11 : +0xf.999b10fcc554p-35
    const vf_type exp2_c11=+4.5402040631835683572640e-10;
    // x^12 : +0xe.0857c9dd66898p-39
    const vf_type exp2_c12=+2.5525131689811799440090e-11;
    // x^13 : -0xa.7fd6a5d64da58p-40
    const vf_type exp2_c13=-9.5491204915762316409487e-12;
#if 0
    // this is terrible slow without fma
    vf_type y, ye;
    impl::eft_poly(y, ye, xr,
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
                   exp2_c3,
                   exp2_c2,
                   exp2_c1,
                   exp2_c0);
    y += ye;
#if 0
    vf_type y = exp2_c13;
    vf_type ye;
    vf_type p_i;
    vf_type o_i;
    y = exp2_c13;
    y = d_ops::two_prod(y, xr, p_i);
    y = d_ops::two_sum(y, exp2_c12, o_i);
    ye= (p_i + o_i);

    y = d_ops::two_prod(y, xr, p_i);
    y = d_ops::two_sum(y, exp2_c11, o_i);
    ye= ye* xr +(p_i + o_i);

    y = d_ops::two_prod(y, xr, p_i);
    y = d_ops::two_sum(y, exp2_c10, o_i);
    ye= ye* xr +(p_i + o_i);

    y = d_ops::two_prod(y, xr, p_i);
    y = d_ops::two_sum(y, exp2_c9, o_i);
    ye= ye* xr +(p_i + o_i);

    y = d_ops::two_prod(y, xr, p_i);
    y = d_ops::two_sum(y, exp2_c8, o_i);
    ye= ye* xr +(p_i + o_i);

    y = d_ops::two_prod(y, xr, p_i);
    y = d_ops::two_sum(y, exp2_c7, o_i);
    ye= ye* xr +(p_i + o_i);

    y = d_ops::two_prod(y, xr, p_i);
    y = d_ops::two_sum(y, exp2_c6, o_i);
    ye= ye* xr +(p_i + o_i);

    y = d_ops::two_prod(y, xr, p_i);
    y = d_ops::two_sum(y, exp2_c5, o_i);
    ye= ye* xr +(p_i + o_i);

    y = d_ops::two_prod(y, xr, p_i);
    y = d_ops::two_sum(y, exp2_c4, o_i);
    ye= ye* xr +(p_i + o_i);

    y = d_ops::two_prod(y, xr, p_i);
    y = d_ops::two_sum(y, exp2_c3, o_i);
    ye= ye* xr +(p_i + o_i);

    y = d_ops::two_prod(y, xr, p_i);
    y = d_ops::two_sum(y, exp2_c2, o_i);
    ye= ye* xr +(p_i + o_i);

    y = d_ops::two_prod(y, xr, p_i);
    y = d_ops::two_sum(y, exp2_c1, o_i);
    ye= ye* xr +(p_i + o_i);

    y = d_ops::two_prod(y, xr, p_i);
    y = d_ops::two_sum(y, exp2_c0, o_i);
    ye= ye* xr +(p_i + o_i);
    y += ye;
#endif
#else
#if 1
    vf_type xx=xr*xr;
    vf_type i=impl::poly(xx,
                         exp2_c13,
                         exp2_c11,
                         exp2_c9,
                         exp2_c7,
                         exp2_c5);
    vf_type j=impl::poly(xx,
                         exp2_c12,
                         exp2_c10,
                         exp2_c8,
                         exp2_c6,
                         exp2_c4);
    vf_type y=i*xr + j;
    y = impl::poly(xr, y, 
                   exp2_c3,
                   exp2_c2,
                   exp2_c1);
#else
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
                         exp2_c3,
                         exp2_c2,
                         exp2_c1);
#endif
    vf_type ye;
    impl::eft_poly(y, ye, xr, y,
                   exp2_c0);
    y += ye;
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
    //vf_type lo = kf * ctbl::m_ld2_cw[1];
    vf_type xr = hi - kf * ctbl::m_ld2_cw[1];
    vi_type k= _T::cvt_f_to_i(kf);
    vi2_type k2= _T::vi_to_vi2(k);
    // [-0.15051500499248504638671875, 0.15051500499248504638671875] : | p - f | <= 2^-58.125
    // coefficients for exp10 generated by sollya
    // x^0 : +0x8p-3
    const vf_type exp10_c0=+1.0000000000000000000000e+00;
    // x^1 : +0x9.35d8dddaaa8bp-2
    const vf_type exp10_c1=+2.3025850929940459010936e+00;
    // x^2 : +0xa.9a92639e75348p-2
    const vf_type exp10_c2=+2.6509490552391992146397e+00;
    // x^3 : +0x8.2382c8ef15868p-2
    const vf_type exp10_c3=+2.0346785922932952850317e+00;
    // x^4 : +0x9.5ebb04fecb6bp-3
    const vf_type exp10_c4=+1.1712551489121572068086e+00;
    // x^5 : +0x8.a14ffe9221c28p-4
    const vf_type exp10_c5=+5.3938292924623054691580e-01;
    // x^6 : +0xd.3f6b84295b4ep-6
    const vf_type exp10_c6=+2.0699584871674836517030e-01;
    // x^7 : +0x8.b726f007d29b8p-7
    const vf_type exp10_c7=+6.8089358522816265106847e-02;
    // x^8 : +0xa.08b57519113e8p-9
    const vf_type exp10_c8=+1.9597693008594142122236e-02;
    // x^9 : +0xa.44f7d392d1d4p-11
    const vf_type exp10_c9=+5.0143586580383772699498e-03;
    // x^10 : +0x9.7549b593272p-13
    const vf_type exp10_c10=+1.1545600542363226859166e-03;
    // x^11 : +0xe.ed40542d5b07p-16
    const vf_type exp10_c11=+2.2776432540665174841452e-04;
    // x^12 : +0xb.f1d5ad6f709e8p-18
    const vf_type exp10_c12=+4.5565287435991236114022e-05;
    // x^13 : +0xc.147dcb213d25p-16
    const vf_type exp10_c13=+1.8432685022147710833876e-04;
    // x^ : +0x9.35d8dddaaa8bp-2
    const vf_type log10=+2.3025850929940459010936e+00;
#if 1
    const vf_type log10sqr=log10*log10;
#if 1
    vf_type xx=xr*xr;
    vf_type i=impl::poly(xx,
                         exp10_c13,
                         exp10_c11,
                         exp10_c9,
                         exp10_c7,
                         exp10_c5);
    vf_type j=impl::poly(xx,
                         exp10_c12,
                         exp10_c10,
                         exp10_c8,
                         exp10_c6,
                         exp10_c4);
    vf_type y=i*xr + j;
    y = impl::poly(xr, y, 
                   exp10_c3,
                   exp10_c2,
                   exp10_c1);
#else
    vf_type y=impl::poly(xr,
                         exp10_c13,
                         exp10_c12,
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
                         exp10_c1);
#endif
    vf_type ye;
    impl::eft_poly(y, ye, xr, y,
                   exp10_c0);
    // correction for argument reduction
    vf_type dx= (hi-xr);
    vf_type cr = dx-kf * ctbl::m_ld2_cw[1];
    // f(x) := 10^(r+c);
    // f(x) ~ 10^r + log(10) 10^r c + ..
    // 10^r ~ 1 + log(10) r
    // f(x) ~ 10^r + (1+log(10)*r)*log(10)*c
    //      = 10^r + log(10)*c + log(10)*log(10)*r*c
    vf_type yee1=log10sqr*xr*cr;
    vf_type yee= log10*cr + yee1;
    ye += yee;
    y += ye;
#else
    vf_type y=impl::poly(xr,
                         exp10_c13,
                         exp10_c12,
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
#endif
    y= scale_exp_k(y, kf, k2);
    return y;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
expxx_k(arg_t<vf_type> xc, arg_t<vf_type> s)
{
#if 0
    const vf_type M=128.0;
    const vf_type MINV=1.0/128.0;
    vf_type x=abs(xc);
    vf_type m=MINV*rint(vf_type(M*x));
    vf_type f=x-m;
    vf_type uh=m*m;
    vf_type ul= 2*m*f + f*f;
    vf_type sgn=copysign(vf_type(1.0), s);
    uh *= sgn;
    ul *= sgn;
    vf_type eh=exp_k(uh, false);
    vf_type el=exp_k(ul, false);
    return eh*el;
#else
    // exp(-x*x):
    // log(exp(-x*x)) = -x*x
    // x = h + l;
    // x*x = (h+l)*(h+l) = h^2 + 2*h*l + l^ 2
    vf_type x=abs(vf_type(xc));
    vf_type h, l;
    using traits_t=d_real_traits<vf_type>;
    traits_t::split(x, h, l);
    vf_type uh= h*h;
    vf_type ul= 2*h*l + l*l;
    vf_type sgn=copysign(vf_type(1.0), s);
    uh *= sgn;
    ul *= sgn;
    vf_type eh=exp_k(uh, false);
    vf_type el=exp_k(ul, false);
    vf_type r=eh*el;
    // vf_type xx=xc*xc*sgn;
    // using fc_t = math::func_constants<double>;
    // r= select(xx <= fc_t::exp_lo_zero, vf_type(0), r);
    return r;
#endif
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
    // [3.4694469519536141888238489627838134765625e-18, 1] : | p - f | <= 2^-50
    // coefficients for sinh generated by sollya
    // x^0 : +0xc.0000000000008p-1
    const vf_type sinh_c0=+6.0000000000000008881784e+00;
    // x^2 : -0x9.999999999ca38p-5
    const vf_type sinh_c2=-3.0000000000008636424909e-01;
    // x^4 : +0x8.0bb3ee782901p-10
    const vf_type sinh_c4=+7.8571428585201309735542e-03;
    // x^6 : -0x8.d797bffecaeep-16
    const vf_type sinh_c6=-1.3492064317259424687662e-04;
    // x^8 : +0xc.2b79366720ef8p-23
    const vf_type sinh_c8=+1.4507553942369093147308e-06;
    // x^10 : -0xa.f5fa2c4d6d8ap-32
    const vf_type sinh_c10=-2.5520214317128015392265e-09;
    // x^12 : -0x9.15c1eb16ed0b8p-35
    const vf_type sinh_c12=-2.6440801473562751133314e-10;

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
    // [3.4694469519536141888238489627838134765625e-18, 0.693147182464599609375] : | p - f | <= 2^-64.1875
    // coefficients for cosh generated by sollya
    // x^0 : +0x8p-4
    const vf_type cosh_c0=+5.0000000000000000000000e-01;
    // x^2 : +0xa.aaaaaaaaaaaa8p-8
    const vf_type cosh_c2=+4.1666666666666664353702e-02;
    // x^4 : +0xb.60b60b60b745p-13
    const vf_type cosh_c4=+1.3888888888890249008468e-03;
    // x^6 : +0xd.00d00cfbf9fb8p-19
    const vf_type cosh_c6=+2.4801587299439595317918e-05;
    // x^8 : +0x9.3f27e3ec2ce78p-25
    const vf_type cosh_c8=+2.7557320678283791649579e-07;
    // x^10 : +0x8.f75ee555b55d8p-32
    const vf_type cosh_c10=+2.0876274783143503579269e-09;
    // x^12 : +0xc.b279999c86d88p-40
    const vf_type cosh_c12=+1.1548006995718819778011e-11;
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
    vmf_type x_gt_ln_3_2= x > 0.5625;
    vf_type tanh_x_gt_ln_3_2 = 1.0 - 2.0/(em1+2);

    // [0, 0.5625] : | p - f | <= 2^-63.59375
    // coefficients for tanh generated by sollya
    // x^1 : +0x8p-3
    const vf_type tanh_c1=+1.0000000000000000000000e+00;
    // x^2 : +0x8.ba7dee5430eap-56
    const vf_type tanh_c2=+1.2113204958725435054473e-16;
    // x^3 : -0xa.aaaaaaaaaba4p-5
    const vf_type tanh_c3=-3.3333333333336101489408e-01;
    // x^4 : +0x9.d92edf7f1479p-42
    const vf_type tanh_c4=+2.2392604195649190452381e-12;
    // x^5 : +0x8.8888886f1c348p-6
    const vf_type tanh_c5=+1.3333333324084442605972e-01;
    // x^6 : +0x9.d89e8fdd302p-32
    const vf_type tanh_c6=+2.2924899737433110272715e-09;
    // x^7 : -0xd.d0ddae30ff68p-8
    const vf_type tanh_c7=-5.3968291308590488064567e-02;
    // x^8 : +0xe.3146e95a37d18p-25
    const vf_type tanh_c8=+4.2296911102897322466901e-07;
    // x^9 : +0xb.320640ea7469p-9
    const vf_type tanh_c9=+2.1866031097695089180366e-02;
    // x^10 : +0xa.f3c0139f1479p-19
    const vf_type tanh_c10=+2.0889567579320798579746e-05;
    // x^11 : -0x9.2c400e71a8b5p-10
    const vf_type tanh_c11=-8.9578636947542263080368e-03;
    // x^12 : +0xa.97b3266761c5p-15
    const vf_type tanh_c12=+3.2325980719876605627011e-04;
    // x^13 : +0xb.4ff285388a378p-12
    const vf_type tanh_c13=+2.7617906048669686562558e-03;
    // x^14 : +0xc.f423a92aecd48p-13
    const vf_type tanh_c14=+1.5812584400386275971379e-03;
    // x^15 : -0xe.d10d9ac2ff7cp-12
    const vf_type tanh_c15=-3.6173373629820836094861e-03;
    // x^16 : +0x8.1594d45c3ecap-12
    const vf_type tanh_c16=+1.9737065938582685348246e-03;
    // x^17 : -0xc.c65594c3b6598p-15
    const vf_type tanh_c17=-3.8985422864152712322736e-04;
    vf_type R= impl::poly(x,
                          tanh_c17,
                          tanh_c16,
                          tanh_c15,
                          tanh_c14,
                          tanh_c13,
                          tanh_c12,
                          tanh_c11,
                          tanh_c10,
                          tanh_c9,
                          tanh_c8,
                          tanh_c7,
                          tanh_c6,
                          tanh_c5,
                          tanh_c4,
                          tanh_c3,
                          tanh_c2,
                          tanh_c1);
    vf_type tanh_x_small = R * x;
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
    // [3.4694469519536141888238489627838134765625e-18, 0.17157287895679473876953125] : | p - f | <= 2^-64.625
    // coefficients for log generated by sollya
    // x^2 : +0xa.aaaaaaaaaaaa8p-4
    const vf_type log_c2=+6.6666666666666662965923e-01;
    // x^4 : +0xc.ccccccccceac8p-5
    const vf_type log_c4=+4.0000000000005325739849e-01;
    // x^6 : +0x9.24924921770b8p-5
    const vf_type log_c6=+2.8571428569168361155661e-01;
    // x^8 : +0xe.38e392e2fd49p-6
    const vf_type log_c8=+2.2222222656633455750708e-01;
    // x^10 : +0xb.a2e6dba5baafp-6
    const vf_type log_c10=+1.8181773614825663676342e-01;
    // x^12 : +0x9.d90aca733a8d8p-6
    const vf_type log_c12=+1.5387220163840073516859e-01;
    // x^14 : +0x8.7a5091423103p-6
    const vf_type log_c14=+1.3246549783140454392694e-01;
    // x^16 : +0x8.811edd68c1cb8p-6
    const vf_type log_c16=+1.3288089391701582431260e-01;
#if 1
    vf_type w = z*z;
    vf_type t1= z*impl::poly(w,
                             log_c14,
                             log_c10,
                             log_c6,
                             log_c2);
    vf_type t2= impl::poly(w,
                           log_c16,
                           log_c12,
                           log_c8,
                           log_c4);
    vf_type y = t2*w + t1;
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
    vf_type hfsq = (0.5*f)*f;
    vf_type s = f/(2.0+f);
    vf_type z = s*s;

    // split of the polynomial reduces precision
    vf_type R = log_k_poly(z);
    vf_type res;
    vf_type kf = _T::cvt_i_to_f(_T::vi2_odd_to_vi(k));
    if (func == log_func::c_log_e) {
        using ctbl=impl::d_real_constants<d_real<double>, double>;
        vf_type log_x=s*(hfsq+R);
        log_x += kf*ctbl::m_ln2_cw[1];
        log_x -= hfsq;
        log_x += f;
        log_x += kf*ctbl::m_ln2_cw[0];
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

    vf_type hfsq = (0.5*f)*f;
    vf_type s = f/(2.0+f);
    vf_type z = s*s;
    vf_type R = log_k_poly(z);

    using ctbl=impl::d_real_constants<d_real<double>, double>;
    vf_type log1p_x= s*(hfsq+R);
    log1p_x += kf*ctbl::m_ln2_cw[1] +c;
    log1p_x -= hfsq;
    log1p_x += f;
    log1p_x += kf*ctbl::m_ln2_cw[0];
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
    // [3.4694469519536141888238489627838134765625e-18, 0.785398185253143310546875] : | p - f | <= 2^-57.875
    // coefficients for sin generated by sollya
    // x^2 : -0xa.aaaaaaaaaaa4p-6
    const vf_type sin_c2=-1.6666666666666629659233e-01;
    // x^4 : +0x8.888888887bbp-10
    const vf_type sin_c4=+8.3333333333219239413836e-03;
    // x^6 : -0xd.00d00cdf95c08p-16
    const vf_type sin_c6=-1.9841269829464980235974e-04;
    // x^8 : +0xb.8ef1aafd29de8p-22
    const vf_type sin_c8=+2.7557313585037963205341e-06;
    // x^10 : -0xd.72f2a80609a48p-29
    const vf_type sin_c10=-2.5050742816066743808360e-08;
    // x^12 : +0xa.ec73141479948p-36
    const vf_type sin_c12=+1.5895975168099208266046e-10;

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
    // [3.4694469519536141888238489627838134765625e-18, 0.785398185253143310546875] : | p - f | <= 2^-60.953125
    // coefficients for cos generated by sollya
    // x^4 : +0xa.aaaaaaaaaaaa8p-8
    const vf_type cos_c4=+4.1666666666666664353702e-02;
    // x^6 : -0xb.60b60b60b465p-13
    const vf_type cos_c6=-1.3888888888887057117272e-03;
    // x^8 : +0xd.00d00cf9c1c8p-19
    const vf_type cos_c8=+2.4801587298453923405989e-05;
    // x^10 : -0x9.3f27d0171f35p-25
    const vf_type cos_c10=-2.7557317155370230123010e-07;
    // x^12 : +0x8.f75abe99be69p-32
    const vf_type cos_c12=+2.0876127299141133743184e-09;
    // x^14 : -0xc.839c2b11f7e6p-40
    const vf_type cos_c14=-1.1381509182935641183027e-11;

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
    // [3.4694469519536141888238489627838134765625e-18, 0.673198401927947998046875] : | p - f | <= 2^-59.203125
    // coefficients for tan generated by sollya
    // x^2 : +0xa.aaaaaaaaaab1p-5
    const vf_type tan_c2=+3.3333333333333403647458e-01;
    // x^4 : +0x8.888888887ff8p-6
    const vf_type tan_c4=+1.3333333333321162328389e-01;
    // x^6 : +0xd.d0dd0dd8f576p-8
    const vf_type tan_c6=+5.3968253975616636841650e-02;
    // x^8 : +0xb.327a42296588p-9
    const vf_type tan_c8=+2.1869488312130036522518e-02;
    // x^10 : +0x9.1371efe0de738p-10
    const vf_type tan_c10=+8.8632395420220177334469e-03;
    // x^12 : +0xe.b6922b69db5ap-12
    const vf_type tan_c12=+3.5920819997191325706476e-03;
    // x^14 : +0xb.edd9ef641aa88p-13
    const vf_type tan_c14=+1.4561897797905241306454e-03;
    // x^16 : +0x9.a2ce102c6538p-14
    const vf_type tan_c16=+5.8813212735338120384920e-04;
    // x^18 : +0x8.111418046d13p-15
    const vf_type tan_c18=+2.4617653983530424829235e-04;
    // x^20 : +0xa.53a6a90d99118p-17
    const vf_type tan_c20=+7.8786939890559045947087e-05;
    // x^22 : +0x9.403fb8f2a8ff8p-17
    const vf_type tan_c22=+7.0579317683901174654802e-05;
    // x^24 : -0x9.62efe0aba1318p-19
    const vf_type tan_c24=-1.7903275951360724942444e-05;
    // x^26 : +0xd.767c03ce18978p-19
    const vf_type tan_c26=+2.5678310044561697059315e-05;

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
    // [3.4694469519536141888238489627838134765625e-18, 0.4375] : | p - f | <= 2^-55.578125
    // coefficients for atan generated by sollya
    // x^0 : +0xa.aaaaaaaaaaaa8p-5
    const vf_type atan_c0=+3.3333333333333331482962e-01;
    // x^2 : -0xc.cccccccccbecp-6
    const vf_type atan_c2=-1.9999999999998752109320e-01;
    // x^4 : +0x9.24924923ecb9p-6
    const vf_type atan_c4=+1.4285714285479006457891e-01;
    // x^6 : -0xe.38e38dcb8c098p-7
    const vf_type atan_c6=-1.1111111091221941016283e-01;
    // x^8 : +0xb.a2e8a66330358p-7
    const vf_type atan_c8=+9.0909081691621970722217e-02;
    // x^10 : -0x9.d89b5a3a9692p-7
    const vf_type atan_c10=-7.6922816330967480613623e-02;
    // x^12 : +0x8.8860741c15338p-7
    const vf_type atan_c12=+6.6661888784588549383692e-02;
    // x^14 : -0xf.0b35042500c3p-8
    const vf_type atan_c14=-5.8764756690837180452824e-02;
    // x^16 : +0xd.59042ba8433ap-8
    const vf_type atan_c16=+5.2139530809893225304918e-02;
    // x^18 : -0xb.798b2c169a4c8p-8
    const vf_type atan_c18=-4.4823358787291663063446e-02;
    // x^20 : +0x8.6d95ca9f7d6ep-8
    const vf_type atan_c20=+3.2922136276729324633195e-02;
    // x^22 : -0xe.efef0dee26fa8p-10
    const vf_type atan_c22=-1.4587149834858851096819e-02;

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
    // [3.4694469519536141888238489627838134765625e-18, 0.5] : | p - f | <= 2^-55.578125
    // coefficients for asin generated by sollya
    // x^0 : +0xa.aaaaaaaaaaabp-6
    const vf_type asin_c0=+1.6666666666666668517038e-01;
    // x^2 : +0x9.9999999996e68p-7
    const vf_type asin_c2=+7.4999999999980818121692e-02;
    // x^4 : +0xb.6db6db721cbep-8
    const vf_type asin_c4=+4.4642857146857090056002e-02;
    // x^6 : +0xf.8e38e0a6d04ep-9
    const vf_type asin_c6=+3.0381944106381383874371e-02;
    // x^8 : +0xb.745d97f1195dp-9
    const vf_type asin_c8=+2.2372174069959817332975e-02;
    // x^10 : +0x8.e268dfce900c8p-9
    const vf_type asin_c10=+1.7352368660141424122623e-02;
    // x^12 : +0xe.4e8e767a889f8p-10
    const vf_type asin_c12=+1.3971544247973198202284e-02;
    // x^14 : +0xb.c066bfc3c65e8p-10
    const vf_type asin_c14=+1.1476140455619060834480e-02;
    // x^16 : +0xa.96f869a145d7p-10
    const vf_type asin_c16=+1.0341531226293412121242e-02;
    // x^18 : +0xb.0523e77b2d4f8p-11
    const vf_type asin_c18=+5.3808980004733933041883e-03;
    // x^20 : +0x9.02efb2b82f72p-9
    const vf_type asin_c20=+1.7600527349798236742551e-02;
    // x^22 : -0xf.83ec355b4bc98p-10
    const vf_type asin_c22=-1.5151682621602968401020e-02;
    // x^24 : +0xe.d339866978be8p-9
    const vf_type asin_c24=+2.8955266626085929965173e-02;

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
    vmf_type abs_x_le_1_2 = abs(x) <= 0.5;

    vf_type z= _T::sel(x_lt_m_1_2, (1.0+x)*0.5, (1.0-x)*0.5);
    vf_type s= sqrt(z);
    vf_type x2=x*x;
    vf_type xr= _T::sel(abs_x_le_1_2, x2, z);
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

    // [3.4694469519536141888238489627838134765625e-18, 0.707106769084930419921875] : | p - f | <= 2^-56
    // coefficients for asinh generated by sollya
    // x^0 : +0x8p-3
    const vf_type asinh_c0=+1.0000000000000000000000e+00;
    // x^2 : -0xa.aaaaaaaaaa1cp-6
    const vf_type asinh_c2=-1.6666666666665874707576e-01;
    // x^4 : +0x9.99999998cd5p-7
    const vf_type asinh_c4=+7.4999999998548450008684e-02;
    // x^6 : -0xb.6db6db0673fb8p-8
    const vf_type asinh_c6=-4.4642857048941601838532e-02;
    // x^8 : +0xf.8e38c907b54dp-9
    const vf_type asinh_c8=+3.0381941356476184490365e-02;
    // x^10 : -0xb.745b0f60c1bbp-9
    const vf_type asinh_c10=-2.2372098567191987805725e-02;
    // x^12 : +0x8.e25c3a0e8df58p-9
    const vf_type asinh_c12=+1.7351991736429466656189e-02;
    // x^14 : -0xe.4b05712b70068p-10
    const vf_type asinh_c14=-1.3958058388070094038569e-02;
    // x^16 : +0xb.c91c2d4f668f8p-10
    const vf_type asinh_c16=+1.1509361520302406264871e-02;
    // x^18 : -0x9.cc465ffb1bfa8p-10
    const vf_type asinh_c18=-9.5683094102944985653858e-03;
    // x^20 : +0xf.da37011c56bap-11
    const vf_type asinh_c20=+7.7404305662115320540995e-03;
    // x^22 : -0xb.a56203cc5b2cp-11
    const vf_type asinh_c22=-5.6865365418566557464963e-03;
    // x^24 : +0xd.ecd9210d1e03p-12
    const vf_type asinh_c24=+3.3997041326254721568811e-03;
    // x^26 : -0xb.7d7197c462c08p-13
    const vf_type asinh_c26=-1.4025896654284721824096e-03;
    // x^28 : +0x9.73fd0c879255p-15
    const vf_type asinh_c28=+2.8848510652019576736699e-04;

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
#if 1
    vf_type xm1l;
    vf_type xm1=d_ops::two_diff(x, vf_type(1), xm1l);
    dvf_type sqrt2xm1=sqrt(mul_pwr2(dvf_type(xm1, xm1l), vf_type(2)));
    // acosh(x) = sqrt(2*x) * [1-1/12*x+3/160*x^2-5/896*x^3+ ...]
    // [3.4694469519536141888238489627838134765625e-18, 1] : | p - f | <= 2^-62.75
    // coefficients for acosh generated by sollya
    // x^0 : +0x8p-3
    const vf_type acosh_c0=+1.0000000000000000000000e+00;
    // x^1 : -0xa.aaaaaaaaaaa9p-7
    const vf_type acosh_c1=-8.3333333333333287074041e-02;
    // x^2 : +0x9.99999999969dp-9
    const vf_type acosh_c2=+1.8749999999994694521721e-02;
    // x^3 : -0xb.6db6db6bccc88p-11
    const vf_type acosh_c3=-5.5803571426395063084791e-03;
    // x^4 : +0xf.8e38e2ed17b48p-13
    const vf_type acosh_c4=+1.8988715231981984164072e-03;
    // x^5 : -0xb.745d07569c688p-14
    const vf_type acosh_c5=-6.9912991362188804406880e-04;
    // x^6 : +0x8.e2751de7a3f1p-15
    const vf_type acosh_c6=+2.7113646120568827852654e-04;
    // x^7 : -0xe.4cb4bce8dd5ep-17
    const vf_type acosh_c7=-1.0909754060304648884058e-04;
    // x^8 : +0xb.d372715f209dp-18
    const vf_type acosh_c8=+4.5112476384836415759134e-05;
    // x^9 : -0x9.fa0bf6aacc0ep-19
    const vf_type acosh_c9=-1.9029131029489704750833e-05;
    // x^10 : +0x8.8081ba4f05f9p-20
    const vf_type acosh_c10=+8.1081194769401966767567e-06;
    // x^11 : -0xe.55cbc4be4ec28p-22
    const vf_type acosh_c11=-3.4177638318537515068880e-06;
    // x^12 : +0xb.72c013cb57d08p-23
    const vf_type acosh_c12=+1.3647369584241793363111e-06;
    // x^13 : -0x8.0cd10a91b969p-24
    const vf_type acosh_c13=-4.7982124786910910239706e-07;
    // x^14 : +0x8.f8c9d4867b86p-26
    const vf_type acosh_c14=+1.3369068032649017936561e-07;
    // x^15 : -0xd.91588be74b8bp-29
    const vf_type acosh_c15=-2.5271917436897211509152e-08;
    // x^16 : +0xa.262fe8ff68a98p-32
    const vf_type acosh_c16=+2.3630374462414833615335e-09;
    vf_type ys=impl::poly(xm1,
                          acosh_c16,
                          acosh_c15,
                          acosh_c14,
                          acosh_c13,
                          acosh_c12,
                          acosh_c11,
                          acosh_c10,
                          acosh_c9,
                          acosh_c8,
                          acosh_c7,
                          acosh_c6,
                          acosh_c5,
                          acosh_c4,
                          acosh_c3,
                          acosh_c2,
                          acosh_c1,
                          acosh_c0);
    ys= (sqrt2xm1 * ys).h();
#else
    vf_type log1p_arg=x-1 + sqrt(vf_type((x-1)*(x-1)+2*(x-1)));
    vf_type ys=log1p_k(log1p_arg);
#endif
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
    // [3.4694469519536141888238489627838134765625e-18, 0.5] : | p - f | <= 2^-54.3125
    // coefficients for atanh generated by sollya
    // x^0 : -0xe.6666666666668p-3
    const vf_type atanh_c0=-1.8000000000000000444089e+00;
    // x^2 : -0xd.2a6c405d9c6a8p-6
    const vf_type atanh_c2=-2.0571428571424257847333e-01;
    // x^4 : -0xd.7552366fea678p-7
    const vf_type atanh_c4=-1.0514285715165104517776e-01;
    // x^6 : -0x8.914156cf95528p-7
    const vf_type atanh_c6=-6.6932837856408314292089e-02;
    // x^8 : -0xc.2feccc796ed28p-8
    const vf_type atanh_c8=-4.7606277389998376270430e-02;
    // x^10 : -0x9.454e5409eed38p-8
    const vf_type atanh_c10=-3.6213775174412980717431e-02;
    // x^12 : -0xe.c38ee3a37e688p-9
    const vf_type atanh_c12=-2.8835740363999221719249e-02;
    // x^14 : -0xc.0caa32fca509p-9
    const vf_type atanh_c14=-2.3534125064836493301801e-02;
    // x^16 : -0xa.d819c51f48c4p-9
    const vf_type atanh_c16=-2.1179967224854517882093e-02;
    // x^18 : -0xb.17d69a9ae9a5p-10
    const vf_type atanh_c18=-1.0833123384807703121213e-02;
    // x^20 : -0x9.52ebeee6a1868p-8
    const vf_type atanh_c20=-3.6421533418098041290367e-02;
    // x^22 : +0x8.20bf3feb67ac8p-8
    const vf_type atanh_c22=+3.1749680619582228147113e-02;
    // x^24 : -0xf.5530a41a25ddp-8
    const vf_type atanh_c24=-5.9893646301268657627936e-02;
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

namespace cftal {
    namespace math {
        namespace impl {
            
            template <typename _V>
            struct erf_res {
                _V _x;
                _V _yh;
                _V _yl;
                _V _c0h;
                _V _c0l;

                erf_res(_V x, _V yh, _V yl, _V c0h, _V c0l)
                    : _x(x), _yh(yh), _yl(yl), _c0h(c0h), _c0l(c0l) {}
            };

            template <typename _V>
            _V
            final_result(const erf_res<_V>& r)
            {
                _V rh, rl;
                eft_poly_si(rh, rl, r._x, r._yh, r._yl, r._c0h);
                rh += (rl + r._c0l);
                return rh;
            };

            template <typename _M, typename _V>
            erf_res<_V>
            select(const _M& m, const erf_res<_V>& t, const erf_res<_V>& f)
            {
                erf_res<_V> r(select(m, t._x, f._x),
                              select(m, t._yh, f._yh),
                              select(m, t._yl, f._yl),
                              select(m, t._c0h, f._c0l),
                              select(m, t._c0l, f._c0l));
                return r;
            }
            
        }
    }
}

template <typename _T>
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
erf_k(arg_t<vf_type> xc)
{

    vf_type x=abs(xc);

    auto i0 = [x]() -> vf_type {
        // [3.4694469519536141888238489627838134765625e-18, 0.75] : | p - f | <= 2^-60.78125
        // coefficients for erf_i0 generated by sollya
        // x^1 : +0x9.06eba8214db68p-3
        const vf_type erf_i0_c1=+1.1283791670955125585607e+00;
        // x^3 : -0xc.093a3581bcdep-5
        const vf_type erf_i0_c3=-3.7612638903183515104445e-01;
        // x^5 : +0xe.71790d0206a48p-7
        const vf_type erf_i0_c5=+1.1283791670944255669529e-01;
        // x^7 : -0xd.c167188f35fap-9
        const vf_type erf_i0_c7=-2.6866170642829659276352e-02;
        // x^9 : +0xa.b2de6784c358p-11
        const vf_type erf_i0_c9=+5.2239775983210917642552e-03;
        // x^11 : -0xe.016d6a3ef017p-14
        const vf_type erf_i0_c11=-8.5483250675988885734780e-04;
        // x^13 : +0xf.cd116c04eb3cp-17
        const vf_type erf_i0_c13=+1.2055242224015018642075e-04;
        // x^15 : -0xf.a5d4b323d2f78p-20
        const vf_type erf_i0_c15=-1.4922882834294901377502e-05;
        // x^17 : +0xd.c359e3d2a913p-23
        const vf_type erf_i0_c17=+1.6406882240210931047373e-06;
        // x^19 : -0xa.83e395b26706p-26
        const vf_type erf_i0_c19=-1.5668856230000872722501e-07;
        // x^21 : +0xa.6cd8665fd081p-30
        const vf_type erf_i0_c21=+9.7092026848530503315802e-09;
        // x^23 : +0x8.91a24edd71ee8p-34
        const vf_type erf_i0_c23=+4.9877462876900157143168e-10;
        vf_type xx= x*x;
        vf_type y_i0= impl::poly(xx,
                                 erf_i0_c23,
                                 erf_i0_c21,
                                 erf_i0_c19,
                                 erf_i0_c17,
                                 erf_i0_c15,
                                 erf_i0_c13,
                                 erf_i0_c11,
                                 erf_i0_c9,
                                 erf_i0_c7,
                                 erf_i0_c5,
                                 erf_i0_c3);
        vf_type ye;
        impl::eft_poly(y_i0, ye, xx, y_i0,
                       erf_i0_c1);
        vf_type p_i;
        y_i0 = d_ops::two_prod(y_i0, x, p_i);
        ye = ye*x + p_i;
        //
        // impl::eft_poly_si(y_i0, ye, x, y_i0, ye,
        //                   0.0);
        y_i0 += ye;
        return y_i0;
    };

    auto i1 = [x]()-> vf_type {
        // [0.75, 1.875] : | p - f | <= 2^-65.65625
        // coefficients for erf_i1 generated by sollya
        // x^0 h: +0xd.a00ad76b9204p-4
        const vf_type erf_i1_c0h=+8.5157283924593318857887e-01;
        // x^0 l: +0xe.0bace157c715p-59
        const vf_type erf_i1_c0l=+2.4365243665033013894766e-17;
        // x^1 : +0xc.b59ff8cfc23f8p-5
        const vf_type erf_i1_c1=+3.9717100711829539383402e-01;
        // x^2 : -0xc.fcb4a8d44e408p-5
        const vf_type erf_i1_c2=-4.0584786390758870178175e-01;
        // x^3 : +0x9.38b3dd1da6eb8p-6
        const vf_type erf_i1_c3=+1.4408585160582162987275e-01;
        // x^4 : +0xf.c9546cfdda59p-8
        const vf_type erf_i1_c4=+6.1665798768311033684064e-02;
        // x^5 : -0x8.c2586d568b56p-7
        const vf_type erf_i1_c5=-6.8430951488233915380732e-02;
        // x^6 : +0xe.0ef0a178d53f8p-11
        const vf_type erf_i1_c6=+6.8644332196564619361090e-03;
        // x^7 : +0xe.a1c48a68778fp-10
        const vf_type erf_i1_c7=+1.4288969943769876808082e-02;
        // x^8 : -0xa.7d0064636f1fp-11
        const vf_type erf_i1_c8=-5.1212340007889527865315e-03;
        // x^9 : -0xd.3bf0ea237c58p-13
        const vf_type erf_i1_c9=-1.6154961932524462830951e-03;
        // x^10 : +0xa.29b9c60073768p-13
        const vf_type erf_i1_c10=+1.2405994784913624163353e-03;
        // x^11 : +0x8.e07992a9980b8p-18
        const vf_type erf_i1_c11=+3.3862514706578683988236e-05;
        // x^12 : -0xc.b25c1918cbf1p-16
        const vf_type erf_i1_c12=-1.9373653876469861543144e-04;
        // x^13 : +0xd.76eba164d97cp-19
        const vf_type erf_i1_c13=+2.5681558485523913555257e-05;
        // x^14 : +0xb.6d8849d428178p-19
        const vf_type erf_i1_c14=+2.1796914760299927396733e-05;
        // x^15 : -0xc.e3e4daac0ea3p-21
        const vf_type erf_i1_c15=-6.1465314806838005837327e-06;
        // x^16 : -0xe.b8e83c40bb9ap-23
        const vf_type erf_i1_c16=-1.7550341642395222597627e-06;
        // x^17 : +0xe.9642d594a2f9p-24
        const vf_type erf_i1_c17=+8.6945040884462715306098e-07;
        // x^18 : +0x8.434fa13b037d8p-26
        const vf_type erf_i1_c18=+1.2312730855381382499845e-07;
        // x^19 : -0x9.8f7487e83636p-26
        const vf_type erf_i1_c19=-1.4246064231133920797507e-07;
        // x^20 : +0x8.aad670629c2d8p-28
        const vf_type erf_i1_c20=+3.2288337422680242895254e-08;
        // x^21 : -0x9.eb079386d623p-32
        const vf_type erf_i1_c21=-2.3092339641415239179504e-09;
        // x^ : +0xcp-4
        const vf_type erf_i1_left=+7.5000000000000000000000e-01;
        // x^ : +0x8.2cbdfp-3
        const vf_type erf_i1_x0=+1.0218466520309448242188e+00;
        vf_type x_i1 = x - erf_i1_x0;
#if 1
        vf_type xx= x_i1*x_i1;
        vf_type i= impl::poly(xx,
                              erf_i1_c21,
                              erf_i1_c19,
                              erf_i1_c17,
                              erf_i1_c15,
                              erf_i1_c13,
                              erf_i1_c11,
                              erf_i1_c9,
                              erf_i1_c7,
                              erf_i1_c5);
        vf_type j= impl::poly(xx,
                              erf_i1_c20,
                              erf_i1_c18,
                              erf_i1_c16,
                              erf_i1_c14,
                              erf_i1_c12,
                              erf_i1_c10,
                              erf_i1_c8,
                              erf_i1_c6,
                              erf_i1_c4);
        vf_type y_i1= i*x_i1 + j;
        y_i1 = impl::poly(x_i1, y_i1,
                          erf_i1_c3,
                          erf_i1_c2,
                          erf_i1_c1);
#else
        vf_type y_i1= impl::poly(x_i1,
                                 erf_i1_c21,
                                 erf_i1_c20,
                                 erf_i1_c19,
                                 erf_i1_c18,
                                 erf_i1_c17,
                                 erf_i1_c16,
                                 erf_i1_c15,
                                 erf_i1_c14,
                                 erf_i1_c13,
                                 erf_i1_c12,
                                 erf_i1_c11,
                                 erf_i1_c10,
                                 erf_i1_c9,
                                 erf_i1_c8,
                                 erf_i1_c7,
                                 erf_i1_c6,
                                 erf_i1_c5,
                                 erf_i1_c4,
                                 erf_i1_c3,
                                 erf_i1_c2,
                                 erf_i1_c1);
#endif
        vf_type ye;
        impl::eft_poly(y_i1, ye, x_i1, y_i1,
                       erf_i1_c0h);
        y_i1 += ye+erf_i1_c0l;
        return y_i1;
    };

    auto i2 = [x]()->vf_type {
        // [1.875, 3.5] : | p - f | <= 2^-60.90625
        // coefficients for erf_i2 generated by sollya
        // x^0 h: +0xf.ef9817e2c51a8p-4
        const vf_type erf_i2_c0h=+9.9599465685270749393254e-01;
        // x^0 l: +0xe.ea4df2f66f138p-58
        const vf_type erf_i2_c0l=+5.1747675271424131958331e-17;
        // x^1 : +0x9.3155c40283268p-9
        const vf_type erf_i2_c1=+1.7954521347979746775936e-02;
        // x^2 : -0x9.5a5d850dd55p-8
        const vf_type erf_i2_c2=-3.6535115226645986652443e-02;
        // x^3 : +0xb.27ecea03b4548p-8
        const vf_type erf_i2_c3=+4.3577963955344252433566e-02;
        // x^4 : -0x8.3b98bb29e3f2p-8
        const vf_type erf_i2_c4=-3.2159372038122829851048e-02;
        // x^5 : +0xd.6ac90b41e7748p-10
        const vf_type erf_i2_c5=+1.3102666198825345736378e-02;
        // x^6 : -0xa.35ad2fc18ccb8p-15
        const vf_type erf_i2_c6=-3.1157451986665293591425e-04;
        // x^7 : -0xc.09472b631ce8p-12
        const vf_type erf_i2_c7=-2.9385356958251188097542e-03;
        // x^8 : +0xc.cb04cae657cdp-13
        const vf_type erf_i2_c8=+1.5616506199860103777655e-03;
        // x^9 : -0x8.d557a80197158p-16
        const vf_type erf_i2_c9=-1.3478651090391541278977e-04;
        // x^10 : -0xe.9984e98a632p-16
        const vf_type erf_i2_c10=-2.2277350357451271289921e-04;
        // x^11 : +0xd.b21fada9734e8p-17
        const vf_type erf_i2_c11=+1.0449063013853251036690e-04;
        // x^12 : -0xe.8c7985c2fb768p-23
        const vf_type erf_i2_c12=-1.7343436820855339363241e-06;
        // x^13 : -0xe.c2fcb6920a32p-20
        const vf_type erf_i2_c13=-1.4077824208156247784863e-05;
        // x^14 : +0x8.adcd11a64e448p-21
        const vf_type erf_i2_c14=+4.1384269493855688456575e-06;
        // x^15 : +0xd.eafbd15889fep-24
        const vf_type erf_i2_c15=+8.2957177961111339101782e-07;
        // x^16 : -0xe.921eb4322d228p-24
        const vf_type erf_i2_c16=-8.6848622585478523869560e-07;
        // x^17 : +0xe.c887defc270c8p-26
        const vf_type erf_i2_c17=+2.2028868239318452089703e-07;
        // x^18 : -0x9.d9038b554d91p-35
        const vf_type erf_i2_c18=-2.8660609186842229174787e-10;
        // x^19 : -0xd.fb15b0fa873p-30
        const vf_type erf_i2_c19=-1.3020634402817493488279e-08;
        // x^20 : +0xd.287a0e3c87118p-32
        const vf_type erf_i2_c20=+3.0636117842102736309007e-09;
        // x^21 : -0x8.91299618558a8p-35
        const vf_type erf_i2_c21=-2.4933370315452378001011e-10;
        // x^ : +0xfp-3
        const vf_type erf_i2_left=+1.8750000000000000000000e+00;
        // x^ : +0x8.23b4fp-2
        const vf_type erf_i2_x0=+2.0348699092864990234375e+00;
        vf_type x_i2 = x - erf_i2_x0;
#if 1
        vf_type xx= x_i2*x_i2;
        vf_type i= impl::poly(xx,
                              erf_i2_c21,
                              erf_i2_c19,
                              erf_i2_c17,
                              erf_i2_c15,
                              erf_i2_c13,
                              erf_i2_c11,
                              erf_i2_c9,
                              erf_i2_c7,
                              erf_i2_c5);
        vf_type j= impl::poly(xx,
                              erf_i2_c20,
                              erf_i2_c18,
                              erf_i2_c16,
                              erf_i2_c14,
                              erf_i2_c12,
                              erf_i2_c10,
                              erf_i2_c8,
                              erf_i2_c6,
                              erf_i2_c4);
        vf_type y_i2= i*x_i2 + j;
        y_i2 = impl::poly(x_i2, y_i2,
                          erf_i2_c3,
                          erf_i2_c2,
                          erf_i2_c1);
#else
        vf_type y_i2= impl::poly(x_i2,
                                 erf_i2_c21,
                                 erf_i2_c20,
                                 erf_i2_c19,
                                 erf_i2_c18,
                                 erf_i2_c17,
                                 erf_i2_c16,
                                 erf_i2_c15,
                                 erf_i2_c14,
                                 erf_i2_c13,
                                 erf_i2_c12,
                                 erf_i2_c11,
                                 erf_i2_c10,
                                 erf_i2_c9,
                                 erf_i2_c8,
                                 erf_i2_c7,
                                 erf_i2_c6,
                                 erf_i2_c5,
                                 erf_i2_c4,
                                 erf_i2_c3,
                                 erf_i2_c2,
                                 erf_i2_c1);
#endif
        vf_type ye;
        impl::eft_poly(y_i2, ye, x_i2, y_i2,
                       erf_i2_c0h);
        y_i2 += ye+erf_i2_c0l;
        return y_i2;
    };

    auto i3= [x]()->vf_type {
        // [3.5, 6] : | p - f | <= 2^-58.109375
        // coefficients for erf_i3 generated by sollya
        // x^0 h: +0xf.ffff9c4350758p-4
        const vf_type erf_i3_c0h=+9.9999962845052203785912e-01;
        // x^0 l: +0xb.caf1dd3904968p-58
        const vf_type erf_i3_c0l=+4.0914331138571226372713e-17;
        // x^1 : +0xb.9b8659624d8f8p-22
        const vf_type erf_i3_c1=+2.7674481285657176957832e-06;
        // x^2 : -0xa.6e12c20f42108p-20
        const vf_type erf_i3_c2=-9.9467980623786509997196e-06;
        // x^3 : +0xc.031fb3a65261p-19
        const vf_type erf_i3_c3=+2.2911457978090595856164e-05;
        // x^4 : -0x9.eca80dc283bcp-18
        const vf_type erf_i3_c4=-3.7858731448027949009066e-05;
        // x^5 : +0xc.77654fc74de58p-18
        const vf_type erf_i3_c5=+4.7555502482858254557820e-05;
        // x^6 : -0xc.4a021f4b75ad8p-18
        const vf_type erf_i3_c6=-4.6879176646772150371858e-05;
        // x^7 : +0x9.a6d073de7f738p-18
        const vf_type erf_i3_c7=+3.6818001687864182383102e-05;
        // x^8 : -0xc.13cdc36c5f8dp-19
        const vf_type erf_i3_c8=-2.3035733127395927705931e-05;
        // x^9 : +0xb.c7c1a19a2d53p-20
        const vf_type erf_i3_c9=+1.1234567955526363942529e-05;
        // x^10 : -0x8.529e8bd618bf8p-21
        const vf_type erf_i3_c10=-3.9685877435520957654653e-06;
        // x^11 : +0xc.547e8a04dfc2p-24
        const vf_type erf_i3_c11=+7.3492859804616469880764e-07;
        // x^12 : +0xc.85ec9d5c5b36p-26
        const vf_type erf_i3_c12=+1.8660935317950479413396e-07;
        // x^13 : -0xf.8fd15d59bd238p-26
        const vf_type erf_i3_c13=-2.3188871742844543630620e-07;
        // x^14 : +0xf.3ed20621d0eap-27
        const vf_type erf_i3_c14=+1.1358702340129324142554e-07;
        // x^15 : -0x9.f61fc73b32e1p-28
        const vf_type erf_i3_c15=-3.7109190216543264217597e-08;
        // x^16 : +0x9.50a9702108248p-30
        const vf_type erf_i3_c16=+8.6753493349650820866145e-09;
        // x^17 : -0xc.4cc58c305bdb8p-33
        const vf_type erf_i3_c17=-1.4318955756438658326616e-09;
        // x^18 : +0xa.9fa758a91467p-36
        const vf_type erf_i3_c18=+1.5459441423225671075377e-10;
        // x^19 : -0x9.8b0042d43c5d8p-40
        const vf_type erf_i3_c19=-8.6792831401194721286056e-12;
        // x^20 : -0xf.835a0e526809p-50
        const vf_type erf_i3_c20=-1.3778394331846918471113e-14;
        // x^21 : +0xc.1aecc242ad2p-49
        const vf_type erf_i3_c21=+2.1503110675247887643702e-14;
        // x^ : +0xep-2
        const vf_type erf_i3_left=+3.5000000000000000000000e+00;
        // x^ : +0xe.60796p-2
        const vf_type erf_i3_x0=+3.5942130088806152343750e+00;
        

        vf_type x_i3 = x - erf_i3_x0;
#if 1
        vf_type xx= x_i3*x_i3;
        vf_type i= impl::poly(xx,
                              erf_i3_c21,
                              erf_i3_c19,
                              erf_i3_c17,
                              erf_i3_c15,
                              erf_i3_c13,
                              erf_i3_c11,
                              erf_i3_c9,
                              erf_i3_c7,
                              erf_i3_c5);
        vf_type j= impl::poly(xx,
                              erf_i3_c20,
                              erf_i3_c18,
                              erf_i3_c16,
                              erf_i3_c14,
                              erf_i3_c12,
                              erf_i3_c10,
                              erf_i3_c8,
                              erf_i3_c6,
                              erf_i3_c4);
        vf_type y_i3= i*x_i3 + j;
        y_i3 = impl::poly(x_i3, y_i3,
                          erf_i3_c3,
                          erf_i3_c2,
                          erf_i3_c1);
#else
        vf_type y_i3= impl::poly(x_i3,
                                 erf_i3_c21,
                                 erf_i3_c20,
                                 erf_i3_c19,
                                 erf_i3_c18,
                                 erf_i3_c17,
                                 erf_i3_c16,
                                 erf_i3_c15,
                                 erf_i3_c14,
                                 erf_i3_c13,
                                 erf_i3_c12,
                                 erf_i3_c11,
                                 erf_i3_c10,
                                 erf_i3_c9,
                                 erf_i3_c8,
                                 erf_i3_c7,
                                 erf_i3_c6,
                                 erf_i3_c5,
                                 erf_i3_c4,
                                 erf_i3_c3,
                                 erf_i3_c2,
                                 erf_i3_c1);
#endif
        vf_type ye;
        impl::eft_poly(y_i3, ye, x_i3, y_i3,
                       erf_i3_c0h);
        y_i3 += ye+erf_i3_c0l;
        return y_i3;
    };

    auto s01 = [x, i0, i1]() -> vf_type {
        // x^ : +0xcp-4
        const vf_type erf_i1_left=+7.5000000000000000000000e-01;
        vf_type r=select_branch(x < erf_i1_left, i0, i1);
        return r;
    };

    auto s12 = [x, s01, i2]() -> vf_type {
        // x^ : +0xfp-3
        const vf_type erf_i2_left=+1.8750000000000000000000e+00;
        vf_type r=select_branch(x < erf_i2_left, s01, i2);
        return r;
    };

    auto s23 = [x, s12, i3]() ->vf_type {
        // x^ : +0xep-2
        const vf_type erf_i3_left=+3.5000000000000000000000e+00;
        vf_type r=select_branch(x <erf_i3_left, s12, i3);
        return r;
    };

    vf_type y= s23();
    y = copysign(y, xc);
    return y;
}

template <typename _T>
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
erfc_k(arg_t<vf_type> xc)
{
#if 0
    const int _N=sizeof(vf_type)/sizeof(double);
    union t {
        double _d[_N];
        vf_type _v;
    } x, y;
    x._v= xc;
    for (int i=0; i<_N; ++i) {
        y._d[i]=boost::math::erfc(x._d[i]);
    }
    vf_type r=y._v;
    return r;
#else
    vf_type x=abs(xc);
    struct erfc_data {
        bool _calculated;
        vf_type _expmxx;
        vf_type _1_plus_2_x;
        vf_type _f;
        constexpr erfc_data() : _calculated(false),
                                _expmxx(0.0), _1_plus_2_x(0) {}
        void
        operator()(vf_type x) {
            if (_calculated == true)
                return;
            _expmxx = expxx_k(x, vf_type(-1));
            _1_plus_2_x= 1 + 2*x;
            _f = _expmxx / _1_plus_2_x;
        };
        vf_type
        operator()() const {
            return _f;
        }
    };

    erfc_data ef;

    auto i0=[x]()->vf_type {
        // [3.4694469519536141888238489627838134765625e-18, 0.75] : | p - f | <= 2^-60.71875
        // coefficients for erfc_i0 generated by sollya
        // x^0 : +0x8p-3
        const vf_type erfc_i0_c0=+1.0000000000000000000000e+00;
        // x^1 : -0x9.06eba8214db68p-3
        const vf_type erfc_i0_c1=-1.1283791670955125585607e+00;
        // x^3 : +0xc.093a3581bcdf8p-5
        const vf_type erfc_i0_c3=+3.7612638903183531757790e-01;
        // x^5 : -0xe.71790d020896p-7
        const vf_type erfc_i0_c5=-1.1283791670945636509416e-01;
        // x^7 : +0xd.c167189014758p-9
        const vf_type erfc_i0_c7=+2.6866170643224867448096e-02;
        // x^9 : -0xa.b2de67b63691p-11
        const vf_type erfc_i0_c9=-5.2239776039429159509853e-03;
        // x^11 : +0xe.016d76ef4a11p-14
        const vf_type erfc_i0_c11=+8.5483255292173967489211e-04;
        // x^13 : -0xf.cd1371bbf2558p-17
        const vf_type erfc_i0_c13=-1.2055265766965315976916e-04;
        // x^15 : +0xf.a609a2cfb581p-20
        const vf_type erfc_i0_c15=+1.4923653157630001249998e-05;
        // x^17 : -0xd.c6d41ecbe4bf8p-23
        const vf_type erfc_i0_c17=-1.6423075436226438355598e-06;
        // x^19 : +0xa.a8395922ecd18p-26
        const vf_type erfc_i0_c19=+1.5880353844048938806551e-07;
        // x^21 : -0xc.1a4926aa7611p-30
        const vf_type erfc_i0_c21=-1.1271497883150963258877e-08;
        vf_type xx= x*x;
        vf_type y_i0=impl::poly(xx,
                                erfc_i0_c21,
                                erfc_i0_c19,
                                erfc_i0_c17,
                                erfc_i0_c15,
                                erfc_i0_c13,
                                erfc_i0_c11,
                                erfc_i0_c9,
                                erfc_i0_c7,
                                erfc_i0_c5,
                                erfc_i0_c3);
        vf_type ye;
        impl::eft_poly(y_i0, ye, xx, y_i0,
                       erfc_i0_c1);
        impl::eft_poly_si(y_i0, ye, x, y_i0, ye,
                          erfc_i0_c0);
        y_i0 += ye;
        return y_i0;
    };
    auto i1=[x, &ef]()->vf_type {
        // [0.75, 1.875] : | p - f | <= 2^-65.71875
        // coefficients for erfc_i1 generated by sollya
        // x^0 h: +0x9.7fd4a251b7ef8p-6
        const vf_type erfc_i1_c0h=+1.4842716075406678366555e-01;
        // x^0 l: +0xf.9fb871dc60c8p-62
        const vf_type erfc_i1_c0l=+3.3878950326178034048751e-18;
        // x^1 : -0xc.b59ff8cfc23f8p-5
        const vf_type erfc_i1_c1=-3.9717100711829539383402e-01;
        // x^2 : +0xc.fcb4a8d44e408p-5
        const vf_type erfc_i1_c2=+4.0584786390758870178175e-01;
        // x^3 : -0x9.38b3dd1da6ecp-6
        const vf_type erfc_i1_c3=-1.4408585160582165762833e-01;
        // x^4 : -0xf.c9546cfdda53p-8
        const vf_type erfc_i1_c4=-6.1665798768310950417337e-02;
        // x^5 : +0x8.c2586d568bcc8p-7
        const vf_type erfc_i1_c5=+6.8430951488237204416443e-02;
        // x^6 : -0xe.0ef0a178f0318p-11
        const vf_type erfc_i1_c6=-6.8644332196684280586463e-03;
        // x^7 : -0xe.a1c48a69121f8p-10
        const vf_type erfc_i1_c7=-1.4288969943907157619800e-02;
        // x^8 : +0xa.7d0064694ab88p-11
        const vf_type erfc_i1_c8=+5.1212340014549087921503e-03;
        // x^9 : +0xd.3bf0ea72c49dp-13
        const vf_type erfc_i1_c9=+1.6154961955057848578543e-03;
        // x^10 : -0xa.29b9c864c618p-13
        const vf_type erfc_i1_c10=-1.2405994958946224560048e-03;
        // x^11 : -0x8.e07994534153p-18
        const vf_type erfc_i1_c11=-3.3862515084641817901361e-05;
        // x^12 : +0xc.b25d02723914p-16
        const vf_type erfc_i1_c12=+1.9373675099467022216182e-04;
        // x^13 : -0xd.76fa35fdf798p-19
        const vf_type erfc_i1_c13=-2.5681982832800171172999e-05;
        // x^14 : -0xb.6da3a40b0683p-19
        const vf_type erfc_i1_c14=-2.1797710819904308544078e-05;
        // x^15 : +0xc.e6363c0a35c28p-21
        const vf_type erfc_i1_c15=+6.1508488909078894529251e-06;
        // x^16 : +0xe.ae59a07aa1d7p-23
        const vf_type erfc_i1_c16=+1.7501181480315038643716e-06;
        // x^17 : -0xe.b598da16604f8p-24
        const vf_type erfc_i1_c17=-8.7674639135360295341307e-07;
        // x^18 : -0xc.558fa521527ap-27
        const vf_type erfc_i1_c18=-9.1897123302226876293458e-08;
        // x^19 : +0xc.b6dd7f5932538p-27
        const vf_type erfc_i1_c19=+9.4729045651409012425576e-08;
        // x^20 : +0xa.038a37b1fe3d8p-30
        const vf_type erfc_i1_c20=+9.3261038722361826518186e-09;
        // x^21 : -0xa.713a2a19131a8p-29
        const vf_type erfc_i1_c21=-1.9450287835670348636804e-08;
        // x^22 : +0xd.ab1c41f48e208p-31
        const vf_type erfc_i1_c22=+6.3648447056001057675020e-09;
        // x^23 : -0xd.c0f6f56ef1548p-34
        const vf_type erfc_i1_c23=-8.0057468096948020393389e-10;
        // x^ : +0xcp-4
        const vf_type erfc_i1_left=+7.5000000000000000000000e-01;
        // x^ : +0x8.2cbdfp-3
        const vf_type erfc_i1_x0=+1.0218466520309448242188e+00;

        vf_type x_i1 = x - erfc_i1_x0;
        vf_type y_i1= impl::poly(x_i1,
                                 erfc_i1_c23,
                                 erfc_i1_c22,
                                 erfc_i1_c21,
                                 erfc_i1_c20,
                                 erfc_i1_c19,
                                 erfc_i1_c18,
                                 erfc_i1_c17,
                                 erfc_i1_c16,
                                 erfc_i1_c15,
                                 erfc_i1_c14,
                                 erfc_i1_c13,
                                 erfc_i1_c12,
                                 erfc_i1_c11,
                                 erfc_i1_c10,
                                 erfc_i1_c9,
                                 erfc_i1_c8,
                                 erfc_i1_c7);
        vf_type ye;
        impl::eft_poly(y_i1, ye, x_i1, y_i1,
                       erfc_i1_c6,
                       erfc_i1_c5,
                       erfc_i1_c4,
                       erfc_i1_c3,
                       erfc_i1_c2,
                       erfc_i1_c1,
                       erfc_i1_c0h);
        y_i1 += ye +erfc_i1_c0l;
        return y_i1;
    };

    auto i2=[x, &ef]()->vf_type {
        // [1.875, 3.5] : | p - f | <= 2^-61.90625
        // coefficients for erfc_i2 generated by sollya
        // x^0 h: +0x8.33f40e9d72a2p-11
        const vf_type erfc_i2_c0h=+4.0053431472924540257541e-03;
        // x^0 l: +0x9.1bf1ccb7e27fp-66
        const vf_type erfc_i2_c0l=+1.2345211550514282013483e-19;
        // x^1 : -0x9.3155c4028323p-9
        const vf_type erfc_i2_c1=-1.7954521347979722489807e-02;
        // x^2 : +0x9.5a5d850dd558p-8
        const vf_type erfc_i2_c2=+3.6535115226646097674745e-02;
        // x^3 : -0xb.27ecea03b6c3p-8
        const vf_type erfc_i2_c3=-4.3577963955352891356476e-02;
        // x^4 : +0x8.3b98bb29e81p-8
        const vf_type erfc_i2_c4=+3.2159372038137457039397e-02;
        // x^5 : -0xd.6ac90b3e50af8p-10
        const vf_type erfc_i2_c5=-1.3102666198009314466044e-02;
        // x^6 : +0xa.35ad2d3e7b4c8p-15
        const vf_type erfc_i2_c6=+3.1157451529737753082375e-04;
        // x^7 : +0xc.09472a2fb1e18p-12
        const vf_type erfc_i2_c7=+2.9385356783504248089078e-03;
        // x^8 : -0xc.cb04aa156263p-13
        const vf_type erfc_i2_c8=-1.5616503812164047280964e-03;
        // x^9 : +0x8.d554b89e9eebp-16
        const vf_type erfc_i2_c9=+1.3478582752178444549226e-04;
        // x^10 : +0xe.997e807ca53p-16
        const vf_type erfc_i2_c10=+2.2277201104488591337782e-04;
        // x^11 : -0xd.b1840fc65e268p-17
        const vf_type erfc_i2_c11=-1.0447251396493544277778e-04;
        // x^12 : +0xd.f3f6787d9bd7p-23
        const vf_type erfc_i2_c12=+1.6633247845068352241307e-06;
        // x^13 : +0xe.f15ba81d24eap-20
        const vf_type erfc_i2_c13=+1.4250569172068282676556e-05;
        // x^14 : -0x9.4c5a96e14db1p-21
        const vf_type erfc_i2_c14=-4.4337545796250801339493e-06;
        // x^15 : -0xf.5bb28c6c21638p-25
        const vf_type erfc_i2_c15=-4.5770982457040160565004e-07;
        // x^16 : +0x8.ac7f217d817f8p-24
        const vf_type erfc_i2_c16=+5.1699965372001071763915e-07;
        // x^17 : +0x8.1109caca39b08p-28
        const vf_type erfc_i2_c17=+3.0050261565760021652852e-08;
        // x^18 : -0x8.ec44c6e3c9158p-26
        const vf_type erfc_i2_c18=-1.3296193558590645276267e-07;
        // x^19 : +0x8.b656c792ed678p-27
        const vf_type erfc_i2_c19=+6.4911407615191319781432e-08;
        // x^20 : -0x9.4699f6e92ba68p-29
        const vf_type erfc_i2_c20=-1.7277499310222299800160e-08;
        // x^21 : +0xc.07c3b7c2c7b3p-32
        const vf_type erfc_i2_c21=+2.8010295161204299998322e-09;
        // x^22 : -0x8.fb7eb0fccf6dp-35
        const vf_type erfc_i2_c22=-2.6142230218687706855659e-10;
        // x^23 : +0xb.e2b6c1ea60f08p-40
        const vf_type erfc_i2_c23=+1.0809891280474724393940e-11;
        // x^ : +0xfp-3
        const vf_type erfc_i2_left=+1.8750000000000000000000e+00;
        // x^ : +0x8.23b4fp-2
        const vf_type erfc_i2_x0=+2.0348699092864990234375e+00;

        vf_type x_i2 = x - erfc_i2_x0;
        vf_type y_i2= impl::poly(x_i2,
                                 erfc_i2_c23,
                                 erfc_i2_c22,
                                 erfc_i2_c21,
                                 erfc_i2_c20,
                                 erfc_i2_c19,
                                 erfc_i2_c18,
                                 erfc_i2_c17,
                                 erfc_i2_c16,
                                 erfc_i2_c15,
                                 erfc_i2_c14,
                                 erfc_i2_c13,
                                 erfc_i2_c12,
                                 erfc_i2_c11,
                                 erfc_i2_c10);
        vf_type ye;
        impl::eft_poly(y_i2, ye, x_i2, y_i2,
                       erfc_i2_c9,
                       erfc_i2_c8,
                       erfc_i2_c7,
                       erfc_i2_c6,
                       erfc_i2_c5,
                       erfc_i2_c4,
                       erfc_i2_c3,
                       erfc_i2_c2,
                       erfc_i2_c1,
                       erfc_i2_c0h);
        y_i2 += ye +erfc_i2_c0l;
        return y_i2;
    };

#if 0
    auto i4=[x, &expmxx]()->vf_type {
        // [16, 27.5] : | p - f | <= 2^-64.75
        // coefficients for erfc_i1 generated by sollya
        // x^0 h: +0xd.44648e2f65a78p-9
        const vf_type erfc_i1_c0h=+2.5912420612893168753166e-02;
        // x^0 l: -0xe.40dfcdad23fep-65
        const vf_type erfc_i1_c0l=-3.8633958687429383394176e-19;
        // x^1 : -0x9.bd3df45a7ae6p-13
        const vf_type erfc_i1_c1=-1.1888704346597498903715e-03;
        // x^2 : +0xe.48ac08cd2d85p-18
        const vf_type erfc_i1_c2=+5.4488659043608054827375e-05;
        // x^3 : -0xa.76b3295d48518p-22
        const vf_type erfc_i1_c3=-2.4947336408499828137202e-06;
        // x^4 : +0xf.507c925fbe178p-27
        const vf_type erfc_i1_c4=+1.1410117756138507899834e-07;
        // x^5 : -0xb.31fe4cf61153p-31
        const vf_type erfc_i1_c5=-5.2132115558101667806995e-09;
        // x^6 : +0x8.2cf5eac61e41p-35
        const vf_type erfc_i1_c6=+2.3794207363782838080994e-10;
        // x^7 : -0xb.edb7e5c3351dp-40
        const vf_type erfc_i1_c7=-1.0848986951998424797101e-11;
        // x^8 : +0x8.b176760bc7578p-44
        const vf_type erfc_i1_c8=+4.9415199459871791329908e-13;
        // x^9 : -0xc.a86218ecc0688p-49
        const vf_type erfc_i1_c9=-2.2484675182999015691024e-14;
        // x^10 : +0x9.34ab5f42f421p-53
        const vf_type erfc_i1_c10=+1.0220424430062766230130e-15;
        // x^11 : -0xd.607706e4fabb8p-58
        const vf_type erfc_i1_c11=-4.6410154215663817748747e-17;
        // x^12 : +0x9.b57b2d85e1f3p-62
        const vf_type erfc_i1_c12=+2.1052844351590252850989e-18;
        // x^13 : -0xe.132b35748f99p-67
        const vf_type erfc_i1_c13=-9.5375083591136594297948e-20;
        // x^14 : +0xa.3202142a56d48p-71
        const vf_type erfc_i1_c14=+4.3178962312698204272509e-21;
        // x^15 : -0xe.d8370544d48cp-76
        const vf_type erfc_i1_c15=-1.9646650679929372862725e-22;
        // x^16 : +0xa.b9bed46efd288p-80
        const vf_type erfc_i1_c16=+8.8719819760051011610255e-24;
        // x^17 : -0xe.5d9ec6bf3a6f8p-85
        const vf_type erfc_i1_c17=-3.7134474443742943181956e-25;
        // x^18 : +0xa.672576c192468p-89
        const vf_type erfc_i1_c18=+1.6806816281050232658047e-26;
        // x^19 : -0xb.6e79b86d56238p-93
        const vf_type erfc_i1_c19=-1.1542910443371632508712e-27;
        // x^20 : +0x8.2b85fb8aaa248p-97
        const vf_type erfc_i1_c20=+5.1560031829121269346255e-29;
        // x^ : +0x8p+1
        const vf_type erfc_i1_left=+1.6000000000000000000000e+01;
        // x^ : +0xa.ep+1
        const vf_type erfc_i1_x0=+2.1750000000000000000000e+01;
        vf_type xx=x-erfc_i1_x0;
        vf_type y_i1= impl::poly(xx,
                                 erfc_i1_c20,
                                 erfc_i1_c19,
                                 erfc_i1_c18,
                                 erfc_i1_c17,
                                 erfc_i1_c16,
                                 erfc_i1_c15,
                                 erfc_i1_c14,
                                 erfc_i1_c13,
                                 erfc_i1_c12,
                                 erfc_i1_c11,
                                 erfc_i1_c10,
                                 erfc_i1_c9,
                                 erfc_i1_c8,
                                 erfc_i1_c7,
                                 erfc_i1_c6,
                                 erfc_i1_c5,
                                 erfc_i1_c4,
                                 erfc_i1_c3,
                                 erfc_i1_c2,
                                 erfc_i1_c1);
        y_i1 *=xx;
        y_i1 +=erfc_i1_c0l;
        // y_i1 +=erfc_i1_c0h;
        if (expmxx.first == false) {
            expmxx.first =true;
            expmxx.second =expxx_k(x, -1.0);
        }
        y_i1 *= expmxx.second;
        return y_i1;
    };
#endif

    auto s01=[x, i0, i1]()->vf_type {
        // x^ : +0xcp-4
        const vf_type erfc_i1_left=+7.5000000000000000000000e-01;
        vf_type r=select_branch(x < erfc_i1_left, i0, i1);
        return r;
    };

    auto s12=[x, s01, i2]()->vf_type {
        // x^ : +0xfp-3
        const vf_type erfc_i2_left=+1.8750000000000000000000e+00;
        vf_type r=select_branch(x < erfc_i2_left, s01, i2);
        return r;
    };
    
    vf_type y=s12();
    return y;
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

    // [0.125, 1] : | p - f | <= 2^-10.46875
    // coefficients for cbrt generated by sollya
    // x^0 : +0x9.64c9e4f87925p-5
    const vf_type cbrt_c0=+2.9355330200977347576696e-01;
    // x^1 : +0x8.6b339d30d0f88p-2
    const vf_type cbrt_c1=+2.1046890793843364697580e+00;
    // x^2 : -0x8.9c501632c06fp-1
    const vf_type cbrt_c2=-4.3052985131218672876230e+00;
    // x^3 : +0xc.621697514d99p-1
    const vf_type cbrt_c3=+6.1915786062952964385886e+00;
    // x^4 : -0x9.74a86d8b0b04p-1
    const vf_type cbrt_c4=-4.7278475029211293190201e+00;
    // x^5 : +0xb.8d5ef802e3ebp-3
    const vf_type cbrt_c5=+1.4440287948495913461500e+00;
    vf_type mm = impl::poly(mm0,
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
