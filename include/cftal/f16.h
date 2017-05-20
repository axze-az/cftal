//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_F16_H__)
#define __CFTAL_F16_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/constants.h>
#include <cftal/vec.h>


namespace cftal {

    // a 16 bit floating point number used as storage format
    class f16_t {
    public:
        constexpr explicit f16_t(uint16_t f) : _f(f) {}
        constexpr uint16_t v() const { return _f; }
    private:
        uint16_t _f;
    };

    // conversion of a f32 to a f16 value
    f16_t
    cvt_f32_to_f16(f32_t f);
    // conversion of a f16 value to a f16 value
    f32_t
    cvt_f16_to_f32(f16_t f);

    template <std::size_t _N>
    vec<f16_t, _N>
    cvt_f32_to_f16(const vec<f32_t, _N>& s);

    template <std::size_t _N>
    vec<f32_t, _N>
    cvt_f16_to_f32(const vec<f16_t, _N>& s);
}

inline
cftal::f32_t
cftal::cvt_f16_to_f32(f16_t t)
{
    uint32_t tt= t.v();
    const uint32_t exp_msk = 0x7c00 << 13;
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

inline
cftal::f16_t
cftal::cvt_f32_to_f16(f32_t ff)
{
    const f32_t inf= std::numeric_limits<float>::infinity();
    const uint32_t inf_u= as<uint32_t>(inf);
    const uint32_t max_f16_u = (127+16)<<23;
    const f32_t denom_magic= 0.5f;

    const uint32_t sgn_msk = 0x80000000u;

    uint32_t f=as<uint32_t>(ff);
    uint32_t s=(f & sgn_msk);
    f ^= s;
    s >>= 16;
    if (f >= max_f16_u) {
        f = f > inf_u ?
            0x7e00 | ((f & 0x7fffff)>>13) : 0x7c00;
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
    return f16_t(f|s);
}


template <std::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::cvt_f32_to_f16(const vec<f32_t, _N>& ff)
{
    using f32vec = vec<f32_t, _N>;
    using u32vec = vec<int32_t, _N>;

    const f32vec inf=std::numeric_limits<float>::infinity();
    const u32vec inf_u= as<u32vec>(inf);
    const u32vec max_f16_u= (bias_f32+16) << exp_shift_f32;
    const f32vec denom_magic=0.5f;
    const u32vec denom_magic_u=as<u32vec>(denom_magic);
    
    u32vec f= as<u32vec>(ff);
    u32vec s= f & u32vec(sign_f32_msk::v.u32());
    f ^= s;
    // the signed shift does not matter because we truncate
    // the 16 higher bits anyway
    s >>= 16;

    // inf or nan handling
    auto inf_or_nan = f >= max_f16_u;
    u32vec r_nan = u32vec(0x7e00) | ((f & sig_f32_msk::v.u32()) >> 13);
    u32vec r_inf = u32vec(0x7c00);
    u32vec r_inf_nan = select(f > inf_u, r_nan, r_inf);
    // denormal handling
    auto denom= f < u32vec(113<<23);
    u32vec r_denom= as<u32vec>(as<f32vec>(f) + denom_magic);
    r_denom -= denom_magic_u;
    // normal numbers
    u32vec mant_odd= (f>>13) & 1;
    f += u32vec((uint32_t(15-bias_f32)<<13) +  0xfff);
    f += mant_odd;
    f >>= 13;
    // produce result
    u32vec r = select(denom, r_denom, f);
    r = select(inf_or_nan, r_inf_nan, r);
    r |= s;

    using u16vec2 = cftal::vec<uint16_t, 2*_N>;
    auto t=as<u16vec2>(r);
    auto rr=even_elements(t);
    return rr;
}

template <std::size_t _N>
cftal::vec<cftal::f32_t, _N>
cftal::cvt_f16_to_f32(const vec<f16_t, _N>& ff)
{
    using u32vec = vec<uint32_t, _N>;
    using u16vec = vec<uint16_t, _N>;
    using f32vec = vec<f32_t, _N>;
    u16vec ffu16=as<u16vec>(ff);
    u16vec z=0;
    u32vec tt=as<u32vec>(combine_even_odd(ffu16, z));
    
    const u32vec exp_msk = 0x7c00 << 13;
    u32vec r= (tt & 0x7fff) << 13;
    u32vec s= (tt & 0x8000) << 16;
    u32vec e= exp_msk & r;
    r += (127-15) << 23; // adust the exponent

    u32vec r_inf_nan= r + ((128-16) << 23);

    u32vec r_denom = r + (1<<23);
    const f32vec magic=as<f32_t>(113<<23);
    r_denom = as<u32vec>(as<f32vec>(r_denom) - magic);

    r = select(e== exp_msk, r_inf_nan, r);
    r = select(e== 0, r_denom, r);
    r |= s;
    return as<f32vec>(r);
}
    
// Local variables:
// mode: c++
// end:
#endif
