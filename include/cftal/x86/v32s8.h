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
#if !defined (__CFTAL_X86_V32S8__)
#define __CFTAL_X86_V32S8__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/vreg.h>
#include <cftal/vec_op.h>
#include <cftal/x86/v16s8.h>

namespace cftal {

#define V32S8_SPECIALIZED 1

    template <>
    class vec<int8_t, 32> : public x86::vreg<__m256i> {
    public:
        using base_type = x86::vreg<__m256i>;

        using value_type = int8_t;
        using mask_value_type = int8_t;
        using mask_type= vec<mask_value_type, 32>;

        using base_type::base_type;
        vec() = default;
        vec(const vec<uint8_t, 32>& v);
        // create vec{v,v,v,v}
        vec(int8_t v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<int8_t> l);
        // allow construction from vec<int8_t, 32>
        vec(init_list<int8_t> l);
        // allow construction from two halfes
        vec(const vec<int8_t, 16>& lh, const vec<int8_t, 16>& hh);
        // expression template constructor
        template <template <class _U> class _OP,
                  class _L, class _R>
        vec(const expr<_OP<vec<int8_t, 32> >, _L, _R>& r);
    };

    template <>
    struct arg< vec<int8_t, 32> > {
        using type = vec<int8_t, 32>;
    };

    template <>
    struct is_vec_specialized<vec<int8_t, 32> > : public std::true_type {};

    template <>
    struct mem< vec<int8_t, 32> > {
        static
        vec<int8_t, 32> load(const int8_t* p, std::size_t n=32);
        static
        void store(int8_t* p, const vec<int8_t, 32>& v);
    };

    vec<int8_t, 16> low_half(const vec<int8_t, 32>& a);
    vec<int8_t, 16> high_half(const vec<int8_t, 32>& a);

    template <size_t _I>
    int8_t
    extract(const vec<int8_t, 32>& v);

    int8_t
    extract(const vec<int8_t, 32>& v, size_t i);

    template <size_t _I>
    void
    insert(vec<int8_t, 32>& v, const int8_t& vi);

    void
    insert(vec<int8_t, 32>& v, const int8_t& vi, size_t i);

    bool
    all_of(const vec<int8_t, 32>::mask_type& v);
    bool
    any_of(const vec<int8_t, 32>::mask_type& v);
    bool
    none_of(const vec<int8_t, 32>::mask_type& v);

    vec<bit, 32>
    compress_mask(const vec<int8_t, 32>::mask_type& m);

    template<>
    struct expand_mask<vec<int8_t, 32> > {
        static
        vec<int8_t, 32>
        from(const vec<bit, 32>& s);
    };

    v32s8 max(const v32s8& a, const v32s8& b);
    v32s8 min(const v32s8& a, const v32s8& b);
    v32s8 abs(const v32s8& a);

    vec<int8_t, 32>
    select(const vec<int8_t, 32>::mask_type& msk,
           const vec<int8_t, 32>& on_true,
           const vec<int8_t, 32>& on_false);

    vec<int8_t, 32>
    select_val_or_zero(const vec<int8_t, 32>::mask_type& msk,
                       const vec<int8_t, 32>& on_true);

    vec<int8_t, 32>
    select_zero_or_val(const vec<int8_t, 32>::mask_type& msk,
                       const vec<int8_t, 32>& on_false);

    template <bool _P00, bool _P01, bool _P02, bool _P03,
	      bool _P04, bool _P05, bool _P06, bool _P07,
	      bool _P08, bool _P09, bool _P10, bool _P11,
	      bool _P12, bool _P13, bool _P14, bool _P15,
	      bool _P16, bool _P17, bool _P18, bool _P19,
	      bool _P20, bool _P21, bool _P22, bool _P23,
	      bool _P24, bool _P25, bool _P26, bool _P27,
	      bool _P28, bool _P29, bool _P30, bool _P31>
    vec<int8_t, 32>
    select(const vec<int8_t, 32>& on_true,
           const vec<int8_t, 32>& on_false);

    template <int32_t _P00, int32_t _P01, int32_t _P02, int32_t _P03,
	      int32_t _P04, int32_t _P05, int32_t _P06, int32_t _P07,
	      int32_t _P08, int32_t _P09, int32_t _P10, int32_t _P11,
	      int32_t _P12, int32_t _P13, int32_t _P14, int32_t _P15,
	      int32_t _P16, int32_t _P17, int32_t _P18, int32_t _P19,
	      int32_t _P20, int32_t _P21, int32_t _P22, int32_t _P23,
	      int32_t _P24, int32_t _P25, int32_t _P26, int32_t _P27,
	      int32_t _P28, int32_t _P29, int32_t _P30, int32_t _P31>
    vec<int8_t, 32> permute(const vec<int8_t, 32>& s);

    template <int32_t _P00, int32_t _P01, int32_t _P02, int32_t _P03,
	      int32_t _P04, int32_t _P05, int32_t _P06, int32_t _P07,
	      int32_t _P08, int32_t _P09, int32_t _P10, int32_t _P11,
	      int32_t _P12, int32_t _P13, int32_t _P14, int32_t _P15,
	      int32_t _P16, int32_t _P17, int32_t _P18, int32_t _P19,
	      int32_t _P20, int32_t _P21, int32_t _P22, int32_t _P23,
	      int32_t _P24, int32_t _P25, int32_t _P26, int32_t _P27,
	      int32_t _P28, int32_t _P29, int32_t _P30, int32_t _P31>
    vec<int8_t, 32> permute(const vec<int8_t, 32>& s0,
                            const vec<int8_t, 32>& s1);

    std::pair<vec<int8_t, 32>, vec<int8_t, 32> >
    mul_lo_hi(const vec<int8_t, 32>& a, const vec<int8_t, 32>& b);

    vec<int8_t, 32>
    sat_add(const vec<int8_t, 32>& a, const vec<int8_t, 32>& b);

    vec<int8_t, 32>
    sat_sub(const vec<int8_t, 32>& a, const vec<int8_t, 32>& b);

    vec<int8_t, 32>
    average(const vec<int8_t, 32>& a, const vec<int8_t, 32>& b);

}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V32S8__
