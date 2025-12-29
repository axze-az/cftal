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
#if !defined (__CFTAL_CHECK_VSVEC_FUNCS_H__)
#define __CFTAL_CHECK_VSVEC_FUNCS_H__ 1

#include <cftal/config.h>
#include <cftal/vsvec.h>
#include <cftal/math/vsvec_func_traits.h>
#include <cftal/math/elem_func_core_f32.h>
#include <cftal/math/elem_func_core_f64.h>
#include <cftal/math/elem_func.h>

namespace cftal {
    namespace test {

        template <typename _T, typename _A=aligned_allocator<_T, 64> >
        struct vsvec_test_base {
            using vsvec_t = vsvec<_T, _A>;
            using _AI= typename
                std::allocator_traits<_A>::template rebind_alloc<int32_t>;
            using traits_t=cftal::math::func_traits<vsvec<_T, _A>,
                                                    vsvec<int32_t, _AI> >;
            using func_t=cftal::math::elem_func<_T, traits_t>;
        };

        template <typename _T, typename _A=aligned_allocator<_T, 64> >
        struct vsvec_rsqrt : public vsvec_test_base<_T, _A> {
            using base_t=vsvec_test_base<_T, _A>;
            static
            vsvec<_T, _A>
            ref(const vsvec<_T, _A>& x) {
                return rsqrt(x);
            }

            static
            vsvec<_T, _A>
            v(const vsvec<_T, _A>& x) {
                return base_t::func_t::rsqrt(x);
            }

            static
            const char* fname() {
                return "rsqrt";
            }
        };

        extern template struct
        vsvec_rsqrt<float, aligned_allocator<float, 64> >;

        extern template struct
        vsvec_rsqrt<double, aligned_allocator<double, 64> >;


        template <typename _T, typename _A=aligned_allocator<_T, 64> >
        struct vsvec_exp : public vsvec_test_base<_T, _A> {
            using base_t=vsvec_test_base<_T, _A>;
            static
            vsvec<_T, _A>
            ref(const vsvec<_T, _A>& x) {
                return exp(x);
            }

            static
            vsvec<_T, _A>
            v(const vsvec<_T, _A>& x) {
                return base_t::func_t::exp(x);
            }

            static
            const char* fname() {
                return "exp";
            }
        };

        extern template struct
        vsvec_exp<float, aligned_allocator<float, 64> >;

        extern template struct
        vsvec_exp<double, aligned_allocator<double, 64> >;

        template <typename _T, typename _A=aligned_allocator<_T, 64> >
        struct vsvec_log : public vsvec_test_base<_T, _A> {
            using base_t=vsvec_test_base<_T, _A>;
            static
            vsvec<_T, _A>
            ref(const vsvec<_T, _A>& x) {
                return log(x);
            }

            static
            vsvec<_T, _A>
            v(const vsvec<_T, _A>& x) {
                return base_t::func_t::log(x);
            }

            static
            const char* fname() {
                return "log";
            }
        };
        extern template struct
        vsvec_log<float, aligned_allocator<float, 64> >;

        extern template struct
        vsvec_log<double, aligned_allocator<double, 64> >;

    }
}
#endif
