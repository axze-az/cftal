//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/env_var.h"
#include <cstdlib>
#include <string_view>

namespace {
    const char cftal_dev[]="CFTAL_DEV\0";
}

bool
cftal::test::env_use_cache()
{
    const char* p=std::getenv(cftal_dev);
    bool r=false;
    if (p != nullptr) {
        const std::string_view sv(p);
        if ((sv == "cf") || (sv == "fc") || (sv =="c"))
            r=true;
    }
    return r;
}

bool
cftal::test::env_faster_tests()
{
    const char* p=std::getenv(cftal_dev);
    bool r=false;
    if (p != nullptr) {
        const std::string_view sv(p);
        if ((sv == "cf") || (sv == "fc") || (sv =="f"))
            r=true;
    }
    return r;
}
