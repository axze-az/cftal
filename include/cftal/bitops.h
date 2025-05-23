//
// Copyright (C) 2010-2025 Axel Zeuner
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
//
#if !defined (__CFTAL_BITOPS_H__)
#define __CFTAL_BITOPS_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#if defined (__x86_64__) || defined (__i386__) || \
    (defined (_M_AMD64) && defined (_MSC_VER))
#include <cftal/x86/intrin.h>
#endif
#include <type_traits>

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

    namespace impl {

	template <typename _U>
	std::enable_if_t<std::is_unsigned_v<_U>, _U>
	bit_unpack(const _U& b, const _U& mask);

	template <typename _U>
	std::enable_if_t<std::is_unsigned_v<_U>, _U>
	bit_pack(const _U& b, const _U& mask);
    }

    // unpack the low bits of b into the positions of one bits in mask
    // in the result, other bits are set to 0
    uint32_t bit_unpack(uint32_t b, uint32_t mask);
    uint64_t bit_unpack(uint64_t b, uint64_t mask);

    // pack the bits in the positions of one bits in mask from b to
    // the low bits of the result, other bits are set to 0
    uint32_t bit_pack(uint32_t b, uint32_t mask);
    uint64_t bit_pack(uint64_t b, uint64_t mask);
}

inline
cftal::int64_t cftal::rdtsc()
{
#if defined (__x86_64__)
    uint64_t a, d;
    __asm__ __volatile__("lfence;\n\t" // NO fences during devel
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
#if defined (__amd64) || defined (__i386__)
    uint32_t x32 = x;
    x32 = _bswap(x32);
    x32 >>= 16;
    x = uint16_t(x32);
#else
    // swap bytes
    x = ((x >> 8) & 0x00FF00FF) | ((x & 0x00FF00FF) << 8);
#endif
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
#if defined (__amd64) || defined (__i386__)
    x = _bswap(x);
#else
    // swap bytes
    x = ((x >> 8) & 0x00FF00FF) | ((x & 0x00FF00FF) << 8);
    // swap 2-byte elements
    x = ( x >> 16             ) | ( x               << 16);
#endif
    return x;
}

inline
cftal::uint64_t cftal::bitrev(uint64_t x)
{
    const uint64_t c5555 = 0x5555555555555555ULL;
    const uint64_t c3333 = 0x3333333333333333ULL;
    const uint64_t c0f0f = 0x0f0f0f0f0f0f0f0fULL;
    // swap odd and even bits
    x = ((x >> 1) & c5555) | ((x & c5555) << 1);
    // swap consecutive pairs
    x = ((x >> 2) & c3333) | ((x & c3333) << 2);
    // swap nibbles ...
    x = ((x >> 4) & c0f0f) | ((x & c0f0f) << 4);
#if defined (__amd64)
    x = _bswap64(x);
#else
    const uint64_t c00ff = 0x00ff00ff00ff00ffULL;
    const uint64_t cffff = 0x0000ffff0000ffffULL;
    // swap bytes
    x = ((x >> 8) & c00ff) | ((x & c00ff) << 8);
    // swap 2-byte elements
    x = ((x >>16) & cffff) | ((x & cffff) <<16);
    // swap 4-byte elements
    x = ((x >>32)        ) | ( x          <<32);
#endif
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

template <typename _U>
std::enable_if_t<std::is_unsigned_v<_U>, _U>
cftal::impl::bit_unpack(const _U& b, const _U& mask)
{
    _U r=0;
#if 1
    _U s=b;
    _U d=1;
    _U m=mask;
#pragma GCC unroll 1
#pragma clang unroll(1)
    for (uint32_t i=0; i<sizeof(_U)*8; ++i) {
#if 1
        _U m_and_s = m & s;
        _U r_or_d = r|d;
        _U s_shr_1 = s>>1;
        r = (m_and_s & 1) ==1 ? r_or_d : r;
        s = (m & 1) ==1 ? s_shr_1 : s;
        if (s==0)
            break;
#else
        if (m & 1) {
            if (s & 1) {
                r |= d;
            }
            // next source bit
            s >>=1;
            if (s==0)
                break;
        }
#endif
        m >>=1;
        if (m==0)
            break;
        // next destination bit
        d <<=1;
    }
    return r;
#else
    // source mask
    _U s=1;
    // destination mask
    _U d=1;
    // current mask
    _U m=mask;
#pragma GCC unroll 1
#pragma clang unroll(1)
    for (uint32_t i=0; i<sizeof(_U)*8; ++i) {
	if (d & m) {
	    if (s & b) {
		r |= d;
	    }
	    // clear bit i in m
	    m ^= d;
            // if no mask bits are left, leave early
            if (m==0)
                break;
	    // next source bit
	    s <<=1;
	}
	// next destination bit
	d <<=1;
    }
    return r;
#endif
}

template <typename _U>
std::enable_if_t<std::is_unsigned_v<_U>, _U>
cftal::impl::bit_pack(const _U& b, const _U& mask)
{
    _U r=0;
#if 1
    _U m=mask;
    _U s=b;
    _U d=1;
#pragma GCC unroll 1
#pragma clang unroll(1)
    for (uint32_t i=0; i<sizeof(_U)*8; ++i) {
#if 1
        _U m_and_s= m & s;
        _U r_or_d = r|d;
        _U d_shl_1 = d<<1;
        r = (m_and_s & 1) ==1 ? r_or_d : r;
        d = (m & 1) == 1? d_shl_1: d;
#else
        if (m & 1) {
            if (s & 1) {
                r |= d;
            }
            // next destination bit
            d <<=1;
        }
#endif
        // next source bit
        s >>=1;
        if (s==0)
            break;
        m >>=1;
        if (m==0)
            break;
    }
    return r;
#else
    // source mask
    _U s=1;
    // destination mask
    _U d=1;
    _U m=mask;
#pragma GCC unroll 1
#pragma clang unroll(1)
    for (uint32_t i=0; i<sizeof(_U)*8; ++i) {
	if (s & m) {
	    if (s & b) {
		r |= d;
	    }
	    // next destination bit
	    d <<=1;
            // clear bit i in m
            m ^=s;
            // if no mask bits are left, leave early
            if (m==0)
                break;
	}
	// next source bit
	s <<=1;
    }
    return r;
#endif
}

inline
cftal::uint32_t
cftal::bit_unpack(uint32_t b, uint32_t mask)
{
#if defined (__BMI2__)
    return _pdep_u32(b, mask);
#else
    return impl::bit_unpack(b, mask);
#endif
}

inline
cftal::uint64_t
cftal::bit_unpack(uint64_t b, uint64_t mask)
{
#if defined (__BMI2__)
    return _pdep_u64(b, mask);
#else
    return impl::bit_unpack(b, mask);
#endif
}

inline
cftal::uint32_t
cftal::bit_pack(uint32_t b, uint32_t mask)
{
#if defined (__BMI2__)
    return _pext_u32(b, mask);
#else
    return impl::bit_pack(b, mask);
#endif
}

inline
cftal::uint64_t
cftal::bit_pack(uint64_t b, uint64_t mask)
{
#if defined (__BMI2__)
    return _pext_u64(b, mask);
#else
    return impl::bit_pack(b, mask);
#endif
}


// Local variables:
// mode: c++
// end:
#endif
