//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/vec.h"
#include "cftal/math/vec_func_traits.h"
#include "cftal/math/spec_func_core_f64.h"
#include "vec_def_math_spec_funcs.h"

#if V2F64_FUNCS>0
DEF_SPEC_FUNCS(cftal, cftal, v2f64, v2s32, double)
DEF_SLOW_SPEC_FUNCS(cftal, cftal, v2f64, v2s32, double)
#endif
