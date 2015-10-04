// #if defined (__AVX__)
#include "vec.h"
#include "vec_traits.h"
#include "vec_def_math_funcs.h"

DEF_MATH_FUNCS(cftal, v4f64, v4s32, double, 6)
// #endif

using cftal::v4f64;

void
trans4x4(v4f64* res,
         v4f64 a0, v4f64 a1, v4f64 a2, v4f64 a3)
{
    v4f64 r0=a0, r1=a1, r2=a2, r3=a3;
    cftal::transpose_4x4(r0, r1, r2, r3);
    res[0] = r0;
    res[1] = r1;
    res[2] = r2;
    res[3] = r3;
}

void
calc4x4(v4f64* res,
        const v4f64* a, const v4f64* b)
{
    v4f64 r0, r1, r2, r3;
    cftal::mat_mul_4x4(r0, r1, r2, r3,
                       a[0], a[1], a[2], a[3],
                       b[0], b[1], b[2], b[3]);
    res[0] = r0;
    res[1] = r1;
    res[2] = r2;
    res[3] = r3;
}

using cftal::v4f32;

void
calc4x4(v4f32* res,
        const v4f32* a, const v4f32* b)
{
    v4f32 r0, r1, r2, r3;
    cftal::mat_mul_4x4(r0, r1, r2, r3,
                       a[0], a[1], a[2], a[3],
                       b[0], b[1], b[2], b[3]);
    res[0] = r0;
    res[1] = r1;
    res[2] = r2;
    res[3] = r3;
}

