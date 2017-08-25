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


            template <bool _EXP_M1>
            static
            vf_type
            __native_exp_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
                           arg_t<vf_type> kf, arg_t<vi2_type> k);

            template <bool _EXP_M1>
            static
            vf_type
            native_exp_k(arg_t<vf_type> x);

            static
            vf_type
            native_exp(arg_t<vf_type> x);

            static
            vf_type
            native_expm1(arg_t<vf_type> x);
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
            __half_exp_k(arg_t<vf_type> xrh,
                         arg_t<vf_type> kf,
                         arg_t<vi_type> k);

            static
            vf_type
            half_exp_k(arg_t<vf_type> x);

            static
            vf_type
            half_exp(arg_t<vf_type> x);

            static
            vf_type
            half_exp2_k(arg_t<vf_type> x);

            static
            vf_type
            half_exp2(arg_t<vf_type> x);

            static
            vf_type
            half_exp10_k(arg_t<vf_type> x);

            static
            vf_type
            half_exp10(arg_t<vf_type> x);

            static
            vf_type
            half_log_k(arg_t<vf_type> x);

            static
            vf_type
            half_log(arg_t<vf_type> x);

            static
            vf_type
            half_log2(arg_t<vf_type> x);

            static
            vf_type
            half_log10(arg_t<vf_type> x);

            static
            std::pair<vf_type, vi_type>
            __half_reduce_trig_arg(arg_t<vf_type> x);

            static
            void
            half_sin_cos_k(arg_t<vf_type> x, vf_type* s, vf_type* c);

            static
            vf_type
            half_sin(arg_t<vf_type> x);

            static
            vf_type
            half_cos(arg_t<vf_type> x);

            static
            vf_type
            half_tan(arg_t<vf_type> x);

        };
    }

    namespace math {

        template <typename _FLOAT_T, typename _TRAITS_T>
        struct half_elem_func_core {
        };

        // common implementation of base and elementary functions
        // special argument handling like inf, nan, overflow, underflow
        // is done here
        template <typename _FLOAT_T, typename _TRAITS_T>
        struct half_elem_func
            : public half_elem_func_core< _FLOAT_T, _TRAITS_T> {
        };

        template <typename _T>
        struct half_elem_func_core<float, _T>
            : public elem_func_core<float, _T> {
            using base_type = elem_func_core<float, _T>;
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
        struct check_native_exp {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                auto r=func_t::native_exp(a);
                return r;
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_exp, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::exp(a);
            }
            static
            const char* fname() {
                return "native_exp";
            }
        };

        template <typename _T>
        struct check_native_expm1 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                auto r=func_t::native_expm1(a);
                return r;
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_expm1, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::expm1(a);
            }
            static
            const char* fname() {
                return "native_expm1";
            }
        };

        template <typename _T>
        struct check_half_exp2 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::half_exp2(a);
            }
            static
            auto
            r(const _T& a) {
                // _T v=call_mpfr::func(a, mpfr_exp2);
                vec<_T, 4> aa(a);
                return extract<0>(exp2(aa));
            }
            static
            _T
            s(const _T& a) {
                return std::exp2(a);
            }
            static
            const char* fname() {
                return "half_exp2";
            }
        };

        template <typename _T>
        struct check_half_exp10 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::half_exp10(a);
            }
            static
            auto
            r(const _T& a) {
                // _T v=call_mpfr::func(a, mpfr_ext::exp10);
                vec<_T, 4> aa(a);
                return extract<0>(exp10(aa));
            }
            static
            _T
            s(const _T& a) {
                return ::exp10(a);
            }
            static
            const char* fname() {
                return "half_exp10";
            }
        };

        template <typename _T>
        struct check_half_log {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::half_log(a);
            }
            static
            auto
            r(const _T& a) {
                vec<_T, 4> aa(a);
                return extract<0>(log(aa));
            }
            static
            _T
            s(const _T& a) {
                return std::log(a);
            }
            static
            const char* fname() { return "half_log"; }
        };

        template <typename _T>
        struct check_half_log2 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::half_log2(a);
            }
            static
            auto
            r(const _T& a) {
                vec<_T, 4> aa(a);
                return extract<0>(log2(aa));
            }
            static
            _T
            s(const _T& a) {
                return std::log2(a);
            }
            static
            const char* fname() { return "half_log2"; }
        };

        template <typename _T>
        struct check_half_log10 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::half_log10(a);
            }
            static
            auto
            r(const _T& a) {
                vec<_T, 4> aa(a);
                return extract<0>(log10(aa));
            }
            static
            _T
            s(const _T& a) {
                return std::log10(a);
            }
            static
            const char* fname() { return "half_log10"; }
        };

        template <typename _T>
        struct check_half_sin {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::half_sin(a);
            }
            static
            auto
            r(const _T& a) {
                vec<_T, 4> aa(a);
                return extract<0>(sin(aa));
            }
            static
            _T
            s(const _T& a) {
                return std::sin(a);
            }
            static
            const char* fname() { return "half_sin"; }
        };

        template <typename _T>
        struct check_half_cos {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::half_cos(a);
            }
            static
            auto
            r(const _T& a) {
                vec<_T, 4> aa(a);
                return extract<0>(cos(aa));
            }
            static
            _T
            s(const _T& a) {
                return std::cos(a);
            }
            static
            const char* fname() { return "half_cos"; }
        };

        template <typename _T>
        struct check_half_tan {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::half_tan(a);
            }
            static
            auto
            r(const _T& a) {
                vec<_T, 4> aa(a);
                return extract<0>(tan(aa));
            }
            static
            _T
            s(const _T& a) {
                return std::tan(a);
            }
            static
            const char* fname() { return "half_tan"; }
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
}


template <typename _T>
template <bool _EXP_M1>
__attribute__((always_inline))
inline
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::
__native_exp_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
               arg_t<vf_type> kf, arg_t<vi2_type> k2)
{
#if 1
    // [-0.3465735912322998046875, 0.3465735912322998046875] : | p - f | <= 2^-67.5
    // coefficients for exp generated by sollya
    // x^0 : +0x8p-3
    const double exp_c0=+1.0000000000000000000000e+00;
    // x^1 : +0x8p-3
    const double exp_c1=+1.0000000000000000000000e+00;
    // x^2 : +0x8p-4
    const double exp_c2=+5.0000000000000000000000e-01;
    // x^3 : +0xa.aaaaaaaaaaaa8p-6
    const double exp_c3=+1.6666666666666665741481e-01;
    // x^4 : +0xa.aaaaaaaaaaacp-8
    const double exp_c4=+4.1666666666666685170384e-02;
    // x^5 : +0x8.888888888961p-10
    const double exp_c5=+8.3333333333340843529502e-03;
    // x^6 : +0xb.60b60b60a81p-13
    const double exp_c6=+1.3888888888873365812238e-03;
    // x^7 : +0xd.00d00cfa88cc8p-16
    const double exp_c7=+1.9841269839039331096715e-04;
    // x^8 : +0xd.00d00d6b5b978p-19
    const double exp_c8=+2.4801587348902822885563e-05;
    // x^9 : +0xb.8ef1e87f81768p-22
    const double exp_c9=+2.7557322326013774747291e-06;
    // x^10 : +0x9.3f26623e02258p-25
    const double exp_c10=+2.7557252167692825528943e-07;
    // x^11 : +0xd.72da4d99dd1ep-29
    const double exp_c11=+2.5050050656120229688701e-08;
    // x^12 : +0x8.fc5bcb2f9dd7p-32
    const double exp_c12=+2.0921639307947297714762e-09;
    // x^13 : +0xb.675e3aadcbc88p-36
    const double exp_c13=+1.6594686274338619941159e-10;
    vf_type xx=xrh*xrh;
    vf_type i=horner(xx,
                     exp_c13,
                     exp_c11,
                     exp_c9,
                     exp_c7,
                     exp_c5);
    vf_type j=horner(xx,
                     exp_c12,
                     exp_c10,
                     exp_c8,
                     exp_c6,
                     exp_c4);
    vf_type y=horner(xrh, i, j, exp_c3, exp_c2);
    if (_EXP_M1 == false) {
        y = horner(xrh, y, exp_c1)*xrh;
        // calculate y==expm1, for correction term
        vf_type yee= xrl + xrl * y;
        vf_type ye;
        d_ops::add12(y, ye, exp_c0, y);
        ye += yee;
        y += ye;
        y = base_type::__scale_exp_k(y, kf, k2);
    } else {
        vf_type ye;
        y = y*xrh;
        d_ops::add12(y, ye, exp_c1, y);
        // y+ye = expm1/xrh
        vf_type yee= xrl + xrl * xrh * (y+ye);
        horner_comp_quick_si(y, ye, xrh, y, ye, exp_c0);
        ye += yee;
        // 2^kf = 2*2^s ; s = kf/2
        vf_type scale = base_type::__scale_exp_k(vf_type(0.5), kf, k2);
        // e^x-1 = 2*(y * 2^s - 0.5)
        horner_comp_si(y, ye, scale, y, ye, vf_type(-0.5));
        y *= 2;
        y  = y + 2*ye;
        // x small, required for handling of subnormal numbers
        y = _T::sel((abs(xrh) < 0x1p-512) & (kf==0.0), xrh, y);
    }
    return y;
#else
    // exp(x) = 1 + 2x/(2-x+x^2*P(x^2)
    //                    x [x - x^2 * P]
    //        = 1 + x + ------------------
    //                    2 - [x - x^2 * P]
    // [0, 0.3465735912322998046875] : | p - f | <= 2^-56.578125
    // coefficients for expn generated by sollya
    // x^0 : +0xa.aaaaaaaaaaaa8p-6
    const vf_type expn_c0=+1.6666666666666665741481e-01;
    // x^2 : -0xb.60b60b60af088p-12
    const vf_type expn_c2=-2.7777777777762209694690e-03;
    // x^4 : +0x8.ab355dd7070ep-17
    const vf_type expn_c4=+6.6137566063822030622971e-05;
    // x^6 : -0xd.debafedf4fbdp-23
    const vf_type expn_c6=-1.6534377129482213292548e-06;
    // x^8 : +0xb.3469aa5968fdp-28
    const vf_type expn_c8=+4.1740899259070261892474e-08;
    // x^10 : -0x8.b38f6a7d59358p-33
    const vf_type expn_c10=-1.0129771083725208005378e-09;
    vf_type xx= xrh*xrh;
    vf_type P= horner(xx,
                      expn_c10,
                      expn_c8,
                      expn_c6,
                      expn_c4,
                      expn_c2,
                      expn_c0);
    vf_type br= xrh- xx*P;
    vf_type t = (br)/(2.0-br);
#if 1
    vf_type y, ye;
    horner_comp(y, ye, xrh, t, xrh);
    vf_type yee = xrl + xrl * (y+ye);
    d_ops::add122(y, ye, 1.0, y, ye);
    ye = ye + yee;
#else
    vf_type y, ye;
    d_ops::mul12(y, ye, xrh, t);
    d_ops::add122(y, ye, xrh, y, ye);
    vf_type yee = xrl + xrl * (y+ye);
    d_ops::add122(y, ye, 1.0, y, ye);
    ye += yee;
#endif
    if (_EXP_M1 == false) {
        y += ye;
        y = base_type::__scale_exp_k(y, kf, k2);
    } else {
        // 2^kf = 2*2^s ; s = kf/2
        vf_type scale = base_type::__scale_exp_k(vf_type(0.5), kf, k2);
        // e^x-1 = 2*(y * 2^s - 0.5)
        horner_comp_si(y, ye, scale, y, ye, vf_type(-0.5));
        y *= 2;
        y  = y + 2*ye;
        // x small, required for handling of subnormal numbers
        y = _T::sel((abs(xrh) < 0x1p-512) & (kf==0.0), xrh, y);
    }
    return y;
#endif
}

template <typename _T>
template <bool _EXP_M1>
inline
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::
native_exp_k(arg_t<vf_type> xc)
{
    vf_type xrh, xrl, kf;
    auto k=base_type::__reduce_exp_arg(xrh, xrl, kf, xc);
    vf_type y=__native_exp_k<_EXP_M1>(xrh, xrl, kf, k);
    return y;
}

template <typename  _T>
inline
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::
native_exp(arg_t<vf_type> d)
{
    vf_type res=native_exp_k<false>(d);
    using fc= func_constants<double>;
    const vf_type exp_hi_inf= fc::exp_hi_inf();
    const vf_type exp_lo_zero= fc::exp_lo_zero();
    res = _T::sel_zero_or_val(d <= exp_lo_zero, res);
    res = _T::sel(d >= exp_hi_inf, _T::pinf(), res);
    // res = _T::sel(d == 0.0, 1.0, res);
    // res = _T::sel(d == 1.0, M_E, res);
    return res;
}

template <typename _T>
inline
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::
native_expm1(arg_t<vf_type> d)
{
    vf_type res = native_exp_k<true>(d);
    using fc= func_constants<double>;
    const vf_type expm1_hi_inf= fc::expm1_hi_inf();
    const vf_type expm1_lo_minus_one= fc::expm1_lo_minus_one();
    res = _T::sel(d <= expm1_lo_minus_one, -1.0, res);
    res = _T::sel(d >= expm1_hi_inf, _T::pinf(), res);
    // res = _T::sel(d == 0.0, 0.0, res);
    // res = _T::sel(d == 1.0, M_E-1.0, res);
    return res;
}

int main_native_exp(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=8;
    const int _N=8;
    bool rc=true;
    std::size_t cnt=update_cnt(0x8000);
    bool speed_only=false;
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    } else {
        std::string test_data_dir = dirname(argv[0]);
        std::string test_data_file=
            append_filename(test_data_dir, "../../test/data/exp.testdata");
        if (argc > 1) {
            test_data_dir = argv[1];
            test_data_file = append_filename(test_data_dir, "exp.testdata");
        }
        std::vector<func_arg_result<double> > v=
            read_double_file(test_data_file, false);
        rc &= check_func_1<double, 1, check_native_exp<double> >(v, ulp, 0, false);
        rc &= check_func_1<double, 2, check_native_exp<double> >(v, ulp, 0, false);
        rc &= check_func_1<double, 4, check_native_exp<double> >(v, ulp, 0, false);
        rc &= check_func_1<double, 8, check_native_exp<double> >(v, ulp, 0, false);
    }
    func_domain<double> d=std::make_pair(-750.0, 710.0);
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        double, _N, check_native_exp<double> >::v(st, d, speed_only,
                                           cmp_ulp<double>(ulp, us),
                                           cnt);
    // check the denormal result range
    d= std::make_pair(-750, -7.083964185322641924358322e+02);
    rc &= of_fp_func_up_to<
        double, _N, check_native_exp<double> >::v(st, d, speed_only,
                                           cmp_ulp<double>(ulp, us),
                                           cnt>>3);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}


int main_native_expm1(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=8;
    const int _N=8;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    } else {
        std::string test_data_dir = dirname(argv[0]);
        std::string test_data_file=
            append_filename(test_data_dir, "../../test/data/expm1.testdata");
        if (argc > 1) {
            test_data_dir = argv[1];
            test_data_file = append_filename(test_data_dir, "expm1.testdata");
        }
        std::vector<func_arg_result<double> > v=
            read_double_file(test_data_file, false);
        rc &= check_func_1<double, 1, check_native_expm1<double> >(v, ulp,
                                                            0, false);
        rc &= check_func_1<double, 2, check_native_expm1<double> >(v, ulp,
                                                            0, false);
        rc &= check_func_1<double, 4, check_native_expm1<double> >(v, ulp,
                                                            0, false);
        rc &= check_func_1<double, 8, check_native_expm1<double> >(v, ulp,
                                                            0, false);
    }
    // func_domain<double> d=std::make_pair(-0.25, 0.25);
    func_domain<double> d=std::make_pair(-380.0, 710.0);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        double, _N, check_native_expm1<double> >::v(st, d, speed_only,
                                             cmp_ulp<double>(ulp, us),
                                             cnt);
    d=std::make_pair(-0x1p-4, 0x1p-4);
    rc &= of_fp_func_up_to<
        double, _N, check_native_expm1<double> >::v(st, d, speed_only,
                                             cmp_ulp<double>(ulp, us),
                                             cnt>>2);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}


int main(int argc, char** argv)
{
    int r=0;
    r |= main_native_exp(argc, argv);
    r |= main_native_expm1(argc, argv);
    return r;
}
