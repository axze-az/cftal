//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_X86_INS_EXT_H__)
#define __CFTAL_X86_INS_EXT_H__ 1

#include <cftal/config.h>
#include <cftal/x86/intrin.h>
#include <cftal/x86/select.h>
#include <cftal/x86/cast_bits.h>

namespace cftal {
    namespace x86 {

        using u_v2x64 = vecunion<int64_t, 2, __m128, __m128d, __m128i>;
        using u_v4x32 = vecunion<int32_t, 4, __m128, __m128d, __m128i>;
        using u_v8x16 = vecunion<int16_t, 8, __m128, __m128d, __m128i>;
        using u_v16x8 = vecunion<int8_t, 16, __m128, __m128d, __m128i>;

        extern const u_v2x64 ins_msk_v2x64[2];
        extern const u_v4x32 ins_msk_v4x32[4];
        extern const u_v8x16 ins_msk_v8x16[8];
        extern const u_v16x8 ins_msk_v16x8[16];

        // extract/insert float
        template <unsigned _IDX>
        float extract_f32(__m128 r);
        template <unsigned _IDX>
        __m128 insert_f32(__m128 r, float v);

        float extract_f32(__m128 r, size_t i);
        __m128 insert_f32(__m128 r, float v, size_t i);

        // extract/insert double
        template <unsigned _IDX>
        double extract_f64(__m128d r);
        template <unsigned _IDX>
        __m128d insert_f64(__m128d r, double v);

        double extract_f64(__m128d r, size_t i);
        __m128d insert_f64(__m128d r, double v, size_t i);

        // extract/insert uint8_t
        template <unsigned _IDX>
        uint8_t extract_u8(__m128i v);
        template <unsigned _IDX>
        __m128i insert_u8(__m128i r, uint8_t v);

        uint8_t extract_u8(__m128i r, size_t i);
        __m128i insert_u8(__m128i r, uint8_t v, size_t i);

        // extract/insert uint16_t
        template <unsigned _IDX>
        uint16_t extract_u16(__m128i v);
        template <unsigned _IDX>
        __m128i insert_u16(__m128i r, uint16_t v);

        uint16_t extract_u16(__m128i r, size_t i);
        __m128i insert_u16(__m128i r, uint16_t v, size_t i);

        // extract/insert uint32_t
        template <unsigned _IDX>
        uint32_t extract_u32(__m128i v);
        template <unsigned _IDX>
        __m128i insert_u32(__m128i r, uint32_t v);

        uint32_t extract_u32(__m128i r, size_t i);
        __m128i insert_u32(__m128i r, uint32_t v, size_t i);

        // extract/insert uint64_t
        template <unsigned _IDX>
        uint64_t extract_u64(__m128i v);
        template <unsigned _IDX>
        __m128i insert_u64(__m128i r, uint64_t v);

        uint64_t extract_u64(__m128i r, size_t i);
        __m128i insert_u64(__m128i r, uint64_t v, size_t i);

#if defined (__AVX__)

        using u_v4x64 = vecunion<int64_t, 4, __m256, __m256d, __m256i>;
        using u_v8x32 = vecunion<int32_t, 8, __m256, __m256d, __m256i>;

        extern const u_v4x64 ins_msk_v4x64[4];
        extern const u_v8x32 ins_msk_v8x32[8];

        // extract insert f32
        template <unsigned _IDX>
        float extract_f32(__m256 r);
        template <unsigned _IDX>
        __m256 insert_f32(__m256 r, float v);

        float extract_f32(__m256 r, size_t i);
        __m256 insert_f32(__m256 r, float v, size_t i);

        // extract insert f64
        template <unsigned _IDX>
        double extract_f64(__m256d r);
        template <unsigned _IDX>
        __m256d insert_f64(__m256d r, double v);

        double extract_f64(__m256d r, size_t i);
        __m256d insert_f64(__m256d r, double v, size_t i);
#endif
#if defined (__AVX2__)
        // extract/insert uint32_t
        template <unsigned _IDX>
        uint32_t extract_u32(__m256i v);
        template <unsigned _IDX>
        __m256i insert_u32(__m256i r, uint32_t v);

        uint32_t extract_u32(__m256i r, size_t i);
        __m256i insert_u32(__m256i r, uint32_t v, size_t i);

        // extract/insert uint64_t
        template <unsigned _IDX>
        uint64_t extract_u64(__m256i v);
        template <unsigned _IDX>
        __m256i insert_u64(__m256i r, uint64_t v);

        uint64_t extract_u64(__m256i r, size_t i);
        __m256i insert_u64(__m256i r, uint64_t v, size_t i);
#endif
    }
}


template <unsigned _IDX>
inline
float cftal::x86::extract_f32(__m128 v)
{
    const bool cond = _IDX < 4;
    static_assert(cond, "cftal::x86::extract_f32 _IDX < 4");
    float r;
    switch (_IDX) {
    case 0:
        r = _mm_cvtss_f32(v);
        break;
    case 1: {
        static const int m= shuffle4<1, 1, 1, 1>::val;
        r = _mm_cvtss_f32(_mm_shuffle_ps(v, v, m & 0x0f));
        break;
    }
    case 2:
        r =_mm_cvtss_f32(_mm_unpackhi_ps(v, v));
        break;
    case 3: {
        static const int m= shuffle4<3, 3, 3, 3>::val;
        r = _mm_cvtss_f32(_mm_shuffle_ps(v, v, m & 0x0f));
    }
        break;
    }
    return r;
}

template <unsigned _IDX>
inline
__m128 cftal::x86::insert_f32(__m128 v, float f)
{
    const bool cond = _IDX < 4;
    static_assert(cond, "cftal::x86::insert_f32 _IDX < 4");
    __m128 r, t;
    t = _mm_set1_ps(f);
    switch (_IDX) {
    case 0:
        r = _mm_move_ss(v, t);
        break;
    case 1:
        r= select_f32<0,1,0,0>(t, v);
        break;
    case 2:
        r= select_f32<0,0,1,0>(t, v);
        break;
    case 3:
        r= select_f32<0,0,0,1>(t, v);
        break;
    }
    return r;
}

inline
float cftal::x86::extract_f32(__m128 v, size_t i)
{
#if defined (__SSSE3__)
    int32_t ii= ((int32_t(i) & 3) * 0x04040404) + 0x03020100;
    // __m128i msk=_mm_set1_epi32(ii);
    __m128i msk=_mm_cvtsi32_si128(ii);
    __m128i ri= _mm_shuffle_epi8(as<__m128i>(v), msk);
    return _mm_cvtss_f32(as<__m128>(ri));
#else
    float r;
    switch (i & 3) {
    case 0:
        r=extract_f32<0>(v);
        break;
    case 1:
        r=extract_f32<1>(v);
        break;
    case 2:
        r=extract_f32<2>(v);
        break;
    case 3:
        r=extract_f32<3>(v);
        break;
    }
    return r;
#endif
}

inline
__m128 cftal::x86::insert_f32(__m128 v, float f, size_t i)
{
    __m128 vf=_mm_set1_ps(f);
    const __m128 msk=ins_msk_v4x32[i&3]._vf;
    return select_f32(msk, vf, v);
}

template <unsigned _IDX>
inline
double cftal::x86::extract_f64(__m128d v)
{
    const bool cond = _IDX < 2;
    static_assert(cond, "cftal::x86::extract_f64 _IDX < 2");
    double r;
    switch (_IDX) {
    case 0:
        r = _mm_cvtsd_f64(v);
        break;
    case 1:
        r = _mm_cvtsd_f64(_mm_unpackhi_pd(v, v));
        break;
    }
    return r;
}

template <unsigned _IDX>
inline
__m128d cftal::x86::insert_f64(__m128d v, double d)
{
    const bool cond = _IDX < 2;
    static_assert(cond, "cftal::x86::insert_f64 _IDX < 2");
    double vv;
    __m128d r;
    switch (_IDX) {
    case 0:
        vv = extract_f64<1>(v);
        r = _mm_set_pd(vv, d);
        break;
    case 1:
        vv = extract_f64<0>(v);
        r = _mm_set_pd(d, vv);
        break;
    }
    return r;
}

inline
double cftal::x86::extract_f64(__m128d v, size_t i)
{
#if defined (__SSSE3__)
    int64_t ii= ((int64_t(i) & 1) * 0x0808080808080808LL) +
        0x0706050403020100LL;
    // __m128i msk=_mm_set1_epi64x(ii);
    __m128i msk=_mm_cvtsi64_si128(ii);        
    __m128i ri= _mm_shuffle_epi8(as<__m128i>(v), msk);
    return _mm_cvtsd_f64(as<__m128d>(ri));
#else
    double r;
    switch (i & 1) {
    case 0:
        r=extract_f64<0>(v);
        break;
    case 1:
        r=extract_f64<1>(v);
        break;
    }
    return r;
#endif
}

inline
__m128d cftal::x86::insert_f64(__m128d v, double d, size_t i)
{
    __m128d vf=_mm_set1_pd(d);
    const __m128d msk=ins_msk_v2x64[i&1]._vd;
    return select_f64(msk, vf, v);
}

template <unsigned _IDX>
inline
uint8_t cftal::x86::extract_u8(__m128i v) {
    const bool cond = _IDX < 16;
    static_assert(cond, "cftal::x86::extract_u8 _IDX < 16");
#if defined (__SSE4_1__)
    return _mm_extract_epi8(v, _IDX);
#else
    uint32_t t = _mm_extract_epi16(v, _IDX/2);
    if (_IDX & 1)
        t >>= 8;
    else
        t &= 0xFF;
    return t;
#endif
}

template <unsigned _IDX>
inline
__m128i cftal::x86::insert_u8(__m128i v, uint8_t i)
{
    const bool cond = _IDX < 16;
    static_assert(cond, "cftal::x86::insert_u8 _IDX < 16");
#if defined (__SSE4_1__)
    return _mm_insert_epi8(v, i, _IDX);
#else
    uint32_t t = _mm_extract_epi16(v, _IDX/2);
    if (_IDX & 1) {
        uint32_t val = i;
        val <<= 8;
        t = select(0xFF, t, val);
    } else {
        uint32_t val = i;
        t = select(0xFF, val, t);
    }
    return _mm_insert_epi16(v, t, _IDX/2);
#endif
}

inline
std::uint8_t cftal::x86::extract_u8(__m128i v, size_t i)
{
#if defined (__SSSE3__)
    int32_t ii= (int32_t(i) & 15);
    // __m128i msk=_mm_set1_epi32(ii);
    __m128i msk=_mm_cvtsi32_si128(ii);
    __m128i ri= _mm_shuffle_epi8(v, msk);
    return _mm_cvtsi128_si32(ri) & 0xf;
#else
    uint8_t r;
    switch (i & 0xf) {
    case 0:
        r=extract_u8<0>(v);
        break;
    case 1:
        r=extract_u8<1>(v);
        break;
    case 2:
        r=extract_u8<2>(v);
        break;
    case 3:
        r=extract_u8<3>(v);
        break;
    case 4:
        r=extract_u8<4>(v);
        break;
    case 5:
        r=extract_u8<5>(v);
        break;
    case 6:
        r=extract_u8<6>(v);
        break;
    case 7:
        r=extract_u8<7>(v);
        break;
    case 8:
        r=extract_u8<8>(v);
        break;
    case 9:
        r=extract_u8<9>(v);
        break;
    case 10:
        r=extract_u8<10>(v);
        break;
    case 11:
        r=extract_u8<11>(v);
        break;
    case 12:
        r=extract_u8<12>(v);
        break;
    case 13:
        r=extract_u8<13>(v);
        break;
    case 14:
        r=extract_u8<14>(v);
        break;
    case 15:
        r=extract_u8<15>(v);
        break;
    }
    return r;
#endif
}

inline
__m128i
cftal::x86::insert_u8(__m128i v, uint8_t f, size_t i)
{
    __m128i vf=_mm_set1_epi16(f);
    const __m128i msk=ins_msk_v16x8[i & 0xf]._vi;
    return select_u8(msk, vf, v);
}

template <unsigned _IDX>
inline
uint16_t cftal::x86::extract_u16(__m128i v) {
    const bool cond = _IDX < 8;
    static_assert(cond, "cftal::x86::extract_u16 _IDX < 8");
    return _mm_extract_epi16(v, _IDX);
}

template <unsigned _IDX>
inline
__m128i cftal::x86::insert_u16(__m128i v, uint16_t i)
{
    const bool cond = _IDX < 16;
    static_assert(cond, "cftal::x86::insert_u16 _IDX < 16");
    return _mm_insert_epi16(v, i, _IDX);
}

inline
std::uint16_t cftal::x86::extract_u16(__m128i v, size_t i)
{
#if defined (__SSSE3__)
    int32_t ii= ((int32_t(i) & 7) * 0x0202) + 0x100;
    // __m128i msk=_mm_set1_epi32(ii);
    __m128i msk=_mm_cvtsi32_si128(ii);
    __m128i ri= _mm_shuffle_epi8(v, msk);
    return _mm_cvtsi128_si32(ri) & 0xff;
#else
    uint32_t r;
    switch (i & 7) {
    case 0:
        r=extract_u16<0>(v);
        break;
    case 1:
        r=extract_u16<1>(v);
        break;
    case 2:
        r=extract_u16<2>(v);
        break;
    case 3:
        r=extract_u16<3>(v);
        break;
    case 4:
        r=extract_u16<4>(v);
        break;
    case 5:
        r=extract_u16<5>(v);
        break;
    case 6:
        r=extract_u16<6>(v);
        break;
    case 7:
        r=extract_u16<7>(v);
        break;
    }
    return r;
#endif
}

inline
__m128i
cftal::x86::insert_u16(__m128i v, uint16_t f, size_t i)
{
    __m128i vf=_mm_set1_epi16(f);
    const __m128i msk=ins_msk_v8x16[i&7]._vi;
    return select_u16(msk, vf, v);
}

template <unsigned _IDX>
inline
uint32_t cftal::x86::extract_u32(__m128i v)
{
    const bool cond = _IDX < 4;
    static_assert(cond, "cftal::x86::extract_u32 _IDX < 4");
    uint32_t r;
    if (_IDX==0) {
        r = _mm_cvtsi128_si32(v);
    } else {
#if defined (__SSE4_1__)
        r = _mm_extract_epi32(v,_IDX);
#else
        v = _mm_srli_si128(v, _IDX*4);
        r = _mm_cvtsi128_si32(v);
#endif
    }
    return r;
}

template <unsigned _IDX>
inline
__m128i cftal::x86::insert_u32(__m128i v, uint32_t i)
{
    const bool cond = _IDX < 4;
    static_assert(cond, "cftal::x86::insert_u32 _IDX < 4");
#if defined (__SSE4_1__)
    return _mm_insert_epi32(v, i, _IDX);
#else
    __m128i t= _mm_cvtsi32_si128(i);
    __m128i r;
    switch (_IDX) {
    case 0:
        r = select_u32<1,0,0,0>(t, v);
        break;
    case 1:
        t = _mm_slli_si128(v, 4);
        r = select_u32<0,1,0,0>(t, v);
        break;
    case 2:
        t = _mm_slli_si128(v, 8);
        r = select_u32<0,0,1,0>(t, v);
        break;
    case 3:
        t = _mm_slli_si128(v, 12);
        r = select_u32<0,0,0,1>(t, v);
        break;
    }
    return r;
#endif
}

inline
std::uint32_t cftal::x86::extract_u32(__m128i v, size_t i)
{
#if defined (__SSSE3__)
    int32_t ii= ((int32_t(i) & 3) * 0x04040404) + 0x03020100;
    // __m128i msk=_mm_set1_epi32(ii);
    __m128i msk=_mm_cvtsi32_si128(ii);
    __m128i ri= _mm_shuffle_epi8(v, msk);
    return _mm_cvtsi128_si32(ri);
#else
    uint32_t r;
    switch (i & 3) {
    case 0:
        r=extract_u32<0>(v);
        break;
    case 1:
        r=extract_u32<1>(v);
        break;
    case 2:
        r=extract_u32<2>(v);
        break;
    case 3:
        r=extract_u32<3>(v);
        break;
    }
    return r;
#endif
}

inline
__m128i
cftal::x86::insert_u32(__m128i v, uint32_t f, size_t i)
{
    __m128i vf=_mm_set1_epi32(f);
    const __m128i msk=ins_msk_v4x32[i&3]._vi;
    return select_u32(msk, vf, v);
}

template <unsigned _IDX>
inline
uint64_t cftal::x86::extract_u64(__m128i v) {
    const bool cond = _IDX < 2;
    static_assert(cond, "cftal::x86::extract_u64 _IDX < 2");
    uint64_t r;
#if defined (__x86_64__)
    // 64 bit code
    if (_IDX==0) {
        r = _mm_cvtsi128_si64(v);
    } else {
#if defined (__SSE4_1__)
        r= _mm_extract_epi64(v, _IDX);
#else
        v= _mm_unpackhi_epi64(v, v);
        r= _mm_cvtsi128_si64(v);
#endif
    }
#else
    // 32 bit code
    uint32_t l, h;
    if (_IDX==0) {
        l = _mm_cvtsi128_si32(v);
#if defined (__SSE4_1__)
        h = _mm_extract_epi32(v, 1);
#else
        v = _mm_srli_si128(v, 4);
        h = _mm_cvtsi128_si32(v);
#endif
    } else {
#if defined (__SSE4_1__)
        l = _mm_extract_epi32(v, 2);
        h = _mm_extract_epi32(v, 3);
#else
        __m128i hv = _mm_srli_si128(v, 12);
        __m128i lv = _mm_srli_si128(v, 8);
        l = _mm_cvtsi128_si32(lv);
        h = _mm_cvtsi128_si32(hv);
#endif
    }
    r = (uint64_t(h) << 32) | l;
#endif
    return r;
}

template <unsigned _IDX>
inline
__m128i cftal::x86::insert_u64(__m128i v, uint64_t i)
{
    const bool cond = _IDX < 2;
    static_assert(cond, "cftal::x86::insert_u64_IDX < 2");
    __m128i r;
#if defined (__SSE4_1__)
    // SSE4.1
#if defined (__x86_64__)
    r = _mm_insert_epi64(v, i, _IDX);
#else
    r = _mm_insert_epi32(v, i, _IDX*2);
    r = _mm_insert_epi32(r, i>>32, _IDX*2+1);
#endif
#else
    // SSE2
    __m128i t;
#if defined (__x86_64__)
    t= _mm_cvtsi64_si128(i);
#else
    __m128i t1 = _mm_cvtsi32_si128(i>>32);
    t = _mm_cvtsi32_si128(i);
    t = _mm_unpacklo_epi32(t, t1);
#endif
    if (_IDX==0) {
        __m128d dt, dv, dr;
        dt = as<__m128d>(t);
        dv = as<__m128d>(v);
        dr = _mm_move_sd(dv, dt);
        r = as<__m128i>(dr);
    } else {
        r = _mm_unpacklo_epi64(v, t);
    }
#endif
    return r;
}

inline
std::uint64_t cftal::x86::extract_u64(__m128i v, size_t i)
{
#if defined (__SSSE3__)
    int64_t ii= ((int64_t(i) & 1) * 0x0808080808080808LL) +
        0x0706050403020100LL;
    // __m128i msk=_mm_set1_epi64x(ii);
    __m128i msk=_mm_cvtsi64_si128(ii);
    __m128i ri= _mm_shuffle_epi8(v, msk);
    return _mm_cvtsi128_si64(ri);
#else
    uint64_t r;
    switch (i & 1) {
    case 0:
        r=extract_u64<0>(v);
        break;
    case 1:
        r=extract_u64<1>(v);
        break;
    }
    return r;
#endif
}

inline
__m128i cftal::x86::insert_u64(__m128i v, uint64_t d, size_t i)
{
    __m128i vf=_mm_set1_epi64x(d);
    const __m128i msk=ins_msk_v2x64[i&1]._vi;
    return select_u64(msk, vf, v);
}

#if defined (__AVX__)

template <unsigned _IDX>
inline
float cftal::x86::extract_f32(__m256 v)
{
    const bool cond = _IDX < 8;
    static_assert(cond, "cftal::x86::extract_f32 _IDX < 8");
    __m128 vv;
    if (_IDX<4) {
        vv = as<__m128>(v);
    } else {
        vv = _mm256_extractf128_ps(v, 1);
    }
    return extract_f32<_IDX&3>(vv);
}

template <unsigned _IDX>
inline
__m256 cftal::x86::insert_f32(__m256 v, float d)
{
    const bool cond = _IDX < 8;
    static_assert(cond, "cftal::x86::insert_f32 _IDX < 4");
    __m256 r = v;
    __m256 vv;
    vv = _mm256_set1_ps(d);
    switch (_IDX) {
    case 0:
        r= select_f32<1, 0, 0, 0, 0, 0, 0, 0>(vv, r);
        break;
    case 1:
        r= select_f32<0, 1, 0, 0, 0, 0, 0, 0>(vv, r);
        break;
    case 2:
        r= select_f32<0, 0, 1, 0, 0, 0, 0, 0>(vv, r);
        break;
    case 3:
        r= select_f32<0, 0, 0, 1, 0, 0, 0, 0>(vv, r);
        break;
    case 4:
        r= select_f32<0, 0, 0, 0, 1, 0, 0, 0>(vv, r);
        break;
    case 5:
        r= select_f32<0, 0, 0, 0, 0, 1, 0, 0>(vv, r);
        break;
    case 6:
        r= select_f32<0, 0, 0, 0, 0, 0, 1, 0>(vv, r);
        break;
    case 7:
        r= select_f32<0, 0, 0, 0, 0, 0, 0, 1>(vv, r);
        break;
    }
    return r;
}

inline
float cftal::x86::extract_f32(__m256 v, size_t i)
{
#if defined (__AVX2__)
    // const __m256i msk= _mm256_set1_epi32( i & 7);
    const __m256i msk=_mm256_castsi128_si256(_mm_cvtsi32_si128(i & 7));
    __m256 r=_mm256_permutevar8x32_ps(v, msk);
    __m128 rh=_mm256_castps256_ps128(r);
    return _mm_cvtss_f32(rh);
#else
    __m128 vv;
    if (i<4) {
        vv = as<__m128>(v);
    } else {
        vv = _mm256_extractf128_ps(v, 1);
    }
    return extract_f32(vv, i);
#endif
}

inline
__m256 cftal::x86::insert_f32(__m256 v, float f, size_t i)
{
    __m256 vf=_mm256_set1_ps(f);
    const __m256 msk=ins_msk_v8x32[i&7]._vf;
    return select_f32(msk, vf, v);
}

template <unsigned _IDX>
inline
double cftal::x86::extract_f64(__m256d v)
{
    const bool cond = _IDX < 4;
    static_assert(cond, "cftal::x86::extract_f64 _IDX < 4");
    __m128d vv;
    if (_IDX<2) {
        vv = as<__m128d>(v);
    } else {
        vv = _mm256_extractf128_pd(v, 1);
    }
    return extract_f64<_IDX&1>(vv);
}

template <unsigned _IDX>
inline
__m256d cftal::x86::insert_f64(__m256d v, double d)
{
    const bool cond = _IDX < 4;
    static_assert(cond, "cftal::x86::insert_f64 _IDX < 4");
    __m256d r = v;
    __m256d vv;
    vv = _mm256_set1_pd(d);
    switch (_IDX) {
    case 0:
        r= select_f64<1, 0, 0, 0>(vv, r);
        break;
    case 1:
        r= select_f64<0, 1, 0, 0>(vv, r);
        break;
    case 2:
        r= select_f64<0, 0, 1, 0>(vv, r);
        break;
    case 3:
        r= select_f64<0, 0, 0, 1>(vv, r);
        break;
    }
    return r;
}

inline
double cftal::x86::extract_f64(__m256d v, size_t i)
{
#if defined (__AVX2__)
    size_t ii= ((i & 3) * 0x200000002LL) + 0x100000000LL;
    // const __m256i msk= _mm256_set1_epi64x(ii);
    const __m256i msk=_mm256_castsi128_si256(_mm_cvtsi64_si128(ii));
    __m256 r=_mm256_permutevar8x32_ps(_mm256_castpd_ps(v), msk);
    __m128 rh=_mm256_castps256_ps128(r);
    return _mm_cvtsd_f64(as<__m128d>(rh));
#else
    __m128d vv;
    if (i<4) {
        vv = as<__m128d>(v);
    } else {
        vv = _mm256_extractf128_pd(v, 1);
    }
    return extract_f64(vv, i&1);
#endif
}

inline
__m256d cftal::x86::insert_f64(__m256d v, double d, size_t i)
{
    __m256d vf=_mm256_set1_pd(d);
    const __m256d msk=ins_msk_v4x64[i&3]._vd;
    return select_f64(msk, vf, v);
}

#endif

#if defined (__AVX2__)
template <unsigned _IDX>
inline
cftal::uint32_t cftal::x86::extract_u32(__m256i v)
{
    const bool cond = _IDX < 8;
    static_assert(cond, "cftal::x86::extract_u32 _IDX < 8");
    __m128i vv;
    if (_IDX<4) {
        vv = as<__m128i>(v);
    } else {
        vv = _mm256_extracti128_si256(v, 1);
    }
    return extract_u32<_IDX&3>(vv);
}


template <unsigned _IDX>
inline
__m256i cftal::x86::insert_u32(__m256i v, uint32_t d)
{
    const bool cond = _IDX < 8;
    static_assert(cond, "cftal::x86::insert_u32 _IDX < 4");
    __m256i r = v;
    __m256i vv;
    vv = _mm256_set1_epi32(d);
    switch (_IDX) {
    case 0:
        r= select_u32<1, 0, 0, 0, 0, 0, 0, 0>(vv, r);
        break;
    case 1:
        r= select_u32<0, 1, 0, 0, 0, 0, 0, 0>(vv, r);
        break;
    case 2:
        r= select_u32<0, 0, 1, 0, 0, 0, 0, 0>(vv, r);
        break;
    case 3:
        r= select_u32<0, 0, 0, 1, 0, 0, 0, 0>(vv, r);
        break;
    case 4:
        r= select_u32<0, 0, 0, 0, 1, 0, 0, 0>(vv, r);
        break;
    case 5:
        r= select_u32<0, 0, 0, 0, 0, 1, 0, 0>(vv, r);
        break;
    case 6:
        r= select_u32<0, 0, 0, 0, 0, 0, 1, 0>(vv, r);
        break;
    case 7:
        r= select_u32<0, 0, 0, 0, 0, 0, 0, 1>(vv, r);
        break;
    }
    return r;
}

inline
std::uint32_t cftal::x86::extract_u32(__m256i v, size_t i)
{
#if defined (__AVX2__)
    // const __m256i msk= _mm256_set1_epi32( i & 7);
    const __m256i msk=_mm256_castsi128_si256(_mm_cvtsi32_si128(i & 7));
    __m256i r=_mm256_permutevar8x32_epi32(v, msk);
    __m128i rh=_mm256_castsi256_si128(r);
    return _mm_cvtsi128_si32(rh);
#else
    __m128i vv;
    if (i<4) {
        vv = as<__m128i>(v);
    } else {
        vv = _mm256_extractsi128_si256(v, 1);
    }
    return extract_u32(vv, i);
#endif
}

inline
__m256i cftal::x86::insert_u32(__m256i v, uint32_t f, size_t i)
{
    __m256i vf=_mm256_set1_epi32(f);
    const __m256i msk=ins_msk_v8x32[i&7]._vi;
    return select_u32(msk, vf, v);
}

template <unsigned _IDX>
inline
uint64_t cftal::x86::extract_u64(__m256i v)
{
    const bool cond = _IDX < 4;
    static_assert(cond, "cftal::x86::extract_u64 _IDX < 4");
    __m128i vv;
    if (_IDX<2) {
        vv = as<__m128i>(v);
    } else {
        vv = _mm256_extracti128_si256(v, 1);
    }
    return extract_u64<_IDX&1>(vv);
}

template <unsigned _IDX>
inline
__m256i cftal::x86::insert_u64(__m256i v, uint64_t d)
{
    const bool cond = _IDX < 4;
    static_assert(cond, "cftal::x86::insert_u64 _IDX < 4");
    __m256i r = v;
    __m256i vv;
    vv = _mm256_set1_epi64x(d);
    switch (_IDX) {
    case 0:
        r= select_u64<1, 0, 0, 0>(vv, r);
        break;
    case 1:
        r= select_u64<0, 1, 0, 0>(vv, r);
        break;
    case 2:
        r= select_u64<0, 0, 1, 0>(vv, r);
        break;
    case 3:
        r= select_u64<0, 0, 0, 1>(vv, r);
        break;
    }
    return r;
}

inline
std::uint64_t cftal::x86::extract_u64(__m256i v, size_t i)
{
#if defined (__AVX2__)
    size_t ii= ((i & 3) * 0x200000002LL) + 0x100000000LL;
    // const __m256i msk= _mm256_set1_epi64x( ii);
    const __m256i msk=_mm256_castsi128_si256(_mm_cvtsi64_si128(ii));
    __m256i r=_mm256_permutevar8x32_epi32(v, msk);
    __m128i rh=_mm256_castsi256_si128(r);
    return _mm_cvtsi128_si64(rh);
#else
    __m128i vv;
    if (i<4) {
        vv = as<__m128i>(v);
    } else {
        vv = _mm256_extractsi128_si256(v, 1);
    }
    return extract_u32(vv, i);
#endif
}

inline
__m256i cftal::x86::insert_u64(__m256i v, uint64_t d, size_t i)
{
    __m256i vf=_mm256_set1_epi64x(d);
    const __m256i msk=ins_msk_v4x64[i&3]._vi;
    return select_u64(msk, vf, v);
}


#endif

// Local variables:
// mode: c++
// end:
#endif
