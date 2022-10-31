//
// Copyright (C) 2010-2022 Axel Zeuner
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
#if !defined (__CFTAL_MATH_ELEM_FUNC_LOPREC_CORE_F64_H__)
#define __CFTAL_MATH_ELEM_FUNC_LOPREC_CORE_F64_H__ 1

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
#include <cftal/as.h>
#include <cftal/std_types.h>
#include <cftal/math/elem_func.h>
#include <cftal/math/func_traits_f64_s32.h>
#include <cftal/math/func_data.h>
#include <cftal/math/misc.h>
#include <cftal/math/horner.h>
#include <cftal/math/impl_d_real_constants_f64.h>
#include <cftal/math/payne_hanek.h>
#include <cftal/mem.h>
#include <cftal/vec_t_n.h>

namespace cftal {
    namespace math {

        // specialization of elem_func_core for double and different
        // traits
        template <typename _T>
        struct elem_func_loprec_core<double, _T> {
            using vf_type = typename _T::vf_type;
            using vi_type = typename _T::vi_type;
            using vli_type = typename _T::vli_type;
            using vi2_type = typename _T::vi2_type;
            using vmf_type = typename _T::vmf_type;
            using vmi_type = typename _T::vmi_type;
            using vmli_type = typename _T::vmli_type;
            using vmi2_type = typename _T::vmi2_type;
            using vdf_type = typename _T::vdf_type;

            using d_ops=d_real_ops<vf_type,
                                   d_real_traits<vf_type>::fma>;

            using f32_traits= typename _T::vlf_traits;
            using vlf_type = typename f32_traits::vf_type;
            using vmlf_type = typename f32_traits::vmf_type;

            // return y*2^k
            static
            vf_type
            __mul_two_pow(arg_t<vf_type> y,
                          arg_t<vi_type> k);

            // return y*2^rint(kf)
            static
            vf_type
            __mul_two_pow(arg_t<vf_type> y,
                          arg_t<vf_type> kf);

            // arguments are the reduced xr in
            // [-log(2)/2, log(2)/2], and the argument
            // k as argument for __mul_two_pow
            // x is the unreduced argument
            // calculates %e^(xrh)*2^k - 1 if exp_m1 is true,
            // %e^(xrh+xrl)*2^k otherwise
            template <bool _EXP_M1>
            static
            vf_type
            __exp_k(arg_t<vf_type> xr,
                    arg_t<vf_type> kfd, arg_t<vf_type> x);

            // calculates %e^xr for xr in [-log(2)/(2*N),
            // log(2)/(2*N)], idx is the table index
            static
            vf_type
            __exp_tbl_k(arg_t<vf_type> xr,
                        arg_t<vi_type> idx);
            // calculates 2^k*%e^xr for xr in [-log(2)/(2*N),
            // log(2)/(2*N)], idx is the table index,
            static
            vf_type
            __exp_tbl_k(arg_t<vf_type> xr,
                        arg_t<vi_type> idx,
                        arg_t<vi_type> k);

            // argument reduction for %e^(x)
            // return 2^k * (xr) with xr in
            // [-log(2)/2, log(2)/2] for calling __exp_k
            static
            void
            __reduce_exp_arg(vf_type& xr,
                             vf_type& kf,
                             arg_t<vf_type> x);

            // argument reduction for %e^(x)
            // return 2^k * (xr) with xr in
            // [-log(2)/(2*N), log(2)/(2*N)] for calling __exp_tbl_k
            static
            void
            __reduce_exp_arg(vf_type& xr,
                             vi_type& idx,
                             vi_type& k,
                             arg_t<vf_type> x);

            template <bool _EXP_M1>
            static
            vf_type
            exp_k(arg_t<vf_type> x);

            template <bool _EXP2_M1>
            static
            vf_type
            exp2_k(arg_t<vf_type> x);

            template <bool _EXP2_M1>
            static
            vf_type
            exp10_k(arg_t<vf_type> x);

            static
            vi2_type
            __reduce_log_arg(vf_type& xr,
                             arg_t<vf_type> x);

            enum log_func {
                c_log_e,
                c_log_2,
                c_log_10
            };

            template <log_func _LFUNC>
            static
            vf_type
            __log_k(arg_t<vf_type> xc);


            template <log_func _LFUNC>
            static
            vf_type
            __log_k12(arg_t<vf_type> xc);

        };
    }
}


template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_loprec_core<double, _T>::vf_type
cftal::math::elem_func_loprec_core<double, _T>::
__mul_two_pow(arg_t<vf_type> y, arg_t<vi_type> k)
{
    vi_type ep(k << 20);
    vi2_type ir=combine_zeroeven_odd(ep);
    vi2_type yi=as<vi2_type>(y) + ir;
    vf_type ys = as<vf_type>(yi);
    return ys;
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_loprec_core<double, _T>::vf_type
cftal::math::elem_func_loprec_core<double, _T>::
__mul_two_pow(arg_t<vf_type> y, arg_t<vf_type> kf)
{
    vi_type k=_T::cvt_f_to_i(kf);
    return __mul_two_pow(y, k);
}

template <typename _T>
template <bool _EXP_M1>
typename cftal::math::elem_func_loprec_core<double, _T>::vf_type
cftal::math::elem_func_loprec_core<double, _T>::
__exp_k(arg_t<vf_type> xrd, arg_t<vf_type> kfd,
        arg_t<vf_type> x)
{
    // [-0.3465735912322998046875, 0.3465735912322998046875] : | p - f | <= 2^-33.65625
    // coefficients for exp generated by sollya
    // x^0 : +0x8p-3
    constexpr
    const double exp_c0=+1.0000000000000000000000e+00;
    // x^1 : +0x8p-3
    constexpr
    const double exp_c1=+1.0000000000000000000000e+00;
    // x^2 : +0x8.000001d0d64b8p-4
    constexpr
    const double exp_c2=+5.0000000676426992196610e-01;
    // x^3 : +0xa.aaaaa21b31aep-6
    constexpr
    const double exp_c3=+1.6666665869413577194535e-01;
    // x^4 : +0xa.aaa46ec513648p-8
    constexpr
    const double exp_c4=+4.1666295092978318514998e-02;
    // x^5 : +0x8.88938475a673p-10
    constexpr
    const double exp_c5=+8.3334970089822928140944e-03;
    // x^6 : +0xb.6c679f8263a88p-13
    constexpr
    const double exp_c6=+1.3944648636194554528617e-03;
    // x^7 : +0xc.f8452631b28p-16
    constexpr
    const double exp_c7=+1.9790352070606781476059e-04;
    static_assert(exp_c0 == 1.0, "oops");
    static_assert(exp_c1 == 1.0, "oops");

    constexpr
    static const double ci[]= {
        exp_c7, exp_c6, exp_c5, exp_c4, exp_c3, exp_c2
    };
    vf_type xrd2=xrd * xrd;
    vf_type yd= horner2(xrd, xrd2, ci)*xrd2 + xrd;
    yd+= exp_c0;
    yd=__mul_two_pow(yd, kfd);
    if (_EXP_M1 == true) {
        yd -= exp_c0;
        yd= _T::sel(abs(x) < 0x1p-25, x, yd);
    }
    return yd;
}

template <typename _T>
typename cftal::math::elem_func_loprec_core<double, _T>::vf_type
cftal::math::elem_func_loprec_core<double, _T>::
__exp_tbl_k(arg_t<vf_type> xr, arg_t<vi_type> idx)
{
    auto lk=make_variable_lookup_table<double>(idx);
    const auto& tbl=exp_data<double>::_tbl;
    vf_type th=lk.from(tbl._2_pow_i_n_h);

    // [-1.0830424726009368896484375e-2, 1.0830424726009368896484375e-2] : | p - f | <= 2^-32.6875
    // coefficients for exp generated by sollya
    // x^1 : +0x8p-3
    constexpr
    const double exp_c1=+1.0000000000000000000000e+00;
    // x^2 : +0x8.0003d76f37bf8p-4
    constexpr
    const double exp_c2=+5.0000366357879488798943e-01;
    // x^3 : +0xa.aaac332fabb6p-6
    constexpr
    const double exp_c3=+1.6666703222898193725854e-01;
    static_assert(exp_c1==1.0, "oops");
    vf_type x2=xr*xr;
    vf_type p= horner(xr, exp_c3, exp_c2);
    vf_type eh=xr + x2*p;
    vf_type yd=th + th*eh;
    return yd;
}

template <typename _T>
typename cftal::math::elem_func_loprec_core<double, _T>::vf_type
cftal::math::elem_func_loprec_core<double, _T>::
__exp_tbl_k(arg_t<vf_type> xr, arg_t<vi_type> idx, arg_t<vi_type> ki)
{
    vf_type yd=__exp_tbl_k(xr, idx);
    return __mul_two_pow(yd, ki);
}

template <typename _T>
void
cftal::math::elem_func_loprec_core<double, _T>::
__reduce_exp_arg(vf_type& xr, vf_type& kf, arg_t<vf_type> xd)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    kf= rint(vf_type(xd * ctbl::m_1_ln2[0]));
    xr= xd - kf * ctbl::m_ln2[0];
}

template <typename _T>
void
cftal::math::elem_func_loprec_core<double, _T>::
__reduce_exp_arg(vf_type& xr, vi_type& idx, vi_type& k, arg_t<vf_type> xd)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    static_assert(exp_data<double>::EXP_N==32,
                 "exp_data<double>::EXP_N==32");
    // N
    const double _N=exp_data<double>::EXP_N;
    // N/ln(2)
    const double _32_ln2=_N * ctbl::m_1_ln2[0];
    // ln2/N;
    const double _ln2_32=ctbl::m_ln2[0] * (1.0/_N);
    vf_type kf= rint(vf_type(xd * _32_ln2));
    xr= xd - kf * _ln2_32;
    vi_type ki=cvt<vi_type>(kf);
    idx = ki & exp_data<double>::EXP_IDX_MASK;
    k = ki >> exp_data<double>::EXP_SHIFT;
}

template <typename _T>
template <bool _EXP_M1>
inline
typename cftal::math::elem_func_loprec_core<double, _T>::vf_type
cftal::math::elem_func_loprec_core<double, _T>::
exp_k(arg_t<vf_type> xc)
{
    vf_type yd;
    if (_EXP_M1==false) {
        vi_type idx, ki;
        vf_type xrd;
        __reduce_exp_arg(xrd, idx, ki, xc);
        yd=__exp_tbl_k(xrd, idx, ki);
    } else {
        vf_type xr, kf;
        __reduce_exp_arg(xr, kf, xc);
        yd=__exp_k<_EXP_M1>(xr, kf, xc);
    }
    return yd;
}

template <typename _T>
template <bool _EXP2_M1>
inline
typename cftal::math::elem_func_loprec_core<double, _T>::vf_type
cftal::math::elem_func_loprec_core<double, _T>::
exp2_k(arg_t<vf_type> xc)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    vf_type xd=xc*ctbl::m_ln2[0];
    vf_type yd=exp_k<_EXP2_M1>(xd);
    return yd;
}

template <typename _T>
template <bool _EXP10_M1>
inline
typename cftal::math::elem_func_loprec_core<double, _T>::vf_type
cftal::math::elem_func_loprec_core<double, _T>::
exp10_k(arg_t<vf_type> xc)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    vf_type xd=xc*ctbl::m_ln10[0];
    vf_type yd=exp_k<_EXP10_M1>(xd);
    return yd;
}

template <typename _T>
inline
typename cftal::math::elem_func_loprec_core<double, _T>::vi2_type
cftal::math::elem_func_loprec_core<double, _T>::
__reduce_log_arg(vf_type& xr, arg_t<vf_type> xc)
{
    // round(sqrt(2)/2, 53-32, RD);
    // 0.70710659027099609375
    constexpr
    const bytes8 offs=int64_t(0x3fe6a09e00000000LL);
#if 0
    using fc = func_constants<double>;
    vmf_type is_denom=xc <= fc::max_denormal();
    vf_type x=_T::sel(is_denom, xc*0x1p54, xc);
    vi2_type k=_T::sel_vi2(_T::vmf_to_vmi2(is_denom),
                           vi2_type(-54-_T::bias()),
                           vi2_type(-_T::bias()));
#else
    vi2_type k=-_T::bias();
#endif
    /* reduce x into [sqrt(2)/2, sqrt(2)] */
    vli_type h=as<vli_type>(xc);
    constexpr const int64_t one=0x3ff0000000000000LL;
    h += (one - offs.s64());
    vi2_type h2=as<vi2_type>(h);
    constexpr const int64_t msk=0x000fffffffffffffLL;
    h = (h & msk) + offs.s64();
    k += (h2>>20);
    xr = as<vf_type>(h);
    return k;
}

template <typename _T>
template <typename
    cftal::math::elem_func_loprec_core<double, _T>::log_func _LFUNC>
inline
typename cftal::math::elem_func_loprec_core<double, _T>::vf_type
cftal::math::elem_func_loprec_core<double, _T>::
__log_k(arg_t<vf_type> xc)
{
    vf_type xr;
    vi2_type ki=__reduce_log_arg(xr, xc);
    vf_type r;
    r = xr - 1.0;

    // [-0.292893230915069580078125, 0.41421353816986083984375] : | p - f | <= 2^-29.390625
    // coefficients for log generated by sollya
    // x^1 : +0xf.fffffffd3046p-4
    constexpr
    const double log_c1=+9.9999999995908828154256e-01;
    // x^2 : -0xf.ffffc1217c6bp-5
    constexpr
    const double log_c2=-4.9999988289699837107349e-01;
    // x^3 : +0xa.aaaa83416f8a8p-5
    constexpr
    const double log_c3=+3.3333325992451651176296e-01;
    // x^4 : -0x8.002145c45f9fp-5
    constexpr
    const double log_c4=-2.5001586557754140738297e-01;
    // x^5 : +0xc.cd1f5e066525p-6
    constexpr
    const double log_c5=+2.0001968557478938537386e-01;
    // x^6 : -0xa.a1387ca90d9cp-6
    constexpr
    const double log_c6=-1.6609012769569075906873e-01;
    // x^7 : +0x9.138d3cd84f5p-6
    constexpr
    const double log_c7=+1.4181834165468831798762e-01;
    // x^8 : -0x8.79cf021e5c7e8p-6
    constexpr
    const double log_c8=-1.3243460852522295767564e-01;
    // x^9 : +0x8.424ce7ea5f5b8p-6
    constexpr
    const double log_c9=+1.2904665611266860625328e-01;
    // x^10 : -0x9.c14a282383dep-7
    constexpr
    const double log_c10=-7.6211232756604851967808e-02;
    constexpr
    static const double ci[]={
        log_c10,
        log_c9, log_c8, log_c7, log_c6,
        log_c5, log_c4, log_c3, log_c2, log_c1
    };
    vf_type r2=r*r;
    vf_type p=horner2(r, r2, ci);
    vf_type kf=_T::cvt_i_to_f(_T::vi2_odd_to_vi(ki));
    vf_type ll=r*p;
    vf_type lh;
    using ctbl=impl::d_real_constants<d_real<double>, double>;
    if (_LFUNC==log_func::c_log_e) {
        lh = (kf * ctbl::m_ln2[0]) + ll;
    } else if (_LFUNC==log_func::c_log_2) {
        lh = kf + ll * ctbl::m_1_ln2[0];
    } else if (_LFUNC==log_func::c_log_10) {
        lh = kf * ctbl::m_lg2[0] + ll * ctbl::m_1_ln10[0];
    }
    return lh;
}

template <typename _T>
template <typename
    cftal::math::elem_func_loprec_core<double, _T>::log_func _LFUNC>
inline
typename cftal::math::elem_func_loprec_core<double, _T>::vf_type
cftal::math::elem_func_loprec_core<double, _T>::
__log_k12(arg_t<vf_type> xc)
{
    vf_type xr;
    vi2_type ki=__reduce_log_arg(xr, xc);
    vf_type r;
    r = xr - 1.0;

    // [-0.292893230915069580078125, 0.41421353816986083984375] : | p - f | <= 2^-34.65625
    // coefficients for log generated by sollya
    // x^1 : +0x8p-3
    constexpr
    const double log_c1=+1.0000000000000000000000e+00;
    // x^2 : -0x8.000000c3473cp-4
    constexpr
    const double log_c2=-5.0000000284167267494695e-01;
    // x^3 : +0xa.aaaaa36a67dbp-5
    constexpr
    const double log_c3=+3.3333331982725711295501e-01;
    // x^4 : -0xf.fffd6786b4f1p-6
    constexpr
    const double log_c4=-2.4999938116054837289326e-01;
    // x^5 : +0xc.ccd0d882e603p-6
    constexpr
    const double log_c5=+2.0000096458133514998323e-01;
    // x^6 : -0xa.ab4437fb0c538p-6
    constexpr
    const double log_c6=-1.6670327631817835611905e-01;
    // x^7 : +0x9.24919a40f1ebp-6
    constexpr
    const double log_c7=+1.4285697997891472210696e-01;
    // x^8 : -0xf.e3600a9c1c398p-7
    constexpr
    const double log_c8=-1.2412643926674764294216e-01;
    // x^9 : +0xe.1b644643830a8p-7
    constexpr
    const double log_c9=+1.1021092825742358212171e-01;
    // x^10 : -0xd.ea0bac440641p-7
    constexpr
    const double log_c10=-1.0870500480091219164258e-01;
    // x^11 : +0xd.bb064f4d63e08p-7
    constexpr
    const double log_c11=+1.0727003929312585450706e-01;
    // x^12 : -0xf.58521b5ab5cd8p-8
    constexpr
    const double log_c12=-5.9941417387299376906551e-02;
    static_assert(log_c1 == 1.0, "constraint violated");

    static const double ci[]={
        log_c12, log_c11, log_c10,
        log_c9, log_c8, log_c7, log_c6,
        log_c5, log_c4, log_c3, log_c2
    };
    vf_type r2=r*r;
    vf_type p=horner2(r, r2, ci);
    vf_type kf=_T::cvt_i_to_f(_T::vi2_odd_to_vi(ki));
    vf_type ll=r*p;
    vf_type lh;
    using ctbl=impl::d_real_constants<d_real<double>, double>;
    if (_LFUNC==log_func::c_log_e) {
        lh = (kf * ctbl::m_ln2[0]) + ll;
    } else if (_LFUNC==log_func::c_log_2) {
        lh = kf + ll * ctbl::m_1_ln2[0];
    } else if (_LFUNC==log_func::c_log_10) {
        lh = kf * ctbl::m_lg2[0] + ll * ctbl::m_1_ln10[0];
    }
    return lh;
}

#endif // __CFTAL_MATH_ELEM_FUNC_CORE_LOPREC_F64_H__
