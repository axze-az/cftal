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
#if !defined (__CFTAL_BF16_T_H__)
#define __CFTAL_BF16_T_H__ 1

#include <cftal/config.h>
#include <cftal/cvt_bf16.h>
#include <cftal/constants.h>
#include <cftal/type_traits.h>
#define __USE_STDCPP_BFLOAT16_T__ 0
#if (__USE_STDCPP_BFLOAT16_T__ > 0)
#if __has_include(<stdfloat>)
#include <stdfloat>
#if !defined(__STDCPP_BFLOAT16_T__)
#undef __USE_STDCPP_BFLOAT16_T__
#endif
#else
// no stdfloat
#undef __USE_STDCPP_BFLOAT16_T__
#endif
#endif

#if __USE_STDCPP_BFLOAT16_T__==0
#include <cftal/expr.h>
#include <cftal/op.h>
#include <iostream>
#endif

#include <cmath>

namespace cftal {

#if (__USE_STDCPP_BFLOAT16_T__>0)
    using bf16_t = std::bfloat16_t;

    constexpr
    inline
    mf_bf16_t read_bits(const bf16_t& v) {
        return as<mf_bf16_t>(v);
    }

#else
    // a 16 bit IEEE floating point number
    class bf16_t {
    private:
        mf_bf16_t _f;
        struct cvt_from_rep_tag {};
        constexpr bf16_t(mf_bf16_t f, const cvt_from_rep_tag& ) : _f(f) {}
    public:
        constexpr const mf_bf16_t& operator()() const { return _f; }

        constexpr bf16_t(float v) : _f(impl::_cvt_f32_to_bf16(v)) {}
        constexpr
        explicit operator float() const { return impl::_cvt_bf16_to_f32(_f); }
        explicit operator short int() const {
            return static_cast<short int>(cvt_bf16_to_f32(_f));
        }
        explicit operator int() const {
            return static_cast<int>(cvt_bf16_to_f32(_f));
        }

        constexpr bf16_t()=default;
        constexpr bf16_t(const bf16_t&)=default;
        constexpr bf16_t(bf16_t&&)=default;
        bf16_t& operator=(const bf16_t&)=default;
        bf16_t& operator=(bf16_t&&)=default;

        template <template <typename _U> class _OP,
                  class _L, class _R>
        bf16_t(const expr<_OP<bf16_t>, _L, _R>& r) : bf16_t(eval(r)) {}

        static
        constexpr bf16_t cvt_from_rep(mf_bf16_t f) {
            return bf16_t(f, cvt_from_rep_tag());
        }
    };

    constexpr
    inline
    mf_bf16_t read_bits(bf16_t v) {
        return v();
    }

    namespace op {
        template <>
        struct neg<bf16_t> {
            using full_type=bf16_t;
            static
            bf16_t v(const bf16_t& a) {
                return bf16_t(-float(a));
            }
        };

        template <>
        struct add<bf16_t> {
            using full_type=bf16_t;
            static
            bf16_t v(const bf16_t& a, const bf16_t& b) {
                return bf16_t(float(a) + float(b));
            }
        };

        template <>
        struct sub<bf16_t> {
            using full_type=bf16_t;
            static
            bf16_t v(const bf16_t& a, const bf16_t& b) {
                return bf16_t(float(a) - float(b));
            }
        };

        template <>
        struct mul<bf16_t> {
            using full_type=bf16_t;
            static
            bf16_t v(const bf16_t& a, const bf16_t& b) {
                return bf16_t(float(a) * float(b));
            }
        };

        template <>
        struct div<bf16_t> {
            using full_type=bf16_t;
            static
            bf16_t v(const bf16_t& a, const bf16_t& b) {
                return bf16_t(float(a) / float(b));
            }
        };

        template <>
        struct fma<bf16_t> {
            using full_type=bf16_t;
            static
            bf16_t v(const bf16_t& a, const bf16_t& b, const bf16_t& c) {
                auto fa=float(a);
                auto fb=float(b);
                auto fc=float(c);
                return bf16_t(fa*fb + fc);
                // return bf16_t(std::fmaf(fa, fb, fc));
            }
        };

        template <>
        struct fms<bf16_t> {
            using full_type=bf16_t;
            static
            bf16_t v(const bf16_t& a, const bf16_t& b, const bf16_t& c) {
                auto fa=float(a);
                auto fb=float(b);
                auto fc=float(c);
                return bf16_t(fa*fb - fc);
                // return bf16_t(std::fmaf(fa, fb, -fc));
            }
        };

        template <>
        struct fnma<bf16_t> {
            using full_type=bf16_t;
            static
            bf16_t v(const bf16_t& a, const bf16_t& b, const bf16_t& c) {
                auto fa=float(a);
                auto fb=float(b);
                auto fc=float(c);
                return bf16_t(fc - fa*fb);
                // return bf16_t(std::fmaf(-fa, fb, fc));
            }
        };
    }

    // expression template filters
    // a + b*c
    template <class _L1, class _L2, class _R2>
    inline
    bf16_t
    eval(const expr<op::add<bf16_t>,
                   _L1,
                   expr<op::mul<bf16_t>, _L2, _R2> >& e) {
        return op::fma<bf16_t>::v(eval(e._r._l),
                                 eval(e._r._r),
                                 eval(e._l));
    }

    // a*b +c
    template <class _L1, class _R1, class _R2>
    inline
    bf16_t
    eval(const expr<op::add<bf16_t>,
         expr<op::mul<bf16_t>, _L1, _R1>,
         _R2>& e) {
        return op::fma<bf16_t>::v(eval(e._l._l),
                                 eval(e._l._r),
                                 eval(e._r));
    }

    // a*b +c*d
    template <class _L1, class _R1, class _L2, class _R2>
    inline
    bf16_t
    eval(const expr<op::add<bf16_t>,
         expr<op::mul<bf16_t>, _L1, _R1>,
         expr<op::mul<bf16_t>, _L2, _R2> >& e) {
        return op::fma<bf16_t>::v(eval(e._r._l),
                                 eval(e._r._r),
                                 eval(e._l));
    }

    // a*b -c
    template <class _L1, class _R1, class _R2>
    inline
    bf16_t
    eval(const expr<op::sub<bf16_t>,
         expr<op::mul<bf16_t>, _L1, _R1>,
         _R2>& e) {
        return op::fms<bf16_t>::v(eval(e._l._l),
                                 eval(e._l._r),
                                 eval(e._r));
    }
    // -a*b +c = c- a* b;
    template <class _L1, class _L2, class _R2>
    inline
    bf16_t
    eval(const expr<op::sub<bf16_t>,
         _L1,
         expr<op::mul<bf16_t>, _L2, _R2> >& e) {
        return op::fnma<bf16_t>::v(eval(e._r._l),
                                  eval(e._r._r),
                                  eval(e._l));
    }

    // a*b - c*d
    template <class _L1, class _R1, class _L2, class _R2>
    inline
    bf16_t
    eval(const expr<op::sub<bf16_t>,
         expr<op::mul<bf16_t>, _L1, _R1>,
         expr<op::mul<bf16_t>, _L2, _R2> >& e) {
#if 1
        return op::fnma<bf16_t>::v(eval(e._r._l),
                                  eval(e._r._r),
                                  eval(e._l));
#else
        return op::fms<bf16_t>::v(eval(e._l._l),
                                 eval(e._l._r),
                                 eval(e._r));
#endif
    }

    // evaluation of
    // a + -b = a - b
    template <class _L, class _R>
    inline
    bf16_t
    eval(const expr<op::add<bf16_t>,
         _L,
         expr<op::neg<bf16_t>, _R, void> >& e) {
        return op::sub<bf16_t>::v(eval(e._l),
                                 eval(e._r._l));
    }

    // evaluation of
    // -a + b = b - a
    template <class _L, class _R>
    inline
    bf16_t
    eval(const expr<op::add<bf16_t>,
         expr<op::neg<bf16_t>, _L, void>,
         _R>& e) {
        return op::sub<bf16_t>::v(eval(e._r._l),
                                 eval(e._l));
    }

    // evaluation of
    // a - -b = a + b
    template <typename _T, std::size_t _N,
              class _L, class _R>
    inline
    bf16_t
    eval(const expr<op::sub<bf16_t>,
         _L,
         expr<op::neg<bf16_t>, _R, void> >& e) {
        return op::add<bf16_t>::v(eval(e._l),
                                 eval(e._r._l));
    }

    constexpr
    bool operator<(const bf16_t& a, const bf16_t& b);
    constexpr
    bool operator<=(const bf16_t& a, const bf16_t& b);
    constexpr
    bool operator==(const bf16_t& a, const bf16_t& b);
    constexpr
    bool operator!=(const bf16_t& a, const bf16_t& b);
    constexpr
    bool operator>=(const bf16_t& a, const bf16_t& b);
    constexpr
    bool operator>(const bf16_t& a, const bf16_t& b);

    constexpr
    const bf16_t& operator+(const bf16_t& a);

    constexpr
    bf16_t operator-(const bf16_t& v);

    // unary minus: expr
    template <template <typename _T1> class _OP,
              typename _L, typename _R>
    expr<op::neg<bf16_t>,
         expr<_OP<bf16_t>, _L, _R>, void>
    operator-(const expr<_OP<bf16_t>, _L, _R>& r);

    // add operator: s, s
    expr<op::add<bf16_t>, bf16_t, bf16_t >
    operator+(const bf16_t& a, const bf16_t& b);
    // add operator: s, expr
    template <template <typename _T1> class _OP,
              class _L, class _R>
    expr<op::add<bf16_t>, bf16_t, expr<_OP<bf16_t>, _L, _R> >
    operator+(const bf16_t& a,
              const expr<_OP<bf16_t>, _L, _R>& b);
    // add operator: expr, s
    template <template <typename _T1> class _OP,
              class _L, class _R>
    expr<op::add<bf16_t>, expr<_OP<bf16_t>, _L, _R>, bf16_t>
    operator+(const expr<_OP<bf16_t>, _L, _R>& a,
              const bf16_t& b);
    // add operator: expr, expr
    template <template <typename _T1> class _OP1,
              class _L1, class _R1,
              template <typename _T2> class _OP2,
              class _L2, class _R2>
    expr<op::add<bf16_t>,
         expr<_OP1<bf16_t>, _L1, _R1>,
         expr<_OP2<bf16_t>, _L2, _R2> >
    operator+(const expr<_OP1<bf16_t>, _L1, _R1>& a,
              const expr<_OP2<bf16_t>, _L2, _R2>& b);
    // self add operator: s, s
    bf16_t&
    operator+=(bf16_t& a,
               const bf16_t& b);
    // self add operator: s, expr
    template <template <typename _T1> class _OP,
              class _L, class _R>
    bf16_t&
    operator+=(bf16_t& a,
               const expr<_OP<bf16_t>, _L, _R>& b);

    // sub operator: s, s
    expr<op::sub<bf16_t>, bf16_t, bf16_t >
    operator-(const bf16_t& a, const bf16_t& b);
    // sub operator: s, expr
    template <template <typename _T1> class _OP,
              class _L, class _R>
    expr<op::sub<bf16_t>, bf16_t, expr<_OP<bf16_t>, _L, _R> >
    operator-(const bf16_t& a,
              const expr<_OP<bf16_t>, _L, _R>& b);
    // sub operator: expr, s
    template <template <typename _T1> class _OP,
              class _L, class _R>
    expr<op::sub<bf16_t>, expr<_OP<bf16_t>, _L, _R>, bf16_t>
    operator-(const expr<_OP<bf16_t>, _L, _R>& a,
              const bf16_t& b);
    // sub operator: expr, expr
    template <template <typename _T1> class _OP1,
              class _L1, class _R1,
              template <typename _T2> class _OP2,
              class _L2, class _R2>
    expr<op::sub<bf16_t>,
         expr<_OP1<bf16_t>, _L1, _R1>,
         expr<_OP2<bf16_t>, _L2, _R2> >
    operator-(const expr<_OP1<bf16_t>, _L1, _R1>& a,
              const expr<_OP2<bf16_t>, _L2, _R2>& b);
    // self sub operator: s, s
    bf16_t&
    operator-=(bf16_t& a,
               const bf16_t& b);
    // self sub operator: s, expr
    template <template <typename _T1> class _OP,
              class _L, class _R>
    bf16_t&
    operator-=(bf16_t& a,
               const expr<_OP<bf16_t>, _L, _R>& b);


    // mul operator: s, s
    expr<op::mul<bf16_t>, bf16_t, bf16_t >
    operator*(const bf16_t& a, const bf16_t& b);
    // mul operator: s, expr
    template <template <typename _T1> class _OP,
              class _L, class _R>
    expr<op::mul<bf16_t>, bf16_t, expr<_OP<bf16_t>, _L, _R> >
    operator*(const bf16_t& a,
              const expr<_OP<bf16_t>, _L, _R>& b);
    // mul operator: expr, s
    template <template <typename _T1> class _OP,
              class _L, class _R>
    expr<op::mul<bf16_t>, expr<_OP<bf16_t>, _L, _R>, bf16_t>
    operator*(const expr<_OP<bf16_t>, _L, _R>& a,
              const bf16_t& b);
    // mul operator: expr, expr
    template <template <typename _T1> class _OP1,
              class _L1, class _R1,
              template <typename _T2> class _OP2,
              class _L2, class _R2>
    expr<op::mul<bf16_t>,
         expr<_OP1<bf16_t>, _L1, _R1>,
         expr<_OP2<bf16_t>, _L2, _R2> >
    operator*(const expr<_OP1<bf16_t>, _L1, _R1>& a,
              const expr<_OP2<bf16_t>, _L2, _R2>& b);
    // self mul operator: s, s
    bf16_t&
    operator*=(bf16_t& a,
               const bf16_t& b);
    // self mul operator: s, expr
    template <template <typename _T1> class _OP,
              class _L, class _R>
    bf16_t&
    operator*=(bf16_t& a,
               const expr<_OP<bf16_t>, _L, _R>& b);

    // div operator: s, s
    expr<op::div<bf16_t>, bf16_t, bf16_t >
    operator/(const bf16_t& a, const bf16_t& b);
    // div operator: s, expr
    template <template <typename _T1> class _OP,
              class _L, class _R>
    expr<op::div<bf16_t>, bf16_t, expr<_OP<bf16_t>, _L, _R> >
    operator/(const bf16_t& a,
              const expr<_OP<bf16_t>, _L, _R>& b);
    // div operator: expr, s
    template <template <typename _T1> class _OP,
              class _L, class _R>
    expr<op::div<bf16_t>, expr<_OP<bf16_t>, _L, _R>, bf16_t>
    operator/(const expr<_OP<bf16_t>, _L, _R>& a,
              const bf16_t& b);
    // div operator: expr, expr
    template <template <typename _T1> class _OP1,
              class _L1, class _R1,
              template <typename _T2> class _OP2,
              class _L2, class _R2>
    expr<op::div<bf16_t>,
         expr<_OP1<bf16_t>, _L1, _R1>,
         expr<_OP2<bf16_t>, _L2, _R2> >
    operator/(const expr<_OP1<bf16_t>, _L1, _R1>& a,
              const expr<_OP2<bf16_t>, _L2, _R2>& b);
    // self div operator: s, s
    bf16_t&
    operator/=(bf16_t& a,
               const bf16_t& b);
    // self div operator: s, expr
    template <template <typename _T1> class _OP,
              class _L, class _R>
    bf16_t&
    operator/=(bf16_t& a,
               const expr<_OP<bf16_t>, _L, _R>& b);

    bf16_t fma(const bf16_t& a, const bf16_t& b, const bf16_t& c);

    bf16_t rint(const bf16_t& v);
    bf16_t floor(const bf16_t& v);
    bf16_t ceil(const bf16_t& v);
    bf16_t trunc(const bf16_t& v);

    bf16_t sqrt(const bf16_t& v);
    bf16_t cbrt(const bf16_t& v);

    bf16_t hypot(const bf16_t& a, const bf16_t& b);

    bf16_t exp(const bf16_t& v);
    bf16_t expm1(const bf16_t& v);
    bf16_t exp2(const bf16_t& v);
    bf16_t sinh(const bf16_t& v);
    bf16_t cosh(const bf16_t& v);
    bf16_t tanh(const bf16_t& v);
    bf16_t log(const bf16_t& v);
    bf16_t log2(const bf16_t& v);
    bf16_t log10(const bf16_t& v);
    bf16_t log1p(const bf16_t& v);
    bf16_t pow(const bf16_t& a, const bf16_t& b);

    bf16_t sin(const bf16_t& v);
    bf16_t cos(const bf16_t& v);
    bf16_t tan(const bf16_t& v);

    bf16_t asin(const bf16_t& v);
    bf16_t acos(const bf16_t& v);
    bf16_t atan(const bf16_t& v);
    bf16_t atan2(const bf16_t& v, const bf16_t& w);

    bf16_t asinh(const bf16_t& v);
    bf16_t acosh(const bf16_t& v);
    bf16_t atanh(const bf16_t& v);

    bf16_t erf(const bf16_t& v);
    bf16_t erfc(const bf16_t& v);

    bf16_t tgamma(const bf16_t& v);
    bf16_t j0(const bf16_t& v);
    bf16_t y0(const bf16_t& v);
    bf16_t j1(const bf16_t& v);
    bf16_t y1(const bf16_t& v);

    std::ostream& operator<<(std::ostream& s, const bf16_t& v);
    std::istream& operator>>(std::istream& s, bf16_t& v);
#endif // (__USE_STDCPP_BFLOAT16_T__>0)

    template <>
    struct is_floating_point<bf16_t> : public std::true_type {};

    template <>
    struct is_signed<bf16_t> : public std::true_type {};

    // use a user defined operator to avoid overriding bf16
    constexpr
    bf16_t operator ""_bf16(long double);

    bool isnan(const bf16_t& v);
    bool isinf(const bf16_t& v);
    bf16_t abs(const bf16_t& v);
    bool signbit(const bf16_t& v);

    // math functions for bf16_t are missing
    bf16_t
    copysign(bf16_t a, bf16_t b);

    bf16_t
    nextafter(bf16_t a, bf16_t b);

    bf16_t frexp(bf16_t x, int* e);
    bf16_t ldexp(bf16_t x, int e);
    int16_t ilogb(bf16_t x);
}

#if (__USE_STDCPP_BFLOAT16_T__==0)

constexpr
inline
bool cftal::operator<(const bf16_t& a, const bf16_t& b)
{
    return float(a) < float(b);
}

constexpr
inline
bool cftal::operator<=(const bf16_t& a, const bf16_t& b)
{
    return float(a) <= float(b);
}

constexpr
inline
bool cftal::operator==(const bf16_t& a, const bf16_t& b)
{
    return float(a) == float(b);
}

constexpr
inline
bool cftal::operator!=(const bf16_t& a, const bf16_t& b)
{
    return float(a) != float(b);
}

constexpr
inline
bool cftal::operator>=(const bf16_t& a, const bf16_t& b)
{
    return float(a) >= float(b);
}

constexpr
inline
bool cftal::operator>(const bf16_t& a, const bf16_t& b)
{
    return float(a) > float(b);
}

constexpr
inline
const cftal::bf16_t&
cftal::operator+(const bf16_t& v)
{
    return v;
}

constexpr
inline
cftal::bf16_t
cftal::operator-(const bf16_t& v)
{
    mf_bf16_t t=read_bits(v) ^ sign_f32_msk::v.s16h();
    return bf16_t::cvt_from_rep(t);
}

template <template <typename _T1> class _OP,
          typename _L, typename _R>
cftal::expr<cftal::op:: neg<cftal::bf16_t>,
            cftal::expr<_OP<cftal::bf16_t>, _L, _R>,
            void>
cftal::operator-(const expr<_OP<bf16_t>, _L, _R>& v)
{
    return expr<op:: neg<bf16_t>,
                expr<_OP<bf16_t>, _L, _R>,
                void>(v);
}

inline
cftal::expr<cftal::op::add <cftal::bf16_t>,
            cftal::bf16_t,
            cftal::bf16_t >
cftal::operator+(const bf16_t& a, const bf16_t& b)
{
    return expr<op:: add<bf16_t>,
                bf16_t,
                bf16_t >(a, b);
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::add <cftal::bf16_t>,
            cftal::bf16_t,
            cftal::expr<_OP<cftal::bf16_t>, _L, _R> >
cftal::operator+(const bf16_t& a,
                 const expr<_OP<bf16_t>, _L, _R>& b)
{
    return expr<op::add<bf16_t>,
                bf16_t,
                expr<_OP<bf16_t>, _L, _R> >(a, b);
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::add <cftal::bf16_t>,
            cftal::expr<_OP<cftal::bf16_t>, _L, _R>,
            cftal::bf16_t >
cftal::operator+(const expr<_OP<bf16_t>, _L, _R>& a,
                 const bf16_t& b)
{
    return expr<op::add<bf16_t>,
                expr<_OP<bf16_t>, _L, _R>,
                bf16_t >(a, b);
}

template <template <typename _T1> class _OP1,
          class _L1, class _R1,
          template <typename _T2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::add <cftal::bf16_t>,
            cftal::expr<_OP1<cftal::bf16_t>, _L1, _R1>,
            cftal::expr<_OP2<cftal::bf16_t>, _L2, _R2> >
cftal::operator+(const expr<_OP1<bf16_t>, _L1, _R1>& a,
                 const expr<_OP2<bf16_t>, _L2, _R2>& b)
{
    return expr<op::add<bf16_t>,
                expr<_OP1<bf16_t>, _L1, _R1>,
                expr<_OP2<bf16_t>, _L2, _R2> >(a, b);
}

inline
cftal::bf16_t&
cftal::operator+=(bf16_t& a,
                  const bf16_t& b)
{
    a = a + b;
    return a;
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::bf16_t&
cftal::operator+=(bf16_t& a,
                  const expr<_OP<bf16_t>, _L, _R>& b)
{
    a = a + b;
    return a;
}

inline
cftal::expr<cftal::op::sub <cftal::bf16_t>,
            cftal::bf16_t,
            cftal::bf16_t >
cftal::operator-(const bf16_t& a, const bf16_t& b)
{
    return expr<op:: sub<bf16_t>,
                bf16_t,
                bf16_t >(a, b);
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::sub <cftal::bf16_t>,
            cftal::bf16_t,
            cftal::expr<_OP<cftal::bf16_t>, _L, _R> >
cftal::operator-(const bf16_t& a,
                 const expr<_OP<bf16_t>, _L, _R>& b)
{
    return expr<op::sub<bf16_t>,
                bf16_t,
                expr<_OP<bf16_t>, _L, _R> >(a, b);
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::sub <cftal::bf16_t>,
            cftal::expr<_OP<cftal::bf16_t>, _L, _R>,
            cftal::bf16_t >
cftal::operator-(const expr<_OP<bf16_t>, _L, _R>& a,
                 const bf16_t& b)
{
    return expr<op::sub<bf16_t>,
                expr<_OP<bf16_t>, _L, _R>,
                bf16_t >(a, b);
}

template <template <typename _T1> class _OP1,
          class _L1, class _R1,
          template <typename _T2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::sub <cftal::bf16_t>,
            cftal::expr<_OP1<cftal::bf16_t>, _L1, _R1>,
            cftal::expr<_OP2<cftal::bf16_t>, _L2, _R2> >
cftal::operator-(const expr<_OP1<bf16_t>, _L1, _R1>& a,
                 const expr<_OP2<bf16_t>, _L2, _R2>& b)
{
    return expr<op::sub<bf16_t>,
                expr<_OP1<bf16_t>, _L1, _R1>,
                expr<_OP2<bf16_t>, _L2, _R2> >(a, b);
}

inline
cftal::bf16_t&
cftal::operator-=(bf16_t& a,
                  const bf16_t& b)
{
    a = a - b;
    return a;
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::bf16_t&
cftal::operator-=(bf16_t& a,
                  const expr<_OP<bf16_t>, _L, _R>& b)
{
    a = a - b;
    return a;
}

inline
cftal::expr<cftal::op::mul <cftal::bf16_t>,
            cftal::bf16_t,
            cftal::bf16_t >
cftal::operator*(const bf16_t& a, const bf16_t& b)
{
    return expr<op:: mul<bf16_t>,
                bf16_t,
                bf16_t >(a, b);
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::mul <cftal::bf16_t>,
            cftal::bf16_t,
            cftal::expr<_OP<cftal::bf16_t>, _L, _R> >
cftal::operator*(const bf16_t& a,
                 const expr<_OP<bf16_t>, _L, _R>& b)
{
    return expr<op::mul<bf16_t>,
                bf16_t,
                expr<_OP<bf16_t>, _L, _R> >(a, b);
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::mul <cftal::bf16_t>,
            cftal::expr<_OP<cftal::bf16_t>, _L, _R>,
            cftal::bf16_t >
cftal::operator*(const expr<_OP<bf16_t>, _L, _R>& a,
                 const bf16_t& b)
{
    return expr<op::mul<bf16_t>,
                expr<_OP<bf16_t>, _L, _R>,
                bf16_t >(a, b);
}

template <template <typename _T1> class _OP1,
          class _L1, class _R1,
          template <typename _T2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::mul <cftal::bf16_t>,
            cftal::expr<_OP1<cftal::bf16_t>, _L1, _R1>,
            cftal::expr<_OP2<cftal::bf16_t>, _L2, _R2> >
cftal::operator*(const expr<_OP1<bf16_t>, _L1, _R1>& a,
                 const expr<_OP2<bf16_t>, _L2, _R2>& b)
{
    return expr<op::mul<bf16_t>,
                expr<_OP1<bf16_t>, _L1, _R1>,
                expr<_OP2<bf16_t>, _L2, _R2> >(a, b);
}

inline
cftal::bf16_t&
cftal::operator*=(bf16_t& a,
                  const bf16_t& b)
{
    a = a * b;
    return a;
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::bf16_t&
cftal::operator*=(bf16_t& a,
                  const expr<_OP<bf16_t>, _L, _R>& b)
{
    a = a * b;
    return a;
}

inline
cftal::expr<cftal::op::div <cftal::bf16_t>,
            cftal::bf16_t,
            cftal::bf16_t >
cftal::operator/(const bf16_t& a, const bf16_t& b)
{
    return expr<op:: div<bf16_t>,
                bf16_t,
                bf16_t >(a, b);
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::div <cftal::bf16_t>,
            cftal::bf16_t,
            cftal::expr<_OP<cftal::bf16_t>, _L, _R> >
cftal::operator/(const bf16_t& a,
                 const expr<_OP<bf16_t>, _L, _R>& b)
{
    return expr<op::div<bf16_t>,
                bf16_t,
                expr<_OP<bf16_t>, _L, _R> >(a, b);
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::div <cftal::bf16_t>,
            cftal::expr<_OP<cftal::bf16_t>, _L, _R>,
            cftal::bf16_t >
cftal::operator/(const expr<_OP<bf16_t>, _L, _R>& a,
                 const bf16_t& b)
{
    return expr<op::div<bf16_t>,
                expr<_OP<bf16_t>, _L, _R>,
                bf16_t >(a, b);
}

template <template <typename _T1> class _OP1,
          class _L1, class _R1,
          template <typename _T2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::div <cftal::bf16_t>,
            cftal::expr<_OP1<cftal::bf16_t>, _L1, _R1>,
            cftal::expr<_OP2<cftal::bf16_t>, _L2, _R2> >
cftal::operator/(const expr<_OP1<bf16_t>, _L1, _R1>& a,
                 const expr<_OP2<bf16_t>, _L2, _R2>& b)
{
    return expr<op::div<bf16_t>,
                expr<_OP1<bf16_t>, _L1, _R1>,
                expr<_OP2<bf16_t>, _L2, _R2> >(a, b);
}

inline
cftal::bf16_t&
cftal::operator/=(bf16_t& a,
                  const bf16_t& b)
{
    a = a / b;
    return a;
}

template <template <typename _T1> class _OP,
          class _L, class _R>
cftal::bf16_t&
cftal::operator/=(bf16_t& a,
                  const expr<_OP<bf16_t>, _L, _R>& b)
{
    a = a / b;
    return a;
}

inline
cftal::bf16_t cftal::fma(const bf16_t& a, const bf16_t& b, const bf16_t& c)
{
    return bf16_t(float(a)*float(b)+float(c));
}

inline
cftal::bf16_t cftal::rint(const bf16_t& v)
{
    return bf16_t(std::rint(float(v)));
}

inline
cftal::bf16_t cftal::floor(const bf16_t& v)
{
    return bf16_t(std::floor(float(v)));
}

inline
cftal::bf16_t cftal::ceil(const bf16_t& v)
{
    return bf16_t(std::ceil(float(v)));
}

inline
cftal::bf16_t cftal::trunc(const bf16_t& v)
{
    return bf16_t(std::trunc(float(v)));
}

inline
cftal::bf16_t cftal::sqrt(const bf16_t& v)
{
    return bf16_t(std::sqrt(float(v)));
}

inline
cftal::bf16_t cftal::cbrt(const bf16_t& v)
{
    return bf16_t(std::cbrt(float(v)));
}

inline
cftal::bf16_t cftal::hypot(const bf16_t& x, const bf16_t& y)
{
    return bf16_t(std::hypot(float(x), float(y)));
}

inline
cftal::bf16_t cftal::exp(const bf16_t& v)
{
    return bf16_t(std::exp(float(v)));
}

inline
cftal::bf16_t cftal::expm1(const bf16_t& v)
{
    return bf16_t(std::expm1(float(v)));
}

inline
cftal::bf16_t cftal::exp2(const bf16_t& v)
{
    return bf16_t(std::exp2(float(v)));
}

inline
cftal::bf16_t cftal::sinh(const bf16_t& v)
{
    return bf16_t(std::sinh(float(v)));
}

inline
cftal::bf16_t cftal::cosh(const bf16_t& v)
{
    return bf16_t(std::cosh(float(v)));
}

inline
cftal::bf16_t cftal::tanh(const bf16_t& v)
{
    return bf16_t(std::tanh(float(v)));
}

inline
cftal::bf16_t cftal::log(const bf16_t& v)
{
    return bf16_t(std::log(float(v)));
}

inline
cftal::bf16_t cftal::log2(const bf16_t& v)
{
    return bf16_t(std::log2(float(v)));
}

inline
cftal::bf16_t cftal::log10(const bf16_t& v)
{
    return bf16_t(std::log10(float(v)));
}

inline
cftal::bf16_t cftal::log1p(const bf16_t& v)
{
    return bf16_t(std::log1p(float(v)));
}

inline
cftal::bf16_t cftal::pow(const bf16_t& a, const bf16_t& b)
{
    return bf16_t(std::pow(float(a), float(b)));
}

inline
cftal::bf16_t cftal::sin(const bf16_t& v)
{
    return bf16_t(std::sin(float(v)));
}

inline
cftal::bf16_t cftal::cos(const bf16_t& v)
{
    return bf16_t(std::cos(float(v)));
}

inline
cftal::bf16_t cftal::tan(const bf16_t& v)
{
    return bf16_t(std::tan(float(v)));
}

inline
cftal::bf16_t cftal::asin(const bf16_t& v)
{
    return bf16_t(std::asin(float(v)));
}

inline
cftal::bf16_t cftal::acos(const bf16_t& v)
{
    return bf16_t(std::acos(float(v)));
}

inline
cftal::bf16_t cftal::atan(const bf16_t& v)
{
    return bf16_t(std::atan(float(v)));
}

inline
cftal::bf16_t cftal::atan2(const bf16_t& a, const bf16_t& b)
{
    return bf16_t(std::atan2(float(a), float(b)));
}

inline
cftal::bf16_t cftal::asinh(const bf16_t& v)
{
    return bf16_t(std::asinh(float(v)));
}

inline
cftal::bf16_t cftal::acosh(const bf16_t& v)
{
    return bf16_t(std::acosh(float(v)));
}

inline
cftal::bf16_t cftal::atanh(const bf16_t& v)
{
    return bf16_t(std::atanh(float(v)));
}

inline
cftal::bf16_t cftal::erf(const bf16_t& v)
{
    return bf16_t(std::erf(float(v)));
}

inline
cftal::bf16_t cftal::erfc(const bf16_t& v)
{
    return bf16_t(std::erfc(float(v)));
}

inline
cftal::bf16_t cftal::tgamma(const bf16_t& v)
{
    return bf16_t(std::tgamma(float(v)));
}

inline
cftal::bf16_t cftal::j0(const bf16_t& v)
{
    return bf16_t(::j0f(float(v)));
}

inline
cftal::bf16_t cftal::y0(const bf16_t& v)
{
    return bf16_t(::y0f(float(v)));
}

inline
cftal::bf16_t cftal::j1(const bf16_t& v)
{
    return bf16_t(::j1f(float(v)));
}

inline
cftal::bf16_t cftal::y1(const bf16_t& v)
{
    return bf16_t(::y1f(float(v)));
}

inline
std::ostream& cftal::operator<<(std::ostream& s, const bf16_t& v)
{
    float fv(v);
    s << fv;
    return s;
}

inline
std::istream& cftal::operator>>(std::istream& s, bf16_t& v)
{
    float fv;
    s >> fv;
    v = bf16_t(fv);
    return s;
}
#endif // __USE_STDCPP_BFLOAT16_T__==0

inline
constexpr
cftal::bf16_t cftal::operator ""_bf16(long double d)
{
#if __USE_STDCPP_BFLOAT16_T__>0
    return bf16_t(static_cast<float>(d));
#else
    return bf16_t::cvt_from_rep(impl::_cvt_f32_to_bf16(static_cast<float>(d)));
#endif
}

inline
bool cftal::isnan(const bf16_t& v)
{
    const mf_bf16_t& vi= read_bits(v);
    mf_bf16_t abs_vi= vi & not_sign_f32_msk::v.s16h();
    return abs_vi > exp_f32_msk::v.s16h();
}

inline
bool cftal::isinf(const bf16_t& v)
{
    const mf_bf16_t& vi= read_bits(v);
    mf_bf16_t abs_vi= vi & not_sign_f32_msk::v.s16h();
    return abs_vi == exp_f32_msk::v.s16h();
}

inline
cftal::bf16_t cftal::abs(const bf16_t& v)
{
    const mf_bf16_t& vi= read_bits(v);
    mf_bf16_t abs_vi= vi & not_sign_f32_msk::v.s16h();
    return as<bf16_t>(abs_vi);
}

inline
bool cftal::signbit(const bf16_t& v)
{
    const mf_bf16_t& vi= read_bits(v);
    return (vi & sign_f32_msk::v.s16h()) == sign_f32_msk::v.s16h();
}

inline
cftal::bf16_t
cftal::copysign(bf16_t x, bf16_t y)
{
    const uint16_t abs_msk=not_sign_f32_msk::v.u16h();
    uint16_t abs_x=read_bits(x) & abs_msk;
    const uint16_t sgn_msk=sign_f32_msk::v.u16h();
    uint16_t sgn_y=read_bits(y) & sgn_msk;
    uint16_t r= abs_x | sgn_y;
    return as<bf16_t>(r);
}

#if (__USE_STDCPP_BFLOAT16_T__==0)
namespace std {

    template <>
    struct numeric_limits<cftal::bf16_t> {
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
        static const bool is_iec559 =
            has_infinity &&
            has_quiet_NaN &&
            has_denorm == denorm_present;
        static const bool is_bounded = false;
        static const bool is_modulo = false;
        static const int digits = 8;
        static const int digits10 = 2;
        static const int max_digits10 = 4;
        static const int radix = 2;
        static const int min_exponent = -125;
        static const int min_exponent10 = -37;
        static const int max_exponent = 128;
        static const int max_exponent10 = 38;
        static const bool traps = true;
        static const bool tinyness_before = false;

        constexpr
        static cftal::bf16_t (min)() {
            return cftal::bf16_t::cvt_from_rep(0x0800);
        }
        constexpr
        static cftal::bf16_t lowest() {
            return cftal::bf16_t::cvt_from_rep(0xbf7f);
        }
        constexpr
        static cftal::bf16_t (max)() {
            return cftal::bf16_t::cvt_from_rep(0x7f7f);
        }
        constexpr
        static cftal::bf16_t epsilon() {
            return cftal::bf16_t::cvt_from_rep(0x3c00);
        }
        static cftal::bf16_t round_error() {
            return cftal::bf16_t(float(0.5));
        }
        constexpr
        static cftal::bf16_t infinity() {
            return cftal::bf16_t::cvt_from_rep(0x7f80);
        }
        constexpr
        static cftal::bf16_t quiet_NaN() {
            // highest fraction bit set otherwise arbitrary
            return cftal::bf16_t::cvt_from_rep(0x7fc0);
        }
        constexpr
        static cftal::bf16_t signaling_NaN() {
            // highest fraction bit not set, at least one other
            // fraction bit set
            return cftal::bf16_t::cvt_from_rep(0x7fa0);
        }
        constexpr
        static cftal::bf16_t denorm_min() {
#if __CFTAL_CFG_FLUSH_BFLOAT16_TO_ZERO>0
            return min();
#else
            return cftal::bf16_t::cvt_from_rep(0x0001);
#endif
        }
    };
}
#endif // __USE_STDCPP_BFLOAT16_T__ == 0

// keep this function after the specialization of std::numeric_limits<bf16_t>
inline
cftal::bf16_t
cftal::nextafter(bf16_t xc, bf16_t yc)
{
    uint16_t ux=read_bits(xc);
    uint16_t uy=read_bits(yc);
    uint16_t ax= ux & not_sign_f32_msk::v.u16h();
    uint16_t ay= uy & not_sign_f32_msk::v.u16h();
    uint16_t ux_inc= ux + 1;
    uint16_t ux_dec= ux - 1;
    // decrement required if ax > ay or (ux^uy & sgn) != 0
    bool opp_sgn=
        uint16_t((ux^uy) & sign_f32_msk::v.u16h()) != uint16_t(0);
    uint16_t r= ((ax > ay) | opp_sgn) ? ux_dec : ux_inc;
    uint16_t r0= ay == 0 ? uy : (uy & sign_f32_msk::v.u16h()) | 1;
    r = ax == 0 ? r0 : r;
    r = ux == uy ? uy : r;
    // bf16_t rf= bf16_t::cvt_from_rep(r);
#if __CFTAL_CFG_FLUSH_BFLOAT16_TO_ZERO>0
    // assumption: no subnormal inputs in xc
    // r == max subnormal --> min normal down --> 0
    r = (r==0x007f) ? 0x0000 : r;
    // r == min subnormal --> zero up --> min normal
    r = (r==0x0001) ? 0x0080 : r;
    // r == -min subnormal --> zero down --> -min normal
    r = (r==0x8001) ? 0x8080 : r;
    // r == -max subnormal --> -min normal up --> -0
    r = (r==0x807f) ? 0x8000 : r;
#endif
    bf16_t rf=as<bf16_t>(r);
    rf = (isnan(xc) || isnan(yc)) ? std::numeric_limits<bf16_t>::quiet_NaN() : rf;
    return rf;
}

inline
cftal::bf16_t
cftal::frexp(bf16_t x, int* e)
{
    float fx=static_cast<float>(x);
    using std::frexp;
    float m=frexp(fx, e);
    return bf16_t(m);
}

inline
cftal::bf16_t
cftal::ldexp(bf16_t x, int e)
{
    float fx=static_cast<float>(x);
    using std::ldexp;
    float r=ldexp(fx, e);
    return bf16_t(r);
}

inline
cftal::int16_t
cftal::ilogb(bf16_t x)
{
    float fx=static_cast<float>(x);
    using std::ilogb;
    int16_t r=ilogb(fx);
    if (isinf(x))
        r=std::numeric_limits<int16_t>::max();
    return r;
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_BF16_T_H__
