//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_X86_OPS_0_H__)
#define __CFTAL_X86_OPS_0_H__ 1

#include <cftal/x86/intrin.h>
#include <cftal/x86/const.h>
#include <cftal/x86/select.h>
#include <cftal/x86/cast_bits.h>
#include <cftal/x86/ins_ext.h>
#include <cftal/impl/masks.h>

namespace cftal {
    namespace x86 {

        using cftal::impl::pos_msk_2;
        using cftal::impl::zero_msk_2;
        using cftal::impl::pos_msk_4;
        using cftal::impl::zero_msk_4;
        using cftal::impl::pos_msk_8;
        using cftal::impl::zero_msk_8;

        template <class _T, class _OP>
        struct swap_ab {
            static _T v(_T a, _T b) {
                return _OP::v(b, a);
            }
        };

        template <class _T, class _OP>
        struct use_arg_1 {
            static _T v(_T a, _T b) {
                static_cast<void>(b);
                return _OP::v(a, a);
            }
        };

        template <class _T, class _OP>
        struct use_arg_2 {
            static _T v(_T a, _T b) {
                static_cast<void>(a);
                return _OP::v(b, b);
            }
        };

        template <class _T, class _FIXED_ARG2, class _OP>
        struct fixed_arg_2 {
            static _T v(_T a, _T b) {
                return _OP::v(a, _FIXED_ARG2::v(a,b));
            }
            static _T v(_T a) {
                return v(a, a);
            }
        };

        template <class _T, class _FIXED_ARG1, class _OP>
        struct fixed_arg_1 {
            static _T v(_T a, _T b) {
                return _OP::v(_FIXED_ARG1::v(a,b), b);
            }
            static _T v(_T a) {
                return v(a, a);
            }
        };

#if 0
        template <class _T, class _OP>
        struct dup_arg {
            static _T v(_T a) {
                return _OP::v(a, a);
            }
        };
#endif

        template <class _INT_OP>
        struct exec_int {
            // float: cast to int, exec, cast back
            static __m128 v(__m128 a) {
                return as<__m128>(
                    _INT_OP::v(as<__m128i>(a)));
            }
            static __m128 v(__m128 a, __m128 b) {
                return as<__m128>(
                    _INT_OP::v(as<__m128i>(a),
                               as<__m128i>(b)));
            }
            // double: cast to int, exec, cast back
            static __m128d v(__m128d a) {
                return as<__m128d>(
                    _INT_OP::v(as<__m128i>(a)));
            }
            static __m128d v(__m128d a, __m128d b) {
                return as<__m128d>(
                    _INT_OP::v(as<__m128i>(a),
                               as<__m128i>(b)));
            }
#if defined (__AVX2__)
            // float: cast to int, exec, cast back
            static __m256 v(__m256 a) {
                return as<__m256>(
                    _INT_OP::v(as<__m256i>(a)));
            }
            static __m256 v(__m256 a, __m256 b) {
                return as<__m256>(
                    _INT_OP::v(as<__m256i>(a),
                               as<__m256i>(b)));
            }
            // double: cast to int, exec, cast back
            static __m256d v(__m256d a) {
                return as<__m256d>(
                    _INT_OP::v(as<__m256i>(a)));
            }
            static __m256d v(__m256d a, __m256d b) {
                return as<__m256d>(
                    _INT_OP::v(as<__m256i>(a),
                               as<__m256i>(b)));
            }
#endif
        };

        template <class _F32_OP>
        struct exec_f32 {
            // int: cast to float, exec, cast back
            static __m128i v(__m128i a) {
                return as<__m128i>(
                    _F32_OP::v(as<__m128>(a)));
            }
            static __m128i v(__m128i a, __m128i b) {
                return as<__m128i>(
                    _F32_OP::v(as<__m128>(a),
                               as<__m128>(b)));
            }
            // double: cast to float, exec, cast back
            static __m128d v(__m128d a) {
                return as<__m128d>(
                    _F32_OP::v(as<__m128>(a)));
            }
            static __m128d v(__m128d a, __m128d b) {
                return as<__m128d>(
                    _F32_OP::v(as<__m128>(a),
                               as<__m128>(b)));
            }
#if defined (__AVX__)
            // int: cast to float, exec, cast back
            static __m256i v(__m256i a) {
                return as<__m256i>(
                    _F32_OP::v(as<__m256>(a)));
            }
            static __m256i v(__m256i a, __m256i b) {
                return as<__m256i>(
                    _F32_OP::v(as<__m256>(a),
                               as<__m256>(b)));
            }
            // double: cast to float, exec, cast back
            static __m256d v(__m256d a) {
                return as<__m256d>(
                    _F32_OP::v(as<__m256>(a)));
            }
            static __m256d v(__m256d a, __m256d b) {
                return as<__m256d>(
                    _F32_OP::v(as<__m256>(a),
                               as<__m256>(b)));
            }
#endif
        };

        template <class _F64_OP>
        struct exec_f64 {
            // int: cast to double, exec, cast back
            static __m128i v(__m128i a) {
                return as<__m128i>(
                    _F64_OP::v(as<__m128d>(a)));
            }
            static __m128i v(__m128i a, __m128i b) {
                return as<__m128i>(
                    _F64_OP::v(as<__m128d>(a),
                               as<__m128d>(b)));
            }
            // float: cast to double, exec, cast back
            static __m128 v(__m128 a) {
                return as<__m128>(
                    _F64_OP::v(as<__m128d>(a)));
            }
            static __m128 v(__m128 a, __m128 b) {
                return as<__m128>(
                    _F64_OP::v(as<__m128d>(a),
                               as<__m128d>(b)));
            }
#if defined (__AVX__)
            // int: cast to double, exec, cast back
            static __m256i v(__m256i a) {
                return as<__m256i>(
                    _F64_OP::v(as<__m256d>(a)));
            }
            static __m256i v(__m256i a, __m256i b) {
                return as<__m256i>(
                    _F64_OP::v(as<__m256d>(a),
                               as<__m256d>(b)));
            }
            // float: cast to double, exec, cast back
            static __m256 v(__m256 a) {
                return as<__m256>(
                    _F64_OP::v(as<__m256d>(a)));
            }
            static __m256 v(__m256 a, __m256 b) {
                return as<__m256>(
                    _F64_OP::v(as<__m256d>(a),
                               as<__m256d>(b)));
            }
#endif
        };


        struct make_zero_v2f64 {
            static __m128d v() {
                return _mm_setzero_pd();
            }
            static __m128d v(__m128d a) {
                static_cast<void>(a);
                return v();
            }
            static __m128d v(__m128d a, __m128d b) {
                static_cast<void>(a);
                static_cast<void>(b);
                return v();
            }
        };

        struct make_zero_v4f32 {
            static __m128 v() {
                return _mm_setzero_ps();
            }
            static __m128 v(__m128 a)  {
                static_cast<void>(a);
                return v();
            }
            static __m128 v(__m128 a, __m128 b) {
                static_cast<void>(a);
                static_cast<void>(b);
                return v();
            }
        };

        struct make_zero_int {
            static __m128i v() {
                return _mm_setzero_si128();
            }
            static __m128i v(__m128i a) {
                static_cast<void>(a);
                return v();
            }
            static __m128i v(__m128i a, __m128i b) {
                static_cast<void>(a);
                static_cast<void>(b);
                return v();
            }
        };

#if defined (__AVX__)
        struct make_zero_int256 {
            static __m256i v() {
                return _mm256_setzero_si256();
            }
            static __m256i v(__m256i a) {
                static_cast<void>(a);
                return v();
            }
            static __m256i v(__m256i a, __m256i b) {
                static_cast<void>(a);
                static_cast<void>(b);
                return v();
            }
        };
#endif

        template <unsigned _P0, unsigned _P1>
        struct vshufpd {
            static __m128d v(__m128d a, __m128d b) {
                const int m=shuffle2<int(_P0), int(_P1)>::val;
                return _mm_shuffle_pd(a, b, m & 3);
            }
            static __m128d v(__m128d a) {
                return v(a, a);
            }
        };


        template <unsigned _P0, unsigned _P1,
                  unsigned _P2, unsigned _P3>
        struct vshufps {
            enum {
                m=shuffle4<
                int(_P0),
                int(_P1),
                int(_P2),
                int(_P3)>::val
            };

            static __m128 v(__m128 a, __m128 b) {
                return _mm_shuffle_ps(a, b, m);
            }
            static __m128 v(__m128 a) {
                return v(a, a);
            }
#if defined (__AVX__)
            static __m256 v(__m256 a, __m256 b) {
                return _mm256_shuffle_ps(a, b, m);
            }
            static __m256 v(__m256 a) {
                return v(a, a);
            }
#endif
        };

        template <unsigned _P0, unsigned _P1,
                  unsigned _P2, unsigned _P3>
        struct vpshuflw {
            static __m128i v(__m128i a) {
                constexpr int _p0=_P0;
                constexpr int _p1=_P1;
                constexpr int _p2=_P2;
                constexpr int _p3=_P3;
                const int m=shuffle4<_p0, _p1, _p2, _p3>::val;
                return _mm_shufflelo_epi16(a, m & 0xff);
            }
        };

        template <>
        struct vpshuflw<0, 1, 2, 3>
            : public select_arg_1<__m128i> {};

        template <unsigned _P0, unsigned _P1,
                  unsigned _P2, unsigned _P3>
        struct vpshufhw {
            static __m128i v(__m128i a) {
                constexpr int p0=_P0;
                constexpr int p1=_P1;
                constexpr int p2=_P2;
                constexpr int p3=_P3;
                const int m=shuffle4<p0, p1, p2, p3>::val;
                return _mm_shufflehi_epi16(a, m & 0xff);
            }
        };

        template <>
        struct vpshufhw<0, 1, 2, 3>
            : public select_arg_1<__m128i> {};

        template <unsigned _P0, unsigned _P1,
                  unsigned _P2, unsigned _P3>
        struct vpshufd {
            enum {
                _p0 = _P0,
                _p1 = _P1,
                _p2 = _P2,
                _p3 = _P3,
                m= shuffle4<int(_p0), int(_p1), int(_p2), int(_p3)>::
                val & 0xff
            };

            static __m128i v(__m128i a) {
                return _mm_shuffle_epi32(a, m);
            }
#if defined (__AVX2__)
            static __m256i v(__m256i a) {
                return _mm256_shuffle_epi32(a, m);
            }
#endif
        };

        template <>
        struct vpshufd<0, 1, 2, 3>
            : public select_arg_1<__m128i> {};

        template <unsigned _P>
        struct splat_v2f64 : public vshufpd<_P, _P> {};

        template <unsigned _P>
        struct splat_v4f32 : public vshufps<_P, _P, _P, _P> {};

        template <unsigned _P>
        struct splat_v2u64
            : public vpshufd<2*_P,2*_P+1, 2*_P,2*_P+1> {};

        template <unsigned _P>
        struct splat_v4u32 : public vpshufd<_P, _P, _P, _P> {};

        template <unsigned _P>
        struct splat_v8u16 {
            static __m128i v(__m128i a) {
#if defined (__SSSE3__)
                const __m128i msk=const_v16u8<
                    (_P&7)*2, (_P&7)*2+1,
                    (_P&7)*2, (_P&7)*2+1,
                    (_P&7)*2, (_P&7)*2+1,
                    (_P&7)*2, (_P&7)*2+1,
                    (_P&7)*2, (_P&7)*2+1,
                    (_P&7)*2, (_P&7)*2+1,
                    (_P&7)*2, (_P&7)*2+1,
                    (_P&7)*2, (_P&7)*2+1>::iv();
                return _mm_shuffle_epi8(a, msk);
#else
                __m128i t;
                if (_P > 3) {
                    const int ph= _P & 3;
                    t = vpshufhw<ph, ph, ph, ph>::v(a);
                    t = vpshufd<2, 2, 2, 2>::v(t);
                } else {
                    t = vpshuflw<_P, _P, _P, _P>::v(a);
                    t = vpshufd<0, 0, 0, 0>::v(t);
                }
                return t;
#endif
            }
        };

        struct vunpckhpd {
            static __m128d v(__m128d a, __m128d b) {
                return _mm_unpackhi_pd(a, b);
            }
            static __m128d v(__m128d a) {
                return v(a, a);
            }
#if defined (__AVX__)
            static __m256d v(__m256d a, __m256d b) {
                return _mm256_unpackhi_pd(a, b);
            }
            static __m256d v(__m256d a) {
                return v(a, a);
            }
#endif
        };

        struct vunpcklpd {
            static __m128d v(__m128d a, __m128d b) {
                return _mm_unpacklo_pd(a, b);
            }
            static __m128d v(__m128d a) {
                return v(a, a);
            }
#if defined (__AVX__)
            static __m256d v(__m256d a, __m256d b) {
                return _mm256_unpacklo_pd(a, b);
            }
            static __m256d v(__m256d a) {
                return v(a, a);
            }
#endif
        };

        struct vunpcklps {
            static __m128 v(__m128 a, __m128 b) {
                return _mm_unpacklo_ps(a, b);
            }
            static __m128 v(__m128 a) {
                return v(a, a);
            }
#if defined (__AVX__)
            static __m256 v(__m256 a, __m256 b) {
                return _mm256_unpacklo_ps(a, b);
            }
            static __m256 v(__m256 a) {
                return v(a, a);
            }
#endif

        };

        struct vunpckhps {
            static __m128 v(__m128 a, __m128 b) {
                return _mm_unpackhi_ps(a, b);
            }
            static __m128 v(__m128 a) {
                return v(a, a);
            }
#if defined (__AVX__)
            static __m256 v(__m256 a, __m256 b) {
                return _mm256_unpackhi_ps(a, b);
            }
            static __m256 v(__m256 a) {
                return v(a, a);
            }
#endif
        };

        struct vpunpcklqdq {
            static __m128i v(__m128i a, __m128i b) {
                return _mm_unpacklo_epi64(a, b);
            }
            static __m128i v(__m128i a) {
                return v(a, a);
            }
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i b) {
                return _mm256_unpacklo_epi64(a, b);
            }
            static __m256i v(__m256i a) {
                return v(a, a);
            }
#endif
        };

        struct vpunpckhqdq {
            static __m128i v(__m128i a, __m128i b) {
                return _mm_unpackhi_epi64(a, b);
            }
            static __m128i v(__m128i a) {
                return v(a, a);
            }
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i b) {
                return _mm256_unpackhi_epi64(a, b);
            }
            static __m256i v(__m256i a) {
                return v(a, a);
            }
#endif
        };

        struct vpunpckldq {
            static __m128i v(__m128i a, __m128i b) {
                return _mm_unpacklo_epi32(a, b);
            }
            static __m128i v(__m128i a) {
                return v(a, a);
            }
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i b) {
                return _mm256_unpacklo_epi32(a, b);
            }
            static __m256i v(__m256i a) {
                return v(a, a);
            }
#endif
        };

        struct vpunpckhdq {
            static __m128i v(__m128i a, __m128i b) {
                return _mm_unpackhi_epi32(a, b);
            }
            static __m128i v(__m128i a) {
                return v(a, a);
            }
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i b) {
                return _mm256_unpackhi_epi32(a, b);
            }
            static __m256i v(__m256i a) {
                return v(a, a);
            }
#endif
        };

        struct vpunpcklwd {
            static __m128i v(__m128i a, __m128i b) {
                return _mm_unpacklo_epi16(a, b);
            }
            static __m128i v(__m128i a) {
                return v(a, a);
            }
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i b) {
                return _mm256_unpacklo_epi16(a, b);
            }
            static __m256i v(__m256i a) {
                return v(a, a);
            }
#endif
        };

        struct vpunpckhwd {
            static __m128i v(__m128i a, __m128i b) {
                return _mm_unpackhi_epi16(a, b);
            }
            static __m128i v(__m128i a) {
                return v(a, a);
            }
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i b) {
                return _mm256_unpackhi_epi16(a, b);
            }
            static __m256i v(__m256i a) {
                return v(a, a);
            }
#endif
        };

        struct vpshufb {
            static __m128i v(__m128i a, __m128i msk);
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i msk) {
                return _mm256_shuffle_epi8(a, msk);
            }
#endif
        };

        struct vpmovzxwd {
            static __m128i v(__m128i a, __m128i b) {
                static_cast<void>(b);
                return v(a);
            }
            static __m128i v(__m128i a) {
#if defined (__SSE4_1__)
                return _mm_cvtepu16_epi32(a);
#else
                return _mm_unpacklo_epi16(a,
                                          _mm_setzero_si128());
#endif
            }
        };

        struct vpmovzxdq {
            static __m128i v(__m128i a, __m128i b) {
                static_cast<void>(b);
                return v(a);
            }
            static __m128i v(__m128i a) {
#if defined (__SSE4_1__)
                return _mm_cvtepu32_epi64(a);
#else
                return _mm_unpacklo_epi32(a,
                                          _mm_setzero_si128());
#endif
            }
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i b) {
                static_cast<void>(b);
                return v(a);
            }
            static __m256i v(__m256i a) {
                return _mm256_cvtepu32_epi64(_mm256_castsi256_si128(a));
            }
#endif
        };

        struct vpsllb {
            static __m128i v(__m128i a, unsigned shift);
        };

        struct vpsllw {
            static __m128i v(__m128i a, __m128i shift) {
                return _mm_sll_epi16(a, shift);
            }
            static __m128i v(__m128i a, unsigned shift) {
                __m128i sh= _mm_cvtsi32_si128(shift);
                return v(a, sh);
            }
        };

        template <unsigned _P>
        struct vpsllw_const : public vpsllw {
            static __m128i v(__m128i a) {
                if (_P>15)
                    return make_zero_int::v();
                return _mm_slli_epi16(a, _P);
            }
        };

        template <>
        struct vpsllw_const<0> : public select_arg_1<__m128i> {};

        template <>
        struct vpsllw_const<1> : public vpsllw {
            static __m128i v(__m128i a) {
                return _mm_add_epi16(a, a);
            }
        };

        struct vpslld {
            static __m128i v(__m128i a, __m128i shift) {
                return _mm_sll_epi32(a, shift);
            }
            static __m128i v(__m128i a, unsigned shift) {
                __m128i sh= _mm_cvtsi32_si128(shift);
                return v(a, sh);
            }
        };

        template <unsigned _P>
        struct vpslld_const : public vpslld {
            static __m128i v(__m128i a) {
                if (_P>31)
                    return make_zero_int::v();
                return _mm_slli_epi32(a, _P);
            }
        };

        template <>
        struct vpslld_const<0> : public select_arg_1<__m128i> {};

        template <>
        struct vpslld_const<1> : public vpslld {
            static __m128i v(__m128i a) {
                return _mm_add_epi32(a, a);
            }
        };

        struct vpsllq {
            static __m128i v(__m128i a, __m128i shift) {
                return _mm_sll_epi64(a, shift);
            }
            static __m128i v(__m128i a, unsigned shift) {
                __m128i sh= _mm_cvtsi32_si128(shift);
                return v(a, sh);
            }
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m128i shift) {
                return _mm256_sll_epi64(a, shift);
            }
            static __m256i v(__m256i a, unsigned shift) {
                __m128i sh= _mm_cvtsi32_si128(shift);
                return v(a, sh);
            }
#endif
        };

        template <unsigned _P>
        struct vpsllq_const : public vpsllq {
            static __m128i v(__m128i a) {
                if (_P>63)
                    return make_zero_int::v();
                return _mm_slli_epi64(a, _P);
            }
#if defined (__AVX2__)
            static __m256i v(__m256i a) {
                if (_P>63)
                    return _mm256_setzero_si256();
                return _mm256_slli_epi64(a, _P);
            }
#endif
        };

        template <>
        struct vpsllq_const<0> : public select_arg_1<__m128i> {};

        template <>
        struct vpsllq_const<1> : public vpsllq {
            static __m128i v(__m128i a) {
                return _mm_add_epi64(a, a);
            }
        };

        struct vpsrlb {
            static __m128i v(__m128i a, unsigned shift);
        };


        struct vpsrlw {
            static __m128i v(__m128i a, __m128i shift) {
                return _mm_srl_epi16(a, shift);
            }
            static __m128i v(__m128i a, unsigned shift) {
                __m128i sh= _mm_cvtsi32_si128(shift);
                return v(a, sh);
            }
        };

        template <unsigned _P>
        struct vpsrlw_const : public vpsrlw {
            static __m128i v(__m128i a) {
                if (_P>15)
                    return make_zero_int::v();
                return _mm_srli_epi16(a, _P);
            }
        };

        template <>
        struct vpsrlw_const<0> : public select_arg_1<__m128i> {};

        struct vpsrld {
            static __m128i v(__m128i a, __m128i shift) {
                return _mm_srl_epi32(a, shift);
            }
            static __m128i v(__m128i a, unsigned shift) {
                __m128i sh= _mm_cvtsi32_si128(shift);
                return v(a, sh);
            }
        };

        template <unsigned _P>
        struct vpsrld_const : public vpsrld {
            static __m128i v(__m128i a) {
                if (_P>31)
                    return make_zero_int::v();
                return _mm_srli_epi32(a, _P);
            }
        };

        template <>
        struct vpsrld_const<0> : public select_arg_1<__m128i> {};

        struct vpsrlq {
            static __m128i v(__m128i a, __m128i shift) {
                return _mm_srl_epi64(a, shift);
            }
            static __m128i v(__m128i a, unsigned shift) {
                __m128i sh= _mm_cvtsi32_si128(shift);
                return v(a, sh);
            }
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m128i shift) {
                return _mm256_srl_epi64(a, shift);
            }
            static __m256i v(__m256i a, unsigned shift) {
                __m128i sh= _mm_cvtsi32_si128(shift);
                return v(a, sh);
            }
#endif
        };

        template <unsigned _P>
        struct vpsrlq_const : public vpsrlq {
            static __m128i v(__m128i a) {
                if (_P>63)
                    return make_zero_int::v();
                return _mm_srli_epi64(a, _P);
            }
        };

        template <>
        struct vpsrlq_const<0> : public select_arg_1<__m128i> {};

        struct vpsrab {
            static __m128i v(__m128i a, unsigned shift);
        };


        struct vpsraw {
            static __m128i v(__m128i a, __m128i shift) {
                return _mm_sra_epi16(a, shift);
            }
            static __m128i v(__m128i a, unsigned shift) {
                __m128i sh= _mm_cvtsi32_si128(shift);
                return v(a, sh);
            }
        };

        template <unsigned _P>
        struct vpsraw_const : public vpsraw {
            static __m128i v(__m128i a) {
                return _mm_srai_epi16(a, _P);
            }
        };

        template <>
        struct vpsraw_const<0> : public select_arg_1<__m128i> {};

        struct vpsrad {
            static __m128i v(__m128i a, __m128i shift) {
                return _mm_sra_epi32(a, shift);
            }
            static __m128i v(__m128i a, unsigned shift) {
                return _mm_srai_epi32(a, shift);
            }
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m128i shift) {
                return _mm256_sra_epi32(a, shift);
            }
            static __m256i v(__m256i a, unsigned shift) {
                return _mm256_srai_epi32(a, shift);
            }
#endif
        };

        template <unsigned _P>
        struct vpsrad_const : public vpsrad {
            static __m128i v(__m128i a) {
                return _mm_srai_epi32(a, _P);
            }
        };

        template <>
        struct vpsrad_const<0> : public select_arg_1<__m128i> {};

        struct vpsraq {
            static __m128i v(__m128i a, unsigned shift);

            static __m128i v(__m128i a, __m128i shift) {
                unsigned sh= _mm_cvtsi128_si32(shift);
                return v(a, sh);
            }

#if defined (__AVX2__)
            static __m256i v(__m256i a, unsigned shift);
            static __m256i v(__m256i a, __m128i shift) {
                unsigned sh= _mm_cvtsi128_si32(shift);
                return v(a, sh);
            }
#endif

        };

        template <unsigned _P>
        struct vpsraq_const : public vpsraq {
            static __m128i v(__m128i a);
        };

        template <>
        struct vpsraq_const<0> : public select_arg_1<__m128i> {};

        template <>
        struct vpsraq_const<63> {
            static __m128i v(__m128i a) {
                __m128i sgn= vpsrad_const<31>::v(a);
                return vpshufd<1, 1, 3, 3>::v(sgn);
            }
        };

        template <unsigned _P>
        struct vpslldq {
            static __m128i v(__m128i a) {
                if (_P>15)
                    return make_zero_int::v();
                return _mm_slli_si128(a, _P);
            }            
#if defined (__AVX2__)
            static __m256i v(__m256i a) {
                if (_P>15)
                    return _mm256_set1_epi32(0);
                return _mm256_slli_si256(a, _P);
            }            
#endif
        };
        template <>
        struct vpslldq<0> : public select_arg_1<__m128i> {};

        template <unsigned _P>
        struct vpsrldq {
            static __m128i v(__m128i a) {
                if (_P>15)
                    return make_zero_int::v();
                return _mm_srli_si128(a, _P);
            }
#if defined (__AVX2__)
            static __m256i v(__m256i a) {
                if (_P>15)
                    return _mm256_set1_epi32(0);
                return _mm256_srli_si256(a, _P);
            }            
#endif
        };
        template <>
        struct vpsrldq<0> : public select_arg_1<__m128i> {};

#if defined (__AVX2__)

        struct vpsxxvw {
            // select uint16_t with the number 0, 2, 4, 6, 8, 10, 12, 14
            static __m128i v(__m256i rt);
        };

        struct vpsllvw {
            static __m128i v(__m128i a, __m128i s);
        };

        struct vpsrlvw {
            static __m128i v(__m128i a, __m128i s);
        };

        struct vpsravw {
            static __m128i v(__m128i a, __m128i s);
        };
#endif

            
#if !defined (__AVX2__)
        // helper class for vpsllvd, vpsrlvd and vpsravd
        struct vpsxxvd {
            // perform element _IDX of a, s
            template <uint8_t _IDX, 
                      typename _SINGLE_SHIFT>
            static
            __m128i vi(__m128i a, __m128i s);
            // perform all elements
            template <typename _SINGLE_SHIFT>
            static
            __m128i v(__m128i a, __m128i s);
                
        };
#endif

            
        struct vpsllvd {
            static __m128i v(__m128i a, __m128i s);
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i s) {
                return _mm256_sllv_epi32(a, s);
            }
#endif
        };

        struct vpsrlvd {
            static __m128i v(__m128i a, __m128i s);
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i s) {
                return _mm256_srlv_epi32(a, s);
            }
#endif
        };

        struct vpsravd {
            static __m128i v(__m128i a, __m128i s);
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i s) {
                return _mm256_srav_epi32(a, s);
            }
#endif
        };

        struct vpsllvq {
            static __m128i v(__m128i a, __m128i s);
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i s) {
                return _mm256_sllv_epi64(a, s);
            }
#endif
        };

        struct vpsrlvq {
            static __m128i v(__m128i a, __m128i s);
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i s) {
                return _mm256_srlv_epi64(a, s);
            }
#endif
        };

        struct vpsravq {
            static __m128i v(__m128i a, __m128i s);
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i s);
#endif
        };

        struct vpmullb {
            static
            __m128i v(__m128i a, __m128i b);
#if defined (__AVX2__)
            // static
            // __m256i v(__m256i a, __m256i b);
#endif
        };

        struct vpmullw {
            static __m128i v(__m128i a, __m128i b) {
                return _mm_mullo_epi16(a, b);
            }
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i b) {
                return _mm256_mullo_epi16(a, b);
            }
#endif
        };

        struct vpmulhw {
            static __m128i v(__m128i a, __m128i b) {
                return _mm_mulhi_epi16(a, b);
            }
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i b) {
                return _mm256_mulhi_epi16(a, b);
            }
#endif
        };

        struct vpmulhuw {
            static __m128i v(__m128i a, __m128i b) {
                return _mm_mulhi_epu16(a, b);
            }
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i b) {
                return _mm256_mulhi_epu16(a, b);
            }
#endif
        };

        struct vpmulld {
            static __m128i v(__m128i a, __m128i b);
            // same as v but multiplies only the low halfes of a/b
            static __m128i lh(__m128i a, __m128i b);
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i b) {
                return _mm256_mullo_epi32(a, b);
            }
#endif
        };

        struct vpmulhud {
            static __m128i v(__m128i a, __m128i b);
        };

        struct vpmulhd {
            static __m128i v(__m128i a, __m128i b);
        };

        struct vpmullq {
            static __m128i v(__m128i a, __m128i b);
#if defined (__AVX2__)
            static __m256i v(__m256i a, __m256i b);
#endif
        };
        
        struct pavgb {
            static
            __m128i v(__m128i a, __m128i b) {
                return _mm_avg_epu8(a, b);
            };
#if defined (__AVX2__)
            static
            __m256i v(__m256i a, __m256i b) {
                return _mm256_avg_epu8(a, b);
            }
#endif
        };
                
        struct pavgsb {
            static
            __m128i v(__m128i a, __m128i b) {
                const __m128i cmin=_mm_set1_epi8(int8_t(-128));
                __m128i au=_mm_add_epi8(a, cmin);
                __m128i bu=_mm_add_epi8(b, cmin);
                __m128i avgu=pavgb::v(au, bu);
                __m128i r=_mm_add_epi8(cmin, avgu);
                return r;
            }
#if defined (__AVX2__)
            static
            __m256i v(__m256i a, __m256i b) {
                const __m256i cmin=_mm256_set1_epi8(int8_t(-128));
                __m256i au=_mm256_add_epi8(a, cmin);
                __m256i bu=_mm256_add_epi8(b, cmin);
                __m256i avgu=pavgb::v(au, bu);
                __m256i r=_mm256_add_epi8(cmin, avgu);
                return r;
            }
#endif
        };

        struct pavgw {
            static
            __m128i v(__m128i a, __m128i b) {
                return _mm_avg_epu16(a, b);
            };
#if defined (__AVX2__)
            static
            __m256i v(__m256i a, __m256i b) {
                return _mm256_avg_epu16(a, b);
            }
#endif
        };
        
        
        struct pavgsw {
            static
            __m128i v(__m128i a, __m128i b) {
                const __m128i cmin=_mm_set1_epi16(int16_t(-32768));
                __m128i au=_mm_add_epi16(a, cmin);
                __m128i bu=_mm_add_epi16(b, cmin);
                __m128i avgu=pavgw::v(au, bu);
                __m128i r=_mm_add_epi16(cmin, avgu);
                return r;
            }
#if defined (__AVX2__)
            static
            __m256i v(__m256i a, __m256i b) {
                const __m256i cmin=_mm256_set1_epi16(int16_t(-32768));
                __m256i au=_mm256_add_epi16(a, cmin);
                __m256i bu=_mm256_add_epi16(b, cmin);
                __m256i avgu=pavgw::v(au, bu);
                __m256i r=_mm256_add_epi16(cmin, avgu);
                return r;
            }
#endif
        };

        template <std::size_t _SCALE, typename _T>
        const _T*
        vsib_addr(const _T* base, int32_t idx);

        void
        extract(int32_t& i0, int32_t& i1,
                __m128i idx);

        void
        extract(int32_t& i0, int32_t& i1, int32_t& i2, int32_t& i3,
                __m128i idx);

        // template for vgatherdpd
        template <class _T, class _I>
        struct vgatherdpd {
            template <std::size_t _SCALE>
            static _T
            v(const double* base, const _I& idx);

            template <std::size_t _SCALE>
            static _T
            v(const _T& src, const double* base,
              const _I& idx, const _T& msk);
        };

        // specialization for __m128d, __m128i
        template <>
        struct vgatherdpd<__m128d, __m128i> {
            template <std::size_t _SCALE>
            static __m128d
            v(const double* base, __m128i idx);

            template <std::size_t _SCALE>
            static __m128d
            v(__m128d src, const double* base,
              __m128i idx, __m128d msk);
        };

        // template for vgatherdps
        template <class _T, class _I>
        struct vgatherdps {
            template <std::size_t _SCALE>
            static _T
            v(const float* base, const _I& idx);

            template <std::size_t _SCALE>
            static _T
            v(const _T& src, const float* base,
              const _I& idx, const _T& msk);
        };

        // specialization for __m128, __m128i
        template <>
        struct vgatherdps<__m128, __m128i> {
            template <std::size_t _SCALE>
            static __m128
            v(const float* base, __m128i idx);

            template <std::size_t _SCALE>
            static __m128
            v(__m128 src, const float* base,
              __m128i idx, __m128 msk);
        };


#if defined (__AVX__)
        // specialization for __m256d, __m128i
        template <>
        struct vgatherdpd<__m256d, __m128i> {
            template <std::size_t _SCALE>
            static __m256d
            v(const double* base, __m128i idx);

            template <std::size_t _SCALE>
            static __m256d
            v(__m256d src, const double* base,
              __m128i idx, __m256d msk);
        };

        // specialization for __m256, __m256i
        template <>
        struct vgatherdps<__m256, __m256i> {
            template <std::size_t _SCALE>
            static __m256 v(const float* base,
                            __m256i idx);

            template <std::size_t _SCALE>
            static __m256
            v(__m256 src, const float* base,
              __m256i idx, __m256 msk);
        };
#endif

#if defined (__AVX__)
        struct make_zero_v4f64 {
            static __m256d v() {
                return _mm256_setzero_pd();
            }
            static __m256d v(__m256d a) {
                static_cast<void>(a);
                return v();
            }
            static __m256d v(__m256d a, __m256d b) {
                static_cast<void>(a);
                static_cast<void>(b);
                return v();
            }
        };

        struct make_zero_v8f32 {
            static __m256 v() {
                return _mm256_setzero_ps();
            }
            static __m256 v(__m256 a)  {
                static_cast<void>(a);
                return v();
            }
            static __m256 v(__m256 a, __m256 b) {
                static_cast<void>(a);
                static_cast<void>(b);
                return v();
            }
        };

        template <int _P>
        struct vinsertf128 {
            static __m256d v(__m256d a, __m128d b) {
                return _mm256_insertf128_pd(a, b, _P);
            }
            static __m256d v(__m256d a, __m256d b) {
                return v(a, _mm256_castpd256_pd128(b));
            }
            static __m256d v(__m256d a) {
                return v(a, a);
            }
            static __m256 v(__m256 a, __m128 b) {
                return _mm256_insertf128_ps(a, b, _P);
            }
            static __m256 v(__m256 a, __m256 b) {
                return v(a, _mm256_castps256_ps128(b));
            }
            static __m256 v(__m256 a) {
                return v(a, a);
            }
            static __m256i v(__m256i a, __m128i b) {
                return _mm256_insertf128_si256(a, b, _P);
            }
            static __m256i v(__m256i a, __m256i b) {
                return v(a, _mm256_castsi256_si128(b));
            }
            static __m256i v(__m256i a) {
                return v(a, a);
            }
        };

        template <int _P0, int _P1>
        struct vperm2f128 {
            enum { imm8 = (_P0 & 3) | ((_P1 & 3) << 4) };

            static __m256d v(__m256d a, __m256d b) {
                return _mm256_permute2f128_pd(a, b, imm8);
            }
            static __m256d v(__m256d a) {
                return v(a, a);
            }
            static __m256 v(__m256 a, __m256 b) {
                return _mm256_permute2f128_ps(a, b, imm8);
            }
            static __m256 v(__m256 a) {
                return v(a, a);
            }
            static __m256i v(__m256i a, __m256i b) {
                return _mm256_permute2f128_si256(a, b, imm8);
            }
            static __m256i v(__m256i a) {
                return v(a, a);
            }
        };

        template <unsigned _P0, unsigned _P1,
                  unsigned _P2, unsigned _P3>
        struct vpermilps {
            static __m128 v(__m128 a) {
                constexpr int _p0=_P0;
                constexpr int _p1=_P1;
                constexpr int _p2=_P2;
                constexpr int _p3=_P3;
                const int m=shuffle4<_p0, _p1, _p2, _p3>::val;
                return _mm_permute_ps(a, m & 0xff);
            }
            static __m256 v(__m256 a) {
                constexpr int _p0=_P0;
                constexpr int _p1=_P1;
                constexpr int _p2=_P2;
                constexpr int _p3=_P3;
                const int m=shuffle4<_p0, _p1, _p2, _p3>::val;
                return _mm256_permute_ps(a, m & 0xff);
            }
        };

        template <unsigned _P0, unsigned _P1>
        struct vpermilpd {
            static __m128d v(__m128d a) {
                constexpr int _p0=_P0;
                constexpr int _p1=_P1;
                const int m=shuffle2<_p0, _p1>::val;
                return _mm_permute_pd(a, m & 0xff);
            }
            static __m256d v(__m256d a) {
                constexpr int _p0=_P0;
                constexpr int _p1=_P1;
                const int m=shuffle2<_p0, _p1>::val;
                return _mm256_permute_pd(a, m & 0xff);
            }
        };

        template <typename _V>
        struct vbroadcastss {
        };

        template <>
        struct vbroadcastss<__m128> {
            static
            __m128 v(__m128 a) {
#if defined (__AVX2__)
                return _mm_broadcastss_ps(a);
#else
                return vpermilps<0, 0, 0, 0>::v(a);
#endif
            }
            static
            __m128 v(float f) {
                return _mm_setr_ps(f, f, f, f);
            }
        };

        template <>
        struct vbroadcastss<__m256> {
            static
            __m256 v(__m128 a) {
#if defined (__AVX2__)
                return _mm256_broadcastss_ps(a);
#else
                __m128 sl=vpermilps<0, 0, 0, 0>::v(a);
                __m256 s=_mm256_castps128_ps256(sl);
                __m256 r=vinsertf128<1>::v(s, sl);
                return r;
#endif
            }

            static
            __m256 v(__m256 a) {
                return v(_mm256_castps256_ps128(a));
            }

            static
            __m256 v(float f) {
                return _mm256_setr_ps(f, f, f, f, f, f, f, f);
            }
        };

        template <typename _V>
        struct vbroadcastsd {
        };

        template <>
        struct vbroadcastsd<__m128d> {
            static
            __m128d v(__m128d a) {
#if defined (__AVX2__)
                return _mm_movedup_pd(a);
#else
                return vpermilpd<0, 0>::v(a);
#endif
            }
            static
            __m128d v(double d) {
                return _mm_setr_pd(d, d);
            }
        };

        template <>
        struct vbroadcastsd<__m256d> {
            static
            __m256d v(__m128d a) {
#if defined (__AVX2__)
                return _mm256_broadcastsd_pd(a);
#else
                __m128d sl=vpermilpd<0, 0>::v(a);
                __m256d s=_mm256_castpd128_pd256(sl);
                __m256d r=vinsertf128<1>::v(s, sl);
                return r;
#endif
            }
            static
            __m256d v(__m256d a) {
                return v(_mm256_castpd256_pd128(a));
            }

            static
            __m256d v(double d) {
                return _mm256_setr_pd(d, d, d, d);
            }
        };

        template <typename _V>
        struct vbroadcastd {
        };

        template <>
        struct vbroadcastd<__m128i> {
            static
            __m128i v(__m128i a) {
                return vpshufd<0, 0, 0, 0>::v(a);
            }
            static
            __m128i v(int32_t i) {
                return _mm_setr_epi32(i, i, i, i);
            }
        };

        template <>
        struct vbroadcastd<__m256i> {
            static
            __m256i v(__m128i a) {
#if defined (__AVX2__)
                return _mm256_broadcastd_epi32(a);
#else
                __m128i b=vbroadcastd<__m128i>::v(a);
                __m128d bd=_mm_castsi128_pd(b);
                __m256d s=_mm256_castpd128_pd256(bd);
                __m256d r=vinsertf128<1>::v(s, bd);
                __m256i ri=_mm256_castpd_si256(r);
                return ri;
#endif
            }

            static
            __m256i v(__m256i a) {
                return v(_mm256_castsi256_si128(a));
            }

            static
            __m256i v(int32_t i) {
                return _mm256_setr_epi32(i, i, i, i, i, i, i, i);
            }
        };

        template <typename _V>
        struct vbroadcastq {
        };

        template <>
        struct vbroadcastq<__m128i> {
            static
            __m128i v(__m128i a) {
                return vpshufd<0, 1, 0, 1>::v(a);
            }
            static
            __m128i v(int64_t i) {
                return _mm_set_epi64x(i, i);
            }
        };

        template <>
        struct vbroadcastq<__m256i> {
            static
            __m256i v(__m128i a) {
#if defined (__AVX2__)
                return _mm256_broadcastq_epi64(a);
#else
                __m128i b=vbroadcastq<__m128i>::v(a);
                __m128d bd=_mm_castsi128_pd(b);
                __m256d s=_mm256_castpd128_pd256(bd);
                __m256d r=vinsertf128<1>::v(s, bd);
                __m256i ri=_mm256_castpd_si256(r);
                return ri;
#endif
            }

            static
            __m256i v(__m256i a) {
                return v(_mm256_castsi256_si128(a));
            }

            static
            __m256i v(int64_t i) {
                return _mm256_set_epi64x(i, i, i, i);
            }
        };

#endif
    } // namespace x86
} // namespace cftal

inline
__m128i cftal::x86::vpshufb::v(__m128i a, __m128i msk)
{
#if defined (__SSSE3__)
    return _mm_shuffle_epi8(a, msk);
#else
    union {
        __m128i _v;
        int8_t _a[16];
    } s, m, d;
    _mm_store_si128(&s._v, a);
    _mm_store_si128(&m._v, msk);
    for (int i=0; i<16; ++i) {
        int8_t mi=m._a[i];
        int8_t offs=mi & 15;
        int8_t msk=~(mi>>7);
        d._a[i] =  s._a[offs] & msk;
    }
    __m128i r=_mm_load_si128(&d._v);
    return r;
#endif
}

inline
__m128i cftal::x86::vpsllb::v(__m128i a, unsigned shift)
{
    const __m128i odd_mask = const_v16u8<0x00, 0xff, 0x00, 0xff,
                                         0x00, 0xff, 0x00, 0xff,
                                         0x00, 0xff, 0x00, 0xff,
                                         0x00, 0xff, 0x00, 0xff>::iv();
    const __m128i even_mask = const_v16u8<0xff, 0x00, 0xff, 0x00,
                                          0xff, 0x00, 0xff, 0x00,
                                          0xff, 0x00, 0xff, 0x00,
                                          0xff, 0x00, 0xff, 0x00>::iv();
    __m128i re = _mm_slli_epi16(a, shift);
    re = _mm_and_si128(re, even_mask);
    __m128i ro = _mm_and_si128(a, odd_mask);
    ro = _mm_slli_epi16(ro, shift);
    __m128i r= _mm_or_si128(re, ro);
    return r;
}

inline
__m128i cftal::x86::vpsrlb::v(__m128i a, unsigned shift)
{
    const __m128i odd_mask = const_v16u8<0x00, 0xff, 0x00, 0xff,
                                         0x00, 0xff, 0x00, 0xff,
                                         0x00, 0xff, 0x00, 0xff,
                                         0x00, 0xff, 0x00, 0xff>::iv();
    const __m128i even_mask = const_v16u8<0xff, 0x00, 0xff, 0x00,
                                          0xff, 0x00, 0xff, 0x00,
                                          0xff, 0x00, 0xff, 0x00,
                                          0xff, 0x00, 0xff, 0x00>::iv();
    __m128i ro = _mm_srli_epi16(a, shift);
    ro = _mm_and_si128(ro, odd_mask);
    __m128i re = _mm_and_si128(a, even_mask);
    re = _mm_srli_epi16(re, shift);
    __m128i r= _mm_or_si128(re, ro);
    return r;
}

inline
__m128i cftal::x86::vpsrab::v(__m128i a, unsigned shift)
{
    const __m128i odd_mask = const_v16u8<0x00, 0xff, 0x00, 0xff,
                                         0x00, 0xff, 0x00, 0xff,
                                         0x00, 0xff, 0x00, 0xff,
                                         0x00, 0xff, 0x00, 0xff>::iv();
    __m128i ro = _mm_srai_epi16(a, shift);
    ro = _mm_and_si128(ro, odd_mask);
    __m128i re = _mm_slli_epi16(a, 8);
    re =_mm_srai_epi16(re, shift);
    re =_mm_srli_epi16(re, 8);
    __m128i r= _mm_or_si128(re, ro);
    return r;
}

inline
__m128i cftal::x86::vpsraq::v(__m128i a, unsigned shift)
{
    // signed right shift from unsigned right shift
    // t = - (x>>63)
    // r = ((x^t) >> shift) ^ t
    __m128i sh = _mm_cvtsi32_si128(shift);
    __m128i z= _mm_setzero_si128();
    __m128i t= _mm_sub_epi64(z, vpsrlq::v(a, 63));
    __m128i r= vpsrlq::v(_mm_xor_si128(a, t), sh);
    r = _mm_xor_si128(r, t);
    return r;
}

#if defined (__AVX2__)
inline
__m256i cftal::x86::vpsraq::v(__m256i a, unsigned shift)
{
    // signed right shift from unsigned right shift
    // t = - (x>>63)
    // r = ((x^t) >> shift) ^ t
    __m128i sh = _mm_cvtsi32_si128(shift);
    __m256i z= _mm256_setzero_si256();
    __m256i t= _mm256_sub_epi64(z, vpsrlq::v(a, 63));
    __m256i r= vpsrlq::v(_mm256_xor_si256(a, t), sh);
    r = _mm256_xor_si256(r, t);
    return r;
}

inline
__m128i cftal::x86::vpsxxvw::v(__m256i i)
{
    const __m256i m= _mm256_setr_epi8(0, 1, 4, 5, 8, 9, 12, 13,
                                      0, 1, 4, 5, 8, 9, 12, 13,
                                      0, 1, 4, 5, 8, 9, 12, 13,
                                      0, 1, 4, 5, 8, 9, 12, 13);
    // shuffle the interesting bytes into the low/high halfes of the
    // two lanes
    __m256i it=_mm256_shuffle_epi8(i, m);
    // and use vpermq to create the values in the low half
    const int p=shuffle4<0, 2, 0, 2>::val;
    __m256i rt=_mm256_permute4x64_epi64(it, p);
    __m128i r=_mm256_castsi256_si128(rt);
    return r;
}

inline
__m128i cftal::x86::vpsllvw::v(__m128i a, __m128i s)
{
    // zero extension
    __m256i at=_mm256_cvtepu16_epi32(a);
    __m256i st=_mm256_cvtepi16_epi32(s);
    __m256i rt=_mm256_sllv_epi32(at, st);
    __m128i r=vpsxxvw::v(rt);
    return r;
}

inline
__m128i cftal::x86::vpsrlvw::v(__m128i a, __m128i s)
{
    // zero extension
    __m256i at=_mm256_cvtepu16_epi32(a);
    __m256i st=_mm256_cvtepi16_epi32(s);
    __m256i rt=_mm256_srlv_epi32(at, st);
    __m128i r=vpsxxvw::v(rt);
    return r;
}

inline
__m128i cftal::x86::vpsravw::v(__m128i a, __m128i s)
{
    // sign extension
    __m256i at=_mm256_cvtepi16_epi32(a);
    __m256i st=_mm256_cvtepi16_epi32(s);
    __m256i rt=_mm256_srav_epi32(at, st);
    __m128i r=vpsxxvw::v(rt);
    return r;
}
#endif


#if !defined (__AVX2__)
template <cftal::uint8_t _IDX, typename _SINGLE_SHIFT>
inline
__m128i cftal::x86::vpsxxvd::vi(__m128i a, __m128i s)
{
    __m128i si= s;
    if (_IDX == 0) {
        const __m128i msk= const_v4u32<uint32_t(-1), 0, 0, 0>::iv();
        si = _mm_and_si128(si, msk);
    } else {
#if defined (__SSSE3__)
        constexpr const uint8_t c00 = _IDX*4 + 0;
        constexpr const uint8_t c01 = _IDX*4 + 1;
        constexpr const uint8_t c02 = _IDX*4 + 2;
        constexpr const uint8_t c03 = _IDX*4 + 3;
        constexpr const uint8_t cxx = -1;
        const __m128i msk=const_v16u8<c00, c01, c02, c03,
                                      cxx, cxx, cxx, cxx,
                                      cxx, cxx, cxx, cxx,
                                      cxx, cxx, cxx, cxx>::iv();
        si=vpshufb::v(si, msk);                                        
#else
        si = vpshufd<_IDX, _IDX, _IDX, _IDX>::v(si);
        const __m128i msk= const_v4u32<uint32_t(-1), 0, 0, 0>::iv();
        si = _mm_and_si128(si, msk);
#endif        
    }
    constexpr const uint32_t m0= _IDX==0 ? -1 : 0;
    constexpr const uint32_t m1= _IDX==1 ? -1 : 0;
    constexpr const uint32_t m2= _IDX==2 ? -1 : 0;
    constexpr const uint32_t m3= _IDX==3 ? -1 : 0;
    const __m128i amsk= const_v4u32<m0, m1, m2, m3>::iv();
    __m128i r=_mm_and_si128(a, amsk);
    r = _SINGLE_SHIFT::v(r, si);
    return r;
}

template <typename _SINGLE_SHIFT>
inline
__m128i cftal::x86::vpsxxvd::v(__m128i a, __m128i s)
{
    __m128i r=vi<0, _SINGLE_SHIFT>(a, s);
    __m128i ri=vi<1, _SINGLE_SHIFT>(a, s);
    r=_mm_or_si128(r, ri);
    ri=vi<2, _SINGLE_SHIFT>(a, s);
    r=_mm_or_si128(r, ri);
    ri=vi<3, _SINGLE_SHIFT>(a, s);
    r=_mm_or_si128(r, ri);    
    return r;
}
#endif

inline
__m128i cftal::x86::vpsllvd::v(__m128i a, __m128i s)
{
#if defined (__AVX2__)
    return _mm_sllv_epi32(a, s);
#else
    return vpsxxvd::v<vpslld>(a, s);
#endif
}

inline
__m128i cftal::x86::vpsrlvd::v(__m128i a, __m128i s)
{
#if defined (__AVX2__)
    return _mm_srlv_epi32(a, s);
#else
    return vpsxxvd::v<vpsrld>(a, s);
#endif
}

inline
__m128i cftal::x86::vpsravd::v(__m128i a, __m128i s)
{
#if defined (__AVX2__)
    return _mm_srav_epi32(a, s);
#else
    return vpsxxvd::v<vpsrad>(a, s);
#endif
}

inline
__m128i cftal::x86::vpsllvq::v(__m128i a, __m128i s)
{
#if defined (__AVX2__)
    return _mm_sllv_epi64(a, s);
#else
    __m128i s0 = s;
    __m128i s1 = vpshufd<2, 3, 2, 3>::v(s);
    __m128i r = vpsllq::v(a, s0);
    __m128i r1= vpsllq::v(a, s1);
    r = select_u64<true, false>(r, r1);
    return r;
#endif
}

inline
__m128i cftal::x86::vpsrlvq::v(__m128i a, __m128i s)
{
#if defined (__AVX2__)
    return _mm_srlv_epi64(a, s);
#else
    __m128i s0 = s;
    __m128i s1 = vpshufd<2, 3, 2, 3>::v(s);
    __m128i r = vpsrlq::v(a, s0);
    __m128i r1= vpsrlq::v(a, s1);
    r = select_u64<true, false>(r, r1);
    return r;
#endif
}

inline
__m128i cftal::x86::vpsravq::v(__m128i a, __m128i sh)
{
    // signed right shift from unsigned right shift
    // t = - (x>>63)
    // r = ((x^t) >> shift) ^ t
    __m128i z= _mm_setzero_si128();
    __m128i t= _mm_sub_epi64(z, vpsrlq::v(a, 63));
    __m128i r= vpsrlvq::v(_mm_xor_si128(a, t), sh);
    r = _mm_xor_si128(r, t);
    return r;
}

#if defined (__AVX2__)
inline
__m256i cftal::x86::vpsravq::v(__m256i a, __m256i sh)
{
    // signed right shift from unsigned right shift
    // t = - (x>>63)
    // r = ((x^t) >> shift) ^ t
    __m256i z= _mm256_setzero_si256();
    __m256i t= _mm256_sub_epi64(z, vpsrlq::v(a, 63));
    __m256i r= vpsrlvq::v(_mm256_xor_si256(a, t), sh);
    r = _mm256_xor_si256(r, t);
    return r;
}

#endif


template <unsigned _S>
inline
__m128i cftal::x86::vpsraq_const<_S>::v(__m128i a)
{
    __m128i r;
    if (_S <= 32) {
        // high parts of result.
        __m128i sgnbits= vpsrad_const<_S>::v(a);
        // low parts of result.
        __m128i allbits= vpsrlq_const<_S>::v(a);
#if defined (__SSE4_1__)
        r = select_v4u32<0, 1, 0, 1>::v(sgnbits, allbits);
#else
        // clear the low uint32_t of sgnbits
        __m128i msk= const_v4u32<0, uint32_t(-1), 0, uint32_t(-1)>::iv();
        sgnbits = _mm_and_si128(sgnbits, msk);
        // works because high uint32_t of sgnbits contains
        // either the same pattern as allbits or ones
        r= _mm_or_si128(allbits, sgnbits);
#endif
    } else {
#if defined (__SSE4_1__)
        r= vpshufd<1, 3, 1, 3>::v(a);
        r= vpsrad_const<_S-32>::v(r);
        r= _mm_cvtepi32_epi64(r);
#else
        // future sign bits.
        __m128i sgnbits= vpsrad_const<31>::v(a);
        // result bits right shifted by shift - 32
        __m128i allbits= vpsrad_const<_S-32>::v(a);
        // result bits correctly located.
        allbits = vpsrlq_const<32>::v(allbits);
        // clear the low uint32_t of sgnbits
        __m128i msk= const_v4u32<0, uint32_t(-1), 0, uint32_t(-1)>::iv();
        sgnbits = _mm_and_si128(sgnbits, msk);
        // works because high uint32_t of sgnbits contains
        // either the same pattern as allbits or ones
        r= _mm_or_si128(allbits, sgnbits);
#endif
    }
    return r;
}

inline
__m128i cftal::x86::vpmullb::v(__m128i a, __m128i b)
{
    __m128i oa=_mm_srli_epi16(a, 8);
    __m128i ob=_mm_srli_epi16(b, 8);
    __m128i pe=_mm_mullo_epi16(a, b);
    __m128i po=_mm_mullo_epi16(oa, ob);
    po=_mm_slli_epi16(po, 8);
    const __m128i even_mask = const_v16u8<0xff, 0x00, 0xff, 0x00,
                                          0xff, 0x00, 0xff, 0x00,
                                          0xff, 0x00, 0xff, 0x00,
                                          0xff, 0x00, 0xff, 0x00>::iv();
    pe=_mm_and_si128(pe, even_mask);
    __m128i r= _mm_or_si128(po, pe);
    return r;
}


inline
__m128i cftal::x86::vpmulld::lh(__m128i a, __m128i b)
{
#if defined (__SSE4_1__)
    return v(a, b);
#else
    __m128i as= vpshufd<0, 0, 1, 1>::v(a);
    __m128i bs= vpshufd<0, 0, 1, 1>::v(b);
    __m128i rs=_mm_mul_epu32(as, bs);
    __m128i r= vpshufd<0, 2, 0, 2>::v(rs);
    return r;
#endif
}

inline
__m128i cftal::x86::vpmulld::v(__m128i a, __m128i b)
{
#if defined (__SSE4_1__)
    return _mm_mullo_epi32(a, b);
#else
    // 0, 2 at positions 0 2
    __m128i e= _mm_mul_epu32(a, b);
    // 1, 3 at positions 0 2
    __m128i o= _mm_mul_epu32(vpsrlq_const<32>::v(a),
                             vpsrlq_const<32>::v(b));
    const __m128i msk = const_v4u32<uint32_t(-1), 0, uint32_t(-1), 0>::iv();
    e = _mm_and_si128(e, msk);
    o = _mm_slli_epi64(o, 32);
    e = _mm_or_si128(e, o);
    return e;
#endif
}

inline
__m128i cftal::x86::vpmulhud::v(__m128i a, __m128i b)
{
    // return _mm_mulhi_epu32(a(), b());
    // 0, 2 at positions 1 3
    __m128i e= _mm_mul_epu32(a, b);
    // 1, 3 at positions 1 3
    __m128i o= _mm_mul_epu32(vpshufd<1, 0, 3, 2>::v(a),
                             vpshufd<1, 0, 3, 2>::v(b));
    // 0, 2 at position 0, 2
    e = _mm_srli_epi64(e, 32);
#if defined (__SSE4_1__)
    return select_v4u32<1, 0, 1, 0>::v(e, o);
#else
    const __m128i msk = const_v4u32<0, uint32_t(-1), 0, uint32_t(-1)>::iv();
    o = _mm_and_si128(o, msk);
    return _mm_or_si128(e, o);
#endif
}

inline
__m128i cftal::x86::vpmulhd::v(__m128i x, __m128i y)
{
#if defined(__SSE4_1__)
    // 0, 2 at positions 1 3
    __m128i e= _mm_mul_epi32(x, y);
    // 1, 3 at positions 1 3
    __m128i o= _mm_mul_epi32(vpshufd<1, 0, 3, 2>::v(x),
                             vpshufd<1, 0, 3, 2>::v(y));
    // 0, 2 at positions 0 2
    e = _mm_srli_epi64(e, 32);
    return select_v4u32<1, 0, 1, 0>::v(e, o);
#else
    // muluh(x,y) = mulsh(x,y) + and(x, xsign(y)) + and(y, xsign(x));
    // mulsh(x,y) = muluh(x,y) - and(x, xsign(y)) - and(y, xsign(x));
    __m128i p= vpmulhud::v(x, y);
    __m128i xsgn_y= vpsrad_const<31>::v(y);
    __m128i xsgn_x= vpsrad_const<31>::v(x);
    __m128i x_and_xsgn_y = _mm_and_si128(x, xsgn_y);
    __m128i y_and_xsgn_x = _mm_and_si128(y, xsgn_x);
    p = _mm_sub_epi32(p, x_and_xsgn_y);
    p = _mm_sub_epi32(p, y_and_xsgn_x);
    return p;
#endif
}

inline
__m128i cftal::x86::vpmullq::v(__m128i a, __m128i b)
{
    // a= ah *2^32 + al
    // b= bh *2^32 + bl
    // a*b = ah*bh*2^64 + ah* bl * 2^32 + al * bh*2^32 + al *bl
    // a*b mod 2^64= ah* bl * 2^32 + al * bh*2^32 + al *bl
#if defined (__SSE4_1__)
    // swap lo and hi uint32_t parts of the 2 uint64_t in bs
    __m128i bs = vpshufd<1, 0, 3, 2>::v(b);
    __m128i al_bl = _mm_mul_epu32(a, b);
    // mixed: (bh*al, ah*bl)_0, (bh*al, ah* bl)_1
    __m128i mixed = _mm_mullo_epi32(a, bs);
    // ah_bl: (ah*bl, ah*bl)_0, (ah*bl, ah* bl)_1
    __m128i ah_bl = vpshufd<1, 1, 3, 3>::v(mixed);
    // mixed: (bh*al + ah*bl, 2*ah*bl)_0, (bh*al + ah*bl, 2*ah*bl)_1
    mixed = _mm_add_epi32(mixed, ah_bl);
    // mixed: (0, bh*al + ah*bl)_0, (0, bh*al + ah*bl)_1
    mixed = vpsllq_const<32>::v(mixed);
    __m128i p= _mm_add_epi64(al_bl, mixed);
    return p;
#else
    __m128i ah = vpshufd<1, 0, 3, 2>::v(a);
    __m128i bh = vpshufd<1, 0, 3, 2>::v(b);
    // mul(al * bl)
    __m128i al_bl = _mm_mul_epu32(a, b);
    // mul(ah * bl)
    __m128i ah_bl = _mm_mul_epu32(ah, b);
    // mul(al * bh)
    __m128i al_bh = _mm_mul_epu32(a, bh);
    // add the products with the same power of 2
    __m128i mixed = _mm_add_epi32(ah_bl, al_bh);
    // shift left
    mixed = vpsllq_const<32>::v(mixed);
    __m128i p = _mm_add_epi64(al_bl, mixed);
    return p;
#endif
}

#if defined (__AVX2__)
inline
__m256i cftal::x86::vpmullq::v(__m256i a, __m256i b)
{
    // a= ah *2^32 + al
    // b= bh *2^32 + bl
    // a*b = ah*bh*2^64 + ah* bl * 2^32 + al * bh*2^32 + al *bl
    // a*b mod 2^64= ah* bl * 2^32 + al * bh*2^32 + al *bl
    // fortunately we have not to cross any lanes:
    // swap lo and hi uint32_t parts of the 2 uint64_t in bs
    __m256i bs = vpshufd<1, 0, 3, 2>::v(b);
    __m256i al_bl = _mm256_mul_epu32(a, b);
    // mixed: (bh*al, ah*bl)_0, (bh*al, ah* bl)_1
    __m256i mixed = _mm256_mullo_epi32(a, bs);
    // ah_bl: (ah*bl, ah*bl)_0, (ah*bl, ah* bl)_1
    __m256i ah_bl = vpshufd<1, 1, 3, 3>::v(mixed);
    // mixed: (bh*al + ah*bl, 2*ah*bl)_0, (bh*al + ah*bl, 2*ah*bl)_1
    mixed = _mm256_add_epi32(mixed, ah_bl);
    // mixed: (0, bh*al + ah*bl)_0, (0, bh*al + ah*bl)_1
    mixed = vpsllq_const<32>::v(mixed);
    __m256i p= _mm256_add_epi64(al_bl, mixed);
    return p;
}
#endif

template <std::size_t _SCALE, typename _T>
inline
const _T*
cftal::x86::vsib_addr(const _T* p, int32_t idx)
{
    const char* pc=reinterpret_cast<const char*>(p);
    const char* pi=pc + int64_t(idx)*_SCALE;
    return reinterpret_cast<const _T*>(pi);
}

inline
void
cftal::x86::
extract(int32_t& i0, int32_t& i1,
        __m128i idx)
{
#if defined (__i386__)
    i0 = extract_u32<0>(idx);
    i1 = extract_u32<1>(idx);
#else
    uint64_t u0=extract_u64<0>(idx);
    i0 = u0;
    i1 = int32_t(u0>>32);
#endif
}

inline
void
cftal::x86::
extract(int32_t& i0, int32_t& i1, int32_t& i2, int32_t& i3,
        __m128i idx)
{
#if defined (__i386__)
    i0 = extract_u32<0>(idx);
    i1 = extract_u32<1>(idx);
    i2 = extract_u32<2>(idx);
    i3 = extract_u32<3>(idx);
#else
    uint64_t u0=extract_u64<0>(idx);
    uint64_t u1=extract_u64<1>(idx);
    i0 = u0;
    i1 = int32_t(u0>>32);
    i2 = u1;
    i3 = int32_t(u1>>32);
#endif
}

template <std::size_t _SCALE>
inline
__m128d
cftal::x86::vgatherdpd<__m128d, __m128i>::
v(const double* base, __m128i idx)
{
#if defined (__AVX2__)
    return _mm_i32gather_pd(base, idx, _SCALE);
#else
    int32_t i0, i1;
    extract(i0, i1, idx);
    const double* p0=vsib_addr<_SCALE>(base, i0);
    const double* p1=vsib_addr<_SCALE>(base, i1);
    return _mm_setr_pd(*p0, *p1);
#endif
}

template <std::size_t _SCALE>
inline
__m128d
cftal::x86::vgatherdpd<__m128d, __m128i>::
v(__m128d src, const double* base, __m128i idx, __m128d msk)
{
#if defined (__AVX2__)
    return _mm_mask_i32gather_pd(src, base, idx, msk, _SCALE);
#else
    __m128d l=v<_SCALE>(base, idx);
    __m128d r=select_f64(msk, l, src);
    return r;
#endif
}

template <std::size_t _SCALE>
inline
__m128
cftal::x86::
vgatherdps<__m128, __m128i>::
v(const float* base, __m128i idx)
{
#if defined (__AVX2__)
    return _mm_i32gather_ps(base, idx, _SCALE);
#else
    int32_t i0, i1, i2, i3;
    extract(i0, i1, i2, i3, idx);
    const float* p0=vsib_addr<_SCALE>(base, i0);
    const float* p1=vsib_addr<_SCALE>(base, i1);
    const float* p2=vsib_addr<_SCALE>(base, i2);
    const float* p3=vsib_addr<_SCALE>(base, i3);
    return _mm_setr_ps(*p0, *p1, *p2, *p3);
#endif
}

template <std::size_t _SCALE>
inline
__m128
cftal::x86::
vgatherdps<__m128, __m128i>::
v(__m128 src, const float* base, __m128i idx, __m128 msk)
{
#if defined (__AVX2__)
    return _mm_mask_i32gather_ps(src, base, idx, msk, _SCALE);
#else
    __m128 l=v<_SCALE>(base, idx);
    __m128 r=select_f32(msk, l, src);
    return r;
#endif
}

#if defined (__AVX__)

template <std::size_t _SCALE>
inline
__m256d
cftal::x86::
vgatherdpd<__m256d, __m128i>::v(const double* base, __m128i idx)
{
#if defined (__AVX2__)
    return _mm256_i32gather_pd(base, idx, _SCALE);
#else
    int32_t i0, i1, i2, i3;
    extract(i0, i1, i2, i3, idx);
    const double* p0=vsib_addr<_SCALE>(base, i0);
    const double* p1=vsib_addr<_SCALE>(base, i1);
    const double* p2=vsib_addr<_SCALE>(base, i2);
    const double* p3=vsib_addr<_SCALE>(base, i3);
    return _mm256_setr_pd(*p0, *p1, *p2, *p3);
#endif
}

template <std::size_t _SCALE>
inline
__m256d
cftal::x86::
vgatherdpd<__m256d, __m128i>::
v(__m256d src, const double* base, __m128i idx, __m256d msk)
{
#if defined (__AVX2__)
    return _mm256_mask_i32gather_pd(src, base, idx, msk, _SCALE);
#else
    __m256d l=v<_SCALE>(base, idx);
    __m256d r=select_f64(msk, l, src);
    return r;
#endif
}

template <std::size_t _SCALE>
inline
__m256
cftal::x86::
vgatherdps<__m256, __m256i>::
v(const float* base, __m256i idx)
{
#if defined (__AVX2__)
    return _mm256_i32gather_ps(base, idx, _SCALE);
#else
    __m128i idxh=_mm256_extracti128_si256(idx, 1);
    __m128i idxl=_mm256_castsi256_si128(idx);
    __m128 rh=v<_SCALE>(base, idxl);
    __m128 rl=v<_SCALE>(base, idxh);
    __m256 r=_mm256_castps128_ps256(rl);
    r = _mm256_insertf128_ps(r, rh, 1);
    return r;
#endif
}

template <std::size_t _SCALE>
inline
__m256
cftal::x86::
vgatherdps<__m256, __m256i>::
v(__m256 src, const float* base, __m256i idx, __m256 msk)
{
#if defined (__AVX2__)
    return _mm256_mask_i32gather_ps(src, base, idx, msk, _SCALE);
#else
    __m256 l=v<_SCALE>(base, idx);
    __m256 r=select_f32(msk, l, src);
    return r;
#endif
}

#endif


// Local variables:
// mode: c++
// end:
#endif
