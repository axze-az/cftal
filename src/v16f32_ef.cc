//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/vec_traits.h"
#include "cftal/math/func.h"
#include "cftal/math/elem_func_core_f32.h"
#include "vec_def_math_elem_funcs.h"
#include <cmath>
#include <limits>

#if V16F32_FUNCS>0
DEF_ELEM_FUNCS(cftal, cftal, v16f32, v16s32, float)
#endif
