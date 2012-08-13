#if !defined (__X86VEC_CVT_H__)
#define __X86VEC_CVT_H__ 1

#include <cftal/x86vec_intrin.h>
#include <cftal/x86vec_ivec.h>
#include <cftal/x86vec_fvec.h>
#include <utility>

namespace x86vec {
	
	// f32 --> f64
	v2f64 cvt_f32_f64_lo(const v4f32& v);
	v2f64 cvt_f32_f64_hi(const v4f32& v);
	std::pair<v2f64, v2f64> cvt_f32_f64(const v4f32& v);
	// f64 --> f32
	v4f32 cvt_f64_f32(const v2f64& v);
	v4f32 cvt_f64_f32(const v2f64& l, const v2f64& h);
	
	// s32 --> f64
	v2f64 cvt_s32_f64_lo(const v4s32& v);
	v2f64 cvt_s32_f64_hi(const v4s32& v);
	std::pair<v2f64, v2f64> cvt_s32_f64(const v4s32& v);
	// f64 --> s32 with rounding according to the actual rounding
	// mode
	v4s32 cvt_f64_s32(const v2f64& v);
	v4s32 cvt_f64_s32(const v2f64& l, const v2f64& h);
	// f64 --> s32 with truncation (round toward zero)
	v4s32 cvt_f64_trunc_s32(const v2f64& v);
	v4s32 cvt_f64_trunc_s32(const v2f64& l, const v2f64& h);

}

inline
x86vec::v2f64 x86vec::cvt_f32_f64_lo(const v4f32& v)
{
	return _mm_cvtps_pd(v());
}

inline
x86vec::v2f64 x86vec::cvt_f32_f64_hi(const v4f32& v)
{
	return cvt_f32_f64_lo(permute<2, 3, 2, 3>(v));
}

inline
std::pair<x86vec::v2f64, x86vec::v2f64> x86vec::cvt_f32_f64(const v4f32& v)
{
	return std::make_pair(cvt_f32_f64_lo(v), cvt_f32_f64_hi(v));
}

inline
x86vec::v4f32 x86vec::cvt_f64_f32(const v2f64& v)
{
	return _mm_cvtpd_ps(v());
}

inline
x86vec::v4f32 x86vec::cvt_f64_f32(const v2f64& l, const v2f64& h)
{
	v4f32 fl= cvt_f64_f32(l);
	v4f32 fh= cvt_f64_f32(h);
	return permute<0, 1, 4, 5>(fl, fh);
}


inline
x86vec::v2f64 x86vec::cvt_s32_f64_lo(const v4s32& v)
{
	return _mm_cvtepi32_pd(v());
}

inline
x86vec::v2f64 x86vec::cvt_s32_f64_hi(const v4s32& v)
{
	return cvt_s32_f64_lo(permute<2, 3, 2, 3>(v));
}

inline
std::pair<x86vec::v2f64, x86vec::v2f64> x86vec::cvt_s32_f64(const v4s32& v)
{
	return std::make_pair(cvt_s32_f64_lo(v), cvt_s32_f64_hi(v));
}

inline
x86vec::v4s32 x86vec::cvt_f64_s32(const v2f64& v)
{
	return _mm_cvtpd_epi32(v());
}

inline
x86vec::v4s32 x86vec::cvt_f64_s32(const v2f64& l, const v2f64& h)
{
	v4s32 fl= cvt_f64_s32(l);
	v4s32 fh= cvt_f64_s32(h);
	return permute<0, 1, 4, 5>(fl, fh);
}

inline
x86vec::v4s32 x86vec::cvt_f64_trunc_s32(const v2f64& v)
{
	return _mm_cvttpd_epi32(v());
}

inline
x86vec::v4s32 x86vec::cvt_f64_trunc_s32(const v2f64& l, const v2f64& h)
{
	v4s32 fl= cvt_f64_trunc_s32(l);
	v4s32 fh= cvt_f64_trunc_s32(h);
	return permute<0, 1, 4, 5>(fl, fh);
}


// Local variables:
// mode: c++
// end:
#endif
