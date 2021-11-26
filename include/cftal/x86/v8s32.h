//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_X86_V8S32__)
#define __CFTAL_X86_V8S32__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/x86/v4s32.h>
#include <cftal/x86/v8u32.h>
#include <cftal/vec_op.h>

#if defined (__AVX2__)

namespace cftal {

#define V8S32_SPECIALIZED 1

    template <>
    class vec<int32_t, 8> : public x86::vreg<__m256i> {
    public:
        using base_type = x86::vreg<__m256i>;

        using value_type = int32_t;
#if defined (__AVX512VL__)
        using mask_value_type = bit;
#else
        using mask_value_type = int32_t;
#endif
        using mask_type= vec<mask_value_type, 8>;

        using base_type::base_type;
        vec() = default;
        vec(const v8u32& v);
        // create vec{v,v,v,v}
        vec(int32_t v);
        vec(const vec<int32_t, 4>& l, const vec<int32_t, 4>& h);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<int32_t> l);
        // allow construction from vec<int32_t, 16>
        vec(init_list<int32_t> l);
        // expression template constructor
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<int32_t, 8>, _L, _R>& r);
    };

    template <>
    struct arg< vec<int32_t, 8> > {
        using type = vec<int32_t, 8>;
    };

    template <>
    struct is_vec_specialized<vec<int32_t, 8> > : public std::true_type {};

    template <>
    struct mem< vec<int32_t, 8> > {
        static
        vec<int32_t, 8> load(const int32_t* p, std::size_t n=8);
        static
        void store(int32_t* p, const vec<int32_t, 8>& v);
    };

    v4s32 low_half(const v8s32& a);
    v4s32 high_half(const v8s32& a);

    template <size_t _I>
    int32_t
    extract(const vec<int32_t, 8>& v);

    int32_t
    extract(const vec<int32_t, 8>& v, size_t i);

    template <size_t _I>
    void
    insert(vec<int32_t, 8>& v, const int32_t& vi);

    void
    insert(vec<int32_t, 8>& v, const int32_t& vi, size_t i);

#if !defined (__AVX512VL__)
    bool
    all_of(const vec<int32_t, 8>::mask_type& v);
    bool
    any_of(const vec<int32_t, 8>::mask_type& v);
    bool
    none_of(const vec<int32_t, 8>::mask_type& v);
#endif

    v8s32 max(const v8s32& a, const v8s32& b);
    v8s32 min(const v8s32& a, const v8s32& b);
    v8s32 abs(const v8s32& a);

    vec<int32_t, 8>
    select(const vec<int32_t, 8>::mask_type& msk,
           const vec<int32_t, 8>& on_true,
           const vec<int32_t, 8>& on_false);

    vec<int32_t, 8>
    select_val_or_zero(const vec<int32_t, 8>::mask_type& msk,
                       const vec<int32_t, 8>& on_true);

    vec<int32_t, 8>
    select_zero_or_val(const vec<int32_t, 8>::mask_type& msk,
                       const vec<int32_t, 8>& on_false);

    template <bool _P0, bool _P1, bool _P2, bool _P3,
              bool _P4, bool _P5, bool _P6, bool _P7>
    vec<int32_t, 8>
    select(const vec<int32_t, 8>& on_true,
           const vec<int32_t, 8>& on_false);

    template <int32_t _P0, int32_t _P1, int32_t _P2, int32_t _P3,
              int32_t _P4, int32_t _P5, int32_t _P6, int32_t _P7>
    vec<int32_t, 8> permute(const vec<int32_t, 8>& s);

    template <int32_t _P0, int32_t _P1, int32_t _P2, int32_t _P3,
              int32_t _P4, int32_t _P5, int32_t _P6, int32_t _P7>
    vec<int32_t, 8> permute(const vec<int32_t, 8>& s0,
                            const vec<int32_t, 8>& s1);

    std::pair<vec<int32_t, 8>, vec<int32_t, 8> >
    mul_lo_hi(const vec<int32_t, 8>& a, const vec<int32_t, 8>& b);

}

#endif

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V8S32__
