//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <cftal/test/call_mpfr.h>

#define DEBUG_EXP2M1 0
#define DEBUG_EXPXM1 (DEBUG_EXP2M1)
#if DEBUG_EXPXM1 > 0
#include <iostream>
#include <iomanip>
#endif

double
cftal::test::call_mpfr::
func(double a, f1_t f, std::pair<double, double>* ulp1i)
{
    MPFR_DECL_INIT(ai, 53);
    MPFR_DECL_INIT(r, 53);
    mpfr_set_d(ai, a, GMP_RNDN);
    int mpres=f(r, ai, GMP_RNDN);
    double dr=mpfr_get_d(r, GMP_RNDN);
    if (ulp1i != nullptr) {
        *ulp1i=ulp1_interval(dr, mpres);
    }
    return dr;
}

double
cftal::test::call_mpfr::
func(double a, double b, f2_t f, std::pair<double, double>* ulp1i)
{
    MPFR_DECL_INIT(ai, 53);
    MPFR_DECL_INIT(bi, 53);
    MPFR_DECL_INIT(r, 53);
    mpfr_set_d(ai, a, GMP_RNDN);
    mpfr_set_d(bi, b, GMP_RNDN);
    int mpres=f(r, ai, bi, GMP_RNDN);
    double dr=mpfr_get_d(r, GMP_RNDN);
    if (ulp1i != nullptr) {
        *ulp1i=ulp1_interval(dr, mpres);
    }
    return dr;
}

float
cftal::test::call_mpfr::
func(float a, f1_t f, std::pair<float, float>* ulp1i)
{
    MPFR_DECL_INIT(ai, 24);
    MPFR_DECL_INIT(r, 24);
    mpfr_set_flt(ai, a, GMP_RNDN);
    int mpres=f(r, ai, GMP_RNDN);
    float dr=mpfr_get_flt(r, GMP_RNDN);
    if (ulp1i != nullptr) {
        *ulp1i=ulp1_interval(dr, mpres);
    }
    return dr;
}

float
cftal::test::call_mpfr::
func(float a, float b, f2_t f, std::pair<float, float>* ulp1i)
{
    MPFR_DECL_INIT(ai, 24);
    MPFR_DECL_INIT(bi, 24);
    MPFR_DECL_INIT(r, 24);
    mpfr_set_flt(ai, a, GMP_RNDN);
    mpfr_set_flt(bi, b, GMP_RNDN);
    int mpres=f(r, ai, bi, GMP_RNDN);
    float dr=mpfr_get_flt(r, GMP_RNDN);
    if (ulp1i != nullptr) {
        *ulp1i=ulp1_interval(dr, mpres);
    }
    return dr;
}

int
cftal::test::mpfr_ext::
exp2(mpfr_t res, const mpfr_t x, mpfr_rnd_t rm)
{
    // exp2(x) = exp(x * M_LN2)
    fpn_handle ln2(mpfr_get_prec(x));
    fpn_handle xln2(mpfr_get_prec(x)*2+32+16);
    fpn_handle res_last(mpfr_get_prec(res));
    int i1=~0, i2=~0;
#if DEBUG_EXPXM1>0
    std::cout << "calculating exp2 "
              << mpfr_get_d(x, rm)
              << std::endl;
#endif
    do {
#if DEBUG_EXPXM1>0
        std::cout << mpfr_get_prec(ln2()) << std::endl;
#endif
        mpfr_const_log2(ln2(), rm);
        if (mpfr_mul(xln2(), x, ln2(), rm)!=0) {
            std::abort();
            // std::cout << "oops " << std::endl;
            break;
        }
        i2=mpfr_exp(res, xln2(), rm);
        if ((i1 == i2) &&
            ((mpfr_nan_p(res) && mpfr_nan_p(res_last())) ||
             (mpfr_cmp(res, res_last())==0)))
            break;
        i1=i2;
        res_last = res;
        mpfr_set_prec(ln2(), ln2.prec() + 32);
        mpfr_set_prec(xln2(), mpfr_get_prec(x) + ln2.prec()+16);
    } while (1);
#if DEBUG_EXPXM1>0
    fpn_handle e2(res);
    int i3=mpfr_exp2(res, x, rm);

    if ((i2 != i3) ||
        ((mpfr_cmp(res, e2()) !=0) &&
         (mpfr_nan_p(e2()) == 0))) {
        std::cout << std::hexfloat;
        std::cout << "invalid result from exp2 "
                  << mpfr_get_d(x, rm)
                  << std::endl
                  << mpfr_get_d(res, rm)
                  << std::endl
                  << mpfr_get_d(e2(), rm)
                  << std::endl;
        std::cout << std::scientific;
    }
#endif
    return i2;
}

namespace {
    bool
    mpfr_equal_or_nan(const mpfr_t a, const mpfr_t b)
    {
        return (mpfr_nan_p(a) && mpfr_nan_p(b)) ||
            (mpfr_cmp(a, b)==0);
    }

}

int
cftal::test::mpfr_ext::
exp2m1(mpfr_t res, const mpfr_t src, mpfr_rnd_t rm)
{
    mpfr_prec_t tgt_prec=mpfr_get_prec(res);
    fpn_handle t(tgt_prec);
    fpn_handle u(tgt_prec);
    int inexact_exp2 = ~0;
    int inexact_exp2m1_1 = ~0;
    int inexact_exp2m1_2 = ~0;
#if DEBUG_EXP2M1>0
    double tt=mpfr_get_d(src, MPFR_RNDN);
    std::cout << "exp2m1 of " << tt << std::endl;
#endif
    mpfr_prec_t prec_inc=16;
    switch (tgt_prec) {
    case 24:
        prec_inc=16;
        mpfr_set_prec(t(), 32-prec_inc);
        break;
    case 53:
        prec_inc=32;
        mpfr_set_prec(t(), 64-prec_inc);
        break;
    default:
        break;
    }
    do {
        mpfr_set_prec(t(), t.prec()+prec_inc);
#if DEBUG_EXP2M1>0
        if (t.prec()>64)
            std::cout << "using precision " << t.prec() << std::endl;
#endif
        inexact_exp2= mpfr_exp2(t(), src, MPFR_RNDD);
        inexact_exp2m1_1 = mpfr_sub_ui(res, t(), 1, rm);
        if (inexact_exp2 == 0) {
            break;
        }
        // round up exp2 to the next larger number
        mpfr_nextabove(t());
        // and repeat the subtraction
        inexact_exp2m1_2 = mpfr_sub_ui(u(), t(), 1, rm);
        static_cast<void>(inexact_exp2m1_2);
    } while (!mpfr_equal_or_nan(u(), res) &&
             ((inexact_exp2m1_1 >= 0 && inexact_exp2m1_2 <=0) ||
             (inexact_exp2m1_1 <= 0 && inexact_exp2m1_2 >=0)));
#if DEBUG_EXP2M1>0
    tt= mpfr_get_d(res, MPFR_RNDN);
    std::cout << "result is " << tt << std::endl;
#endif
    return inexact_exp2m1_1;
}

int
cftal::test::mpfr_ext::
exp10m1(mpfr_t res, const mpfr_t src, mpfr_rnd_t rm)
{
    mpfr_prec_t tgt_prec=mpfr_get_prec(res);
    fpn_handle t(tgt_prec);
    fpn_handle u(tgt_prec);
    int inexact_exp10 = ~0;
    int inexact_exp10m1_1 = ~0;
    int inexact_exp10m1_2 = ~0;
    mpfr_prec_t prec_inc=16;
    switch (tgt_prec) {
    case 24:
        prec_inc=16;
        mpfr_set_prec(t(), 32-prec_inc);
        break;
    case 53:
        prec_inc=32;
        mpfr_set_prec(t(), 64-prec_inc);
        break;
    default:
        break;
    }
    do {
        mpfr_set_prec(t(), t.prec()+prec_inc);
        inexact_exp10= mpfr_exp10(t(), src, MPFR_RNDD);
        inexact_exp10m1_1 = mpfr_sub_ui(res, t(), 1, rm);
        if (inexact_exp10 == 0) {
            break;
        }
        // round up exp2 to the next larger number
        mpfr_nextabove(t());
        // and repeat the subtraction
        inexact_exp10m1_2 = mpfr_sub_ui(u(), t(), 1, rm);
    } while (!mpfr_equal_or_nan(u(), res) &&
             ((inexact_exp10m1_1 >= 0 && inexact_exp10m1_2 <=0) ||
             (inexact_exp10m1_1 <= 0 && inexact_exp10m1_2 >=0)));
    return inexact_exp10m1_1;
}
