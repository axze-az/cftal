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
#if !defined (__CFTAL_X86_V2U32_H__)
#define __CFTAL_X86_V2U32_H__ 1

#include <cftal/config.h>

#if __CFTAL_CFG_USE_8_BYTE_VECS_ON_X86__ > 0

#include <cftal/types.h>
#include <cftal/x86/v64bit.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/vec_op.h>

namespace cftal {

#define V2U32_SPECIALIZED 1

    template <>
    class vec<uint32_t, 2> {
	using rep=x86::v64bit<uint32_t>;
	rep _v;
    public:
        // using base_type = x86::vreg<__m128i>;
        __m128i operator()() const {
            return _v.to_m128i();
        }
        using value_type = uint32_t;
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
        using mask_value_type = bit;
#else
        using mask_value_type = uint32_t;
#endif
        using mask_type= vec<mask_value_type, 2>;

        vec() = default;
	vec(__m128i v);
        vec(const vec<int32_t, 2>& v);
        // create vec{v,v}
        vec(uint32_t v);
        // create vec(l, h);
        vec(vec<uint32_t, 1> l, vec<uint32_t, 1> h);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<uint32_t> l);
        // allow construction from init list
        vec(init_list<uint32_t> l);
        // expression template constructor
        template <template <class _U> class _OP,
                  class _L, class _R>
        vec(const expr<_OP<vec<uint32_t, 2> >, _L, _R>& r);
    };

    template <>
    struct arg< vec<uint32_t, 2> > {
        using type = vec<uint32_t, 2>;
    };

    template <>
    struct is_vec_specialized<vec<uint32_t, 2> > : public std::true_type {};

    template <>
    struct mem< vec<uint32_t, 2> > {
        static
        vec<uint32_t, 2>
	load(const uint32_t* p, ssize_t n=2);
        static
        void
	store(uint32_t* p, const vec<uint32_t, 2>& v, ssize_t n=2);
    };

    vec<uint32_t, 1>
    low_half(const vec<uint32_t, 2>& v);
    vec<uint32_t, 1>
    high_half(const vec<uint32_t, 2>& v);

    template <size_t _I>
    uint32_t
    extract(const vec<uint32_t, 2>& v);

    uint32_t
    extract(const vec<uint32_t, 2>& v, size_t i);

    template <size_t _I>
    void
    insert(vec<uint32_t, 2>& v, const uint32_t& vi);

    void
    insert(vec<uint32_t, 2>& v, const uint32_t& vi, size_t i);

#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__==0)
    bool
    all_of(const vec<uint32_t, 2>::mask_type& v);
    bool
    any_of(const vec<uint32_t, 2>::mask_type& v);
    bool
    none_of(const vec<uint32_t, 2>::mask_type& v);

    vec<bit, 2>
    compress_mask(const vec<uint32_t, 2>::mask_type& m);

    template<>
    struct expand_mask<vec<uint32_t, 2> > {
        static
        vec<uint32_t, 2>
        from(const vec<bit, 2>& s);
    };
#endif

    v2u32 max(const v2u32& a, const v2u32& b);
    v2u32 min(const v2u32& a, const v2u32& b);

    vec<uint32_t, 2>
    select(const vec<uint32_t, 2>::mask_type& msk,
           const vec<uint32_t, 2>& on_true,
           const vec<uint32_t, 2>& on_false);

    vec<uint32_t, 2>
    select_val_or_zero(const vec<uint32_t, 2>::mask_type& msk,
                       const vec<uint32_t, 2>& on_true);

    vec<uint32_t, 2>
    select_zero_or_val(const vec<uint32_t, 2>::mask_type& msk,
                       const vec<uint32_t, 2>& on_false);

    template <bool _P0, bool _P1>
    vec<uint32_t, 2>
    select(const vec<uint32_t, 2>& on_true,
           const vec<uint32_t, 2>& on_false);

    template <int32_t _P0, int32_t _P1>
    vec<uint32_t, 2> permute(const vec<uint32_t, 2>& s);

    template <int32_t _P0, int32_t _P1>
    vec<uint32_t, 2> permute(const vec<uint32_t, 2>& s0,
                             const vec<uint32_t, 2>& s1);

    vec<uint32_t, 2>
    permute(const vec<uint32_t, 2>& s, const vec<int32_t, 2>& idx);

    std::pair<vec<uint32_t, 2>, vec<uint32_t, 2> >
    mul_lo_hi(const vec<uint32_t, 2>& a,
              const vec<uint32_t, 2>& b);

    namespace impl {
#if defined (__AVX2__)
        template <>
        class variable_vec_lookup_table<uint32_t, int32_t, 2> {
        private:
            vec<int32_t, 2> _msk;
        public:
            variable_vec_lookup_table(const vec<int32_t, 2>& idx);
            vec<uint32_t, 2>
            fromp(const uint32_t* tbl) const;
        };
#endif

#if defined (__SSSE3__)
        template <>
        class fixed_vec_lookup_table<4, uint32_t, int32_t, 2> {
            // a msk
            vec<int32_t, 2> _msk;
            // setup function for _msk
            static
            vec<int32_t, 2>
            setup_msk(const vec<int32_t, 2>& idx);
        public:
            fixed_vec_lookup_table(const vec<int32_t, 2>& idx);
            // the lookup function
            vec<uint32_t, 2>
            fromp(const uint32_t*) const;
        };
#endif
    }
#if defined (__AVX2__)
    namespace impl {
        template <>
        class fixed_vec_lookup_table<8, uint32_t, int32_t, 2> {
            // a msk
            vec<int32_t, 2> _msk;
            // setup function for _msk
            static
            vec<int32_t, 2>
            setup_msk(const vec<int32_t, 2>& idx);
        public:
            fixed_vec_lookup_table(const vec<int32_t, 2>& idx);
            // the lookup function
            vec<uint32_t, 2>
            fromp(const uint32_t*) const;
        };

        template <>
        class fixed_vec_lookup_table<32, uint32_t, int32_t, 2> {
        private:
            __m128i _msk;
            __m128i _idx_gt_7;
            __m128i _idx_gt_15;
            __m128i _idx_gt_23;
        public:
            fixed_vec_lookup_table(const vec<int32_t, 2>& idx);
            vec<uint32_t, 2>
            fromp(const uint32_t* tbl) const;
        };

    }
#endif

}

#endif
// Local variables:
// mode: c++
// end:
#endif // __CFTAL_SIMD_X86_V2U32_H__
