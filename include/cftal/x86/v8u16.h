//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_X86_V8U16__)
#define __CFTAL_X86_V8U16__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/vreg.h>
#include <cftal/vec_op.h>

namespace cftal {

#define V8U16_SPECIALIZED 1

    template <>
    class vec<uint16_t, 8> : public x86::vreg<__m128i> {
    public:
        using base_type = x86::vreg<__m128i>;

        using value_type = uint16_t;
        using mask_value_type = uint16_t;
        using mask_type= vec<mask_value_type, 8>;

        using base_type::base_type;
        vec() = default;
        vec(const vec<int16_t, 8>& v);
        // create vec{v,v,v,v}
        vec(uint16_t v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<uint16_t> l);
        // allow construction from vec<int32_t, 8>
        vec(init_list<uint16_t> l);
        // allow construction from two halfes
        vec(const vec<uint16_t, 4>& lh, const vec<uint16_t, 4>& hh);
        // expression template constructor
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<uint16_t, 8>, _L, _R>& r);
    };

    template <>
    struct arg< vec<uint16_t, 8> > {
        using type = vec<uint16_t, 8>;
    };

    template <>
    struct is_vec_specialized<vec<uint16_t, 8> > : public std::true_type {};

    template <>
    struct mem< vec<uint16_t, 8> > {
        static
        vec<uint16_t, 8> load(const uint16_t* p, std::size_t n=8);
        static
        void store(uint16_t* p, const vec<uint16_t, 8>& v);
    };

    vec<uint16_t, 4> low_half(const vec<uint16_t, 8>& a);
    vec<uint16_t, 4> high_half(const vec<uint16_t, 8>& a);

    bool
    all_of(const vec<uint16_t, 8>::mask_type& v);
    bool
    any_of(const vec<uint16_t, 8>::mask_type& v);
    bool
    none_of(const vec<uint16_t, 8>::mask_type& v);

    v8u16 max(const v8u16& a, const v8u16& b);
    v8u16 min(const v8u16& a, const v8u16& b);

    vec<uint16_t, 8>
    select(const vec<uint16_t, 8>::mask_type& msk,
           const vec<uint16_t, 8>& on_true,
           const vec<uint16_t, 8>& on_false);

    vec<uint16_t, 8>
    select_val_or_zero(const vec<uint16_t, 8>::mask_type& msk,
                       const vec<uint16_t, 8>& on_true);

    vec<uint16_t, 8>
    select_zero_or_val(const vec<uint16_t, 8>::mask_type& msk,
                       const vec<uint16_t, 8>& on_false);

    template <bool _P0, bool _P1, bool _P2, bool _P3,
              bool _P4, bool _P5, bool _P6, bool _P7>
    vec<uint16_t, 8>
    select(const vec<uint16_t, 8>& on_true,
           const vec<uint16_t, 8>& on_false);

    template <int32_t _P0, int32_t _P1, int32_t _P2, int32_t _P3,
              int32_t _P4, int32_t _P5, int32_t _P6, int32_t _P7>
    vec<uint16_t, 8> permute(const vec<uint16_t, 8>& s);

    template <int32_t _P0, int32_t _P1, int32_t _P2, int32_t _P3,
              int32_t _P4, int32_t _P5, int32_t _P6, int32_t _P7>
    vec<uint16_t, 8> permute(const vec<uint16_t, 8>& s0,
                             const vec<uint16_t, 8>& s1);

    std::pair<vec<uint16_t, 8>, vec<uint16_t, 8> >
    mul_lo_hi(const vec<uint16_t, 8>& a,
              const vec<uint16_t, 8>& b);
}


// Local variables:
// mode: c++
// end:
#endif // __CFTAL_SIMD_X86_V8U16__
