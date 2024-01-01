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
#if !defined (__CFTAL_D_REAL_TRAITS_F32_H__)
#define __CFTAL_D_REAL_TRAITS_F32_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <cftal/d_real_traits.h>

namespace cftal {

    // fma available specialized for float
    template <>
    struct has_fma<float> {
#if defined (FP_FAST_FMAF) && (FP_FAST_FMAF > 0)
        static constexpr bool fma = true;
#else
        static constexpr bool fma = false;
#endif
    };

    // d_real_traits specialization for float
    template <>
    struct d_real_traits<float> : public has_fma<float> {
        // result of a comparison operator
        using cmp_result_type = bool;
        // corresponding integer type for ldexp, frexp
        using int_type = int32_t;

        static bool any_of_v(const cmp_result_type& b) {
            return b;
        }
        static float sel(const cmp_result_type& s,
                         const float& on_true,
                         const float& on_false) {
            return s ? on_true : on_false;
        }

        // veltkamp split of a float
        static
        void split(float a, float& hi, float& lo) {
            const uint32_t msk=
                const_u32<0xfffff000U>::v.u32();
            const float h = as<float>(as<uint32_t>(a) & msk);
            const float l = a - h;
            hi = h;
            lo = l;
        }

        // veltkamp split of a float
        static
        void veltkamp_plit(float a, float& hi, float& lo) {
            // 2^13 + 1
            constexpr const float split_val=8193.0f;
            // 2^115 = 2^{127-14+1}
            constexpr const float split_threshold= 4.15383749e+34f;
            // 2^-14
            constexpr const float split_scale_down = 1.0f/16384.0f;
            // 2^14
            constexpr const float split_scale_up = 16384.0f;
            cmp_result_type is_big(std::fabs(a) > split_threshold);
            float temp;
            if (__unlikely(any_of_v(is_big))) {
                a*=split_scale_down;
                temp = split_val*a;
                hi=temp-(temp-a);
                lo= a-hi;
                hi*= split_scale_up;
                lo*= split_scale_up;
            } else {
                temp=split_val *a;
                hi=temp-(temp-a);
                lo=a-hi;
            }
        }

        static
        constexpr
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
