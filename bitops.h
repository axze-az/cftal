#if !defined (__BITOPS_H__)
#define __BITOPS_H__ 1

#include <x86intrin.h>
#include <cstdint>
#include <utility>
#include <algorithm>

namespace bitops {

	using std::int8_t;
	using std::int16_t;
	using std::int32_t;
	using std::int64_t;
	using std::uint8_t;
	using std::uint16_t;
	using std::uint32_t;
	using std::uint64_t;

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

	// perform _V/_D via _V * (1/_D)
	template <class _V, class _D = _V>
	class divisor {
		_V _rec;
		_D _d;
	public:
		divisor(const _D& dd) : _rec(_V(_D(1)/dd)), _d(dd) {
		}
		const _D& d() const {
			return _d;
		}
		_V divide(const _V& n) const {
			return n * _rec;
		}
	};

	template <class _V>
	_V remainder(const _V& n, const _V& d, const _V& q)
	{
		_V p(d* q);
		return n - p;
	}

	template <class _V, class _D>
	_V operator/(const _V& n, const divisor<_V, _D>& d)
	{
		return d.divide(n);
	}

	template <class _V, class _D>
	_V& operator/=(_V& n, const divisor<_V, _D>& d)
	{
		_V q(d.divide(n));
		n = q;
		return n;
	}

	namespace impl {

		template <typename _T>
		struct udiv_setup_traits {
			// uword, udword types
			// ceil_log2 of _T
			// _N as sizeof(uword) in bits
		};

		template <typename _T>
		struct sdiv_setup_traits {
			// sword, udword types
			// ceil_log2 of _T
			// _N as sizeof(sword) in bits
		};

		template <typename _V, typename _D>
		struct udiv_traits {
			// _V splat_for_shift(_D)
			// _V muluh(_V, _V);
		};

		template <typename _V, typename _D>
		struct sdiv_traits {
			// _V splat_for_shift(_D)
			// _V mulsh(_V, _V);
		};

		template <typename _D, typename _TR= udiv_setup_traits<_D> >
		class udiv_setup {
		public:
			typedef typename _TR::uword uword;
			typedef typename _TR::udword udword;
			udiv_setup(const uword& d);
			const uword& m() const { return _m; }
			const uword& s1() const { return _s1; }
			const uword& s2() const { return _s2; }
			bool shift_only() const { return _shift_only; }
		private:
			uword _m;
			uword _s1;
			uword _s2;
			bool _shift_only;
		};

		template <typename _D, typename _TR= udiv_setup_traits<_D> >
		class sdiv_setup {
		public:
			typedef typename _TR::sword sword;
			typedef typename _TR::udword udword;
			sdiv_setup(const sword& d);
			const sword& m() const { return _m; }
			const sword& s() const { return _s; }
			const sword& xsgn_d() const { return _xsgn_d; }
		private:
			sword _m;
			sword _s;
			sword _xsgn_d;
		};

		template <typename _V, typename _D,
			  typename _UDIV_TRAITS= udiv_traits<_V, _D>,
			  typename _UDIV_SETUP_TRAITS = udiv_setup_traits<_V> >
		class udiv {
			_V _m;
			_V _s1;
			_V _s2;
			_D _d;
			bool _shift_only;
		public:
			udiv(const _D& d) { set(d); }
			void set(const _D& d);
			const _D& d() const { return _d; }
			_V divide(const _V& n) const;
		};

		template <typename _V, typename _D,
			  typename _SDIV_TRAITS= sdiv_traits<_V, _D>,
			  typename _SDIV_SETUP_TRAITS = sdiv_setup_traits<_V> >
		class sdiv {
			_V _m;
			_V _s;
			_V _xsgn_d;
			_D _d;
		public:
			sdiv(const _D& d) { set(d); }
			void set(const _D& d);
			const _D& d() const { return _d; }
			_V divide(const _V& n) const;
		};

		struct div16_traits {
			typedef int16_t sword;
			typedef uint16_t uword;
			typedef uint32_t udword;
			static
			uword ceil_log2(uword t) {
				return 16 - lzcnt(uword(t-1));
			}
			static
			sword ceil_log2(sword t) {
				return ceil_log2(uint16_t(t));
			}
			static
			uword splat_for_shift(uword t) {
				return t;
			}
			static
			sword splat_for_shift(sword t) {
				return t;
			}
			static
			uword muluh(uword a, uword b) {
				return (uint32_t(a) * uint32_t(b)) >> 16;
			}
			static
			sword mulsh(sword a, sword b) {
				return (int32_t(a) * int32_t(b))>>16;
			}
			enum {
				_N = 16
			};
		};

		struct div32_traits {
			typedef int32_t sword;
			typedef uint32_t uword;
			typedef uint64_t udword;
			static
			uword ceil_log2(uword t) {
				return 32 - lzcnt(t-1);
			}
			static
			sword ceil_log2(sword t) {
				return ceil_log2(uint32_t(t));
			}
			static
			uword splat_for_shift(uword t) {
				return t;
			}
			static
			sword splat_for_shift(sword t) {
				return t;
			}
			static
			uword muluh(uword a, uword b) {
				return (uint64_t(a) * uint64_t(b)) >> 32;
			}
			static
			sword mulsh(sword a, sword b) {
				return (int64_t(a) * int64_t(b))>>32;
			}
			enum {
				_N =32
			};
		};

		// unsigned div 16
		template <>
		struct udiv_setup_traits<uint16_t> : public div16_traits {};
		template <>
		struct udiv_traits<uint16_t, uint16_t> : public div16_traits {};

		// signed div 16
		template <>
		struct sdiv_setup_traits<int16_t> : public div16_traits {};
		template <>
		struct sdiv_traits<int16_t, int16_t> : public div16_traits {};

		// unsigned div 32
		template <>
		struct udiv_setup_traits<uint32_t> : public div32_traits {};
		template <>
		struct udiv_traits<uint32_t, uint32_t> : public div32_traits {};

		// signed div 32
		template <>
		struct sdiv_setup_traits<int32_t> : public div32_traits {};
		template <>
		struct sdiv_traits<int32_t, int32_t> : public div32_traits {};
	}

	template <>
	class divisor<int16_t, int16_t>
		: public impl::sdiv<int16_t, int16_t> {
	public:
		divisor(int16_t d) : impl::sdiv<int16_t, int16_t>(d) {}
	};
	template <>
	class divisor<uint16_t, uint16_t>
		: public impl::udiv<uint16_t, uint16_t> {
	public:
		divisor(int16_t d) : impl::udiv<uint16_t, uint16_t>(d) {}
	};
	template <>
	class divisor<int32_t, int32_t>
		: public impl::sdiv<int32_t, int32_t> {
	public:
		divisor(int32_t d) : impl::sdiv<int32_t, int32_t>(d) {}
	};
	template <>
	class divisor<uint32_t, uint32_t>
		: public impl::udiv<uint32_t, uint32_t> {
	public:
		divisor(uint32_t d) : impl::udiv<uint32_t, uint32_t>(d) {}
	};

	template <class _V>
	_V operator%(const _V& n, const divisor<_V, int16_t>& d)
	{
		_V q(d.divide(n));
		_V dd(d.d());
		return remainder(n, dd, q);
	}

	template <class _V>
	_V operator%(const _V& n, const divisor<_V, uint16_t>& d)
	{
		_V q(d.divide(n));
		_V dd(d.d());
		return remainder(n, dd, q);
	}

	template <class _V>
	_V operator%(const _V& n, const divisor<_V, int32_t>& d)
	{
		_V q(d.divide(n));
		_V dd(d.d());
		return remainder(n, dd, q);
	}

	template <class _V>
	_V operator%(const _V& n, const divisor<_V, uint32_t>& d)
	{
		_V q(d.divide(n));
		_V dd(d.d());
		return remainder(n, dd, q);
	}


	namespace test {
		bool div_u16();
		bool div_s16();
		bool div_u32();
		bool div_s32();
	}

}

inline
std::int64_t bitops::rdtsc()
{
	std::uint64_t a, d;
	__asm__ __volatile__("rdtsc" :"=a"(a), "=d"(d));
	return d<<32 | a;
}

inline
std::uint32_t bitops::__popcnt_8(std::uint32_t x)
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
std::uint64_t bitops::__popcnt_8(std::uint64_t x)
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
unsigned bitops::popcnt(std::uint8_t x)
{
#if defined (__GNUC__) && defined (__POPCNT__)
	return _mm_popcnt_u32(x);
#else
	return __popcnt_8(std::uint32_t(x));
#endif
}

inline
unsigned bitops::popcnt(std::uint16_t x)
{
#if defined (__GNUC__) && defined (__POPCNT__)
	return _mm_popcnt_u32(x);
#else
	unsigned r = __popcnt_8(std::uint32_t(x));
        return (r*0x01010101) >> 24;
#endif
}

inline
unsigned bitops::popcnt(std::uint32_t x)
{
#if defined (__GNUC__) && defined (__POPCNT__)
	return _mm_popcnt_u32(x);
#else
	unsigned r= __popcnt_8(x);
        return (r*0x01010101) >> 24;
#endif
}

inline
unsigned bitops::popcnt(std::uint64_t x)
{
#if defined (__GNUC__) && defined (__POPCNT__)
#if defined (__LP64__) || defined (__ILP32__)
	return _mm_popcnt_u64(x);
#else
	return _mm_popcnt(std::uint32_t(x)) +
		_mm_popcnt(std::uint32_t(x>>32));
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
std::uint8_t bitops::bitrev(std::uint8_t x)
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
std::uint16_t bitops::bitrev(std::uint16_t x)
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
std::uint32_t bitops::bitrev(std::uint32_t x)
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
std::uint64_t bitops::bitrev(std::uint64_t x)
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
unsigned bitops::lzcnt(std::uint16_t x)
{
	return lzcnt(std::uint32_t(x))-16;
}

inline
unsigned bitops::lzcnt(std::uint32_t x)
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
unsigned bitops::lzcnt(std::uint64_t x)
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

template <typename _D, class _TR>
bitops::impl::udiv_setup<_D, _TR>::udiv_setup(const uword& d)
{
	int l = _TR::ceil_log2(d);
	if ( (d & (d-1)) == uword(0)) {
		_m = uword(0);
		_s1 = l;
		_s2 = 0;
		_shift_only = true;
	} else {
		udword ms0= ((udword(1) << l) - d)<<_TR::_N;
		udword ms= ms0/d + 1;
		_m = uword(ms);
		_s1= std::min(l, 1);
		_s2= std::max(l-1, 0);
		_shift_only = false;
	}
}

template <typename _V, typename _D,
          class _UDIV_TRAITS, class _UDIV_SETUP_TRAITS>
void
bitops::impl::
udiv<_V, _D, _UDIV_TRAITS, _UDIV_SETUP_TRAITS>::set(const _D& d)
{
	udiv_setup<_D, _UDIV_SETUP_TRAITS> setup(d);
	_d = d;
	_m = _V(setup.m());
	_s1 = _UDIV_TRAITS::splat_for_shift(setup.s1());
	_s2 = _UDIV_TRAITS::splat_for_shift(setup.s2());
	_shift_only = setup.shift_only();
}

template <typename _V, typename _D,
          class _UDIV_TRAITS, class _UDIV_SETUP_TRAITS>
_V
bitops::impl::
udiv<_V, _D, _UDIV_TRAITS, _UDIV_SETUP_TRAITS>::divide(const _V& n)
	const
{
	if (_d == _D(0))
		return _V(_D(-1));
	_V q;
	if (_shift_only) {
		q = n >> _s1;
	} else {
		_V t1 = _UDIV_TRAITS::muluh(_m, n);
		_V t2 = (n - t1) >> _s1;
		q = (t1 + t2) >> _s2;
	}
	return q;
}

template <typename _D, class _TR>
bitops::impl::sdiv_setup<_D, _TR>::sdiv_setup(const sword& d)
{
	const sword min_sword=_D(1) << (_TR::_N-1);
	if (d==0) {
		_m = 0;
		_s = 0;
	} else if (d == min_sword) {
		_m = d +1;
		_s = _TR::_N -2;
	} else {
		sword ad = d < _D(0) ? -d : d;
		int l = std::max(_TR::ceil_log2(ad), sword(1));
		udword ms0= (udword(1) << (_TR::_N + l -1))/ad + udword(1);
		udword ms = ms0 - (udword(1) << (_TR::_N));
		_m = sword(ms);
		_s = l-1;
	}
	_xsgn_d = d >> (_TR::_N-1);
}

template <typename _V, typename _D,
          class _SDIV_TRAITS, class _SDIV_SETUP_TRAITS>
void
bitops::impl::
sdiv<_V, _D, _SDIV_TRAITS, _SDIV_SETUP_TRAITS>::set(const _D& d)
{
	sdiv_setup<_D, _SDIV_SETUP_TRAITS> setup(d);
	_d = d;
	_m = _V(setup.m());
	_s = _V(setup.s());
	_xsgn_d = _V(setup.xsgn_d());
}

template <typename _V, typename _D,
          class _SDIV_TRAITS, class _SDIV_SETUP_TRAITS>
_V
bitops::impl::
sdiv<_V, _D, _SDIV_TRAITS, _SDIV_SETUP_TRAITS>::divide(const _V& n)
	const
{
	if (_d == _D(0))
		return _V(_D(-1));
	_V q0 = n + _SDIV_TRAITS::mulsh(_m, n);
	_V xsgn_n = n >> (_SDIV_SETUP_TRAITS::_N-1);
	_V q1 = (q0 >> _s) - xsgn_n;
	_V q = (q1 ^ _xsgn_d) - _xsgn_d;
	return q;
}


// Local variables:
// mode: c++
// end:
#endif
