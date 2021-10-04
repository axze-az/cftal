//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/math/vec_func_traits.h"
#include "cftal/math/half_func.h"
#include "vec_def_math_half_funcs.h"
#include <cmath>
#include <limits>

#if V8F32_FUNCS>0
DEF_HALF_FUNCS(cftal, cftal::half_math, v8f32, v8s32, float)
#endif
