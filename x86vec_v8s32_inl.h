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
        const __m128i msk = impl::make_zero_int::v();
        return _mm_cmpeq_epi32(a(), msk);
}

inline
x86vec::v8s32 x86vec::operator| (const v8s32& a, const v8s32& b)
{
        return _mm_or_si128(a(), b());
}

inline
x86vec::v8s32 x86vec::operator|| (const v8s32& a, const v8s32& b)
{
        return a | b;
}

inline
x86vec::v8s32 x86vec::operator& (const v8s32& a, const v8s32& b)
{
        return _mm_and_si128(a(), b());
}

inline
x86vec::v8s32 x86vec::operator&& (const v8s32& a, const v8s32& b)
{
        return a & b;
}

inline
x86vec::v8s32 x86vec::operator^(const v8s32& a, const v8s32& b)
{
        return _mm_xor_si128(a(), b());
}

inline
x86vec::v8s32 x86vec::operator+ (const v8s32& a, const v8s32& b)
{
        return _mm_add_epi32(a(), b());
}

inline
x86vec::v8s32 x86vec::operator- (const v8s32& a, const v8s32& b)
{
        return _mm_sub_epi32(a(), b());
}

inline
x86vec::v8s32 x86vec::operator* (const v8s32& a, const v8s32& b)
{
        return impl::vpmulld::v(a(), b());
}

inline
x86vec::v8s32
x86vec::operator/(const v8s32& a, const v8s32& b)
{
        return impl::div_s32::v(a(), b());
}

inline
x86vec::v8s32
x86vec::operator%(const v8s32& a, const v8s32& b)
{
        return cftal::remainder(a, b, a/b);
}

inline
x86vec::v8s32 x86vec::operator< (const v8s32& a, const v8s32& b)
{
        return _mm_cmpgt_epi32(b(), a());
}

inline
x86vec::v8s32 x86vec::operator<= (const v8s32& a, const v8s32& b)
{
#if defined (__SSE4_1__)
	// a <= b: a == min(a, b);
	__m128i min_ab = _mm_min_epi32(b(), a());
	return _mm_cmpeq_epi32(a(), min_ab);
#else
	return ~(b > a);
#endif
}

inline
x86vec::v8s32 x86vec::operator== (const v8s32& a, const v8s32& b)
{
        return _mm_cmpeq_epi32(a(), b());
}

inline
x86vec::v8s32 x86vec::operator!= (const v8s32& a, const v8s32& b)
{
        return ~(a == b);
}

inline
x86vec::v8s32 x86vec::operator>= (const v8s32& a, const v8s32& b)
{
#if defined (__SSE4_1__)
	// a >= b: a == max(a, b);
	__m128i max_ab = _mm_max_epi32(b(), a());
	return _mm_cmpeq_epi32(a(), max_ab);
#else
        return ~(a < b);
#endif
}

inline
x86vec::v8s32 x86vec::operator> (const v8s32& a, const v8s32& b)
{
        return _mm_cmpgt_epi32(a(), b());
}

inline
bool x86vec::all_signs(const v8s32& a)
{
        return all_signs_s32(a());
}

inline
bool x86vec::both_signs(const v8s32& a)
{
        return both_signs_s32(a());
}

inline
bool x86vec::no_signs(const v8s32& a)
{
        return no_signs_s32(a());
}

inline
x86vec::v8s32 x86vec::max(const v8s32& a, const v8s32& b)
{
#if defined (__SSE4_1__)
        return _mm_max_epi32(a(), b());
#else
	v8s32 _gt(a > b);
	return select(_gt, a, b);
#endif
}

inline
x86vec::v8s32 x86vec::min(const v8s32& a, const v8s32& b)
{
#if defined (__SSE4_1__)
        return _mm_min_epi32(a(), b());
#else
	v8s32 _lt(a < b);
	return select(_lt, a, b);
#endif
}

inline
x86vec::v8s32 x86vec::abs(const v8s32& a)
{
#if defined (__SSSE3__)
        return _mm_abs_epi32(a());
#else
        v8s32 neg(impl::make_zero_int::v());
        neg -= a;
        return max(a, neg);
#endif
}

inline
x86vec::v8s32 x86vec::andnot(const v8s32& a, const v8s32& b)
{
	return _mm_andnot_si128(a(), b());
}

inline
x86vec::v8s32 x86vec::mul_hi(const v8s32& x, const v8s32& y)
{
	return impl::vpmulhd::v(x(), y());
}

inline
std::pair<x86vec::v8s32, x86vec::v8s32>
x86vec::mul_lo_hi(const v8s32& x, const v8s32& y)
{
#if defined (__SSE4_1__) 
	// p0l p0h p2l p2h
	v8s32 e= _mm_mul_epi32(x(), y());
	// p1l p1h p3l p3h
	v8s32 o= _mm_mul_epi32(impl::vpshufd<1, 0, 3, 2>::v(x()),
			       impl::vpshufd<1, 0, 3, 2>::v(y()));
	// p0l p1l p0h p1h
	v8s32 t0= permute<0, 4, 1, 5>(e, o);
	// p2l p3l p2h p3h
	v8s32 t1= permute<2, 6, 3, 7>(e, o);
	// p0h p1h p2h p3h
	v8s32 h = permute<2, 3, 6, 7>(t0, t1);
	v8s32 l = permute<0, 1, 4, 5>(t0, t1);
	return std::make_pair(l, h);
#else
	// muluh(x,y) = mulsh(x,y) + and(x, xsign(y)) + and(y, xsign(x));
	// mulsh(x,y) = muluh(x,y) - and(x, xsign(y)) - and(y, xsign(x));
	std::pair<v4u32, v4u32> ur(mul_lo_hi(v4u32(x), v4u32(y)));
	v8s32 xsgn_y= y >> const_shift::_31;
	v8s32 xsgn_x= x >> const_shift::_31;
	v8s32 x_and_xsgn_y = x & xsgn_y;
	v8s32 y_and_xsgn_x = y & xsgn_x;
	v8s32 sh = v8s32(ur.second) - x_and_xsgn_y - y_and_xsgn_x;
	v8s32 sl = v8s32(ur.first);
	return std::make_pair(sl, sh);
#endif
}

template < bool _P0, bool _P1, bool _P2, bool _P3 >
inline
x86vec::v8s32 x86vec::select(const v8s32& a, const v8s32& b)
{
        return select_u32 <_P0, _P1, _P2, _P3> (a(), b());
}

inline
x86vec::v8s32 x86vec::select(const v8s32& msk,
                             const v8s32& on_true,
                             const v8s32& on_false)
{
        return select(msk(), on_true(), on_false());
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
	return insert_u32<_I>(a(), v);
}

template <unsigned _I>
inline
typename x86vec::v8s32::element_type
x86vec::extract(const v8s32& a)
{
	return extract_u32<_I>(a());
}

#endif

// Local variables:
// mode: c++
// end:
#endif
