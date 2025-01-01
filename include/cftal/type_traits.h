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
#if !defined (__CFTAL_TYPE_TRAITS_H__)
#define __CFTAL_TYPE_TRAITS_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <type_traits>

namespace cftal {

    // is_integral similiar to std::is_integral but we want
    // to add specializations
    template <typename _T>
    struct is_integral : public std::is_integral<_T> {};

    template< class T >
    inline constexpr bool
    is_integral_v = is_integral<T>::value;

    // is_floating_point similiar to std::is_floating_point but we
    // want to add specializations
    template <typename _T>
    struct is_floating_point : public std::is_floating_point<_T> {};

    template< class T >
    inline constexpr bool
    is_floating_point_v = is_floating_point<T>::value;

    // is_signed similiar to std::is_signed but we want
    // to add specializations
    template <typename _T>
    struct is_signed : public std::is_signed<_T> {};

    template< class T >
    inline constexpr bool
    is_signed_v = is_signed<T>::value;

    // is_unsigned similiar to std::is_unsigned but we want
    // to add specializations
    template <typename _T>
    struct is_unsigned : public std::is_unsigned<_T> {};

    template< class T >
    inline constexpr bool
    is_unsigned_v = is_unsigned<T>::value;

    // make_signed similiar to std::make_signed but we want
    // to add specializations
    template <typename _T>
    struct make_signed : public std::make_signed<_T> {};

    template< class T >
    using make_signed_t = typename make_signed<T>::type;

    // make_unsigned similiar to std::make_unsigned but we want
    // to add specializations
    template <typename _T>
    struct make_unsigned : public std::make_unsigned<_T> {};

    template< class T >
    using make_unsigned_t = typename make_unsigned<T>::type;

    // same as std::conditional_t
    template <bool _B, typename _TRUE, typename _FALSE>
    using select_t =
        typename std::conditional<_B, _TRUE, _FALSE>::type;

    // is the pointer aligned to _A bytes? _A must be
    // a power of 2
    template <size_t _A>
    bool
    is_aligned_to(const void* p);

}

template <cftal::size_t _A>
inline
bool
cftal::is_aligned_to(const void* p)
{
    static_assert((_A & (_A-1))==0, "_A must be a power of 2");
    return (intptr_t(p) & (_A-1))==0;
}

#endif
