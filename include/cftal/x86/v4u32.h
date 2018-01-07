//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_X86_V4U32__)
#define __CFTAL_X86_V4U32__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/vec_op.h>

namespace cftal {

    template <>
    class vec<uint32_t, 4> : public x86::vreg<__m128i> {
    public:
        using base_type = x86::vreg<__m128i>;
        using value_type = uint32_t;
#if defined (__AVX512VL__)
        using mask_value_type = bit;
#else
        using mask_value_type = uint32_t;
#endif
        using mask_type= vec<mask_value_type, 4>;

        using x86::vreg<__m128i>::vreg;
        vec() = default;
        vec(const vec<int32_t, 4>& v);
        // create vec{v,v,v,v}
        vec(uint32_t v);
        // create vec(l, h);
        vec(vec<uint32_t, 2> l, vec<uint32_t, 2> h);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<uint32_t> l);
        // allow construction from vec<int32_t, 8>
        vec(init_list<uint32_t> l);
        // expression template constructor
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<uint32_t, 4>, _L, _R>& r);
    };

    template <>
    struct arg< vec<uint32_t, 4> > {
        using type = vec<uint32_t, 4>;
    };

    template <>
    struct mem< vec<uint32_t, 4> > {
        static
        vec<uint32_t, 4> load(const uint32_t* p, std::size_t n=4);
        static
        void store(uint32_t* p, const vec<uint32_t, 4>& v);
    };

    vec<uint32_t, 2>
    low_half(const vec<uint32_t, 4>& v);
    vec<uint32_t, 2>
    high_half(const vec<uint32_t, 4>& v);

#if !defined (__AVX512VL__)
    bool
    all_of(const vec<uint32_t, 4>::mask_type& v);
    bool
    any_of(const vec<uint32_t, 4>::mask_type& v);
    bool
    none_of(const vec<uint32_t, 4>::mask_type& v);
#endif

    v4u32 max(const v4u32& a, const v4u32& b);
    v4u32 min(const v4u32& a, const v4u32& b);

    vec<uint32_t, 4>
    select(const vec<uint32_t, 4>::mask_type& msk,
           const vec<uint32_t, 4>& on_true,
           const vec<uint32_t, 4>& on_false);

    vec<uint32_t, 4>
    select_val_or_zero(const vec<uint32_t, 4>::mask_type& msk,
                       const vec<uint32_t, 4>& on_true);

    vec<uint32_t, 4>
    select_zero_or_val(const vec<uint32_t, 4>::mask_type& msk,
                       const vec<uint32_t, 4>& on_false);

    template <bool _P0, bool _P1,
              bool _P2, bool _P3>
    vec<uint32_t, 4>
    select(const vec<uint32_t, 4>& on_true,
           const vec<uint32_t, 4>& on_false);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3>
    vec<uint32_t, 4> permute(const vec<uint32_t, 4>& s);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3>
    vec<uint32_t, 4> permute(const vec<uint32_t, 4>& s0,
                             const vec<uint32_t, 4>& s1);

    std::pair<vec<uint32_t, 4>, vec<uint32_t, 4> >
    mul_lo_hi(const vec<uint32_t, 4>& a,
              const vec<uint32_t, 4>& b);
}


// Local variables:
// mode: c++
// end:
#endif // __CFTAL_SIMD_X86_V4U32__
