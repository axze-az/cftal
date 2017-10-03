//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/vec.h"
#include "cftal/vec_traits.h"
#include "cftal/math/elem_func.h"
#include "cftal/math/elem_func_core_f64.h"
#include "cftal/math/elem_func_core_f32.h"
#include "cftal/math/impl_estrin.h"
#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_expm1.h"
#include "cftal/test/mpfr_cache.h"
#include <tuple>
#include <iostream>
#include <iomanip>
#include <memory>


/*
    floatn cos(floatn x);
    floatn exp(floatn x); +
    floatn exp2(floatn x); +
    floatn exp10(floatn x); +
    floatn log(floatn x); +
    floatn log2(floatn x); +
    floatn log10(floatn x); +
    floatn recip(floatn x);
    floatn rsqrt(floatn x);
    floatn sin(floatn x);
    floatn sqrt(floatn x);
    floatn tan(floatn x);
    floatn divide(floatn x, floatn y);
    floatn powr(floatn x, floatn y);
 */

#define EXP 1

namespace cftal {

    namespace math {
        template <typename _FLOAT_T, typename _TRAITS_T>
        struct test_func : public elem_func_core< _FLOAT_T, _TRAITS_T> {
            using base_type = elem_func_core<_FLOAT_T, _TRAITS_T>;
            using my_type = test_func<_FLOAT_T, _TRAITS_T>;
            using vf_type = typename base_type::vf_type;
            using vi_type = typename base_type::vi_type;
            using vmf_type = typename base_type::vmf_type;
            using vmi_type = typename base_type::vmi_type;
            using dvf_type = typename base_type::dvf_type;

            static vf_type func(arg_t<vf_type> vf);
        };

        template <typename _T>
        struct test_func<double, _T> : public elem_func_core<double, _T> {
            using base_type = elem_func_core<double, _T>;
            using vf_type = typename _T::vf_type;
            using vi_type = typename _T::vi_type;
            // using vli_type = typename _T::vli_type;
            using vi2_type = typename _T::vi2_type;
            using vmf_type = typename _T::vmf_type;
            using vmi_type = typename _T::vmi_type;
            using vmi2_type = typename _T::vmi2_type;

            using dvf_type = d_real<vf_type>;
            using tvf_type = t_real<vf_type>;
            using my_type = test_func<double, _T>;

            using d_ops = typename base_type::d_ops;

            // static vf_type func_k(arg_t<vf_type> vf);

            using base_type::ilogbp1_k;
            using base_type::ldexp_k;
            using base_type::pow_k;

            static
            vf_type
            erfc_k(arg_t<vf_type> xc);

            static
            vf_type
            erfc(arg_t<vf_type> xc);

        };

        template <typename _T>
        struct test_func<float, _T> : public elem_func_core<float, _T> {
            using base_type = elem_func_core<float, _T>;
            using vf_type = typename _T::vf_type;
            using vi_type = typename _T::vi_type;
            // using vli_type = typename _T::vli_type;
            using vmf_type = typename _T::vmf_type;
            using vmi_type = typename _T::vmi_type;

            using dvf_type = d_real<vf_type>;
            using tvf_type = t_real<vf_type>;
            using my_type = test_func<float, _T>;

            using d_ops = typename base_type::d_ops;

            using base_type::ilogbp1;
            using base_type::ldexp;
            using base_type::__reduce_exp_arg;
            using base_type::__scale_exp_k;
            using base_type::__exp_k;

        };
    }


    namespace test {

        template <typename _T>
        struct check_erfc {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::erfc(a);
            }
            static
            std::tuple<_T, _T, _T>
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_erfc, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::erfc(a);
            }
            static
            const char* fname() { return "erfc"; }
        };

    }
}


template <typename _T>
inline
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::
erfc_k(arg_t<vf_type> xc)
{

    // i=[0.75, 3];
    // i=[3.0, 6.0];
    // deg=25;
    // f=exp(x*x)*x*erfc(x);
    // b=[|0, ..., deg|];
    // c= [|D, D...|];
    // p=fpminimax(f, b, c, i, relative, floating);
    // write_approx_prec(p, f, i);
    // write_coeffs(p, "const double erfc_asymp_c", "erfc", b, c);
    // plot(log(abs(p(x)-f(x))), i, postscriptfile, "erfc-i-n-f64");
    // implementpoly(p, i, 0x1p-52, D, "erfc_i_n", "erfc_i_n.c");

    // i=[1/6.0, 1/27.25];
    // deg=25;
    // f=exp(1/x*1/x)*1/x*erfc(1/x);
    // b=[|0, ..., deg|];
    // c= [|D, D...|];
    // p=fpminimax(f, b, c, i, relative, floating);
    // write_approx_prec(p, f, i);
    // write_coeffs(p, "const double erfc_asymp_c", "erfc", b, c);
    // plot(log(abs(p(x)-f(x))), i, postscriptfile, "erfc-i-n-f64");
    // implementpoly(p, i, 0x1p-52, D, "erfc_i_n", "erfc_i_n.c");
    // [3.6697246134281158447265625e-2, 0.16666667163372039794921875] : | p - f | <= 2^-92.125
    // coefficients for erfc generated by sollya
    // x^0 : +0x9.06eba8214db68p-4
    const double erfc_asymp_c0=+5.6418958354775627928035e-01;
    // x^1 : +0xa.f92535989c79p-52
    const double erfc_asymp_c1=+2.4365451922245938660534e-15;
    // x^2 : -0x9.06eba8215aap-5
    const double erfc_asymp_c2=-2.8209479177424512386096e-01;
    // x^3 : +0x9.95dd9557213bp-38
    const double erfc_asymp_c3=+3.4871526963839179975749e-11;
    // x^4 : +0xd.8a617aef4f97p-5
    const double erfc_asymp_c4=+4.2314218531326985850427e-01;
    // x^5 : +0xf.ff517b44d421p-27
    const double erfc_asymp_c5=+1.1918944909655141650019e-07;
    // x^6 : -0x8.767f6a5356d1p-3
    const double erfc_asymp_c6=-1.0578602129633982720236e+00;
    // x^7 : +0x9.f403d11a91298p-16
    const double erfc_asymp_c7=+1.5187352355840402925134e-04;
    // x^8 : +0xe.cb46be56c001p-2
    const double erfc_asymp_c8=+3.6985120525787360534764e+00;
    // x^9 : +0xb.16181dfe9c908p-7
    const double erfc_asymp_c9=+8.6611761709012316523548e-02;
    // x^10 : -0x9.1e7f2b6dc93a8p+1
    const double erfc_asymp_c10=-1.8238255909544438537750e+01;
    // x^11 : +0xc.185e70965c288p+1
    const double erfc_asymp_c11=+2.4190382073801007578595e+01;
    // x^12 : -0xd.e384db7ff99f8p+4
    const double erfc_asymp_c12=-2.2221993589391965429058e+02;
    // x^13 : +0xd.7b5d7b665fe7p+8
    const double erfc_asymp_c13=+3.4513651641830574590131e+03;
    // x^14 : -0x8.0013b33a31c48p+12
    const double erfc_asymp_c14=-3.2769231256670384027530e+04;
    // x^15 : +0xf.7df0afac028ep+14
    const double erfc_asymp_c15=+2.5382017155460349749774e+05;
    // x^16 : -0xc.d8dd1176d6d2p+17
    const double erfc_asymp_c16=-1.6838981364391827955842e+06;
    // x^17 : +0x8.f9fc5603a2518p+20
    const double erfc_asymp_c17=+9.4125493758872207254171e+06;
    // x^18 : -0xa.66ddd2a2f023p+22
    const double erfc_asymp_c18=-4.3628404659119173884392e+07;
    // x^19 : +0x9.deafb38cd5c6p+24
    const double erfc_asymp_c19=+1.6558891555013692378998e+08;
    // x^20 : -0xf.18369669d6f98p+25
    const double erfc_asymp_c20=-5.0649015682687300443649e+08;
    // x^21 : +0x9.145a63c860018p+27
    const double erfc_asymp_c21=+1.2186304302617194652557e+09;
    // x^22 : -0x8.45df7864a3c3p+28
    const double erfc_asymp_c22=-2.2207507262899808883667e+09;
    // x^23 : +0xa.bad0fb0fef79p+28
    const double erfc_asymp_c23=+2.8802456809959650039673e+09;
    // x^24 : -0x8.d2241011fd07p+28
    const double erfc_asymp_c24=-2.3678323211242742538452e+09;
    // x^25 : +0xd.d03fb0fdd546p+26
    const double erfc_asymp_c25=+9.2700640396614217758179e+08;
    vf_type ea, eal;
    vf_type inv_x=1.0/xc;
    ea=horner(inv_x,
                      erfc_asymp_c25,
                      erfc_asymp_c24,
                      erfc_asymp_c23,
                      erfc_asymp_c22,
                      erfc_asymp_c21,
                      erfc_asymp_c20,
                      erfc_asymp_c19,
                      erfc_asymp_c18,
                      erfc_asymp_c17,
                      erfc_asymp_c16,
                      erfc_asymp_c15,
                      erfc_asymp_c14,
                      erfc_asymp_c13,
                      erfc_asymp_c12,
                      erfc_asymp_c11,
                      erfc_asymp_c10,
                      erfc_asymp_c9,
                      erfc_asymp_c8,
                      erfc_asymp_c7,
                      erfc_asymp_c6,
                      erfc_asymp_c5,
                      erfc_asymp_c4,
                      erfc_asymp_c3,
                erfc_asymp_c2,
                erfc_asymp_c1);
    horner_comp(ea, eal, inv_x, ea, erfc_asymp_c0);
    vf_type x2h, x2l;
    if (d_real_traits<vf_type>::fma==true) {
        d_ops::mul12(x2h, x2l, xc, -xc);
    } else {
        d_ops::sqr12(x2h, x2l, xc);
        x2h = -x2h;
        x2l = -x2l;
    }
    vf_type xrh, xrl, kf;
    auto k=base_type::__reduce_exp_arg(xrh, xrl, kf, x2h, x2l);
    vf_type exl, ex= base_type::__pow_exp_k(xrh, xrl, kf, k, &exl);
    d_ops::mul22(ea, eal, ea, eal, ex, exl);
    dvf_type t(ea, eal);
    t = d_ops::sloppy_div(t, xc);
    return t.h()+t.l();
}

template <typename _T>
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::
erfc(arg_t<vf_type> x)
{
    vf_type r=erfc_k(x);
    // using fc=func_constants<_FLOAT_T>;
    // r = _TRAITS_T::sel(x < -fc::erf_lt_one_fin, -1.0, r);
    // r = _TRAITS_T::sel(x > fc::erf_lt_one_fin, 1.0, r);
    r = _T::sel(x == 0, 1.0, r);
    r = _T::sel(isnan(x), x, r);
    return r;
}

int main_erfc(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=32;
    const int _N=8;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    } else {
        mpfr_cache::use(mpfr_erfc, "erfc", 0.0);
    }
    func_domain<double> d=std::make_pair(6.0, 27.25);
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        double, _N, check_erfc<double> >::v(st, d, speed_only,
                                            cmp_ulp<double>(ulp, us),
                                            cnt, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}


int main(int argc, char**argv)
{
    int r=0;
    // r |= main_cosh(argc, argv);
    r |= main_erfc(argc, argv);
    // r |= main_tanh(argc, argv);
    return r;
}
