#if !defined (__X86VEC_MATH_FUNC_H__)
#define __X86VEC_MATH_FUNC_H__ 1

#include <cftal/config.h>
#include <cftal/x86vec.h>
#include <cftal/math_funcs.h>

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
				x86vec::const4_u32<0xf8000000U, 
						   0xffffffffU,
						   0xf8000000U, 
						   0xffffffffU>::dv();
			h = a & msk;
			l = a - h;
		}
        };

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
                                x86vec::v4s32 xm= x86vec::permute<0, 0, 1, 1>(mi);
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

	}

}

// Local variables:
// mode: c++
// end:
#endif
