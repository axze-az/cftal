//
// Copyright (C) 2010-2025 Axel Zeuner
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
#if !defined (__CFTAL_OP_H__)
#define __CFTAL_OP_H__ 1

#include <cftal/config.h>

namespace cftal {

    // namespace op containing operation classes for operators returning
    // expression of operator classes and left and right operands
    // the default classes defines only the structure of the template
    // with one class/typename arguments
    namespace op {
        // template classes for the different operations
        // these operation classes must export a static member function v
        // returning and taking the right arguments, the return type of v
        // must be exported as full_type
        // neg: (unary minus) static _T v(const _T&); using full_type=_T;
        // these classes or only defined here to allow later specialization
        // for different _T

        // <
        template <typename _T>
        struct lt {};
        // <=
        template <typename _T>
        struct le {};
        // ==
        template <typename _T>
        struct eq {};
        // !=
        template <typename _T>
        struct ne {};
        // >=
        template <typename _T>
        struct ge {};
        // >
        template <typename _T>
        struct gt {};

        // arithmetic operations
        // +a
        template <typename _T>
        struct plus {};
        // -a
        template <typename _T>
        struct neg {};
        // a + b
        template <typename _T>
        struct add {};
        // a - b
        template <typename _T>
        struct sub {};
        // a * b
        template <typename _T>
        struct mul {};
        // a / b
        template <typename _T>
        struct div {};
        // a % b
        template <typename _T>
        struct mod {};

        // a*b + c
        template <typename _T>
        struct fma {};
        // a*b -c
        template <typename _T>
        struct fms {};
        // -a*b +c = (c-a*b)
        template <typename _T>
        struct fnma {};

        // bitwise logical operations
        template <typename _T>
        struct bit_or {};

        template <typename _T>
        struct bit_and {};

        template <typename _T>
        struct bit_xor {};

        template <typename _T>
        struct bit_not  {};

        // scalar shift left operator
        template <typename _T>
        struct shl {};
        // scalar shift right operator
        template <typename _T>
        struct shr { };
        // vector shift left operator
        template <typename _T>
        struct vshl {};
        // vector shift right operator
        template <typename _T>
        struct vshr {};

        // logical operations
        template <typename _T>
        struct log_or {};

        template <typename _T>
        struct log_and {};

        template <typename _T>
        struct log_not  {};

    }
}

// Local variables:
// mode: c++
// end:
#endif
