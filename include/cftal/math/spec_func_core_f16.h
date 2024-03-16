//
// Copyright (C) 2010-2024 Axel Zeuner
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
#if !defined (__CFTAL_MATH_SPEC_FUNC_CORE_F16_H__)
#define __CFTAL_MATH_SPEC_FUNC_CORE_F16_H__ 1

#include <cftal/config.h>
#include <cftal/math/spec_func.h>
#include <cftal/math/elem_func_wrapper_f16.h>
#include <cftal/math/lanczos.h>
#include <cftal/math/horner_idx.h>
#include <cftal/math/f16_tables.h>
#include <limits>
#include <utility>

namespace cftal {
    namespace math {

        // specialization of elem_func_core for f16_t and different
        // traits
        template <typename _T>
        struct spec_func_core<f16_t, _T>
            : public elem_func_core<f16_t, _T> {

            using my_type = spec_func_core<f16_t, _T>;
            using base_type = elem_func_core<f16_t, _T>;

            using vf_type = typename _T::vf_type;
            using vi_type = typename _T::vi_type;
            using vmf_type = typename _T::vmf_type;
            using vmi_type = typename _T::vmi_type;
            using vdf_type = typename _T::vdf_type;

            using d_ops= typename base_type::d_ops;

            static
            vf_type
            erf_k(arg_t<vf_type> x);

            static
            vf_type
            erfc_k(arg_t<vf_type> x);

            static
            vf_type
            erfc_tbl_k(arg_t<vf_type> x);

            static
            vf_type
            tgamma_k(arg_t<vf_type> xc, arg_t<vmf_type> xc_lt_0);

            static
            vf_type
            lgamma_k(arg_t<vf_type> xc, vi_type* signp);

            static
            vf_type
            j0_k(arg_t<vf_type> xc);

            static
            vf_type
            j1_k(arg_t<vf_type> xc);

            static
            vf_type
            y0_k(arg_t<vf_type> xc);

            static
            vf_type
            y1_k(arg_t<vf_type> xc);
        };

    }
}

template <typename _T>
typename cftal::math::spec_func_core<cftal::f16_t, _T>::vf_type
cftal::math::spec_func_core<cftal::f16_t, _T>::
erf_k(arg_t<vf_type> xc)
{
    return xc;
}

template <typename _T>
typename cftal::math::spec_func_core<cftal::f16_t, _T>::vf_type
cftal::math::spec_func_core<cftal::f16_t, _T>::
erfc_k(arg_t<vf_type> xc)
{
    return erfc_tbl_k(xc);
}

template <typename _T>
typename cftal::math::spec_func_core<cftal::f16_t, _T>::vf_type
cftal::math::spec_func_core<cftal::f16_t, _T>::
erfc_tbl_k(arg_t<vf_type> xc)
{
    return xc;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<cftal::f16_t, _T>::vf_type
cftal::math::spec_func_core<cftal::f16_t, _T>::
tgamma_k(arg_t<vf_type> x, arg_t<vmf_type> x_lt_zero)
{
    return x;

}


template <typename _T>
inline
typename cftal::math::spec_func_core<cftal::f16_t, _T>::vf_type
cftal::math::spec_func_core<cftal::f16_t, _T>::
lgamma_k(arg_t<vf_type> xc, vi_type* signp)
{
    return xc;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<cftal::f16_t, _T>::vf_type
cftal::math::spec_func_core<cftal::f16_t, _T>::
j0_k(arg_t<vf_type> xc)
{
    vf_type xp=abs(xc);
    vi_type idx=_T::as_int(xp);
    constexpr const int16_t max_idx=
        static_cast<int16_t>(f16_j0_data::max_offset-1);
    idx = min(idx, vi_type(max_idx));
    auto lk=make_variable_lookup_table<f16_t>(idx);
    vf_type y=lk.from(f16_j0_data::tbl_zero());
    y=copysign(y, xc);
    // zero and nan are handled in j0
    return y;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<cftal::f16_t, _T>::vf_type
cftal::math::spec_func_core<cftal::f16_t, _T>::
j1_k(arg_t<vf_type> xc)
{
    vf_type xp=abs(xc);
    vi_type idx=_T::as_int(xp);
    constexpr const int16_t max_idx=
        static_cast<int16_t>(f16_j1_data::max_offset-1);
    idx = min(idx, vi_type(max_idx));
    auto lk=make_variable_lookup_table<f16_t>(idx);
    vf_type y=lk.from(f16_j1_data::tbl_zero());
    y=copysign(y, xc);
    // zero and nan are handled in j1
    return y;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<cftal::f16_t, _T>::vf_type
cftal::math::spec_func_core<cftal::f16_t, _T>::
y0_k(arg_t<vf_type> xc)
{
    vf_type xp=abs(xc);
    vi_type idx=_T::as_int(xp);
    constexpr const int16_t max_idx=
        static_cast<int16_t>(f16_y0_data::max_offset-1);
    idx = min(idx, vi_type(max_idx));
    auto lk=make_variable_lookup_table<f16_t>(idx);
    vf_type y=lk.from(f16_y0_data::tbl_zero());
    // zero and nan and negative xc are handletd in y1
    return y;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<cftal::f16_t, _T>::vf_type
cftal::math::spec_func_core<cftal::f16_t, _T>::
y1_k(arg_t<vf_type> xc)
{
    vf_type xp=abs(xc);
    vi_type idx=_T::as_int(xp);
    constexpr const int16_t max_idx=
        static_cast<int16_t>(f16_y1_data::max_offset-1);
    idx = min(idx, vi_type(max_idx));
    auto lk=make_variable_lookup_table<f16_t>(idx);
    vf_type y=lk.from(f16_y1_data::tbl_zero());
    y= _T::sel(signbit(xc), _T::nan(), y);
    // zero and nan and negative xc handled in y1
    return y;
}

// Local Variables:
// mode: c++
// end:
#endif
