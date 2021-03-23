//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <cftal/config.h>
#include <cftal/test/of_vec.h>
#include <cftal/test/of_vec_v8.h>

namespace cftal {
    namespace test {
        bool spec_v8f32();
    }
}

bool cftal::test::spec_v8f32()
{
    bool r=true;
    r &= perm1_v8<float, -1, -1, -1, -1, -1, -1, -1, -1>();
    r &= perm1_v8<float, 0, 0, 0, 0, 0, 0, 0, 0>();
    r &= perm1_v8<float, 0, 1, 2, 3, 4, 5, 6, 7>();
    r &= perm1_v8<float, 0, 0, 1, 1, 4, 4, 5, 5>();
    r &= perm1_v8<float, 0, -1, 1, -1, 4, -1, 5, -1>();
    r &= perm1_v8<float, -1, 0, -1, 1, -1, 4, -1, 5>();
    r &= perm1_v8<float, 2, 2, 3, 3, 6, 6, 7, 7>();
    r &= perm1_v8<float, 2, -1, 3, -1, 6, -1, 7, -1>();
    r &= perm1_v8<float, -1, 2, -1, 3, -1, 6, -1, 7>();
    r &= perm1_v8<float,  0, 1, 0, 1, 4, 5, 4, 5>();
    r &= perm1_v8<float,  2, 3, 2, 3, 6, 7, 6, 7>();

    r &= perm2_v8<float,  -1, -1, -1, -1, -1, -1, -1, -1>();
    r &= perm2_v8<float, 0, 1, 2, 3, 4, 5, 6, 7>();
    r &= perm2_v8<float, 8, 9, 10, 11, 12, 13, 14, 15>();
    r &= perm2_v8<float, 2, 10, 3, 11, 6, 14, 7, 15>();
    r &= perm2_v8<float, 0, 1, 8, 9, 4, 5, 12, 13>();
    r &= perm2_v8<float, 2, 3, 10, 11, 6, 7, 14, 15>();
    
    r &= perm2_v8<float, 0, 1, 2, 3, 8, 9, 10, 11>();
    r &= perm2_v8<float, 0, 1, 2, 3, 12, 13, 14, 15>();
    r &= perm2_v8<float, 4, 5, 6, 7, 8, 9, 10, 11>();
    r &= perm2_v8<float, 4, 5, 6, 7, 12, 13, 14, 15 >();

    return r;
}


int main()
{
    bool rc(true);
    rc &= cftal::test::check_v8<float>();
    rc &= cftal::test::spec_v8f32();
    return rc == true ? 0 : 1;
}
