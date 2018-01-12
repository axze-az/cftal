//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined(__CFTAL_TEST_CHECK_HYPOT_H__)
#define __CFTAL_TEST_CHECK_HYPOT_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct check_hypot {

            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N> b) {
                return hypot(a, b);
            }

            static
            auto
            r(const _T& a, const _T& b) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, b, mpfr_hypot, &i);
                return std::make_tuple(v, i.first, i.second);
            }

            static
            _T
            s(const _T& a, const _T& b) {
                return std::hypot(a, b);
            }

            static
            const char* fname() { return "hypot"; }
        };
    }
}

// local variables:
// mode: c++
// end:
#endif