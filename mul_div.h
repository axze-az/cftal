#if !defined (__CFTAL_MUL_DIV_H__)
#define __CFTAL_MUL_DIV_H__ 1

#include <cftal/config.h>
#include <cftal/bitops.h>
#include <type_traits>

namespace cftal {

        // calculate the remainder from ceil(n/d)=q
        template <class _V>
        _V remainder(const _V& n, const _V& d, const _V& q);

        template <typename _T>
        class duint {
        public:
                typedef _T type;
                enum {
                        N2 = sizeof(type) * 8,
                        N = N2*2
                };
                duint() : _l(0), _h(0) {
		}
		duint(const type& vl) : _l(vl), _h(0) {
		}
                duint(const type& vl, const type& vh) : _l(vl), _h(vh) {
		}
                const type& l() const { 
			return _l; 
		}
                const type& h() const { 
			return _h; 
		}
                void l(const type& v) { 
			_l = v; 
		}
                void h(const type& v) { 
			_h = v; 
		}
		operator _T() const {
			return _l;
		}
        private:
                type _l;
                type _h;
        };

	template <class _T>
	unsigned lzcnt(const duint<_T>& a);

	template <typename _T>
	duint<_T> operator~(const duint<_T>& a);
	template <typename _T>
	duint<_T> operator-(const duint<_T>& a);

        template <typename _T>
        duint<_T> operator|(const duint<_T>& a, const duint<_T>& b);
        template <typename _T>
        duint<_T> operator&(const duint<_T>& a, const duint<_T>& b);
        template <typename _T>
        duint<_T> operator^(const duint<_T>& a, const duint<_T>& b);

        template <typename _T>
        duint<_T> operator+(const duint<_T>& a, const duint<_T>& b);
        template <typename _T>
        duint<_T> operator-(const duint<_T>& a, const duint<_T>& b);
        template <typename _T>
        duint<_T> operator*(const duint<_T>& a, const duint<_T>& b);
        template <typename _T>
        duint<_T> operator/(const duint<_T>& a, const _T& b);
        template <typename _T>
        duint<_T> operator/(const duint<_T>& a, const duint<_T>& b);

        template <typename _T>
        duint<_T> operator<<(const duint<_T>& a, unsigned s);
        template <typename _T>
        duint<_T> operator<<(const duint<_T>& a, int s);
        template <typename _T>
        duint<_T> operator>>(const duint<_T>& a, unsigned s);
        template <typename _T>
        duint<_T> operator>>(const duint<_T>& a, int s);

        template <typename _T>
        duint<_T>& operator+=(duint<_T>& , const duint<_T>& b);
        template <typename _T>
        duint<_T>& operator-=(duint<_T>& a, const duint<_T>& b);
        template <typename _T>
        duint<_T>& operator*=(duint<_T>& a, const duint<_T>& b);
        template <typename _T>
        duint<_T>& operator/=(duint<_T>& a, const duint<_T>& b);
        template <typename _T>
        duint<_T>& operator%=(duint<_T>& a, const duint<_T>& b);
        template <typename _T>
        duint<_T>& operator<<=(duint<_T>& a, unsigned s);
        template <typename _T>
        duint<_T>& operator>>=(duint<_T>& a, unsigned s);

	template <typename _T>
	bool operator<(const duint<_T>& a, const duint<_T>& b);
	template <typename _T>
	bool operator<=(const duint<_T>& a, const duint<_T>& b);
	template <typename _T>
	bool operator==(const duint<_T>& a, const duint<_T>& b);
	template <typename _T>
	bool operator!=(const duint<_T>& a, const duint<_T>& b);
	template <typename _T>
	bool operator>=(const duint<_T>& a, const duint<_T>& b);
	template <typename _T>
	bool operator>(const duint<_T>& a, const duint<_T>& b);

        template <class _T>
        std::pair<_T, _T> wide_mul(const _T& a, const _T& b);

        namespace impl {

                template <class _U>
                struct wide_umul {
                        // returns low part in first, high part in second
                        std::pair<_U, _U> operator()(const _U& a, const _U& b)
                                const;
                };

                template <class _S>
                struct wide_smul {
                        // returns low part in first, high part in second
                        std::pair<_S, _S> operator()(const _S& a, const _S& b)
                                const;
                };

		// specialisations for standard types.
		template <>
		struct wide_umul<std::uint8_t> {
			std::pair<std::uint8_t, std::uint8_t>
			operator()(const std::uint8_t a, const std::uint8_t b)
				const {
				std::uint16_t p(std::uint16_t(a)*b);
				std::uint8_t l(p);
				std::uint8_t h(p>>8);
				return std::make_pair(l, h);
			}
		};
		
		template <>
		struct wide_umul<std::uint16_t> {
			std::pair<std::uint16_t, std::uint16_t>
			operator()(const std::uint16_t a, const std::uint16_t b)
				const {
				std::uint32_t p(std::uint32_t(a)*b);
				std::uint16_t l(p);
				std::uint16_t h(p>>16);
				return std::make_pair(l, h);
			}
		};

		template <>
		struct wide_umul<std::uint32_t> {
			std::pair<std::uint32_t, std::uint32_t>
			operator()(const std::uint32_t a, const std::uint32_t b)
				const {
				std::uint64_t p(std::uint64_t(a)*b);
				std::uint32_t l(p);
				std::uint32_t h(p>>32);
				return std::make_pair(l, h);
			}
		};

		// specialisations for standard types.
		template <>
		struct wide_smul<std::int8_t> {
			std::pair<std::int8_t, std::int8_t>
			operator()(const std::int8_t a, const std::int8_t b)
				const {
				std::int16_t p(std::int16_t(a)*b);
				std::int8_t l(p);
				std::int8_t h(p>>8);
				return std::make_pair(l, h);
			}
		};
		
		template <>
		struct wide_smul<std::int16_t> {
			std::pair<std::int16_t, std::int16_t>
			operator()(const std::int16_t a, const std::int16_t b)
				const {
				std::int32_t p(std::int32_t(a)*b);
				std::int16_t l(p);
				std::int16_t h(p>>16);
				return std::make_pair(l, h);
			}
		};

		template <>
		struct wide_smul<std::int32_t> {
			std::pair<std::int32_t, std::int32_t>
			operator()(const std::int32_t a, const std::int32_t b)
				const {
				std::int64_t p(std::int64_t(a)*b);
				std::int32_t l(p);
				std::int32_t h(p>>32);
				return std::make_pair(l, h);
			}
		};
        }
	
        namespace impl {

                template <class _U, class _UHALF=_U>
                class udiv_2by1 {
		public:
			static 
			std::pair<_U, _U>
			d(const _U& u0, const _U& u1, const _U& v, _U* r);
			static _U
			g(const _U& uh, const _U& ul,  const _U& v, _U* r);
                };
        }
}

template <class _V>
inline
_V cftal::remainder(const _V& n, const _V& d, const _V& q)
{
        _V p(d* q);
        return n - p;
}

template <class _T>
unsigned cftal::lzcnt(const duint<_T>& a)
{
	unsigned res(a.h() == 0 ? 
		     lzcnt(a.l()) + duint<_T>::N2 :
		     lzcnt(a.h()));
	return res;
}

template <typename _T>
cftal::duint<_T> cftal::operator~(const duint<_T>& a)
{
	return duint<_T>(~a.l(),~a.h());
}

template <typename _T>
cftal::duint<_T> cftal::operator-(const duint<_T>& a)
{
	return duint<_T>(0) - a;
}

template <typename _T>
cftal::duint<_T> cftal::operator|(const duint<_T>& a, const duint<_T>& b)
{
	typename duint<_T>::type rl= a.l() | b.l();
	typename duint<_T>::type rh= a.h() | b.h();
	return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator&(const duint<_T>& a, const duint<_T>& b)
{
	typename duint<_T>::type rl= a.l() & b.l();
	typename duint<_T>::type rh= a.h() & b.h();
	return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator^(const duint<_T>& a, const duint<_T>& b)
{
	typename duint<_T>::type rl= a.l() ^ b.l();
	typename duint<_T>::type rh= a.h() ^ b.h();
	return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator+(const duint<_T>& a, const duint<_T>& b)
{
	typename duint<_T>::type rl= a.l() + b.l();
	typename duint<_T>::type rh= a.h() + b.h();
	rh += (rl < a.l() ? _T(1) : _T(0));
	return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator-(const duint<_T>& a, const duint<_T>& b)
{
	typename duint<_T>::type rl= a.l() - b.l();
	typename duint<_T>::type rh= a.h() - b.h();
	rh -= (a.l() < b.l() ? _T(1) : _T(0));
	return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator*(const duint<_T>& a, const duint<_T>& b)
{
	typedef typename duint<_T>::type type;
	typedef std::pair<type, type> pair_type;
	// [2^ 0, 2^N2 )
	pair_type al_bl(wide_mul(a.l(), b.l()));
	// [2^(N2/2),  2^(N2*3/2) )
	pair_type al_bh(wide_mul(a.l(), b.h()));
	pair_type ah_bl(wide_mul(a.h(), b.l()));
	// [2^N2, 2^N ) would be wide_mul(a.h(), b.h())
	// shift al_bh and ah_bl right by 2^(N2/2)
	duint<_T> s20(0, al_bh.first);
	duint<_T> s21(0, ah_bl.first);
	duint<_T> s0(al_bl.first, al_bl.second);
	duint<_T> r= s0 + s20 + s21;
	return r;
}

template <typename _T>
cftal::duint<_T> cftal::operator/(const duint<_T>& a, const _T& b)
{
	typedef impl::udiv_2by1<_T, _T> div_type;
	std::pair<_T, _T> pq(div_type::d(a.l(), a.h(), b, nullptr));
	duint<_T> q(pq.first, pq.second);
	return q;
}

template <typename _T>
cftal::duint<_T> cftal::operator/(const duint<_T>& a, const duint<_T>& b)
{
	typedef impl::udiv_2by1<duint<_T>, _T> div_type;
	std::pair<duint<_T>, duint<_T> > pq(div_type::d(a, 0, b, nullptr));
	return pq.first;
}

template <typename _T>
cftal::duint<_T> cftal::operator<<(const duint<_T>& a, unsigned s)
{
	typename duint<_T>::type rl;
	typename duint<_T>::type rh;
	if (s >= duint<_T>::N) {
		rl = rh = _T(0);
	} else if ( s>= duint<_T>::N2 ) {
		rl = _T(0);
		unsigned ss=s-duint<_T>::N2;
		rh = a.l() << ss;
	} else {
		// s < N2
		unsigned sr=duint<_T>::N2-s;
		typename duint<_T>::type t=a.l() >> sr;
		rl = a.l() << s;
		rh = (a.h() << s) | t;
	}
	return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator<<(const duint<_T>& a, int s)
{
	return a << unsigned(s);
}

template <typename _T>
cftal::duint<_T> cftal::operator>>(const duint<_T>& a, unsigned s)
{
	typename duint<_T>::type rl;
	typename duint<_T>::type rh;
	if (s >= duint<_T>::N) {
		rl = rh = _T(0);
	} else if ( s>= duint<_T>::N2 ) {
		rh = _T(0);
		unsigned ss= s- duint<_T>::N2;
		rl = a.h() >> ss;
	} else {
		// s < N2
		unsigned sr=duint<_T>::N2-s;
		typename duint<_T>::type t =a.h() << sr;
		rh = a.h() >> s;
		rl = (a.l() >> s) | t;
	}
	return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator>>(const duint<_T>& a, int s)
{
	return a >> unsigned(s);
}


template <typename _T>
cftal::duint<_T>& cftal::operator+=(duint<_T>& a, const duint<_T>& b)
{
	a = a + b;
	return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator-=(duint<_T>& a, const duint<_T>& b)
{
	a = a - b;
	return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator*=(duint<_T>& a, const duint<_T>& b)
{
	a = a * b;
	return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator<<=(duint<_T>& a, unsigned s)
{
	a= a << s;
	return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator>>=(duint<_T>& a, unsigned s)
{
	a= a >> s;
	return a;
}

template <typename _T>
bool cftal::operator<(const duint<_T>& a, const duint<_T>& b)
{
	return (a.h()< b.h()) || ((a.h()==b.h()) && (a.l() < b.l()));
}

template <typename _T>
bool cftal::operator<=(const duint<_T>& a, const duint<_T>& b)
{
	return (a.h()< b.h()) || ((a.h()==b.h()) && (a.l() <= b.l()));
}

template <typename _T>
bool cftal::operator==(const duint<_T>& a, const duint<_T>& b)
{
	return (a.h() == b.h()) && (a.l() == b.l());
}

template <typename _T>
bool cftal::operator!=(const duint<_T>& a, const duint<_T>& b)
{
	return (a.h() != b.h()) || (a.l() != b.l());
}

template <typename _T>
bool cftal::operator>=(const duint<_T>& a, const duint<_T>& b)
{
	return (a.h() > b.h()) || ((a.h()==b.h()) && (a.l() >= b.l()));
}

template <typename _T>
bool cftal::operator>(const duint<_T>& a, const duint<_T>& b)
{
	return (a.h() > b.h()) || ((a.h()==b.h()) && (a.l() > b.l()));
}

template <class _U>
std::pair<_U, _U>
cftal::impl::wide_umul<_U>::operator()(const _U& a, const _U& b)
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
        return std::make_pair(al_bl, ah_bh);
}

template <class _S>
std::pair<_S, _S>
cftal::impl::wide_smul<_S>::operator()(const _S& x, const _S& y)
        const
{
        enum {
                N = sizeof(_S)* 8
        };
        typedef typename std::make_unsigned<_S>::type _U;
        _U xu(x);
        _U yu(y);
        wide_umul<_U> m;
        std::pair<_U, _U> ur(m(xu, yu));
        // muluh(x,y) = mulsh(x,y) + and(x, xsign(y)) + and(y, xsign(x));
        // mulsh(x,y) = muluh(x,y) - and(x, xsign(y)) - and(y, xsign(x));
        _S xsign_x = x >> (N-1);
        _S xsign_y = y >> (N-1);
        _S h = _S(ur.second) - (x & xsign_y) - (y & xsign_x);
        _S l = _S(ur.first);
        return std::make_pair(l, h);
}

template <class _U, class _UHALF>
std::pair<_U, _U>
cftal::impl::udiv_2by1<_U, _UHALF>::
d(const _U& u0, const _U& u1, const _U& v, _U* rem)
{
	_U q1(0); _U q0(0);
	if (u1 >= v) {
		// j== 1
		_U r;
		q1= g(u1, 0, v, &r);
		// j== 0
		q0= g(u0, r, v, rem);
	} else {
		q0= g(u0, u1, v, rem);
	}
	return std::make_pair(q0, q1);
}

template <class _U, class _UHALF>
_U cftal::impl::udiv_2by1<_U, _UHALF>::
g(const _U& ul, const _U& uh, const _U& cv, _U* r)
{
#if 0
	enum {
		N = sizeof(_U)*8,
		N2 = N>>1
	};
#endif
	const unsigned N= sizeof(_U)*8;
	const unsigned N2= N>>1;
        // number base of the division
        const _U b= _U(1)<<N2;
        // mask out half of the bits of an _U
        const _U N2MSK= b - _U(1);
        // maximum possible u
        const _U U_MAX= ~_U(0);
        // Norm. divisor digits.
        _U un1, un0;
	// divisor digits.
	_UHALF vn1, vn0;
        // Quotient digits.
        _U q1, q0;
        // Dividend digit pairs.
        _U un32, un21, un10;
        // A remainder.
        _U rhat;
        // Shift amount for norm.
        unsigned s;
        _U v(cv);
        if (uh >= v) {
                // If overflow, set rem. to an impossible value,
                if (r != nullptr)
                        *r = U_MAX;
                // and return the largest possible quotient.
                return U_MAX;
        }
        s = lzcnt(v);               // 0 <= s <= N-1.
        if (s>0) {
                // Normalize divisor.
                v = v << s;
        }
        vn1 = v >> N2;       // Break divisor up into
        vn0 = v & N2MSK;     // two half digits

        if (s>0) {
                // Shift dividend left.
                un32 = (uh << s) | ((ul >> (N - s)) & (-_U(s) >> (N-1)));
                un10 = ul << s;
        } else {
                un32 = uh;
                un10 = ul;
        }

        // Break right half of dividend into two digits.
        un1 = un10 >> N2;
        un0 = un10 & N2MSK;

        q1 = un32/vn1;            // Compute the first
        rhat = un32 - q1*vn1;     // quotient digit, q1.

        while (q1 >= b || q1*vn0 > b*rhat + un1) {
                q1 = q1 - 1;
                rhat = rhat + vn1;
                if (rhat >= b)
                        break;
        }

        un21 = un32*b + un1 - q1*v;  // Multiply and subtract.

        q0 = un21/vn1;            // Compute the second
        rhat = un21 - q0*vn1;     // quotient digit, q0.

        while (q0 >= b || q0*vn0 > b*rhat + un0) {
                q0 = q0 - 1;
                rhat = rhat + vn1;
                if (rhat >= b)
                        break;
        }
        if (r != nullptr) {
                // If remainder is wanted, return it.
                *r = (un21*b + un0 - q0*v) >> s;
        }
        return q1*b + q0;
}

template <class _T>
inline
std::pair<_T, _T>
cftal::wide_mul(const _T& x, const _T& y)
{
        typedef typename std::conditional<std::is_signed<_T>::value,
		impl::wide_smul<_T>,
		impl::wide_umul<_T> >::type
                mul_type;
        mul_type m;
        return m(x, y);
}

// Local variables:
// mode: c++
// end:
#endif
