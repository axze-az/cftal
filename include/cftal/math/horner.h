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
        horner(const _X& x, const _C1& c1, const _C0& c0);

        template <typename _X,
                  typename _CN, typename _CNM1, typename ... _CS>
        _X
        horner(const _X& x, const _CN& cn, const _CNM1& cnm1, _CS... cs);

        // a_n in a[0]
        template <typename _X, typename _C>
        _X
        horner(const _X& x, const _C& c);

        // a_n in a[0]
        template <std::size_t _N, typename _X, typename _C>
        _X
        horner(const _X& x, const _C*);

        // a_n in a[0]
        template <typename _X, typename _C, std::size_t _N>
        _X
        horner(const _X& x, const _C (&a)[_N]);

        // a_n in a[0], x2 = x*x
        // computes the even and odd parts of the polynomial
        // in parallel
        template <std::size_t _N, typename _X, typename _C>
        _X
        horner2(const _X& x, const _X& x2, const _C* pa);

        // a_n in a[0],
        // computes the even and odd parts of the polynomial
        // in parallel
        template <std::size_t _N, typename _X, typename _C>
        _X
        horner2(const _X& x, const _C* pa);

        // a_n in a[0], x2 = x*x
        // computes the even and odd parts of the polynomial
        // in parallel
        template <typename _X, typename _C, std::size_t _N>
        _X
        horner2(const _X& x, const _X& x2, const _C (&a)[_N]);

        // a_n in a[0],
        // computes the even and odd parts of the polynomial
        // in parallel
        template <typename _X, typename _C, std::size_t _N>
        _X
        horner2(const _X& x, const _C (&a)[_N]);

        // a_n in a[0], x3 = x*x*x, computes 3 parts of the
        // polynomial in parallel
        template <std::size_t _N, typename _X, typename _C>
        _X
        horner3(const _X& x, const _X& x3, const _C* pa);

        // a_n in a[0], computes 3 parts of the
        // polynomial in parallel
        template <std::size_t _N, typename _X, typename _C>
        _X
        horner3(const _X& x, const _C* pa);

        // a_n in a[0], x3 = x*x*x, computes 3 parts of the
        // polynomial in parallel
        template <typename _X, typename _C, std::size_t _N>
        _X
        horner3(const _X& x, const _X& x3, const _C (&a)[_N]);

        // a_n in a[0], computes 3 parts of the
        // polynomial in parallel
        template <typename _X, typename _C, std::size_t _N>
        _X
        horner3(const _X& x, const _C (&a)[_N]);

        // a_n in a[0], x2=x*x, x4=x*x*x,
        // computes 4 parts of the polynomial in parallel
        template <std::size_t _N, typename _X, typename _C>
        _X
        horner4(const _X& x, const _X& x2, const _X& x4, const _C* pa);

        // a_n in a[0],
        // computes 4 parts of the polynomial in parallel
        template <std::size_t _N, typename _X, typename _C>
        _X
        horner4(const _X& x, const _C* pa);

        // a_n in a[0], x2=x*x, x4=x*x*x,
        // computes 4 parts of the polynomial in parallel
        template <typename _X, typename _C, std::size_t _N>
        _X
        horner4(const _X& x, const _X& x2, const _X& x4, const _C (&a)[_N]);

        // a_n in a[0],
        // computes 4 parts of the polynomial in parallel
        template <typename _X, typename _C, std::size_t _N>
        _X
        horner4(const _X& x, const _C (&a)[_N]);

        template <typename _F, typename _C, std::size_t _N>
        d_real<_F>
        horner(const d_real<_F>& x, const d_real<_C> (&a)[_N]);

        template <typename _F, typename _C, std::size_t _N>
        _F
        horner(const _F& x, const d_real<_C> (&a)[_N]);

        // polynomial with c1 = 1.0
        template <typename _X, typename _C0>
        _X
        horner1(const _X& x, const _C0& c0);

        // polynomial with cn = 1.0
        template <typename _X,
                  typename _CNM1, typename ... _CS>
        _X
        horner1(const _X& x, const _CNM1& cnm1, _CS... cs);

        // a_n in a[0], b_n in b[0]
        template <typename _X, typename _C, std::size_t _N>
        void
        horner_n2(_X& ya, _X& yb, const _X& x,
                  const _C (&a)[_N], const _C (&b)[_N]);

        // a_n in a[0], b_n in b[0]
        template <typename _X, typename _C, std::size_t _N>
        void
        horner2_n2(_X& ya, _X& yb, const _X& x, const _X& x2,
                   const _C (&a)[_N], const _C (&b)[_N]);

        // a_n in a[0], b_n in b[0], c_n in a[0], d_n in a[0]
        template <typename _X, typename _C, std::size_t _N>
        void
        horner_n4(_X& ya, _X& yb, _X& yc, _X& yd, const _X& x,
                  const _C (&a)[_N], const _C (&b)[_N],
                  const _C (&c)[_N], const _C (&d)[_N]);

        template <typename _X, typename _C1, typename _C0>
        void
        horner_n4(_X& y0, _X& y1, _X& y2, _X& y3,
                  const _X& x0, const _X& x1,
                  const _X& x2, const _X& x3,
                  const _C1& c1_0, const _C1& c1_1,
                  const _C1& c1_2, const _C1& c1_3,
                  const _C0& c0_0, const _C0& c0_1,
                  const _C0& c0_2, const _C0& c0_3);

        template <typename _X,
                  typename _CN, typename _CNM1, typename ... _CS>
        void
        horner_n4(_X& y0, _X& y1, _X& y2, _X& y3,
                  const _X& x0, const _X& x1, const _X& x2, const _X& x3,
                  const _CN& cn_0, const _CN& cn_1,
                  const _CN& cn_2, const _CN& cn_3,
                  const _CNM1& cnm1_0, const _CNM1& cnm1_1,
                  const _CNM1& cnm1_2, const _CNM1& cnm1_3,
                  _CS... cs);

        // compensated horner scheme
        // error free transformation of evaluation of polynomials
        // setup step, assumes nothing about |x*c1| and |c0|
        template <typename _X, typename _C1, typename _C0>
        void
        horner_comp_s0(_X& y, _X& ye,
                       const _X& x,
                       const _C1& c1, const _C0& c0);

        // compensated horner scheme
        // error free transformation of evaluation of polynomials
        // next step, assumes nothing about |x*c1| and |c0|
        template <typename _X, typename _C1, typename _C0>
        void
        horner_comp_si(_X& y, _X& ye,
                       const _X& x,
                       const _C1& c1h, const _C1& c1l, const _C0& c0);

        // compensated horner scheme
        // error free transformation of evaluation of polynomials
        // recursive next steps,
        // assumes nothing about |x*c_N| and |c_N-1|
        template <typename _X, typename _CN, typename _CNM1,
                  typename ... _CS>
        void
        horner_comp_si(_X& y, _X& ye,
                       const _X& x,
                       const _CN& cnh, const _CN& cnl, const _CNM1& cnm1,
                       _CS... cs);

        // compensated horner scheme
        // error free transformation of evaluation of polynomials
        // overload for degree 1
        // assumes nothing about |x*c_1| and |c_0|
        template <typename _X, typename _CN, typename _CNM1>
        void
        horner_comp(_X& y, _X& ye,
                    const _X& x,
                    const _CN& c1, const _CNM1& c0);

        // compensated horner scheme
        // error free transformation of evaluation of polynomials
        // assumes nothing about x*c_N and c_N-1
        template <typename _X, typename _CN, typename _CNM1,
                  typename ... _CS>
        void
        horner_comp(_X& y, _X& ye,
                    const _X& x,
                    const _CN& cn, const _CNM1& cnm1,
                    _CS... cs);

        // compensated horner scheme using a coefficient array
        // assumes nothing about the coefficients
        template <typename _X, typename _C, std::size_t _N>
        void
        horner_comp(_X& y, _X& ye,
                    const _X& x,
                    const _C (&a)[_N]);

        // compensated horner scheme using a coefficient array
        // return ((_x * (yi) + a[0])*x)+...)+a[_N-1]
        // assumes nothing about the coefficients
        template <typename _X, typename _C, std::size_t _N>
        void
        horner_comp_sn(_X& y, _X& ye,
                       const _X& x,  const _X& yi,
                       const _C (&a)[_N]);

        // compensated horner scheme
        // error free transformation of evaluation of polynomials
        // setup step, assumes |x*c1| < |c0|
        template <typename _X, typename _C1, typename _C0>
        void
        horner_comp_quick_s0(_X& y, _X& ye,
                             const _X& x,
                             const _C1& c1, const _C0& c0);

        // compensated horner scheme
        // error free transformation of evaluation of polynomials
        // next step, assumes |x*c1| < |c0|
        template <typename _X, typename _C1, typename _C0>
        void
        horner_comp_quick_si(_X& y, _X& ye,
                             const _X& x,
                             const _C1& c1h, const _C1& c1l, const _C0& c0);

        // compensated horner scheme
        // error free transformation of evaluation of polynomials
        // recursive next steps,
        // assumes |x*c_N| < |c_N-1|
        template <typename _X, typename _CN, typename _CNM1,
                  typename ... _CS>
        void
        horner_comp_quick_si(_X& y, _X& ye,
                             const _X& x,
                             const _CN& cnh, const _CN& cnl,
                             const _CNM1& cnm1, _CS... cs);

        // compensated horner scheme
        // error free transformation of evaluation of polynomials
        // overload for degree 1
        // assumes  |x*c_1| < |c_0|
        template <typename _X, typename _CN, typename _CNM1>
        void
        horner_comp_quick(_X& y, _X& ye,
                          const _X& x,
                          const _CN& c1, const _CNM1& c0);

        // compensated horner scheme
        // error free transformation of evaluation of polynomials
        // assumes |x*c_N| < |c_N-1|, |x*c_N_1| < |c_N-2| ..
        template <typename _X, typename _CN, typename _CNM1,
                  typename ... _CS>
        void
        horner_comp_quick(_X& y, _X& ye,
                          const _X& x,
                          const _CN& cn, const _CNM1& cnm1,
                          _CS... cs);

        // compensated horner scheme using a coefficient array
        // assumes |x*a[0]| < |a[1]|, |x*a[1]| < |a[2]| ..
        template <typename _X, typename _C, std::size_t _N>
        void
        horner_comp_quick(_X& y, _X& ye,
                          const _X& x,
                          const _C (&a)[_N]);

        // compensated horner scheme using a coefficient array
        // return ((x * (yi) + a[0])*x)+...)+a[_N-1]
        // assumes |x*a[0]| < |a[1]|, |x*a[1]| < |a[2]| ..
        template <typename _X, typename _C, std::size_t _N>
        void
        horner_comp_quick_sn(_X& y, _X& ye,
                             const _X& x, const _X& yi,
                             const _C (&a)[_N]);

        // compensated horner scheme with double precision coefficients
        // error free transformation of evaluation of polynomials
        // setup step, assumes nothing about |x*c1| and |c0|
        template <typename _X, typename _C1, typename _C0>
        void
        horner_comp_dpc_s0(_X& y, _X& ye,
                           const _X& x,
                           const _C1& c1h, const _C1& c1l,
                           const _C0& c0h, const _C0& c0l);

        // compensated horner scheme with double precision coefficients
        // error free transformation of evaluation of polynomials
        // setup step, assumes nothing about |x*yp| and |c0|
        template <typename _X, typename _C0>
        void
        horner_comp_dpc_s0(_X& y, _X& ye,
                           const _X& x,
                           const _X& yp,
                           const _C0& c0h, const _C0& c0l);

        // compensated horner scheme with double precision coefficients
        // error free transformation of evaluation of polynomials
        // next step, assumes nothing about |x*c1| and |c0|
        template <typename _X, typename _C1, typename _C0>
        void
        horner_comp_dpc_si(_X& y, _X& ye,
                           const _X& x,
                           const _C1& c1h, const _C1& c1l,
                           const _C0& c0h, const _C0& c0l);

        // compensated horner scheme with double precision coefficients
        // error free transformation of evaluation of polynomials
        // recursive next steps,
        // assumes nothing about |x*c_N| and |c_N-1|
        template <typename _X, typename _CN, typename _CNM1,
                  typename ... _CS>
        void
        horner_comp_dpc_si(_X& y, _X& ye,
                           const _X& x,
                           const _CN& cnh, const _CN& cnl,
                           const _CNM1& cnm1h, const _CNM1& cnm1l,
                           _CS... cs);

        // compensated horner scheme with double precision coefficients
        // error free transformation of evaluation of polynomials
        // overload for degree 1
        // assumes nothing about |x*c_1| and |c_0|
        template <typename _X, typename _CN, typename _CNM1>
        void
        horner_comp_dpc(_X& y, _X& ye,
                        const _X& x,
                        const _CN& c1h, const _CN& c1l,
                        const _CNM1& c0h, const _CNM1& c0l);

        // compensated horner scheme with double precision coefficients
        // error free transformation of evaluation of polynomials
        // assumes nothing about x*c_N and c_N-1
        template <typename _X, typename _CN, typename _CNM1,
                  typename ... _CS>
        void
        horner_comp_dpc(_X& y, _X& ye,
                        const _X& x,
                        const _CN& cnh, const _CN& cnl,
                        const _CNM1& cnm1h, const _CNM1& cnm1l,
                        _CS... cs);

        // compensated horner scheme with double precision coefficients
        // using a coefficient array containing a_i_h, a_i_l,
        // assumes nothing about the coefficients
        template <typename _X, typename _C, std::size_t _N>
        void
        horner_comp_dpc(_X& y, _X& ye,
                        const _X& x,
                        const _C (&a)[_N*2]);

        // compensated horner scheme with double precision coefficients
        // using a coefficient array
        // return ((_x * (yi) + a[0])*x)+...)+a[_N-1]
        // assumes nothing about the coefficients
        template <typename _X, typename _C, std::size_t _N>
        void
        horner_comp_dpc_sn(_X& y, _X& ye,
                           const _X& x,  const _X& yi,
                           const _C (&a)[_N*2]);

        // compensated horner scheme with double precision coefficients
        // error free transformation of evaluation of polynomials
        // setup step, assumes |x*c1| < |c0|
        template <typename _X, typename _C1, typename _C0>
        void
        horner_comp_quick_dpc_s0(_X& y, _X& ye,
                                 const _X& x,
                                 const _C1& c1h, const _C1& c1l,
                                 const _C0& c0h, const _C0& c0l);

        // compensated horner scheme with double precision coefficients
        // error free transformation of evaluation of polynomials
        // setup step, assumes |x*y| < |c0|
        template <typename _X, typename _C0>
        void
        horner_comp_quick_dpc_s0(_X& y, _X& ye,
                                 const _X& x,
                                 const _X& yp,
                                 const _C0& c0h, const _C0& c0l);

        // compensated horner scheme with double precision coefficients
        // error free transformation of evaluation of polynomials
        // next step, assumes |x*c1| < |c0|
        template <typename _X, typename _C1, typename _C0>
        void
        horner_comp_quick_dpc_si(_X& y, _X& ye,
                                 const _X& x,
                                 const _C1& c1h, const _C1& c1l,
                                 const _C0& c0h, const _C0& c0l);

        // compensated horner scheme with double precision coefficients
        // error free transformation of evaluation of polynomials
        // recursive next steps,
        // assumes |x*c_N| < |c_N-1|
        template <typename _X, typename _CN, typename _CNM1,
                  typename ... _CS>
        void
        horner_comp_quick_dpc_si(_X& y, _X& ye,
                                 const _X& x,
                                 const _CN& cnh, const _CN& cnl,
                                 const _CNM1& cnm1h, const _CNM1& cnm1l,
                                 _CS... cs);

        // compensated horner scheme with double precision coefficients
        // error free transformation of evaluation of polynomials
        // overload for degree 1
        // assumes  |x*c_1| < |c_0|
        template <typename _X, typename _CN, typename _CNM1>
        void
        horner_comp_quick_dpc(_X& y, _X& ye,
                              const _X& x,
                              const _CN& c1h, const _CN& c1l,
                              const _CNM1& c0h, const _CNM1& c0l);

        // compensated horner scheme with double precision coefficients
        // error free transformation of evaluation of polynomials
        // assumes |x*c_N| < |c_N-1|, |x*c_N_1| < |c_N-2| ..
        template <typename _X, typename _CN, typename _CNM1,
                  typename ... _CS>
        void
        horner_comp_quick_dpc(_X& y, _X& ye,
                              const _X& x,
                              const _CN& cnh, const _CN& cnl,
                              const _CNM1& cnm1h, const _CNM1& cnm1l,
                              _CS... cs);

        // compensated horner scheme with double precision coefficients
        // using a coefficient array
        // assumes |x*a[0]| < |a[1]|, |x*a[1]| < |a[2]| ..
        template <typename _X, typename _C, std::size_t _N>
        void
        horner_comp_quick_dpc(_X& y, _X& ye,
                              const _X& x,
                              const _C (&a)[_N*2]);

        // compensated horner scheme with double precision coefficients
        // using a coefficient array
        // return ((x * (yi) + a[0])*x)+...)+a[_N-1]
        // assumes |x*a[0]| < |a[1]|, |x*a[1]| < |a[2]| ..
        template <typename _X, typename _C, std::size_t _N>
        void
        horner_comp_quick_dpc_sn(_X& y, _X& ye,
                                 const _X& x, const _X& yi,
                                 const _C (&a)[_N*2]);
        // evaluation of a rational function
        // the parameters with the highest order are stored in p[0]
        // and q[0] as in the horner functions
        template <typename _X,
                  typename _C,
                  std::size_t _N1, std::size_t _N2>
        _X
        eval_rational(const _X& xc,
                      const _C(&p)[_N1],
                      const _C(&q)[_N2]);
        // evaluation of a rational function using _N1HP and _N2HP
        // compensated horner steps during the evaluation
        // _N1HP <= _N1-1, _N2HP <= _N2-1
        // the parameters with the highest order are stored in p[0]
        // and q[0] as in the horner functions
        template <std::size_t _N1HP, std::size_t _N2HP,
                  typename _X,
                  typename _C,
                  std::size_t _N1, std::size_t _N2>
        _X
        eval_rational(const _X& xc,
                      const _C(&p)[_N1],
                      const _C(&q)[_N2],
                      _X* ql=nullptr);

    }
}

template <typename _X, typename _C1, typename _C0>
_X
cftal::math::
horner(const _X& x, const _C1& c1, const _C0& c0)
{
    return x*c1 + _X(c0);
}

template <typename _X,
          typename _CN, typename _CNM1, typename ... _CS>
_X
cftal::math::
horner(const _X& x, const _CN& cn, const _CNM1& cnm1, _CS... cs)
{
    _X t = horner(x, cn, cnm1);
    _X r = horner(x, t, cs...);
    return r;
}

template <typename _X, typename _C>
_X
cftal::math::
horner(const _X& x, const _C& c)
{
    using std::cbegin;
    using std::cend;
    auto b=cbegin(c);
    auto e=cend(c);
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

template <std::size_t _N, typename _X, typename _C>
_X
cftal::math::
horner(const _X& x, const _C* pa)
{
    static_assert(_N > 0, "invalid call to horner(x, ptr)");
    _X r= _X(pa[0]);
#pragma GCC unroll 256
#pragma clang unroll(256)
    for (std::size_t i=1; i<_N; ++i) {
        r= horner(x, r, pa[i]);
    }
    return r;
}

template <typename _X, typename _C, std::size_t _N>
_X
cftal::math::
horner(const _X& x, const _C (&a)[_N])
{
    static_assert(_N > 0, "invalid call to horner(x, array)");
    const _C* pa=a;
    return horner<_N>(x, pa);
}

template <std::size_t _N, typename _X, typename _C>
_X
cftal::math::
horner2(const _X& x, const _X& x2, const _C* pa)
{
    static_assert(_N > 1, "invalid call to horner2(x, x2, ptr)");
    _X r0= _X(pa[0]);
    _X r1= _X(pa[1]);
    constexpr const std::size_t _NE= _N & ~(std::size_t(1));
#pragma GCC unroll 256
#pragma clang unroll(256)
    for (std::size_t i=2; i<_NE; i+=2) {
        r0= horner(x2, r0, pa[i]);
        r1= horner(x2, r1, pa[i+1]);
    }
    _X r = horner(x, r0, r1);
    if (_N & 1) {
        r = horner(x, r, pa[_N-1]);
    }
    return r;
}

template <std::size_t _N, typename _X, typename _C>
_X
cftal::math::
horner2(const _X& x, const _C* pa)
{
    static_assert(_N > 1, "invalid call to horner2(x, ptr)");
    _X x2=x*x;
    return horner2<_N>(x, x2, pa);
}

template <typename _X, typename _C, std::size_t _N>
_X
cftal::math::
horner2(const _X& x, const _X& x2, const _C (&a)[_N])
{
    static_assert(_N > 1, "invalid call to horner2(x, x2, array)");
    const _C* pa=a;
    return horner2<_N>(x, x2, pa);
}

template <typename _X, typename _C, std::size_t _N>
_X
cftal::math::
horner2(const _X& x, const _C (&a)[_N])
{
    static_assert(_N > 1, "invalid call to horner2(x, array)");
    const _C* pa=a;
    return horner2<_N>(x, pa);
}

template <std::size_t _N, typename _X, typename _C>
_X
cftal::math::
horner3(const _X& x, const _X& x3, const _C* pa)
{
    static_assert(_N > 2, "invalid call to horner3(x, x3, ptr)");
    _X r0= _X(pa[0]);
    _X r1= _X(pa[1]);
    _X r2= _X(pa[2]);
    constexpr const std::size_t _NE= (_N / 3) * 3;
#pragma GCC unroll 256
#pragma clang unroll(256)
    for (std::size_t i=3; i<_NE; i+=3) {
        r0= horner(x3, r0, pa[i]);
        r1= horner(x3, r1, pa[i+1]);
        r2= horner(x3, r2, pa[i+2]);
    }
    _X r = horner(x, r0, r1, r2);
    constexpr const std::size_t _NR= _N - _NE;
    switch (_NR) {
    case 2:
        r = horner(x, r, pa[_N-2], pa[_N-1]);
        break;
    case 1:
        r = horner(x, r, pa[_N-1]);
        break;
    default:
        break;
    }
    return r;
}

template <std::size_t _N, typename _X, typename _C>
_X
cftal::math::
horner3(const _X& x, const _C* pa)
{
    static_assert(_N > 2, "invalid call to horner3(x, ptr)");
    _X x3=x*x*x;
    return horner3<_N>(x, x3, pa);
}

template <typename _X, typename _C, std::size_t _N>
_X
cftal::math::
horner3(const _X& x, const _X& x3, const _C (&a)[_N])
{
    static_assert(_N > 2, "invalid call to horner3(x, x3, array)");
    const _C* pa=a;
    return horner3<_N>(x, x3, pa);
}

template <typename _X, typename _C, std::size_t _N>
_X
cftal::math::
horner3(const _X& x, const _C (&a)[_N])
{
    static_assert(_N > 2, "invalid call to horner3(x, array)");
    const _C* pa=a;
    return horner3<_N>(x, pa);
}

template <std::size_t _N, typename _X, typename _C>
_X
cftal::math::
horner4(const _X& x, const _X& x2, const _X& x4, const _C* pa)
{
    static_assert(_N > 3, "invalid call to horner4(x, x2, x4, ptr)");
    _X r0= _X(pa[0]);
    _X r1= _X(pa[1]);
    _X r2= _X(pa[2]);
    _X r3= _X(pa[3]);
    constexpr const std::size_t _NE= _N & ~std::size_t(3);
#pragma GCC unroll 256
#pragma clang unroll(256)
    for (std::size_t i=4; i<_NE; i+=4) {
        r0= horner(x4, r0, pa[i]);
        r1= horner(x4, r1, pa[i+1]);
        r2= horner(x4, r2, pa[i+2]);
        r3= horner(x4, r3, pa[i+3]);
    }
    _X r02 = horner(x2, r0, r2);
    _X r13 = horner(x2, r1, r3);
    _X r= horner(x, r02, r13);
    constexpr const std::size_t _NR= _N & std::size_t(3);
    if (_NR == 3) {
        _X a = horner(x2, r, pa[_N-2]);
        _X b = horner(x2, pa[_N-3], pa[_N-1]);
        r = horner(x, a, b);
    }
    if (_NR == 2) {
        _X a = horner(x2, r, pa[_N-1]);
        r = horner(x, pa[_N-2], a);
    }
    if (_NR == 1) {
        r = horner(x, r, pa[_N-1]);
    }
    return r;
}

template <std::size_t _N, typename _X, typename _C>
_X
cftal::math::
horner4(const _X& x, const _C* pa)
{
    static_assert(_N > 3, "invalid call to horner4(x, ptr)");
    _X x2=x*x;
    _X x4=x2*x2;
    return horner<_N>(x, x2, x4, pa);
}

template <typename _X, typename _C, std::size_t _N>
_X
cftal::math::
horner4(const _X& x, const _X& x2, const _X& x4, const _C (&a)[_N])
{
    static_assert(_N > 3, "invalid call to horner4(x, x2, x4, array)");
    const _C* pa=a;
    return horner4<_N>(x, x2, x4, pa);
}

template <typename _X, typename _C, std::size_t _N>
_X
cftal::math::
horner4(const _X& x, const _C (&a)[_N])
{
    static_assert(_N > 3, "invalid call to horner4(x, array)");
    const _C* pa=a;
    return horner4<_N>(x, pa);
}

template <typename _F, typename _C, std::size_t _N>
cftal::d_real<_F>
cftal::math::
horner(const d_real<_F>& x, const d_real<_C> (&a)[_N])
{
    static_assert(
        _N > 0,
        "invalid call to horner(d_real<_F>, d_real<_C>(&a)[])");
    d_real<_F> r=d_real<_F>(a[0]);
    const d_real<_C>* pa=a;
    for (std::size_t i=1; i<_N; ++i) {
        r=horner(x, r, d_real<_F>(pa[i] ));
    }
    return r;
}

template <typename _F, typename _C, std::size_t _N>
_F
cftal::math::
horner(const _F& x, const d_real<_C> (&a)[_N])
{
    static_assert(_N > 0, "invalid call to horner(_F, d_real<_C>(&a)[])");
    const d_real<_C>* pa=a;
    _F r= pa[0].h();
    for (std::size_t i=1; i<_N; ++i) {
        r= horner(x, r, _F(pa[i].h()));
    }
    return r;
}

// polynomial with c1 = 1.0
template <typename _X, typename _C0>
_X
cftal::math::
horner1(const _X& x, const _C0& c0)
{
    return x + c0;
}

// polynomial with cn = 1.0
template <typename _X,typename _CNM1, typename ... _CS>
_X
cftal::math::
horner1(const _X& x, const _CNM1& cnm1, _CS... cs)
{
    _X t = horner1(x, cnm1);
    _X r = horner(x, t, cs...);
    return r;
}

template <typename _X, typename _C, std::size_t _N>
void
cftal::math::
horner_n2(_X& ya, _X& yb,
          const _X& x,
          const _C (&a)[_N], const _C (&b)[_N])
{
    static_assert(_N > 0, "invalid call to horner_n2(ya, yb, x, ca, cb)");
    const _C* pa=a;
    const _C* pb=b;
    _X ra= _X(pa[0]);
    _X rb= _X(pb[0]);
    for (std::size_t i=1; i<_N; ++i) {
        ra= horner(x, ra, pa[i]);
        rb= horner(x, rb, pb[i]);
    }
    ya = ra;
    yb = rb;
}

template <typename _X, typename _C, std::size_t _N>
void
cftal::math::
horner2_n2(_X& ya, _X& yb,
           const _X& x, const _X& x2,
           const _C (&a)[_N], const _C (&b)[_N])
{
    static_assert(_N > 1,
                  "invalid call to horner2_n2(ya, yb, x, x2, array, array)");
    const _C* pa=a;
    const _C* pb=b;
    _X r0a= _X(pa[0]);
    _X r1a= _X(pa[1]);
    _X r0b= _X(pb[0]);
    _X r1b= _X(pb[1]);
    constexpr const std::size_t _NE= _N & ~(std::size_t(1));
    for (std::size_t i=2; i<_NE; i+=2) {
        r0a= horner(x2, r0a, pa[i]);
        r1a= horner(x2, r1a, pa[i+1]);
        r0b= horner(x2, r0b, pb[i]);
        r1b= horner(x2, r1b, pb[i+1]);
    }
    _X ra = horner(x, r0a, r1a);
    _X rb = horner(x, r0b, r1b);
    if (_N & 1) {
        ra = horner(x, ra, pa[_N-1]);
        rb = horner(x, rb, pb[_N-1]);
    }
    ya = ra;
    yb = rb;
}

template <typename _X, typename _C, std::size_t _N>
void
cftal::math::
horner_n4(_X& ya, _X& yb, _X& yc, _X& yd,
          const _X& x,
          const _C (&a)[_N], const _C (&b)[_N],
          const _C (&c)[_N], const _C (&d)[_N])
{
    static_assert(_N > 0,
                  "invalid call to horner_n4(ya, yb, yc, yd x, ca, cb, cc, cd)");
    _X ra= _X(a[0]);
    _X rb= _X(b[0]);
    _X rc= _X(c[0]);
    _X rd= _X(d[0]);
    const _C* pa=a;
    const _C* pb=b;
    const _C* pc=c;
    const _C* pd=d;
    for (std::size_t i=1; i<_N; ++i) {
        ra= horner(x, ra, pa[i]);
        rb= horner(x, rb, pb[i]);
        rc= horner(x, rc, pc[i]);
        rd= horner(x, rd, pd[i]);
    }
    ya = ra;
    yb = rb;
    yc = rc;
    yd = rd;
}

template <typename _X, typename _C1, typename _C0>
void
cftal::math::
horner_n4(_X& y0, _X& y1, _X& y2, _X& y3,
          const _X& x0, const _X& x1,
          const _X& x2, const _X& x3,
          const _C1& c1_0, const _C1& c1_1,
          const _C1& c1_2, const _C1& c1_3,
          const _C0& c0_0, const _C0& c0_1,
          const _C0& c0_2, const _C0& c0_3)
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
          const _X& x0, const _X& x1,
          const _X& x2, const _X& x3,
          const _CN& cn_0, const _CN& cn_1,
          const _CN& cn_2, const _CN& cn_3,
          const _CNM1& cnm1_0, const _CNM1& cnm1_1,
          const _CNM1& cnm1_2, const _CNM1& cnm1_3,
          _CS... cs)
{
    horner_n4(y0, y1, y2, y3, x0, x1, x2, x3,
              cn_0, cn_1, cn_2, cn_3,
              cnm1_0, cnm1_1, cnm1_2, cnm1_3);
    horner_n4(y0, y1, y2, y3, x0, x1, x2, x3,
              y0, y1, y2, y3, cs...);
}

template <typename _X, typename _C1, typename _C0>
inline
__attribute__((__always_inline__))
void
cftal::math::
horner_comp_s0(_X& y, _X& ye,
               const _X& x,
               const _C1& c1, const _C0& c0)
{
    using d_ops=d_real_ops<_X, d_real_traits<_X>::fma>;
    _X p_i, o_i;
    d_ops::mul12(y, p_i, c1, x);
    d_ops::add12cond(y, o_i, c0, y);
    ye= (p_i + o_i);
}

template <typename _X, typename _C1, typename _C0>
inline
__attribute__((__always_inline__))
void
cftal::math::
horner_comp_si(_X& y, _X& ye,
               const _X& x,
               const _C1& c1h, const _C1& c1l, const _C0& c0)
{
    using d_ops=d_real_ops<_X, d_real_traits<_X>::fma>;
    _X p_i, o_i;
    d_ops::mul12(y, p_i, c1h, x);
    d_ops::add12cond(y, o_i, c0, y);
    ye= c1l*x + (p_i + o_i);
}

template <typename _X,
          typename _CN, typename _CNM1, typename ... _CS>
inline
__attribute__((__always_inline__))
void
cftal::math::
horner_comp_si(_X& y, _X& ye,
               const _X& x,
               const _CN& cnh, const _CN& cnl,
               const _CNM1& cnm1, _CS ... cs)
{
    horner_comp_si(y, ye, x, cnh, cnl, cnm1);
    horner_comp_si(y, ye, x, y, ye, cs...);
}

template <typename _X, typename _CN, typename _CNM1>
inline
__attribute__((__always_inline__))
void
cftal::math::
horner_comp(_X& y, _X& ye,
            const _X& x,
            const _CN& c1, const _CNM1& c0)
{
    horner_comp_s0(y, ye, x, c1, c0);
}

template <typename _X,
          typename _CN, typename _CNM1, typename ... _CS>
inline
__attribute__((__always_inline__))
void
cftal::math::
horner_comp(_X& y, _X& ye,
            const _X& x,
            const _CN& cn, const _CNM1& cnm1, _CS ... cs)
{
    horner_comp_s0(y, ye, x, cn, cnm1);
    horner_comp_si(y, ye, x, y, ye, cs...);
}

template <typename _X, typename _C, std::size_t _N>
void
cftal::math::
horner_comp(_X& y, _X& ye,
            const _X& x, const _C (&a)[_N])
{
    static_assert(_N > 1, "at least 2 array elements required");
    const _C* pa=a;
    horner_comp_s0(y, ye, x, pa[0], pa[1]);
    for (std::size_t i=2; i < _N; ++i) {
        horner_comp_si(y, ye, x, y, ye, pa[i]);
    }
}

template <typename _X, typename _C, std::size_t _N>
void
cftal::math::
horner_comp_sn(_X& y, _X& ye,
               const _X& x, const _X& yi, const _C (&a)[_N])
{
    static_assert(_N > 0, "at least 1 array element required");
    const _C* pa=a;
    horner_comp_s0(y, ye, x, yi, pa[0]);
#pragma GCC unroll 256
#pragma clang unroll(256)
    for (std::size_t i=1; i < _N; ++i) {
        horner_comp_si(y, ye, x, y, ye, pa[i]);
    }
}

template <typename _X, typename _C1, typename _C0>
inline
__attribute__((__always_inline__))
void
cftal::math::
horner_comp_quick_s0(_X& y, _X& ye,
                     const _X& x,
                     const _C1& c1, const _C0& c0)
{
    using d_ops=d_real_ops<_X, d_real_traits<_X>::fma>;
#if 1
    d_ops::muladd12(y, ye, c0, x, c1);
#else
    _X p_i, o_i;
    d_ops::mul12(y, p_i, c1, x);
    d_ops::add12(y, o_i, c0, y);
    ye= (p_i + o_i);
#endif
}

template <typename _X, typename _C1, typename _C0>
inline
__attribute__((__always_inline__))
void
cftal::math::
horner_comp_quick_si(_X& y, _X& ye,
                     const _X& x,
                     const _C1& c1h, const _C1& c1l, const _C0& c0)
{
    using d_ops=d_real_ops<_X, d_real_traits<_X>::fma>;
#if 1
    _X t1;
    d_ops::muladd12(y, t1, c0, x, c1h);
    ye = (x*c1l) + t1;
#else
    _X p_i, o_i;
    d_ops::mul12(y, p_i, c1h, x);
    d_ops::add12(y, o_i, c0, y);
    ye= c1l*x + (p_i + o_i);
#endif
}

template <typename _X,
          typename _CN, typename _CNM1, typename ... _CS>
inline
__attribute__((__always_inline__))
void
cftal::math::
horner_comp_quick_si(_X& y, _X& ye,
                     const _X& x,
                     const _CN& cnh, const _CN& cnl,
                     const _CNM1& cnm1, _CS ... cs)
{
    horner_comp_quick_si(y, ye, x, cnh, cnl, cnm1);
    horner_comp_quick_si(y, ye, x, y, ye, cs...);
}

template <typename _X, typename _CN, typename _CNM1>
inline
__attribute__((__always_inline__))
void
cftal::math::
horner_comp_quick(_X& y, _X& ye,
                  const _X& x,
                  const _CN& c1,
                  const _CNM1& c0)
{
    horner_comp_quick_s0(y, ye, x, c1, c0);
}

template <typename _X,
          typename _CN, typename _CNM1, typename ... _CS>
inline
__attribute__((__always_inline__))
void
cftal::math::
horner_comp_quick(_X& y, _X& ye,
                  const _X& x,
                  const _CN& cn, const _CNM1& cnm1, _CS ... cs)
{
    horner_comp_quick_s0(y, ye, x, cn, cnm1);
    horner_comp_quick_si(y, ye, x, y, ye, cs...);
}

template <typename _X, typename _C, std::size_t _N>
void
cftal::math::
horner_comp_quick(_X& y, _X& ye,
                  const _X& x, const _C (&a)[_N])
{
    static_assert(_N > 1, "at least 2 array elements required");
    const _C* pa=a;
    horner_comp_quick_s0(y, ye, x, pa[0], pa[1]);
    for (std::size_t i=2; i < _N; ++i) {
        horner_comp_quick_si(y, ye, x, y, ye, pa[i]);
    }
}

template <typename _X, typename _C, std::size_t _N>
void
cftal::math::
horner_comp_quick_sn(_X& y, _X& ye,
                     const _X& x, const _X& yi, const _C (&a)[_N])
{
    static_assert(_N > 0, "at least 1 array element required");
    const _C* pa=a;
    horner_comp_quick_s0(y, ye, x, yi, pa[0]);
#pragma GCC unroll 256
#pragma clang unroll(256)
    for (std::size_t i=1; i < _N; ++i) {
        horner_comp_quick_si(y, ye, x, y, ye, pa[i]);
    }
}

template <typename _X, typename _C1, typename _C0>
inline
__attribute__((__always_inline__))
void
cftal::math::
horner_comp_dpc_s0(_X& y, _X& ye,
                   const _X& x,
                   const _C1& c1h, const _C1& c1l,
                   const _C0& c0h, const _C0& c0l)
{
    using d_ops=d_real_ops<_X, d_real_traits<_X>::fma>;
    _X p_i, o_i;
    d_ops::mul12(y, p_i, c1h, x);
    d_ops::add12cond(y, o_i, c0h, y);
    ye= c1l*x + (p_i + o_i + c0l);
}

template <typename _X, typename _C0>
inline
__attribute__((__always_inline__))
void
cftal::math::
horner_comp_dpc_s0(_X& y, _X& ye,
                   const _X& x,
                   const _X& yp,
                   const _C0& c0h, const _C0& c0l)
{
    using d_ops=d_real_ops<_X, d_real_traits<_X>::fma>;
    _X p_i, o_i;
    d_ops::mul12(y, p_i, yp, x);
    d_ops::add12cond(y, o_i, c0h, y);
    ye= (p_i + o_i + c0l);
}

template <typename _X, typename _C1, typename _C0>
inline
__attribute__((__always_inline__))
void
cftal::math::
horner_comp_dpc_si(_X& y, _X& ye,
                   const _X& x,
                   const _C1& c1h, const _C1& c1l,
                   const _C0& c0h, const _C0& c0l)
{
    using d_ops=d_real_ops<_X, d_real_traits<_X>::fma>;
    _X p_i, o_i;
    d_ops::mul12(y, p_i, c1h, x);
    d_ops::add12cond(y, o_i, c0h, y);
    ye= c1l*x + (p_i + o_i + c0l);
}

template <typename _X,
          typename _CN, typename _CNM1, typename ... _CS>
inline
__attribute__((__always_inline__))
void
cftal::math::
horner_comp_dpc_si(_X& y, _X& ye,
                   const _X& x,
                   const _CN& cnh, const _CN& cnl,
                   const _CNM1& cnm1h, const _CNM1& cnm1l,
                   _CS ... cs)
{
    horner_comp_dpc_si(y, ye, x, cnh, cnl, cnm1h, cnm1l);
    horner_comp_dpc_si(y, ye, x, y, ye, cs...);
}

template <typename _X, typename _CN, typename _CNM1>
inline
__attribute__((__always_inline__))
void
cftal::math::
horner_comp_dpc(_X& y, _X& ye,
                const _X& x,
                const _CN& c1h, const _CN& c1l,
                const _CNM1& c0h, const _CNM1& c0l)
{
    horner_comp_dpc_s0(y, ye, x, c1h, c1l, c0h, c0l);
}

template <typename _X,
          typename _CN, typename _CNM1, typename ... _CS>
inline
__attribute__((__always_inline__))
void
cftal::math::
horner_comp_dpc(_X& y, _X& ye,
                const _X& x,
                const _CN& cnh, const _CN& cnl,
                const _CNM1& cnm1h, const _CNM1& cnm1l,
                _CS ... cs)
{
    horner_comp_dpc_s0(y, ye, x, cnh, cnl, cnm1h, cnm1l);
    horner_comp_dpc_si(y, ye, x, y, ye, cs...);
}

template <typename _X, typename _C, std::size_t _N>
void
cftal::math::
horner_comp_dpc(_X& y, _X& ye,
                const _X& x, const _C (&a)[_N*2])
{
    static_assert(_N > 1, "at least 4 array elements required");
    const _C* pa=a;
    horner_comp_dpc_s0(y, ye, x, pa[0], pa[1], pa[2], pa[3]);
    for (std::size_t i=2; i < _N; ++i) {
        horner_comp_dpc_si(y, ye, x, y, ye, pa[2*i], pa[2*i+1]);
    }
}

template <typename _X, typename _C, std::size_t _N>
void
cftal::math::
horner_comp_dpc_sn(_X& y, _X& ye,
                   const _X& x,
                   const _X& yi,
                   const _C (&a)[_N*2])
{
    static_assert(_N > 0, "at least 2 array elements required");
    const _C* pa=a;
    horner_comp_s0(y, ye, x, yi, pa[0], pa[1]);
#pragma GCC unroll 256
#pragma clang unroll(256)
    for (std::size_t i=1; i < _N; ++i) {
        horner_comp_dpc_si(y, ye, x, y, ye, pa[2*i], pa[2*i+1]);
    }
}

template <typename _X, typename _C1, typename _C0>
inline
__attribute__((__always_inline__))
void
cftal::math::
horner_comp_quick_dpc_s0(_X& y, _X& ye,
                         const _X& x,
                         const _C1& c1h, const _C1& c1l,
                         const _C0& c0h, const _C0& c0l)
{
    using d_ops=d_real_ops<_X, d_real_traits<_X>::fma>;
#if 1
    _X t1;
    d_ops::muladd12(y, t1, c0h, x, c1h);
    ye = (x*c1l) + (t1 + c0l);
#else
    _X p_i, o_i;
    d_ops::mul12(y, p_i, c1h, x);
    d_ops::add12(y, o_i, c0h, y);
    ye= c1l*x+(p_i + o_i + c0l);
#endif
}

template <typename _X, typename _C0>
inline
__attribute__((__always_inline__))
void
cftal::math::
horner_comp_quick_dpc_s0(_X& y, _X& ye,
                         const _X& x,
                         const _X& yp,
                         const _C0& c0h, const _C0& c0l)
{
    using d_ops=d_real_ops<_X, d_real_traits<_X>::fma>;
#if 1
    _X t1;
    d_ops::muladd12(y, t1, c0h, x, yp);
    ye = (t1 + c0l);
#else
    _X p_i, o_i;
    d_ops::mul12(y, p_i, yp, x);
    d_ops::add12(y, o_i, c0h, y);
    ye= (p_i + o_i + c0l);
#endif
}

template <typename _X, typename _C1, typename _C0>
inline
__attribute__((__always_inline__))
void
cftal::math::
horner_comp_quick_dpc_si(_X& y, _X& ye,
                         const _X& x,
                         const _C1& c1h, const _C1& c1l,
                         const _C0& c0h, const _C0& c0l)
{
    using d_ops=d_real_ops<_X, d_real_traits<_X>::fma>;
#if 1
    _X t1;
    d_ops::muladd12(y, t1, c0h, x, c1h);
    ye = (x*c1l) + (t1+c0l);
#else
    _X p_i, o_i;
    d_ops::mul12(y, p_i, c1h, x);
    d_ops::add12(y, o_i, c0h, y);
    ye= c1l*x + (p_i + o_i+c0l);
#endif
}

template <typename _X,
          typename _CN, typename _CNM1, typename ... _CS>
inline
__attribute__((__always_inline__))
void
cftal::math::
horner_comp_quick_dpc_si(_X& y, _X& ye,
                         const _X& x,
                         const _CN& cnh, const _CN& cnl,
                         const _CNM1& cnm1h, const _CNM1& cnm1l,
                         _CS ... cs)
{
    horner_comp_quick_dpc_si(y, ye, x, cnh, cnl, cnm1h, cnm1l);
    horner_comp_quick_dpc_si(y, ye, x, y, ye, cs...);
}

template <typename _X, typename _CN, typename _CNM1>
inline
__attribute__((__always_inline__))
void
cftal::math::
horner_comp_quick_dpc(_X& y, _X& ye,
                      const _X& x,
                      const _CN& c1h, const _CN& c1l,
                      const _CNM1& c0h, const _CNM1& c0l)
{
    horner_comp_quick_dpc_s0(y, ye, x, c1h, c1l, c0h, c0l);
}

template <typename _X,
          typename _CN, typename _CNM1, typename ... _CS>
inline
__attribute__((__always_inline__))
void
cftal::math::
horner_comp_quick_dpc(_X& y, _X& ye,
                      const _X& x,
                      const _CN& cnh, const _CN& cnl,
                      const _CNM1& cnm1h, const _CNM1& cnm1l,
                      _CS ... cs)
{
    horner_comp_quick_dpc_s0(y, ye, x, cnh, cnl, cnm1h, cnm1l);
    horner_comp_quick_dpc_si(y, ye, x, y, ye, cs...);
}

template <typename _X, typename _C, std::size_t _N>
void
cftal::math::
horner_comp_quick_dpc(_X& y, _X& ye,
                      const _X& x, const _C (&a)[_N*2])
{
    static_assert(_N > 1, "at least 4 array elements required");
    const _C* pa=a;
    horner_comp_quick_dpc_s0(y, ye, x, pa[0], pa[1], pa[2], pa[3]);
    for (std::size_t i=2; i < _N; ++i) {
        horner_comp_quick_dpc_si(y, ye, x, y, ye, pa[2*i], pa[2*i+1]);
    }
}

template <typename _X, typename _C, std::size_t _N>
void
cftal::math::
horner_comp_quick_dpc_sn(_X& y, _X& ye,
                         const _X& x, const _X& yi, const _C (&a)[_N*2])
{
    static_assert(_N > 0, "at least 2 array elements required");
    const _C* pa=a;
    horner_comp_quick_s0(y, ye, x, yi, pa[0], pa[1]);
#pragma GCC unroll 256
#pragma clang unroll(256)
    for (std::size_t i=1; i < _N; ++i) {
        horner_comp_quick_dpc_si(y, ye, x, y, ye, pa[2*i], pa[2*i+1]);
    }
}

template <typename _X,
          typename _C,
          std::size_t _N1, std::size_t _N2>
_X
cftal::math::
eval_rational(const _X& xc,
              const _C (&p)[_N1],
              const _C (&q)[_N2])
{
    const _X& x=xc;
    const _C c=_C(1.0);
    auto x_le_c = x <= c;
    auto x_gt_c = x > c;
    // normal enumerator and denominator
    _X n;
    _X d;
    if (any_of(x_le_c)) {
        n= horner(x, p);
        d= horner(x, q);
    }
    if (any_of(x_gt_c)) {
        _X r_x=_C(1.0)/x;
        _X r_n= p[_N1-1];
        for (int i= _N1-2; i>= 0; --i)
            r_n = r_n * r_x + _X(p[i]);
        _X r_d= q[_N2-1];
        for (int i= _N2-2; i>= 0; --i)
            r_d = r_d * r_x + _X(q[i]);
        if (any_of(x_le_c)) {
            n = select(x_le_c, n, r_n);
            d = select(x_le_c, d, r_d);
        } else {
            n = r_n;
            d = r_d;
        }
    }
    return n/d;
}

template <std::size_t _N1HP, std::size_t _N2HP,
          typename _X,
          typename _C,
          std::size_t _N1, std::size_t _N2>
_X
cftal::math::
eval_rational(const _X& xc,
              const _C (&p)[_N1],
              const _C (&q)[_N2],
              _X* pql)
{
    static_assert(_N1HP < _N1, "ooops");
    static_assert(_N2HP < _N2, "ooops");
    const _X& x=xc;
    const _C c=_C(1.0);
    auto x_le_c = x <= c;
    auto x_gt_c = x > c;
    // normal enumerator and denominator
    _X n, n_l;
    _X d, d_l;

    if (any_of(x_le_c)) {
        n= p[0];
        for (int i=1; i<int(_N1-_N1HP); ++i)
            n = n * x + p[i];
        d= q[0];
        for (int i=1; i<int(_N2-_N2HP); ++i)
            d = d * x + q[i];
        n_l = d_l = _C(0);
        if (_N1HP != 0) {
            horner_comp_s0(n, n_l, x, n, p[_N1-_N1HP]);
            for (int i=int(_N1-_N1HP)+1; i<int(_N1); ++i)
                horner_comp_si(n, n_l, x, n, n_l, p[i]);
        }
        if (_N2HP != 0) {
            horner_comp_s0(d, d_l, x, d, q[_N2-_N2HP]);
            for (int i=int(_N2-_N2HP)+1; i<int(_N2); ++i)
                horner_comp_si(d, d_l, x, d, d_l, q[i]);
        }
    }
    if (any_of(x_gt_c)) {
        _X r_x=_C(1.0)/x;
        _X r_n= p[_N1-1];
        for (int i= int(_N1)-2; i>= int(_N1HP); --i)
            r_n = r_n * r_x + p[i];
        _X r_d= q[_N2-1];
        for (int i= int(_N2)-2; i>= int(_N2HP); --i)
            r_d = r_d * r_x + q[i];
        _X r_n_l = _C(0);
        if (_N1HP != 0) {
            horner_comp_s0(r_n, r_n_l, r_x, r_n, p[_N1HP-1]);
            for (int i=int(_N1HP)-2; i>=0; --i)
                horner_comp_si(r_n, r_n_l, r_x, r_n, r_n_l, p[i]);
        }
        _X r_d_l = _C(0);
        if (_N2HP != 0) {
            horner_comp_s0(r_d, r_d_l, r_x, r_d, q[_N2HP-1]);
            for (int i=int(_N2HP)-2; i>=0; --i)
                horner_comp_si(r_d, r_d_l, r_x, r_d, r_d_l, q[i]);
        }
        if (any_of(x_le_c)) {
            n = select(x_le_c, n, r_n);
            d = select(x_le_c, d, r_d);
            if (_N1HP|_N2HP) {
                n_l = select(x_le_c, n_l, r_n_l);
                d_l = select(x_le_c, d_l, r_d_l);
            }
        } else {
            n = r_n;
            d = r_d;
            if (_N1HP|_N2HP) {
                n_l = r_n_l;
                d_l = r_d_l;
            }
        }
    }
    _X qq;
    using d_ops=d_real_ops<_X, d_real_traits<_X>::fma>;
    if (_N1HP|_N2HP) {
        if (pql != nullptr) {
            d_ops::div22(qq, *pql, n, n_l, d, d_l);
        } else {
            d_ops::div21(qq, n, n_l, d, d_l);
        }
    } else {
        if (pql != nullptr) {
            d_ops::div12(qq, *pql, n, d);
        } else {
            qq = n/d;
        }
    }
    return qq;
}

// local variables:
// mode: c++
// end:
#endif
