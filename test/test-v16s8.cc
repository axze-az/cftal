//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <cftal/config.h>
#include <cftal/test/of_vec.h>
#include <cftal/test/of_vec_v16.h>

namespace cftal {
    namespace test {
        bool spec_v16s8();
    }
}

bool cftal::test::spec_v16s8()
{
    bool r=true;
    return r;
}

int main()
{
    bool rc(true);
    rc &= cftal::test::check_v16<int8_t>();
    rc &= cftal::test::spec_v16s8();
    return rc == true ? 0 : 1;
}