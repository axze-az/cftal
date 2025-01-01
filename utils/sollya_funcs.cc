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
// all the functions below are terrible hacks
#include <mpfr.h>
#define __gmp_const const
#include <mpfi.h>
#include <sollya.h>
#include <iostream>
#include "cftal/test/call_mpfr.h"
#include <iomanip>
#include <vector>

// ext_tgamma = library("./libsollya_funcs.so");
extern "C"
int ext_tgamma(mpfi_t rop, mpfi_t op, int n);

// ext_lngamma = library("./libsollya_funcs.so");
extern "C"
int ext_lngamma(mpfi_t rop, mpfi_t op, int n);

extern "C"
int ext_j0(mpfi_t rop, mpfi_t op, int n);

extern "C"
int ext_j1(mpfi_t rop, mpfi_t op, int n);

extern "C"
int ext_y0(mpfi_t rop, mpfi_t op, int n);

extern "C"
int ext_y1(mpfi_t rop, mpfi_t op, int n);

extern "C"
void ext_euler_gamma(mpfr_t res, mp_prec_t prec);

namespace cftal {
    namespace test {
        int mpfi_from_mpfr(mpfi_t i, const fpn_handle& v, int mpfr_result);

        template <typename _T>
        void
        approx_dy_dx(fpn_handle& r,
                     const fpn_handle& x,
                     _T f,
                     mpfr_rnd_t rm);

        template <typename _T>
        void
        approx_d2y_dx2(fpn_handle& r,
                       const fpn_handle& x,
                       _T f,
                       mpfr_rnd_t rm);
    }
}

template <typename _T>
void
cftal::test::approx_dy_dx(fpn_handle& r,
                          const fpn_handle& x,
                          _T f,
                          mpfr_rnd_t rm)
{
    // df/dx ~ [f(x+h) - f(x-h)] / 2h
    const mpfr_prec_t prec=x.prec();
    // h = 2^-prec
    fpn_handle d(prec);
    const mpfr_exp_t eh=-int64_t(prec);
    mpfr_set_si_2exp(d(), 1L, eh, MPFR_RNDN);
    // 2h: 2*(2^-prec)
    fpn_handle dx(prec);
    mpfr_set_si_2exp(dx(), 2L, eh, MPFR_RNDN);
    fpn_handle x_l(2*prec), x_r(2*prec);
    mpfr_sub(x_l(), x(), d(), MPFR_RNDN);
    mpfr_add(x_r(), x(), d(), MPFR_RNDN);
    fpn_handle y_l(2*prec), y_r(2*prec);
    f(y_l, x_l, MPFR_RNDN);
    f(y_r, x_r, MPFR_RNDN);
    fpn_handle dy(2*prec);
    mpfr_sub(dy(), y_r(), y_l(), MPFR_RNDN);
    mpfr_div(r(), dy(), dx(), rm);
#if 0
    double xx=mpfr_get_d(x(), MPFR_RNDN);
    fpn_handle y(x.prec());
    f(y, x, MPFR_RNDN);
    double fx=mpfr_get_d(y(), MPFR_RNDN);
    double fxs=mpfr_get_d(r(), MPFR_RNDN);
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << std::setprecision(18) << std::scientific
              << xx << std::endl
              << fx << std::endl
              << fxs << std::endl;
#endif
}

template <typename _T>
void
cftal::test::approx_d2y_dx2(fpn_handle& r,
                            const fpn_handle& x,
                            _T f,
                            mpfr_rnd_t rm)
{
    // d2f/dx2 ~ [f(x+h) - 2*f(x) + f(x-h)] / h^2
    const mpfr_prec_t prec=x.prec();
    // h = 2^-prec
    fpn_handle d(prec);
    const mpfr_exp_t eh= -int64_t(prec);
    mpfr_set_si_2exp(d(), 1L, eh, MPFR_RNDN);
    // h^2 = h*h = 2^(-2*prec)
    const mpfr_exp_t eh2= 2*eh;
    fpn_handle dx2(prec);
    mpfr_set_si_2exp(dx2(), 1L, eh2, MPFR_RNDN);
    fpn_handle x_l(2*prec), x_r(2*prec);
    mpfr_sub(x_l(), x(), d(), MPFR_RNDN);
    mpfr_add(x_r(), x(), d(), MPFR_RNDN);
    fpn_handle y_l(2*prec), y_r(2*prec), y(2*prec);
    f(y_l, x_l, MPFR_RNDN);
    f(y, x, MPFR_RNDN);
    f(y_r, x_r, MPFR_RNDN);
    fpn_handle t(2*prec);
    fpn_handle y2(2* prec);
    mpfr_mul_2si(y2(), y(), 1, MPFR_RNDN);
    mpfr_sub(t(), y_r(), y2(), MPFR_RNDN);
    mpfr_add(t(), t(), y_l(), MPFR_RNDN);
    mpfr_div(r(), t(), dx2(), rm);
#if 0
    double xx=mpfr_get_d(x(), MPFR_RNDN);
    double fx=mpfr_get_d(y(), MPFR_RNDN);
    double fxs=mpfr_get_d(r(), MPFR_RNDN);
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << std::setprecision(18) << std::scientific
              << xx << std::endl
              << fx << std::endl
              << fxs << std::endl;
#endif
}

int
cftal::test::
mpfi_from_mpfr(mpfi_t i, const fpn_handle& res, int mpfr_result)
{
    if (mpfr_result > 0) {
        // res is greater than the real value
        fpn_handle res_l(res);
        mpfr_nextbelow(res_l());
        mpfr_set(&i->left, res_l(), MPFR_RNDN);
        mpfr_set(&i->right, res(), MPFR_RNDN);
    } else if (mpfr_result < 0) {
        // res is smaller than the real value
        fpn_handle res_r(res);
        mpfr_nextabove(res_r());
        mpfr_set(&i->left, res(), MPFR_RNDN);
        mpfr_set(&i->right, res_r(), MPFR_RNDN);
    } else if (mpfr_result == 0) {
        mpfr_set(&i->left, res(), MPFR_RNDN);
        mpfr_set(&i->right, res(), MPFR_RNDN);
    }
    return 0;
}

int ext_tgamma(mpfi_t y, mpfi_t x, int f_n)
{
    using cftal::test::fpn_handle;
    int res=0;
    mpfr_prec_t p_y=mpfi_get_prec(y);
    mpfr_prec_t p_x=mpfi_get_prec(x);

    fpn_handle y_l(p_y), y_r(p_y), x_l(p_x), x_r(p_x);

    auto gamma_f=[](fpn_handle& y, const fpn_handle& x, mpfr_rnd_t rnd)->void {
        mpfr_gamma(y(), x(), rnd);
    };

    auto gamma_f1=[](fpn_handle& y,
                     const fpn_handle& x,
                     mpfr_rnd_t rnd)->void {
        fpn_handle d(y.prec());
        mpfr_digamma(d(), x(), rnd);
        fpn_handle g(y.prec());
        mpfr_gamma(g(), x(), rnd);
        mpfr_mul(y(), g(), d(), rnd);
    };

    mpfi_get_left(x_l(), x);
    mpfi_get_right(x_r(), x);
    switch(f_n) {
    case 0:
        // return the function itself
        gamma_f(y_l, x_l, MPFR_RNDD);
        gamma_f(y_r, x_r, MPFR_RNDU);
        mpfi_interv_fr(y, y_l(), y_r());
        mpfi_revert_if_needed(y);
        break;
    case 1: {
        // std::cout << __PRETTY_FUNCTION__ << " with N=1 called\n";
        // return df/dx
        // dG(z)/dz = DG(z)*G(z)
        // cftal::test::approx_d2y_dx2(y_l, x_l, gamma_f1, MPFR_RNDD);
        // cftal::test::approx_d2y_dx2(y_r, x_r, gamma_f1, MPFR_RNDU);
        gamma_f1(y_l, x_l, MPFR_RNDD);
        gamma_f1(y_r, x_r, MPFR_RNDU);
        mpfi_interv_fr(y, y_l(), y_r());
        mpfi_revert_if_needed(y);
        break;
    }
    default:
    case 2: {
        // std::cout << __PRETTY_FUNCTION__ << " with N=2 called\n";
        cftal::test::approx_dy_dx(y_l, x_l, gamma_f1, MPFR_RNDD);
        cftal::test::approx_dy_dx(y_r, x_r, gamma_f1, MPFR_RNDU);
        mpfi_interv_fr(y, y_l(), y_r());
        mpfi_revert_if_needed(y);
        // return d/dx(df/dx)
        // d^2G/dz =
        break;
    }}
    return res;
}

int ext_lngamma(mpfi_t y, mpfi_t x, int f_n)
{
    using cftal::test::fpn_handle;
    int res=0;
    mpfr_prec_t p_y=mpfi_get_prec(y);
    mpfr_prec_t p_x=mpfi_get_prec(x);

    fpn_handle y_l(p_y), y_r(p_y), x_l(p_x), x_r(p_x);

    auto lngamma_f=[](fpn_handle& y,
                      const fpn_handle& x,
                      mpfr_rnd_t rnd)->void {
        mpfr_lngamma(y(), x(), rnd);
    };

    auto lngamma_f1=[](fpn_handle& y,
                       const fpn_handle& x,
                       mpfr_rnd_t rnd)->void {
        mpfr_digamma(y(), x(), rnd);
    };

    mpfi_get_left(x_l(), x);
    mpfi_get_right(x_r(), x);
    switch(f_n) {
    case 0:
        // return the function itself
        lngamma_f(y_l, x_l, MPFR_RNDD);
        lngamma_f(y_r, x_r, MPFR_RNDU);
        mpfi_interv_fr(y, y_l(), y_r());
        mpfi_revert_if_needed(y);
        break;
    case 1: {
        // std::cout << __PRETTY_FUNCTION__ << " with N=1 called\n";
        // return df/dx
        // dG(z)/dz = DG(z)*G(z)
        // cftal::test::approx_d2y_dx2(y_l, x_l, gamma_f1, MPFR_RNDD);
        // cftal::test::approx_d2y_dx2(y_r, x_r, gamma_f1, MPFR_RNDU);
        lngamma_f1(y_l, x_l, MPFR_RNDD);
        lngamma_f1(y_r, x_r, MPFR_RNDU);
        mpfi_interv_fr(y, y_l(), y_r());
        mpfi_revert_if_needed(y);
        break;
    }
    default:
    case 2: {
        // std::cout << __PRETTY_FUNCTION__ << " with N=2 called\n";
        cftal::test::approx_dy_dx(y_l, x_l, lngamma_f1, MPFR_RNDD);
        cftal::test::approx_dy_dx(y_r, x_r, lngamma_f1, MPFR_RNDU);
        mpfi_interv_fr(y, y_l(), y_r());
        mpfi_revert_if_needed(y);
        // return d/dx(df/dx)
        // d^2G/dz =
        break;
    }}
    return res;
}

int ext_j0(mpfi_t y, mpfi_t x, int f_n)
{
    using cftal::test::fpn_handle;
    int res=0;
    mpfr_prec_t p_y=mpfi_get_prec(y);
    mpfr_prec_t p_x=mpfi_get_prec(x);
    fpn_handle y_l(p_y), y_r(p_y), x_l(p_x), x_r(p_x);
    mpfi_get_left(x_l(), x);
    mpfi_get_right(x_r(), x);

    auto f=[](fpn_handle& y, const fpn_handle& x, mpfr_rnd_t rm)->void {
        mpfr_j0(y(), x(), rm);
    };
    auto f1=[](fpn_handle& y, const fpn_handle& x, mpfr_rnd_t rm)->void {
        // d/dx j0 = -j1
        fpn_handle ny(y);
        mpfr_j1(ny(), x(), rm);
        mpfr_neg(y(), ny(), MPFR_RNDN);
    };
    auto f2=[](fpn_handle& y, const fpn_handle& x, mpfr_rnd_t rm)->void {
        // d2/dx2 j0 = -(j0-j2)/2 = (j2-j0)/2
        fpn_handle j0(y), j2(y);
        mpfr_j0(j0(), x(), MPFR_RNDN);
        mpfr_jn(j2(), 2, x(), MPFR_RNDN);
        fpn_handle t(y);
        mpfr_sub(t(), j2(), j0(), rm);
        mpfr_mul_2si(y(), t(), -1, MPFR_RNDN);
    };

    switch (f_n) {
    case 0:
        f(y_l, x_l, MPFR_RNDD);
        f(y_r, x_r, MPFR_RNDU);
        break;
    case 1:
        f1(y_l, x_l, MPFR_RNDD);
        f1(y_r, x_r, MPFR_RNDU);
        break;
    case 2:
        f2(y_l, x_l, MPFR_RNDD);
        f2(y_r, x_r, MPFR_RNDU);
        break;
    default:
        break;
    }
    mpfi_interv_fr(y, y_l(), y_r());
    mpfi_revert_if_needed(y);
    return res;
}

int ext_j1(mpfi_t y, mpfi_t x, int f_n)
{
    using cftal::test::fpn_handle;
    int res=0;
    mpfr_prec_t p_y=mpfi_get_prec(y);
    mpfr_prec_t p_x=mpfi_get_prec(x);
    fpn_handle y_l(p_y), y_r(p_y), x_l(p_x), x_r(p_x);
    mpfi_get_left(x_l(), x);
    mpfi_get_right(x_r(), x);

    auto f=[](fpn_handle& y, const fpn_handle& x, mpfr_rnd_t rm)->void {
        mpfr_j1(y(), x(), rm);
    };
    auto f1=[](fpn_handle& y, const fpn_handle& x, mpfr_rnd_t rm)->void {
        // d/dx j1 = (j0-j2)/2
        fpn_handle j0(y), j2(y);
        mpfr_j0(j0(), x(), MPFR_RNDN);
        mpfr_jn(j2(), 2, x(), MPFR_RNDN);
        fpn_handle t(y);
        mpfr_sub(t(), j0(), j2(), rm);
        mpfr_mul_2si(y(), t(), -1, MPFR_RNDN);
    };
    auto f2=[](fpn_handle& y, const fpn_handle& x, mpfr_rnd_t rm)->void {
        // d2/dx2 j1 = (j3-3*j1)/4
        fpn_handle j3(y), j1(y);
        mpfr_j1(j1(), x(), MPFR_RNDN);
        mpfr_jn(j3(), 3, x(), MPFR_RNDN);
        fpn_handle t(3.0, y.prec());
        mpfr_mul(t(), j1(), t(), MPFR_RNDN);
        mpfr_sub(t(), j3(), t(), rm);
        // y = t*2^-2 = t/4
        mpfr_mul_2si(y(), t(), -2, MPFR_RNDN);
    };
    switch (f_n) {
    case 0:
        f(y_l, x_l, MPFR_RNDD);
        f(y_r, x_r, MPFR_RNDU);
        break;
    case 1:
        f1(y_l, x_l, MPFR_RNDD);
        f1(y_r, x_r, MPFR_RNDU);
        break;
    case 2:
        f2(y_l, x_l, MPFR_RNDD);
        f2(y_r, x_r, MPFR_RNDU);
        break;
    default:
        break;
    }
    mpfi_interv_fr(y, y_l(), y_r());
    mpfi_revert_if_needed(y);
    return res;
}

int ext_y0(mpfi_t y, mpfi_t x, int f_n)
{
    using cftal::test::fpn_handle;
    int res=0;
    mpfr_prec_t p_y=mpfi_get_prec(y);
    mpfr_prec_t p_x=mpfi_get_prec(x);
    fpn_handle y_l(p_y), y_r(p_y), x_l(p_x), x_r(p_x);
    mpfi_get_left(x_l(), x);
    mpfi_get_right(x_r(), x);

    auto f=[](fpn_handle& y, const fpn_handle& x, mpfr_rnd_t rm)->void {
        mpfr_y0(y(), x(), rm);
    };
    auto f1=[](fpn_handle& y, const fpn_handle& x, mpfr_rnd_t rm)->void {
        // d/dx j0 = -y1
        fpn_handle ny(y);
        mpfr_y1(ny(), x(), rm);
        mpfr_neg(y(), ny(), MPFR_RNDN);
    };
    auto f2=[](fpn_handle& y, const fpn_handle& x, mpfr_rnd_t rm)->void {
        // d2/dx2 y0 = -(y0-y2)/2 = (y2-y0)/2
        fpn_handle y0(y), y2(y);
        mpfr_y0(y0(), x(), MPFR_RNDN);
        mpfr_yn(y2(), 2, x(), MPFR_RNDN);
        fpn_handle t(y);
        mpfr_sub(t(), y2(), y0(), rm);
        mpfr_mul_2si(y(), t(), -1, MPFR_RNDN);
    };
    switch (f_n) {
    case 0:
        f(y_l, x_l, MPFR_RNDD);
        f(y_r, x_r, MPFR_RNDU);
        break;
    case 1:
        f1(y_l, x_l, MPFR_RNDD);
        f1(y_r, x_r, MPFR_RNDU);
        break;
    case 2:
        f2(y_l, x_l, MPFR_RNDD);
        f2(y_r, x_r, MPFR_RNDU);
        break;
    default:
        break;
    }
    mpfi_interv_fr(y, y_l(), y_r());
    mpfi_revert_if_needed(y);
    return res;
}

int ext_y1(mpfi_t y, mpfi_t x, int f_n)
{
    using cftal::test::fpn_handle;
    int res=0;
    mpfr_prec_t p_y=mpfi_get_prec(y);
    mpfr_prec_t p_x=mpfi_get_prec(x);
    fpn_handle y_l(p_y), y_r(p_y), x_l(p_x), x_r(p_x);
    mpfi_get_left(x_l(), x);
    mpfi_get_right(x_r(), x);

    auto f=[](fpn_handle& y, const fpn_handle& x, mpfr_rnd_t rm)->void {
        mpfr_y1(y(), x(), rm);
    };
    auto f1=[](fpn_handle& y, const fpn_handle& x, mpfr_rnd_t rm)->void {
        // d/dx y1 = (y0-y2)/2
        fpn_handle y0(y), y2(y);
        mpfr_y0(y0(), x(), MPFR_RNDN);
        mpfr_yn(y2(), 2, x(), MPFR_RNDN);
        fpn_handle t(y);
        mpfr_sub(t(), y0(), y2(), rm);
        mpfr_mul_2si(y(), t(), -1, MPFR_RNDN);
    };
    auto f2=[](fpn_handle& y, const fpn_handle& x, mpfr_rnd_t rm)->void {
        // d2/dx2 y1 = (y3-3*y1)/4
        fpn_handle y3(y), y1(y);
        mpfr_y1(y1(), x(), MPFR_RNDN);
        mpfr_yn(y3(), 3, x(), MPFR_RNDN);
        fpn_handle t(3.0, y.prec());
        mpfr_mul(t(), y1(), t(), MPFR_RNDN);
        mpfr_sub(t(), y3(), t(), rm);
        // y = t*2^-2 = t/4
        mpfr_mul_2si(y(), t(), -2, MPFR_RNDN);
    };
    switch (f_n) {
    case 0:
        f(y_l, x_l, MPFR_RNDD);
        f(y_r, x_r, MPFR_RNDU);
        break;
    case 1:
        f1(y_l, x_l, MPFR_RNDD);
        f1(y_r, x_r, MPFR_RNDU);
        break;
    case 2:
        f2(y_l, x_l, MPFR_RNDD);
        f2(y_r, x_r, MPFR_RNDU);
        break;
    default:
        break;
    }
    mpfi_interv_fr(y, y_l(), y_r());
    mpfi_revert_if_needed(y);
    return res;
}

void ext_euler_gamma(mpfr_t res, mp_prec_t prec)
{
    mpfr_set_prec(res, prec);
    mpfr_const_euler(res, GMP_RNDN);
}
