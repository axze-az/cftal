#if !defined (__X86VEC_V8S16_INL_H__)
#define __X86VEC_V8S16_INL_H__ 1

#if !defined (__X86VEC_IVEC_H__)
#include <cftal/x86vec_ivec.h>
#error "never use this file directly"
#endif

inline
x86vec::v8s16::v8s16(vector_type r) : base_type(r)
{
}

inline
x86vec::v8s16::v8s16(const base_type& r) : base_type(r)
{
}

inline
x86vec::v8s16::v8s16(element_type p00, element_type p01,
                     element_type p02, element_type p03,
                     element_type p04, element_type p05,
                     element_type p06, element_type p07)
        : base_type(_mm_set_epi16(p07, p06, p05, p04,
                                  p03, p02, p01, p00))
{
}

inline
x86vec::v8s16::v8s16(element_type r)
        : base_type(_mm_set1_epi16(r))
{
}

inline
x86vec::v8s16::v8s16(v8s16::element_type r, bool broadcast)
        : base_type(broadcast ?
                    _mm_set1_epi16(r) : 
		    _mm_set_epi16(0, 0, 0, 0, 0, 0, 0, r))
{
}

inline
x86vec::v8s16::v8s16(const mem::addr_bcast<element_type>& r)
        : base_type(_mm_set1_epi16(* (r())))
{
}

inline
x86vec::v8s16::v8s16(const mem::addr<element_type>& r)
        : base_type(is_aligned_to<16>::ptr(r()) ?
                    _mm_load_si128(m128i_ptr::make(r())) :
                    _mm_loadu_si128(m128i_ptr::make(r())))
{
}

inline
x86vec::v8s16::v8s16(const mem::aligned::addr<element_type>& r)
        : base_type(_mm_load_si128(m128i_ptr::make(r())))
{
}

inline
x86vec::v8s16::v8s16(const mem::unaligned::addr<element_type>& r)
        : base_type(_mm_loadu_si128(m128i_ptr::make(r())))
{
}

inline
x86vec::masked_vec<x86vec::v8s16>
x86vec::v8s16::operator()(const mask<v8s16>& m) 
{
	return masked_vec<v8s16>(*this, m);
}

inline
x86vec::v8s16&
x86vec::operator|= (v8s16& a, const v8s16& b)
{
        a = _mm_or_si128(a(), b());
        return a;
}

inline
x86vec::v8s16&
x86vec::operator&= (v8s16& a, const v8s16& b)
{
        a = _mm_and_si128(a(), b());
        return a;
}

inline
x86vec::v8s16&
x86vec::operator^= (v8s16& a, const v8s16& b)
{
        a = _mm_xor_si128(a(), b());
        return a;
}

inline
x86vec::v8s16&
x86vec::operator+= (v8s16& a, const v8s16& b)
{
        a = _mm_add_epi16(a(), b());
        return a;
}

inline
x86vec::v8s16&
x86vec::operator-= (v8s16& a, const v8s16& b)
{
        a = _mm_sub_epi16(a(), b());
        return a;
}

inline
x86vec::v8s16&
x86vec::operator*= (v8s16& a, const v8s16& b)
{
        a = impl::vpmullw::v(a(), b());
        return a;
}

inline
x86vec::v8s16&
x86vec::operator/=(v8s16& a, const v8s16& b)
{
        a= impl::div_s16::v(a(), b());
        return a;
}

inline
x86vec::v8s16&
x86vec::operator%=(v8s16& a, const v8s16& b)
{
        v8s16 q(a/b);
        a = cftal::remainder(a, b, q);
        return a;
}

template <unsigned _P>
inline
x86vec::v8s16&
x86vec::operator<<= (v8s16& a, const const_u32< _P >& b)
{
        const int val = b.val;
        a = impl::vpsllw_const<val>::v(a());
        return a;
}

inline
x86vec::v8s16&
x86vec::operator<<= (v8s16& a, uint32_t b)
{
        a = impl::vpsllw::v(a(), b);
        return a;
}

template <unsigned _P>
inline
x86vec::v8s16
x86vec::operator<< (const v8s16& a, const const_u32< _P >& b)
{
        const int val = b.val;
        return impl::vpsllw_const<val>::v(a());
}

inline
x86vec::v8s16
x86vec::operator<< (const v8s16& a, uint32_t b)
{
        return impl::vpsllw::v(a(), b);
}


template <unsigned _P>
inline
x86vec::v8s16&
x86vec::operator>>= (v8s16& a, const const_u32< _P >& b)
{
        const int val = b.val;
        a = impl::vpsraw_const<val>::v(a());
        return a;
}

inline
x86vec::v8s16&
x86vec::operator>>= (v8s16& a, uint32_t r)
{
        a = impl::vpsraw::v(a(), r);
        return a;
}

template <unsigned _P>
inline
x86vec::v8s16
x86vec::operator>> (const v8s16& a, const const_u32< _P >& b)
{
        const int val = b.val;
        return impl::vpsraw_const<val>::v(a());
}

inline
x86vec::v8s16
x86vec::operator>> (const v8s16& a, uint32_t r)
{
        return impl::vpsraw::v(a(), r);
}


inline
x86vec::v8s16&
x86vec::operator++(v8s16& a)
{
        const __m128i one = const_v8u16< 1, 1, 1, 1, 1, 1, 1, 1>::iv();
        a = _mm_add_epi16(a(), one);
        return a;
}

inline
x86vec::v8s16
x86vec::operator++ (v8s16& a, int)
{
        v8s16 t(a);
        const __m128i one = const_v8u16< 1, 1, 1, 1, 1, 1, 1, 1>::iv();
        a = _mm_add_epi16(a(), one);
        return t;
}

inline
x86vec::v8s16&
x86vec::operator--(v8s16& a)
{
        const __m128i one = const_v8u16< 1, 1, 1, 1, 1, 1, 1, 1>::iv();
        a = _mm_sub_epi16(a(), one);
        return a;
}

inline
x86vec::v8s16
x86vec::operator-- (v8s16& a, int)
{
        v8s16 t(a);
        const __m128i one = const_v8u16< 1, 1, 1, 1, 1, 1, 1, 1>::iv();
        a = _mm_sub_epi16(a(), one);
        return t;
}

inline
x86vec::v8s16
x86vec::operator-(const v8s16& a)
{
#if defined (__SSSE3__)
	const __m128i sgn_bits= v_sign_s16_msk::iv();
	return _mm_sign_epi16(a(), sgn_bits);
#else
        const __m128i zero = impl::make_zero_int::v();
        return _mm_sub_epi16(zero, a());
#endif
}

inline
const x86vec::v8s16&
x86vec::operator+(const v8s16& a)
{
	return a;
}


inline
x86vec::v8s16
x86vec::operator~(const v8s16& a)
{
        const __m128i all_set = const_v4u32<uint32_t(-1), uint32_t(-1), 
					    uint32_t(-1), uint32_t(-1)>::iv();
        return _mm_xor_si128(a(), all_set);
}

inline
x86vec::v8s16
x86vec::operator!(const v8s16& a)
{
        const __m128i msk = impl::make_zero_int::v();
        return _mm_cmpeq_epi16(a(), msk);
}

inline
x86vec::v8s16 x86vec::operator| (const v8s16& a, const v8s16& b)
{
        return _mm_or_si128(a(), b());
}

inline
x86vec::v8s16 x86vec::operator|| (const v8s16& a, const v8s16& b)
{
        return a | b;
}

inline
x86vec::v8s16 x86vec::operator& (const v8s16& a, const v8s16& b)
{
        return _mm_and_si128(a(), b());
}

inline
x86vec::v8s16 x86vec::operator&& (const v8s16& a, const v8s16& b)
{
        return a & b;
}

inline
x86vec::v8s16 x86vec::operator^(const v8s16& a, const v8s16& b)
{
        return _mm_xor_si128(a(), b());
}

inline
x86vec::v8s16 x86vec::operator+ (const v8s16& a, const v8s16& b)
{
        return _mm_add_epi16(a(), b());
}

inline
x86vec::v8s16 x86vec::operator- (const v8s16& a, const v8s16& b)
{
        return _mm_sub_epi16(a(), b());
}

inline
x86vec::v8s16 x86vec::operator* (const v8s16& a, const v8s16& b)
{
        return impl::vpmullw::v(a(), b());
}

inline
x86vec::v8s16
x86vec::operator/(const v8s16& a, const v8s16& b)
{
        return impl::div_s16::v(a(), b());
}

inline
x86vec::v8s16
x86vec::operator%(const v8s16& a, const v8s16& b)
{
        return cftal::remainder(a, b, a/b);
}

inline
x86vec::v8s16 x86vec::operator< (const v8s16& a, const v8s16& b)
{
        return _mm_cmpgt_epi16(b(), a());
}

inline
x86vec::v8s16 x86vec::operator<= (const v8s16& a, const v8s16& b)
{
	// a<= b: a == min(a, b);
	__m128i min_ab = _mm_min_epi16(b(), a());
	return _mm_cmpeq_epi16(a(), min_ab);
}

inline
x86vec::v8s16 x86vec::operator== (const v8s16& a, const v8s16& b)
{
        return _mm_cmpeq_epi16(a(), b());
}

inline
x86vec::v8s16 x86vec::operator!= (const v8s16& a, const v8s16& b)
{
        return ~(a == b);
}

inline
x86vec::v8s16 x86vec::operator>= (const v8s16& a, const v8s16& b)
{
	// a>= b: a == max(a, b);
	__m128i max_ab = _mm_max_epi16(b(), a());
	return _mm_cmpeq_epi16(a(), max_ab);
}

inline
x86vec::v8s16 x86vec::operator> (const v8s16& a, const v8s16& b)
{
        return _mm_cmpgt_epi16(a(), b());
}

inline
bool x86vec::all_signs(const v8s16& a)
{
        return all_signs_s16(a());
}

inline
bool x86vec::both_signs(const v8s16& a)
{
        return both_signs_s16(a());
}

inline
bool x86vec::no_signs(const v8s16& a)
{
        return no_signs_s16(a());
}

inline
x86vec::v8s16 x86vec::max(const v8s16& a, const v8s16& b)
{
        return v8s16(_mm_max_epi16(a(), b()));
}

inline
x86vec::v8s16 x86vec::min(const v8s16& a, const v8s16& b)
{
        return v8s16(_mm_min_epi16(a(), b()));
}

inline
x86vec::v8s16 x86vec::abs(const v8s16& a)
{
#if defined (__SSSE3__)
        return v8s16(_mm_abs_epi16(a()));
#else
        v8s16 neg(impl::make_zero_int::v());
        neg -= a;
        return max(a, neg);
#endif
}

inline
x86vec::v8s16 x86vec::add_sat(const v8s16& a, const v8s16& b)
{
	return _mm_adds_epi16(a(), b());
}

inline
x86vec::v8s16 x86vec::sub_sat(const v8s16& a, const v8s16& b)
{
	return _mm_subs_epi16(a(), b());
}

inline
x86vec::v8s16 x86vec::andnot(const v8s16& a, const v8s16& b)
{
	return _mm_andnot_si128(a(), b());
}

inline
x86vec::v8s16 x86vec::mul_hi(const v8s16& a, const v8s16& b)
{
	return impl::vpmulhw::v(a(), b());
}

inline
std::pair<x86vec::v8s16, x86vec::v8s16>
x86vec::mul_lo_hi(const v8s16& a, const v8s16& b)
{
	return std::make_pair(a*b, mul_hi(a,b));
}

template < bool _P0, bool _P1, bool _P2, bool _P3,
	   bool _P4, bool _P5, bool _P6, bool _P7 >
inline
x86vec::v8s16 x86vec::select(const v8s16& a, const v8s16& b)
{
        return select_u16 <
		_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7 > (a(), b());
}

inline
x86vec::v8s16 x86vec::select(const v8s16& msk,
                             const v8s16& on_true,
                             const v8s16& on_false)
{
        return select(msk(), on_true(), on_false());
}

template < int _P0, int _P1, int _P2, int _P3,
	   int _P4, int _P5, int _P6, int _P7 >
inline
x86vec::v8s16 x86vec::permute(const v8s16& a)
{
        return perm_u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>(a());
}

template < int _P0, int _P1, int _P2, int _P3,
	   int _P4, int _P5, int _P6, int _P7 >
inline
x86vec::v8s16 x86vec::permute(const v8s16& a, const v8s16& b)
{
        return perm_u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>(a(), b());
}

template <unsigned _I>
inline
x86vec::v8s16 x86vec::insert(const v8s16& a, typename v8s16::element_type v)
{
	return insert_u16<_I>(a(), v);
}

template <unsigned _I>
inline
typename x86vec::v8s16::element_type
x86vec::extract(const v8s16& a)
{
	return extract_u16<_I>(a());
}

// Local variables:
// mode: c++
// end:
#endif
