#if !defined (__X86VEC_IVEC_H__)
#define __X86VEC_IVEC_H__ 1

#include <cftal/x86vec_const.h>
#include <cftal/x86vec_vreg.h>
#include <cftal/x86vec_perm.h>
#include <cftal/x86vec_ops_1.h>
#include <cftal/mem_load.h>
#include <cftal/divisor.h>
#include <type_traits>
#include <limits>

namespace x86vec
{

	class v128u1 : public vreg<__m128i> {
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
                typedef int16_t element_type;
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

        template <uint32_t _P>
        v8s16& operator<<= (v8s16& a, const const_u32<_P>& b);
        v8s16& operator<<= (v8s16& a, uint32_t b);
        template <uint32_t _P>
        v8s16 operator <<(const v8s16& a, const const_u32<_P>& b);
        v8s16 operator <<(const v8s16& a, uint32_t b);

        template <uint32_t _P>
        v8s16& operator>>= (v8s16& a, const_u32<_P>& b);
        v8s16& operator>>= (v8s16& a, uint32_t b);
        template <uint32_t _P>
        v8s16 operator >>(const v8s16& a, const const_u32<_P>& b);
        v8s16 operator >>(const v8s16& a, uint32_t b);

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
	// low part in first, high part in second
	std::pair<v8s16, v8s16> wide_mul(const v8s16& a, const v8s16& b);

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
                typedef uint16_t element_type;
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

        template <uint32_t _P>
        v8u16& operator<<= (v8u16& a, const const_u32<_P>& b);
        v8u16& operator<<= (v8u16& a, uint32_t b);
        template <uint32_t _P>
        v8u16 operator <<(const v8u16& a, const const_u32<_P>& b);
        v8u16 operator <<(const v8u16& a, uint32_t b);

        template <uint32_t _P>
        v8u16& operator>>= (v8u16& a, const_u32<_P>& b);
        v8u16& operator>>= (v8u16& a, uint32_t b);
        template <uint32_t _P>
        v8u16 operator >>(const v8u16& a, const const_u32<_P>& b);
        v8u16 operator >>(const v8u16& a, uint32_t b);

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
	// low part in first, high part in second
	std::pair<v8u16, v8u16> wide_mul(const v8u16& a, const v8u16& b);

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
                typedef int32_t element_type;
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

        template <uint32_t _P>
        v4s32& operator<<= (v4s32& a, const const_u32<_P>& b);
        v4s32& operator<<= (v4s32& a, uint32_t b);
        template <uint32_t _P>
        v4s32 operator <<(const v4s32& a, const const_u32<_P>& b);
        v4s32 operator <<(const v4s32& a, uint32_t b);

        template <uint32_t _P>
        v4s32& operator>>= (v4s32& a, const_u32<_P>& b);
        v4s32& operator>>= (v4s32& a, uint32_t b);
        template <uint32_t _P>
        v4s32 operator >>(const v4s32& a, const const_u32<_P>& b);
        v4s32 operator >>(const v4s32& a, uint32_t b);

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
	// low part in first, high part in second
	std::pair<v4s32, v4s32> wide_mul(const v4s32& a, const v4s32& b);
	

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
                typedef uint32_t element_type;
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

        template <uint32_t _P>
        v4u32& operator<<= (v4u32& a, const const_u32<_P>& b);
        v4u32& operator<<= (v4u32& a, uint32_t b);
        template <uint32_t _P>
        v4u32 operator <<(const v4u32& a, const const_u32<_P>& b);
        v4u32 operator <<(const v4u32& a, uint32_t b);

        template <uint32_t _P>
        v4u32& operator>>= (v4u32& a, const_u32<_P>& b);
        v4u32& operator>>= (v4u32& a, uint32_t b);
        template <uint32_t _P>
        v4u32 operator >>(const v4u32& a, const const_u32<_P>& b);
        v4u32 operator >>(const v4u32& a, uint32_t b);

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
	// low part in first, high part in second
	std::pair<v4u32, v4u32> wide_mul(const v4u32& a, const v4u32& b);

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

        class v2s64 : public v128u1 {
        public:
                typedef int64_t element_type;
                typedef v128u1 base_type;
                v2s64() = default;
                v2s64(vector_type r);
                v2s64(const base_type& r);
                v2s64(element_type p00, element_type p01);
                // broadcast to all positions
                v2s64(element_type r);
                v2s64(element_type r, bool broadcast);
                v2s64(const mem::addr_bcast<element_type>& r);
                v2s64(const mem::addr<element_type>& r);
                v2s64(const mem::aligned::addr<element_type>& r);
                v2s64(const mem::unaligned::addr<element_type>& r);
        };

        v2s64& operator|= (v2s64& a, const v2s64& b);
        v2s64& operator&= (v2s64& a, const v2s64& b);
        v2s64& operator^= (v2s64& a, const v2s64& b);
        v2s64& operator+= (v2s64& a, const v2s64& b);
        v2s64& operator-= (v2s64& a, const v2s64& b);
        v2s64& operator*= (v2s64& a, const v2s64& b);
        v2s64& operator/= (v2s64& a, const v2s64& b);
        v2s64& operator%= (v2s64& a, const v2s64& b);

        template <uint32_t _P>
        v2s64& operator<<= (v2s64& a, const const_u32<_P>& b);
        v2s64& operator<<= (v2s64& a, uint32_t b);
        template <uint32_t _P>
        v2s64 operator <<(const v2s64& a, const const_u32<_P>& b);
        v2s64 operator <<(const v2s64& a, uint32_t b);

        template <uint32_t _P>
        v2s64& operator>>= (v2s64& a, const_u32<_P>& b);
        v2s64& operator>>= (v2s64& a, uint32_t b);
        template <uint32_t _P>
        v2s64 operator >>(const v2s64& a, const const_u32<_P>& b);
        v2s64 operator >>(const v2s64& a, uint32_t b);

        v2s64 operator++ (v2s64& a, int);
        v2s64& operator++(v2s64& a);
        v2s64 operator-- (v2s64& a, int);
        v2s64& operator--(v2s64& a);

        v2s64 operator-(const v2s64& a);
	const v2s64& operator+(const v2s64& a);
        v2s64 operator~(const v2s64& a);
        v2s64 operator!(const v2s64& a);

        v2s64 operator| (const v2s64& a, const v2s64& b);
        v2s64 operator|| (const v2s64& a, const v2s64& b);
        v2s64 operator& (const v2s64& a, const v2s64& b);
        v2s64 operator&& (const v2s64& a, const v2s64& b);
        v2s64 operator^(const v2s64& a, const v2s64& b);

        v2s64 operator+ (const v2s64& a, const v2s64& b);
        v2s64 operator- (const v2s64& a, const v2s64& b);
        v2s64 operator* (const v2s64& a, const v2s64& b);
        v2s64 operator/ (const v2s64& a, const v2s64& b);
        v2s64 operator% (const v2s64& a, const v2s64& b);

        v2s64 operator< (const v2s64& a, const v2s64& b);
        v2s64 operator<= (const v2s64& a, const v2s64& b);
        v2s64 operator== (const v2s64& a, const v2s64& b);
        v2s64 operator!= (const v2s64& a, const v2s64& b);
        v2s64 operator>= (const v2s64& a, const v2s64& b);
        v2s64 operator> (const v2s64& a, const v2s64& b);

        // checks the signs
        bool all_signs(const v2s64& a);
        // checks the signs
        bool both_signs(const v2s64& a);
        // checks the signs
        bool no_signs(const v2s64& a);

        v2s64 max(const v2s64& a, const v2s64& b);
        v2s64 min(const v2s64& a, const v2s64& b);
        v2s64 abs(const v2s64& a);
	v2s64 mulh(const v2s64& a, const v2s64& b);
	// low part in first, high part in second
	std::pair<v2s64, v2s64> wide_mul(const v2s64& a, const v2s64& b);

        template < bool _P0, bool _P1>
        v2s64 select(const v2s64& a, const v2s64& b);
        v2s64 select(const v2s64& msk, const v2s64& on_true,
                     const v2s64& on_false);

        template <int _P0, int _P1>
        v2s64 permute(const v2s64& a);
        template <int _P0, int _P1>
        v2s64 permute(const v2s64& a, const v2s64& b);

	template <unsigned _I>
	v2s64 insert(const v2s64& a, typename v2s64::element_type v);
	template <unsigned _I>
	typename v2s64::element_type extract(const v2s64& a);

        class v2u64 : public v2s64 {
        public:
                typedef uint64_t element_type;
                typedef v2s64 base_type;
                v2u64() = default;
                v2u64(vector_type r);
                v2u64(const base_type& r);
                v2u64(element_type r);
                v2u64(element_type r, bool broadcast);
                v2u64(element_type p00, element_type p01);
                v2u64(const mem::addr_bcast<element_type>& r);
                v2u64(const mem::addr<element_type>& r);
                v2u64(const mem::aligned::addr<element_type>& r);
                v2u64(const mem::unaligned::addr<element_type>& r);
        };

        v2u64& operator|= (v2u64& a, const v2u64& b);
        v2u64& operator&= (v2u64& a, const v2u64& b);
        v2u64& operator^= (v2u64& a, const v2u64& b);
        v2u64& operator+= (v2u64& a, const v2u64& b);
        v2u64& operator-= (v2u64& a, const v2u64& b);
        v2u64& operator*= (v2u64& a, const v2u64& b);
        v2u64& operator/= (v2u64& a, const v2u64& b);
        v2u64& operator%= (v2u64& a, const v2u64& b);

        template <uint32_t _P>
        v2u64& operator<<= (v2u64& a, const const_u32<_P>& b);
        v2u64& operator<<= (v2u64& a, uint32_t b);
        template <uint32_t _P>
        v2u64 operator <<(const v2u64& a, const const_u32<_P>& b);
        v2u64 operator <<(const v2u64& a, uint32_t b);

        template <uint32_t _P>
        v2u64& operator>>= (v2u64& a, const_u32<_P>& b);
        v2u64& operator>>= (v2u64& a, uint32_t b);
        template <uint32_t _P>
        v2u64 operator >>(const v2u64& a, const const_u32<_P>& b);
        v2u64 operator >>(const v2u64& a, uint32_t b);

        v2u64 operator++ (v2u64& a, int);
        v2u64& operator++(v2u64& a);
        v2u64 operator-- (v2u64& a, int);
        v2u64& operator--(v2u64& a);

        v2u64 operator-(const v2u64& a);
	const v2u64& operator+(const v2u64& a);
        v2u64 operator~(const v2u64& a);
        v2u64 operator!(const v2u64& a);

        v2u64 operator| (const v2u64& a, const v2u64& b);
        v2u64 operator|| (const v2u64& a, const v2u64& b);
        v2u64 operator& (const v2u64& a, const v2u64& b);
        v2u64 operator&& (const v2u64& a, const v2u64& b);
        v2u64 operator^(const v2u64& a, const v2u64& b);

        v2u64 operator+ (const v2u64& a, const v2u64& b);
        v2u64 operator- (const v2u64& a, const v2u64& b);
        v2u64 operator* (const v2u64& a, const v2u64& b);
        v2u64 operator/ (const v2u64& a, const v2u64& b);
        v2u64 operator% (const v2u64& a, const v2u64& b);

        v2u64 operator< (const v2u64& a, const v2u64& b);
        v2u64 operator<= (const v2u64& a, const v2u64& b);
        v2u64 operator== (const v2u64& a, const v2u64& b);
        v2u64 operator!= (const v2u64& a, const v2u64& b);
        v2u64 operator>= (const v2u64& a, const v2u64& b);
        v2u64 operator> (const v2u64& a, const v2u64& b);

        v2u64 max(const v2u64& a, const v2u64& b);
        v2u64 min(const v2u64& a, const v2u64& b);
	v2u64 mulh(const v2u64& a, const v2u64& b);
	// low part in first, high part in second
	std::pair<v2u64, v2u64> wide_mul(const v2u64& a, const v2u64& b);

        template < bool _P0, bool _P1>
        v2u64 select(const v2u64& a, const v2u64& b);
        v2u64 select(const v2u64& msk, const v2u64& on_true,
                     const v2u64& on_false);

        template < int _P0, int _P1>
        v2u64 permute(const v2u64& a);
        template < int _P0, int _P1>
        v2u64 permute(const v2u64& a, const v2u64& b);

	template <unsigned _I>
	v2u64 insert(const v2u64& a, typename v2u64::element_type v);
	template <unsigned _I>
	typename v2u64::element_type extract(const v2u64& a);

}

namespace std {

	// v8s16
	template <>
	struct is_signed<x86vec::v8s16> : public true_type {};
	template <>
	struct make_signed<x86vec::v8s16> {
		typedef x86vec::v8s16 type;
	};
	
	template <>
	struct is_unsigned<x86vec::v8s16> : public false_type {};
	template <>
	struct make_unsigned<x86vec::v8s16> {
		typedef x86vec::v8u16 type;
	};

	template <>
	struct numeric_limits<x86vec::v8s16> : 
		public numeric_limits<x86vec::v8s16::element_type> {};

	// v8u16
	template <>
	struct is_signed<x86vec::v8u16> : public false_type {};
	template <>
	struct make_signed<x86vec::v8u16> {
		typedef x86vec::v8s16 type;
	};

	template <>
	struct is_unsigned<x86vec::v8u16> : public true_type {};
	template <>
	struct make_unsigned<x86vec::v8u16> {
		typedef x86vec::v8u16 type;
	};

	template <>
	struct numeric_limits<x86vec::v8u16> : 
		public numeric_limits<x86vec::v8u16::element_type> {};

	// v4s32
	template <>
	struct is_signed<x86vec::v4s32> : public true_type {};
	template <>
	struct make_signed<x86vec::v4s32> {
		typedef x86vec::v4s32 type;
	};
	
	template <>
	struct is_unsigned<x86vec::v4s32> : public false_type {};
	template <>
	struct make_unsigned<x86vec::v4s32> {
		typedef x86vec::v4u32 type;
	};

	template <>
	struct numeric_limits<x86vec::v4s32> : 
		public numeric_limits<x86vec::v4s32::element_type> {};

	// v4u32
	template <>
	struct is_signed<x86vec::v4u32> : public false_type {};
	template <>
	struct make_signed<x86vec::v4u32> {
		typedef x86vec::v4s32 type;
	};

	template <>
	struct is_unsigned<x86vec::v4u32> : public true_type {};
	template <>
	struct make_unsigned<x86vec::v4u32> {
		typedef x86vec::v4u32 type;
	};

	template <>
	struct numeric_limits<x86vec::v4u32> : 
		public numeric_limits<x86vec::v4u32::element_type> {};

	// v2s64
	template <>
	struct is_signed<x86vec::v2s64> : public true_type {};
	template <>
	struct make_signed<x86vec::v2s64> {
		typedef x86vec::v2s64 type;
	};
	
	template <>
	struct is_unsigned<x86vec::v2s64> : public false_type {};
	template <>
	struct make_unsigned<x86vec::v2s64> {
		typedef x86vec::v2u64 type;
	};

	template <>
	struct numeric_limits<x86vec::v2s64> : 
		public numeric_limits<x86vec::v2s64::element_type> {};

	// v2u64
	template <>
	struct is_signed<x86vec::v2u64> : public false_type {};
	template <>
	struct make_signed<x86vec::v2u64> {
		typedef x86vec::v2s64 type;
	};

	template <>
	struct is_unsigned<x86vec::v2u64> : public true_type {};
	template <>
	struct make_unsigned<x86vec::v2u64> {
		typedef x86vec::v2u64 type;
	};

	template <>
	struct numeric_limits<x86vec::v2u64> : 
		public numeric_limits<x86vec::v2u64::element_type> {};

}

#include <cftal/x86vec_v128u1_inl.h>
#include <cftal/x86vec_v8s16_inl.h>
#include <cftal/x86vec_v8u16_inl.h>
#include <cftal/x86vec_v4s32_inl.h>
#include <cftal/x86vec_v4u32_inl.h>
#include <cftal/x86vec_v2s64_inl.h>
#include <cftal/x86vec_v2u64_inl.h>

// Local variables:
// mode: c++
// end:
#endif
