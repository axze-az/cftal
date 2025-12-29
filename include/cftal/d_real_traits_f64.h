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
#if !defined (__CFTAL_D_REAL_TRAITS_F64_H__)
#define __CFTAL_D_REAL_TRAITS_F64_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <cftal/constants.h>
#include <cftal/as.h>
#include <cftal/d_real_traits.h>
#include <cmath>

namespace cftal {

    // fma available specialized for double
    template <>
    struct has_fma<double> {
#if defined (FP_FAST_FMA) && (FP_FAST_FMA > 0)
        static constexpr bool fma = true;
#else
        static constexpr bool fma = false;
#endif
    };

    // d_real_traits specialization for double
    template <>
    struct d_real_traits<double> : public has_fma<double> {
        // result of a comparison operator
        using cmp_result_type = bool;
        // corresponding integer type for ldexp, frexp
        using int_type = int32_t;

        static constexpr double eps() {
            // 2^-104
            return 4.93038065763132e-32;
        }

        // return true if any in b is true
        static bool any_of_v(const cmp_result_type& b) {
            return b;
        }
        // select an value
        static double sel(const cmp_result_type& s,
                          const double& on_true,
                          const double& on_false) {
            return s ? on_true : on_false;
        }

        static
        void split(double a, double& hi, double& lo) {
            const uint64_t msk=
                const_u64<0xf8000000U, 0xffffffffU>::v.u64();
            uint64_t ai=as<uint64_t>(a) & msk;
            double th = as<double>(ai);
            double tl = a - th;
            hi = th;
            lo = tl;
        }

        // veltkamp split of a double
        static
        void veltkamp_split(double a, double& hi, double& lo) {
            // 2^996 = 2^{1023-28+1}
            constexpr const double split_threshold=
                6.69692879491417e+299;
            // 2^27 + 1
            constexpr const double split_val =
                134217729.0;
            // 2^-28
            constexpr const double split_scale_down=
                3.7252902984619140625e-09;
            // 2^28
            constexpr const double split_scale_up =
                268435456.0;
            using std::fabs;
            cmp_result_type is_big(fabs(a) > split_threshold);
            volatile double temp;
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
        double
        scale_div_threshold() {
            // -1022 + 53
            return 0x1.p-969;
        }

    };

}

// Local variables:
// mode: c++
// end:
#endif
