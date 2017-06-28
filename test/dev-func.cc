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
            using base_type::pow_k;

            static
            vf_type pow(arg_t<vf_type> x, arg_t<vf_type> y);

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

            using base_type::ilogbp1;
            using base_type::ldexp;
            using base_type::__reduce_exp_arg;
            using base_type::__scale_exp_k;
            using base_type::__exp_k;

            static
            vf_type
            __native_exp_k(arg_t<vf_type> xrh,
                           arg_t<vf_type> xrl,
                           arg_t<vf_type> kf,
                           arg_t<vi_type> k);
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


        template <typename _T>
        struct check_func {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::func(a);
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
#if EXP>0
                _T v=call_mpfr::func(a, mpfr_exp, &i);
#else
                _T v=call_mpfr::func(a, mpfr_expm1, &i);
#endif
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
#if EXP>0
                return std::exp(a);
#else
                return std::expm1(a);
#endif
            }
            static
            const char* fname() {
#if EXP >0
                return "func-exp";
#else
                return "func-expm1";
#endif
            }
        };



    }

    // native div
    template <typename _T>
    _T
    native_div(_T a, _T b);

    template <typename _T, std::size_t _N>
    vec<_T, _N>
    native_div(const vec<_T, _N>& a, const vec<_T, _N>& b);

    template <typename _T>
    vec<_T, 1>
    native_div(const vec<_T, 1>& a, const vec<_T, 1>& b);

    v1f32
    native_div(const v1f32& a, const v1f32& b);

    v2f32
    native_div(const v2f32& a, const v2f32& b);

    v4f32
    native_div(const v4f32& a, const v4f32& b);

    v8f32
    native_div(const v8f32& a, const v8f32& b);
}

template <typename _T>
_T
cftal::native_div(_T a, _T b)
{
    return a/b;
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>
cftal::native_div(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    vec<_T, _N> r(native_div(low_half(a), low_half(b)),
                  native_div(high_half(a), high_half(b)));
    return r;
}

template <typename _T>
cftal::vec<_T, 1>
cftal::native_div(const vec<_T, 1>& a, const vec<_T, 1>& b)
{
    vec<_T, 1> r(native_div(a(), b()));
    return r;
}

inline
cftal::v1f32
cftal::native_div(const v1f32& b, const v1f32& a)
{
#if defined (__SSE__)
    v1f32 rcp=_mm_cvtss_f32(_mm_rcp_ss(_mm_set_ss(a())));
    rcp = rcp + rcp*(1-rcp*a);
#if 1
    return b*rcp;
#else
    // goldstein iteration
    v1f32 x= b*rcp;
    v1f32 y= a*rcp;
    v1f32 r= 2-y;
    y= r*y;
    v1f32 bda= r*x;
    return bda;
#endif
#else
    return x/y;
#endif
}

inline
cftal::v2f32
cftal::native_div(const v2f32& x, const v2f32& y)
{
#if defined (__SSE__)
    v4f32 x4(x, x);
    v4f32 y4(y, y);
    return low_half(native_div(x4, y4));
#else
    return x/y;
#endif
}

inline
cftal::v4f32
cftal::native_div(const v4f32& b, const v4f32& a)
{
#if defined (__SSE__)
    v4f32 rcp=_mm_rcp_ps(a());
    rcp = rcp + rcp*(1-rcp*a);
#if 1
    return b*rcp;
#else
    // goldstein iteration
    v4f32 x= b*rcp;
    v4f32 y= a*rcp;
    v4f32 r= 2-y;
    y= r*y;
    v4f32 bda= r*x;
    return bda;
#endif
#else
    return x/y;
#endif
}

inline
cftal::v8f32
cftal::native_div(const v8f32& b, const v8f32& a)
{
#if defined (__AVX__)
    v8f32 rcp=_mm256_rcp_ps(a());
    rcp = rcp + rcp*(1-rcp*a);
#if 1
    return b*rcp;
#else
    // goldstein iteration
    v8f32 x= b*rcp;
    v8f32 y= a*rcp;
    v8f32 r= 2-y;
    y= r*y;
    v8f32 bda= r*x;
    return bda;
#endif
#else
    return a/b;
#endif
}

template <typename _T>
inline
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::
__native_exp_k(arg_t<vf_type> xrh,
               arg_t<vf_type> xrl,
               arg_t<vf_type> kf,
               arg_t<vi_type> k)
{
#if 0
#if 0
    // [0, 0.3465735912322998046875] : | p - f | <= 2^-27.578125
    // coefficients for native_exp generated by sollya
    // x^0 : +0xa.aaaabp-6f
    const float native_exp_c0=+1.6666667163e-01f;
    // x^2 : -0xb.60dfap-12f
    const float native_exp_c2=-2.7779326774e-03f;
    // x^4 : +0x8.c6d66p-17f
    const float native_exp_c4=+7.0000000000e-05f;
    vf_type xx= xrh*xrh;
    vf_type P= impl::poly(xx,
                          native_exp_c4,
                          native_exp_c2,
                          native_exp_c0);
    vf_type br= xrh- xx*P;
#if 0
    vf_type t= br/(2.0f-br);
    vf_type y, ye;
    d_ops::add12(y, ye, vf_type(1.0), t);
    vf_type yl=y+ye;
    impl::eft_poly_si(y, ye, xrh, y, ye, vf_type(1.0));
    ye += xrl + xrl*xrh*yl;
    y += ye;
#else
    // y += (xrh*br)/(2.0f-br) + xrh;
    vf_type t= (xrh*br)/(2.0f-br) + xrh;
    vf_type y = xrl + xrl*t;
    y += t;
    y += 1.0f;
#endif
    y = __scale_exp_k(y, kf, k);
    return y;
#else
    // exp(x) = 1 + 2x/(2-x+x^2*P(x^2)
    //                    x [x - x^2 * P]
    //        = 1 + x + ------------------
    //                    2 - [x - x^2 * P]
    // x^2 : +0xa.aaa8fp-6f
#if 0
    // pade 4, 4, taylor 8 of %e^x-1-x faithfully
    vf_type p= horner(xrh,
                      +60.0f,
                      -280.0f,
                      +4200.0f)*xrh*xrh;
    vf_type q= horner1(xrh,
                       // 1.0f
                       -40.0f,
                       +540.0f,
                       -3360.0f,
                       +8400.0f);
    vf_type y= xrh + p/q;
    vf_type ye= xrl + xrl*xrh;
    y += ye;
    y += 1.0f;
    y = __scale_exp_k(y, kf, k);
    return y;
#endif
#if 1

    vf_type e= horner(xrh,
                      7.610925536017418e1f,
                      8.73744877496524e2f,
                      4.256882124716833e3f,
                      8.368816062267611e3f);
    vf_type d= horner(xrh,
                      -6.4e1f,
                      8.012710646668774e2f,
                      -4.111933953502037e3f,
                      8.36881606265761e3f);
#if 0
    vmf_type x_lt_z = xrh < vf_type(0.0);
    vf_type p= _T::sel(x_lt_z, d, e);
    vf_type q= _T::sel(x_lt_z, e, d);
    vf_type y= p/q;
#else
    vf_type y= e/d;
#endif
    vf_type ye= xrl + xrl*xrh;
    y += ye;
    y = __scale_exp_k(y, kf, k);
    return y;
#endif
#endif
#else
    // [-0.3465735912322998046875, 0.3465735912322998046875] : | p - f | <= 2^-32.609375
    // coefficients for exp generated by sollya
    // x^0 : +0x8p-3f
    const float exp_c0=+1.0000000000e+00f;
    // x^1 : +0x8p-3f
    const float exp_c1=+1.0000000000e+00f;
    // x^2 : +0x8p-4f
    const float exp_c2=+5.0000000000e-01f;
    // x^3 : +0xa.aaaa9p-6f
    const float exp_c3=+1.6666664183e-01f;
    // x^4 : +0xa.aaa73p-8f
    const float exp_c4=+4.1666459292e-02f;
    // x^5 : +0x8.88ae5p-10f
    const float exp_c5=+8.3338962868e-03f;
    // x^6 : +0xb.6a77ep-13f
    const float exp_c6=+1.3935414609e-03f;
    // x^7 : +0xc.d3317p-16f
    const float exp_c7=+1.9569355936e-04f;
#if 1
    vf_type y= impl::estrin(xrh,
                            exp_c7,
                            exp_c6,
                            exp_c5,
                            exp_c4,
                            exp_c3,
                            exp_c2);
#else
    vf_type xx= xrh*xrh;
    vf_type i=horner(xx,
                     exp_c7,
                     exp_c5);
    vf_type j=horner(xx,
                     exp_c6,
                     exp_c4);
    vf_type y= horner(xrh, i, j, exp_c3, exp_c2);
#endif
    vf_type ye;
    horner_comp_quick(y, ye, xrh, y, exp_c1);
    // correction for errors in argument reduction
    vf_type yl=y +ye;
    horner_comp_quick_si(y, ye, xrh, y, ye, exp_c0);
    vf_type yee= xrl + xrl*xrh*yl;
    ye += yee;
    y += ye;
    y = __scale_exp_k(y, kf, k);
    return y;
#endif
}

template <typename _T>
inline
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::func_k(arg_t<vf_type> xc)
{
    vf_type xrh, xrl, kf;
    auto k= __reduce_exp_arg(xrh, xrl, kf, xc);
#if EXP> 0
    auto y= __native_exp_k(xrh, xrl, kf, k);
#else
    // exp(x) = 1 + 2x/(2-x+x^2*P(x^2)
    //                    x [x - x^2 * P]
    //        = 1 + x + ------------------
    //                    2 - [x - x^2 * P]
    // [0, 0.3465735912322998046875] : | p - f | <= 2^-27.578125
    // coefficients for native_exp generated by sollya
    // x^0 : +0xa.aaaabp-6f
    const float native_exp_c0=+1.6666667163e-01f;
    // x^2 : -0xb.60dfap-12f
    const float native_exp_c2=-2.7779326774e-03f;
    // x^4 : +0x8.c6d66p-17f
    const float native_exp_c4=+7.0000000000e-05f;
    vf_type xx= xrh*xrh;
    vf_type P= impl::poly(xx,
                          native_exp_c4,
                          native_exp_c2,
                          native_exp_c0);
    vf_type br= xrh- xx*P;
    vf_type t= br/(2.0f-br);
    vf_type y, ye;
    d_ops::add12(y, ye, vf_type(1.0), t);
    impl::eft_poly_si(y, ye, xrh, y, ye, vf_type(1.0));
    ye += xrl + xrl*xrh;
    // 2^kf = 2*2^s ; s = kf/2
    vf_type scale = __scale_exp_k(vf_type(0.5f), kf, k);
    // e^x-1 = 2*(y * 2^s - 0.5)
    impl::eft_poly_si(y, ye, scale, y, ye, vf_type(-0.5f));
    y *= 2;
    y  = y + 2*ye;
    // x small, required for handling of subnormal numbers
    y = _T::sel((abs(xrh) < 0x1p-25f) & (kf==0.0), xrh, y);
    return y;
#endif
    return y;
}

template <typename _T>
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::
func(arg_t<vf_type> d)
{
#if EXP
    vf_type res=func_k(d);
    using fc= func_constants<float>;
    const vf_type exp_hi_inf= fc::exp_hi_inf();
    const vf_type exp_lo_zero= fc::exp_lo_zero();
    res = _T::sel(d <= exp_lo_zero, 0.0, res);
    res = _T::sel(d >= exp_hi_inf, _T::pinf(), res);
    res = _T::sel(d == 0.0, 1.0, res);
    res = _T::sel(d == 1.0, M_E, res);
    return res;
#else
    vf_type res = func_k(d);
    using fc= func_constants<float>;
    const vf_type expm1_hi_inf= fc::expm1_hi_inf();
    const vf_type expm1_lo_minus_one= fc::expm1_lo_minus_one();
    res = _T::sel(d <= expm1_lo_minus_one, -1.0, res);
    res = _T::sel(d >= expm1_hi_inf, _T::pinf(), res);
    res = _T::sel(d == 0.0, 0.0, res);
    res = _T::sel(d == 1.0, M_E-1.0, res);
    return res;
#endif
}

#if 0
int main(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    using ftype = float;

    // func_domain<double> d=std::make_pair(0.0,
    //                                     std::numeric_limits< double >::max());
    func_domain<ftype> d=std::make_pair(-std::numeric_limits<ftype>::max(),
                                         std::numeric_limits<ftype>::max());
#if EXP>0
    d=std::make_pair(-104.0f, 89.0f);
#else
    d=std::make_pair(-18.0f, 89.0f);
    // d=std::make_pair(-M_LN2/2, M_LN2/2);
#endif
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_func<ftype> >::v(st, d, speed_only,
                                          cmp_ulp<ftype>(ulp, us),
                                          cnt);
#if 0
    d=std::make_pair(-0x1p-4, 0x1p-4);
    rc &= of_fp_func_up_to<
        ftype, _N, check_func<ftype> >::v(st, d, speed_only,
                                           cmp_ulp<ftype>(ulp, us),
                                           cnt>>2);
#endif
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
#endif

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
#if 0
    return 0;
#else
    const int ulp=64;
    const int _N=8;
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
                                           cnt>>2, false);
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
#endif
}
