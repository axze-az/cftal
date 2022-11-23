//
// Copyright (C) 2010-2022 Axel Zeuner
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
#if !defined (__CFTAL_X86_V4F32__)
#define __CFTAL_X86_V4F32__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/vec_t_n.h>
#include <cftal/vec_lookup.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/x86/v2f64.h>
#include <cftal/x86/v4f64.h>

namespace cftal {

#define V4F32_SPECIALIZED 1

    template <>
    class vec<float, 4> : public x86::vreg<__m128> {
    public:
        using base_type = x86::vreg<__m128>;

        using value_type = float;
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
        using mask_value_type = bit;
#else
        using mask_value_type = float;
#endif
        using mask_type= vec<mask_value_type, 4>;

        using x86::vreg<__m128>::vreg;
        vec() = default;
        // create vec{v,v,v,v,....}
        vec(float v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<float> l);
        // allow construction from vec<float, 16>
        vec(init_list<float> l);
        // allow construction from two halfes
        vec(const vec<float, 2>& lh, const vec<float, 2>& hh);
         // expression template constructor
        template <template <class _U> class _OP,
                  class _L, class _R>
        vec(const expr<_OP<vec<float, 4> >, _L, _R>& r);
    };

    template <>
    struct arg< vec<float, 4> > {
        using type = vec<float, 4>;
    };

    template <>
    struct is_vec_specialized<vec<float, 4> > : public std::true_type {};

    template <>
    struct mem< vec<float, 4> > {
        static
        vec<float, 4> load(const float* p, std::size_t n=4);
        static
        void store(float* p, const vec<float, 4>& v);
    };

    vec<float, 2>
    low_half(const vec<float, 4>& s);

    vec<float, 2>
    high_half(const vec<float, 4>& s);

    template <size_t _I>
    float
    extract(const vec<float, 4>& v);

    float
    extract(const vec<float, 4>& v, size_t i);

    template <size_t _I>
    void
    insert(vec<float, 4>& v, const float& vi);

    void
    insert(vec<float, 4>& v, const float& vi, size_t i);

    vec<float, 4>
    select(const vec<float, 4>::mask_type& msk,
           const vec<float, 4>& on_true,
           const vec<float, 4>& on_false);

    vec<float, 4>
    select_val_or_zero(const vec<float, 4>::mask_type& msk,
                       const vec<float, 4>& on_true);

    vec<float, 4>
    select_zero_or_val(const vec<float, 4>::mask_type& msk,
                       const vec<float, 4>& on_false);

#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    bool
    all_of(const vec<float, 4>::mask_type& a);

    bool
    any_of(const vec<float, 4>::mask_type& a);

    bool
    none_of(const vec<float, 4>::mask_type& a);

    vec<bit, 4>
    compress_mask(const vec<float, 4>::mask_type& m);
#endif

    unsigned
    read_signs(const vec<float, 4>& b);

    bool
    elements_equal(const vec<float, 4>& v);

    v4f32 max(const v4f32& a, const v4f32& b);
    v4f32 min(const v4f32& a, const v4f32& b);
    v4f32 abs(const v4f32& a);
    v4f32 fabs(const v4f32& a);
    v2f32 sqrt(const v2f32& a);
    v4f32 sqrt(const v4f32& a);

    namespace x86 {
        v4f32 round(const v4f32& v, rounding_mode::type m);
    }

    v4f32 rint(const v4f32& a);
    v4f32 floor(const v4f32& a);
    v4f32 ceil(const v4f32& a);
    v4f32 trunc(const v4f32& a);
    // returns (~a) & (b)
    v4f32 andnot(const v4f32& a, const v4f32& b);
    v4f32 copysign(const v4f32& x, const v4f32& y);
    v4f32 mulsign(const v4f32& x, const v4f32& y);

    // a*b +c
    v4f32 fma(const v4f32& a, const v4f32& b, const v4f32& c);
    // a*b -c
    v4f32 fms(const v4f32& a, const v4f32& b, const v4f32& c);
    // -(a*b) + c
    v4f32 nfma(const v4f32& a, const v4f32& b, const v4f32& c);
    // -(a*b) - c
    v4f32 nfms(const v4f32& a, const v4f32& b, const v4f32& c);

    template <bool _P0, bool _P1,
              bool _P2, bool _P3>
    vec<float, 4>
    select(const vec<float, 4>& on_true,
           const vec<float, 4>& on_false);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3>
    vec<float, 4>
    permute(const vec<float, 4>& s);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3>
    vec<float, 4>
    permute(const vec<float, 4>& s0,
            const vec<float, 4>& s1);

    vec<float, 4>
    permute(const vec<float, 4>& s, const vec<int32_t, 4>& idx);

#if defined (__AVX2__)
    template <>
    class variable_vec_lookup_table<float, int32_t, 4> {
    private:
        vec<int32_t, 4> _msk;
    public:
        variable_vec_lookup_table(const vec<int32_t, 4>& idx);
        vec<float, 4>
        from(const float* tbl) const;
    };
#endif

#if defined (__SSSE3__)
    namespace impl {
        template <>
        class fixed_vec_lookup_table<4, float, int32_t, 4> {
            // a msk
            vec<int32_t, 4> _msk;
            // setup function for _msk
            static
            vec<int32_t, 4>
            setup_msk(const vec<int32_t, 4>& idx);
        public:
            fixed_vec_lookup_table(const vec<int32_t, 4>& idx);
            // the lookup function
            vec<float, 4>
            fromp(const float*) const;
        };
    }
#endif

#if defined (__AVX2__)
    namespace impl {
        template <>
        class fixed_vec_lookup_table<8, float, int32_t, 4> {
            // a msk
            vec<int32_t, 4> _msk;
            // setup function for _msk
            static
            vec<int32_t, 4>
            setup_msk(const vec<int32_t, 4>& idx);
        public:
            fixed_vec_lookup_table(const vec<int32_t, 4>& idx);
            // the lookup function
            vec<float, 4>
            fromp(const float*) const;
        };
    }
#endif

}


// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V4F32__
