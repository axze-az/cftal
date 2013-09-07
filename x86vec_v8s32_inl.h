#if !defined (__X86VEC_V8S32_INL_H__)
#define __X86VEC_V8S32_INL_H__ 1

#if !defined (__X86VEC_IVEC_H__)
#include <cftal/x86vec_ivec.h>
#error "never use this file directly"
#endif

#if defined (__AVX2__)

#else

inline
x86vec::v8s32::v8s32(const v4s32&l, const v4s32& h) 
	: _l(l), _h(h)
{
}

inline
x86vec::v8s32::v8s32(const base_type& r) : base_type(r)
{
}

inline
x86vec::v8s32::v8s32(element_type p00, element_type p01,
                     element_type p02, element_type p03,
		     element_type p04, element_type p05,
                     element_type p06, element_type p07)
        : _l(p00, p01, p02, p03), _h(p04, p05, p06, p07)
{
}

inline
x86vec::v8s32::v8s32(element_type r)
        : _l(r), _h(r)
{
}

inline
x86vec::v8s32::v8s32(v8s32::element_type r, bool broadcast)
        : _l(r, broadcast), _h( broadcast ? r : 0)
{
}
	
inline
x86vec::v8s32::v8s32(const mem::addr_bcast<element_type>& r)
        : base_type(_mm_set1_epi32(*r()))
{
}

inline
x86vec::v8s32::v8s32(const mem::addr<element_type>& r)
	: _l(r), _h(mem::addr<element_type>(r()+4))
{
}

inline
x86vec::v8s32::v8s32(const mem::aligned::addr<element_type>& r)
	: _l(r), _h(mem::aligned::addr<element_type>(r()+4))
{
}

inline
x86vec::v8s32::v8s32(const mem::unaligned::addr<element_type>& r)
	: _l(r), _h(mem::unaligned::addr<element_type>(r()+4))
{
}

inline
x86vec::masked_vec<x86vec::v8s32>
x86vec::v8s32::operator()(const mask<v8s32>& m) 
{
	return masked_vec<v8s32>(*this, m);
}

inline
x86vec::v4s32 
x86vec::low_half(const v8s32& v)
{
	return v._l;
}

inline
x86vec::v4s32 
x86vec::high_half(const v8s32& v)
{
	return v._h;
}

inline
x86vec::v8s32&
x86vec::operator|= (v8s32& a, const v8s32& b)
{
	a = a | b;
        return a;
}

inline
x86vec::v8s32&
x86vec::operator&= (v8s32& a, const v8s32& b)
{
        a = a & b;
        return a;
}

inline
x86vec::v8s32&
x86vec::operator^= (v8s32& a, const v8s32& b)
{
        a = a ^ b;
        return a;
}

inline
x86vec::v8s32&
x86vec::operator+= (v8s32& a, const v8s32& b)
{
        a = a + b;
        return a;
}

inline
x86vec::v8s32&
x86vec::operator-= (v8s32& a, const v8s32& b)
{
        a = a - b;
        return a;
}

inline
x86vec::v8s32&
x86vec::operator*= (v8s32& a, const v8s32& b)
{
        a = a* b;
        return a;
}

inline
x86vec::v8s32&
x86vec::operator/=(v8s32& a, const v8s32& b)
{
        a= a / b;
        return a;
}

inline
x86vec::v8s32&
x86vec::operator%=(v8s32& a, const v8s32& b)
{
        v8s32 q(a/b);
        a = cftal::remainder(a, b, q);
        return a;
}

template <unsigned _P>
inline
x86vec::v8s32&
x86vec::operator<<= (v8s32& a, const const_u32< _P >& b)
{
        a = a << b;
        return a;
}

inline
x86vec::v8s32&
x86vec::operator<<= (v8s32& a, uint32_t b)
{
        a = a << b;
        return a;
}

template <unsigned _P>
inline
x86vec::v8s32
x86vec::operator<< (const v8s32& a, const const_u32< _P >& b)
{
	v4s32 rl(low_half(a) << b);
	v4s32 rh(high_half(a) << b);
	return v8s32(rl, rh);
}

inline
x86vec::v8s32
x86vec::operator<< (const v8s32& a, uint32_t b)
{
	v4s32 rl(low_half(a) << b);
	v4s32 rh(high_half(a) << b);
	return v8s32(rl, rh);
}


template <unsigned _P>
inline
x86vec::v8s32&
x86vec::operator>>= (v8s32& a, const const_u32< _P >& b)
{
	a = a >> b;
        return a;
}

inline
x86vec::v8s32&
x86vec::operator>>= (v8s32& a, uint32_t r)
{
        a = a >> b;
        return a;
}

template <unsigned _P>
inline
x86vec::v8s32
x86vec::operator>> (const v8s32& a, const const_u32< _P >& b)
{
	v4s32 rl(low_half(a) >> b);
	v4s32 rh(high_half(a) >> b);
	return v8s32(rl, rh);
}

inline
x86vec::v8s32
x86vec::operator>> (const v8s32& a, uint32_t r)
{
	v4s32 rl(low_half(a) >> b);
	v4s32 rh(high_half(a) >> b);
	return v8s32(rl, rh);
}


inline
x86vec::v8s32&
x86vec::operator++(v8s32& a)
{
	v4s32 rl(low_half(a));
	v4s32 rh(high_half(a));
	++rl;
	++rh;
	return v8s32(rl, rh);
}

inline
x86vec::v8s32
x86vec::operator++ (v8s32& a, int)
{
        v8s32 t(a);
	v4s32 rl(low_half(a));
	v4s32 rh(high_half(a));
	++rl;
	++rh;
	a = v8s32(rl, rh);
        return t;
}

inline
x86vec::v8s32&
x86vec::operator--(v8s32& a)
{
	v4s32 rl(low_half(a));
	v4s32 rh(high_half(a));
	--rl;
	--rh;
	return v8s32(rl, rh);
}

inline
x86vec::v8s32
x86vec::operator-- (v8s32& a, int)
{
        v8s32 t(a);
	v4s32 rl(low_half(a));
	v4s32 rh(high_half(a));
	--rl;
	--rh;
	a = v8s32(rl, rh);
        return t;
}

inline
x86vec::v8s32
x86vec::operator-(const v8s32& a)
{
	v4s32 rl(-low_half(a));
	v4s32 rh(-high_half(a));
	return v8s32(rl, rh);
}

inline
const x86vec::v8s32&
x86vec::operator+(const v8s32& a)
{
	return a;
}

inline
x86vec::v8s32
x86vec::operator~(const v8s32& a)
{
	v4s32 rl(~low_half(a));
	v4s32 rh(~high_half(a));
	return v8s32(rl, rh);
}

inline
x86vec::v8s32
x86vec::operator!(const v8s32& a)
{
	v4s32 rl(!low_half(a));
	v4s32 rh(!high_half(a));
	return v8s32(rl, rh);
}

inline
x86vec::v8s32 x86vec::operator| (const v8s32& a, const v8s32& b)
{
	v4s32 rl(low_half(a) | low_half(b) );
	v4s32 rh(high_half(a) | high_half(b) );
	return v8s32(rl, rh);
}

inline
x86vec::v8s32 x86vec::operator|| (const v8s32& a, const v8s32& b)
{
        return a | b;
}

inline
x86vec::v8s32 x86vec::operator& (const v8s32& a, const v8s32& b)
{
	v4s32 rl(low_half(a) & low_half(b) );
	v4s32 rh(high_half(a) & high_half(b) );
	return v8s32(rl, rh);
}

inline
x86vec::v8s32 x86vec::operator&& (const v8s32& a, const v8s32& b)
{
        return a & b;
}

inline
x86vec::v8s32 x86vec::operator^(const v8s32& a, const v8s32& b)
{
	v4s32 rl(low_half(a) ^ low_half(b) );
	v4s32 rh(high_half(a) ^ high_half(b) );
	return v8s32(rl, rh);
}

inline
x86vec::v8s32 x86vec::operator+ (const v8s32& a, const v8s32& b)
{
	v4s32 rl(low_half(a) + low_half(b) );
	v4s32 rh(high_half(a) + high_half(b) );
	return v8s32(rl, rh);
}

inline
x86vec::v8s32 x86vec::operator- (const v8s32& a, const v8s32& b)
{
	v4s32 rl(low_half(a) - low_half(b) );
	v4s32 rh(high_half(a) - high_half(b) );
	return v8s32(rl, rh);
}

inline
x86vec::v8s32 x86vec::operator* (const v8s32& a, const v8s32& b)
{
	v4s32 rl(low_half(a) * low_half(b) );
	v4s32 rh(high_half(a) * high_half(b) );
	return v8s32(rl, rh);
}

inline
x86vec::v8s32
x86vec::operator/(const v8s32& a, const v8s32& b)
{
	v4s32 rl(low_half(a) / low_half(b) );
	v4s32 rh(high_half(a) / high_half(b) );
	return v8s32(rl, rh);
}

inline
x86vec::v8s32
x86vec::operator%(const v8s32& a, const v8s32& b)
{
	v4s32 rl(low_half(a) % low_half(b) );
	v4s32 rh(high_half(a) % high_half(b) );
	return v8s32(rl, rh);
}

inline
x86vec::v8s32 x86vec::operator< (const v8s32& a, const v8s32& b)
{
	v4s32 rl(low_half(a) < low_half(b) );
	v4s32 rh(high_half(a) < high_half(b) );
	return v8s32(rl, rh);
}

inline
x86vec::v8s32 x86vec::operator<= (const v8s32& a, const v8s32& b)
{
	v4s32 rl(low_half(a) <= low_half(b) );
	v4s32 rh(high_half(a) <= high_half(b) );
	return v8s32(rl, rh);
}

inline
x86vec::v8s32 x86vec::operator== (const v8s32& a, const v8s32& b)
{
	v4s32 rl(low_half(a) == low_half(b) );
	v4s32 rh(high_half(a) == high_half(b) );
	return v8s32(rl, rh);
}

inline
x86vec::v8s32 x86vec::operator!= (const v8s32& a, const v8s32& b)
{
	v4s32 rl(low_half(a) != low_half(b) );
	v4s32 rh(high_half(a) != high_half(b) );
	return v8s32(rl, rh);
}

inline
x86vec::v8s32 x86vec::operator>= (const v8s32& a, const v8s32& b)
{
	v4s32 rl(low_half(a) >= low_half(b) );
	v4s32 rh(high_half(a) >= high_half(b) );
	return v8s32(rl, rh);
}

inline
x86vec::v8s32 x86vec::operator> (const v8s32& a, const v8s32& b)
{
	v4s32 rl(low_half(a) > low_half(b) );
	v4s32 rh(high_half(a) > high_half(b) );
	return v8s32(rl, rh);
}

inline
bool x86vec::all_signs(const v8s32& a)
{
        return all_signs(low_half(a)) && all_signs(high_half(a));
}

inline
bool x86vec::both_signs(const v8s32& a)
{
        return both_signs(low_half(a)) || both_signs(high_half(a));
}

inline
bool x86vec::no_signs(const v8s32& a)
{
        return no_signs(low_half(a)) && no_signs(high_half(a));
}

inline
x86vec::v8s32 x86vec::max(const v8s32& a, const v8s32& b)
{
	v4s32 rl(max(low_half(a), low_half(b)));
	v4s32 rh(max(high_half(a), high_half(b)));
	return v8s32(rl, rh);
}

inline
x86vec::v8s32 x86vec::min(const v8s32& a, const v8s32& b)
{
	v4s32 rl(min(low_half(a), low_half(b)));
	v4s32 rh(min(high_half(a), high_half(b)));
	return v8s32(rl, rh);
}

inline
x86vec::v8s32 x86vec::abs(const v8s32& a)
{
	v4s32 rl(abs(low_half(a)));
	v4s32 rh(abs(high_half(a)));
	return v8s32(rl, rh);
}

inline
x86vec::v8s32 x86vec::andnot(const v8s32& a, const v8s32& b)
{
	v4s32 rl(andnot(low_half(a), low_half(b)));
	v4s32 rh(andnot(high_half(a), high_half(b)));
	return v8s32(rl, rh);
}

inline
x86vec::v8s32 x86vec::mul_hi(const v8s32& x, const v8s32& y)
{
	v4s32 rl(mul_hi(low_half(a), low_half(b)));
	v4s32 rh(mul_hi(high_half(a), high_half(b)));
	return v8s32(rl, rh);
}

inline
std::pair<x86vec::v8s32, x86vec::v8s32>
x86vec::mul_lo_hi(const v8s32& x, const v8s32& y)
{
	std::pair<v4s32, v4s32> lp(mul_lo_hi(low_half(x), low_half(y)));
	std::pair<v4s32, v4s32> hp(mul_lo_hi(high_half(x), high_half(y)));
	v8s32 ml(lp.first, hp.first);
	v8s32 mh(lp.second, hp.second);
	return std::make_pair(ml, mh);
}

template <bool _P0, bool _P1, bool _P2, bool _P3,
	  bool _P4, bool _P5, bool _P6, bool _P7>
inline
x86vec::v8s32 x86vec::select(const v8s32& a, const v8s32& b)
{
	v4s32 rl(select<_P0, _P1, _P2, _P3>(low_half(a), low_half(b)));
	v4s32 rh(select<_P4, _P5, _P6, _P7>(high_half(a), high_half(b)));
	return v8s32(rl, rh);
}

inline
x86vec::v8s32 x86vec::select(const v8s32& msk,
                             const v8s32& on_true,
                             const v8s32& on_false)
{
	v4s32 rl(select(low_half(msk), 
			low_half(on_true), low_half(on_false)));
	v4s32 rh(select(high_half(msk), 
			high_half(on_true), high_half(on_false)));
	return v8s32(rl, rh);
}

template <int _P0, int _P1, int _P2, int _P3>
inline
x86vec::v8s32 x86vec::permute(const v8s32& a)
{
        return perm_u32<_P0, _P1, _P2, _P3>(a());
}

template < int _P0, int _P1, int _P2, int _P3 >
inline
x86vec::v8s32 x86vec::permute(const v8s32& a, const v8s32& b)
{
        return perm_u32<_P0, _P1, _P2, _P3>(a(), b());
}

template <unsigned _I>
inline
x86vec::v8s32 x86vec::insert(const v8s32& a, typename v8s32::element_type v)
{
	const bool low= _I < 4;
	v4s32 rl(low_half(a)), rh(high_half(a));
	if (_I < 4)
		rl = insert<_I>(rl, v);
	else
		rh = insert<_I-4>(rh, v);
	return v8s32(rl, rh);
}

template <unsigned _I>
inline
typename x86vec::v8s32::element_type
x86vec::extract(const v8s32& a)
{
	if (_I < 4)
		return extract<_I>(low_half(a));
	return extract<_I-4>(high_half(a));
}

#endif

// Local variables:
// mode: c++
// end:
#endif
