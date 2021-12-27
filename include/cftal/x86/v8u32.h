// 
// Copyright (C) 2010-2021 Axel Zeuner
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
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA  
//
#if !defined (__CFTAL_X86_V8U32__)
#define __CFTAL_X86_V8U32__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/vec_op.h>

namespace cftal {

#define V8U32_SPECIALIZED 1

    template <>
    class vec<uint32_t, 8> : public x86::vreg<__m256i> {
    public:
        using base_type = x86::vreg<__m256i>;

        using value_type = uint32_t;
#if defined (__AVX512VL__)
        using mask_value_type = bit;
#else
        using mask_value_type = uint32_t;
#endif
        using mask_type= vec<mask_value_type, 8>;

        using base_type::base_type;
        vec() = default;
        vec(const vec<int32_t, 8>& v);
        vec(const vec<uint32_t, 4>& l, const vec<uint32_t, 4>& h);
        // create vec{v,v,v,v}
        vec(uint32_t v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<uint32_t> l);
        // allow construction from vec<int32_t, 8>
        vec(init_list<uint32_t> l);
        // expression template constructor
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<uint32_t, 8>, _L, _R>& r);
    };

    template <>
    struct arg< vec<uint32_t, 8> > {
        using type = vec<uint32_t, 8>;
    };

    template <>
    struct is_vec_specialized<vec<uint32_t, 8> > : public std::true_type {};

    template <>
    struct mem< vec<uint32_t, 8> > {
        static
        vec<uint32_t, 8> load(const uint32_t* p, std::size_t n=8);
        static
        void store(uint32_t* p, const vec<uint32_t, 8>& v);
    };

    v4u32 low_half(const v8u32& a);
    v4u32 high_half(const v8u32& a);

    template <size_t _I>
    uint32_t
    extract(const vec<uint32_t, 8>& v);

    uint32_t
    extract(const vec<uint32_t, 8>& v, size_t i);

    template <size_t _I>
    void
    insert(vec<uint32_t, 8>& v, const uint32_t& vi);

    void
    insert(vec<uint32_t, 8>& v, const uint32_t& vi, size_t i);

#if !defined (__AVX512VL__)
    bool
    all_of(const vec<uint32_t, 8>::mask_type& v);
    bool
    any_of(const vec<uint32_t, 8>::mask_type& v);
    bool
    none_of(const vec<uint32_t, 8>::mask_type& v);
#endif

    v8u32 max(const v8u32& a, const v8u32& b);
    v8u32 min(const v8u32& a, const v8u32& b);

    vec<uint32_t, 8>
    select(const vec<uint32_t, 8>::mask_type& msk,
           const vec<uint32_t, 8>& on_true,
           const vec<uint32_t, 8>& on_false);

    vec<uint32_t, 8>
    select_val_or_zero(const vec<uint32_t, 8>::mask_type& msk,
                       const vec<uint32_t, 8>& on_true);

    vec<uint32_t, 8>
    select_zero_or_val(const vec<uint32_t, 8>::mask_type& msk,
                       const vec<uint32_t, 8>& on_false);

    template <bool _P0, bool _P1, bool _P2, bool _P3,
              bool _P4, bool _P5, bool _P6, bool _P7>
    vec<uint32_t, 8>
    select(const vec<uint32_t, 8>& on_true,
           const vec<uint32_t, 8>& on_false);

    template <int32_t _P0, int32_t _P1, int32_t _P2, int32_t _P3,
              int32_t _P4, int32_t _P5, int32_t _P6, int32_t _P7>
    vec<uint32_t, 8> permute(const vec<uint32_t, 8>& s);

    template <int32_t _P0, int32_t _P1, int32_t _P2, int32_t _P3,
              int32_t _P4, int32_t _P5, int32_t _P6, int32_t _P7>
    vec<uint32_t, 8> permute(const vec<uint32_t, 8>& s0,
                             const vec<uint32_t, 8>& s1);

    std::pair<vec<uint32_t, 8>, vec<uint32_t, 8> >
    mul_lo_hi(const vec<uint32_t, 8>& a,
              const vec<uint32_t, 8>& b);
}


// Local variables:
// mode: c++
// end:
#endif // __CFTAL_SIMD_X86_V4U32__
