#if !defined (__CFTAL_X86_SELECT_H__)
#define __CFTAL_X86_SELECT_H__ 1

#include <cftal/x86_intrin.h>
#include <cftal/x86_const.h>

namespace cftal {

    namespace x86 {

        // select bitwise
        uint32_t select(uint32_t msk,
                        uint32_t on_one, uint32_t on_zero);
        // select bitwise
        uint64_t select(uint64_t msk,
                        uint64_t on_one, uint64_t on_zero);
        // select bytes
        // __SSE2__: bitwise
        // __SSE4_1__: on sign bit of int8_t
        // r[i] = msk[i] ? one[i] : zero
        __m128i select(__m128i msk, __m128i on_one, __m128i on_zero);

        // select floats
        // __SSE2__: bitwise
        // __SSE4_1__: on sign bit of float
        __m128 select(__m128 msk, __m128 on_one, __m128 on_zero);

        // select doubles
        // __SSE2__: bitwise
        // __SSE4_1__: on sign bit of double
        __m128d select(__m128d msk, __m128d on_one, __m128d on_zero);

#if defined (__AVX__)
        // select floats
        // on sign bit of float
        __m256 select(__m256 msk, __m256 on_one, __m256 on_zero);
        // select on doubles
        // on sign bit of double
        __m256d select(__m256d msk, __m256d on_one, __m256d on_zero);
#endif
#if defined (__AVX2__)
        // select bytes
        // on sign bit of int8_t
        // r[i] = msk[i] ? one[i] : zero
        __m256i select(__m256i msk, __m256i on_one, __m256i on_zero);
#endif

        
        namespace impl {

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

            // general case u32, implementation on top of u16
            // therefore no additional specializations
            template <bool _P0, bool _P1, bool _P2, bool _P3>
            struct select_v4u32 {
                static __m128i v(__m128i a, __m128i b);
            };

            // general case u64, implementation on top of u16
            // therefore no additional specializations
            template <bool _P0, bool _P1>
            struct select_v2u64 {
                static __m128i v(__m128i a, __m128i b);
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
#endif
            
        }

        template <bool _P0, bool _P1>
        __m128d select_f64(__m128d a, __m128d b);

        template <bool _P0, bool _P1, bool _P2, bool _P3>
        __m128 select_f32(__m128 a, __m128 b);

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
__m128i cftal::x86::select(__m128i msk, __m128i on_one, __m128i on_zero)
{
#if defined (__SSE4_1__)
    return _mm_blendv_epi8 (on_zero, on_one, msk);
#else
    return _mm_or_si128(_mm_and_si128(msk, on_one),
                        _mm_andnot_si128(msk, on_zero));
#endif
}

inline
__m128 cftal::x86::select(__m128 msk, __m128 on_one, __m128 on_zero)
{
#if defined (__SSE4_1__)
    return _mm_blendv_ps (on_zero, on_one, msk);
#else
    return _mm_or_ps(_mm_and_ps(on_one, msk),
                     _mm_andnot_ps(msk, on_zero));
#endif
}

inline
__m128d cftal::x86::select(__m128d msk, __m128d on_one, __m128d on_zero)
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
__m256 cftal::x86::select(__m256 msk, __m256 on_one, __m256 on_zero)
{
    return _mm256_blendv_ps (on_zero, on_one, msk);
}

inline
__m256d cftal::x86::select(__m256d msk, __m256d on_one, __m256d on_zero)
{
    return _mm256_blendv_pd (on_zero, on_one, msk);
}
#endif

#if defined (__AVX2__)
inline
__m256i cftal::x86::select(__m256i msk, __m256i on_one, __m256i on_zero)
{
    return _mm256_blendv_epi8 (on_zero, on_one, msk);
}

#endif


template <typename _T>
inline _T
cftal::x86::impl::select_arg_1<_T>::v(_T a)
{
    return a;
}

template <typename _T>
inline _T
cftal::x86::impl::select_arg_1<_T>::v(_T a, _T b)
{
    static_cast<void>(b);
    return a;
}

template <typename _T>
inline _T
cftal::x86::impl::select_arg_2<_T>::v(_T a, _T b)
{
    static_cast<void>(a);
    return b;
}

template <bool _P0, bool _P1>
inline __m128d
cftal::x86::impl::select_v2f64<_P0, _P1>::v(__m128d a, __m128d b)
{
#if defined (__SSE4_1__)
    const int sm=csel2<_P0, _P1>::val;
    return _mm_blend_pd(b, a, sm);
#else
    typedef const_v4u32<
        (_P0 ? -1 : 0), (_P0 ? -1 : 0),
        (_P1 ? -1 : 0), (_P1 ? -1 : 0)> mask_type;
    typedef const_v4u32<
        (_P0 ? 0 : -1), (_P0 ? 0 : -1),
        (_P1 ? 0 : -1), (_P1 ? 0 : -1)> compl_mask_type;
    a = _mm_and_pd(a, mask_type::dv());
    b = _mm_and_pd(b, compl_mask_type::dv());
    return _mm_or_pd(a, b);
#endif
}

template <bool _P0, bool _P1, bool _P2, bool _P3>
inline __m128
cftal::x86::impl::select_v4f32<_P0, _P1, _P2, _P3>::v(__m128 a, __m128 b)
{
#if defined (__SSE4_1__)
    const int sm=csel4<_P0, _P1, _P2, _P3>::val;
    return _mm_blend_ps(b, a, sm & 0xf);
#else
    typedef const_v4u32<
        (_P0 ? -1 : 0), (_P1 ? -1 : 0),
        (_P2 ? -1 : 0), (_P3 ? -1 : 0)> mask_type;
    typedef const_v4u32<
        (_P0 ? 0 : -1), (_P1 ? 0 : -1),
        (_P2 ? 0 : -1), (_P3 ? 0 : -1)> compl_mask_type;
    a = _mm_and_ps(a, mask_type::fv());
    b = _mm_and_ps(b, compl_mask_type::fv());
    return _mm_or_ps(a, b);
#endif
}

template<bool _P0, bool _P1, bool _P2, bool _P3,
         bool _P4, bool _P5, bool _P6, bool _P7>
inline __m128i
cftal::x86::impl::
select_v8u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(__m128i a, __m128i b)
{
#if defined (__SSE4_1__)
    enum { sm=csel8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::val };
    return _mm_blend_epi16(b, a, sm);
#else
    typedef const_v8u16<
        uint16_t(_P0 ? -1 : 0), uint16_t(_P1 ? -1 : 0),
        uint16_t(_P2 ? -1 : 0), uint16_t(_P3 ? -1 : 0),
        uint16_t(_P4 ? -1 : 0), uint16_t(_P5 ? -1 : 0),
        uint16_t(_P6 ? -1 : 0), uint16_t(_P7 ? -1 : 0)> mask_type;
    typedef const_v8u16<
        uint16_t(_P0 ? 0 : -1), uint16_t(_P1 ? 0 : -1),
        uint16_t(_P2 ? 0 : -1), uint16_t(_P3 ? 0 : -1),
        uint16_t(_P4 ? 0 : -1), uint16_t(_P5 ? 0 : -1),
        uint16_t(_P6 ? 0 : -1), uint16_t(_P7 ? 0 : -1)> compl_mask_type;
    a = _mm_and_si128(a, mask_type::iv());
    b = _mm_and_si128(b, compl_mask_type::iv());
    return _mm_or_si128(a, b);
#endif
}

#if defined (__AVX__)
template <bool _P0, bool _P1, bool _P2, bool _P3>
inline __m256d
cftal::x86::impl::select_v4f64<_P0, _P1, _P2, _P3>::v(__m256d a, __m256d b)
{
    const int sm=csel4<_P0, _P1, _P2, _P3>::val;
    return _mm256_blend_pd(b, a, sm);
}

template<bool _P0, bool _P1, bool _P2, bool _P3,
         bool _P4, bool _P5, bool _P6, bool _P7>
inline __m256
cftal::x86::impl::
select_v8f32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(__m256 a, __m256 b)
{
    const int sm=csel8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::val;
    return _mm256_blend_ps(b, a, sm);
}
#endif

#if defined (__AVX2__)

template<bool _P0, bool _P1, bool _P2, bool _P3>
inline __m256i
cftal::x86::impl::
select_v4u64<_P0, _P1, _P2, _P3>::v(__m256i a, __m256i b)
{
    const int sm=csel8<_P0, _P0, _P1, _P1, _P2, _P2, _P3, _P3>::val;
    return _mm256_blend_epi32(b, a, sm);
}


template<bool _P0, bool _P1, bool _P2, bool _P3,
         bool _P4, bool _P5, bool _P6, bool _P7>
inline __m256i
cftal::x86::impl::
select_v8u32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(__m256i a, __m256i b)
{
    const int sm=csel8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::val;
    return _mm256_blend_epi32(b, a, sm);
}

#endif



template<bool _P0, bool _P1, bool _P2, bool _P3>
inline __m128i
cftal::x86::impl::
select_v4u32<_P0, _P1, _P2, _P3>::v(__m128i a, __m128i b)
{
    return select_v8u16<_P0, _P0, _P1, _P1, _P2, _P2, _P3, _P3>::v(a, b);
}

template<bool _P0, bool _P1>
inline __m128i
cftal::x86::impl::
select_v2u64<_P0, _P1>::v(__m128i a, __m128i b)
{
    return select_v8u16<_P0, _P0, _P0, _P0, _P1, _P1, _P1, _P1>::v(a, b);
}

template <bool _P0, bool _P1>
inline
__m128d cftal::x86::select_f64(__m128d a, __m128d b)
{
    return impl::select_v2f64<_P0, _P1>::v(a, b);
}

template <bool _P0, bool _P1, bool _P2, bool _P3>
inline
__m128 cftal::x86::select_f32(__m128 a, __m128 b)
{
    return impl::select_v4f32<_P0, _P1, _P2, _P3>::v(a, b);
}

template <bool _P0, bool _P1>
inline
__m128i cftal::x86::select_u64(__m128i a, __m128i b)
{
    return impl::select_v2u64<_P0, _P1>::v(a, b);
}

template <bool _P0, bool _P1, bool _P2, bool _P3>
inline
__m128i cftal::x86::select_u32(__m128i a, __m128i b)
{
    return impl::select_v4u32<_P0, _P1, _P2, _P3>::v(a, b);
}

template <bool _P0, bool _P1, bool _P2, bool _P3,
          bool _P4, bool _P5, bool _P6, bool _P7>
__m128i cftal::x86::select_u16(__m128i a, __m128i b)
{
    return impl::select_v8u16<_P0, _P1, _P2, _P3,
                              _P4, _P5, _P6, _P7>::v(a, b);
}

#if defined (__AVX__)

template <bool _P0, bool _P1, bool _P2, bool _P3>
inline
__m256d cftal::x86::select_f64(__m256d a, __m256d b)
{
    return impl::select_v4f64<_P0, _P1, _P2, _P3>::v(a, b);
}

template <bool _P0, bool _P1, bool _P2, bool _P3,
          bool _P4, bool _P5, bool _P6, bool _P7>
__m256 cftal::x86::select_f32(__m256 a, __m256 b)
{
    return impl::select_v8f32<_P0, _P1, _P2, _P3,
                              _P4, _P5, _P6, _P7>::v(a, b);
}

#endif

#if defined (__AVX2__)
template <bool _P0, bool _P1, bool _P2, bool _P3>
__m256i cftal::x86::select_u64(__m256i a, __m256i b)
{
    return impl::select_v4u64<_P0, _P1, _P2, _P3>::v(a, b);
}

template <bool _P0, bool _P1, bool _P2, bool _P3,
          bool _P4, bool _P5, bool _P6, bool _P7>
__m256i cftal::x86::select_u32(__m256i a, __m256i b)
{
    return impl::select_v8u32<_P0, _P1, _P2, _P3,
                              _P4, _P5, _P6, _P7>::v(a, b);
}

#endif

// Local variables:
// mode: c++
// end:

#endif // __CFTAL_X86_SELECT_H__
