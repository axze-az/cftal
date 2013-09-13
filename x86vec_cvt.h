#if !defined (__X86VEC_CVT_H__)
#define __X86VEC_CVT_H__ 1

#include <cftal/x86vec_intrin.h>
#include <cftal/x86vec_ivec.h>
#include <cftal/x86vec_fvec.h>
#include <utility>

namespace x86vec {

	namespace impl {

		// convert according to current rounding mode
		template <typename _D, typename _S>
		struct cvt {
			static 
			_D l(const _S& s);
			static
			_D h(const _S& s);
		};

		// convert with truncation (i.e. round to zero)
		template <typename _D, typename _S>
		struct cvt_rz {
			static
			_D l(const _S& s);
			static
			_D h(const _S& s);
		};

		template <>
		struct cvt<v4f32, v2f64> {
			static v4f32 l(const v2f64& d) {
				return _mm_cvtpd_ps(d());
			}
		};

		template <>
		struct cvt<v2f64, v4f32> {
			static v2f64 l(const v4f32& d) {
				return _mm_cvtps_pd(d());
			}
			static v2f64 h(const v4f32& d) {
				return l(permute<2,3,0,1>(d));
			}
		};

		template <>
		struct cvt<v4s32, v2f64> {
			static v4s32 l(const v2f64& d) {
				return _mm_cvtpd_epi32(d());
			}
		};

		template <>
		struct cvt_rz<v4s32, v2f64> {
			static v4s32 l(const v2f64& d) {
				return _mm_cvttpd_epi32(d());
			}
		};

		template <>
		struct cvt<v2f64, v4s32> {
			static v2f64 l(const v4s32& d) {
				return _mm_cvtepi32_pd(d());
			};
			static v2f64 h(const v4s32& d) {
				return l(permute<2,3,0,1>(d));
			}
		};

		template <>
		struct cvt<v4f32, v4s32> {
			static v4f32 l(const v4s32& s) {
				return _mm_cvtepi32_ps(s());
			}
		};

		template <>
		struct cvt<v4s32, v4f32> {
			static v4s32 l(const v4f32& s) {
				return _mm_cvtps_epi32(s());
			}
		};

		template <>
		struct cvt_rz<v4s32, v4f32> {
			static v4s32 l(const v4f32& s) {
				return _mm_cvttps_epi32(s());
			}
		};

#if defined (__AVX__)
		template <>
		struct cvt<v4s32, v4f64> {
			static v4s32 l(const v4f64& s) {
				return _mm256_cvtpd_epi32(s());
			}
		};

		template <>
		struct cvt_rz<v4s32, v4f64> {
			static v4s32 l(const v4f64& s) {
				return _mm256_cvttpd_epi32(s());
			}
		};

		template <>
		struct cvt<v4f64, v4s32> {
			static v4f64 l(const v4s32&s) {
				return _mm256_cvtepi32_pd(s());
			}
		};

		template <>
		struct cvt<v4f32, v4f64> {
			static v4f32 l(const v4f64& s) {
				return _mm256_cvtpd_ps(s());
			}
		};

		
		template <>
		struct cvt<v4f64, v4f32> {
			static v4f64 l(const v4f32& s) {
				return _mm256_cvtps_pd(s());
			}
		};

		template <>
		struct cvt<v4f64, v8f32> {
			static v4f64 l(const v8f32& a) {
				return cvt<v4f64, v4f32>::l(low_half(a));
			}
			static v4f64 h(const v8f32& a) {
				return cvt<v4f64, v4f32>::l(high_half(a));
			}
		};

#endif

	}
	
	template <class _D, class _S>
	_D cvt_lo(const _S& s);
	template <class _D, class _S>
	_D cvt_hi(const _S& s);
	template <class _D, class _S>
	_D cvt(const _S& s);

	v4f32 cvt_f32(const v2f64& l, const v2f64& h);
	v8f32 cvt_f32(const v4f64& l, const v4f64& h);

	template <class _D, class _S>
	std::pair<_D, _D> cvt_widen(const _S& s);
	
	template <class _D, class _S>
	_D cvt_rz_lo(const _S& s);
	template <class _D, class _S>
	_D cvt_rz_hi(const _S& s);
	template <class _D, class _S>
	_D cvt_rz(const _S& s);
	template <class _D, class _S>
	std::pair<_D, _D> cvt_rz_widen(const _S& s);

}

template <class _D, class _S>
inline
_D x86vec::cvt_lo(const _S& s)
{
	return impl::cvt<_D, _S>::l(s);
}

template <class _D, class _S>
inline
_D x86vec::cvt_hi(const _S& s)
{
	return impl::cvt<_D, _S>::h(s);
}

template <class _D, class _S>
inline
_D x86vec::cvt(const _S& s)
{
	return impl::cvt<_D, _S>::l(s);
}

template <class _D, class _S>
inline
std::pair<_D, _D> x86vec::cvt_widen(const _S& s)
{
	_D l=cvt_lo<_D>(s);
	_D h=cvt_hi<_D>(s);
	return std::make_pair(l, h);
}

inline
x86vec::v4f32 x86vec::cvt_f32(const v2f64& l, const v2f64& h)
{
	v4f32 lf(cvt<v4f32>(l));
	v4f32 hf(cvt<v4f32>(h));
	return permute<0, 1, 4, 5>(lf, hf);
}

inline
x86vec::v8f32 x86vec::cvt_f32(const v4f64& l, const v4f64& h)
{
	v4f32 lf(cvt<v4f32>(l));
	v4f32 hf(cvt<v4f32>(h));
	return v8f32(lf, hf);
}


template <class _D, class _S>
inline
_D x86vec::cvt_rz_lo(const _S& s)
{
	return impl::cvt_rz<_D, _S>::l(s);
}

template <class _D, class _S>
inline
_D x86vec::cvt_rz_hi(const _S& s)
{
	return impl::cvt_rz<_D, _S>::h(s);
}

template <class _D, class _S>
inline
_D x86vec::cvt_rz(const _S& s)
{
	return impl::cvt_rz<_D, _S>::l(s);
}

template <class _D, class _S>
inline
std::pair<_D, _D> x86vec::cvt_rz_widen(const _S& s)
{
	_D l=cvt_rz_lo<_D>(s);
	_D h=cvt_rz_hi<_D>(s);
	return std::make_pair(l, h);
}



// Local variables:
// mode: c++
// end:
#endif
