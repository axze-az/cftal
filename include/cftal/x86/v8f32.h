//
// Copyright (C) 2010-2024 Axel Zeuner
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
#if !defined (__CFTAL_X86_V8F32_H__)
#define __CFTAL_X86_V8F32_H__ 1

#if defined (__AVX__)

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/vec_t_n.h>
#include <cftal/vec_lookup.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/x86/v4f32.h>

namespace cftal {

#define V8F32_SPECIALIZED 1

    template <>
    class vec<float, 8> : public x86::vreg<__m256> {
    public:
        using base_type = x86::vreg<__m256>;

        using value_type = float;
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
        using mask_value_type = bit;
#else
        using mask_value_type = float;
#endif
        using mask_type= vec<mask_value_type, 8>;

        using x86::vreg<__m256>::vreg;
        vec() = default;
        // create vec{v,v,v,v,....}
        vec(float v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<float> l);
        // allow construction from vec<float, 16>
        vec(init_list<float> l);
        // allow construction from two halfes
        vec(const vec<float, 4>& lh, const vec<float, 4>& hh);

        // expression template constructor
        template <template <class _U> class _OP,
                  class _L, class _R>
        vec(const expr<_OP<vec<float, 8> >, _L, _R>& r);
    };

    template <>
    struct arg< vec<float, 8> > {
        using type = vec<float, 8>;
    };

    template <>
    struct is_vec_specialized<vec<float, 8> > : public std::true_type {};

    template <>
    struct mem< vec<float, 8> > {
        static
        vec<float, 8> load(const float* p, std::size_t n=8);
        static
        void store(float* p, const vec<float, 8>& v);
    };

    vec<float, 4>
    low_half(const vec<float, 8>& s);

    vec<float, 4>
    high_half(const vec<float, 8>& s);

    template <size_t _I>
    float
    extract(const vec<float, 8>& v);

    float
    extract(const vec<float, 8>& v, size_t i);

    template <size_t _I>
    void
    insert(vec<float, 8>& v, const float& vi);

    void
    insert(vec<float, 8>& v, const float& vi, size_t i);

    vec<float, 8>
    select(const vec<float, 8>::mask_type& msk,
           const vec<float, 8>& on_true,
           const vec<float, 8>& on_false);

    vec<float, 8>
    select_val_or_zero(const vec<float, 8>::mask_type& msk,
                       const vec<float, 8>& on_true);

    vec<float, 8>
    select_zero_or_val(const vec<float, 8>::mask_type& msk,
                       const vec<float, 8>& on_false);

#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__==0)
    bool
    all_of(const vec<float, 8>::mask_type& a);

    bool
    any_of(const vec<float, 8>::mask_type& a);

    bool
    none_of(const vec<float, 8>::mask_type& a);

    vec<bit, 8>
    compress_mask(const vec<float, 8>::mask_type& a);

    template<>
    struct expand_mask<vec<float, 8> > {
        static
        vec<float, 8>
        from(const vec<bit, 8>& s);
    };
#endif

    unsigned
    read_signs(const vec<float, 8>& b);

    bool
    elements_equal(const vec<float, 8>& v);


    v8f32 max(const v8f32& a, const v8f32& b);
    v8f32 min(const v8f32& a, const v8f32& b);
    v8f32 abs(const v8f32& a);
    v8f32 sqrt(const v8f32& a);

    namespace x86 {
        v8f32 round(const v8f32& v, rounding_mode::type m);
    }

    v8f32 rint(const v8f32& a);
    v8f32 floor(const v8f32& a);
    v8f32 ceil(const v8f32& a);
    v8f32 trunc(const v8f32& a);
    // returns (~a) & (b)
    v8f32 andnot(const v8f32& a, const v8f32& b);
    v8f32 copysign(const v8f32& x, const v8f32& y);
    v8f32 mulsign(const v8f32& x, const v8f32& y);

    // a*b +c
    v8f32 fma(const v8f32& a, const v8f32& b, const v8f32& c);
    // a*b -c
    v8f32 fms(const v8f32& a, const v8f32& b, const v8f32& c);
    // -(a*b) + c
    v8f32 nfma(const v8f32& a, const v8f32& b, const v8f32& c);
    // -(a*b) - c
    v8f32 nfms(const v8f32& a, const v8f32& b, const v8f32& c);

    template <bool _P0, bool _P1,
              bool _P2, bool _P3,
              bool _P4, bool _P5,
              bool _P6, bool _P7>
    vec<float, 8>
    select(const vec<float, 8>& on_true,
           const vec<float, 8>& on_false);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3,
              int32_t _P4, int32_t _P5,
              int32_t _P6, int32_t _P7>
    vec<float, 8>
    permute(const vec<float, 8>& s);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3,
              int32_t _P4, int32_t _P5,
              int32_t _P6, int32_t _P7>
    vec<float, 8>
    permute(const vec<float, 8>& s0,
            const vec<float, 8>& s1);

#if defined (__AVX2__)

    vec<float, 8>
    permute(const vec<float, 8>& s, const vec<int32_t, 8>& idx);

    template <>
    class variable_vec_lookup_table<float, int32_t, 8> {
    private:
        vec<int32_t, 8> _msk;
    public:
        variable_vec_lookup_table(const vec<int32_t, 8>& idx);
        vec<float, 8>
        from(const float* tbl) const;
    };
#endif

    namespace impl {
        template <>
        class fixed_vec_lookup_table<4, float, int32_t, 8> {
        private:
            __m256i _msk;
            static
            __m256i
            setup_msk(const vec<int32_t, 8>& idx);
        public:
            fixed_vec_lookup_table(const vec<int32_t, 8>& idx);
            vec<float, 8>
            fromp(const float* tbl) const;
        };

#if defined (__AVX2__)
        template <>
        class fixed_vec_lookup_table<8, float, int32_t, 8> {
        private:
            __m256i _msk;
            static
            __m256i
            setup_msk(const vec<int32_t, 8>& idx);
        public:
            fixed_vec_lookup_table(const vec<int32_t, 8>& idx);
            vec<float, 8>
            fromp(const float* tbl) const;
        };

        template <>
        class fixed_vec_lookup_table<32, float, int32_t, 8> {
        private:
            __m256i _msk;
            __m256i _idx_gt_7;
            __m256i _idx_gt_15;
            __m256i _idx_gt_23;
        public:
            fixed_vec_lookup_table(const vec<int32_t, 8>& idx);
            vec<float, 8>
            fromp(const float* tbl) const;
        };
#endif
    }

}

#endif

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V8F32__
