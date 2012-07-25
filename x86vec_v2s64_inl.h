#if !defined (__X86VEC_V2S64_INL_H__)
#define __X86VEC_V2S64_INL_H__ 1

#if !defined (__X86VEC_IVEC_H__)
#include <cftal/x86vec_ivec.h>
#error "never use this file directly"
#endif

inline
x86vec::v2s64::v2s64(vector_type r) : base_type(r)
{
}

inline
x86vec::v2s64::v2s64(const base_type& r) : base_type(r)
{
}

inline
x86vec::v2s64::v2s64(element_type p00, element_type p01)
        : base_type(_mm_set_epi64x(p01, p00))
{
}

inline
x86vec::v2s64::v2s64(element_type r)
        : base_type(_mm_set1_epi64x(r))
{
}

inline
x86vec::v2s64::v2s64(v2s64::element_type r, bool broadcast)
        : base_type(broadcast ?
                    _mm_set1_epi64x(r) :
		    _mm_set_epi64x(0, r))
{
}

inline
x86vec::v2s64::v2s64(const mem::addr_bcast<element_type>& r)
        : base_type(_mm_set1_epi64x(*r()))
{
}

inline
x86vec::v2s64::v2s64(const mem::addr<element_type>& r)
        : base_type(is_aligned_to<16>::ptr(r()) ?
                    _mm_load_si128(m128i_ptr::make(r())) :
                    _mm_loadu_si128(m128i_ptr::make(r())))
{
}

inline
x86vec::v2s64::v2s64(const mem::aligned::addr<element_type>& r)
        : base_type(_mm_load_si128(m128i_ptr::make(r())))
{
}

inline
x86vec::v2s64::v2s64(const mem::unaligned::addr<element_type>& r)
        : base_type(_mm_loadu_si128(m128i_ptr::make(r())))
{
}

inline
x86vec::v2s64&
x86vec::operator|= (v2s64& a, const v2s64& b)
{
        a = _mm_or_si128(a(), b());
        return a;
}

inline
x86vec::v2s64&
x86vec::operator&= (v2s64& a, const v2s64& b)
{
        a = _mm_and_si128(a(), b());
        return a;
}

inline
x86vec::v2s64&
x86vec::operator^= (v2s64& a, const v2s64& b)
{
        a = _mm_xor_si128(a(), b());
        return a;
}

inline
x86vec::v2s64&
x86vec::operator+= (v2s64& a, const v2s64& b)
{
        a = _mm_add_epi64(a(), b());
        return a;
}

inline
x86vec::v2s64&
x86vec::operator-= (v2s64& a, const v2s64& b)
{
        a = _mm_sub_epi64(a(), b());
        return a;
}

inline
x86vec::v2s64&
x86vec::operator*= (v2s64& a, const v2s64& b)
{
        a = impl::vpmullq::v(a(), b());
        return a;
}

inline
x86vec::v2s64&
x86vec::operator/=(v2s64& a, const v2s64& b)
{
        a= impl::div_s64::v(a(), b());
        return a;
}

inline
x86vec::v2s64&
x86vec::operator%=(v2s64& a, const v2s64& b)
{
        v2s64 q(a/b);
        a = cftal::remainder(a, b, q);
        return a;
}

template <unsigned _P>
inline
x86vec::v2s64&
x86vec::operator<<= (v2s64& a, const const_u32< _P >& b)
{
        const int val = b.val;
        a = impl::vpsllq_const<val>::v(a());
        return a;
}

inline
x86vec::v2s64&
x86vec::operator<<= (v2s64& a, uint32_t b)
{
        a = impl::vpsllq::v(a(), b);
        return a;
}

template <unsigned _P>
inline
x86vec::v2s64
x86vec::operator<< (const v2s64& a, const const_u32< _P >& b)
{
        const int val = b.val;
        return impl::vpsllq_const<val>::v(a());
}

inline
x86vec::v2s64
x86vec::operator<< (const v2s64& a, uint32_t b)
{
        return impl::vpsllq::v(a(), b);
}


template <unsigned _P>
inline
x86vec::v2s64&
x86vec::operator>>= (v2s64& a, const const_u32< _P >& b)
{
        const int val = b.val;
        a = impl::vpsraq_const<val>::v(a());
        return a;
}

inline
x86vec::v2s64&
x86vec::operator>>= (v2s64& a, uint32_t r)
{
        a = impl::vpsraq::v(a(), r);
        return a;
}

template <unsigned _P>
inline
x86vec::v2s64
x86vec::operator>> (const v2s64& a, const const_u32< _P >& b)
{
        const int val = b.val;
        return impl::vpsraq_const<val>::v(a());
}

inline
x86vec::v2s64
x86vec::operator>> (const v2s64& a, uint32_t r)
{
        return impl::vpsraq::v(a(), r);
}

inline
x86vec::v2s64&
x86vec::operator++(v2s64& a)
{
        const __m128i one = const4_u32< 1, 0, 1, 0>::iv();
        a = _mm_add_epi64(a(), one);
        return a;
}

inline
x86vec::v2s64
x86vec::operator++ (v2s64& a, int)
{
        v2s64 t(a);
        const __m128i one = const4_u32< 1, 0, 1, 0>::iv();
        a = _mm_add_epi64(a(), one);
        return t;
}

inline
x86vec::v2s64&
x86vec::operator--(v2s64& a)
{
        const __m128i one = const4_u32< 1, 0, 1, 0>::iv();
        a = _mm_sub_epi64(a(), one);
        return a;
}

inline
x86vec::v2s64
x86vec::operator-- (v2s64& a, int)
{
        v2s64 t(a);
        const __m128i one = const4_u32< 1, 0, 1, 0>::iv();
        a = _mm_sub_epi64(a(), one);
        return t;
}

inline
x86vec::v2s64
x86vec::operator-(const v2s64& a)
{
        const __m128i zero = impl::make_zero_int::v();
        return _mm_sub_epi64(zero, a());
}

inline
const x86vec::v2s64&
x86vec::operator+(const v2s64& a)
{
	return a;
}

inline
x86vec::v2s64
x86vec::operator~(const v2s64& a)
{
        const __m128i all_set = const4_u32 < -1, -1, -1, -1 >::iv();
        return _mm_xor_si128(a(), all_set);
}

inline
x86vec::v2s64
x86vec::operator!(const v2s64& a)
{
        const __m128i msk = impl::make_zero_int::v();
        return a == v2s64(msk);
}

inline
x86vec::v2s64 x86vec::operator| (const v2s64& a, const v2s64& b)
{
        return _mm_or_si128(a(), b());
}

inline
x86vec::v2s64 x86vec::operator|| (const v2s64& a, const v2s64& b)
{
        return a | b;
}

inline
x86vec::v2s64 x86vec::operator& (const v2s64& a, const v2s64& b)
{
        return _mm_and_si128(a(), b());
}

inline
x86vec::v2s64 x86vec::operator&& (const v2s64& a, const v2s64& b)
{
        return a & b;
}

inline
x86vec::v2s64 x86vec::operator^(const v2s64& a, const v2s64& b)
{
        return _mm_xor_si128(a(), b());
}

inline
x86vec::v2s64 x86vec::operator+ (const v2s64& a, const v2s64& b)
{
        return _mm_add_epi64(a(), b());
}

inline
x86vec::v2s64 x86vec::operator- (const v2s64& a, const v2s64& b)
{
        return _mm_sub_epi64(a(), b());
}

inline
x86vec::v2s64 x86vec::operator* (const v2s64& a, const v2s64& b)
{
        return impl::vpmullq::v(a(), b());
}

inline
x86vec::v2s64
x86vec::operator/(const v2s64& a, const v2s64& b)
{
        return impl::div_s64::v(a(), b());
}

inline
x86vec::v2s64
x86vec::operator%(const v2s64& a, const v2s64& b)
{
        return cftal::remainder(a, b, a/b);
}

inline
x86vec::v2s64 x86vec::operator< (const v2s64& a, const v2s64& b)
{
	return b > a;
}

inline
x86vec::v2s64 x86vec::operator<= (const v2s64& a, const v2s64& b)
{
	return ~(b > a);
}

inline
x86vec::v2s64 x86vec::operator== (const v2s64& a, const v2s64& b)
{
#if defined (__SSE4_1__)
        return _mm_cmpeq_epi64(a(), b());
#else
	// a == b : a_h == b_h && a_l == b_l
	__m128i r= _mm_cmpeq_epi32(a(), b());
	__m128i c32s = impl::vpsllq_const<32>::v(r);
	r = _mm_and_si128(r, c32s);
	return impl::vpshufd<1, 1, 3, 3>::v(r);
#endif
}

inline
x86vec::v2s64 x86vec::operator!= (const v2s64& a, const v2s64& b)
{
        return ~(a == b);
}

inline
x86vec::v2s64 x86vec::operator>= (const v2s64& a, const v2s64& b)
{
        return ~(a < b);
}

inline
x86vec::v2s64 x86vec::operator> (const v2s64& a, const v2s64& b)
{
#if defined (__SSE4_2__)
        return _mm_cmpgt_epi64(a(), b());
#else
	// a > b : (a>=0 && b<0) || ((sgn(a) == sgn(b) && (b-a < 0)))
	// c1 --------^
	// c2 ---------------^
	// c3 -------------------------------^ 
	// c4 -------------------------------------------------^
	// sgn(a) == sgn(b) --> a ^ b == highest bit clear
	// b-a <0 == highest bit set
	// a >=0 == highest bit empty 
	// b < 0 == highest bit set 
	__m128i c4= _mm_sub_epi64(b(), a());
	__m128i c1_and_c2 = _mm_andnot_si128(a(), b());
	__m128i c3 = _mm_xor_si128(a(), b());
	__m128i c3_and_c4 = _mm_andnot_si128(c3, c4);
	__m128i r = _mm_or_si128(c1_and_c2, c3_and_c4);
	r = impl::vpsrad_const<31>::v(r);
	r = impl::vpshufd< 1, 1, 3, 3>::v(r);
	return r;
#endif
}

inline
bool x86vec::all_signs(const v2s64& a)
{
        return all_signs_s64(a());
}

inline
bool x86vec::both_signs(const v2s64& a)
{
        return both_signs_s64(a());
}

inline
bool x86vec::no_signs(const v2s64& a)
{
        return no_signs_s64(a());
}

inline
x86vec::v2s64 x86vec::max(const v2s64& a, const v2s64& b)
{
	v2s64 _gt(a > b);
	return select(_gt, a, b);
}

inline
x86vec::v2s64 x86vec::min(const v2s64& a, const v2s64& b)
{
	v2s64 _lt(a < b);
	return select(_lt, a, b);
}

inline
x86vec::v2s64 x86vec::abs(const v2s64& a)
{
        v2s64 neg(impl::make_zero_int::v());
        neg -= a;
        return max(a, neg);
}

inline
x86vec::v2s64 x86vec::mulh(const v2s64& x, const v2s64& y)
{
	return wide_mul(x, y).second;
}

inline
std::pair<x86vec::v2s64, x86vec::v2s64>
x86vec::wide_mul(const v2s64& x, const v2s64& y)
{
#if 1 //defined (__x86_64__)
	typedef v2s64::element_type e_t;
	typedef std::pair<e_t, e_t> p_t;
	p_t t0(cftal::wide_mul(extract<0>(x), extract<0>(y)));
	p_t t1(cftal::wide_mul(extract<1>(x), extract<1>(y)));
	v2s64 l(t0.first, t1.first);
	v2s64 h(t0.second, t1.second);
	return std::make_pair(l, h);
#else
	// muluh(x,y) = mulsh(x,y) + and(x, xsign(y)) + and(y, xsign(x));
	// mulsh(x,y) = muluh(x,y) - and(x, xsign(y)) - and(y, xsign(x));
	std::pair<v2u64, v2u64> ur(wide_mul(v2u64(x), v2u64(y)));
	v2s64 xsgn_y= y >> const_shift::_63;
	v2s64 xsgn_x= x >> const_shift::_63;
	v2s64 x_and_xsgn_y = x & xsgn_y;
	v2s64 y_and_xsgn_x = y & xsgn_x;
	v2s64 ph= v2s64(ur.second) - x_and_xsgn_y - y_and_xsgn_x;
	v2s64 pl= v2s64(ur.first);
	return std::make_pair(pl, ph);
#endif
}

template < bool _P0, bool _P1>
inline
x86vec::v2s64 x86vec::select(const v2s64& a, const v2s64& b)
{
        return select_u64<_P0, _P1> (a(), b());
}

inline
x86vec::v2s64 x86vec::select(const v2s64& msk,
                             const v2s64& on_true,
                             const v2s64& on_false)
{
        return select(msk(), on_true(), on_false());
}

template <int _P0, int _P1>
inline
x86vec::v2s64 x86vec::permute(const v2s64& a)
{
        return perm_u64<_P0, _P1>(a());
}

template < int _P0, int _P1 >
inline
x86vec::v2s64 x86vec::permute(const v2s64& a, const v2s64& b)
{
        return perm_u64<_P0, _P1>(a(), b());
}

template <unsigned _I>
inline
x86vec::v2s64 x86vec::insert(const v2s64& a, typename v2s64::element_type v)
{
	return insert_u64<_I>(a(), v);
}

template <unsigned _I>
inline
typename x86vec::v2s64::element_type
x86vec::extract(const v2s64& a)
{
	return extract_u64<_I>(a());
}

// Local variables:
// mode: c++
// end:
#endif
