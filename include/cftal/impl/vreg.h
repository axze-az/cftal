//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
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

template <class _X>
inline
constexpr
cftal::impl::vreg<_X>::vreg(_X x) : _v(x)
{
}

template <class _X>
inline
constexpr
_X cftal::impl::vreg<_X>::operator()() const
{
    return _v;
}

template <class _X>
inline
_X& cftal::impl::vreg<_X>::operator()()
{
    return _v;
}

// Local variables:
// mode: c++
// end:
#endif
