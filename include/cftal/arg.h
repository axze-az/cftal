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
#if !defined (__CFTAL_ARG_H__)
#define __CFTAL_ARG_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <cftal/type_traits.h>

namespace cftal {

    // description of an argument - all things greater than
    // a double are transferred by constant reference and by
    // value otherwise.
    template <typename _T>
    struct arg {
        // using type = const _T&;
        using type=
            select_t<(sizeof(_T) > sizeof(double)),
                     const _T&,
                     _T>;
    };

    // abbreviation for typename arg::type
    template <typename _T>
    using arg_t = typename arg<_T>::type;

    // specialization of arg<> for char
    template <>
    struct arg<char> { using type= char; };

    // specialization of arg<> for wchar_t
    template <>
    struct arg<wchar_t> { using type= wchar_t; };

    // specialization of arg<> for uint8_t/unsigned char
    template <>
    struct arg<uint8_t> { using type= uint8_t; };

    // specialization of arg<> for int8_t/signed char
    template <>
    struct arg<int8_t> { using type= int8_t; };

    // specialization of arg<> for uint16_t
    template <>
    struct arg<uint16_t> { using type= uint16_t; };

    // specialization of arg<> for int16_t
    template <>
    struct arg<int16_t> { using type= int16_t; };

    // specialization of arg<> for uint32_t
    template <>
    struct arg<uint32_t> { using type= uint32_t; };

    // specialization of arg<> for int32_t
    template <>
    struct arg<int32_t> { using type= int32_t; };

    // specialization of arg<> for uint64_t
    template <>
    struct arg<uint64_t> { using type= uint64_t; };

    // specialization of arg<> for int64_t
    template <>
    struct arg<int64_t> { using type= int64_t; };

    // specialization of arg<> for float
    template <>
    struct arg<float> { using type= float; };

    // specialization of arg<> for double
    template <>
    struct arg<double> { using type= double; };

}

// local variables:
// mode: c++
// end:
#endif
