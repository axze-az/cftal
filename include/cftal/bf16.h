//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
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
    using mf_bf16_t = uint16_t;

    namespace impl {

        template <std::size_t _N>
        vec<mf_bf16_t, _N>
        _cvt_f32_to_bf16(const vec<float, _N>& v);

        template <std::size_t _N>
        vec<mf_bf16_t, _N>
        _cvt_f32_to_bf16_rz(const vec<float, _N>& v);

        template <std::size_t _N>
        vec<float, _N>
        _cvt_bf16_to_f32(const vec<mf_bf16_t, _N>& v);

    }

    // template for conversion
    template <std::size_t _N>
    vec<mf_bf16_t, _N>
    cvt_f32_to_bf16(const vec<float, _N>& v);

    vec<mf_bf16_t, 1>
    cvt_f32_to_bf16(const vec<float, 1>& v);

    vec<mf_bf16_t, 2>
    cvt_f32_to_bf16(const vec<float, 2>& v);

    vec<mf_bf16_t, 4>
    cvt_f32_to_bf16(const vec<float, 4>& v);

    vec<mf_bf16_t, 8>
    cvt_f32_to_bf16(const vec<float, 8>& v);

    // template for conversion
    template <std::size_t _N>
    vec<mf_bf16_t, _N>
    cvt_f32_to_bf16_rz(const vec<float, _N>& v);

    vec<mf_bf16_t, 1>
    cvt_f32_to_bf16_rz(const vec<float, 1>& v);

    vec<mf_bf16_t, 2>
    cvt_f32_to_bf16_rz(const vec<float, 2>& v);

    vec<mf_bf16_t, 4>
    cvt_f32_to_bf16_rz(const vec<float, 4>& v);

    vec<mf_bf16_t, 8>
    cvt_f32_to_bf16_rz(const vec<float, 8>& v);

    // template for conversion
    template <std::size_t _N>
    vec<float, _N>
    cvt_bf16_to_f32(const vec<mf_bf16_t, _N>& v);

    vec<float, 1>
    cvt_bf16_to_f32(const vec<mf_bf16_t, 1>& v);

    vec<float, 2>
    cvt_bf16_to_f32(const vec<mf_bf16_t, 2>& v);

    vec<float, 4>
    cvt_bf16_to_f32(const vec<mf_bf16_t, 4>& v);

    vec<float, 8>
    cvt_bf16_to_f32(const vec<mf_bf16_t, 8>& v);

}

template <std::size_t _N>
cftal::vec<cftal::mf_bf16_t, _N>
cftal::impl::_cvt_f32_to_bf16(const vec<float, _N>& v)
{
    using vi2_type= vec<int32_t, _N>;
    using vmi2_type = typename vec<int32_t, _N>::mask_type;

    vi2_type i= as<vi2_type>(v);
    // normal case: round the mantissa only
    const int32_t bias=0x7fff;
    vi2_type mt_odd= (i>>16) & 1;
    vi2_type in =  i + (mt_odd + bias);
    // keep nans
    auto is_nan= isnan(v);
    in = select(as<vmi2_type>(is_nan), i, in);

    auto t=as<vec<cftal::mf_bf16_t, 2*_N> >(in);
    auto r=odd_elements(t);
    return r;
}

template <std::size_t _N>
cftal::vec<cftal::mf_bf16_t, _N>
cftal::impl::_cvt_f32_to_bf16_rz(const vec<float, _N>& v)
{
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

// Local variables:
// mode: c++
// end:
#endif
