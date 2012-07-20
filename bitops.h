#if !defined (__CFTAL_BITOPS_H__)
#define __CFTAL_BITOPS_H__ 1

#include <x86intrin.h>
#include <cstdint>
#include <utility>
#include <algorithm>
#include <type_traits>

namespace cftal {

	template <class _U>
	struct unsigned_mul {
		// returns high part in first, low part in second
		std::pair<_U, _U> operator()(const _U& a, const _U& b)
			const;
	};

	template <class _S>
	struct signed_mul {
		// returns high part in first, low part in second
		std::pair<_S, _S> operator()(const _S& a, const _S& b)
			const;
	};

	template <class _T>
	std::pair<_T, _T> wide_mul(const _T& a, const _T& b);
	
	// read time stamp counter
	std::int64_t rdtsc();

	// returns the counted bits of every byte in every byte
	std::uint32_t __popcnt_8(std::uint32_t a);
	// returns the counted bits of every byte in every byte
	std::uint64_t __popcnt_8(std::uint64_t a);

	unsigned popcnt(std::uint8_t x);
	unsigned popcnt(std::uint16_t x);
	unsigned popcnt(std::uint32_t x);
	unsigned popcnt(std::uint64_t x);

	std::uint8_t bitrev(std::uint8_t x);
	std::uint16_t bitrev(std::uint16_t x);
	std::uint32_t bitrev(std::uint32_t x);
	std::uint64_t bitrev(std::uint64_t x);

	unsigned lzcnt(std::uint16_t x);
	unsigned lzcnt(std::uint32_t x);
	unsigned lzcnt(std::uint64_t x);
}

template <class _U>
std::pair<_U, _U> 
cftal::unsigned_mul<_U>::operator()(const _U& a, const _U& b)
	const
{
	enum {
		N = sizeof(_U)* 8,
		N2 = N>>1
	};

	const _U N2MSK= (_U(1)<<N2)-_U(1);
	const _U MED_CARRY = _U(1) << N2;

	_U al = a & N2MSK;
	_U ah = a >> N2;
	_U bl = b & N2MSK;
	_U bh = b >> N2;

	_U al_bl = al * bl;
	_U al_bh = al * bh;
	_U ah_bl = ah * bl;
	_U ah_bh = ah * bh;

	_U med_sum = al_bh + ah_bl;
	_U l_add = med_sum << N2;
	_U h_add = med_sum >> N2;

	h_add |= (med_sum < al_bh) ? MED_CARRY : _U(0);

	al_bl += l_add;
	_U l_carry= al_bl < l_add ? _U(1) : _U(0);

	ah_bh += l_carry;
	ah_bh += h_add;
	return std::make_pair(ah_bh, al_bl);
}

template <class _S>
std::pair<_S, _S> 
cftal::signed_mul<_S>::operator()(const _S& x, const _S& y)
	const
{
	enum {
		N = sizeof(_S)* 8
	};
	typedef typename std::make_unsigned<_S>::type _U;
	_U xu(x);
	_U yu(y);
	unsigned_mul<_U> m;
	std::pair<_U, _U> ur(m(xu, yu));
	// muluh(x,y) = mulsh(x,y) + and(x, xsign(y)) + and(y, xsign(x));
	// mulsh(x,y) = muluh(x,y) - and(x, xsign(y)) - and(y, xsign(x));
	_S xsign_x = x >> (N-1);
	_S xsign_y = y >> (N-1);
	_S h = _S(ur.first) - (x & xsign_y) - (y & xsign_x);
	_S l = _S(ur.second); 
	return std::make_pair(h, l);
}

template <class _T>
inline
std::pair<_T, _T>
cftal::wide_mul(const _T& x, const _T& y)
{
	typedef typename std::conditional<std::is_signed<_T>::value,
					  signed_mul<_T>, 
					  unsigned_mul<_T> >::type mul_type;
	mul_type m;
	return m(x, y);
}


inline
std::int64_t cftal::rdtsc()
{
#if defined (__x86_64__)
	std::uint64_t a, d;
	_mm_lfence();
	__asm__ __volatile__("rdtsc" :"=a"(a), "=d"(d)::"memory");
	return d<<32 | a;
#elif defined (__i386__)
	std::uint64_t a;
	_mm_lfence();
	__asm__ __volatile__("rdtsc" :"=A"(a)::"memory");
	return a;
#else
#error "please insert a read current time functionality here"
#endif
}

inline
std::uint32_t cftal::__popcnt_8(std::uint32_t x)
{
	const std::uint32_t c55=0x55555555;
	const std::uint32_t c33=0x33333333;
	const std::uint32_t c0f=0x0f0f0f0f;
        x = x - ((x >> 1) & c55);
        x = (x & c33) + ((x >> 2) & c33);
        x = (x + (x >> 4)) & c0f;
	return x;
}

inline
std::uint64_t cftal::__popcnt_8(std::uint64_t x)
{
	const std::uint64_t c55 = 0x5555555555555555ULL;
	// binary: 00110011..
	const std::uint64_t c33 = 0x3333333333333333ULL;
	// binary:  4 zeros,  4 ones ...
	const std::uint64_t c0f = 0x0f0f0f0f0f0f0f0fULL;
	// count pairs of consecutive bits
        x = x - ((x >> 1) & c55);
	// add consecutive pairs of two bits
        x = (x & c33) + ((x >> 2) & c33);
	// add consecutive pairs of four bits
        x = (x + (x >> 4)) & c0f;
	return x;
}

inline
unsigned cftal::popcnt(std::uint8_t x)
{
#if defined (__GNUC__) && defined (__POPCNT__)
	return _mm_popcnt_u32(x);
#else
	return __popcnt_8(std::uint32_t(x));
#endif
}

inline
unsigned cftal::popcnt(std::uint16_t x)
{
#if defined (__GNUC__) && defined (__POPCNT__)
	return _mm_popcnt_u32(x);
#else
	unsigned r = __popcnt_8(std::uint32_t(x));
        return (r*0x01010101) >> 24;
#endif
}

inline
unsigned cftal::popcnt(std::uint32_t x)
{
#if defined (__GNUC__) && defined (__POPCNT__)
	return _mm_popcnt_u32(x);
#else
	unsigned r= __popcnt_8(x);
        return (r*0x01010101) >> 24;
#endif
}

inline
unsigned cftal::popcnt(std::uint64_t x)
{
#if defined (__GNUC__) && defined (__POPCNT__)
#if defined (__LP64__) || defined (__ILP32__)
	return _mm_popcnt_u64(x);
#else
	return _mm_popcnt_u32(std::uint32_t(x)) +
		_mm_popcnt_u32(std::uint32_t(x>>32));
#endif
#else
#if defined (__LP64__) || defined (__ILP32__)
	x = __popcnt_8(x);
	const std::uint64_t c01 = 0x0101010101010101ULL;
	return (x*c01) >> 56;
#else
	unsigned l = popcnt(std::uint32_t(x));
	unsigned h = popcnt(std::uint32_t(x>>32));
	return l+h;
#endif
#endif
}

inline
std::uint8_t cftal::bitrev(std::uint8_t x)
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
std::uint16_t cftal::bitrev(std::uint16_t x)
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
std::uint32_t cftal::bitrev(std::uint32_t x)
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
std::uint64_t cftal::bitrev(std::uint64_t x)
{
	const std::uint64_t c5555 = 0x5555555555555555ULL;
	const std::uint64_t c3333 = 0x3333333333333333ULL;
	const std::uint64_t c0f0f = 0x0f0f0f0f0f0f0f0fULL;
	const std::uint64_t c00ff = 0x00ff00ff00ff00ffULL;
	const std::uint64_t cffff = 0x0000ffff0000ffffULL;
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
unsigned cftal::lzcnt(std::uint16_t x)
{
	return lzcnt(std::uint32_t(x))-16;
}

inline
unsigned cftal::lzcnt(std::uint32_t x)
{
#if defined (__GNUC__)
	return x ? __builtin_clz(x) : 32;
#else
	x |= (x>>1);
	x |= (x>>2);
	x |= (x>>4);
	x |= (x>>8);
	x |= (x>>16);
	return popcnt(x);
#endif
}

inline
unsigned cftal::lzcnt(std::uint64_t x)
{
#if defined (__GNUC__)
	return x ? __builtin_clzl(x) : 64;
#else
	x |= (x>>1);
	x |= (x>>2);
	x |= (x>>4);
	x |= (x>>8);
	x |= (x>>16);
	x |= (x>>32);
	return popcnt(x);
#endif
}


// Local variables:
// mode: c++
// end:
#endif
