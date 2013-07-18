#include "x86vec_test.h"

bool x86vec::test::check_perm1_v4f64()
{
        bool rc(true);
        rc &= check_perm1_v4f64__();
        rc &= check_perm1_v4f64_0();
        rc &= check_perm1_v4f64_1();
        rc &= check_perm1_v4f64_2();
        rc &= check_perm1_v4f64_3();
        return rc;
}

//#include "x86vec_test.h"

bool x86vec::test::check_perm2_v4f64()
{
        bool rc(true);
        rc &= check_perm2_v4f64__();
        rc &= check_perm2_v4f64_0();
        rc &= check_perm2_v4f64_1();
        rc &= check_perm2_v4f64_2();
        rc &= check_perm2_v4f64_3();
        rc &= check_perm2_v4f64_4();
        rc &= check_perm2_v4f64_5();
        rc &= check_perm2_v4f64_6();
        rc &= check_perm2_v4f64_7();
        return rc;
}

