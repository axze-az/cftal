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
#if !defined (__CFTAL_CVT_F16_H__)
#define __CFTAL_CVT_F16_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/constants.h>
#include <cftal/as.h>
#include <limits>

namespace cftal {

    // memory format for IEEE f16_t types
    using mf_f16_t = int16_t;

    constexpr
    inline
    int16_t read_bits(mf_f16_t v) {
        return v;
    }

    // conversion of a f32 to a f16 value
    mf_f16_t
    cvt_f32_to_f16(f32_t f);
    // conversion of a f16 value to a f32 value
    f32_t
    cvt_f16_to_f32(mf_f16_t f);

    namespace impl {

        constexpr
        mf_f16_t
        _cvt_f32_to_f16(f32_t f);

        constexpr
        f32_t
        _cvt_f16_to_f32(mf_f16_t f);

    }
}

#if __cpp_lib_bit_cast>0
constexpr
#endif
inline
cftal::f32_t
cftal::impl::_cvt_f16_to_f32(mf_f16_t t)
{
    const uint32_t tt= read_bits(t);
    constexpr const uint32_t exp_msk = 0x7c00 << 13;
    uint32_t r= (tt & 0x7fff) << 13;
    uint32_t s= (tt & 0x8000) << 16;
    uint32_t e= exp_msk & r;
    r += (127-15) << 23; // adust the exponent
    if (e == exp_msk) {
        // maximum exponent? inf/NaNs
        r += (128-16) << 23;
    } else if (e == 0) {
        // denormal numbers
        const f32_t magic = as<f32_t>(113 << 23);
        r += 1<<23;
        r = as<uint32_t>(as<f32_t>(r) - magic);
    }
    r |= s;
    return as<f32_t>(r);
}

#if __cpp_lib_bit_cast>0
constexpr
#endif
inline
cftal::mf_f16_t
cftal::impl::_cvt_f32_to_f16(f32_t ff)
{
    // const f32_t inf= std::numeric_limits<float>::infinity();
    // const uint32_t inf_u= as<uint32_t>(inf);
    constexpr const uint32_t inf_u=  exp_f32_msk::v.u32();
    constexpr const uint32_t max_f16_u = (127+16)<<23;
    constexpr const f32_t denom_magic= 0.5f;

    constexpr const uint32_t sgn_msk = 0x80000000u;

    uint32_t f=as<uint32_t>(ff);
    uint32_t s=(f & sgn_msk);
    f ^= s;
    s >>= 16;
    if (f >= max_f16_u) {
        f = f > inf_u ?
            0x7e00 /*| ((f & 0x7fffff)>>13)*/ : 0x7c00;
    } else {
        if (f < (113<<23)) {
            f = as<uint32_t>(as<f32_t>(f) + denom_magic);
            f = f - as<uint32_t>(denom_magic);
        } else {
            uint32_t mant_odd= (f>>13) & 1;
            f += (uint32_t(15-127)<<23)+ 0xfff;
            f += mant_odd;
            f >>=13;
        }
    }
    return mf_f16_t(f|s);
}


inline
cftal::f32_t
cftal::cvt_f16_to_f32(mf_f16_t t)
{
#if defined (__F16C__)
    return _cvtsh_ss(read_bits(t));
#else
    return impl::_cvt_f16_to_f32(t);
#endif
}

inline
cftal::mf_f16_t
cftal::cvt_f32_to_f16(f32_t ff)
{
#if defined (__F16C__)
    return mf_f16_t(_cvtss_sh(ff, 0));
#else
    return impl::_cvt_f32_to_f16(ff);
#endif
}

// Local variables:
// mode: c++
// end:
#endif
