#include "x86vec_ops_1.h"
#include "x86vec_ins_ext.h"

__m128i x86vec::impl::div_u16::v(__m128i x, __m128i y, __m128i* rem)
{
	__m128i xt = vpsrld_const<16>::v(x);
	__m128i yt = vpsrld_const<16>::v(y);
	__m128 xf= _mm_cvtepi32_ps(xt);
	__m128 yf= _mm_cvtepi32_ps(yt);
	__m128 qf= _mm_div_ps(xf, yf);
	__m128i qo= _mm_cvttps_epi32(qf);
	const __m128i me= const8_u16<-1, 0, -1, 0,-1,0,-1, 0>::iv();
	xt = _mm_and_si128(x, me);
	yt = _mm_and_si128(y, me);
	xf = _mm_cvtepi32_ps(xt);
	yf = _mm_cvtepi32_ps(yt);
	qf = _mm_div_ps(xf, yf);
	__m128i q = _mm_cvttps_epi32(qf);
	qo = vpslld_const<16>::v(qo);
	q = _mm_and_si128(q, me);
	q = _mm_or_si128(q, qo);
	// set quotient to -1 where divisor is zero
	__m128i eqz= _mm_cmpeq_epi16(y, make_zero_int::v());
	q = _mm_or_si128(q, eqz);
	if (rem!=nullptr) {
		// multiply back and subtract
		xt = _mm_mullo_epi16(q, y);
		yt = _mm_sub_epi16(x, xt);
		_mm_store_si128(rem, yt);
	}
	return q;
}

__m128i x86vec::impl::div_s16::v(__m128i x, __m128i y, __m128i* rem)
{
	// shift even elements to odd positions
	__m128i xe = vpslld_const<16>::v(x);
	__m128i ye = vpslld_const<16>::v(y);
	// convert odd elements to int32_t
	__m128i xt = vpsrad_const<16>::v(x);
	__m128i yt = vpsrad_const<16>::v(y);
	// convert even elements to int32_t
	xe = vpsrad_const<16>::v(xe);
	ye = vpsrad_const<16>::v(ye);
	__m128 xf= _mm_cvtepi32_ps(xt);
	__m128 yf= _mm_cvtepi32_ps(yt);
	__m128 qf= _mm_div_ps(xf, yf);
	// odd results.
	__m128i qo= _mm_cvttps_epi32(qf);
	xf = _mm_cvtepi32_ps(xe);
	yf = _mm_cvtepi32_ps(ye);
	qf = _mm_div_ps(xf, yf);
	// even results
	__m128i q = _mm_cvttps_epi32(qf);
	// shift left odd results
	qo = vpslld_const<16>::v(qo);
	const __m128i me= const8_u16<-1, 0, -1, 0,-1,0,-1, 0>::iv();
	// mask out odd positions in q
	q = _mm_and_si128(q, me);
	// combine odd and even results
	q = _mm_or_si128(q, qo);
	// set quotient to -1 where divisor is zero
	__m128i eqz= _mm_cmpeq_epi16(y, make_zero_int::v());
	q = _mm_or_si128(q, eqz);
	if (rem!=nullptr) {
		// multiply back and subtract
		xt = _mm_mullo_epi16(q, y);
		yt = _mm_sub_epi16(x, xt);
		_mm_store_si128(rem, yt);
	}
	return q;
}

__m128i x86vec::impl::div_s32::v(__m128i x, __m128i y, __m128i* rem)
{
	__m128d xt= _mm_cvtepi32_pd(x);
	__m128d yt= _mm_cvtepi32_pd(y);
	__m128d qf= _mm_div_pd(xt, yt);
	__m128i q= _mm_cvttpd_epi32(qf);
	__m128i t= _mm_unpackhi_epi64(x, x);
	xt = _mm_cvtepi32_pd(t);
	t = _mm_unpackhi_epi64(y, y);
	yt = _mm_cvtepi32_pd(t);
	qf = _mm_div_pd(xt, yt);
	t = _mm_cvttpd_epi32(qf);
	q = _mm_unpacklo_epi64(q, t);
	// set quotient to -1 where divisor is zero
	__m128i eqz= _mm_cmpeq_epi32(y, make_zero_int::v());
	q = _mm_or_si128(q, eqz);
	if (rem != nullptr) {
		// multiply back and subtract
		t =  vpmulld::v(q, y);
		__m128i r = _mm_sub_epi32(x, t);
		_mm_store_si128(rem, r);
	}
	return q;
}

#if 1
__m128i x86vec::impl::div_u32::v(__m128i x, __m128i y, __m128i* rem)
{
	// add 2^31
	__m128i xs = _mm_add_epi32(x, v_sign_s32_msk::iv());
	__m128i ys = _mm_add_epi32(y, v_sign_s32_msk::iv());
	// generate dp fp constant: 2^31
	const int _2_pow_31_fp_h= (1023+31)<<20;
	__m128d _2_pow_31 =
		const4_u32<0, _2_pow_31_fp_h, 0, _2_pow_31_fp_h>::dv();
	// convert low halves to double
	__m128d xt = _mm_cvtepi32_pd(xs);
	__m128d yt = _mm_cvtepi32_pd(ys);
	// add 2^31
	xt = _mm_add_pd(xt, _2_pow_31);
	yt = _mm_add_pd(yt, _2_pow_31);
	__m128d q = _mm_div_pd(xt, yt);
	// convert back to uint32
	// compare against 2^31
	__m128d hm= _mm_cmple_pd(_2_pow_31, q);
	__m128d corr= _mm_and_pd(hm, _2_pow_31);
	// subtract 2^31 where necessary
	q = _mm_sub_pd(q, corr);
	// convert
	__m128i xm= _mm_slli_epi32(_mm_castpd_si128(hm), 31);
	xm = vpshufd<0,2, 0,2>::v(xm);
	// correct too large values
	__m128i qil=_mm_xor_si128(_mm_cvttpd_epi32(q), xm);

	// move high halves to low
	xs = _mm_unpackhi_epi64(xs, xs);
	ys = _mm_unpackhi_epi64(ys, ys);
	// convert to double
	xt = _mm_cvtepi32_pd(xs);
	yt = _mm_cvtepi32_pd(ys);
	// add 2^31
	xt = _mm_add_pd(xt, _2_pow_31);
	yt = _mm_add_pd(yt, _2_pow_31);
	q = _mm_div_pd(xt, yt);
	// convert back.
	hm = _mm_cmple_pd(_2_pow_31, q);
	corr =_mm_and_pd(hm, _2_pow_31);
	q = _mm_sub_pd(q, corr);
	xm= _mm_slli_epi32(_mm_castpd_si128(hm), 31);
	xm = vpshufd<0,2, 0,2>::v(xm);
	__m128i qih= _mm_xor_si128(_mm_cvttpd_epi32(q), xm);
	__m128i qi= _mm_unpacklo_epi64(qil, qih);
	// set quotient to -1 where y==0
	__m128i eqz= _mm_cmpeq_epi32(y, make_zero_int::v());
	qi = _mm_or_si128(qi, eqz);
	if (rem != nullptr) {
		// multiply back and subtract
		__m128i p =  vpmulld::v(qi, y);
		__m128i r = _mm_sub_epi32(x, p);
		_mm_store_si128(rem, r);
	}
	return qi;
}
#else

namespace {

	template <unsigned _I>
	struct udiv32 {
		static void div(__m128i& q, __m128i x, __m128i y);
		static void div(__m128i& q, __m128i& r, __m128i x, __m128i y);
	};

	template <unsigned _I>
	inline
	void udiv32<_I>::div(__m128i& q, __m128i& r, __m128i x, __m128i y)
	{
		using namespace x86vec;
		std::uint32_t xi= extract_u32<_I>(x);
		std::uint32_t yi= extract_u32<_I>(y);
		std::uint32_t qi, ri;
		if (yi != 0) {
			qi = xi / yi;
			ri = xi % yi;
		} else {
			qi = std::uint32_t(-1);
			ri = xi;
		}
		if (_I == 0) {
			q = _mm_set_epi32(0, 0, 0, qi);
			r = _mm_set_epi32(0, 0, 0, ri);
		} else {
			q = insert_u32<_I>(q, qi);
			r = insert_u32<_I>(r, ri);
		}
	}

	template <unsigned _I>
	inline
	void udiv32<_I>::div(__m128i& q, __m128i x, __m128i y)
	{
		using namespace x86vec;
		std::uint32_t xi= extract_u32<_I>(x);
		std::uint32_t yi= extract_u32<_I>(y);
		std::uint32_t qi;
		if (yi != 0) {
			qi = xi / yi;
		} else {
			qi = std::uint32_t(-1);
		}
		if (_I == 0) {
			q = _mm_set_epi32(0, 0, 0, qi);
		} else {
			q = insert_u32<_I>(q, qi);
		}
	}

}

__m128i x86vec::impl::div_u32::v(__m128i x, __m128i y, __m128i* r)
{
#if 0
	return ref(x, y, r);
#else
	__m128i q;
	if (r) {
		udiv32<0>::div(q, *r, x, y);
		udiv32<1>::div(q, *r, x, y);
		udiv32<2>::div(q, *r, x, y);
		udiv32<3>::div(q, *r, x, y);
	} else {
		udiv32<0>::div(q, x, y);
		udiv32<1>::div(q, x, y);
		udiv32<2>::div(q, x, y);
		udiv32<3>::div(q, x, y);
	}
	return q;
#endif
}

#endif

extern "C" double cvt_u32_double(uint32_t t);
extern "C" double cvt_u64_double(uint64_t t);
extern "C" uint64_t cvt_double_uint64(double x);
extern "C" uint32_t cvt_double_uint32(double x);

double cvt_u32_double(uint32_t t)
{
	return double(t);
}

#if defined (__x86_64__)
double cvt_u64_double(uint64_t t)
{
	return double(t);
}

uint64_t cvt_double_uint64(double x)
{
	return uint64_t(x);
}
#endif

uint32_t cvt_double_uint32(double x)
{
	return uint32_t(x);
}




