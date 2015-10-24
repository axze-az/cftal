#if !defined (__CFTAL_VEC_H__)
#define __CFTAL_VEC_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <cftal/select.h>
#include <cftal/init_list.h>
#include <cftal/constants.h>
#include <cftal/expr.h>
#include <cftal/mem.h>
#include <cftal/vec_t_n.h>
#include <cftal/vec_mask.h>
#include <cftal/vec_op.h>
#include <type_traits>
#include <cmath>

#include <cftal/vec_t_1.h>
#if defined (__SSE2__)
// include 128 bit integer vector specializations 
#include <cftal/x86_v4s32.h>
#include <cftal/x86_v4u32.h>
#include <cftal/x86_v2s64.h>
#include <cftal/x86_v2u64.h>
#include <cftal/x86_v8s16.h>
#include <cftal/x86_v8u16.h>
// include 128 bit integer vector specializations implementations
#include <cftal/x86_v4s32_inl.h>
#include <cftal/x86_v4u32_inl.h>
#include <cftal/x86_v2s64_inl.h>
#include <cftal/x86_v2u64_inl.h>
#include <cftal/x86_v8s16_inl.h>
#include <cftal/x86_v8u16_inl.h>
#endif
#if defined (__AVX2__)
// include 256 bit integer vector specializations
#include <cftal/x86_v8s32.h>
#include <cftal/x86_v8u32.h>
#include <cftal/x86_v4s64.h>
#include <cftal/x86_v4u64.h>
// include 256 bit integer vector specializations implementations
#include <cftal/x86_v8s32_inl.h>
#include <cftal/x86_v8u32_inl.h>
#include <cftal/x86_v4s64_inl.h>
#include <cftal/x86_v4u64_inl.h>
#endif

#include <cftal/vec_double_n.h>
#include <cftal/vec_float_n.h>

#include <cftal/vec_cvt.h>
#include <cftal/vec_cast.h>
#include <cftal/vec_misc.h>


// Local variables:
// mode: c++
// end:
#endif
