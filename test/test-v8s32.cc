#include <cftal/config.h>
#include <cftal/test/of_vec.h>
#include <cftal/test/of_vec_v8.h>

namespace cftal {
    namespace test {
        bool spec_v8s32();
    }
}

bool cftal::test::spec_v8s32()
{
    bool r=true;
    r &= perm1_v8<int32_t, -1, -1, -1, -1, -1, -1, -1, -1>();
    r &= perm1_v8<int32_t,  0,  1,  2,  3,  4,  5,  6,  7>();
    r &= perm1_v8<int32_t,  0, 1, 0, 1, 4, 5, 4, 5>();
    r &= perm1_v8<int32_t,  2, 3, 2, 3, 6, 7, 6, 7>();

    r &= perm2_v8<int32_t,  0, 1, 8, 9, 4, 5, 12, 13>();
    r &= perm2_v8<int32_t,  2, 3, 10, 11, 6, 7, 14, 15>();
    r &= perm2_v8<int32_t,  0, 8, 1, 9, 4, 12, 5, 13>();
    r &= perm2_v8<int32_t,  2, 10, 3, 11, 6, 14, 7, 15>();
    
    return r;
}

int main()
{
    bool rc(true);
    rc &= cftal::test::check_v8<int32_t>();
    rc &= cftal::test::spec_v8s32();
    return rc == true ? 0 : 1;
}
