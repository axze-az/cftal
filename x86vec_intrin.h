#if !defined (__X86VEC_INTRIN_H__)
#define __X86VEC_INTRIN_H__ 1

#if defined (IN_KDEVELOP_PARSER)
#define __AVX__ 1
#define __SSE4_1__ 1
#define __SSE4_2__ 1
#define __SSE4A__ 1
#define __SSSE3__ 1
#endif

#include <x86intrin.h>

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
