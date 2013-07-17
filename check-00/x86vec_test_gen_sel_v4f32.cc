#include "x86vec_test.h"

bool x86vec::test::check_select_v4f32()
{
        bool rc(true);
        __m128 a = load_v4f32(false);
        __m128 b = load_v4f32(true);
        __m128 r;
        idx id(-2,-2);

        r=select_v4f32< 0, 0, 0, 0>(a,b);
        id.assign( 4, 5, 6, 7);
        rc &= check_v4f32("select_v4f32", r, id);
        r=select_v4f32< 0, 0, 0, 1>(a,b);
        id.assign( 4, 5, 6, 3);
        rc &= check_v4f32("select_v4f32", r, id);
        r=select_v4f32< 0, 0, 1, 0>(a,b);
        id.assign( 4, 5, 2, 7);
        rc &= check_v4f32("select_v4f32", r, id);
        r=select_v4f32< 0, 0, 1, 1>(a,b);
        id.assign( 4, 5, 2, 3);
        rc &= check_v4f32("select_v4f32", r, id);
        r=select_v4f32< 0, 1, 0, 0>(a,b);
        id.assign( 4, 1, 6, 7);
        rc &= check_v4f32("select_v4f32", r, id);
        r=select_v4f32< 0, 1, 0, 1>(a,b);
        id.assign( 4, 1, 6, 3);
        rc &= check_v4f32("select_v4f32", r, id);
        r=select_v4f32< 0, 1, 1, 0>(a,b);
        id.assign( 4, 1, 2, 7);
        rc &= check_v4f32("select_v4f32", r, id);
        r=select_v4f32< 0, 1, 1, 1>(a,b);
        id.assign( 4, 1, 2, 3);
        rc &= check_v4f32("select_v4f32", r, id);
        r=select_v4f32< 1, 0, 0, 0>(a,b);
        id.assign( 0, 5, 6, 7);
        rc &= check_v4f32("select_v4f32", r, id);
        r=select_v4f32< 1, 0, 0, 1>(a,b);
        id.assign( 0, 5, 6, 3);
        rc &= check_v4f32("select_v4f32", r, id);
        r=select_v4f32< 1, 0, 1, 0>(a,b);
        id.assign( 0, 5, 2, 7);
        rc &= check_v4f32("select_v4f32", r, id);
        r=select_v4f32< 1, 0, 1, 1>(a,b);
        id.assign( 0, 5, 2, 3);
        rc &= check_v4f32("select_v4f32", r, id);
        r=select_v4f32< 1, 1, 0, 0>(a,b);
        id.assign( 0, 1, 6, 7);
        rc &= check_v4f32("select_v4f32", r, id);
        r=select_v4f32< 1, 1, 0, 1>(a,b);
        id.assign( 0, 1, 6, 3);
        rc &= check_v4f32("select_v4f32", r, id);
        r=select_v4f32< 1, 1, 1, 0>(a,b);
        id.assign( 0, 1, 2, 7);
        rc &= check_v4f32("select_v4f32", r, id);
        r=select_v4f32< 1, 1, 1, 1>(a,b);
        id.assign( 0, 1, 2, 3);
        rc &= check_v4f32("select_v4f32", r, id);
        return rc;
}

