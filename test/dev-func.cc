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
    floatn exp(floatn x);
    floatn exp2(floatn x);
    floatn exp10(floatn x);
    floatn log(floatn x);
    floatn log2(floatn x);
    floatn log10(floatn x);
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
                return func_t::half_exp(a);
            }
            static
            auto
            r(const _T& a) {
#if 0
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_exp, &i);
                return std::make_tuple(v, i.first, i.second);
#else
                return call_mpfr::func(a, mpfr_exp);
#endif
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
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_exp2, &i);
                return std::make_tuple(v, i.first, i.second);
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
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_ext::exp10, &i);
                return std::make_tuple(v, i.first, i.second);
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
__half_exp_k(arg_t<vf_type> xrh,
             arg_t<vi_type> k)
{
    // [-0.3465735912322998046875, 0.3465735912322998046875] : | p - f | <= 2^-18.0546875
    // coefficients for exp generated by sollya
    // x^0 : +0xf.ffff4p-4f
    const vf_type exp_f16_c0=+9.9999928474e-01f;
    // x^1 : +0xf.ffd9ap-4f
    const vf_type exp_f16_c1=+9.9996340275e-01f;
    // x^2 : +0x8.002cep-4f
    const vf_type exp_f16_c2=+5.0004279613e-01f;
    // x^3 : +0xa.bf05cp-6f
    const vf_type exp_f16_c3=+1.6790908575e-01f;
    // x^4 : +0xa.9d60bp-8f
    const vf_type exp_f16_c4=+4.1463892907e-02f;
    vf_type xx= xrh*xrh;
    vf_type y1= horner(xx,
                       exp_f16_c4,
                       exp_f16_c2);
    vf_type y2= horner(xx,
                       exp_f16_c3,
                       exp_f16_c1);
    vf_type y= horner(xrh, y1, y2, exp_f16_c0);
    vf_type ee=_T::insert_exp(k + _T::bias());
    y *= ee;
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
    auto y= __half_exp_k(xrh,k);
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
    auto y= __half_exp_k(xrh*ctbl::m_ln2.h(), k);
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
    auto y= __half_exp_k(xrh*ctbl::m_ln10.h(), k);
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

int main(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=8192;
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
    // d=std::make_pair(-104.0f, 89.0f);
    // EXP:
    d=std::make_pair(-16.75f, 12.0f);
    // EXP2:
    // d = std::make_pair(-24.5f, 15.5f);
    // EXP10:
    // d = std::make_pair(-7.3f, 4.9f);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_half_exp<ftype> >::v(st, d, speed_only,
                                                cmp_ulp<ftype>(ulp, us),
                                                cnt, false);
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


