//
// Copyright (C) 2010-2024 Axel Zeuner
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
#if !defined (__CFTAL_F16_T_H__)
#define __CFTAL_F16_T_H__ 1

#include <cftal/config.h>
#include <cftal/cvt_f16.h>
#include <cftal/constants.h>
#include <cftal/type_traits.h>
#define __USE_STDCPP_FLOAT16_T__ 0
#if (__USE_STDCPP_FLOAT16_T__ > 0)
#if __has_include(<stdfloat>)
#include <stdfloat>
#if !defined(__STDCPP_FLOAT16_T__)
#undef __USE_STDCPP_FLOAT16_T__
#endif
#else
// no stdfloat
#undef __USE_STDCPP_FLOAT16_T__
#endif
#endif

#if __USE_STDCPP_FLOAT16_T__==0
#include <cftal/expr.h>
#include <iostream>
#endif

#include <cmath>

namespace cftal {

#if (__USE_STDCPP_FLOAT16_T__>0)
    using f16_t = std::float16_t;

    constexpr
    inline
    mf_f16_t read_bits(f16_t v) {
        return as<mf_f16_t>(v);
    }

#else
    // a 16 bit IEEE floating point number
    class f16_t {
    private:
        mf_f16_t _f;
        struct cvt_from_rep_tag {};
        constexpr f16_t(mf_f16_t f, const cvt_from_rep_tag& ) : _f(f) {}
    public:
        constexpr const mf_f16_t& operator()() const { return _f; }

        constexpr f16_t(float v) : _f(impl::_cvt_f32_to_f16(v)) {}
        explicit operator float() const { return cvt_f16_to_f32(_f); }
        explicit operator short int() const {
            return static_cast<short int>(cvt_f16_to_f32(_f));
        }
        explicit operator int() const {
            return static_cast<int>(cvt_f16_to_f32(_f));
        }

        constexpr f16_t()=default;
        constexpr f16_t(const f16_t&)=default;
        constexpr f16_t(f16_t&&)=default;
        f16_t& operator=(const f16_t&)=default;
        f16_t& operator=(f16_t&&)=default;

        template <template <typename _U> class _OP,
                  class _L, class _R>
        f16_t(const expr<_OP<f16_t>, _L, _R>& r) : f16_t(eval(r)) {}

        static
        constexpr f16_t cvt_from_rep(mf_f16_t f) {
            return f16_t(f, cvt_from_rep_tag());
        }
    };

    constexpr
    inline
    mf_f16_t read_bits(f16_t v) {
        return v();
    }

    namespace op {
        template <>
        struct neg<f16_t> {
            using full_type=f16_t;
            static
            f16_t v(const f16_t& a) {
                return f16_t(-float(a));
            }
        };

        template <>
        struct add<f16_t> {
            using full_type=f16_t;
            static
            f16_t v(const f16_t& a, const f16_t& b) {
                return f16_t(float(a) + float(b));
            }
        };

        template <>
        struct sub<f16_t> {
            using full_type=f16_t;
            static
            f16_t v(const f16_t& a, const f16_t& b) {
                return f16_t(float(a) - float(b));
            }
        };

        template <>
        struct mul<f16_t> {
            using full_type=f16_t;
            static
            f16_t v(const f16_t& a, const f16_t& b) {
                return f16_t(float(a) * float(b));
            }
        };

        template <>
        struct div<f16_t> {
            using full_type=f16_t;
            static
            f16_t v(const f16_t& a, const f16_t& b) {
                return f16_t(float(a) / float(b));
            }
        };

        template <>
        struct fma<f16_t> {
            using full_type=f16_t;
            static
            f16_t v(const f16_t& a, const f16_t& b, const f16_t& c) {
                auto fa=float(a);
                auto fb=float(b);
                auto fc=float(c);
                return f16_t(fa*fb + fc);
                // return f16_t(std::fmaf(fa, fb, fc));
            }
        };

        template <>
        struct fms<f16_t> {
            using full_type=f16_t;
            static
            f16_t v(const f16_t& a, const f16_t& b, const f16_t& c) {
                auto fa=float(a);
                auto fb=float(b);
                auto fc=float(c);
                return f16_t(fa*fb - fc);
                // return f16_t(std::fmaf(fa, fb, -fc));
            }
        };

        template <>
        struct fnma<f16_t> {
            using full_type=f16_t;
            static
            f16_t v(const f16_t& a, const f16_t& b, const f16_t& c) {
                auto fa=float(a);
                auto fb=float(b);
                auto fc=float(c);
                return f16_t(fc - fa*fb);
                // return f16_t(std::fmaf(-fa, fb, fc));
            }
        };
    }

    // expression template filters
    // a + b*c
    template <class _L1, class _L2, class _R2>
    inline
    f16_t
    eval(const expr<op::add<f16_t>,
                   _L1,
                   expr<op::mul<f16_t>, _L2, _R2> >& e) {
        return op::fma<f16_t>::v(eval(e._r._l),
                                 eval(e._r._r),
                                 eval(e._l));
    }

    // a*b +c
    template <class _L1, class _R1, class _R2>
    inline
    f16_t
    eval(const expr<op::add<f16_t>,
         expr<op::mul<f16_t>, _L1, _R1>,
         _R2>& e) {
        return op::fma<f16_t>::v(eval(e._l._l),
                                 eval(e._l._r),
                                 eval(e._r));
    }

    // a*b +c*d
    template <class _L1, class _R1, class _L2, class _R2>
    inline
    f16_t
    eval(const expr<op::add<f16_t>,
         expr<op::mul<f16_t>, _L1, _R1>,
         expr<op::mul<f16_t>, _L2, _R2> >& e) {
        return op::fma<f16_t>::v(eval(e._r._l),
                                 eval(e._r._r),
                                 eval(e._l));
    }

    // a*b -c
    template <class _L1, class _R1, class _R2>
    inline
    f16_t
    eval(const expr<op::sub<f16_t>,
         expr<op::mul<f16_t>, _L1, _R1>,
         _R2>& e) {
        return op::fms<f16_t>::v(eval(e._l._l),
                                 eval(e._l._r),
                                 eval(e._r));
    }
    // -a*b +c = c- a* b;
    template <class _L1, class _L2, class _R2>
    inline
    f16_t
    eval(const expr<op::sub<f16_t>,
         _L1,
         expr<op::mul<f16_t>, _L2, _R2> >& e) {
        return op::fnma<f16_t>::v(eval(e._r._l),
                                  eval(e._r._r),
                                  eval(e._l));
    }

    // a*b - c*d
    template <class _L1, class _R1, class _L2, class _R2>
    inline
    f16_t
    eval(const expr<op::sub<f16_t>,
         expr<op::mul<f16_t>, _L1, _R1>,
         expr<op::mul<f16_t>, _L2, _R2> >& e) {
#if 1
        return op::fnma<f16_t>::v(eval(e._r._l),
                                  eval(e._r._r),
                                  eval(e._l));
#else
        return op::fms<f16_t>::v(eval(e._l._l),
                                 eval(e._l._r),
                                 eval(e._r));
#endif
    }

    // evaluation of
    // a + -b = a - b
    template <class _L, class _R>
    inline
    f16_t
    eval(const expr<op::add<f16_t>,
         _L,
         expr<op::neg<f16_t>, _R, void> >& e) {
        return op::sub<f16_t>::v(eval(e._l),
                                 eval(e._r._l));
    }

    // evaluation of
    // -a + b = b - a
    template <class _L, class _R>
    inline
    f16_t
    eval(const expr<op::add<f16_t>,
         expr<op::neg<f16_t>, _L, void>,
         _R>& e) {
        return op::sub<f16_t>::v(eval(e._r._l),
                                 eval(e._l));
    }

    // evaluation of
    // a - -b = a + b
    template <typename _T, std::size_t _N,
              class _L, class _R>
    inline
    f16_t
    eval(const expr<op::sub<f16_t>,
         _L,
         expr<op::neg<f16_t>, _R, void> >& e) {
        return op::add<f16_t>::v(eval(e._l),
                                 eval(e._r._l));
    }

    bool operator<(const f16_t& a, const f16_t& b);
    bool operator<=(const f16_t& a, const f16_t& b);
    bool operator==(const f16_t& a, const f16_t& b);
    bool operator!=(const f16_t& a, const f16_t& b);
    bool operator>=(const f16_t& a, const f16_t& b);
    bool operator>(const f16_t& a, const f16_t& b);

    constexpr
    const f16_t& operator+(const f16_t& a);

    constexpr
    f16_t operator-(const f16_t& v);

    // unary minus: expr
    template <template <typename _T1> class _OP,
              typename _L, typename _R>
    expr<op::neg<f16_t>,
         expr<_OP<f16_t>, _L, _R>, void>
    operator-(const expr<_OP<f16_t>, _L, _R>& r);

    // add operator: s, s
    expr<op::add<f16_t>, f16_t, f16_t >
    operator+(const f16_t& a, const f16_t& b);
    // add operator: s, expr
    template <template <typename _T1> class _OP,
              class _L, class _R>
    expr<op::add<f16_t>, f16_t, expr<_OP<f16_t>, _L, _R> >
    operator+(const f16_t& a,
              const expr<_OP<f16_t>, _L, _R>& b);
    // add operator: expr, s
    template <template <typename _T1> class _OP,
              class _L, class _R>
    expr<op::add<f16_t>, expr<_OP<f16_t>, _L, _R>, f16_t>
    operator+(const expr<_OP<f16_t>, _L, _R>& a,
              const f16_t& b);
    // add operator: expr, expr
    template <template <typename _T1> class _OP1,
              class _L1, class _R1,
              template <typename _T2> class _OP2,
              class _L2, class _R2>
    expr<op::add<f16_t>,
         expr<_OP1<f16_t>, _L1, _R1>,
         expr<_OP2<f16_t>, _L2, _R2> >
    operator+(const expr<_OP1<f16_t>, _L1, _R1>& a,
              const expr<_OP2<f16_t>, _L2, _R2>& b);
    // self add operator: s, s
    f16_t&
    operator+=(f16_t& a,
               const f16_t& b);
    // self add operator: s, expr
    template <template <typename _T1> class _OP,
              class _L, class _R>
    f16_t&
    operator+=(f16_t& a,
               const expr<_OP<f16_t>, _L, _R>& b);

    // sub operator: s, s
    expr<op::sub<f16_t>, f16_t, f16_t >
    operator-(const f16_t& a, const f16_t& b);
    // sub operator: s, expr
    template <template <typename _T1> class _OP,
              class _L, class _R>
    expr<op::sub<f16_t>, f16_t, expr<_OP<f16_t>, _L, _R> >
    operator-(const f16_t& a,
              const expr<_OP<f16_t>, _L, _R>& b);
    // sub operator: expr, s
    template <template <typename _T1> class _OP,
              class _L, class _R>
    expr<op::sub<f16_t>, expr<_OP<f16_t>, _L, _R>, f16_t>
    operator-(const expr<_OP<f16_t>, _L, _R>& a,
              const f16_t& b);
    // sub operator: expr, expr
    template <template <typename _T1> class _OP1,
              class _L1, class _R1,
              template <typename _T2> class _OP2,
              class _L2, class _R2>
    expr<op::sub<f16_t>,
         expr<_OP1<f16_t>, _L1, _R1>,
         expr<_OP2<f16_t>, _L2, _R2> >
    operator-(const expr<_OP1<f16_t>, _L1, _R1>& a,
              const expr<_OP2<f16_t>, _L2, _R2>& b);
    // self sub operator: s, s
    f16_t&
    operator-=(f16_t& a,
               const f16_t& b);
    // self sub operator: s, expr
    template <template <typename _T1> class _OP,
              class _L, class _R>
    f16_t&
    operator-=(f16_t& a,
               const expr<_OP<f16_t>, _L, _R>& b);


    // mul operator: s, s
    expr<op::mul<f16_t>, f16_t, f16_t >
    operator*(const f16_t& a, const f16_t& b);
    // mul operator: s, expr
    template <template <typename _T1> class _OP,
              class _L, class _R>
    expr<op::mul<f16_t>, f16_t, expr<_OP<f16_t>, _L, _R> >
    operator*(const f16_t& a,
              const expr<_OP<f16_t>, _L, _R>& b);
    // mul operator: expr, s
    template <template <typename _T1> class _OP,
              class _L, class _R>
    expr<op::mul<f16_t>, expr<_OP<f16_t>, _L, _R>, f16_t>
    operator*(const expr<_OP<f16_t>, _L, _R>& a,
              const f16_t& b);
    // mul operator: expr, expr
    template <template <typename _T1> class _OP1,
              class _L1, class _R1,
              template <typename _T2> class _OP2,
              class _L2, class _R2>
    expr<op::mul<f16_t>,
         expr<_OP1<f16_t>, _L1, _R1>,
         expr<_OP2<f16_t>, _L2, _R2> >
    operator*(const expr<_OP1<f16_t>, _L1, _R1>& a,
              const expr<_OP2<f16_t>, _L2, _R2>& b);
    // self mul operator: s, s
    f16_t&
    operator*=(f16_t& a,
               const f16_t& b);
    // self mul operator: s, expr
    template <template <typename _T1> class _OP,
              class _L, class _R>
    f16_t&
    operator*=(f16_t& a,
               const expr<_OP<f16_t>, _L, _R>& b);

    // div operator: s, s
    expr<op::div<f16_t>, f16_t, f16_t >
    operator/(const f16_t& a, const f16_t& b);
    // div operator: s, expr
    template <template <typename _T1> class _OP,
              class _L, class _R>
    expr<op::div<f16_t>, f16_t, expr<_OP<f16_t>, _L, _R> >
    operator/(const f16_t& a,
              const expr<_OP<f16_t>, _L, _R>& b);
    // div operator: expr, s
    template <template <typename _T1> class _OP,
              class _L, class _R>
    expr<op::div<f16_t>, expr<_OP<f16_t>, _L, _R>, f16_t>
    operator/(const expr<_OP<f16_t>, _L, _R>& a,
              const f16_t& b);
    // div operator: expr, expr
    template <template <typename _T1> class _OP1,
              class _L1, class _R1,
              template <typename _T2> class _OP2,
              class _L2, class _R2>
    expr<op::div<f16_t>,
         expr<_OP1<f16_t>, _L1, _R1>,
         expr<_OP2<f16_t>, _L2, _R2> >
    operator/(const expr<_OP1<f16_t>, _L1, _R1>& a,
              const expr<_OP2<f16_t>, _L2, _R2>& b);
    // self div operator: s, s
    f16_t&
    operator/=(f16_t& a,
               const f16_t& b);
    // self div operator: s, expr
    template <template <typename _T1> class _OP,
              class _L, class _R>
    f16_t&
    operator/=(f16_t& a,
               const expr<_OP<f16_t>, _L, _R>& b);

    f16_t fma(const f16_t& a, const f16_t& b, const f16_t& c);

    f16_t rint(const f16_t& v);
    f16_t floor(const f16_t& v);
    f16_t ceil(const f16_t& v);
    f16_t trunc(const f16_t& v);

    f16_t sqrt(const f16_t& v);
    f16_t cbrt(const f16_t& v);

    f16_t hypot(const f16_t& a, const f16_t& b);

    f16_t exp(const f16_t& v);
    f16_t expm1(const f16_t& v);
    f16_t exp2(const f16_t& v);
    f16_t sinh(const f16_t& v);
    f16_t cosh(const f16_t& v);
    f16_t tanh(const f16_t& v);
    f16_t log(const f16_t& v);
    f16_t log2(const f16_t& v);
    f16_t log10(const f16_t& v);
    f16_t log1p(const f16_t& v);
    f16_t pow(const f16_t& a, const f16_t& b);

    f16_t sin(const f16_t& v);
    f16_t cos(const f16_t& v);
    f16_t tan(const f16_t& v);

    f16_t asin(const f16_t& v);
    f16_t acos(const f16_t& v);
    f16_t atan(const f16_t& v);
    f16_t atan2(const f16_t& v, const f16_t& w);

    std::ostream& operator<<(std::ostream& s, const f16_t& v);
    std::istream& operator>>(std::istream& s, f16_t& v);
#endif // (__USE_STDCPP_FLOAT16_T__>0)

    template <>
    struct is_floating_point<f16_t> : public std::true_type {};

    // use a user defined operator to avoid overriding f16
    constexpr
    f16_t operator ""_f16(long double);

    bool isnan(const f16_t& v);
    bool isinf(const f16_t& v);
    f16_t abs(const f16_t& v);
    bool signbit(const f16_t& v);

    // math functions for f16_t are missing
    f16_t
    copysign(f16_t a, f16_t b);

    f16_t
    nextafter(f16_t a, f16_t b);

    f16_t frexp(f16_t x, int* e);
    f16_t ldexp(f16_t x, int e);
}

#if (__USE_STDCPP_FLOAT16_T__==0)

inline
bool cftal::operator<(const f16_t& a, const f16_t& b)
{
    return float(a) < float(b);
}

inline
bool cftal::operator<=(const f16_t& a, const f16_t& b)
{
    return float(a) <= float(b);
}

inline
bool cftal::operator==(const f16_t& a, const f16_t& b)
{
    return float(a) == float(b);
}

inline
bool cftal::operator!=(const f16_t& a, const f16_t& b)
{
    return float(a) != float(b);
}

inline
bool cftal::operator>=(const f16_t& a, const f16_t& b)
{
    return float(a) >= float(b);
}

inline
bool cftal::operator>(const f16_t& a, const f16_t& b)
{
    return float(a) > float(b);
}

constexpr
inline
const cftal::f16_t&
cftal::operator+(const f16_t& v)
{
    return v;
}

constexpr
inline
cftal::f16_t
cftal::operator-(const f16_t& v)
{
    mf_f16_t t=read_bits(v) ^ sign_f16_msk::v.s16();
    return f16_t::cvt_from_rep(t);
}

template <template <typename _T1> class _OP,
          typename _L, typename _R>
cftal::expr<cftal::op:: neg<cftal::f16_t>,
            cftal::expr<_OP<cftal::f16_t>, _L, _R>,
            void>
cftal::operator-(const expr<_OP<f16_t>, _L, _R>& v)
{
    return expr<op:: neg<f16_t>,
                expr<_OP<f16_t>, _L, _R>,
                void>(v);
}

inline
cftal::expr<cftal::op::add <cftal::f16_t>,
            cftal::f16_t,
            cftal::f16_t >
cftal::operator+(const f16_t& a, const f16_t& b)
{
    return expr<op:: add<f16_t>,
                f16_t,
                f16_t >(a, b);
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::add <cftal::f16_t>,
            cftal::f16_t,
            cftal::expr<_OP<cftal::f16_t>, _L, _R> >
cftal::operator+(const f16_t& a,
                 const expr<_OP<f16_t>, _L, _R>& b)
{
    return expr<op::add<f16_t>,
                f16_t,
                expr<_OP<f16_t>, _L, _R> >(a, b);
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::add <cftal::f16_t>,
            cftal::expr<_OP<cftal::f16_t>, _L, _R>,
            cftal::f16_t >
cftal::operator+(const expr<_OP<f16_t>, _L, _R>& a,
                 const f16_t& b)
{
    return expr<op::add<f16_t>,
                expr<_OP<f16_t>, _L, _R>,
                f16_t >(a, b);
}

template <template <typename _T1> class _OP1,
          class _L1, class _R1,
          template <typename _T2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::add <cftal::f16_t>,
            cftal::expr<_OP1<cftal::f16_t>, _L1, _R1>,
            cftal::expr<_OP2<cftal::f16_t>, _L2, _R2> >
cftal::operator+(const expr<_OP1<f16_t>, _L1, _R1>& a,
                 const expr<_OP2<f16_t>, _L2, _R2>& b)
{
    return expr<op::add<f16_t>,
                expr<_OP1<f16_t>, _L1, _R1>,
                expr<_OP2<f16_t>, _L2, _R2> >(a, b);
}

inline
cftal::f16_t&
cftal::operator+=(f16_t& a,
                  const f16_t& b)
{
    a = a + b;
    return a;
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::f16_t&
cftal::operator+=(f16_t& a,
                  const expr<_OP<f16_t>, _L, _R>& b)
{
    a = a + b;
    return a;
}

inline
cftal::expr<cftal::op::sub <cftal::f16_t>,
            cftal::f16_t,
            cftal::f16_t >
cftal::operator-(const f16_t& a, const f16_t& b)
{
    return expr<op:: sub<f16_t>,
                f16_t,
                f16_t >(a, b);
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::sub <cftal::f16_t>,
            cftal::f16_t,
            cftal::expr<_OP<cftal::f16_t>, _L, _R> >
cftal::operator-(const f16_t& a,
                 const expr<_OP<f16_t>, _L, _R>& b)
{
    return expr<op::sub<f16_t>,
                f16_t,
                expr<_OP<f16_t>, _L, _R> >(a, b);
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::sub <cftal::f16_t>,
            cftal::expr<_OP<cftal::f16_t>, _L, _R>,
            cftal::f16_t >
cftal::operator-(const expr<_OP<f16_t>, _L, _R>& a,
                 const f16_t& b)
{
    return expr<op::sub<f16_t>,
                expr<_OP<f16_t>, _L, _R>,
                f16_t >(a, b);
}

template <template <typename _T1> class _OP1,
          class _L1, class _R1,
          template <typename _T2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::sub <cftal::f16_t>,
            cftal::expr<_OP1<cftal::f16_t>, _L1, _R1>,
            cftal::expr<_OP2<cftal::f16_t>, _L2, _R2> >
cftal::operator-(const expr<_OP1<f16_t>, _L1, _R1>& a,
                 const expr<_OP2<f16_t>, _L2, _R2>& b)
{
    return expr<op::sub<f16_t>,
                expr<_OP1<f16_t>, _L1, _R1>,
                expr<_OP2<f16_t>, _L2, _R2> >(a, b);
}

inline
cftal::f16_t&
cftal::operator-=(f16_t& a,
                  const f16_t& b)
{
    a = a - b;
    return a;
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::f16_t&
cftal::operator-=(f16_t& a,
                  const expr<_OP<f16_t>, _L, _R>& b)
{
    a = a - b;
    return a;
}

inline
cftal::expr<cftal::op::mul <cftal::f16_t>,
            cftal::f16_t,
            cftal::f16_t >
cftal::operator*(const f16_t& a, const f16_t& b)
{
    return expr<op:: mul<f16_t>,
                f16_t,
                f16_t >(a, b);
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::mul <cftal::f16_t>,
            cftal::f16_t,
            cftal::expr<_OP<cftal::f16_t>, _L, _R> >
cftal::operator*(const f16_t& a,
                 const expr<_OP<f16_t>, _L, _R>& b)
{
    return expr<op::mul<f16_t>,
                f16_t,
                expr<_OP<f16_t>, _L, _R> >(a, b);
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::mul <cftal::f16_t>,
            cftal::expr<_OP<cftal::f16_t>, _L, _R>,
            cftal::f16_t >
cftal::operator*(const expr<_OP<f16_t>, _L, _R>& a,
                 const f16_t& b)
{
    return expr<op::mul<f16_t>,
                expr<_OP<f16_t>, _L, _R>,
                f16_t >(a, b);
}

template <template <typename _T1> class _OP1,
          class _L1, class _R1,
          template <typename _T2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::mul <cftal::f16_t>,
            cftal::expr<_OP1<cftal::f16_t>, _L1, _R1>,
            cftal::expr<_OP2<cftal::f16_t>, _L2, _R2> >
cftal::operator*(const expr<_OP1<f16_t>, _L1, _R1>& a,
                 const expr<_OP2<f16_t>, _L2, _R2>& b)
{
    return expr<op::mul<f16_t>,
                expr<_OP1<f16_t>, _L1, _R1>,
                expr<_OP2<f16_t>, _L2, _R2> >(a, b);
}

inline
cftal::f16_t&
cftal::operator*=(f16_t& a,
                  const f16_t& b)
{
    a = a * b;
    return a;
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::f16_t&
cftal::operator*=(f16_t& a,
                  const expr<_OP<f16_t>, _L, _R>& b)
{
    a = a * b;
    return a;
}

inline
cftal::expr<cftal::op::div <cftal::f16_t>,
            cftal::f16_t,
            cftal::f16_t >
cftal::operator/(const f16_t& a, const f16_t& b)
{
    return expr<op:: div<f16_t>,
                f16_t,
                f16_t >(a, b);
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::div <cftal::f16_t>,
            cftal::f16_t,
            cftal::expr<_OP<cftal::f16_t>, _L, _R> >
cftal::operator/(const f16_t& a,
                 const expr<_OP<f16_t>, _L, _R>& b)
{
    return expr<op::div<f16_t>,
                f16_t,
                expr<_OP<f16_t>, _L, _R> >(a, b);
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::div <cftal::f16_t>,
            cftal::expr<_OP<cftal::f16_t>, _L, _R>,
            cftal::f16_t >
cftal::operator/(const expr<_OP<f16_t>, _L, _R>& a,
                 const f16_t& b)
{
    return expr<op::div<f16_t>,
                expr<_OP<f16_t>, _L, _R>,
                f16_t >(a, b);
}

template <template <typename _T1> class _OP1,
          class _L1, class _R1,
          template <typename _T2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::div <cftal::f16_t>,
            cftal::expr<_OP1<cftal::f16_t>, _L1, _R1>,
            cftal::expr<_OP2<cftal::f16_t>, _L2, _R2> >
cftal::operator/(const expr<_OP1<f16_t>, _L1, _R1>& a,
                 const expr<_OP2<f16_t>, _L2, _R2>& b)
{
    return expr<op::div<f16_t>,
                expr<_OP1<f16_t>, _L1, _R1>,
                expr<_OP2<f16_t>, _L2, _R2> >(a, b);
}

inline
cftal::f16_t&
cftal::operator/=(f16_t& a,
                  const f16_t& b)
{
    a = a / b;
    return a;
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::f16_t&
cftal::operator/=(f16_t& a,
                  const expr<_OP<f16_t>, _L, _R>& b)
{
    a = a / b;
    return a;
}

inline
cftal::f16_t cftal::fma(const f16_t& a, const f16_t& b, const f16_t& c)
{
    return f16_t(float(a)*float(b)+float(c));
}

inline
cftal::f16_t cftal::rint(const f16_t& v)
{
    return f16_t(std::rint(float(v)));
}

inline
cftal::f16_t cftal::floor(const f16_t& v)
{
    return f16_t(std::floor(float(v)));
}

inline
cftal::f16_t cftal::ceil(const f16_t& v)
{
    return f16_t(std::ceil(float(v)));
}

inline
cftal::f16_t cftal::trunc(const f16_t& v)
{
    return f16_t(std::trunc(float(v)));
}

inline
cftal::f16_t cftal::sqrt(const f16_t& v)
{
    return f16_t(std::sqrt(float(v)));
}

inline
cftal::f16_t cftal::cbrt(const f16_t& v)
{
    return f16_t(std::cbrt(float(v)));
}

inline
cftal::f16_t cftal::hypot(const f16_t& x, const f16_t& y)
{
    return f16_t(std::hypot(float(x), float(y)));
}

inline
cftal::f16_t cftal::exp(const f16_t& v)
{
    return f16_t(std::exp(float(v)));
}

inline
cftal::f16_t cftal::expm1(const f16_t& v)
{
    return f16_t(std::expm1(float(v)));
}

inline
cftal::f16_t cftal::exp2(const f16_t& v)
{
    return f16_t(std::exp2(float(v)));
}

inline
cftal::f16_t cftal::sinh(const f16_t& v)
{
    return f16_t(std::sinh(float(v)));
}

inline
cftal::f16_t cftal::cosh(const f16_t& v)
{
    return f16_t(std::cosh(float(v)));
}

inline
cftal::f16_t cftal::tanh(const f16_t& v)
{
    return f16_t(std::tanh(float(v)));
}

inline
cftal::f16_t cftal::log(const f16_t& v)
{
    return f16_t(std::log(float(v)));
}

inline
cftal::f16_t cftal::log2(const f16_t& v)
{
    return f16_t(std::log2(float(v)));
}

inline
cftal::f16_t cftal::log10(const f16_t& v)
{
    return f16_t(std::log10(float(v)));
}

inline
cftal::f16_t cftal::log1p(const f16_t& v)
{
    return f16_t(std::log1p(float(v)));
}

inline
cftal::f16_t cftal::pow(const f16_t& a, const f16_t& b)
{
    return f16_t(std::pow(float(a), float(b)));
}

inline
cftal::f16_t cftal::sin(const f16_t& v)
{
    return f16_t(std::sin(float(v)));
}

inline
cftal::f16_t cftal::cos(const f16_t& v)
{
    return f16_t(std::cos(float(v)));
}

inline
cftal::f16_t cftal::tan(const f16_t& v)
{
    return f16_t(std::tan(float(v)));
}

inline
cftal::f16_t cftal::asin(const f16_t& v)
{
    return f16_t(std::asin(float(v)));
}

inline
cftal::f16_t cftal::acos(const f16_t& v)
{
    return f16_t(std::acos(float(v)));
}

inline
cftal::f16_t cftal::atan(const f16_t& v)
{
    return f16_t(std::atan(float(v)));
}

inline
cftal::f16_t cftal::atan2(const f16_t& a, const f16_t& b)
{
    return f16_t(std::atan2(float(a), float(b)));
}

inline
std::ostream& cftal::operator<<(std::ostream& s, const f16_t& v)
{
    float fv(v);
    s << fv;
    return s;
}

inline
std::istream& cftal::operator>>(std::istream& s, f16_t& v)
{
    float fv;
    s >> fv;
    v = f16_t(fv);
    return s;
}
#endif // __USE_STDCPP_FLOAT16_T__==0

inline
constexpr
cftal::f16_t cftal::operator ""_f16(long double d)
{
#if __USE_STDCPP_FLOAT16_T__>0
    return f16_t(static_cast<float>(d));
#else
    return f16_t::cvt_from_rep(impl::_cvt_f32_to_f16(static_cast<float>(d)));
#endif
}

inline
bool cftal::isnan(const f16_t& v)
{
    const mf_f16_t& vi= read_bits(v);
    mf_f16_t abs_vi= vi & not_sign_f16_msk::v.u16();
    return abs_vi > exp_f16_msk::v.u16();
}

inline
bool cftal::isinf(const f16_t& v)
{
    const mf_f16_t& vi= read_bits(v);
    mf_f16_t abs_vi= vi & not_sign_f16_msk::v.u16();
    return abs_vi == exp_f16_msk::v.u16();
}

inline
cftal::f16_t cftal::abs(const f16_t& v)
{
    const mf_f16_t& vi= read_bits(v);
    mf_f16_t abs_vi= vi & not_sign_f16_msk::v.u16();
    return as<f16_t>(abs_vi);
}

inline
bool cftal::signbit(const f16_t& v)
{
    const mf_f16_t& vi= read_bits(v);
    return (vi & sign_f16_msk::v.u16()) == sign_f16_msk::v.u16();
}

inline
cftal::f16_t
cftal::copysign(f16_t x, f16_t y)
{
    const uint16_t abs_msk=not_sign_f16_msk::v.u16();
    uint16_t abs_x=read_bits(x) & abs_msk;
    const uint16_t sgn_msk=sign_f16_msk::v.u16();
    uint16_t sgn_y=read_bits(y) & sgn_msk;
    uint16_t r= abs_x | sgn_y;
    return as<f16_t>(r);
}

#if (__USE_STDCPP_FLOAT16_T__==0)
namespace std {

    template <>
    struct numeric_limits<cftal::f16_t> {
        static const bool is_specialized = true;
        static const bool is_signed = true;
        static const bool is_integer = false;
        static const bool is_exact = false;
        static const bool has_infinity = true;
        static const bool has_quiet_NaN = true;
        static const bool has_signaling_NaN = true;
        static const float_denorm_style has_denorm = denorm_present;
        static const bool has_denorm_loss = false;
        static const std::float_round_style round_style = std::round_to_nearest;
        static const bool is_iec559 = false;
        static const bool is_bounded = false;
        static const bool is_modulo = false;
        static const int digits = 11;
        static const int digits10 = 3;      // according to http://half.sourceforge.net/structstd_1_1numeric__limits_3_01half__float_1_1half_01_4.html
        static const int max_digits10 = 5;  // according to http://half.sourceforge.net/structstd_1_1numeric__limits_3_01half__float_1_1half_01_4.html
        static const int radix = 2;
        static const int min_exponent = -13;
        static const int min_exponent10 = -4;
        static const int max_exponent = 16;
        static const int max_exponent10 = 4;
        static const bool traps = true;
        static const bool tinyness_before = false;

        constexpr
        static cftal::f16_t (min)() {
            return cftal::f16_t::cvt_from_rep(0x400);
        }
        constexpr
        static cftal::f16_t lowest() {
            return cftal::f16_t::cvt_from_rep(0xfbff);
        }
        constexpr
        static cftal::f16_t (max)() {
            return cftal::f16_t::cvt_from_rep(0x7bff);
        }
        constexpr
        static cftal::f16_t epsilon() {
            return cftal::f16_t::cvt_from_rep(0x0800);
        }
        static cftal::f16_t round_error() {
            return cftal::f16_t(float(0.5));
        }
        constexpr
        static cftal::f16_t infinity() {
            return cftal::f16_t::cvt_from_rep(0x7c00);
        }
        constexpr
        static cftal::f16_t quiet_NaN() {
            return cftal::f16_t::cvt_from_rep(0x7e00);
        }
        constexpr
        static cftal::f16_t signaling_NaN() {
            return cftal::f16_t::cvt_from_rep(0x7e00);
        }
        constexpr
        static cftal::f16_t denorm_min() {
            return cftal::f16_t::cvt_from_rep(0x1);
        }
    };
}
#endif // __USE_STDCPP_FLOAT16_T__ == 0

// keep this function after the specialization of std::numeric_limits<f16_t>
inline
cftal::f16_t
cftal::nextafter(f16_t xc, f16_t yc)
{
    uint16_t ux=read_bits(xc);
    uint16_t uy=read_bits(yc);
    uint16_t ax= ux & not_sign_f16_msk::v.u16();
    uint16_t ay= uy & not_sign_f16_msk::v.u16();
    uint16_t ux_inc= ux + 1;
    uint16_t ux_dec= ux - 1;
    // decrement required if ax > ay or (ux^uy & sgn) != 0
    bool opp_sgn=
        uint16_t((ux^uy) & sign_f16_msk::v.u16()) != uint16_t(0);
    uint16_t r= ((ax > ay) | opp_sgn) ? ux_dec : ux_inc;
    uint16_t r0= ay == 0 ? uy : (uy & sign_f16_msk::v.u16()) | 1;
    r = ax == 0 ? r0 : r;
    r = ux == uy ? uy : r;
    // f16_t rf= f16_t::cvt_from_rep(r);
    f16_t rf=as<f16_t>(r);
    rf = (isnan(xc) || isnan(yc)) ? std::numeric_limits<f16_t>::quiet_NaN() : rf;
    return rf;
}

inline
cftal::f16_t
cftal::frexp(f16_t x, int* e)
{
    float fx=static_cast<float>(x);
    using std::frexp;
    float m=frexp(fx, e);
    return f16_t(m);
}

inline
cftal::f16_t
cftal::ldexp(f16_t x, int e)
{
    float fx=static_cast<float>(x);
    using std::ldexp;
    float r=ldexp(fx, e);
    return f16_t(r);
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_F16_T_H__
