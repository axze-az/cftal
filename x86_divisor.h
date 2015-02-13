#if !defined (__CFTAL_X86_DIVISOR_H__)
#define __CFTAL_X86_DIVISOR_H__ 1

#include <cftal/vec_op.h>
#include <cftal/divisor.h>

#if 0
namespace cftal {

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

        template <typename _T, std::size_t _T>
        struct vec_div : public
        typename std::conditional<>::type {
        };
        
#if 0
        // v8u16
        template <>
        struct udiv_traits<v8u16, uint16_t> : public
        x86vec::impl::unsigned_vec_traits<v8u16> {
        };
        // v8s16
        template <>
        struct sdiv_traits<v8s16, int16_t> : public
        x86vec::impl::signed_vec_traits<v8s16> {
        };

        // v4u32
        template <>
        struct udiv_traits<v4u32, uint32_t> : public
        x86vec::impl::unsigned_vec_traits<x86vec::v4u32> {
        };
#endif

        // v4s32
        template <>
        struct sdiv_traits<vec<int32_t, 4>, int32_t> : public
        impl::signed_vec_traits<vec<int32_t, 4> > {
        };

#if 0
        // v2u64
        template <>
        struct udiv_traits<v2u64, uint64_t> : public
        x86vec::impl::unsigned_vec_traits<v2u64> {
        };
        // v2s64
        template <>
        struct sdiv_traits<v2s64, int64_t> : public
        x86vec::impl::signed_vec_traits<v2s64> {
        };
#endif

        // v8u32
        template <>
        struct udiv_traits<cftal::v8u32, uint32_t> : public
        x86vec::impl::unsigned_vec_traits<cftal::v8u32> {
        };

        // v8s32
        template <>
        struct sdiv_traits<cftal::v8s32, int32_t> : public
        x86vec::impl::signed_vec_traits<cftal::v8s32> {
        };
        
    }

#if 0
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
#endif

    template <>
    class divisor<vec<int32_t, 4>, int32_t>
        : public impl::sdiv<vec<int32_t, 4>, int32_t> {
    public:
        divisor(int32_t d) :
            impl::sdiv<vec<int32_t, 4>, int32_t>(d) {}
    };

#if 0
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
#endif
}

namespace x86vec {

    using cftal::divisor;
}

#endif


// Local variables:
// mode: c++
// end:
#endif
