#include "x86vec_test.h"

bool x86vec::test::check_perm1_u32_1()
{
        bool rc(true);
        __m128i a = load_u32(false);
        __m128i r;
        idx id(-2,-2);

        r=perm_u32< 1,-1,-1,-1>(a);
        id.assign( 1,-1,-1,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1,-1, 0>(a);
        id.assign( 1,-1,-1, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1,-1, 1>(a);
        id.assign( 1,-1,-1, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1,-1, 2>(a);
        id.assign( 1,-1,-1, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1,-1, 3>(a);
        id.assign( 1,-1,-1, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1, 0,-1>(a);
        id.assign( 1,-1, 0,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1, 0, 0>(a);
        id.assign( 1,-1, 0, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1, 0, 1>(a);
        id.assign( 1,-1, 0, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1, 0, 2>(a);
        id.assign( 1,-1, 0, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1, 0, 3>(a);
        id.assign( 1,-1, 0, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1, 1,-1>(a);
        id.assign( 1,-1, 1,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1, 1, 0>(a);
        id.assign( 1,-1, 1, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1, 1, 1>(a);
        id.assign( 1,-1, 1, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1, 1, 2>(a);
        id.assign( 1,-1, 1, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1, 1, 3>(a);
        id.assign( 1,-1, 1, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1, 2,-1>(a);
        id.assign( 1,-1, 2,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1, 2, 0>(a);
        id.assign( 1,-1, 2, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1, 2, 1>(a);
        id.assign( 1,-1, 2, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1, 2, 2>(a);
        id.assign( 1,-1, 2, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1, 2, 3>(a);
        id.assign( 1,-1, 2, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1, 3,-1>(a);
        id.assign( 1,-1, 3,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1, 3, 0>(a);
        id.assign( 1,-1, 3, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1, 3, 1>(a);
        id.assign( 1,-1, 3, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1, 3, 2>(a);
        id.assign( 1,-1, 3, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1,-1, 3, 3>(a);
        id.assign( 1,-1, 3, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0,-1,-1>(a);
        id.assign( 1, 0,-1,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0,-1, 0>(a);
        id.assign( 1, 0,-1, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0,-1, 1>(a);
        id.assign( 1, 0,-1, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0,-1, 2>(a);
        id.assign( 1, 0,-1, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0,-1, 3>(a);
        id.assign( 1, 0,-1, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0, 0,-1>(a);
        id.assign( 1, 0, 0,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0, 0, 0>(a);
        id.assign( 1, 0, 0, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0, 0, 1>(a);
        id.assign( 1, 0, 0, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0, 0, 2>(a);
        id.assign( 1, 0, 0, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0, 0, 3>(a);
        id.assign( 1, 0, 0, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0, 1,-1>(a);
        id.assign( 1, 0, 1,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0, 1, 0>(a);
        id.assign( 1, 0, 1, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0, 1, 1>(a);
        id.assign( 1, 0, 1, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0, 1, 2>(a);
        id.assign( 1, 0, 1, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0, 1, 3>(a);
        id.assign( 1, 0, 1, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0, 2,-1>(a);
        id.assign( 1, 0, 2,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0, 2, 0>(a);
        id.assign( 1, 0, 2, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0, 2, 1>(a);
        id.assign( 1, 0, 2, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0, 2, 2>(a);
        id.assign( 1, 0, 2, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0, 2, 3>(a);
        id.assign( 1, 0, 2, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0, 3,-1>(a);
        id.assign( 1, 0, 3,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0, 3, 0>(a);
        id.assign( 1, 0, 3, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0, 3, 1>(a);
        id.assign( 1, 0, 3, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0, 3, 2>(a);
        id.assign( 1, 0, 3, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 0, 3, 3>(a);
        id.assign( 1, 0, 3, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1,-1,-1>(a);
        id.assign( 1, 1,-1,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1,-1, 0>(a);
        id.assign( 1, 1,-1, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1,-1, 1>(a);
        id.assign( 1, 1,-1, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1,-1, 2>(a);
        id.assign( 1, 1,-1, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1,-1, 3>(a);
        id.assign( 1, 1,-1, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1, 0,-1>(a);
        id.assign( 1, 1, 0,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1, 0, 0>(a);
        id.assign( 1, 1, 0, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1, 0, 1>(a);
        id.assign( 1, 1, 0, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1, 0, 2>(a);
        id.assign( 1, 1, 0, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1, 0, 3>(a);
        id.assign( 1, 1, 0, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1, 1,-1>(a);
        id.assign( 1, 1, 1,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1, 1, 0>(a);
        id.assign( 1, 1, 1, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1, 1, 1>(a);
        id.assign( 1, 1, 1, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1, 1, 2>(a);
        id.assign( 1, 1, 1, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1, 1, 3>(a);
        id.assign( 1, 1, 1, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1, 2,-1>(a);
        id.assign( 1, 1, 2,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1, 2, 0>(a);
        id.assign( 1, 1, 2, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1, 2, 1>(a);
        id.assign( 1, 1, 2, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1, 2, 2>(a);
        id.assign( 1, 1, 2, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1, 2, 3>(a);
        id.assign( 1, 1, 2, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1, 3,-1>(a);
        id.assign( 1, 1, 3,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1, 3, 0>(a);
        id.assign( 1, 1, 3, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1, 3, 1>(a);
        id.assign( 1, 1, 3, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1, 3, 2>(a);
        id.assign( 1, 1, 3, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 1, 3, 3>(a);
        id.assign( 1, 1, 3, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2,-1,-1>(a);
        id.assign( 1, 2,-1,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2,-1, 0>(a);
        id.assign( 1, 2,-1, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2,-1, 1>(a);
        id.assign( 1, 2,-1, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2,-1, 2>(a);
        id.assign( 1, 2,-1, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2,-1, 3>(a);
        id.assign( 1, 2,-1, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2, 0,-1>(a);
        id.assign( 1, 2, 0,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2, 0, 0>(a);
        id.assign( 1, 2, 0, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2, 0, 1>(a);
        id.assign( 1, 2, 0, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2, 0, 2>(a);
        id.assign( 1, 2, 0, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2, 0, 3>(a);
        id.assign( 1, 2, 0, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2, 1,-1>(a);
        id.assign( 1, 2, 1,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2, 1, 0>(a);
        id.assign( 1, 2, 1, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2, 1, 1>(a);
        id.assign( 1, 2, 1, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2, 1, 2>(a);
        id.assign( 1, 2, 1, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2, 1, 3>(a);
        id.assign( 1, 2, 1, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2, 2,-1>(a);
        id.assign( 1, 2, 2,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2, 2, 0>(a);
        id.assign( 1, 2, 2, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2, 2, 1>(a);
        id.assign( 1, 2, 2, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2, 2, 2>(a);
        id.assign( 1, 2, 2, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2, 2, 3>(a);
        id.assign( 1, 2, 2, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2, 3,-1>(a);
        id.assign( 1, 2, 3,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2, 3, 0>(a);
        id.assign( 1, 2, 3, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2, 3, 1>(a);
        id.assign( 1, 2, 3, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2, 3, 2>(a);
        id.assign( 1, 2, 3, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 2, 3, 3>(a);
        id.assign( 1, 2, 3, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3,-1,-1>(a);
        id.assign( 1, 3,-1,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3,-1, 0>(a);
        id.assign( 1, 3,-1, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3,-1, 1>(a);
        id.assign( 1, 3,-1, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3,-1, 2>(a);
        id.assign( 1, 3,-1, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3,-1, 3>(a);
        id.assign( 1, 3,-1, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3, 0,-1>(a);
        id.assign( 1, 3, 0,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3, 0, 0>(a);
        id.assign( 1, 3, 0, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3, 0, 1>(a);
        id.assign( 1, 3, 0, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3, 0, 2>(a);
        id.assign( 1, 3, 0, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3, 0, 3>(a);
        id.assign( 1, 3, 0, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3, 1,-1>(a);
        id.assign( 1, 3, 1,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3, 1, 0>(a);
        id.assign( 1, 3, 1, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3, 1, 1>(a);
        id.assign( 1, 3, 1, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3, 1, 2>(a);
        id.assign( 1, 3, 1, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3, 1, 3>(a);
        id.assign( 1, 3, 1, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3, 2,-1>(a);
        id.assign( 1, 3, 2,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3, 2, 0>(a);
        id.assign( 1, 3, 2, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3, 2, 1>(a);
        id.assign( 1, 3, 2, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3, 2, 2>(a);
        id.assign( 1, 3, 2, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3, 2, 3>(a);
        id.assign( 1, 3, 2, 3);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3, 3,-1>(a);
        id.assign( 1, 3, 3,-1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3, 3, 0>(a);
        id.assign( 1, 3, 3, 0);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3, 3, 1>(a);
        id.assign( 1, 3, 3, 1);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3, 3, 2>(a);
        id.assign( 1, 3, 3, 2);
        rc &= check_u32("perm1_u32", r, id);
        r=perm_u32< 1, 3, 3, 3>(a);
        id.assign( 1, 3, 3, 3);
        rc &= check_u32("perm1_u32", r, id);
        return rc;
}

