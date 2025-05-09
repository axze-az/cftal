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
#if !defined (__CFTAL_X86_OPS_1_H__)
#define __CFTAL_X86_OPS_1_H__ 1

#include <cftal/fenv.h>
#include <cftal/constants.h>
#include <cftal/x86/const.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/ops_0.h>

namespace cftal {

    namespace x86 {

        template <class _E, unsigned _EN>
        struct div_ref {
            static __m128i ref(__m128i a, __m128i b,
                               __m128i* rem=nullptr);
            static __m128i v(__m128i a, __m128i b,
                             __m128i* rem=nullptr);
        };

        struct div_u8 : public div_ref<uint8_t, 16> {
        private:
            template <unsigned _POS>
            static __m128i pos(__m128i x, __m128i y);
        public:
            static __m128i v(__m128i a, __m128i b,
                             __m128i* rem=nullptr);
#if defined (__AVX2__)
        private:
            template <unsigned _POS>
            static __m256i pos(__m256i x, __m256i y);
        public:
            static __m256i v(__m256i a, __m256i b,
                             __m256i* rem=nullptr);
#endif
        };

        struct div_s8 : public div_ref<int8_t, 16> {
        private:
            template <unsigned _POS>
            static __m128i pos(__m128i x, __m128i y);
        public:
            static __m128i v(__m128i a, __m128i b,
                             __m128i* rem=nullptr);
#if defined (__AVX2__)
        private:
            template <unsigned _POS>
            static __m256i pos(__m256i x, __m256i y);
        public:
            static __m256i v(__m256i a, __m256i b,
                             __m256i* rem=nullptr);
#endif
        };

        struct div_u16 : public div_ref<uint16_t, 8> {
            static __m128i v(__m128i a, __m128i b,
                             __m128i* rem=nullptr);
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i b,
                             __m256i* rem=nullptr);
#endif
        };

        struct div_s16 : public div_ref<int16_t, 8> {
            static __m128i v(__m128i a, __m128i b,
                             __m128i* rem=nullptr);
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i b,
                             __m256i* rem=nullptr);
#endif
        };

        struct div_u32 : public div_ref<uint32_t, 4> {
            static __m128i v(__m128i a, __m128i b,
                             __m128i* rem=nullptr);
            // same as above but divides only the low halfes of a/b
            static __m128i lh(__m128i a, __m128i b,
                              __m128i* rem=nullptr);
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i b,
                             __m256i* rem=nullptr);
#endif
#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__>0)
            static __m512i v(__m512i a, __m512i b,
                             __m512i* rem=nullptr);
#endif
        };

        struct div_s32 : public div_ref<int32_t, 4> {
            static __m128i v(__m128i a, __m128i b,
                             __m128i* rem=nullptr);
            // same as above but divides only the low halfes of a/b
            static __m128i lh(__m128i a, __m128i b,
                              __m128i* rem=nullptr);
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i b,
                             __m256i* rem=nullptr);
#endif
#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__>0)
            static __m512i v(__m512i a, __m512i b,
                             __m512i* rem=nullptr);
#endif
        };

        struct div_u64 : public div_ref<uint64_t, 2> {
            static __m128i v(__m128i a, __m128i b,
                             __m128i* rem=nullptr);
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i b,
                             __m256i* rem=nullptr);
#endif
#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__>0)
            static __m512i v(__m512i a, __m512i b,
                             __m512i* rem=nullptr);
#endif
        };

        struct div_s64 : public div_ref<int64_t, 2> {
            static __m128i v(__m128i a, __m128i b,
                             __m128i* rem=nullptr);

#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i b,
                             __m256i* rem=nullptr);
#endif
#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__>0)
            static __m512i v(__m512i a, __m512i b,
                             __m512i* rem=nullptr);
#endif
        };

        uint32_t compress_mask_f32(__m128 m);
        uint32_t compress_mask_f64(__m128d m);
        uint32_t compress_mask_u8(__m128i m);
        uint32_t compress_mask_u16(__m128i m);
        uint32_t compress_mask_u32(__m128i m);
        uint32_t compress_mask_u64(__m128i m);
#if defined (__AVX__)
        uint32_t compress_mask_f32(__m256 m);
        uint32_t compress_mask_f64(__m256d m);
#endif
#if defined (__AVX2__)
        uint32_t compress_mask_u8(__m256i m);
        uint32_t compress_mask_u16(__m256i m);
        uint32_t compress_mask_u32(__m256i m);
        uint32_t compress_mask_u64(__m256i m);
#endif

        __m128 expand_mask_v4f32(uint32_t msk4);
        __m128d expand_mask_v2f64(uint32_t msk2);
        __m128i expand_mask_v16u8(uint32_t msk16);
        __m128i expand_mask_v8u16(uint32_t msk8);
        __m128i expand_mask_v4u32(uint32_t msk4);
        __m128i expand_mask_v2u64(uint32_t msk2);

#if defined (__AVX__)
        __m256 expand_mask_v8f32(uint32_t msk8);
        __m256d expand_mask_v4f64(uint32_t msk4);
#endif
#if defined (__AVX2__)
        __m256i expand_mask_v32u8(uint32_t msk32);
        __m256i expand_mask_v16u16(uint32_t msk16);
        __m256i expand_mask_v8u32(uint32_t msk8);
        __m256i expand_mask_v4u64(uint32_t msk4);
#endif
        // read the sign bits of all elements into a bit mask
        uint32_t read_signs_f32(__m128 i);
        // read the sign bits of all elements into a bit mask
        uint32_t read_signs_f64(__m128d d);
        // read the sign bits of all elements into a bit mask
        uint32_t read_signs_s8(__m128i i);
        // read the sign bits of all elements into a bit mask
        uint32_t read_signs_s16(__m128i i);
        // read the sign bits of all elements into a bit mask
        uint32_t read_signs_s32(__m128i i);
        // read the sign bits of all elements into a bit mask
        uint32_t read_signs_s64(__m128i i);
#if defined (__AVX__)
        // read the sign bits of all elements into a bit mask
        uint32_t read_signs_f32(__m256 i);
        // read the sign bits of all elements into a bit mask
        uint32_t read_signs_f64(__m256d d);
#endif
#if defined (__AVX2__)
        // read the sign bits of all elements into a bit mask
        uint32_t read_signs_s8(__m256i i);
        // read the sign bits of all elements into a bit mask
        uint32_t read_signs_s16(__m256i i);
        // read the sign bits of all elements into a bit mask
        uint32_t read_signs_s32(__m256i i);
        // read the sign bits of all elements into a bit mask
        uint32_t read_signs_s64(__m256i i);
#endif
#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
        // return the mask itself
        uint32_t read_signs_f32(__mmask16 i);
        // return the mask itself
        uint32_t read_signs_f64(__mmask8 i);
#endif
        // check the sign bits of v4f32
        bool all_of_f32(__m128 a);
        bool any_of_f32(__m128 a);
        bool none_of_f32(__m128 a);
        // check the sign bits of v2f64
        bool all_of_f64(__m128d a);
        bool any_of_f64(__m128d a);
        bool none_of_f64(__m128d a);
        // check the sign bits of v16s8
        bool all_of_s8(__m128i a);
        bool any_of_s8(__m128i a);
        bool none_of_s8(__m128i a);
        // check the sign bits of v8s16
        bool all_of_s16(__m128i a);
        bool any_of_s16(__m128i a);
        bool none_of_s16(__m128i a);
        // check the sign bits of v4s32
        bool all_of_s32(__m128i a);
        bool any_of_s32(__m128i a);
        bool none_of_s32(__m128i a);
        // check the sign bits of v2s64
        bool all_of_s64(__m128i a);
        bool any_of_s64(__m128i a);
        bool none_of_s64(__m128i a);
#if defined (__AVX__)
        // check the sign bits of v8f32
        bool all_of_f32(__m256 a);
        bool any_of_f32(__m256 a);
        bool none_of_f32(__m256 a);
        // check the sign bits of v4f64
        bool all_of_f64(__m256d a);
        bool any_of_f64(__m256d a);
        bool none_of_f64(__m256d a);
#endif
#if defined (__AVX2__)
        // check the sign bits of v32s8
        bool all_of_s8(__m256i a);
        bool any_of_s8(__m256i a);
        bool none_of_s8(__m256i a);
        // check the sign bits of v16s16
        bool all_of_s16(__m256i a);
        bool any_of_s16(__m256i a);
        bool none_of_s16(__m256i a);
        // check the sign bits of v8s32
        bool all_of_s32(__m256i a);
        bool any_of_s32(__m256i a);
        bool none_of_s32(__m256i a);
        // check the sign bits of v4s64
        bool all_of_s64(__m256i a);
        bool any_of_s64(__m256i a);
        bool none_of_s64(__m256i a);
#endif

        __m128i popcnt_u8(__m128i a);
        __m128i popcnt_u16(__m128i a);
        __m128i popcnt_u32(__m128i b);
        __m128i popcnt_u64(__m128i a);
        int popcnt_u128(__m128i a);

        __m128i bitrev_u8(__m128i a);
        __m128i bitrev_u16(__m128i a);
        __m128i bitrev_u32(__m128i a);
        __m128i bitrev_u64(__m128i a);

    }

}

template <class _E, unsigned _EN>
__m128i cftal::x86::div_ref<_E, _EN>::ref(__m128i a, __m128i b, __m128i* rem)
{
    vecunion<_E, _EN, __m128, __m128d, __m128i> ca, cb, cq, cr;
    _mm_store_si128(&ca._vi, a);
    _mm_store_si128(&cb._vi, b);
    for (unsigned i=0; i<_EN; ++i) {
        if (cb._s[i] != _E(0) ) {
            cq._s[i] = ca._s[i] / cb._s[i];
            cr._s[i] = ca._s[i] % cb._s[i];
        } else {
            cq._s[i] = _E(-1);
            cr._s[i] = ca._s[i];
        }
    }
    if (rem != nullptr)
        _mm_store_si128(rem, _mm_load_si128(&cr._vi));
    return _mm_load_si128(&cq._vi);
}

template <class _E, unsigned _EN>
__m128i cftal::x86::div_ref<_E, _EN>::v(__m128i a, __m128i b, __m128i* rem)
{
    return ref(a, b, rem);
}

inline
cftal::uint32_t
cftal::x86::compress_mask_f32(__m128 a)
{
    return _mm_movemask_ps(a);
}

inline
cftal::uint32_t
cftal::x86::compress_mask_f64(__m128d a)
{
    return _mm_movemask_pd(a);
}

inline
cftal::uint32_t
cftal::x86::compress_mask_u8(__m128i a)
{
    return _mm_movemask_epi8(a);
}

inline
cftal::uint32_t
cftal::x86::compress_mask_u16(__m128i a)
{
#if defined (__SSSE3__)
    const __m128i msk = const_v16u8< 1,  3,  5,  7,  9, 11, 13, 15,
                                     0xff, 0xff, 0xff, 0xff,
                                     0xff, 0xff, 0xff, 0xff>::iv();
    return _mm_movemask_epi8(_mm_shuffle_epi8(a, msk));
#else
    // move the sign bit to all bits
    __m128i sa=_mm_srai_epi16(a, 15);
    const __m128i msk = const_v8u16< 1, 2, 4, 8, 16, 32, 64, 128>::iv();
    sa = _mm_and_si128(sa, msk);
    // combine the bits from the upper 4 elements with the bits from the
    // lower
    __m128i t= vpshufd<2, 3, 2, 3>::v(sa);
    sa = _mm_or_si128(sa, t);
    // combine the bits from uin16_t [0-1] with [2-3]
    t = vpshuflw<2, 3, 2, 3>::v(sa);
    sa = _mm_or_si128(sa, t);
    // combine the bits from the [0] and [1]
    t = vpshuflw<1, 1, 1, 1>::v(sa);
    sa = _mm_or_si128(sa, t);
    return _mm_cvtsi128_si32(sa) & 0xff;
#endif
}

inline
cftal::uint32_t
cftal::x86::compress_mask_u32(__m128i a)
{
    return compress_mask_f32(_mm_castsi128_ps(a));
}

inline
cftal::uint32_t
cftal::x86::compress_mask_u64(__m128i a)
{
    return compress_mask_f64(_mm_castsi128_pd(a));
}

inline
cftal::uint32_t cftal::x86::read_signs_s8(__m128i a)
{
    return compress_mask_u8(a);
}

inline
cftal::uint32_t cftal::x86::read_signs_s16(__m128i a)
{
    return compress_mask_u16(a);
}

inline
cftal::uint32_t cftal::x86::read_signs_s32(__m128i a)
{
    return compress_mask_u32(a);
}

inline
cftal::uint32_t cftal::x86::read_signs_s64(__m128i a)
{
    return compress_mask_u64(a);
}

inline
cftal::uint32_t cftal::x86::read_signs_f32(__m128 a)
{
    return compress_mask_f32(a);
}

inline
cftal::uint32_t cftal::x86::read_signs_f64(__m128d a)
{
    return compress_mask_f64(a);
}

#if defined (__AVX__)

inline
cftal::uint32_t
cftal::x86::compress_mask_f32(__m256 m)
{
    return _mm256_movemask_ps(m);
}

inline
cftal::uint32_t
cftal::x86::compress_mask_f64(__m256d m)
{
    return _mm256_movemask_pd(m);
}

inline
cftal::uint32_t cftal::x86::read_signs_f32(__m256 a)
{
    return compress_mask_f32(a);
}

inline
cftal::uint32_t cftal::x86::read_signs_f64(__m256d a)
{
    return compress_mask_f64(a);
}
#endif

#if defined (__AVX2__)

inline
cftal::uint32_t
cftal::x86::compress_mask_u8(__m256i m)
{
    return _mm256_movemask_epi8(m);
}

inline
cftal::uint32_t
cftal::x86::compress_mask_u16(__m256i m)
{
#if defined (__BMI2__) &&                       \
    !defined(__tune_bdver4__) &&                \
    !defined(__tune_znver1__) &&                \
    !defined(__tune_znver2__)
    uint32_t r=_mm256_movemask_epi8(m);
    constexpr const uint32_t mm=0xAAAA'AAAA;
    r = _pext_u32(r, mm);
#else
    const __m256i m0= const_v32u8<  1,   3,   5,  7,
                                    9,  11,  13, 15,
                                    255, 255, 255, 255,
                                    255, 255, 255, 255,
                                    1,   3,   5,   7,
                                    9,  11,  13,  15,
                                    255, 255, 255, 255,
                                    255, 255, 255, 255>::iv();
    __m256i as= _mm256_shuffle_epi8(m, m0);
    // and use vpermq concentrate the values in the low half
    const int p=shuffle4<0, 2, 1, 3>::val;
    as =_mm256_permute4x64_epi64(as, p);
    uint32_t r=_mm_movemask_epi8(_mm256_castsi256_si128(as));
#endif
    return r;
}

inline
cftal::uint32_t
cftal::x86::compress_mask_u32(__m256i m)
{
    return compress_mask_f32(_mm256_castsi256_ps(m));
}

inline
uint32_t cftal::x86::compress_mask_u64(__m256i m)
{
    return compress_mask_f64(_mm256_castsi256_pd(m));
}

#endif

inline
__m128
cftal::x86::expand_mask_v4f32(uint32_t msk4)
{
    return _mm_castsi128_ps(expand_mask_v4u32(msk4));
}

inline
__m128d
cftal::x86::expand_mask_v2f64(uint32_t msk2)
{
    return _mm_castsi128_pd(expand_mask_v2u64(msk2));
}

inline
__m128i
cftal::x86::expand_mask_v16u8(uint32_t msk16)
{
    const __m128i sm=const_v16u8< 0, 0, 0, 0, 0, 0, 0, 0,
                                  1, 1, 1, 1, 1, 1, 1, 1>::iv();
    const __m128i bm=const_v16u8< 1, 2, 4, 8, 16, 32, 64, 128,
                                  1, 2, 4, 8, 16, 32, 64, 128>::iv();
    __m128i r=_mm_cvtsi32_si128(msk16);
    r = vpshufb::v(r, sm);
    r = _mm_and_si128(r, bm);
    r = _mm_cmpeq_epi8(r, bm);
    return r;
}

inline
__m128i
cftal::x86::expand_mask_v8u16(uint32_t msk8)
{
    const __m128i bm=const_v8u16< 1, 2, 4, 8, 16, 32, 64, 128>::iv();
    __m128i r=_mm_set1_epi16(msk8);
    r = _mm_and_si128(r, bm);
    r = _mm_cmpeq_epi16(r, bm);
    return r;
}

inline
__m128i
cftal::x86::expand_mask_v4u32(uint32_t msk4)
{
    const __m128i bm=const_v4u32< 1, 2, 4, 8>::iv();
    __m128i r=_mm_set1_epi32(msk4);
    r = _mm_and_si128(r, bm);
    r = _mm_cmpeq_epi32(r, bm);
    return r;
}

inline
__m128i
cftal::x86::expand_mask_v2u64(uint32_t msk2)
{
    const __m128i bm=const_v4u32< 1, 0, 2, 0>::iv();
    __m128i r=_mm_set1_epi32(msk2);
    r = _mm_and_si128(r, bm);
    r = vpcmpeqq::v(r, bm);
    return r;
}

#if defined (__AVX__)
inline
__m256
cftal::x86::expand_mask_v8f32(uint32_t msk8)
{
#if defined (__AVX2__)
    return _mm256_castsi256_ps(expand_mask_v8u32(msk8));
#else
    __m128 l=expand_mask_v4f32(msk8 & 7);
    __m128 h=expand_mask_v4f32(msk8 >> 4);
    __m256 r=_mm256_castps128_ps256(l);
    r =_mm256_insertf128_ps(r, h, 1);
    return r;
#endif
}

inline
__m256d
cftal::x86::expand_mask_v4f64(uint32_t msk4)
{
#if defined (__AVX2__)
    return _mm256_castsi256_pd(expand_mask_v4u64(msk4));
#else
    __m128d l=expand_mask_v2f64(msk4 & 3);
    __m128d h=expand_mask_v2f64(msk4 >> 2);
    __m256d r=_mm256_castpd128_pd256(l);
    r =_mm256_insertf128_pd(r, h, 1);
    return r;
#endif
}
#endif

#if defined (__AVX2__)
inline
__m256i
cftal::x86::expand_mask_v32u8(uint32_t msk32)
{
    const __m256i sm=const_v32u8< 0, 0, 0, 0, 0, 0, 0, 0,
                                  1, 1, 1, 1, 1, 1, 1, 1,
                                  2, 2, 2, 2, 2, 2, 2, 2,
                                  3, 3, 3, 3, 3, 3, 3, 3>::iv();
    const __m256i bm=const_v32u8< 1, 2, 4, 8, 16, 32, 64, 128,
                                  1, 2, 4, 8, 16, 32, 64, 128,
                                  1, 2, 4, 8, 16, 32, 64, 128,
                                  1, 2, 4, 8, 16, 32, 64, 128>::iv();
    __m256i r=_mm256_set1_epi32(msk32);
    r = _mm256_shuffle_epi8(r, sm);
    r = _mm256_and_si256(r, bm);
    r = _mm256_cmpeq_epi8(r, bm);
    return r;
}

inline
__m256i
cftal::x86::expand_mask_v16u16(uint32_t msk16)
{
    const __m256i bm=const_v16u16< 0x0001, 0x0002, 0x0004, 0x0008,
                                   0x0010, 0x0020, 0x0040, 0x0080,
                                   0x0100, 0x0200, 0x0400, 0x0800,
                                   0x1000, 0x2000, 0x4000, 0x8000>::iv();
    __m256i r=_mm256_set1_epi16(msk16);
    r = _mm256_and_si256(r, bm);
    r = _mm256_cmpeq_epi16(r, bm);
    return r;
}

inline
__m256i
cftal::x86::expand_mask_v8u32(uint32_t msk8)
{
    const __m256i bm=const_v8u32< 1, 2, 4, 8, 16, 32, 64, 128>::iv();
    __m256i r=_mm256_set1_epi32(msk8);
    r = _mm256_and_si256(r, bm);
    r = _mm256_cmpeq_epi32(r, bm);
    return r;
}

inline
__m256i
cftal::x86::expand_mask_v4u64(uint32_t msk4)
{
    const __m256i bm=const_v8u32< 1, 0, 2, 0, 4, 0, 8, 0>::iv();
    __m256i r=_mm256_set1_epi64x(msk4);
    r = _mm256_and_si256(r, bm);
    r = _mm256_cmpeq_epi64(r, bm);
    return r;
}

inline
cftal::uint32_t cftal::x86::read_signs_s8(__m256i a)
{
    return compress_mask_u8(a);
}

inline
cftal::uint32_t cftal::x86::read_signs_s16(__m256i a)
{
    return compress_mask_u16(a);
}

inline
cftal::uint32_t cftal::x86::read_signs_s32(__m256i a)
{
    return compress_mask_u32(a);
}

inline
cftal::uint32_t cftal::x86::read_signs_s64(__m256i a)
{
    return compress_mask_u64(a);
}
#endif

#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
inline
cftal::uint32_t cftal::x86::read_signs_f64(__mmask8 a)
{
    return a & 0xFF;
}
#endif

inline
bool cftal::x86::all_of_f32(__m128 a)
{
#if defined (__AVX__)
    const __m128 msk=  v_sign_v4f32_msk::fv();
    // test if (~a & msk) are all zero
    return _mm_testc_ps(a, msk);
#else
    return compress_mask_f32(a) == 0x0f;
#endif
}

inline
bool cftal::x86::none_of_f32(__m128 a)
{
#if defined (__AVX__)
    const __m128 msk=  v_sign_v4f32_msk::fv();
    // test if (a & msk) are all zero
    return _mm_testz_ps(a, msk);
#else
    return compress_mask_f32(a) == 0x00;
#endif
}

inline
bool cftal::x86::any_of_f32(__m128 a)
{
#if defined (__AVX__)
    const __m128 msk=  v_sign_v4f32_msk::fv();
    // test if (a & msk) are all zero
    return !_mm_testz_ps(a, msk);
#else
    return compress_mask_f32(a) != 0x00;
#endif
}

inline
bool cftal::x86::all_of_f64(__m128d a)
{
#if defined (__AVX__)
    const __m128d msk=  v_sign_v2f64_msk::dv();
    // test if (~a & msk) are all zero
    return _mm_testc_pd(a, msk);
#else
    return compress_mask_f64(a) == 0x03;
#endif
}

inline
bool cftal::x86::none_of_f64(__m128d a)
{
#if defined (__AVX__)
    const __m128d msk=  v_sign_v2f64_msk::dv();
    // test if (a & msk) are all zero
    return _mm_testz_pd(a, msk);
#else
    return compress_mask_f64(a) == 0x00;
#endif
}

inline
bool cftal::x86::any_of_f64(__m128d a)
{
#if defined (__AVX__)
    const __m128d msk=  v_sign_v2f64_msk::dv();
    // test if (a & msk) are all zero
    return !_mm_testz_pd(a, msk);
#else
    return compress_mask_f64(a) != 0x00;
#endif
}

inline
bool cftal::x86::all_of_s8(__m128i a)
{
#if defined (__SSE4_1__)
    const __m128i msk=  v_sign_v16s8_msk::iv();
    // test if (~a & msk) are all zero
    return _mm_testc_si128(a, msk);
#else
    return compress_mask_u8(a) == 0xffff;
#endif
}

inline
bool cftal::x86::none_of_s8(__m128i a)
{
#if defined (__SSE4_1__)
    const __m128i msk=  v_sign_v16s8_msk::iv();
    // test if (a & msk) are all zero
    return _mm_testz_si128(a, msk);
#else
    return compress_mask_u8(a) == 0x0000;
#endif
}

inline
bool cftal::x86::any_of_s8(__m128i a)
{
#if defined (__SSE4_1__)
    const __m128i msk=  v_sign_v16s8_msk::iv();
    // test if (a & msk) are all zero
    return !_mm_testz_si128(a, msk);
#else
    return compress_mask_u8(a) != 0x0000;
#endif
}

inline
bool cftal::x86::all_of_s16(__m128i a)
{
#if defined (__SSE4_1__)
    const __m128i msk=  v_sign_v8s16_msk::iv();
    // test if (~a & msk) are all zero
    return _mm_testc_si128(a, msk);
#else
    return compress_mask_u16(a) == 0xff;
#endif
}

inline
bool cftal::x86::none_of_s16(__m128i a)
{
#if defined (__SSE4_1__)
    const __m128i msk=  v_sign_v8s16_msk::iv();
    // test if (a & msk) are all zero
    return _mm_testz_si128(a, msk);
#else
    return compress_mask_u16(a) == 0x00;
#endif
}

inline
bool cftal::x86::any_of_s16(__m128i a)
{
#if defined (__SSE4_1__)
    const __m128i msk=  v_sign_v8s16_msk::iv();
    // test if (a & msk) are all zero
    return !_mm_testz_si128(a, msk);
#else
    return compress_mask_u16(a) != 0x00;
#endif
}

inline
bool cftal::x86::all_of_s32(__m128i a)
{
#if defined (__SSE4_1__)
    const __m128i msk=  v_sign_v4s32_msk::iv();
    // test if (~a & msk) are all zero
    return _mm_testc_si128(a, msk);
#else
    return compress_mask_u32(a) == 0x0f;
#endif
}

inline
bool cftal::x86::none_of_s32(__m128i a)
{
#if defined (__SSE4_1__)
    const __m128i msk=  v_sign_v4s32_msk::iv();
    // test if (a & msk) are all zero
    return _mm_testz_si128(a, msk);
#else
    return compress_mask_u32(a) == 0x00;
#endif
}

inline
bool cftal::x86::any_of_s32(__m128i a)
{
#if defined (__SSE4_1__)
    const __m128i msk=  v_sign_v4s32_msk::iv();
    // test if (a & msk) are all zero
    return !_mm_testz_si128(a, msk);
#else
    return compress_mask_u32(a) != 0x00;
#endif
}

inline
bool cftal::x86::all_of_s64(__m128i a)
{
#if defined (__SSE4_1__)
    const __m128i msk=  v_sign_v2s64_msk::iv();
    // test if (~a & msk) are all zero
    return _mm_testc_si128(a, msk);
#else
    return compress_mask_u64(a) == 0x03;
#endif
}


inline
bool cftal::x86::none_of_s64(__m128i a)
{
#if defined (__SSE4_1__)
    const __m128i msk=  v_sign_v2s64_msk::iv();
    // test if (a & msk) are all zero
    return _mm_testz_si128(a, msk);
#else
    return compress_mask_u64(a) == 0x00;
#endif
}

inline
bool cftal::x86::any_of_s64(__m128i a)
{
#if defined (__SSE4_1__)
    const __m128i msk=  v_sign_v2s64_msk::iv();
    // test if (a & msk) are all zero
    return !_mm_testz_si128(a, msk);
#else
    return compress_mask_u64(a) != 0x00;
#endif
}

#if defined (__AVX__)
inline
bool cftal::x86::all_of_f32(__m256 a)
{
    const __m256 msk= _mm256_set1_ps(sign_f32_msk::v.f32());
    // test if (~a & msk) are all zero
    return _mm256_testc_ps(a, msk);
}

inline
bool cftal::x86::none_of_f32(__m256 a)
{
    const __m256 msk= _mm256_set1_ps(sign_f32_msk::v.f32());
    // test if (a & msk) are all zero
    return _mm256_testz_ps(a, msk);
}

inline
bool cftal::x86::any_of_f32(__m256 a)
{
    const __m256 msk= _mm256_set1_ps(sign_f32_msk::v.f32());
    // test if (a & msk) are all zero
    return !_mm256_testz_ps(a, msk);
}

inline
bool cftal::x86::all_of_f64(__m256d a)
{
    const __m256d msk= _mm256_set1_pd(sign_f64_msk::v.f64());
    // test if (~a & msk) are all zero
    return _mm256_testc_pd(a, msk);
}

inline
bool cftal::x86::none_of_f64(__m256d a)
{
    const __m256d msk= _mm256_set1_pd(sign_f64_msk::v.f64());
    // test if (a & msk) are all zero
    return _mm256_testz_pd(a, msk);
}

inline
bool cftal::x86::any_of_f64(__m256d a)
{
    const __m256d msk= _mm256_set1_pd(sign_f64_msk::v.f64());
    // test if (a & msk) are all zero
    return !_mm256_testz_pd(a, msk);
}
#endif

#if defined (__AVX2__)

inline
bool cftal::x86::all_of_s8(__m256i a)
{
    const __m256i msk= _mm256_set1_epi32(sign_s8_msk::v.u32());
    // test if (~a & msk) are all zero
    return _mm256_testc_si256(a, msk);
}

inline
bool cftal::x86::none_of_s8(__m256i a)
{
    const __m256i msk= _mm256_set1_epi32(sign_s8_msk::v.u32());
    // test if (a & msk) are all zero
    return _mm256_testz_si256(a, msk);
}

inline
bool cftal::x86::any_of_s8(__m256i a)
{
    const __m256i msk= _mm256_set1_epi32(sign_s8_msk::v.u32());
    // test if (a & msk) are all zero
    return !_mm256_testz_si256(a, msk);
}

inline
bool cftal::x86::all_of_s16(__m256i a)
{
    const __m256i msk= _mm256_set1_epi16(sign_s16_msk::v.u16());
    // test if (~a & msk) are all zero
    return _mm256_testc_si256(a, msk);
}

inline
bool cftal::x86::none_of_s16(__m256i a)
{
    const __m256i msk= _mm256_set1_epi16(sign_s16_msk::v.u16());
    // test if (a & msk) are all zero
    return _mm256_testz_si256(a, msk);
}

inline
bool cftal::x86::any_of_s16(__m256i a)
{
    const __m256i msk= _mm256_set1_epi16(sign_s16_msk::v.u16());
    // test if (a & msk) are all zero
    return !_mm256_testz_si256(a, msk);
}

inline
bool cftal::x86::all_of_s32(__m256i a)
{
    const __m256i msk= _mm256_set1_epi32(sign_s32_msk::v.u32());
    // test if (~a & msk) are all zero
    return _mm256_testc_si256(a, msk);
}

inline
bool cftal::x86::none_of_s32(__m256i a)
{
    const __m256i msk= _mm256_set1_epi32(sign_s32_msk::v.u32());
    // test if (a & msk) are all zero
    return _mm256_testz_si256(a, msk);
}

inline
bool cftal::x86::any_of_s32(__m256i a)
{
    const __m256i msk= _mm256_set1_epi32(sign_s32_msk::v.u32());
    // test if (a & msk) are all zero
    return !_mm256_testz_si256(a, msk);
}

inline
bool cftal::x86::all_of_s64(__m256i a)
{
    const __m256i msk= _mm256_set1_epi64x(sign_s64_msk::v.u64());
    // test if (~a & msk) are all zero
    return _mm256_testc_si256(a, msk);
}

inline
bool cftal::x86::none_of_s64(__m256i a)
{
    const __m256i msk= _mm256_set1_epi64x(sign_s64_msk::v.u64());
    // test if (a & msk) are all zero
    return _mm256_testz_si256(a, msk);
}

inline
bool cftal::x86::any_of_s64(__m256i a)
{
    const __m256i msk= _mm256_set1_epi64x(sign_s64_msk::v.u64());
    // test if (a & msk) are all zero
    return !_mm256_testz_si256(a, msk);
}
#endif

inline __m128i cftal::x86::popcnt_u8(__m128i a)
{
    const __m128i c0f=x86::v_uint8_0x0f::iv();
#if defined (__SSSE3__)
    // lookup table based approach
    // bits set
    const __m128i lookup= x86::const_v16u8< 0, 1, 1, 2, 1, 2, 2, 3,
                                            1, 2, 2, 3, 2, 3, 3, 4>::iv();
    __m128i h= _mm_srli_epi16(a, 4);
    // low nibbles
    a = _mm_and_si128(a, c0f);
    // high nibbles
    h = _mm_and_si128(h, c0f);
    // lookup
    a = _mm_shuffle_epi8(lookup, a);
    h = _mm_shuffle_epi8(lookup, h);
    // produce result
    return _mm_add_epi8(a, h);
#else
    // bit slicing algorithm.
    // a = a - ((a >> 1) & 0x55555555);
    // a = (a & 0x33333333) + ((a >> 2) & 0x33333333);
    // a = (a + (a >> 4)) & 0x0F0F0F0F;
    const __m128i c55= x86::v_uint8_0x55::iv();
    const __m128i c33= x86::v_uint8_0x33::iv();
    // combine pairs of 1 bits
    __m128i b= _mm_srli_epi16(a, 1);
    b = _mm_and_si128(b, c55);
    a = _mm_sub_epi16(a, b);
    // combine pairs of 2 bits
    b= _mm_srli_epi16(a, 2);
    a= _mm_and_si128(a, c33);
    b= _mm_and_si128(b, c33);
    a= _mm_add_epi16(a, b);
    // combine pairs of 4 bits
    b= _mm_srli_epi16(a, 4);
    a= _mm_add_epi16(a, b);
    return _mm_and_si128(a, c0f);
#endif
}

inline __m128i cftal::x86::popcnt_u16(__m128i a)
{
#if defined (__SSSE3__)
    const __m128i msk= v_uint8_0x01::iv();
    return _mm_maddubs_epi16(popcnt_u8(a), msk);
#else
    a = popcnt_u8(a);
    const __m128i msk= x86::v_uint16_0x00ff::iv();
    __m128i t= _mm_srli_epi16(a, 8);
    a = _mm_and_si128(a, msk);
    return _mm_add_epi16(a, t);
#endif
}

inline __m128i cftal::x86::popcnt_u32(__m128i a)
{
    const __m128i msk= v_uint16_0x0001::iv();
    return _mm_madd_epi16(popcnt_u16(a), msk);
}

inline __m128i cftal::x86::popcnt_u64(__m128i a)
{
    a= popcnt_u8(a);
    return _mm_sad_epu8(a, make_zero_int::v());
}

inline int cftal::x86::popcnt_u128(__m128i a)
{
    a= popcnt_u64(a);
    const int sm= shuffle4<2,3,1,0>::val;
    __m128i t= _mm_shuffle_epi32(a, sm & 0xff);
    t = _mm_add_epi32(t, a);
    return _mm_cvtsi128_si32(t);
}

inline __m128i cftal::x86::bitrev_u8(__m128i a)
{
    // AMD XOP: use pperm
    // bitrev algorithm
    // swap odd and even bits
    // v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
    const __m128i c55= v_uint8_0x55::iv();
    __m128i t= vpsrlw_const<1>::v(a);
    a = _mm_and_si128(a, c55);
    t = _mm_and_si128(t, c55);
    a = vpsllw_const<1>::v(a);
    a = _mm_or_si128(a, t);
    // swap consecutive pairs
    // v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
    const __m128i c33= v_uint8_0x33::iv();
    t = vpsrlw_const<2>::v(a);
    a = _mm_and_si128(a, c33);
    t = _mm_and_si128(t, c33);
    a = vpsllw_const<2>::v(a);
    a = _mm_or_si128(a, t);
    // swap nibbles ...
    // v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
    const __m128i c0f= v_uint8_0x0f::iv();
    t = vpsrlw_const<4>::v(a);
    a = _mm_and_si128(a, c0f);
    t = _mm_and_si128(t, c0f);
    a = vpsllw_const<4>::v(a);
    a = _mm_or_si128(a, t);
    return a;
    // swap bytes
    // v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
    // swap 2-byte long pairs
    // v = ( v >> 16             ) | ( v               << 16);
}

inline __m128i cftal::x86::bitrev_u16(__m128i a)
{
    // AMD XOP: use pperm
#if defined (__SSSE3__)
    const __m128i msk = const_v16u8< 1, 0, 3, 2, 5, 4, 7, 6,
                                     9, 8,11,10,13,12,15,14>::iv();
    a = bitrev_u8(a);
    return _mm_shuffle_epi8(a, msk);
#else
    // swap bytes
    // v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
    a = bitrev_u8(a);
    __m128i t= vpsrlw_const<8>::v(a);
    a = vpsllw_const<8>::v(a);
    return _mm_or_si128(a, t);
#endif
}

inline __m128i cftal::x86::bitrev_u32(__m128i a)
{
    // AMD XOP: use pperm
#if defined (__SSSE3__)
    const __m128i msk = const_v16u8<3, 2, 1, 0, 7, 6, 5, 4,
                                    11,10, 9, 8,15,14,13,12>::iv();
    a = bitrev_u8(a);
    return _mm_shuffle_epi8(a, msk);
#else
    a = bitrev_u16(a);
    // swap 2-byte long pairs
    // v = ( v >> 16             ) | ( v               << 16);
    __m128i t= vpsrld_const<16>::v(a);
    a= vpslld_const<16>::v(a);
    return _mm_or_si128(a, t);
#endif
}

inline __m128i cftal::x86::bitrev_u64(__m128i a)
{
    // AMD XOP: use pperm
#if defined (__SSSE3__)
    const __m128i msk = const_v16u8<7, 6, 5, 4, 3, 2, 1, 0,
                                    15,14,13,12,11,10,9, 8>::iv();
    a = bitrev_u8(a);
    return _mm_shuffle_epi8(a, msk);
#else
    // swap unsigned pairs
    // v = ( v >> 32             ) | ( v               << 32);
    a = bitrev_u32(a);
    return vpshufd<1, 0, 3, 2>::v(a);
#endif
}

// Local variables:
// mode: c++
// end:
#endif
