//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_CONFIG_H__)
#define __CFTAL_CONFIG_H__ 1

#define __CFTAL_MAJOR__ 0
#define __CFTAL_MINOR__ 4
#define __CFTAL_PATCHLEVEL__ 0

#if defined (__ARM_NEON)
#if !defined (__ARM_NEON__)
#define __ARM_NEON__ 1
#endif
#endif

#if defined (__GNUC__) || defined (__clang__)
#define thread_local __thread
#define likely(a) __builtin_expect(!!(a), 1)
#define unlikely(a) __builtin_expect(!!(a), 0)
#if defined (__clang__)
#define __builtin_assume_aligned(p, x) p
#endif
#endif

#if defined (__clang__)
#if defined (__FMA__) || defined (__FMA4__)
#define FP_FAST_FMA 1
#define FP_FAST_FMAF 1
#endif
#endif

#if !defined (__GNUC__) && !defined(__clang__) || (IN_KDEVELOP_PARSER>0)
#define alignas(X)
#define __SSSE3__
#define __SSE41__
#define __SSE42__
#define __AVX__
#define __AVX2__
#define __AVX515F__
#endif

#if defined (_MSC_VER)
#define thread_local __declspec(thread)
#endif

#if !defined (likely)
#define likely(a) a
#endif
#if !defined (unlikely)
#define unlikely(a) a
#endif
#if !defined(__GNUC__) && !defined (__CLANG__)
#define __restrict
#endif

#if (defined (__GNUC__) || defined (__clang__)) && defined (__x86_64__)
#define X86_64_SPECIALIZE_V2F32 1
#endif

// Local variables:
// mode: c++
// end:
#endif
