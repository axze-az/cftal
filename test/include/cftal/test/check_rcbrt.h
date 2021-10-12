//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined(__CFTAL_TEST_CHECK_RCBRT_H__)
#define __CFTAL_TEST_CHECK_RCBRT_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct check_rcbrt {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return rcbrt(a);
                // return rootn(a, vec<int32_t, _N>(3));
            }

            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_ext::rcbrt, &i);
                return std::make_tuple(v, i.first, i.second);
                // return call_mpfr::func(a, mpfr_cbrt);
            }
            static
            _T
            s(const _T& a) {
                return _T(1)/std::cbrt(a);
            }
            static
            const char* fname() { return "rcbrt"; }
        };

    }
}

// local variables:
// mode: c++
// end:

#endif
