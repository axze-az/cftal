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


    namespace impl {
        // round the last _BITS to nearest, ties to even
        template <typename _VEC_FLOAT, typename _FLOAT,
                  typename _VEC_INT, typename _INT,
                  std::size_t _BITS>
        _VEC_FLOAT
        round_to_nearest_even_last_bits(const _VEC_FLOAT& v);

        // round the last _BITS to zero
        template <typename _VEC_FLOAT, typename _FLOAT,
                  typename _VEC_INT, typename _INT,
                  std::size_t _BITS>
        _VEC_FLOAT
        round_to_zero_last_bits(const _VEC_FLOAT& v);
    }

    // round the last _BITS to nearest, ties to even
    template <std::size_t _BITS, typename _T, std::size_t _N>
    vec<_T, _N>
    round_to_nearest_even_last_bits(const  vec<_T, _N>& v);

    // round the last _BITS to zero
    template <std::size_t _BITS, typename _T, std::size_t _N>
    vec<_T, _N>
    round_to_zero_last_bits(const vec<_T, _N>& v);

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

// round the last _BITS to nearest, ties to even
template <typename _VEC_FLOAT, typename _FLOAT,
          typename _VEC_INT, typename _INT,
          std::size_t _BITS>
_VEC_FLOAT
cftal::impl::round_to_nearest_even_last_bits(const _VEC_FLOAT& v)
{
    static_assert(sizeof(_FLOAT) == sizeof(_INT), "int of wrong size");
    static_assert(_BITS>0 && _BITS < sizeof(_FLOAT)*8);

    using vi_t = _VEC_INT;
    using vmi_t = typename _VEC_INT::mask_type;
    using int_type = _INT;
    using vf_type = _VEC_FLOAT;
    // first bit to round away:
    constexpr const int_type br= (1LL << (_BITS-1));
    // last bit to keep
    constexpr const int_type bk= (1LL << (_BITS));
    // mask of the bits to round away:
    constexpr const int_type trailing_mask= bk-1L;
    // mask of the bits to keep
    constexpr const int_type mask=~trailing_mask;
    vi_t i=as<vi_t>(v);
    vi_t rbits=i & trailing_mask;
    vi_t lbit= i & bk;
    constexpr const int_type z=0LL;
    const vi_t v_br=br;
    vmi_t sel_zero_offs= (rbits == v_br) & (lbit==z);
    vi_t offs=select_zero_or_val(sel_zero_offs, v_br);
    i += offs;
    i &= mask;
    vf_type r=as<vf_type>(i);
    return r;
}

// round the last _BITS to zero
template <typename _VEC_FLOAT, typename _FLOAT,
          typename _VEC_INT, typename _INT,
          std::size_t _BITS>
_VEC_FLOAT
cftal::impl::round_to_zero_last_bits(const _VEC_FLOAT& v)
{
    static_assert(sizeof(_FLOAT) == sizeof(_INT), "int of wrong size");
    static_assert(_BITS>0 && _BITS < sizeof(_FLOAT)*8);

    using vi_t = _VEC_INT;
    using int_type = _INT;
    using vf_type = _VEC_FLOAT;
    // last bit to keep
    constexpr const int_type bk= (1LL << (_BITS));
    // mask of the bits to round away:
    constexpr const int_type trailing_mask= bk-1L;
    // mask of the bits to keep
    constexpr const int_type mask=~trailing_mask;
    vi_t i=as<vi_t>(v);
    i &= mask;
    vf_type r=as<vf_type>(i);
    return r;

}

template <std::size_t _BITS, typename _T, std::size_t _N>
cftal::vec<_T, _N>
cftal::round_to_nearest_even_last_bits(const  vec<_T, _N>& v)
{
    static_assert(_BITS>0 && _BITS < sizeof(_T)*8);

    using int_type =
        std::conditional_t<
            std::is_same_v<_T, double>,
                           int64_t,
                           std::conditional_t<std::is_same_v<_T, float>,
                                              int32_t,
                                              _T> >;
    return impl::round_to_nearest_even_last_bits<vec<_T, _N>, _T,
                                                 vec<int_type, _N>, int_type,
                                                 _BITS>(v);
#if 0
    using vi_t = vec<int_type, _N>;
    using vmi_t = typename vec<int_type, _N>::mask_type;
    // first bit to round away:
    constexpr const int_type br= (1LL << (_BITS-1));
    // last bit to keep
    constexpr const int_type bk= (1LL << (_BITS));
    // mask of the bits to round away:
    constexpr const int_type trailing_mask= bk-1L;
    // mask of the bits to keep
    constexpr const int_type mask=~trailing_mask;
    vi_t i=as<vi_t>(v);
    vi_t rbits=i & trailing_mask;
    vi_t lbit= i & bk;
    const vi_t v_z=0LL;
    const vi_t v_br=br;
    vmi_t sel_zero_offs= (rbits == v_br) & (lbit==v_z);
    vi_t offs=select_zero_or_val(sel_zero_offs, v_br);
    i += offs;
    i &= mask;
    vec<_T, _N> r=as<vec<_T, _N> >(i);
    return r;
#endif
}

template <std::size_t _BITS, typename _T, std::size_t _N>
cftal::vec<_T, _N>
cftal::round_to_zero_last_bits(const vec<_T, _N>& v)
{
    static_assert(_BITS>0 && _BITS < sizeof(_T)*8);

    using int_type =
        std::conditional_t<
            std::is_same_v<_T, double>,
                           int64_t,
                           std::conditional_t<std::is_same_v<_T, float>,
                                              int32_t,
                                              _T> >;
    return impl::round_to_zero_last_bits<vec<_T, _N>, _T,
                                         vec<int_type, _N>, int_type,
                                         _BITS>(v);
#if 0
    using vi_t = vec<int_type, _N>;
    // last bit to keep
    constexpr const int_type bk= (1LL << (_BITS));
    // mask of the bits to round away:
    constexpr const int_type trailing_mask= bk-1L;
    // mask of the bits to keep
    constexpr const int_type mask=~trailing_mask;
    vi_t i=as<vi_t>(v);
    i &= mask;
    vec<_T, _N> r=as<vec<_T, _N> >(i);
    return r;
#endif
}

// Local variables:
// mode: c++
// end:
#endif
