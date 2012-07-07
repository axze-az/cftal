#if !defined (__X86VEC_INS_EXT_H__)
#define __X86VEC_INS_EXT_H__ 1

#include <cftal/x86vec_intrin.h>
#include <cftal/x86vec_select.h>

namespace x86vec {

        // extract/insert double
        template <unsigned _IDX>
        double extract_f64(__m128d r);
        template <unsigned _IDX>
        __m128d insert_f64(__m128d r, double v);

        // extract/insert float
        template <unsigned _IDX>
        float extract_f32(__m128 r);
        template <unsigned _IDX>
        __m128 insert_f32(__m128 r, float v);

        // extract/insert uint8_t
        template <unsigned _IDX>
        std::uint8_t extract_u8(__m128i v);
        template <unsigned _IDX>
        __m128i insert_u8(__m128i r, std::uint8_t v);

        // extract/insert uint16_t
        template <unsigned _IDX>
        std::uint16_t extract_u16(__m128i v);
        template <unsigned _IDX>
        __m128i insert_u16(__m128i r, std::uint16_t v);

        // extract/insert uint32_t
        template <unsigned _IDX>
        std::uint32_t extract_u32(__m128i v);
        template <unsigned _IDX>
        __m128i insert_u32(__m128i r, std::uint32_t v);

        // extract/insert uint64_t
        template <unsigned _IDX>
        std::uint64_t extract_u64(__m128i v);
        template <unsigned _IDX>
        __m128i insert_u64(__m128i r, std::uint64_t v);

}
template <unsigned _IDX>
inline
double x86vec::extract_f64(__m128d v)
{
        const bool cond = _IDX < 2;
        static_assert (cond, "x86vec::extract_f64 _IDX < 2");
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
__m128d x86vec::insert_f64(__m128d v, double d)
{
        const bool cond = _IDX < 2;
        static_assert (cond, "x86vec::insert_f64 _IDX < 2");
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

template <unsigned _IDX>
inline
float x86vec::extract_f32(__m128 v)
{
        const bool cond = _IDX < 4;
        static_assert (cond, "x86vec::extract_f32 _IDX < 4");
#if defined (__SSE4_1__)
        union { int _i; float _f; } tmp;
        tmp._i = _mm_extract_ps(v, _IDX);
        float r= tmp._f;
        return r;
#else
        float r;
        switch (_IDX) {
        case 0:
                _mm_store_ss(&r, v);
                break;
        case 1: {
		static const int m= shuffle4<1, 1, 1, 1>::val;
                _mm_store_ss(&r, _mm_shuffle_ps(v, v, m));
                break;
	}
        case 2:
                _mm_store_ss(&r, _mm_unpackhi_ps(v, v));
                break;
        case 3: {
		static const int m= shuffle4<3, 3, 3, 3>::val;
                _mm_store_ss(&r, _mm_shuffle_ps(v, v, m));
	}
                break;
        }
        return r;
#endif
}

template <unsigned _IDX>
inline
__m128 x86vec::insert_f32(__m128 v, float f)
{
        const bool cond = _IDX < 4;
        static_assert (cond, "x86vec::insert_f32 _IDX < 4");
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

template <unsigned _IDX>
inline
std::uint8_t x86vec::extract_u8(__m128i v) {
        const bool cond = _IDX < 16;
        static_assert (cond, "x86vec::extract_u8 _IDX < 16");
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
__m128i x86vec::insert_u8(__m128i v, std::uint8_t i)
{
        const bool cond = _IDX < 16;
        static_assert (cond, "x86vec::insert_u8 _IDX < 16");
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

template <unsigned _IDX>
inline
std::uint16_t x86vec::extract_u16(__m128i v) {
        const bool cond = _IDX < 8;
        static_assert (cond, "x86vec::extract_u16 _IDX < 8");
        return _mm_extract_epi16(v, _IDX);
}

template <unsigned _IDX>
inline
__m128i x86vec::insert_u16(__m128i v, std::uint16_t i)
{
        const bool cond = _IDX < 16;
        static_assert (cond, "x86vec::insert_u16 _IDX < 16");
        return _mm_insert_epi16(v, i, _IDX);
}

template <unsigned _IDX>
inline
std::uint32_t x86vec::extract_u32(__m128i v)
{
        const bool cond = _IDX < 4;
        static_assert (cond, "x86vec::extract_u32 _IDX < 4");
        std::uint32_t r;
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
__m128i x86vec::insert_u32(__m128i v, std::uint32_t i)
{
        const bool cond = _IDX < 4;
        static_assert (cond, "x86vec::insert_u32 _IDX < 4");
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

template <unsigned _IDX>
inline
std::uint64_t x86vec::extract_u64(__m128i v) {
        const bool cond = _IDX < 2;
        static_assert (cond, "x86vec::extract_u64 _IDX < 2");
        std::uint64_t r;
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
        std::uint32_t l, h;
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
        r = (std::uint64_t(h) << 32) | l;
#endif
        return r;
}

template <unsigned _IDX>
inline
__m128i x86vec::insert_u64(__m128i v, std::uint64_t i)
{
        const bool cond = _IDX < 2;
        static_assert (cond, "x86vec::insert_u64_IDX < 2");
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
                dt = _mm_castsi128_pd(t);
                dv = _mm_castsi128_pd(v);
                dr = _mm_move_sd(dv, dt);
                r = _mm_castpd_si128(dr);
        } else {
                r = _mm_unpacklo_epi64(v, t);
        }
#endif
        return r;
}

// Local variables:
// mode: c++
// end:
#endif
