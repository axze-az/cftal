//
// Copyright Axel Zeuner 2010-2020. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_X86_V4S64__)
#define __CFTAL_X86_V4S64__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/vec_op.h>

namespace cftal {

#define V4S64_SPECIALIZED 1

    template <>
    class vec<int64_t, 4> : public x86::vreg<__m256i> {
    public:
        using base_type = x86::vreg<__m256i>;

        using value_type = int64_t;
#if defined (__AVX512VL__)
        using mask_value_type = bit;
#else
        using mask_value_type = int64_t;
#endif
        using mask_type= vec<mask_value_type, 4>;

        using base_type::base_type;
        vec() = default;
        vec(const vec<uint64_t, 4>& v);
        // create vec{v,v}
        vec(int64_t v);
        // create vec(l, h);
        vec(const vec<int64_t, 2>& l, const vec<int64_t, 2>& h);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<int64_t> l);
        // allow construction from vec<int64_t, 8>
        vec(init_list<int64_t> l);
        // expression template constructor
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<int64_t, 4>, _L, _R>& r);
    };

    template <>
    struct arg< vec<int64_t, 4> > {
        using type = vec<int64_t, 4>;
    };

    template <>
    struct is_vec_specialized<vec<int64_t, 4> > : public std::true_type {};

    template <>
    struct mem< vec<int64_t, 4> > {
        static
        vec<int64_t, 4> load(const int64_t* p, std::size_t n=4);
        static
        void store(int64_t* p, const vec<int64_t, 4>& v);
    };

    vec<int64_t, 2>
    low_half(const vec<int64_t, 4>& v);
    vec<int64_t, 2>
    high_half(const vec<int64_t, 4>& v);

#if !defined (__AVX512VL__)
    bool
    all_of(const vec<int64_t, 4>::mask_type& v);
    bool
    any_of(const vec<int64_t, 4>::mask_type& v);
    bool
    none_of(const vec<int64_t, 4>::mask_type& v);
#endif

    v4s64 max(const v4s64& a, const v4s64& b);
    v4s64 min(const v4s64& a, const v4s64& b);
    v4s64 abs(const v4s64& a);

    vec<int64_t, 4>
    select(const vec<int64_t, 4>::mask_type& msk,
           const vec<int64_t, 4>& on_true,
           const vec<int64_t, 4>& on_false);

    vec<int64_t, 4>
    select_val_or_zero(const vec<int64_t, 4>::mask_type& msk,
                       const vec<int64_t, 4>& on_true);

    vec<int64_t, 4>
    select_zero_or_val(const vec<int64_t, 4>::mask_type& msk,
                       const vec<int64_t, 4>& on_false);

    template <bool _P0, bool _P1, bool _P2, bool _P3>
    vec<int64_t, 4>
    select(const vec<int64_t, 4>& on_true,
           const vec<int64_t, 4>& on_false);

    template <int _P0, int _P1, int _P2, int _P3>
    vec<int64_t, 4>
    permute(const vec<int64_t, 4>& s);

    template <int _P0, int _P1, int _P2, int _P3>
    vec<int64_t, 4>
    permute(const vec<int64_t, 4>& s0,
            const vec<int64_t, 4>& s1);

    std::pair<vec<int64_t, 4>, vec<int64_t, 4> >
    mul_lo_hi(const vec<int64_t, 4>& a, const vec<int64_t, 4>& b);

}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V4S64__
