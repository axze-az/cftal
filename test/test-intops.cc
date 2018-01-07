//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <cftal/test/intops.h>

bool all_tests()
{
    bool r(true);
    r &= cftal::test::check_xxx_of();
    r &= cftal::test::check_popcnt();
    r &= cftal::test::check_bitrev();
    return r;
}

int main(int argc, char** argv)
{
    return all_tests()==true ? 0 : 3;
}
