//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_FENV_H__)
#define __CFTAL_FENV_H__ 1

#include <cftal/config.h>
#include <fenv.h>

namespace cftal {
    struct rounding_mode {
        enum type {
            nearest = 0, 
            downward = 1,
            upward = 2,
            towardzero = 3,
            current = 4
        };
    };
}

// Local variables:
// mode: c++
// end:
#endif
