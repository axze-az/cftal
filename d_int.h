#if !defined (__CFTAL_D_INT_H__)
#define __CFTAL_D_INT_H__ 1

#include <cftal/config.h>
#include <cftal/mul_div.h>
#include <type_traits>

namespace cftal {

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
		const type& uh() const {
			return h();
		}
                void l(const type& v) { 
			_l = v; 
		}
                void h(const type& v) { 
			_h = v; 
		}
		void uh(const type& v) {
			h(v);
		}
		explicit operator _T() const {
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
	const duint<_T> operator+(const duint<_T>& a);
	template <typename _T>
	bool operator!(const duint<_T>& a);

        template <typename _T>
        duint<_T> operator|(const duint<_T>& a, const duint<_T>& b);
        template <typename _T>
        duint<_T> operator|(const duint<_T>& a, const _T& b);
        template <typename _T>
        duint<_T> operator|(const _T& a, const duint<_T>& b);

        template <typename _T>
        duint<_T> operator&(const duint<_T>& a, const duint<_T>& b);
        template <typename _T>
        duint<_T> operator&(const duint<_T>& a, const _T& b);
        template <typename _T>
        duint<_T> operator&(const _T& a, const duint<_T>& b);

        template <typename _T>
        duint<_T> operator^(const duint<_T>& a, const duint<_T>& b);
        template <typename _T>
        duint<_T> operator^(const duint<_T>& a, const _T& b);
        template <typename _T>
        duint<_T> operator^(const _T& a, const duint<_T>& b);

        template <typename _T>
        bool operator&&(const duint<_T>& a, const duint<_T>& b);
        template <typename _T>
        bool operator&&(const duint<_T>& a, const _T& b);
        template <typename _T>
        bool operator&&(const _T& a, const duint<_T>& b);

        template <typename _T>
        duint<_T> operator+(const duint<_T>& a, const duint<_T>& b);
        template <typename _T>
        duint<_T> operator+(const duint<_T>& a, const _T& b);
        template <typename _T>
        duint<_T> operator+(const _T& a, const duint<_T>& b);

        template <typename _T>
        duint<_T> operator-(const duint<_T>& a, const duint<_T>& b);
        template <typename _T>
        duint<_T> operator-(const duint<_T>& a, const _T& b);
        template <typename _T>
        duint<_T> operator-(const _T& a, const duint<_T>& b);

        template <typename _T>
        duint<_T> operator*(const duint<_T>& a, const duint<_T>& b);
        template <typename _T>
        duint<_T> operator*(const duint<_T>& a, const _T& b);
        template <typename _T>
        duint<_T> operator*(const _T& a, const duint<_T>& b);


        template <typename _T>
        duint<_T> operator/(const duint<_T>& a, const _T& b);
        template <typename _T>
        duint<_T> operator/(const duint<_T>& a, const duint<_T>& b);
        template <typename _T>
        duint<_T> operator/(const _T& a, const duint<_T>& b);

        template <typename _T>
        duint<_T> operator%(const duint<_T>& a, const duint<_T>& b);
        template <typename _T>
        duint<_T> operator%(const duint<_T>& a, const _T& b);
        template <typename _T>
        duint<_T> operator%(const _T& a, const duint<_T>& b);

        template <typename _T>
        duint<_T> operator<<(const duint<_T>& a, unsigned s);
        template <typename _T>
        duint<_T> operator<<(const duint<_T>& a, int s);
        template <typename _T>
        duint<_T> operator>>(const duint<_T>& a, unsigned s);
        template <typename _T>
        duint<_T> operator>>(const duint<_T>& a, int s);

        template <typename _T>
        duint<_T>& operator|=(duint<_T>& , const duint<_T>& b);
        template <typename _T>
        duint<_T>& operator|=(duint<_T>& , const _T& b);

        template <typename _T>
        duint<_T>& operator&=(duint<_T>& , const duint<_T>& b);
        template <typename _T>
        duint<_T>& operator&=(duint<_T>& , const _T& b);

        template <typename _T>
        duint<_T>& operator^=(duint<_T>& , const duint<_T>& b);
        template <typename _T>
        duint<_T>& operator^=(duint<_T>& , const _T& b);

        template <typename _T>
        duint<_T>& operator+=(duint<_T>& , const duint<_T>& b);
        template <typename _T>
        duint<_T>& operator+=(duint<_T>& , const _T& b);

        template <typename _T>
        duint<_T>& operator-=(duint<_T>& a, const duint<_T>& b);
        template <typename _T>
        duint<_T>& operator-=(duint<_T>& a, const _T& b);

        template <typename _T>
        duint<_T>& operator*=(duint<_T>& a, const duint<_T>& b);
        template <typename _T>
        duint<_T>& operator*=(duint<_T>& a, const _T& b);

        template <typename _T>
        duint<_T>& operator/=(duint<_T>& a, const duint<_T>& b);
        template <typename _T>
        duint<_T>& operator/=(duint<_T>& a, const duint<_T>& b);

        template <typename _T>
        duint<_T>& operator%=(duint<_T>& a, const duint<_T>& b);
        template <typename _T>
        duint<_T>& operator%=(duint<_T>& a, const _T& b);

        template <typename _T>
        duint<_T>& operator<<=(duint<_T>& a, unsigned s);
        template <typename _T>
        duint<_T>& operator<<=(duint<_T>& a, int s);
        template <typename _T>
        duint<_T>& operator>>=(duint<_T>& a, unsigned s);
        template <typename _T>
        duint<_T>& operator>>=(duint<_T>& a, int s);

	template <typename _T>
	bool operator<(const duint<_T>& a, const duint<_T>& b);
	template <typename _T>
	bool operator<(const _T& a, const duint<_T>& b);
	template <typename _T>
	bool operator<(const duint<_T>& a, const _T& b);

	template <typename _T>
	bool operator<=(const duint<_T>& a, const duint<_T>& b);
	template <typename _T>
	bool operator<=(const _T& a, const duint<_T>& b);
	template <typename _T>
	bool operator<=(const duint<_T>& a, const _T& b);

	template <typename _T>
	bool operator==(const duint<_T>& a, const duint<_T>& b);
	template <typename _T>
	bool operator==(const _T& a, const duint<_T>& b);
	template <typename _T>
	bool operator==(const duint<_T>& a, const _T& b);

	template <typename _T>
	bool operator!=(const duint<_T>& a, const duint<_T>& b);
	template <typename _T>
	bool operator!=(const _T& a, const duint<_T>& b);
	template <typename _T>
	bool operator!=(const duint<_T>& a, const _T& b);

	template <typename _T>
	bool operator>=(const duint<_T>& a, const duint<_T>& b);
	template <typename _T>
	bool operator>=(const _T& a, const duint<_T>& b);
	template <typename _T>
	bool operator>=(const duint<_T>& a, const _T& b);

	template <typename _T>
	bool operator>(const duint<_T>& a, const duint<_T>& b);
	template <typename _T>
	bool operator>(const _T& a, const duint<_T>& b);
	template <typename _T>
	bool operator>(const duint<_T>& a, const _T& b);



}

namespace std {

	template <class _T>
	struct is_signed<cftal::duint<_T> > 
		: public is_signed<_T> { };
	template <class _T>
	struct is_unsigned<cftal::duint<_T> > 
		: public is_unsigned<_T> { };
	
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
	return _T(0) - a;
}

template <typename _T>
const cftal::duint<_T>& cftal::operator+(const duint<_T>& a)
{
	return a;
}

template <typename _T>
bool cftal::operator!(const duint<_T>& a)
{
	return a != _T(0);
}

template <typename _T>
cftal::duint<_T> cftal::operator|(const duint<_T>& a, const duint<_T>& b)
{
	typename duint<_T>::type rl= a.l() | b.l();
	typename duint<_T>::type rh= a.h() | b.h();
	return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator|(const duint<_T>& a, const _T& b)
{
	typename duint<_T>::type rl= a.l() | b;
	typename duint<_T>::type rh= a.h();
	return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator|(const _T& a, const duint<_T>& b)
{
	return b | a;
}

template <typename _T>
cftal::duint<_T> cftal::operator&(const duint<_T>& a, const duint<_T>& b)
{
	typename duint<_T>::type rl= a.l() & b.l();
	typename duint<_T>::type rh= a.h() & b.h();
	return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator&(const duint<_T>& a, const _T& b)
{
	typename duint<_T>::type rl= a.l() & b;
	typename duint<_T>::type rh= 0;
	return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator&(const _T& a, const duint<_T>& b)
{
	return b & a;
}

template <typename _T>
bool cftal::operator&&(const duint<_T>& a, const duint<_T>& b)
{
	return (a != _T(0)) && (b != _T(0));
}

template <typename _T>
bool cftal::operator&&(const duint<_T>& a, const _T& b)
{
	return (a != _T(0)) && (b != _T(0));
}

template <typename _T>
bool cftal::operator&&(const _T& a, const duint<_T>& b)
{
	return b && a;
}

template <typename _T>
cftal::duint<_T> cftal::operator^(const duint<_T>& a, const duint<_T>& b)
{
	typename duint<_T>::type rl= a.l() ^ b.l();
	typename duint<_T>::type rh= a.h() ^ b.h();
	return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator^(const duint<_T>& a, const _T& b)
{
	typename duint<_T>::type rl= a.l() ^ b;
	typename duint<_T>::type rh= a.h() ^ 0;
	return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator^(const _T& a, const duint<_T>& b)
{
	return b ^ a;
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
cftal::duint<_T> cftal::operator+(const duint<_T>& a, const _T& b)
{
	typename duint<_T>::type rl= a.l() + b;
	typename duint<_T>::type rh= a.h();
	rh += (rl < a.l() ? _T(1) : _T(0));
	return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator+(const _T& a, const duint<_T>& b)
{
	return b+a;
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
cftal::duint<_T> cftal::operator-(const duint<_T>& a, const _T& b)
{
	typename duint<_T>::type rl= a.l() - b;
	typename duint<_T>::type rh= a.h();
	rh -= (a.l() < b ? _T(1) : _T(0));
	return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator-(const _T& a, const duint<_T>& b)
{
	typename duint<_T>::type rl= a - b.l();
	typename duint<_T>::type rh= -b.h();
	rh -= (a < b.l() ? _T(1) : _T(0));
	return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator*(const duint<_T>& a, const duint<_T>& b)
{
	typedef typename duint<_T>::type type;
	typedef std::pair<type, type> pair_type;
	// [2^ 0, 2^N2 )
	pair_type al_bl(wide_mul(a.l(), b.l()));
	// [2^(N2/2),  2^(N2*2/2) )
	type al_bh(a.l() * b.h());
	type ah_bl(a.h() * b.l());
	// shift al_bh and ah_bl right by 2^(N2/2)
	duint<_T> s20(0, al_bh);
	duint<_T> s21(0, ah_bl);
	duint<_T> s0(al_bl.first, al_bl.second);
	duint<_T> r= s0 + s20 + s21;
	return r;
}

template <typename _T>
cftal::duint<_T> cftal::operator*(const duint<_T>& a, const _T& b)
{
	typedef typename duint<_T>::type type;
	typedef std::pair<type, type> pair_type;
	// [2^ 0, 2^N2 )
	pair_type al_b(wide_mul(a.l(), b));
	// [2^(N2/2),  2^(N2*2/2) )
	type ah_b(a.h() * b);
	// shift al_bh and ah_bl right by 2^(N2/2)
	duint<_T> s21(0, ah_b);
	duint<_T> s0(al_b.first, al_b.second);
	duint<_T> r= s0 + s21;
	return r;
}

template <typename _T>
cftal::duint<_T> cftal::operator*(const _T& a, const duint<_T>& b)
{
	return b* a;
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
cftal::duint<_T> cftal::operator/(const _T& a, const duint<_T>& b)
{
	duint<_T> ad(a);
	return ad / b;
}

template <typename _T>
cftal::duint<_T> cftal::operator%(const duint<_T>& a, const _T& b)
{
	duint<_T> q(a/b);
	return remainder(a, duint<_T>(b), q);
}

template <typename _T>
cftal::duint<_T> cftal::operator%(const duint<_T>& a, const duint<_T>& b)
{
	duint<_T> q(a/b);
	return remainder(a, b, q);
}

template <typename _T>
cftal::duint<_T> cftal::operator%(const _T& a, const duint<_T>& b)
{
	duint<_T> ad(a), q(ad/b);
	return remainder(ad, b, q);
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
cftal::duint<_T>& cftal::operator|=(duint<_T>& a, const duint<_T>& b)
{
	a = a | b;
	return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator|=(duint<_T>& a, const _T& b)
{
	a = a | b;
	return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator&=(duint<_T>& a, const duint<_T>& b)
{
	a = a & b;
	return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator&=(duint<_T>& a, const _T& b)
{
	a = a & b;
	return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator^=(duint<_T>& a, const duint<_T>& b)
{
	a = a ^ b;
	return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator^=(duint<_T>& a, const _T& b)
{
	a = a ^ b;
	return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator+=(duint<_T>& a, const duint<_T>& b)
{
	a = a + b;
	return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator+=(duint<_T>& a, const _T& b)
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
cftal::duint<_T>& cftal::operator-=(duint<_T>& a, const _T& b)
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
cftal::duint<_T>& cftal::operator*=(duint<_T>& a, const _T& b)
{
	a = a * b;
	return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator/=(duint<_T>& a, const duint<_T>& b)
{
	a = a / b;
	return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator/=(duint<_T>& a, const _T& b)
{
	a = a / b;
	return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator%=(duint<_T>& a, const duint<_T>& b)
{
	a = a % b;
	return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator%=(duint<_T>& a, const _T& b)
{
	a = a % b;
	return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator<<=(duint<_T>& a, unsigned s)
{
	a= a << s;
	return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator<<=(duint<_T>& a, int s)
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
cftal::duint<_T>& cftal::operator>>=(duint<_T>& a, int s)
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
bool cftal::operator<(const _T& a, const duint<_T>& b)
{
	return (b.h()==_T(0)) && (a < b.l());
}

template <typename _T>
bool cftal::operator<(const duint<_T>& a, const _T& b)
{
	return (a.h()==_T(0)) && (a.l() < b);
}

template <typename _T>
bool cftal::operator<=(const duint<_T>& a, const duint<_T>& b)
{
	return (a.h()< b.h()) || ((a.h()==b.h()) && (a.l() <= b.l()));
}

template <typename _T>
bool cftal::operator<=(const _T& a, const duint<_T>& b)
{
	return (b.h()==_T(0)) && (a <= b.l());
}

template <typename _T>
bool cftal::operator<=(const duint<_T>& a, const _T& b)
{
	return (a.h()==_T(0)) && (a.l() <= b);
}

template <typename _T>
bool cftal::operator==(const duint<_T>& a, const duint<_T>& b)
{
	return (a.h() == b.h()) && (a.l() == b.l());
}

template <typename _T>
bool cftal::operator==(const _T& a, const duint<_T>& b)
{
	return (b.h()==_T(0)) && (a == b.l());
}

template <typename _T>
bool cftal::operator==(const duint<_T>& a, const _T& b)
{
	return (a.h()==_T(0)) && (a.l() == b);
}

template <typename _T>
bool cftal::operator!=(const duint<_T>& a, const duint<_T>& b)
{
	return (a.h() != b.h()) || (a.l() != b.l());
}

template <typename _T>
bool cftal::operator!=(const _T& a, const duint<_T>& b)
{
	return (b.h()!=_T(0)) || (a != b.l());
}

template <typename _T>
bool cftal::operator!=(const duint<_T>& a, const _T& b)
{
	return (a.h()!=_T(0)) || (a.l() != b);
}

template <typename _T>
bool cftal::operator>=(const duint<_T>& a, const duint<_T>& b)
{
	return (a.h() > b.h()) || ((a.h()==b.h()) && (a.l() >= b.l()));
}

template <typename _T>
bool cftal::operator>=(const _T& a, const duint<_T>& b)
{
	return (b.h()==_T(0)) && (a >= b.l());
}

template <typename _T>
bool cftal::operator>=(const duint<_T>& a, const _T& b)
{
	return (a.h()>_T(0)) || (a.l() >= b);
}

template <typename _T>
bool cftal::operator>(const duint<_T>& a, const duint<_T>& b)
{
	return (a.h() > b.h()) || ((a.h()==b.h()) && (a.l() > b.l()));
}

template <typename _T>
bool cftal::operator>(const _T& a, const duint<_T>& b)
{
	return (b.h()==_T(0)) && (a > b.l());
}

template <typename _T>
bool cftal::operator>(const duint<_T>& a, const _T& b)
{
	return (a.h()>_T(0)) || (a.l() > b);
}

// Local variables:
// mode: c++
// end:
#endif
