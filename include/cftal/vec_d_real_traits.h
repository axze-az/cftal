//
// Copyright (C) 2010-2023 Axel Zeuner
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
#if !defined (__CFTAL_VEC_D_REAL_TRAITS_H__)
#define __CFTAL_VEC_D_REAL_TRAITS_H__ 1

#include <cftal/config.h>
#include <cftal/vec_t_n.h>
#include <cftal/d_real.h>
#include <cftal/d_real_traits_f64.h>
#include <cftal/d_real_traits_f32.h>
#include <cftal/d_real_traits_f16.h>

namespace cftal {

    template <std::size_t _N>
    struct d_real_traits<vec<double, _N> > : public has_fma<double> {
        using cmp_result_type = typename vec<double, _N>::mask_type;
        using int_type = vec<int32_t, _N>;

        static
        bool any_of_v(const cmp_result_type& b) {
            return any_of(b);
        }

        static
        bool all_of_v(const cmp_result_type& b) {
            return all_of(b);
        }

        static
        bool none_of_v(const cmp_result_type& b) {
            return none_of(b);
        }

        static
        vec<double, _N>
        sel (const cmp_result_type& s,
             const vec<double, _N>& on_true,
             const vec<double, _N>& on_false) {
            return select(s, on_true, on_false);
        }

        static
        void
        split(const vec<double, _N> & a,
              vec<double, _N>& h,
              vec<double, _N>& l) {
            const double msk=
                const_u64<0xf8000000U, 0xffffffffU>::v.f64();
            const vec<double, _N> th = a & msk;
            const vec<double, _N> tl = a - th;
            h = th;
            l = tl;
        }

        constexpr
        static
        double
        scale_div_threshold() {
            // -1022 + 53
            return 0x1.p-969;
        }

    };

    template <std::size_t _N>
    struct d_real_traits<vec<float, _N> > : public has_fma<float> {
        using cmp_result_type = typename vec<float, _N>::mask_type;
        using int_type = vec<int32_t, _N>;

        static
        bool any_of_v(const cmp_result_type& b) {
            return any_of(b);
        }

        static
        bool all_of_v(const cmp_result_type& b) {
            return all_of(b);
        }

        static
        bool none_of_v(const cmp_result_type& b) {
            return none_of(b);
        }

        static
        vec<float, _N>
        sel(const cmp_result_type& s,
            const vec<float, _N>& on_true,
            const vec<float, _N>& on_false) {
            return select(s, on_true, on_false);
        }

        static
        void
        split(const vec<float, _N> & a,
              vec<float, _N>& h,
              vec<float, _N>& l) {
            const float msk=
                const_u32<0xfffff000U>::v.f32();
            const vec<float, _N> th = a & msk;
            const vec<float, _N> tl = a - th;
            h = th;
            l = tl;
        }

        constexpr
        static
        float
        scale_div_threshold() {
            // -126 + 24
            return 0x1.p-102f;
        }

    };

    template <std::size_t _N>
    struct d_real_traits<vec<f16_t, _N> > : public has_fma<f16_t> {
        using cmp_result_type = typename vec<f16_t, _N>::mask_type;
        using int_type = vec<int16_t, _N>;

        static
        bool any_of_v(const cmp_result_type& b) {
            return any_of(b);
        }

        static
        bool all_of_v(const cmp_result_type& b) {
            return all_of(b);
        }

        static
        bool none_of_v(const cmp_result_type& b) {
            return none_of(b);
        }

        static
        vec<f16_t, _N>
        sel(const cmp_result_type& s,
            const vec<f16_t, _N>& on_true,
            const vec<f16_t, _N>& on_false) {
            return select(s, on_true, on_false);
        }

        static
        void
        split(const vec<f16_t, _N> & a,
              vec<f16_t, _N>& h,
              vec<f16_t, _N>& l) {
            const f16_t msk=as<f16_t>(uint16_t(0xffc0));
            const vec<f16_t, _N> th = a & msk;
            const vec<f16_t, _N> tl = a - th;
            h = th;
            l = tl;
        }

        // constexpr
        static
        f16_t
        scale_div_threshold() {
            // -15 + 11
            return 0x1.p-3_f16;
        }

    };

}

// Local variables:
// mode: c++
// end:
#endif
