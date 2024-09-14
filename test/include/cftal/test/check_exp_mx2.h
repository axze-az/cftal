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
#if !defined(__CFTAL_TEST_CHECK_EXP_MX2_H__)
#define __CFTAL_TEST_CHECK_EXP_MX2_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/math/func_constants.h>
#include <cftal/math/func_constants_bf16.h>
#include <cftal/math/func_constants_f16.h>
#include <cftal/math/func_constants_f32.h>
#include <cftal/math/func_constants_f64.h>
#include <cftal/test/call_mpfr.h>
#include <cftal/test/func_domain_common.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct domain_exp_mx2 {};

        template <>
        struct domain_exp_mx2<double> {
            constexpr static
            const func_domain<double> domains[]={
                std::make_pair(0.0, 27.3)
            };
            constexpr static
            const int shifts[]= {
                0
            };
        };

        template <>
        struct domain_exp_mx2<float> {
            constexpr static
            const func_domain<float> domains[]={
                std::make_pair(0.0f, 10.2f)
            };
            constexpr static
            const int shifts[]={
                0
            };
        };

        template <>
        struct domain_exp_mx2<f16_t> {
            constexpr static
            const func_domain<f16_t> domains[]={
                std::make_pair(0.0_f16, 3.5_f16)
            };
            constexpr static
            const int shifts[]={
                0
            };
        };

        template <>
        struct domain_exp_mx2<bf16_t> {
            constexpr static
            const func_domain<bf16_t> domains[]={
                std::make_pair(0.0_bf16, 10.2_bf16)
            };
            constexpr static
            const int shifts[]={
                0
            };
        };

        template <typename _T>
        struct check_exp_mx2 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return exp_mx2(a);
            }

            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_ext::exp_mx2, &i);
                return std::make_tuple(v, i.first, i.second);
            }

            template <typename _F>
            static
            _F
            __exp_mx2(_F a);

            static
            f16_t
            __exp_mx2(f16_t a) {
                auto af=static_cast<float>(a);
                using std::exp;
                float rf=exp(-af*af);
                return f16_t(rf);
            }

            static
            bf16_t
            __exp_mx2(bf16_t a) {
                auto af=static_cast<float>(a);
                using std::exp;
                float rf=exp(-af*af);
                return bf16_t(rf);
            }

            static
            _T
            s(const _T& a) {
                // return std::exp(-a*a);
                return __exp_mx2(a);
            }

            static
            const char* fname() { return "exp_mx2"; }
        };

        template <typename _U>
        struct scale {
        };

        template <>
        struct scale<double> {
            static constexpr double up() { return 0x1p512; }
            static constexpr double down() { return 0x1p-512; }
        };

        template <>
        struct scale<float> {
            static constexpr float up() { return 0x1p64f; }
            static constexpr float down() { return 0x1p-64f; }
        };

        template <>
        struct scale<f16_t> {
            static constexpr f16_t up() { return 0x1p24_f16; }
            static constexpr f16_t down() { return 0x1p-24_f16; }
        };

    }
}

template <typename _F>
template <typename _T>
_T
cftal::test::check_exp_mx2<_F>::__exp_mx2(_T x)
{
    using std::isnan;
    _T y;
    using fc=math::func_constants<_T>;
    if (isnan(x)) {
        y=x;
    } else {
        using std::abs;
        _T ax=abs(x);
        if (ax >= -fc::exp_lo_zero()) {
            y = _T(0);
        } else if (ax < 0x1p-8) {
            _T x2=x*x;
            // %e^(-x*x) ~ 1 - x^2 + x^4/2 - x^6/6
            y = _T(1) - x2  + x2* ( x2 * (0.5 - _T(1)/_T(6) * x2));
        } else {
            using std::exp;
            using d_ops=d_real_ops<_T, d_real_traits<_T>::fma>;
            _T x2h, x2l;
            d_ops::sqr12(x2h, x2l, x);
            y = exp(-x2h);
            y *= scale<_T>::up();
            _T t= y * x2l;
            y -= t;
            y *= scale<_T>::down();
        }
    }
    return y;
}


// local variables:
// mode: c++
// end:

#endif
