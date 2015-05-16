#if !defined (__CFTAL_X86_OPS_1_H__)
#define __CFTAL_X86_OPS_1_H__ 1

#include <cftal/fenv.h>
#include <cftal/x86_perm.h>
#include <cftal/x86_ops_0.h>

namespace cftal {

    namespace x86 {

        template <class _E, unsigned _EN>
        struct div_ref {
            static __m128i ref(__m128i a, __m128i b,
                               __m128i* rem=nullptr);
            static __m128i v(__m128i a, __m128i b,
                             __m128i* rem=nullptr);
        };

        struct div_u16 : public div_ref<uint16_t, 8> {
            static __m128i v(__m128i a, __m128i b,
                             __m128i* rem=nullptr);
        };

        struct div_s16 : public div_ref<int16_t, 8> {
            static __m128i v(__m128i a, __m128i b,
                             __m128i* rem=nullptr);
        };

        struct div_u32 {
            static __m128i v(__m128i a, __m128i b,
                             __m128i* rem=nullptr);            
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i b,
                             __m256i* rem=nullptr);
#endif
        };

        struct div_s32 {
            static __m128i v(__m128i a, __m128i b,
                             __m128i* rem=nullptr);
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i b,
                             __m256i* rem=nullptr);
#endif
        };

        struct div_u64 : public div_ref<uint64_t, 2> {
            static __m128i v(__m128i a, __m128i b,
                             __m128i* rem=nullptr);
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i b,
                             __m256i* rem=nullptr);
#endif
        };

        struct div_s64 : public div_ref<int64_t, 2> {
            static __m128i v(__m128i a, __m128i b,
                             __m128i* rem=nullptr);
            
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i b,
                             __m256i* rem=nullptr);
#endif
        };

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

        // neither all bits set nor unset
        bool both_bits(__m128i a);
        // all bits set
        bool all_bits(__m128i a);
        // all bits not set
        bool no_bits(__m128i a);

        bool both_signs_f32(__m128 a);
        bool all_signs_f32(__m128 a);
        bool no_signs_f32(__m128 a);

        bool both_signs_f64(__m128d a);
        bool all_signs_f64(__m128d a);
        bool no_signs_f64(__m128d a);

#if defined (__AVX__)
        bool both_signs_f32(__m256 a);
        bool all_signs_f32(__m256 a);
        bool no_signs_f32(__m256 a);

        bool both_signs_f64(__m256d a);
        bool all_signs_f64(__m256d a);
        bool no_signs_f64(__m256d a);
#endif

        bool both_signs_s16(__m128i a);
        bool all_signs_s16(__m128i a);
        bool no_signs_s16(__m128i a);

        bool both_signs_s32(__m128i a);
        bool all_signs_s32(__m128i a);
        bool no_signs_s32(__m128i a);

        bool both_signs_s64(__m128i a);
        bool all_signs_s64(__m128i a);
        bool no_signs_s64(__m128i a);



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
    typename vecunion<__m128i, _E, _EN>::u_t ca, cb, cq, cr;
    _mm_store_si128(&ca._v, a);
    _mm_store_si128(&cb._v, b);
    for (unsigned i=0; i<_EN; ++i) {
        if (cb._e[i] != _E(0) ) {
            cq._e[i] = ca._e[i] / cb._e[i];
            cr._e[i] = ca._e[i] % cb._e[i];
        } else {
            cq._e[i] = _E(-1);
            cr._e[i] = ca._e[i];
        }
    }
    if (rem != nullptr)
        _mm_store_si128(rem, _mm_load_si128(&cr._v));
    return _mm_load_si128(&cq._v);
}

template <class _E, unsigned _EN>
__m128i cftal::x86::div_ref<_E, _EN>::v(__m128i a, __m128i b, __m128i* rem)
{
    return ref(a, b, rem);
}

inline
cftal::uint32_t cftal::x86::read_signs_s8(__m128i a)
{
    return _mm_movemask_epi8(a);
}

inline
cftal::uint32_t cftal::x86::read_signs_s16(__m128i a)
{
#if defined (__SSSE3__)
    const __m128i msk= _mm_setr_epi8( 1,  3,  5,  7,  9, 11, 13, 15,
                                     -1, -1, -1, -1, -1, -1, -1, -1);
    __m128i as= _mm_shuffle_epi8(a, msk);
    uint32_t r= read_signs_s8(as);
    return r;
#else
    uint32_t t=read_signs_s8(a);
    uint32_t t0 = (t >>  (1-0)) & (1<<0);
    uint32_t t1 = (t >>  (3-1)) & (1<<1);
    uint32_t t2 = (t >>  (5-2)) & (1<<2);
    uint32_t t3 = (t >>  (7-3)) & (1<<3);
    uint32_t t4 = (t >>  (9-4)) & (1<<4);
    uint32_t t5 = (t >> (11-5)) & (1<<5);
    uint32_t t6 = (t >> (13-6)) & (1<<6);
    uint32_t t7 = (t >> (15-7)) /* & (1<<8)*/ ;
    return t0 | t1 | t2 | t3 | t4 | t5 | t6 | t7;
#endif
}

inline
cftal::uint32_t cftal::x86::read_signs_s32(__m128i a)
{
#if defined (__SSSE3__)
    const __m128i msk= _mm_setr_epi8( 3,  7, 11, 15, -1, -1, -1, -1,
                                      -1, -1, -1, -1, -1, -1, -1, -1);
    __m128i as= _mm_shuffle_epi8(a, msk);
    uint32_t r= read_signs_s8(as);
    return r;
#else
    uint32_t t=read_signs_s8(a);
    uint32_t t0 = (t >>  (3-0)) & (1<<0);
    uint32_t t1 = (t >>  (7-1)) & (1<<1);
    uint32_t t2 = (t >> (11-2)) & (1<<2);
    uint32_t t3 = (t >> (15-3)) /* & (1<<3) */;
    return t0 | t1 | t2 | t3;
#endif
}

inline
cftal::uint32_t cftal::x86::read_signs_s64(__m128i a)
{
#if defined (__SSSE3__)
    const __m128i msk= _mm_setr_epi8( 7, 15, -1, -1, -1, -1, -1, -1,
                                      -1, -1, -1, -1, -1, -1, -1, -1);
    __m128i as= _mm_shuffle_epi8(a, msk);
    uint32_t r= read_signs_s8(as);
    return r;
#else
    uint32_t t=read_signs_s8(a);
    uint32_t t0 = (t >>  (7-0)) & (1<<0);
    uint32_t t1 = (t >> (15-1)) /* & (1<<1) */;
    return t0 | t1;
#endif
}


inline
cftal::uint32_t cftal::x86::read_signs_f32(__m128 a)
{
    return _mm_movemask_ps(a);
}

inline
cftal::uint32_t cftal::x86::read_signs_f64(__m128d a)
{
    return _mm_movemask_pd(a);
}

#if defined (__AVX__)
inline
cftal::uint32_t cftal::x86::read_signs_f32(__m256 a)
{
    return _mm256_movemask_ps(a);
}

inline
cftal::uint32_t cftal::x86::read_signs_f64(__m256d a)
{
    return _mm256_movemask_pd(a);
}
#endif

#if defined (__AVX2__)
inline
cftal::uint32_t cftal::x86::read_signs_s8(__m256i a)
{
    return _mm256_movemask_epi8(a);
}

inline
cftal::uint32_t cftal::x86::read_signs_s16(__m256i a)
{
    const __m128i m0= _mm_setr_epi8( 1,  3,  5,  7,  9, 11, 13, 15,
                                     -1, -1, -1, -1, -1, -1, -1, -1);
    const __m256i m1= _mm256_cast_si128_si256(msk);
    const __m256i m2= _mm256_inserti128_si256(m1, m0);
    __m256i as= _mm256_shuffle_epi8(a, m2);
    uint32_t r= read_signs_s8(as);
    r = (r>>16-8) | (r & 0xFF);
    return r;
}

inline
cftal::uint32_t cftal::x86::read_signs_s32(__m256i a)
{
    const __m128i m0= _mm_setr_epi8( 3,  7, 11, 15, -1, -1, -1, -1,
                                     -1, -1, -1, -1, -1, -1, -1, -1);
    const __m256i m1= _mm256_cast_si128_si256(msk);
    const __m256i m2= _mm256_inserti128_si256(m1, m0);
    __m256i as= _mm256_shuffle_epi8(a, m2);
    uint32_t r= read_signs_s8(as);
    r = (r>>16-4) | (r & 0xF);
    return r;
}

inline
cftal::uint32_t cftal::x86::read_signs_s64(__m256i a)
{
    const __m128i m0= _mm_setr_epi8( 7, 15, -1, -1, -1, -1, -1, -1,
                                     -1, -1, -1, -1, -1, -1, -1, -1);
    const __m256i m1= _mm256_cast_si128_si256(msk);
    const __m256i m2= _mm256_inserti128_si256(m1, m0);
    __m256i as= _mm256_shuffle_epi8(a, m2);
    uint32_t r= read_signs_s8(as);
    r = (r>>16-2) | (r & 0x3);
    return r;
}

#endif

inline
bool cftal::x86::both_bits(__m128i a)
{
#if defined (__SSE4_1__)
    const __m128i msk=const_v4u32<uint32_t(-1), uint32_t(-1),
                                  uint32_t(-1), uint32_t(-1)>::iv();
    return _mm_testnzc_si128(a, msk);
#else
    const __m128i msk= impl::make_zero_int::v();
    __m128i t=_mm_cmpeq_epi8(a, msk);
    int r=read_signs_s8(t);
    return (r != 0) && (r != 0xFFFF);
#endif
}

inline
bool cftal::x86::all_bits(__m128i a)
{
    const __m128i msk=x86::const_v4u32<uint32_t(-1), uint32_t(-1),
                                       uint32_t(-1), uint32_t(-1)>::iv();
#if defined (__SSE4_1__)
    return _mm_testc_si128(a, msk);
#else
    __m128i t=_mm_cmpeq_epi8(a, msk);
    int r=read_signs_s8(t);
    return r == 0xFFFF;
#endif
}

inline
bool cftal::x86::no_bits(__m128i a)
{
#if defined (__SSE4_1__)
    return _mm_testz_si128(a, a);
#else
    __m128i t=_mm_cmpeq_epi8(a, impl::make_zero_int::v());
    int r=read_signs_s8(t);
    return r == 0xFFFF;
#endif
}

inline
bool cftal::x86::both_signs_f32(__m128 a)
{
#if defined (__SSE4_1__)
    const __m128i msk= x86::v_sign_v4f32_msk::iv();
    return _mm_testnzc_si128(as<__m128i>(a), msk);
#else
    int r=read_signs_f32(a);
    return (r != 0) && (r != sign_f32_msk);
#endif
}

inline
bool cftal::x86::all_signs_f32(__m128 a)
{
#if defined (__SSE4_1__)
    const __m128i msk= x86::v_sign_v4f32_msk::iv();
    return _mm_testc_si128(as<__m128i>(a), msk);
#else
    int r=read_signs_f32(a);
    return r  ==  sign_f32_msk;
#endif
}

inline
bool cftal::x86::no_signs_f32(__m128 a)
{
#if defined (__SSE4_1__)
    const __m128i msk= x86::v_sign_v4f32_msk::iv();
    return _mm_testz_si128(as<__m128i>(a), msk);
#else
    int r=read_signs_f32(a);
    return r  == 0;
#endif
}

inline
bool cftal::x86::both_signs_f64(__m128d a)
{
#if defined (__SSE4_1__)
    const __m128i msk= x86::v_sign_v2f64_msk::iv();
    return _mm_testnzc_si128(as<__m128i>(a), msk);
#else
    int r=read_signs_f64(a);
    return (r != 0) && (r != sign_f64_msk);
#endif
}

inline
bool cftal::x86::all_signs_f64(__m128d a)
{
#if defined (__SSE4_1__)
    const __m128i msk= x86::v_sign_v2f64_msk::iv();
    return _mm_testc_si128(as<__m128i>(a), msk);
#else
    int r=read_signs_f64(a);
    return r == sign_f64_msk;
#endif
}

inline
bool cftal::x86::no_signs_f64(__m128d a)
{
#if defined (__SSE4_1__)
    const __m128i msk= x86::v_sign_v2f64_msk::iv();
    return _mm_testz_si128(as<__m128i>(a), msk);
#else
    int r=read_signs_f64(a);
    return r == 0;
#endif
}

#if defined (__AVX__)
inline
bool cftal::x86::both_signs_f32(__m256 a)
{
    const __m256i msk= x86::v_sign_v8f32_msk::iv();
    return _mm256_testnzc_si256(as<__m256i>(a), msk);
}

inline
bool cftal::x86::all_signs_f32(__m256 a)
{
    const __m256i msk= x86::v_sign_v8f32_msk::iv();
    return _mm256_testc_si256(as<__m256i>(a), msk);
}

inline
bool cftal::x86::no_signs_f32(__m256 a)
{
    const __m256i msk= x86::v_sign_v8f32_msk::iv();
    return _mm256_testz_si256(as<__m256i>(a), msk);
}

inline
bool cftal::x86::both_signs_f64(__m256d a)
{
    const __m256i msk= x86::v_sign_v4f64_msk::iv();
    return _mm256_testnzc_si256(as<__m256i>(a), msk);
}

inline
bool cftal::x86::all_signs_f64(__m256d a)
{
    const __m256i msk= x86::v_sign_v4f64_msk::iv();
    return _mm256_testc_si256(as<__m256i>(a), msk);
}

inline
bool cftal::x86::no_signs_f64(__m256d a)
{
    const __m256i msk= x86::v_sign_v4f64_msk::iv();
    return _mm256_testz_si256(as<__m256i>(a), msk);
}

#endif

inline
bool cftal::x86::both_signs_s16(__m128i a)
{
#if defined (__SSE4_1__)
    const __m128i msk= x86::v_sign_s16_msk::iv();
    return _mm_testnzc_si128(a, msk);
#else
    int r=read_signs_s8(a);
    return (r != 0) && ((r & sign_s16_msk) != sign_s16_msk);
#endif
}

inline
bool cftal::x86::all_signs_s16(__m128i a)
{
#if defined (__SSE4_1__)
    const __m128i msk= x86::v_sign_s16_msk::iv();
    return _mm_testc_si128(a, msk);
#else
    int r=read_signs_s8(a);
    return (r & sign_s16_msk) == sign_s16_msk;
#endif
}

inline
bool cftal::x86::no_signs_s16(__m128i a)
{
#if defined (__SSE4_1__)
    const __m128i msk= x86::v_sign_s16_msk::iv();
    return _mm_testz_si128(a, msk);
#else
    int r=read_signs_s8(a);
    return (r & sign_s16_msk) ==0;
#endif
}

inline
bool cftal::x86::both_signs_s32(__m128i a)
{
#if defined (__SSE4_1__)
    const __m128i msk= x86::v_sign_s32_msk::iv();
    return _mm_testnzc_si128(a, msk);
#else
    int r=read_signs_s8(a);
    return (r != 0) && ((r & sign_s32_msk) != sign_s32_msk);
#endif
}

inline
bool cftal::x86::all_signs_s32(__m128i a)
{
#if defined (__SSE4_1__)
    const __m128i msk= x86::v_sign_s32_msk::iv();
    return _mm_testc_si128(a, msk);
#else
    int r=read_signs_s8(a);
    return (r & sign_s32_msk) == sign_s32_msk;
#endif
}

inline
bool cftal::x86::no_signs_s32(__m128i a)
{
#if defined (__SSE4_1__)
    const __m128i msk= x86::v_sign_s32_msk::iv();
    return _mm_testz_si128(a, msk);
#else
    int r=read_signs_s8(a);
    return (r & sign_s32_msk) == 0;
#endif
}

inline
bool cftal::x86::both_signs_s64(__m128i a)
{
#if defined (__SSE4_1__)
    const __m128i msk= x86::v_sign_s64_msk::iv();
    return _mm_testnzc_si128(a, msk);
#else
    int r=read_signs_s8(a);
    return (r != 0) && ((r & sign_s64_msk) != sign_s64_msk);
#endif
}

inline
bool cftal::x86::all_signs_s64(__m128i a)
{
#if defined (__SSE4_1__)
    const __m128i msk= x86::v_sign_s64_msk::iv();
    return _mm_testc_si128(a, msk);
#else
    int r=read_signs_s8(a);
    return (r & sign_s64_msk) == sign_s64_msk;
#endif
}

inline
bool cftal::x86::no_signs_s64(__m128i a)
{
#if defined (__SSE4_1__)
    const __m128i msk= x86::v_sign_s64_msk::iv();
    return _mm_testz_si128(a, msk);
#else
    int r=read_signs_s8(a);
    return (r & sign_s64_msk) ==0;
#endif
}


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
    const __m128i msk= x86::v_uint8_0x01::iv();
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
    const __m128i msk= x86::v_uint16_0x0001::iv();
    return _mm_madd_epi16(popcnt_u16(a), msk);
}

inline __m128i cftal::x86::popcnt_u64(__m128i a)
{
    a= popcnt_u8(a);
    return _mm_sad_epu8(a, x86::impl::make_zero_int::v());
}

inline int cftal::x86::popcnt_u128(__m128i a)
{
    a= popcnt_u64(a);
    const int sm= x86::impl::shuffle4<2,3,1,0>::val;
    __m128i t= _mm_shuffle_epi32(a, sm);
    t = _mm_add_epi32(t, a);
    return _mm_cvtsi128_si32(t);
}

inline __m128i cftal::x86::bitrev_u8(__m128i a)
{
    // AMD XOP: use pperm
    // bitrev algorithm
    // swap odd and even bits
    // v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
    const __m128i c55= x86::v_uint8_0x55::iv();
    __m128i t= x86::impl::vpsrlw_const<1>::v(a);
    a = _mm_and_si128(a, c55);
    t = _mm_and_si128(t, c55);
    a = x86::impl::vpsllw_const<1>::v(a);
    a = _mm_or_si128(a, t);
    // swap consecutive pairs
    // v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
    const __m128i c33= x86::v_uint8_0x33::iv();
    t = x86::impl::vpsrlw_const<2>::v(a);
    a = _mm_and_si128(a, c33);
    t = _mm_and_si128(t, c33);
    a = x86::impl::vpsllw_const<2>::v(a);
    a = _mm_or_si128(a, t);
    // swap nibbles ...
    // v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
    const __m128i c0f= x86::v_uint8_0x0f::iv();
    t = x86::impl::vpsrlw_const<4>::v(a);
    a = _mm_and_si128(a, c0f);
    t = _mm_and_si128(t, c0f);
    a = x86::impl::vpsllw_const<4>::v(a);
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
    const __m128i msk = x86::const_v16u8< 1, 0, 3, 2, 5, 4, 7, 6,
                                          9, 8,11,10,13,12,15,14>::iv();
    a = bitrev_u8(a);
    return _mm_shuffle_epi8(a, msk);
#else
    // swap bytes
    // v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
    a = bitrev_u8(a);
    __m128i t= impl::vpsrlw_const<8>::v(a);
    a = impl::vpsllw_const<8>::v(a);
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
    __m128i t= impl::vpsrld_const<16>::v(a);
    a= impl::vpslld_const<16>::v(a);
    return _mm_or_si128(a, t);
#endif
}

inline __m128i cftal::x86::bitrev_u64(__m128i a)
{
    // AMD XOP: use pperm
#if defined (__SSS3__)
    const __m128i msk = const_v16u8<7, 6, 5, 4, 3, 2, 1, 0,
                                    15,14,13,12,11,10,9, 8>::iv();
    a = bitrev_u8(a);
    return _mm_shuffle_epi8(a, msk);
#else
    // swap unsigned pairs
    // v = ( v >> 32             ) | ( v               << 32);
    a = bitrev_u32(a);
    return x86::impl::vpshufd<1, 0, 3, 2>::v(a);
#endif
}

// Local variables:
// mode: c++
// end:
#endif
