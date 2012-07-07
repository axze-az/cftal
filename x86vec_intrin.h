#if !defined (__X86VEC_INTRIN_H__)
#define __X86VEC_INTRIN_H__ 1

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
