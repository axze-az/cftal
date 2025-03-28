//
// Copyright (C) 2010-2025 Axel Zeuner
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
//
#if !defined (__CFTAL_ARM_V2U64_H__)
#define __CFTAL_ARM_V2U64_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/impl/vreg.h>
#include <cftal/vec_op.h>
#include <cftal/arm/intrin.h>

namespace cftal {

#define V2U64_SPECIALIZED 1

    template <>
    class vec<uint64_t, 2> : public impl::vreg<uint64x2_t> {
    public:
        using base_type = impl::vreg<uint64x2_t>;
        using value_type = uint64_t;
        using mask_value_type = uint64_t;
        using mask_type= vec<mask_value_type, 2>;

        using impl::vreg<uint64x2_t>::vreg;
        vec() = default;
        vec(const vec<int64_t, 2>& v);
        // create vec{v,v}
        vec(uint64_t v);
        // create vec(l, h);
        vec(vec<uint64_t, 1> l, vec<uint64_t, 1> h);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<uint64_t> l);
        // allow construction from init_list
        vec(init_list<uint64_t> l);
        // expression template constructor
        template <template <class _U> class _OP,
                  class _L, class _R>
        vec(const expr<_OP<vec<uint64_t, 2> >, _L, _R>& r);
    };

    template <>
    struct arg< vec<uint64_t, 2> > {
        using type = vec<uint64_t, 2>;
    };

    template <>
    struct is_vec_specialized<vec<uint64_t, 2> > : public std::true_type {};

    template <>
    struct mem< vec<uint64_t, 2> > {
        static
        vec<uint64_t, 2> load(const uint64_t* p, std::size_t n=2);
        static
        void store(uint64_t* p, const vec<uint64_t, 2>& v);
    };

    vec<uint64_t, 1>
    low_half(const vec<uint64_t, 2>& v);
    vec<uint64_t, 1>
    high_half(const vec<uint64_t, 2>& v);

#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__==0)
    bool
    all_of(const vec<uint64_t, 2>::mask_type& v);
    bool
    any_of(const vec<uint64_t, 2>::mask_type& v);
    bool
    none_of(const vec<uint64_t, 2>::mask_type& v);
#endif

    v2u64 max(const v2u64& a, const v2u64& b);
    v2u64 min(const v2u64& a, const v2u64& b);

    vec<uint64_t, 2>
    select(const typename vec<uint64_t, 2>::mask_type& msk,
           const vec<uint64_t, 2>& on_true,
           const vec<uint64_t, 2>& on_false);

    template <bool _P0, bool _P1>
    vec<uint64_t, 2>
    select(const vec<uint64_t, 2>& on_true,
           const vec<uint64_t, 2>& on_false);

    template <int32_t _P0, int32_t _P1>
    vec<uint64_t, 2> permute(const vec<uint64_t, 2>& s);

    template <int32_t _P0, int32_t _P1>
    vec<uint64_t, 2> permute(const vec<uint64_t, 2>& s0,
                             const vec<uint64_t, 2>& s1);

    std::pair<vec<uint64_t, 2>, vec<uint64_t, 2> >
    mul_lo_hi(const vec<uint64_t, 2>& a,
              const vec<uint64_t, 2>& b);
}


// Local variables:
// mode: c++
// end:
#endif // __CFTAL_ARM_V2U64__
