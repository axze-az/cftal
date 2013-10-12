#if !defined (__X86VEC_V8U32_INL_H__)
#define __X86VEC_V8U32_INL_H__ 1

#if !defined (__X86VEC_IVEC_H__)
#include <cftal/x86vec_ivec.h>
#error "never use this file directly"
#endif

#if defined (__AVX2__)

#else

inline
x86vec::v8u32::v8u32(const base_type& v)
	: base_type(v)
{
}

inline
x86vec::v8u32::v8u32(const v4u32&l, const v4u32& h) 
	: base_type(l, h)
{
}

inline
x86vec::v8u32::v8u32(element_type p00, element_type p01,
                     element_type p02, element_type p03,
		     element_type p04, element_type p05,
                     element_type p06, element_type p07)
        : base_type(p00, p01, p02, p03, p04, p05, p06, p07)
{
}

inline
x86vec::v8u32::v8u32(element_type r)
        : base_type(r)
{
}

inline
x86vec::v8u32::v8u32(v8u32::element_type r, bool broadcast)
        : base_type(r, broadcast)
{
}
	
inline
x86vec::v8u32::v8u32(const mem::addr_bcast<element_type>& r)
        : base_type(mem::addr_bcast<base_type::element_type>(
			    reinterpret_cast<const int*>(r())))
{
}

inline
x86vec::v8u32::v8u32(const mem::addr<element_type>& r)
        : base_type(mem::addr<base_type::element_type>(
			    reinterpret_cast<const int*>(r())))
{
}

inline
x86vec::v8u32::v8u32(const mem::aligned::addr<element_type>& r)
        : base_type(mem::aligned::addr<base_type::element_type>(
			    reinterpret_cast<const int*>(r())))
{
}

inline
x86vec::v8u32::v8u32(const mem::unaligned::addr<element_type>& r)
        : base_type(mem::unaligned::addr<base_type::element_type>(
			    reinterpret_cast<const int*>(r())))
{
}

inline
x86vec::masked_vec<x86vec::v8u32>
x86vec::v8u32::operator()(const mask<v8u32>& m) 
{
	return masked_vec<v8u32>(*this, m);
}

inline
x86vec::v4u32 
x86vec::low_half(const v8u32& v)
{
	const v8u32::base_type& bt=v;
	return low_half(bt);
}

inline
x86vec::v4u32 
x86vec::high_half(const v8u32& v)
{
	const v8u32::base_type& bt=v;
	return high_half(bt);
}

inline
x86vec::v8u32&
x86vec::operator|= (v8u32& a, const v8u32& b)
{
	a = a | b;
        return a;
}

inline
x86vec::v8u32&
x86vec::operator&= (v8u32& a, const v8u32& b)
{
        a = a & b;
        return a;
}

inline
x86vec::v8u32&
x86vec::operator^= (v8u32& a, const v8u32& b)
{
        a = a ^ b;
        return a;
}

inline
x86vec::v8u32&
x86vec::operator+= (v8u32& a, const v8u32& b)
{
        a = a + b;
        return a;
}

inline
x86vec::v8u32&
x86vec::operator-= (v8u32& a, const v8u32& b)
{
        a = a - b;
        return a;
}

inline
x86vec::v8u32&
x86vec::operator*= (v8u32& a, const v8u32& b)
{
        a = a* b;
        return a;
}

inline
x86vec::v8u32&
x86vec::operator/=(v8u32& a, const v8u32& b)
{
        a= a / b;
        return a;
}

inline
x86vec::v8u32&
x86vec::operator%=(v8u32& a, const v8u32& b)
{
        v8u32 q(a/b);
        a = cftal::remainder(a, b, q);
        return a;
}

template <unsigned _P>
inline
x86vec::v8u32&
x86vec::operator<<= (v8u32& a, const const_u32< _P >& b)
{
        a = a << b;
        return a;
}

inline
x86vec::v8u32&
x86vec::operator<<= (v8u32& a, uint32_t b)
{
        a = a << b;
        return a;
}

template <unsigned _P>
inline
x86vec::v8u32
x86vec::operator<< (const v8u32& a, const const_u32< _P >& b)
{
	v4s32 rl(low_half(a) << b);
	v4s32 rh(high_half(a) << b);
	return v8u32(rl, rh);
}

inline
x86vec::v8u32
x86vec::operator<< (const v8u32& a, uint32_t b)
{
	v4s32 rl(low_half(a) << b);
	v4s32 rh(high_half(a) << b);
	return v8u32(rl, rh);
}


template <unsigned _P>
inline
x86vec::v8u32&
x86vec::operator>>= (v8u32& a, const const_u32< _P >& b)
{
	a = a >> b;
        return a;
}

inline
x86vec::v8u32&
x86vec::operator>>= (v8u32& a, uint32_t r)
{
        a = a >> r;
        return a;
}

template <unsigned _P>
inline
x86vec::v8u32
x86vec::operator>> (const v8u32& a, const const_u32< _P >& b)
{
	v4s32 rl(low_half(a) >> b);
	v4s32 rh(high_half(a) >> b);
	return v8u32(rl, rh);
}

inline
x86vec::v8u32
x86vec::operator>> (const v8u32& a, uint32_t r)
{
	v4s32 rl(low_half(a) >> r);
	v4s32 rh(high_half(a) >> r);
	return v8u32(rl, rh);
}


inline
x86vec::v8u32&
x86vec::operator++(v8u32& a)
{
	v4s32 rl(low_half(a));
	v4s32 rh(high_half(a));
	++rl;
	++rh;
	a = v8u32(rl, rh);
	return a;
}

inline
x86vec::v8u32
x86vec::operator++ (v8u32& a, int)
{
        v8u32 t(a);
	v4s32 rl(low_half(a));
	v4s32 rh(high_half(a));
	++rl;
	++rh;
	a = v8u32(rl, rh);
        return t;
}

inline
x86vec::v8u32&
x86vec::operator--(v8u32& a)
{
	v4s32 rl(low_half(a));
	v4s32 rh(high_half(a));
	--rl;
	--rh;
	a= v8u32(rl, rh);
	return a;
}

inline
x86vec::v8u32
x86vec::operator-- (v8u32& a, int)
{
        v8u32 t(a);
	v4s32 rl(low_half(a));
	v4s32 rh(high_half(a));
	--rl;
	--rh;
	a = v8u32(rl, rh);
        return t;
}

inline
x86vec::v8u32
x86vec::operator-(const v8u32& a)
{
	v4s32 rl(-low_half(a));
	v4s32 rh(-high_half(a));
	return v8u32(rl, rh);
}

inline
const x86vec::v8u32&
x86vec::operator+(const v8u32& a)
{
	return a;
}

inline
x86vec::v8u32
x86vec::operator~(const v8u32& a)
{
	v4s32 rl(~low_half(a));
	v4s32 rh(~high_half(a));
	return v8u32(rl, rh);
}

inline
x86vec::v8u32
x86vec::operator!(const v8u32& a)
{
	v4s32 rl(!low_half(a));
	v4s32 rh(!high_half(a));
	return v8u32(rl, rh);
}

inline
x86vec::v8u32 x86vec::operator| (const v8u32& a, const v8u32& b)
{
	v4s32 rl(low_half(a) | low_half(b) );
	v4s32 rh(high_half(a) | high_half(b) );
	return v8u32(rl, rh);
}

inline
x86vec::v8u32 x86vec::operator|| (const v8u32& a, const v8u32& b)
{
        return a | b;
}

inline
x86vec::v8u32 x86vec::operator& (const v8u32& a, const v8u32& b)
{
	v4s32 rl(low_half(a) & low_half(b) );
	v4s32 rh(high_half(a) & high_half(b) );
	return v8u32(rl, rh);
}

inline
x86vec::v8u32 x86vec::operator&& (const v8u32& a, const v8u32& b)
{
        return a & b;
}

inline
x86vec::v8u32 x86vec::operator^(const v8u32& a, const v8u32& b)
{
	v4s32 rl(low_half(a) ^ low_half(b) );
	v4s32 rh(high_half(a) ^ high_half(b) );
	return v8u32(rl, rh);
}

inline
x86vec::v8u32 x86vec::operator+ (const v8u32& a, const v8u32& b)
{
	v4s32 rl(low_half(a) + low_half(b) );
	v4s32 rh(high_half(a) + high_half(b) );
	return v8u32(rl, rh);
}

inline
x86vec::v8u32 x86vec::operator- (const v8u32& a, const v8u32& b)
{
	v4s32 rl(low_half(a) - low_half(b) );
	v4s32 rh(high_half(a) - high_half(b) );
	return v8u32(rl, rh);
}

inline
x86vec::v8u32 x86vec::operator* (const v8u32& a, const v8u32& b)
{
	v4s32 rl(low_half(a) * low_half(b) );
	v4s32 rh(high_half(a) * high_half(b) );
	return v8u32(rl, rh);
}

inline
x86vec::v8u32
x86vec::operator/(const v8u32& a, const v8u32& b)
{
	v4s32 rl(low_half(a) / low_half(b) );
	v4s32 rh(high_half(a) / high_half(b) );
	return v8u32(rl, rh);
}

inline
x86vec::v8u32
x86vec::operator%(const v8u32& a, const v8u32& b)
{
	v4s32 rl(low_half(a) % low_half(b) );
	v4s32 rh(high_half(a) % high_half(b) );
	return v8u32(rl, rh);
}

inline
x86vec::v8u32 x86vec::operator< (const v8u32& a, const v8u32& b)
{
	v4s32 rl(low_half(a) < low_half(b) );
	v4s32 rh(high_half(a) < high_half(b) );
	return v8u32(rl, rh);
}

inline
x86vec::v8u32 x86vec::operator<= (const v8u32& a, const v8u32& b)
{
	v4s32 rl(low_half(a) <= low_half(b) );
	v4s32 rh(high_half(a) <= high_half(b) );
	return v8u32(rl, rh);
}

inline
x86vec::v8u32 x86vec::operator== (const v8u32& a, const v8u32& b)
{
	v4s32 rl(low_half(a) == low_half(b) );
	v4s32 rh(high_half(a) == high_half(b) );
	return v8u32(rl, rh);
}

inline
x86vec::v8u32 x86vec::operator!= (const v8u32& a, const v8u32& b)
{
	v4s32 rl(low_half(a) != low_half(b) );
	v4s32 rh(high_half(a) != high_half(b) );
	return v8u32(rl, rh);
}

inline
x86vec::v8u32 x86vec::operator>= (const v8u32& a, const v8u32& b)
{
	v4s32 rl(low_half(a) >= low_half(b) );
	v4s32 rh(high_half(a) >= high_half(b) );
	return v8u32(rl, rh);
}

inline
x86vec::v8u32 x86vec::operator> (const v8u32& a, const v8u32& b)
{
	v4s32 rl(low_half(a) > low_half(b) );
	v4s32 rh(high_half(a) > high_half(b) );
	return v8u32(rl, rh);
}

inline
x86vec::v8u32 x86vec::max(const v8u32& a, const v8u32& b)
{
	v4s32 rl(max(low_half(a), low_half(b)));
	v4s32 rh(max(high_half(a), high_half(b)));
	return v8u32(rl, rh);
}

inline
x86vec::v8u32 x86vec::min(const v8u32& a, const v8u32& b)
{
	v4s32 rl(min(low_half(a), low_half(b)));
	v4s32 rh(min(high_half(a), high_half(b)));
	return v8u32(rl, rh);
}

inline
x86vec::v8u32 x86vec::andnot(const v8u32& a, const v8u32& b)
{
	v4s32 rl(andnot(low_half(a), low_half(b)));
	v4s32 rh(andnot(high_half(a), high_half(b)));
	return v8u32(rl, rh);
}

inline
x86vec::v8u32 x86vec::mul_hi(const v8u32& x, const v8u32& y)
{
	v4s32 rl(mul_hi(low_half(x), low_half(y)));
	v4s32 rh(mul_hi(high_half(x), high_half(y)));
	return v8u32(rl, rh);
}

inline
std::pair<x86vec::v8u32, x86vec::v8u32>
x86vec::mul_lo_hi(const v8u32& x, const v8u32& y)
{
	std::pair<v4s32, v4s32> lp(mul_lo_hi(low_half(x), low_half(y)));
	std::pair<v4s32, v4s32> hp(mul_lo_hi(high_half(x), high_half(y)));
	v8u32 ml(lp.first, hp.first);
	v8u32 mh(lp.second, hp.second);
	return std::make_pair(ml, mh);
}

template <bool _P0, bool _P1, bool _P2, bool _P3,
	  bool _P4, bool _P5, bool _P6, bool _P7>
inline
x86vec::v8u32 x86vec::select(const v8u32& a, const v8u32& b)
{
	v4s32 rl(select<_P0, _P1, _P2, _P3>(low_half(a), low_half(b)));
	v4s32 rh(select<_P4, _P5, _P6, _P7>(high_half(a), high_half(b)));
	return v8u32(rl, rh);
}

inline
x86vec::v8u32 x86vec::select(const v8u32& msk,
                             const v8u32& on_true,
                             const v8u32& on_false)
{
	v4s32 rl(select(low_half(msk), 
			low_half(on_true), low_half(on_false)));
	v4s32 rh(select(high_half(msk), 
			high_half(on_true), high_half(on_false)));
	return v8u32(rl, rh);
}

template <int _P0, int _P1, int _P2, int _P3,
	  int _P4, int _P5, int _P6, int _P7>
inline
x86vec::v8u32 x86vec::permute(const v8u32& a)
{
	v4s32 rl(permute<_P0, _P1, _P2, _P3>(low_half(a), 
					     high_half(a)));
	const int _PP4 = _P4 > 7 ? _P4 & 7 : _P4;
	const int _PP5 = _P5 > 7 ? _P5 & 7 : _P5;
	const int _PP6 = _P6 > 7 ? _P6 & 7 : _P6;
	const int _PP7 = _P7 > 7 ? _P7 & 7 : _P7;

	v4s32 rh(permute<_PP4, _PP5, _PP6, _PP7>(low_half(a), 
						 high_half(a)));
	return v8u32(rl, rh);
}

template <int _P0, int _P1, int _P2, int _P3,
	  int _P4, int _P5, int _P6, int _P7>
inline
x86vec::v8u32 x86vec::permute(const v8u32& a, const v8u32& b)
{
	using impl::pos_msk_8;
	using impl::zero_msk_8;
        // Combine all the indexes into a single bitfield, with 4 bits
        // for each
        const int m1 = pos_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7, 15>::m;
        // Mask to zero out negative indexes
        const int m2 = zero_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::m;

        if ((m1 & 0x88888888 & m2) == 0) {
                // no elements from b
                return permute<_P0, _P1, _P2, _P3, 
			       _P4, _P5, _P6, _P7>(a);
        }
        if (((m1^0x88888888) & 0x88888888 & m2) == 0) {
                // no elements from a
                return permute<_P0 & ~8, _P1 & ~8,
			       _P2 & ~8, _P3 & ~8,
			       _P4 & ~8, _P5 & ~8,
			       _P6 & ~8, _P7 & ~8>(b);
        }
        if (((m1 & ~0x88888888) ^ 0x76543210) == 0 && m2 == 0xFFFFFFFF) {
                // selecting without shuffling or zeroing
                const bool sm0 = _P0 < 8;
                const bool sm1 = _P1 < 8;
                const bool sm2 = _P2 < 8;
                const bool sm3 = _P3 < 8;
                const bool sm4 = _P4 < 8;
                const bool sm5 = _P5 < 8;
                const bool sm6 = _P6 < 8;
                const bool sm7 = _P7 < 8;
                return select<sm0, sm1, sm2, sm3,
			      sm4, sm5, sm6, sm7>(a, b);
        }

        // select all elements to clear or from 1st vector
        const int ma0 = _P0 < 8 ? _P0 : -1;
	const int ma1 = _P1 < 8 ? _P1 : -1;
	const int ma2 = _P2 < 8 ? _P2 : -1;
	const int ma3 = _P3 < 8 ? _P3 : -1;
        const int ma4 = _P4 < 8 ? _P4 : -1;
	const int ma5 = _P5 < 8 ? _P5 : -1;
	const int ma6 = _P6 < 8 ? _P6 : -1;
	const int ma7 = _P7 < 8 ? _P7 : -1;
	v8u32 a1 = permute<ma0, ma1, ma2, ma3,
			   ma4, ma5, ma6, ma7>(a);
	// select all elements from second vector
	const int mb0 = _P0 > 7 ? (_P0-8) : -1;
	const int mb1 = _P1 > 7 ? (_P1-8) : -1;
	const int mb2 = _P2 > 7 ? (_P2-8) : -1;
	const int mb3 = _P3 > 7 ? (_P3-8) : -1;
	const int mb4 = _P4 > 7 ? (_P4-8) : -1;
	const int mb5 = _P5 > 7 ? (_P5-8) : -1;
	const int mb6 = _P6 > 7 ? (_P6-8) : -1;
	const int mb7 = _P7 > 7 ? (_P7-8) : -1;
	v8u32 b1 = permute<mb0, mb1, mb2, mb3,
			   mb4, mb5, mb6, mb7>(b);
	return  a1 | b1;
}

template <unsigned _I>
inline
x86vec::v8u32 x86vec::insert(const v8u32& a, typename v8u32::element_type v)
{
	const bool low= _I < 4;
	v4s32 rl(low_half(a)), rh(high_half(a));
	if (_I < 4)
		rl = insert<_I>(rl, v);
	else
		rh = insert<_I&3>(rh, v);
	return v8u32(rl, rh);
}

template <unsigned _I>
inline
typename x86vec::v8u32::element_type
x86vec::extract(const v8u32& a)
{
	if (_I < 4)
		return extract<_I>(low_half(a));
	return extract<_I&3>(high_half(a));
}

#endif

// Local variables:
// mode: c++
// end:
#endif
