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
#if !defined (__CFTAL_MATH_FACTORIAL_H__)
#define __CFTAL_MATH_FACTORIAL_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/f16_t.h>

namespace cftal {
    namespace math {

        template <typename _T>
        struct rcp_factorial {
            static
            _T v(uint32_t n);
        };

        template <>
        struct rcp_factorial<double> {
            constexpr static const uint32_t MAX_N=178;
            static const double
            _recip_factorial_f64[179];
            static
            double v(uint32_t n);
        };

        template <>
        struct rcp_factorial<float> {
            constexpr static const uint32_t MAX_N=39;
            static const float
            _recip_factorial_f32[40];
            static
            float v(uint32_t n);
        };

        template <>
        struct rcp_factorial<f16_t> {
            constexpr static const uint32_t MAX_N=11;
            static const f16_t
            _recip_factorial_f16[12];
            static
            f16_t v(uint32_t n);
        };

        template <typename _T>
        struct factorial {
            static
            _T v(uint32_t n);
        };

        template <>
        struct factorial<double> {
            constexpr static const uint32_t MAX_N=171;
            static const double
            _factorial_f64[172];
            static
            double v(uint32_t n);
        };

        template <>
        struct factorial<float> {
            constexpr static const uint32_t MAX_N=35;
            static const float
            _factorial_f32[36];
            static
            float v(uint32_t n);
        };

        template <>
        struct factorial<f16_t> {
            constexpr static const uint32_t MAX_N=9;
            static const f16_t
            _factorial_f16[10];
            static
            f16_t v(uint32_t n);
        };

    }
}

inline
double
cftal::math::rcp_factorial<double>::v(uint32_t n)
{
    uint32_t i=std::min(MAX_N, n);
    return _recip_factorial_f64[i];
}

inline
float
cftal::math::rcp_factorial<float>::v(uint32_t n)
{
    uint32_t i=std::min(MAX_N, n);
    return _recip_factorial_f32[i];
}

inline
cftal::f16_t
cftal::math::rcp_factorial<cftal::f16_t>::v(uint32_t n)
{
    uint32_t i=std::min(MAX_N, n);
    return _recip_factorial_f16[i];
}

inline
double
cftal::math::factorial<double>::v(uint32_t n)
{
    uint32_t i=std::min(MAX_N, n);
    return _factorial_f64[i];
}

inline
float cftal::math::factorial<float>::v(uint32_t n)
{
    uint32_t i=std::min(MAX_N, n);
    return _factorial_f32[i];
}

inline
cftal::f16_t
cftal::math::factorial<cftal::f16_t>::v(uint32_t n)
{
    uint32_t i=std::min(MAX_N, n);
    return _factorial_f16[i];
}

#endif // __CFTAL_MATH_FACTORIAL_H__
