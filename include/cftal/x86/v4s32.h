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
#if !defined (__CFTAL_X86_V4S32__)
#define __CFTAL_X86_V4S32__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/vec_op.h>

namespace cftal {

#define V4S32_SPECIALIZED 1

    template <>
    class vec<int32_t, 4> : public x86::vreg<__m128i> {
    public:
        using base_type = x86::vreg<__m128i>;

        using value_type = int32_t;
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
        using mask_value_type = bit;
#else
        using mask_value_type = int32_t;
#endif
        using mask_type= vec<mask_value_type, 4>;

        using base_type::base_type;
        vec() = default;
        vec(const vec<uint32_t, 4>& v);
        // create vec{v,v,v,v}
        vec(int32_t v);
        // create vec(l, h);
        vec(vec<int32_t, 2> l, vec<int32_t, 2> h);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<int32_t> l);
        // allow construction from vec<int32_t, 8>
        vec(init_list<int32_t> l);
        // expression template constructor
        template <template <class _U> class _OP,
                  class _L, class _R>
        vec(const expr<_OP<vec<int32_t, 4> >, _L, _R>& r);
    };

    template <>
    struct arg< vec<int32_t, 4> > {
        using type = vec<int32_t, 4>;
    };

    template <>
    struct is_vec_specialized<vec<int32_t, 4> > : public std::true_type {};

    template <>
    struct mem< vec<int32_t, 4> > {
        static
        vec<int32_t, 4>
	load(const int32_t* p, ssize_t n=4);
        static
        void
	store(int32_t* p, const vec<int32_t, 4>& v, ssize_t n=4);
    };

    vec<int32_t, 2>
    low_half(const vec<int32_t, 4>& v);
    vec<int32_t, 2>
    high_half(const vec<int32_t, 4>& v);

    template <size_t _I>
    int32_t
    extract(const vec<int32_t, 4>& v);

    int32_t
    extract(const vec<int32_t, 4>& v, size_t i);

    template <size_t _I>
    void
    insert(vec<int32_t, 4>& v, const int32_t& vi);

    void
    insert(vec<int32_t, 4>& v, const int32_t& vi, size_t i);

#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__==0)
    bool
    all_of(const vec<int32_t, 4>::mask_type& v);
    bool
    any_of(const vec<int32_t, 4>::mask_type& v);
    bool
    none_of(const vec<int32_t, 4>::mask_type& v);

    vec<bit, 4>
    compress_mask(const vec<int32_t, 4>::mask_type& m);

    template<>
    struct expand_mask<vec<int32_t, 4> > {
        static
        vec<int32_t, 4>
        from(const vec<bit, 4>& s);
    };
#endif

    v4s32 max(const v4s32& a, const v4s32& b);
    v4s32 min(const v4s32& a, const v4s32& b);
    v4s32 abs(const v4s32& a);

    vec<int32_t, 4>
    select(const vec<int32_t, 4>::mask_type& msk,
           const vec<int32_t, 4>& on_true,
           const vec<int32_t, 4>& on_false);

    vec<int32_t, 4>
    select_val_or_zero(const vec<int32_t, 4>::mask_type& msk,
                       const vec<int32_t, 4>& on_true);

    vec<int32_t, 4>
    select_zero_or_val(const vec<int32_t, 4>::mask_type& msk,
                       const vec<int32_t, 4>& on_false);


    template <bool _P0, bool _P1,
              bool _P2, bool _P3>
    vec<int32_t, 4>
    select(const vec<int32_t, 4>& on_true,
           const vec<int32_t, 4>& on_false);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3>
    vec<int32_t, 4> permute(const vec<int32_t, 4>& s);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3>
    vec<int32_t, 4> permute(const vec<int32_t, 4>& s0,
                            const vec<int32_t, 4>& s1);

    vec<int32_t, 4>
    permute(const vec<int32_t, 4>& s, const vec<int32_t, 4>& idx);

    std::pair<vec<int32_t, 4>, vec<int32_t, 4> >
    mul_lo_hi(const vec<int32_t, 4>& a, const vec<int32_t, 4>& b);

    namespace impl {
#if defined (__AVX2__)
        template <>
        class variable_vec_lookup_table<int32_t, int32_t, 4> {
        private:
            vec<int32_t, 4> _msk;
        public:
            variable_vec_lookup_table(const vec<int32_t, 4>& idx);
            vec<int32_t, 4>
            fromp(const int32_t* tbl) const;
        };
#endif

#if defined (__SSSE3__)
        template <>
        class fixed_vec_lookup_table<4, int32_t, int32_t, 4> {
            // a msk
            vec<int32_t, 4> _msk;
            // setup function for _msk
            static
            vec<int32_t, 4>
            setup_msk(const vec<int32_t, 4>& idx);
        public:
            fixed_vec_lookup_table(const vec<int32_t, 4>& idx);
            // the lookup function
            vec<int32_t, 4>
            fromp(const int32_t*) const;
        };
#endif
    }

#if defined (__AVX2__)
    namespace impl {
        template <>
        class fixed_vec_lookup_table<8, int32_t, int32_t, 4> {
            // a msk
            vec<int32_t, 4> _msk;
            // setup function for _msk
            static
            vec<int32_t, 4>
            setup_msk(const vec<int32_t, 4>& idx);
        public:
            fixed_vec_lookup_table(const vec<int32_t, 4>& idx);
            // the lookup function
            vec<int32_t, 4>
            fromp(const int32_t*) const;
        };

        template <>
        class fixed_vec_lookup_table<32, int32_t, int32_t, 4> {
        private:
            __m128i _msk;
            __m128i _idx_gt_7;
            __m128i _idx_gt_15;
            __m128i _idx_gt_23;
        public:
            fixed_vec_lookup_table(const vec<int32_t, 4>& idx);
            vec<int32_t, 4>
            fromp(const int32_t* tbl) const;
        };

    }
#endif

}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V4S32__
