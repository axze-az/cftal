//
// Copyright Axel Zeuner 2010-2017. Use, modification and
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
            static vf_type erf(arg_t<vf_type> x);
            static vf_type erfc(arg_t<vf_type> x);
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
    r = _TRAITS_T::sel(x < -fc::erf_lt_one_fin(), -1.0, r);
    r = _TRAITS_T::sel(x > fc::erf_lt_one_fin(), 1.0, r);
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
    // using fc=func_constants<_FLOAT_T>;
    // r = _TRAITS_T::sel(x < -fc::erf_lt_one_fin, -1.0, r);
    // r = _TRAITS_T::sel(x > fc::erf_lt_one_fin, 1.0, r);
    r = _TRAITS_T::sel(x == 0, 1.0, r);
    r = _TRAITS_T::sel(isnan(x), x, r);
    return r;
}

// Local Variables:
// mode: c++
// end:
#endif
