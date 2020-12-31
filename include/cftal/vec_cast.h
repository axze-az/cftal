//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_VEC_CAST_H__)
#define __CFTAL_VEC_CAST_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/x86/cast.h>

namespace cftal {

    namespace impl {
#if defined (__SSE2__)

        template <>
        struct cast<v2f64, v4s32> {
            static
            v2f64 v(const v4s32& s) {
                return v2f64(cast<__m128d, __m128i>::v(s()));
            }
        };

        template <>
        struct cast<v2f64, v4u32> {
            static
            v2f64 v(const v4s32& s) {
                return v2f64(cast<__m128d, __m128i>::v(s()));
            }
        };
#endif
#if defined (__AVX__)
#if !defined (__AVX2__)
        template <>
        struct cast<v4f64, v8s32> {
            static
            v4f64 v(const v8s32& s) {
                return v4f64(cast<v2f64, v4s32>::v(low_half(s)),
                             cast<v2f64, v4s32>::v(high_half(s)));
            }
        };

        template <>
        struct cast<v4f64, v8u32> {
            static
            v4f64 v(const v8u32& s) {
                return v4f64(cast<v2f64, v4u32>::v(low_half(s)),
                             cast<v2f64, v4u32>::v(high_half(s)));
            }
        };
#else
        template <>
        struct cast<v4f64, v8s32> {
            static
            v4f64 v(const v8s32& s) {
                return v4f64(cast<__m256d, __m256i>::v(s()));
            }
        };

        template <>
        struct cast<v4f64, v8u32> {
            static
            v4f64 v(const v8s32& s) {
                return v4f64(cast<__m256d, __m256i>::v(s()));
            }
        };

#endif
#endif
    }

}


// Local variables:
// mode: c++
// end:
#endif
