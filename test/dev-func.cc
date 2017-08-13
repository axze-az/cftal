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

            enum hyperbolic_func {
                c_sinh,
                c_cosh,
                c_tanh
            };

            template <hyperbolic_func _F>
            static
            vf_type
            hyperbolic_k(arg_t< vf_type > xc);

            static
            vf_type
            cosh_k(arg_t<vf_type> x);

            static
            vf_type
            sinh_k(arg_t<vf_type> x);

            static
            vf_type
            tanh_k(arg_t<vf_type> x);

            static
            vf_type
            new_cosh(arg_t<vf_type> x);

            static
            vf_type
            new_sinh(arg_t<vf_type> x);

            static
            vf_type
            new_tanh(arg_t<vf_type> x);

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

        template <typename _T>
        struct check_sinh {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::new_sinh(a);
            }
            static
            std::tuple<_T, _T, _T>
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_sinh, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::sinh(a);
            }
            static
            const char* fname() { return "sinh"; }
        };

        template <typename _T>
        struct check_tanh {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::new_tanh(a);
            }
            static
            std::tuple<_T, _T, _T>
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_tanh, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::tanh(a);
            }
            static
            const char* fname() { return "tanh"; }
        };

    }
}

template <typename _T>
template <enum cftal::math::test_func<float, _T>::hyperbolic_func _F>
inline
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::
hyperbolic_k(arg_t<vf_type> xc)
{
    vf_type x= abs(xc);
    vf_type xrh, xrl, kf;
    auto k= base_type::__reduce_exp_arg(xrh, xrl, kf, x);

    vf_type scale=_T::sel(kf >= 128, 2.0f, 1.0f);
    auto kn= _T::sel(k>= 128, k-1, k);

    // filter out small terms for tanh
    vmf_type kf_le_35 = kf <= 13.0;
    bool any_of_kf_le_35 = any_of(kf_le_35);
    if (_F == hyperbolic_func::c_tanh) {
        if (!any_of_kf_le_35) {
            vf_type tanh_x = copysign(vf_type(1.0), xc);
            return tanh_x;
        }
    }
    // calculate 2^(k-1)
    vf_type two_pow_plus_k_minus_1 = _T::insert_exp((_T::bias()-1) + kn);
    // calculate sinh + cosh
    // [0, 0.3465735912322998046875] : | p - f | <= 2^-39.203125
    // coefficients for sinh generated by sollya
    // x^1 : +0xf.ffffffffb1bc8p-4
    const float sinh_c1=+9.9999999999555122531802e-01;
    // x^3 : +0xa.aaaaabf1cb64p-6
    const float sinh_c3=+1.6666666785675077200324e-01;
    // x^5 : +0x8.8885337cb256p-10
    const float sinh_c5=+8.3332836795072182112243e-03;
    // x^7 : +0xd.0bec3b9436598p-16
    const float sinh_c7=+1.9907491112367489151901e-04;

    // [0, 0.3465735912322998046875] : | p - f | <= 2^-33.171875
    // coefficients for cosh generated by sollya
    // x^0 : +0x8p-3f
    const float cosh_c0=+1.0000000000e+00f;
    // x^2 : +0x8p-4f
    const float cosh_c2=+5.0000000000e-01f;
    // x^4 : +0xa.aaa72p-8f
    const float cosh_c4=+4.1666455567e-02f;
    // x^6 : +0xb.6a8a3p-13f
    const float cosh_c6=+1.3935755705e-03f;

    vf_type xx= xrh*xrh;
    vf_type rsh= horner(xx,
                        sinh_c7,
                        sinh_c5,
                        sinh_c3,
                        sinh_c1) * xrh;
    vf_type rch= horner(xx,
                        cosh_c6,
                        cosh_c4,
                        cosh_c2,
                        cosh_c0);
    // correction of argument reduction errors:
    // cosh(x+y) \approx cosh(y) + sinh(y) x
    // sinh(x+y) \approx sinh(y) + cosh(y) x
    vf_type rch_corr= rsh* xrl;
    vf_type rsh_corr= rch* xrl;
    rch += rch_corr;
    rsh += rsh_corr;

    // cosh(x + y) = cosh(x) cosh(y) + sinh(x)*sinh(y)
    // sinh(x + y) = sinh(x) cosh(y) + sinh(x)*cosh(y);
    // cosh(k * ln(2)) = 2^(k-1) + 2^(-k-1)
    // sinh(k * ln(2)) = 2^(k-1) - 2^(-k-1)

    // two_pow_plus_k_minus_1 = _T::sel_zero_or_val(kf < -35,
    //                                             two_pow_plus_k_minus_1);
    vf_type two_pow_km1_rch = two_pow_plus_k_minus_1 * rch;
    vf_type two_pow_km1_rsh = two_pow_plus_k_minus_1 * rsh;

    vf_type cosh_x, sinh_x;

    const bool calc_sinh=_F == hyperbolic_func::c_sinh ||
        _F == hyperbolic_func::c_tanh;
    const bool calc_cosh=_F == hyperbolic_func::c_cosh ||
        _F == hyperbolic_func::c_tanh;

    // calculate 2^(-k-1)
    vf_type two_pow_minus_k_minus_1 = _T::insert_exp((_T::bias()-1) - kn);
    two_pow_minus_k_minus_1= _T::sel_val_or_zero(kf_le_35,
                                                 two_pow_minus_k_minus_1);
    vf_type two_pow_mkm1_rch = two_pow_minus_k_minus_1 * rch;
    vf_type two_pow_mkm1_rsh = two_pow_minus_k_minus_1 * rsh;

#if 1
    cosh_x = sinh_x = two_pow_km1_rch + two_pow_km1_rsh;
    if (calc_sinh) {
        sinh_x -= two_pow_mkm1_rch;
        sinh_x += two_pow_mkm1_rsh;
    }
    if (calc_cosh) {
        cosh_x += two_pow_mkm1_rch -two_pow_mkm1_rsh;
    }
    vf_type r;
    if (_F == hyperbolic_func::c_sinh) {
        sinh_x *=scale;
        sinh_x = _T::sel(x < 0x1p-13f, x, sinh_x);
        sinh_x = copysign(sinh_x, xc);
        r = sinh_x;
    }
    if (_F == hyperbolic_func::c_cosh) {
        cosh_x *= scale;
        r = cosh_x;
    }
    if (_F == hyperbolic_func::c_tanh) {
        vf_type tanh_x=_T::sel(kf_le_35, sinh_x/cosh_x, 1.0);
        tanh_x = _T::sel(x < 0x1p-13f, x, tanh_x);
        tanh_x = copysign(tanh_x, xc);
        r = tanh_x;
    }
#else
    vf_type cosh_h, cosh_l;
    d_ops::add12(cosh_h, cosh_l, two_pow_km1_rch, two_pow_km1_rsh);
    vf_type sinh_h = cosh_h;
    vf_type sinh_l = cosh_l;

    if (calc_sinh) {
        vf_type th, tl;
        d_ops::add12(th, tl, -two_pow_mkm1_rch, two_pow_mkm1_rsh);
        d_ops::add22(sinh_h, sinh_l, sinh_h, sinh_l, th, tl);
    }
    if (calc_cosh) {
        vf_type th, tl;
        d_ops::add12(th, tl, two_pow_mkm1_rch, -two_pow_mkm1_rsh);
        d_ops::add22(cosh_h, cosh_l, cosh_h, cosh_l, th, tl);
    }
    vf_type r;
    if (_F == hyperbolic_func::c_sinh) {
        sinh_x = (sinh_h+sinh_l)*scale;
        sinh_x = _T::sel(x < 0x1p-13f, x, sinh_x);
        sinh_x = copysign(sinh_x, xc);
        r = sinh_x;
    }
    if (_F == hyperbolic_func::c_cosh) {
        cosh_x = (cosh_h+cosh_l)*scale;
        r = cosh_x;
    }
    if (_F == hyperbolic_func::c_tanh) {
        cosh_x = (cosh_h+cosh_l);
        sinh_x = (sinh_h+sinh_l);
        vf_type tanh_x=_T::sel(kf_le_35, sinh_x/cosh_x, 1.0);
        tanh_x = _T::sel(x < 0x1p-13f, x, tanh_x);
        tanh_x = copysign(tanh_x, xc);
        r = tanh_x;
    }
#endif
    return r;
}

template <typename _T>
inline
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::
cosh_k(arg_t<vf_type> x)
{
    return hyperbolic_k<hyperbolic_func::c_cosh>(x);
}

template <typename _T>
inline
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::
sinh_k(arg_t<vf_type> x)
{
    return hyperbolic_k<hyperbolic_func::c_sinh>(x);
}

template <typename _T>
inline
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::
tanh_k(arg_t<vf_type> x)
{
    return hyperbolic_k<hyperbolic_func::c_tanh>(x);
}

template <typename _T>
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::
new_cosh(arg_t<vf_type> x)
{
    using fc=func_constants<float>;
    const vf_type cosh_hi_inf= fc::cosh_hi_inf();
    vf_type res=cosh_k(x);
    res = _T::sel(abs(x) >= cosh_hi_inf, _T::pinf(), res);
    // res = _T::sel(x == 0.0, 1.0, res);
    return res;
}

template <typename _T>
inline
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::
new_sinh(arg_t<vf_type> x)
{
    using fc=func_constants<float>;
    vf_type res=sinh_k(x);
    const vf_type sinh_hi_inf= fc::sinh_hi_inf();
    const vf_type sinh_lo_inf= fc::sinh_lo_inf();
    res = _T::sel(x >= sinh_hi_inf, _T::pinf(), res);
    res = _T::sel(x <= sinh_lo_inf, _T::ninf(), res);
    res = _T::sel_zero_or_val(x == 0.0, res);
    return res;
}

template <typename _T>
inline
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::
new_tanh(arg_t<vf_type> x)
{
    vf_type res=tanh_k(x);
    // res = _T::sel(abs(x) >= cosh_hi_inf, _T::pinf(), res);
    res = _T::sel(isnan(x), x, res);
    // res = _T::sel(isinf(x), copysign(1.0, x), res);
    return res;
}

int main_cosh(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=32;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    func_domain<float> d=std::make_pair(-90.0f, 90.0f);
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        float, _N, check_cosh<float> >::v(st, d, speed_only,
                                          cmp_ulp<float>(ulp, us),
                                          cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_sinh(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=32;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    exec_stats st(_N);
    func_domain<float> d=std::make_pair(-90.0f, 90.0f);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, _N, check_sinh<float> >::v(st, d, speed_only,
                                          cmp_ulp<float>(ulp, us),
                                          cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_tanh(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=32;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    func_domain<float> d=std::make_pair(-15.0f, 15.0f);
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        float, _N, check_tanh<float> >::v(st, d, speed_only,
                                          cmp_ulp<float>(ulp, us),
                                          cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}


int main(int argc, char**argv)
{
    int r=0;
    // r |= main_cosh(argc, argv);
    r |= main_sinh(argc, argv);
    // r |= main_tanh(argc, argv);
    return r;
}
