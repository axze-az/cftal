#if !defined (__CFTAL_D_INT_H__)
#define __CFTAL_D_INT_H__ 1

#include <cftal/config.h>
#include <cftal/mul_div.h>
#include <type_traits>

namespace cftal {

	// double unsigned integer
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
		const type& uh() const {
			return _h;
		}
                void l(const type& v) { 
			_l = v; 
		}
		void uh(const type& v) {
			_h = v;
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

	// double signed integer
        template <typename _T>
        class dint : public duint<typename std::make_unsigned<_T>::type> {
        public:
                typedef _T type;
		typedef typename std::make_unsigned<_T>::type utype;
		typedef duint<utype> base_type;
                dint() : base_type() {
		}
		dint(const type& vl) : base_type(vl, 
						 vl < _T(0) ? 
						 ~_T(0) : _T(0)) {
		}
                dint(const utype& vl, const type& vh) : base_type(vl,vh) {
		}
		dint(const base_type& b) : base_type(b) {
		}
		// l is inherited from h.
                const type& sh() const { 
			const utype& _uh= base_type::uh();
			const type* ph= reinterpret_cast<const type*>(&_uh);
			return *ph;
		}
		explicit operator _T() const {
			return type(this->l());
		}
        };

	template <typename _T>
	dint<_T> operator~(const dint<_T>& a);
	template <typename _T>
	dint<_T> operator-(const dint<_T>& a);
	template <typename _T>
	const dint<_T> operator+(const dint<_T>& a);
	template <typename _T>
	bool operator!(const dint<_T>& a);

        template <typename _T>
        dint<_T> operator|(const dint<_T>& a, const dint<_T>& b);
        template <typename _T>
        dint<_T> operator|(const dint<_T>& a, const _T& b);
        template <typename _T>
        dint<_T> operator|(const _T& a, const dint<_T>& b);

        template <typename _T>
        dint<_T> operator&(const dint<_T>& a, const dint<_T>& b);
        template <typename _T>
        dint<_T> operator&(const dint<_T>& a, const _T& b);
        template <typename _T>
        dint<_T> operator&(const _T& a, const dint<_T>& b);

        template <typename _T>
        dint<_T> operator^(const dint<_T>& a, const dint<_T>& b);
        template <typename _T>
        dint<_T> operator^(const dint<_T>& a, const _T& b);
        template <typename _T>
        dint<_T> operator^(const _T& a, const dint<_T>& b);

        template <typename _T>
        bool operator&&(const dint<_T>& a, const dint<_T>& b);
        template <typename _T>
        bool operator&&(const dint<_T>& a, const _T& b);
        template <typename _T>
        bool operator&&(const _T& a, const dint<_T>& b);

        template <typename _T>
        dint<_T> operator+(const dint<_T>& a, const dint<_T>& b);
        template <typename _T>
        dint<_T> operator+(const dint<_T>& a, const _T& b);
        template <typename _T>
        dint<_T> operator+(const _T& a, const dint<_T>& b);

        template <typename _T>
        dint<_T> operator-(const dint<_T>& a, const dint<_T>& b);
        template <typename _T>
        dint<_T> operator-(const dint<_T>& a, const _T& b);
        template <typename _T>
        dint<_T> operator-(const _T& a, const dint<_T>& b);

        template <typename _T>
        dint<_T> operator*(const dint<_T>& a, const dint<_T>& b);
        template <typename _T>
        dint<_T> operator*(const dint<_T>& a, const _T& b);
        template <typename _T>
        dint<_T> operator*(const _T& a, const dint<_T>& b);

        template <typename _T>
        dint<_T> operator/(const dint<_T>& a, const _T& b);
        template <typename _T>
        dint<_T> operator/(const dint<_T>& a, const dint<_T>& b);
        template <typename _T>
        dint<_T> operator/(const _T& a, const dint<_T>& b);

        template <typename _T>
        dint<_T> operator%(const dint<_T>& a, const dint<_T>& b);
        template <typename _T>
        dint<_T> operator%(const dint<_T>& a, const _T& b);
        template <typename _T>
        dint<_T> operator%(const _T& a, const dint<_T>& b);

        template <typename _T>
        dint<_T> operator<<(const dint<_T>& a, unsigned s);
        template <typename _T>
        dint<_T> operator<<(const dint<_T>& a, int s);
        template <typename _T>
        dint<_T> operator>>(const dint<_T>& a, unsigned s);
        template <typename _T>
        dint<_T> operator>>(const dint<_T>& a, int s);

        template <typename _T>
        dint<_T>& operator|=(dint<_T>& , const dint<_T>& b);
        template <typename _T>
        dint<_T>& operator|=(dint<_T>& , const _T& b);

        template <typename _T>
        dint<_T>& operator&=(dint<_T>& , const dint<_T>& b);
        template <typename _T>
        dint<_T>& operator&=(dint<_T>& , const _T& b);

        template <typename _T>
        dint<_T>& operator^=(dint<_T>& , const dint<_T>& b);
        template <typename _T>
        dint<_T>& operator^=(dint<_T>& , const _T& b);

        template <typename _T>
        dint<_T>& operator+=(dint<_T>& , const dint<_T>& b);
        template <typename _T>
        dint<_T>& operator+=(dint<_T>& , const _T& b);

        template <typename _T>
        dint<_T>& operator-=(dint<_T>& a, const dint<_T>& b);
        template <typename _T>
        dint<_T>& operator-=(dint<_T>& a, const _T& b);

        template <typename _T>
        dint<_T>& operator*=(dint<_T>& a, const dint<_T>& b);
        template <typename _T>
        dint<_T>& operator*=(dint<_T>& a, const _T& b);

        template <typename _T>
        dint<_T>& operator/=(dint<_T>& a, const dint<_T>& b);
        template <typename _T>
        dint<_T>& operator/=(dint<_T>& a, const dint<_T>& b);

        template <typename _T>
        dint<_T>& operator%=(dint<_T>& a, const dint<_T>& b);
        template <typename _T>
        dint<_T>& operator%=(dint<_T>& a, const _T& b);

        template <typename _T>
        dint<_T>& operator<<=(dint<_T>& a, unsigned s);
        template <typename _T>
        dint<_T>& operator<<=(dint<_T>& a, int s);
        template <typename _T>
        dint<_T>& operator>>=(dint<_T>& a, unsigned s);
        template <typename _T>
        dint<_T>& operator>>=(dint<_T>& a, int s);

	template <typename _T>
	bool operator<(const dint<_T>& a, const dint<_T>& b);
	template <typename _T>
	bool operator<(const _T& a, const dint<_T>& b);
	template <typename _T>
	bool operator<(const dint<_T>& a, const _T& b);

	template <typename _T>
	bool operator<=(const dint<_T>& a, const dint<_T>& b);
	template <typename _T>
	bool operator<=(const _T& a, const dint<_T>& b);
	template <typename _T>
	bool operator<=(const dint<_T>& a, const _T& b);

	template <typename _T>
	bool operator==(const dint<_T>& a, const dint<_T>& b);
	template <typename _T>
	bool operator==(const _T& a, const dint<_T>& b);
	template <typename _T>
	bool operator==(const dint<_T>& a, const _T& b);

	template <typename _T>
	bool operator!=(const dint<_T>& a, const dint<_T>& b);
	template <typename _T>
	bool operator!=(const _T& a, const dint<_T>& b);
	template <typename _T>
	bool operator!=(const dint<_T>& a, const _T& b);

	template <typename _T>
	bool operator>=(const dint<_T>& a, const dint<_T>& b);
	template <typename _T>
	bool operator>=(const _T& a, const dint<_T>& b);
	template <typename _T>
	bool operator>=(const dint<_T>& a, const _T& b);

	template <typename _T>
	bool operator>(const dint<_T>& a, const dint<_T>& b);
	template <typename _T>
	bool operator>(const _T& a, const dint<_T>& b);
	template <typename _T>
	bool operator>(const dint<_T>& a, const _T& b);
}

namespace std {

	template <class _T>
	struct is_signed<cftal::duint<_T> > 
		: public is_signed<_T> { };
	template <class _T>
	struct is_unsigned<cftal::duint<_T> > 
		: public is_unsigned<_T> { };
	template <class _T>
	struct make_signed<cftal::duint<_T> > {
		typedef cftal::dint<_T> type;
	};
	template <class _T>
	struct make_unsigned<cftal::duint<_T> > {
		typedef cftal::duint<_T> type;
	};

	template <class _T>
	struct is_signed<cftal::dint<_T> > 
		: public is_signed<_T> { };
	template <class _T>
	struct is_unsigned<cftal::dint<_T> > 
		: public is_unsigned<_T> { };
	template <class _T>
	struct make_signed<cftal::dint<_T> > {
		typedef cftal::dint<_T> type;
	};
	template <class _T>
	struct make_unsigned<cftal::dint<_T> > {
		typedef cftal::duint<_T> type;
	};
}

namespace cftal {

	namespace impl {

		template <class _T>
		struct sign {
			static 
			bool get(const _T& a) {
				typename std::make_signed<_T>::type s(a);
				return s < 0 ? true : false;
			}
		};

		template <class _T>
		struct sign<duint<_T> > {
			static
			bool get(const duint<_T>& a) {
				return sign<_T>::get(a.uh());
			}
		};

		template <class _T>
		struct sign<dint<_T> > {
			static
			bool get(const dint<_T>& a) {
				return sign<_T>::get(a.uh());
			}
		};

		template <class _T>
		bool get_sign(const _T& a) 
		{
			return sign<_T>::get(a);
		}
	}
}

// duint<_T> implementation
template <class _T>
unsigned cftal::lzcnt(const duint<_T>& a)
{
	unsigned res(a.uh() == 0 ? 
		     lzcnt(a.l()) + duint<_T>::N2 :
		     lzcnt(a.uh()));
	return res;
}

template <typename _T>
cftal::duint<_T> cftal::operator~(const duint<_T>& a)
{
	return duint<_T>(~a.l(),~a.uh());
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
	typename duint<_T>::type rh= a.uh() | b.uh();
	return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator|(const duint<_T>& a, const _T& b)
{
	typename duint<_T>::type rl= a.l() | b;
	typename duint<_T>::type rh= a.uh();
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
	typename duint<_T>::type rh= a.uh() & b.uh();
	return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator&(const duint<_T>& a, const _T& b)
{
	typename duint<_T>::type rl= a.l() & b;
	typename duint<_T>::type rh= _T(0);
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
	typename duint<_T>::type rh= a.uh() ^ b.uh();
	return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator^(const duint<_T>& a, const _T& b)
{
	typename duint<_T>::type rl= a.l() ^ b;
	typename duint<_T>::type rh= a.uh() ^ _T(0);
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
	typename duint<_T>::type rh= a.uh() + b.uh();
	rh += (rl < a.l() ? _T(1) : _T(0));
	return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator+(const duint<_T>& a, const _T& b)
{
	typename duint<_T>::type rl= a.l() + b;
	typename duint<_T>::type rh= a.uh();
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
	typename duint<_T>::type rh= a.uh() - b.uh();
	rh -= (a.l() < b.l() ? _T(1) : _T(0));
	return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator-(const duint<_T>& a, const _T& b)
{
	typename duint<_T>::type rl= a.l() - b;
	typename duint<_T>::type rh= a.uh();
	rh -= (a.l() < b ? _T(1) : _T(0));
	return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator-(const _T& a, const duint<_T>& b)
{
	typename duint<_T>::type rl= a - b.l();
	typename duint<_T>::type rh= -b.uh();
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
	type al_bh(a.l() * b.uh());
	type ah_bl(a.uh() * b.l());
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
	type ah_b(a.uh() * b);
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
	std::pair<_T, _T> pq(div_type::d(a.l(), a.uh(), b, nullptr));
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
		rh = (a.uh() << s) | t;
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
		rl = a.uh() >> ss;
	} else {
		// s < N2
		unsigned sr=duint<_T>::N2-s;
		typename duint<_T>::type t =a.uh() << sr;
		rh = a.uh() >> s;
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
	return (a.uh()< b.uh()) || ((a.uh()==b.uh()) && (a.l() < b.l()));
}

template <typename _T>
bool cftal::operator<(const _T& a, const duint<_T>& b)
{
	return (b.uh()==_T(0)) && (a < b.l());
}

template <typename _T>
bool cftal::operator<(const duint<_T>& a, const _T& b)
{
	return (a.uh()==_T(0)) && (a.l() < b);
}

template <typename _T>
bool cftal::operator<=(const duint<_T>& a, const duint<_T>& b)
{
	return (a.uh()< b.uh()) || ((a.uh()==b.uh()) && (a.l() <= b.l()));
}

template <typename _T>
bool cftal::operator<=(const _T& a, const duint<_T>& b)
{
	return (b.uh()==_T(0)) && (a <= b.l());
}

template <typename _T>
bool cftal::operator<=(const duint<_T>& a, const _T& b)
{
	return (a.uh()==_T(0)) && (a.l() <= b);
}

template <typename _T>
bool cftal::operator==(const duint<_T>& a, const duint<_T>& b)
{
	return (a.uh() == b.uh()) && (a.l() == b.l());
}

template <typename _T>
bool cftal::operator==(const _T& a, const duint<_T>& b)
{
	return (b.uh()==_T(0)) && (a == b.l());
}

template <typename _T>
bool cftal::operator==(const duint<_T>& a, const _T& b)
{
	return (a.uh()==_T(0)) && (a.l() == b);
}

template <typename _T>
bool cftal::operator!=(const duint<_T>& a, const duint<_T>& b)
{
	return (a.uh() != b.uh()) || (a.l() != b.l());
}

template <typename _T>
bool cftal::operator!=(const _T& a, const duint<_T>& b)
{
	return (b.uh()!=_T(0)) || (a != b.l());
}

template <typename _T>
bool cftal::operator!=(const duint<_T>& a, const _T& b)
{
	return (a.uh()!=_T(0)) || (a.l() != b);
}

template <typename _T>
bool cftal::operator>=(const duint<_T>& a, const duint<_T>& b)
{
	return (a.uh() > b.uh()) || ((a.uh()==b.uh()) && (a.l() >= b.l()));
}

template <typename _T>
bool cftal::operator>=(const _T& a, const duint<_T>& b)
{
	return (b.uh()==_T(0)) && (a >= b.l());
}

template <typename _T>
bool cftal::operator>=(const duint<_T>& a, const _T& b)
{
	return (a.uh()>_T(0)) || (a.l() >= b);
}

template <typename _T>
bool cftal::operator>(const duint<_T>& a, const duint<_T>& b)
{
	return (a.uh() > b.uh()) || ((a.uh()==b.uh()) && (a.l() > b.l()));
}

template <typename _T>
bool cftal::operator>(const _T& a, const duint<_T>& b)
{
	return (b.uh()==_T(0)) && (a > b.l());
}

template <typename _T>
bool cftal::operator>(const duint<_T>& a, const _T& b)
{
	return (a.uh()>_T(0)) || (a.l() > b);
}

// dint<_T> implementation
template <typename _T>
cftal::dint<_T> cftal::operator~(const dint<_T>& a)
{
	return ~ static_cast<const typename dint<_T>::base_type &>(a);
}

template <typename _T>
cftal::dint<_T> cftal::operator-(const dint<_T>& a)
{
	return - static_cast<const typename dint<_T>::base_type &>(a);
}

template <typename _T>
const cftal::dint<_T>& cftal::operator+(const dint<_T>& a)
{
	return a;
}

template <typename _T>
bool cftal::operator!(const dint<_T>& a)
{
	return ! static_cast<const typename dint<_T>::base_type &>(a);
}

template <typename _T>
cftal::dint<_T> cftal::operator|(const dint<_T>& a, const dint<_T>& b)
{
	typename dint<_T>::utype rl= a.l() | b.l();
	typename dint<_T>::type rh= a.sh() | b.sh();
	return dint<_T>(rl, rh);
}

template <typename _T>
cftal::dint<_T> cftal::operator|(const dint<_T>& a, const _T& b)
{
	typename dint<_T>::utype rl= a.l() | b;
	typename dint<_T>::utype rh= a.sh();
	return dint<_T>(rl, rh);
}

template <typename _T>
cftal::dint<_T> cftal::operator|(const _T& a, const dint<_T>& b)
{
	return b | a;
}

template <typename _T>
cftal::dint<_T> cftal::operator&(const dint<_T>& a, const dint<_T>& b)
{
	typename dint<_T>::utype rl= a.l() & b.l();
	typename dint<_T>::type rh= a.sh() & b.sh();
	return dint<_T>(rl, rh);
}

template <typename _T>
cftal::dint<_T> cftal::operator&(const dint<_T>& a, const _T& b)
{
	typename dint<_T>::utype rl= a.l() & b;
	typename dint<_T>::type rh= _T(0);
	return dint<_T>(rl, rh);
}

template <typename _T>
cftal::dint<_T> cftal::operator&(const _T& a, const dint<_T>& b)
{
	return b & a;
}

template <typename _T>
bool cftal::operator&&(const dint<_T>& a, const dint<_T>& b)
{
	return (a != _T(0)) && (b != _T(0));
}

template <typename _T>
bool cftal::operator&&(const dint<_T>& a, const _T& b)
{
	return (a != _T(0)) && (b != _T(0));
}

template <typename _T>
bool cftal::operator&&(const _T& a, const dint<_T>& b)
{
	return b && a;
}

template <typename _T>
cftal::dint<_T> cftal::operator^(const dint<_T>& a, const dint<_T>& b)
{
	typename dint<_T>::utype rl= a.l() ^ b.l();
	typename dint<_T>::utype rh= a.uh() ^ b.uh();
	return dint<_T>(rl, rh);
}

template <typename _T>
cftal::dint<_T> cftal::operator^(const dint<_T>& a, const _T& b)
{
	typename dint<_T>::type rl= a.l() ^ b;
	typename dint<_T>::type rh= a.uh() ^ 0;
	return dint<_T>(rl, rh);
}

template <typename _T>
cftal::dint<_T> cftal::operator^(const _T& a, const dint<_T>& b)
{
	return b ^ a;
}


template <typename _T>
cftal::dint<_T> cftal::operator+(const dint<_T>& a, const dint<_T>& b)
{
	typedef typename dint<_T>::base_type du_t;
	return static_cast<const du_t&>(a) +
		static_cast<const du_t&>(b);
}

template <typename _T>
cftal::dint<_T> cftal::operator+(const dint<_T>& a, const _T& b)
{
	return a + dint<_T>(b);
}

template <typename _T>
cftal::dint<_T> cftal::operator+(const _T& a, const dint<_T>& b)
{
	return dint<_T>(a) + b;
}

template <typename _T>
cftal::dint<_T> cftal::operator-(const dint<_T>& a, const dint<_T>& b)
{
	typedef typename dint<_T>::base_type du_t;
	return static_cast<const du_t&>(a) -
		static_cast<const du_t&>(b);
}

template <typename _T>
cftal::dint<_T> cftal::operator-(const dint<_T>& a, const _T& b)
{
	return a - dint<_T>(b);
}

template <typename _T>
cftal::dint<_T> cftal::operator-(const _T& a, const dint<_T>& b)
{
	return dint<_T>(a) + b;
}

template <typename _T>
cftal::dint<_T> cftal::operator*(const dint<_T>& a, const dint<_T>& b)
{
	typedef typename dint<_T>::base_type du_t;
	return static_cast<const du_t&>(a) *
		static_cast<const du_t&>(b);
}

template <typename _T>
cftal::dint<_T> cftal::operator*(const dint<_T>& a, const _T& b)
{
	typedef typename dint<_T>::base_type du_t;
	typedef typename du_t::type type;
	typedef std::pair<type, type> pair_type;
	const type& ub= static_cast<const type&>(b);
	// [2^ 0, 2^N2 )
	pair_type al_bl(wide_mul(a.l(), ub));
	// [2^(N2/2),  2^(N2*2/2) )
	type al_bh(impl::get_sign(b) ? -a.l() : type(0));
	type ah_bl(a.uh() * ub);
	// shift al_bh and ah_bl right by 2^(N2/2)
	du_t s20(0, al_bh);
	du_t s21(0, ah_bl);
	du_t s0(al_bl.first, al_bl.second);
	du_t r= s0 + s20 + s21;
	return r;
}

template <typename _T>
cftal::dint<_T> cftal::operator*(const _T& a, const dint<_T>& b)
{
	return b* a;
}

template <typename _T>
cftal::dint<_T> cftal::operator/(const dint<_T>& a, const _T& b)
{
	bool flip_a(impl::get_sign(a)), flip_b(impl::get_sign(b));
	typedef typename std::make_unsigned<_T>::type u_t;
	typedef typename dint<_T>::base_type du_t;
	du_t ap(flip_a ? -a : a);
	u_t bp(flip_b ? -b : b);
	dint<_T> q(ap / bp);
	if (flip_a ^ flip_b) 
		q = -q;
	return q;
}

template <typename _T>
cftal::dint<_T> cftal::operator/(const dint<_T>& a, const dint<_T>& b)
{
	bool flip_a(impl::get_sign(a)), flip_b(impl::get_sign(b));
	typedef typename dint<_T>::base_type du_t;
	du_t ap(flip_a ? -a : a);
	du_t bp(flip_b ? -b : b);
	dint<_T> q(ap / bp);
	if (flip_a ^ flip_b) 
		q = -q;
	return q;
}

template <typename _T>
cftal::dint<_T> cftal::operator/(const _T& a, const dint<_T>& b)
{
	dint<_T> ad(a);
	return ad / b;
}

template <typename _T>
cftal::dint<_T> cftal::operator%(const dint<_T>& a, const _T& b)
{
	dint<_T> q(a/b);
	return remainder(a, dint<_T>(b), q);
}

template <typename _T>
cftal::dint<_T> cftal::operator%(const dint<_T>& a, const dint<_T>& b)
{
	dint<_T> q(a/b);
	return remainder(a, b, q);
}

template <typename _T>
cftal::dint<_T> cftal::operator%(const _T& a, const dint<_T>& b)
{
	dint<_T> ad(a), q(ad/b);
	return remainder(ad, b, q);
}

template <typename _T>
cftal::dint<_T> cftal::operator<<(const dint<_T>& a, unsigned s)
{
	typedef typename dint<_T>::base_type du_t;
	return static_cast<const du_t&>(a) << s;
}

template <typename _T>
cftal::dint<_T> cftal::operator<<(const dint<_T>& a, int s)
{
	return a << unsigned(s);
}

template <typename _T>
cftal::dint<_T> cftal::operator>>(const dint<_T>& a, unsigned s)
{
	// arithmetic shift from logical shift:
	typedef typename dint<_T>::base_type du_t;
	typedef typename std::make_unsigned<_T>::type u_t;
	dint<_T> t1(impl::get_sign(a) ? ~_T(0) : _T(0));
	dint<_T> t2(a^ t1);
	dint<_T> t3(static_cast<const du_t&>(a) >> s);
	return t3 ^ t1;
}

template <typename _T>
cftal::dint<_T> cftal::operator>>(const dint<_T>& a, int s)
{
	return a >> unsigned(s);
}

template <typename _T>
cftal::dint<_T>& cftal::operator|=(dint<_T>& a, const dint<_T>& b)
{
	a = a | b;
	return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator|=(dint<_T>& a, const _T& b)
{
	a = a | b;
	return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator&=(dint<_T>& a, const dint<_T>& b)
{
	a = a & b;
	return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator&=(dint<_T>& a, const _T& b)
{
	a = a & b;
	return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator^=(dint<_T>& a, const dint<_T>& b)
{
	a = a ^ b;
	return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator^=(dint<_T>& a, const _T& b)
{
	a = a ^ b;
	return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator+=(dint<_T>& a, const dint<_T>& b)
{
	a = a + b;
	return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator+=(dint<_T>& a, const _T& b)
{
	a = a + b;
	return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator-=(dint<_T>& a, const dint<_T>& b)
{
	a = a - b;
	return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator-=(dint<_T>& a, const _T& b)
{
	a = a - b;
	return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator*=(dint<_T>& a, const dint<_T>& b)
{
	a = a * b;
	return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator*=(dint<_T>& a, const _T& b)
{
	a = a * b;
	return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator/=(dint<_T>& a, const dint<_T>& b)
{
	a = a / b;
	return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator/=(dint<_T>& a, const _T& b)
{
	a = a / b;
	return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator%=(dint<_T>& a, const dint<_T>& b)
{
	a = a % b;
	return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator%=(dint<_T>& a, const _T& b)
{
	a = a % b;
	return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator<<=(dint<_T>& a, unsigned s)
{
	a= a << s;
	return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator<<=(dint<_T>& a, int s)
{
	a= a << s;
	return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator>>=(dint<_T>& a, unsigned s)
{
	a= a >> s;
	return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator>>=(dint<_T>& a, int s)
{
	a= a >> s;
	return a;
}

template <typename _T>
bool cftal::operator<(const dint<_T>& a, const dint<_T>& b)
{
	bool r((a.uh()< b.uh()) || ((a.uh()==b.uh()) && (a.l() < b.l())));
	return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator<(const _T& a, const dint<_T>& b)
{
	bool r((b.uh()==_T(0)) && (a < b.l()));
	return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator<(const dint<_T>& a, const _T& b)
{
	bool r((a.uh()==_T(0)) && (a.l() < b));
	return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator<=(const dint<_T>& a, const dint<_T>& b)
{
	bool r((a.uh()< b.uh()) || ((a.uh()==b.uh()) && (a.l() <= b.l())));
	return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator<=(const _T& a, const dint<_T>& b)
{
	bool r((b.uh()==_T(0)) && (a <= b.l()));
	return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator<=(const dint<_T>& a, const _T& b)
{
	bool r((a.uh()==_T(0)) && (a.l() <= b));
	return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator==(const dint<_T>& a, const dint<_T>& b)
{
	bool r((a.uh() == b.uh()) && (a.l() == b.l()));
	return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator==(const _T& a, const dint<_T>& b)
{
	bool r((b.uh()==_T(0)) && (a == b.l()));
	return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator==(const dint<_T>& a, const _T& b)
{
	bool r((a.uh()==_T(0)) && (a.l() == b));
	return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator!=(const dint<_T>& a, const dint<_T>& b)
{
	bool r((a.uh() != b.uh()) || (a.l() != b.l()));
	return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator!=(const _T& a, const dint<_T>& b)
{
	bool r((b.uh()!=_T(0)) || (a != b.l()));
	return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator!=(const dint<_T>& a, const _T& b)
{
	bool r((a.uh()!=_T(0)) || (a.l() != b));
	return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator>=(const dint<_T>& a, const dint<_T>& b)
{
	bool r((a.uh() > b.uh()) || ((a.uh()==b.uh()) && (a.l() >= b.l())));
	return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator>=(const _T& a, const dint<_T>& b)
{
	bool r((b.uh()==_T(0)) && (a >= b.l()));
	return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator>=(const dint<_T>& a, const _T& b)
{
	bool r((a.uh()>_T(0)) || (a.l() >= b));
	return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator>(const dint<_T>& a, const dint<_T>& b)
{
	bool r((a.uh() > b.uh()) || ((a.uh()==b.uh()) && (a.l() > b.l())));
	return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator>(const _T& a, const dint<_T>& b)
{
	bool r((b.uh()==_T(0)) && (a > b.l()));
	return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator>(const dint<_T>& a, const _T& b)
{
	bool r((a.uh()>_T(0)) || (a.l() > b));
	return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

// Local variables:
// mode: c++
// end:
#endif
