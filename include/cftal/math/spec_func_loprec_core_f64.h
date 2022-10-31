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
            struct reduced_small_gamma_args_vf {
                vf_type _xr, _f;
                vmf_type _inv_f;
                reduced_small_gamma_args_vf() : _xr(), _f(), _inv_f() {}
                reduced_small_gamma_args_vf(const vf_type& xr,
                                            const vf_type& f,
                                            const vmf_type& inv_f)
                    : _xr(xr), _f(f), _inv_f(inv_f) {}
            };

            static
            reduced_small_gamma_args_vf
            __lgamma_reduce_small_k(arg_t<vf_type> x);

        };
    }
}

template <typename _T>
inline
typename cftal::math::spec_func_loprec_core<double, _T>::vf_type
cftal::math::spec_func_loprec_core<double, _T>::
tgamma_k(arg_t<vf_type> x, arg_t<vmf_type> x_lt_zero)
{
    // using lanczos_ratfunc=lanczos_table_g_5_59172_N6;
    using lanczos_ratfunc=lanczos_table_g_4_35169_N5;
    vf_type xa=abs(x);
    vf_type pq=lanczos_rational_at(xa,
                                   lanczos_ratfunc::p,
                                   lanczos_ratfunc::q);
    vf_type sum = pq;
    vf_type base = xa + lanczos_ratfunc::gm0_5();
    vf_type z = xa - 0.5;

    // using f64_core = spec_func_core<double, typename _T::vhf_traits>;
    vf_type g = f64_core::template exp_k<false>(-base);
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

#endif // __CFTAL_MATH_SPEC_FUNC_LOPREC_CORE_F64_H__
