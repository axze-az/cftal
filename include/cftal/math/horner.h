//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_MATH_HORNER_H__)
#define __CFTAL_MATH_HORNER_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <stdexcept>
#include <iterator>

namespace cftal {
    namespace math {
        // arrays and containers contain c_n in C[0]
        template <typename _X, typename _C1, typename _C0>
        _X
        horner(_X x, _C1 c1, _C0 c0);

        template <typename _X,
                  typename _CN, typename _CNM1, typename ... _CS>
        _X
        horner(_X x, _CN cn, _CNM1 cnm1, _CS... cs);

        template <typename _X, typename _C>
        _X
        horner(_X x, const _C& c);

        template <typename _X, typename _C, std::size_t _N>
        _X
        horner(_X x, const _C (&a)[_N]);

        template <typename _F, typename _C, std::size_t _N>
        d_real<_F>
        horner(d_real<_F> x, const d_real<_C> (&a)[_N]);

        template <typename _F, typename _C, std::size_t _N>
        _F
        horner(_F x, const d_real<_C> (&a)[_N]);

        // polynomial with c1 = 1.0
        template <typename _X, typename _C0>
        _X
        horner1(_X x, _C0 c0);

        // polynomial with cn = 1.0
        template <typename _X,
                  typename _CNM1, typename ... _CS>
        _X
        horner1(_X x, _CNM1 cnm1, _CS... cs);


        template <typename _X, typename _C1, typename _C0>
        void
        horner_n4(_X& y0, _X& y1, _X& y2, _X& y3,
                  _X x0, _X x1, _X x2, _X x3,
                  _C1 c1_0, _C1 c1_1, _C1 c1_2, _C1 c1_3,
                  _C0 c0_0, _C0 c0_1, _C0 c0_2, _C0 c0_3);

        template <typename _X,
                  typename _CN, typename _CNM1, typename ... _CS>
        void
        horner_n4(_X& y0, _X& y1, _X& y2, _X& y3,
                  _X x0, _X x1, _X x2, _X x3,
                  _CN cn_0, _CN cn_1, _CN cn_2, _CN cn_3,
                  _CNM1 cnm1_0, _CNM1 cnm1_1, _CNM1 cnm1_2, _CNM1 cnm1_3,
                  _CS... cs);

        // error free transformation of evaluation of polynomials
        // setup step, assumes nothing about |x*c1| and |c0|
        template <typename _X, typename _C1, typename _C0>
        void
        eft_horner_s0(_X& y, _X& ye, _X x, _C1 c1, _C0 c0);

        // error free transformation of evaluation of polynomials
        // next step, assumes nothing about |x*c1| and |c0|
        template <typename _X, typename _C1, typename _C0>
        void
        eft_horner_si(_X& y, _X& ye, _X x, _C1 c1h, _C1 c1l, _C0 c0);

        // error free transformation of evaluation of polynomials
        // recursive next steps,
        // assumes nothing about |x*c_N| and |c_N-1|
        template <typename _X, typename _CN, typename _CNM1,
                  typename ... _CS>
        void
        eft_horner_si(_X& y, _X& ye, _X x, _CN cnh, _CN cnl, _CNM1 cnm1,
                      _CS... cs);

        // error free transformation of evaluation of polynomials
        // overload for degree 1
        // assumes nothing about |x*c_1| and |c_0|
        template <typename _X, typename _CN, typename _CNM1>
        void
        eft_horner(_X& y, _X& ye, _X x, _CN c1, _CNM1 c0);

        // error free transformation of evaluation of polynomials
        // assumes nothing about x*c_N and c_N-1
        template <typename _X, typename _CN, typename _CNM1,
                  typename ... _CS>
        void
        eft_horner(_X& y, _X& ye, _X x, _CN cn, _CNM1 cnm1,
                   _CS... cs);

        // error free transformation of evaluation of polynomials
        // setup step, assumes |x*c1| < |c0|
        template <typename _X, typename _C1, typename _C0>
        void
        eft_quick_horner_s0(_X& y, _X& ye, _X x, _C1 c1, _C0 c0);

        // error free transformation of evaluation of polynomials
        // next step, assumes |x*c1| < |c0|
        template <typename _X, typename _C1, typename _C0>
        void
        eft_quick_horner_si(_X& y, _X& ye, _X x, _C1 c1h, _C1 c1l, _C0 c0);

        // error free transformation of evaluation of polynomials
        // recursive next steps,
        // assumes |x*c_N| < |c_N-1|
        template <typename _X, typename _CN, typename _CNM1,
                  typename ... _CS>
        void
        eft_quick_horner_si(_X& y, _X& ye, _X x, _CN cnh, _CN cnl,
                            _CNM1 cnm1, _CS... cs);

        // error free transformation of evaluation of polynomials
        // overload for degree 1
        // assumes  |x*c_1| < |c_0|
        template <typename _X, typename _CN, typename _CNM1>
        void
        eft_quick_horner(_X& y, _X& ye, _X x, _CN c1, _CNM1 c0);

        // error free transformation of evaluation of polynomials
        // assumes |x*c_N| < |c_N-1|, |x*c_N_1| < |c_N-2| ..
        template <typename _X, typename _CN, typename _CNM1,
                  typename ... _CS>
        void
        eft_quick_horner(_X& y, _X& ye, _X x, _CN cn, _CNM1 cnm1,
                         _CS... cs);
    }
}

template <typename _X, typename _C1, typename _C0>
_X
cftal::math::horner(_X x, _C1 c1, _C0 c0)
{
    return x*c1 + c0;
}

template <typename _X,
          typename _CN, typename _CNM1, typename ... _CS>
_X
cftal::math::horner(_X x, _CN cn, _CNM1 cnm1, _CS... cs)
{
    _X t = horner(x, cn, cnm1);
    _X r = horner(x, t, cs...);
    return r;
}

template <typename _X, typename _C>
_X
cftal::math::horner(_X x, const _C& c)
{
    auto b=std::cbegin(c);
    auto e=std::cend(c);
    if (b==e) {
        throw std::invalid_argument("cftal::math::horner(x, C)");
    }
    _X r= (*b);
    ++b;
    while (b != e) {
        r = horner(x, r, *b);
        ++b;
    }
    return r;
}

template <typename _X, typename _C, std::size_t _N>
_X
cftal::math::horner(_X x, const _C (&a)[_N])
{
    static_assert(_N > 0, "invalid call to horner(x, array)");
    _X r= _X(a[0]);
    for (std::size_t i=1; i<_N; ++i) {
        r= horner(x, r, a[i]);
    }
    return r;
}

template <typename _F, typename _C, std::size_t _N>
cftal::d_real<_F>
cftal::math::horner(d_real<_F> x, const d_real<_C> (&a)[_N])
{
    static_assert(
        _N > 0,
        "invalid call to horner(d_real<_F>, d_real<_C>(&a)[])");
    d_real<_F> r=d_real<_F>(a[0]);
    for (std::size_t i=1; i<_N; ++i) {
        r=horner(x, r, d_real<_F>(a[i] ));
    }
    return r;
}

template <typename _F, typename _C, std::size_t _N>
_F
cftal::math::horner(_F x, const d_real<_C> (&a)[_N])
{
    static_assert(_N > 0, "invalid call to horner(_F, d_real<_C>(&a)[])");
    _F r= a[0].h();
    for (std::size_t i=1; i<_N; ++i) {
        r= horner(x, r, _F(a[i].h()));
    }
    return r;
}

// polynomial with c1 = 1.0
template <typename _X, typename _C0>
_X
cftal::math::horner1(_X x, _C0 c0)
{
    return x + c0;
}

// polynomial with cn = 1.0
template <typename _X,typename _CNM1, typename ... _CS>
_X
cftal::math::horner1(_X x, _CNM1 cnm1, _CS... cs)
{
    _X t = horner1(x, cnm1);
    _X r = horner(x, t, cs...);
    return r;
}

template <typename _X, typename _C1, typename _C0>
void
cftal::math::horner_n4(_X& y0, _X& y1, _X& y2, _X& y3,
                       _X x0, _X x1, _X x2, _X x3,
                       _C1 c1_0, _C1 c1_1, _C1 c1_2, _C1 c1_3,
                       _C0 c0_0, _C0 c0_1, _C0 c0_2, _C0 c0_3)
{
    y0 = horner(x0, c1_0, c0_0);
    y1 = horner(x1, c1_1, c0_1);
    y2 = horner(x2, c1_2, c0_2);
    y3 = horner(x3, c1_3, c0_3);
}

template <typename _X,
          typename _CN, typename _CNM1, typename ... _CS>
void
cftal::math::
horner_n4(_X& y0, _X& y1, _X& y2, _X& y3,
          _X x0, _X x1, _X x2, _X x3,
          _CN cn_0, _CN cn_1, _CN cn_2, _CN cn_3,
          _CNM1 cnm1_0, _CNM1 cnm1_1, _CNM1 cnm1_2, _CNM1 cnm1_3,
          _CS... cs)
{
    horner_n4(y0, y1, y2, y3, x0, x1, x2, x3,
              cn_0, cn_1, cn_2, cn_3,
              cnm1_0, cnm1_1, cnm1_2, cnm1_3);
    horner_n4(y0, y1, y2, y3, x0, x1, x2, x3,
              y0, y1, y2, y3, cs...);
}

template <typename _X, typename _C1, typename _C0>
void
cftal::math::eft_horner_s0(_X& y, _X& ye, _X x, _C1 c1, _C0 c0)
{
    using d_ops=cftal::impl::d_real_ops<_X, d_real_traits<_X>::fma>;
    _X p_i, o_i;
    // y = d_ops::two_prod(c1, x, p_i);
    // y = d_ops::two_sum(y, c0, o_i);
    d_ops::mul12(y, p_i, c1, x);
    d_ops::add12cond(y, o_i, c0, y);
    ye= (p_i + o_i);
}

template <typename _X, typename _C1, typename _C0>
void
cftal::math::eft_horner_si(_X& y, _X& ye, _X x, _C1 c1h, _C1 c1l, _C0 c0)
{
    using d_ops=cftal::impl::d_real_ops<_X, d_real_traits<_X>::fma>;
    _X p_i, o_i;
    // y = d_ops::two_prod(c1h, x, p_i);
    // y = d_ops::two_sum(y, c0, o_i);
    d_ops::mul12(y, p_i, c1h, x);
    d_ops::add12cond(y, o_i, c0, y);
    ye= c1l*x + (p_i + o_i);
}

template <typename _X,
          typename _CN, typename _CNM1, typename ... _CS>
void
cftal::math::
eft_horner_si(_X& y, _X& ye, _X x, _CN cnh, _CN cnl, _CNM1 cnm1, _CS ... cs)
{
    eft_horner_si(y, ye, x, cnh, cnl, cnm1);
    // const _X _y=y;
    // const _X _ye=ye;
    eft_horner_si(y, ye, x, y, ye, cs...);
}

template <typename _X, typename _CN, typename _CNM1>
void
cftal::math::
eft_horner(_X& y, _X& ye, _X x, _CN c1, _CNM1 c0)
{
    eft_horner_s0(y, ye, x, c1, c0);
}

template <typename _X,
          typename _CN, typename _CNM1, typename ... _CS>
void
cftal::math::
eft_horner(_X& y, _X& ye, _X x, _CN cn, _CNM1 cnm1, _CS ... cs)
{
    eft_horner_s0(y, ye, x, cn, cnm1);
    // const _X _y=y;
    // const _X _ye=ye;
    eft_horner_si(y, ye, x, y, ye, cs...);
}

template <typename _X, typename _C1, typename _C0>
void
cftal::math::
eft_quick_horner_s0(_X& y, _X& ye, _X x, _C1 c1, _C0 c0)
{
    using d_ops=cftal::impl::d_real_ops<_X, d_real_traits<_X>::fma>;
    _X p_i, o_i;
    // y = d_ops::two_prod(c1, x, p_i);
    // y = d_ops::two_sum(y, c0, o_i);
    d_ops::mul12(y, p_i, c1, x);
    d_ops::add12(y, o_i, c0, y);
    ye= (p_i + o_i);
}

template <typename _X, typename _C1, typename _C0>
void
cftal::math::
eft_quick_horner_si(_X& y, _X& ye, _X x, _C1 c1h, _C1 c1l, _C0 c0)
{
    using d_ops=cftal::impl::d_real_ops<_X, d_real_traits<_X>::fma>;
    _X p_i, o_i;
    // y = d_ops::two_prod(c1h, x, p_i);
    // y = d_ops::two_sum(y, c0, o_i);
    d_ops::mul12(y, p_i, c1h, x);
    d_ops::add12(y, o_i, c0, y);
    ye= c1l*x + (p_i + o_i);
}

template <typename _X,
          typename _CN, typename _CNM1, typename ... _CS>
void
cftal::math::
eft_quick_horner_si(_X& y, _X& ye, _X x, _CN cnh, _CN cnl,
                    _CNM1 cnm1, _CS ... cs)
{
    eft_quick_horner_si(y, ye, x, cnh, cnl, cnm1);
    // const _X _y=y;
    // const _X _ye=ye;
    eft_quick_horner_si(y, ye, x, y, ye, cs...);
}

template <typename _X, typename _CN, typename _CNM1>
void
cftal::math::
eft_quick_horner(_X& y, _X& ye, _X x, _CN c1, _CNM1 c0)
{
    eft_quick_horner_s0(y, ye, x, c1, c0);
}

template <typename _X,
          typename _CN, typename _CNM1, typename ... _CS>
void
cftal::math::
eft_quick_horner(_X& y, _X& ye, _X x, _CN cn, _CNM1 cnm1, _CS ... cs)
{
    eft_quick_horner_s0(y, ye, x, cn, cnm1);
    // const _X _y=y;
    // const _X _ye=ye;
    eft_quick_horner_si(y, ye, x, y, ye, cs...);
}

// local variables:
// mode: c++
// end:
#endif
