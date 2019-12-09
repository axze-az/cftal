//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined(__CFTAL_TEST_CHECK_ROOTN_H__)
#define __CFTAL_TEST_CHECK_ROOTN_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct check_rootn {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<int32_t, _N>& ib) {
                return rootn(a, ib);
            }

            static
            auto
            r(const _T& a, const int32_t& b) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, b, mpfr_ext::rootn, &i);
                return std::make_tuple(v, i.first, i.second);
            }

            static
            _T
            s(const _T& a, const int32_t& b) {
                double db=1.0/double(b);
                _T tb=_T(db);
                return std::pow(a, tb);
            }

            static
            const char* fname() { return "rootn"; }
        };
    }
}

// local variables:
// mode: c++
// end:

#endif
