//
// Copyright (C) 2010-2022 Axel Zeuner
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
//
#if !defined (__CFTAL_MATH_ELEM_FUNC_H__)
#define __CFTAL_MATH_ELEM_FUNC_H__ 1

#include <cftal/config.h>
#include <cftal/arg.h>
#include <cftal/mem.h>
#include <cftal/math/func_traits.h>
#include <cftal/math/func_constants.h>
#include <cftal/math/horner.h>
#include <cftal/type_traits.h>
#include <cftal/math/misc.h>

namespace cftal {

    namespace math {

        namespace impl {

            // argument reduction routine for large doubles
            int
            __kernel_rem_pio2(double xr[2], double x);

            // argument reduction routine for large doubles
            int
            __kernel_rem_pio2(double xr[2], double x, double xl);

            // argument reduction routine for large floats
            int
            __kernel_rem_pio2(float xr[2], float x);

            // declared here to allow the float routine above to
            // use the faster double version
            // same routine as from sun but uses internal tables
            __attribute__((__visibility__("internal")))
            int
            __kernel_rem_pio2(double* x,
                              double* y,
                              int e0,
                              int nx,
                              int prec);
        }

        // core implementation of elementary and base
        // functions exports exp_k, exp2_k ...
        // must be specialized for different _FLOAT_T
        template <typename _FLOAT_T, typename _TRAITS_T>
        struct elem_func_core {
        };

        // low precision core implementation of elementary
        // and base functions exports exp_k, exp2_k ...
        // may be specialized for different _FLOAT_T
        // precision should be high enough to return faithfully
        // rounded result for the next shorter float type
        template <typename _FLOAT_T, typename _TRAITS_T>
        struct elem_func_loprec_core {
        };

        // wrapper for core implementation of elementary and base
        // functions, may be specialized to switch elem func_core
        // implementations or only some functions
        template <typename _FLOAT_T, typename _TRAITS_T>
        struct elem_func_wrapper :
            public elem_func_core<_FLOAT_T, _TRAITS_T> {
        };

        // common implementation of base and elementary functions
        // special argument handling like inf, nan, overflow, underflow
        // is done here
        template <typename _FLOAT_T, typename _TRAITS_T>
        struct elem_func : public elem_func_wrapper< _FLOAT_T, _TRAITS_T> {
            using base_type = elem_func_wrapper<_FLOAT_T, _TRAITS_T>;
            using vf_type = typename base_type::vf_type;
            using vi_type = typename base_type::vi_type;
            using vmf_type = typename base_type::vmf_type;
            using vmi_type = typename base_type::vmi_type;
            using vdf_type = typename base_type::vdf_type;
            using d_ops = typename base_type::d_ops;

            using base_type::frexp;
            using base_type::ldexp;
            using base_type::ilogb;
            using base_type::ilogbp1;

            static
            vf_type
            nextafter(arg_t<vf_type> xc, arg_t<vf_type> yc);

            // reciprocal square root with full error handling
            static
            vf_type
            rsqrt(arg_t<vf_type> vf);

            // calls cbrt_k (cubic root) and performs error handling
            static
            vf_type
            cbrt(arg_t<vf_type> vf);

            // call rcbrt_k (reciprocal cubic root) and performs
            // error handling
            static
            vf_type
            rcbrt(arg_t<vf_type> vf);

            // call roo12_k (12. root) and performs error handling
            static
            vf_type
            root12(arg_t<vf_type> vf);

            // call hypot_k and performs error handling
            static
            vf_type
            hypot(arg_t<vf_type> xc, arg_t<vf_type> yc);

            // exponential function with error handling
            static
            vf_type
            exp(arg_t<vf_type> vf);

            // exp2 (2^x) function with error handling
            static
            vf_type
            exp2(arg_t<vf_type> vf);

            // exp10 (10^x) function with error handling
            static
            vf_type
            exp10(arg_t<vf_type> vf);

            // exponential function minus 1 with error handling
            static
            vf_type
            expm1(arg_t<vf_type> vf);

            // 2^x-1 function with error handling
            static
            vf_type
            exp2m1(arg_t<vf_type> vf);

            // 10^x-1 function with error handling
            static
            vf_type
            exp10m1(arg_t<vf_type> vf);

            // sinus hyperbolicus with error handling
            static
            vf_type
            sinh(arg_t<vf_type> vf);

            // cosinus hyperbolicus with error handling
            static
            vf_type
            cosh(arg_t<vf_type> vf);

            // tangens hyperbolicus with error handling
            static
            vf_type
            tanh(arg_t<vf_type> vf);

            // logarithmus function with error handling
            static
            vf_type
            log(arg_t<vf_type> vf);

            // logarithmus of 1+x function with error handling
            static
            vf_type
            log1p(arg_t<vf_type> vf);

            // base 10 logarithmus function with error handling
            static
            vf_type
            log10(arg_t<vf_type> vf);

            // base 2 logarithmus function with error handling
            static
            vf_type
            log2(arg_t<vf_type> vf);

            // power function with error handling
            static
            vf_type
            pow(arg_t<vf_type> b, arg_t<vf_type> e);

            // power function with error handling
            static
            vf_type
            pow(arg_t<vf_type> xc, arg_t <vi_type> e);

            // n-th root function with error handling
            static
            vf_type
            rootn(arg_t<vf_type> xc, arg_t <vi_type> yc);

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
            void
            sinpicospi(arg_t<vf_type> vf, vf_type* psin, vf_type* pcos);

            static
            vf_type
            sinpi(arg_t<vf_type> vf);

            static
            vf_type
            cospi(arg_t<vf_type> vf);

            static
            vf_type
            tanpi(arg_t<vf_type> vf);

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

            // returns 1/(1+exp(-x))
            static
            vf_type
            sig(arg_t<vf_type> x);
        };

    }
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
nextafter(arg_t<vf_type> xc, arg_t<vf_type> yc)
{
    vf_type r= base_type::nextafter_k(xc, yc);
    r = _T::sel(isnan(xc) | isnan(yc), _T::nan(), r);
    return r;
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
    y=_T::sel(x == _FLOAT_T(0.0), _T::pinf(), y);
    y=_T::sel((x < _FLOAT_T(0.0)) | isnan(x), _T::nan(), y);
    return y;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
cbrt(arg_t<vf_type> x)
{
    // llvm-mca-7 -mtriple=x86_64-unknown-unknown -mcpu=skylake
    // -iterations=1  --all-stats --all-views -timeline-max-cycles=1000
    // xy.s
    // __asm volatile("# LLVM-MCA-BEGIN\n\t");
    vf_type r=base_type::cbrt_k(x);
    vmf_type is_zero_or_inf_or_nan=
        (x == _FLOAT_T(0.0)) | isinf(x) | isnan(x);
    r=_T::sel(is_zero_or_inf_or_nan, x, r);
    // __asm volatile("# LLVM-MCA-END\n\t");
    return r;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
rcbrt(arg_t<vf_type> x)
{
    // llvm-mca-7 -mtriple=x86_64-unknown-unknown -mcpu=skylake
    // -iterations=1  --all-stats --all-views -timeline-max-cycles=1000
    // xy.s
    // __asm volatile("# LLVM-MCA-BEGIN\n\t");
    vf_type y=base_type::rcbrt_k(x);
    y=_T::sel_val_or_zero(x != _T::pinf(), y);
    y=_T::sel(x == _T::ninf(), -0.0, y);
    y=_T::sel(x == _FLOAT_T(0.0), copysign(_T::pinf(), x), y);
    y=_T::sel(isnan(x), x, y);
    // __asm volatile("# LLVM-MCA-END\n\t");
    return y;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
root12(arg_t<vf_type> x)
{
    vf_type y= base_type::root12_k(x);
    y=_T::sel(x == _T::pinf(), _T::pinf(), y);
    // y=_T::sel(x == 0, 0.0, y);
    y=_T::sel_val_or_zero(x != _FLOAT_T(0), y);
    y=_T::sel((x < _FLOAT_T(0.0))|isnan(x), _T::nan(), y);
    return y;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
hypot(arg_t<vf_type> x, arg_t<vf_type> y)
{
    vf_type r= base_type::hypot_k(x, y);
    // NaN only if the other argument is not inf
    r = _T::sel(isnan(x)|isnan(y), _T::nan(), r);
    r = _T::sel(isinf(x)|isinf(y), _T::pinf(), r);
    return r;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
exp(arg_t<vf_type> x)
{
    __asm__ volatile("# LLVM-MCA-BEGIN\n\t");
#if 0
    auto f=[](_FLOAT_T d)->_FLOAT_T {
        return std::exp(d);
    };
    vf_type y= base_type::call_scalar_func(x, f);
#else
    vf_type y=base_type:: template exp_k<false>(x);
    using fc= func_constants<_FLOAT_T>;
    const _FLOAT_T exp_hi_inf= fc::exp_hi_inf();
    const _FLOAT_T exp_lo_zero= fc::exp_lo_zero();
    y = _T::sel_zero_or_val(x <= exp_lo_zero, y);
    y = _T::sel(x >= exp_hi_inf, _T::pinf(), y);
    // y = _T::sel(x == 0.0, 1.0, y);
    // y = _T::sel(x == 1.0, M_E, y);
#endif
    __asm__ volatile("# LLVM-MCA-END\n\t");
    return y;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
exp2(arg_t<vf_type> x)
{
    vf_type y=base_type:: template exp2_k<false>(x);
    using fc= func_constants<_FLOAT_T>;
    const _FLOAT_T exp2_hi_inf= fc::exp2_hi_inf();
    const _FLOAT_T exp2_lo_zero= fc::exp2_lo_zero();
    y = _T::sel_zero_or_val(x <= exp2_lo_zero, y);
    y = _T::sel(x >= exp2_hi_inf, _T::pinf(), y);
    // y = _T::sel(x == 0.0, 1.0, y);
    // y = _T::sel(x == 1.0, 2.0, y);
    return y;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
exp10(arg_t<vf_type> x)
{
    vf_type y=base_type:: template exp10_k<false>(x);
    using fc= func_constants<_FLOAT_T>;
    const _FLOAT_T exp10_hi_inf=fc::exp10_hi_inf();
    const _FLOAT_T exp10_lo_zero=fc::exp10_lo_zero();
    y = _T::sel_zero_or_val(x <= exp10_lo_zero, y);
    y = _T::sel(x >= exp10_hi_inf, _T::pinf(), y);
    // y = _T::sel(d == 0.0, 1.0, y);
    // y = _T::sel(d == 1.0, 10.0, y);
    return y;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
expm1(arg_t<vf_type> x)
{
    vf_type y = base_type:: template exp_k<true>(x);
    using fc= func_constants<_FLOAT_T>;
    const _FLOAT_T expm1_hi_inf= fc::expm1_hi_inf();
    const _FLOAT_T expm1_lo_minus_one= fc::expm1_lo_minus_one();
    y = _T::sel(x <= expm1_lo_minus_one, _FLOAT_T(-1.0), y);
    y = _T::sel(x >= expm1_hi_inf, _T::pinf(), y);
    return y;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
exp2m1(arg_t<vf_type> x)
{
    vf_type y = base_type:: template exp2_k<true>(x);
    using fc= func_constants<_FLOAT_T>;
    const _FLOAT_T exp2m1_hi_inf= fc::exp2m1_hi_inf();
    const _FLOAT_T exp2m1_lo_minus_one= fc::exp2m1_lo_minus_one();
    y = _T::sel(x <= exp2m1_lo_minus_one, _FLOAT_T(-1.0), y);
    y = _T::sel(x >= exp2m1_hi_inf, _T::pinf(), y);
    return y;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
exp10m1(arg_t<vf_type> x)
{
    vf_type y = base_type:: template exp10_k<true>(x);
    using fc= func_constants<_FLOAT_T>;
    const _FLOAT_T exp10m1_hi_inf= fc::exp10m1_hi_inf();
    const _FLOAT_T exp10m1_lo_minus_one= fc::exp10m1_lo_minus_one();
    y = _T::sel(x <= exp10m1_lo_minus_one, _FLOAT_T(-1.0), y);
    y = _T::sel(x >= exp10m1_hi_inf, _T::pinf(), y);
    return y;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
sinh(arg_t<vf_type> x)
{
    using fc=func_constants<_FLOAT_T>;
    vf_type y=base_type::sinh_k(x);
    const _FLOAT_T sinh_hi_inf= fc::sinh_hi_inf();
    const _FLOAT_T sinh_lo_inf= fc::sinh_lo_inf();
    y = _T::sel(x >= sinh_hi_inf, _T::pinf(), y);
    y = _T::sel(x <= sinh_lo_inf, _T::ninf(), y);
    // y = _T::sel(x == 0.0, x, y);
    return y;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
cosh(arg_t<vf_type> x)
{
    using fc=func_constants<_FLOAT_T>;
    const _FLOAT_T cosh_hi_inf= fc::cosh_hi_inf();
    vf_type res=base_type::cosh_k(x);
    res = _T::sel(abs(x) >= cosh_hi_inf, _T::pinf(), res);
    // res = _T::sel(x == 0.0, 1.0, res);
    return res;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
tanh(arg_t<vf_type> x)
{
    vf_type res=base_type::tanh_k(x);
    res = _T::sel(isnan(x), x, res);
    return res;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
log(arg_t<vf_type> d)
{
#if 0
    auto f=[](_FLOAT_T xx)->_FLOAT_T {
        return std::log(xx);
    };
    vf_type x= base_type::call_scalar_func(d, f);
#else
    vf_type x = base_type::log_k(d);
    const _FLOAT_T pinf=_T::pinf();
    const _FLOAT_T ninf=_T::ninf();
    // x = _T::sel(isinf(d), pinf, x);
    x = _T::sel(d == pinf, pinf, x);
    // if ((d < 0)|isnan(d)) x = NAN;
    x = _T::sel((d < _FLOAT_T(0.0))|isnan(d), _T::nan(), x);
    // if (d == 0) x = -INFINITY;
    x = _T::sel(d == _FLOAT_T(0.0), ninf, x);
#endif
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
    const _FLOAT_T pinf=_T::pinf();
    const _FLOAT_T ninf=_T::ninf();
    x = _T::sel(d==pinf, pinf, x);
    // if ((d < -1.0)|isnan(d)) x = NAN;
    x = _T::sel((d < _FLOAT_T(-1.0))|isnan(d), _T::nan(), x);
    // if (d == -1.0) x = -INFINITY;
    x = _T::sel(d == _FLOAT_T(-1.0), ninf, x);
    x = _T::sel(d == _FLOAT_T(0.0), d, x);
    return x;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
log10(arg_t<vf_type> d)
{
    vf_type x=base_type::log10_k(d);
    const _FLOAT_T pinf=_T::pinf();
    const _FLOAT_T ninf=_T::ninf();
    x = _T::sel(d==pinf, pinf, x);
    // if ((d < 0)|isnan(d)) x = NAN;
    x = _T::sel((d < _FLOAT_T(0.0))|isnan(d), vf_type(_T::nan()), x);
    // if (d == 0) x = -INFINITY;
    x = _T::sel(d == _FLOAT_T(0.0), ninf, x);
    return x;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
log2(arg_t<vf_type> d)
{
    vf_type x=base_type::log2_k(d);
    const _FLOAT_T pinf=_T::pinf();
    const _FLOAT_T ninf=_T::ninf();
    x = _T::sel(d==pinf, pinf, x);
    // if ((d < 0)|isnan(d)) x = NAN;
    x = _T::sel((d < _FLOAT_T(0.0))|isnan(d), vf_type(_T::nan()), x);
    // if (d == 0) x = -INFINITY;
    x = _T::sel(d == _FLOAT_T(0.0), ninf, x);
    return x;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
pow(arg_t<vf_type> x, arg_t<vf_type> y)
{
// Pow returns x**y, the base-x exponential of y.
// Special cases are (in order):
// Pow(x, ±0) = 1 for any x
// Pow(1, y) = 1 for any y
// Pow(x, 1) = x for any x
// Pow(NaN, y) = NaN
// Pow(x, NaN) = NaN
// Pow(±0, y) = ±Inf for y an odd integer < 0
// Pow(±0, -Inf) = +Inf
// Pow(±0, +Inf) = +0
// Pow(±0, y) = +Inf for finite y < 0 and not an odd integer
// Pow(±0, y) = ±0 for y an odd integer > 0
// Pow(±0, y) = +0 for finite y > 0 and not an odd integer
// Pow(-1, ±Inf) = 1
// Pow(x, +Inf) = +Inf for |x| > 1
// Pow(x, -Inf) = +0 for |x| > 1
// Pow(x, +Inf) = +0 for |x| < 1
// Pow(x, -Inf) = +Inf for |x| < 1
// Pow(+Inf, y) = +Inf for y > 0
// Pow(+Inf, y) = +0 for y < 0
// Pow(-Inf, y) = Pow(-0, -y)
// Pow(x, y) = NaN for finite x < 0 and finite non-integer y

#if 0
    const auto f=[](_FLOAT_T xx, _FLOAT_T yy)->_FLOAT_T {
                     return std::pow(xx, yy);
                 };
    return base_type::call_scalar_func(x, y, f);
#else
    // domain of pow: (x > 0) || (x == 0 && y > 0) ||
    //                (x < 0 && y is an integer)

    __asm__ volatile("# LLVM-MCA-BEGIN\n\t");
    vf_type res=base_type::pow_k(x, y);
    vmf_type y_is_int = rint(y) == y;
    vf_type y_half=_FLOAT_T(0.5) *y;
    vmf_type y_is_odd = y_is_int & (rint(y_half) != y_half);

    vf_type res_fac= _T::sel(y_is_odd, _FLOAT_T(-1), _FLOAT_T(1));
    // res_fac = _T::sel(~y_is_int, _T::nan(), res_fac);
    res_fac = _T::sel(y_is_int, res_fac, _T::nan());
    res_fac = _T::sel(x >= _FLOAT_T(0), _FLOAT_T(1), res_fac);
    res *= res_fac;

    // vf_type efx= (abs(x) -1) * _T::sel(y<0, vf_type(-1), vf_type(1));
    vf_type efx = mulsign(vf_type(abs(x)-_FLOAT_T(1)), y);

    vmf_type y_inf= isinf(y);
    vf_type t= _T::sel(efx==_FLOAT_T(0), _FLOAT_T(1), _T::pinf());
    t = _T::sel_zero_or_val(efx < _FLOAT_T(0), t);
    res = _T::sel(y_inf, t, res);

    // if y==1, res==x
    res = _T::sel(y==_FLOAT_T(1), x, res);

    vmf_type x_zero = x == _FLOAT_T(0);
    vmf_type x_inf_or_zero= isinf(x) | x_zero;
    t= _T::sel(x_zero, -y, y);
    t= _T::sel_zero_or_val(t < _FLOAT_T(0), _T::pinf());
    t = _T::sel(y_is_odd, mulsign(t, x), t);
    res = _T::sel(x_inf_or_zero, t, res);
    res = _T::sel(isnan(x) | isnan(y), _T::nan(), res);
    res = _T::sel((y==_FLOAT_T(0)) | (x==_FLOAT_T(1)), _FLOAT_T(1), res);
    __asm__ volatile("# LLVM-MCA-END\n\t");
    return res;
#endif
}

template <typename _FLOAT_T, typename _T>
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
pow(arg_t<vf_type> x, arg_t<vi_type> e)
{
    vf_type res = base_type:: template powi_k<false>(x, e);
    vf_type y= cvt<vf_type>(e);

    vmi_type ei_is_odd= vi_type(e & 1)==vi_type(1);
    vmf_type e_is_odd = _T::vmi_to_vmf(ei_is_odd);
    // result is negative if x < 0 & y is odd
    vf_type sgn_x= copysign(_FLOAT_T(1.0), x);
    vmf_type res_neg = vmf_type(sgn_x < _FLOAT_T(0)) & e_is_odd;
    res = _T::sel(res_neg, -res, res);

    vmf_type x_zero = x == _FLOAT_T(0.0);
    vmf_type x_inf_or_zero= isinf(x) | x_zero;
    vf_type t= _T::sel(x_zero, -y, y);
    t= _T::sel_zero_or_val(t < _FLOAT_T(0.0), _T::pinf());
    vf_type t1=_T::sel(e_is_odd, sgn_x, vf_type(1));
    t1 *= t;
    res = _T::sel(x_inf_or_zero, t1, res);
    vmi_type ei_is_one = e==1;
    vmf_type e_is_one = _T::vmi_to_vmf(ei_is_one);
    res = _T::sel(e_is_one, x, res);
    res = _T::sel(isnan(x) | isnan(y), _T::nan(), res);
    res = _T::sel((y==_FLOAT_T(0.0)) | (x==_FLOAT_T(1.0)), _FLOAT_T(1), res);
    return res;
}

template <typename _FLOAT_T, typename _T>
typename cftal::math::elem_func<_FLOAT_T, _T>::vf_type
cftal::math::elem_func<_FLOAT_T, _T>::
rootn(arg_t<vf_type> x, arg_t<vi_type> e)
{
    vf_type res = base_type:: template powi_k<true>(x, e);
    res = copysign(res, x);
    vmi_type ei_is_one= e==1;
    vmf_type e_is_one= _T::vmi_to_vmf(ei_is_one);
    res = _T::sel(e_is_one, x, res);

    vmi_type ei_is_even= vi_type(e & 1) == 0;
    vmf_type e_is_even=_T::vmi_to_vmf(ei_is_even);
    vmi_type ei_is_zero= e==0;
    vmf_type e_is_zero=_T::vmi_to_vmf(ei_is_zero);
    vmi_type ei_is_pos= e>0;
    vmf_type e_is_pos= _T::vmi_to_vmf(ei_is_pos);
    vmf_type x_zero=x==0;
    res = _T::sel(x_zero, copysign(_T::pinf(), x), res);
    res = _T::sel(x_zero & e_is_even, _T::pinf(), res);
    res = _T::sel(x_zero & e_is_pos, x, res);
    res = _T::sel(x_zero & e_is_pos & e_is_even, _FLOAT_T(0.0), res);

    vmf_type x_inf=isinf(x);
    res = _T::sel(x_inf, copysign(vf_type(0.0), x), res);
    res = _T::sel(x_inf & e_is_pos, x, res);

    res = _T::sel(((x < 0) & e_is_even)|isnan(x)|e_is_zero, _T::nan(), res);
    return res;
}

template <typename _FLOAT_T, typename _TRAITS_T>
inline
void
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
sincos(arg_t<vf_type> d, vf_type* psin, vf_type* pcos)
{
    if ((psin!=nullptr) || (pcos!=nullptr)) {
        base_type::sin_cos_k(d, psin, pcos);
        if (psin!=nullptr) {
            *psin = _TRAITS_T::sel(d==_FLOAT_T(0), d, *psin);
        }
    }
}

template <typename _FLOAT_T, typename _TRAITS_T>
inline
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
sin(arg_t<vf_type> d)
{
    vf_type s;
    base_type::sin_cos_k(d, &s, nullptr);
    s = _TRAITS_T::sel(d==_FLOAT_T(0), d, s);
    return s;
}

template <typename _FLOAT_T, typename _TRAITS_T>
inline
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
cos(arg_t<vf_type> d)
{
    vf_type c;
    base_type::sin_cos_k(d, nullptr, &c);
    return c;
}

template <typename _FLOAT_T, typename _TRAITS_T>
inline
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
tan(arg_t<vf_type> d)
{
    vf_type t=base_type::tan_k(d);
    t = _TRAITS_T::sel(isinf(d) | isnan(d),
                       copysign(_TRAITS_T::nan(), d),
                       t);
    t = _TRAITS_T::sel(d==_FLOAT_T(0), d, t);
    return t;
}

template <typename _FLOAT_T, typename _TRAITS_T>
inline
void
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
sinpicospi(arg_t<vf_type> d, vf_type* psin, vf_type* pcos)
{
    if ((psin!=nullptr) || (pcos!=nullptr)) {
        vmf_type inf_nan=isinf(d) | isnan(d);
        base_type::sinpi_cospi_k(d, psin, pcos);
        if (psin!=nullptr) {
            *psin= _TRAITS_T::sel(inf_nan,
                                  copysign(_TRAITS_T::nan(), d),
                                  *psin);
        }
        if (pcos!=nullptr) {
            *pcos= _TRAITS_T::sel(inf_nan,
                                  _TRAITS_T::nan(),
                                  *pcos);
        }
    }
}

template <typename _FLOAT_T, typename _TRAITS_T>
inline
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
sinpi(arg_t<vf_type> d)
{
    vf_type s;
    base_type::sinpi_cospi_k(d, &s, nullptr);
    s = _TRAITS_T::sel(isinf(d) | isnan(d),
                       copysign(_TRAITS_T::nan(), d),
                       s);
    return s;
}

template <typename _FLOAT_T, typename _TRAITS_T>
inline
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
cospi(arg_t<vf_type> d)
{
    vf_type c;
    base_type::sinpi_cospi_k(d, nullptr, &c);
    c = _TRAITS_T::sel(isinf(d) | isnan(d),
                       _TRAITS_T::nan(),
                       c);
    return c;
}

template <typename _FLOAT_T, typename _TRAITS_T>
inline
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
tanpi(arg_t<vf_type> d)
{
    vf_type t=base_type::tanpi_k(d);
    t = _TRAITS_T::sel(isinf(d) | isnan(d),
                       copysign(_TRAITS_T::nan(), d),
                       t);
    return t;
}

template <typename _FLOAT_T, typename _TRAITS_T>
inline
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
atan2(arg_t<vf_type> y, arg_t<vf_type> x)
{
    vf_type r=base_type::atan2_k(y, x);

    using _T = _TRAITS_T;

    vmf_type y_zero = y==_FLOAT_T(0);
    vmf_type x_inf = isinf(x);
    vmf_type y_inf = isinf(y);
    vmf_type x_zero = x==_FLOAT_T(0);
    vmf_type x_nan = isnan(x);
    vmf_type y_nan = isnan(y);

    vmf_type special = y_zero | x_inf | y_inf | x_zero | x_nan | y_nan;

    if (_T::any_of_vmf(special)) {
        vf_type y_sgn =  copysign(_FLOAT_T(1), y);
        vmf_type y_p= y_sgn == _FLOAT_T(1.0);
        vmf_type y_n= y_sgn == _FLOAT_T(-1.0);
        vmf_type y_p_zero = y_p & y_zero;
        vmf_type y_n_zero = y_n & y_zero;
        vmf_type y_gt_z = y>_FLOAT_T(0);
        vmf_type y_lt_z = y<_FLOAT_T(0);
        vmf_type y_p_inf = y_inf & y_p;
        vmf_type y_n_inf = y_inf & y_n;

        vf_type x_sgn = copysign(_FLOAT_T(1), x);
        vmf_type x_p= x_sgn == _FLOAT_T(1.0);
        vmf_type x_n= x_sgn == _FLOAT_T(-1.0);
        vmf_type x_p_zero = x_p & x_zero;
        vmf_type x_n_zero = x_n & x_zero;
        vmf_type x_p_inf = x_p & x_inf;
        vmf_type x_n_inf = x_n & x_inf;
        vmf_type x_gt_z = x>_FLOAT_T(0);
        vmf_type x_lt_z = x<_FLOAT_T(0);
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
        //  atan2(y, +Inf) = copysign(0, y);
        r = _T::sel(x_p_inf, copysign(_FLOAT_T(0), y), r);
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
inline
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
atan(arg_t<vf_type> x)
{
    vf_type r= base_type::atan_k(x);
    r=_TRAITS_T::sel(x==_FLOAT_T(0), x, r);
    r=_TRAITS_T::sel(isinf(x), copysign(_FLOAT_T(M_PI/2), x) , r);
    r=_TRAITS_T::sel(isnan(x), x, r);
    return r;
}

template <typename _FLOAT_T, typename _TRAITS_T>
inline
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
asin(arg_t<vf_type> x)
{
    vf_type r=base_type::asin_k(x);
    r = _TRAITS_T::sel(x == _FLOAT_T(-1), -M_PI/2, r);
    r = _TRAITS_T::sel(x == _FLOAT_T(1), M_PI/2, r);
    r = _TRAITS_T::sel(x < _FLOAT_T(-1), -_TRAITS_T::nan(), r);
    r = _TRAITS_T::sel((x > _FLOAT_T(1))|isnan(x), _TRAITS_T::nan(), r);
    return r;
}

template <typename _FLOAT_T, typename _TRAITS_T>
inline
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
acos(arg_t<vf_type> x)
{
    vf_type r=base_type::acos_k(x);
    r = _TRAITS_T::sel(x == _FLOAT_T(-1), M_PI, r);
    r = _TRAITS_T::sel_zero_or_val(x == _FLOAT_T(1), r);
    r = _TRAITS_T::sel(x == _FLOAT_T(0), M_PI/2, r);
    r = _TRAITS_T::sel(x < _FLOAT_T(-1), -_TRAITS_T::nan(), r);
    r = _TRAITS_T::sel((x > _FLOAT_T(1))|isnan(x), _TRAITS_T::nan(), r);
    return r;
}

template <typename _FLOAT_T, typename _TRAITS_T>
inline
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
asinh(arg_t<vf_type> x)
{
    vf_type r=base_type::asinh_k(x);
    r = _TRAITS_T::sel(isinf(x)|isnan(x), x, r);
    return r;
}

template <typename _FLOAT_T, typename _TRAITS_T>
inline
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
acosh(arg_t<vf_type> x)
{
    vf_type r=base_type::acosh_k(x);
    r = _TRAITS_T::sel(x < _FLOAT_T(1.0), _TRAITS_T::nan(), r);
    r = _TRAITS_T::sel((x== _TRAITS_T::pinf())|isnan(x), x, r);
    return r;
}

template <typename _FLOAT_T, typename _TRAITS_T>
inline
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
atanh(arg_t<vf_type> x)
{
    vf_type r=base_type::atanh_k(x);
    r = _TRAITS_T::sel(x == _FLOAT_T(-1.0), _TRAITS_T::ninf(), r);
    r = _TRAITS_T::sel(x < _FLOAT_T(-1.0), -_TRAITS_T::nan(), r);
    r = _TRAITS_T::sel(x == _FLOAT_T(1.0), _TRAITS_T::pinf(), r);
    r = _TRAITS_T::sel((x > _FLOAT_T(1.0))|isnan(x), _TRAITS_T::nan(), r);
    return r;
}

template <typename _FLOAT_T, typename _TRAITS_T>
inline
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
exp_mx2(arg_t<vf_type> x)
{
    return base_type::exp_mx2_k(x);
}

template <typename _FLOAT_T, typename _TRAITS_T>
inline
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
exp_px2(arg_t<vf_type> x)
{
    return base_type::exp_px2_k(x);
}

template <typename _FLOAT_T, typename _TRAITS_T>
inline
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
exp2_mx2(arg_t<vf_type> x)
{
    return base_type::exp2_mx2_k(x);
}

template <typename _FLOAT_T, typename _TRAITS_T>
inline
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
exp2_px2(arg_t<vf_type> x)
{
    return base_type::exp2_px2_k(x);
}

template <typename _FLOAT_T, typename _TRAITS_T>
inline
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
exp10_mx2(arg_t<vf_type> x)
{
    return base_type::exp10_mx2_k(x);
}

template <typename _FLOAT_T, typename _TRAITS_T>
inline
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
exp10_px2(arg_t<vf_type> x)
{
    return base_type::exp10_px2_k(x);
}

template <typename _FLOAT_T, typename _TRAITS_T>
inline
typename cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::elem_func<_FLOAT_T, _TRAITS_T>::
sig(arg_t<vf_type> x)
{

    using fc= func_constants<_FLOAT_T>;
    //
    // constexpr const double xh=36.7368005696771013991133;
    // constexpr const double xl=-xh-5.0;
    // log(0x1p54);
    // constexpr const double xh=37.42994775023704676404168579;
    // constexpr const double xl=-xh;
    // log(0x1p23)
    // const float xh=15.9423847198486328125f;
    // const float xl=-xh;
    constexpr const _FLOAT_T lgf_lo_eq_exp= fc::sig_le_eq_exp();
    vmf_type xm= x>lgf_lo_eq_exp;
    vf_type xe= _TRAITS_T::sel(xm, -x, x);
    vf_type xrh, xrl;
    vi_type idx, ki;
    base_type::__reduce_exp_arg(xrh, xrl, idx, ki, xe);
    vf_type el, eh=base_type::template
        __exp_tbl_k<base_type::result_prec::medium>(xrh, xrl, idx, &el);
    auto sc=base_type::__two_pow(ki);
    eh *= sc.f0();
    eh *= sc.f1();
    constexpr const _FLOAT_T lgf_hi_one=  fc::sig_hi_one();
    vmf_type x_not_hi= x < lgf_hi_one;
    vf_type rh, rl;
    // avoid multiplication of subnormal numbers
    vmf_type avoid_sn= xm & x_not_hi;
    vf_type th=_TRAITS_T::sel_val_or_zero(avoid_sn, eh);
    vf_type tl=_TRAITS_T::sel_val_or_zero(avoid_sn, el);
    tl *= sc.f0();
    tl *= sc.f1();
    d_ops::add122cond(rh, rl, _FLOAT_T(1.0), th, tl);
    d_ops::rcp21(rh, rh, rl);
    vf_type r = _TRAITS_T::sel(xm, rh, eh);
    r = _TRAITS_T::sel(x_not_hi, r, _FLOAT_T(1.0));
    constexpr const _FLOAT_T neg_exp_hi_inf= -fc::exp_hi_inf();
    r = _TRAITS_T::sel(x<= neg_exp_hi_inf, _FLOAT_T(0.0), r);
    r = _TRAITS_T::sel(isnan(x), x, r);
    return r;
}

// Local Variables:
// mode: c++
// end:
#endif
