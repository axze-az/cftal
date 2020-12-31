//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined(__CFTAL_TEST_CHECK_ROOT12_H__)
#define __CFTAL_TEST_CHECK_ROOT12_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {
        template <typename _T>
        struct check_root12 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return root12(a);
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_ext::root12, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                // return std::cbrt(std::sqrt(std::sqrt(a)));
                return std::sqrt(std::sqrt(std::cbrt(a)));
                // return std::pow(a, 1.0/12.0);
            }
            static
            const char* fname() {
                return "root12";
            }
        };

    }
}
#endif
