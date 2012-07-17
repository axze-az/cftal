#if !defined (__CFTAL_DIVISOR_H__)
#define __CFTAL_DIVISOR_H__ 1

#include <cftal/bitops.h>

namespace cftal {

	// perform _V/_D via _V * (1/_D)
	template <class _V, class _D = _V>
	class divisor {
		_V _rec;
		_D _d;
	public:
		divisor(const _D& dd) : _rec(_V(_D(1)/dd)), _d(dd) {}
		const _D& d() const { return _d; }
		_V divide(const _V& n) const { return n * _rec;	}
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

		template <typename _D, typename _TR= sdiv_setup_traits<_D> >
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
			  typename _UDIV_SETUP_TRAITS = udiv_setup_traits<_D> >
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
			  typename _SDIV_SETUP_TRAITS = sdiv_setup_traits<_D> >
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
			typedef std::int16_t sword;
			typedef std::uint16_t uword;
			typedef std::uint32_t udword;
			static
			uword ceil_log2(uword t) {
				return 16 - lzcnt(uword(t-1));
			}
			static
			sword ceil_log2(sword t) {
				return ceil_log2(std::uint16_t(t));
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
				return (std::uint32_t(a) * 
					std::uint32_t(b)) >> 16;
			}
			static
			sword mulsh(sword a, sword b) {
				return (std::int32_t(a) * 
					std::int32_t(b))>>16;
			}
			enum {
				_N = 16
			};
		};

		struct div32_traits {
			typedef std::int32_t sword;
			typedef std::uint32_t uword;
			typedef std::uint64_t udword;
			static
			uword ceil_log2(uword t) {
				return 32 - lzcnt(t-1);
			}
			static
			sword ceil_log2(sword t) {
				return ceil_log2(std::uint32_t(t));
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
				return (std::uint64_t(a) * 
					std::uint64_t(b)) >> 32;
			}
			static
			sword mulsh(sword a, sword b) {
				return (std::int64_t(a) * 
					std::int64_t(b))>>32;
			}
			enum {
				_N =32
			};
		};

		// unsigned div 16
		template <>
		struct udiv_setup_traits<std::uint16_t> 
			: public div16_traits {};
		template <>
		struct udiv_traits<std::uint16_t, std::uint16_t> 
			: public div16_traits {};
		// signed div 16
		template <>
		struct sdiv_setup_traits<std::int16_t> 
			: public div16_traits {};
		template <>
		struct sdiv_traits<std::int16_t, std::int16_t> 
			: public div16_traits {};

		// unsigned div 32
		template <>
		struct udiv_setup_traits<std::uint32_t> 
			: public div32_traits {};
		template <>
		struct udiv_traits<std::uint32_t, std::uint32_t> 
			: public div32_traits {};

		// signed div 32
		template <>
		struct sdiv_setup_traits<std::int32_t> 
			: public div32_traits {};
		template <>
		struct sdiv_traits<std::int32_t, std::int32_t> 
			: public div32_traits {};
	}

	template <>
	class divisor<std::int16_t, std::int16_t>
		: public impl::sdiv<std::int16_t, std::int16_t> {
	public:
		divisor(std::int16_t d) : 
			impl::sdiv<std::int16_t, std::int16_t>(d) {}
	};
	template <>
	class divisor<std::uint16_t, std::uint16_t>
		: public impl::udiv<std::uint16_t, std::uint16_t> {
	public:
		divisor(int16_t d) : 
			impl::udiv<std::uint16_t, std::uint16_t>(d) {}
	};
	template <>
	class divisor<std::int32_t, std::int32_t>
		: public impl::sdiv<std::int32_t, std::int32_t> {
	public:
		divisor(std::int32_t d) : 
			impl::sdiv<std::int32_t, std::int32_t>(d) {}
	};
	template <>
	class divisor<std::uint32_t, std::uint32_t>
		: public impl::udiv<std::uint32_t, std::uint32_t> {
	public:
		divisor(std::uint32_t d) : 
			impl::udiv<std::uint32_t, std::uint32_t>(d) {}
	};

	template <class _V>
	_V operator%(const _V& n, const divisor<_V, std::int16_t>& d)
	{
		_V q(d.divide(n));
		_V dd(d.d());
		return remainder(n, dd, q);
	}

	template <class _V>
	_V operator%(const _V& n, const divisor<_V, std::uint16_t>& d)
	{
		_V q(d.divide(n));
		_V dd(d.d());
		return remainder(n, dd, q);
	}

	template <class _V>
	_V operator%(const _V& n, const divisor<_V, std::int32_t>& d)
	{
		_V q(d.divide(n));
		_V dd(d.d());
		return remainder(n, dd, q);
	}

	template <class _V>
	_V operator%(const _V& n, const divisor<_V, std::uint32_t>& d)
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

template <typename _D, class _TR>
cftal::impl::udiv_setup<_D, _TR>::udiv_setup(const uword& d)
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
cftal::impl::
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
cftal::impl::
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
cftal::impl::sdiv_setup<_D, _TR>::sdiv_setup(const sword& d)
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
cftal::impl::
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
cftal::impl::
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
