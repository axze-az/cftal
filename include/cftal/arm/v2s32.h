//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_ARM_V2S32_H__)
#define __CFTAL_ARM_V2S32_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/impl/vreg.h>
#include <cftal/vec_op.h>
#include <cftal/arm/intrin.h>

namespace cftal {

#define V2S32_SPECIALIZED 1

    template <>
    class vec<int32_t, 2> : public impl::vreg<int32x2_t> {
    public:
        using base_type = impl::vreg<int32x2_t>;

        using value_type = int32_t;
        using mask_value_type = uint32_t;

        using mask_type= vec<mask_value_type, 2>;

        using base_type::base_type;
        vec() = default;
        vec(const vec<uint32_t,2>& v);
        // create vec{v,v}
        vec(int32_t v);
        // create vec(l, h);
        vec(vec<int32_t, 1> l, vec<int32_t, 1> h);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<int32_t> l);
        // allow construction from init_list
        vec(init_list<int32_t> l);
        // expression template constructor
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<int32_t, 2>, _L, _R>& r);
    };

    template <>
    struct arg< vec<int32_t, 2> > {
        using type = vec<int32_t, 2>;
    };

    template <>
    struct is_vec_specialized<vec<int32_t, 2> > : public std::true_type {};

    template <>
    struct mem< vec<int32_t, 2> > {
        static
        vec<int32_t, 2> load(const int32_t* p, std::size_t n=2);
        static
        void store(int32_t* p, const vec<int32_t, 2>& v);
    };

    vec<int32_t, 1>
    low_half(const vec<int32_t, 2>& v);
    vec<int32_t, 1>
    high_half(const vec<int32_t, 2>& v);

    v2s32 max(const v2s32& a, const v2s32& b);
    v2s32 min(const v2s32& a, const v2s32& b);

    vec<int32_t, 2>
    select(const typename vec<int32_t, 2>::mask_type& msk,
           const vec<int32_t, 2>& on_true,
           const vec<int32_t, 2>& on_false);

    template <bool _P0, bool _P1>
    vec<int32_t, 2>
    select(const vec<int32_t, 2>& on_true,
           const vec<int32_t, 2>& on_false);

    template <int32_t _P0, int32_t _P1>
    vec<int32_t, 2> permute(const vec<int32_t, 2>& s);

    template <int32_t _P0, int32_t _P1>
    vec<int32_t, 2> permute(const vec<int32_t, 2>& s0,
                            const vec<int32_t, 2>& s1);

    std::pair<vec<int32_t, 2>, vec<int32_t, 2> >
    mul_lo_hi(const vec<int32_t, 2>& a, const vec<int32_t, 2>& b);

}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_ARM_V2S32__
