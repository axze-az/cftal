#if !defined (__X86VEC_DIVISOR_H__)
#define __X86VEC_DIVISOR_H__ 1

#include <cftal/x86vec_ivec.h>
#include <cftal/x86vec_fvec.h>
#include <cftal/divisor.h>

namespace x86vec {

	namespace impl {
		struct vdiv16_traits {
			static v8s16 splat_for_shift(std::int16_t x) {
				return v8s16(x, false);
			}
			static v8s16 mulsh(const v8s16& a, const v8s16& b)  {
				return mulh(a, b);
			}
			static v8u16 splat_for_shift(std::uint16_t x) {
				return v8u16(x, false);
			}
			static v8u16 muluh(const v8u16& a, const v8u16& b)  {
				return mulh(a, b);
			}
		};

		struct vdiv32_traits {
			static v4s32 splat_for_shift(std::int32_t x) {
				return v4s32(x, false);
			}
			static v4s32 mulsh(const v4s32& a, const v4s32& b)  {
				return mulh(a, b);
			}
			static v4u32 splat_for_shift(std::uint32_t x) {
				return v4u32(x, false);
			}
			static v4u32 muluh(const v4u32& a, const v4u32& b)  {
				return mulh(a, b);
			}
		};
	}
}

namespace cftal {

	namespace impl {

		// unsigned vector div 16
		template <>
		struct udiv_traits<x86vec::v8u16, std::uint16_t> 
			: public x86vec::impl::vdiv16_traits {};
		// signed vector div 16
		template <>
		struct sdiv_traits<x86vec::v8s16, std::int16_t> 
			: public x86vec::impl::vdiv16_traits {};

		// unsigned vector div 32
		template <>
		struct udiv_traits<x86vec::v4u32, std::uint32_t> 
			: public x86vec::impl::vdiv32_traits {};

		// signed vector div 32
		template <>
		struct sdiv_traits<x86vec::v4s32, std::int32_t> 
			: public x86vec::impl::vdiv32_traits {};
	}

	template <>
	class divisor<x86vec::v8s16, std::int16_t>
		: public impl::sdiv<x86vec::v8s16, std::int16_t> {
	public:
		divisor(std::int16_t d) : 
			impl::sdiv<x86vec::v8s16, std::int16_t>(d) {}
	};
	
	template <>
	class divisor<x86vec::v8u16, std::uint16_t>
		: public impl::udiv<x86vec::v8u16, std::uint16_t> {
	public:
		divisor(int16_t d) : 
			impl::udiv<x86vec::v8u16, std::uint16_t>(d) {}
	};

	template <>
	class divisor<x86vec::v4s32, std::int32_t>
		: public impl::sdiv<x86vec::v4s32, std::int32_t> {
	public:
		divisor(std::int32_t d) : 
			impl::sdiv<x86vec::v4s32, std::int32_t>(d) {}
	};
	template <>
	class divisor<x86vec::v4u32, std::uint32_t>
		: public impl::udiv<x86vec::v4u32, std::uint32_t> {
	public:
		divisor(std::uint32_t d) : 
			impl::udiv<x86vec::v4u32, std::uint32_t>(d) {}
	};	
}

namespace x86vec {

	using cftal::divisor;
}


// Local variables:
// mode: c++
// end:
#endif
