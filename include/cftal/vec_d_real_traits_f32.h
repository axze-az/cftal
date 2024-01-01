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
#if !defined (__CFTAL_VEC_D_REAL_TRAITS_F32_H__)
#define __CFTAL_VEC_D_REAL_TRAITS_F32_H__ 1

#include <cftal/config.h>
#include <cftal/vec_t_n.h>
#include <cftal/d_real.h>
#include <cftal/d_real_traits_f32.h>

namespace cftal {

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

}

// Local variables:
// mode: c++
// end:
#endif
