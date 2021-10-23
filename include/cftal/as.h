//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_AS_H__)
#define __CFTAL_AS_H__ 1

#include <cftal/config.h>

namespace cftal {

    // as: reinterpret cast to _D from _S, name similiar to opencl
    // forwarder function to impl::cast_bits<_D, _S>::v
    template <typename _D, typename _S>
    _D as(const _S& s);

    // bit_cast: reinterpret cast to _D from _S, name similiar 
    // std::bit_cast
    // forwarder function to impl::cast_bits<_D, _S>::v
    template <typename _D, typename _S>
    _D bit_cast(const _S& s);
    
    namespace impl {

        // generic working class for cftal::as
        template <typename _D, typename _S>
        struct cast_bits {
#if 1
            static _D v(const _S& s) {
                const _D& ds=reinterpret_cast<const _D&>(s);
                return ds;
            }
#else
            union ds {
                _D _d;
                _S _s;
                ds(const _S& s) : _s{s} {}
            };

            static _D v(const _S& s) {
                ds c{s};
                return c._d;
            }
#endif            
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
_D
cftal::as(const _S& s)
{
    return impl::cast_bits<_D, _S>::v(s);
}

template <typename _D, typename _S>
inline
_D
cftal::bit_cast(const _S& s)
{
    return impl::cast_bits<_D, _S>::v(s);
}


// Local variables:
// mode: c++
// end:
#endif
