//
// Copyright Axel Zeuner 2010-2020. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/vec.h"
#include "cftal/vec_traits.h"
#include "cftal/math/spec_func_core_f64.h"
#include "vec_def_math_spec_funcs.h"

#if V8F64_FUNCS>0
DEF_SPEC_FUNCS(cftal, cftal, v8f64, v8s32, double)
#endif
#if V8F64_SLOW_SPEC_FUNCS>0
DEF_SLOW_SPEC_FUNCS(cftal, cftal, v8f64, v8s32, double)
#endif
