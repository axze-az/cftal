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
#if !defined (__CFTAL_BF16_H__)
#define __CFTAL_BF16_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/constants.h>
#include <cftal/vec.h>

namespace cftal {

    // memory format of bfloat16, aka. the highest 16 bits of a
    // binary32
    using mf_bf16_t = int16_t;

    namespace impl {

        // round f32 to bf16 using round to nearest even rounding
        template <std::size_t _N>
        vec<float, _N>
        _rne_f32_to_bf16(const vec<float, _N>& v);

        // convert  vec<f32, _N> to vec<mf_bf16_t, _N> using
        // round to nearest even rounding
        template <std::size_t _N>
        vec<mf_bf16_t, _N>
        _cvt_f32_to_bf16(const vec<float, _N>& v);

        // round f32 to bf16 using round to zero rounding
        template <std::size_t _N>
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

template <std::size_t _N>
cftal::vec<float, _N>
cftal::impl::_rne_f32_to_bf16(const vec<float, _N>& v)
{
    using vf_type = vec<float, _N>;
    vf_type vne=round_to_nearest_even_last_bits<16>(v);
    // infinities are not affected by rounding
    typename vf_type::mask_type is_nan=isnan(v);
    vne = select(is_nan, v, vne);
    return vne;
}

template <std::size_t _N>
cftal::vec<cftal::mf_bf16_t, _N>
cftal::impl::_cvt_f32_to_bf16(const vec<float, _N>& v)
{
    auto vne = _rne_f32_to_bf16(v);
    auto t=as<vec<cftal::mf_bf16_t, 2*_N> >(vne);
    auto r=odd_elements(t);
    return r;
}

template <std::size_t _N>
cftal::vec<float, _N>
cftal::impl::_rz_f32_to_bf16(const vec<float, _N>& v)
{
    // zero the last 16 bits
    auto vne=round_to_zero_last_bits<16>(v);
    return vne;
}

template <std::size_t _N>
cftal::vec<cftal::mf_bf16_t, _N>
cftal::impl::_cvt_f32_to_bf16_rz(const vec<float, _N>& v)
{
    // no masking of the trailing 16 bits is required
    auto t=as<vec<cftal::mf_bf16_t, 2*_N> >(v);
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
