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
#if !defined (__CFTAL_AS_H__)
#define __CFTAL_AS_H__ 1

#include <cftal/config.h>
#if __has_include(<bit>)
#include <bit>
#if __cpp_lib_bit_cast > 0
#define USE_BIT_CAST 1
#endif
#endif

namespace cftal {

    // as: reinterpret cast to _D from _S, name similiar to opencl
    // forwarder function to impl::cast_bits<_D, _S>::v
    template <typename _D, typename _S>
#if USE_BIT_CAST > 0
    constexpr
#endif
    _D as(const _S& s);

    // bit_cast: reinterpret cast to _D from _S, name similiar
    // std::bit_cast
    // forwarder function to impl::cast_bits<_D, _S>::v
    template <typename _D, typename _S>
#if USE_BIT_CAST > 0
    constexpr
#endif
    _D bit_cast(const _S& s);

    namespace impl {

        // generic working class for cftal::as
        template <typename _D, typename _S>
        struct cast_bits {
            static
#if USE_BIT_CAST > 0
            constexpr
#endif
            _D v(const _S& s) {
#if USE_BIT_CAST>0
                return std::bit_cast<_D>(s);
#else
                static_assert(sizeof(_D)==sizeof(_S),
                              "size differences in cast_bits::v");
                const _D& ds=reinterpret_cast<const _D&>(s);
                return ds;
#endif
            }
        };

        // specialization for cftal::as<_T, _T>
        template <typename _SD>
        struct cast_bits<_SD, _SD> {
            static
            constexpr
            const _SD& v(const _SD& r) {
                return r;
            }
        };
    }

}

template <typename _D, typename _S>
inline
#if USE_BIT_CAST > 0
constexpr
#endif
_D
cftal::as(const _S& s)
{
    return impl::cast_bits<_D, _S>::v(s);
}

template <typename _D, typename _S>
inline
#if USE_BIT_CAST > 0
constexpr
#endif
_D
cftal::bit_cast(const _S& s)
{
    return impl::cast_bits<_D, _S>::v(s);
}

#if defined (USE_BIT_CAST)
#undef USE_BIT_CAST
#endif

// Local variables:
// mode: c++
// end:
#endif
