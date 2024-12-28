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
#if !defined (__CFTAL_X86_V16F32_H__)
#define __CFTAL_X86_V16F32_H__ 1

#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__>0)

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/vec_t_n.h>
#include <cftal/vec_lookup.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/x86/v8f32.h>

namespace cftal {

#define V16F32_SPECIALIZED 1

    template <>
    class vec<float, 16> : public x86::vreg<__m512> {
    public:
        using base_type = x86::vreg<__m512>;

        using value_type = float;
        using mask_value_type = bit;
        using mask_type= vec<mask_value_type, 16>;

        using x86::vreg<__m512>::vreg;
        vec() = default;
        // create vec{v,v,v,v,....}
        vec(float v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<float> l);
        // allow construction from vec<float, 16>
        vec(init_list<float> l);
        // allow construction from two halfes
        vec(const vec<float, 8>& lh, const vec<float, 8>& hh);

        // expression template constructor
        template <template <class _U> class _OP,
                  class _L, class _R>
        vec(const expr<_OP<vec<float, 16> >, _L, _R>& r);
    };

    template <>
    struct arg< vec<float, 16> > {
        using type = vec<float, 16>;
    };

    template <>
    struct is_vec_specialized<vec<float, 16> > : public std::true_type {};

    template <>
    struct mem< vec<float, 16> > {
        static
        vec<float, 16> load(const float* p, std::size_t n=16);
        static
        void store(float* p, const vec<float, 16>& v);
    };

    vec<float, 8>
    low_half(const vec<float, 16>& s);

    vec<float, 8>
    high_half(const vec<float, 16>& s);

    template <size_t _I>
    float
    extract(const vec<float, 16>& v);

    float
    extract(const vec<float, 16>& v, size_t i);

    template <size_t _I>
    void
    insert(vec<float, 16>& v, const float& vi);

    void
    insert(vec<float, 16>& v, const float& vi, size_t i);

    vec<float, 16>
    select(const vec<float, 16>::mask_type& msk,
           const vec<float, 16>& on_true,
           const vec<float, 16>& on_false);

    vec<float, 16>
    select_val_or_zero(const vec<float, 16>::mask_type& msk,
                       const vec<float, 16>& on_true);

    vec<float, 16>
    select_zero_or_val(const vec<float, 16>::mask_type& msk,
                       const vec<float, 16>& on_false);

    unsigned
    read_signs(const vec<float, 16>::mask_type& b);

    bool
    elements_equal(const vec<float, 16>& v);


    v16f32 max(const v16f32& a, const v16f32& b);
    v16f32 min(const v16f32& a, const v16f32& b);
    v16f32 abs(const v16f32& a);
    v16f32 sqrt(const v16f32& a);

    namespace x86 {
        v16f32 round(const v16f32& v, rounding_mode::type m);
    }

    v16f32 rint(const v16f32& a);
    v16f32 floor(const v16f32& a);
    v16f32 ceil(const v16f32& a);
    v16f32 trunc(const v16f32& a);
    // returns (~a) & (b)
    v16f32 andnot(const v16f32& a, const v16f32& b);
    v16f32 copysign(const v16f32& x, const v16f32& y);
    v16f32 mulsign(const v16f32& x, const v16f32& y);

    // a*b +c
    v16f32 fma(const v16f32& a, const v16f32& b, const v16f32& c);
    // a*b -c
    v16f32 fms(const v16f32& a, const v16f32& b, const v16f32& c);
    // -(a*b) + c
    v16f32 nfma(const v16f32& a, const v16f32& b, const v16f32& c);
    // -(a*b) - c
    v16f32 nfms(const v16f32& a, const v16f32& b, const v16f32& c);

    template <bool _P00, bool _P01, bool _P02, bool _P03,
              bool _P04, bool _P05, bool _P06, bool _P07,
              bool _P08, bool _P09, bool _P10, bool _P11,
              bool _P12, bool _P13, bool _P14, bool _P15>
    vec<float, 16>
    select(const vec<float, 16>& on_true,
           const vec<float, 16>& on_false);

    template <int32_t _P00, int32_t _P01, int32_t _P02, int32_t _P03,
              int32_t _P04, int32_t _P05, int32_t _P06, int32_t _P07,
              int32_t _P08, int32_t _P09, int32_t _P10, int32_t _P11,
              int32_t _P12, int32_t _P13, int32_t _P14, int32_t _P15>
    vec<float, 16>
    permute(const vec<float, 16>& s);

    template <int32_t _P00, int32_t _P01, int32_t _P02, int32_t _P03,
              int32_t _P04, int32_t _P05, int32_t _P06, int32_t _P07,
              int32_t _P08, int32_t _P09, int32_t _P10, int32_t _P11,
              int32_t _P12, int32_t _P13, int32_t _P14, int32_t _P15>
    vec<float, 16>
    permute(const vec<float, 16>& s0,
            const vec<float, 16>& s1);

    vec<float, 16>
    permute(const vec<float, 16>& s, const vec<int32_t, 16>& idx);

    namespace impl {

        template <>
        class variable_vec_lookup_table<float, int32_t, 16> {
        private:
            vec<int32_t, 16> _msk;
        public:
            variable_vec_lookup_table(const vec<int32_t, 16>& idx);
            vec<float, 16>
            fromp(const float* tbl) const;
        };

        template <>
        class fixed_vec_lookup_table<4, float, int32_t, 16> {
        private:
            __m512i _msk;
            static
            __m512i
            setup_msk(const vec<int32_t, 16>& idx);
        public:
            fixed_vec_lookup_table(const vec<int32_t, 16>& idx);
            vec<float, 16>
            fromp(const float* tbl) const;
        };

        template <>
        class fixed_vec_lookup_table<8, float, int32_t, 16> {
        private:
            __m512i _msk;
            static
            __m512i
            setup_msk(const vec<int32_t, 16>& idx);
        public:
            fixed_vec_lookup_table(const vec<int32_t, 16>& idx);
            vec<float, 16>
            fromp(const float* tbl) const;
        };

        template <>
        class fixed_vec_lookup_table<32, float, int32_t, 16> {
        private:
            __m512i _msk;
            __mmask16 _idx_gt_15;
        public:
            fixed_vec_lookup_table(const vec<int32_t, 16>& idx);
            vec<float, 16>
            fromp(const float* tbl) const;
        };
    }

}

#endif // __AVX512F__ ...

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V16F32__
