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
#if !defined (__CFTAL_EXPR_H__)
#define __CFTAL_EXPR_H__ 1

#include <cftal/config.h>

namespace cftal {

    template <typename _T>
    struct expr_traits {
        using type = const _T;
    };

    template <class _OP, class _L, class _R>
    struct expr {
        typename expr_traits<_L>::type _l;
        typename expr_traits<_R>::type _r;
        constexpr expr(const _L& l, const _R& r) : _l(l), _r(r) {}
    };

    template <class _OP, class _L>
    struct expr<_OP, _L, void> {
        typename expr_traits<_L>::type _l;
        constexpr expr(const _L& l) : _l(l) {}
    };

    template <typename _T>
    inline
    const _T&
    eval(const _T& v) {
        return v;
    }

    template <class _OP, class _L, class _R>
    inline
    typename _OP::full_type
    eval(const expr<_OP, _L, _R>& e) {
        return _OP::v(eval(e._l), eval(e._r));
    }

    template <class _OP, class _L>
    inline
    typename _OP::full_type
    eval(const expr<_OP, _L, void>& e) {
        return _OP::v(eval(e._l));
    }

    // namespace containing the operations for the operators
    namespace op {
        // template class for the different operations
        // these operation class must export a static member function v
        // returning and taking the right arguments.
        // neg: (unary minus) static _T v(const _T&)
        // common comparison operations

        template <typename _T>
        struct lt {};

        template <typename _T>
        struct le {};

        template <typename _T>
        struct eq {};

        template <typename _T>
        struct ne {};

        template <typename _T>
        struct ge {};

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
