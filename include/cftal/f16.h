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
    vec<fp16_t, _N>
    cvt_f32_to_f16(const vec<f32_t, _N>& s);

    template <std::size_t _N>
    vec<f32_t, _N>
    cvt_f16_to_f32(const vec<f16_t, _N>& s);

}

// Local variables:
// mode: c++
// end:
#endif
