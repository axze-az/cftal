#if !defined (__X86VEC_STORE_H__)
#define __X86VEC_STORE_H__ 1

#include <cftal/x86vec_ivec.h>
#include <cftal/x86vec_fvec.h>

namespace x86vec {

	namespace impl {
		
		template <class _T>
		void store_a(typename _T::element_type* p, const _T& a);

		template <class _T>
		void store_u(typename _T::element_type* p, const _T& a);


	}

	namespace aligned {
		void store(v8u16::element_type* p, const v8u16& r);
		void store(v8s16::element_type* p, const v8s16& r);
		void store(v4u32::element_type* p, const v4u32& r);
		void store(v4s32::element_type* p, const v4s32& r);
		void store(v4f32::element_type* p, const v4f32& r);
		void store(v2f64::element_type* p, const v2f64& r);
	}

	namespace unaligned {
		void store(v8u16::element_type* p, const v8u16& r);
		void store(v8s16::element_type* p, const v8s16& r);
		void store(v4u32::element_type* p, const v4u32& r);
		void store(v4s32::element_type* p, const v4s32& r);
		void store(v4f32::element_type* p, const v4f32& r);
		void store(v2f64::element_type* p, const v2f64& r);
	}

	namespace impl {

		// selects aligned/unaligned stores.
		template <class _T>
		void store(typename _T::element_type* p, const _T& a);
		
	}

	void store(v8u16::element_type* p, const v8u16& r);
	void store(v8s16::element_type* p, const v8s16& r);
	void store(v4u32::element_type* p, const v4u32& r);
	void store(v4s32::element_type* p, const v4s32& r);
	void store(v4f32::element_type* p, const v4f32& r);
	void store(v2f64::element_type* p, const v2f64& r);
}

namespace mem {

	using x86vec::store;
	namespace aligned {
		using x86vec::aligned::store;
	}
	namespace unaligned {
		using x86vec::unaligned::store;
	}
}

// implementation helpers.
template <class _T>
inline 
void
x86vec::impl::store_a(typename _T::element_type* p, const _T& a)
{
	typename _T::vector_type* pv= 
		ptr<typename _T::vector_type>::make(p);
	_mm_store_si128(pv, a());
}

template <class _T>
inline 
void
x86vec::impl::store_u(typename _T::element_type* p, const _T& a)
{
	typename _T::vector_type* pv= 
		ptr<typename _T::vector_type>::make(p);
	_mm_storeu_si128(pv, a());
}

// aligned stores
inline
void 
x86vec::aligned::store(v8s16::element_type* p, const v8s16& v)
{
	impl::store_a(p, v);
}

inline
void 
x86vec::aligned::store(v8u16::element_type* p, const v8u16& v)
{
	impl::store_a(p, v);
}

inline
void 
x86vec::aligned::store(v4s32::element_type* p, const v4s32& v)
{
	impl::store_a(p, v);
}

inline
void 
x86vec::aligned::store(v4u32::element_type* p, const v4u32& v)
{
	impl::store_a(p, v);
}

inline
void
x86vec::aligned::store(v4f32::element_type* p, const v4f32& v)
{
	_mm_store_ps(p, v());
}

inline
void
x86vec::aligned::store(v2f64::element_type* p, const v2f64& v)
{
	_mm_store_pd(p, v());
}

// unaligned stores
inline
void 
x86vec::unaligned::store(v8s16::element_type* p, const v8s16& v)
{
	impl::store_u(p, v);
}

inline
void 
x86vec::unaligned::store(v8u16::element_type* p, const v8u16& v)
{
	impl::store_u(p, v);
}

inline
void 
x86vec::unaligned::store(v4s32::element_type* p, const v4s32& v)
{
	impl::store_u(p, v);
}

inline
void 
x86vec::unaligned::store(v4u32::element_type* p, const v4u32& v)
{
	impl::store_a(p, v);
}

inline
void
x86vec::unaligned::store(v4f32::element_type* p, const v4f32& v)
{
	_mm_storeu_ps(p, v());
}

inline
void
x86vec::unaligned::store(v2f64::element_type* p, const v2f64& v)
{
	_mm_storeu_pd(p, v());
}

// impl store helper
template <class _T>
void 
x86vec::impl::store(typename _T::element_type* p, const _T& v)
{
	if (is_aligned_to<16>::ptr(p)) {
		aligned::store(p, v);
	} else {
		unaligned::store(p, v);
	}
}

inline
void 
x86vec::store(v8s16::element_type* p, const v8s16& v)
{
	impl::store(p, v);
}

inline
void 
x86vec::store(v8u16::element_type* p, const v8u16& v)
{
	impl::store(p, v);
}

inline
void 
x86vec::store(v4s32::element_type* p, const v4s32& v)
{
	impl::store(p, v);
}

inline
void 
x86vec::store(v4u32::element_type* p, const v4u32& v)
{
	impl::store(p, v);
}

inline
void
x86vec::store(v4f32::element_type* p, const v4f32& v)
{
	impl::store(p, v);
}

inline
void
x86vec::store(v2f64::element_type* p, const v2f64& v)
{
	impl::store(p, v);
}

// Local variables:
// mode: c++
// end:
#endif
