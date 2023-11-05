//
// Copyright (C) 2010-2023 Axel Zeuner
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
#if !defined (__CFTAL_CVT_H__)
#define __CFTAL_VEC_CVT_H__ 1

#include <cftal/config.h>

namespace cftal {

    template <class _D, class _S>
    _D cvt(const _S& s);

    template <class _D, class _S>
    _D cvt_rz(const _S& s);

    namespace impl {
        // convert according to current rounding mode
        // to _D from _S
        template <typename _D, typename _S>
        struct cvt {
            static
            _D v(const _S& s);
        };

        // convert with truncation (i.e. round to zero)
        // to _D from _S
        template <typename _D, typename _S>
        struct cvt_rz {
            static
            _D v(const _S& s);
        };
    }
}

template <class _D, class _S>
inline
_D cftal::cvt(const _S& s)
{
    return impl::cvt<_D, _S>::v(s);
}

template <class _D, class _S>
inline
_D cftal::cvt_rz(const _S& s)
{
    return impl::cvt_rz<_D, _S>::v(s);
}

// Local variables:
// mode: c++
// end:
#endif
