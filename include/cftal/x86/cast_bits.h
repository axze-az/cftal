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
#if !defined (__CFTAL_X86_CAST_BITS_H__)
#define __CFTAL_X86_CAST_BITS_H__ 1

#include <cftal/config.h>
#include <cftal/as.h>
#if defined (__SSE2__)
#include <cftal/x86/intrin.h>
#endif

namespace cftal {

#if defined (__SSE2__)
    namespace impl {
        // cast to __m128
        template <>
        struct cast_bits<__m128, __m128d> {
            static __m128 v(const __m128d& r) {
                return _mm_castpd_ps(r);
            }
        };

        // cast to __m128
        template <>
        struct cast_bits<__m128, __m128i> {
            static __m128 v(const __m128i& r) {
                return _mm_castsi128_ps(r);
            }
        };

        // cast to __m128d
        template <>
        struct cast_bits<__m128d, __m128> {
            static __m128d v(const __m128& r) {
                return _mm_castps_pd(r);
            }
        };

        // cast to __m128d
        template <>
        struct cast_bits<__m128d, __m128i> {
            static __m128d v(const __m128i& r) {
                return _mm_castsi128_pd(r);
            }
        };


        // cast to __m128i
        template <>
        struct cast_bits<__m128i, __m128> {
            static __m128i v(const __m128& r) {
                return _mm_castps_si128(r);
            }
        };

        // cast to __m128i
        template <>
        struct cast_bits<__m128i, __m128d> {
            static __m128i v(const __m128d& r) {
                return _mm_castpd_si128(r);
            }
        };

#if defined __AVX__
        // cast to __m128d from __m256d
        template <>
        struct cast_bits<__m128d, __m256d> {
            static __m128d v(const __m256d& r) {
                return _mm256_castpd256_pd128(r);
            }
        };

        // cast to __m256d from __m128d
        template <>
        struct cast_bits<__m256d, __m128d> {
            static __m256d v(const __m128d& r) {
                return _mm256_castpd128_pd256(r);
            }
        };

        // cast to __m256d from __m256
        template <>
        struct cast_bits<__m256d, __m256> {
            static __m256d v(const __m256& r) {
                return _mm256_castps_pd(r);
            }
        };

        // cast to __m256d from __m256i
        template <>
        struct cast_bits<__m256d, __m256i> {
            static __m256d v(const __m256i& r) {
                return _mm256_castsi256_pd(r);
            }
        };

        // cast to __m128 from __m256
        template <>
        struct cast_bits<__m128, __m256> {
            static __m128 v(const __m256& r) {
                return _mm256_castps256_ps128(r);
            }
        };

        // cast to __m256 from __m128
        template <>
        struct cast_bits<__m256, __m128> {
            static __m256 v(const __m128& r) {
                return _mm256_castps128_ps256(r);
            }
        };

        // cast to __m256 from __m256d
        template <>
        struct cast_bits<__m256, __m256d> {
            static __m256 v(const __m256d& r) {
                return _mm256_castpd_ps(r);
            }
        };

        // cast to __m256 from __m256i
        template <>
        struct cast_bits<__m256, __m256i> {
            static __m256 v(const __m256i& r) {
                return _mm256_castsi256_ps(r);
            }
        };

        // cast to __m128i from __m256i
        template <>
        struct cast_bits<__m128i, __m256i> {
            static __m128i v(const __m256i& r) {
                return _mm256_castsi256_si128(r);
            }
        };

        // cast to __m256i from __m128i
        template <>
        struct cast_bits<__m256i, __m128i> {
            static __m256i v(const __m128i& r) {
                return _mm256_castsi128_si256(r);
            }
        };

        // cast to __m256i from __m256d
        template <>
        struct cast_bits<__m256i, __m256d> {
            static __m256i v(const __m256d& r) {
                return _mm256_castpd_si256(r);
            }
        };

        // cast to __m256i from __m256
        template <>
        struct cast_bits<__m256i, __m256> {
            static __m256i v(const __m256& r) {
                return _mm256_castps_si256(r);
            }
        };
#endif
#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
        // cast to __m128d from __m512d
        template <>
        struct cast_bits<__m128d, __m512d> {
            static __m128d v(const __m512d& r) {
                return _mm512_castpd512_pd128(r);
            }
        };

        // cast to __m512d from __m128d
        template <>
        struct cast_bits<__m512d, __m128d> {
            static __m512d v(const __m128d& r) {
                return _mm512_castpd128_pd512(r);
            }
        };

        // cast to __m256d from __m512d
        template <>
        struct cast_bits<__m256d, __m512d> {
            static __m256d v(const __m512d& r) {
                return _mm512_castpd512_pd256(r);
            }
        };

        // cast to __m512d from __m256d
        template <>
        struct cast_bits<__m512d, __m256d> {
            static __m512d v(const __m256d& r) {
                return _mm512_castpd256_pd512(r);
            }
        };


        // cast to __m128 from __m512
        template <>
        struct cast_bits<__m128, __m512> {
            static __m128 v(const __m512& r) {
                return _mm512_castps512_ps128(r);
            }
        };

        // cast to __m512 from __m128
        template <>
        struct cast_bits<__m512, __m128> {
            static __m512 v(const __m128& r) {
                return _mm512_castps128_ps512(r);
            }
        };

        // cast to __m256 from __m512
        template <>
        struct cast_bits<__m256, __m512> {
            static __m256 v(const __m512& r) {
                return _mm512_castps512_ps256(r);
            }
        };

        // cast to __m512 from __m256
        template <>
        struct cast_bits<__m512, __m256> {
            static __m512 v(const __m256& r) {
                return _mm512_castps256_ps512(r);
            }
        };

        // cast to __m128i from __m512i
        template <>
        struct cast_bits<__m128i, __m512i> {
            static __m128i v(const __m512i& r) {
                return _mm512_castsi512_si128(r);
            }
        };

        // cast to __m512i from __m128i
        template <>
        struct cast_bits<__m512i, __m128i> {
            static __m512i v(const __m128i& r) {
                return _mm512_castsi128_si512(r);
            }
        };

        // cast to __m256i from __m512i
        template <>
        struct cast_bits<__m256i, __m512i> {
            static __m256i v(const __m512i& r) {
                return _mm512_castsi512_si256(r);
            }
        };

        // cast to __m512i from __m256i
        template <>
        struct cast_bits<__m512i, __m256i> {
            static __m512i v(const __m256i& r) {
                return _mm512_castsi256_si512(r);
            }
        };

        // cast to __m512d from __m512
        template <>
        struct cast_bits<__m512d, __m512> {
            static __m512d v(const __m512& r) {
                return _mm512_castps_pd(r);
            }
        };

        // cast to __m512d from __m512i
        template <>
        struct cast_bits<__m512d, __m512i> {
            static __m512d v(const __m512i& r) {
                return _mm512_castsi512_pd(r);
            }
        };

        // cast to __m512i from __m512d
        template <>
        struct cast_bits<__m512i, __m512d> {
            static __m512i v(const __m512d& r) {
                return _mm512_castpd_si512(r);
            }
        };

        // cast to __m512i from __m512
        template <>
        struct cast_bits<__m512i, __m512> {
            static __m512i v(const __m512& r) {
                return _mm512_castps_si512(r);
            }
        };

        // cast to __m512 from __m512d
        template <>
        struct cast_bits<__m512, __m512d> {
            static __m512 v(const __m512d& r) {
                return _mm512_castpd_ps(r);
            }
        };

        // cast to __m512 from __m512i
        template <>
        struct cast_bits<__m512, __m512i> {
            static __m512 v(const __m512i& r) {
                return _mm512_castsi512_ps(r);
            }
        };

#endif
    } // namespace impl
#endif // __SSE2__
} // namespace cftal

// Local variables:
// mode: c++
// end:
#endif
