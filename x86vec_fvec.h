#if !defined (__X86VEC_FVEC_H__)
#define __X86VEC_FVEC_H__ 1

#include <cftal/x86vec_const.h>
#include <cftal/x86vec_vreg.h>
#include <cftal/x86vec_perm.h>
#include <cftal/x86vec_ops_1.h>
#include <cftal/mem_load.h>
#include <cftal/divisor.h>
#include <cfenv>

namespace x86vec {

	namespace impl {

		struct rounding_mode {
			enum type {
				nearest = 0x0,
				downward = 0x1,
				upward = 0x2,
				towardzero = 0x3
			};
		};
	}

        class v4f32 : public vreg<__m128> {
        public:
                typedef float element_type;
                typedef vreg<__m128> base_type;
                v4f32() = default;
                v4f32(vector_type r);
                v4f32(const base_type& r);
                v4f32(element_type p00, element_type p01,
                      element_type p02, element_type p03);
                // broadcast to all positions
                v4f32(element_type r);
                v4f32(element_type r, bool broadcast);
                v4f32(const mem::addr_bcast<element_type>& r);
                v4f32(const mem::addr<element_type>& r);
                v4f32(const mem::aligned::addr<element_type>& r);
                v4f32(const mem::unaligned::addr<element_type>& r);
        };

        v4f32& operator|= (v4f32& a, const v4f32& b);
        v4f32& operator&= (v4f32& a, const v4f32& b);
        v4f32& operator^= (v4f32& a, const v4f32& b);
        v4f32& operator+= (v4f32& a, const v4f32& b);
        v4f32& operator-= (v4f32& a, const v4f32& b);
        v4f32& operator*= (v4f32& a, const v4f32& b);
        v4f32& operator/= (v4f32& a, const v4f32& b);
	
        v4f32 operator++ (v4f32& a, int);
        v4f32& operator++(v4f32& a);
        v4f32 operator-- (v4f32& a, int);
        v4f32& operator--(v4f32& a);

        v4f32 operator-(const v4f32& a);
	const v4f32& operator+(const v4f32& a);
        v4f32 operator~(const v4f32& a);
        v4f32 operator!(const v4f32& a);

        v4f32 operator| (const v4f32& a, const v4f32& b);
        v4f32 operator|| (const v4f32& a, const v4f32& b);
        v4f32 operator& (const v4f32& a, const v4f32& b);
        v4f32 operator&& (const v4f32& a, const v4f32& b);
        v4f32 operator^(const v4f32& a, const v4f32& b);

        v4f32 operator+ (const v4f32& a, const v4f32& b);
        v4f32 operator- (const v4f32& a, const v4f32& b);
        v4f32 operator* (const v4f32& a, const v4f32& b);
        v4f32 operator/ (const v4f32& a, const v4f32& b);
	
        v4f32 operator< (const v4f32& a, const v4f32& b);
        v4f32 operator<= (const v4f32& a, const v4f32& b);
        v4f32 operator== (const v4f32& a, const v4f32& b);
        v4f32 operator!= (const v4f32& a, const v4f32& b);
        v4f32 operator>= (const v4f32& a, const v4f32& b);
        v4f32 operator> (const v4f32& a, const v4f32& b);

        // checks the signs
        bool all_signs(const v4f32& a);
        // checks the signs
        bool both_signs(const v4f32& a);
        // checks the signs
        bool no_signs(const v4f32& a);

        v4f32 max(const v4f32& a, const v4f32& b);
        v4f32 min(const v4f32& a, const v4f32& b);
        v4f32 abs(const v4f32& a);
	v4f32 sqrt(const v4f32& a);

	namespace impl {
		v4f32 round(const v4f32& a, const rounding_mode::type  m);
	}
	v4f32 rint(const v4f32& a);
	v4f32 floor(const v4f32& a);
	v4f32 ceil(const v4f32& a);
	v4f32 trunc(const v4f32& a);

        template < bool _P0, bool _P1, bool _P2, bool _P3>
        v4f32 select(const v4f32& a, const v4f32& b);
        v4f32 select(const v4f32& msk, const v4f32& on_true,
                     const v4f32& on_false);

        template < int _P0, int _P1, int _P2, int _P3 >
        v4f32 permute(const v4f32& a);
        template < int _P0, int _P1, int _P2, int _P3 >
        v4f32 permute(const v4f32& a, const v4f32& b);

	template <unsigned _I>
	v4f32 insert(const v4f32& a, typename v4f32::element_type v);
	template <unsigned _I>
	typename v4f32::element_type extract(const v4f32& a);

        class v2f64 : public vreg<__m128d> {
        public:
                typedef double element_type;
                typedef vreg<__m128d> base_type;
                v2f64() = default;
                v2f64(vector_type r);
                v2f64(const base_type& r);
                v2f64(element_type p00, element_type p01);
                // broadcast to all positions
                v2f64(element_type r);
                v2f64(element_type r, bool broadcast);
                v2f64(const mem::addr_bcast<element_type>& r);
                v2f64(const mem::addr<element_type>& r);
                v2f64(const mem::aligned::addr<element_type>& r);
                v2f64(const mem::unaligned::addr<element_type>& r);
        };

        v2f64& operator|= (v2f64& a, const v2f64& b);
        v2f64& operator&= (v2f64& a, const v2f64& b);
        v2f64& operator^= (v2f64& a, const v2f64& b);
        v2f64& operator+= (v2f64& a, const v2f64& b);
        v2f64& operator-= (v2f64& a, const v2f64& b);
        v2f64& operator*= (v2f64& a, const v2f64& b);
        v2f64& operator/= (v2f64& a, const v2f64& b);
	
        v2f64 operator++ (v2f64& a, int);
        v2f64& operator++(v2f64& a);
        v2f64 operator-- (v2f64& a, int);
        v2f64& operator--(v2f64& a);

        v2f64 operator-(const v2f64& a);
	const v2f64& operator+(const v2f64& a);
        v2f64 operator~(const v2f64& a);
        v2f64 operator!(const v2f64& a);

        v2f64 operator| (const v2f64& a, const v2f64& b);
        v2f64 operator|| (const v2f64& a, const v2f64& b);
        v2f64 operator& (const v2f64& a, const v2f64& b);
        v2f64 operator&& (const v2f64& a, const v2f64& b);
        v2f64 operator^(const v2f64& a, const v2f64& b);

        v2f64 operator+ (const v2f64& a, const v2f64& b);
        v2f64 operator- (const v2f64& a, const v2f64& b);
        v2f64 operator* (const v2f64& a, const v2f64& b);
        v2f64 operator/ (const v2f64& a, const v2f64& b);
	
        v2f64 operator< (const v2f64& a, const v2f64& b);
        v2f64 operator<= (const v2f64& a, const v2f64& b);
        v2f64 operator== (const v2f64& a, const v2f64& b);
        v2f64 operator!= (const v2f64& a, const v2f64& b);
        v2f64 operator>= (const v2f64& a, const v2f64& b);
        v2f64 operator> (const v2f64& a, const v2f64& b);

        // checks the signs
        bool all_signs(const v2f64& a);
        // checks the signs
        bool both_signs(const v2f64& a);
        // checks the signs
        bool no_signs(const v2f64& a);

        v2f64 max(const v2f64& a, const v2f64& b);
        v2f64 min(const v2f64& a, const v2f64& b);
        v2f64 abs(const v2f64& a);
	v2f64 sqrt(const v2f64& a);

	namespace impl {
		v2f64 round(const v2f64& a, const rounding_mode::type m);
	}
	v2f64 rint(const v2f64& a);
	v2f64 floor(const v2f64& a);
	v2f64 ceil(const v2f64& a);
	v2f64 trunc(const v2f64& a);

        template < bool _P0, bool _P1>
        v2f64 select(const v2f64& a, const v2f64& b);
        v2f64 select(const v2f64& msk, const v2f64& on_true,
                     const v2f64& on_false);

        template < int _P0, int _P1>
        v2f64 permute(const v2f64& a);
        template < int _P0, int _P1>
        v2f64 permute(const v2f64& a, const v2f64& b);

	template <unsigned _I>
	v2f64 insert(const v2f64& a, typename v2f64::element_type v);
	template <unsigned _I>
	typename v2f64::element_type extract(const v2f64& a);

}

#include <cftal/x86vec_v4f32_inl.h>
#include <cftal/x86vec_v2f64_inl.h>

// Local variables:
// mode: c++
// end:
#endif
