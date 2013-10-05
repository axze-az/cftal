#if !defined (__X86VEC_DIVISOR_H__)
#define __X86VEC_DIVISOR_H__ 1

#include <cftal/x86vec_ivec.h>
#include <cftal/x86vec_fvec.h>
#include <cftal/divisor.h>

namespace x86vec {

	namespace impl {

 		template <class _S>
		struct signed_vec_traits {
  			static _S mulsh(const _S& a, const _S& b)  {
				return mul_hi(a, b);
			}
		};

 		template <class _U>
		struct unsigned_vec_traits {
			static _U muluh(const _U& a, const _U& b)  {
				return mul_hi(a, b);
			}
		};

	}
}

namespace cftal {

	namespace impl {

		// v8u16
		template <>
		struct udiv_traits<x86vec::v8u16, uint16_t> : public 
		x86vec::impl::unsigned_vec_traits<x86vec::v8u16> {
		};
		// v8s16
		template <>
		struct sdiv_traits<x86vec::v8s16, int16_t> : public 
		x86vec::impl::signed_vec_traits<x86vec::v8s16> {
		};

		// v4u32
		template <>
		struct udiv_traits<x86vec::v4u32, uint32_t> : public 
		x86vec::impl::unsigned_vec_traits<x86vec::v4u32> {
		};
		// v4s32
		template <>
		struct sdiv_traits<x86vec::v4s32, int32_t> : public 
		x86vec::impl::signed_vec_traits<x86vec::v4s32> {
		};

		// v2u64
		template <>
		struct udiv_traits<x86vec::v2u64, uint64_t> : public 
		x86vec::impl::unsigned_vec_traits<x86vec::v2u64> {
		};
		// v2s64
		template <>
		struct sdiv_traits<x86vec::v2s64, int64_t> : public 
		x86vec::impl::signed_vec_traits<x86vec::v2s64> {
		};

		// v8u32
		template <>
		struct udiv_traits<x86vec::v8u32, uint32_t> : public 
		x86vec::impl::unsigned_vec_traits<x86vec::v8u32> {
		};
		// v8s32
		template <>
		struct sdiv_traits<x86vec::v8s32, int32_t> : public 
		x86vec::impl::signed_vec_traits<x86vec::v8s32> {
		};


	}

	template <>
	class divisor<x86vec::v8s16, int16_t>
		: public impl::sdiv<x86vec::v8s16, int16_t> {
	public:
		divisor(int16_t d) :
			impl::sdiv<x86vec::v8s16, int16_t>(d) {}
	};

	template <>
	class divisor<x86vec::v8u16, uint16_t>
		: public impl::udiv<x86vec::v8u16, uint16_t> {
	public:
		divisor(int16_t d) :
			impl::udiv<x86vec::v8u16, uint16_t>(d) {}
	};

	template <>
	class divisor<x86vec::v4s32, int32_t>
		: public impl::sdiv<x86vec::v4s32, int32_t> {
	public:
		divisor(int32_t d) :
			impl::sdiv<x86vec::v4s32, int32_t>(d) {}
	};
	template <>
	class divisor<x86vec::v4u32, uint32_t>
		: public impl::udiv<x86vec::v4u32, uint32_t> {
	public:
		divisor(uint32_t d) :
			impl::udiv<x86vec::v4u32, uint32_t>(d) {}
	};

	template <>
	class divisor<x86vec::v2s64, int64_t>
		: public impl::sdiv<x86vec::v2s64, int64_t> {
	public:
		divisor(int64_t d) :
			impl::sdiv<x86vec::v2s64, int64_t>(d) {}
	};
	template <>
	class divisor<x86vec::v2u64, uint64_t>
		: public impl::udiv<x86vec::v2u64, uint64_t> {
	public:
		divisor(uint64_t d) :
			impl::udiv<x86vec::v2u64, uint64_t>(d) {}
	};

	template <>
	class divisor<x86vec::v8s32, int32_t>
		: public impl::sdiv<x86vec::v8s32, int32_t> {
	public:
		divisor(int32_t d) :
			impl::sdiv<x86vec::v8s32, int32_t>(d) {}
	};
	template <>
	class divisor<x86vec::v8u32, uint32_t>
		: public impl::udiv<x86vec::v8u32, uint32_t> {
	public:
		divisor(uint32_t d) :
			impl::udiv<x86vec::v8u32, uint32_t>(d) {}
	};

}

namespace x86vec {

	using cftal::divisor;
}


// Local variables:
// mode: c++
// end:
#endif
