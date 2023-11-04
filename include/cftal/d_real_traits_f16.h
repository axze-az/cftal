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
#if !defined (__CFTAL_D_REAL_TRAITS_F16_H__)
#define __CFTAL_D_REAL_TRAITS_F16_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <cftal/d_real_traits.h>
#include <cftal/f16_t.h>

namespace cftal {

    // fma available specialized for f16_t aka half precision
    template <>
    struct has_fma<f16_t> {
#if defined (FP_FAST_FMAF16) && (FP_FAST_FMAF16 > 0)
        static constexpr bool fma = true;
#else
        static constexpr bool fma = false;
#endif
    };

    // d_real_traits specialization for f16_t aka half precision
    template <>
    struct d_real_traits<f16_t> : public has_fma<f16_t> {
        // result of a comparison operator
        using cmp_result_type = bool;
        // corresponding integer type for ldexp, frexp
        using int_type = int32_t;

        static bool any_of_v(const cmp_result_type& b) {
            return b;
        }
        static
        f16_t
        sel(const cmp_result_type& s,
            const f16_t& on_true,
            const f16_t& on_false) {
            return s ? on_true : on_false;
        }

        // veltkamp split of a float
        static
        void split(f16_t a, f16_t& hi, f16_t& lo) {
            const uint16_t msk=0xffc0;
            const uint16_t t=as<uint16_t>(a) & msk;
            const f16_t h = as<f16_t>(t);
            const f16_t l = a - h;
            hi = h;
            lo = l;
        }

        static
        // constexpr
        f16_t
        scale_div_threshold() {
            // -14 + 11
            return 0x1.p-3_f16;
        }

    };

}

// Local variables:
// mode: c++
// end:
#endif
