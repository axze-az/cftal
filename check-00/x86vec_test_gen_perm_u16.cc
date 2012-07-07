#include "x86vec_test.h"

bool x86vec::test::check_perm1_u16()
{
        bool rc(true);
        rc &= check_perm1_u16__();
        rc &= check_perm1_u16_0();
        rc &= check_perm1_u16_1();
        rc &= check_perm1_u16_2();
        rc &= check_perm1_u16_3();
        rc &= check_perm1_u16_4();
        rc &= check_perm1_u16_5();
        rc &= check_perm1_u16_6();
        rc &= check_perm1_u16_7();
        return rc;
}

//#include "x86vec_test.h"

bool x86vec::test::check_perm2_u16()
{
        bool rc(true);
        rc &= check_perm2_u16___();
        rc &= check_perm2_u16_00();
        rc &= check_perm2_u16_01();
        rc &= check_perm2_u16_02();
        rc &= check_perm2_u16_03();
        rc &= check_perm2_u16_04();
        rc &= check_perm2_u16_05();
        rc &= check_perm2_u16_06();
        rc &= check_perm2_u16_07();
        rc &= check_perm2_u16_08();
        rc &= check_perm2_u16_09();
        rc &= check_perm2_u16_10();
        rc &= check_perm2_u16_11();
        rc &= check_perm2_u16_12();
        rc &= check_perm2_u16_13();
        rc &= check_perm2_u16_14();
        rc &= check_perm2_u16_15();
        return rc;
}

