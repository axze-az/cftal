//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined(__CFTAL_TEST_ENV_VAR_H__)
#define __CFTAL_TEST_ENV_VAR_H__ 1

#include <cftal/config.h>

namespace cftal {

    namespace test {

        // environment variable CFTAL_DEV="cf" | "fc" | "c" | "f"
        // c -- use use cache
        // f -- faster tests

        bool env_use_cache();

        bool env_faster_tests();

    }
}


// Local variables:
// mode: c++
// end:
#endif

