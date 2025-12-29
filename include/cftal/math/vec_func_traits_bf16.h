//
// Copyright (C) 2010-2026 Axel Zeuner
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
#if !defined (__CFTAL_MATH_VEC_FUNC_TRAITS_BF16_H__)
#define __CFTAL_MATH_VEC_FUNC_TRAITS_BF16_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/vec_cvt.h>
#include <cftal/x86/cast_bits.h>
#include <cftal/math/vec_func_traits_f32.h>
#include <cftal/math/func_traits_bf16_s16.h>

namespace cftal {

    namespace math {

        template <std::size_t _N>
        struct vec_func_traits_bf16 : public func_traits<bf16_t, int16_t> {
            using vf_type = vec<bf16_t, _N>;
            using vmf_type = typename vf_type::mask_type;
            using vi_type = vec<int16_t, _N>;
            using vu_type = vec<uint16_t, _N>;
            using vmi_type = typename vi_type::mask_type;
            using vli_type = vec<int32_t, _N>;
            using v2i_type = vec<int16_t, 2*_N>;

            // using vdf_type = d_real<vf_type>;

            using vhf_traits = func_traits<vec<float, _N>,
                                           vec<int32_t, _N> >;

            static
            vmf_type vmi_to_vmf(const vmi_type& mi) {
                return as<vmf_type>(mi);
            }
            static
            vmi_type vmf_to_vmi(const vmf_type& mf) {
                return as<vmi_type>(mf);
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
                return select(msk, t, f);
            }
            static
            vi_type sel_val_or_zero_vi(const vmi_type& msk,
                                       const vi_type& t) {
                return select_val_or_zero(msk, t);
            }
            static
            vi_type sel_zero_or_val_vi(const vmi_type& msk,
                                       const vi_type& f) {
                return select_zero_or_val(msk, f);
            }
            static
            vf_type sel(const vmf_type& msk,
                        const vf_type& t, const vf_type& f) {
                return select(msk, t, f);
            }
            static
            vf_type sel_val_or_zero(const vmf_type& msk,
                                    const vf_type& t) {
                return select_val_or_zero(msk, t);
            }
            static
            vf_type sel_zero_or_val(const vmf_type& msk,
                                    const vf_type& f) {
                return select_zero_or_val(msk, f);
            }

#if 0
            static
            vf_type insert_exp(const vi_type& e) {
                vi_type ep(e << 10);
                return as<vf_type>(ep);
            }

            static
            vi_type extract_exp(const vf_type& d) {
                const vu_type msk(exp_f16_msk::v.u16());
                vu_type i=as_int(d);
                vu_type e(i & msk);
                e >>= 10;
                return e;
            }

            static
            vf_type cvt_i_to_f(const vi_type& i) {
                return cvt<vf_type>(i);
            }

            static
            vi_type cvt_f_to_i(const vf_type& f) {
                return cvt<vi_type>(f);
            }

            // including rounding towards zero
            static
            vi_type cvt_rz_f_to_i(const vf_type& f) {
                return cvt_rz<vi_type>(f);
            }
#endif
            static
            vi_type as_int(const vf_type& f) {
                return as<vi_type>(f);
            }

            static
            vf_type as_float(const vi_type& i) {
                return as<vf_type>(i);
            }

        };

        template <std::size_t _N>
        struct func_traits<vec<bf16_t, _N>, vec<int16_t, _N> >
            : public vec_func_traits_bf16<_N> {};

    }
}

// Local variables:
// mode: c++
// end:
#endif
