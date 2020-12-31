//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined(__CFTAL_TEST_CHECK_POWI_H__)
#define __CFTAL_TEST_CHECK_POWI_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct check_powi {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<int32_t, _N>& b) {
                return pow(a, b);
            }

            static
            auto
            r(const _T& a, const int32_t& b) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, b, mpfr_pow_si, &i);
                return std::make_tuple(v, i.first, i.second);
            }

            static
            _T
            s(const _T& a, const int32_t& b) {
                return std::pow(a, b);
            }

            static
            const char* fname() { return "powi"; }
        };
    }
}

// local variables:
// mode: c++
// end:

#endif
