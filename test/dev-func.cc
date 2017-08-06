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
            cosh_k(arg_t<vf_type> x);

            static
            vf_type
            sinh_k(arg_t<vf_type> x);


            static
            vf_type
            new_cosh(arg_t<vf_type> x);

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
        struct check_cosh {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::new_cosh(a);
            }
            static
            std::tuple<_T, _T, _T>
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_cosh, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::cosh(a);
            }
            static
            const char* fname() { return "cosh"; }
        };
    }
}

template <typename _T>
inline
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::
cosh_k(arg_t<vf_type> x)
{
    vf_type xc= abs(x);
    vf_type xrh, xrl, kf;
    auto k= base_type::__reduce_exp_arg(xrh, xrl, kf, xc);

    vf_type scale=_T::sel(kf >= 1024, 2.0, 1.0);
    auto kn= _T::sel(k>= 1024, k-1, k);

    // calculate 2^(k-1)
    vf_type two_pow_plus_k_minus_1 = _T::insert_exp((_T::bias()-1) + kn);
    // calculate 2^(-k-1)
    vf_type two_pow_minus_k_minus_1 = _T::insert_exp((_T::bias()-1) - kn);

    // calculate sinh + cosh
    // [0, 0.3465735912322998046875] : | p - f | <= 2^-68.1875
    // coefficients for sinh generated by sollya
    // x^1 : +0x8p-3
    const double sinh_c1=+1.0000000000000000000000e+00;
    // x^3 : +0xa.aaaaaaaaaaaa8p-6
    const double sinh_c3=+1.6666666666666665741481e-01;
    // x^5 : +0x8.888888888987p-10
    const double sinh_c5=+8.3333333333342161919344e-03;
    // x^7 : +0xd.00d00cf88266p-16
    const double sinh_c7=+1.9841269838319906034657e-04;
    // x^9 : +0xb.8ef1f23c3658p-22
    const double sinh_c9=+2.7557323709743886271627e-06;
    // x^11 : +0xd.72b2a27c563b8p-29
    const double sinh_c11=+2.5048923211833473960268e-08;
    // x^13 : +0xb.a1b17ee8523e8p-36
    const double sinh_c13=+1.6926226991841124453737e-10;

    // [0, 0.3465735912322998046875] : | p - f | <= 2^-69.96875
    // coefficients for cosh generated by sollya
    // x^0 : +0x8p-3
    const double cosh_c0=+1.0000000000000000000000e+00;
    // x^2 : +0x8p-4
    const double cosh_c2=+5.0000000000000000000000e-01;
    // x^4 : +0xa.aaaaaaaaaaacp-8
    const double cosh_c4=+4.1666666666666685170384e-02;
    // x^6 : +0xb.60b60b60a809p-13
    const double cosh_c6=+1.3888888888873335454577e-03;
    // x^8 : +0xd.00d00d6b984fp-19
    const double cosh_c8=+2.4801587349008149738488e-05;
    // x^10 : +0x9.3f26619515b2p-25
    const double cosh_c10=+2.7557252050478505757717e-07;
    // x^12 : +0x8.fc5cfb218889p-32
    const double cosh_c12=+2.0921681488787703832704e-09;

    vf_type xx= xrh*xrh;
    vf_type rsh= horner(xx,
                        sinh_c13,
                        sinh_c11,
                        sinh_c9,
                        sinh_c7,
                        sinh_c5,
                        sinh_c3);
    vf_type rsh_h, rsh_l;
    horner_comp_quick(rsh_h, rsh_l, xx, rsh, sinh_c1);
    d_ops::mul122(rsh_h, rsh_l, xrh, rsh_h, rsh_l);

    vf_type rch= horner(xx,
                        cosh_c12,
                        cosh_c10,
                        cosh_c8,
                        cosh_c6,
                        cosh_c4,
                        cosh_c2);
    vf_type rch_h, rch_l;
    horner_comp_quick(rch_h, rch_l, xx, rch, cosh_c0);

    // cosh(x + y) = cosh(x) cosh(y) + sinh(x)*sinh(y)
    // sinh(x + y) = sinh(x) cosh(y) + sinh(y)*cosh(x);
    // cosh(k * ln(2)) = 2^(k-1) + 2^(-k-1)
    // sinh(k * ln(2)) = 2^(k-1) - 2^(-k-1)

    // filter out small terms
    two_pow_plus_k_minus_1 = _T::sel_zero_or_val(kf < -35,
                                                 two_pow_plus_k_minus_1);
    two_pow_minus_k_minus_1= _T::sel_zero_or_val(kf > 35,
                                                 two_pow_minus_k_minus_1);

    vf_type rh = two_pow_plus_k_minus_1 * rch_h;
    vf_type rl = two_pow_plus_k_minus_1 * rch_l;

    vf_type th = two_pow_plus_k_minus_1 * rsh_h;
    vf_type tl = two_pow_plus_k_minus_1 * rsh_l;
    d_ops::add22cond(rh, rl, th, tl, rh, rl);

    th = two_pow_minus_k_minus_1 * rch_h;
    tl = two_pow_minus_k_minus_1 * rch_l;
    d_ops::add22cond(rh, rl, th, tl, rh, rl);

    th = two_pow_minus_k_minus_1 * -rsh_h;
    tl = two_pow_minus_k_minus_1 * -rsh_l;

    d_ops::add22cond(rh, rl, th, tl, rh, rl);

    vf_type cosh_x = rh + rl;
#if 0
    std::cout << std::hexfloat
              << "x= " << x << '\n'
              << two_pow_plus_k_minus_1 << '\n'
              << two_pow_minus_k_minus_1 << '\n'
              << t0 << '\n'
              << t1 << '\n'
              << t2 << '\n'
              << rch << '\n'
              << rsh << '\n';
#endif
    return cosh_x*scale;
}

template <typename _T>
inline
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::
new_cosh(arg_t<vf_type> x)
{
    using fc=func_constants<double>;
    const vf_type cosh_hi_inf= fc::cosh_hi_inf();
    vf_type res=cosh_k(x);
    res = _T::sel(abs(x) >= cosh_hi_inf, _T::pinf(), res);
    // res = _T::sel(x == 0.0, 1.0, res);
    return res;
}

int main(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=8;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    } else {
#if 0
        std::string test_data_dir = dirname(argv[0]);
        std::string test_data_file=
            append_filename(test_data_dir, "../../test/data/cosh.testdata");
        if (argc > 1) {
            test_data_dir = argv[1];
            test_data_file = append_filename(test_data_dir, "cosh.testdata");
        }
        std::vector<func_arg_result<double> > v=
            read_double_file(test_data_file, false);

        rc &= check_func_1<double, 1, check_cosh<double> >(v, ulp, 0, false);
        rc &= check_func_1<double, 2, check_cosh<double> >(v, ulp, 0, false);
        rc &= check_func_1<double, 4, check_cosh<double> >(v, ulp, 0, false);
        rc &= check_func_1<double, 8, check_cosh<double> >(v, ulp, 0, false);
#endif
    }
    func_domain<double> d=std::make_pair(-710.5, 710.5);
    auto us=std::make_shared<ulp_stats>();
    // d= std::make_pair(710.0, 710.5);
    d= std::make_pair(0.0, 710.5);
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        double, _N, check_cosh<double> >::v(st, d, speed_only,
                                            cmp_ulp<double>(ulp, us),
                                            cnt, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}


