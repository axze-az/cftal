//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_VEC_T_N_H__)
#define __CFTAL_VEC_T_N_H__ 1

#include <cftal/config.h>
#include <cftal/expr.h>
#include <cftal/constants.h>
#include <cftal/init_list.h>
#include <cftal/arg.h>
#include <cftal/mem.h>
#include <type_traits>
#include <iosfwd>
#include <algorithm>


namespace cftal {

    template <typename _T, std::size_t _N >
    class vec {
    public:
        // value type
        using value_type = _T;
        // vector with half the length
        using half_type = vec<_T, _N/2>;
        // type of value of a mask vector
        using mask_value_type =
            typename half_type::mask_value_type;
        // vector of mask values
        using mask_type = vec<mask_value_type, _N>;

        vec() = default;
        vec(const vec& r) = default;
        vec(vec&& r) = default;
        vec& operator=(const vec& r) = default;
        vec& operator=(vec&& r) = default;

#if 0
        template <typename _U>
        explicit vec(const vec<_U, _N>& r);
#endif
        vec(const _T& v);
        vec(std::initializer_list<_T> l);
        vec(init_list<_T> l);
        vec(const half_type& lh, const half_type& hh);

        struct pair_type {
            half_type first;
            half_type second;
            pair_type() = default;
            pair_type(const pair_type& ) = default;
            pair_type(pair_type&& ) = default;
            pair_type& operator=(const pair_type&) = default;
            pair_type& operator=(pair_type&&) = default;
            pair_type(half_type l, half_type h) : first(l), second(h) {}
        };
        const pair_type& operator()() const;
        const half_type& lh() const;
        const half_type& hh() const;

        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<_T, _N>, _L, _R>& r);
    private:
        static_assert(0==(_N & (_N-1)),
                      "vec<_T, _N>: _N is not a power of 2");
        static_assert(_N > 0 && _N <= 64,
                      "_N must be element of [1, 64]");
        pair_type _v;
    };

    template <typename _T, std::size_t _N>
    struct expr_traits<vec<_T, _N> > {
        using type = const vec<_T, _N>&;
    };

    template <typename _T>
    struct expr_traits<vec<_T, 1> > {
        using type = vec<_T, 1>;
    };

    template <typename _T>
    struct is_vec_specialized : public std::false_type {};

    using v1f64 = vec<double, 1>;
    using v2f64 = vec<double, 2>;
    using v4f64 = vec<double, 4>;
    using v8f64 = vec<double, 8>;

    using v1f32 = vec<float, 1>;
    using v2f32 = vec<float, 2>;
    using v4f32 = vec<float, 4>;
    using v8f32 = vec<float, 8>;
    using v16f32= vec<float, 16>;

    using v8s16 = vec<int16_t, 8>;
    using v8u16 = vec<uint16_t, 8>;
    using v16s16= vec<int16_t, 16>;
    using v16u16= vec<uint16_t, 16>;

    using v1s32 = vec<int32_t, 1>;
    using v1u32 = vec<uint32_t, 1>;
    using v2s32 = vec<int32_t, 2>;
    using v2u32 = vec<uint32_t, 2>;
    using v4s32 = vec<int32_t, 4>;
    using v4u32 = vec<uint32_t, 4>;
    using v8s32 = vec<int32_t, 8>;
    using v8u32 = vec<uint32_t, 8>;
    using v16s32 = vec<int32_t, 16>;
    using v16u32 = vec<uint32_t, 16>;

    using v1s64 = vec<int64_t, 1>;
    using v1u64 = vec<uint64_t, 1>;
    using v2s64 = vec<int64_t, 2>;
    using v2u64 = vec<uint64_t, 2>;
    using v4s64 = vec<int64_t, 4>;
    using v4u64 = vec<uint64_t, 4>;
    using v8s64 = vec<int64_t, 8>;
    using v8u64 = vec<uint64_t, 8>;

    // return the lower half of the vector
    template <typename _T, std::size_t _N>
    const typename vec<_T, _N>::half_type&
    low_half(const vec<_T, _N>& v);

    // return the higher half of the vector
    template <typename _T, std::size_t _N>
    const typename vec<_T, _N>::half_type&
    high_half(const vec<_T, _N>& v);

    // extract one element from a vector
    template <std::size_t _I, typename _T, std::size_t _N>
    _T extract(const vec<_T, _N>& v);

    // test if all elements lt 0 / have their MSB set
    template <typename _T, std::size_t _N>
    bool all_of(const vec<_T, _N>& v);
    // test if any element lt 0 / has its MSB set
    template <typename _T, std::size_t _N>
    bool any_of(const vec<_T, _N>& v);
    // test of no element lt 0 / MSB is not set
    template <typename _T, std::size_t _N>
    bool none_of(const vec<_T, _N>& v);

    // return the low and the high part of a
    // multiplication for integer types
    template <typename _T, std::size_t _N>
    std::enable_if_t<std::is_integral<_T>::value,
                     std::pair<vec<_T, _N>, vec<_T, _N> > >
    mul_lo_hi(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // variable select function on mask
    template <typename _T, std::size_t _N>
    vec<_T, _N>
    select(const typename vec<_T, _N>::mask_type& m,
           const vec<_T, _N>& on_true,
           const vec<_T, _N>& on_false);

    // variable select value or zero function on mask
    template <typename _T, std::size_t _N>
    vec<_T, _N>
    select_val_or_zero(const typename vec<_T, _N>::mask_type& m,
                       const vec<_T, _N>& on_true);

    // variable select zero or value function on mask
    template <typename _T, std::size_t _N>
    vec<_T, _N>
    select_zero_or_val(const typename vec<_T, _N>::mask_type& m,
                       const vec<_T, _N>& on_false);

    // fixed select on vector of length 2
    template <bool _I0, bool _I1, typename _T>
    vec<_T, 2>
    select(const vec<_T, 2>& a, const vec<_T, 2>& b);

    // fixed select on vector of length 4
    template <bool _I0, bool _I1, bool _I2, bool _I3, typename _T>
    vec<_T, 4>
    select(const vec<_T, 4>& a, const vec<_T, 4>& b);

    // fixed select on vector of length 8
    template <bool _I0, bool _I1, bool _I2, bool _I3,
              bool _I4, bool _I5, bool _I6, bool _I7, typename _T>
    vec<_T, 8>
    select(const vec<_T, 8>& a, const vec<_T, 8>& b);

    // fixed select on vector of length 16
    template <bool _I0, bool _I1, bool _I2, bool _I3,
              bool _I4, bool _I5, bool _I6, bool _I7,
              bool _I8, bool _I9, bool _IA, bool _IB,
              bool _IC, bool _ID, bool _IE, bool _IF, typename _T>
    vec<_T, 16>
    select(const vec<_T, 16>& a, const vec<_T, 16>& b);

    // fixed permutation of one vector of length 2
    template <int32_t _I0, int32_t _I1, typename _T>
    vec<_T, 2>
    permute(const vec<_T, 2>& v);

    // fixed permutation of two vectors of length 2
    template <int32_t _I0, int32_t _I1, typename _T>
    vec<_T, 2>
    permute(const vec<_T, 2>& v0, const vec<_T, 2>& v1);

    // fixed permutation of one vector of length 4
    template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
              typename _T>
    vec<_T, 4>
    permute(const vec<_T, 4>& v);

    // fixed permutation of two vectors of length 4
    template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
              typename _T>
    vec<_T, 4>
    permute(const vec<_T, 4>& v0, const vec<_T, 4>& v1);

    // fixed permutation of one vector of length 8
    template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
              int32_t _I4, int32_t _I5, int32_t _I6, int32_t _I7,
              typename _T>
    vec<_T, 8>
    permute(const vec<_T, 8>& v);

    // fixed permutation of two vectors of length 8
    template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
              int32_t _I4, int32_t _I5, int32_t _I6, int32_t _I7,
              typename _T>
    vec<_T, 8>
    permute(const vec<_T, 8>& v0, const vec<_T, 8>& v1);

    // fixed permutation of one vector of length 8
    template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
              int32_t _I4, int32_t _I5, int32_t _I6, int32_t _I7,
              int32_t _I8, int32_t _I9, int32_t _IA, int32_t _IB,
              int32_t _IC, int32_t _ID, int32_t _IE, int32_t _IF,
              typename _T>
    vec<_T, 16>
    permute(const vec<_T, 16>& v);

    // fixed permutation of two vectors of length 16
    template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
              int32_t _I4, int32_t _I5, int32_t _I6, int32_t _I7,
              int32_t _I8, int32_t _I9, int32_t _IA, int32_t _IB,
              int32_t _IC, int32_t _ID, int32_t _IE, int32_t _IF,
              typename _T>
    vec<_T, 16>
    permute(const vec<_T, 16>& v0, const vec<_T, 16>& v1);

    // helper function for even_elements, odd_elements: returns even
    // elements in low half, odd elements in high half
    template <typename _T>
    vec<_T, 4>
    sort_even_odd(const vec<_T, 4>& v);

    template <typename _T>
    vec<_T, 8>
    sort_even_odd(const vec<_T, 8>& v);

    template <typename _T>
    vec<_T, 16>
    sort_even_odd(const vec<_T, 16>& v);

    // return the even elements 0, 2, ... of v
    template <typename _T, std::size_t _N>
    vec<_T, _N/2>
    even_elements(const vec<_T, _N>& v);

    // return the even elements 0, 2, 4, 6, 8, 10, 12, 14 of v
    template <typename _T>
    vec<_T, 8>
    even_elements(const vec<_T, 16>& v);

    // return the even elements 0, 2, 4, 6 of v
    template <typename _T>
    vec<_T, 4>
    even_elements(const vec<_T, 8>& v);

    // return the even elements 0, 2 of v
    template <typename _T>
    vec<_T, 2>
    even_elements(const vec<_T, 4>& v);

    // return the even element 0 of v
    template <typename _T>
    vec<_T, 1>
    even_elements(const vec<_T, 2>& v);

    // return the odd elements 1, 3, 5, ... of v
    template <typename _T, std::size_t _N>
    vec<_T, _N/2>
    odd_elements(const vec<_T, _N>& v);

    // return the odd elements 1, 3, 5, 7, 9, 11, 13, 15 of v
    template <typename _T>
    vec<_T, 8>
    odd_elements(const vec<_T, 16>& v);

    // return the odd elements 1, 3, 5, 7 of v
    template <typename _T>
    vec<_T, 4>
    odd_elements(const vec<_T, 8>& v);

    // return the odd elements 1, 3 of v
    template <typename _T>
    vec<_T, 2>
    odd_elements(const vec<_T, 4>& v);

    // return the odd element 1 of v
    template <typename _T>
    vec<_T, 1>
    odd_elements(const vec<_T, 2>& v);

    // combine e and o into e0, o0, e1, o1, ...
    template <typename _T, std::size_t _N>
    vec<_T, _N*2>
    combine_even_odd(const vec<_T, _N>& e, const vec<_T, _N>& o);

    // combine e and o into e0, o0, e1, o1, ..
    template <typename _T>
    vec<_T, 16>
    combine_even_odd(const vec<_T, 8>& e, const vec<_T, 8>& o);

    // combine e and o into e0, o0, e1, o1, ..
    template <typename _T>
    vec<_T, 8>
    combine_even_odd(const vec<_T, 4>& e, const vec<_T, 4>& o);

    // combine e and o into e0, o0, e1, o1, ..
    template <typename _T>
    vec<_T, 4>
    combine_even_odd(const vec<_T, 2>& e, const vec<_T, 2>& o);

    // combine e and o into e0, o0
    template <typename _T>
    vec<_T, 2>
    combine_even_odd(const vec<_T, 1>& e, const vec<_T, 1>& o);

    // select even elements from e and odd elements from o
    // e0 o1 e2 o3 e4 o5 ..
    template <typename _T, std::size_t _N>
    vec<_T, _N>
    select_even_odd(const vec<_T, _N>& e, const vec<_T, _N>& o);

    // select even elements from e and odd elements from o
    // e0 o1 e2 o3 e4 o5 ..
    template <typename _T>
    vec<_T, 16>
    select_even_odd(const vec<_T, 16>& e, const vec<_T, 16>& o);

    // select even elements from e and odd elements from o
    // e0 o1 e2 o3 e4 o5 ..
    template <typename _T>
    vec<_T, 8>
    select_even_odd(const vec<_T, 8>& e, const vec<_T, 8>& o);

    // select even elements from e and odd elements from o
    // e0 o1 e2 o3
    template <typename _T>
    vec<_T, 4>
    select_even_odd(const vec<_T, 4>& e, const vec<_T, 4>& o);

    // select even elements from e and odd elements from o
    // e0 o1
    template <typename _T>
    vec<_T, 2>
    select_even_odd(const vec<_T, 2>& e, const vec<_T, 2>& o);

    // copy odd elements to even elements: v1 v1 v3 v3 v5 v5 ...
    template <typename _T, std::size_t _N>
    vec<_T, _N>
    copy_odd_to_even(const vec<_T, _N>& v);

    // copy even elements to odd elements: v0 v0 v2 v2 v4 v4 ...
    template <typename _T, std::size_t _N>
    vec<_T, _N>
    copy_even_to_odd(const vec<_T, _N>& v);

    template <typename _T>
    vec<_T, 16>
    copy_odd_to_even(const vec<_T, 16>& v);

    template <typename _T>
    vec<_T, 16>
    copy_even_to_odd(const vec<_T, 16>& v);

    template <typename _T>
    vec<_T, 8>
    copy_odd_to_even(const vec<_T, 8>& v);

    template <typename _T>
    vec<_T, 8>
    copy_even_to_odd(const vec<_T, 8>& v);

    template <typename _T>
    vec<_T, 4>
    copy_odd_to_even(const vec<_T, 4>& v);

    template <typename _T>
    vec<_T, 4>
    copy_even_to_odd(const vec<_T, 4>& v);

    template <typename _T>
    vec<_T, 2>
    copy_odd_to_even(const vec<_T, 2>& v);

    template <typename _T>
    vec<_T, 2>
    copy_even_to_odd(const vec<_T, 2>& v);

    // checks if all elements in v are equal
    template <typename _T, std::size_t _N>
    bool
    elements_equal(const vec<_T, _N>& v);

    // checks if all elements in v are equal
    template <typename _T>
    bool
    elements_equal(const vec<_T, 2>& v);

    // checks if all elements in v are equal
    template <typename _T>
    bool
    elements_equal(const vec<_T, 1>& v);

    template <typename _T, typename _I, std::size_t _VEC_LEN>
    class variable_lookup_table {
    private:
        variable_lookup_table<_T, _I, _VEC_LEN/2> _lh;
        variable_lookup_table<_T, _I, _VEC_LEN/2> _hh;
    public:
        variable_lookup_table(const vec<_I, _VEC_LEN>& idx)
            : _lh(low_half(idx)), _hh(high_half(idx)) {}
        vec<_T, _VEC_LEN>
        from(const _T* tbl) const {
            vec<_T, _VEC_LEN/2> lh=_lh.from(tbl);
            vec<_T, _VEC_LEN/2> hh=_hh.from(tbl);
            return vec<_T, _VEC_LEN>(lh, hh);
        }
    };

    template <typename _T, typename _I, std::size_t _VEC_LEN>
    variable_lookup_table<_T, _I, _VEC_LEN>
    make_variable_lookup_table(const vec<_I, _VEC_LEN>& idx) {
        return variable_lookup_table<_T, _I, _VEC_LEN>(idx);
    }

    namespace impl {
        // implementation class for fixed lookup tables without
        // a safe interface
        template <std::size_t _TABLE_LEN, typename _T,
                  typename _I, std::size_t _VEC_LEN>
        class fixed_lookup_table {
        private:
            fixed_lookup_table<_TABLE_LEN, _T, _I, _VEC_LEN/2> _lh;
            fixed_lookup_table<_TABLE_LEN, _T, _I, _VEC_LEN/2> _hh;
        public:
            // constructor, prepares table lookups into _T[_TABLE_LEN]
            fixed_lookup_table(const vec<_I, _VEC_LEN>& idx)
                : _lh(low_half(idx)), _hh(high_half(idx)) {}
            // perform the lookup using the prepared data
            vec<_T, _VEC_LEN>
            fromp(const _T* tbl) const {
                vec<_T, _VEC_LEN/2> lh=_lh.fromp(tbl);
                vec<_T, _VEC_LEN/2> hh=_hh.fromp(tbl);
                return vec<_T, _VEC_LEN>(lh, hh);
            }
        };
    }

    // lookup table with a fixed length, delegates work to
    // impl::fixed_lookup_table
    template <std::size_t _TABLE_LEN, typename _T,
              typename _I, std::size_t _VEC_LEN>
    class fixed_lookup_table
        : public impl::fixed_lookup_table<_TABLE_LEN, _T, _I, _VEC_LEN> {
    private:
        using base_type=
            impl::fixed_lookup_table<_TABLE_LEN, _T, _I, _VEC_LEN>;
    public:
        // constructor, prepares table lookups into _T[_TABLE_LEN]
        fixed_lookup_table(const vec<_I, _VEC_LEN>& idx)
            : base_type(idx) {}
        // perform the lookup using the prepared data
        vec<_T, _VEC_LEN>
        from(const _T (&tbl)[_TABLE_LEN]) const {
            return base_type::fromp(tbl);
        }
    };

    template <std::size_t _TABLE_LEN, typename _T,
              typename _I, std::size_t _VEC_LEN>
    fixed_lookup_table<_TABLE_LEN, _T, _I, _VEC_LEN>
    make_fixed_lookup_table(const vec<_I, _VEC_LEN>& idx) {
        return fixed_lookup_table<_TABLE_LEN, _T, _I, _VEC_LEN>(idx);
    }

    // absolute value for signed integers
    template <typename _T, std::size_t _N>
    std::enable_if_t< std::is_signed<_T>::value &&
                      !std::is_floating_point<_T>::value,
                      vec<_T, _N> >
    abs(const vec<_T, _N>& v);

    // return elementwise minimum
    template <typename _T, std::size_t _N>
    vec<_T, _N>
    min(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // return elementwise maximum
    template <typename _T, std::size_t _N>
    vec<_T, _N>
    max(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // floating point minimum with nan and signed 0.0 handling
    template <typename _T, std::size_t _N>
    std::enable_if_t<std::is_floating_point<_T>::value,
                     vec<_T, _N> >
    fmin(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // floating point maximum with nan and signed 0.0 handling
    template <typename _T, std::size_t _N>
    std::enable_if_t<std::is_floating_point<_T>::value,
                     vec<_T, _N> >
    fmax(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // fdim: max(x-y, 0)
    template <typename _T, std::size_t _N>
    std::enable_if_t<std::is_floating_point<_T>::value,
                     vec<_T, _N> >
    fdim(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // modf
    template <typename _T, std::size_t _N>
    std::enable_if_t<std::is_floating_point<_T>::value,
                     vec<_T, _N> >
    modf(const vec<_T, _N>& x, vec<_T, _N>* iptr);

    // return the maximum element
    template <typename _T, std::size_t _N>
    _T
    max_element(const vec<_T, _N>& v);

    // return the minimum element
    template <typename _T, std::size_t _N>
    _T
    min_element(const vec<_T, _N>& v);

    // load and store vectors from and to memory
    template <class _T, std::size_t _N>
    struct mem< vec<_T, _N> > {
        static
        vec<_T, _N> load(const _T* p, std::size_t n=_N) {
            return vec<_T,_N>(init_list<_T>(p, p+n));
        }
        static
        void store(_T* p, const vec<_T, _N>& v) {
            mem< vec<_T, _N/2> >::store(p, low_half(v));
            mem< vec<_T, _N/2> >::store(p+_N/2, high_half(v));
        }
    };

    template <typename _T, std::size_t _N>
    std::ostream& operator<<(std::ostream& s, const vec<_T, _N>& v);
}

namespace std {

    template <typename _T, std::size_t _N>
    struct is_signed< cftal::vec<_T, _N> > : public
        is_signed<typename cftal::vec<_T, _N>::value_type> {
    };

    template <typename _T, std::size_t _N>
    struct is_unsigned<cftal::vec<_T, _N> > : public
        is_unsigned<typename cftal::vec<_T, _N>::value_type> {
    };

    template <typename _T, std::size_t _N>
    struct make_unsigned< cftal::vec<_T, _N> > {
        using type = cftal::vec<typename std::make_unsigned<
                                    typename cftal::vec<_T, _N>::value_type
                               >::type, _N>;
    };

    template <typename _T, std::size_t _N>
    struct make_signed< cftal::vec<_T, _N> > {
        using type = cftal::vec<typename std::make_signed<
                                    typename cftal::vec<_T, _N>::value_type
                               >::type, _N>;
    };

}

#if 0
template <class _T, std::size_t _N>
template <class _U>
inline
cftal::vec<_T, _N>::vec(const vec<_U, _N>& r)
    : _l(low_half(r)), _h(high_half(r))
{

}
#endif

template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>::vec(const _T& v)
    : _v(half_type(v), half_type(v))
{
}

template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>::vec(std::initializer_list<_T> l)
    : vec(init_list<_T>(l.begin(), l.end()))
{
}

template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>::vec(init_list<_T> l)
    :_v(half_type(low_half<_T, _N>(l)),
        half_type(high_half<_T, _N>(l)))
{
}

template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>::vec(const half_type& l,
                        const half_type& h)
    : _v(l, h)
{
}

template <typename _T, std::size_t _N>
template <template <class _U, std::size_t _M>
          class _OP,
          class _L, class _R>
inline
cftal::vec<_T, _N>::vec(const expr<_OP<_T, _N>, _L, _R>& r)
    : vec(eval(r))
{
}

template <class _T, std::size_t _N>
inline
const typename cftal::vec<_T, _N>::pair_type&
cftal::vec<_T, _N>::operator()() const
{
    return _v;
}

template <class _T, std::size_t _N>
inline
const typename cftal::vec<_T, _N>::half_type&
cftal::vec<_T, _N>::lh() const
{
    return _v.first;
}

template <class _T, std::size_t _N>
inline
const typename cftal::vec<_T, _N>::half_type&
cftal::vec<_T, _N>::hh() const
{
    return _v.second;
}

template <class _T, std::size_t _N>
inline
const typename cftal::vec<_T, _N>::half_type&
cftal::low_half(const vec<_T, _N>& v)
{
    return v.lh();
}

template <class _T, std::size_t _N>
inline
const typename cftal::vec<_T, _N>::half_type&
cftal::high_half(const vec<_T, _N>& v)
{
    return v.hh();
}

template <std::size_t _I, class _T, std::size_t _N>
inline
_T
cftal::extract(const vec<_T, _N>& v)
{
    // static_assert(_I < _N, "invalid offset in extract(vec<_T, _N>)");
    _T r;
    if (_I < _N/2) {
        r = extract<_I>(low_half(v));
    } else {
        r = extract< _I ? (_I-_N/2) : 0 >(high_half(v));
    }
    return r;
}

template <class _T, std::size_t _N>
inline
bool
cftal::all_of(const vec<_T, _N>& v)
{
    return all_of(low_half(v)) & all_of(high_half(v));
}

template <class _T, std::size_t _N>
inline
bool
cftal::any_of(const vec<_T, _N>& v)
{
    return any_of(low_half(v)) | any_of(high_half(v));
}

template <class _T, std::size_t _N>
inline
bool
cftal::none_of(const vec<_T, _N>& v)
{
    return none_of(low_half(v)) & none_of(high_half(v));
}

template <class _T, std::size_t _N>
inline
std::enable_if_t<std::is_integral<_T>::value,
                 std::pair<cftal::vec<_T, _N>, cftal::vec<_T, _N> > >
cftal::mul_lo_hi(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    auto l= mul_lo_hi(low_half(a), low_half(b));
    auto h= mul_lo_hi(high_half(a), high_half(b));
    vec<_T, _N> ll(l.first, h.first);
    vec<_T, _N> hh(l.second, h.second);
    return std::make_pair(ll, hh);
}


template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>
cftal::select(const typename vec<_T, _N>::mask_type& m,
              const vec<_T, _N>& on_true,
              const vec<_T, _N>& on_false)
{
    vec<_T, _N> res(
        select(low_half(m), low_half(on_true), low_half(on_false)),
        select(high_half(m), high_half(on_true), high_half(on_false)));
    return res;
}

template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>
cftal::select_val_or_zero(const typename vec<_T, _N>::mask_type& m,
                          const vec<_T, _N>& on_true)
{
    vec<_T, _N> res(
        select_val_or_zero(low_half(m), low_half(on_true)),
        select_val_or_zero(high_half(m), high_half(on_true)));
    return res;
}

template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>
cftal::select_zero_or_val(const typename vec<_T, _N>::mask_type& m,
                          const vec<_T, _N>& on_false)
{
    vec<_T, _N> res(
        select_zero_or_val(low_half(m), low_half(on_false)),
        select_zero_or_val(high_half(m), high_half(on_false)));
    return res;
}


template <bool _I0, bool _I1, class _T>
inline
cftal::vec<_T, 2>
cftal::select(const vec<_T, 2>& a, const vec<_T, 2>& b)
{
    return vec<_T, 2>(_I0 ? low_half(a) : low_half(b),
                      _I1 ? high_half(a) : high_half(b));
}

template <bool _I0, bool _I1, bool _I2, bool _I3, class _T>
inline
cftal::vec<_T, 4>
cftal::select(const vec<_T, 4>& a, const vec<_T, 4>& b)
{
    return vec<_T, 4>(select<_I0, _I1>(low_half(a), low_half(b)),
                      select<_I2, _I3>(high_half(a), high_half(b)));
}

template <bool _I0, bool _I1, bool _I2, bool _I3,
          bool _I4, bool _I5, bool _I6, bool _I7, class _T>
inline
cftal::vec<_T, 8>
cftal::select(const vec<_T, 8>& a, const vec<_T, 8>& b)
{
    return vec<_T, 8>(select<_I0, _I1, _I2, _I3>(low_half(a), low_half(b)),
                      select<_I4, _I5, _I6, _I7>(high_half(a), high_half(b)));
}

template <bool _I0, bool _I1, bool _I2, bool _I3,
          bool _I4, bool _I5, bool _I6, bool _I7,
          bool _I8, bool _I9, bool _IA, bool _IB,
          bool _IC, bool _ID, bool _IE, bool _IF, class _T>
inline
cftal::vec<_T, 16>
cftal::select(const vec<_T, 16>& a, const vec<_T, 16>& b)
{
    return vec<_T, 16>(
        select<_I0, _I1, _I2, _I3, _I4, _I5, _I6, _I7>(low_half(a),
                                                       low_half(b)),
        select<_I8, _I9, _IA, _IB, _IC, _ID, _IE, _IF>(high_half(a),
                                                       high_half(b)));
}

template <class _T, std::size_t _N>
inline
bool
cftal::elements_equal(const vec<_T, _N>& v)
{
    bool lh= elements_equal(low_half(v));
    bool hh= elements_equal(high_half(v));
    bool r = lh && hh;
    return r;
}

template <class _T>
inline
bool
cftal::elements_equal(const vec<_T, 2>& v)
{
    return extract<0>(v) == extract<1>(v);
}

template <class _T>
inline
bool
cftal::elements_equal(const vec<_T, 1>& v)
{
    return true;
}

template <typename _T, std::size_t _N>
inline
std::enable_if_t<std::is_signed<_T>::value &&
                 !std::is_floating_point<_T>::value,
                 cftal::vec<_T, _N> >
cftal::abs(const vec<_T, _N>& v)
{
    return vec<_T, _N>(abs(low_half(v)), abs(high_half(v)));
}

template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>
cftal::min(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return vec<_T, _N>(min(low_half(a), low_half(b)),
                       min(high_half(a), high_half(b)));
}

template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>
cftal::max(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return vec<_T, _N>(max(low_half(a), low_half(b)),
                       max(high_half(a), high_half(b)));
}

template <typename _T, std::size_t _N>
inline
std::enable_if_t<std::is_floating_point<_T>::value,
                 cftal::vec<_T, _N> >
cftal::fmin(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    using v_t = vec<_T, _N>;
    v_t r=min(a, b);
    // select the "smaller" of signed zeros
    typename v_t::mask_type abz= (a==b) & (a==_T(0));
    if (any_of(abz)) {
        v_t a1=copysign(v_t(_T(1)), a);
        v_t b1=copysign(v_t(_T(1)), b);
        v_t r1=min(a1, b1);
        r = select(abz, copysign(v_t(_T(0)), r1), r);
    }
    r = select(isnan(a), b, r);
    r = select(isnan(b), a, r);
    return r;
}

template <typename _T, std::size_t _N>
inline
std::enable_if_t<std::is_floating_point<_T>::value,
                 cftal::vec<_T, _N> >
cftal::fmax(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    using v_t = vec<_T, _N>;
    v_t r=max(a, b);
    // select the "larger" of signed zeros
    typename v_t::mask_type abz= (a==b) & (a==_T(0));
    if (any_of(abz)) {
        v_t a1=copysign(v_t(_T(1)), a);
        v_t b1=copysign(v_t(_T(1)), b);
        v_t r1=max(a1, b1);
        r = select(abz, copysign(v_t(_T(0)), r1), r);
    }
    r = select(isnan(a), b, r);
    r = select(isnan(b), a, r);
    return r;
}

template <typename _T, std::size_t _N>
inline
std::enable_if_t<std::is_floating_point<_T>::value,
                 cftal::vec<_T, _N> >
cftal::fdim(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    using v_t = vec<_T, _N>;
    v_t r= max(a - b, v_t(0));
    r = select(isnan(a), a, r);
    r = select(isnan(b), b, r);
    return r;
}

template <typename _T, std::size_t _N>
inline
std::enable_if_t<std::is_floating_point<_T>::value,
                 cftal::vec<_T, _N> >
cftal::modf(const vec<_T, _N>& x, vec<_T, _N>* iptr)
{
    using v_t = vec<_T, _N>;
    v_t i= trunc(x);
    v_t r= x - i;
    using mv_t = typename v_t::mask_type;
    mv_t x_inf = isinf(x);
    // return +-0 on x== +-inf
    v_t r_inf= copysign(v_t(0.0), x);
    r = select(x_inf, r_inf , r);
    if (iptr != nullptr) {
        // iptr +-inf on x== +-inf
        i = select(x_inf, x, i);
        *iptr = i;
    }
    return r;
}

template <class _T, std::size_t _N>
inline
_T
cftal::max_element(const vec<_T, _N>& v)
{
    return max_element(max(low_half(v), high_half(v)));
}

template <class _T, std::size_t _N>
inline
_T
cftal::min_element(const vec<_T, _N>& v)
{
    return min_element(min(low_half(v), high_half(v)));
}

template <int32_t _I0, int32_t _I1, typename _T>
inline
cftal::vec<_T, 2>
cftal::permute(const vec<_T, 2>& v)
{
    const vec<_T, 1> lv= low_half(v);
    const vec<_T, 1> hv= high_half(v);
    // low half of the result vector
    // vec<_T, 1> lr = permute<_I0>(lv, hv);
    vec<_T, 1> lr = (_I0 < 0 ? vec<_T, 1>(_T(0)) :
                     (_I0 == 0 ? lv : hv));
    // high half of the result vector
    // vec<_T, 1> hr = permute<_I1>(lv, hv);
    vec<_T, 1> hr = (_I1 < 0 ? vec<_T, 1>(_T(0)) :
                     (_I1 == 0 ? lv : hv));
    return vec<_T, 2>(lr, hr);
}

template <int32_t _I0, int32_t _I1, typename _T>
inline
cftal::vec<_T, 2>
cftal::permute(const vec<_T, 2>& v0, const vec<_T, 2>& v1)
{
    // select elements from v0
    const int32_t i0= _I0 < 2 ? _I0 : -1;
    const int32_t i1= _I1 < 2 ? _I1 : -1;
    vec<_T, 2> ri = permute<i0, i1>(v0);
    // select elements from v1
    const int32_t j0= _I0 >= 2 ? _I0-2 : -1;
    const int32_t j1= _I1 >= 2 ? _I1-2 : -1;
    vec<_T, 2> rj = permute<j0, j1>(v1);
    // combine result sets:
    vec<_T, 2> r( ri | rj);
    return r;
}

template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
          typename _T>
inline
cftal::vec<_T, 4>
cftal::permute(const vec<_T, 4>& v)
{
    const vec<_T, 2> lv= low_half(v);
    const vec<_T, 2> hv= high_half(v);
    // low half of the result vector
    vec<_T, 2> lr = permute<_I0, _I1>(lv, hv);
    // high half of the result vector
    vec<_T, 2> hr = permute<_I2, _I3>(lv, hv);
    return vec<_T, 4>(lr, hr);
}

template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
          typename _T>
inline
cftal::vec<_T, 4>
cftal::permute(const vec<_T, 4>& v0, const vec<_T, 4>& v1)
{
    // select elements from v0
    const int32_t i0= _I0 < 4 ? _I0 : -1;
    const int32_t i1= _I1 < 4 ? _I1 : -1;
    const int32_t i2= _I2 < 4 ? _I2 : -1;
    const int32_t i3= _I3 < 4 ? _I3 : -1;
    vec<_T, 4> ri = permute<i0, i1, i2, i3>(v0);
    // select elements from v1
    const int32_t j0= _I0 >= 4 ? _I0-4 : -1;
    const int32_t j1= _I1 >= 4 ? _I1-4 : -1;
    const int32_t j2= _I2 >= 4 ? _I2-4 : -1;
    const int32_t j3= _I3 >= 4 ? _I3-4 : -1;
    vec<_T, 4> rj = permute<j0, j1, j2, j3>(v1);
    // combine result sets:
    vec<_T, 4> r( ri | rj);
    return r;
}

template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
          int32_t _I4, int32_t _I5, int32_t _I6, int32_t _I7,
          typename _T>
inline
cftal::vec<_T, 8>
cftal::permute(const vec<_T, 8>& v)
{
    const vec<_T, 4> lv= low_half(v);
    const vec<_T, 4> hv= high_half(v);
    // low half of the result vector
    vec<_T, 4> lr = permute<_I0, _I1, _I2, _I3>(lv, hv);
    // high half of the result vector
    vec<_T, 4> hr = permute<_I4, _I5, _I6, _I7>(lv, hv);
    return vec<_T, 8>(lr, hr);
}

template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
          int32_t _I4, int32_t _I5, int32_t _I6, int32_t _I7,
          typename _T>
inline
cftal::vec<_T, 8>
cftal::permute(const vec<_T, 8>& v0, const vec<_T, 8>& v1)
{
    // select elements from v0
    const int32_t i0= _I0 < 8 ? _I0 : -1;
    const int32_t i1= _I1 < 8 ? _I1 : -1;
    const int32_t i2= _I2 < 8 ? _I2 : -1;
    const int32_t i3= _I3 < 8 ? _I3 : -1;
    const int32_t i4= _I4 < 8 ? _I4 : -1;
    const int32_t i5= _I5 < 8 ? _I5 : -1;
    const int32_t i6= _I6 < 8 ? _I6 : -1;
    const int32_t i7= _I7 < 8 ? _I7 : -1;
    vec<_T, 8> ri = permute<i0, i1, i2, i3, i4, i5, i6, i7>(v0);
    // select elements from v1
    const int32_t j0= _I0 >= 8 ? _I0-8 : -1;
    const int32_t j1= _I1 >= 8 ? _I1-8 : -1;
    const int32_t j2= _I2 >= 8 ? _I2-8 : -1;
    const int32_t j3= _I3 >= 8 ? _I3-8 : -1;
    const int32_t j4= _I4 >= 8 ? _I4-8 : -1;
    const int32_t j5= _I5 >= 8 ? _I5-8 : -1;
    const int32_t j6= _I6 >= 8 ? _I6-8 : -1;
    const int32_t j7= _I7 >= 8 ? _I7-8 : -1;
    vec<_T, 8> rj = permute<j0, j1, j2, j3, j4, j5, j6, j7>(v1);
    // combine result sets:
    vec<_T, 8> r( ri | rj);
    return r;
}

template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
          int32_t _I4, int32_t _I5, int32_t _I6, int32_t _I7,
          int32_t _I8, int32_t _I9, int32_t _IA, int32_t _IB,
          int32_t _IC, int32_t _ID, int32_t _IE, int32_t _IF,
          typename _T>
inline
cftal::vec<_T, 16>
cftal::permute(const vec<_T, 16>& v)
{
    const vec<_T, 8> lv= low_half(v);
    const vec<_T, 8> hv= high_half(v);
    // low half of the result vector
    vec<_T, 8> lr = permute<_I0, _I1, _I2, _I3, _I4, _I5, _I6, _I7>(lv, hv);
    // high half of the result vector
    vec<_T, 8> hr = permute<_I8, _I9, _IA, _IB, _IC, _ID, _IE, _IF>(lv, hv);
    return vec<_T, 16>(lr, hr);
}

template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
          int32_t _I4, int32_t _I5, int32_t _I6, int32_t _I7,
          int32_t _I8, int32_t _I9, int32_t _IA, int32_t _IB,
          int32_t _IC, int32_t _ID, int32_t _IE, int32_t _IF,
          typename _T>
inline
cftal::vec<_T, 16>
cftal::permute(const vec<_T, 16>& v0, const vec<_T, 16>& v1)
{
    // select elements from v0
    const int32_t k0= _I0 < 16 ? _I0 : -1;
    const int32_t k1= _I1 < 16 ? _I1 : -1;
    const int32_t k2= _I2 < 16 ? _I2 : -1;
    const int32_t k3= _I3 < 16 ? _I3 : -1;
    const int32_t k4= _I4 < 16 ? _I4 : -1;
    const int32_t k5= _I5 < 16 ? _I5 : -1;
    const int32_t k6= _I6 < 16 ? _I6 : -1;
    const int32_t k7= _I7 < 16 ? _I7 : -1;

    const int32_t k8= _I8 < 16 ? _I8 : -1;
    const int32_t k9= _I9 < 16 ? _I9 : -1;
    const int32_t ka= _IA < 16 ? _IA : -1;
    const int32_t kb= _IB < 16 ? _IB : -1;
    const int32_t kc= _IC < 16 ? _IC : -1;
    const int32_t kd= _ID < 16 ? _ID : -1;
    const int32_t ke= _IE < 16 ? _IE : -1;
    const int32_t kf= _IF < 16 ? _IF : -1;

    vec<_T, 16> ri = permute<k0, k1, k2, k3, k4, k5, k6, k7,
                             k8, k9, ka, kb, kc, kd, ke, kf>(v0);
    // select elements from v1
    const int32_t j0= _I0 >= 16 ? _I0-16 : -1;
    const int32_t j1= _I1 >= 16 ? _I1-16 : -1;
    const int32_t j2= _I2 >= 16 ? _I2-16 : -1;
    const int32_t j3= _I3 >= 16 ? _I3-16 : -1;
    const int32_t j4= _I4 >= 16 ? _I4-16 : -1;
    const int32_t j5= _I5 >= 16 ? _I5-16 : -1;
    const int32_t j6= _I6 >= 16 ? _I6-16 : -1;
    const int32_t j7= _I7 >= 16 ? _I7-16 : -1;

    const int32_t j8= _I8 >= 16 ? _I8 : -1;
    const int32_t j9= _I9 >= 16 ? _I9 : -1;
    const int32_t ja= _IA >= 16 ? _IA : -1;
    const int32_t jb= _IB >= 16 ? _IB : -1;
    const int32_t jc= _IC >= 16 ? _IC : -1;
    const int32_t jd= _ID >= 16 ? _ID : -1;
    const int32_t je= _IE >= 16 ? _IE : -1;
    const int32_t jf= _IF >= 16 ? _IF : -1;

    vec<_T, 16> rj = permute<j0, j1, j2, j3, j4, j5, j6, j7,
                             j8, j9, ja, jb, jc, jd, je, jf>(v1);
    // combine result sets:
    vec<_T, 16> r( ri | rj);
    return r;
}

template <typename _T>
cftal::vec<_T, 4>
cftal::sort_even_odd(const vec<_T, 4>& v)
{
    return permute<0, 2, 1, 3>(v);
}

template <typename _T>
cftal::vec<_T, 8>
cftal::sort_even_odd(const vec<_T, 8>& v)
{
    return permute<0, 2, 4, 6, 1, 3, 5, 7>(v);
}

template <typename _T>
cftal::vec<_T, 16>
cftal::sort_even_odd(const vec<_T, 16>& v)
{
    return permute<0, 2, 4, 6, 8, 10, 12, 14,
                   1, 3, 5, 7, 9, 11, 13, 15>(v);
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N/2>
cftal::even_elements(const vec<_T, _N>& v)
{
    return vec<_T, _N/2>(even_elements(low_half(v)),
                         even_elements(high_half(v)));
}

template <typename _T>
cftal::vec<_T, 8>
cftal::even_elements(const vec<_T, 16>& v)
{
    return low_half(sort_even_odd(v));
}

template <typename _T>
cftal::vec<_T, 4>
cftal::even_elements(const vec<_T, 8>& v)
{
    return low_half(sort_even_odd(v));
}

template <typename _T>
cftal::vec<_T, 2>
cftal::even_elements(const vec<_T, 4>& v)
{
    return low_half(sort_even_odd(v));
}

template <typename _T>
cftal::vec<_T, 1>
cftal::even_elements(const vec<_T, 2>& v)
{
    return low_half(v);
}


template <typename _T, std::size_t _N>
cftal::vec<_T, _N/2>
cftal::odd_elements(const vec<_T, _N>& v)
{
    return vec<_T, _N/2>(odd_elements(low_half(v)),
                         odd_elements(high_half(v)));
}

template <typename _T>
cftal::vec<_T, 8>
cftal::odd_elements(const vec<_T, 16>& v)
{
    return high_half(sort_even_odd(v));
}

template <typename _T>
cftal::vec<_T, 4>
cftal::odd_elements(const vec<_T, 8>& v)
{
    return high_half(sort_even_odd(v));
}

template <typename _T>
cftal::vec<_T, 2>
cftal::odd_elements(const vec<_T, 4>& v)
{
    return high_half(sort_even_odd(v));
}

template <typename _T>
cftal::vec<_T, 1>
cftal::odd_elements(const vec<_T, 2>& v)
{
    return high_half(v);
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N*2>
cftal::combine_even_odd(const vec<_T, _N>& e, const vec<_T, _N>& o)
{
    return vec<_T, _N*2>(combine_even_odd(low_half(e), low_half(o)),
                         combine_even_odd(high_half(e), high_half(o)));
}

template <typename _T>
cftal::vec<_T, 16>
cftal::combine_even_odd(const vec<_T, 8>& e, const vec<_T, 8>& o)
{
    vec<_T, 8> lh= permute<0,  8, 1,  9, 2, 10, 3, 11>(e, o);
    vec<_T, 8> hh= permute<4, 12, 5, 13, 6, 14, 7, 15>(e, o);
    return vec<_T, 16>(lh, hh);
}

template <typename _T>
cftal::vec<_T, 8>
cftal::combine_even_odd(const vec<_T, 4>& e, const vec<_T, 4>& o)
{
    vec<_T, 4> lh= permute<0, 4, 1, 5>(e, o);
    vec<_T, 4> hh= permute<2, 6, 3, 7>(e, o);
    return vec<_T, 8>(lh, hh);
}

template <typename _T>
cftal::vec<_T, 4>
cftal::combine_even_odd(const vec<_T, 2>& e, const vec<_T, 2>& o)
{
    vec<_T, 2> lh= permute<0, 2>(e, o);
    vec<_T, 2> hh= permute<1, 3>(e, o);
    return vec<_T, 4>(lh, hh);
}

template <typename _T>
cftal::vec<_T, 2>
cftal::combine_even_odd(const vec<_T, 1>& e, const vec<_T, 1>& o)
{
    return vec<_T, 2>(e, o);
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>
cftal::select_even_odd(const vec<_T, _N>& e, const vec<_T, _N>& o)
{
    vec<_T, _N/2> lh=select_even_odd(low_half(e), low_half(o));
    vec<_T, _N/2> hh=select_even_odd(high_half(e), high_half(o));
    return vec<_T, _N>(lh, hh);
}

template <typename _T>
cftal::vec<_T, 16>
cftal::select_even_odd(const vec<_T, 16>& e, const vec<_T, 16>& o)
{
    return select<true, false, true, false,
                  true, false, true, false,
                  true, false, true, false,
                  true, false, true, false>(e, o);
}

template <typename _T>
cftal::vec<_T, 8>
cftal::select_even_odd(const vec<_T, 8>& e, const vec<_T, 8>& o)
{
    return select<true, false, true, false,
                  true, false, true, false>(e, o);
}

template <typename _T>
cftal::vec<_T, 4>
cftal::select_even_odd(const vec<_T, 4>& e, const vec<_T, 4>& o)
{
    return select<true, false, true, false>(e, o);
}

template <typename _T>
cftal::vec<_T, 2>
cftal::select_even_odd(const vec<_T, 2>& e, const vec<_T, 2>& o)
{
    return select<true, false>(e, o);
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>
cftal::copy_even_to_odd(const vec<_T, _N>& v)
{
    vec<_T, _N/2> l=copy_even_to_odd(low_half(v));
    vec<_T, _N/2> h=copy_even_to_odd(high_half(v));
    return vec<_T, _N>(l, h);
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>
cftal::copy_odd_to_even(const vec<_T, _N>& v)
{
    vec<_T, _N/2> l=copy_odd_to_even(low_half(v));
    vec<_T, _N/2> h=copy_odd_to_even(high_half(v));
    return vec<_T, _N>(l, h);
}

template <typename _T>
cftal::vec<_T, 16>
cftal::copy_even_to_odd(const vec<_T, 16>& v)
{
    return permute< 0,  0,  2,  2,  4,  4,  6,  6,
                    8,  8, 10, 10, 12, 12, 14, 14>(v);
}

template <typename _T>
cftal::vec<_T, 16>
cftal::copy_odd_to_even(const vec<_T, 16>& v)
{
    return permute< 1,  1,  3,  3,  5,  5,  7,  7,
                    9,  9, 11, 11, 13, 13, 15, 15>(v);
}

template <typename _T>
cftal::vec<_T, 8>
cftal::copy_even_to_odd(const vec<_T, 8>& v)
{
    return permute< 0,  0,  2,  2,  4,  4,  6,  6>(v);
}

template <typename _T>
cftal::vec<_T, 8>
cftal::copy_odd_to_even(const vec<_T, 8>& v)
{
    return permute< 1,  1,  3,  3,  5,  5,  7,  7>(v);
}

template <typename _T>
cftal::vec<_T, 4>
cftal::copy_even_to_odd(const vec<_T, 4>& v)
{
    return permute< 0,  0,  2,  2>(v);
}

template <typename _T>
cftal::vec<_T, 4>
cftal::copy_odd_to_even(const vec<_T, 4>& v)
{
    return permute< 1,  1,  3,  3>(v);
}

template <typename _T>
cftal::vec<_T, 2>
cftal::copy_even_to_odd(const vec<_T, 2>& v)
{
    return permute< 0,  0>(v);
}

template <typename _T>
cftal::vec<_T, 2>
cftal::copy_odd_to_even(const vec<_T, 2>& v)
{
    return permute< 1,  1>(v);
}

template <typename _T, std::size_t _N>
std::ostream&
cftal::operator<<(std::ostream& s, const vec<_T, _N>& v)
{
    const vec<_T, _N/2> lh = low_half(v);
    const vec<_T, _N/2> hh = high_half(v);
    s << lh << ' ' << hh ;
    return s;
}

// Local variables:
// mode: c++
// end:
#endif
