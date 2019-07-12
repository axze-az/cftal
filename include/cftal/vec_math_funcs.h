//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_VEC_MATH_FUNCS_H__)
#define __CFTAL_VEC_MATH_FUNCS_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/vec_spec.h>

namespace cftal {

    namespace impl {
    }

    // returns linear interpolation between a and b
    template <typename _T, typename _T1, std::size_t _N>
    std::enable_if_t<std::is_floating_point_v<_T>, vec<_T, _N> >
    lerp(_T1 a, _T1 b, const vec<_T, _N>& t);

}

template <typename _T, typename _T1, std::size_t _N>
inline
std::enable_if_t<std::is_floating_point_v<_T>, cftal::vec<_T, _N> >
cftal::lerp(_T1 a, _T1 b, const vec<_T, _N>& t)
{
    vec<_T, _N> va=a;
    vec<_T, _N> vb=b;
    typename vec<_T, _N>::mask_type nan_res=
        isnan(va)|isnan(vb)|isnan(t);
    typename vec<_T, _N>::mask_type opposite_sgns=
        (va <= _T(0) & vb >= _T(0)) || (va >= _T(0) & vb <= _T(0));
    typename vec<_T, _N>::mask_type t_one= t == _T(1.0);

    // a, b with different signs
    vec<_T, _N> r0= t * vb + ((_T(1) - t) * va);
    // near t equal 1
    vec<_T, _N> r1= va + t * (va - vb);
    typename vec<_T, _N>::mask_type tt= (t > _T(1.0)) == (vb > va);
    vec<_T, _N> rt= max(vb, r1);
    vec<_T, _N> rf= min(vb, r1);
    r1 = select(tt, rt, rf);
    // if opposite signs near t equal 1
    vec<_T, _N> r = select(opposite_sgns, r0, r1);
    // t exactly 1.0
    r = select(t_one, vb, r);
    // t or a, b nan
    const vec<_T, _N> tnan=std::numeric_limits<_T>::quiet_NaN();
    r = select(nan_res, tnan, r);
    return r;
}

// Local variables:
// mode: c++
// end:
#endif
