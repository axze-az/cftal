#if !defined (__X86VEC_MATH_FUNC_H__)
#define __X86VEC_MATH_FUNC_H__ 1

#include <cftal/config.h>
#include <cftal/x86vec.h>
#include <cftal/math_func.h>

namespace cftal {

        template <>
        struct d_real_traits<x86vec::v2f64> : public has_fma<double> {
                constexpr d_real_traits<x86vec::v2f64>() = default;
                // result of a comparison operator
                typedef x86vec::v2f64 cmp_result_type;
                static bool any(const cmp_result_type& b) {
                        return !no_signs(b);
                }

                static x86vec::v2f64 sel(const cmp_result_type& s,
                                         const x86vec::v2f64& on_true,
                                         const x86vec::v2f64& on_false) {
                        return select(s, on_true, on_false);
                }

		static 
		void split(const x86vec::v2f64& a, 
			   x86vec::v2f64& h, 
			   x86vec::v2f64& l) {
			const x86vec::v2f64 msk= 
				x86vec::const_v4u32<0xf8000000U, 
						    0xffffffffU,
						    0xf8000000U, 
						    0xffffffffU>::dv();
			h = a & msk;
			l = a - h;
		}
        };

        template <>
        struct d_real_traits<x86vec::v4f32> : public has_fma<float> {
                constexpr d_real_traits<x86vec::v4f32>() = default;
                // result of a comparison operator
                typedef x86vec::v4f32 cmp_result_type;
                static bool any(const cmp_result_type& b) {
                        return !no_signs(b);
                }

                static x86vec::v4f32 sel(const cmp_result_type& s,
                                         const x86vec::v4f32& on_true,
                                         const x86vec::v4f32& on_false) {
                        return select(s, on_true, on_false);
                }

		static 
		void split(const x86vec::v4f32& a, 
			   x86vec::v4f32& h, 
			   x86vec::v4f32& l) {
			const x86vec::v4f32 msk= 
				x86vec::const_v4u32<0xfffff000U, 
						    0xfffff000U, 
						    0xfffff000U, 
						    0xfffff000U>::fv();
			h = a & msk;
			l = a - h;
		}
        };

        template <>
        struct d_real_traits<x86vec::v4f64> : public has_fma<double> {
                constexpr d_real_traits<x86vec::v4f64>() = default;
                // result of a comparison operator
                typedef x86vec::v4f64 cmp_result_type;
                static bool any(const cmp_result_type& b) {
                        return !no_signs(b);
                }

                static x86vec::v4f64 sel(const cmp_result_type& s,
                                         const x86vec::v4f64& on_true,
                                         const x86vec::v4f64& on_false) {
                        return select(s, on_true, on_false);
                }

		static 
		void split(const x86vec::v4f64& a, 
			   x86vec::v4f64& h, 
			   x86vec::v4f64& l) {
#if !defined (__AVX__)
			const x86vec::v2f64 msk_half= 
				x86vec::const_v4u32<0xf8000000U, 
						    0xffffffffU,
						    0xf8000000U, 
						    0xffffffffU>::dv();
			const x86vec::v4f64 msk(msk_half, msk_half);
#else
			const x86vec::v4f64 msk= 
				x86vec::const_v8u32<0xf8000000U, 
						    0xffffffffU,
						    0xf8000000U, 
						    0xffffffffU,
						    0xf8000000U, 
						    0xffffffffU,
						    0xf8000000U, 
						    0xffffffffU>::dv();
#endif
			h = a & msk;
			l = a - h;
		}
        };

#if defined (__AVX__)
        template <>
        struct d_real_traits<x86vec::v8f32> : public has_fma<float> {
                constexpr d_real_traits<x86vec::v8f32>() = default;
                // result of a comparison operator
                typedef x86vec::v8f32 cmp_result_type;
                static bool any(const cmp_result_type& b) {
                        return !no_signs(b);
                }

                static x86vec::v8f32 sel(const cmp_result_type& s,
                                         const x86vec::v8f32& on_true,
                                         const x86vec::v8f32& on_false) {
                        return select(s, on_true, on_false);
                }

		static 
		void split(const x86vec::v8f32& a, 
			   x86vec::v8f32& h, 
			   x86vec::v8f32& l) {
			const x86vec::v8f32 msk= 
				x86vec::const_v8u32<0xfffff000U, 
						    0xfffff000U, 
						    0xfffff000U, 
						    0xfffff000U,
						    0xfffff000U, 
						    0xfffff000U, 
						    0xfffff000U, 
						    0xfffff000U>::fv();
			h = a & msk;
			l = a - h;
		}
        };

#endif

	namespace math {

                template <>
                struct func_traits<x86vec::v2f64, x86vec::v4s32> : public 
		func_traits<typename x86vec::v2f64::element_type,
			    typename x86vec::v4s32::element_type> {
                        typedef x86vec::v2f64 vf_type;
                        typedef x86vec::v2f64 vmf_type;
                        typedef x86vec::v4s32 vi_type;
                        typedef x86vec::v4s32 vmi_type;

                        static
                        vmf_type vmi_to_vmf(const vmi_type& mi) {
                                x86vec::v4s32 xm= 
					x86vec::permute<0, 0, 1, 1>(mi);
                                return x86vec::as<x86vec::v2f64>(xm);
                        }
                        static
                        vmi_type vmf_to_vmi(const vmf_type& mf) {
                                x86vec::v4s32 xm= x86vec::as<x86vec::v4s32>(mf);
                                xm = x86vec::permute<1, 3, 0, 2>(xm);
                                return xm;
                        }
                        static
                        vi_type sel(const vmi_type& msk,
                                    const vi_type& t, const vi_type& f) {
                                return select(msk, t, f);
                        }
                        static
                        vf_type sel(const vmf_type& msk,
                                    const vf_type& t, const vf_type& f) {
                                return select(msk, t, f);
                        }
			static
			vf_type gather(const double* p, const vi_type& idx,
				       int sc) {
				return x86vec::gather<vf_type>(p, idx, sc);
			}
                        static
                        vf_type insert_exp(const vi_type& e) {
				vi_type ep(x86vec::permute<0, 0, 1, 1>(e));
                                x86vec::v2u64 m= x86vec::as<x86vec::v2u64>(ep);
                                m <<= x86vec::const_shift::_52;
                                return x86vec::as<x86vec::v2f64>(m);
                        }
                        static
                        vi_type extract_exp(const vf_type& d) {
                                x86vec::v4s32 e= x86vec::as<x86vec::v4s32>(d);
                                e >>= x86vec::const_shift::_20;
                                e = x86vec::permute<1, 3, 0, 0>(e);
                                e &= x86vec::v4s32(0x7ff, 0x7ff, 0, 0);
                                return e;
                        }
			
			static
			vi_type extract_high_word(const vf_type& d) {
				x86vec::v4s32 w=x86vec::as<x86vec::v4s32>(d);
				w= x86vec::permute<1, 3, 1, 3>(w);
				return w;
				
			}

			static
			vi_type extract_low_word(const vf_type& d) {
				x86vec::v4s32 w=x86vec::as<x86vec::v4s32>(d);
				w= x86vec::permute<0, 2, 0, 2>(w);
				return w;
			}

			static 
			vf_type combine_words(const vi_type& l,
					      const vi_type& h) {
				x86vec::v4s32 c=
					x86vec::permute<0, 4, 1, 5>(l, h);
				x86vec::v2f64 r=x86vec::as<vf_type>(c);
				return r;
			}
			
                        static
                        vf_type cvt_i_to_f(const vi_type& i) {
                                return x86vec::cvt_lo<x86vec::v2f64>(i);
                        }

                        static
                        vi_type cvt_f_to_i(const vf_type& f) {
                                return x86vec::cvt_lo<x86vec::v4s32>(f);
                        }
                        // including rounding towards zero
                        static
                        vi_type cvt_rz_f_to_i(const vf_type& f) {
                                return x86vec::cvt_rz_lo<x86vec::v4s32>(f);
                        }
                };


                template <>
                struct func_traits<x86vec::v4f32, x86vec::v4s32> : public 
		func_traits<typename x86vec::v4f32::element_type,
			    typename x86vec::v4s32::element_type> {
                        typedef x86vec::v4f32 vf_type;
                        typedef x86vec::v4f32 vmf_type;
                        typedef x86vec::v4s32 vi_type;
                        typedef x86vec::v4s32 vmi_type;
			typedef d_real<vf_type> dvf_type;

			typedef x86vec::v2f64 vhpf_type;
			typedef func_traits<vhpf_type, x86vec::v4s32> 
			hpf_traits;
			static
			constexpr std::size_t vhpf_per_vf() {
				return 2;
			}
			
			static 
			void vf_to_vhpf(const vf_type& x, vhpf_type* r) {
				using namespace x86vec;
				using x86vec::impl::cvt;
				r[0] = cvt<v2f64, v4f32>::l(x);
				r[1] = cvt<v2f64, v4f32>::h(x);
			}

			static
			void vhpf_to_dvf(const vhpf_type* hpf, dvf_type& res) {
				using namespace x86vec;
				using x86vec::impl::cvt;
				vf_type lo(cvt<v4f32, v2f64>::l(hpf[0]));
				vhpf_type rest(hpf[0] - cvt<v2f64, v4f32>::l(lo));
				vf_type lo_lo(cvt<v4f32, v2f64>::l(rest));
					
				vf_type hi(cvt<v4f32, v2f64>::l(hpf[1]));
				rest = hpf[1] - cvt<v2f64, v4f32>::l(hi);
				
				vf_type hi_lo(cvt<v4f32, v2f64>::l(rest));

				vf_type msv(permute<0, 1, 4, 5>(lo, hi));
				vf_type lsv(permute<0, 1, 4, 5>(lo_lo, hi_lo));
				res = dvf_type(msv, lsv);
			}


                        static
                        vmf_type vmi_to_vmf(const vmi_type& mi) {
                                return x86vec::as<x86vec::v4f32>(mi);
                        }
                        static
                        vmi_type vmf_to_vmi(const vmf_type& mf) {
                                return x86vec::as<x86vec::v4s32>(mf);
                        }
                        static
                        vi_type sel(const vmi_type& msk,
                                    const vi_type& t, const vi_type& f) {
                                return select(msk, t, f);
                        }
                        static
                        vf_type sel(const vmf_type& msk,
                                    const vf_type& t, const vf_type& f) {
                                return select(msk, t, f);
                        }
			static
			vf_type gather(const float* p, const vi_type& idx,
				       int sc) {
				return x86vec::gather<vf_type>(p, idx, sc);
			}
                        static
                        vf_type insert_exp(const vi_type& e) {
				vi_type ep(e << x86vec::const_shift::_23);
                                return x86vec::as<x86vec::v4f32>(ep);
                        }
                        static
                        vi_type extract_exp(const vf_type& d) {
                                x86vec::v4s32 e= x86vec::as<x86vec::v4s32>(d);
                                e >>= x86vec::const_shift::_23;
                                e &= x86vec::v4s32(0xff, 0xff, 0xff, 0xff);
                                return e;
                        }
                        static
                        vf_type cvt_i_to_f(const vi_type& i) {
                                return x86vec::cvt<x86vec::v4f32>(i);
                        }

                        static
                        vi_type cvt_f_to_i(const vf_type& f) {
                                return x86vec::cvt<x86vec::v4s32>(f);
                        }
                        // including rounding towards zero
                        static
                        vi_type cvt_rz_f_to_i(const vf_type& f) {
                                return x86vec::cvt_rz<x86vec::v4s32>(f);
                        }

			static 
			vi_type as_int(const vf_type& f) {
				return x86vec::as<x86vec::v4s32>(f);
			}

			static 
			vf_type as_float(const vi_type& i) {
				return x86vec::as<x86vec::v4f32>(i);
			}
                };

                template <>
                struct func_traits<x86vec::v4f64, x86vec::v4s32> : public 
		func_traits<typename x86vec::v4f64::element_type,
			    typename x86vec::v4s32::element_type> {
                        typedef x86vec::v4f64 vf_type;
                        typedef x86vec::v4f64 vmf_type;
                        typedef x86vec::v4s32 vi_type;
                        typedef x86vec::v4s32 vmi_type;

                        static
                        vmf_type vmi_to_vmf(const vmi_type& mi) {
				// TODO AVX2 code
                                x86vec::v4s32 xml=x86vec::permute<0, 0, 1, 1>(mi);
				x86vec::v4s32 xmh=x86vec::permute<2, 2, 3, 3>(mi);
				x86vec::v2f64 dml=x86vec::as<x86vec::v2f64>(xml);
				x86vec::v2f64 dmh=x86vec::as<x86vec::v2f64>(xmh);
				x86vec::v4f64 r(dml, dmh);
				return r;
                        }
                        static
                        vmi_type vmf_to_vmi(const vmf_type& mf) {
				// TODO AVX2 code
				x86vec::v2f64 mfl=low_half(mf);
				x86vec::v2f64 mfh=high_half(mf);
                                x86vec::v4s32 xml=x86vec::as<x86vec::v4s32>(mfl);
                                x86vec::v4s32 xmh=x86vec::as<x86vec::v4s32>(mfh);
				x86vec::v4s32 xm =x86vec::permute<0, 2, 4, 6>(xml, xmh);
                                return xm;
                        }
                        static
                        vi_type sel(const vmi_type& msk,
                                    const vi_type& t, const vi_type& f) {
                                return select(msk, t, f);
                        }
                        static
                        vf_type sel(const vmf_type& msk,
                                    const vf_type& t, const vf_type& f) {
                                return select(msk, t, f);
                        }
			static
			vf_type gather(const double* p, const vi_type& idx,
				       int sc) {
				return x86vec::gather<vf_type>(p, idx, sc);
			}
                        static
                        vf_type insert_exp(const vi_type& e) {
				// TODO AVX2 code
				// 52 - 32
				vi_type ep(e << x86vec::const_shift::_20);
				vi_type hep(x86vec::permute<2, 2, 3, 3>(ep));
				vi_type lep(x86vec::permute<0, 0, 1, 1>(ep));
				x86vec::v2f64 fh(x86vec::as<x86vec::v2f64>(hep));
				x86vec::v2f64 lh(x86vec::as<x86vec::v2f64>(lep));
#if !defined (__AVX__)
				lh &= x86vec::v_exp_v2f64_msk::dv();
				fh &= x86vec::v_exp_v2f64_msk::dv();
				vf_type r(lh, fh);
#else
				vf_type r(lh, fh);
				r &= x86vec::v_exp_v4f64_msk::dv();
#endif
				return r;
                        }
			
                        static
                        vi_type extract_exp(const vf_type& d) {
				// TODO AVX2 code
#if !defined (__AVX__)
				vf_type m(low_half(d) & x86vec::v_exp_v2f64_msk::dv(),
					  high_half(d) & x86vec::v_exp_v2f64_msk::dv());
#else
				vf_type m(d & x86vec::v_exp_v4f64_msk::dv());
#endif
				x86vec::v2f64 fh(high_half(d));
				x86vec::v2f64 fl(low_half(d));
				x86vec::v4s32 hi(x86vec::as<x86vec::v4s32>(fh));
				x86vec::v4s32 li(x86vec::as<x86vec::v4s32>(fl));
				x86vec::v4s32 r(x86vec::permute<1, 3, 5, 7>(li, hi));
				r >>= x86vec::const_shift::_20;
				return r;
                        }
			static
			vi_type extract_high_word(const vf_type& d) {
				x86vec::v2f64 l= low_half(d);
				x86vec::v2f64 h= high_half(d);
				x86vec::v4s32 il=x86vec::as<x86vec::v4s32>(l);
				x86vec::v4s32 ih=x86vec::as<x86vec::v4s32>(h);
				x86vec::v4s32 w=x86vec::permute<1, 3, 5, 7>(il, ih);
				return w;
			}

			static
			vi_type extract_low_word(const vf_type& d) {
				x86vec::v2f64 l= low_half(d);
				x86vec::v2f64 h= high_half(d);
				x86vec::v4s32 il=x86vec::as<x86vec::v4s32>(l);
				x86vec::v4s32 ih=x86vec::as<x86vec::v4s32>(h);
				x86vec::v4s32 w=x86vec::permute<0, 2, 4, 6>(il, ih);
				return w;
			}

			static 
			vf_type combine_words(const vi_type& l,
					      const vi_type& h) {
				x86vec::v4s32 il=x86vec::permute<0, 4, 1, 5>(l, h);
				x86vec::v4s32 ih=x86vec::permute<2, 6, 3, 7>(l, h);
				x86vec::v2f64 fl=x86vec::as<x86vec::v2f64>(il);
				x86vec::v2f64 fh=x86vec::as<x86vec::v2f64>(ih);
				vf_type r(fl, fh);
				return r;
			}
			
                        static
                        vf_type cvt_i_to_f(const vi_type& i) {
                                return x86vec::cvt<x86vec::v4f64>(i);
                        }

                        static
                        vi_type cvt_f_to_i(const vf_type& f) {
                                return x86vec::cvt<x86vec::v4s32>(f);
                        }
                        // including rounding towards zero
                        static
                        vi_type cvt_rz_f_to_i(const vf_type& f) {
                                return x86vec::cvt_rz<x86vec::v4s32>(f);
                        }
                };

#if defined (__AVX__)
                template <>
                struct func_traits<x86vec::v8f32, x86vec::v8s32> : public 
		func_traits<typename x86vec::v8f32::element_type,
			    typename x86vec::v8s32::element_type> {
                        typedef x86vec::v8f32 vf_type;
                        typedef x86vec::v8f32 vmf_type;
                        typedef x86vec::v8s32 vi_type;
                        typedef x86vec::v8s32 vmi_type;

			typedef d_real<vf_type> dvf_type;

			typedef x86vec::v4f64 vhpf_type;
			typedef func_traits<vhpf_type, x86vec::v4s32> 
			hpf_traits;

			static
			constexpr std::size_t vhpf_per_vf() {
				return 2;
			}
			
			static 
			void vf_to_vhpf(const vf_type& x, vhpf_type* r) {
				using namespace x86vec;
				using x86vec::impl::cvt;
				r[0] = cvt<v4f64, v8f32>::l(x);
				r[1] = cvt<v4f64, v8f32>::h(x);
			}

			static
			void vhpf_to_dvf(const vhpf_type* hpf, dvf_type& res) {
				using namespace x86vec;
				using x86vec::impl::cvt;
				vf_type lo(cvt<v8f32, v4f64>::l(hpf[0]));
				vhpf_type rest(hpf[0] - cvt<v4f64, v8f32>::l(lo));
				vf_type lo_lo(cvt<v8f32, v4f64>::l(rest));
					
				vf_type hi(cvt<v8f32, v4f64>::l(hpf[1]));
				rest = hpf[1] - cvt<v4f64, v8f32>::l(hi);
				
				vf_type hi_lo(cvt<v8f32, v4f64>::l(rest));

				vf_type msv(permute<0, 1, 2, 3, 
						    8, 9, 10, 11>(lo, hi));
				vf_type lsv(permute<0, 1, 2, 3, 
						    8, 9, 10, 11>(lo_lo, 
								  hi_lo));
				res = dvf_type(msv, lsv);
			}

                        static
                        vmf_type vmi_to_vmf(const vmi_type& mi) {
                                return x86vec::as<x86vec::v8f32>(mi);
                        }
                        static
                        vmi_type vmf_to_vmi(const vmf_type& mf) {
                                return x86vec::as<x86vec::v8s32>(mf);
                        }
                        static
                        vi_type sel(const vmi_type& msk,
                                    const vi_type& t, const vi_type& f) {
                                return select(msk, t, f);
                        }
                        static
                        vf_type sel(const vmf_type& msk,
                                    const vf_type& t, const vf_type& f) {
                                return select(msk, t, f);
                        }
			static
			vf_type gather(const float* p, const vi_type& idx,
				       int sc) {
				return x86vec::gather<vf_type>(p, idx, sc);
			}
                        static
                        vf_type insert_exp(const vi_type& e) {
				vi_type ep(e << x86vec::const_shift::_23);
                                return x86vec::as<x86vec::v8f32>(ep);
                        }
                        static
                        vi_type extract_exp(const vf_type& d) {
                                x86vec::v8s32 e= x86vec::as<x86vec::v8s32>(d);
                                e >>= x86vec::const_shift::_23;
                                e &= x86vec::v8s32(0xff, 0xff, 0xff, 0xff,
						   0xff, 0xff, 0xff, 0xff);
                                return e;
                        }
                        static
                        vf_type cvt_i_to_f(const vi_type& i) {
                                return x86vec::cvt<x86vec::v8f32>(i);
                        }

                        static
                        vi_type cvt_f_to_i(const vf_type& f) {
                                return x86vec::cvt<x86vec::v8s32>(f);
                        }
                        // including rounding towards zero
                        static
                        vi_type cvt_rz_f_to_i(const vf_type& f) {
                                return x86vec::cvt_rz<x86vec::v8s32>(f);
                        }

			static 
			vi_type as_int(const vf_type& f) {
				return x86vec::as<x86vec::v8s32>(f);
			}

			static 
			vf_type as_float(const vi_type& i) {
				return x86vec::as<x86vec::v8f32>(i);
			}
                };

#endif

	}

}

// Local variables:
// mode: c++
// end:
#endif
