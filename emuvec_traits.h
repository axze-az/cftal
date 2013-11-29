#if !defined (__EMUVEC_TRAITS_H__)
#define __EMUVEC_TRAITS_H__ 1

#include <cftal/config.h>
#include <cftal/emuvec.h>
#include <cftal/math_func.h>

namespace cftal {

        template <>
        struct d_real_traits<emuvec::v2f64> : public has_fma<double> {
                constexpr d_real_traits<emuvec::v2f64>() = default;
                // result of a comparison operator
                typedef emuvec::v2f64 cmp_result_type;
                static bool any(const cmp_result_type& b) {
                        return !no_signs(b);
                }

                static emuvec::v2f64 sel(const cmp_result_type& s,
                                         const emuvec::v2f64& on_true,
                                         const emuvec::v2f64& on_false) {
                        return select(s, on_true, on_false);
                }

		static 
		void split(const emuvec::v2f64& a, 
			   emuvec::v2f64& h, 
			   emuvec::v2f64& l) {
			const emuvec::v2f64 msk= 
				emuvec::const_v4u32<0xf8000000U, 
						    0xffffffffU,
						    0xf8000000U, 
						    0xffffffffU>::dv();
			h = a & msk;
			l = a - h;
		}
        };

        template <>
        struct d_real_traits<emuvec::v4f32> : public has_fma<float> {
                constexpr d_real_traits<emuvec::v4f32>() = default;
                // result of a comparison operator
                typedef emuvec::v4f32 cmp_result_type;
                static bool any(const cmp_result_type& b) {
                        return !no_signs(b);
                }

                static emuvec::v4f32 sel(const cmp_result_type& s,
                                         const emuvec::v4f32& on_true,
                                         const emuvec::v4f32& on_false) {
                        return select(s, on_true, on_false);
                }

		static 
		void split(const emuvec::v4f32& a, 
			   emuvec::v4f32& h, 
			   emuvec::v4f32& l) {
			const emuvec::v4f32 msk= 
				emuvec::const_v4u32<0xfffff000U, 
						    0xfffff000U, 
						    0xfffff000U, 
						    0xfffff000U>::fv();
			h = a & msk;
			l = a - h;
		}
        };

#if 0
        template <>
        struct d_real_traits<emuvec::v4f64> : public has_fma<double> {
                constexpr d_real_traits<emuvec::v4f64>() = default;
                // result of a comparison operator
                typedef emuvec::v4f64 cmp_result_type;
                static bool any(const cmp_result_type& b) {
                        return !no_signs(b);
                }

                static emuvec::v4f64 sel(const cmp_result_type& s,
                                         const emuvec::v4f64& on_true,
                                         const emuvec::v4f64& on_false) {
                        return select(s, on_true, on_false);
                }

		static 
		void split(const emuvec::v4f64& a, 
			   emuvec::v4f64& h, 
			   emuvec::v4f64& l) {
			const emuvec::v4f64 msk= 
				emuvec::const_v8u32<0xf8000000U, 
						    0xffffffffU,
						    0xf8000000U, 
						    0xffffffffU,
						    0xf8000000U, 
						    0xffffffffU,
						    0xf8000000U, 
						    0xffffffffU>::dv();
			h = a & msk;
			l = a - h;
		}
        };

        template <>
        struct d_real_traits<emuvec::v8f32> : public has_fma<float> {
                constexpr d_real_traits<emuvec::v8f32>() = default;
                // result of a comparison operator
                typedef emuvec::v8f32 cmp_result_type;
                static bool any(const cmp_result_type& b) {
                        return !no_signs(b);
                }

                static emuvec::v8f32 sel(const cmp_result_type& s,
                                         const emuvec::v8f32& on_true,
                                         const emuvec::v8f32& on_false) {
                        return select(s, on_true, on_false);
                }

		static 
		void split(const emuvec::v8f32& a, 
			   emuvec::v8f32& h, 
			   emuvec::v8f32& l) {
			const emuvec::v8f32 msk= 
				emuvec::const_v8u32<0xfffff000U, 
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
                struct func_traits<emuvec::v2f64, emuvec::v4s32> : public 
		func_traits<typename emuvec::v2f64::element_type,
			    typename emuvec::v4s32::element_type> {
                        typedef emuvec::v2f64 vf_type;
                        typedef emuvec::v2f64 vmf_type;
                        typedef emuvec::v4s32 vi_type;
                        typedef emuvec::v4s32 vmi_type;

                        static
                        vmf_type vmi_to_vmf(const vmi_type& mi) {
                                emuvec::v4s32 xm= 
					emuvec::permute<0, 0, 1, 1>(mi);
                                return emuvec::as<emuvec::v2f64>(xm);
                        }
                        static
                        vmi_type vmf_to_vmi(const vmf_type& mf) {
                                emuvec::v4s32 xm= emuvec::as<emuvec::v4s32>(mf);
                                xm = emuvec::permute<1, 3, 0, 2>(xm);
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
                        vf_type insert_exp(const vi_type& e) {
				vi_type ep(emuvec::permute<0, 0, 1, 1>(e));
                                emuvec::v2u64 m= emuvec::as<emuvec::v2u64>(ep);
                                m <<= emuvec::const_shift::_52;
                                return emuvec::as<emuvec::v2f64>(m);
                        }
                        static
                        vi_type extract_exp(const vf_type& d) {
                                emuvec::v4s32 e= emuvec::as<emuvec::v4s32>(d);
                                e >>= emuvec::const_shift::_20;
                                e = emuvec::permute<1, 3, 0, 0>(e);
                                e &= emuvec::v4s32(0x7ff, 0x7ff, 0, 0);
                                return e;
                        }
			
			static
			vi_type extract_high_word(const vf_type& d) {
				emuvec::v4s32 w=emuvec::as<emuvec::v4s32>(d);
				w= emuvec::permute<1, 3, 1, 3>(w);
				return w;
				
			}

			static
			vi_type extract_low_word(const vf_type& d) {
				emuvec::v4s32 w=emuvec::as<emuvec::v4s32>(d);
				w= emuvec::permute<0, 2, 0, 2>(w);
				return w;
			}

			static 
			vf_type combine_words(const vi_type& l,
					      const vi_type& h) {
				emuvec::v4s32 c=
					emuvec::permute<0, 4, 1, 5>(l, h);
				emuvec::v2f64 r=emuvec::as<vf_type>(c);
				return r;
			}
			
                        static
                        vf_type cvt_i_to_f(const vi_type& i) {
                                return emuvec::cvt_lo<emuvec::v2f64>(i);
                        }

                        static
                        vi_type cvt_f_to_i(const vf_type& f) {
                                return emuvec::cvt_lo<emuvec::v4s32>(f);
                        }
                        // including rounding towards zero
                        static
                        vi_type cvt_rz_f_to_i(const vf_type& f) {
                                return emuvec::cvt_rz_lo<emuvec::v4s32>(f);
                        }
                };


                template <>
                struct func_traits<emuvec::v4f32, emuvec::v4s32> : public 
		func_traits<typename emuvec::v4f32::element_type,
			    typename emuvec::v4s32::element_type> {
                        typedef emuvec::v4f32 vf_type;
                        typedef emuvec::v4f32 vmf_type;
                        typedef emuvec::v4s32 vi_type;
                        typedef emuvec::v4s32 vmi_type;
			typedef d_real<vf_type> dvf_type;

			typedef emuvec::v2f64 vhpf_type;
			typedef func_traits<vhpf_type, emuvec::v4s32> 
			hpf_traits;
			static
			constexpr std::size_t vhpf_per_vf() {
				return 2;
			}
			
			static 
			void vf_to_vhpf(const vf_type& x, vhpf_type* r) {
				using namespace emuvec;
				using emuvec::impl::cvt;
				r[0] = cvt<v2f64, v4f32>::l(x);
				r[1] = cvt<v2f64, v4f32>::h(x);
			}

			static
			void vhpf_to_dvf(const vhpf_type* hpf, dvf_type& res) {
				using namespace emuvec;
				using emuvec::impl::cvt;
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
                                return emuvec::as<emuvec::v4f32>(mi);
                        }
                        static
                        vmi_type vmf_to_vmi(const vmf_type& mf) {
                                return emuvec::as<emuvec::v4s32>(mf);
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
                        vf_type insert_exp(const vi_type& e) {
				vi_type ep(e << emuvec::const_shift::_23);
                                return emuvec::as<emuvec::v4f32>(ep);
                        }
                        static
                        vi_type extract_exp(const vf_type& d) {
                                emuvec::v4s32 e= emuvec::as<emuvec::v4s32>(d);
                                e >>= emuvec::const_shift::_23;
                                e &= emuvec::v4s32(0xff, 0xff, 0xff, 0xff);
                                return e;
                        }
                        static
                        vf_type cvt_i_to_f(const vi_type& i) {
                                return emuvec::cvt<emuvec::v4f32>(i);
                        }

                        static
                        vi_type cvt_f_to_i(const vf_type& f) {
                                return emuvec::cvt<emuvec::v4s32>(f);
                        }
                        // including rounding towards zero
                        static
                        vi_type cvt_rz_f_to_i(const vf_type& f) {
                                return emuvec::cvt_rz<emuvec::v4s32>(f);
                        }

			static 
			vi_type as_int(const vf_type& f) {
				return emuvec::as<emuvec::v4s32>(f);
			}

			static 
			vf_type as_float(const vi_type& i) {
				return emuvec::as<emuvec::v4f32>(i);
			}
                };

#if 0
                template <>
                struct func_traits<emuvec::v4f64, emuvec::v4s32> : public 
		func_traits<typename emuvec::v4f64::element_type,
			    typename emuvec::v4s32::element_type> {
                        typedef emuvec::v4f64 vf_type;
                        typedef emuvec::v4f64 vmf_type;
                        typedef emuvec::v4s32 vi_type;
                        typedef emuvec::v4s32 vmi_type;

                        static
                        vmf_type vmi_to_vmf(const vmi_type& mi) {
				// TODO AVX2 code
                                emuvec::v4s32 xml=emuvec::permute<0, 0, 1, 1>(mi);
				emuvec::v4s32 xmh=emuvec::permute<2, 2, 3, 3>(mi);
				emuvec::v2f64 dml=emuvec::as<emuvec::v2f64>(xml);
				emuvec::v2f64 dmh=emuvec::as<emuvec::v2f64>(xmh);
				emuvec::v4f64 r(dml, dmh);
				return r;
                        }
                        static
                        vmi_type vmf_to_vmi(const vmf_type& mf) {
				// TODO AVX2 code
				emuvec::v2f64 mfl=low_half(mf);
				emuvec::v2f64 mfh=high_half(mf);
                                emuvec::v4s32 xml=emuvec::as<emuvec::v4s32>(mfl);
                                emuvec::v4s32 xmh=emuvec::as<emuvec::v4s32>(mfh);
				emuvec::v4s32 xm =emuvec::permute<0, 2, 4, 6>(xml, xmh);
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
				return emuvec::gather<vf_type>(p, idx, sc);
			}
                        static
                        vf_type insert_exp(const vi_type& e) {
				// TODO AVX2 code
				// 52 - 32
				vi_type ep(e << emuvec::const_shift::_20);
				vi_type hep(emuvec::permute<2, 2, 3, 3>(ep));
				vi_type lep(emuvec::permute<0, 0, 1, 1>(ep));
				emuvec::v2f64 fh(emuvec::as<emuvec::v2f64>(hep));
				emuvec::v2f64 lh(emuvec::as<emuvec::v2f64>(lep));
#if !defined (__AVX__)
				lh &= emuvec::v_exp_v2f64_msk::dv();
				fh &= emuvec::v_exp_v2f64_msk::dv();
				vf_type r(lh, fh);
#else
				vf_type r(lh, fh);
				r &= emuvec::v_exp_v4f64_msk::dv();
#endif
				return r;
                        }
			
                        static
                        vi_type extract_exp(const vf_type& d) {
				// TODO AVX2 code
#if !defined (__AVX__)
				vf_type m(low_half(d) & emuvec::v_exp_v2f64_msk::dv(),
					  high_half(d) & emuvec::v_exp_v2f64_msk::dv());
#else
				vf_type m(d & emuvec::v_exp_v4f64_msk::dv());
#endif
				emuvec::v2f64 fh(high_half(d));
				emuvec::v2f64 fl(low_half(d));
				emuvec::v4s32 hi(emuvec::as<emuvec::v4s32>(fh));
				emuvec::v4s32 li(emuvec::as<emuvec::v4s32>(fl));
				emuvec::v4s32 r(emuvec::permute<1, 3, 5, 7>(li, hi));
				r >>= emuvec::const_shift::_20;
				return r;
                        }
			static
			vi_type extract_high_word(const vf_type& d) {
				emuvec::v2f64 l= low_half(d);
				emuvec::v2f64 h= high_half(d);
				emuvec::v4s32 il=emuvec::as<emuvec::v4s32>(l);
				emuvec::v4s32 ih=emuvec::as<emuvec::v4s32>(h);
				emuvec::v4s32 w=emuvec::permute<1, 3, 5, 7>(il, ih);
				return w;
			}

			static
			vi_type extract_low_word(const vf_type& d) {
				emuvec::v2f64 l= low_half(d);
				emuvec::v2f64 h= high_half(d);
				emuvec::v4s32 il=emuvec::as<emuvec::v4s32>(l);
				emuvec::v4s32 ih=emuvec::as<emuvec::v4s32>(h);
				emuvec::v4s32 w=emuvec::permute<0, 2, 4, 6>(il, ih);
				return w;
			}

			static 
			vf_type combine_words(const vi_type& l,
					      const vi_type& h) {
				emuvec::v4s32 il=emuvec::permute<0, 4, 1, 5>(l, h);
				emuvec::v4s32 ih=emuvec::permute<2, 6, 3, 7>(l, h);
				emuvec::v2f64 fl=emuvec::as<emuvec::v2f64>(il);
				emuvec::v2f64 fh=emuvec::as<emuvec::v2f64>(ih);
				vf_type r(fl, fh);
				return r;
			}
			
                        static
                        vf_type cvt_i_to_f(const vi_type& i) {
                                return emuvec::cvt<emuvec::v4f64>(i);
                        }

                        static
                        vi_type cvt_f_to_i(const vf_type& f) {
                                return emuvec::cvt<emuvec::v4s32>(f);
                        }
                        // including rounding towards zero
                        static
                        vi_type cvt_rz_f_to_i(const vf_type& f) {
                                return emuvec::cvt_rz<emuvec::v4s32>(f);
                        }
                };

                template <>
                struct func_traits<emuvec::v8f32, emuvec::v8s32> : public 
		func_traits<typename emuvec::v8f32::element_type,
			    typename emuvec::v8s32::element_type> {
                        typedef emuvec::v8f32 vf_type;
                        typedef emuvec::v8f32 vmf_type;
                        typedef emuvec::v8s32 vi_type;
                        typedef emuvec::v8s32 vmi_type;

			typedef d_real<vf_type> dvf_type;

			typedef emuvec::v4f64 vhpf_type;
			typedef func_traits<vhpf_type, emuvec::v4s32> 
			hpf_traits;

			static
			constexpr std::size_t vhpf_per_vf() {
				return 2;
			}
			
			static 
			void vf_to_vhpf(const vf_type& x, vhpf_type* r) {
				using namespace emuvec;
				using emuvec::impl::cvt;
				r[1] = cvt<v4f64, v8f32>::h(x);
				r[0] = cvt<v4f64, v8f32>::l(x);
			}

			static
			void vhpf_to_dvf(const vhpf_type* hpf, dvf_type& res) {
				using namespace emuvec;
				using emuvec::impl::cvt;
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
                                return emuvec::as<emuvec::v8f32>(mi);
                        }
                        static
                        vmi_type vmf_to_vmi(const vmf_type& mf) {
                                return emuvec::as<emuvec::v8s32>(mf);
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
				return emuvec::gather<vf_type>(p, idx, sc);
			}
                        static
                        vf_type insert_exp(const vi_type& e) {
				vi_type ep(e << emuvec::const_shift::_23);
                                return emuvec::as<emuvec::v8f32>(ep);
                        }
                        static
                        vi_type extract_exp(const vf_type& d) {
                                emuvec::v8s32 e= emuvec::as<emuvec::v8s32>(d);
                                e >>= emuvec::const_shift::_23;
                                e &= emuvec::v8s32(0xff, 0xff, 0xff, 0xff,
						   0xff, 0xff, 0xff, 0xff);
                                return e;
                        }
                        static
                        vf_type cvt_i_to_f(const vi_type& i) {
                                return emuvec::cvt<emuvec::v8f32>(i);
                        }

                        static
                        vi_type cvt_f_to_i(const vf_type& f) {
                                return emuvec::cvt<emuvec::v8s32>(f);
                        }
                        // including rounding towards zero
                        static
                        vi_type cvt_rz_f_to_i(const vf_type& f) {
                                return emuvec::cvt_rz<emuvec::v8s32>(f);
                        }

			static 
			vi_type as_int(const vf_type& f) {
				return emuvec::as<emuvec::v8s32>(f);
			}

			static 
			vf_type as_float(const vi_type& i) {
				return emuvec::as<emuvec::v8f32>(i);
			}
                };
#endif
	}
}



// Local variables:
// mode: c++
// end:
#endif
