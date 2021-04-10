//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_X86_V16S8__)
#define __CFTAL_X86_V16S8__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/vreg.h>
#include <cftal/vec_op.h>

namespace cftal {

#define V16S8_SPECIALIZED 1

    template <>
    class vec<int8_t, 16> : public x86::vreg<__m128i> {
    public:
        using base_type = x86::vreg<__m128i>;

        using value_type = int8_t;
        using mask_value_type = int8_t;
        using mask_type= vec<mask_value_type, 16>;

        using base_type::base_type;
        vec() = default;
        vec(const vec<uint8_t, 16>& v);
        // create vec{v,v,v,v}
        vec(int8_t v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<int8_t> l);
        // allow construction from vec<int8_t, 16>
        vec(init_list<int8_t> l);
        // allow construction from two halfes
        vec(const vec<int8_t, 8>& lh, const vec<int8_t, 8>& hh);
        // expression template constructor
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<int8_t, 16>, _L, _R>& r);
    };

    template <>
    struct arg< vec<int8_t, 16> > {
        using type = vec<int8_t, 16>;
    };

    template <>
    struct is_vec_specialized<vec<int8_t, 16> > : public std::true_type {};

    template <>
    struct mem< vec<int8_t, 16> > {
        static
        vec<int8_t, 16> load(const int8_t* p, std::size_t n=16);
        static
        void store(int8_t* p, const vec<int8_t, 16>& v);
    };

    vec<int8_t, 8> low_half(const vec<int8_t, 16>& a);
    vec<int8_t, 8> high_half(const vec<int8_t, 16>& a);

    bool
    all_of(const vec<int8_t, 16>::mask_type& v);
    bool
    any_of(const vec<int8_t, 16>::mask_type& v);
    bool
    none_of(const vec<int8_t, 16>::mask_type& v);

    v16s8 max(const v16s8& a, const v16s8& b);
    v16s8 min(const v16s8& a, const v16s8& b);
    v16s8 abs(const v16s8& a);

    vec<int8_t, 16>
    select(const vec<int8_t, 16>::mask_type& msk,
           const vec<int8_t, 16>& on_true,
           const vec<int8_t, 16>& on_false);

    vec<int8_t, 16>
    select_val_or_zero(const vec<int8_t, 16>::mask_type& msk,
                       const vec<int8_t, 16>& on_true);

    vec<int8_t, 16>
    select_zero_or_val(const vec<int8_t, 16>::mask_type& msk,
                       const vec<int8_t, 16>& on_false);

    template <bool _P00, bool _P01, bool _P02, bool _P03,
              bool _P04, bool _P05, bool _P06, bool _P07,
              bool _P08, bool _P09, bool _P10, bool _P11,
              bool _P12, bool _P13, bool _P14, bool _P15>
    vec<int8_t, 16>
    select(const vec<int8_t, 16>& on_true,
           const vec<int8_t, 16>& on_false);

    template <int32_t _P00, int32_t _P01, int32_t _P02, int32_t _P03,
              int32_t _P04, int32_t _P05, int32_t _P06, int32_t _P07,
              int32_t _P08, int32_t _P09, int32_t _P10, int32_t _P11,
              int32_t _P12, int32_t _P13, int32_t _P14, int32_t _P15>
    vec<int8_t, 16> permute(const vec<int8_t, 16>& s);

    template <int32_t _P00, int32_t _P01, int32_t _P02, int32_t _P03,
              int32_t _P04, int32_t _P05, int32_t _P06, int32_t _P07,
              int32_t _P08, int32_t _P09, int32_t _P10, int32_t _P11,
              int32_t _P12, int32_t _P13, int32_t _P14, int32_t _P15>
    vec<int8_t, 16> permute(const vec<int8_t, 16>& s0,
                            const vec<int8_t, 16>& s1);

    std::pair<vec<int8_t, 16>, vec<int8_t, 16> >
    mul_lo_hi(const vec<int8_t, 16>& a, const vec<int8_t, 16>& b);

}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V16S8__
