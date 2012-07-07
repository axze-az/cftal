#include "x86vec_test.h"

bool x86vec::test::check_perm1_f32()
{
        bool rc(true);
        rc &= check_perm1_f32__();
        rc &= check_perm1_f32_0();
        rc &= check_perm1_f32_1();
        rc &= check_perm1_f32_2();
        rc &= check_perm1_f32_3();
        return rc;
}

//#include "x86vec_test.h"

bool x86vec::test::check_perm2_f32()
{
        bool rc(true);
        rc &= check_perm2_f32__();
        rc &= check_perm2_f32_0();
        rc &= check_perm2_f32_1();
        rc &= check_perm2_f32_2();
        rc &= check_perm2_f32_3();
        rc &= check_perm2_f32_4();
        rc &= check_perm2_f32_5();
        rc &= check_perm2_f32_6();
        rc &= check_perm2_f32_7();
        return rc;
}

