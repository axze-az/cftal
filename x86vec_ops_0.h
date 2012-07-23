#if !defined (__X86VEC_OPS_0_H__)
#define __X86VEC_OPS_0_H__ 1

#include <cftal/x86vec_intrin.h>
#include <cftal/x86vec_const.h>
#include <cftal/x86vec_select.h>

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
				__m128i sh= _mm_cvtsi32_si128(shift);
				return v(a, sh);
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

		struct vpsraq {
			static __m128i v(__m128i a, unsigned shift);

			static __m128i v(__m128i a, __m128i shift) {
				unsigned sh= _mm_cvtsi128_si32(shift);
				return v(a, sh);
			}
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
		};
		
		struct vpmulhud {
			static __m128i v(__m128i a, __m128i b);
		};
		
		struct vpmulhd {
			static __m128i v(__m128i a, __m128i b);
		};

		struct vpmullq {
			static __m128i v(__m128i a, __m128i b);
		};
	}
}

inline
__m128i x86vec::impl::vpsraq::v(__m128i a, unsigned shift)
{
	__m128i r;
	if (shift <= 32) {
		// high parts of result.
		__m128i sh = _mm_cvtsi32_si128(shift);
		__m128i sgnbits= vpsrad::v(a, sh);
		// low parts of result.
		__m128i allbits= vpsrlq::v(a, sh);
#if defined (__SSE4_1__)
		r = select_u32<0, 1, 0, 1>::v(sgnbits, allbits);
#else
		// clear the low uint32_t of sgnbits
		__m128i msk= const4_u32<0, -1, 0, -1>::iv();
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
		__m128i msk= const4_u32<0, -1, 0, -1>::iv();
		sgnbits = _mm_and_si128(sgnbits, msk);
		// works because high uint32_t of sgnbits contains
		// either the same pattern as allbits or ones 
		r= _mm_or_si128(allbits, sgnbits);
#endif
	}
	return r;
}

template <unsigned _S>
inline
__m128i x86vec::impl::vpsraq_const<_S>::v(__m128i a)
{
	__m128i r;
	if (_S <= 32) {
		// high parts of result.
		__m128i sgnbits= vpsrad_const<_S>::v(a);
		// low parts of result.
		__m128i allbits= vpsrlq_const<_S>::v(a);
#if defined (__SSE4_1__)
		r = select_u32<0, 1, 0, 1>::v(sgnbits, allbits);
#else
		// clear the low uint32_t of sgnbits
		__m128i msk= const4_u32<0, -1, 0, -1>::iv();
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
		__m128i msk= const4_u32<0, -1, 0, -1>::iv();
		sgnbits = _mm_and_si128(sgnbits, msk);
		// works because high uint32_t of sgnbits contains
		// either the same pattern as allbits or ones 
		r= _mm_or_si128(allbits, sgnbits);
#endif
	}
	return r;
}

inline
__m128i x86vec::impl::vpmulld::v(__m128i a, __m128i b)
{
#if defined (__SSE4_1__)
	return _mm_mullo_epi32(a, b);
#else
	// 0, 2 at positions 0 2
	__m128i e= _mm_mul_epu32(a, b);
	// 1, 3 at positions 0 2
	__m128i o= _mm_mul_epu32(vpsrlq_const<32>::v(a),
				 vpsrlq_const<32>::v(b));
	const __m128i msk = const4_u32<-1, 0, -1, 0>::iv();
	e = _mm_and_si128(e, msk);
	o = _mm_slli_epi64(o, 32);
	e = _mm_or_si128(e, o);
	return e;
#endif
}

inline
__m128i x86vec::impl::vpmulhud::v(__m128i a, __m128i b)
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
	return select_u32<1, 0, 1, 0>::v(e, o);
#else
	const __m128i msk = const4_u32<0, -1, 0, -1>::iv();
	o = _mm_and_si128(o, msk);
	return _mm_or_si128(e, o);
#endif
}

inline
__m128i x86vec::impl::vpmulhd::v(__m128i x, __m128i y)
{
#if defined(__SSE4_1__)
	// 0, 2 at positions 1 3
	__m128i e= _mm_mul_epi32(x, y);
	// 1, 3 at positions 1 3
	__m128i o= _mm_mul_epi32(vpshufd<1, 0, 3, 2>::v(x),
				 vpshufd<1, 0, 3, 2>::v(y));
	// 0, 2 at positions 0 2
	e = _mm_srli_epi64(e, 32);
	return select_u32<1, 0, 1, 0>::v(e, o);
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
__m128i x86vec::impl::vpmullq::v(__m128i a, __m128i b)
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
	// mul(al * bl)
	__m128i al_bh = _mm_mul_epu32(b, bh);
	// add the products with the same power of 2
	__m128i mixed = _mm_add_epi32(ah_bl, al_bh);
	// shift left
	mixed = vpsllq_const<32>::v(mixed);
	__m128i p = _mm_add_epi64(al_bl, mixed);
	return p;
#endif
}


// Local variables:
// mode: c++
// end:
#endif
