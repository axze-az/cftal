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
            vf_type
            root12_k(arg_t<vf_type> x);

            static
            vf_type
            root12(arg_t<vf_type> x);
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
        struct check_root12 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
#if 0
                // return sqrt(sqrt(cbrt(a))); // 1351533  
                // return cbrt(sqrt(sqrt(a))); //  927090
                // return sqrt(cbrt(sqrt(a))); // 1289438
#else
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::root12(a);
#endif
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_ext::root12, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::cbrt(std::sqrt(std::sqrt(a)));
                // return std::pow(a, 1.0/12.0);
            }
            static
            const char* fname() {
                return "root12";
            }
        };

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

namespace cftal {
    namespace math {
        template <typename _X, typename _C>
        _X
        fast_poly(_X x,
                  _C a3, _C a2, _C a1, _C a0);

        template <typename _X, typename _C>
        _X
        fast_poly(_X x,
                  _C a4,
                  _C a3, _C a2, _C a1, _C a0);


        template <typename _X, typename _C>
        _X
        fast_poly(_X x,
                  _C a5, _C a4,
                  _C a3, _C a2, _C a1, _C a0);

        template <typename _X, typename _C>
        _X
        fast_poly(_X x,
                  _C a6, _C a5, _C a4,
                  _C a3, _C a2, _C a1, _C a0);

    }
}
template <typename _X, typename _C>
_X
cftal::math::
fast_poly(_X x,
          _C a3, _C a2, _C a1, _C a0)
{
    // ((a0+(x*a1))+((x*x)*(a2+(x*a3))))
    _X a0xa1= a0+x*a1; _X a2xa3= a2+x*a3; _X x2=x*x;
    _X r= a0xa1+ x2*a2xa3;
    return r;
}

template <typename _X, typename _C>
_X
cftal::math::
fast_poly(_X x,
          _C a4,
          _C a3, _C a2, _C a1, _C a0)
{

    // (((a0+(x*a1))+((x*x)*a2))+((x*(x*x))*(a3+(x*a4))))
    _X x2=x*x; _X a0xa1= a0+x*a1; _X a3xa4= a3+x*a4;
    _X le= a0xa1 + x2*a2; _X re= x2* a3xa4;
    _X r= le+ x*re;
    return r;
}

template <typename _X, typename _C>
_X
cftal::math::
fast_poly(_X x,
            _C a5, _C a4,
            _C a3, _C a2, _C a1, _C a0)
{
    // estrin:
    // (((a0+(x*a1))+((x*x)*(a2+(x*a3))))+(((x*x)*(x*x))*(a4+(x*a5))))
    // step 1
    _X x2=x*x;
    _X a2xa3= a2 + x*a3; _X a4xa5= a4 + x*a5; _X a0xa1= a0 + x*a1;
    _X x4=x2*x2;
    _X le= a0xa1 + x2* a2xa3;
    _X r= le + x4 * a4xa5;
    return r;
}

template <typename _X, typename _C>
_X
cftal::math::
fast_poly(_X x,
          _C a6, _C a5, _C a4,
          _C a3, _C a2, _C a1, _C a0)
{
    // (((a0+(x*a1))+((x*x)*(a2+(x*a3))))+(((x*x)*(x*x))*((a4+(x*a5))+((x*x)*a6))))
    // step 1
    _X x2=x*x;
    _X a2xa3= a2 + x*a3; _X a4xa5= a4 + x*a5; _X a0xa1= a0 + x*a1;
    _X x4=x2*x2;
    // step 2
    _X le= a0xa1 + x2* a2xa3; _X re= a4xa5 + x2* a6;
    // step 3
    _X r= le + x4* re;
    return r;
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
#if 1
#if 1
    // [0, 0.3465735912322998046875] : | p - f | <= 2^-27.578125
    // coefficients for native_exp generated by sollya
    // x^0 : +0xa.aaaabp-6f
    const float native_exp_c0=+1.6666667163e-01f;
    // x^2 : -0xb.60dfap-12f
    const float native_exp_c2=-2.7779326774e-03f;
    // x^4 : +0x8.c6d66p-17f
    const float native_exp_c4=+7.0000000000e-05f;
    vf_type xx= xrh*xrh;
    vf_type P= horner(xx,
                      native_exp_c4,
                      native_exp_c2,
                      native_exp_c0);
    vf_type br= xrh- xx*P;
#if 0
    vf_type t= br/(2.0f-br);
    vf_type y, ye;
    d_ops::add12(y, ye, vf_type(1.0), t);
    // vf_type yl=y+ye;
    horner_comp_quick_si(y, ye, xrh, y, ye, vf_type(1.0));
    ye += xrl + xrl*xrh;
    y += ye;
#else
    // y += (xrh*br)/(2.0f-br) + xrh;
    vf_type t= (xrh*br)/(2.0f-br) + xrh;
    // vf_type t= native_div(vf_type(xrh*br),vf_type(2.0f-br)) + xrh;
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
#if 1
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

    vf_type y= fast_poly(xrh,
                         exp_c7,
                         exp_c6,
                         exp_c5,
                         exp_c4,
                         exp_c3,
                         exp_c2,
                         exp_c1);
    vf_type yl=y;
    vf_type yee= xrl + xrl*xrh*yl;
    y = horner(xrh, y, exp_c0);
    y += yee;
    y = __scale_exp_k(y, kf, k);
    return y;
#else
    vf_type xx= xrh*xrh;
    vf_type i=horner(xx,
                     exp_c7,
                     exp_c5);
    vf_type j=horner(xx,
                     exp_c6,
                     exp_c4);
    vf_type y= horner(xrh, i, j, exp_c3, exp_c2);
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
    vf_type P= horner(xx,
                      native_exp_c4,
                      native_exp_c2,
                      native_exp_c0);
    vf_type br= xrh- xx*P;
    vf_type t= br/(2.0f-br);
    vf_type y, ye;
    d_ops::add12(y, ye, vf_type(1.0), t);
    horner_comp_quick_si(y, ye, xrh, y, ye, vf_type(1.0));
    ye += xrl + xrl*xrh;
    // 2^kf = 2*2^s ; s = kf/2
    vf_type scale = __scale_exp_k(vf_type(0.5f), kf, k);
    // e^x-1 = 2*(y * 2^s - 0.5)
    horner_comp_si(y, ye, scale, y, ye, vf_type(-0.5f));
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
    const int ulp=256;
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
                                          cnt, true);
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

namespace cftal {
    namespace math {

        namespace impl {
            struct root12 {
                // x^12 = y 
                template <typename _T>
                static
                _T
                nr(_T y, _T x);
                
                template <typename _T>
                static
                _T
                halley(_T y, _T x);

                template <typename _T>
                static
                _T
                householder3(_T x, _T y);

                template <typename _T>
                static
                _T
                householder4(_T x, _T y);

                template <typename _T>
                static
                _T
                householder5(_T x, _T y);
            };
            
        }
    }
}

template <typename _T>
_T
cftal::math::impl::root12::nr(_T x, _T y)
{
    _T x2=x*x;
    _T x3=x2*x;
    _T x6=x3*x3;
    _T x11=x6*x3*x2;
    _T xn = x - _T(1.0/12.0) * (x - y/x11);
    return xn;
}

template <typename _T>
_T
cftal::math::impl::root12::halley(_T x, _T y)
{
    _T x2=x*x;
    _T x4=x2*x2;
    _T x8=x4*x4;
    _T x12=x8*x4;
    _T num= _T(2.0/11.0) * x * (y - x12);
    _T denom= y + _T(13.0/11.0) *x12;
    _T xn = x + num/denom;
    return xn;
}

template <typename _T>
_T
cftal::math::impl::root12::householder3(_T x, _T y)
{
    _T x2=x*x;
    _T x4=x2*x2;
    _T x8=x4*x4;
    _T x12=x8*x4;
    _T y1=y;
    _T y2=y*y;
    _T num= x*horner(x12,
                     _T(-39.0),
                     _T(6.0)*y1,
                     _T(33.0)*y2);
    _T denom= horner(x12,
                     _T(182.0),
                     _T(572.0)*y1,
                     _T(110)*y2);
    _T xn = x + num/denom;
    return xn;
}
    
template <typename _T>
_T
cftal::math::impl::root12::householder4(_T x, _T y)
{
    _T x2=x*x;
    _T x4=x2*x2;
    _T x8=x4*x4;
    _T x12=x8*x4;
    _T y1=y;
    _T y2=y*y;
    _T y3=y1*y2;
    _T num= x*horner(x12,
                     _T(-364.0),
                     _T(-780)*y1,
                     _T(924.0)*y2,
                     _T(220.0)*y3);
    _T denom= horner(x12,
                     _T(1365.0),
                     _T(10725.0)*y1,
                     _T(8151.0)*y2,
                     _T(495.0)*y3);
    _T xn = xn + num/denom;
    return xn;
}
    
template <typename _T>
_T
cftal::math::impl::root12::householder5(_T x, _T y)
{
    _T x2=x*x;
    _T x4=x2*x2;
    _T x8=x4*x4;
    _T x12=x8*x4;
    _T y1=y;
    _T y2=y*y;
    _T y3=y1*y2;
    _T y4=y2*y2;
    _T num= x*horner(x12,
                     _T(-455.0),
                     _T(-3120.0)*y1,
                     _T(858.0)*y2,
                     _T(2552.0)*y3,
                     _T(165.0)*y4);
    _T denom= horner(x12,
                     _T(1456.0),
                     _T(24024.0)*y1,
                     _T(44616.0)*y2,
                     _T(12584.0)*y3,
                     _T(264.0)*y4);
    _T xn = x + num/denom;
    return xn;
}

template <typename _T>
typename cftal::math::test_func<double, _T>::vf_type
__attribute__((flatten))
cftal::math::test_func<double, _T>::
root12_k(arg_t<vf_type> xc)
{
    // reduce x into [2^-12, 1.0)
    const int32_t shift_1_12= 0x11;
    const int32_t fac_1_12= 0x2aab;

    vf_type xp=abs(xc);
    vf_type mm0;
    auto e=base_type::__frexp_k(mm0, xp);
    e=copy_odd_to_even(e);
    // do a division by 3
    // vi2_type e3 = (((e)*fac_1_3)>>shift_1_3) -(e>>31);
    // do a division by 3 rounded to - infinity
    const vi2_type v_bias_12(12*_T::bias()), v_bias(_T::bias());
    vi2_type e12_with_bias = (((e+v_bias_12)*fac_1_12)>>shift_1_12);
    vi2_type e12 =e12_with_bias - v_bias;
    // r is always in [0, 1, 11] because of the round down
    vi2_type r = e - e12 *12;

    // correction of mm0 in dependence of r
    // r    scale   log_2(scale) r - 12
    // 1    ...     -11          -11
    // 2            -10
    // 3            -9
    // 4            -8           ....
    // 5            -7
    // 6            -6
    // 7            -5
    // 8            -4
    // 9            -3
    // 10   0.25    -2           -2
    // 11   0.5     -1           -1
    // 0    1.0     -0            0
    // -1   0.5     -1           -4
    // -2   0.25    -2           -5
    vmi2_type r_ne_z = r != 0;
    e12_with_bias=_T::sel(r_ne_z, e12_with_bias+1, e12_with_bias);

    // log_2(scale) = bias + (r-12) = bias - 12 + r
    const vi2_type v_bias_plus_12(_T::bias()-12);
    vf_type scale = _T::insert_exp(v_bias_plus_12 + r);
    vmf_type f_r_ne_z = _T::vmi2_to_vmf(r_ne_z);
    scale = _T::sel(f_r_ne_z, scale, 1.0);
    mm0 = mm0 * scale;
#if 1
#if 1
    // [2.44140625e-4, 1] : | p - f | <= 2^-2.6767578125
    // coefficients for root12 generated by sollya
    // x^0 : +0x9.3e756ac285bb8p-4
    const vf_type root12_c0=+5.7774869635646453058797e-01;
    // x^1 : +0xe.45350dc5fb91p-3
    const vf_type root12_c1=+1.7837925983471412116899e+00;
    // x^2 : -0xc.24adbc4221718p-3
    const vf_type root12_c2=-1.5179094989472836640942e+00;
    vf_type mm = horner(mm0,
                        root12_c2,
                        root12_c1,
                        root12_c0);
    // faithful: 884098
    // const int halley=4; const int nr=2;
    // faithful: 846889
    const int order5=2;
    const int order4=0;
    const int order3=0;
    const int halley=0;
    const int nr=2;
#endif
#if 0
    // faithful: 864807
    vf_type mm = M_SQRT2/2;
    // vf_type mm = M_SQRT2/2;
    // faithful: 
    const int order5=3;
    const int order4=0;
    const int order3=0;
    const int halley=0;
    const int nr=2;
#endif

    for (int i=0; i<order5; ++i) {
        mm = impl::root12::householder5(mm, mm0);
    }

    for (int i=0; i<order4; ++i) {
        mm = impl::root12::householder4(mm, mm0);
    }

    for (int i=0; i<order3; ++i) {
        mm = impl::root12::householder3(mm, mm0);
    }

    for (int i=0; i<halley; ++i) {
        mm = impl::root12::halley(mm, mm0);
    }
    for (int i=0; i<nr; ++i) {
        mm = impl::root12::nr(mm, mm0);
    }
#else
    // faithful: 927090
    vf_type mm= cbrt(sqrt(sqrt(mm0)));
#endif
    vf_type t= _T::insert_exp(e12_with_bias);
    mm *=t;
    // mm = copysign(mm, xc);
    return mm;
}

template <typename _T>
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::
root12(arg_t<vf_type> x)
{
    vf_type y= root12_k(x);
    y=_T::sel(isnan(x), x, y);
    y=_T::sel(x == _T::pinf(), _T::pinf(), y);
    y=_T::sel(x == 0, 0.0, y);
    y=_T::sel(x < 0.0, _T::nan(), y);
    return y;
}

int main(int argc, char** argv)
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
    }
    func_domain<double> dd=std::make_pair(0.0,
                                          std::numeric_limits<double>::max());
    // dd=std::make_pair(0.125, 1.0);
    auto us=std::make_shared<ulp_stats>();
    exec_stats d_st(_N);
    rc &= of_fp_func_up_to<
        double, _N, check_root12<double> >::v(d_st, dd, speed_only,
                                              cmp_ulp<double>(ulp, us),
                                              cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << d_st << std::endl;
    return rc==true ? 0 : 1;
}
