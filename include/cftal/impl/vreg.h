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
#if !defined (__CFTAL_IMPL_VREG_H__)
#define __CFTAL_IMPL_VREG_H__ 1

#include <cftal/config.h>

namespace cftal {

    namespace impl {

        // wrapper around a vector register type
        template <class _R>
        class vreg {
            _R _v;
        public:
            using vector_type = _R;
            using element_type = void;
            vreg() = default;
            vreg(const vreg& r) = default;
            vreg(vreg&& r) = default;
            vreg& operator=(const vreg& r) = default;
            vreg& operator=(vreg&& r) = default;
            constexpr vreg(_R x);
            constexpr _R operator()() const;
            _R& operator()();
        };
    }
}

template <class _R>
inline
constexpr
cftal::impl::vreg<_R>::vreg(_R x) : _v(x)
{
}

template <class _R>
inline
constexpr
_R cftal::impl::vreg<_R>::operator()() const
{
    return _v;
}

template <class _R>
inline
_R& cftal::impl::vreg<_R>::operator()()
{
    return _v;
}

// Local variables:
// mode: c++
// end:
#endif
