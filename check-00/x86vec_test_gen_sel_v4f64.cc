#include "x86vec_test.h"

bool x86vec::test::check_select_v4f64()
{
#if !defined (__AVX__)
        return true;
#else
        bool rc(true);
        __m256d a = load_v4f64(false);
        __m256d b = load_v4f64(true);
        __m256d r;
        idx id(-2,-2);

        r=select_f64< 0, 0, 0, 0>(a,b);
        id.assign( 4, 5, 6, 7);
        rc &= check_v4f64("select_v4f64", r, id);
        r=select_f64< 0, 0, 0, 1>(a,b);
        id.assign( 4, 5, 6, 3);
        rc &= check_v4f64("select_v4f64", r, id);
        r=select_f64< 0, 0, 1, 0>(a,b);
        id.assign( 4, 5, 2, 7);
        rc &= check_v4f64("select_v4f64", r, id);
        r=select_f64< 0, 0, 1, 1>(a,b);
        id.assign( 4, 5, 2, 3);
        rc &= check_v4f64("select_v4f64", r, id);
        r=select_f64< 0, 1, 0, 0>(a,b);
        id.assign( 4, 1, 6, 7);
        rc &= check_v4f64("select_v4f64", r, id);
        r=select_f64< 0, 1, 0, 1>(a,b);
        id.assign( 4, 1, 6, 3);
        rc &= check_v4f64("select_v4f64", r, id);
        r=select_f64< 0, 1, 1, 0>(a,b);
        id.assign( 4, 1, 2, 7);
        rc &= check_v4f64("select_v4f64", r, id);
        r=select_f64< 0, 1, 1, 1>(a,b);
        id.assign( 4, 1, 2, 3);
        rc &= check_v4f64("select_v4f64", r, id);
        r=select_f64< 1, 0, 0, 0>(a,b);
        id.assign( 0, 5, 6, 7);
        rc &= check_v4f64("select_v4f64", r, id);
        r=select_f64< 1, 0, 0, 1>(a,b);
        id.assign( 0, 5, 6, 3);
        rc &= check_v4f64("select_v4f64", r, id);
        r=select_f64< 1, 0, 1, 0>(a,b);
        id.assign( 0, 5, 2, 7);
        rc &= check_v4f64("select_v4f64", r, id);
        r=select_f64< 1, 0, 1, 1>(a,b);
        id.assign( 0, 5, 2, 3);
        rc &= check_v4f64("select_v4f64", r, id);
        r=select_f64< 1, 1, 0, 0>(a,b);
        id.assign( 0, 1, 6, 7);
        rc &= check_v4f64("select_v4f64", r, id);
        r=select_f64< 1, 1, 0, 1>(a,b);
        id.assign( 0, 1, 6, 3);
        rc &= check_v4f64("select_v4f64", r, id);
        r=select_f64< 1, 1, 1, 0>(a,b);
        id.assign( 0, 1, 2, 7);
        rc &= check_v4f64("select_v4f64", r, id);
        r=select_f64< 1, 1, 1, 1>(a,b);
        id.assign( 0, 1, 2, 3);
        rc &= check_v4f64("select_v4f64", r, id);
        return rc;
#endif
}

