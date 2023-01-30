//
// Copyright (C) 2010-2023 Axel Zeuner
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
#if !defined (__CFTAL_X86_V2F32__)
#define __CFTAL_X86_V2F32__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/vec_t_n.h>
#include <cftal/vec_lookup.h>
#include <cftal/x86/intrin.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/x86/v2f64.h>

namespace cftal {

#define V2F32_SPECIALIZED 1

    template <>
    class vec<float, 2> {
        union rep {
            double _d;
            float _f[2];
            rep(double d) : _d(d) {}
            rep(float l, float h) : _f{l, h} {}
            rep(__m128 v) : _d(_mm_cvtsd_f64(_mm_castps_pd(v))) {}
            rep() = default;
        };
        rep _v;
    public:
        // using base_type = x86::vreg<__m128>;
        __m128 operator()() const {
            return x86::_mm_cvtf64_sd(_v._d);
        }

        using value_type = float;
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
        using mask_value_type = bit;
#else
        using mask_value_type = float;
#endif
        using mask_type= vec<mask_value_type, 2>;

        vec() = default;
        vec(__m128 v);
        // create vec{v,v,}
        vec(float v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<float> l);
        // allow construction from vec<float, 16>
        vec(init_list<float> l);
        // allow construction from two halfes
        vec(const vec<float, 1>& lh, const vec<float, 1>& hh);
         // expression template constructor
        template <template <class _U> class _OP,
                  class _L, class _R>
        vec(const expr<_OP<vec<float, 2> >, _L, _R>& r);
    };

    template <>
    struct arg< vec<float, 2> > {
        using type = vec<float, 2>;
    };

    template <>
    struct is_vec_specialized<vec<float, 2> > : public std::true_type {};

    template <>
    struct mem< vec<float, 2> > {
        static
        vec<float, 2> load(const float* p, std::size_t n=4);
        static
        void store(float* p, const vec<float, 2>& v);
    };

    vec<float, 1>
    low_half(const vec<float, 2>& s);

    vec<float, 1>
    high_half(const vec<float, 2>& s);

    template <size_t _I>
    float
    extract(const vec<float, 2>& v);

    float
    extract(const vec<float, 2>& v, size_t i);

    template <size_t _I>
    void
    insert(vec<float, 2>& v, const float& vi);

    void
    insert(vec<float, 2>& v, const float& vi, size_t i);

    vec<float, 2>
    select(const vec<float, 2>::mask_type& msk,
           const vec<float, 2>& on_true,
           const vec<float, 2>& on_false);

    vec<float, 2>
    select_val_or_zero(const vec<float, 2>::mask_type& msk,
                       const vec<float, 2>& on_true);

    vec<float, 2>
    select_zero_or_val(const vec<float, 2>::mask_type& msk,
                       const vec<float, 2>& on_false);

#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    bool
    all_of(const vec<float, 2>::mask_type& a);

    bool
    any_of(const vec<float, 2>::mask_type& a);

    bool
    none_of(const vec<float, 2>::mask_type& a);

    vec<bit, 2>
    compress_mask(const vec<float, 2>::mask_type& m);

    template<>
    struct expand_mask<vec<float, 2> > {
        static
        vec<float, 2>
        from(const vec<bit, 2>& s);
    };
#endif

    unsigned
    read_signs(const vec<float, 2>& b);

    bool
    elements_equal(const vec<float, 2>& v);

    v2f32 max(const v2f32& a, const v2f32& b);
    v2f32 min(const v2f32& a, const v2f32& b);
    v2f32 abs(const v2f32& a);
    v2f32 fabs(const v2f32& a);
    v2f32 sqrt(const v2f32& a);
    v2f32 sqrt(const v2f32& a);

    namespace x86 {
        v2f32 round(const v2f32& v, rounding_mode::type m);
    }

    v2f32 rint(const v2f32& a);
    v2f32 floor(const v2f32& a);
    v2f32 ceil(const v2f32& a);
    v2f32 trunc(const v2f32& a);
    // returns (~a) & (b)
    v2f32 andnot(const v2f32& a, const v2f32& b);
    v2f32 copysign(const v2f32& x, const v2f32& y);
    v2f32 mulsign(const v2f32& x, const v2f32& y);

    // a*b +c
    v2f32 fma(const v2f32& a, const v2f32& b, const v2f32& c);
    // a*b -c
    v2f32 fms(const v2f32& a, const v2f32& b, const v2f32& c);
    // -(a*b) + c
    v2f32 nfma(const v2f32& a, const v2f32& b, const v2f32& c);
    // -(a*b) - c
    v2f32 nfms(const v2f32& a, const v2f32& b, const v2f32& c);

    template <bool _P0, bool _P1>
    vec<float, 2>
    select(const vec<float, 2>& on_true,
           const vec<float, 2>& on_false);

    template <int32_t _P0, int32_t _P1>
    vec<float, 2>
    permute(const vec<float, 2>& s);

    template <int32_t _P0, int32_t _P1>
    vec<float, 2>
    permute(const vec<float, 2>& s0,
            const vec<float, 2>& s1);

    vec<float, 2>
    permute(const vec<float, 2>& s, const vec<int32_t, 2>& idx);

#if 0 // defined (__AVX2__)
    template <>
    class variable_vec_lookup_table<float, int32_t, 4> {
    private:
        vec<int32_t, 4> _msk;
    public:
        variable_vec_lookup_table(const vec<int32_t, 4>& idx);
        vec<float, 2>
        from(const float* tbl) const;
    };
#endif

#if 0 // defined (__SSSE3__)
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
            vec<float, 2>
            fromp(const float*) const;
        };
    }
#endif

#if 0 // defined (__AVX2__)
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
            vec<float, 2>
            fromp(const float*) const;
        };

        template <>
        class fixed_vec_lookup_table<32, float, int32_t, 4> {
        private:
            __m128i _msk;
            __m128i _idx_gt_7;
            __m128i _idx_gt_15;
            __m128i _idx_gt_23;
        public:
            fixed_vec_lookup_table(const vec<int32_t, 4>& idx);
            vec<float, 2>
            fromp(const float* tbl) const;
        };

    }
#endif
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2F32__
