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
#include <iostream>
#include <cftal/test/call_mpfr.h>
#include <cftal/test/mpfr_cache.h>
#include <mutex>
#include <cstdarg>
#include <vector>
#include <iomanip>

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
    mpfr_cache::f1_mpfr_result<double> c;
    auto pf= mpfr_cache::result(a, f, c);
    if (pf == nullptr) {
        double_emin_emax g;
        MPFR_DECL_INIT(ai, 53);
        MPFR_DECL_INIT(r, 53);
        mpfr_set_d(ai, a, MPFR_RNDN);
        int mpres=f(r, ai, MPFR_RNDN);
        mpres=mpfr_subnormalize(r, mpres, MPFR_RNDN);
        double dr=mpfr_get_d(r, MPFR_RNDN);
        c._mpfr_res= mpres;
        c._res = dr;
        mpfr_cache::update(a, f, c);
    }
    double dr=c._res;
    int mpres=c._mpfr_res;
    if (ulp1i != nullptr) {
        *ulp1i=ulp1_interval(dr, mpres);
    }
    return dr;
}

std::pair<double, double>
cftal::test::call_mpfr::
func(double a, f1p_t f,
     std::pair<double, double>* ulp1i0,
     std::pair<double, double>* ulp1i1)
{
    double_emin_emax g;
    MPFR_DECL_INIT(ai, 53);
    MPFR_DECL_INIT(r0, 53);
    MPFR_DECL_INIT(r1, 53);
    mpfr_set_d(ai, a, MPFR_RNDN);
    int i01=f(r0, r1, ai, MPFR_RNDN);

    int i0 = i01 & 3;
    i0 = i0 > 1 ? -1 : i0;
    i0=mpfr_subnormalize(r0, i0, MPFR_RNDN);
    int i1 = (i01 >> 2) & 3;
    i1 = i1 > 1 ? -1 : i1;
    i1=mpfr_subnormalize(r1, i1, MPFR_RNDN);

    double d0, d1;
    d0 = mpfr_get_d(r0, MPFR_RNDN);
    d1 = mpfr_get_d(r1, MPFR_RNDN);

    if (ulp1i0 != nullptr) {
        *ulp1i0= ulp1_interval(d0, i0);
    }
    if (ulp1i1 != nullptr) {
        *ulp1i1= ulp1_interval(d1, i1);
    }
    return std::make_pair(d0, d1);
}

double
cftal::test::call_mpfr::
func(int32_t* ip, double a, f1i_t f, std::pair<double, double>* ulp1i)
{
    mpfr_cache::f1i_mpfr_result<std::pair<double, int32_t> > c;
    auto pf= mpfr_cache::result(a, f, c);
    if (pf == nullptr) {
        double_emin_emax g;
        MPFR_DECL_INIT(ai, 53);
        MPFR_DECL_INIT(r, 53);
        int32_t i;
        mpfr_set_d(ai, a, MPFR_RNDN);
        int mpres=f(r, &i, ai, MPFR_RNDN);
        mpres=mpfr_subnormalize(r, mpres, MPFR_RNDN);
        double dr=mpfr_get_d(r, MPFR_RNDN);
        c._mpfr_res= mpres;
        c._res = std::make_pair(dr, i);
        mpfr_cache::update(a, f, c);
    }
    if (ip != nullptr) {
        *ip = c._res.second;
    }
    double dr=c._res.first;
    int mpres=c._mpfr_res;
    if (ulp1i != nullptr) {
        *ulp1i=ulp1_interval(dr, mpres);
    }
    return dr;
}

double
cftal::test::call_mpfr::
func(double a, double b, f2_t f, std::pair<double, double>* ulp1i)
{
    mpfr_cache::f2_mpfr_result<double> c;
    auto pf= mpfr_cache::result(a, b, f, c);
    if (pf == nullptr) {
        double_emin_emax g;
        MPFR_DECL_INIT(ai, 53);
        MPFR_DECL_INIT(bi, 53);
        MPFR_DECL_INIT(r, 53);
        mpfr_set_d(ai, a, MPFR_RNDN);
        mpfr_set_d(bi, b, MPFR_RNDN);
        int mpres=f(r, ai, bi, MPFR_RNDN);
        mpres=mpfr_subnormalize(r, mpres, MPFR_RNDN);
        double dr=mpfr_get_d(r, MPFR_RNDN);
        c._mpfr_res= mpres;
        c._res = dr;
        mpfr_cache::update(a, b, f, c);
    }
    double dr=c._res;
    int mpres=c._mpfr_res;
    if (ulp1i != nullptr) {
        *ulp1i=ulp1_interval(dr, mpres);
    }
    return dr;
}

double
cftal::test::call_mpfr::
func(double a, int32_t ib, f2fi_t f, std::pair<double, double>* ulp1i)
{
    double_emin_emax g;
    MPFR_DECL_INIT(ai, 53);
    MPFR_DECL_INIT(r, 53);
    mpfr_set_d(ai, a, GMP_RNDN);
    int mpres=f(r, ai, ib, GMP_RNDN);
    mpres=mpfr_subnormalize(r, mpres, MPFR_RNDN);
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
    mpfr_cache::f1_mpfr_result<float> c;
    auto pf= mpfr_cache::result(a, f, c);
    if (pf == nullptr) {
        float_emin_emax g;
        MPFR_DECL_INIT(ai, 24);
        MPFR_DECL_INIT(r, 24);
        mpfr_set_flt(ai, a, MPFR_RNDN);
        int mpres=f(r, ai, MPFR_RNDN);
        mpres=mpfr_subnormalize(r, mpres, MPFR_RNDN);
        float dr=mpfr_get_flt(r, MPFR_RNDN);
        c._mpfr_res= mpres;
        c._res = dr;
        mpfr_cache::update(a, f, c);
    }
    float dr=c._res;
    int mpres=c._mpfr_res;
    if (ulp1i != nullptr) {
        *ulp1i=ulp1_interval(dr, mpres);
    }
    return dr;
}

std::pair<float, float>
cftal::test::call_mpfr::
func(float a, f1p_t f,
     std::pair<float, float>* ulp1i0,
     std::pair<float, float>* ulp1i1)
{
    float_emin_emax g;
    MPFR_DECL_INIT(ai, 24);
    MPFR_DECL_INIT(r0, 24);
    MPFR_DECL_INIT(r1, 24);
    mpfr_set_flt(ai, a, MPFR_RNDN);
    int i01=f(r0, r1, ai, MPFR_RNDN);

    int i0 = i01 & 3;
    i0 = i0 > 1 ? -1 : i0;
    i0=mpfr_subnormalize(r0, i0, MPFR_RNDN);
    int i1 = (i01 >> 2) & 3;
    i1 = i1 > 1 ? -1 : i1;
    i1=mpfr_subnormalize(r1, i1, MPFR_RNDN);

    float d0, d1;
    d0 = mpfr_get_flt(r0, MPFR_RNDN);
    d1 = mpfr_get_flt(r1, MPFR_RNDN);

    if (ulp1i0 != nullptr) {
        *ulp1i0= ulp1_interval(d0, i0);
    }
    if (ulp1i1 != nullptr) {
        *ulp1i1= ulp1_interval(d1, i1);
    }
    return std::make_pair(d0, d1);
}

float
cftal::test::call_mpfr::
func(int32_t* ip, float a, f1i_t f, std::pair<float, float>* ulp1i)
{
    mpfr_cache::f1i_mpfr_result<std::pair<float, int32_t> > c;
    auto pf= mpfr_cache::result(a, f, c);
    if (pf == nullptr) {
        float_emin_emax g;
        MPFR_DECL_INIT(ai, 24);
        MPFR_DECL_INIT(r, 24);
        int32_t i;
        mpfr_set_flt(ai, a, MPFR_RNDN);
        int mpres=f(r, &i, ai, MPFR_RNDN);
        mpres=mpfr_subnormalize(r, mpres, MPFR_RNDN);
        float dr=mpfr_get_flt(r, MPFR_RNDN);
        c._mpfr_res= mpres;
        c._res = std::make_pair(dr, i);
        mpfr_cache::update(a, f, c);
    }
    if (ip != nullptr) {
        *ip = c._res.second;
    }
    float dr=c._res.first;
    int mpres=c._mpfr_res;
    if (ulp1i != nullptr) {
        *ulp1i=ulp1_interval(dr, mpres);
    }
    return dr;
}

float
cftal::test::call_mpfr::
func(float a, float b, f2_t f, std::pair<float, float>* ulp1i)
{
    mpfr_cache::f2_mpfr_result<float> c;
    auto pf= mpfr_cache::result(a, b, f, c);
    if (pf == nullptr) {
        float_emin_emax g;
        MPFR_DECL_INIT(ai, 24);
        MPFR_DECL_INIT(bi, 24);
        MPFR_DECL_INIT(r, 24);
        mpfr_set_flt(ai, a, MPFR_RNDN);
        mpfr_set_flt(bi, b, MPFR_RNDN);
        int mpres=f(r, ai, bi, MPFR_RNDN);
        mpres=mpfr_subnormalize(r, mpres, MPFR_RNDN);
        float dr=mpfr_get_flt(r, MPFR_RNDN);
        c._mpfr_res= mpres;
        c._res = dr;
        mpfr_cache::update(a, b, f, c);
    }
    float dr=c._res;
    int mpres=c._mpfr_res;
    if (ulp1i != nullptr) {
        *ulp1i=ulp1_interval(dr, mpres);
    }
    return dr;
}

float
cftal::test::call_mpfr::
func(float a, int ib, f2fi_t f, std::pair<float, float>* ulp1i)
{
    float_emin_emax g;
    MPFR_DECL_INIT(ai, 24);
    MPFR_DECL_INIT(r, 24);
    mpfr_set_flt(ai, a, GMP_RNDN);
    int mpres=f(r, ai, ib, GMP_RNDN);
    mpres=mpfr_subnormalize(r, mpres, MPFR_RNDN);
    float dr=mpfr_get_flt(r, GMP_RNDN);
    if (ulp1i != nullptr) {
        *ulp1i=ulp1_interval(dr, mpres);
    }
    return dr;
}

cftal::f16_t
cftal::test::call_mpfr::
func(f16_t a, f1_t f, std::pair<f16_t, f16_t>* ulp1i)
{
    mpfr_cache::f1_mpfr_result<f16_t> c;
    // auto pf= mpfr_cache::result(a, f, c);
    auto pf=nullptr;
    if (pf == nullptr) {
        half_emin_emax g;
        MPFR_DECL_INIT(ai, 11);
        MPFR_DECL_INIT(r, 11);
        float fa=cvt_f16_to_f32(read_bits(a));
        mpfr_set_flt(ai, fa, MPFR_RNDN);
        int mpres=f(r, ai, MPFR_RNDN);
        mpres=mpfr_subnormalize(r, mpres, MPFR_RNDN);
        float fdr=mpfr_get_flt(r, MPFR_RNDN);
        c._mpfr_res= mpres;
        c._res = f16_t(fdr);
        // mpfr_cache::update(a, f, c);
    }
    f16_t dr=c._res;
    int mpres=c._mpfr_res;
    if (ulp1i != nullptr) {
        *ulp1i=ulp1_interval(dr, mpres);
    }
    return dr;
}

std::pair<cftal::f16_t, cftal::f16_t>
cftal::test::call_mpfr::
func(f16_t a, f1p_t f,
     std::pair<f16_t, f16_t>* ulp1i0,
     std::pair<f16_t, f16_t>* ulp1i1)
{
    half_emin_emax g;
    MPFR_DECL_INIT(ai, 11);
    MPFR_DECL_INIT(r0, 11);
    MPFR_DECL_INIT(r1, 11);
    float fa=cvt_f16_to_f32(read_bits(a));
    mpfr_set_flt(ai, fa, MPFR_RNDN);
    int i01=f(r0, r1, ai, MPFR_RNDN);

    int i0 = i01 & 3;
    i0 = i0 > 1 ? -1 : i0;
    i0=mpfr_subnormalize(r0, i0, MPFR_RNDN);
    int i1 = (i01 >> 2) & 3;
    i1 = i1 > 1 ? -1 : i1;
    i1=mpfr_subnormalize(r1, i1, MPFR_RNDN);

    float fd0, fd1;
    fd0 = mpfr_get_flt(r0, MPFR_RNDN);
    fd1 = mpfr_get_flt(r1, MPFR_RNDN);
    auto d0=static_cast<f16_t>(fd0);
    auto d1=static_cast<f16_t>(fd1);

    if (ulp1i0 != nullptr) {
        *ulp1i0= ulp1_interval(d0, i0);
    }
    if (ulp1i1 != nullptr) {
        *ulp1i1= ulp1_interval(d1, i1);
    }
    return std::make_pair(d0, d1);
}

cftal::f16_t
cftal::test::call_mpfr::
func(int32_t* ip, f16_t a, f1i_t f, std::pair<f16_t, f16_t>* ulp1i)
{
    mpfr_cache::f1i_mpfr_result<std::pair<f16_t, int32_t> > c;
    // auto pf= mpfr_cache::result(a, f, c);
    auto pf=nullptr;
    if (pf == nullptr) {
        half_emin_emax g;
        MPFR_DECL_INIT(ai, 11);
        MPFR_DECL_INIT(r, 11);
        int32_t i;
        float fa=cvt_f16_to_f32(read_bits(a));
        mpfr_set_flt(ai, fa, MPFR_RNDN);
        int mpres=f(r, &i, ai, MPFR_RNDN);
        mpres=mpfr_subnormalize(r, mpres, MPFR_RNDN);
        float fdr=mpfr_get_flt(r, MPFR_RNDN);
        auto dr=static_cast<f16_t>(fdr);
        c._mpfr_res= mpres;
        c._res = std::make_pair(dr, i);
        // mpfr_cache::update(a, f, c);
    }
    if (ip != nullptr) {
        *ip = c._res.second;
    }
    f16_t dr=c._res.first;
    int mpres=c._mpfr_res;
    if (ulp1i != nullptr) {
        *ulp1i=ulp1_interval(dr, mpres);
    }
    return dr;
}

cftal::f16_t
cftal::test::call_mpfr::
func(f16_t a, f16_t b, f2_t f, std::pair<f16_t, f16_t>* ulp1i)
{
    mpfr_cache::f2_mpfr_result<f16_t> c;
    // auto pf= mpfr_cache::result(a, b, f, c);
    auto pf=nullptr;
    if (pf == nullptr) {
        half_emin_emax g;
        MPFR_DECL_INIT(ai, 11);
        MPFR_DECL_INIT(bi, 11);
        MPFR_DECL_INIT(r, 11);
        float fa=cvt_f16_to_f32(read_bits(a));
        float fb=cvt_f16_to_f32(read_bits(b));
        mpfr_set_flt(ai, fa, MPFR_RNDN);
        mpfr_set_flt(bi, fb, MPFR_RNDN);
        int mpres=f(r, ai, bi, MPFR_RNDN);
        mpres=mpfr_subnormalize(r, mpres, MPFR_RNDN);
        float fdr=mpfr_get_flt(r, MPFR_RNDN);
        auto dr=static_cast<f16_t>(fdr);
        c._mpfr_res= mpres;
        c._res = dr;
        // mpfr_cache::update(a, b, f, c);
    }
    f16_t dr=c._res;
    int mpres=c._mpfr_res;
    if (ulp1i != nullptr) {
        *ulp1i=ulp1_interval(dr, mpres);
    }
    return dr;
}

cftal::f16_t
cftal::test::call_mpfr::
func(f16_t a, int ib, f2fi_t f, std::pair<f16_t, f16_t>* ulp1i)
{
    half_emin_emax g;
    MPFR_DECL_INIT(ai, 11);
    MPFR_DECL_INIT(r, 11);
    float fa=cvt_f16_to_f32(read_bits(a));
    mpfr_set_flt(ai, fa, GMP_RNDN);
    int mpres=f(r, ai, ib, GMP_RNDN);
    mpres=mpfr_subnormalize(r, mpres, MPFR_RNDN);
    float fdr=mpfr_get_flt(r, GMP_RNDN);
    auto dr=static_cast<f16_t>(fdr);
    if (ulp1i != nullptr) {
        *ulp1i=ulp1_interval(dr, mpres);
    }
    return dr;
}

namespace {

    int
    bf16_ftz_rounding(cftal::bf16_t v, float f, int mpres)
    {
#if __CFTAL_CFG_FLUSH_BFLOAT16_TO_ZERO > 0
        using namespace cftal;
        mf_f16_t vi=read_bits(v);
        mf_f16_t ai=vi & 0x7fff;
        // mf_f16_t si=vi & 0x8000;

        // constexpr const float rt=std::numeric_limits<float>::denorm_min()*0.5f;
        if (ai > 0x0080)
            return mpres;

        // mpres tells us how f with 7+1 bits was obtained:
        // >0 f was rounded up
        // <0 f was rounded down
        // == 0 exact
        float vf = static_cast<float>(v);
        if (vf < f) {
            // vf was rounded down
            mpres=-1;
        } else if (vf > f) {
            // vf was rounded up
            mpres= 1;
        } else {
            if (vi & 0x8000)
                mpres=-1;
            else
                mpres=+1;
        }
        // vf == f --> no ftz but normal zero, keep mpres
#endif
        return mpres;
    }
}

cftal::bf16_t
cftal::test::call_mpfr::
func(bf16_t a, f1_t f, std::pair<bf16_t, bf16_t>* ulp1i)
{
    mpfr_cache::f1_mpfr_result<bf16_t> c;
    // auto pf= mpfr_cache::result(a, f, c);
    auto pf=nullptr;
    if (pf == nullptr) {
        bfloat16_emin_emax g;
        MPFR_DECL_INIT(ai, 8);
        MPFR_DECL_INIT(r, 8);
        float fa=cvt_bf16_to_f32(read_bits(a));
        mpfr_set_flt(ai, fa, MPFR_RNDN);
        int mpres=f(r, ai, MPFR_RNDN);
        mpres=mpfr_subnormalize(r, mpres, MPFR_RNDN);
        float fdr=mpfr_get_flt(r, MPFR_RNDN);
        c._res = bf16_t(fdr);
        c._mpfr_res= bf16_ftz_rounding(c._res, fdr, mpres);
        // mpfr_cache::update(a, f, c);
    }
    bf16_t dr=c._res;
    int mpres=c._mpfr_res;
    if (ulp1i != nullptr) {
        *ulp1i=ulp1_interval(dr, mpres);
    }
    return dr;
}

std::pair<cftal::bf16_t, cftal::bf16_t>
cftal::test::call_mpfr::
func(bf16_t a, f1p_t f,
     std::pair<bf16_t, bf16_t>* ulp1i0,
     std::pair<bf16_t, bf16_t>* ulp1i1)
{
    bfloat16_emin_emax g;
    MPFR_DECL_INIT(ai, 8);
    MPFR_DECL_INIT(r0, 8);
    MPFR_DECL_INIT(r1, 8);
    float fa=cvt_bf16_to_f32(read_bits(a));
    mpfr_set_flt(ai, fa, MPFR_RNDN);
    int i01=f(r0, r1, ai, MPFR_RNDN);

    int i0 = i01 & 3;
    i0 = i0 > 1 ? -1 : i0;
    i0=mpfr_subnormalize(r0, i0, MPFR_RNDN);
    int i1 = (i01 >> 2) & 3;
    i1 = i1 > 1 ? -1 : i1;
    i1=mpfr_subnormalize(r1, i1, MPFR_RNDN);

    float fd0, fd1;
    fd0 = mpfr_get_flt(r0, MPFR_RNDN);
    fd1 = mpfr_get_flt(r1, MPFR_RNDN);
    auto d0=static_cast<bf16_t>(fd0);
    auto d1=static_cast<bf16_t>(fd1);

    i0=bf16_ftz_rounding(d0, fd0, i0);
    i1=bf16_ftz_rounding(d1, fd1, i1);


    if (ulp1i0 != nullptr) {
        *ulp1i0= ulp1_interval(d0, i0);
    }
    if (ulp1i1 != nullptr) {
        *ulp1i1= ulp1_interval(d1, i1);
    }
    return std::make_pair(d0, d1);
}

cftal::bf16_t
cftal::test::call_mpfr::
func(int32_t* ip, bf16_t a, f1i_t f, std::pair<bf16_t, bf16_t>* ulp1i)
{
    mpfr_cache::f1i_mpfr_result<std::pair<bf16_t, int32_t> > c;
    // auto pf= mpfr_cache::result(a, f, c);
    auto pf=nullptr;
    if (pf == nullptr) {
        bfloat16_emin_emax g;
        MPFR_DECL_INIT(ai, 8);
        MPFR_DECL_INIT(r, 8);
        int32_t i;
        float fa=cvt_bf16_to_f32(read_bits(a));
        mpfr_set_flt(ai, fa, MPFR_RNDN);
        int mpres=f(r, &i, ai, MPFR_RNDN);
        mpres=mpfr_subnormalize(r, mpres, MPFR_RNDN);
        float fdr=mpfr_get_flt(r, MPFR_RNDN);
        auto dr=static_cast<bf16_t>(fdr);
        c._res = std::make_pair(dr, i);
        c._mpfr_res= bf16_ftz_rounding(dr, fdr, mpres);
        // mpfr_cache::update(a, f, c);
    }
    if (ip != nullptr) {
        *ip = c._res.second;
    }
    bf16_t dr=c._res.first;
    int mpres=c._mpfr_res;
    if (ulp1i != nullptr) {
        *ulp1i=ulp1_interval(dr, mpres);
    }
    return dr;
}

cftal::bf16_t
cftal::test::call_mpfr::
func(bf16_t a, bf16_t b, f2_t f, std::pair<bf16_t, bf16_t>* ulp1i)
{
    mpfr_cache::f2_mpfr_result<bf16_t> c;
    // auto pf= mpfr_cache::result(a, b, f, c);
    auto pf=nullptr;
    if (pf == nullptr) {
        bfloat16_emin_emax g;
        MPFR_DECL_INIT(ai, 8);
        MPFR_DECL_INIT(bi, 8);
        MPFR_DECL_INIT(r, 8);
        float fa=cvt_bf16_to_f32(read_bits(a));
        float fb=cvt_bf16_to_f32(read_bits(b));
        mpfr_set_flt(ai, fa, MPFR_RNDN);
        mpfr_set_flt(bi, fb, MPFR_RNDN);
        int mpres=f(r, ai, bi, MPFR_RNDN);
        mpres=mpfr_subnormalize(r, mpres, MPFR_RNDN);
        float fdr=mpfr_get_flt(r, MPFR_RNDN);
        auto dr=static_cast<bf16_t>(fdr);
        c._res = dr;
        c._mpfr_res= bf16_ftz_rounding(dr, fdr, mpres);
        // mpfr_cache::update(a, b, f, c);
    }
    bf16_t dr=c._res;
    int mpres=c._mpfr_res;
    if (ulp1i != nullptr) {
        *ulp1i=ulp1_interval(dr, mpres);
    }
    return dr;
}

cftal::bf16_t
cftal::test::call_mpfr::
func(bf16_t a, int ib, f2fi_t f, std::pair<bf16_t, bf16_t>* ulp1i)
{
    bfloat16_emin_emax g;
    MPFR_DECL_INIT(ai, 8);
    MPFR_DECL_INIT(r, 8);
    float fa=cvt_bf16_to_f32(read_bits(a));
    mpfr_set_flt(ai, fa, GMP_RNDN);
    int mpres=f(r, ai, ib, GMP_RNDN);
    mpres=mpfr_subnormalize(r, mpres, MPFR_RNDN);
    float fdr=mpfr_get_flt(r, GMP_RNDN);
    auto dr=static_cast<bf16_t>(fdr);
    mpres= bf16_ftz_rounding(dr, fdr, mpres);
    if (ulp1i != nullptr) {
        *ulp1i=ulp1_interval(dr, mpres);
    }
    return dr;
}

std::pair<cftal::bf16_t, cftal::bf16_t>
cftal::test::call_mpfr::ulp1_interval(bf16_t res, int mpres)
{
#if __CFTAL_CFG_FLUSH_BFLOAT16_TO_ZERO >0
    uint16_t ir=as<uint16_t>(res);
    if ((ir == 0x0000) && (mpres < 0)) {
        return std::make_pair(res, as<bf16_t>(uint16_t(0x0080)));
    }
    if ((ir == 0x0080) && (mpres > 0)) {
        return std::make_pair(as<bf16_t>(uint16_t(0x0000)), res);
    }
    if ((ir == 0x8000) && (mpres > 0)) {
        return std::make_pair( as<bf16_t>(uint16_t(0x8080)), res);
    }
    if ((ir == 0x8080) && (mpres < 0)) {
        return std::make_pair(res, as<bf16_t>(uint16_t(0x8000)));
    }
#endif
    return impl::ulp1_interval(res, mpres);
}

namespace cftal::test::mpfr_ext {

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
    int r=mpfr_exp10(res, px2(), rm);
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
    int r=mpfr_exp10(res, mx2(), rm);
    return r;
}

int
cftal::test::mpfr_ext::
rcbrt(mpfr_t res,
      const mpfr_t x,
      mpfr_rnd_t rm)
{
    return rootn(res, x, -3, rm);
}

int
cftal::test::mpfr_ext::
root12(mpfr_t res,
       const mpfr_t x,
       mpfr_rnd_t rm)
{
    return rootn(res, x, 12, rm);
}

int
cftal::test::mpfr_ext::
rootn(mpfr_t y, const mpfr_t x, long int n, mpfr_rnd_t rm)
{
    if ((n & 1)==0 && mpfr_cmp_si(x, 0L) < 0) {
        mpfr_set_nan(y);
        return 0;
    }
    int r;
    if (n < 0) {
        auto f=[n](mpfr_t yy, const mpfr_t xx, mpfr_rnd_t rm)->int {
                   int64_t ni=n;
                   int64_t ai=ni < 0 ? -ni : ni;
                   fpn_handle rn(mpfr_get_prec(xx));
#if MPFR_VERSION_MAJOR<4
                   int r=mpfr_root(rn(), xx, ai, rm);
#else
                   int r=mpfr_rootn_ui(rn(), xx, ai, rm);
#endif
                   if (ni >= 0) {
                       mpfr_set(yy, rn(), rm);
                   } else {
                       r=mpfr_si_div(yy, 1L, rn(), rm);
                   }
                   return r;
               };
        r=call_ziv_func(y, x, rm, f);
    } else {
#if MPFR_VERSION_MAJOR<4
        r=mpfr_root(y, x, n, rm);
#else
        r=mpfr_rootn_ui(y, x, n, rm);
#endif
    }
    return r;
}


bool
cftal::test::mpfr_ext::
is_half_integer(const mpfr_t x)
{
    if (mpfr_integer_p(x))
        return false;
    fpn_handle ax(mpfr_get_prec(x));
    mpfr_abs(ax(), x, MPFR_RNDN);
    fpn_handle axmh(mpfr_get_prec(x));
    mpfr_sub_d(axmh(), ax(), 0.5, MPFR_RNDN);
    return mpfr_integer_p(axmh());
}

int cftal::test::mpfr_ext::
sig(mpfr_t res, const mpfr_t x, mpfr_rnd_t rm)
{
    auto f=[](mpfr_t yy, const mpfr_t xx, mpfr_rnd_t rm)->int {
        fpn_handle one(1.0, mpfr_get_prec(xx));
        fpn_handle nx(mpfr_get_prec(xx));
        mpfr_neg(nx(), xx, MPFR_RNDN);
        fpn_handle exp_nx(mpfr_get_prec(xx));
        mpfr_exp(exp_nx(), nx(), MPFR_RNDN);
        fpn_handle t(mpfr_get_prec(xx));
        mpfr_add(t(), one(), exp_nx(), MPFR_RNDN);
        return mpfr_div(yy, one(), t(), rm);
    };
    int r=call_ziv_func(res, x, rm, f);
    return r;
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
