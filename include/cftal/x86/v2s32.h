//
// Copyright (C) 2010-2026 Axel Zeuner
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
#if !defined (__CFTAL_X86_V2S32_H__)
#define __CFTAL_X86_V2S32_H__ 1

#include <cftal/config.h>

#if __CFTAL_CFG_USE_8_BYTE_VECS_ON_X86__ > 0

#include <cftal/types.h>
#include <cftal/x86/v64bit.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/vec_op.h>

namespace cftal {

#define V2S32_SPECIALIZED 1

    template <>
    class vec<int32_t, 2> {
	using rep=x86::v64bit<int32_t>;
	rep _v;
    public:
        // using base_type = x86::vreg<__m128i>;
        __m128i operator()() const {
            return _v.to_m128i();
        }

        using value_type = int32_t;
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
        using mask_value_type = bit;
#else
        using mask_value_type = int32_t;
#endif
        using mask_type= vec<mask_value_type, 2>;

        vec() = default;
	vec(__m128i v);
        vec(const vec<uint32_t, 2>& v);
        // create vec{v,v}
        vec(int32_t v);
        // create vec(l, h);
        vec(vec<int32_t, 1> l, vec<int32_t, 1> h);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<int32_t> l);
        // allow construction from init list
        vec(init_list<int32_t> l);
        // expression template constructor
        template <template <class _U> class _OP,
                  class _L, class _R>
        vec(const expr<_OP<vec<int32_t, 2> >, _L, _R>& r);
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
        vec<int32_t, 2>
	load(const int32_t* p, ssize_t n=2);
        static
        void
	store(int32_t* p, const vec<int32_t, 2>& v, ssize_t n=2);
    };

    vec<int32_t, 1>
    low_half(const vec<int32_t, 2>& v);
    vec<int32_t, 1>
    high_half(const vec<int32_t, 2>& v);

    template <size_t _I>
    int32_t
    extract(const vec<int32_t, 2>& v);

    int32_t
    extract(const vec<int32_t, 2>& v, size_t i);

    template <size_t _I>
    void
    insert(vec<int32_t, 2>& v, const int32_t& vi);

    void
    insert(vec<int32_t, 2>& v, const int32_t& vi, size_t i);

#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__==0)
    bool
    all_of(const vec<int32_t, 2>::mask_type& v);
    bool
    any_of(const vec<int32_t, 2>::mask_type& v);
    bool
    none_of(const vec<int32_t, 2>::mask_type& v);

    vec<bit, 2>
    compress_mask(const vec<int32_t, 2>::mask_type& m);

    template<>
    struct expand_mask<vec<int32_t, 2> > {
        static
        vec<int32_t, 2>
        from(const vec<bit, 2>& s);
    };
#endif

    v2s32 max(const v2s32& a, const v2s32& b);
    v2s32 min(const v2s32& a, const v2s32& b);
    v2s32 abs(const v2s32& a);

    vec<int32_t, 2>
    select(const vec<int32_t, 2>::mask_type& msk,
           const vec<int32_t, 2>& on_true,
           const vec<int32_t, 2>& on_false);

    vec<int32_t, 2>
    select_val_or_zero(const vec<int32_t, 2>::mask_type& msk,
                       const vec<int32_t, 2>& on_true);

    vec<int32_t, 2>
    select_zero_or_val(const vec<int32_t, 2>::mask_type& msk,
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

    vec<int32_t, 2>
    permute(const vec<int32_t, 2>& s, const vec<int32_t, 2>& idx);

    std::pair<vec<int32_t, 2>, vec<int32_t, 2> >
    mul_lo_hi(const vec<int32_t, 2>& a, const vec<int32_t, 2>& b);

}

#endif

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2S32_H__
