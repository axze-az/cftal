#if !defined (__X86VEC_IVEC_H__)
#define __X86VEC_IVEC_H__ 1

#include <cftal/x86vec_const.h>
#include <cftal/x86vec_vreg.h>
#include <cftal/x86vec_perm.h>
#include <cftal/x86vec_ops_1.h>
#include <cftal/mem_load.h>
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

        class v8s16 : public v128u1 {
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
	const v8s16& operator+(const v8s16& a);
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

	template <unsigned _I>
	v8s16 insert(const v8s16& a, typename v8s16::element_type v);
	template <unsigned _I>
	typename v8s16::element_type extract(const v8s16& a);

        class v8u16 : public v8s16 {
        public:
                typedef std::uint16_t element_type;
                typedef v8s16 base_type;
                v8u16() = default;
                v8u16(vector_type r);
                v8u16(const base_type& r);
                v8u16(element_type r);
                v8u16(element_type r, bool broadcast);
                v8u16(element_type p00, element_type p01,
                      element_type p02, element_type p03,
                      element_type p04, element_type p05,
                      element_type p06, element_type p07);
                v8u16(const mem::addr_bcast<element_type>& r);
                v8u16(const mem::addr<element_type>& r);
                v8u16(const mem::aligned::addr<element_type>& r);
                v8u16(const mem::unaligned::addr<element_type>& r);
        };

        v8u16& operator|= (v8u16& a, const v8u16& b);
        v8u16& operator&= (v8u16& a, const v8u16& b);
        v8u16& operator^= (v8u16& a, const v8u16& b);
        v8u16& operator+= (v8u16& a, const v8u16& b);
        v8u16& operator-= (v8u16& a, const v8u16& b);
        v8u16& operator*= (v8u16& a, const v8u16& b);
        v8u16& operator/= (v8u16& a, const v8u16& b);
        v8u16& operator%= (v8u16& a, const v8u16& b);

        template <std::uint32_t _P>
        v8u16& operator<<= (v8u16& a, const const_u32<_P>& b);
        v8u16& operator<<= (v8u16& a, std::uint32_t b);
        template <std::uint32_t _P>
        v8u16 operator <<(const v8u16& a, const const_u32<_P>& b);
        v8u16 operator <<(const v8u16& a, std::uint32_t b);

        template <std::uint32_t _P>
        v8u16& operator>>= (v8u16& a, const_u32<_P>& b);
        v8u16& operator>>= (v8u16& a, std::uint32_t b);
        template <std::uint32_t _P>
        v8u16 operator >>(const v8u16& a, const const_u32<_P>& b);
        v8u16 operator >>(const v8u16& a, std::uint32_t b);

        v8u16 operator++ (v8u16& a, int);
        v8u16& operator++(v8u16& a);
        v8u16 operator-- (v8u16& a, int);
        v8u16& operator--(v8u16& a);

        v8u16 operator-(const v8u16& a);
	const v8u16& operator+(const v8u16& a);
        v8u16 operator~(const v8u16& a);
        v8u16 operator!(const v8u16& a);

        v8u16 operator| (const v8u16& a, const v8u16& b);
        v8u16 operator|| (const v8u16& a, const v8u16& b);
        v8u16 operator& (const v8u16& a, const v8u16& b);
        v8u16 operator&& (const v8u16& a, const v8u16& b);
        v8u16 operator^(const v8u16& a, const v8u16& b);

        v8u16 operator+ (const v8u16& a, const v8u16& b);
        v8u16 operator- (const v8u16& a, const v8u16& b);
        v8u16 operator* (const v8u16& a, const v8u16& b);
        v8u16 operator/ (const v8u16& a, const v8u16& b);
        v8u16 operator% (const v8u16& a, const v8u16& b);

        v8u16 operator< (const v8u16& a, const v8u16& b);
        v8u16 operator<= (const v8u16& a, const v8u16& b);
        v8u16 operator== (const v8u16& a, const v8u16& b);
        v8u16 operator!= (const v8u16& a, const v8u16& b);
        v8u16 operator>= (const v8u16& a, const v8u16& b);
        v8u16 operator> (const v8u16& a, const v8u16& b);

        v8u16 max(const v8u16& a, const v8u16& b);
        v8u16 min(const v8u16& a, const v8u16& b);
	v8u16 mulh(const v8u16& a, const v8u16& b);

        template < bool _P0, bool _P1, bool _P2, bool _P3,
		   bool _P4, bool _P5, bool _P6, bool _P7 >
        v8u16 select(const v8u16& a, const v8u16& b);
        v8u16 select(const v8u16& msk, const v8u16& on_true,
                     const v8u16& on_false);

        template < int _P0, int _P1, int _P2, int _P3,
		   int _P4, int _P5, int _P6, int _P7 >
        v8u16 permute(const v8u16& a);
        template < int _P0, int _P1, int _P2, int _P3,
		   int _P4, int _P5, int _P6, int _P7 >
        v8u16 permute(const v8u16& a, const v8u16& b);

	template <unsigned _I>
	v8u16 insert(const v8u16& a, typename v8u16::element_type v);
	template <unsigned _I>
	typename v8u16::element_type extract(const v8u16& a);
	
        class v4s32 : public v128u1 {
        public:
                typedef std::int32_t element_type;
                typedef v128u1 base_type;
                v4s32() = default;
                v4s32(vector_type r);
                v4s32(const base_type& r);
                v4s32(element_type p00, element_type p01,
                      element_type p02, element_type p03);
                // broadcast to all positions
                v4s32(element_type r);
                v4s32(element_type r, bool broadcast);
                v4s32(const mem::addr_bcast<element_type>& r);
                v4s32(const mem::addr<element_type>& r);
                v4s32(const mem::aligned::addr<element_type>& r);
                v4s32(const mem::unaligned::addr<element_type>& r);
        };

        v4s32& operator|= (v4s32& a, const v4s32& b);
        v4s32& operator&= (v4s32& a, const v4s32& b);
        v4s32& operator^= (v4s32& a, const v4s32& b);
        v4s32& operator+= (v4s32& a, const v4s32& b);
        v4s32& operator-= (v4s32& a, const v4s32& b);
        v4s32& operator*= (v4s32& a, const v4s32& b);
        v4s32& operator/= (v4s32& a, const v4s32& b);
        v4s32& operator%= (v4s32& a, const v4s32& b);

        template <std::uint32_t _P>
        v4s32& operator<<= (v4s32& a, const const_u32<_P>& b);
        v4s32& operator<<= (v4s32& a, std::uint32_t b);
        template <std::uint32_t _P>
        v4s32 operator <<(const v4s32& a, const const_u32<_P>& b);
        v4s32 operator <<(const v4s32& a, std::uint32_t b);

        template <std::uint32_t _P>
        v4s32& operator>>= (v4s32& a, const_u32<_P>& b);
        v4s32& operator>>= (v4s32& a, std::uint32_t b);
        template <std::uint32_t _P>
        v4s32 operator >>(const v4s32& a, const const_u32<_P>& b);
        v4s32 operator >>(const v4s32& a, std::uint32_t b);

        v4s32 operator++ (v4s32& a, int);
        v4s32& operator++(v4s32& a);
        v4s32 operator-- (v4s32& a, int);
        v4s32& operator--(v4s32& a);

        v4s32 operator-(const v4s32& a);
	const v4s32& operator+(const v4s32& a);
        v4s32 operator~(const v4s32& a);
        v4s32 operator!(const v4s32& a);

        v4s32 operator| (const v4s32& a, const v4s32& b);
        v4s32 operator|| (const v4s32& a, const v4s32& b);
        v4s32 operator& (const v4s32& a, const v4s32& b);
        v4s32 operator&& (const v4s32& a, const v4s32& b);
        v4s32 operator^(const v4s32& a, const v4s32& b);

        v4s32 operator+ (const v4s32& a, const v4s32& b);
        v4s32 operator- (const v4s32& a, const v4s32& b);
        v4s32 operator* (const v4s32& a, const v4s32& b);
        v4s32 operator/ (const v4s32& a, const v4s32& b);
        v4s32 operator% (const v4s32& a, const v4s32& b);

        v4s32 operator< (const v4s32& a, const v4s32& b);
        v4s32 operator<= (const v4s32& a, const v4s32& b);
        v4s32 operator== (const v4s32& a, const v4s32& b);
        v4s32 operator!= (const v4s32& a, const v4s32& b);
        v4s32 operator>= (const v4s32& a, const v4s32& b);
        v4s32 operator> (const v4s32& a, const v4s32& b);

        // checks the signs
        bool all_signs(const v4s32& a);
        // checks the signs
        bool both_signs(const v4s32& a);
        // checks the signs
        bool no_signs(const v4s32& a);

        v4s32 max(const v4s32& a, const v4s32& b);
        v4s32 min(const v4s32& a, const v4s32& b);
        v4s32 abs(const v4s32& a);
	v4s32 mulh(const v4s32& a, const v4s32& b);

        template < bool _P0, bool _P1, bool _P2, bool _P3>
        v4s32 select(const v4s32& a, const v4s32& b);
        v4s32 select(const v4s32& msk, const v4s32& on_true,
                     const v4s32& on_false);

        template < int _P0, int _P1, int _P2, int _P3 >
        v4s32 permute(const v4s32& a);
        template < int _P0, int _P1, int _P2, int _P3 >
        v4s32 permute(const v4s32& a, const v4s32& b);

	template <unsigned _I>
	v4s32 insert(const v4s32& a, typename v4s32::element_type v);
	template <unsigned _I>
	typename v4s32::element_type extract(const v4s32& a);

        class v4u32 : public v4s32 {
        public:
                typedef std::uint32_t element_type;
                typedef v4s32 base_type;
                v4u32() = default;
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

        v4u32& operator|= (v4u32& a, const v4u32& b);
        v4u32& operator&= (v4u32& a, const v4u32& b);
        v4u32& operator^= (v4u32& a, const v4u32& b);
        v4u32& operator+= (v4u32& a, const v4u32& b);
        v4u32& operator-= (v4u32& a, const v4u32& b);
        v4u32& operator*= (v4u32& a, const v4u32& b);
        v4u32& operator/= (v4u32& a, const v4u32& b);
        v4u32& operator%= (v4u32& a, const v4u32& b);

        template <std::uint32_t _P>
        v4u32& operator<<= (v4u32& a, const const_u32<_P>& b);
        v4u32& operator<<= (v4u32& a, std::uint32_t b);
        template <std::uint32_t _P>
        v4u32 operator <<(const v4u32& a, const const_u32<_P>& b);
        v4u32 operator <<(const v4u32& a, std::uint32_t b);

        template <std::uint32_t _P>
        v4u32& operator>>= (v4u32& a, const_u32<_P>& b);
        v4u32& operator>>= (v4u32& a, std::uint32_t b);
        template <std::uint32_t _P>
        v4u32 operator >>(const v4u32& a, const const_u32<_P>& b);
        v4u32 operator >>(const v4u32& a, std::uint32_t b);

        v4u32 operator++ (v4u32& a, int);
        v4u32& operator++(v4u32& a);
        v4u32 operator-- (v4u32& a, int);
        v4u32& operator--(v4u32& a);

        v4u32 operator-(const v4u32& a);
	const v4u32& operator+(const v4u32& a);
        v4u32 operator~(const v4u32& a);
        v4u32 operator!(const v4u32& a);

        v4u32 operator| (const v4u32& a, const v4u32& b);
        v4u32 operator|| (const v4u32& a, const v4u32& b);
        v4u32 operator& (const v4u32& a, const v4u32& b);
        v4u32 operator&& (const v4u32& a, const v4u32& b);
        v4u32 operator^(const v4u32& a, const v4u32& b);

        v4u32 operator+ (const v4u32& a, const v4u32& b);
        v4u32 operator- (const v4u32& a, const v4u32& b);
        v4u32 operator* (const v4u32& a, const v4u32& b);
        v4u32 operator/ (const v4u32& a, const v4u32& b);
        v4u32 operator% (const v4u32& a, const v4u32& b);

        v4u32 operator< (const v4u32& a, const v4u32& b);
        v4u32 operator<= (const v4u32& a, const v4u32& b);
        v4u32 operator== (const v4u32& a, const v4u32& b);
        v4u32 operator!= (const v4u32& a, const v4u32& b);
        v4u32 operator>= (const v4u32& a, const v4u32& b);
        v4u32 operator> (const v4u32& a, const v4u32& b);

        v4u32 max(const v4u32& a, const v4u32& b);
        v4u32 min(const v4u32& a, const v4u32& b);
	v4u32 mulh(const v4u32& a, const v4u32& b);

        template < bool _P0, bool _P1, bool _P2, bool _P3 >
        v4u32 select(const v4u32& a, const v4u32& b);
        v4u32 select(const v4u32& msk, const v4u32& on_true,
                     const v4u32& on_false);

        template < int _P0, int _P1, int _P2, int _P3 >
        v4u32 permute(const v4u32& a);
        template < int _P0, int _P1, int _P2, int _P3 >
        v4u32 permute(const v4u32& a, const v4u32& b);

	template <unsigned _I>
	v4u32 insert(const v4u32& a, typename v4u32::element_type v);
	template <unsigned _I>
	typename v4u32::element_type extract(const v4u32& a);
	
	//std::pair<v4s32, v4s32> mul(const v8s16& x, const v8u16& y);
	// std::pair<v4u32, v4u32> mul(const v8u16& x, const v8u16& y);
}

#include <cftal/x86vec_v128u1_inl.h>
#include <cftal/x86vec_v8s16_inl.h>
#include <cftal/x86vec_v8u16_inl.h>
#include <cftal/x86vec_v4s32_inl.h>
#include <cftal/x86vec_v4u32_inl.h>


// Local variables:
// mode: c++
// end:
#endif
