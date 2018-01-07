//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/rcp_div.h"

int main()
{
    bool rc= cftal::test::rcp_div_u32();
    return rc == true ? 0 : 1;
}
