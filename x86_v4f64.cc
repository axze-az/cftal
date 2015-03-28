// #if defined (__AVX__)
#include "x86_v4f64.h"
#include "vec_traits.h"
#include "vec_math_funcs.h"

DEF_MATH_FUNCS(cftal, v4f64, v4s32, double, 6)
// #endif
