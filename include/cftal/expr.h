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
#if !defined (__CFTAL_EXPR_H__)
#define __CFTAL_EXPR_H__ 1

#include <cftal/config.h>

namespace cftal {

    // expression traits define how we store _T operands in expr
    // objects, defaults to constant by value
    template <typename _T>
    struct expr_traits {
        using type = const _T;
    };

    // expression class consisting of an operation and a left
    // and a right operand
    template <class _OP, class _L, class _R>
    struct expr {
        typename expr_traits<_L>::type _l;
        typename expr_traits<_R>::type _r;
        constexpr expr(const _L& l, const _R& r) : _l(l), _r(r) {}
    };

    // expression class specialized an operation and a left
    // operand, i.e. for an unary operation
    template <class _OP, class _L>
    struct expr<_OP, _L, void> {
        typename expr_traits<_L>::type _l;
        constexpr expr(const _L& l) : _l(l) {}
    };

    // helper function for creation of expressions
    template <class _OP, class _L, class _R>
    constexpr expr<_OP, _L, _R>
    make_expr(const _L& l, const _R& r) {
        return expr<_OP, _L, _R>(l, r);
    }

    // helper function for creation of expressions
    template <class _OP, class _L>
    constexpr expr<_OP, _L, void>
    make_expr(const _L& l) {
        return expr<_OP, _L, void>(l);
    }

    // evaluation of an arbitrary type, returns the argument
    template <typename _T>
    inline
    const _T&
    eval(const _T& v) {
        return v;
    }

    // evaluation of expr<_OP, _L, _R> as
    // _OP::v(eval(e._l), eval(e._r)), i.e. as operation on the
    // evaluated left and right branches of the expression tree
    template <class _OP, class _L, class _R>
    inline
    typename _OP::full_type
    eval(const expr<_OP, _L, _R>& e) {
        return _OP::v(eval(e._l), eval(e._r));
    }

    // evaluation of expr<_OP, _L, void> as
    // _OP::v(eval(e._l)), i.e. as operation on the
    // evaluated left branch of the expression tree
    template <class _OP, class _L>
    inline
    typename _OP::full_type
    eval(const expr<_OP, _L, void>& e) {
        return _OP::v(eval(e._l));
    }

}

// Local variables:
// mode: c++
// end:
#endif
