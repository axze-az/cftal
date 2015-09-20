#if !defined (__CFTAL_X86_OPS_0_H__)
#define __CFTAL_X86_OPS_0_H__ 1

#include <cftal/x86_intrin.h>
#include <cftal/x86_const.h>
#include <cftal/x86_select.h>
#include <cftal/x86_cast.h>
#include <cftal/x86_ins_ext.h>

namespace cftal {
    namespace x86 {

        namespace impl {

            template <int _P0, int _P1, int _MSK>
            struct pos_msk_2 {
                enum {
                    m =
                    (((_P0 & _MSK)<<0) |
                     ((_P1 & _MSK)<<4))
                };
            };

            template <int _P0, int _P1>
            struct zero_msk_2 {
                enum {
                    m =
                    (((_P0 <0 ? 0 : 0xF) << 0)|
                     ((_P1 <0 ? 0 : 0xF) << 4))
                };
            };

            template <int _P0, int _P1, int _P2, int _P3, int _MSK>
            struct pos_msk_4 {
                enum {
                    m=
                    (((_P0 & _MSK)<< 0) |
                     ((_P1 & _MSK)<< 4) |
                     ((_P2 & _MSK)<< 8) |
                     ((_P3 & _MSK)<<12))
                };
            };

            template <int _P0, int _P1, int _P2, int _P3>
            struct zero_msk_4 {
                enum {
                    m =
                    (((_P0 <0 ? 0 : 0xF) << 0) |
                     ((_P1 <0 ? 0 : 0xF) << 4) |
                     ((_P2 <0 ? 0 : 0xF) << 8) |
                     ((_P3 <0 ? 0 : 0xF) <<12))
                };
            };

            template <int _P0, int _P1, int _P2, int _P3,
                      int _P4, int _P5, int _P6, int _P7,
                      int _MSK>
            struct pos_msk_8 {
                enum {
                    m =
                    (((_P0 & _MSK)<< 0) |
                     ((_P1 & _MSK)<< 4) |
                     ((_P2 & _MSK)<< 8) |
                     ((_P3 & _MSK)<<12) |
                     ((_P4 & _MSK)<<16) |
                     ((_P5 & _MSK)<<20) |
                     ((_P6 & _MSK)<<24) |
                     ((_P7 & _MSK)<<28))
                };
            };

            template <int _P0, int _P1, int _P2, int _P3,
                      int _P4, int _P5, int _P6, int _P7>
            struct zero_msk_8 {
                enum {
                    m =
                    (((_P0 <0 ? 0 : 0xF) << 0) |
                     ((_P1 <0 ? 0 : 0xF) << 4) |
                     ((_P2 <0 ? 0 : 0xF) << 8) |
                     ((_P3 <0 ? 0 : 0xF) <<12) |
                     ((_P4 <0 ? 0 : 0xF) <<16) |
                     ((_P5 <0 ? 0 : 0xF) <<20) |
                     ((_P6 <0 ? 0 : 0xF) <<24) |
                     ((_P7 <0 ? 0 : 0xF) <<28))
                };
            };

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
                    return _mm_shuffle_pd(a, b, m);
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
                    return _mm_shufflelo_epi16(a, m);
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
                    m= shuffle4<int(_p0), int(_p1), int(_p2), int(_p3)>::val & 0xff
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
            struct splat_u64
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
            };

            template <>
            struct vpsllq_const<0> : public select_arg_1<__m128i> {};

            template <>
            struct vpsllq_const<1> : public vpsllq {
                static __m128i v(__m128i a) {
                    return _mm_add_epi64(a, a);
                }
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
            };
            template <>
            struct vpsrldq<0> : public select_arg_1<__m128i> {};

            struct vpmullw {
                static __m128i v(__m128i a, __m128i b) {
                    return _mm_mullo_epi16(a, b);
                }
            };

            struct vpmulhw {
                static __m128i v(__m128i a, __m128i b) {
                    return _mm_mulhi_epi16(a, b);
                }
            };

            struct vpmulhuw {
                static __m128i v(__m128i a, __m128i b) {
                    return _mm_mulhi_epu16(a, b);
                }
            };

            struct vpmulld {
                static __m128i v(__m128i a, __m128i b);
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


            template <class _T>
            struct vgatherdpd {
                static _T v(const double* base,
                            __m128i idx,
                            int scale);
                static _T v(const _T& src,
                            const double* base,
                            __m128i idx,
                            const _T& msk,
                            int scale);
            };

            template <>
            struct vgatherdpd<__m128d> {
                static __m128d v(const double* base,
                                 __m128i idx,
                                 int scale);
                static __m128d v(__m128d src,
                                 const double* base,
                                 __m128i idx,
                                 __m128d msk,
                                 int scale);
            };

            template <class _T, class _I>
            struct vgatherdps {
                static _T v(const float* base,
                            const _I& idx,
                            int scale);
                static _T v(const _T& src,
                            const float* base,
                            const _I& idx,
                            const _T& msk,
                            int scale);
            };

            template <>
            struct vgatherdps<__m128, __m128i> {
                static __m128 v(const float* base,
                                __m128i idx,
                                int scale);
                static __m128 v(__m128 src,
                                const float* base,
                                __m128i idx,
                                __m128 msk,
                                int scale);
            };


#if defined (__AVX__)
            template <>
            struct vgatherdpd<__m256d> {
                static __m256d v(const double* base,
                                 __m128i idx,
                                 int scale);
                static __m256d v(__m256d src,
                                 const double* base,
                                 __m128i idx,
                                 __m256d msk,
                                 int scale);
            };

            template <>
            struct vgatherdps<__m256, __m256i> {
                static __m256 v(const float* base,
                                __m256i idx,
                                int scale);
                static __m256 v(__m256 src,
                                const float* base,
                                __m256i idx,
                                __m256 msk,
                                int scale);
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

#endif
        }
    }
}

inline
__m128i cftal::x86::impl::vpsraq::v(__m128i a, unsigned shift)
{
    __m128i r;
    if (shift <= 32) {
        // high parts of result.
        __m128i sh = _mm_cvtsi32_si128(shift);
        __m128i sgnbits= vpsrad::v(a, sh);
        // low parts of result.
        __m128i allbits= vpsrlq::v(a, sh);
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
        r= vpsrad::v(r, shift-32);
        r= _mm_cvtepi32_epi64(r);
#else
        // future sign bits.
        __m128i sgnbits= vpsrad_const<31>::v(a);
        // result bits right shifted by shift - 32
        __m128i allbits= vpsrad::v(a, shift-32);
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

#if defined (__AVX2__)
inline
__m256i cftal::x86::impl::vpsraq::v(__m256i a, unsigned shift)
{
    __m256i r;
    if (shift <= 32) {
        // high parts of result.
        __m128i sh = _mm_cvtsi32_si128(shift);
        __m256i sgnbits= vpsrad::v(a, sh);
        // low parts of result.
        __m256i allbits= vpsrlq::v(a, sh);
        r = select_v8u32<0, 1, 0, 1, 0, 1, 0, 1>::v(sgnbits, allbits);
    } else {
        // r= vpshufd<1, 3, 1, 3>::v(a);
        const __m256i v= _mm256_setr_epi32(1, 3, 5, 7,
                                           1, 3, 5, 7);
        r= _mm256_permutevar8x32_epi32(a, v);
        r= vpsrad::v(r, shift-32);
        r= _mm256_cvtepi32_epi64(_mm256_castsi256_si128(r));
    }
    return r;
}
#endif


template <unsigned _S>
inline
__m128i cftal::x86::impl::vpsraq_const<_S>::v(__m128i a)
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
__m128i cftal::x86::impl::vpmulld::v(__m128i a, __m128i b)
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
__m128i cftal::x86::impl::vpmulhud::v(__m128i a, __m128i b)
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
__m128i cftal::x86::impl::vpmulhd::v(__m128i x, __m128i y)
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
__m128i cftal::x86::impl::vpmullq::v(__m128i a, __m128i b)
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

inline
__m128d
cftal::x86::impl::vgatherdpd<__m128d>::v(const double* base,
                                         __m128i idx,
                                         int scale)
{
#if defined (__AVX2__)
    return _mm_i32gather_pd(base, idx, scale);
#else
    const char* p= reinterpret_cast<const char*>(base);
    const char* p0= p + extract_u32<0>(idx) * scale;
    const char* p1= p + extract_u32<1>(idx) * scale;
    double d0= *reinterpret_cast<const double*>(p0);
    double d1= *reinterpret_cast<const double*>(p1);
    return _mm_set_pd(d1, d0);
#endif
}

inline
__m128
cftal::x86::impl::vgatherdps<__m128, __m128i>::v(const float* base,
                                                 __m128i idx,
                                                 int scale)
{
#if defined (__AVX2__)
    return _mm_i32gather_ps(base, idx, scale);
#else
    const char* p= reinterpret_cast<const char*>(base);
    const char* p0= p + extract_u32<0>(idx) * scale;
    const char* p1= p + extract_u32<1>(idx) * scale;
    const char* p2= p + extract_u32<2>(idx) * scale;
    const char* p3= p + extract_u32<3>(idx) * scale;
    float f0= *reinterpret_cast<const float*>(p0);
    float f1= *reinterpret_cast<const float*>(p1);
    float f2= *reinterpret_cast<const float*>(p2);
    float f3= *reinterpret_cast<const float*>(p3);
    return _mm_setr_ps(f0, f1, f2, f3);
#endif
}


#if defined (__AVX__)
inline
__m256d
cftal::x86::impl::vgatherdpd<__m256d>::v(const double* base,
                                         __m128i idx,
                                         int scale)
{
#if defined (__AVX2__)
    return _mm256_i32gather_pd(base, idx, scale);
#else
    const char* p= reinterpret_cast<const char*>(base);
    const char* p0= p + extract_u32<0>(idx) * scale;
    const char* p1= p + extract_u32<1>(idx) * scale;
    const char* p2= p + extract_u32<2>(idx) * scale;
    const char* p3= p + extract_u32<3>(idx) * scale;
    double d0= *reinterpret_cast<const double*>(p0);
    double d1= *reinterpret_cast<const double*>(p1);
    double d2= *reinterpret_cast<const double*>(p2);
    double d3= *reinterpret_cast<const double*>(p3);
    return _mm256_set_pd(d3, d2, d1, d0);
#endif
}
#endif

#if defined (__AVX2__)
inline
__m256
cftal::x86::impl::vgatherdps<__m256, __m256i>::v(const float* base,
                                                 __m256i idx,
                                                 int scale)
{
    return _mm256_i32gather_ps(base, idx, scale);
}

#endif


// Local variables:
// mode: c++
// end:
#endif
