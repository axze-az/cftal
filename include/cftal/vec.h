//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_VEC_H__)
#define __CFTAL_VEC_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <cftal/arg.h>
#include <cftal/select.h>
#include <cftal/init_list.h>
#include <cftal/constants.h>
#include <cftal/expr.h>
#include <cftal/mem.h>
#include <cftal/vec_t_n.h>
#include <cftal/vec_mask.h>
#include <cftal/vec_op.h>
#include <cftal/vec_t_1.h>

#if defined (__ARM_NEON) || defined (__ARM_NEON__)
#include <cftal/arm/v2s32.h>
#include <cftal/arm/v2u32.h>
#include <cftal/arm/v2s64.h>
#include <cftal/arm/v2u64.h>

#include <cftal/arm/v2s32_inl.h>
#include <cftal/arm/v2u32_inl.h>
#include <cftal/arm/v2s64_inl.h>
#include <cftal/arm/v2u64_inl.h>
#endif

#if defined (__SSE2__)
// include 128 bit integer vector specializations
#include <cftal/x86/v4s32.h>
#include <cftal/x86/v4u32.h>
#include <cftal/x86/v2s64.h>
#include <cftal/x86/v2u64.h>
#include <cftal/x86/v8s16.h>
#include <cftal/x86/v8u16.h>
// include 128 bit integer vector specializations implementations
#include <cftal/x86/v4s32_inl.h>
#include <cftal/x86/v4u32_inl.h>
#include <cftal/x86/v2s64_inl.h>
#include <cftal/x86/v2u64_inl.h>
#include <cftal/x86/v8s16_inl.h>
#include <cftal/x86/v8u16_inl.h>
#endif
#if defined (__AVX2__)
// include 256 bit integer vector specializations
#include <cftal/x86/v8s32.h>
#include <cftal/x86/v8u32.h>
#include <cftal/x86/v4s64.h>
#include <cftal/x86/v4u64.h>
// include 256 bit integer vector specializations implementations
#include <cftal/x86/v8s32_inl.h>
#include <cftal/x86/v8u32_inl.h>
#include <cftal/x86/v4s64_inl.h>
#include <cftal/x86/v4u64_inl.h>
#endif

#include <cftal/vec_double_n.h>
#include <cftal/vec_float_n.h>
#include <cftal/vec_math_funcs.h>

#include <cftal/vec_cvt.h>
#include <cftal/vec_cast.h>
#include <cftal/vec_misc.h>



// Local variables:
// mode: c++
// end:
#endif
