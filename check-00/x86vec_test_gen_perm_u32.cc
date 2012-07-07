#include "x86vec_test.h"

bool x86vec::test::check_perm1_u32()
{
        bool rc(true);
        rc &= check_perm1_u32__();
        rc &= check_perm1_u32_0();
        rc &= check_perm1_u32_1();
        rc &= check_perm1_u32_2();
        rc &= check_perm1_u32_3();
        return rc;
}

//#include "x86vec_test.h"

bool x86vec::test::check_perm2_u32()
{
        bool rc(true);
        rc &= check_perm2_u32__();
        rc &= check_perm2_u32_0();
        rc &= check_perm2_u32_1();
        rc &= check_perm2_u32_2();
        rc &= check_perm2_u32_3();
        rc &= check_perm2_u32_4();
        rc &= check_perm2_u32_5();
        rc &= check_perm2_u32_6();
        rc &= check_perm2_u32_7();
        return rc;
}

