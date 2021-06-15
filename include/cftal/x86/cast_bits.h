//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
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

    } // namespace impl
#endif // __SSE2__
} // namespace cftal


// Local variables:
// mode: c++
// end:
#endif
