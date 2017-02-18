//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <cftal/config.h>
#include <cftal/test/of_vec.h>
#include <cftal/test/of_vec_v4.h>

int main()
{
    bool rc(true);
    rc &= cftal::test::check_v4<double>();
    // rc &= cftal::test::check_v4<int32_t>();
    // rc &= cftal::test::check_v4<uint32_t>();
    return rc == true ? 0 : 1;
}
