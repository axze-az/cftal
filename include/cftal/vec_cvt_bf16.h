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
#if !defined (__CFTAL_VEC_CVT_BF16_H__)
#define __CFTAL_VEC_CVT_BF16_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/constants.h>
#include <cftal/cvt_bf16.h>
#include <cftal/vec_t_n.h>
#include <cftal/vec_t_1.h>
#include <cftal/vec_spec.h>

namespace cftal {

    namespace impl {

        // round f32 to bf16 using round to nearest even rounding
        template <bool _FLUSH_SUBNORMALS_TO_ZERO, std::size_t _N>
        vec<float, _N>
        _rne_f32_to_bf16(const vec<float, _N>& v);

        // convert  vec<f32, _N> to vec<mf_bf16_t, _N> using
        // round to nearest even rounding
        template <std::size_t _N>
        vec<mf_bf16_t, _N>
        _cvt_f32_to_bf16(const vec<float, _N>& v);

        // round f32 to bf16 using round to zero rounding
        template <bool _FLUSH_SUBNORMALS_TO_ZERO, std::size_t _N>
        vec<float, _N>
        _rz_f32_to_bf16(const vec<float, _N>& v);

        // convert vec<f32, _N> to vec<mf_bf16_t, _N> using
        // round to zero rounding
        template <std::size_t _N>
        vec<mf_bf16_t, _N>
        _cvt_f32_to_bf16_rz(const vec<float, _N>& v);

        // convert vec<mf_bf16_t, _N> to vec<f32, _N>
        template <std::size_t _N>
        vec<float, _N>
        _cvt_bf16_to_f32(const vec<mf_bf16_t, _N>& v);

    }

    // convert  vec<f32, _N> to vec<mf_bf16_t, _N> using
    // round to nearest even rounding
    template <std::size_t _N>
    vec<mf_bf16_t, _N>
    cvt_f32_to_bf16(const vec<float, _N>& v);

    // convert  vec<f32, 1> to vec<mf_bf16_t, 1> using
    // round to nearest even rounding
    vec<mf_bf16_t, 1>
    cvt_f32_to_bf16(const vec<float, 1>& v);

    // convert  vec<f32, 2> to vec<mf_bf16_t, 2> using
    // round to nearest even rounding
    vec<mf_bf16_t, 2>
    cvt_f32_to_bf16(const vec<float, 2>& v);

    // convert  vec<f32, 4> to vec<mf_bf16_t, 4> using
    // round to nearest even rounding
    vec<mf_bf16_t, 4>
    cvt_f32_to_bf16(const vec<float, 4>& v);

    // convert  vec<f32, 8> to vec<mf_bf16_t, 8> using
    // round to nearest even rounding
    vec<mf_bf16_t, 8>
    cvt_f32_to_bf16(const vec<float, 8>& v);

    // convert  vec<f32, 16> to vec<mf_bf16_t, 16> using
    // round to nearest even rounding
    vec<mf_bf16_t, 16>
    cvt_f32_to_bf16(const vec<float, 16>& v);

    // convert vec<f32, _N> to vec<mf_bf16_t, _N> using
    // round to zero rounding
    template <std::size_t _N>
    vec<mf_bf16_t, _N>
    cvt_f32_to_bf16_rz(const vec<float, _N>& v);

    // convert vec<f32, 1> to vec<mf_bf16_t, 1> using
    // round to zero rounding
    vec<mf_bf16_t, 1>
    cvt_f32_to_bf16_rz(const vec<float, 1>& v);

    // convert vec<f32, 2> to vec<mf_bf16_t, 2> using
    // round to zero rounding
    vec<mf_bf16_t, 2>
    cvt_f32_to_bf16_rz(const vec<float, 2>& v);

    // convert vec<f32, 4> to vec<mf_bf16_t, 4> using
    // round to zero rounding
    vec<mf_bf16_t, 4>
    cvt_f32_to_bf16_rz(const vec<float, 4>& v);

    // convert vec<f32, 8> to vec<mf_bf16_t, 8> using
    // round to zero rounding
    vec<mf_bf16_t, 8>
    cvt_f32_to_bf16_rz(const vec<float, 8>& v);

    // convert vec<f32, 8> to vec<mf_bf16_t, 8> using
    // round to zero rounding
    vec<mf_bf16_t, 16>
    cvt_f32_to_bf16_rz(const vec<float, 16>& v);

    // convert vec<mf_bf16_t, _N> to vec<f32, _N>
    template <std::size_t _N>
    vec<float, _N>
    cvt_bf16_to_f32(const vec<mf_bf16_t, _N>& v);

    // convert vec<mf_bf16_t, 1> to vec<f32, 1>
    vec<float, 1>
    cvt_bf16_to_f32(const vec<mf_bf16_t, 1>& v);

    // convert vec<mf_bf16_t, 2> to vec<f32, 2>
    vec<float, 2>
    cvt_bf16_to_f32(const vec<mf_bf16_t, 2>& v);

    // convert vec<mf_bf16_t, 4> to vec<f32, 4>
    vec<float, 4>
    cvt_bf16_to_f32(const vec<mf_bf16_t, 4>& v);

    // convert vec<mf_bf16_t, 8> to vec<f32, 8>
    vec<float, 8>
    cvt_bf16_to_f32(const vec<mf_bf16_t, 8>& v);

    // convert vec<mf_bf16_t, 16> to vec<f32, 16>
    vec<float, 16>
    cvt_bf16_to_f32(const vec<mf_bf16_t, 16>& v);
}

template <bool _FLUSH_SUBNORMALS_TO_ZERO, std::size_t _N>
cftal::vec<float, _N>
cftal::impl::_rne_f32_to_bf16(const vec<float, _N>& v)
{
    using vf_type = vec<float, _N>;
    vf_type vne=round_to_nearest_even_last_bits<16>(v);
    // infinities are not affected by rounding
    typename vf_type::mask_type is_nan=isnan(v);
    vne = select(is_nan, v, vne);
    if constexpr (_FLUSH_SUBNORMALS_TO_ZERO==true) {
        // flush subnormals to zero
        typename vf_type::mask_type is_subnorm=
            abs(v) < std::numeric_limits<float>::min();
        constexpr const float mz=-0.0f;
        vne = select(is_subnorm, vf_type(v & mz), vne);
    }
    return vne;
}

template <std::size_t _N>
cftal::vec<cftal::mf_bf16_t, _N>
cftal::impl::_cvt_f32_to_bf16(const vec<float, _N>& v)
{
#if 1
    constexpr bool ftz = __CFTAL_CFG_FLUSH_BFLOAT16_TO_ZERO > 0;
    auto vne = _rne_f32_to_bf16<ftz>(v);
    auto t=as<vec<cftal::mf_bf16_t, 2*_N> >(vne);
    auto r=odd_elements(t);
#else
    auto vne = _rne_f32_to_bf16<false>(v);
    auto t=as<vec<cftal::mf_bf16_t, 2*_N> >(vne);
    using vi_type = vec<cftal::mf_bf16_t,_N>;
    vi_type r=odd_elements(t);
#if __CFTAL_CFG_FLUSH_BFLOAT16_TO_ZERO > 0
    vi_type ra=r & int16_t(0x7fff);
    typename vi_type::mask_type is_subnorm= ra < int16_t(0x0080);
    vi_type rsn= r & int16_t(0x8000);
    r=select(is_subnorm, rsn, r);
#endif
#endif
    return r;
}

template <bool _FLUSH_SUBNORMALS_TO_ZERO, std::size_t _N>
cftal::vec<float, _N>
cftal::impl::_rz_f32_to_bf16(const vec<float, _N>& v)
{
    // do not zero the last 16 bits
    // auto vne=round_to_zero_last_bits<16>(v);
    auto vne = v;
    if constexpr (_FLUSH_SUBNORMALS_TO_ZERO==true) {
        using vf_type = vec<float, _N>;
        // flush subnormals to zero
        typename vf_type::mask_type is_subnorm=
            abs(v) < std::numeric_limits<float>::min();
        constexpr const float mz=-0.0f;
        vne = select(is_subnorm, vf_type(v & mz), vne);
    }
    return vne;
}

template <std::size_t _N>
cftal::vec<cftal::mf_bf16_t, _N>
cftal::impl::_cvt_f32_to_bf16_rz(const vec<float, _N>& v)
{
    constexpr bool ftz = __CFTAL_CFG_FLUSH_BFLOAT16_TO_ZERO > 0;
    auto vne = _rz_f32_to_bf16<ftz>(v);
    auto t=as<vec<cftal::mf_bf16_t, 2*_N> >(vne);
    auto r=odd_elements(t);
    return r;
}

template <std::size_t _N>
cftal::vec<float, _N>
cftal::impl::_cvt_bf16_to_f32(const vec<mf_bf16_t, _N>& v)
{
    auto v2=combine_zeroeven_odd(v);
    auto r=as<vec<float, _N> >(v2);
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::mf_bf16_t, _N>
cftal::cvt_f32_to_bf16(const vec<float, _N>& v)
{
    return vec<mf_bf16_t, _N>(cvt_f32_to_bf16(low_half(v)),
                              cvt_f32_to_bf16(high_half(v)));
}

inline
cftal::vec<cftal::mf_bf16_t, 1>
cftal::cvt_f32_to_bf16(const vec<float, 1>& v)
{
    return impl::_cvt_f32_to_bf16(v);
}

inline
cftal::vec<cftal::mf_bf16_t, 2>
cftal::cvt_f32_to_bf16(const vec<float, 2>& v)
{
    return impl::_cvt_f32_to_bf16(v);
}

inline
cftal::vec<cftal::mf_bf16_t, 4>
cftal::cvt_f32_to_bf16(const vec<float, 4>& v)
{
    return impl::_cvt_f32_to_bf16(v);
}

inline
cftal::vec<cftal::mf_bf16_t, 8>
cftal::cvt_f32_to_bf16(const vec<float, 8>& v)
{
    return impl::_cvt_f32_to_bf16(v);
}

inline
cftal::vec<cftal::mf_bf16_t, 16>
cftal::cvt_f32_to_bf16(const vec<float, 16>& v)
{
    return impl::_cvt_f32_to_bf16(v);
}

template <std::size_t _N>
inline
cftal::vec<cftal::mf_bf16_t, _N>
cftal::cvt_f32_to_bf16_rz(const vec<float, _N>& v)
{
    return vec<mf_bf16_t, _N>(cvt_f32_to_bf16_rz(low_half(v)),
                              cvt_f32_to_bf16_rz(high_half(v)));
}

inline
cftal::vec<cftal::mf_bf16_t, 1>
cftal::cvt_f32_to_bf16_rz(const vec<float, 1>& v)
{
    return impl::_cvt_f32_to_bf16_rz(v);
}

inline
cftal::vec<cftal::mf_bf16_t, 2>
cftal::cvt_f32_to_bf16_rz(const vec<float, 2>& v)
{
    return impl::_cvt_f32_to_bf16_rz(v);
}

inline
cftal::vec<cftal::mf_bf16_t, 4>
cftal::cvt_f32_to_bf16_rz(const vec<float, 4>& v)
{
    return impl::_cvt_f32_to_bf16_rz(v);
}

inline
cftal::vec<cftal::mf_bf16_t, 8>
cftal::cvt_f32_to_bf16_rz(const vec<float, 8>& v)
{
    return impl::_cvt_f32_to_bf16_rz(v);
}

inline
cftal::vec<cftal::mf_bf16_t, 16>
cftal::cvt_f32_to_bf16_rz(const vec<float, 16>& v)
{
    return impl::_cvt_f32_to_bf16_rz(v);
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::cvt_bf16_to_f32(const vec<mf_bf16_t, _N>& v)
{
    return vec<float, _N>(cvt_bf16_to_f32(low_half(v)),
                          cvt_bf16_to_f32(high_half(v)));
}

inline
cftal::vec<float, 1>
cftal::cvt_bf16_to_f32(const vec<mf_bf16_t, 1>& v)
{
    return impl::_cvt_bf16_to_f32(v);
}

inline
cftal::vec<float, 2>
cftal::cvt_bf16_to_f32(const vec<mf_bf16_t, 2>& v)
{
    return impl::_cvt_bf16_to_f32(v);
}

inline
cftal::vec<float, 4>
cftal::cvt_bf16_to_f32(const vec<mf_bf16_t, 4>& v)
{
    return impl::_cvt_bf16_to_f32(v);
}

inline
cftal::vec<float, 8>
cftal::cvt_bf16_to_f32(const vec<mf_bf16_t, 8>& v)
{
    return impl::_cvt_bf16_to_f32(v);
}

inline
cftal::vec<float, 16>
cftal::cvt_bf16_to_f32(const vec<mf_bf16_t, 16>& v)
{
    return impl::_cvt_bf16_to_f32(v);
}

// Local variables:
// mode: c++
// end:
#endif
