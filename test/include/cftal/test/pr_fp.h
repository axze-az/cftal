//
// Copyright (C) 2010-2026 Axel Zeuner
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
#if !defined (__CFTAL_TEST_PR_FP_H__)
#define __CFTAL_TEST_PR_FP_H__ 1

#include <cftal/config.h>
#include <iostream>
#include <cftal/f16_t.h>

namespace cftal {
    namespace test {

        template <typename _T>
        struct out_prec { };

        template <>
        struct out_prec<double> {
            constexpr static const int val= 22;
            constexpr static const int width = 27;
            constexpr static const char* suffix() { return ""; }
        };

        template <>
        struct out_prec<float> {
            constexpr static const int val= 13;
            constexpr static const int width= 18;
            constexpr static const char* suffix() { return "f"; }
        };

        template <>
        struct out_prec<f16_t> {
            constexpr static const int val= 8;
            constexpr static const int width= 13;
            constexpr static const char* suffix() { return "_f16"; }
        };


        template <typename _T>
        struct pr_fp {
            _T _v;
            pr_fp(const _T& t) : _v(t) {}
        };

        template <typename _T>
        std::ostream& operator<<(std::ostream& s, const pr_fp<_T>& v);
    }
}

template <typename _T>
std::ostream&
cftal::test::operator<<(std::ostream& s, const pr_fp<_T>& v)
{
    s << std::scientific
      << std::setprecision(out_prec<_T>::val)
      << std::showpos
      << std::setw(out_prec<_T>::width)
      << v._v
      << out_prec<_T>::suffix()
      << std::noshowpos;
      return s;
}

// local variables:
// mode: c++
// end:
#endif
