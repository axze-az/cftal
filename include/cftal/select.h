//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_SELECT_H__)
#define __CFTAL_SELECT_H__ 1

#include <cftal/config.h>

namespace cftal {

    template <class _M, class _T>
    _T select(const _M& m,
              const _T& on_true, const _T& on_false);

    template <class _M, class _T>
    _T if_else(const _M& m,
               const _T& on_true, const _T& on_false);
}

template <typename _M, typename _T>
inline
_T
cftal::select(const _M& m, const _T& on_true, const _T& on_false)
{
    return m ? on_true : on_false;
}

template <typename _M, typename _T>
inline
_T
cftal::if_else(const _M& m, const _T& on_true, const _T& on_false)
{
    return select(m, on_true, on_false);
}

// Local variables:
// mode: c++
// end:
#endif
