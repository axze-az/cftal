//
// Copyright (C) 2010-2026 Axel Zeuner
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
#if !defined (__CFTAL_X86_V8F64__)
#define __CFTAL_X86_V8F64__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/vec_t_n.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/v4f64.h>

namespace cftal {

#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)

#define V8F64_SPECIALIZED 1

    template <>
    class vec<double, 8> : public x86::vreg<__m512d> {
    public:
        using base_type = x86::vreg<__m512d>;

        using value_type = double;
        using mask_value_type = bit;
        using mask_type= vec<mask_value_type, 8>;

        using x86::vreg<__m512d>::vreg;
        vec() = default;
        // create vec{v,v,v,v}
        vec(double v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<double> l);
        // allow construction from vec<double, 8>
        vec(init_list<double> l);
        // allow construction from two halfes
        vec(const vec<double, 4>& lh, const vec<double, 4>& hh);

        // expression template constructor
        template <template <class _U> class _OP,
                  class _L, class _R>
        vec(const expr<_OP<vec<double, 8> >, _L, _R>& r);
    };

    template <>
    struct arg<vec<double, 8> > {
        using type = vec<double, 8>;
    };

    template <>
    struct is_vec_specialized<vec<double, 8> >: public std::true_type {};

    template <>
    struct mem< vec<double, 8> > {
        static
        vec<double, 8>
	load(const double* p, ssize_t n=8);
        static
        void
	store(double* p, const vec<double, 8>& v, ssize_t n=8);
    };

    vec<double, 4>
    low_half(const vec<double, 8>& s);

    vec<double, 4>
    high_half(const vec<double, 8>& s);

    template <size_t _I>
    double
    extract(const vec<double, 8>& v);

    double
    extract(const vec<double, 8>& v, size_t i);

    template <size_t _I>
    void
    insert(vec<double, 8>& v, const double& vi);

    void
    insert(vec<double, 8>& v, const double& vi, size_t i);

    template <std::size_t _I>
    double
    extract(const vec<double, 8>& s);

    vec<double, 8>
    select(const vec<double, 8>::mask_type& msk,
           const vec<double, 8>& on_true,
           const vec<double, 8>& on_false);

    vec<double, 8>
    select_val_or_zero(const vec<double, 8>::mask_type& msk,
                       const vec<double, 8>& on_true);

    vec<double, 8>
    select_zero_or_val(const vec<double, 8>::mask_type& msk,
                       const vec<double, 8>& on_false);

    unsigned
    read_signs(const vec<double, 8>::mask_type& b);

    bool
    elements_equal(const vec<double, 8>& v);

    v8f64 max(const v8f64& a, const v8f64& b);
    v8f64 min(const v8f64& a, const v8f64& b);
    v8f64 abs(const v8f64& a);
    v8f64 sqrt(const v8f64& a);

    namespace x86 {
        v8f64 round(const v8f64& v, rounding_mode::type m);
    }

    v8f64 rint(const v8f64& a);
    v8f64 floor(const v8f64& a);
    v8f64 ceil(const v8f64& a);
    v8f64 trunc(const v8f64& a);
    // returns (~a) & (b)
    v8f64 andnot(const v8f64& a, const v8f64& b);
    v8f64 copysign(const v8f64& x, const v8f64& y);
    v8f64 mulsign(const v8f64& x, const v8f64& y);

    // a*b +c
    v8f64 fma(const v8f64& a, const v8f64& b, const v8f64& c);
    // a*b -c
    v8f64 fms(const v8f64& a, const v8f64& b, const v8f64& c);
    // -(a*b) + c
    v8f64 nfma(const v8f64& a, const v8f64& b, const v8f64& c);
    // -(a*b) - c
    v8f64 nfms(const v8f64& a, const v8f64& b, const v8f64& c);

    template <bool _P0, bool _P1,
              bool _P2, bool _P3,
              bool _P4, bool _P5,
              bool _P6, bool _P7>
    vec<double, 8>
    select(const vec<double, 8>& on_true,
           const vec<double, 8>& on_false);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3,
              int32_t _P4, int32_t _P5,
              int32_t _P6, int32_t _P7>
    vec<double, 8>
    permute(const vec<double, 8>& s);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3,
              int32_t _P4, int32_t _P5,
              int32_t _P6, int32_t _P7>
    vec<double, 8>
    permute(const vec<double, 8>& s0,
            const vec<double, 8>& s1);

    vec<double, 8>
    permute(const vec<double, 8>& s, const vec<int64_t, 8>& idx);

    namespace impl {
        template <>
        class variable_vec_lookup_table<double, int32_t, 8> {
        private:
            vec<int32_t, 8> _msk;
        public:
            variable_vec_lookup_table(const vec<int32_t, 8>& idx);
            vec<double, 8>
            fromp(const double* tbl) const;
        };
    }
}

#endif // __AVX512F__

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V8F64__
