//
// Copyright (C) 2010-2025 Axel Zeuner
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
//
#if !defined (__CFTAL_MATH_HALF_FUNC_H__)
#define __CFTAL_MATH_HALF_FUNC_H__ 1

#include <cftal/config.h>
#include <cftal/arg.h>
#include <cftal/d_real.h>
#include <cftal/d_real_traits_f32.h>
#include <cftal/math/elem_func_core_f32.h>

namespace cftal {
    namespace math {


        // template, may be we need a specialization for double
        // later
        template <typename _FLOAT_T, typename _TRAITS_T>
        struct half_func {};

        // specialization for float
        template <typename _T>
        struct half_func<float, _T> : public elem_func_core<float, _T> {
            using base_type = elem_func_core<float, _T>;
            using d_ops= typename base_type::d_ops;

            using vf_type = typename _T::vf_type;
            using vi_type = typename _T::vi_type;
            using vmf_type = typename _T::vmf_type;
            using vmi_type = typename _T::vmi_type;

            static
            vf_type
            __scale_exp_k(arg_t<vf_type> kf);


            static
            void
            __reduce_exp_arg(vf_type& xrh,
                             vi_type& idx,
                             vi_type& k,
                             arg_t<vf_type> x);

            static
            vf_type
            __half_exp_tbl_k(arg_t<vf_type> xrh,
                             arg_t<vi_type> idx,
                             arg_t<vi_type> k);

            static
            vf_type
            __half_exp_k(arg_t<vf_type> xrh,
                         arg_t<vf_type> kf);

            static
            vf_type
            half_exp_k(arg_t<vf_type> x);

            static
            vf_type
            half_exp(arg_t<vf_type> x);

            static
            vf_type
            half_exp2_k(arg_t<vf_type> x);

            static
            vf_type
            half_exp2(arg_t<vf_type> x);

            static
            vf_type
            half_exp10_k(arg_t<vf_type> x);

            static
            vf_type
            half_exp10(arg_t<vf_type> x);

            static
            vf_type
            __half_log_poly_k(arg_t<vf_type> x);

            static
            vf_type
            half_log(arg_t<vf_type> x);

            static
            vf_type
            half_log2(arg_t<vf_type> x);

            static
            vf_type
            half_log10(arg_t<vf_type> x);

            static
            vi_type
            __half_reduce_trig_arg(vf_type& xr, arg_t<vf_type> x);

            static
            void
            half_sin_cos_k(arg_t<vf_type> x, vf_type* s, vf_type* c);

            static
            vf_type
            half_sin(arg_t<vf_type> x);

            static
            vf_type
            half_cos(arg_t<vf_type> x);

            static
            vf_type
            half_tan(arg_t<vf_type> x);

            static
            vf_type
            half_rsqrt(arg_t<vf_type> x);

            static
            vf_type
            half_sqrt(arg_t<vf_type> x);

        };

    }
}

template <typename _T>
inline
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
__scale_exp_k(arg_t<vf_type> kf)
{
    vi_type ki= _T::cvt_f_to_i(kf);
    vf_type rh= _T::insert_exp(_T::bias()+ki);
    return rh;
}

template <typename _T>
void
cftal::math::half_func<float, _T>::
__reduce_exp_arg(vf_type& xrh,
                 vi_type& idx,
                 vi_type& k,
                 arg_t<vf_type> xc)
{
    static_assert(exp_data<float>::EXP_N==32,
                 "exp_data<float>::EXP_N==32");
    const float _32_ln2=+4.6166240692e+01f;
#if 0
    vf_type kf = rint(vf_type(xc * _32_ln2));
    vi_type ki=_T::cvt_f_to_i(kf);
#else
    vf_type x32ln2=xc*_32_ln2;
    vf_type kf = rint(x32ln2);
    vi_type ki=_T::cvt_f_to_i(x32ln2);
#endif
    idx = ki & exp_data<float>::EXP_IDX_MASK;
    k = ki >> exp_data<float>::EXP_SHIFT;
    const float _ln2_32_cw_h=+2.1659851074e-02f;
    const float _ln2_32_cw_l=+9.9831822808e-07f;
    xrh = (xc - kf * _ln2_32_cw_h) -
        (kf * _ln2_32_cw_l);
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
__half_exp_tbl_k(arg_t<vf_type> xrh,
                 arg_t<vi_type> idx,
                 arg_t<vi_type> k)
{
    // [-1.0830424726009368896484375e-2, 1.0830424726009368896484375e-2] : | p - f | <= 2^-32.65625
    // coefficients for exp generated by sollya
    // x^1 : +0x8p-3f
    constexpr
    const float exp_c1=+1.0000000000e+00f;
    // x^2 : +0x8.0003dp-4f
    constexpr
    const float exp_c2=+5.0000363588e-01f;
    // x^3 : +0xa.aaac9p-6f
    constexpr
    const float exp_c3=+1.6666711867e-01f;
    static_assert(exp_c1==1.0f, "oops");
    auto lk=make_variable_lookup_table<float>(idx);
    const auto& tbl=exp_data<float>::_tbl;
    vf_type th=lk.from(tbl._2_pow_i_n_h);
    // vf_type tl=lk.from(tbl._2_pow_i_n_l);
    vf_type x2=xrh*xrh;
    vf_type p= horner(xrh, exp_c3, exp_c2);
    vf_type eh=xrh + x2*p;
    vf_type y= th + (/* tl+*/ th*eh);
    vi_type yi= _T::as_int(y);
    yi += (k<<23);
    y = _T::as_float(yi);
    // vf_type sc=_T::insert_exp(_T::bias()+k);
    // y *=  sc;
    return y;
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
__half_exp_k(arg_t<vf_type> xrh,
             arg_t<vf_type> kf)
{
    // [-0.3465735912322998046875, 0.3465735912322998046875] : | p - f | <= 2^-22.6875
    // coefficients for exp_f16 generated by sollya
    // x^0 : +0x8p-3f
    constexpr const float exp_f16_c0=+1.0000000000e+00f;
    // x^1 : +0x8p-3f
    constexpr const float exp_f16_c1=+1.0000000000e+00f;
    // x^2 : +0xf.ffefep-5f
    constexpr const float exp_f16_c2=+4.9999231100e-01f;
    // x^3 : +0xa.aabd6p-6f
    constexpr const float exp_f16_c3=+1.6667112708e-01f;
    // x^4 : +0xa.b9509p-8f
    constexpr const float exp_f16_c4=+4.1890177876e-02f;
    // x^5 : +0x8.831f1p-10f
    constexpr const float exp_f16_c5=+8.3126882091e-03f;
    static_assert(exp_f16_c1==1.0f, "oops");
    static const float c[]={
        exp_f16_c5, exp_f16_c4, exp_f16_c3,
        exp_f16_c2
    };
    vf_type xrh2=xrh*xrh;
    vf_type y=horner2(xrh, xrh2, c)*xrh2 + xrh;
    y+= exp_f16_c0;
#if 1
    vi_type k=_T::cvt_f_to_i(kf);
    vi_type yi= _T::as_int(y);
    yi += (k<<23);
    y = _T::as_float(yi);
#else
    y*= __scale_exp_k(kf);
#endif
    return y;
}

template <typename _T>
inline
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::half_exp_k(arg_t<vf_type> xc)
{
#if 0
    vf_type xrh;
    vi_type idx, k;
    __reduce_exp_arg(xrh, idx, k, xc);
    auto y=__half_exp_tbl_k(xrh, idx, k);
#else
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type kf = rint(vf_type(xc * ctbl::m_1_ln2[0]));
    vf_type xrh = (xc - kf*ctbl::m_ln2_cw[0]) -
        kf*ctbl::m_ln2_cw[1];
    auto y= __half_exp_k(xrh, kf);
#endif
    return y;
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
half_exp(arg_t<vf_type> d)
{
    vf_type res=half_exp_k(d);
    using fc= func_constants<float>;
    const vf_type exp_hi_inf= fc::exp_hi_inf();
    const vf_type exp_lo_zero= fc::exp_lo_zero();
    res = _T::sel(d <= exp_lo_zero, 0.0, res);
    res = _T::sel(d >= exp_hi_inf, _T::pinf(), res);
    return res;
}

template <typename _T>
inline
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::half_exp2_k(arg_t<vf_type> xc)
{
#if 0
    static_assert(exp_data<float>::EXP_N==32,
                 "exp_data<float>::EXP_N==32");
    const float _ND=exp_data<float>::EXP_N;
    const float _1_ND=1.0f/exp_data<float>::EXP_N;
#if 0
    vf_type kf = rint(vf_type(xc * _ND));
    vi_type ki=_T::cvt_f_to_i(kf);
#else
    vf_type xnd=xc * _ND;
    vf_type kf = rint(xnd);
    vi_type ki=_T::cvt_f_to_i(xnd);
#endif
    vi_type idx = ki & exp_data<float>::EXP_IDX_MASK;
    vi_type k = ki >> exp_data<float>::EXP_SHIFT;
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type xrh = xc - kf * _1_ND;
    auto y=__half_exp_tbl_k(xrh*ctbl::m_ln2[0], idx, k);
    return y;
#else
    vf_type kf = rint(xc);
    vf_type xrh = xc - kf;
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    auto y= __half_exp_k(xrh*ctbl::m_ln2[0], kf);
    return y;
#endif
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
half_exp2(arg_t<vf_type> d)
{
    vf_type res=half_exp2_k(d);
    using fc= func_constants<float>;
    const vf_type exp2_hi_inf= fc::exp2_hi_inf();
    const vf_type exp2_lo_zero= fc::exp2_lo_zero();
    res = _T::sel(d <= exp2_lo_zero, 0.0, res);
    res = _T::sel(d >= exp2_hi_inf, _T::pinf(), res);
    return res;
}

template <typename _T>
inline
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::half_exp10_k(arg_t<vf_type> xc)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type kf = rint(vf_type(xc * ctbl::m_1_lg2[0]));
    vf_type xrh = (xc - kf*ctbl::m_lg2_cw[0]) -
        (kf*ctbl::m_lg2_cw[1]);
    auto y= __half_exp_k(xrh*ctbl::m_ln10[0], kf);
    return y;
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
half_exp10(arg_t<vf_type> d)
{
    vf_type res=half_exp10_k(d);
    using fc= func_constants<float>;
    const vf_type exp10_hi_inf= fc::exp10_hi_inf();
    const vf_type exp10_lo_zero= fc::exp10_lo_zero();
    res = _T::sel(d <= exp10_lo_zero, 0.0, res);
    res = _T::sel(d >= exp10_hi_inf, _T::pinf(), res);
    return res;
}

template <typename _T>
inline
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::__half_log_poly_k(arg_t<vf_type> xc)
{
    vf_type xr;
    vi_type ki=base_type::__reduce_log_arg(xr, xc);
    // [-0.292893230915069580078125, 0.41421353816986083984375] : | p - f | <= 2^-25.546875
    // coefficients for log generated by sollya
    // x^1 : +0x8p-3f
    constexpr
    const float log_f16_c1=+1.0000000000e+00f;
    // x^2 : -0xf.fffffp-5f
    constexpr
    const float log_f16_c2=-4.9999997020e-01f;
    // x^3 : +0xa.aab1bp-5f
    constexpr
    const float log_f16_c3=+3.3333668113e-01f;
    // x^4 : -0x8.001b4p-5f
    constexpr
    const float log_f16_c4=-2.5001299381e-01f;
    // x^5 : +0xc.c847p-6f
    constexpr
    const float log_f16_c5=+1.9972395897e-01f;
    // x^6 : -0xa.9d02cp-6f
    constexpr
    const float log_f16_c6=-1.6583317518e-01f;
    // x^7 : +0x9.7cc4bp-6f
    constexpr
    const float log_f16_c7=+1.4824025333e-01f;
    // x^8 : -0x9.16814p-6f
    constexpr
    const float log_f16_c8=-1.4199858904e-01f;
    // x^9 : +0xb.5c70bp-7f
    constexpr
    const float log_f16_c9=+8.8758550584e-02f;
    static_assert(log_f16_c1 == 1.0f, "constraint violated");
    vf_type r=xr-1.0f;
    vf_type r2=r*r;
    static const float c[]= {
        log_f16_c9, log_f16_c8, log_f16_c7, log_f16_c6,
        log_f16_c5, log_f16_c4, log_f16_c3, log_f16_c2
    };
    vf_type y =horner2(r, r2, c);
    y = y*r2 + r;
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vf_type kf=_T::cvt_i_to_f(ki);
    vf_type log_x = kf * ctbl::m_ln2[0] + y;
    return log_x;
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
half_log(arg_t<vf_type> d)
{
    vf_type x = __half_log_poly_k(d);
    const vf_type pinf(_T::pinf());
    const vf_type ninf(_T::ninf());
    x = _T::sel(isinf(d), pinf, x);
    // if (d < 0) x = NAN;
    x = _T::sel(d < vf_type(0.0), vf_type(_T::nan()), x);
    // if (d == 0) x = -INFINITY;
    x = _T::sel(d == vf_type(0.0), ninf, x);
    // NAN --> n_and_1
    x = _T::sel(isnan(d), d, x);
    return x;
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
half_log2(arg_t<vf_type> d)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type x = __half_log_poly_k(d)*ctbl::m_1_ln2[0];
    const vf_type pinf(_T::pinf());
    const vf_type ninf(_T::ninf());
    x = _T::sel(isinf(d), pinf, x);
    // if (d < 0) x = NAN;
    x = _T::sel(d < vf_type(0.0), vf_type(_T::nan()), x);
    // if (d == 0) x = -INFINITY;
    x = _T::sel(d == vf_type(0.0), ninf, x);
    // NAN --> n_and_1
    x = _T::sel(isnan(d), d, x);
    return x;
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
half_log10(arg_t<vf_type> d)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type l=__half_log_poly_k(d);
    vf_type x=l * ctbl::m_1_ln10[0];
    const vf_type pinf(_T::pinf());
    const vf_type ninf(_T::ninf());
    x = _T::sel(isinf(d), pinf, x);
    // if (d < 0) x = NAN;
    x = _T::sel(d < vf_type(0.0), vf_type(_T::nan()), x);
    // if (d == 0) x = -INFINITY;
    x = _T::sel(d == vf_type(0.0), ninf, x);
    // NAN --> n_and_1
    x = _T::sel(isnan(d), d, x);
    return x;
}

template <typename _T>
inline
typename cftal::math::half_func<float, _T>::vi_type
cftal::math::half_func<float, _T>::
__half_reduce_trig_arg(vf_type& xrh, arg_t<vf_type> x)
{
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vf_type fn= rint(vf_type(x*ctbl::m_2_pi[0]));
    // conversion to double vectors does not make the code faster
    // seven bit chunks of %pi/2
    // x^ : +0xc.ap-3f
    const float pi_2_0=+1.5781250000e+00f;
    // x^ : -0xfp-11f
    const float pi_2_1=-7.3242187500e-03f;
    // x^ : -0x9.6p-21f
    const float pi_2_2=-4.4703483582e-06f;
    // x^ : +0x8.8p-29f
    const float pi_2_3=+1.5832483768e-08f;
    // x^ : +0x8.6p-37f
    const float pi_2_4=+6.0936145019e-11f;
    // and the remaining bits
    // x^ : -0xb.9ee5ap-46f
    const float pi_2_5=-1.6513995575e-13f;
    xrh = x + fn * -pi_2_0;
    xrh = xrh + fn * -pi_2_1;
    xrh = xrh + fn * -pi_2_2;
    xrh = xrh + fn * -pi_2_3;
    xrh = xrh + fn * -pi_2_4;
    xrh = xrh + fn * -pi_2_5;
    vi_type q=_T::cvt_f_to_i(fn);
    return q;
}

template <typename _T>
inline
void
cftal::math::half_func<float, _T>::
half_sin_cos_k(arg_t<vf_type> x, vf_type* ps, vf_type* pc)
{
    vf_type xr;
    auto q= __half_reduce_trig_arg(xr, x);

    vf_type xr2= xr*xr;
    vmi_type q_and_2(vi_type(q & vi_type(2))==vi_type(2));
    vmf_type q_and_2_f(_T::vmi_to_vmf(q_and_2));
    vmi_type q_and_1(vi_type(q & vi_type(1))==vi_type(1));
    vmf_type q_and_1_f(_T::vmi_to_vmf(q_and_1));

    // [0, 0.785398185253143310546875] : | p - f | <= 2^-33.09375
    // coefficients for cos_f16 generated by sollya
    // x^0 : +0x8p-3f
    const float cos_f16_c0=+1.0000000000e+00f;
    // x^2 : -0x8p-4f
    const float cos_f16_c2=-5.0000000000e-01f;
    // x^4 : +0xa.aaaa5p-8f
    const float cos_f16_c4=+4.1666645557e-02f;
    // x^6 : -0xb.60615p-13f
    const float cos_f16_c6=-1.3887310633e-03f;
    // x^8 : +0xc.cf48ap-19f
    const float cos_f16_c8=+2.4432567443e-05f;
    // vf_type xr4=xr2*xr2;
    static const float cc[]={
        cos_f16_c8, cos_f16_c6, cos_f16_c4,
        cos_f16_c2, cos_f16_c0
    };
    vf_type xr4=xr2*xr2;
    // vf_type c= horner2(xr2, xr4, cc);
    // [0, 0.785398185253143310546875] : | p - f | <= 2^-33.890625
    // coefficients for sin_f16 generated by sollya
    // x^1 : +0x8p-3f
    const float sin_f16_c1=+1.0000000000e+00f;
    // x^3 : -0xa.aaaabp-6f
    const float sin_f16_c3=-1.6666667163e-01f;
    // x^5 : +0x8.888b2p-10f
    const float sin_f16_c5=+8.3333719522e-03f;
    // x^7 : -0xd.02433p-16f
    const float sin_f16_c7=-1.9849911041e-04f;
    // x^9 : +0xb.bf108p-22f
    const float sin_f16_c9=+2.8005470085e-06f;
    static const float cs[]={
        sin_f16_c9, sin_f16_c7,  sin_f16_c5,
        sin_f16_c3, sin_f16_c1
    };
    // vf_type s= horner2(xr2, xr4, cs)*xr;
    vf_type s, c;
    horner2_n2(s, c, xr2, xr4, cs, cc);
    s *= xr;

    // swap sin/cos if q & 1
    vf_type rs(_T::sel(q_and_1_f, c, s));
    vf_type rc(_T::sel(q_and_1_f, s, c));
    // swap signs
    if (ps != nullptr) {
        // vf_type fs = _T::sel(q_and_2_f, vf_type(-1.0), vf_type(1.0));
        // rs *= fs;
        *ps = _T::sel(q_and_2_f, -rs, rs);
    }
    if (pc != nullptr) {
        vmf_type mt = q_and_2_f ^ q_and_1_f;
        // vf_type fc =  _T::sel(mt, vf_type(-1.0), vf_type(1.0));
        // rc *= fc;
        *pc= _T::sel(mt, -rc, rc);
    }
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
half_sin(arg_t<vf_type> d)
{
    vf_type s;
    half_sin_cos_k(d, &s, nullptr);
    return s;
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
half_cos(arg_t<vf_type> d)
{
    vf_type c;
    half_sin_cos_k(d, nullptr, &c);
    return c;
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
half_tan(arg_t<vf_type> x)
{
    vf_type xr;
    auto q= __half_reduce_trig_arg(xr, x);
    // [0, 0.785398185253143310546875] : | p - f | <= 2^-29.546875
    // coefficients for tan_16 generated by sollya
    // x^1 : +0x8p-3f
    const float tan_f16_c1=+1.0000000000e+00f;
    // x^3 : +0xa.aaabp-5f
    const float tan_f16_c3=+3.3333349228e-01f;
    // x^5 : +0x8.886dp-6f
    const float tan_f16_c5=+1.3332676888e-01f;
    // x^7 : +0xd.d6c9cp-8f
    const float tan_f16_c7=+5.4058656096e-02f;
    // x^9 : +0xa.e63c5p-9f
    const float tan_f16_c9=+2.1287808195e-02f;
    // x^11 : +0xb.15241p-10f
    const float tan_f16_c11=+1.0822833516e-02f;
    // x^13 : +0xd.b2701p-17f
    const float tan_f16_c13=+1.0449998808e-04f;
    // x^15 : +0x8.f2db7p-11f
    const float tan_f16_c15=+4.3694633059e-03f;
    vf_type x2=xr*xr;
    vf_type x4=x2*x2;

    static const float ci[]={
        tan_f16_c15,
        tan_f16_c13,
        tan_f16_c11,
        tan_f16_c9,
        tan_f16_c7,
        tan_f16_c5,
        tan_f16_c3,
        tan_f16_c1
    };
    vf_type t = horner2(x2, x4, ci)*xr;
    vmi_type qm1= vi_type(q & vi_type(1)) == vi_type(1);
    vmf_type fqm1= _T::vmi_to_vmf(qm1);

    vf_type ct=-1.0f/t;
    t = _T::sel(fqm1, ct, t);
    return t;
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
half_rsqrt(arg_t<vf_type> x)
{
#if 0
    vf_type y=1.0f/sqrt(x);
#else
    vf_type y=::cftal::native::rsqrt_11b(x);
    y = impl::root_r2::order2<float, false>(y, x);
#endif
    return y;
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
half_sqrt(arg_t<vf_type> x)
{
#if 1
    return sqrt(x);
#else
    vf_type y=::cftal::native::rsqrt_11b(x);
    y = impl::root_r2::order2<float, false>(y, x)*x;
    return y;
#endif
}

// local variables:
// mode: c++
// end:
#endif
