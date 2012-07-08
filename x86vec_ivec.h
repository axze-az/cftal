#if !defined (__X86VEC_IVEC_H__)
#define __X86VEC_IVEC_H__ 1

#include <cftal/x86vec_const.h>
#include <cftal/x86vec_vreg.h>
#include <cftal/x86vec_perm.h>
#include <cftal/x86vec_ops_1.h>
#include <cftal/divisor.h>

namespace x86vec
{

        class v128u1 : public vreg<__m128i>
        {
        public:
                typedef vreg<__m128i> base_type;
                v128u1() = default;
                v128u1(vector_type v);
                v128u1(const base_type& v);
        };

        v128u1 operator~(const v128u1& a);
        v128u1 operator| (const v128u1& a, const v128u1& b);
        v128u1& operator|= (v128u1& a, const v128u1& b);
        v128u1 operator|| (const v128u1& a, const v128u1& b);
        v128u1 operator& (const v128u1& a, const v128u1& b);
        v128u1& operator&= (v128u1& a, const v128u1& b);
        v128u1 operator&& (const v128u1& a, const v128u1& b);
        v128u1 operator^(const v128u1& a, const v128u1& b);
        v128u1& operator^= (v128u1& a, const v128u1& b);

        bool all(const v128u1& a);
        bool both(const v128u1& a);
        bool none(const v128u1& a);

        class v8s16 : public v128u1
        {
        public:
                typedef std::int16_t element_type;
                typedef v128u1 base_type;
                v8s16() = default;
                v8s16(vector_type r);
                v8s16(const base_type& r);
                v8s16(element_type p00, element_type p01,
                      element_type p02, element_type p03,
                      element_type p04, element_type p05,
                      element_type p06, element_type p07);
                // broadcast to all positions
                v8s16(element_type r);
                v8s16(element_type r, bool broadcast);
                v8s16(const mem::addr_bcast<element_type>& r);
                v8s16(const mem::addr<element_type>& r);
                v8s16(const mem::aligned::addr<element_type>& r);
                v8s16(const mem::unaligned::addr<element_type>& r);
        };

        v8s16& operator|= (v8s16& a, const v8s16& b);
        v8s16& operator&= (v8s16& a, const v8s16& b);
        v8s16& operator^= (v8s16& a, const v8s16& b);
        v8s16& operator+= (v8s16& a, const v8s16& b);
        v8s16& operator-= (v8s16& a, const v8s16& b);
        v8s16& operator*= (v8s16& a, const v8s16& b);
        v8s16& operator/= (v8s16& a, const v8s16& b);
        v8s16& operator%= (v8s16& a, const v8s16& b);

        template <std::uint32_t _P>
        v8s16& operator<<= (v8s16& a, const const_u32<_P>& b);
        v8s16& operator<<= (v8s16& a, std::uint32_t b);
        template <std::uint32_t _P>
        v8s16 operator <<(const v8s16& a, const const_u32<_P>& b);
        v8s16 operator <<(const v8s16& a, std::uint32_t b);

        template <std::uint32_t _P>
        v8s16& operator>>= (v8s16& a, const_u32<_P>& b);
        v8s16& operator>>= (v8s16& a, std::uint32_t b);
        template <std::uint32_t _P>
        v8s16 operator >>(const v8s16& a, const const_u32<_P>& b);
        v8s16 operator >>(const v8s16& a, std::uint32_t b);

        v8s16 operator++ (v8s16& a, int);
        v8s16& operator++(v8s16& a);
        v8s16 operator-- (v8s16& a, int);
        v8s16& operator--(v8s16& a);

        v8s16 operator-(const v8s16& a);
        v8s16 operator~(const v8s16& a);
        v8s16 operator!(const v8s16& a);

        v8s16 operator| (const v8s16& a, const v8s16& b);
        v8s16 operator|| (const v8s16& a, const v8s16& b);
        v8s16 operator& (const v8s16& a, const v8s16& b);
        v8s16 operator&& (const v8s16& a, const v8s16& b);
        v8s16 operator^(const v8s16& a, const v8s16& b);

        v8s16 operator+ (const v8s16& a, const v8s16& b);
        v8s16 operator- (const v8s16& a, const v8s16& b);
        v8s16 operator* (const v8s16& a, const v8s16& b);
        v8s16 operator/ (const v8s16& a, const v8s16& b);
        v8s16 operator% (const v8s16& a, const v8s16& b);

        v8s16 operator< (const v8s16& a, const v8s16& b);
        v8s16 operator<= (const v8s16& a, const v8s16& b);
        v8s16 operator== (const v8s16& a, const v8s16& b);
        v8s16 operator!= (const v8s16& a, const v8s16& b);
        v8s16 operator>= (const v8s16& a, const v8s16& b);
        v8s16 operator> (const v8s16& a, const v8s16& b);

        // checks the signs
        bool all_signs(const v8s16& a);
        // checks the signs
        bool both_signs(const v8s16& a);
        // checks the signs
        bool no_signs(const v8s16& a);

        v8s16 max(const v8s16& a, const v8s16& b);
        v8s16 min(const v8s16& a, const v8s16& b);
        v8s16 abs(const v8s16& a);
	v8s16 mulh(const v8s16& a, const v8s16& b);

        template < bool _P0, bool _P1, bool _P2, bool _P3,
		   bool _P4, bool _P5, bool _P6, bool _P7 >
        v8s16 select(const v8s16& a, const v8s16& b);
        v8s16 select(const v8s16& msk, const v8s16& on_true,
                     const v8s16& on_false);

        template < int _P0, int _P1, int _P2, int _P3,
		   int _P4, int _P5, int _P6, int _P7 >
        v8s16 permute(const v8s16& a);
        template < int _P0, int _P1, int _P2, int _P3,
		   int _P4, int _P5, int _P6, int _P7 >
        v8s16 permute(const v8s16& a, const v8s16& b);

        class v8u16 : public v8s16
        {
        public:
                typedef uint16_t element_type;
                typedef v8s16 base_type;
                v8u16();
                v8u16(vector_type r);
                v8u16(const base_type& r);
                v8u16(element_type r);
                v8u16(element_type r, bool broadcast);
                v8u16(element_type p00, element_type p01,
                      element_type p02, element_type p03,
                      element_type p04, element_type p05,
                      element_type p06, element_type p07);
                v8u16(const mem::addr_bcast<element_type>& r);
                v8u16(const mem::addr<element_type*>& r);
                v8u16(const mem::aligned::addr<element_type>& r);
                v8u16(const mem::unaligned::addr<element_type>& r);
        };


        class v4s32 : public v128u1
        {
        public:
                typedef int32_t element_type;
                typedef v128u1 base_type;
                v4s32();
                v4s32(vector_type r);
                v4s32(const base_type& r);
                v4s32(element_type r);
                v4s32(element_type r, bool broadcast);
                v4s32(element_type p00, element_type p01,
                      element_type p02, element_type p03);
                v4s32(const mem::addr_bcast<element_type>& r);
                v4s32(const mem::addr<element_type>& r);
                v4s32(const mem::aligned::addr<element_type>& r);
                v4s32(const mem::unaligned::addr<element_type>& r);
        };

        class v4u32 : public v4s32
        {
        public:
		typedef int32_t element_type;
		typedef v128u1 base_type;
		v4u32();
		v4u32(vector_type r);
		v4u32(const base_type& r);
		v4u32(element_type r);
		v4u32(element_type r, bool broadcast);
		v4u32(element_type p00, element_type p01,
		      element_type p02, element_type p03);
		v4u32(const mem::addr_bcast<element_type>& r);
		v4u32(const mem::addr<element_type>& r);
		v4u32(const mem::aligned::addr<element_type>& r);
		v4u32(const mem::unaligned::addr<element_type>& r);
        };
}

inline
x86vec::v128u1::v128u1(__m128i v) : base_type(v)
{
}

inline
x86vec::v128u1::v128u1(const base_type& v) : base_type(v)
{
}

inline
x86vec::v128u1&
x86vec::operator|= (v128u1& a, const v128u1& b)
{
        a = _mm_or_si128(a(), b());
        return a;
}

inline
x86vec::v128u1&
x86vec::operator&= (v128u1& a , const v128u1& b)
{
        a = _mm_and_si128(a(), b());
        return a;
}

inline
x86vec::v128u1&
x86vec::operator^= (v128u1& a, const v128u1& b)
{
        a = _mm_xor_si128(a(), b());
        return a;
}

inline
x86vec::v128u1
x86vec::operator~(const v128u1& r)
{
        const __m128i msk = const4_u32 < -1, -1, -1, -1 >::iv();
        return _mm_xor_si128(r(), msk);
}

inline
x86vec::v128u1
x86vec::operator| (const v128u1& a, const v128u1& b)
{
        return _mm_or_si128(a(), b());
}

inline
x86vec::v128u1
x86vec::operator|| (const v128u1& a, const v128u1& b)
{
        return a | b;
}

inline
x86vec::v128u1
x86vec::operator& (const v128u1& a, const v128u1& b)
{
        return _mm_and_si128(a(), b());
}

inline
x86vec::v128u1
x86vec::operator&& (const v128u1& a, const v128u1& b)
{
        return a & b;
}

inline
x86vec::v128u1
x86vec::operator^(const v128u1& a, const v128u1& b)
{
        return _mm_xor_si128(a(), b());
}

inline
bool
x86vec::all(const v128u1& a)
{
        return all_bits(a());
}

inline
bool
x86vec::both(const v128u1& a)
{
        return both_bits(a());
}

inline
bool
x86vec::none(const v128u1& a)
{
        return no_bits(a());
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
x86vec::v8s16::v8s16(x86vec::v8s16::element_type r, bool broadcast)
        : base_type(broadcast ?
                    _mm_set1_epi16(r) : _mm_cvtsi32_si128(r))
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
        a = _mm_mullo_epi16(a(), b());
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
        __m128i s = _mm_cvtsi32_si128(b);
        a = impl::vpsllw::v(a(), s);
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
        __m128i s = _mm_cvtsi32_si128(b);
        return impl::vpsllw::v(a(), s);
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
        __m128i s = _mm_cvtsi32_si128(r);
        a = impl::vpsraw::v(a(), s);
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
        __m128i s = _mm_cvtsi32_si128(r);
        return impl::vpsraw::v(a(), s);
}


inline
x86vec::v8s16&
x86vec::operator++(v8s16& a)
{
        const __m128i one = const8_u16< 1, 1, 1, 1, 1, 1, 1, 1>::iv();
        a = _mm_add_epi16(a(), one);
        return a;
}

inline
x86vec::v8s16
x86vec::operator++ (v8s16& a, int)
{
        v8s16 t(a);
        const __m128i one = const8_u16< 1, 1, 1, 1, 1, 1, 1, 1>::iv();
        a = _mm_add_epi16(a(), one);
        return t;
}

inline
x86vec::v8s16&
x86vec::operator--(v8s16& a)
{
        const __m128i one = const8_u16< 1, 1, 1, 1, 1, 1, 1, 1>::iv();
        a = _mm_sub_epi16(a(), one);
        return a;
}

inline
x86vec::v8s16
x86vec::operator-- (v8s16& a, int)
{
        v8s16 t(a);
        const __m128i one = const8_u16< 1, 1, 1, 1, 1, 1, 1, 1>::iv();
        a = _mm_sub_epi16(a(), one);
        return a;
}

inline
x86vec::v8s16
x86vec::operator-(const v8s16& a)
{
        const __m128i zero = impl::make_zero_int::v();
        return _mm_sub_epi16(zero, a());
}

inline
x86vec::v8s16
x86vec::operator~(const v8s16& a)
{
        const __m128i all_set = const4_u32 < -1, -1, -1, -1 >::iv();
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
        return _mm_mullo_epi16(a(), b());
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
        return _mm_or_si128(_mm_cmpgt_epi16(b(), a()),
                            _mm_cmpeq_epi16(b(), a()));
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
        return _mm_or_si128(_mm_cmpgt_epi16(a(), b()),
                            _mm_cmpeq_epi16(a(), b()));
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
x86vec::v8s16 x86vec::mulh(const v8s16& a, const v8s16& b)
{
	return _mm_mulhi_epi16(a(), b());
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

// Local variables:
// mode: c++
// end:
#endif
// kate: indent-mode cstyle; indent-width 8; replace-tabs on; ;
