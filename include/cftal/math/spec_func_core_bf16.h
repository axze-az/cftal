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
#define __CFTAL_MATH_SPEC_FUNC_CORE_BF16_H__ 1

#include <cftal/config.h>
#include <cftal/math/spec_func.h>
#include <cftal/math/elem_func_wrapper_bf16.h>
#include <cftal/math/lanczos.h>
#include <cftal/math/horner_idx.h>
#include <cftal/math/bf16_tables.h>
#include <limits>
#include <utility>

namespace cftal {
    namespace math {

        // specialization of elem_func_core for bf16_t and different
        // traits
        template <typename _T>
        struct spec_func_core<bf16_t, _T> {

            using my_type = spec_func_core<bf16_t, _T>;

            using vf_type = typename _T::vf_type;
            using vi_type = typename _T::vi_type;
            using vmf_type = typename _T::vmf_type;
            using vmi_type = typename _T::vmi_type;
            using vdf_type = typename _T::vdf_type;

            using d_ops= typename base_type::d_ops;

            template <typename _TBL>
            static
            vi_type
            cvt_to_index_4(arg_t<vf_type> x);

            template <typename _TBL>
            static
            vf_type
            lookup_from(arg_t<vf_type> x);

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
template <typename _TBL>
inline
typename
cftal::math::spec_func_core<cftal::bf16_t, _T>::vi_type
cftal::math::spec_func_core<cftal::bf16_t, _T>::
cvt_to_index_4(arg_t<vf_type> x)
{
    vi_type idx;
    if (_TBL::zero_offset == 0) {
        vf_type ax=abs(x);
        idx=_T::as_int(ax);
    } else {
        vmi_type ltz=_T::vmf_to_vmi(signbit(x));
        vi_type i=_T::as_int(x);
        const int16_t nmsk=0x7fff;
        vi_type nidx= i^nmsk; // or nmsk - i;
        idx=_T::sel_vi(ltz, nidx, i);
        const vi_type min_idx(static_cast<int16_t>(_TBL::min_offset));
        idx=max(idx, min_idx);
    }
    const vi_type max_idx(static_cast<int16_t>(_TBL::max_offset-1));
    idx=min(idx, max_idx);
    return idx;
}

template <typename _T>
template <typename _TBL>
inline
typename
cftal::math::spec_func_core<cftal::bf16_t, _T>::vf_type
cftal::math::spec_func_core<cftal::bf16_t, _T>::
lookup_from(arg_t<vf_type> x)
{
    vi_type idx=cvt_to_index_4<_TBL>(x);
    auto lk=make_variable_lookup_table<bf16_t>(idx);
    vf_type y=lk.from(_TBL::tbl_zero());
    return y;
}

template <typename _T>
typename cftal::math::spec_func_core<cftal::bf16_t, _T>::vf_type
cftal::math::spec_func_core<cftal::bf16_t, _T>::
erf_k(arg_t<vf_type> xc)
{
    vf_type y=lookup_from<bf16_erf_data>(xc);
    y=copysign(y, xc);
    return y;
}

template <typename _T>
typename cftal::math::spec_func_core<cftal::bf16_t, _T>::vf_type
cftal::math::spec_func_core<cftal::bf16_t, _T>::
erfc_k(arg_t<vf_type> xc)
{
    return erfc_tbl_k(xc);
}

template <typename _T>
typename cftal::math::spec_func_core<cftal::bf16_t, _T>::vf_type
cftal::math::spec_func_core<cftal::bf16_t, _T>::
erfc_tbl_k(arg_t<vf_type> xc)
{
    vf_type y=lookup_from<bf16_erfc_data>(xc);
    return y;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<cftal::bf16_t, _T>::vf_type
cftal::math::spec_func_core<cftal::bf16_t, _T>::
tgamma_k(arg_t<vf_type> x, arg_t<vmf_type> x_lt_zero)
{
    vf_type y=lookup_from<bf16_tgamma_data>(x);
    // zero and nan and negative xc are handletd in tgamma
    return y;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<cftal::bf16_t, _T>::vf_type
cftal::math::spec_func_core<cftal::bf16_t, _T>::
lgamma_k(arg_t<vf_type> xc, vi_type* signp)
{
    vi_type idx=cvt_to_index_4<bf16_lgamma_data>(xc);
    using vli_type=typename _T::vli_type;
    using v2i_type=typename _T::v2i_type;
    vli_type idx32=cvt<vli_type>(idx);
    auto lk=make_variable_lookup_table<typename vli_type::value_type>(idx32);
    vli_type t=lk.from(bf16_lgamma_data::tbl_zero());
    v2i_type t1=as<v2i_type>(t);
    vi_type yi=odd_elements(t1);
    vmf_type is_nan=isnan(xc);
    vf_type y=as<vf_type>(yi);
    y = _T::sel(is_nan, xc, y);
    if (signp != nullptr) {
        vi_type s=even_elements(t1);
        vmi_type i_is_nan=_T::vmf_to_vmi(is_nan);
        s = _T::sel_vi(i_is_nan, vi_type(1), s);
        *signp= s;
    }
    return y;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<cftal::bf16_t, _T>::vf_type
cftal::math::spec_func_core<cftal::bf16_t, _T>::
j0_k(arg_t<vf_type> xc)
{
    vf_type y=lookup_from<bf16_j0_data>(xc);
    // zero and nan are handled in j0
    return y;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<cftal::bf16_t, _T>::vf_type
cftal::math::spec_func_core<cftal::bf16_t, _T>::
j1_k(arg_t<vf_type> xc)
{
    vf_type y=lookup_from<bf16_j1_data>(xc);
    y=mulsign(y, xc);
    // zero and nan are handled in j1
    return y;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<cftal::bf16_t, _T>::vf_type
cftal::math::spec_func_core<cftal::bf16_t, _T>::
y0_k(arg_t<vf_type> xc)
{
    vf_type y=lookup_from<bf16_y0_data>(xc);
    // zero and nan and negative xc are handletd in y1
    return y;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<cftal::bf16_t, _T>::vf_type
cftal::math::spec_func_core<cftal::bf16_t, _T>::
y1_k(arg_t<vf_type> xc)
{
    vf_type y=lookup_from<bf16_y1_data>(xc);
    // zero and nan and negative xc handled in y1
    return y;
}

// Local Variables:
// mode: c++
// end:
#endif
