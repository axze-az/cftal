//
// Copyright (C) 2010-2022 Axel Zeuner
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
