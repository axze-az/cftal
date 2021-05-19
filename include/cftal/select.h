//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_SELECT_H__)
#define __CFTAL_SELECT_H__ 1

#include <cftal/config.h>

namespace cftal {

    // select: m ? on_true : on_false
    template <class _T>
    _T select(const bool& m,
              const _T& on_true, const _T& on_false);

    // if_else: m ? on_true : on_false
    template <class _T>
    _T if_else(const bool& m,
               const _T& on_true, const _T& on_false);

    // select_val_or_zero: m ? on_true : _T(0)
    template <class _T>
    _T select_val_or_zero(const bool& m,
                          const _T& on_true);

    // select_zero_or_val m ? _T(0) : on_false
    template <class _T>
    _T select_zero_or_val(const bool& m,
                          const _T& on_false);

    // any_of
    bool any_of(bool b);
    // none_of
    bool none_of(bool b);
    // all_of
    bool all_of(bool b);

}

template <typename _T>
inline
_T
cftal::select(const bool& m, const _T& on_true, const _T& on_false)
{
    return m ? on_true : on_false;
}

template <typename _T>
inline
_T
cftal::if_else(const bool& m, const _T& on_true, const _T& on_false)
{
    return select(m, on_true, on_false);
}

template <typename _T>
inline
_T
cftal::
select_val_or_zero(const bool& m, const _T& on_true)
{
    return select(m, on_true, _T(0));
}

template <typename _T>
inline
_T
cftal::
select_zero_or_val(const bool& m, const _T& on_false)
{
    return select(m, _T(0), on_false);
}

inline
bool
cftal::any_of(bool b)
{
    return b;
}

inline
bool
cftal::none_of(bool b)
{
    return b==false;
}

inline
bool
cftal::all_of(bool b)
{
    return b;
}

// Local variables:
// mode: c++
// end:
#endif
