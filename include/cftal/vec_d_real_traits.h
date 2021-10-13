//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_VEC_D_REAL_TRAITS_H__)
#define __CFTAL_VEC_D_REAL_TRAITS_H__ 1

#include <cftal/config.h>
#include <cftal/vec_t_n.h>
#include <cftal/d_real.h>

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
        vec<double, _N>
        scale_div_threshold() {
            // -1022 + 53
            return vec<double, _N>(0x1.p-969);
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
        vec<float, _N>
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