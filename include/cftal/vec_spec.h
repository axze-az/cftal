//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_VEC_SPEC_H__)
#define __CFTAL_VEC_SPEC_H__ 1

#include <cftal/config.h>
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

#if defined (__ARM_NEON__) || defined (__ARM_NEON)
#include <cftal/arm/v2f32.h>
#include <cftal/arm/v2f64.h>
#endif

// floating point vector specializations
#if defined (__SSE2__)
#include <cftal/x86/v4f32.h>
#include <cftal/x86/v2f64.h>
#endif
#if defined (__AVX__)
#include <cftal/x86/v8f32.h>
#include <cftal/x86/v4f64.h>
#endif
// floating point vector specialization implementations
#if defined (__SSE2__)
#include <cftal/x86/v4f32_inl.h>
#endif
#if defined (__AVX__)
#include <cftal/x86/v8f32_inl.h>
#endif
#if defined (__AVX512F__)
#include <cftal/x86/v8f64.h>
#endif
#if defined (__SSE2__)
#include <cftal/x86/v2f64_inl.h>
#endif
#if defined (__AVX__)
#include <cftal/x86/v4f64_inl.h>
#endif
#if defined (__AVX512F__)
#include <cftal/x86/v8f64_inl.h>
#endif

namespace cftal {

    template <typename _T>
    constexpr
    size_t max_vec_size_specialized();
}

template <typename _T>
constexpr cftal::size_t
cftal::max_vec_size_specialized()
{
    constexpr
    const size_t r=
        is_vec_specialized<vec<_T, 64> >::value==true ? 64 :
        is_vec_specialized<vec<_T, 32> >::value==true ? 32 :
        is_vec_specialized<vec<_T, 16> >::value==true ? 16 :
        is_vec_specialized<vec<_T, 8> >::value==true ? 8 :
        is_vec_specialized<vec<_T, 4> >::value==true ? 4 :
        is_vec_specialized<vec<_T, 2> >::value==true ? 2 : 1;
    return r;
}


#endif // __CFTAL_VEC_SPEC_H__
