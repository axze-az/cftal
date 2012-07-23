#if !defined (__CFTAL_MUL_DIV_H__)
#define __CFTAL_MUL_DIV_H__ 1

#include <cftal/config.h>
#include <cftal/bitops.h>
#include <utility>
#include <type_traits>

namespace cftal {

        // calculate the remainder from trunc(n/d)=q
        template <class _V>
        _V remainder(const _V& n, const _V& d, const _V& q);

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

#if !defined (__NO_WIDE_MUL_SPECIALIZATIONS__)
		// specializations for standard types.
		template <>
		struct wide_umul<uint8_t> {
			std::pair<uint8_t, uint8_t>
			operator()(const uint8_t a, const uint8_t b)
				const {
				uint16_t p(uint16_t(a)*b);
				uint8_t l(p);
				uint8_t h(p>>8);
				return std::make_pair(l, h);
			}
		};
		
		template <>
		struct wide_umul<uint16_t> {
			std::pair<uint16_t, uint16_t>
			operator()(const uint16_t a, const uint16_t b)
				const {
				uint32_t p(uint32_t(a)*b);
				uint16_t l(p);
				uint16_t h(p>>16);
				return std::make_pair(l, h);
			}
		};

		template <>
		struct wide_umul<uint32_t> {
			std::pair<uint32_t, uint32_t>
			operator()(const uint32_t a, const uint32_t b)
				const {
				uint64_t p(uint64_t(a)*b);
				uint32_t l(p);
				uint32_t h(p>>32);
				return std::make_pair(l, h);
			}
		};

		// specialisations for standard types.
		template <>
		struct wide_smul<int8_t> {
			std::pair<int8_t, int8_t>
			operator()(const int8_t a, const int8_t b)
				const {
				int16_t p(int16_t(a)*b);
				int8_t l(p);
				int8_t h(p>>8);
				return std::make_pair(l, h);
			}
		};
		
		template <>
		struct wide_smul<int16_t> {
			std::pair<int16_t, int16_t>
			operator()(const int16_t a, const int16_t b)
				const {
				int32_t p(int32_t(a)*b);
				int16_t l(p);
				int16_t h(p>>16);
				return std::make_pair(l, h);
			}
		};

		template <>
		struct wide_smul<int32_t> {
			std::pair<int32_t, int32_t>
			operator()(const int32_t a, const int32_t b)
				const {
				int64_t p(int64_t(a)*b);
				int32_t l(p);
				int32_t h(p>>32);
				return std::make_pair(l, h);
			}
		};
#endif     
	}
	
        namespace impl {

                template <class _U, class _UHALF=_U>
                class udiv_2by1 {
		public:
			static 
			std::pair<_U, _U>
			d(const _U& u0, const _U& u1, const _U& v, _U* r);
		private:
			static _U
			g(const _U& uh, const _U& ul,  const _U& v, _U* r);
                };
#if !defined (__NO_UDIV_2BY1_SPECIALIZATIONS__)

		template <class _UHALF>
		class udiv_2by1<uint8_t, _UHALF> {
		public:
			static_assert(std::is_same<uint8_t, _UHALF>::value,
				      "test");
			static
			std::pair<uint8_t, uint8_t>
			d(uint8_t u0, uint8_t u1, uint8_t v, uint8_t* r) {
				uint16_t u((uint16_t(u1)<<8)|u0);
				uint16_t q(u/v);
				if (r) 
					*r= remainder(u, uint16_t(v), q);
				return std::make_pair(uint8_t(q),
						      uint8_t(q>>8));
			}
		};

		template <class _UHALF>
		class udiv_2by1<uint16_t, _UHALF> {
		public:
			static
			std::pair<uint16_t, uint16_t>
			d(uint16_t u0, uint16_t u1, uint16_t v, uint16_t* r) {
				uint32_t u((uint32_t(u1)<<16)|u0);
				uint32_t q(u/v);
				if (r) 
					*r= remainder(u, uint32_t(v), q);
				return std::make_pair(uint16_t(q),
						      uint16_t(q>>16));
			}
		};

		template <class _UHALF>
		class udiv_2by1<uint32_t, _UHALF> {
		public:
			static
			std::pair<uint32_t, uint32_t>
			d(uint32_t u0, uint32_t u1, uint32_t v, uint32_t* r) {
				uint64_t u((uint64_t(u1)<<32)|u0);
				uint64_t q(u/v);
				if (r) 
					*r= remainder(u, uint64_t(v), q);
				return std::make_pair(uint32_t(q),
						      uint32_t(q>>32));
			}
		};

#endif
        }
}

template <class _V>
inline
_V cftal::remainder(const _V& n, const _V& d, const _V& q)
{
        _V p(d* q);
        return n - p;
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
        vn1 = _UHALF(v >> N2);       // Break divisor up into
	vn0 = _UHALF(v & N2MSK);     // two half digits

        if (s>0) {
                // Shift dividend left.
		unsigned sr= N-s;
		_U un32_lb= ul >> sr;
		un32 = (uh << s) | un32_lb;
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
                q1 = q1 - _UHALF(1);
                rhat = rhat + vn1;
                if (rhat >= b)
                        break;
        }

        un21 = un32*b + un1 - q1*v;  // Multiply and subtract.

        q0 = un21/vn1;            // Compute the second
        rhat = un21 - q0*vn1;     // quotient digit, q0.

        while (q0 >= b || q0*vn0 > b*rhat + un0) {
                q0 = q0 - _UHALF(1);
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
