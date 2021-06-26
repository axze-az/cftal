//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_VEC_MATH_FUNCS_H__)
#define __CFTAL_VEC_MATH_FUNCS_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/type_traits.h>
#include <cftal/vec_spec.h>

namespace cftal {

    namespace impl {
    }

    // returns linear interpolation between a and b
    template <typename _T, typename _T1, std::size_t _N>
    std::enable_if_t<cftal::is_floating_point_v<_T>, vec<_T, _N> >
    lerp(const _T1& a, const _T1& b, const vec<_T, _N>& t);

    // signed saturated addition
    template <typename _I>
    std::enable_if_t<cftal::is_signed_v<_I> && cftal::is_integral_v<_I>, _I>
    sat_add(const _I& a, const _I& b);
    
    // unsigned saturated addition
    template <typename _U>
    std::enable_if_t<cftal::is_unsigned_v<_U> && cftal::is_integral_v<_U>, _U>
    sat_add(const _U& a, const _U& b);
 
    // signed saturated subtraction
    template <typename _I>
    std::enable_if_t<cftal::is_signed_v<_I> && cftal::is_integral_v<_I>, _I>
    sat_sub(const _I& a, const _I& b);
    
    // unsigned saturated subtraction
    template <typename _U>
    std::enable_if_t<cftal::is_unsigned_v<_U> && cftal::is_integral_v<_U>, _U>
    sat_sub(const _U& a, const _U& b);

    // (unsigned) integer average: (a+b+1)/2
    template <typename _T>
    std::enable_if_t<cftal::is_integral_v<_T>, _T>
    average(const _T& a, const _T& b);
    
}

template <typename _T, typename _T1, std::size_t _N>
inline
std::enable_if_t<cftal::is_floating_point_v<_T>, cftal::vec<_T, _N> >
cftal::lerp(const _T1& a, const _T1& b, const vec<_T, _N>& t)
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

// signed saturated addition
template <typename _I>
std::enable_if_t<cftal::is_signed_v<_I> && cftal::is_integral_v<_I>, _I>
cftal::sat_add(const _I& a, const _I& b) 
{
    _I r= a +b;
    const _I v_max=std::numeric_limits<_I>::max();
    const _I v_min=std::numeric_limits<_I>::min();
    // if ((b > 0) && (a > int8_t(v_max - b))) {
    //     r = v_max;
    // } 
    _I v_max_minus_b=v_max - b;
    r = select((b > _I(0)) & (a > v_max_minus_b), v_max, r);
    // if ((b < 0) && (a < int8_t(v_min - b))) {
    //     r = v_min;
    // }
    _I v_min_minus_b=v_min - b;
    r = select((b<_I(0)) & (a < v_min_minus_b), v_min, r);        
    return r;
}

// unsigned saturated addition
template <typename _U>
std::enable_if_t<cftal::is_unsigned_v<_U> && cftal::is_integral_v<_U>, _U>
cftal::sat_add(const _U& a, const _U& b) 
{
    _U r= a +b;
    const _U v_max=std::numeric_limits<_U>::max();
    // if (a > uint8_t(v_max - b)) {
    //     r = v_max;
    // } 
    _U v_max_minus_b=v_max - b;
    r = select(a > v_max_minus_b, v_max, r);
    return r;
}   

// signed saturated subtraction
template <typename _I>
std::enable_if_t<cftal::is_signed_v<_I> && cftal::is_integral_v<_I>, _I>
cftal::sat_sub(const _I& a, const _I& b) 
{
    _I r= a - b;
    const _I v_max=std::numeric_limits<_I>::max();
    const _I v_min=std::numeric_limits<_I>::min();
    // if ((b < 0) && (a > int8_t(v_max + b))) {
    //    r = v_max;
    // }
    _I v_max_plus_b=v_max + b;
    r = select((b<_I(0)) & (a > v_max_plus_b), v_max, r);
    // if ((b > 0) && (a < int8_t(v_min + b))) {
    //    r = v_min;
    // } 
    _I v_min_plus_b=v_min + b;
    r = select((b>_I(0)) & (a < v_min_plus_b), v_min, r);
    return r;
}

// unsigned saturated subtraction
template <typename _U>
std::enable_if_t<cftal::is_unsigned_v<_U> && cftal::is_integral_v<_U>, _U>
cftal::sat_sub(const _U& a, const _U&  b) 
{
    _U r= a - b;
    const _U v_min=std::numeric_limits<_U>::min();
    // if (a < uint8_t(v_min + b)) {
    //    r = v_min;
    // } 
    _U v_min_plus_b=v_min + b;
    r = select(a < v_min_plus_b, v_min, r);
    return r;
}

// (unsigned) integer average
template <typename _T>
std::enable_if_t<cftal::is_integral_v<_T>, _T>
cftal::average(const _T& a, const _T&  b) 
{
    // return (a >> 1) + (b >> 1) + (((a & 1) + (b & 1) + 1) >> 1);
    return (a & b) + (((a^b)+1)>>1);    
}


// Local variables:
// mode: c++
// end:
#endif
