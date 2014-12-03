#include "vec.h"
#if defined (__AVX__)
#include "x86_traits.h"
#include "x86_math_funcs.h"

DEF_MATH_FUNCS(cftal, v4f64, v4s32, double, 6)
#endif
