//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_EXPR_H__)
#define __CFTAL_EXPR_H__ 1

#include <cftal/config.h>

namespace cftal {

    template <typename _T>
    struct expr_traits {
        using type = const _T&;
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

}

// Local variables:
// mode: c++
// end:
#endif
