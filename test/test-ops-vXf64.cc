//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/of_ops.h"

int main()
{
    bool rc=true;
    std::cout << "testing vXf64" << std::endl;
    rc=cftal::test::of_ops_up_to<double, 8>::v();
    if (rc==false)
        std::cerr << "double test failed" << std::endl;
    return rc==true ? 0 : 1;
}

