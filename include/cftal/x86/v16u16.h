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
#if !defined (__CFTAL_X86_V16U16__)
#define __CFTAL_X86_V16U16__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/vreg.h>
#include <cftal/vec_op.h>

namespace cftal {

#define V16U16_SPECIALIZED 1

    template <>
    class vec<uint16_t, 16> : public x86::vreg<__m256i> {
    public:
        using base_type = x86::vreg<__m256i>;

        using value_type = uint16_t;
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
        using mask_value_type = bit;
#else
        using mask_value_type = uint16_t;
#endif
        using mask_type= vec<mask_value_type, 16>;

        using base_type::base_type;
        vec() = default;
        vec(const vec<int16_t, 16>& v);
        // create vec{v,v,v,v}
        vec(uint16_t v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<uint16_t> l);
        // allow construction from vec<int32_t, 16>
        vec(init_list<uint16_t> l);
        // allow construction from two halfes
        vec(const vec<uint16_t, 8>& lh, const vec<uint16_t, 8>& hh);
        // expression template constructor
        template <template <class _U> class _OP,
                  class _L, class _R>
        vec(const expr<_OP<vec<uint16_t, 16> >, _L, _R>& r);
    };

    template <>
    struct arg< vec<uint16_t, 16> > {
        using type = vec<uint16_t, 16>;
    };

    template <>
    struct is_vec_specialized<vec<uint16_t, 16> > : public std::true_type {};

    template <>
    struct mem< vec<uint16_t, 16> > {
        static
        vec<uint16_t, 16> load(const uint16_t* p, std::size_t n=16);
        static
        void store(uint16_t* p, const vec<uint16_t, 16>& v);
    };

    vec<uint16_t, 8> low_half(const vec<uint16_t, 16>& a);
    vec<uint16_t, 8> high_half(const vec<uint16_t, 16>& a);

    template <size_t _I>
    uint16_t
    extract(const vec<uint16_t, 16>& v);

    uint16_t
    extract(const vec<uint16_t, 16>& v, size_t i);

    template <size_t _I>
    void
    insert(vec<uint16_t, 16>& v, const uint16_t& vi);

    void
    insert(vec<uint16_t, 16>& v, const uint16_t& vi, size_t i);

    bool
    all_of(const vec<uint16_t, 16>::mask_type& v);
    bool
    any_of(const vec<uint16_t, 16>::mask_type& v);
    bool
    none_of(const vec<uint16_t, 16>::mask_type& v);

    vec<bit, 16>
    compress_mask(const vec<uint16_t, 16>::mask_type& m);

    template<>
    struct expand_mask<vec<uint16_t, 16> > {
        static
        vec<uint16_t, 16>
        from(const vec<bit, 16>& s);
    };

    v16u16 max(const v16u16& a, const v16u16& b);
    v16u16 min(const v16u16& a, const v16u16& b);

    vec<uint16_t, 16>
    select(const vec<uint16_t, 16>::mask_type& msk,
           const vec<uint16_t, 16>& on_true,
           const vec<uint16_t, 16>& on_false);

    vec<uint16_t, 16>
    select_val_or_zero(const vec<uint16_t, 16>::mask_type& msk,
                       const vec<uint16_t, 16>& on_true);

    vec<uint16_t, 16>
    select_zero_or_val(const vec<uint16_t, 16>::mask_type& msk,
                       const vec<uint16_t, 16>& on_false);

    template <bool _P00, bool _P01, bool _P02, bool _P03,
              bool _P04, bool _P05, bool _P06, bool _P07,
              bool _P08, bool _P09, bool _P10, bool _P11,
              bool _P12, bool _P13, bool _P14, bool _P15>
    vec<uint16_t, 16>
    select(const vec<uint16_t, 16>& on_true,
           const vec<uint16_t, 16>& on_false);

    template <int32_t _P00, int32_t _P01, int32_t _P02, int32_t _P03,
              int32_t _P04, int32_t _P05, int32_t _P06, int32_t _P07,
              int32_t _P08, int32_t _P09, int32_t _P10, int32_t _P11,
              int32_t _P12, int32_t _P13, int32_t _P14, int32_t _P15>
    vec<uint16_t, 16> permute(const vec<uint16_t, 16>& s);

    template <int32_t _P00, int32_t _P01, int32_t _P02, int32_t _P03,
              int32_t _P04, int32_t _P05, int32_t _P06, int32_t _P07,
              int32_t _P08, int32_t _P09, int32_t _P10, int32_t _P11,
              int32_t _P12, int32_t _P13, int32_t _P14, int32_t _P15>
    vec<uint16_t, 16> permute(const vec<uint16_t, 16>& s0,
                              const vec<uint16_t, 16>& s1);

    std::pair<vec<uint16_t, 16>, vec<uint16_t, 16> >
    mul_lo_hi(const vec<uint16_t, 16>& a,
              const vec<uint16_t, 16>& b);

    vec<uint16_t, 16>
    sat_add(const vec<uint16_t, 16>& a, const vec<uint16_t, 16>& b);

    vec<uint16_t, 16>
    sat_sub(const vec<uint16_t, 16>& a, const vec<uint16_t, 16>& b);

    vec<uint16_t, 16>
    average(const vec<uint16_t, 16>& a, const vec<uint16_t, 16>& b);
}


// Local variables:
// mode: c++
// end:
#endif // __CFTAL_SIMD_X86_V16U16__
