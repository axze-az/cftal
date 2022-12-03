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
#if !defined (__CFTAL_MATH_ELEM_FUNC_WRAPPER_F32_H__)
#define __CFTAL_MATH_ELEM_FUNC_WRAPPER_F32_H__ 1

#include <cftal/config.h>
#include <cftal/math/elem_func_core_f32.h>
#if  __CFTAL_CFG_USE_VF64_FOR_VF32__ > 0
#include <cftal/vec_cvt.h>
#include <cftal/math/elem_func_core_f64.h>
#include <cftal/math/elem_func_loprec_core_f64.h>
#include <cftal/math/func_traits_f64_s32.h>
#include <cftal/math/impl_d_real_constants_f64.h>

#define __CFTAL_CFG_USE_VF64_FOR_VF32_RSQRT__ 0
#define __CFTAL_CFG_USE_VF64_FOR_VF32_EXP_FUNCS__ 1
#define __CFTAL_CFG_USE_VF64_FOR_VF32_EXP2_FUNCS__ 1
#define __CFTAL_CFG_USE_VF64_FOR_VF32_EXP10_FUNCS__ 1
#define __CFTAL_CFG_USE_VF64_FOR_VF32_HYPERBOLIC_FUNCS__ 1
#define __CFTAL_CFG_USE_VF64_FOR_VF32_LOG__ 1
#define __CFTAL_CFG_USE_VF64_FOR_VF32_LOG2__ 1
#define __CFTAL_CFG_USE_VF64_FOR_VF32_LOG10__ 1
#define __CFTAL_CFG_USE_VF64_FOR_VF32_POW_FUNCS__ 1

namespace cftal {
    namespace math {
        // specialization of elem_func_wrapper for float and different
        // traits
        template <typename _T>
        struct elem_func_wrapper<float, _T>
            : public elem_func_core<float, _T> {
            using base_type = elem_func_core<float, _T>;
            using vf_type = typename base_type::vf_type;
            using vi_type = typename base_type::vi_type;
            using vmi_type = typename base_type::vmi_type;
            using vmf_type = typename base_type::vmf_type;

            using f64_traits = typename _T::vhf_traits;
            using f64_core = elem_func_loprec_core<double, f64_traits>;
            using vhf_type = typename f64_traits::vf_type;
            using vmhf_type = typename f64_traits::vmf_type;
            using vi2_type = typename f64_traits::vi2_type;
            using vmi2_type = typename f64_traits::vmi2_type;

#if __CFTAL_CFG_USE_VF64_FOR_VF32_RSQRT__>0
            static
            vf_type
            rsqrt_k(arg_t<vf_type> x);
#endif
#if __CFTAL_CFG_USE_VF64_FOR_VF32_EXP_FUNCS__ >0
            template <bool _EXP_M1>
            static
            vf_type
            exp_k(arg_t<vf_type> x);

            static
            vf_type
            exp_mx2_k(arg_t<vf_type> x);

            static
            vf_type
            exp_px2_k(arg_t<vf_type> x);
#endif
#if __CFTAL_CFG_USE_VF64_FOR_VF32_EXP2_FUNCS__ >0
            template <bool _EXP2_M1>
            static
            vf_type
            exp2_k(arg_t<vf_type> x);

            static
            vf_type
            exp2_mx2_k(arg_t<vf_type> x);

            static
            vf_type
            exp2_px2_k(arg_t<vf_type> x);
#endif
#if __CFTAL_CFG_USE_VF64_FOR_VF32_EXP10_FUNCS__ >0
            template <bool _EXP10_M1>
            static
            vf_type
            exp10_k(arg_t<vf_type> x);

            static
            vf_type
            exp10_mx2_k(arg_t<vf_type> x);

            static
            vf_type
            exp10_px2_k(arg_t<vf_type> x);
#endif
#if __CFTAL_CFG_USE_VF64_FOR_VF32_HYPERBOLIC_FUNCS__>0
            static
            vf_type
            sinh_k(arg_t<vf_type> x);

            static
            vf_type
            cosh_k(arg_t<vf_type> x);
#endif
#if __CFTAL_CFG_USE_VF64_FOR_VF32_LOG__ >0
            static
            vf_type
            log_k(arg_t<vf_type> x);
#endif
#if __CFTAL_CFG_USE_VF64_FOR_VF32_LOG2__ >0
            static
            vf_type
            log2_k(arg_t<vf_type> x);
#endif
#if __CFTAL_CFG_USE_VF64_FOR_VF32_LOG10__ >0
            static
            vf_type
            log10_k(arg_t<vf_type> x);
#endif
#if __CFTAL_CFG_USE_VF64_FOR_VF32_POW_FUNCS__ >0
            static
            vf_type
            pow_k(arg_t<vf_type> x, arg_t<vf_type> y);

            template <bool _CALC_ROOT>
            static
            vf_type
            powi_k(arg_t<vf_type> x, arg_t<vi_type> e);
#endif

        };
    }
}

#if __CFTAL_CFG_USE_VF64_FOR_VF32_RSQRT__>0
template <typename _T>
inline
typename cftal::math::elem_func_wrapper<float, _T>::vf_type
cftal::math::elem_func_wrapper<float, _T>::
rsqrt_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type rd=1.0/sqrt(xd);
    vf_type r=cvt<vf_type>(rd);
    return r;
}
#endif

#if __CFTAL_CFG_USE_VF64_FOR_VF32_EXP_FUNCS__ >0
template <typename _T>
template <bool _EXP_M1>
inline
typename cftal::math::elem_func_wrapper<float, _T>::vf_type
cftal::math::elem_func_wrapper<float, _T>::
exp_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type rd=f64_core::template exp_k<_EXP_M1>(xd);
    vf_type r=cvt<vf_type>(rd);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<float, _T>::vf_type
cftal::math::elem_func_wrapper<float, _T>::
exp_mx2_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type x2d=-xd*xd;
    vhf_type yd=f64_core::template exp_k<false>(x2d);
    vf_type x2h=cvt<vf_type>(x2d);
    vf_type y=cvt<vf_type>(yd);
    using fc_t = math::func_constants<float>;
    y= _T::sel_zero_or_val(x2h <= fc_t::exp_lo_zero(), y);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<float, _T>::vf_type
cftal::math::elem_func_wrapper<float, _T>::
exp_px2_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type x2d=xd*xd;
    vhf_type yd=f64_core::template exp_k<false>(x2d);
    vf_type x2h=cvt<vf_type>(x2d);
    vf_type y=cvt<vf_type>(yd);
    using fc_t = math::func_constants<float>;
    // NOT >= because of rounding:
    y= _T::sel(x2h > fc_t::exp_hi_inf(), _T::pinf(), y);
    return y;
}
#endif

#if __CFTAL_CFG_USE_VF64_FOR_VF32_EXP2_FUNCS__ >0
template <typename _T>
template <bool _EXP2_M1>
inline
typename cftal::math::elem_func_wrapper<float, _T>::vf_type
cftal::math::elem_func_wrapper<float, _T>::
exp2_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type rd=f64_core::template exp2_k<_EXP2_M1>(xd);
    vf_type r=cvt<vf_type>(rd);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<float, _T>::vf_type
cftal::math::elem_func_wrapper<float, _T>::
exp2_mx2_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type x2d=-xd*xd;
    vf_type x2h=cvt<vf_type>(x2d);
    vhf_type yd=f64_core::template exp2_k<false>(x2d);
    vf_type y=cvt<vf_type>(yd);
    using fc_t = math::func_constants<float>;
    y= _T::sel_zero_or_val(x2h <= fc_t::exp2_lo_zero(), y);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<float, _T>::vf_type
cftal::math::elem_func_wrapper<float, _T>::
exp2_px2_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type x2d=xd*xd;
    vhf_type yd=f64_core::template exp2_k<false>(x2d);
    vf_type x2h=cvt<vf_type>(x2d);
    vf_type y=cvt<vf_type>(yd);
    using fc_t = math::func_constants<float>;
    y= _T::sel(x2h >= fc_t::exp2_hi_inf(), _T::pinf(), y);
    return y;
}
#endif

#if __CFTAL_CFG_USE_VF64_FOR_VF32_EXP10_FUNCS__ >0
template <typename _T>
template <bool _EXP10_M1>
inline
typename cftal::math::elem_func_wrapper<float, _T>::vf_type
cftal::math::elem_func_wrapper<float, _T>::
exp10_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type rd=f64_core::template exp10_k<_EXP10_M1>(xd);
    vf_type r=cvt<vf_type>(rd);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<float, _T>::vf_type
cftal::math::elem_func_wrapper<float, _T>::
exp10_mx2_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type x2d=-xd*xd;
    vf_type x2h=cvt<vf_type>(x2d);
    vhf_type yd=f64_core::template exp10_k<false>(x2d);
    vf_type y=cvt<vf_type>(yd);
    using fc_t = math::func_constants<float>;
    y= _T::sel_zero_or_val(x2h <= fc_t::exp10_lo_zero(), y);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<float, _T>::vf_type
cftal::math::elem_func_wrapper<float, _T>::
exp10_px2_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type x2d=xd*xd;
    vhf_type yd=f64_core::template exp10_k<false>(x2d);
    vf_type x2h=cvt<vf_type>(x2d);
    vf_type y=cvt<vf_type>(yd);
    using fc_t = math::func_constants<float>;
    y= _T::sel(x2h >= fc_t::exp10_hi_inf(), _T::pinf(), y);
    return y;
}
#endif

#if __CFTAL_CFG_USE_VF64_FOR_VF32_HYPERBOLIC_FUNCS__>0
template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_wrapper<float, _T>::vf_type
cftal::math::elem_func_wrapper<float, _T>::
sinh_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type yd=f64_core::template
        sinh_cosh_k<f64_core::hyperbolic_func::c_sinh>(xd);
    vf_type y=cvt<vf_type>(yd);
    y=_T::sel(isnan(x), x, y);
    return y;
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_wrapper<float, _T>::vf_type
cftal::math::elem_func_wrapper<float, _T>::
cosh_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type yd=f64_core::template
        sinh_cosh_k<f64_core::hyperbolic_func::c_cosh>(xd);
    vf_type y=cvt<vf_type>(yd);
    y=_T::sel(isnan(x), x, y);
    return y;
}
#endif

#if __CFTAL_CFG_USE_VF64_FOR_VF32_LOG__ >0
template <typename _T>
inline
typename cftal::math::elem_func_wrapper<float, _T>::vf_type
cftal::math::elem_func_wrapper<float, _T>::
log_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type rd=f64_core::template __log_k<f64_core::log_func::c_log_e>(xd);
    vf_type r=cvt<vf_type>(rd);
    return r;
}
#endif

#if __CFTAL_CFG_USE_VF64_FOR_VF32_LOG2__ >0
template <typename _T>
inline
typename cftal::math::elem_func_wrapper<float, _T>::vf_type
cftal::math::elem_func_wrapper<float, _T>::
log2_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type rd=f64_core::template __log_k<f64_core::log_func::c_log_2>(xd);
    vf_type r=cvt<vf_type>(rd);
    return r;
}
#endif

#if __CFTAL_CFG_USE_VF64_FOR_VF32_LOG10__ >0
template <typename _T>
inline
typename cftal::math::elem_func_wrapper<float, _T>::vf_type
cftal::math::elem_func_wrapper<float, _T>::
log10_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type rd=f64_core::template __log_k<f64_core::log_func::c_log_10>(xd);
    vf_type r=cvt<vf_type>(rd);
    return r;
}
#endif

#if __CFTAL_CFG_USE_VF64_FOR_VF32_POW_FUNCS__ >0
template <typename _T>
inline
typename cftal::math::elem_func_wrapper<float, _T>::vf_type
cftal::math::elem_func_wrapper<float, _T>::
pow_k(arg_t<vf_type> x, arg_t<vf_type> y)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type yd=cvt<vhf_type>(y);
    vhf_type ylnx;
    vhf_type rd=f64_core::pow_k(xd, yd, &ylnx);
    vf_type r=cvt<vf_type>(rd);
    using fc=func_constants<float>;
    const vf_type d= cvt<vf_type>(ylnx);
    constexpr
    const float exp_hi_inf= fc::exp_hi_inf();
    constexpr
    const float exp_lo_zero= fc::exp_lo_zero();
    r = _T::sel_zero_or_val(d <= exp_lo_zero, r);
    r = _T::sel(d >= exp_hi_inf, _T::pinf(), r);
    return r;
}

template <typename _T>
template <bool _CALC_ROOT>
inline
typename cftal::math::elem_func_wrapper<float, _T>::vf_type
cftal::math::elem_func_wrapper<float, _T>::
powi_k(arg_t<vf_type> x, arg_t<vi_type> e)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type ylnx;
    vhf_type rd=f64_core::template powi_k<_CALC_ROOT>(xd, e, &ylnx);
    vf_type r=cvt<vf_type>(rd);
    using fc=func_constants<float>;
    const vf_type d= cvt<vf_type>(ylnx);
    constexpr
    const float exp_hi_inf= fc::exp_hi_inf();
    constexpr
    const float exp_lo_zero= fc::exp_lo_zero();
    r = _T::sel_zero_or_val(d <= exp_lo_zero, r);
    r = _T::sel(d >= exp_hi_inf, _T::pinf(), r);
    return r;
}

#endif

#endif
#endif // __CFTAL_MATH_ELEM_FUNC_WRAPPER_F32_H__
