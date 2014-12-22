#if defined (__AVX__)
#include "x86_traits.h"
#include "math_func.h"
#include "d_real.h"
#include <cmath>
#include <limits>
#include "x86_math_funcs.h"

DEF_MATH_FUNCS(cftal, v8f32, v8s32, float, 4)

#endif
