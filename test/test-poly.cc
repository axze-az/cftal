//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/of_math_funcs.h"
#include "cftal/math/horner.h"
#include "cftal/math/impl_estrin.h"
#include "cftal/vec.h"
#include "cftal/vec_traits.h"
#include "cftal/test/call_mpfr.h"
#include <tuple>
#include <iostream>
#include <iomanip>

namespace cftal {
    namespace test {
        struct check_exp_f64_base {
            static
            const double c13, c12, c11, c10, c9, c8, c7, c6,
                c5, c4, c3, c2, c1, c0;

            using mpfr53_t = mpfr_real<53>;
            static
            const mpfr53_t a13, a12, a11, a10, a9, a8, a7, a6,
                a5, a4, a3, a2, a1, a0;

            template <std::size_t _N>
            static
            vec<double, _N>
            v(const vec<double, _N>& x) {
                return math::horner(x,
                                    c13, c12, c11, c10,
                                    c9, c8, c7, c6, c5,
                                    c4, c3, c2, c1, c0);
            }

            static
            int exp_f64_poly(mpfr_t res, const mpfr_t x,
                             mpfr_rnd_t rnd);

            static
            std::tuple<double, double, double>
            r(const double& a) {
                std::pair<double, double> i;
                double y=call_mpfr::func(a, exp_f64_poly, &i);
                return std::make_tuple(y, i.first, i.second);
            }

            static
            double
            s(const double& a) {
                return math::horner(a,
                                    c13, c12, c11, c10,
                                    c9, c8, c7, c6, c5,
                                    c4, c3, c2, c1, c0);
            }

            static
            const char* fname() { return "exp_f64_horner base"; }
        };

        struct check_exp_f64_impl : public check_exp_f64_base {

            template <std::size_t _N>
            static
            vec<double, _N>
            v(const vec<double, _N>& x) {
                using vf_type = vec<double, _N>;
                vf_type xx=x*x;
                vf_type i=math::horner(xx,
                                 c13,
                                 c11,
                                 c9,
                                 c7,
                                 c5);
                vf_type j=math::horner(xx,
                                 c12,
                                 c10,
                                 c8,
                                 c6,
                                 c4);
                vf_type y=math::horner(x, i, j, c3, c2);
                vf_type ye;
                math::horner_comp_quick(y, ye, x, y, c1, c0);
                return y+ ye;
            }

            static
            const char* fname() { return "exp_f64_horner impl horner2"; }
        };

        struct check_exp_f64_horner : public check_exp_f64_base {

            template <std::size_t _N>
            static
            vec<double, _N>
            v(const vec<double, _N>& x) {
                using vf_type = vec<double, _N>;
                vf_type y=math::horner(x,
                                       c13, c12, c11, c10,
                                       c9, c8, c7, c6, c5,
                                       c4, c3, c2);
                vf_type ye;
                math::horner_comp_quick(y, ye, x, y, c1, c0);
                return y+ ye;
            }

            static
            const char* fname() { return "exp_f64 poly horner"; }
        };

        struct check_exp_f64_estrin : public check_exp_f64_base {

            template <std::size_t _N>
            static
            vec<double, _N>
            v(const vec<double, _N>& x) {
                using vf_type = vec<double, _N>;
                vf_type y= math::impl::estrin(x,
                                              c13, c12, c11, c10,
                                              c9, c8, c7, c6, c5,
                                              c4, c3);
                y=math::horner(x, y, c2);
                vf_type ye;
                math::horner_comp_quick(y, ye, x, y, c1, c0);
                return y+ ye;
            }

            static
            const char* fname() { return "exp_f64 poly estrin"; }
        };

    }
}

// [-0.3465735912322998046875, 0.3465735912322998046875] : | p - f | <= 2^-67.5
// coefficients for exp generated by sollya
// x^0 : +0x8p-3
const double cftal::test::check_exp_f64_base::c0=+1.0000000000000000000000e+00;
// x^1 : +0x8p-3
const double cftal::test::check_exp_f64_base::c1=+1.0000000000000000000000e+00;
// x^2 : +0x8p-4
const double cftal::test::check_exp_f64_base::c2=+5.0000000000000000000000e-01;
// x^3 : +0xa.aaaaaaaaaaaa8p-6
const double cftal::test::check_exp_f64_base::c3=+1.6666666666666665741481e-01;
// x^4 : +0xa.aaaaaaaaaaacp-8
const double cftal::test::check_exp_f64_base::c4=+4.1666666666666685170384e-02;
// x^5 : +0x8.888888888961p-10
const double cftal::test::check_exp_f64_base::c5=+8.3333333333340843529502e-03;
// x^6 : +0xb.60b60b60a81p-13
const double cftal::test::check_exp_f64_base::c6=+1.3888888888873365812238e-03;
// x^7 : +0xd.00d00cfa88cc8p-16
const double cftal::test::check_exp_f64_base::c7=+1.9841269839039331096715e-04;
// x^8 : +0xd.00d00d6b5b978p-19
const double cftal::test::check_exp_f64_base::c8=+2.4801587348902822885563e-05;
// x^9 : +0xb.8ef1e87f81768p-22
const double cftal::test::check_exp_f64_base::c9=+2.7557322326013774747291e-06;
// x^10 : +0x9.3f26623e02258p-25
const double cftal::test::check_exp_f64_base::c10=+2.7557252167692825528943e-07;
// x^11 : +0xd.72da4d99dd1ep-29
const double cftal::test::check_exp_f64_base::c11=+2.5050050656120229688701e-08;
// x^12 : +0x8.fc5bcb2f9dd7p-32
const double cftal::test::check_exp_f64_base::c12=+2.0921639307947297714762e-09;
// x^13 : +0xb.675e3aadcbc88p-36
const double cftal::test::check_exp_f64_base::c13=+1.6594686274338619941159e-10;

const cftal::test::check_exp_f64_base::mpfr53_t
cftal::test::check_exp_f64_base::a0 = cftal::test::check_exp_f64_base::c0;
const cftal::test::check_exp_f64_base::mpfr53_t
cftal::test::check_exp_f64_base::a1 = cftal::test::check_exp_f64_base::c1;
const cftal::test::check_exp_f64_base::mpfr53_t
cftal::test::check_exp_f64_base::a2 = cftal::test::check_exp_f64_base::c2;
const cftal::test::check_exp_f64_base::mpfr53_t
cftal::test::check_exp_f64_base::a3 = cftal::test::check_exp_f64_base::c3;
const cftal::test::check_exp_f64_base::mpfr53_t
cftal::test::check_exp_f64_base::a4 = cftal::test::check_exp_f64_base::c4;
const cftal::test::check_exp_f64_base::mpfr53_t
cftal::test::check_exp_f64_base::a5 = cftal::test::check_exp_f64_base::c5;
const cftal::test::check_exp_f64_base::mpfr53_t
cftal::test::check_exp_f64_base::a6 = cftal::test::check_exp_f64_base::c6;
const cftal::test::check_exp_f64_base::mpfr53_t
cftal::test::check_exp_f64_base::a7 = cftal::test::check_exp_f64_base::c7;
const cftal::test::check_exp_f64_base::mpfr53_t
cftal::test::check_exp_f64_base::a8 = cftal::test::check_exp_f64_base::c8;
const cftal::test::check_exp_f64_base::mpfr53_t
cftal::test::check_exp_f64_base::a9 = cftal::test::check_exp_f64_base::c9;
const cftal::test::check_exp_f64_base::mpfr53_t
cftal::test::check_exp_f64_base::a10 = cftal::test::check_exp_f64_base::c10;
const cftal::test::check_exp_f64_base::mpfr53_t
cftal::test::check_exp_f64_base::a11 = cftal::test::check_exp_f64_base::c11;
const cftal::test::check_exp_f64_base::mpfr53_t
cftal::test::check_exp_f64_base::a12 = cftal::test::check_exp_f64_base::c12;
const cftal::test::check_exp_f64_base::mpfr53_t
cftal::test::check_exp_f64_base::a13 = cftal::test::check_exp_f64_base::c13;

int
cftal::test::check_exp_f64_base::
exp_f64_poly(mpfr_t res, const mpfr_t x, mpfr_rnd_t rnd)
{
    return mpfr_ext::horner(res, x, rnd,
                            a13(), a12(), a11(), a10(),
                            a9(), a8(), a7(), a6(), a5(),
                            a4(), a3(), a2(), a1(), a0(),
                            nullptr);
}

int main(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;

    const int ulp=256;
    const int _N=8;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    using ftype = double;

    func_domain<ftype> d=std::make_pair(-M_LN2/2, M_LN2/2);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
#if 0
    rc &= of_fp_func_up_to<
        ftype, _N, check_exp_f64_base>::v(st, d, speed_only,
                                          cmp_ulp<ftype>(ulp, us),
                                          cnt, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    us=std::make_shared<ulp_stats>();
#endif
    rc &= of_fp_func_up_to<
        ftype, _N, check_exp_f64_impl>::v(st, d, speed_only,
                                          cmp_ulp<ftype>(ulp, us),
                                          cnt, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;

#if 0
    // deactivated, no new information
    us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_exp_f64_horner>::v(st, d, speed_only,
                                          cmp_ulp<ftype>(ulp, us),
                                          cnt, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
#endif

    us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_exp_f64_estrin>::v(st, d, speed_only,
                                          cmp_ulp<ftype>(ulp, us),
                                          cnt, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;

    return (rc == true) ? 0 : 1;
}
