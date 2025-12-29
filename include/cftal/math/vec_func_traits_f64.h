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
#if !defined (__CFTAL_MATH_VEC_FUNC_TRAITS_F64_H__)
#define __CFTAL_MATH_VEC_FUNC_TRAITS_F64_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/vec_d_real_traits_f64.h>
#include <cftal/math/func_traits_f64_s32.h>
#include <cftal/divisor.h>
#include <cftal/vec_cvt.h>
#include <cftal/constants.h>
#include <cftal/x86/cast_bits.h>

namespace cftal {

    namespace math {

        template <std::size_t _N>
        struct vec_func_traits_f64
            : public func_traits<double, int32_t> {
            using vf_type = vec<double, _N>;
            using vmf_type = typename vec<double, _N>::mask_type;
            using vi_type = vec<int32_t, _N>;
            using vmi_type = typename vec<int32_t, _N>::mask_type;
            using vu_type = vec<uint32_t, _N>;
            using vmu_type = typename vec<uint32_t, _N>::mask_type;
            // integer vector with the same length as vf_type
            using vi2_type = vec<int32_t, 2*_N >;
            using vmi2_type = typename vec<int32_t, 2* _N>::mask_type;
            using vli_type = vec<int64_t, _N>;
            using vmli_type= typename vec<int64_t, _N>::mask_type;
            using vlu_type = vec<uint64_t, _N>;
            using vmlu_type= typename vec<uint64_t, _N>::mask_type;

            using vdf_type = d_real<vf_type>;

            using vlf_traits = func_traits<vec<float, _N>,
                                           vec<int32_t, _N> >;

            static
            vmf_type
            vmi_to_vmf(const vmi_type& mi) {
                return cvt_mask<vmf_type, vmi_type>::v(mi);
            }

            static
            vmi_type
            vmf_to_vmi(const vmf_type& mf) {
                return cvt_mask<vmi_type, vmf_type>::v(mf);
            }

            static
            vmi2_type
            vmf_to_vmi2(const vmf_type& mf) {
                return cvt_mask<vmi2_type, vmf_type>::v(mf);
            };

            static
            vmf_type
            vmi2_to_vmf(const vmi2_type& mi) {
                return cvt_mask<vmf_type, vmi2_type>::v(mi);
            };

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
            bool any_of_vmi2(const vmi2_type& b) {
                return any_of(b);
            }

            static
            bool all_of_vmi2(const vmi2_type& b) {
                return all_of(b);
            }

            static
            bool none_of_vmi2(const vmi2_type& b) {
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

            static
            vi2_type sel_vi2(const vmi2_type& msk,
                            const vi2_type& t, const vi2_type& f) {
                return select(msk, t, f);
            }

            static
            vi2_type sel_val_or_zero_vi2(const vmi2_type& msk,
                                         const vi2_type& t) {
                return select_val_or_zero(msk, t);
            }

            static
            vi2_type sel_zero_or_val_vi2(const vmi2_type& msk,
                                         const vi2_type& f) {
                return select_zero_or_val(msk, f);
            }

            static
            vli_type sel_vli(const vmli_type& msk,
                             const vli_type& t, const vli_type& f) {
                return select(msk, t, f);
            }

            static
            vf_type insert_exp_vi2(const vi2_type& e) {
                vi2_type ep(e << 20);
                vf_type r= as<vf_type>(ep);
                r &= exp_f64_msk::v.f64();
                return r;
            }

            static
            vi2_type vi_to_vi2(const vi_type& r) {
                vi2_type t=combine_even_odd(r, r);
                return t;
            }

            static
            vi_type vi2_odd_to_vi(const vi2_type& r) {
                vi_type t=odd_elements(r);
                return t;
            }

            static
            vi_type vi2_even_to_vi(const vi2_type& r) {
                vi_type t=even_elements(r);
                return t;
            }

            static
            vf_type insert_exp(const vi_type& e) {
                vi_type ep(e << 20);
                vi2_type ir(combine_zeroeven_odd(ep));
                vf_type r= as<vf_type>(ir);
                // r &= vf_type(exp_f64_msk::v.f64());
                return r;
            }

            static
            vi_type extract_exp(const vf_type& d) {
                const vf_type msk(exp_f64_msk::v.f64());
                vf_type m(d & msk);
                vi2_type di= as<vi2_type>(m);
                vi_type r= odd_elements(di);
                r >>= 20;
                return r;
            }

            static
            vi_type extract_high_word(const vf_type& d) {
                vi2_type di=as<vi2_type>(d);
                return odd_elements(di);
            }

            static
            vi_type extract_low_word(const vf_type& d) {
                vi2_type di=as<vi2_type>(d);
                return even_elements(di);
            }

            static
            void
            extract_words(vi_type& low_word, vi_type& high_word,
                          const vf_type& d) {
                vi2_type di=as<vi2_type>(d);
                low_word=even_elements(di);
                high_word=odd_elements(di);
            }

            static
            void
            extract_words_vi2(vi2_type& low_word, vi2_type& high_word,
                              const vf_type& x) {
                vi2_type di=as<vi2_type>(x);
                low_word = di;
                high_word = di;
            }

            static
            vf_type
            combine_words(const vi_type& l, const vi_type& h) {
                vi2_type vi= combine_even_odd(l, h);
                vf_type r= as<vf_type>(vi);
                return r;
            }

            static
            vf_type
            combine_words_vi2(const vi2_type& l, const vi2_type& h) {
                vi2_type t= select_even_odd(l, h);
                vf_type r=as<vf_type>(t);
                return r;
            }

            static
            vf_type clear_low_word(const vf_type& d) {
                const uint64_t mu=0xffffffff00000000ULL;
                const bytes8 mf(mu);
                const vf_type m(mf.f64());
                return d & m;
            }

            static
            vli_type as_vli(const vf_type& d) {
                vli_type r=as<vli_type>(d);
                return r;
            }

            static
            vf_type as_vf(const vli_type& l) {
                vf_type r=as<vf_type>(l);
                return r;
            }

            static
            vf_type cvt_i_to_f(const vi_type& i) {
                return cvt<vf_type>(i);
            }

            static
            vi_type cvt_f_to_i(const vf_type& f) {
                return cvt<vi_type>(f);
            }

            static
            vi2_type cvt_f_to_i2(const vf_type& f) {
#if 1
                vi_type t=cvt<vi_type>(f);
                vi2_type r=combine_even_odd(t, t);
#else
                // the number is 2^52+2^51
                vf_type fr=f + 0x1.8p52;
                vi2_type r=as<vi2_type>(fr);
                r=copy_even_to_odd(r);
#endif
                return r;
            }

            // including rounding towards zero
            static
            vi_type cvt_rz_f_to_i(const vf_type& f) {
                return cvt_rz<vi_type>(f);
            }
        };

        template <std::size_t _N>
        struct func_traits<vec<double, _N>, vec<int32_t, _N> >
            : public vec_func_traits_f64<_N> {
        };

    }
}

// Local variables:
// mode: c++
// end:
#endif
