#if !defined (__X86VEC_CAST_H__)
#define __X86VEC_CAST_H__ 1

#include <cftal/x86vec_intrin.h>

namespace x86vec {

	namespace impl {

		template <typename _D, typename _S>
		struct cast {
			static const _D& v(const _S& r) {
				return static_cast<const _D&>(r);
			}
		};

		template <typename _SD>
		struct cast<_SD, _SD> {
			static const _SD& v(const _SD& r) {
				return r;
			}
		};

		// cast to __m128
		template <>
		struct cast<__m128, __m128d> {
			static __m128 v(const __m128d& r) {
				return _mm_castpd_ps(r);
			}
		};

		// cast to __m128
		template <>
		struct cast<__m128, __m128i> {
			static __m128 v(const __m128i& r) {
				return _mm_castsi128_ps(r);
			}
		};

		// cast to __m128d
		template <>
		struct cast<__m128d, __m128> {
			static __m128d v(const __m128& r) {
				return _mm_castps_pd(r);
			}
		};

		// cast to __m128d
		template <>
		struct cast<__m128d, __m128i> {
			static __m128d v(const __m128i& r) {
				return _mm_castsi128_pd(r);
			}
		};


		// cast to __m128i
		template <>
		struct cast<__m128i, __m128> {
			static __m128i v(const __m128& r) {
				return _mm_castps_si128(r);
			}
		};

		// cast to __m128i
		template <>
		struct cast<__m128i, __m128d> {
			static __m128i v(const __m128d& r) {
				return _mm_castpd_si128(r);
			}
		};

		template <class _T>
		struct vector_traits {
			typedef typename _T::vector_type vector_type;
			static vector_type v(const _T& r) {
				return r();
			}
		};

		template <>
		struct vector_traits<__m128> {
			typedef __m128 vector_type;
			static vector_type v(__m128 r) {
				return r;
			}
		};

		template <>
		struct vector_traits<__m128d> {
			typedef __m128d vector_type;
			static vector_type v(__m128d r) {
				return r;
			}
		};

		template <>
		struct vector_traits<__m128i> {
			typedef __m128i vector_type;
			static vector_type v(__m128i r) {
				return r;
			}
		};

#if defined __AVX__
		// cast to __m128d from __m256d
		template <>
		struct cast<__m128d, __m256d> {
			static __m128d v(const __m256d& r) {
				return _mm256_castpd256_pd128(r);
			}
		};

		// cast to __m256d from __m128d
		template <>
		struct cast<__m256d, __m128d> {
			static __m256d v(const __m128d& r) {
				return _mm256_castpd128_pd256(r);
			}
		};

		// cast to __m256d from __m256
		template <>
		struct cast<__m256d, __m256> {
			static __m256d v(const __m256& r) {
				return _mm256_castps_pd(r);
			}
		};

		// cast to __m256d from __m256i
		template <>
		struct cast<__m256d, __m256i> {
			static __m256d v(const __m256i& r) {
				return _mm256_castsi256_pd(r);
			}
		};

		// cast to __m128 from __m256
		template <>
		struct cast<__m128, __m256> {
			static __m128 v(const __m256& r) {
				return _mm256_castps256_ps128(r);
			}
		};

		// cast to __m256 from __m128
		template <>
		struct cast<__m256, __m128> {
			static __m256 v(const __m128& r) {
				return _mm256_castps128_ps256(r);
			}
		};

		// cast to __m256 from __m256d
		template <>
		struct cast<__m256, __m256d> {
			static __m256 v(const __m256d& r) {
				return _mm256_castpd_ps(r);
			}
		};

		// cast to __m256 from __m256i
		template <>
		struct cast<__m256, __m256i> {
			static __m256 v(const __m256i& r) {
				return _mm256_castsi256_ps(r);
			}
		};

		// cast to __m128i from __m256i
		template <>
		struct cast<__m128i, __m256i> {
			static __m128i v(const __m256i& r) {
				return _mm256_castsi256_si128(r);
			}
		};

		// cast to __m256i from __m128i
		template <>
		struct cast<__m256i, __m128i> {
			static __m256i v(const __m128i& r) {
				return _mm256_castsi128_si256(r);
			}
		};

		// cast to __m256i from __m256d
		template <>
		struct cast<__m256i, __m256d> {
			static __m256i v(const __m256d& r) {
				return _mm256_castpd_si256(r);
			}
		};

		// cast to __m256i from __m256
		template <>
		struct cast<__m256i, __m256> {
			static __m256i v(const __m256& r) {
				return _mm256_castps_si256(r);
			}
		};

		template <>
		struct vector_traits<__m256> {
			typedef __m256 vector_type;
			static vector_type v(__m256 r) {
				return r;
			}
		};

		template <>
		struct vector_traits<__m256d> {
			typedef __m256d vector_type;
			static vector_type v(__m256d r) {
				return r;
			}
		};

		template <>
		struct vector_traits<__m256i> {
			typedef __m256i vector_type;
			static vector_type v(__m256i r) {
				return r;
			}
		};
#endif


	}

	template <typename _D, typename _S>
	_D as(const _S& s);
}

template <typename _D, typename _S>
inline
_D x86vec::as(const _S& s)
{
	typedef impl::vector_traits<_D> dst_traits;
	typedef impl::vector_traits<_S> src_traits;
	typedef typename dst_traits::vector_type dst_type;
	typedef typename src_traits::vector_type src_type;
	return impl::cast<dst_type, src_type>::v(src_traits::v(s));
}


// Local variables:
// mode: c++
// end:
#endif
