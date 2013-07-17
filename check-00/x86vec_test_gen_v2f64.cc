#include "x86vec_test.h"
#include <iostream>
bool x86vec::test::check_select_v2f64()
{
        bool rc(true);
        __m128d a = load_v2f64(false);
        __m128d b = load_v2f64(true);
        __m128d r;
        idx id(-2,-2);

        r=select_f64< 0, 0>(a,b);
        id.assign( 2, 3);
        rc &= check_v2f64("select_v2f64", r, id);
        r=select_f64< 0, 1>(a,b);
        id.assign( 2, 1);
        rc &= check_v2f64("select_v2f64", r, id);
        r=select_f64< 1, 0>(a,b);
        id.assign( 0, 3);
        rc &= check_v2f64("select_v2f64", r, id);
        r=select_f64< 1, 1>(a,b);
        id.assign( 0, 1);
        rc &= check_v2f64("select_v2f64", r, id);
        return rc;
}

bool x86vec::test::check_perm1_v2f64()
{
        bool rc(true);
        __m128d a = load_v2f64(false);
        __m128d r;
        idx id(-2,-2);

        r=perm_f64<-1,-1>(a);
        id.assign(-1,-1);
        rc &= check_v2f64("perm1_v2f64", r, id);
        r=perm_f64<-1, 0>(a);
        id.assign(-1, 0);
        rc &= check_v2f64("perm1_v2f64", r, id);
        r=perm_f64<-1, 1>(a);
        id.assign(-1, 1);
        rc &= check_v2f64("perm1_v2f64", r, id);
        r=perm_f64< 0,-1>(a);
        id.assign( 0,-1);
        rc &= check_v2f64("perm1_v2f64", r, id);
        r=perm_f64< 0, 0>(a);
        id.assign( 0, 0);
        rc &= check_v2f64("perm1_v2f64", r, id);
        r=perm_f64< 0, 1>(a);
        id.assign( 0, 1);
        rc &= check_v2f64("perm1_v2f64", r, id);
        r=perm_f64< 1,-1>(a);
        id.assign( 1,-1);
        rc &= check_v2f64("perm1_v2f64", r, id);
        r=perm_f64< 1, 0>(a);
        id.assign( 1, 0);
        rc &= check_v2f64("perm1_v2f64", r, id);
        r=perm_f64< 1, 1>(a);
        id.assign( 1, 1);
        rc &= check_v2f64("perm1_v2f64", r, id);
        return rc;
}

bool x86vec::test::check_perm2_v2f64()
{
        bool rc(true);
        __m128d a = load_v2f64(false);
        __m128d b = load_v2f64(true);
        __m128d r;
        idx id(-2,-2);

        r=perm_f64<-1,-1>(a,b);
        id.assign(-1,-1);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64<-1, 0>(a,b);
        id.assign(-1, 0);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64<-1, 1>(a,b);
        id.assign(-1, 1);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64<-1, 2>(a,b);
        id.assign(-1, 2);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64<-1, 3>(a,b);
        id.assign(-1, 3);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64< 0,-1>(a,b);
        id.assign( 0,-1);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64< 0, 0>(a,b);
        id.assign( 0, 0);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64< 0, 1>(a,b);
        id.assign( 0, 1);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64< 0, 2>(a,b);
        id.assign( 0, 2);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64< 0, 3>(a,b);
        id.assign( 0, 3);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64< 1,-1>(a,b);
        id.assign( 1,-1);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64< 1, 0>(a,b);
        id.assign( 1, 0);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64< 1, 1>(a,b);
        id.assign( 1, 1);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64< 1, 2>(a,b);
        id.assign( 1, 2);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64< 1, 3>(a,b);
        id.assign( 1, 3);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64< 2,-1>(a,b);
        id.assign( 2,-1);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64< 2, 0>(a,b);
        id.assign( 2, 0);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64< 2, 1>(a,b);
        id.assign( 2, 1);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64< 2, 2>(a,b);
        id.assign( 2, 2);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64< 2, 3>(a,b);
        id.assign( 2, 3);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64< 3,-1>(a,b);
        id.assign( 3,-1);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64< 3, 0>(a,b);
        id.assign( 3, 0);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64< 3, 1>(a,b);
        id.assign( 3, 1);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64< 3, 2>(a,b);
        id.assign( 3, 2);
        rc &= check_v2f64("perm2_v2f64", r, id);
        r=perm_f64< 3, 3>(a,b);
        id.assign( 3, 3);
        rc &= check_v2f64("perm2_v2f64", r, id);
        return rc;
}

