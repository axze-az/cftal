//
// Copyright Axel Zeuner 2010-2020. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_X86_INTRIN_H__)
#define __CFTAL_X86_INTRIN_H__ 1

#include <cftal/config.h>

#if IN_KDEVELOP_PARSER !=0 || IN_IDE_PARSER !=0
#define __AVX__ 1
#define __SSE4_1__ 1
#define __SSE4_2__ 1
#define __SSE4A__ 1
#define __SSSE3__ 1
#define __AVX2__ 1
#define __FMA__ 1
#define alignas(x)
#endif

#if defined (__SSE4_1__) && !defined (__POPCNT__)
#define __POPCNT__
#endif

#if defined (__SSE4A__) && !defined (__POPCNT__)
#define __POPCNT__
#endif

#include <x86intrin.h>

// Local variables:
// mode: c++
// end:
#endif
