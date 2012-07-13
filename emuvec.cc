#include "emuvec.h"
#include <algorithm>

emuvec::v8s16::v8s16() : base_type()
{
}

emuvec::v8s16::v8s16(const v8s16& r) : base_type(r)
{
}

emuvec::v8s16::v8s16(v8s16&& r) : base_type(std::move(r))
{
}


emuvec::v8s16::v8s16(element_type p00, element_type p01,
                     element_type p02, element_type p03,
                     element_type p04, element_type p05,
                     element_type p06, element_type p07)
        : base_type()
{
	element_type* p= begin();
	p[0] = p00; p[1] = p01; p[2] = p02; p[3] = p03;
	p[4] = p04; p[5] = p05; p[6] = p06; p[7] = p07;
}


emuvec::v8s16::v8s16(element_type r): base_type(r)
{
}

emuvec::v8s16::v8s16(emuvec::v8s16::element_type r, bool broadcast)
        : base_type(r)
{
	if (!broadcast)
		std::fill_n(begin()+1, N-1, 0);
}

emuvec::v8s16::v8s16(const mem::addr_bcast<element_type>& r)
        : base_type()
{
	std::fill_n(begin(), N, *r());
}

emuvec::v8s16::v8s16(const mem::addr<element_type>& r)
        : base_type()
{
	std::copy_n(r(), N, begin());
}

emuvec::v8s16&
emuvec::operator|= (v8s16& a, const v8s16& b)
{
	impl::v_or<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, b(), v8s16::N);
	return a;
}


emuvec::v8s16&
emuvec::operator&= (v8s16& a, const v8s16& b)
{
	impl::v_and<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, b(), v8s16::N);
	return a;
}

emuvec::v8s16&
emuvec::operator^= (v8s16& a, const v8s16& b)
{
	impl::v_xor<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, b(), v8s16::N);
	return a;
}


emuvec::v8s16&
emuvec::operator+= (v8s16& a, const v8s16& b)
{
	impl::v_add<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, b(), v8s16::N);
	return a;
}


emuvec::v8s16&
emuvec::operator-= (v8s16& a, const v8s16& b)
{
	impl::v_sub<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, b(), v8s16::N);
	return a;
}

emuvec::v8s16&
emuvec::operator*= (v8s16& a, const v8s16& b)
{
	impl::v_mul<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, b(), v8s16::N);
	return a;
}

emuvec::v8s16&
emuvec::operator/=(v8s16& a, const v8s16& b)
{
	impl::v_div<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, b(), v8s16::N);
	return a;
}

emuvec::v8s16&
emuvec::operator%=(v8s16& a, const v8s16& b)
{
	impl::v_irem<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, b(), v8s16::N);
	return a;
}


emuvec::v8s16&
emuvec::operator<<= (v8s16& a, uint32_t b)
{
	impl::v_sl<v8s16::element_type> ot(b);
	impl::v_assign_op(a(), ot, v8s16::N);
        return a;
}


emuvec::v8s16
emuvec::operator<< (const v8s16& a, uint32_t b)
{
	v8s16 r;
	impl::v_sl<v8s16::element_type> ot(b);
	impl::v_bi_op(r(), a(), ot, v8s16::N);
	return r;
}

emuvec::v8s16&
emuvec::operator>>= (v8s16& a, uint32_t b)
{
	impl::v_sr<v8s16::element_type> ot(b);
	impl::v_assign_op(a(), ot, v8s16::N);
        return a;
}

emuvec::v8s16
emuvec::operator>> (const v8s16& a, uint32_t b)
{
	v8s16 r;
	impl::v_sr<v8s16::element_type> ot(b);
	impl::v_bi_op(r(), a(), ot, v8s16::N);
	return r;
}

emuvec::v8s16&
emuvec::operator++(v8s16& a)
{
	impl::v_inc<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, v8s16::N);
	return a;
}

emuvec::v8s16
emuvec::operator++ (v8s16& a, int)
{
	v8s16 t(a);
	impl::v_inc<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, v8s16::N);
        return t;
}


emuvec::v8s16&
emuvec::operator--(v8s16& a)
{
	impl::v_dec<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, v8s16::N);
	return a;
}

emuvec::v8s16
emuvec::operator-- (v8s16& a, int)
{
	v8s16 t(a);
	impl::v_dec<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, v8s16::N);
        return t;
}

emuvec::v8s16
emuvec::operator-(const v8s16& a)
{
	v8s16 r;
	impl::v_neg<v8s16::element_type> ot;
	impl::v_un_op(r(), ot, a(), v8s16::N);
	return r;
}

const emuvec::v8s16&
emuvec::operator+(const v8s16& a)
{
	return a;
}


emuvec::v8s16
emuvec::operator~(const v8s16& a)
{
	v8s16 r;
	impl::v_not<v8s16::element_type> ot;
	impl::v_un_op(r(), ot, a(), v8s16::N);
	return r;
}


emuvec::v8s16
emuvec::operator!(const v8s16& a)
{
	v8s16 r;
	impl::v_log_not<v8s16::element_type> ot;
	impl::v_un_op(r(), ot, a(), v8s16::N);
	return r;
}

#if 0

emuvec::v8s16 emuvec::operator| (const v8s16& a, const v8s16& b)
{
        return _mm_or_si128(a(), b());
}


emuvec::v8s16 emuvec::operator|| (const v8s16& a, const v8s16& b)
{
        return a | b;
}


emuvec::v8s16 emuvec::operator& (const v8s16& a, const v8s16& b)
{
        return _mm_and_si128(a(), b());
}


emuvec::v8s16 emuvec::operator&& (const v8s16& a, const v8s16& b)
{
        return a & b;
}


emuvec::v8s16 emuvec::operator^(const v8s16& a, const v8s16& b)
{
        return _mm_xor_si128(a(), b());
}


emuvec::v8s16 emuvec::operator+ (const v8s16& a, const v8s16& b)
{
        return _mm_add_epi16(a(), b());
}


emuvec::v8s16 emuvec::operator- (const v8s16& a, const v8s16& b)
{
        return _mm_sub_epi16(a(), b());
}


emuvec::v8s16 emuvec::operator* (const v8s16& a, const v8s16& b)
{
        return _mm_mullo_epi16(a(), b());
}


emuvec::v8s16
emuvec::operator/(const v8s16& a, const v8s16& b)
{
        return impl::div_u16::v(a(), b());
}


emuvec::v8s16
emuvec::operator%(const v8s16& a, const v8s16& b)
{
        return cftal::remainder(a, b, a/b);
}


emuvec::v8s16 emuvec::operator< (const v8s16& a, const v8s16& b)
{
	v8s16 ta(a ^ v_sign_s16_msk::iv());
	v8s16 tb(b ^ v_sign_s16_msk::iv());
        return _mm_cmpgt_epi16(tb(), ta());
}


emuvec::v8s16 emuvec::operator<= (const v8s16& a, const v8s16& b)
{
	return ~(b > a);
}


emuvec::v8s16 emuvec::operator== (const v8s16& a, const v8s16& b)
{
        return _mm_cmpeq_epi16(a(), b());
}


emuvec::v8s16 emuvec::operator!= (const v8s16& a, const v8s16& b)
{
        return ~(a == b);
}


emuvec::v8s16 emuvec::operator>= (const v8s16& a, const v8s16& b)
{
	return ~(a < b);
}


emuvec::v8s16 emuvec::operator> (const v8s16& a, const v8s16& b)
{
	v8s16 ta(a ^ v_sign_s16_msk::iv());
	v8s16 tb(b ^ v_sign_s16_msk::iv());
        return _mm_cmpgt_epi16(ta(), tb());
}


emuvec::v8s16 emuvec::max(const v8s16& a, const v8s16& b)
{
#if defined (__SSE4_1__)
	return _mm_max_epu16(a(), b());
#else
	// add 0x8000
	__m128i a0= _mm_xor_si128(a(), v_sign_s16_msk::iv());
	// add 0x8000
	__m128i b0= _mm_xor_si128(b(), v_sign_s16_msk::iv());
	// signed max
	__m128i m0= _mm_max_epi16(a0, b0);
	// sub 0x8000
	return  _mm_xor_si128(m0, v_sign_s16_msk::iv());
#endif
}


emuvec::v8s16 emuvec::min(const v8s16& a, const v8s16& b)
{
#if defined (__SSE4_1__)
        return v8s16(_mm_min_epu16(a(), b()));
#else
	// add 0x8000
	__m128i a0= _mm_xor_si128(a(), v_sign_s16_msk::iv());
	// add 0x8000
	__m128i b0= _mm_xor_si128(b(), v_sign_s16_msk::iv());
	// signed min
	__m128i m0= _mm_min_epi16(a0 , b0);
	// sub 0x8000
	return  _mm_xor_si128(m0, v_sign_s16_msk::iv());
#endif
}


emuvec::v8s16 emuvec::mulh(const v8s16& a, const v8s16& b)
{
	return _mm_mulhi_epu16(a(), b());
}

template < bool _P0, bool _P1, bool _P2, bool _P3,
	   bool _P4, bool _P5, bool _P6, bool _P7 >

emuvec::v8s16 emuvec::select(const v8s16& a, const v8s16& b)
{
        return select_u16 <
		_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7 > (a(), b());
}


emuvec::v8s16 emuvec::select(const v8s16& msk,
                             const v8s16& on_true,
                             const v8s16& on_false)
{
        return select(msk(), on_true(), on_false());
}

template < int _P0, int _P1, int _P2, int _P3,
	   int _P4, int _P5, int _P6, int _P7 >

emuvec::v8s16 emuvec::permute(const v8s16& a)
{
        return perm_u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>(a());
}

template < int _P0, int _P1, int _P2, int _P3,
	   int _P4, int _P5, int _P6, int _P7 >

emuvec::v8s16 emuvec::permute(const v8s16& a, const v8s16& b)
{
        return perm_u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>(a(), b());
}

template <unsigned _I>

emuvec::v8s16 emuvec::insert(const v8s16& a, typename v8s16::element_type v)
{
	return insert_u16<_I>(a(), v);
}

template <unsigned _I>
typename emuvec::v8s16::element_type 
emuvec::extract(const v8s16& a)
{
	return extract_u16<_I>(a());
}

#endif

void catch_print_size() {}
