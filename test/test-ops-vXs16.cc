//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/of_ops.h"

int main()
{
    std::cout << "testing vXs16" << std::endl;
    bool rc=cftal::test::of_ops_up_to<int16_t, 32>::v();
    if (rc==false)
        std::cerr << "int16_t test failed" << std::endl;
    return rc==true ? 0 : 1;
}

