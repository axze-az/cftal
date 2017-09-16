//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_BITOPS_H__)
#define __CFTAL_BITOPS_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#if defined (__x86_64__) || defined (__i386__)
#include <cftal/x86/intrin.h>
#endif

namespace cftal {

    // read time stamp counter
    int64_t rdtsc();

    // returns the counted bits of every byte in every byte
    uint32_t __popcnt_8(uint32_t a);
    // returns the counted bits of every byte in every byte
    uint64_t __popcnt_8(uint64_t a);

    unsigned popcnt(uint8_t x);
    unsigned popcnt(uint16_t x);
    unsigned popcnt(uint32_t x);
    unsigned popcnt(uint64_t x);

    uint8_t bitrev(uint8_t x);
    uint16_t bitrev(uint16_t x);
    uint32_t bitrev(uint32_t x);
    uint64_t bitrev(uint64_t x);

    unsigned lzcnt(uint8_t x);
    unsigned lzcnt(uint16_t x);
    unsigned lzcnt(uint32_t x);
    unsigned lzcnt(uint64_t x);
}

inline
cftal::int64_t cftal::rdtsc()
{
#if defined (__x86_64__)
    uint64_t a, d;
    __asm__ __volatile__(// "lfence;\n\t" // NO fences during devel
                        "rdtsc" :"=a"(a), "=d"(d) ::"memory");
    return (d<<32) | a;
#elif defined (__i386__)
    uint64_t a;
    __asm__ __volatile__("lfence;\n\t"
                        "rdtsc" :"=A"(a)::"memory");
    return a;
#elif defined (_M_AMD64) && defined (_MSC_VER)
	__mm_lfence();
	return __rdtsc();
#elif defined (__ARM_ARCH_7__)
    unsigned tsc;
    uint64_t final_tsc;
    /* Read PMCCNTR synchronized*/
    __asm__ __volatile__("isb sy\n\t"
                        "mrc p15, 0, %0, c9, c13, 0\n\t"
                         : "=r"(tsc));
    /* 1 tick = 64 clocks */
    final_tsc = ((uint64_t)tsc) << 6;
    return (uint64_t)final_tsc;
#elif defined (__aarch64__)
    unsigned int val;
    /* Read Performance Monitors Control Register */
    asm volatile("mrs %0, pmcr_el0" : "=r" (val));
    return val;
    /* return 0 */;
#else
//#error "please insert a read current time functionality here"
    return 0;
#endif
}

inline
cftal::uint32_t cftal::__popcnt_8(uint32_t x)
{
    const uint32_t c55=0x55555555;
    const uint32_t c33=0x33333333;
    const uint32_t c0f=0x0f0f0f0f;
    x = x - ((x >> 1) & c55);
    x = (x & c33) + ((x >> 2) & c33);
    x = (x + (x >> 4)) & c0f;
    return x;
}

inline
cftal::uint64_t cftal::__popcnt_8(uint64_t x)
{
    const uint64_t c55 = 0x5555555555555555ULL;
    // binary: 00110011..
    const uint64_t c33 = 0x3333333333333333ULL;
    // binary:  4 zeros,  4 ones ...
    const uint64_t c0f = 0x0f0f0f0f0f0f0f0fULL;
    // count pairs of consecutive bits
    x = x - ((x >> 1) & c55);
    // add consecutive pairs of two bits
    x = (x & c33) + ((x >> 2) & c33);
    // add consecutive pairs of four bits
    x = (x + (x >> 4)) & c0f;
    return x;
}

inline
unsigned cftal::popcnt(uint8_t x)
{
#if defined (__GNUC__) && defined (__POPCNT__)
    return _mm_popcnt_u32(x);
#else
    return __popcnt_8(uint32_t(x));
#endif
}

inline
unsigned cftal::popcnt(uint16_t x)
{
#if defined (__GNUC__) && defined (__POPCNT__)
    return _mm_popcnt_u32(x);
#else
    unsigned r = __popcnt_8(uint32_t(x));
    return (r*0x01010101) >> 24;
#endif
}

inline
unsigned cftal::popcnt(uint32_t x)
{
#if defined (__GNUC__) && defined (__POPCNT__)
    return _mm_popcnt_u32(x);
#else
    unsigned r= __popcnt_8(x);
    return (r*0x01010101) >> 24;
#endif
}

inline
unsigned cftal::popcnt(uint64_t x)
{
#if defined (__GNUC__) && defined (__POPCNT__)
#if defined (__LP64__) || defined (__ILP32__)
    return _mm_popcnt_u64(x);
#else
    return _mm_popcnt_u32(uint32_t(x)) +
        _mm_popcnt_u32(uint32_t(x>>32));
#endif
#else
#if defined (__LP64__) || defined (__ILP32__)
    x = __popcnt_8(x);
    const uint64_t c01 = 0x0101010101010101ULL;
    return (x*c01) >> 56;
#else
    unsigned l = popcnt(uint32_t(x));
    unsigned h = popcnt(uint32_t(x>>32));
    return l+h;
#endif
#endif
}

inline
cftal::uint8_t cftal::bitrev(uint8_t x)
{
    // swap odd and even bits
    x = ((x >> 1) & 0x55555555) | ((x & 0x55555555) << 1);
    // swap consecutive pairs
    x = ((x >> 2) & 0x33333333) | ((x & 0x33333333) << 2);
    // swap nibbles ...
    x = ((x >> 4) & 0x0F0F0F0F) | ((x & 0x0F0F0F0F) << 4);
    return x;
}

inline
cftal::uint16_t cftal::bitrev(uint16_t x)
{
    // swap odd and even bits
    x = ((x >> 1) & 0x55555555) | ((x & 0x55555555) << 1);
    // swap consecutive pairs
    x = ((x >> 2) & 0x33333333) | ((x & 0x33333333) << 2);
    // swap nibbles ...
    x = ((x >> 4) & 0x0F0F0F0F) | ((x & 0x0F0F0F0F) << 4);
    // swap bytes
    x = ((x >> 8) & 0x00FF00FF) | ((x & 0x00FF00FF) << 8);
    return x;
}

inline
cftal::uint32_t cftal::bitrev(uint32_t x)
{
    // swap odd and even bits
    x = ((x >> 1) & 0x55555555) | ((x & 0x55555555) << 1);
    // swap consecutive pairs
    x = ((x >> 2) & 0x33333333) | ((x & 0x33333333) << 2);
    // swap nibbles ...
    x = ((x >> 4) & 0x0F0F0F0F) | ((x & 0x0F0F0F0F) << 4);
    // swap bytes
    x = ((x >> 8) & 0x00FF00FF) | ((x & 0x00FF00FF) << 8);
    // swap 2-byte elements
    x = ( x >> 16             ) | ( x               << 16);
    return x;
}

inline
cftal::uint64_t cftal::bitrev(uint64_t x)
{
    const uint64_t c5555 = 0x5555555555555555ULL;
    const uint64_t c3333 = 0x3333333333333333ULL;
    const uint64_t c0f0f = 0x0f0f0f0f0f0f0f0fULL;
    const uint64_t c00ff = 0x00ff00ff00ff00ffULL;
    const uint64_t cffff = 0x0000ffff0000ffffULL;
    // swap odd and even bits
    x = ((x >> 1) & c5555) | ((x & c5555) << 1);
    // swap consecutive pairs
    x = ((x >> 2) & c3333) | ((x & c3333) << 2);
    // swap nibbles ...
    x = ((x >> 4) & c0f0f) | ((x & c0f0f) << 4);
    // swap bytes
    x = ((x >> 8) & c00ff) | ((x & c00ff) << 8);
    // swap 2-byte elements
    x = ((x >>16) & cffff) | ((x & cffff) <<16);
    // swap 4-byte elements
    x = ((x >>32)        ) | ( x          <<32);
    return x;
}

inline
unsigned cftal::lzcnt(uint8_t x)
{
    return lzcnt(uint32_t(x))-24;
}

inline
unsigned cftal::lzcnt(uint16_t x)
{
    return lzcnt(uint32_t(x))-16;
}

inline
unsigned cftal::lzcnt(uint32_t x)
{
#if defined (__GNUC__)
    return x ? __builtin_clz(x) : 32;
#else
    x |= (x>>1);
    x |= (x>>2);
    x |= (x>>4);
    x |= (x>>8);
    x |= (x>>16);
    return popcnt(~x);
#endif
}

inline
unsigned cftal::lzcnt(uint64_t x)
{
#if defined (__GNUC__)
    return x ? __builtin_clzll(x) : 64;
#else
    x |= (x>>1);
    x |= (x>>2);
    x |= (x>>4);
    x |= (x>>8);
    x |= (x>>16);
    x |= (x>>32);
    return popcnt(~x);
#endif
}

// Local variables:
// mode: c++
// end:
#endif
