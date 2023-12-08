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
#if !defined (__CFTAL_TEST_FUNC_DOMAIN_COMMON_H__)
#define __CFTAL_TEST_FUNC_DOMAIN_COMMON_H__ 1

#include <cftal/config.h>
#include <cftal/test/func_domain.h>
#include <limits>

namespace cftal {
    namespace test {

        template <typename _T>
        struct domain_full_x_axis {
            static
            const func_domain<_T> domains[];

            constexpr static
            const int shifts[]={0};
        };

        template <typename _T>
        const func_domain<_T> domain_full_x_axis<_T>::domains[]={
            std::make_pair(-std::numeric_limits<_T>::max(),
                            std::numeric_limits<_T>::max())
        };

        template <typename _T>
        struct domain_positive_x_axis {
            static
            const func_domain<_T> domains[];

            constexpr
            static
            const int shifts[]={0};
        };

        template <typename _T>
        const func_domain<_T> domain_positive_x_axis<_T>::domains[]={
            std::make_pair(_T(0),
                            std::numeric_limits<_T>::max())
        };

        template <typename _T>
        struct domain_minus_1_to_1 {
            constexpr static
            const func_domain<_T> domains[]={
                std::make_pair(-_T(1), _T(1))
            };
            constexpr static
            const int shifts[]={0};
        };

        template <typename _T>
        struct domain_sin_cos_tan {};

        template <>
        struct domain_sin_cos_tan<double> : public domain_full_x_axis<double> {
            constexpr static
            const func_domain<double> domains2[]={
                std::make_pair(-0x1p45, 0x1p45)
            };
        };

        template <>
        struct domain_sin_cos_tan<float> : public domain_full_x_axis<float> {
            constexpr static
            const func_domain<float> domains2[]={
                std::make_pair(-0x1p18f, 0x1p18f)
            };
        };


        template <typename _T>
        struct domain_sinh_cosh {};

        template <>
        struct domain_sinh_cosh<double> {
            constexpr static
            const func_domain<double> domains[]={
                std::make_pair(-710.5, 710.5)
            };
            constexpr static
            const int shifts[]={0};
        };

        template <>
        struct domain_sinh_cosh<float> {
            constexpr static
            const func_domain<float> domains[]={
                std::make_pair(-90.0f, 90.0f)
            };
            constexpr static
            const int shifts[]={0};
        };

        template <>
        struct domain_sinh_cosh<f16_t> {
            static
            const func_domain<f16_t> domains[];

            constexpr static
            const int shifts[]={0};
        };

        const func_domain<f16_t> domain_sinh_cosh<f16_t>::domains[]={
            std::make_pair(-11.9_f16, 11.9_f16)
        };

        template <typename _T>
        struct domain_sinpi_cospi_tanpi {};

        template <>
        struct domain_sinpi_cospi_tanpi<double> {
            constexpr static
            const func_domain<double> domains[]={
                std::make_pair(-0x1.5p54, 0x1.5p54)
            };
            constexpr static
            const int shifts[]={0};
        };

        template <>
        struct domain_sinpi_cospi_tanpi<float> {
            constexpr static
            const func_domain<float> domains[]={
                std::make_pair(-0x1.5p25f, 0x1.5p25f)
            };
            constexpr static
            const int shifts[]={0};
        };

        template <typename _T>
        struct domain_logx1p {
            constexpr static
            const func_domain<_T> domains[]={
                std::make_pair(_T(-1.0), std::numeric_limits<_T>::max())
            };
            constexpr static
            const int shifts[]={
                0
            };
        };

    }
}


// Local variables:
// mode: c++
// end:
#endif // __CFTAL_TEST_FUNC_DOMAIN_H__
