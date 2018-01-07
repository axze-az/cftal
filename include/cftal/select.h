//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_SELECT_H__)
#define __CFTAL_SELECT_H__ 1

#include <cftal/config.h>

namespace cftal {

    // select: m ? on_true : on_false
    template <class _M, class _T>
    _T select(const _M& m,
              const _T& on_true, const _T& on_false);

    // if_else: m ? on_true : on_false
    template <class _M, class _T>
    _T if_else(const _M& m,
               const _T& on_true, const _T& on_false);

    // select_val_or_zero: m ? on_true : _T(0)
    template <class _M, class _T>
    _T select_val_or_zero(const _M& m,
                          const _T& on_true);

    // select_zero_or_val m ? _T(0) : on_false
    template <class _M, class _T>
    _T select_zero_or_val(const _M& m,
                          const _T& on_false);
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

template <typename _M, typename _T>
inline
_T
cftal::
select_val_or_zero(const _M& m, const _T& on_true)
{
    return select(m, on_true, _T(0));
}

template <typename _M, typename _T>
inline
_T
cftal::
select_zero_or_val(const _M& m, const _T& on_false)
{
    return select(m, _T(0), on_false);
}

// Local variables:
// mode: c++
// end:
#endif
