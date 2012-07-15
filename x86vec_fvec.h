#if !defined (__X86VEC_FVEC_H__)
#define __X86VEC_FVEC_H__ 1

#include <cftal/x86vec_const.h>
#include <cftal/x86vec_vreg.h>
#include <cftal/x86vec_perm.h>
#include <cftal/x86vec_ops_1.h>
#include <cftal/mem_load.h>
#include <cftal/divisor.h>

namespace x86vec {

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
}

#include <cftal/x86vec_v4f32_inl.h>
//#include <cftal/x86vec_v2f64_inl.h>

// Local variables:
// mode: c++
// end:
#endif
