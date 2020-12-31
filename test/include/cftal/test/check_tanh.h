//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined(__CFTAL_TEST_CHECK_TANH_H__)
#define __CFTAL_TEST_CHECK_TANH_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct check_tanh {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return tanh(a);
            }
            static
            std::tuple<_T, _T, _T>
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_tanh, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::tanh(a);
            }
            static
            const char* fname() { return "tanh"; }
        };

    }
}

// local variables:
// mode: c++
// end:

#endif
