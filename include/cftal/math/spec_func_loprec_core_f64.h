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
#if !defined (__CFTAL_MATH_SPEC_FUNC_LOPREC_CORE_F64_H__)
#define __CFTAL_MATH_SPEC_FUNC_LOPREC_CORE_F64_H__ 1

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
#include <cftal/d_real_traits_f64.h>
#include <cftal/as.h>
#include <cftal/std_types.h>
#include <cftal/math/spec_func.h>
#include <cftal/math/func_traits_f64_s32.h>
#include <cftal/math/elem_func_loprec_core_f64.h>
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
        struct spec_func_loprec_core<double, _T>
            : public elem_func_loprec_core<double, _T> {
            using base_type = elem_func_loprec_core<double, _T>;

            using f64_core=elem_func_core<double, _T>;

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

            static
            vf_type
            tgamma_k(arg_t<vf_type> x, arg_t<vmf_type> x_lt_zero);

            // calculates lngamma for x in [1, 2]
            static
            vf_type
            __lgamma_1_2_k(arg_t<vf_type> x);

            // returns _xr in the range [1, 2]
            // returns _f (including sign)= (x+N)(x+_N-1)...(x-1)(x-2)
            // returns _inv_f as true if f must be inverted or false if not
            // lgamma(x) = lgamma(xr) * log(abs(_f))
            struct reduced_small_gamma_args {
                vf_type _xr, _f;
                vmf_type _inv_f;
                reduced_small_gamma_args() : _xr(), _f(), _inv_f() {}
                reduced_small_gamma_args(const vf_type& xr,
                                         const vf_type& f,
                                         const vmf_type& inv_f)
                    : _xr(xr), _f(f), _inv_f(inv_f) {}
            };

            static
            reduced_small_gamma_args
            __lgamma_reduce_small_k(arg_t<vf_type> x);

            static
            vf_type
            lgamma_k(arg_t<vf_type> xc, vi_type* signp);
        };
    }
}

template <typename _T>
inline
typename cftal::math::spec_func_loprec_core<double, _T>::vf_type
cftal::math::spec_func_loprec_core<double, _T>::
tgamma_k(arg_t<vf_type> x, arg_t<vmf_type> x_lt_zero)
{
    using lanczos_ratfunc=lanczos_table_g_4_35169_N5;
    vf_type xa=abs(x);
    vf_type pq=lanczos_rational_at(xa,
                                   lanczos_ratfunc::p,
                                   lanczos_ratfunc::q);
    vf_type sum = pq;
    vf_type base = xa + lanczos_ratfunc::gm0_5();
    vf_type z = xa - 0.5;

    // using f64_core = spec_func_core<double, typename _T::vhf_traits>;
    vf_type g = base_type::template exp_k<false>(-base);
    g = g * sum;
    if (_T::any_of_vmf(x_lt_zero)) {
        vf_type s;
        f64_core::sinpi_cospi_k(xa, &s, nullptr);
        using ctbl = impl::d_real_constants<d_real<double>, double>;
        vf_type q = xa * g;
        const double p= -ctbl::m_pi[0];
        q = q * s;
        // auto qh=base_type::cvt_to_vdf(q);
        // q = base_type::cvt_to_vhf(qh[0], qh[1]);
        vf_type gn= p/q;
        auto x_lt_z= x < 0.0;
        g = _T::sel(x_lt_z, gn, g);
        z = _T::sel(x_lt_z, -z, z);
    }
    g *= base_type::pow_k(base, z);
    g = _T::sel(xa < 0x1p-24, 1.0/x, g);
    return g;
}

template <typename _T>
inline
typename cftal::math::spec_func_loprec_core<double, _T>::vf_type
cftal::math::spec_func_loprec_core<double, _T>::
__lgamma_1_2_k(arg_t<vf_type> x)
{
    // [1, 2] : | p - f | <= 2^-44.625
    // coefficients for lngamma generated by sollya
    // x^0 : +0xc.65fa47157d3p-3
    const double lngamma_i0_c0=+1.5497937730248381171805e+00;
    // x^1 : -0x8.0120723c45688p-1
    const double lngamma_i0_c1=-4.0022006701062347033826e+00;
    // x^2 : +0xa.b9220e753328p+0
    const double lngamma_i0_c2=+1.0723175910580863501309e+01;
    // x^3 : -0xb.21b402b99bb8p+1
    const double lngamma_i0_c3=-2.2263305988911668009678e+01;
    // x^4 : +0x8.d7189418c7bd8p+2
    const double lngamma_i0_c4=+3.5360875152778099561601e+01;
    // x^5 : -0xa.e1a2d09217d3p+2
    const double lngamma_i0_c5=-4.3525562422436721021768e+01;
    // x^6 : +0xa.8034c8c5ec3f8p+2
    const double lngamma_i0_c6=+4.2003221696170832899497e+01;
    // x^7 : -0xf.febafbf585048p+1
    const double lngamma_i0_c7=-3.1990081305391900201585e+01;
    // x^8 : +0x9.a03a8b3dcf95p+1
    const double lngamma_i0_c8=+1.9251786618405425599576e+01;
    // x^9 : -0x9.1cfe979a2427p+0
    const double lngamma_i0_c9=-9.1132597686120355717776e+00;
    // x^10 : +0xd.6ba1913f6079p-2
    const double lngamma_i0_c10=+3.3551085181171567128899e+00;
    // x^11 : -0xf.0f946b29879ap-4
    const double lngamma_i0_c11=-9.4130365238422664120321e-01;
    // x^12 : +0xc.7290f9838dc18p-6
    const double lngamma_i0_c12=+1.9449257246580139990577e-01;
    // x^13 : -0xe.499235246b9b8p-9
    const double lngamma_i0_c13=-2.7905053126423964154901e-02;
    // x^14 : +0xa.2c3621af382dp-12
    const double lngamma_i0_c14=+2.4835695757712663092609e-03;
    // x^15 : -0xd.89ad867d65478p-17
    const double lngamma_i0_c15=-1.0328524808293270754230e-04;
    static const double ci[]={
        lngamma_i0_c15,
        lngamma_i0_c14,
        lngamma_i0_c13,
        lngamma_i0_c12,
        lngamma_i0_c11,
        lngamma_i0_c10,
        lngamma_i0_c9,
        lngamma_i0_c8,
        lngamma_i0_c7,
        lngamma_i0_c6,
        lngamma_i0_c5,
        lngamma_i0_c4,
        lngamma_i0_c3,
        lngamma_i0_c2,
        lngamma_i0_c1,
        lngamma_i0_c0
    };
    vf_type p=horner(x, ci);
    p= p * ((x-1.0) * (x-2.0));
    return p;
}

template <typename _T>
inline
typename cftal::math::spec_func_loprec_core<double, _T>::
    reduced_small_gamma_args
cftal::math::spec_func_loprec_core<double, _T>::
__lgamma_reduce_small_k(arg_t<vf_type> xc)
{
    vf_type x=xc;
    vf_type f0=1.0;
    constexpr const double il=1.0;
    constexpr const double ir=2.0;

    auto t= x>ir;

    if (_T::any_of_vmf(t)) {
        x -= _T::sel_val_or_zero(t, 1.0);
        f0= _T::sel(t, x, 1.0);
        while (_T::any_of_vmf(t= x>vf_type(ir))) {
            x -= _T::sel_val_or_zero(t, 1.0);
            f0 *= _T::sel(t, x, vf_type(1.0));
#if 0
            // avoid overflows in f0
            if (_T::any_of_vmf(t=f0[0] > 0x1p60f)) {
                vf_type h=_T::sel(t, 0x1p-61f, 1.0f);
                f0[1] *= h;
                f0[0] *= h;
                f1 *= _T::sel(t, 0x1p61f, 1.0f);
            }
#endif
        }
    }
    t= x<il;
    vmf_type inv_f=t;
    if (_T::any_of_vmf(t)) {
        vf_type& q0 = f0;
        q0=_T::sel(t, x, q0);
        x += _T::sel_val_or_zero(t, 1.0);
        while(_T::any_of_vmf(t= x<vf_type(il))) {
            q0 *= _T::sel(t, x, 1.0);
            x += _T::sel_val_or_zero(t, 1.0);
#if 0
            // avoid overflows in q0
            if (_T::any_of_vmf(t=abs(q0[0]) > 0x1p60f)) {
                vf_type h=_T::sel(t, 0x1p-61f, 1.0f);
                q0[1] *= h;
                q0[0] *= h;
                // we divide by f1
                f1 *= h;
            }
#endif
        }
        // f0 /= q0;
        // f0 = f0/q0;
    }
    return reduced_small_gamma_args{x, f0, inv_f};
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::spec_func_loprec_core<double, _T>::vf_type
cftal::math::spec_func_loprec_core<double, _T>::
lgamma_k(arg_t<vf_type> x, vi_type* signp)
{
    vf_type xa=abs(x);
    constexpr const double x_tiny= 0x1p-25;

    constexpr const double x_small_delta = 6.0;
    constexpr const double x_small_left  = 1.0-x_small_delta;
    constexpr const double x_small_right = 2.0+x_small_delta;
    constexpr const double x_large= 0x1p25;

    reduced_small_gamma_args sst;
    // note the calls to f64_core::log_k are required,
    // base_type::template __log_k<..::c_log_e> is not precise enough

    // the reflection implementation below works only if the
    // reflection for really tiny values is delegated to __lgamma_small_k
    static_assert(x_small_left < -x_tiny, "constraint violated");
    vmf_type xa_in_small =
        ((x >= x_small_left) & (x <= x_small_right) & (xa >= x_tiny));

    vf_type base=xa;
    if (_T::any_of_vmf(xa_in_small)) {
        vf_type xs=_T::sel(xa_in_small, x, 1.5);
        sst = __lgamma_reduce_small_k(xs);
        vf_type log_a=abs(sst._f);
        base = _T::sel(xa_in_small, log_a, base);
    }

    using lanczos_ratfunc=lanczos_table_g_4_35169_N5;
    vmf_type xa_in_lanczos =
        (((x < x_small_left) | (x > x_small_right)) & (xa < x_large));
    if (_T::any_of_vmf(xa_in_lanczos)) {
        vf_type t= xa + lanczos_ratfunc::gm0_5();
        base= _T::sel(xa_in_lanczos, t, base);
    }
    // lb contains log(xa+g-0.5) for xa_in_lanczos
    // log(xa) for xa > x_large | xa < x_tiny
    // log(f) for xa < x_small & xa >= tiny
    vf_type lb= f64_core::log_k(base);
    vf_type lg=0.0;
    vmf_type xa_in_large = (xa >= x_large);
    if (_T::any_of_vmf(xa_in_large)) {
        // log(gamma(x)) = xa * (log(xa) - 1.0), xa >> 1
        vf_type t=(lb -1.0)*xa;
        lg = _T::sel(xa_in_large, t, lg);
    }
    if (_T::any_of_vmf(xa_in_lanczos)) {
        // lanczos sum:
        auto pq=lanczos_rational_at(xa,
                                    lanczos_ratfunc::p,
                                    lanczos_ratfunc::q);
        vf_type sum = pq;
        vf_type z= xa - 0.5;
        // g = z * log(base) + log(sum) - base;
        vf_type ls=f64_core::log_k(sum);
        vf_type t= (z * lb) - base + ls;
        lg = _T::sel(xa_in_lanczos, t, lg);
    }
    if (_T::any_of_vmf(xa_in_small)) {
        vf_type lg12=__lgamma_1_2_k(sst._xr);
        vf_type slb= _T::sel(sst._inv_f, -lb, lb);
        vf_type t= lg12 + slb;
        lg = _T::sel(xa_in_small, t, lg);
    }
    // xa_in_tiny:
    vmf_type xa_in_tiny= xa < x_tiny;
    lg = _T::sel(xa_in_tiny, -lb, lg);

    // reflection part
    vi_type sgn=1;
    vmf_type x_lt_0 = x < 0.0;
    if (_T::any_of_vmf(x_lt_0)) {
        // tiny
        vmf_type t= x_lt_0 & xa_in_tiny;
        sgn = _T::sel_vi(_T::vmf_to_vmi(t), -1, sgn);
        // small
        t = x_lt_0 & xa_in_small;
        if (_T::any_of_vmf(t)) {
            vf_type sgn_g=copysign(vf_type(1.0), sst._f);
            vi_type si= _T::cvt_f_to_i(sgn_g);
            sgn=_T::sel_vi(_T::vmf_to_vmi(t), si, sgn);
        }
        // lanczos
        t = x_lt_0 & xa_in_lanczos;
        if (_T::any_of_vmf(t)) {
            // G(-z) = -pi/[sin(pi*z)*z * G(z)]
            vf_type s;
            f64_core::sinpi_cospi_k(xa, &s, nullptr);
            using ctbl = impl::d_real_constants<d_real<double>, double>;
            // log(G(-z)) = log(pi) - log(z) - log(abs(sin(pi*z))-log(G(z))
            //            = log(pi) - log(abs(sin(pi*z)*z) - log(G(z))
            //            = log(pi) - [log(abs(sin(pi*z)*z) + log(G(z))]
            vf_type sa= abs(s);
            sa *= xa;
            vf_type lg_n=f64_core::log_k(sa);
            lg_n += lg;
            lg_n = ctbl::m_ln_pi[0] - lg_n;
            lg = _T::sel(t, lg_n, lg);
            vmf_type s_lt_0 = (s >= 0.0) & t;
            vmi_type i_s_lt_0 = _T::vmf_to_vmi(s_lt_0);
            sgn = _T::sel_vi(i_s_lt_0, -1, sgn);
        }
        // no large handling because xc is integer anyway
    }
    if (signp != nullptr)
        *signp = sgn;
    return lg;
}

#endif // __CFTAL_MATH_SPEC_FUNC_LOPREC_CORE_F64_H__
