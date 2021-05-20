//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_X86_V8S16__)
#define __CFTAL_X86_V8S16__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/vreg.h>
#include <cftal/vec_op.h>

namespace cftal {

#define V8S16_SPECIALIZED 1

    template <>
    class vec<int16_t, 8> : public x86::vreg<__m128i> {
    public:
        using base_type = x86::vreg<__m128i>;

        using value_type = int16_t;
        using mask_value_type = int16_t;
        using mask_type= vec<mask_value_type, 8>;

        using base_type::base_type;
        vec() = default;
        vec(const vec<uint16_t, 8>& v);
        // create vec{v,v,v,v}
        vec(int16_t v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<int16_t> l);
        // allow construction from vec<int16_t, 8>
        vec(init_list<int16_t> l);
        // allow construction from two halfes
        vec(const vec<int16_t, 4>& lh, const vec<int16_t, 4>& hh);
        // expression template constructor
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<int16_t, 8>, _L, _R>& r);
    };

    template <>
    struct arg< vec<int16_t, 8> > {
        using type = vec<int16_t, 8>;
    };

    template <>
    struct is_vec_specialized<vec<int16_t, 8> > : public std::true_type {};

    template <>
    struct mem< vec<int16_t, 8> > {
        static
        vec<int16_t, 8> load(const int16_t* p, std::size_t n=8);
        static
        void store(int16_t* p, const vec<int16_t, 8>& v);
    };

    vec<int16_t, 4> low_half(const vec<int16_t, 8>& a);
    vec<int16_t, 4> high_half(const vec<int16_t, 8>& a);

    bool
    all_of(const vec<int16_t, 8>::mask_type& v);
    bool
    any_of(const vec<int16_t, 8>::mask_type& v);
    bool
    none_of(const vec<int16_t, 8>::mask_type& v);

    v8s16 max(const v8s16& a, const v8s16& b);
    v8s16 min(const v8s16& a, const v8s16& b);
    v8s16 abs(const v8s16& a);

    vec<int16_t, 8>
    select(const vec<int16_t, 8>::mask_type& msk,
           const vec<int16_t, 8>& on_true,
           const vec<int16_t, 8>& on_false);

    vec<int16_t, 8>
    select_val_or_zero(const vec<int16_t, 8>::mask_type& msk,
                       const vec<int16_t, 8>& on_true);

    vec<int16_t, 8>
    select_zero_or_val(const vec<int16_t, 8>::mask_type& msk,
                       const vec<int16_t, 8>& on_false);

    template <bool _P0, bool _P1, bool _P2, bool _P3,
              bool _P4, bool _P5, bool _P6, bool _P7>
    vec<int16_t, 8>
    select(const vec<int16_t, 8>& on_true,
           const vec<int16_t, 8>& on_false);

    template <int32_t _P0, int32_t _P1, int32_t _P2, int32_t _P3,
              int32_t _P4, int32_t _P5, int32_t _P6, int32_t _P7>
    vec<int16_t, 8> permute(const vec<int16_t, 8>& s);

    template <int32_t _P0, int32_t _P1, int32_t _P2, int32_t _P3,
              int32_t _P4, int32_t _P5, int32_t _P6, int32_t _P7>
    vec<int16_t, 8> permute(const vec<int16_t, 8>& s0,
                            const vec<int16_t, 8>& s1);

    std::pair<vec<int16_t, 8>, vec<int16_t, 8> >
    mul_lo_hi(const vec<int16_t, 8>& a, const vec<int16_t, 8>& b);

    vec<int16_t, 8>
    sat_add(const vec<int16_t, 8>& a, const vec<int16_t, 8>& b);
    
    vec<int16_t, 8>
    sat_sub(const vec<int16_t, 8>& a, const vec<int16_t, 8>& b);
    
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V8S16__
