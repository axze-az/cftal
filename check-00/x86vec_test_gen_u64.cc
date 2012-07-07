#include "x86vec_test.h"
#include <iostream>
bool x86vec::test::check_select_u64()
{
        bool rc(true);
        __m128i a = load_u64(false);
        __m128i b = load_u64(true);
        __m128i r;
        idx id(-2,-2);

        r=select_u64< 0, 0>(a,b);
        id.assign( 2, 3);
        rc &= check_u64("select_u64", r, id);
        r=select_u64< 0, 1>(a,b);
        id.assign( 2, 1);
        rc &= check_u64("select_u64", r, id);
        r=select_u64< 1, 0>(a,b);
        id.assign( 0, 3);
        rc &= check_u64("select_u64", r, id);
        r=select_u64< 1, 1>(a,b);
        id.assign( 0, 1);
        rc &= check_u64("select_u64", r, id);
        return rc;
}

bool x86vec::test::check_perm1_u64()
{
        bool rc(true);
        __m128i a = load_u64(false);
        __m128i r;
        idx id(-2,-2);

        r=perm_u64<-1,-1>(a);
        id.assign(-1,-1);
        rc &= check_u64("perm1_u64", r, id);
        r=perm_u64<-1, 0>(a);
        id.assign(-1, 0);
        rc &= check_u64("perm1_u64", r, id);
        r=perm_u64<-1, 1>(a);
        id.assign(-1, 1);
        rc &= check_u64("perm1_u64", r, id);
        r=perm_u64< 0,-1>(a);
        id.assign( 0,-1);
        rc &= check_u64("perm1_u64", r, id);
        r=perm_u64< 0, 0>(a);
        id.assign( 0, 0);
        rc &= check_u64("perm1_u64", r, id);
        r=perm_u64< 0, 1>(a);
        id.assign( 0, 1);
        rc &= check_u64("perm1_u64", r, id);
        r=perm_u64< 1,-1>(a);
        id.assign( 1,-1);
        rc &= check_u64("perm1_u64", r, id);
        r=perm_u64< 1, 0>(a);
        id.assign( 1, 0);
        rc &= check_u64("perm1_u64", r, id);
        r=perm_u64< 1, 1>(a);
        id.assign( 1, 1);
        rc &= check_u64("perm1_u64", r, id);
        return rc;
}

bool x86vec::test::check_perm2_u64()
{
        bool rc(true);
        __m128i a = load_u64(false);
        __m128i b = load_u64(true);
        __m128i r;
        idx id(-2,-2);

        r=perm_u64<-1,-1>(a,b);
        id.assign(-1,-1);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64<-1, 0>(a,b);
        id.assign(-1, 0);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64<-1, 1>(a,b);
        id.assign(-1, 1);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64<-1, 2>(a,b);
        id.assign(-1, 2);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64<-1, 3>(a,b);
        id.assign(-1, 3);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64< 0,-1>(a,b);
        id.assign( 0,-1);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64< 0, 0>(a,b);
        id.assign( 0, 0);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64< 0, 1>(a,b);
        id.assign( 0, 1);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64< 0, 2>(a,b);
        id.assign( 0, 2);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64< 0, 3>(a,b);
        id.assign( 0, 3);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64< 1,-1>(a,b);
        id.assign( 1,-1);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64< 1, 0>(a,b);
        id.assign( 1, 0);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64< 1, 1>(a,b);
        id.assign( 1, 1);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64< 1, 2>(a,b);
        id.assign( 1, 2);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64< 1, 3>(a,b);
        id.assign( 1, 3);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64< 2,-1>(a,b);
        id.assign( 2,-1);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64< 2, 0>(a,b);
        id.assign( 2, 0);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64< 2, 1>(a,b);
        id.assign( 2, 1);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64< 2, 2>(a,b);
        id.assign( 2, 2);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64< 2, 3>(a,b);
        id.assign( 2, 3);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64< 3,-1>(a,b);
        id.assign( 3,-1);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64< 3, 0>(a,b);
        id.assign( 3, 0);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64< 3, 1>(a,b);
        id.assign( 3, 1);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64< 3, 2>(a,b);
        id.assign( 3, 2);
        rc &= check_u64("perm2_u64", r, id);
        r=perm_u64< 3, 3>(a,b);
        id.assign( 3, 3);
        rc &= check_u64("perm2_u64", r, id);
        return rc;
}

