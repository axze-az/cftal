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
#if !defined (__CFTAL_X86_V2F64__)
#define __CFTAL_X86_V2F64__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/vec_t_n.h>
#include <cftal/vec_lookup.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/x86/v4s32.h>
#include <cftal/x86/vreg.h>

namespace cftal {

#define V2F64_SPECIALIZED 1

    template <>
    class vec<double, 2> : public x86::vreg<__m128d> {
    public:
        using base_type= x86::vreg<__m128d>;

        using value_type = double;
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
        using mask_value_type = bit;
#else
        using mask_value_type = double;
#endif
        using mask_type= vec<mask_value_type, 2>;
        using x86::vreg<__m128d>::vreg;;
        vec() = default;
        // create vec{v,v,v,v}
        vec(double v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<double> l);
        // allow construction from vec<double, 8>
        vec(init_list<double> l);
        // allow construction from two halfes
        vec(const vec<double, 1>& lh, const vec<double, 1>& hh);
        // expression template constructor
        template <template <class _U> class _OP,
                  class _L, class _R>
        vec(const expr<_OP<vec<double, 2> >, _L, _R>& r);
    };

    template <>
    struct arg< vec<double, 2> > {
        using type = vec<double, 2>;
    };

    template <>
    struct is_vec_specialized<vec<double, 2> > : public std::true_type {};

    template <>
    struct mem< vec<double, 2> > {
        static
        vec<double, 2>
	load(const double* p, ssize_t n=2);
        static
        void
	store(double* p, const vec<double, 2>& v, ssize_t n=2);
    };

    vec<double, 1>
    low_half(const vec<double, 2>& s);

    vec<double, 1>
    high_half(const vec<double, 2>& s);

    template <size_t _I>
    double
    extract(const vec<double, 2>& v);

    double
    extract(const vec<double, 2>& v, size_t i);

    template <size_t _I>
    void
    insert(vec<double, 2>& v, const double& vi);

    void
    insert(vec<double, 2>& v, const double& vi, size_t i);

#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    bool
    any_of(const vec<double, 2>::mask_type& s);

    bool
    all_of(const vec<double, 2>::mask_type& s);

    bool
    none_of(const vec<double, 2>::mask_type& s);

    vec<bit, 2>
    compress_mask(const vec<double, 2>::mask_type& m);

    template<>
    struct expand_mask<vec<double, 2> > {
        static
        vec<double, 2>
        from(const vec<bit, 2>& s);
    };

#endif

    template <std::size_t _I>
    double
    extract(const vec<double, 2>& s);

    vec<double, 2>
    select(const vec<double, 2>::mask_type& msk,
           const vec<double, 2>& on_true,
           const vec<double, 2>& on_false);

    vec<double, 2>
    select_val_or_zero(const vec<double, 2>::mask_type& msk,
                       const vec<double, 2>& on_true);

    vec<double, 2>
    select_zero_or_val(const vec<double, 2>::mask_type& msk,
                       const vec<double, 2>& on_false);

    unsigned
    read_signs(const vec<double, 2>& b);

    bool
    elements_equal(const v2f64& a);


    v2f64 max(const v2f64& a, const v2f64& b);
    v2f64 min(const v2f64& a, const v2f64& b);

    double hmax(const v2f64& v);
    double min_element(const v2f64& v);

    v2f64 abs(const v2f64& a);
    v2f64 sqrt(const v2f64& a);

    namespace x86 {
        v2f64 round(const v2f64& v, rounding_mode::type m);
    }

    v2f64 rint(const v2f64& a);
    v2f64 floor(const v2f64& a);
    v2f64 ceil(const v2f64& a);
    v2f64 trunc(const v2f64& a);
    // returns (~a) & (b)
    v2f64 andnot(const v2f64& a, const v2f64& b);
    v2f64 copysign(const v2f64& x, const v2f64& y);
    v2f64 mulsign(const v2f64& x, const v2f64& y);

    // a*b +c
    v2f64 fma(const v2f64& a, const v2f64& b, const v2f64& c);
    // a*b -c
    v2f64 fms(const v2f64& a, const v2f64& b, const v2f64& c);
    // -(a*b) + c
    v2f64 nfma(const v2f64& a, const v2f64& b, const v2f64& c);
    // -(a*b) - c
    v2f64 nfms(const v2f64& a, const v2f64& b, const v2f64& c);

    template <bool _P0, bool _P1>
    vec<double, 2>
    select(const vec<double, 2>& on_true,
           const vec<double, 2>& on_false);

    template <int32_t _P0, int32_t _P1>
    vec<double, 2>
    permute(const vec<double, 2>& s);

    template <int32_t _P0, int32_t _P1>
    vec<double, 2>
    permute(const vec<double, 2>& s0,
            const vec<double, 2>& s1);

    vec<double, 2>
    permute(const vec<double, 2>& s, const vec<int64_t, 2>& idx);

    namespace impl {
#if 0 // defined (__AVX2__)
        template <>
        class variable_vec_lookup_table<double, int32_t, 2> {
        private:
            vec<int32_t, 4> _msk;
        public:
            variable_vec_lookup_table(const vec<int32_t, 2>& idx);
            vec<double, 2>
            fromp(const double* tbl) const;
        };
#endif

#if defined (__SSSE3__)
        template <>
        class fixed_vec_lookup_table<2, double, int32_t, 2> {
        private:
            __m128i _msk;
            static
            __m128i
            setup_msk(const vec<int32_t, 2>& idx);
        public:
            fixed_vec_lookup_table(const vec<int32_t, 2>& idx);
            vec<double, 2>
            fromp(const double* tbl) const;
        };
#endif
#if defined (__AVX2__)
        template <>
        class fixed_vec_lookup_table<4, double, int32_t, 2> {
        private:
            __m128i _msk;
            static
            __m128i
            setup_msk(const vec<int32_t, 2>& idx);
        public:
            fixed_vec_lookup_table(const vec<int32_t, 2>& idx);
            vec<double, 2>
            fromp(const double* tbl) const;
        };
#endif
    }
}


// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2F64__
