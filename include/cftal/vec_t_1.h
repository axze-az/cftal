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
#if !defined (__CFTAL_VEC_T_1_H__)
#define __CFTAL_VEC_T_1_H__ 1

#include <cftal/config.h>
#include <cftal/vec_op.h>
#include <cftal/vec_lookup.h>
#include <cftal/vec_bit_n.h>
#include <cftal/mul_div.h>
#include <cftal/impl/divide.h>
#include <cftal/type_traits.h>
#include <cmath>

#define USE_TYPE_AS_MASK 1
#define USE_BOOL_AS_MASK 0

namespace cftal {

    // vec<_T, 1> specialization
    template <typename _T>
    class vec<_T, 1> {
    public:
        using value_type = _T;
#if USE_TYPE_AS_MASK>0
        using mask_value_type = _T;
#elif USE_BOOL_AS_MASK>0
        using mask_value_type = bool;
#else
        using mask_value_type = bit;
#endif
        using mask_type = vec<mask_value_type, 1>;

        vec() = default;
        vec(const vec& r) = default;
        vec(vec&& r) = default;
        vec& operator=(const vec& r) = default;
        vec& operator=(vec&& r) = default;
        vec(const _T& v);
        vec(const _T& v, bool splat);
        vec(std::initializer_list<_T> l);
        vec(init_list<_T> l);
        _T operator()() const;

        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<_T, 1>, _L, _R>& r);

    private:
        _T _v;
    };

    // call by value for vectors of length 1
    template <typename _T>
    struct arg<vec<_T, 1> > {
        using type = vec<_T, 1>;
    };

    template <typename _T>
    struct is_vec_specialized<vec<_T, 1> > : public std::true_type {};

    template <class _T>
    struct mem< vec<_T, 1> > {
        static
        vec<_T, 1> load(const _T* p, std::size_t n=1) {
            return vec<_T, 1>(*p);
        }
        static
        void store(_T* p, const vec<_T, 1>& v) {
            *p = v();
        }
    };

    namespace impl {

        template <typename _T, typename _C>
        struct xxx_of {
            static const unsigned shift= (sizeof(_T)*8-1);
            static const _T msk = _T(1) << shift;
            static
            bool
            any(const vec<_T, 1>& v) {
                return (v() & msk) != _T(0);
            }
            static
            bool
            all(const vec<_T, 1>& v) {
                return (v() & msk) != _T(0);
            }
            static
            bool
            none(const vec<_T, 1>& v) {
                return (v() & msk) == _T(0);
            }
        };

        template <typename _T>
        struct xxx_of<_T, std::true_type> {
            static
            bool
            any(const vec<_T, 1>& v) {
                return std::signbit(v()) != 0;
            }
            static
            bool
            all(const vec<_T, 1>& v) {
                return std::signbit(v()) != 0;
            }
            static
            bool
            none(const vec<_T, 1>& v) {
                return std::signbit(v()) == 0;
            }
        };

        template <typename _T>
        struct bool_to_mask {
            static
            _T
            v(bool t) {
                using utype = typename std::make_unsigned<_T>::type;
                return t ? ~utype(0) : utype(0);
            }
        };

        template <>
        struct bool_to_mask<bool> {
            static
            bool
            v(bool t) {
                return t;
            }
        };

        template <>
        struct bool_to_mask<bit> {
            static
            uint32_t
            v(bool t) {
                return t ? 1 : 0;
            }
        };


        template <>
        struct bool_to_mask<float> {
            static
            float
            v(bool t) {
                uint32_t r= t ? ~0u : 0;
                return as<float>(r);
            }
        };

        template <>
        struct bool_to_mask<double> {
            static
            double
            v(bool t) {
                uint64_t r= t ? ~0ull : 0ull;
                return as<double>(r);
            }
        };

        template <class _T>
        struct mask_to_bool {
            static
            bool
            v(const _T& t) {
                using stype = typename std::make_signed<_T>::type;
                return stype(t) == stype(-1);
            }
        };

        template <>
        struct mask_to_bool<bool> {
            static
            bool
            v(const bool& t) {
                return t;
            }
        };

        template <>
        struct mask_to_bool<bit> {
            static
            bool
            v(const bit& t) {
                return t() == 0 ? false : true;
            }
        };

        template <>
        struct mask_to_bool<double> {
            static
            bool
            v(double t) {
                int64_t ti=as<int64_t>(t);
                return mask_to_bool<int64_t>::v(ti);
            }
        };

        template <>
        struct mask_to_bool<float> {
            static
            bool
            v(float t) {
                int32_t ti=as<int32_t>(t);
                return mask_to_bool<int32_t>::v(ti);
            }
        };


    }

    template <typename _T>
    bool any_of(const vec<_T, 1>& v);

    template <typename _T>
    bool all_of(const vec<_T, 1>& v);

    template <typename _T>
    bool none_of(const vec<_T, 1>& v);

    template <typename _T>
    std::enable_if_t<cftal::is_integral<_T>::value,
                     std::pair<vec<_T, 1>, vec<_T, 1> > >
    mul_lo_hi(const vec<_T, 1>& a, const vec<_T, 1>& b);

    template <typename _T>
    std::enable_if_t<cftal::is_integral<_T>::value,
                     vec<_T, 1> >
    abs(const vec<_T, 1>& a);

    template <typename _T>
    vec<_T, 1> max(const vec<_T, 1>& a, const vec<_T, 1>& b);
    template <typename _T>
    vec<_T, 1> min(const vec<_T, 1>& a, const vec<_T, 1>& b);

    template <typename _T>
    _T max_element(const vec<_T, 1>& v);

    template <typename _T>
    _T min_element(const vec<_T, 1>& v);

    template <std::size_t _I, typename _T>
    _T extract(const vec<_T, 1>& v);

    template <typename _T>
    _T extract(const vec<_T, 1>& v, size_t i);

    template <std::size_t _I, typename _T>
    void insert(vec<_T, 1>& v, const _T& vi);

    template <typename _T>
    void insert(vec<_T, 1>& v, const _T& vi, size_t i);

    template <typename _T>
    vec<_T, 1>
    select(const typename vec<_T, 1>::mask_type& m,
           const vec<_T, 1>& on_true,
           const vec<_T, 1>& on_false);

    template <typename _T>
    vec<_T, 1>
    select_val_or_zero(const typename vec<_T, 1>::mask_type& m,
                       const vec<_T, 1>& on_true);


    template <typename _T>
    vec<_T, 1>
    select_zero_or_val(const typename vec<_T, 1>::mask_type& m,
                       const vec<_T, 1>& on_false);

    template <int32_t _I0, typename _T>
    vec<_T, 1>
    permute(const vec<_T, 1>& v);

    template <int32_t _I0, typename _T>
    vec<_T, 1>
    permute(const vec<_T, 1>& v0, const vec<_T, 1>& v1);

    template <typename _T>
    std::ostream& operator<<(std::ostream& s, const vec<_T, 1>& v);

    template <typename _T, typename _I>
    class variable_vec_lookup_table<_T, _I, 1> {
    private:
        // vec<_I, 1> m_idx;
        _I _idx;
    public:
        variable_vec_lookup_table(const vec<_I, 1>& idx) : _idx(idx()) {}
        vec<_T, 1>
        from(const _T* tbl) const {
            vec<_T, 1> r=tbl[_idx];
            return r;
        }
    };

    namespace impl {
        template <std::size_t _TABLE_LEN, typename _T, typename _I>
        class fixed_vec_lookup_table<_TABLE_LEN, _T, _I, 1> {
        private:
            // vec<_I, 1> m_idx;
            _I _idx;
        public:
            fixed_vec_lookup_table(const vec<_I, 1> idx) : _idx(idx()) {}
            vec<_T, 1>
            fromp(const _T* tbl) const {
                vec<_T, 1> r=tbl[_idx];
                return r;
            };
        };
    }

    namespace op {
        template <typename _T>
        struct lt<_T, 1> {
            using full_type = vec<_T, 1>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                using mvt = typename full_type::mask_value_type;
                return mask_type(impl::bool_to_mask<mvt>::v(a() < b()));
            }
        };

        template <typename _T>
        struct le<_T, 1> {
            using full_type = vec<_T, 1>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                using mvt = typename full_type::mask_value_type;
                return mask_type(impl::bool_to_mask<mvt>::v(a() <= b()));
            }
        };

        template <typename _T>
        struct eq<_T, 1> {
            using full_type = vec<_T, 1>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                using mvt = typename full_type::mask_value_type;
                return mask_type(impl::bool_to_mask<mvt>::v(a() == b()));
            }
        };

        template <typename _T>
        struct ne<_T, 1> {
            using full_type = vec<_T, 1>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                using mvt = typename full_type::mask_value_type;
                return mask_type(impl::bool_to_mask<mvt>::v(a() != b()));
            }
        };

        template <typename _T>
        struct ge<_T, 1> {
            using full_type = vec<_T, 1>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                using mvt = typename full_type::mask_value_type;
                return mask_type(impl::bool_to_mask<mvt>::v(a() >= b()));
            }
        };

        template <typename _T>
        struct gt<_T, 1> {
            using full_type = vec<_T, 1>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                using mvt = typename full_type::mask_value_type;
                return mask_type(impl::bool_to_mask<mvt>::v(a() > b()));
            }
        };

        template <typename _T>
        struct plus<_T, 1> {
            using full_type = vec<_T, 1>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <typename _T>
        struct neg<_T, 1> {
            using full_type = vec<_T, 1>;
            static
            full_type
            v(const full_type& a) {
                return full_type(-a());
            }
        };

        template <typename _T>
        struct add<_T, 1> {
            using full_type = vec<_T, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return full_type(a() + b());
            }
        };

        template <typename _T>
        struct sub<_T, 1> {
            using full_type = vec<_T, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return full_type(a() - b());
            }
        };

        template <typename _T>
        struct mul<_T, 1> {
            using full_type = vec<_T, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return full_type(a() * b());
            }
        };

        template <typename _T>
        struct div<_T, 1> {
            using full_type = vec<_T, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                _T q=impl::divide(a(), b());
                return full_type(q);
            }
        };

        template <typename _T>
        struct mod<_T, 1> {
            using full_type = vec<_T, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return full_type(a() % b());
            }
        };

        template <typename _T>
        struct fma<_T, 1> {
            using full_type = vec<_T, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return full_type(a() * b() + c());
            }
        };

        template <typename _T>
        struct fms<_T, 1> {
            using full_type = vec<_T, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return full_type(a() * b() - c());
                // return full_type(std::fma(a(), b(), -c()));
            }
        };

        template <typename _T>
        struct fnma<_T, 1> {
            using full_type = vec<_T, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
            }
        };

        template <>
        struct fma<double, 1> {
            using full_type = vec<double, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (FP_FAST_FMA) && (FP_FAST_FMA>0)
                return full_type(std::fma(a(), b(), c()));
#elif defined (__clang__) && defined (__FMA__)
                return __builtin_fma(a(), b(), c());
#else
                return full_type(a() * b() + c());
#endif
            }
        };

        template <>
        struct fms<double, 1> {
            using full_type = vec<double, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (FP_FAST_FMA) && (FP_FAST_FMA>0)
                return full_type(std::fma(a(), b(), -c()));
#elif defined (__clang__) && defined (__FMA__)
                return __builtin_fma(a(), b(), -c());
#else
                return full_type(a() * b() - c());
#endif
            }
        };

        template <>
        struct fnma<double, 1> {
            using full_type = vec<double, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (FP_FAST_FMA) && (FP_FAST_FMA>0)
                return full_type(std::fma(-a(), b(), c()));
#elif defined (__clang__) && defined (__FMA__)
                return __builtin_fma(-a(), b(), c());
#else
                return full_type(c() - a() * b());
#endif
            }
        };

        template <>
        struct fma<float, 1> {
            using full_type = vec<float, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (FP_FAST_FMAF) && (FP_FAST_FMAF>0)
                return full_type(std::fmaf(a(), b(), c()));
#elif defined (__clang__) && defined (__FMA__)
                return __builtin_fmaf(a(), b(), c());
#else
                return full_type(a() * b() + c());
#endif
            }
        };

        template <>
        struct fms<float, 1> {
            using full_type = vec<float, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (FP_FAST_FMAF) && (FP_FAST_FMAF>0)
                return full_type(std::fmaf(a(), b(), -c()));
#elif defined (__clang__) && defined (__FMA__)
                return __builtin_fmaf(a(), b(), -c());
#else
                return full_type(a() * b() - c());
#endif
            }
        };

        template <>
        struct fnma<float, 1> {
            using full_type = vec<float, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (FP_FAST_FMAF) && (FP_FAST_FMAF>0)
                return full_type(std::fmaf(-a(), b(), c()));
#elif defined (__clang__) && defined (__FMA__)
                return __builtin_fmaf(-a(), b(), c());
#else
                return full_type(c() - a() * b());
#endif
            }
        };


        template <class _T>
        struct bitrep {
            using int_type = _T;
            using type = _T;
            static
            _T as_int(const _T& v) { return v; }
            static
            _T as_type(const _T& v) { return v; }
        };

        template <class _D, class _U>
        struct bitrep_helper {
            using int_type = _U;
            using type = _D;
            union di {
                _D _d;
                _U _u;
                di(const _D& d) : _d(d) {}
                di(const _U& u) : _u(u) {}
            };
            static
            int_type as_int(type v) {
                di t(v);
                return t._u;
            }
            static
            type as_type(int_type u) {
                di t(u);
                return t._d;
            }
        };

        template <>
        struct bitrep<double> :
            public bitrep_helper<double, std::uint64_t> {
        };

        template <>
        struct bitrep<float>  :
            public bitrep_helper<float, std::uint32_t> {
        };

        template <typename _T>
        struct bit_or<_T, 1> {
            using full_type = vec<_T, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                using cvt = bitrep<_T>;
                typename cvt::int_type ai(
                    cvt::as_int(a()));
                typename cvt::int_type bi(
                    cvt::as_int(b()));
                typename cvt::type r(
                    cvt::as_type(ai | bi));
                return full_type(r);
            }
        };

        template <typename _T>
        struct bit_and<_T, 1> {
            using full_type = vec<_T, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                using cvt = bitrep<_T>;
                typename cvt::int_type ai(
                    cvt::as_int(a()));
                typename cvt::int_type bi(
                    cvt::as_int(b()));
                typename cvt::type r(
                    cvt::as_type(ai & bi));
                return full_type(r);
            }
        };

        template <typename _T>
        struct bit_xor<_T, 1> {
            using full_type = vec<_T, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                using cvt = bitrep<_T>;
                typename cvt::int_type ai(
                    cvt::as_int(a()));
                typename cvt::int_type bi(
                    cvt::as_int(b()));
                typename cvt::type r(
                    cvt::as_type(ai ^ bi));
                return full_type(r);
            }
        };

        template <typename _T>
        struct bit_not<_T, 1> {
            using full_type = vec<_T, 1>;
            static
            full_type
            v(const full_type& a) {
                using cvt = bitrep<_T>;
                typename cvt::int_type ai(
                    cvt::as_int(a()));
                typename cvt::type r(
                    cvt::as_type(~ai));
                return full_type(r);
            }
        };

        template <typename _T>
        struct shl<_T, 1> {
            using full_type = vec<_T, 1>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                using cvt = bitrep<_T>;
                typename cvt::int_type ai(
                    cvt::as_int(a()));
                typename cvt::type r(
                    cvt::as_type(ai << s));
                return full_type(r);
            }
        };

        template <typename _T>
        struct shr<_T, 1> {
            using full_type = vec<_T, 1>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                using cvt = bitrep<_T>;
                typename cvt::int_type ai(
                    cvt::as_int(a()));
                typename cvt::type r(
                    cvt::as_type(ai >> s));
                return full_type(r);
            }
        };

        template <typename _T>
        struct vshl<_T, 1> {
            using full_type = vec<_T, 1>;
            static
            full_type
            v(const full_type& a, const full_type&  s) {
                return full_type(a() << s());
            }
        };

        template <typename _T>
        struct vshr<_T, 1> {
            using full_type = vec<_T, 1>;
            static
            full_type
            v(const full_type& a, const full_type&  s) {
                return full_type(a() >> s());
            }
        };

    }
}


template <class _T>
inline
cftal::vec<_T, 1>::vec(const _T& v)
    : _v(v)
{
}

template <class _T>
inline
cftal::vec<_T, 1>::vec(const _T& v, bool splat)
    : _v(v)
{
    static_cast<void>(splat);
}

template <class _T>
cftal::vec<_T, 1>::vec(std::initializer_list<_T> l)
    : vec<_T, 1>(mem<vec<_T, 1> >::load(std::begin(l)))
{
}

template <class _T>
cftal::vec<_T, 1>::vec(init_list<_T> l)
    : vec<_T, 1>(mem<vec<_T, 1> >::load(l.begin()))
{
}


template <typename _T>
template <template <class _U, std::size_t _M>
          class _OP,
          class _L, class _R>
cftal::vec<_T, 1>::vec(const expr<_OP<_T, 1>, _L, _R>& r)
    : vec(eval(r))
{
}

template <class _T>
inline
_T
cftal::vec<_T, 1>::operator()() const
{
    return _v;
}

template <class _T>
inline
bool
cftal::all_of(const vec<_T, 1>& v)
{
    using it= impl::xxx_of<_T,
                           typename cftal::is_floating_point<_T>::type>;
    return it::all(v);
}

template <class _T>
inline
bool
cftal::any_of(const vec<_T, 1>& v)
{
    using it= impl::xxx_of<_T,
                           typename cftal::is_floating_point<_T>::type>;
    return it::any(v);
}

template <class _T>
inline
bool
cftal::none_of(const vec<_T, 1>& v)
{
    using it= impl::xxx_of<_T,
                           typename cftal::is_floating_point<_T>::type>;
    return it::none(v);
}

template <class _T>
inline
std::enable_if_t<cftal::is_integral<_T>::value,
                 std::pair<cftal::vec<_T, 1>, cftal::vec<_T, 1> > >
cftal::mul_lo_hi(const vec<_T, 1>& a, const vec<_T, 1>& b)
{
    std::pair<_T, _T> r= mul_lo_hi(a(), b());
    return std::make_pair(vec<_T, 1>(r.first), vec<_T, 1>(r.second));
}

template <class _T>
inline
std::enable_if_t<cftal::is_integral<_T>::value, cftal::vec<_T, 1> >
cftal::abs(const vec<_T, 1>& a)
{
    return a() < _T(0) ? _T(-a()) : _T(a());
}

template <class _T>
inline
cftal::vec<_T, 1>
cftal::max(const vec<_T, 1>& a, const vec<_T, 1>& b)
{
    return a() > b() ? a : b;
}

template <class _T>
inline
cftal::vec<_T, 1>
cftal::min(const vec<_T, 1>& a, const vec<_T, 1>& b)
{
    return a() < b() ? a : b;
}

template <class _T>
inline
_T
cftal::max_element(const vec<_T, 1>& v)
{
    return v();
}

template <class _T>
inline
_T
cftal::min_element(const vec<_T, 1>& v)
{
    return v();
}

template <std::size_t _I, class _T>
inline
_T
cftal::extract(const vec<_T, 1>& v)
{
    static_assert(_I ==0, "invalid offset in extract()");
    return v();
}

template <class _T>
inline
_T
cftal::extract(const vec<_T, 1>& v, size_t i)
{
    static_cast<void>(i);
    return v();
}

template <std::size_t _I, class _T>
inline
void
cftal::insert(vec<_T, 1>& v, const _T& vi)
{
    static_assert(_I ==0, "invalid offset in insert()");
    v = vi;
}

template <class _T>
inline
void
cftal::insert(vec<_T, 1>& v, const _T& vi, size_t i)
{
    static_cast<void>(i);
    v = vi;
}

template <class _T>
inline
cftal::vec<_T, 1>
cftal::select(const typename vec<_T, 1>::mask_type& vm,
              const vec<_T, 1>& on_true,
              const vec<_T, 1>& on_false)
{
    using mvt= typename vec<_T, 1>::mask_type::value_type;
    typename vec<_T, 1>::value_type r{
        select(impl::mask_to_bool<mvt>::v(vm()), on_true(), on_false())};
    return vec<_T, 1>{r};
}

template <class _T>
inline
cftal::vec<_T, 1>
cftal::select_val_or_zero(const typename vec<_T, 1>::mask_type& vm,
                          const vec<_T, 1>& on_true)
{
    using mvt= typename vec<_T, 1>::mask_type::value_type;
    typename vec<_T, 1>::value_type r{
        select(impl::mask_to_bool<mvt>::v(vm()), on_true(), _T(0))};
    return vec<_T, 1>{r};
}

template <class _T>
inline
cftal::vec<_T, 1>
cftal::select_zero_or_val(const typename vec<_T, 1>::mask_type& vm,
                          const vec<_T, 1>& on_false)
{
    using mvt= typename vec<_T, 1>::mask_type::value_type;
    typename vec<_T, 1>::value_type r{
        select(impl::mask_to_bool<mvt>::v(vm()), _T(0), on_false())};
    return vec<_T, 1>{r};
}

template <int32_t _I0, class _T>
inline
cftal::vec<_T, 1>
cftal::permute(const vec<_T, 1>& v)
{
    static_assert(_I0 <= 0, "invalid element selection");
    return _I0 < 0 ? vec<_T, 1>(_T(0)) : v;
}

template <int32_t _I0, class _T>
inline
cftal::vec<_T, 1>
cftal::permute(const vec<_T, 1>& v0, const vec<_T, 1>& v1)
{
    static_assert(_I0 <= 1, "invalid element selection");
    if (_I0 < 0)
        return vec<_T, 1>(_T(0));
    return _I0 == 1 ? v1 : v0;
}

template <typename _T>
std::ostream&
cftal::operator<<(std::ostream& s, const vec<_T, 1>& v)
{
    s << v();
    return s;
}


// Local variables:
// mode: c++
// end:
#endif
