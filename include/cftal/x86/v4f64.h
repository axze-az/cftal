//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_X86_V4F64__)
#define __CFTAL_X86_V4F64__ 1

#if defined (__AVX__)

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/vec_t_n.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/v2f64.h>

namespace cftal {

    template <>
    class vec<double, 4> : public x86::vreg<__m256d> {
    public:
        using base_type = x86::vreg<__m256d>;

        using value_type = double;
#if defined (__AVX512VL__)
        using mask_value_type = bit;
#else
        using mask_value_type = double;
#endif
        using mask_type= vec<mask_value_type, 4>;

        using x86::vreg<__m256d>::vreg;
        vec() = default;
        // create vec{v,v,v,v}
        vec(double v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<double> l);
        // allow construction from vec<double, 8>
        vec(init_list<double> l);
        // allow construction from two halfes
        vec(const vec<double, 2>& lh, const vec<double, 2>& hh);

        // expression template constructor
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<double, 4>, _L, _R>& r);
    };

    template <>
    struct arg< vec<double, 4> > {
        using type = vec<double, 4>;
    };

    template <>
    struct is_vec_specialized<vec<double, 4> > : public std::true_type {};

    template <>
    struct mem< vec<double, 4> > {
        static
        vec<double, 4> load(const double* p, std::size_t n=4);
        static
        void store(double* p, const vec<double, 4>& v);
    };

    vec<double, 2>
    low_half(const vec<double, 4>& s);

    vec<double, 2>
    high_half(const vec<double, 4>& s);

#if !defined (__AVX512VL__)
    bool
    any_of(const vec<double, 4>::mask_type& s);
    bool
    all_of(const vec<double, 4>::mask_type& s);
    bool
    none_of(const vec<double, 4>::mask_type& s);
#endif

    template <std::size_t _I>
    double
    extract(const vec<double, 4>& s);

    vec<double, 4>
    select(const vec<double, 4>::mask_type& msk,
           const vec<double, 4>& on_true,
           const vec<double, 4>& on_false);

    vec<double, 4>
    select_val_or_zero(const vec<double, 4>::mask_type& msk,
                       const vec<double, 4>& on_true);

    vec<double, 4>
    select_zero_or_val(const vec<double, 4>::mask_type& msk,
                       const vec<double, 4>& on_false);

    unsigned
    read_signs(const vec<double, 4>& b);

    bool
    elements_equal(const vec<double, 4>& v);

    v4f64 max(const v4f64& a, const v4f64& b);
    v4f64 min(const v4f64& a, const v4f64& b);
    double max_element(const v4f64& v);
    double min_element(const v4f64& v);

    v4f64 abs(const v4f64& a);
    v4f64 fabs(const v4f64& a);
    v4f64 sqrt(const v4f64& a);

    namespace x86 {
        v4f64 round(const v4f64& v, rounding_mode::type m);
    }

    v4f64 rint(const v4f64& a);
    v4f64 floor(const v4f64& a);
    v4f64 ceil(const v4f64& a);
    v4f64 trunc(const v4f64& a);
    // returns (~a) & (b)
    v4f64 andnot(const v4f64& a, const v4f64& b);
    v4f64 copysign(const v4f64& x, const v4f64& y);
    v4f64 mulsign(const v4f64& x, const v4f64& y);

    // a*b +c
    v4f64 fma(const v4f64& a, const v4f64& b, const v4f64& c);
    // a*b -c
    v4f64 fms(const v4f64& a, const v4f64& b, const v4f64& c);
    // -(a*b) + c
    v4f64 nfma(const v4f64& a, const v4f64& b, const v4f64& c);
    // -(a*b) - c
    v4f64 nfms(const v4f64& a, const v4f64& b, const v4f64& c);

    template <bool _P0, bool _P1,
              bool _P2, bool _P3>
    vec<double, 4>
    select(const vec<double, 4>& on_true,
           const vec<double, 4>& on_false);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3>
    vec<double, 4>
    permute(const vec<double, 4>& s);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3>
    vec<double, 4>
    permute(const vec<double, 4>& s0,
            const vec<double, 4>& s1);

#if defined (__AVX2__)
    template <>
    class variable_lookup_table<double, int32_t, 4> {
    private:
        vec<int32_t, 4> _msk;
    public:
        variable_lookup_table(const vec<int32_t, 4>& idx);
        vec<double, 4>
        from(const double* tbl) const;
    };

    namespace impl {
        template <>
        class fixed_lookup_table<4, double, int32_t, 4> {
        private:
            __m256i _msk;
            static
            __m256i
            setup_msk(const vec<int32_t, 4>& idx);
        public:
            fixed_lookup_table(const vec<int32_t, 4>& idx);
            vec<double, 4>
            fromp(const double* tbl) const;
        };
    }
#endif
}

#endif // __AVX__

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V4F64__
