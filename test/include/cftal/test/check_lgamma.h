//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined(__CFTAL_TEST_CHECK_SIN_H__)
#define __CFTAL_TEST_CHECK_SIN_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct check_lgamma {
            template <std::size_t _N>
            static
            std::pair<vec<int32_t, _N>, vec<_T, _N> >
            v(const vec<_T, _N>& a) {
                vec<int32_t, _N> ir;
                vec<_T, _N> fr=lgamma(a, &ir);
                return std::make_pair(ir, fr);
            }

            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                int32_t sgn;
                _T v=call_mpfr::func(&sgn, a, mpfr_lgamma, &i);
                auto s=std::make_tuple(v, i.first, i.second);
                if (a == -std::numeric_limits<_T>::infinity())
                    sgn=1;
                return std::make_pair(sgn, s);
            }

            static
            auto
            s(const _T& a) {
                int32_t sgn;
                _T r=::lgamma_r(a, &sgn);
                return std::make_pair(sgn, r);
            }

            static
            const char* fname() { return "lgamma"; }
        };

    }
}

// local variables:
// mode: c++
// end:
#endif
