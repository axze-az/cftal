//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <cftal/test/call_mpfr.h>

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
exp2m1(mpfr_t res, const mpfr_t src, mpfr_rnd_t rm)
{
    mpfr_prec_t tgt_prec=mpfr_get_prec(res);
    fpn_handle t(tgt_prec);
    fpn_handle u(tgt_prec);
    int inexact_exp2 = ~0;
    int inexact_exp2m1_1 = ~0;
    int inexact_exp2m1_2 = ~0;
    do {
        mpfr_set_prec(t(), t.prec()+8);
        inexact_exp2= mpfr_exp2(t(), src, MPFR_RNDZ);
        inexact_exp2m1_1 = mpfr_sub_ui(res, t(), 1, rm);
        if (inexact_exp2 == 0) {
            break;
        }
        // round up exp2 to the next larger number
        mpfr_nextabove(t());
        // and repeat the subtraction
        inexact_exp2m1_2 = mpfr_sub_ui(u(), t(), 1, rm);
    } while ( ((inexact_exp2m1_1 !=0) != (inexact_exp2m1_2 !=0))
            || (mpfr_cmp(u(), res) != 0));
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
    do {
        mpfr_set_prec(t(), t.prec()+8);
        inexact_exp10= mpfr_exp10(t(), src, MPFR_RNDZ);
        inexact_exp10m1_1 = mpfr_sub_ui(res, t(), 1, rm);
        if (inexact_exp10 == 0) {
            break;
        }
        // round up exp2 to the next larger number
        mpfr_nextabove(t());
        // and repeat the subtraction
        inexact_exp10m1_2 = mpfr_sub_ui(u(), t(), 1, rm);
    } while ( ((inexact_exp10m1_1 !=0) != (inexact_exp10m1_2 !=0))
            || (mpfr_cmp(u(), res) != 0));
    return inexact_exp10m1_1;
}
