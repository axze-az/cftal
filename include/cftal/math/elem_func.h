//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_MATH_ELEM_FUNC_H__)
#define __CFTAL_MATH_ELEM_FUNC_H__ 1

#include <cftal/config.h>
#include <cftal/arg.h>
#include <cftal/d_real.h>
#include <cftal/t_real.h>
#include <cftal/std_types.h>
#include <cftal/divisor.h>
#include <cftal/constants.h>
#include <cftal/mem.h>
#include <cftal/math/func_constants.h>
#include <type_traits>
#include <limits>
#include <utility>
#include <stdexcept>
#include </home/axel/iaca-lin64/include/iacaMarks.h>

namespace cftal {

    namespace math {

        namespace impl {

            // returns (y0+y1) = x - N * pi/2
            // the integer results contains
            // only the lower bits of N
            int32_t
            __attribute__((__visibility__("internal")))
            __ieee754_rem_pio2(float x, float *y);


            // returns (y0+y1) = x - N * pi/2
            // the integer results contains
            // only the lower bits of N
            int32_t
            __attribute__((__visibility__("internal")))
            __ieee754_rem_pio2(double x, double *y);
            int
            __attribute__((__visibility__("internal")))
            __kernel_rem_pio2(double *x, double *y, int e0,
                              int nx, int prec,
                              const int32_t *ipio2);

        }

        // helper for func_core and func_common.
        // contains conversion functions between _FLOAT_T
        // _INT_T, extraction and insertion of integer
        // exponents, bias ...
        template <typename _FLOAT_T, typename _INT_T>
        struct func_traits;

        // core implementation of elementary and base
        // functions exports exp_k, exp2_k ...
        // must be specialized for different _FLOAT_T
        template <typename _FLOAT_T, typename _TRAITS_T>
        struct elem_func_core {
            using vf_type = typename _TRAITS_T::vf_type;
            using vi_type = typename _TRAITS_T::vi_type;
            using vmf_type = typename _TRAITS_T::vmf_type;
            using vmi_type = typename _TRAITS_T::vmi_type;
            using dvf_type = d_real<vf_type>;
        };

        // common implementation of base and elementary functions
        // special argument handling like inf, nan, overflow, underflow
        // is done here
        template <typename _FLOAT_T, typename _TRAITS_T>
        struct elem_func : public elem_func_core< _FLOAT_T, _TRAITS_T> {
            using base_type = elem_func_core<_FLOAT_T, _TRAITS_T>;
            using my_type = elem_func<_FLOAT_T, _TRAITS_T>;
            using vf_type = typename base_type::vf_type;
            using vi_type = typename base_type::vi_type;
            using vmf_type = typename base_type::vmf_type;
            using vmi_type = typename base_type::vmi_type;
            using dvf_type = typename base_type::dvf_type;
            using d_ops = typename base_type::d_ops;

            using base_type::frexp;
            using base_type::ldexp;
            using base_type::ilogb;
            using base_type::ilogbp1;

            static
            vf_type
            rsqrt(arg_t<vf_type> vf);

            // calls cbrt_k
            static
            vf_type
            cbrt(arg_t<vf_type> vf);

            static
            vf_type
            root12(arg_t<vf_type> vf);

            static
            vf_type
            exp(arg_t<vf_type> vf);

            static
            vf_type
            exp2(arg_t<vf_type> vf);

            static
            vf_type
            exp10(arg_t<vf_type> vf);

            static
            vf_type
            expm1(arg_t<vf_type> vf);

            static
            vf_type
            exp2m1(arg_t<vf_type> vf);

            static
            vf_type
            exp10m1(arg_t<vf_type> vf);

            static
            vf_type
            sinh(arg_t<vf_type> vf);

            static
            vf_type
            cosh(arg_t<vf_type> vf);

            static
            vf_type
            tanh(arg_t<vf_type> vf);

            static
            vf_type
            log(arg_t<vf_type> vf);

            static
            vf_type
            log1p(arg_t<vf_type> vf);

            static
            vf_type
            log10(arg_t<vf_type> vf);

            static
            vf_type
            log2(arg_t<vf_type> vf);

            static
            vf_type
            pow(arg_t<vf_type> b, arg_t<vf_type> e);

            // done by squaring
            static
            vf_type
            pow(arg_t<vf_type> b, arg_t<vi_type> e);

            static
            void
            sincos(arg_t<vf_type> vf, vf_type* psin, vf_type* pcos);

            static
            vf_type
            sin(arg_t<vf_type> vf);

            static
            vf_type
            cos(arg_t<vf_type> vf);

            static
            vf_type
            tan(arg_t<vf_type> vf);

            static
            vf_type
            atan2(arg_t<vf_type> x, arg_t<vf_type> y);

            static
            vf_type
            atan(arg_t<vf_type> x);

            static
            vf_type
            asin(arg_t<vf_type> x);

            static
            vf_type
            acos(arg_t<vf_type> x);

            static
            vf_type
            asinh(arg_t<vf_type> x);

            static
            vf_type
            acosh(arg_t<vf_type> x);

            static
            vf_type
            atanh(arg_t<vf_type> x);

            // returns e^(-x*x);
            static
            vf_type
            exp_mx2(arg_t<vf_type> x);

            // returns e^(x*x);
            static
            vf_type
            exp_px2(arg_t<vf_type> x);

            // returns 2^(-x*x);
            static
            vf_type
            exp2_mx2(arg_t<vf_type> x);

            // returns 2^(x*x);
            static
            vf_type
            exp2_px2(arg_t<vf_type> x);

            // returns 10^(-x*x);
            static
            vf_type
            exp10_mx2(arg_t<vf_type> x);

            // returns 10^(x*x);
            static
            vf_type
            exp10_px2(arg_t<vf_type> x);
        };

    }
}


template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
rsqrt(arg_t<vf_type> x)
{
    vf_type y= base_type::rsqrt_k(x);
    // y=_T::sel(x == _T::pinf(), vf_type(0), y);
    y=_T::sel_val_or_zero(x != _T::pinf(), y);
    y=_T::sel(x == 0, _T::pinf(), y);
    y=_T::sel(x < 0.0, _T::nan(), y);
    y=_T::sel(isnan(x), x, y);
    return y;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
cbrt(arg_t<vf_type> x)
{
    vf_type r=base_type::cbrt_k(x);
    vmf_type is_zero_or_inf_or_nan=
        (x == vf_type(0)) | isinf(x) | isnan(x);
    r=_T::sel(is_zero_or_inf_or_nan, x, r);
    return r;
}

template <typename _FLOAT_T, typename _T>
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
root12(arg_t<vf_type> x)
{
    vf_type y= base_type::root12_k(x);
    y=_T::sel(x == _T::pinf(), _T::pinf(), y);
    // y=_T::sel(x == 0, 0.0, y);
    y=_T::sel_val_or_zero(x != 0, y);
    y=_T::sel(x < 0.0, _T::nan(), y);
    y=_T::sel(isnan(x), x, y);
    return y;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
exp(arg_t<vf_type> d)
{
    vf_type res=base_type:: template exp_k<false>(d);
    using fc= func_constants<_FLOAT_T>;
    const vf_type exp_hi_inf= fc::exp_hi_inf();
    const vf_type exp_lo_zero= fc::exp_lo_zero();
    res = _T::sel_zero_or_val(d <= exp_lo_zero, res);
    res = _T::sel(d >= exp_hi_inf, _T::pinf(), res);
    // res = _T::sel(d == 0.0, 1.0, res);
    // res = _T::sel(d == 1.0, M_E, res);
    return res;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
exp2(arg_t<vf_type> d)
{
    IACA_START
    vf_type res=base_type:: template exp2_k<false>(d);
    using fc= func_constants<_FLOAT_T>;
    const vf_type exp2_hi_inf= fc::exp2_hi_inf();
    const vf_type exp2_lo_zero= fc::exp2_lo_zero();
    res = _T::sel_zero_or_val(d <= exp2_lo_zero, res);
    res = _T::sel(d >= exp2_hi_inf, _T::pinf(), res);
    // res = _T::sel(d == 0.0, 1.0, res);
    // res = _T::sel(d == 1.0, 2.0, res);
    IACA_END
    return res;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
exp10(arg_t<vf_type> d)
{
    vf_type res=base_type:: template exp10_k<false>(d);
    using fc= func_constants<_FLOAT_T>;
    const vf_type exp10_hi_inf=fc::exp10_hi_inf();
    const vf_type exp10_lo_zero=fc::exp10_lo_zero();
    res = _T::sel_zero_or_val(d <= exp10_lo_zero, res);
    res = _T::sel(d >= exp10_hi_inf, _T::pinf(), res);
    // res = _T::sel(d == 0.0, 1.0, res);
    // res = _T::sel(d == 1.0, 10.0, res);
    return res;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
expm1(arg_t<vf_type> d)
{
    vf_type res = base_type:: template exp_k<true>(d);
    using fc= func_constants<_FLOAT_T>;
    const vf_type expm1_hi_inf= fc::expm1_hi_inf();
    const vf_type expm1_lo_minus_one= fc::expm1_lo_minus_one();
    res = _T::sel(d <= expm1_lo_minus_one, -1.0, res);
    res = _T::sel(d >= expm1_hi_inf, _T::pinf(), res);
    // res = _T::sel(d == 0.0, 0.0, res);
    // res = _T::sel(d == 1.0, M_E-1.0, res);
    return res;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
exp2m1(arg_t<vf_type> d)
{
    vf_type res = base_type:: template exp2_k<true>(d);
    using fc= func_constants<_FLOAT_T>;
    const vf_type exp2m1_hi_inf= fc::exp2m1_hi_inf();
    const vf_type exp2m1_lo_minus_one= fc::exp2m1_lo_minus_one();
    res = _T::sel(d <= exp2m1_lo_minus_one, -1.0, res);
    res = _T::sel(d >= exp2m1_hi_inf, _T::pinf(), res);
    // res = _T::sel(d == 0.0, 0.0, res);
    // res = _T::sel(d == 1.0, 1.0, res);
    return res;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
exp10m1(arg_t<vf_type> d)
{
    vf_type res = base_type:: template exp10_k<true>(d);
    using fc= func_constants<_FLOAT_T>;
    const vf_type exp10m1_hi_inf= fc::exp10m1_hi_inf();
    const vf_type exp10m1_lo_minus_one= fc::exp10m1_lo_minus_one();
    res = _T::sel(d <= exp10m1_lo_minus_one, -1.0, res);
    res = _T::sel(d >= exp10m1_hi_inf, _T::pinf(), res);
    // res = _T::sel(d == 0.0, 0.0, res);
    // res = _T::sel(d == 1.0, 9.0, res);
    return res;
}


template <typename _FLOAT_T, typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
sinh(arg_t<vf_type> x)
{
    using fc=func_constants<_FLOAT_T>;
    vf_type res=base_type::sinh_k(x);
    const vf_type sinh_hi_inf= fc::sinh_hi_inf();
    const vf_type sinh_lo_inf= fc::sinh_lo_inf();
    res = _T::sel(x >= sinh_hi_inf, _T::pinf(), res);
    res = _T::sel(x <= sinh_lo_inf, _T::ninf(), res);
    res = _T::sel_zero_or_val(x == 0.0, res);
    return res;
}

template <typename _FLOAT_T, typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
cosh(arg_t<vf_type> x)
{
    using fc=func_constants<_FLOAT_T>;
    const vf_type cosh_hi_inf= fc::cosh_hi_inf();
    vf_type res=base_type::cosh_k(x);
    res = _T::sel(abs(x) >= cosh_hi_inf, _T::pinf(), res);
    // res = _T::sel(x == 0.0, 1.0, res);
    return res;
}

template <typename _FLOAT_T, typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
tanh(arg_t<vf_type> x)
{
    // using fc=func_constants<_FLOAT_T>;
    // const vf_type cosh_hi_inf= fc::cosh_hi_inf;
    vf_type res=base_type::tanh_k(x);
    // res = _T::sel(abs(x) >= cosh_hi_inf, _T::pinf(), res);
    res = _T::sel(isnan(x), x, res);
    // res = _T::sel(isinf(x), copysign(1.0, x), res);
    return res;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
log(arg_t<vf_type> d)
{
    vf_type x = base_type::log_k(d);
    const vf_type pinf(_T::pinf());
    const vf_type ninf(_T::ninf());
    x = _T::sel(isinf(d), pinf, x);
    // if (d < 0) x = NAN;
    x = _T::sel(d < vf_type(0.0), vf_type(_T::nan()), x);
    // if (d == 0) x = -INFINITY;
    x = _T::sel(d == vf_type(0.0), ninf, x);
    // NAN --> n_and_1
    x = _T::sel(isnan(d), d, x);
    // using fc= func_constants<_FLOAT_T>;
    // const vf_type log_lo_fin= fc::log_lo_fin;
    // const vf_type log_lo_val= fc::log_lo_val;
    // x = _T::sel(d == log_lo_fin, log_lo_val, x);
    return x;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
log1p(arg_t<vf_type> d)
{
    vf_type x=base_type::log1p_k(d);
    // double log1p(double x)
    // {
    //    double u = 1.+x;
    //    if (u == 1.)
    //        return x;
    //    else
    //        return log(u)*x/(u-1.);
    // }
    const vf_type pinf(_T::pinf());
    const vf_type ninf(_T::ninf());
    x = _T::sel(isinf(d), pinf, x);
    // if (d < -1.0) x = NAN;
    x = _T::sel(d < vf_type(-1.0), vf_type(_T::nan()), x);
    // if (d == -1.0) x = -INFINITY;
    x = _T::sel(d == vf_type(-1.0), ninf, x);
    // NAN --> n_and_1
    x = _T::sel(isnan(d), d, x);
    return x;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
log10(arg_t<vf_type> d)
{
    vf_type x=base_type::log10_k(d);
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

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
log2(arg_t<vf_type> d)
{
    vf_type x=base_type::log2_k(d);
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

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
pow(arg_t<vf_type> x, arg_t<vf_type> y)
{
#if 0
    return x+y;
#else
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
    res = _T::sel_zero_or_val(res_nan & abs_x_lt_1 & y_gt_1, res);
    res = _T::sel_zero_or_val(res_nan & (~abs_x_lt_1) & (~y_gt_1), res);

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
    t = _T::sel_zero_or_val(efx < 0.0, t);
    res = _T::sel(y_inf, t, res);

    vmf_type x_zero = x == 0.0;
    vmf_type x_inf_or_zero= isinf(x) | x_zero;
    t= _T::sel(x_zero, -y, y);
    t= _T::sel_zero_or_val(t < 0.0, _T::pinf());
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
#endif
}

template <typename _FLOAT_T, typename _TRAITS_T>
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
pow(arg_t<vf_type> b, arg_t<vi_type> e)
{
    using _T = _TRAITS_T;
    vmi_type e_lt_z = e < vi_type(0);
    vmf_type f_e_lt_z = _T::vmi_to_vmf(e_lt_z);
    vi_type n= _T::sel(e_lt_z, -e, e);
    vf_type x= _T::sel(f_e_lt_z, vf_type(1.0)/b, b);
    vf_type r= vf_type(1.0);

    vmi_type n_ne_0 = n != vi_type(0);
    while (any_of(n_ne_0)) {
        vmi_type n_and_1 = (n & vi_type(1)) != vi_type(0);
        vmf_type f_n_and_1 = _T::vmi_to_vmf(n_and_1);
        r = _T::sel(f_n_and_1, r*x, r);
        n >>= 1;
        n_ne_0 = n != vi_type(0);
        vmf_type f_n_ne_0 = _T::vmi_to_vmf(n_ne_0);
        // clear vector entries not required any more
        x = _T::sel_val_or_zero(f_n_ne_0, x*x);
    }
    return r;
}


template <typename _FLOAT_T, typename _TRAITS_T>
void
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
sincos(arg_t<vf_type> d, vf_type* psin, vf_type* pcos)
{
    if ((psin!=nullptr) || (pcos!=nullptr)) {
        base_type::sin_cos_k(d, psin, pcos);
    }
}

template <typename _FLOAT_T, typename _TRAITS_T>
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
sin(arg_t<vf_type> d)
{
    vf_type s;
    base_type::sin_cos_k(d, &s, nullptr);
    return s;
}

template <typename _FLOAT_T, typename _TRAITS_T>
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
cos(arg_t<vf_type> d)
{
    vf_type c;
    base_type::sin_cos_k(d, nullptr, &c);
    return c;
}

template <typename _FLOAT_T, typename _TRAITS_T>
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
tan(arg_t<vf_type> d)
{
    vf_type t=base_type::tan_k(d);
    t = _TRAITS_T::sel(isinf(d) | isnan(d),
                       copysign(vf_type(_TRAITS_T::nan()), d),
                       t);
    return t;
}

template <typename _FLOAT_T, typename _TRAITS_T>
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
atan2(arg_t<vf_type> y, arg_t<vf_type> x)
{
    vf_type r=base_type::atan2_k(y, x);

    using _T = _TRAITS_T;

    vmf_type y_zero = y==vf_type(0);
    vmf_type x_inf = isinf(x);
    vmf_type y_inf = isinf(y);
    vmf_type x_zero = x==vf_type(0);
    vmf_type x_nan = isnan(x);
    vmf_type y_nan = isnan(y);

    vmf_type special = y_zero | x_inf | y_inf | x_zero | x_nan | y_nan;

    if (any_of(special)) {
        vf_type y_sgn = copysign(vf_type(1), y);
        vmf_type y_p= y_sgn == vf_type(1.0);
        vmf_type y_n= y_sgn == vf_type(-1.0);
        vmf_type y_p_zero = y_p & y_zero;
        vmf_type y_n_zero = y_n & y_zero;
        vmf_type y_gt_z = y>vf_type(0);
        vmf_type y_lt_z = y<vf_type(0);
        vmf_type y_p_inf = y_inf & y_p;
        vmf_type y_n_inf = y_inf & y_n;

        vf_type x_sgn = copysign(vf_type(1), x);
        vmf_type x_p= x_sgn == vf_type(1.0);
        vmf_type x_n= x_sgn == vf_type(-1.0);
        vmf_type x_p_zero = x_p & x_zero;
        vmf_type x_n_zero = x_n & x_zero;
        vmf_type x_p_inf = x_p & x_inf;
        vmf_type x_n_inf = x_n & x_inf;
        vmf_type x_gt_z = x>vf_type(0);
        vmf_type x_lt_z = x<vf_type(0);
        vmf_type x_ge_p_z = x_p_zero | x_gt_z;
        vmf_type x_le_n_z = x_n_zero | x_lt_z;

        //  atan2(+0, x>=0) = +0
        r = _T::sel(y_p_zero & x_ge_p_z, y, r);
        //  atan2(-0, x>=0) = -0
        r = _T::sel(y_n_zero & x_ge_p_z, y, r);
        //  atan2(+0, x<=-0) = +Pi
        r = _T::sel(y_p_zero & x_le_n_z, +M_PI, r);
        //  atan2(-0, x<=-0) = -Pi
        r = _T::sel(y_n_zero & x_le_n_z, -M_PI, r);
        //  atan2(y>0, 0) = +Pi/2
        r = _T::sel(y_gt_z & x_zero, +M_PI/2, r);
        //  atan2(y<0, 0) = -Pi/2
        r = _T::sel(y_lt_z & x_zero, -M_PI/2, r);
        //  atan2(y, +Inf) = 0
        r = _T::sel_zero_or_val(x_p_inf, r);
        //  atan2(y>0, -Inf) = +Pi
        r = _T::sel(y_gt_z & x_n_inf, M_PI, r);
        //  atan2(y<0, -Inf) = -Pi
        r = _T::sel(y_lt_z & x_n_inf, -M_PI, r);
        //  atan2(+Inf, x) = +Pi/2
        r = _T::sel(y_p_inf, M_PI/2, r);
        //  atan2(-Inf, x) = -Pi/2
        r= _T::sel(y_n_inf, -M_PI/2, r);
        //  atan2(+Inf, +Inf) = +Pi/4
        r = _T::sel(y_p_inf & x_p_inf, +M_PI/4, r);
        //  atan2(-Inf, +Inf) = -Pi/4
        r = _T::sel(y_n_inf & x_p_inf, -M_PI/4, r);
        //  atan2(+Inf, -Inf) = 3Pi/4
        r = _T::sel(y_p_inf & x_n_inf, (3*M_PI)/4, r);
        //  atan2(-Inf, -Inf) = -3Pi/4
        r = _T::sel(y_n_inf & x_n_inf, -(3*M_PI)/4, r);
        //  atan2(y, NaN) = NaN
        //  atan2(NaN, x) = NaN
        r = _T::sel(x_nan | y_nan, _T::nan(), r);
    }
    return r;
}

template <typename _FLOAT_T, typename _TRAITS_T>
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
atan(arg_t<vf_type> x)
{
    vf_type r= base_type::atan_k(x);
    // r=copysign(r, x);
    r=_TRAITS_T::sel(x==vf_type(0), x, r);
    r=_TRAITS_T::sel(isinf(x), copysign(vf_type(M_PI/2), x) , r);
    r=_TRAITS_T::sel(isnan(x), x, r);
    return r;
}

template <typename _FLOAT_T, typename _TRAITS_T>
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
asin(arg_t<vf_type> x)
{
    // vf_type xt= (vf_type(1) - x)*(vf_type(1) + x);
    // vf_type sqrt_xt= sqrt(xt);
    // vf_type asin_x= x/(1+sqrt_xt);
    // vf_type r=2.0*base_type::atan_k(asin_x);
    vf_type r=base_type::asin_k(x);
    r = _TRAITS_T::sel(x == vf_type(-1), -M_PI/2, r);
    r = _TRAITS_T::sel(x == vf_type(1), M_PI/2, r);
    r = _TRAITS_T::sel(x < vf_type(-1), -_TRAITS_T::nan(), r);
    r = _TRAITS_T::sel(x > vf_type(1), _TRAITS_T::nan(), r);
    r = _TRAITS_T::sel(isnan(x), x, r);
    return r;
}

template <typename _FLOAT_T, typename _TRAITS_T>
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
acos(arg_t<vf_type> x)
{
    vf_type r=base_type::acos_k(x);
    r = _TRAITS_T::sel(x == vf_type(-1), M_PI, r);
    r = _TRAITS_T::sel_zero_or_val(x == vf_type(1), r);
    r = _TRAITS_T::sel(x == vf_type(0), M_PI/2, r);
    r = _TRAITS_T::sel(x < vf_type(-1), -_TRAITS_T::nan(), r);
    r = _TRAITS_T::sel(x > vf_type(1), _TRAITS_T::nan(), r);
    r = _TRAITS_T::sel(isnan(x), x, r);
    return r;
}

template <typename _FLOAT_T, typename _TRAITS_T>
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
asinh(arg_t<vf_type> x)
{
    vf_type r=base_type::asinh_k(x);
    r = _TRAITS_T::sel(isinf(x), x, r);
    r = _TRAITS_T::sel(isnan(x), x, r);
    return r;
}

template <typename _FLOAT_T, typename _TRAITS_T>
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
acosh(arg_t<vf_type> x)
{
    vf_type r=base_type::acosh_k(x);
    r = _TRAITS_T::sel(x < 1.0, _TRAITS_T::nan(), r);
    r = _TRAITS_T::sel(x== _TRAITS_T::pinf(), x, r);
    r = _TRAITS_T::sel(isnan(x), x, r);
    return r;
}

template <typename _FLOAT_T, typename _TRAITS_T>
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
atanh(arg_t<vf_type> x)
{
    vf_type r=base_type::atanh_k(x);
    r = _TRAITS_T::sel(x == -1.0, _TRAITS_T::ninf(), r);
    r = _TRAITS_T::sel(x < -1.0, -_TRAITS_T::nan(), r);
    r = _TRAITS_T::sel(x == 1.0, _TRAITS_T::pinf(), r);
    r = _TRAITS_T::sel(x >  1.0, _TRAITS_T::nan(), r);
    r = _TRAITS_T::sel(isnan(x), x, r);
    return r;
}

template <typename _FLOAT_T, typename _TRAITS_T>
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
exp_mx2(arg_t<vf_type> x)
{
    return base_type::exp_mx2_k(x);
}

template <typename _FLOAT_T, typename _TRAITS_T>
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
exp_px2(arg_t<vf_type> x)
{
    return base_type::exp_px2_k(x);
}

template <typename _FLOAT_T, typename _TRAITS_T>
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
exp2_mx2(arg_t<vf_type> x)
{
    return base_type::exp2_mx2_k(x);
}

template <typename _FLOAT_T, typename _TRAITS_T>
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
exp2_px2(arg_t<vf_type> x)
{
    return base_type::exp2_px2_k(x);
}

template <typename _FLOAT_T, typename _TRAITS_T>
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
exp10_mx2(arg_t<vf_type> x)
{
    return base_type::exp10_mx2_k(x);
}

template <typename _FLOAT_T, typename _TRAITS_T>
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
exp10_px2(arg_t<vf_type> x)
{
    return base_type::exp10_px2_k(x);
}


// Local Variables:
// mode: c++
// end:
#endif
