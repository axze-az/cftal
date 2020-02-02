//
// Copyright Axel Zeuner 2010-2020. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined(__CFTAL_TEST_CHECK_EXP_MX2_H__)
#define __CFTAL_TEST_CHECK_EXP_MX2_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/math/func_constants.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {

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

            static
            _T
            __exp_mx2(_T a);

            static
            _T
            s(const _T& a) {
                // return std::exp(-a*a);
                return __exp_mx2(a);
            }

            static
            const char* fname() { return "exp_mx2"; }
        };

    }
}

template <typename _T>
_T
cftal::test::check_exp_mx2<_T>::__exp_mx2(_T x)
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
