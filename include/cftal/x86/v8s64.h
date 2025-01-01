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
#if !defined (__CFTAL_X86_V8S64__)
#define __CFTAL_X86_V8S64__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/vec_op.h>

namespace cftal {

#define V8S64_SPECIALIZED 1

    template <>
    class vec<int64_t, 8> : public x86::vreg<__m512i> {
    public:
        using base_type = x86::vreg<__m512i>;

        using value_type = int64_t;
        using mask_value_type = bit;
        using mask_type= vec<mask_value_type, 8>;

        using base_type::base_type;
        vec() = default;
        vec(const vec<uint64_t, 8>& v);
        // create vec{v,v}
        vec(int64_t v);
        // create vec(l, h);
        vec(const vec<int64_t, 4>& l, const vec<int64_t, 4>& h);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<int64_t> l);
        // allow construction from vec<int64_t, 8>
        vec(init_list<int64_t> l);
        // expression template constructor
        template <template <class _U> class _OP,
                  class _L, class _R>
        vec(const expr<_OP<vec<int64_t, 8> >, _L, _R>& r);
    };

    template <>
    struct arg< vec<int64_t, 8> > {
        using type = vec<int64_t, 8>;
    };

    template <>
    struct is_vec_specialized<vec<int64_t, 8> > : public std::true_type {};

    template <>
    struct mem< vec<int64_t, 8> > {
        static
        vec<int64_t, 8> load(const int64_t* p, std::size_t n=8);
        static
        void store(int64_t* p, const vec<int64_t, 8>& v);
    };

    vec<int64_t, 4>
    low_half(const vec<int64_t, 8>& v);
    vec<int64_t, 4>
    high_half(const vec<int64_t, 8>& v);

    template <size_t _I>
    int64_t
    extract(const vec<int64_t, 8>& v);

    int64_t
    extract(const vec<int64_t, 8>& v, size_t i);

    template <size_t _I>
    void
    insert(vec<int64_t, 8>& v, const int64_t& vi);

    void
    insert(vec<int64_t, 8>& v, const int64_t& vi, size_t i);


    v8s64 max(const v8s64& a, const v8s64& b);
    v8s64 min(const v8s64& a, const v8s64& b);
    v8s64 abs(const v8s64& a);

    vec<int64_t, 8>
    select(const vec<int64_t, 8>::mask_type& msk,
           const vec<int64_t, 8>& on_true,
           const vec<int64_t, 8>& on_false);

    vec<int64_t, 8>
    select_val_or_zero(const vec<int64_t, 8>::mask_type& msk,
                       const vec<int64_t, 8>& on_true);

    vec<int64_t, 8>
    select_zero_or_val(const vec<int64_t, 8>::mask_type& msk,
                       const vec<int64_t, 8>& on_false);

    template <bool _P0, bool _P1, bool _P2, bool _P3,
              bool _P4, bool _P5, bool _P6, bool _P7>
    vec<int64_t, 8>
    select(const vec<int64_t, 8>& on_true,
           const vec<int64_t, 8>& on_false);

    template <int32_t _P0, int32_t _P1, int32_t _P2, int32_t _P3,
              int32_t _P4, int32_t _P5, int32_t _P6, int32_t _P7>
    vec<int64_t, 8>
    permute(const vec<int64_t, 8>& s);

    template <int32_t _P0, int32_t _P1, int32_t _P2, int32_t _P3,
              int32_t _P4, int32_t _P5, int32_t _P6, int32_t _P7>
    vec<int64_t, 8>
    permute(const vec<int64_t, 8>& s0,
            const vec<int64_t, 8>& s1);

    vec<int64_t, 8>
    permute(const vec<int64_t, 8>& s, const vec<int64_t, 8>& idx);

    std::pair<vec<int64_t, 8>, vec<int64_t, 8> >
    mul_lo_hi(const vec<int64_t, 8>& a, const vec<int64_t, 8>& b);

}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V8S64__
