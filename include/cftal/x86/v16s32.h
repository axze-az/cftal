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
#if !defined (__CFTAL_X86_V16S32__)
#define __CFTAL_X86_V16S32__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/vec_op.h>

#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)

namespace cftal {

#define V16S32_SPECIALIZED 1

    template <>
    class vec<int32_t, 16> : public x86::vreg<__m512i> {
    public:
        using base_type = x86::vreg<__m512i>;

        using value_type = int32_t;
        using mask_value_type = bit;
        using mask_type= vec<mask_value_type, 16>;

        using base_type::base_type;
        vec() = default;
        vec(const v16u32& v);
        // create vec{v,v,v,v}
        vec(int32_t v);
        vec(const vec<int32_t, 8>& l, const vec<int32_t, 8>& h);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<int32_t> l);
        // allow construction from vec<int32_t, 16>
        vec(init_list<int32_t> l);
        // expression template constructor
        template <template <class _U> class _OP,
                  class _L, class _R>
        vec(const expr<_OP<vec<int32_t, 16> >, _L, _R>& r);
    };

    template <>
    struct arg< vec<int32_t, 16> > {
        using type = vec<int32_t, 16>;
    };

    template <>
    struct is_vec_specialized<vec<int32_t, 16> > : public std::true_type {};

    template <>
    struct mem< vec<int32_t, 16> > {
        static
        vec<int32_t, 16>
	load(const int32_t* p, ssize_t n=16);
        static
        void
	store(int32_t* p, const vec<int32_t, 16>& v, ssize_t n=16);
    };

    v8s32 low_half(const v16s32& a);
    v8s32 high_half(const v16s32& a);

    template <size_t _I>
    int32_t
    extract(const vec<int32_t, 16>& v);

    int32_t
    extract(const vec<int32_t, 16>& v, size_t i);

    template <size_t _I>
    void
    insert(vec<int32_t, 16>& v, const int32_t& vi);

    void
    insert(vec<int32_t, 16>& v, const int32_t& vi, size_t i);

    v16s32 max(const v16s32& a, const v16s32& b);
    v16s32 min(const v16s32& a, const v16s32& b);
    v16s32 abs(const v16s32& a);

    vec<int32_t, 16>
    select(const vec<int32_t, 16>::mask_type& msk,
           const vec<int32_t, 16>& on_true,
           const vec<int32_t, 16>& on_false);

    vec<int32_t, 16>
    select_val_or_zero(const vec<int32_t, 16>::mask_type& msk,
                       const vec<int32_t, 16>& on_true);

    vec<int32_t, 16>
    select_zero_or_val(const vec<int32_t, 16>::mask_type& msk,
                       const vec<int32_t, 16>& on_false);

    template <bool _P00, bool _P01, bool _P02, bool _P03,
              bool _P04, bool _P05, bool _P06, bool _P07,
              bool _P08, bool _P09, bool _P10, bool _P11,
              bool _P12, bool _P13, bool _P14, bool _P15>
    vec<int32_t, 16>
    select(const vec<int32_t, 16>& on_true,
           const vec<int32_t, 16>& on_false);

    template <int32_t _P00, int32_t _P01, int32_t _P02, int32_t _P03,
              int32_t _P04, int32_t _P05, int32_t _P06, int32_t _P07,
              int32_t _P08, int32_t _P09, int32_t _P10, int32_t _P11,
              int32_t _P12, int32_t _P13, int32_t _P14, int32_t _P15>
    vec<int32_t, 16> permute(const vec<int32_t, 16>& s);

    template <int32_t _P00, int32_t _P01, int32_t _P02, int32_t _P03,
              int32_t _P04, int32_t _P05, int32_t _P06, int32_t _P07,
              int32_t _P08, int32_t _P09, int32_t _P10, int32_t _P11,
              int32_t _P12, int32_t _P13, int32_t _P14, int32_t _P15>
    vec<int32_t, 16> permute(const vec<int32_t, 16>& s0,
                             const vec<int32_t, 16>& s1);

    vec<int32_t, 16>
    permute(const vec<int32_t, 16>& s, const vec<int32_t, 16>& idx);

    std::pair<vec<int32_t, 16>, vec<int32_t, 16> >
    mul_lo_hi(const vec<int32_t, 16>& a, const vec<int32_t, 16>& b);
}

#endif

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V16S32__
