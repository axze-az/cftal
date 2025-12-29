//
// Copyright (C) 2010-2026 Axel Zeuner
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
#if !defined (__CFTAL_CVT_BF16_H__)
#define __CFTAL_CVT_BF16_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/as.h>

namespace cftal {

    // memory format for IEEE bf16_t types
    using mf_bf16_t = int16_t;

    // conversion of a f32 to a bf16 value
    mf_bf16_t
    cvt_f32_to_bf16(f32_t f);
    // conversion of a bf16 value to a f32 value
    f32_t
    cvt_bf16_to_f32(mf_bf16_t f);

    namespace impl {

#if __cpp_lib_bit_cast>0
        constexpr
#endif
        f32_t
        _cvt_bf16_to_f32(mf_bf16_t f);

#if __cpp_lib_bit_cast>0
        constexpr
#endif
        mf_bf16_t
        _cvt_f32_to_bf16(f32_t f);


    }
}

#if __cpp_lib_bit_cast>0
constexpr
#endif
inline
cftal::f32_t
cftal::impl::_cvt_bf16_to_f32(mf_bf16_t t)
{
    int32_t r=t;
    r <<= 16;
    return as<f32_t>(r);
}

#if __cpp_lib_bit_cast>0
constexpr
#endif
inline
cftal::mf_bf16_t
cftal::impl::_cvt_f32_to_bf16(f32_t ff)
{
    int32_t f=as<int32_t>(ff);
    int32_t af=f & 0x7fff'ffff;
    int32_t sf=f & 0x8000'0000;
#define BRANCHLESS 1

#if BRANCHLESS
    // nan result;
    int32_t r_nan = af;
    constexpr const int32_t rnd_bias = 0x7fff;
    constexpr const int32_t rnd_bias_p1 = 0x8000;
    // force round nearest even if bit 16 is set
    int32_t r_def= (af & 0x0001'0000) ? af + rnd_bias_p1 : af + rnd_bias;
#if __CFTAL_CFG_FLUSH_BFLOAT16_TO_ZERO > 0
    // subnormal result:
    int32_t r_sn = 0;
    // select subnormal normal
    int32_t r_def_sn = (af < 0x0080'0000) ? r_sn : r_def;
#else
    const int32_t r_def_sn = r_def;
#endif
    // select nan or subnormal normal
    int32_t r = (af > 0x7f80'0000) ? r_nan : r_def_sn;
#else
    int32_t r;
    if (af > 0x7f80'0000) {
        // nan
        r = af;
#if __CFTAL_CFG_FLUSH_BFLOAT16_TO_ZERO > 0
    } else if (af < 0x0080'0000) {
        // subnormal or 0
        r = 0;
#endif
    } else {
        constexpr const int32_t rnd_bias = 0x7fff;
        constexpr const int32_t rnd_bias_p1 = 0x8000;
        // one could also use a shift here
        if (af & 0x0001'0000) {
            // force round nearest even
            r = af + rnd_bias_p1;
        } else {
            r = af + rnd_bias;
        }
    }
#endif
#undef BRANCHLESS
    r |= sf;
    r >>= 16;
    return mf_bf16_t(r);
}

inline
cftal::f32_t
cftal::cvt_bf16_to_f32(mf_bf16_t t)
{
    return impl::_cvt_bf16_to_f32(t);
}

inline
cftal::mf_bf16_t
cftal::cvt_f32_to_bf16(f32_t ff)
{
    return impl::_cvt_f32_to_bf16(ff);
}

// Local variables:
// mode: c++
// end:
#endif
