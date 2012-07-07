#if !defined (__X86VEC_OPS_0_H__)
#define __X86VEC_OPS_0_H__ 1

#include <x86vec_intrin.h>
#include <x86vec_const.h>
#include <x86vec_select.h>

namespace x86vec {

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
			// float: cvt to int, exec, cvt back
			static __m128 v(__m128 a) {
				return _mm_castsi128_ps(
					_INT_OP::v(_mm_castps_si128(a)));
			}
			static __m128 v(__m128 a, __m128 b) {
				return _mm_castsi128_ps(
					_INT_OP::v(_mm_castps_si128(a),
						   _mm_castps_si128(b)));
			}
			// double: cvt to int, exec, cvt back
			static __m128d v(__m128d a) {
				return _mm_castsi128_pd(
					_INT_OP::v(_mm_castpd_si128(a)));
			}
			static __m128d v(__m128d a, __m128d b) {
				return _mm_castsi128_pd(
					_INT_OP::v(_mm_castpd_si128(a),
						   _mm_castpd_si128(b)));
			}
		};

		template <class _F32_OP>
		struct exec_f32 {
			// int: cvt to float, exec, cvt back
			static __m128i v(__m128i a) {
				return _mm_castps_si128(
					_F32_OP::v(_mm_castsi128_ps(a)));
			}
			static __m128i v(__m128i a, __m128i b) {
				return _mm_castps_si128(
					_F32_OP::v(_mm_castsi128_ps(a),
						   _mm_castsi128_ps(b)));
			}
			// double: cvt to float, exec, cvt back
			static __m128d v(__m128d a) {
				return _mm_castps_pd(
					_F32_OP::v(_mm_castpd_ps(a)));
			}
			static __m128d v(__m128d a, __m128d b) {
				return _mm_castps_pd(
					_F32_OP::v(_mm_castpd_ps(a),
						   _mm_castpd_ps(b)));
			}
		};

		template <class _F64_OP>
		struct exec_f64 {
			// int: cvt to double, exec, cvt back
			static __m128i v(__m128i a) {
				return _mm_castpd_si128(
					_F64_OP::v(_mm_castsi128_pd(a)));
			}
			static __m128i v(__m128i a, __m128i b) {
				return _mm_castpd_si128(
					_F64_OP::v(_mm_castsi128_pd(a),
						   _mm_castsi128_pd(b)));
			}
			// float: cvt to double, exec, cvt back
			static __m128 v(__m128 a) {
				return _mm_castpd_ps(
					_F64_OP::v(_mm_castps_pd(a)));
			}
			static __m128 v(__m128 a, __m128 b) {
				return _mm_castpd_ps(
					_F64_OP::v(_mm_castps_pd(a),
						   _mm_castps_pd(b)));
			}
		};


                struct make_zero_f64 {
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

                struct make_zero_f32 {
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

		template <unsigned _P0, unsigned _P1>
		struct vshufpd {
			static __m128d v(__m128d a, __m128d b) {
				const int m=shuffle2<_P0, _P1>::val;
				return _mm_shuffle_pd(a, b, m);
			}
			static __m128d v(__m128d a) {
				return v(a, a);
			}
		};


		template <unsigned _P0, unsigned _P1,
			  unsigned _P2, unsigned _P3>
		struct vshufps {
			static __m128 v(__m128 a, __m128 b) {
				const int m=shuffle4<_P0, _P1, _P2, _P3>::val;
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
				const int m=shuffle4<_P0, _P1, _P2, _P3>::val;
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
				const int m=shuffle4<_P0, _P1, _P2, _P3>::val;
				return _mm_shufflehi_epi16(a, m);
			}
		};

		template <>
		struct vpshufhw<0, 1, 2, 3>
			: public select_arg_1<__m128i> {};

		template <unsigned _P0, unsigned _P1,
			  unsigned _P2, unsigned _P3>
		struct vpshufd {
			static __m128i v(__m128i a) {
				const int m=shuffle4<_P0, _P1, _P2, _P3>::val;
				return _mm_shuffle_epi32(a, m);
			}
		};

		template <>
		struct vpshufd<0, 1, 2, 3>
			: public select_arg_1<__m128i> {};

		template <unsigned _P>
		struct splat_f64 : public vshufpd<_P, _P> {};

		template <unsigned _P>
		struct splat_f32 : public vshufps<_P, _P, _P, _P> {};

		template <unsigned _P>
		struct splat_u64
			: public vpshufd<2*_P,2*_P+1, 2*_P,2*_P+1> {};

		template <unsigned _P>
		struct splat_u32 : public vpshufd<_P, _P, _P, _P> {};

		template <unsigned _P>
		struct splat_u16 {
			static __m128i v(__m128i a) {
#if defined (__SSSE3__)
				const __m128i msk=const16_u8<
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
                };

                struct vunpcklpd {
                        static __m128d v(__m128d a, __m128d b) {
                                return _mm_unpacklo_pd(a, b);
                        }
                        static __m128d v(__m128d a) {
                                return v(a, a);
                        }
                };

                struct vunpcklps {
                        static __m128 v(__m128 a, __m128 b) {
                                return _mm_unpacklo_ps(a, b);
                        }
                        static __m128 v(__m128 a) {
                                return v(a, a);
                        }
                };

                struct vunpckhps {
                        static __m128 v(__m128 a, __m128 b) {
                                return _mm_unpackhi_ps(a, b);
                        }
                        static __m128 v(__m128 a) {
                                return v(a, a);
                        }
                };

                struct vpunpcklqdq {
                        static __m128i v(__m128i a, __m128i b) {
                                return _mm_unpacklo_epi64(a, b);
                        }
                        static __m128i v(__m128i a) {
                                return v(a, a);
                        }
                };

                struct vpunpckhqdq {
                        static __m128i v(__m128i a, __m128i b) {
                                return _mm_unpackhi_epi64(a, b);
                        }
                        static __m128i v(__m128i a) {
                                return v(a, a);
                        }
                };

                struct vpunpckldq {
                        static __m128i v(__m128i a, __m128i b) {
                                return _mm_unpacklo_epi32(a, b);
                        }
                        static __m128i v(__m128i a) {
                                return v(a, a);
                        }
                };

                struct vpunpckhdq {
                        static __m128i v(__m128i a, __m128i b) {
                                return _mm_unpackhi_epi32(a, b);
                        }
                        static __m128i v(__m128i a) {
                                return v(a, a);
                        }
                };

                struct vpunpcklwd {
                        static __m128i v(__m128i a, __m128i b) {
                                return _mm_unpacklo_epi16(a, b);
                        }
                        static __m128i v(__m128i a) {
                                return v(a, a);
                        }
                };

                struct vpunpckhwd {
                        static __m128i v(__m128i a, __m128i b) {
                                return _mm_unpackhi_epi16(a, b);
                        }
                        static __m128i v(__m128i a) {
                                return v(a, a);
                        }
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

		struct vpslld {
			static __m128i v(__m128i a, __m128i shift) {
				return _mm_sll_epi32(a, shift);
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

		struct vpsllq {
			static __m128i v(__m128i a, __m128i shift) {
				return _mm_sll_epi64(a, shift);
			}
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

		struct vpsrlw {
			static __m128i v(__m128i a, __m128i shift) {
				return _mm_srl_epi16(a, shift);
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
		};

		template <unsigned _P>
		struct vpsrad_const : public vpsrad {
			static __m128i v(__m128i a) {
				return _mm_srai_epi32(a, _P);
			}
		};

		template <>
		struct vpsrad_const<0> : public select_arg_1<__m128i> {};


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

		struct vpmulld {
			static __m128i v(__m128i a, __m128i b);
		};

	}
}

inline
__m128i x86vec::impl::vpmulld::v(__m128i a, __m128i b)
{
#if defined (__SSE4_1__)
		return _mm_mullo_epi32(a, b);
#else
		__m128i e= _mm_mul_epu32(a, b);
		__m128i o= _mm_mul_epu32(_mm_srli_epi64(a, 32),
					 _mm_srli_epi64(b, 32));
		const __m128i msk = const4_u32<-1, 0, -1, 0>::iv();
		e = _mm_and_si128(e, msk);
		o = _mm_slli_epi64(o, 32);
		e = _mm_or_si128(e, o);
		return e;
#endif
}


// Local variables:
// mode: c++
// end:
#endif
