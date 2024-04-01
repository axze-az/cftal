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
#if !defined(__CFTAL_TEST_CHECK_SIN_H__)
#define __CFTAL_TEST_CHECK_SIN_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/vec_f16.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T, typename _I=int32_t>
        struct check_lgamma {
            template <std::size_t _N>
            static
            std::pair<vec<_I, _N>, vec<_T, _N> >
            v(const vec<_T, _N>& a) {
                vec<_I, _N> ir;
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
                return std::make_pair(_I(sgn), s);
            }

            static
            float
            __lgamma(const float& a, int32_t* sgn) {
                return ::lgammaf_r(a, sgn);
            }

            static
            double
            __lgamma(const double& a, int32_t* sgn) {
                return ::lgamma_r(a, sgn);
            }

            static
            f16_t
            __lgamma(const f16_t& a, int32_t* sgn) {
                auto af=static_cast<float>(a);
                return __lgamma(af, sgn);
            }

            static
            auto
            s(const _T& a) {
                int32_t sgn;
                _T r=__lgamma(a, &sgn);
                return std::make_pair(_I(sgn), r);
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
