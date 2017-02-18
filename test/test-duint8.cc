//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/dint8.h"

int main()
{
    std::cout << "duint<uint8_t> unsigned check" << std::endl;
    cftal::test::check_duint_ops<uint16_t, cftal::duint<uint8_t> >();
    return 0;
}
