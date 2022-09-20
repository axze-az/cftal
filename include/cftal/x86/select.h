//
// Copyright (C) 2010-2022 Axel Zeuner
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
#if !defined (__CFTAL_X86_SELECT_H__)
#define __CFTAL_X86_SELECT_H__ 1

#include <cftal/config.h>
#include <cftal/x86/intrin.h>
#include <cftal/x86/const.h>

namespace cftal {

    namespace x86 {

        // select bitwise
        uint32_t select(uint32_t msk, uint32_t on_one, uint32_t on_zero);
        // select bitwise
        uint64_t select(uint64_t msk, uint64_t on_one, uint64_t on_zero);
        // select bytes
        // __SSE2__: bitwise
        // __SSE4_1__: on sign bit of int8_t
        // r[i] = msk[i] ? one[i] : zero
        __m128i select_u8(__m128i msk, __m128i on_one, __m128i on_zero);
        __m128i select_u16(__m128i msk, __m128i on_one, __m128i on_zero);
        __m128i select_u32(__m128i msk, __m128i on_one, __m128i on_zero);
        __m128i select_u64(__m128i msk, __m128i on_one, __m128i on_zero);

        // select floats
        // __SSE2__: bitwise
        // __SSE4_1__: on sign bit of float
        __m128 select_f32(__m128 msk, __m128 on_one, __m128 on_zero);

        // select doubles
        // __SSE2__: bitwise
        // __SSE4_1__: on sign bit of double
        __m128d select_f64(__m128d msk, __m128d on_one, __m128d on_zero);

#if defined (__AVX__)
        // select floats
        // on sign bit of float
        __m256 select_f32(__m256 msk, __m256 on_one, __m256 on_zero);
        // select on doubles
        // on sign bit of double
        __m256d select_f64(__m256d msk, __m256d on_one, __m256d on_zero);
#endif
#if defined (__AVX2__)
        // select bytes
        // on sign bit of int8_t
        // r[i] = msk[i] ? one[i] : zero
        __m256i select_u8(__m256i msk, __m256i on_one, __m256i on_zero);
        __m256i select_u16(__m256i msk, __m256i on_one, __m256i on_zero);
        __m256i select_u32(__m256i msk, __m256i on_one, __m256i on_zero);
        __m256i select_u64(__m256i msk, __m256i on_one, __m256i on_zero);
#endif
#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
        __m512d select_f64(__mmask8 msk, __m512d on_one, __m512d on_zero);
        __m512 select_f32(__mmask16 msk, __m512 on_one, __m512 on_zero);
        __m512i select_u64(__mmask8 msk, __m512i on_one, __m512i on_zero);
        __m512i select_u32(__mmask16 msk, __m512i on_one, __m512i on_zero);
#endif
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
        __m128d select_f64(__mmask8 msk, __m128d on_one, __m128d on_zero);
        __m256d select_f64(__mmask8 msk, __m256d on_one, __m256d on_zero);

        __m128 select_f32(__mmask8 msk, __m128 on_one, __m128 on_zero);
        __m256 select_f32(__mmask8 msk, __m256 on_one, __m256 on_zero);

        __m128i select_u64(__mmask8 msk, __m128i on_one, __m128i on_zero);
        __m256i select_u64(__mmask8 msk, __m256i on_one, __m256i on_zero);

        __m128i select_u32(__mmask8 msk, __m128i on_one, __m128i on_zero);
        __m256i select_u32(__mmask8 msk, __m256i on_one, __m256i on_zero);

        __m128i select_u8(__mmask16 msk, __m128i on_one, __m128i on_zero);
        __m256i select_u8(__mmask32 msk, __m256i on_one, __m256i on_zero);
        __m512i select_u8(__mmask64 msk, __m512i on_one, __m512i on_zero);

        __m128i select_u16(__mmask8 msk, __m128i on_one, __m128i on_zero);
        __m256i select_u16(__mmask16 msk, __m256i on_one, __m256i on_zero);
        __m512i select_u16(__mmask32 msk, __m512i on_one, __m512i on_zero);
#endif

        // helper for selecting first or second arg
        template <typename _T>
        struct select_arg_1 {
            static _T v(_T a);
            static _T v(_T a, _T b);
        };

        template <typename _T>
        struct select_arg_2 {
            static _T v(_T a, _T b);
        };

        // general case double
        template <bool _P0, bool _P1>
        struct select_v2f64 {
            static __m128d v(__m128d a, __m128d b);
        };
        // double specialisations
        template <>
        struct select_v2f64<0,0> : public select_arg_2<__m128d> {
        };
        template <>
        struct select_v2f64<1,1> : public select_arg_1<__m128d> {
        };

        // general case float
        template <bool _P0, bool _P1, bool _P2, bool _P3>
        struct select_v4f32 {
            static __m128 v(__m128 a, __m128 b);
        };
        // float specialisations
        template <>
        struct select_v4f32<0,0,0,0> : public select_arg_2<__m128> {
        };
        template <>
        struct select_v4f32<1,1,1,1> : public select_arg_1<__m128> {
        };

        // general case u64, implementation on top of u16
        // therefore no additional specializations
        template <bool _P0, bool _P1>
        struct select_v2u64 {
            static __m128i v(__m128i a, __m128i b);
        };

        // general case u32, implementation on top of u16
        // therefore no additional specializations
        template <bool _P0, bool _P1, bool _P2, bool _P3>
        struct select_v4u32 {
            static __m128i v(__m128i a, __m128i b);
        };

        // general case u16
        template <bool _P0, bool _P1, bool _P2, bool _P3,
                  bool _P4, bool _P5, bool _P6, bool _P7>
        struct select_v8u16 {
            static __m128i v(__m128i a, __m128i b);
        };
        // u16 specialisations
        template <>
        struct select_v8u16<0,0,0,0,0,0,0,0> :
            public select_arg_2<__m128i> {
        };
        template <>
        struct select_v8u16<1,1,1,1,1,1,1,1> :
            public select_arg_1<__m128i> {
        };

        // general case u8
        template <bool _P00, bool _P01, bool _P02, bool _P03,
                  bool _P04, bool _P05, bool _P06, bool _P07,
                  bool _P08, bool _P09, bool _P10, bool _P11,
                  bool _P12, bool _P13, bool _P14, bool _P15>
        struct select_v16u8 {
            static __m128i v(__m128i a, __m128i b);
        };
        // u8 specialisations
        template <>
        struct select_v16u8<0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0>
            : public select_arg_2<__m128i> {
        };
        template <>
        struct select_v16u8<1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1>
            : public select_arg_1<__m128i> {
        };


#if defined (__AVX__)
        // select v4f64
        template <bool _P0, bool _P1,
                  bool _P2, bool _P3>
        struct select_v4f64 {
            static __m256d v(__m256d a, __m256d b);
        };
        // v4f64 specialisations
        template <>
        struct select_v4f64<0,0,0,0> :
            public select_arg_2<__m256d> {
        };
        template <>
        struct select_v4f64<1,1,1,1> :
            public select_arg_1<__m256d> {
        };

        // select v8f32
        template <bool _P0, bool _P1, bool _P2, bool _P3,
                  bool _P4, bool _P5, bool _P6, bool _P7>
        struct select_v8f32 {
            static __m256 v(__m256 a, __m256 b);
        };
        // v8f32 specialisations
        template <>
        struct select_v8f32<0,0,0,0,0,0,0,0> :
            public select_arg_2<__m256> {
        };
        template <>
        struct select_v8f32<1,1,1,1,1,1,1,1> :
            public select_arg_1<__m256> {
        };
#endif
#if defined (__AVX2__)
        // generic case v4u64
        template <bool _P0, bool _P1, bool _P2, bool _P3>
        struct select_v4u64 {
            static __m256i v(__m256i a, __m256i b);
        };
        // v4u64 specializations
        template <>
        struct select_v4u64<0,0,0,0> :
            public select_arg_2<__m256i> {
        };
        template <>
        struct select_v4u64<1,1,1,1> :
            public select_arg_1<__m256i> {
        };

        // generic case v8u32
        template <bool _P0, bool _P1, bool _P2, bool _P3,
                  bool _P4, bool _P5, bool _P6, bool _P7>
        struct select_v8u32 {
            static __m256i v(__m256i a, __m256i b);
        };
        // v8u32 specializations
        template <>
        struct select_v8u32<0,0,0,0,0,0,0,0> :
            public select_arg_2<__m256i> {
        };
        template <>
        struct select_v8u32<1,1,1,1,1,1,1,1> :
            public select_arg_1<__m256i> {
        };

        // generic case v16u16
        template <bool _P00, bool _P01, bool _P02, bool _P03,
                  bool _P04, bool _P05, bool _P06, bool _P07,
                  bool _P08, bool _P09, bool _P10, bool _P11,
                  bool _P12, bool _P13, bool _P14, bool _P15>
        struct select_v16u16 {
            static __m256i v(__m256i a, __m256i b);
        };
        // v8u32 specializations
        template <>
        struct select_v16u16<0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0> :
            public select_arg_2<__m256i> {
        };
        template <>
        struct select_v16u16<1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1> :
            public select_arg_1<__m256i> {
        };

        // generic case v32u8
        template <bool _P00, bool _P01, bool _P02, bool _P03,
                  bool _P04, bool _P05, bool _P06, bool _P07,
                  bool _P08, bool _P09, bool _P10, bool _P11,
                  bool _P12, bool _P13, bool _P14, bool _P15,
                  bool _P16, bool _P17, bool _P18, bool _P19,
                  bool _P20, bool _P21, bool _P22, bool _P23,
                  bool _P24, bool _P25, bool _P26, bool _P27,
                  bool _P28, bool _P29, bool _P30, bool _P31>
        struct select_v32u8 {
            static __m256i v(__m256i a, __m256i b);
        };
        // v32u8s
        template <>
        struct select_v32u8<0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0> :
            public select_arg_2<__m256i> {
        };
        template <>
        struct select_v32u8<1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1> :
            public select_arg_1<__m256i> {
        };
#endif
#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)

        // general case f64
        template <bool _P0, bool _P1, bool _P2, bool _P3,
                  bool _P4, bool _P5, bool _P6, bool _P7>
        struct select_v8f64 {
            static __m512d v(__m512d a, __m512d b);
        };
        // f64 specializations
        template <>
        struct select_v8f64<0,0,0,0,0,0,0,0> :
            public select_arg_2<__m512d> {
        };
        template <>
        struct select_v8f64<1,1,1,1,1,1,1,1> :
            public select_arg_1<__m512d> {
        };

        // general case f32
        template <bool _P00, bool _P01, bool _P02, bool _P03,
                  bool _P04, bool _P05, bool _P06, bool _P07,
                  bool _P08, bool _P09, bool _P10, bool _P11,
                  bool _P12, bool _P13, bool _P14, bool _P15>
        struct select_v16f32 {
            static __m512 v(__m512 a, __m512 b);
        };
        // f32 specializations
        template <>
        struct select_v16f32<0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0>
            : public select_arg_2<__m512> {
        };
        template <>
        struct select_v16f32<1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1>
            : public select_arg_1<__m512> {
        };

        // general case u64
        template <bool _P0, bool _P1, bool _P2, bool _P3,
                  bool _P4, bool _P5, bool _P6, bool _P7>
        struct select_v8u64 {
            static __m512i v(__m512i a, __m512i b);
        };
        // u64 specialisations
        template <>
        struct select_v8u64<0,0,0,0,0,0,0,0> :
            public select_arg_2<__m512i> {
        };
        template <>
        struct select_v8u64<1,1,1,1,1,1,1,1> :
            public select_arg_1<__m512i> {
        };

        // general case u32
        template <bool _P00, bool _P01, bool _P02, bool _P03,
                  bool _P04, bool _P05, bool _P06, bool _P07,
                  bool _P08, bool _P09, bool _P10, bool _P11,
                  bool _P12, bool _P13, bool _P14, bool _P15>
        struct select_v16u32 {
            static __m512i v(__m512i a, __m512i b);
        };
        // u32 specializations
        template <>
        struct select_v16u32<0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0>
            : public select_arg_2<__m512i> {
        };
        template <>
        struct select_v16u32<1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1>
            : public select_arg_1<__m512i> {
        };

#endif
        // ---------------------------------------------------------
        // function definitions for select

        template <bool _P0, bool _P1>
        __m128d select_f64(__m128d a, __m128d b);

        template <bool _P0, bool _P1, bool _P2, bool _P3>
        __m128 select_f32(__m128 a, __m128 b);

        template <bool _P00, bool _P01, bool _P02, bool _P03,
                  bool _P04, bool _P05, bool _P06, bool _P07,
                  bool _P08, bool _P09, bool _P10, bool _P11,
                  bool _P12, bool _P13, bool _P14, bool _P15>
        __m128i select_u8(__m128i a, __m128i b);

        template <bool _P0, bool _P1, bool _P2, bool _P3,
                  bool _P4, bool _P5, bool _P6, bool _P7>
        __m128i select_u16(__m128i a, __m128i b);

        template <bool _P0, bool _P1, bool _P2, bool _P3>
        __m128i select_u32(__m128i a, __m128i b);

        template <bool _P0, bool _P1>
        __m128i select_u64(__m128i a, __m128i b);

#if defined (__AVX__)
        template <bool _P0, bool _P1, bool _P2, bool _P3>
        __m256d select_f64(__m256d a, __m256d b);

        template <bool _P0, bool _P1, bool _P2, bool _P3,
                  bool _P4, bool _P5, bool _P6, bool _P7>
        __m256 select_f32(__m256 a, __m256 b);
#endif
#if defined (__AVX2__)
        template <bool _P0, bool _P1, bool _P2, bool _P3>
        __m256i select_u64(__m256i a, __m256i b);

        template <bool _P0, bool _P1, bool _P2, bool _P3,
                  bool _P4, bool _P5, bool _P6, bool _P7>
        __m256i select_u32(__m256i a, __m256i b);

        template <bool _P00, bool _P01, bool _P02, bool _P03,
                  bool _P04, bool _P05, bool _P06, bool _P07,
                  bool _P08, bool _P09, bool _P10, bool _P11,
                  bool _P12, bool _P13, bool _P14, bool _P15>
        __m256i select_u16(__m256i a, __m256i b);

        template <bool _P00, bool _P01, bool _P02, bool _P03,
                  bool _P04, bool _P05, bool _P06, bool _P07,
                  bool _P08, bool _P09, bool _P10, bool _P11,
                  bool _P12, bool _P13, bool _P14, bool _P15,
                  bool _P16, bool _P17, bool _P18, bool _P19,
                  bool _P20, bool _P21, bool _P22, bool _P23,
                  bool _P24, bool _P25, bool _P26, bool _P27,
                  bool _P28, bool _P29, bool _P30, bool _P31>
        __m256i select_u8(__m256i a, __m256i b);
#endif

#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)

        template <bool _P0, bool _P1, bool _P2, bool _P3,
                  bool _P4, bool _P5, bool _P6, bool _P7>
        __m512d select_f64(__m512d a, __m512d b);

        template <bool _P00, bool _P01, bool _P02, bool _P03,
                  bool _P04, bool _P05, bool _P06, bool _P07,
                  bool _P08, bool _P09, bool _P10, bool _P11,
                  bool _P12, bool _P13, bool _P14, bool _P15>
        __m512 select_f32(__m512 a, __m512 b);

        template <bool _P0, bool _P1, bool _P2, bool _P3,
                  bool _P4, bool _P5, bool _P6, bool _P7>
        __m512i select_u64(__m512d a, __m512d b);

        template <bool _P00, bool _P01, bool _P02, bool _P03,
                  bool _P04, bool _P05, bool _P06, bool _P07,
                  bool _P08, bool _P09, bool _P10, bool _P11,
                  bool _P12, bool _P13, bool _P14, bool _P15>
        __m512i select_u32(__m512i a, __m512i b);

#endif
    }
}

inline
uint32_t
cftal::x86::select(uint32_t msk, uint32_t on_one, uint32_t on_zero)
{
    // return (msk & on_one) | ((~msk) & on_zero);
    return ((on_zero ^ on_one) & msk) ^ on_one;
}

inline
uint64_t
cftal::x86::select(uint64_t msk, uint64_t on_one, uint64_t on_zero)
{
    // return (msk & on_one) | ((~msk) & on_zero);
    return ((on_zero ^ on_one) & msk) ^ on_one;
}

inline
__m128i
cftal::x86::select_u8(__m128i msk, __m128i on_one, __m128i on_zero)
{
#if defined (__SSE4_1__)
    return _mm_blendv_epi8 (on_zero, on_one, msk);
#else
    return _mm_or_si128(_mm_and_si128(msk, on_one),
                        _mm_andnot_si128(msk, on_zero));
#endif
}

inline
__m128i
cftal::x86::select_u16(__m128i msk, __m128i on_one, __m128i on_zero)
{
    return select_u8(msk, on_one, on_zero);
}

inline
__m128i
cftal::x86::select_u32(__m128i msk, __m128i on_one, __m128i on_zero)
{
    return select_u8(msk, on_one, on_zero);
}

inline
__m128i
cftal::x86::select_u64(__m128i msk, __m128i on_one, __m128i on_zero)
{
    return select_u8(msk, on_one, on_zero);
}

inline
__m128
cftal::x86::select_f32(__m128 msk, __m128 on_one, __m128 on_zero)
{
#if defined (__SSE4_1__)
    return _mm_blendv_ps (on_zero, on_one, msk);
#else
    return _mm_or_ps(_mm_and_ps(on_one, msk),
                     _mm_andnot_ps(msk, on_zero));
#endif
}

inline
__m128d
cftal::x86::select_f64(__m128d msk, __m128d on_one, __m128d on_zero)
{
#if defined (__SSE4_1__)
    return _mm_blendv_pd (on_zero, on_one, msk);
#else
    return _mm_or_pd(_mm_and_pd(msk, on_one),
                     _mm_andnot_pd(msk, on_zero));
#endif
}

#if defined (__AVX__)
inline
__m256
cftal::x86::select_f32(__m256 msk, __m256 on_one, __m256 on_zero)
{
    return _mm256_blendv_ps (on_zero, on_one, msk);
}

inline
__m256d
cftal::x86::select_f64(__m256d msk, __m256d on_one, __m256d on_zero)
{
    return _mm256_blendv_pd (on_zero, on_one, msk);
}
#endif

#if defined (__AVX2__)
inline
__m256i
cftal::x86::select_u8(__m256i msk, __m256i on_one, __m256i on_zero)
{
    return _mm256_blendv_epi8 (on_zero, on_one, msk);
}

inline
__m256i
cftal::x86::select_u16(__m256i msk, __m256i on_one, __m256i on_zero)
{
    return select_u8(msk, on_one, on_zero);
}

inline
__m256i
cftal::x86::select_u32(__m256i msk, __m256i on_one, __m256i on_zero)
{
    return select_u8(msk, on_one, on_zero);
}

inline
__m256i
cftal::x86::select_u64(__m256i msk, __m256i on_one, __m256i on_zero)
{
    return select_u8(msk, on_one, on_zero);
}

#endif

#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
inline
__m512d
cftal::x86::select_f64(__mmask8 msk, __m512d on_one, __m512d on_zero)
{
    return _mm512_mask_blend_pd (msk, on_zero, on_one);
}

inline
__m512
cftal::x86::select_f32(__mmask16 msk, __m512 on_one, __m512 on_zero)
{
    return _mm512_mask_blend_ps (msk, on_zero, on_one);
}

inline
__m512i
cftal::x86::select_u64(__mmask8 msk, __m512i on_one, __m512i on_zero)
{
    return _mm512_mask_blend_epi64 (msk, on_zero, on_one);
}

inline
__m512i
cftal::x86::select_u32(__mmask16 msk, __m512i on_one, __m512i on_zero)
{
    return _mm512_mask_blend_epi32 (msk, on_zero, on_one);
}
#endif

#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
inline
__m128d
cftal::x86::select_f64(__mmask8 msk, __m128d on_one, __m128d on_zero)
{
    return _mm_mask_blend_pd (msk, on_zero, on_one);
}

inline
__m256d
cftal::x86::select_f64(__mmask8 msk, __m256d on_one, __m256d on_zero)
{
    return _mm256_mask_blend_pd (msk, on_zero, on_one);
}

inline
__m128
cftal::x86::select_f32(__mmask8 msk, __m128 on_one, __m128 on_zero)
{
    return _mm_mask_blend_ps (msk, on_zero, on_one);
}

inline
__m256
cftal::x86::select_f32(__mmask8 msk, __m256 on_one, __m256 on_zero)
{
    return _mm256_mask_blend_ps (msk, on_zero, on_one);
}

inline
__m128i
cftal::x86::select_u64(__mmask8 msk, __m128i on_one, __m128i on_zero)
{
    return _mm_mask_blend_epi64 (msk, on_zero, on_one);
}

inline
__m256i
cftal::x86::select_u64(__mmask8 msk, __m256i on_one, __m256i on_zero)
{
    return _mm256_mask_blend_epi64 (msk, on_zero, on_one);
}

inline
__m128i
cftal::x86::select_u32(__mmask8 msk, __m128i on_one, __m128i on_zero)
{
    return _mm_mask_blend_epi32 (msk, on_zero, on_one);
}

inline
__m256i
cftal::x86::select_u32(__mmask8 msk, __m256i on_one, __m256i on_zero)
{
    return _mm256_mask_blend_epi32 (msk, on_zero, on_one);
}

inline
__m128i
cftal::x86::select_u8(__mmask16 msk, __m128i on_one, __m128i on_zero)
{
    return _mm_mask_blend_epi8(msk, on_zero, on_one);
}

inline
__m256i
cftal::x86::select_u8(__mmask32 msk, __m256i on_one, __m256i on_zero)
{
    return _mm256_mask_blend_epi8(msk, on_zero, on_one);
}

inline
__m512i
cftal::x86::select_u8(__mmask64 msk, __m512i on_one, __m512i on_zero)
{
    return _mm512_mask_blend_epi8(msk, on_zero, on_one);
}

inline
__m128i
cftal::x86::select_u16(__mmask8 msk, __m128i on_one, __m128i on_zero)
{
    return _mm_mask_blend_epi16(msk, on_zero, on_one);
}

inline
__m256i
cftal::x86::select_u16(__mmask16 msk, __m256i on_one, __m256i on_zero)
{
    return _mm256_mask_blend_epi16(msk, on_zero, on_one);
}

inline
__m512i
cftal::x86::select_u16(__mmask32 msk, __m512i on_one, __m512i on_zero)
{
    return _mm512_mask_blend_epi16(msk, on_zero, on_one);
}

#endif


template <typename _T>
inline _T
cftal::x86::select_arg_1<_T>::v(_T a)
{
    return a;
}

template <typename _T>
inline _T
cftal::x86::select_arg_1<_T>::v(_T a, _T b)
{
    static_cast<void>(b);
    return a;
}

template <typename _T>
inline _T
cftal::x86::select_arg_2<_T>::v(_T a, _T b)
{
    static_cast<void>(a);
    return b;
}

template <bool _P0, bool _P1>
inline __m128d
cftal::x86::select_v2f64<_P0, _P1>::v(__m128d a, __m128d b)
{
#if defined (__SSE4_1__)
    constexpr const int sm=csel2<_P0, _P1>::val;
    return _mm_blend_pd(b, a, sm & 3);
#else
    constexpr const uint32_t m1=-1;
    typedef const_v4u32<
        (_P0 ? m1 : 0), (_P0 ? m1 : 0),
        (_P1 ? m1 : 0), (_P1 ? m1 : 0)> mask_type;
    __m128d am = _mm_and_pd(mask_type::dv(), a);
    __m128d bm = _mm_andnot_pd(mask_type::dv(), b);
    return _mm_or_pd(am, bm);
#endif
}

template <bool _P0, bool _P1, bool _P2, bool _P3>
inline __m128
cftal::x86::select_v4f32<_P0, _P1, _P2, _P3>::v(__m128 a, __m128 b)
{
#if defined (__SSE4_1__)
    constexpr const int sm=csel4<_P0, _P1, _P2, _P3>::val;
    return _mm_blend_ps(b, a, sm & 0xf);
#else
    constexpr const uint32_t m1=-1;
    typedef const_v4u32<
        (_P0 ? m1 : 0), (_P1 ? m1 : 0),
        (_P2 ? m1 : 0), (_P3 ? m1 : 0)> mask_type;
    __m128 am = _mm_and_ps(mask_type::fv(), a);
    __m128 bm = _mm_andnot_ps(mask_type::fv(), b);
    return _mm_or_ps(am, bm);
#endif
}

template<bool _P0, bool _P1>
inline __m128i
cftal::x86::
select_v2u64<_P0, _P1>::v(__m128i a, __m128i b)
{
    return select_v8u16<_P0, _P0, _P0, _P0, _P1, _P1, _P1, _P1>::v(a, b);
}

template<bool _P0, bool _P1, bool _P2, bool _P3>
inline __m128i
cftal::x86::
select_v4u32<_P0, _P1, _P2, _P3>::v(__m128i a, __m128i b)
{
    return select_v8u16<_P0, _P0, _P1, _P1, _P2, _P2, _P3, _P3>::v(a, b);
}

template<bool _P0, bool _P1, bool _P2, bool _P3,
         bool _P4, bool _P5, bool _P6, bool _P7>
inline __m128i
cftal::x86::
select_v8u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(__m128i a, __m128i b)
{
#if defined (__SSE4_1__)
#if defined (__AVX2__)
    if (_P0 == _P1 && _P2 == _P3 && _P4 == _P5 && _P6 == _P7) {
        enum { sm=csel4<_P0, _P2, _P4, _P6>::val };
        return _mm_blend_epi32(b, a, sm);
    }
#endif
    enum { sm=csel8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::val };
    return _mm_blend_epi16(b, a, sm);
#else
    typedef const_v8u16<
        uint16_t(_P0 ? -1 : 0), uint16_t(_P1 ? -1 : 0),
        uint16_t(_P2 ? -1 : 0), uint16_t(_P3 ? -1 : 0),
        uint16_t(_P4 ? -1 : 0), uint16_t(_P5 ? -1 : 0),
        uint16_t(_P6 ? -1 : 0), uint16_t(_P7 ? -1 : 0)> mask_type;
    __m128i am = _mm_and_si128(mask_type::iv(), a);
    __m128i bm = _mm_andnot_si128(mask_type::iv(), b);
    return _mm_or_si128(am, bm);
#endif
}

template<bool _P00, bool _P01, bool _P02, bool _P03,
         bool _P04, bool _P05, bool _P06, bool _P07,
         bool _P08, bool _P09, bool _P10, bool _P11,
         bool _P12, bool _P13, bool _P14, bool _P15>
inline __m128i
cftal::x86::
select_v16u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
             _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::
v(__m128i a, __m128i b)
{
    // consecutive pairs are equal ?
    if (_P00 == _P01 && _P02 == _P03 && _P04 == _P05 && _P06 == _P07 &&
        _P08 == _P09 && _P10 == _P11 && _P12 == _P13 && _P14 == _P15) {
        return select_v8u16<_P00, _P02, _P04, _P06,
                            _P08, _P10, _P12, _P14>::v(a, b);
    }
    constexpr const uint8_t p00 = _P00 ? -1 : 0;
    constexpr const uint8_t p01 = _P01 ? -1 : 0;
    constexpr const uint8_t p02 = _P02 ? -1 : 0;
    constexpr const uint8_t p03 = _P03 ? -1 : 0;
    constexpr const uint8_t p04 = _P04 ? -1 : 0;
    constexpr const uint8_t p05 = _P05 ? -1 : 0;
    constexpr const uint8_t p06 = _P06 ? -1 : 0;
    constexpr const uint8_t p07 = _P07 ? -1 : 0;
    constexpr const uint8_t p08 = _P08 ? -1 : 0;
    constexpr const uint8_t p09 = _P09 ? -1 : 0;
    constexpr const uint8_t p10 = _P10 ? -1 : 0;
    constexpr const uint8_t p11 = _P11 ? -1 : 0;
    constexpr const uint8_t p12 = _P12 ? -1 : 0;
    constexpr const uint8_t p13 = _P13 ? -1 : 0;
    constexpr const uint8_t p14 = _P14 ? -1 : 0;
    constexpr const uint8_t p15 = _P15 ? -1 : 0;
    const __m128i msk=const_v16u8<p00, p01, p02, p03,
                                  p04, p05, p06, p07,
                                  p08, p09, p10, p11,
                                  p12, p13, p14, p15>::iv();
#if defined (__SSE4_1__)
    return _mm_blendv_epi8(b, a, msk);
#else
    __m128i am = _mm_and_si128(msk, a);
    __m128i bm = _mm_andnot_si128(msk, b);
    return _mm_or_si128(am, bm);
#endif
}

#if defined (__AVX__)
template <bool _P0, bool _P1, bool _P2, bool _P3>
inline __m256d
cftal::x86::select_v4f64<_P0, _P1, _P2, _P3>::v(__m256d a, __m256d b)
{
    constexpr const int sm=csel4<_P0, _P1, _P2, _P3>::val;
    return _mm256_blend_pd(b, a, sm & 0x0f);
}

template<bool _P0, bool _P1, bool _P2, bool _P3,
         bool _P4, bool _P5, bool _P6, bool _P7>
inline __m256
cftal::x86::
select_v8f32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(__m256 a, __m256 b)
{
    constexpr const int sm=csel8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::val;
    return _mm256_blend_ps(b, a, sm & 0xff);
}
#endif

#if defined (__AVX2__)

template<bool _P0, bool _P1, bool _P2, bool _P3>
inline __m256i
cftal::x86::
select_v4u64<_P0, _P1, _P2, _P3>::v(__m256i a, __m256i b)
{
    constexpr const int sm=csel8<_P0, _P0, _P1, _P1, _P2, _P2, _P3, _P3>::val;
    return _mm256_blend_epi32(b, a, sm & 0xff);
}

template<bool _P0, bool _P1, bool _P2, bool _P3,
         bool _P4, bool _P5, bool _P6, bool _P7>
inline __m256i
cftal::x86::
select_v8u32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(__m256i a, __m256i b)
{
    constexpr const int sm=csel8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::val;
    return _mm256_blend_epi32(b, a, sm & 0xff);
}

template <bool _P00, bool _P01, bool _P02, bool _P03,
          bool _P04, bool _P05, bool _P06, bool _P07,
          bool _P08, bool _P09, bool _P10, bool _P11,
          bool _P12, bool _P13, bool _P14, bool _P15>
inline __m256i
cftal::x86::
select_v16u16<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
              _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::
v(__m256i a, __m256i b)
{
    // low lane and high lane are equal ?
    if (_P00 == _P08 && _P01 == _P09 && _P02 == _P10 && _P03 == _P11 &&
        _P04 == _P12 && _P05 == _P13 && _P06 == _P14 && _P07 == _P15) {
        enum {
            sm=csel8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07>::val
        };
        return _mm256_blend_epi16(b, a, sm);
    }
    // consecutive pairs are equal ?
    if (_P00 == _P01 && _P02 == _P03 && _P04 == _P05 && _P06 == _P07 &&
        _P08 == _P09 && _P10 == _P11 && _P12 == _P13 && _P14 == _P15) {
        return select_v8u32<_P00, _P02, _P04, _P06,
                            _P08, _P10, _P12, _P14>::v(a, b);
    }
    constexpr const uint16_t p00 = _P00 ? -1 : 0;
    constexpr const uint16_t p01 = _P01 ? -1 : 0;
    constexpr const uint16_t p02 = _P02 ? -1 : 0;
    constexpr const uint16_t p03 = _P03 ? -1 : 0;
    constexpr const uint16_t p04 = _P04 ? -1 : 0;
    constexpr const uint16_t p05 = _P05 ? -1 : 0;
    constexpr const uint16_t p06 = _P06 ? -1 : 0;
    constexpr const uint16_t p07 = _P07 ? -1 : 0;
    constexpr const uint16_t p08 = _P08 ? -1 : 0;
    constexpr const uint16_t p09 = _P09 ? -1 : 0;
    constexpr const uint16_t p10 = _P10 ? -1 : 0;
    constexpr const uint16_t p11 = _P11 ? -1 : 0;
    constexpr const uint16_t p12 = _P12 ? -1 : 0;
    constexpr const uint16_t p13 = _P13 ? -1 : 0;
    constexpr const uint16_t p14 = _P14 ? -1 : 0;
    constexpr const uint16_t p15 = _P15 ? -1 : 0;
    const __m256i msk=const_v16u16<p00, p01, p02, p03,
                                   p04, p05, p06, p07,
                                   p08, p09, p10, p11,
                                   p12, p13, p14, p15>::iv();
    return select_u16(msk, a, b);
}

template <bool _P00, bool _P01, bool _P02, bool _P03,
          bool _P04, bool _P05, bool _P06, bool _P07,
          bool _P08, bool _P09, bool _P10, bool _P11,
          bool _P12, bool _P13, bool _P14, bool _P15,
          bool _P16, bool _P17, bool _P18, bool _P19,
          bool _P20, bool _P21, bool _P22, bool _P23,
          bool _P24, bool _P25, bool _P26, bool _P27,
          bool _P28, bool _P29, bool _P30, bool _P31>
inline __m256i
cftal::x86::
select_v32u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
             _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15,
             _P16, _P17, _P18, _P19, _P20, _P21, _P22, _P23,
             _P24, _P25, _P26, _P27, _P28, _P29, _P30, _P31>::
v(__m256i a, __m256i b)
{
    // consecutive pairs are equal ?
    if (_P00 == _P01 && _P02 == _P03 && _P04 == _P05 && _P06 == _P07 &&
        _P08 == _P09 && _P10 == _P11 && _P12 == _P13 && _P14 == _P15 &&
        _P16 == _P17 && _P18 == _P19 && _P20 == _P21 && _P22 == _P23 &&
        _P24 == _P25 && _P26 == _P27 && _P28 == _P29 && _P30 == _P31) {
        return select_v16u16<_P00, _P02, _P04, _P06,
                             _P08, _P10, _P12, _P14,
                             _P16, _P18, _P20, _P22,
                             _P24, _P26, _P28, _P30>::v(a, b);
    }
    constexpr const uint8_t p00 = _P00 ? -1 : 0;
    constexpr const uint8_t p01 = _P01 ? -1 : 0;
    constexpr const uint8_t p02 = _P02 ? -1 : 0;
    constexpr const uint8_t p03 = _P03 ? -1 : 0;
    constexpr const uint8_t p04 = _P04 ? -1 : 0;
    constexpr const uint8_t p05 = _P05 ? -1 : 0;
    constexpr const uint8_t p06 = _P06 ? -1 : 0;
    constexpr const uint8_t p07 = _P07 ? -1 : 0;
    constexpr const uint8_t p08 = _P08 ? -1 : 0;
    constexpr const uint8_t p09 = _P09 ? -1 : 0;
    constexpr const uint8_t p10 = _P10 ? -1 : 0;
    constexpr const uint8_t p11 = _P11 ? -1 : 0;
    constexpr const uint8_t p12 = _P12 ? -1 : 0;
    constexpr const uint8_t p13 = _P13 ? -1 : 0;
    constexpr const uint8_t p14 = _P14 ? -1 : 0;
    constexpr const uint8_t p15 = _P15 ? -1 : 0;
    constexpr const uint8_t p16 = _P16 ? -1 : 0;
    constexpr const uint8_t p17 = _P17 ? -1 : 0;
    constexpr const uint8_t p18 = _P18 ? -1 : 0;
    constexpr const uint8_t p19 = _P19 ? -1 : 0;
    constexpr const uint8_t p20 = _P20 ? -1 : 0;
    constexpr const uint8_t p21 = _P21 ? -1 : 0;
    constexpr const uint8_t p22 = _P22 ? -1 : 0;
    constexpr const uint8_t p23 = _P23 ? -1 : 0;
    constexpr const uint8_t p24 = _P24 ? -1 : 0;
    constexpr const uint8_t p25 = _P25 ? -1 : 0;
    constexpr const uint8_t p26 = _P26 ? -1 : 0;
    constexpr const uint8_t p27 = _P27 ? -1 : 0;
    constexpr const uint8_t p28 = _P28 ? -1 : 0;
    constexpr const uint8_t p29 = _P29 ? -1 : 0;
    constexpr const uint8_t p30 = _P30 ? -1 : 0;
    constexpr const uint8_t p31 = _P31 ? -1 : 0;
    const __m256i msk=const_v32u8<p00, p01, p02, p03, p04, p05, p06, p07,
                                  p08, p09, p10, p11, p12, p13, p14, p15,
                                  p16, p17, p18, p19, p20, p21, p22, p23,
                                  p24, p25, p26, p27, p28, p29, p30, p31>::iv();
    return select_u8(msk, a, b);
}
#endif

#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)

template<bool _P0, bool _P1, bool _P2, bool _P3,
         bool _P4, bool _P5, bool _P6, bool _P7>
inline __m512d
cftal::x86::
select_v8f64<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::
v(__m512d a, __m512d b)
{
    constexpr const uint32_t p0=_P0 ? 0x00001 : 0x00000;
    constexpr const uint32_t p1=_P1 ? 0x00002 : 0x00000;
    constexpr const uint32_t p2=_P2 ? 0x00004 : 0x00000;
    constexpr const uint32_t p3=_P3 ? 0x00008 : 0x00000;
    constexpr const uint32_t p4=_P4 ? 0x00010 : 0x00000;
    constexpr const uint32_t p5=_P5 ? 0x00020 : 0x00000;
    constexpr const uint32_t p6=_P6 ? 0x00040 : 0x00000;
    constexpr const uint32_t p7=_P7 ? 0x00080 : 0x00000;
    constexpr __mmask8 msk= p0|p1|p2|p3|p4|p5|p6|p7;

    return _mm512_mask_blend_pd(msk, b, a);
}

template <bool _P00, bool _P01, bool _P02, bool _P03,
          bool _P04, bool _P05, bool _P06, bool _P07,
          bool _P08, bool _P09, bool _P10, bool _P11,
          bool _P12, bool _P13, bool _P14, bool _P15>
inline __m512
cftal::x86::
select_v16f32<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
              _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::
v(__m512 a, __m512 b)
{
    constexpr const uint32_t p00=_P00 ? 0x00001 : 0x00000;
    constexpr const uint32_t p01=_P01 ? 0x00002 : 0x00000;
    constexpr const uint32_t p02=_P02 ? 0x00004 : 0x00000;
    constexpr const uint32_t p03=_P03 ? 0x00008 : 0x00000;
    constexpr const uint32_t p04=_P04 ? 0x00010 : 0x00000;
    constexpr const uint32_t p05=_P05 ? 0x00020 : 0x00000;
    constexpr const uint32_t p06=_P06 ? 0x00040 : 0x00000;
    constexpr const uint32_t p07=_P07 ? 0x00080 : 0x00000;
    constexpr const uint32_t p08=_P08 ? 0x00100 : 0x00000;
    constexpr const uint32_t p09=_P09 ? 0x00200 : 0x00000;
    constexpr const uint32_t p10=_P10 ? 0x00400 : 0x00000;
    constexpr const uint32_t p11=_P11 ? 0x00800 : 0x00000;
    constexpr const uint32_t p12=_P12 ? 0x01000 : 0x00000;
    constexpr const uint32_t p13=_P13 ? 0x02000 : 0x00000;
    constexpr const uint32_t p14=_P14 ? 0x04000 : 0x00000;
    constexpr const uint32_t p15=_P15 ? 0x08000 : 0x00000;

    constexpr __mmask16 msk= p00|p01|p02|p03|p04|p05|p06|p07|
                             p08|p09|p10|p11|p12|p13|p14|p15;
    return _mm512_mask_blend_ps(msk, b, a);
}


template<bool _P0, bool _P1, bool _P2, bool _P3,
         bool _P4, bool _P5, bool _P6, bool _P7>
inline __m512i
cftal::x86::
select_v8u64<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::
v(__m512i a, __m512i b)
{
    constexpr const uint32_t p0=_P0 ? 0x00001 : 0x00000;
    constexpr const uint32_t p1=_P1 ? 0x00002 : 0x00000;
    constexpr const uint32_t p2=_P2 ? 0x00004 : 0x00000;
    constexpr const uint32_t p3=_P3 ? 0x00008 : 0x00000;
    constexpr const uint32_t p4=_P4 ? 0x00010 : 0x00000;
    constexpr const uint32_t p5=_P5 ? 0x00020 : 0x00000;
    constexpr const uint32_t p6=_P6 ? 0x00040 : 0x00000;
    constexpr const uint32_t p7=_P7 ? 0x00080 : 0x00000;

    constexpr __mmask8 msk= p0|p1|p2|p3|p4|p5|p6|p7;
    return _mm512_mask_blend_epi64(msk, b, a);
}


template <bool _P00, bool _P01, bool _P02, bool _P03,
          bool _P04, bool _P05, bool _P06, bool _P07,
          bool _P08, bool _P09, bool _P10, bool _P11,
          bool _P12, bool _P13, bool _P14, bool _P15>
inline __m512i
cftal::x86::
select_v16u32<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
              _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::
v(__m512i a, __m512i b)
{
    constexpr const uint32_t p00=_P00 ? 0x00001 : 0x00000;
    constexpr const uint32_t p01=_P01 ? 0x00002 : 0x00000;
    constexpr const uint32_t p02=_P02 ? 0x00004 : 0x00000;
    constexpr const uint32_t p03=_P03 ? 0x00008 : 0x00000;
    constexpr const uint32_t p04=_P04 ? 0x00010 : 0x00000;
    constexpr const uint32_t p05=_P05 ? 0x00020 : 0x00000;
    constexpr const uint32_t p06=_P06 ? 0x00040 : 0x00000;
    constexpr const uint32_t p07=_P07 ? 0x00080 : 0x00000;
    constexpr const uint32_t p08=_P08 ? 0x00100 : 0x00000;
    constexpr const uint32_t p09=_P09 ? 0x00200 : 0x00000;
    constexpr const uint32_t p10=_P10 ? 0x00400 : 0x00000;
    constexpr const uint32_t p11=_P11 ? 0x00800 : 0x00000;
    constexpr const uint32_t p12=_P12 ? 0x01000 : 0x00000;
    constexpr const uint32_t p13=_P13 ? 0x02000 : 0x00000;
    constexpr const uint32_t p14=_P14 ? 0x04000 : 0x00000;
    constexpr const uint32_t p15=_P15 ? 0x08000 : 0x00000;

    constexpr __mmask16 msk= p00|p01|p02|p03|p04|p05|p06|p07|
                             p08|p09|p10|p11|p12|p13|p14|p15;
    return _mm512_mask_blend_epi32(msk, b, a);
}

#endif

template <bool _P0, bool _P1>
inline
__m128d cftal::x86::select_f64(__m128d a, __m128d b)
{
    return select_v2f64<_P0, _P1>::v(a, b);
}

template <bool _P0, bool _P1, bool _P2, bool _P3>
inline
__m128 cftal::x86::select_f32(__m128 a, __m128 b)
{
    return select_v4f32<_P0, _P1, _P2, _P3>::v(a, b);
}

template <bool _P0, bool _P1>
inline
__m128i cftal::x86::select_u64(__m128i a, __m128i b)
{
    return select_v2u64<_P0, _P1>::v(a, b);
}

template <bool _P0, bool _P1, bool _P2, bool _P3>
inline
__m128i cftal::x86::select_u32(__m128i a, __m128i b)
{
    return select_v4u32<_P0, _P1, _P2, _P3>::v(a, b);
}

template<bool _P00, bool _P01, bool _P02, bool _P03,
         bool _P04, bool _P05, bool _P06, bool _P07,
         bool _P08, bool _P09, bool _P10, bool _P11,
         bool _P12, bool _P13, bool _P14, bool _P15>
inline
__m128i cftal::x86::select_u8(__m128i a, __m128i b)
{
    return select_v16u8<_P00, _P01, _P02, _P03,
                        _P04, _P05, _P06, _P07,
                        _P08, _P09, _P10, _P11,
                        _P12, _P13, _P14, _P15>::v(a, b);
}

template <bool _P0, bool _P1, bool _P2, bool _P3,
          bool _P4, bool _P5, bool _P6, bool _P7>
__m128i cftal::x86::select_u16(__m128i a, __m128i b)
{
    return select_v8u16<_P0, _P1, _P2, _P3,
                        _P4, _P5, _P6, _P7>::v(a, b);
}

#if defined (__AVX__)

template <bool _P0, bool _P1, bool _P2, bool _P3>
inline
__m256d cftal::x86::select_f64(__m256d a, __m256d b)
{
    return select_v4f64<_P0, _P1, _P2, _P3>::v(a, b);
}

template <bool _P0, bool _P1, bool _P2, bool _P3,
          bool _P4, bool _P5, bool _P6, bool _P7>
__m256 cftal::x86::select_f32(__m256 a, __m256 b)
{
    return select_v8f32<_P0, _P1, _P2, _P3,
                        _P4, _P5, _P6, _P7>::v(a, b);
}

#endif

#if defined (__AVX2__)
template <bool _P0, bool _P1, bool _P2, bool _P3>
__m256i cftal::x86::select_u64(__m256i a, __m256i b)
{
    return select_v4u64<_P0, _P1, _P2, _P3>::v(a, b);
}

template <bool _P0, bool _P1, bool _P2, bool _P3,
          bool _P4, bool _P5, bool _P6, bool _P7>
__m256i cftal::x86::select_u32(__m256i a, __m256i b)
{
    return select_v8u32<_P0, _P1, _P2, _P3,
                        _P4, _P5, _P6, _P7>::v(a, b);
}

template<bool _P00, bool _P01, bool _P02, bool _P03,
         bool _P04, bool _P05, bool _P06, bool _P07,
         bool _P08, bool _P09, bool _P10, bool _P11,
         bool _P12, bool _P13, bool _P14, bool _P15>
inline
__m256i cftal::x86::select_u16(__m256i a, __m256i b)
{
    return select_v16u16<_P00, _P01, _P02, _P03,
                         _P04, _P05, _P06, _P07,
                         _P08, _P09, _P10, _P11,
                         _P12, _P13, _P14, _P15>::v(a, b);
}

template<bool _P00, bool _P01, bool _P02, bool _P03,
         bool _P04, bool _P05, bool _P06, bool _P07,
         bool _P08, bool _P09, bool _P10, bool _P11,
         bool _P12, bool _P13, bool _P14, bool _P15,
         bool _P16, bool _P17, bool _P18, bool _P19,
         bool _P20, bool _P21, bool _P22, bool _P23,
         bool _P24, bool _P25, bool _P26, bool _P27,
         bool _P28, bool _P29, bool _P30, bool _P31>
inline
__m256i cftal::x86::select_u8(__m256i a, __m256i b)
{
    return select_v32u8<_P00, _P01, _P02, _P03,
                        _P04, _P05, _P06, _P07,
                        _P08, _P09, _P10, _P11,
                        _P12, _P13, _P14, _P15,
                        _P16, _P17, _P18, _P19,
                        _P20, _P21, _P22, _P23,
                        _P24, _P25, _P26, _P27,
                        _P28, _P29, _P30, _P31>::v(a, b);
}
#endif

#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)

template <bool _P0, bool _P1, bool _P2, bool _P3,
          bool _P4, bool _P5, bool _P6, bool _P7>
inline
__m512d cftal::x86::select_f64(__m512d a, __m512d b)
{
    return select_v8f64<_P0, _P1, _P2, _P3,
                        _P4, _P5, _P6, _P7>::v(a, b);
}

template <bool _P00, bool _P01, bool _P02, bool _P03,
          bool _P04, bool _P05, bool _P06, bool _P07,
          bool _P08, bool _P09, bool _P10, bool _P11,
          bool _P12, bool _P13, bool _P14, bool _P15>
__m512 cftal::x86::select_f32(__m512 a, __m512 b)
{
    return select_v16f32<_P00, _P01, _P02, _P03,
                         _P04, _P05, _P06, _P07,
                         _P08, _P09, _P10, _P11,
                         _P12, _P13, _P14, _P15>::v(a, b);
}

template <bool _P0, bool _P1, bool _P2, bool _P3,
          bool _P4, bool _P5, bool _P6, bool _P7>
__m512i cftal::x86::select_u64(__m512d a, __m512d b)
{
    return select_v8u64<_P0, _P1, _P2, _P3,
                        _P4, _P5, _P6, _P7>::v(a, b);
}

template <bool _P00, bool _P01, bool _P02, bool _P03,
          bool _P04, bool _P05, bool _P06, bool _P07,
          bool _P08, bool _P09, bool _P10, bool _P11,
          bool _P12, bool _P13, bool _P14, bool _P15>
__m512i cftal::x86::select_u32(__m512i a, __m512i b)
{
    return select_v16u32<_P00, _P01, _P02, _P03,
                         _P04, _P05, _P06, _P07,
                         _P08, _P09, _P10, _P11,
                         _P12, _P13, _P14, _P15>::v(a, b);
}

#endif


// Local variables:
// mode: c++
// end:

#endif // __CFTAL_X86_SELECT_H__
