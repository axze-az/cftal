//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_MATH_SPEC_FUNC_H__)
#define __CFTAL_MATH_SPEC_FUNC_H__ 1

#include <cftal/config.h>
#include <cftal/arg.h>
#include <cftal/math/func_constants.h>

namespace cftal {

    namespace math {

        template <typename _FLOAT_T, typename _TRAITS_T>
        struct spec_func_core {
            // specializations contain the implementation of
            // special functions
        };

        // common code for special functions
        template <typename _FLOAT_T, typename _TRAITS_T>
        struct spec_func : public spec_func_core<_FLOAT_T, _TRAITS_T> {
            using base_type = spec_func_core<_FLOAT_T, _TRAITS_T>;
            using vf_type = typename _TRAITS_T::vf_type;
            using vmf_type = typename _TRAITS_T::vmf_type;
            using vi_type = typename _TRAITS_T::vi_type;
            using vmi_type = typename _TRAITS_T::vmi_type;

            static
            vf_type
            erf(arg_t<vf_type> x);

            static
            vf_type
            erfc(arg_t<vf_type> x);

            static
            vf_type
            tgamma(arg_t<vf_type> x);

            static
            vf_type
            lgamma(arg_t<vf_type> xc, vi_type* signp);


        };

    }
}

template <typename _FLOAT_T, typename _TRAITS_T>
typename cftal::math::spec_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::spec_func<_FLOAT_T, _TRAITS_T>::
erf(arg_t<vf_type> x)
{
    vf_type r=base_type::erf_k(x);
    using fc=func_constants<_FLOAT_T>;
    r = _TRAITS_T::sel(x < -fc::erf_lt_one_fin(), vf_type(-1.0), r);
    r = _TRAITS_T::sel(x > fc::erf_lt_one_fin(), vf_type(1.0), r);
    r = _TRAITS_T::sel(x == 0, x, r);
    r = _TRAITS_T::sel(isnan(x), x, r);
    return r;
}

template <typename _FLOAT_T, typename _TRAITS_T>
typename cftal::math::spec_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::spec_func<_FLOAT_T, _TRAITS_T>::
erfc(arg_t<vf_type> x)
{
    vf_type r=base_type::erfc_k(x);
    using fc=func_constants<_FLOAT_T>;
    r = _TRAITS_T::sel_zero_or_val(x > fc::erfc_gt_zero_fin(), r);
    r = _TRAITS_T::sel(x < -fc::erfc_gt_zero_fin(), vf_type(2.0), r);
    r = _TRAITS_T::sel(x == 0, vf_type(1.0), r);
    r = _TRAITS_T::sel(isnan(x), x, r);
    return r;
}

template <typename _FLOAT_T, typename _TRAITS_T>
typename cftal::math::spec_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::spec_func<_FLOAT_T, _TRAITS_T>::
tgamma(arg_t<vf_type> xc)
{
    vmf_type xc_lt_0 = xc < vf_type(0.0);
    vf_type r= base_type::tgamma_k(xc, xc_lt_0);
    using fc= func_constants<_FLOAT_T>;
    r = _TRAITS_T::sel(xc >= fc::tgamma_hi_inf(), _TRAITS_T::pinf(), r);
    if (any_of(xc_lt_0)) {
        if (any_of(xc <= fc::tgamma_lo_zero())) {
            // tgamma(x) = -0 for -odd < x <= -even
            const vf_type half(0.5);
            vmf_type is_even=
                vf_type(floor(xc)*half) == floor(vf_type(xc*half));
            vf_type n_r=_TRAITS_T::sel(is_even, vf_type(+0.0), vf_type(-0.0));
            // nan selection is not necessary
            r = _TRAITS_T::sel(xc <= fc::tgamma_lo_zero(), n_r, r);
        }
        vmf_type xc_is_int=xc==floor(xc);
        vmf_type xc_lt_0_and_int_or_ninf=
            xc_lt_0 & (xc_is_int | (xc == vf_type(_TRAITS_T::ninf())));
        r = _TRAITS_T::sel(xc_lt_0_and_int_or_ninf, _TRAITS_T::nan(), r);
    }
    r = _TRAITS_T::sel(isnan(xc), xc, r);
    return r;
}

template <typename _FLOAT_T, typename _TRAITS_T>
typename cftal::math::spec_func<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::spec_func<_FLOAT_T, _TRAITS_T>::
lgamma(arg_t<vf_type> xc, vi_type* signp)
{
    vmf_type x_lt_0 = xc < vf_type(0.0);
    vi_type si;
    vf_type lg=base_type::lgamma_k(xc, &si);

    using fc= func_constants<_FLOAT_T>;
    lg = _TRAITS_T::sel(xc >= fc::lgamma_hi_inf(), _TRAITS_T::pinf(), lg);
    if (any_of(x_lt_0)) {
        vmf_type is_int = xc == floor(xc);
        vmf_type is_int_lt_0 = is_int & x_lt_0;
        lg = _TRAITS_T::sel(is_int_lt_0, _TRAITS_T::pinf(), lg);
        si = _TRAITS_T::sel(_TRAITS_T::vmf_to_vmi(is_int_lt_0), 1, si);
    }
    vmf_type t;
    if (any_of(t=xc==vf_type(0.0))) {
        lg = _TRAITS_T::sel(t, _TRAITS_T::pinf(), lg);
        vmi_type ti=_TRAITS_T::vmf_to_vmi(t);
        vf_type sgn=copysign(vf_type(1.0), xc);
        vi_type ni=_TRAITS_T::cvt_f_to_i(sgn);
        si = _TRAITS_T::sel(ti, ni, si);
    }
    lg = _TRAITS_T::sel(isnan(xc), xc, lg);
    if (signp != nullptr) {
        *signp = si;
    }
    return lg;
}

// Local Variables:
// mode: c++
// end:
#endif
