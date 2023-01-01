//
// Copyright (C) 2010-2023 Axel Zeuner
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
#if !defined (__CFTAL_VEC_CAST_BITS_H__)
#define __CFTAL_VEC_CAST_BITS_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
// <cftal/as.h> is included by:
#include <cftal/x86/cast_bits.h>

namespace cftal {

    namespace impl {
#if defined (__SSE2__)

        template <>
        struct cast_bits<v2f64, v4s32> {
            static
            v2f64 v(const v4s32& s) {
                return v2f64(cast_bits<__m128d, __m128i>::v(s()));
            }
        };

        template <>
        struct cast_bits<v2f64, v4u32> {
            static
            v2f64 v(const v4s32& s) {
                return v2f64(cast_bits<__m128d, __m128i>::v(s()));
            }
        };
#endif
#if defined (__AVX__)
#if !defined (__AVX2__)
        template <>
        struct cast_bits<v4f64, v8s32> {
            static
            v4f64 v(const v8s32& s) {
                return v4f64(cast_bits<v2f64, v4s32>::v(low_half(s)),
                             cast_bits<v2f64, v4s32>::v(high_half(s)));
            }
        };

        template <>
        struct cast_bits<v4f64, v8u32> {
            static
            v4f64 v(const v8u32& s) {
                return v4f64(cast_bits<v2f64, v4u32>::v(low_half(s)),
                             cast_bits<v2f64, v4u32>::v(high_half(s)));
            }
        };
#else
        template <>
        struct cast_bits<v4f64, v8s32> {
            static
            v4f64 v(const v8s32& s) {
                return v4f64(cast_bits<__m256d, __m256i>::v(s()));
            }
        };

        template <>
        struct cast_bits<v4f64, v8u32> {
            static
            v4f64 v(const v8s32& s) {
                return v4f64(cast_bits<__m256d, __m256i>::v(s()));
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
