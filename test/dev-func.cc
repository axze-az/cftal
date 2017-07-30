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
        struct check_half_exp {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                auto r=func_t::half_exp(a);
                return r;
            }
            static
            auto
            r(const _T& a) {
                // return call_mpfr::half_func(a, mpfr_exp);
                vec<_T, 4> aa(a);
                return extract<0>(exp(aa));
            }
            static
            _T
            s(const _T& a) {
                return std::exp(a);
            }
            static
            const char* fname() {
                return "half_exp";
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
__half_exp_k(arg_t<vf_type> xrh,
             arg_t<vf_type> kf,
             arg_t<vi_type> k)
{
   // [-0.3465735912322998046875, 0.3465735912322998046875] : | p - f | <= 2^-22.984375
    // coefficients for exp_f16 generated by sollya
    // x^0 : +0x8.00001p-3f
    const vf_type exp_f16_c0=+1.0000001192e+00f;
    // x^1 : +0xf.ffffcp-4f
    const vf_type exp_f16_c1=+9.9999976158e-01f;
    // x^2 : +0xf.ffe57p-5f
    const vf_type exp_f16_c2=+4.9998733401e-01f;
    // x^3 : +0xa.aac63p-6f
    const vf_type exp_f16_c3=+1.6667322814e-01f;
    // x^4 : +0xa.bbadap-8f
    const vf_type exp_f16_c4=+4.1926242411e-02f;
    // x^5 : +0x8.83bb8p-10f
    const vf_type exp_f16_c5=+8.3150193095e-03f;
    vf_type y= fast_poly(xrh,
                         exp_f16_c5,
                         exp_f16_c4,
                         exp_f16_c3,
                         exp_f16_c2,
                         exp_f16_c1,
                         exp_f16_c0);
    // vf_type ee=_T::insert_exp(k + _T::bias());
    // y *= ee;
    y=__scale_exp_k(y, kf, k);
    return y;
}

template <typename _T>
inline
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::half_exp_k(arg_t<vf_type> xc)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type kf = rint(vf_type(xc * ctbl::m_1_ln2.h()));
    vf_type xrh = xc - kf*ctbl::m_ln2.h();
    vi_type k= _T::cvt_f_to_i(kf);
    auto y= __half_exp_k(xrh, kf, k);
    return y;
}

template <typename _T>
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::
half_exp(arg_t<vf_type> d)
{
    vf_type res=half_exp_k(d);
    using fc= func_constants<float>;
    const vf_type exp_hi_inf= fc::exp_hi_inf();
    const vf_type exp_lo_zero= fc::exp_lo_zero();
    res = _T::sel(d <= exp_lo_zero, 0.0, res);
    res = _T::sel(d >= exp_hi_inf, _T::pinf(), res);
    return res;
}

template <typename _T>
inline
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::half_exp2_k(arg_t<vf_type> xc)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type kf = rint(xc);
    vf_type xrh = xc - kf;
    vi_type k= _T::cvt_f_to_i(kf);
    auto y= __half_exp_k(xrh*ctbl::m_ln2.h(), kf, k);
    return y;
}

template <typename _T>
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::
half_exp2(arg_t<vf_type> d)
{
    vf_type res=half_exp2_k(d);
    using fc= func_constants<float>;
    const vf_type exp_hi_inf= fc::exp2_hi_inf();
    const vf_type exp_lo_zero= fc::exp2_lo_zero();
    res = _T::sel(d <= exp_lo_zero, 0.0, res);
    res = _T::sel(d >= exp_hi_inf, _T::pinf(), res);
    return res;
}

template <typename _T>
inline
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::half_exp10_k(arg_t<vf_type> xc)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type kf = rint(vf_type(xc * ctbl::m_1_lg2.h()));
    vf_type xrh = xc - kf*ctbl::m_lg2.h();
    vi_type k= _T::cvt_f_to_i(kf);
    auto y= __half_exp_k(xrh*ctbl::m_ln10.h(), kf, k);
    return y;
}

template <typename _T>
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::
half_exp10(arg_t<vf_type> d)
{
    vf_type res=half_exp10_k(d);
    using fc= func_constants<float>;
    const vf_type exp_hi_inf= fc::exp_hi_inf();
    const vf_type exp_lo_zero= fc::exp_lo_zero();
    res = _T::sel(d <= exp_lo_zero, 0.0, res);
    res = _T::sel(d >= exp_hi_inf, _T::pinf(), res);
    return res;
}

template <typename _T>
inline
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::half_log_k(arg_t<vf_type> xc)
{
    // one could remove the denormal handling here
    using fc = func_constants<float>;
    vmf_type is_denom=xc <= fc::max_denormal();
    vf_type x=_T::sel(is_denom, xc*0x1p25f, xc);
    vi_type k=_T::sel(_T::vmf_to_vmi(is_denom), vi_type(-25), vi_type(0));
    vi_type hx = _T::as_int(x);
    /* reduce x into [sqrt(2)/2, sqrt(2)] */
    hx += 0x3f800000 - 0x3f3504f3;;
    k += (hx>>23) - _T::bias();
    hx = (hx&0x007fffff) + 0x3f3504f3;
    vf_type xr = _T::as_float(hx);
    vf_type kf = _T::cvt_i_to_f(k);

    // brute force:
    vf_type ym= xr-1.0f;
    vf_type yp= xr+1.0f;
    vf_type s= native_div(ym, yp);
    // vf_type s= ym/yp;
    // [3.4694469519536141888238489627838134765625e-18, 0.17157287895679473876953125] : | p - f | <= 2^-24.53125
    // coefficients for log_f16 generated by sollya
    // x^1 : +0x8.00001p-2f
    const vf_type log_f16_c1=+2.0000002384e+00f;
    // x^3 : +0xa.aa131p-4f
    const vf_type log_f16_c3=+6.6652208567e-01f;
    // x^5 : +0xd.37089p-5f
    const vf_type log_f16_c5=+4.1296795011e-01f;
    vf_type s2=s*s;
    vf_type y = horner(s2,
                       log_f16_c5,
                       log_f16_c3,
                       log_f16_c1)*s;
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vf_type log_x = kf * ctbl::m_ln2.h() + y;
    return log_x;
}

template <typename _T>
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::
half_log(arg_t<vf_type> d)
{
    vf_type x = half_log_k(d);
    const vf_type pinf(_T::pinf());
    const vf_type ninf(_T::ninf());
    x = _T::sel(isinf(d), pinf, x);
    // if (d < 0) x = NAN;
    x = _T::sel(d < vf_type(0.0), vf_type(_T::nan()), x);
    // if (d == 0) x = -INFINITY;
    x = _T::sel(d == vf_type(0.0), ninf, x);
    // NAN --> n_and_1
    x = _T::sel(isnan(d), d, x);
    return x;
}

template <typename _T>
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::
half_log2(arg_t<vf_type> d)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type x = half_log_k(d)*ctbl::m_1_ln2.h();
    const vf_type pinf(_T::pinf());
    const vf_type ninf(_T::ninf());
    x = _T::sel(isinf(d), pinf, x);
    // if (d < 0) x = NAN;
    x = _T::sel(d < vf_type(0.0), vf_type(_T::nan()), x);
    // if (d == 0) x = -INFINITY;
    x = _T::sel(d == vf_type(0.0), ninf, x);
    // NAN --> n_and_1
    x = _T::sel(isnan(d), d, x);
    return x;
}

template <typename _T>
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::
half_log10(arg_t<vf_type> d)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type x=half_log_k(d) * ctbl::m_1_ln10.h();
    const vf_type pinf(_T::pinf());
    const vf_type ninf(_T::ninf());
    x = _T::sel(isinf(d), pinf, x);
    // if (d < 0) x = NAN;
    x = _T::sel(d < vf_type(0.0), vf_type(_T::nan()), x);
    // if (d == 0) x = -INFINITY;
    x = _T::sel(d == vf_type(0.0), ninf, x);
    // NAN --> n_and_1
    x = _T::sel(isnan(d), d, x);
    return x;
}

int main_exp(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=4096;
    const int _N=32;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x800);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    using ftype = float;
    func_domain<ftype> d=std::make_pair(-std::numeric_limits<ftype>::max(),
                                         std::numeric_limits<ftype>::max());
    d=std::make_pair(-16.5f, 10.4f);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_half_exp<ftype> >::v(st, d, speed_only,
                                              cmp_ulp<ftype>(ulp, us),
                                              cnt, false);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, false) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_exp2(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=4096;
    const int _N=32;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x800);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    using ftype = float;
    func_domain<ftype> d=std::make_pair(-std::numeric_limits<ftype>::max(),
                                         std::numeric_limits<ftype>::max());
    d=std::make_pair(-24.5f, 15.1f);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_half_exp2<ftype> >::v(st, d, speed_only,
                                               cmp_ulp<ftype>(ulp, us),
                                               cnt, false);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, false) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_exp10(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=4096;
    const int _N=32;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x800);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    using ftype = float;
    func_domain<ftype> d=std::make_pair(-std::numeric_limits<ftype>::max(),
                                         std::numeric_limits<ftype>::max());
    d=std::make_pair(-7.3f, 4.6f);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_half_exp10<ftype> >::v(st, d, speed_only,
                                                cmp_ulp<ftype>(ulp, us),
                                                cnt, false);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, false) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_log(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=4096;
    const int _N=32;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x800);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    using ftype = float;

    // func_domain<double> d=std::make_pair(0.0,
    //                                     std::numeric_limits< double >::max());
    func_domain<ftype> d=std::make_pair(-std::numeric_limits<ftype>::max(),
                                         std::numeric_limits<ftype>::max());
    d = std::make_pair(-0x1p-25f, 0x1.1p16f);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_half_log10<ftype> >::v(st, d, speed_only,
                                              cmp_ulp<ftype>(ulp, us),
                                              cnt, false);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, false) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_log2(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=4096;
    const int _N=32;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x800);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    using ftype = float;

    // func_domain<double> d=std::make_pair(0.0,
    //                                     std::numeric_limits< double >::max());
    func_domain<ftype> d=std::make_pair(-std::numeric_limits<ftype>::max(),
                                         std::numeric_limits<ftype>::max());
    d = std::make_pair(-0x1p-25f, 0x1.1p16f);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_half_log2<ftype> >::v(st, d, speed_only,
                                              cmp_ulp<ftype>(ulp, us),
                                              cnt, false);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, false) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_log10(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=4096;
    const int _N=32;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x800);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    using ftype = float;

    // func_domain<double> d=std::make_pair(0.0,
    //                                     std::numeric_limits< double >::max());
    func_domain<ftype> d=std::make_pair(-std::numeric_limits<ftype>::max(),
                                         std::numeric_limits<ftype>::max());
    d = std::make_pair(-0x1p-25f, 0x1.1p16f);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_half_log10<ftype> >::v(st, d, speed_only,
                                                cmp_ulp<ftype>(ulp, us),
                                                cnt, false);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, false) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main(int argc, char** argv)
{
    int r=0;
    r |= main_log(argc, argv);
    r |= main_log2(argc, argv);
    r |= main_log10(argc, argv);
    r |= main_exp(argc, argv);
    r |= main_exp2(argc, argv);
    r |= main_exp10(argc, argv);
    return r;
}
