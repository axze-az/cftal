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

            static
            dvf_type
            __pow_log(arg_t<vf_type> x);

            static
            vf_type
            pow_k(arg_t<vf_type> x, arg_t<vf_type> y);

            static
            vf_type
            pow(arg_t<vf_type> x, arg_t<vf_type> y);

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

            static vf_type func(arg_t<vf_type> vf);
            static vf_type func_k(arg_t<vf_type> vf);

        };


    }

    namespace test {

        template <typename _T>
        struct check_pow {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::pow(a, b);
            }
            static
            auto
            r(const _T& a, const _T& b) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, b, mpfr_pow, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a, const _T& b) {
                return std::pow(a, b);
            }
            static
            const char* fname() {
                return "pow";
            }
        };
    }
}
template <typename _T>
inline
typename cftal::math::test_func<double, _T>::dvf_type
cftal::math::test_func<double, _T>::
__pow_log(arg_t<vf_type> xc)
{
    using fc = func_constants<double>;
    vmf_type is_denom=xc <= fc::max_denormal();
    vf_type x=_T::sel(is_denom, xc*0x1p54, xc);
    vi2_type k=_T::sel(_T::vmf_to_vmi2(is_denom), vi2_type(-54), vi2_type(0));
    vi2_type lx, hx;
    _T::extract_words(lx, hx, x);
    /* reduce x into [sqrt(2)/2, sqrt(2)] */
    hx += 0x3ff00000 - 0x3fe6a09e;
    k += (hx>>20) - _T::bias();
    hx = (hx&0x000fffff) + 0x3fe6a09e;
    vf_type xr = _T::combine_words(lx, hx);

    // vf_type f = xr - 1.0;
    dvf_type df= d_ops::add(xr, vf_type(-1.0));
    // vf_type f= df.h();
    dvf_type dhfsq = mul_pwr2(sqr(df), vf_type(0.5));
    dvf_type ds=d_ops::sloppy_div(df, (vf_type(2.0)+df));
    // with mul12(zh, zl, ds.h(), ds.h()) pow does not become
    // faitfully rounded
    dvf_type dz=sqr(ds);
    vf_type zh=dz.h(); //, zl=dz.l();
    // d_ops::mul22(zh, zl, ds.h(), ds.l(), ds.h(), ds.l());
    // x^2 : +0xa.aaaaaaaaaaaa8p-4
    const vf_type log_c2=+6.6666666666666662965923e-01;
    // x^4 : +0xc.ccccccccceac8p-5
    const vf_type log_c4=+4.0000000000005325739849e-01;
    // x^6 : +0x9.24924921770b8p-5
    const vf_type log_c6=+2.8571428569168361155661e-01;
    // x^8 : +0xe.38e392e2fd49p-6
    const vf_type log_c8=+2.2222222656633455750708e-01;
    // x^10 : +0xb.a2e6dba5baafp-6
    const vf_type log_c10=+1.8181773614825663676342e-01;
    // x^12 : +0x9.d90aca733a8d8p-6
    const vf_type log_c12=+1.5387220163840073516859e-01;
    // x^14 : +0x8.7a5091423103p-6
    const vf_type log_c14=+1.3246549783140454392694e-01;
    // x^16 : +0x8.811edd68c1cb8p-6
    const vf_type log_c16=+1.3288089391701582431260e-01;
#if 1
    vf_type w= zh*zh;
    vf_type ey= horner(w,
                       log_c16,
                       log_c12,
                       log_c8);
    vf_type oy= horner(w,
                       log_c14,
                       log_c10,
                       log_c6);
    vf_type y= horner(zh, ey, oy, log_c4);
#else
    // vf_type w = z*z;
    vf_type y= horner(zh,
                      log_c16,
                      log_c14,
                      log_c12,
                      log_c10,
                      log_c8,
                      log_c6,
                      log_c4);
#endif
    // vf_type ye;
    // horner_comp_quick(y, ye, zh, y, log_c2);
    y = zh*y + log_c2;
    // d_ops::mul12(y, ye, zh, y);
    y *= zh;
    using ctbl=impl::d_real_constants<d_real<double>, double>;
    vf_type kf = _T::cvt_i_to_f(_T::vi2_odd_to_vi(k));

    dvf_type log_x= // kf* dvf_type(ctbl::m_ln2);
        vf_type(kf* ctbl::m_ln2_cw[1]);
    log_x += vf_type(kf*ctbl::m_ln2_cw[0]);
    // log_x += ds*dhfsq;
    // log_x += ds*dvf_type(y, ye);
    // combine these two factors to save one mul22:
    dvf_type dhfsq_y= dhfsq + y; // dvf_type(y,ye);
    log_x += ds*dhfsq_y;
    log_x += (df -dhfsq);
    return log_x;
}

template <typename _T>
inline
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::pow_k(arg_t<vf_type> x,
                                          arg_t<vf_type> y)
{
    vf_type abs_x= abs(x);
    dvf_type lnx = __pow_log(abs_x);
    dvf_type ylnx = lnx * y;
    vf_type xrh, xrl, kf;
    auto k=base_type::__reduce_exp_arg(xrh, xrl, kf, ylnx.h(), ylnx.l());
    vf_type res=base_type:: template __exp_k<false>(xrh, xrl, kf, k);
    using fc=func_constants<double>;
    const vf_type& d= ylnx.h();
    const vf_type exp_hi_inf= fc::exp_hi_inf();
    const vf_type exp_lo_zero= fc::exp_lo_zero();
    res = _T::sel(d <= exp_lo_zero, 0.0, res);
    res = _T::sel(d >= exp_hi_inf, _T::pinf(), res);
    res = _T::sel(d == 0.0, 1.0, res);
    res = _T::sel(d == 1.0, M_E, res);
    return res;
}

template <typename _T>
inline
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::pow(arg_t<vf_type> x,
                                       arg_t<vf_type> y)
{
    // we have a problem if e is an integer
    // dvf_type ln_x(my_type::log_k2(abs(x), vf_type(0)));
    // dvf_type ln_x_y(ln_x * y);
    // dvf_type pow0(my_type::exp_k2(ln_x_y.h(), ln_x_y.l(), false));
    // vf_type res(pow0.h() + pow0.l());
    // vf_type ln_x= my_type::log_k(abs(x));
    // vf_type ln_x_y = ln_x * y;
    // vf_type pow0= my_type::exp_k(ln_x_y, false);
    vf_type res=my_type::pow_k(x, y);

#if 0
    using fc=func_constants<_FLOAT_T>;
    const vf_type& d= ln_x_y;
    const vf_type exp_hi_inf= fc::exp_hi_inf;
    const vf_type exp_lo_zero= fc::exp_lo_zero;
    res = _T::sel(d <= exp_lo_zero, 0.0, res);
    res = _T::sel(d >= exp_hi_inf, _T::pinf(), res);
    res = _T::sel(d == 0.0, 1.0, res);
    res = _T::sel(d == 1.0, M_E, res);
#endif

    // guess the result if the calculation failed
    vmf_type res_nan = isnan(res);
    vmf_type abs_x_lt_1 = abs(x) < 1.0;
    vmf_type y_gt_1 = y > 1.0;
    res = _T::sel(res_nan, _T::pinf(), res);
    res = _T::sel(res_nan & abs_x_lt_1 & y_gt_1, 0.0, res);
    res = _T::sel(res_nan & (~abs_x_lt_1) & (~y_gt_1), 0.0, res);

    vmf_type y_is_int = rint(y) == y;
    vf_type y_half=0.5 *y;
    vmf_type y_is_odd = y_is_int & (rint(y_half) != y_half);

    vf_type res_fac= _T::sel(y_is_odd, vf_type(-1), vf_type(1));
    res_fac = _T::sel(~y_is_int, _T::nan(), res_fac);
    res_fac = _T::sel(x >= 0, vf_type(1), res_fac);
    res *= res_fac;

    vf_type efx= (abs(x) -1) * _T::sel(y<0, vf_type(-1), vf_type(1));

    vmf_type y_inf= isinf(y);
    vf_type t= _T::sel(efx==0.0, vf_type(1), _T::pinf());
    t = _T::sel(efx < 0.0, vf_type(0.0), t);
    res = _T::sel(y_inf, t, res);

    vmf_type x_zero = x == 0.0;
    vmf_type x_inf_or_zero= isinf(x) | x_zero;
    t= _T::sel(x_zero, -y, y);
    t= _T::sel(t < 0.0, vf_type(0), _T::pinf());
    vf_type sgn_x= copysign(vf_type(1), x);
    vf_type t1=_T::sel(y_is_odd, sgn_x, vf_type(1));
    t1 *= t;
    res = _T::sel(x_inf_or_zero, t1, res);

    res = _T::sel(isnan(x) | isnan(y), _T::nan(), res);
    res = _T::sel((y==0.0) | (x==1.0), vf_type(1), res);

#if 0
    res = xisnan(result) ? INFINITY : res;
    res *=  (x >= 0 ? 1 : (!yisint ? NAN : (yisodd ? -1 : 1)));

    double efx = mulsign(xfabs(x) - 1, y);
    if (xisinf(y)) res = efx < 0 ? 0.0 : (efx == 0 ? 1.0 : INFINITY);
    if (xisinf(x) || x == 0) res = (yisodd ? sign(x) : 1) * ((x == 0 ? -y : y) < 0 ? 0 : INFINITY);
    if (xisnan(x) || xisnan(y)) res = NAN;
    if (y == 0 || x == 1) res = 1;

    return res;
#endif
    return res;
}

int main(int argc, char** argv)
{
    using namespace cftal::test;

    const int ulp=64;
    const int _N=4;
    bool rc=true;
    bool speed_only=false;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    } else {
#if 0
        std::string test_data_dir = dirname(argv[0]);
        std::string test_data_file=
            append_filename(test_data_dir, "../../test/data/pow.testdata");
        if (argc > 1) {
            test_data_dir = argv[1];
            test_data_file = append_filename(test_data_dir, "pow.testdata");
        }
        std::vector<func_arg_result<double> > v=
            read_double_file(test_data_file, true);
        rc&= check_func_2<double, 1, check_pow<double> >(v, ulp, 0, false);
        rc&= check_func_2<double, 2, check_pow<double> >(v, ulp, 0, false);
        rc&= check_func_2<double, 4, check_pow<double> >(v, ulp, 0, false);
        rc&= check_func_2<double, 8, check_pow<double> >(v, ulp, 0, false);
#endif
    }

    func_domain<double> d=std::make_pair(-std::numeric_limits< double >::max(),
                                         std::numeric_limits< double >::max());
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_2_up_to<
        double, _N, check_pow<double> >::v(st, d, d, speed_only,
                                           cmp_ulp<double>(ulp, us),
                                           cnt>>2, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    st=exec_stats(_N);
    us=std::make_shared<ulp_stats>();
    func_domain<double> d1=std::make_pair(0.0, 20.0);
    func_domain<double> d2=std::make_pair(-100.0, 100.0);
    us= std::make_shared<ulp_stats>();
    rc &= of_fp_func_2_up_to<
        double, _N, check_pow<double> >::v(st, d1, d2, speed_only,
                                           cmp_ulp<double>(ulp, us),
                                           cnt, true);
    d1=std::make_pair(0x1p-10, 200.0);
    d2=std::make_pair(-20.0, 20.0);
    rc &= of_fp_func_2_up_to<
        double, _N, check_pow<double> >::v(st, d1, d2, speed_only,
                                           cmp_ulp<double>(ulp, us),
                                           cnt, true);

    d1=std::make_pair(0x1p-10, 5.0);
    d2=std::make_pair(-10.0, 10.0);
    rc &= of_fp_func_2_up_to<
        double, _N, check_pow<double> >::v(st, d1, d2, speed_only,
                                           cmp_ulp<double>(ulp, us),
                                           cnt, true);

    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
