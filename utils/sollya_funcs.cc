//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// all the functions below are terrible hacks
#include <mpfr.h>
#define __gmp_const const
#include <mpfi.h>
#include <sollya.h>
#include "cftal/test/call_mpfr.h"
#include <iostream>
#include <iomanip>
#include <vector>

// ext_tgamma = library("./libsollya_funcs.so");
extern "C"
int ext_tgamma(mpfi_t rop, mpfi_t op, int n);

// ext_lngamma = library("./libsollya_funcs.so");
extern "C"
int ext_lngamma(mpfi_t rop, mpfi_t op, int n);

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
