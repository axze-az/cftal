#if !defined (__X86VEC_H__)
#define __X86VEC_H__ 1

#include <mem_load.h>
#include <x86vec_load_store.h>
#include <x86vec_vreg.h>
#include <x86vec_ivec.h>
#include <cstdint>

#if 0
namespace x86vec {

	template <class _T>
	const _T* make_ptr(const void* p);

	const __m128i*
	make_m128i_ptr(const void* p);

	template <class _T>
	struct align {
	};

	class v8x16;
	class v8s16;
	class v8u16;

	class v4x32;
	class v4s32;
	class v4u32;

	class v8x16 : public ivec128 {
	public:
		v8x16() = default;
		typedef ivec128 base_type;
		explicit v8x16(vector_type r);
		explicit v8x16(const base_type& r);
		v8x16& operator+=(const v8x16& r);
		v8x16& operator-=(const v8x16& r);
		v8x16& operator*=(const v8x16& r);
		v8x16 operator-() const;
	};

	bool any(const v8x16& a);
	bool all(const v8x16& a);
	bool none(const v8x16& a);
	
	class v4x32 : public ivec128 {
	public:

	};

	class v8s16 : public v8x16 {
	public:
		typedef int16_t element_type;
		typedef v8x16 base_type;
		v8s16() = default;
		v8s16(vector_type r);
		v8s16(const base_type& r);
		v8s16(element_type r);
		v8s16(const v4s32& low, const v4s32& high);
		v8s16(const mem::addr_bcast<element_type>& r);
		v8s16(const mem::addr<element_type>& r);
		v8s16(const mem::aligned::addr<element_type>& r);
		v8s16(const mem::unaligned::addr<element_type>& r);
	};

	v8s16 max(const v8s16& a, const v8s16& b);
	v8s16 min(const v8s16& a, const v8s16& b);
	v8s16 abs(const v8s16& a);
	
	class v8u16 : public v8x16 {
	public:
		typedef uint16_t element_type;
		v8u16();
		v8u16(vector_type r);
		v8u16(const v8x16& r);
		v8u16(element_type r);
		v8u16(const mem::addr_bcast<element_type>& r);
		v8u16(const mem::addr<element_type*>& r);
		v8u16(const mem::aligned::addr<element_type>& r);
		v8u16(const mem::unaligned::addr<element_type>& r);
	};

	class v4s32 : public ivec128 {
	public:
		typedef int32_t element_type;
		v4s32();
		explicit v4s32(vector_type r);
		explicit v4s32(const ivec128& r);
		explicit v4s32(element_type r);
		v4s32(const mem::addr_bcast<element_type>& r);
		v4s32(const mem::addr<element_type>& r);
		v4s32(const mem::aligned::addr<element_type>& r);
		v4s32(const mem::unaligned::addr<element_type>& r);
		v4s32& operator+=(const v4s32& r);
		v4s32& operator-=(const v4s32& r);
		v4s32& operator*=(const v4s32& r);
	};

	// return a*b + c
	v8s16 mad(const v8s16& a, const v8s16& b, const v8s16& c);

	template <unsigned _P7, unsigned _P6, unsigned _P5, unsigned _P4,
		  unsigned _P3, unsigned _P2, unsigned _P1, unsigned _P0>
	v8s16 permute(const v8s16& v);

#define DECL_OP(op) \
template <class _T> _T operator op (const _T& a, const _T& b)

	DECL_OP(|);
	DECL_OP(&);
	DECL_OP(^);

	DECL_OP(+);
	DECL_OP(-);
	DECL_OP(*);
	DECL_OP(/);

#undef DECL_OP	
}

#define DEF_OP(op)					\
template <class _T>					\
inline							\
_T x86vec::operator op (const _T& a, const _T& b)	\
{							\
	_T t(a);					\
	t op##=b;					\
	return t;					\
}

DEF_OP(|)
DEF_OP(&)
DEF_OP(^)
DEF_OP(+)
DEF_OP(-)
DEF_OP(*)
DEF_OP(/)

#undef DEF_OP

template <class _T>
inline
const _T* x86vec::make_ptr(const void* p)
{
	return static_cast<_T*>(p);
}

inline
const __m128i* x86vec::make_m128i_ptr(const void* p)
{
	return static_cast<const __m128i*>(p);
}

inline 
x86vec::v8x16::v8x16(vector_type r) : base_type(r) {
}

inline
x86vec::v8x16::v8x16(const base_type& r) : base_type(r) {
}

inline
x86vec::v8x16&
x86vec::v8x16::operator+=(const v8x16& r)
{
	vector_type& m=(*this)();
	m = _mm_add_epi16(m, r());
	return *this;
}

inline
x86vec::v8x16&
x86vec::v8x16::operator-=(const v8x16& r)
{
	vector_type& m=(*this)();
	m = _mm_sub_epi16(m, r());
	return *this;
}

inline
x86vec::v8x16&
x86vec::v8x16::operator*=(const v8x16& r)
{
	vector_type& m=(*this)();
	m = _mm_mullo_epi16(m, r());
	return *this;
}

inline
bool
x86vec::any(const v8x16& a) 
{
	const uint32_t msk(0xAAAA);
	uint32_t v(_mm_movemask_epi8(a()));
	return (v & msk) != 0;
}

inline
bool
x86vec::all(const v8x16& a) 
{
	const uint32_t msk(0xAAAA);
	uint32_t v(_mm_movemask_epi8(a()));
	return (v & msk) == msk;
}

inline
bool
x86vec::none(const v8x16& a) 
{
	const uint32_t msk(0xAAAA);
	uint32_t v(_mm_movemask_epi8(a()));
	return (v & msk) == 0;
}

inline
x86vec::v8s16::v8s16(vector_type r) : base_type(r) 
{
}

inline
x86vec::v8s16::v8s16(const base_type& r) : base_type(r) 
{
}

inline
x86vec::v8s16::v8s16(element_type r) 
	: base_type( _mm_set1_epi16(r))
{
}

inline
x86vec::v8s16::v8s16(const mem::addr_bcast<element_type>& r) 
	: base_type( _mm_set1_epi16(*r()))
{
}

inline
x86vec::v8s16::v8s16(const mem::addr<element_type>& r) 
	: base_type(is_aligned_to<16>::ptr(r()) ?
		    _mm_load_si128(make_m128i_ptr(r())) :		
		    _mm_loadu_si128(make_m128i_ptr(r())))
{
}

inline
x86vec::v8s16::v8s16(const mem::aligned::addr<element_type>& r) 
	: base_type(_mm_load_si128(make_m128i_ptr(r())))
{
}

inline
x86vec::v8s16::v8s16(const mem::unaligned::addr<element_type>& r) 
	: base_type(_mm_loadu_si128(make_m128i_ptr(r())))
{
}

inline
x86vec::v8s16
x86vec::max(const v8s16& a, const v8s16& b)
{
	return v8s16(_mm_max_epi16(a(), b()));
}

inline
x86vec::v8s16
x86vec::min(const v8s16& a, const v8s16& b)
{
	return v8s16(_mm_min_epi16(a(), b()));
}

inline
x86vec::v8s16
x86vec::abs(const v8s16& a)
{
#if defined (__SSSE3__)
	return v8s16(_mm_abs_epi16(a()));
#else
	v8s16 zero(a ^ a);
	return max(zero -a, a);
#endif
}

inline
x86vec::v8s16
x86vec::mad(const v8s16& a, const v8s16& b, const v8s16& c)
{
#if !defined (__XOP__)
	return a*b + c;
#else
	return _mm_macc_epi16(a(), b(), c());
#endif	
} 



template <unsigned _P7, unsigned _P6, unsigned _P5, unsigned _P4,
	  unsigned _P3, unsigned _P2, unsigned _P1, unsigned _P0>
inline
x86vec::v8s16 
x86vec::permute(const v8s16& v) 
{
	typedef impl::perm1_u16<_P7,_P6,_P5,_P4,_P3,_P2,_P1,_P0> s_t;
	return s_t::v(v());
}
#endif

// Local variables:
// mode: c++
// end:
#endif
