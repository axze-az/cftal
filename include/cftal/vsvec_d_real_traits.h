//
// Copyright (C) 2010-2025 Axel Zeuner
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
#if !defined (__CFTAL_SVVEC_D_REAL_TRAITS_H__)
#define __CFTAL_SVVEC_D_REAL_TRAITS_H__ 1

#include <cftal/config.h>
#include <cftal/vsvec_t_a.h>
#include <cftal/d_real.h>

namespace cftal {

    template <typename _A>
    struct d_real_traits<vsvec<double,_A> > : public has_fma<double> {
        using cmp_result_type = typename vsvec<double, _A>::mask_type;
        using _AI= typename
            std::allocator_traits<_A>::template rebind_alloc<int32_t>;
        using int_type = vsvec<int32_t, _AI>;

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
        vsvec<double, _A>
        sel (const cmp_result_type& s,
             const vsvec<double, _A>& on_true,
             const vsvec<double, _A>& on_false) {
            return select(s, on_true, on_false);
        }

        static
        void
        split(const vsvec<double, _A> & a,
              vsvec<double, _A>& h,
              vsvec<double, _A>& l) {
            const double msk=
                const_u64<0xf8000000U, 0xffffffffU>::v.f64();
            const vsvec<double, _A> th = a & msk;
            const vsvec<double, _A> tl = a - th;
            h = std::move(th);
            l = std::move(tl);
        }

        constexpr
        static
        double
        scale_div_threshold() {
            // -1022 + 53
            return 0x1.p-969;
        }

    };


    template <typename _A>
    struct d_real_traits<vsvec<float, _A> > : public has_fma<float> {
        using cmp_result_type = typename vsvec<float, _A>::mask_type;
        using _AI= typename
            std::allocator_traits<_A>::template rebind_alloc<int32_t>;
        using int_type = vsvec<int32_t, _AI>;

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
        vsvec<float, _A>
        sel(const cmp_result_type& s,
            const vsvec<float, _A>& on_true,
            const vsvec<float, _A>& on_false) {
            return select(s, on_true, on_false);
        }

        static
        void
        split(const vsvec<float, _A> & a,
              vsvec<float, _A>& h,
              vsvec<float, _A>& l) {
            const float msk=
                const_u32<0xfffff000U>::v.f32();
            const vsvec<float, _A> th = a & msk;
            const vsvec<float, _A> tl = a - th;
            h = std::move(th);
            l = std::move(tl);
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

#endif
