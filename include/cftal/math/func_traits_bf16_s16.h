//
// Copyright (C) 2010-2024 Axel Zeuner
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
//
#if !defined (__CFTAL_MATH_FUNC_TRAIT_BF16_S16_H__)
#define __CFTAL_MATH_FUNC_TRAIT_BF16_S16_H__ 1

#include <cftal/config.h>
// #include <cftal/d_real.h>
// #include <cftal/d_real_traits_bf16.h>
#include <cftal/bf16_t.h>
#include <cftal/std_types.h>
#include <cftal/math/func_traits.h>
#include <limits>

namespace cftal {
    namespace math {

        template <>
        struct func_traits<bf16_t, int16_t>
            : public d_real_traits<bf16_t> {
            using vf_type = bf16_t;
            using vi_type = int16_t;
            using vu_type = uint16_t;
            using vmf_type = bool;
            using vmi_type = bool;
            using vmu_type = bool;
            union ud_t {
                bf16_t _d;
                uint16_t _u;
            };

            static constexpr int32_t bias() { return 127; }
            static constexpr int32_t e_max() { return 127; }
            static constexpr int32_t e_min() { return -126; }
            static constexpr int32_t e_mask() { return 0xff; }
            static constexpr int32_t bits() { return 23-16; }
            static constexpr int32_t vec_len() { return 1; }

            static constexpr bf16_t pinf() {
                return std::numeric_limits<vf_type>::infinity();
            }
            static constexpr bf16_t ninf() {
                return -std::numeric_limits<vf_type>::infinity();
            }
            static constexpr bf16_t nan() {
                return std::numeric_limits<vf_type>::quiet_NaN();
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
            bool any_of_vmf(const vmf_type& b) {
                return any_of(b);
            }

            static
            bool all_of_vmf(const vmf_type& b) {
                return all_of(b);
            }

            static
            bool none_of_vmf(const vmf_type& b) {
                return none_of(b);
            }

            static
            bool any_of_vmi(const vmi_type& b) {
                return any_of(b);
            }

            static
            bool all_of_vmi(const vmi_type& b) {
                return all_of(b);
            }

            static
            bool none_of_vmi(const vmi_type& b) {
                return none_of(b);
            }

            static
            vi_type sel_vi(const vmi_type& msk,
                        const vi_type& t, const vi_type& f) {
                return msk ? t : f;
            }
            static
            vi_type sel_val_or_zero_vi(const vmi_type& msk,
                                    const vi_type& t) {
                return msk ? t : vi_type(0);
            }
            static
            vi_type sel_zero_or_val_vi(const vmi_type& msk,
                                    const vi_type& f) {
                return msk ? vi_type(0) : f;
            }

            static
            vf_type sel(const vmf_type& msk,
                        const vf_type& t, const vf_type& f) {
                return msk ? t : f;
            }
            static
            vf_type sel_val_or_zero(const vmf_type& msk,
                                    const vf_type& t) {
                return msk ? t : vf_type(0);
            }
            vf_type sel_zero_or_val(const vmf_type& msk,
                                    const vf_type& f) {
                return msk ? vf_type(0) : f;
            }
            static
            vf_type insert_exp(const vi_type& e) {
                ud_t t;
                t._u = uint16_t(e) << bits();
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
                return static_cast<vf_type>(i);
            }
            // including rounding to nearest.
            static
            vi_type cvt_f_to_i(const vf_type& f) {
                return f < 0 ?
                    static_cast<vi_type>(vf_type(f - 0.5_bf16)) :
                    static_cast<vi_type>(vf_type(f + 0.5_bf16));
            }
            // including rounding towards zero
            static
            vi_type cvt_rz_f_to_i(const vf_type& f) {
                return static_cast<vi_type>(f);
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
