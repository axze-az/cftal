//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <cftal/test/call_mpfr.h>
#include <cftal/test/mpfr_cache.h>
#include <mutex>
#include <cstdarg>
#include <vector>

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
#if 0
    MPFR_DECL_INIT(r, 53);
    mpfr_set_d(ai, a, GMP_RNDN);
    int mpres=f(r, ai, GMP_RNDN);
    double dr=mpfr_get_d(r, GMP_RNDN);
#else
    mpfr_cache::mpfr_result<double> c;
    auto pf= mpfr_cache::result(a, f, c);
    if (pf == nullptr) {
        MPFR_DECL_INIT(ai, 53);
        MPFR_DECL_INIT(r, 53);
        mpfr_set_d(ai, a, GMP_RNDN);
        int mpres=f(r, ai, GMP_RNDN);
        double dr=mpfr_get_d(r, GMP_RNDN);
        c._mpfr_res= mpres;
        c._res = dr;
        mpfr_cache::update(a, f, c);
    }
    double dr=c._res;
    int mpres=c._mpfr_res;
#endif
    if (ulp1i != nullptr) {
        *ulp1i=ulp1_interval(dr, mpres);
    }
    return dr;
}

double
cftal::test::call_mpfr::
func(int32_t* ip, double a, f1i_t f, std::pair<double, double>* ulp1i)
{
    MPFR_DECL_INIT(ai, 53);
    MPFR_DECL_INIT(r, 53);
    mpfr_set_d(ai, a, GMP_RNDN);
    int mpres=f(r, ip, ai, GMP_RNDN);
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
#if 0
    MPFR_DECL_INIT(ai, 24);
    MPFR_DECL_INIT(r, 24);
    mpfr_set_flt(ai, a, GMP_RNDN);
    int mpres=f(r, ai, GMP_RNDN);
    float dr=mpfr_get_flt(r, GMP_RNDN);
#else
    mpfr_cache::mpfr_result<float> c;
    auto pf= mpfr_cache::result(a, f, c);
    if (pf == nullptr) {
        MPFR_DECL_INIT(ai, 24);
        MPFR_DECL_INIT(r, 24);
        mpfr_set_flt(ai, a, GMP_RNDN);
        int mpres=f(r, ai, GMP_RNDN);
        float dr=mpfr_get_flt(r, GMP_RNDN);
        c._mpfr_res= mpres;
        c._res = dr;
        mpfr_cache::update(a, f, c);
    }
    float dr=c._res;
    int mpres=c._mpfr_res;
#endif
    if (ulp1i != nullptr) {
        *ulp1i=ulp1_interval(dr, mpres);
    }
    return dr;
}

float
cftal::test::call_mpfr::
func(int32_t* ip, float a, f1i_t f, std::pair<float, float>* ulp1i)
{
    MPFR_DECL_INIT(ai, 24);
    MPFR_DECL_INIT(r, 24);
    mpfr_set_flt(ai, a, GMP_RNDN);
    int mpres=f(r, ip, ai, GMP_RNDN);
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

namespace cftal {
    namespace test {
        namespace mpfr_ext {

            template <typename _F>
            class cbase {
            private:
                fpn_handle _v;
                std::mutex _v_mtx;
            public:
                cbase();
                int
                load(mpfr_t y, mpfr_rnd_t rm);
            };


            struct calc_log10 {
                int
                operator()(mpfr_t y, mpfr_rnd_t rm)
                    const;
            };

            static cbase<calc_log10> const_log10;

            struct calc_log2 {
                int
                operator()(mpfr_t y, mpfr_rnd_t rm)
                    const;
            };

            static cbase<calc_log2> const_log2;
        }
    }
}

template <typename _F>
cftal::test::mpfr_ext::cbase<_F>::cbase() : _v(128), _v_mtx()
{
    _F f;
    f(_v(), MPFR_RNDN);
}

template <typename _F>
int
cftal::test::mpfr_ext::cbase<_F>::
load(mpfr_t y, mpfr_rnd_t rm)
{
    std::unique_lock<std::mutex> _l(_v_mtx);
    auto yp=mpfr_get_prec(y);
    if (mpfr_get_prec(_v()) < yp) {
        mpfr_set_prec(_v(), yp+3);
        _F f;
        f(_v(), MPFR_RNDN);
    }
    return mpfr_set(y, _v(), rm);
}

int
cftal::test::mpfr_ext::
calc_log10::operator()(mpfr_t y, mpfr_rnd_t rm)
    const
{
    fpn_handle ten(32);
    mpfr_set_ui(ten(), 10, MPFR_RNDN);
    return mpfr_log(y, ten(), rm);
}

int
cftal::test::mpfr_ext::
calc_log2::operator()(mpfr_t y, mpfr_rnd_t rm)
    const
{
    fpn_handle two(32);
    mpfr_set_ui(two(), 2, MPFR_RNDN);
    return mpfr_log(y, two(), rm);
}

int
cftal::test::mpfr_ext::
exp10(mpfr_t res, const mpfr_t x, mpfr_rnd_t rm)
{
    auto f=[](mpfr_t rr, const mpfr_t xx, mpfr_rnd_t rm)->int {
        fpn_handle xln10(mpfr_get_prec(xx));
        fpn_handle ln10(mpfr_get_prec(xx));
        const_log10.load(ln10(), rm);
        mpfr_mul(xln10(), xx, ln10(), rm);
        int r=mpfr_exp(rr, xln10(), rm);
        return r;
    };
    int r= call_ziv_func(res, x, rm, f);
    return r;
}

int
cftal::test::mpfr_ext::
exp2m1(mpfr_t res, const mpfr_t src, mpfr_rnd_t rm)
{
#if 1
    auto f=[](mpfr_t rr, const mpfr_t xx, mpfr_rnd_t rm)->int {
        fpn_handle xln2(mpfr_get_prec(xx));
        fpn_handle ln2(mpfr_get_prec(xx));
        const_log2.load(ln2(), rm);
        mpfr_mul(xln2(), xx, ln2(), rm);
        int r=mpfr_expm1(rr, xln2(), rm);
        return r;
    };
    int r= call_ziv_func(res, src, rm, f);
    return r;
#else
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
        mpfr_set_prec(t(), 32);
        break;
    case 53:
        prec_inc=32;
        mpfr_set_prec(t(), 64);
        break;
    default:
        break;
    }
    do {
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
        mpfr_set_prec(t(), t.prec()+prec_inc);
    } while (!mpfr_equal_or_nan(u(), res) &&
             ((inexact_exp2m1_1 >= 0 && inexact_exp2m1_2 <=0) ||
             (inexact_exp2m1_1 <= 0 && inexact_exp2m1_2 >=0)));
#if DEBUG_EXP2M1>0
    tt= mpfr_get_d(res, MPFR_RNDN);
    std::cout << "result is " << tt << std::endl;
#endif
    return inexact_exp2m1_1;
#endif
}

int
cftal::test::mpfr_ext::
exp10m1(mpfr_t res, const mpfr_t src, mpfr_rnd_t rm)
{
#if 1
    auto f=[](mpfr_t rr, const mpfr_t xx, mpfr_rnd_t rm)->int {
        fpn_handle xln10(mpfr_get_prec(xx));
        fpn_handle ln10(mpfr_get_prec(xx));
        const_log10.load(ln10(), rm);
        mpfr_mul(xln10(), xx, ln10(), rm);
        int r=mpfr_expm1(rr, xln10(), rm);
        return r;
    };
    return call_ziv_func(res, src, rm, f);
#else
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
        mpfr_set_prec(t(), 32);
        break;
    case 53:
        prec_inc=32;
        mpfr_set_prec(t(), 64);
        break;
    default:
        break;
    }
    do {
        inexact_exp10= mpfr_exp10(t(), src, MPFR_RNDD);
        inexact_exp10m1_1 = mpfr_sub_ui(res, t(), 1, rm);
        if (inexact_exp10 == 0) {
            break;
        }
        // round up exp10 to the next larger number
        mpfr_nextabove(t());
        // and repeat the subtraction
        inexact_exp10m1_2 = mpfr_sub_ui(u(), t(), 1, rm);
        mpfr_set_prec(t(), t.prec()+prec_inc);
    } while (!mpfr_equal_or_nan(u(), res) &&
             ((inexact_exp10m1_1 >= 0 && inexact_exp10m1_2 <=0) ||
             (inexact_exp10m1_1 <= 0 && inexact_exp10m1_2 >=0)));
    return inexact_exp10m1_1;
#endif
}

int
cftal::test::mpfr_ext::
exp_px2(mpfr_t res, const mpfr_t x, mpfr_rnd_t rm)
{
    fpn_handle px2(2*mpfr_get_prec(x)+2);
    // exact:
    mpfr_sqr(px2(), x, MPFR_RNDN);
    int r=mpfr_exp(res, px2(), rm);
    return r;
}

int
cftal::test::mpfr_ext::
exp_mx2(mpfr_t res, const mpfr_t x, mpfr_rnd_t rm)
{
    fpn_handle mx2(2*mpfr_get_prec(x)+2);
    // exact:
    mpfr_sqr(mx2(), x, MPFR_RNDN);
    mpfr_neg(mx2(), mx2(), MPFR_RNDN);
    int r=mpfr_exp(res, mx2(), rm);
    return r;
}

int
cftal::test::mpfr_ext::
exp2_px2(mpfr_t res, const mpfr_t x, mpfr_rnd_t rm)
{
    fpn_handle px2(2*mpfr_get_prec(x)+2);
    // exact:
    mpfr_sqr(px2(), x, MPFR_RNDN);
    int r=mpfr_exp2(res, px2(), rm);
    return r;
}

int
cftal::test::mpfr_ext::
exp2_mx2(mpfr_t res, const mpfr_t x, mpfr_rnd_t rm)
{
    fpn_handle mx2(2*mpfr_get_prec(x)+2);
    // exact:
    mpfr_sqr(mx2(), x, MPFR_RNDN);
    mpfr_neg(mx2(), mx2(), MPFR_RNDN);
    int r=mpfr_exp2(res, mx2(), rm);
    return r;
}

int
cftal::test::mpfr_ext::
exp10_px2(mpfr_t res, const mpfr_t x, mpfr_rnd_t rm)
{
    fpn_handle px2(2*mpfr_get_prec(x)+2);
    // exact:
    mpfr_sqr(px2(), x, MPFR_RNDN);
    int r=exp10(res, px2(), rm);
    return r;
}

int
cftal::test::mpfr_ext::
exp10_mx2(mpfr_t res, const mpfr_t x, mpfr_rnd_t rm)
{
    fpn_handle mx2(2*mpfr_get_prec(x)+2);
    // exact:
    mpfr_sqr(mx2(), x, MPFR_RNDN);
    mpfr_neg(mx2(), mx2(), MPFR_RNDN);
    int r=exp10(res, mx2(), rm);
    return r;
}

int
cftal::test::mpfr_ext::
root12(mpfr_t res,
       const mpfr_t x,
       mpfr_rnd_t rm)
{
#if MPFR_VERSION_MAJOR<4
    return mpfr_root(res, x, 12, rm);
#else
    return mpfr_rootn_ui(res, x, 12, rm);
#endif
}

int
cftal::test::mpfr_ext::
horner(mpfr_t res,
       const mpfr_t x,
       mpfr_rnd_t rm,
       const mpfr_t c_n,
       ...)
{
    std::vector<const __mpfr_struct*> vcx;
    std::va_list va;
    const __mpfr_struct* c= c_n;
    vcx.push_back(c);
    va_start(va, c_n);
    while ((c =va_arg(va, const __mpfr_struct*)) != nullptr) {
        vcx.push_back(c);
    }
    va_end(va);

    auto f=[&vcx](mpfr_t rr, const mpfr_t xx, mpfr_rnd_t rm)->int {
        fpn_handle r(mpfr_get_prec(xx));
        const __mpfr_struct* cn=vcx[0];
        mpfr_set(r(), cn, rm);
        for (std::size_t i=1; i< vcx.size(); ++i) {
            mpfr_mul(r(), xx, r(), rm);
            const __mpfr_struct* cnm1= vcx[i];
            mpfr_add(r(), r(), cnm1, rm);
        }
        return mpfr_set(rr, r(), rm);
    };
    return call_ziv_func(res, x, rm, f);

}
