//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <cftal/test/intops.h>

int main(int argc, char** argv)
{
    bool rc= cftal::test::check_div_s32();
    return rc==true ? 0 : 1;
}
