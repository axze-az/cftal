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
    return b==true;
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
    return b==true;
}

// Local variables:
// mode: c++
// end:
#endif
