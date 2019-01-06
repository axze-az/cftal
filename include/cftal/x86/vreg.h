//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_X86_VREG_H__)
#define __CFTAL_X86_VREG_H__ 1

#include <cftal/config.h>
#include <cftal/impl/vreg.h>

namespace cftal {

    namespace x86 {

        template <typename _T>
        struct arg { using type = _T; };
        using ::cftal::impl::vreg;
    }
}

// Local variables:
// mode: c++
// end:
#endif
