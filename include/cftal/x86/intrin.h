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

#if defined (__SSE__)
#include <immintrin.h>
#endif

#if defined (__SSE4_1__) && !defined (__POPCNT__)
#define __POPCNT__
#endif

#if defined (__SSE4A__) && !defined (__POPCNT__)
#define __POPCNT__
#endif

// Local variables:
// mode: c++
// end:
#endif
