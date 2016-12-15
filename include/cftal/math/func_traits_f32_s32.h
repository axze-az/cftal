#if !defined (__CFTAL_MATH_FUNC_TRAIT_F32_S32_H__)
#define __CFTAL_MATH_FUNC_TRAIT_F32_S32_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/std_types.h>
#include <cftal/math/elem_func.h>
#include <limits>

namespace cftal {
    namespace math {

        template <>
        struct func_traits<float, int32_t>
            : public d_real_traits<float> {
            using vf_type = float;
            using vi_type = int32_t;
            using vmf_type = bool;
            using vmi_type = bool;
            union ud_t {
                float _d;
                uint32_t _u;
            };

            static constexpr int32_t bias() { return 127; }
            static constexpr int32_t e_max() { return 127; }
            static constexpr int32_t e_min() { return -126; }
            static constexpr int32_t e_mask() { return 0xff; }
            static constexpr int32_t bits() { return 23; }
            static constexpr int32_t vec_len() { return 1; }

            static constexpr float pinf() {
                return std::numeric_limits<float>::infinity();
            }
            static constexpr float ninf() {
                return -std::numeric_limits<float>::infinity();
            }
            static constexpr float nan() {
                return std::numeric_limits<float>::quiet_NaN();
            }
            static
            vmf_type vmi_to_vmf(const vmi_type& mi) {
                return mi;
            }
            static
            vmi_type vmf_to_vmi(const vmf_type& mf) {
                return mf;
            }
            static
            vi_type sel(const vmi_type& msk,
                        const vi_type& t, const vi_type& f) {
                return msk ? t : f;
            }
            static
            vf_type sel(const vmf_type& msk,
                        const vf_type& t, const vf_type& f) {
                return msk ? t : f;
            }
            static
            vf_type insert_exp(const vi_type& e) {
                ud_t t;
                t._u = uint32_t(e) << bits();
                return t._d;
            }
            static
            vi_type extract_exp(const vf_type& d) {
                ud_t t;
                t._d = d;
                return (t._u >> bits()) & e_mask();
            }
            static
            vf_type cvt_i_to_f(const vi_type& i) {
                return vf_type(i);
            }
            // including rounding to nearest.
            static
            vi_type cvt_f_to_i(const vf_type& f) {
                return f < 0 ?
                           (vi_type)(f - 0.5) :
                    (vi_type)(f + 0.5);
            }
            // including rounding towards zero
            static
            vi_type cvt_rz_f_to_i(const vf_type& f) {
                return (vi_type)f;
            }

            static
            vi_type as_int(const vf_type& f) {
                ud_t t;
                t._d = f;
                return t._u;
            }

            static
            vf_type as_float(const vi_type& i) {
                ud_t t;
                t._u = i;
                return t._d;
            }
        };
    }
}


// Local Variables:
// mode: c++
// end:
#endif
