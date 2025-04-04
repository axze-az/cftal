//
// Copyright (C) 2010-2025 Axel Zeuner
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
#if !defined (__CFTAL_VEC_MATH_FUNCS_H__)
#define __CFTAL_VEC_MATH_FUNCS_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/f16_t.h>
#include <cftal/type_traits.h>
#include <cftal/vec_spec.h>
#include <cftal/vec_cvt.h>

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
                  typename _VEC_INT_MASK,
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

    template <std::size_t _BITS>
    double
    round_to_nearest_even_last_bits(const double& v);

    template <std::size_t _BITS>
    float
    round_to_nearest_even_last_bits(const float& v);

    template <std::size_t _BITS>
    f16_t
    round_to_nearest_even_last_bits(const f16_t& v);

    // round the last _BITS to zero
    template <std::size_t _BITS, typename _T, std::size_t _N>
    vec<_T, _N>
    round_to_zero_last_bits(const vec<_T, _N>& v);

    template <std::size_t _BITS>
    double
    round_to_zero_last_bits(const double& v);

    template <std::size_t _BITS>
    float
    round_to_zero_last_bits(const float& v);

    template <std::size_t _BITS>
    f16_t
    round_to_zero_last_bits(const f16_t& v);

    void
    split_f64_to_f32pair(const double& s,
                         float& h, float& l);

    template <size_t _N>
    void
    split_f64_to_f32pair(const vec<double, _N>& s,
                         vec<float, _N>& h, vec<float, _N>& l);

    template <size_t _N>
    void
    split_f64_to_f32pair_rne_hi(const vec<double, _N>& s,
                                vec<float, _N>& h, vec<float, _N>& l);

    template <size_t _N>
    void
    split_f64_to_f32pair_rz_hi(const vec<double, _N>& s,
                               vec<float, _N>& h, vec<float, _N>& l);

    double
    combine_f32pair_to_f64(const float& h, const float& l);

    template <size_t _N>
    vec<double, _N>
    combine_f32pair_to_f64(const vec<float, _N>& h, const vec<float, _N>& l);
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
          typename _VEC_INT_MASK,
          std::size_t _BITS>
_VEC_FLOAT
cftal::impl::round_to_nearest_even_last_bits(const _VEC_FLOAT& v)
{
    static_assert(sizeof(_FLOAT) == sizeof(_INT), "int of wrong size");
    static_assert(_BITS>0 && _BITS < sizeof(_FLOAT)*8);

    using vi_t = _VEC_INT;
    using vmi_t = _VEC_INT_MASK;
    using int_type = _INT;
    using vf_type = _VEC_FLOAT;
    // last bit to keep
    constexpr const int_type bk= (1LL << (_BITS));
    // first bit to round away:
    constexpr const int_type br= (1LL << (_BITS-1));
    // mask of the bits to round away:
    constexpr const int_type trailing_mask= bk-1L;
    // mask of the bits to keep
    constexpr const int_type mask=~trailing_mask;
#if 1
    // rounding bias
    constexpr const int_type rnd_bias= br - 1L;
    vi_t i=as<vi_t>(v);
    vi_t lbit = i & bk;
    vmi_t is_lbit_set = lbit == bk;
    vi_t i_br = i + br;
    vi_t i_bias= i + rnd_bias;
    i = select(is_lbit_set, i_br, i_bias);
    i &= mask;
#else
    vi_t i=as<vi_t>(v);
    vi_t rbits=i & trailing_mask;
    vi_t lbit= i & bk;
    constexpr const int_type z=0LL;
    vmi_t sel_zero_offs= (rbits == br) & (lbit == z);
    // vi_t offs=select_zero_or_val(sel_zero_offs, v_br);
    // i += offs;
    vi_t i_offs= i + br;
    i = select(sel_zero_offs, i, i_offs);
    i &= mask;
#endif
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
        select_t<std::is_same_v<_T, double>,
                 int64_t,
                 select_t<std::is_same_v<_T, float>,
                          int32_t,
                          select_t<std::is_same_v<_T, f16_t>,
                                   int16_t,
                                   _T>
                          >
                  >;
    using vi_type = vec<int_type, _N>;
    using vmi_type = typename vec<int_type, _N>::mask_type;
    return impl::round_to_nearest_even_last_bits<vec<_T, _N>, _T,
                                                 vi_type,
                                                 int_type,
                                                 vmi_type,
                                                 _BITS>(v);
}

template <std::size_t _BITS>
inline
double
cftal::round_to_nearest_even_last_bits(const double& x)
{
    return impl::round_to_nearest_even_last_bits<double, double,
                                                 int64_t, int64_t, bool,
                                                 _BITS>(x);
}

template <std::size_t _BITS>
inline
float
cftal::round_to_nearest_even_last_bits(const float& x)
{
    return impl::round_to_nearest_even_last_bits<float, float,
                                                 int32_t, int32_t, bool,
                                                 _BITS>(x);
}

template <std::size_t _BITS>
inline
cftal::f16_t
cftal::round_to_nearest_even_last_bits(const f16_t& x)
{
    return impl::round_to_nearest_even_last_bits<f16_t, f16_t,
                                                 int16_t, int16_t, bool,
                                                 _BITS>(x);
}

template <std::size_t _BITS, typename _T, std::size_t _N>
cftal::vec<_T, _N>
cftal::round_to_zero_last_bits(const vec<_T, _N>& v)
{
    static_assert(_BITS>0 && _BITS < sizeof(_T)*8);

    using int_type =
        select_t<std::is_same_v<_T, double>,
                 int64_t,
                 select_t<std::is_same_v<_T, float>,
                          int32_t,
                          select_t<std::is_same_v<_T, f16_t>,
                                   int16_t,
                                   _T>
                          >
                  >;
    return impl::round_to_zero_last_bits<vec<_T, _N>, _T,
                                         vec<int_type, _N>, int_type,
                                         _BITS>(v);
}

template <std::size_t _BITS>
inline
double
cftal::round_to_zero_last_bits(const double& x)
{
    return impl::round_to_zero_last_bits<double, double,
                                         int64_t, int64_t,
                                         _BITS>(x);
}

template <std::size_t _BITS>
inline
float
cftal::round_to_zero_last_bits(const float& x)
{
    return impl::round_to_zero_last_bits<float, float,
                                         int32_t, int32_t,
                                         _BITS>(x);
}

template <std::size_t _BITS>
inline
cftal::f16_t
cftal::round_to_zero_last_bits(const f16_t& x)
{
    return impl::round_to_zero_last_bits<f16_t, f16_t,
                                         int16_t, int16_t,
                                         _BITS>(x);
}

inline
void
cftal::
split_f64_to_f32pair(const double& s,
                     float& h, float& l)
{
    float th = float(s);
    double dh = float(th);
    double dl = s - dh;
    h = th;
    l = float(dl);
}

template <cftal::size_t _N>
void
cftal::
split_f64_to_f32pair(const vec<double, _N>& s,
                     vec<float, _N>& h, vec<float, _N>& l)
{
    using vf_type = vec<float, _N>;
    using vhf_type = vec<double, _N>;
    vf_type th = cvt<vf_type>(s);
    vhf_type dh = cvt<vhf_type>(th);
    vhf_type dl = s - dh;
    h = th;
    l = cvt<vf_type>(dl);
}

template <cftal::size_t _N>
void cftal::
split_f64_to_f32pair_rne_hi(const vec<double, _N>& s,
                            vec<float, _N>& h, vec<float, _N>& l)
{
    using vf_type = vec<float, _N>;
    using vhf_type = vec<double, _N>;
    vhf_type dh = round_to_nearest_even_last_bits<29>(s);
    vhf_type dl = s - dh;
    h = cvt<vf_type>(dh);
    l = cvt<vf_type>(dl);
}

template <cftal::size_t _N>
void cftal::
split_f64_to_f32pair_rz_hi(const vec<double, _N>& s,
                           vec<float, _N>& h, vec<float, _N>& l)
{
    using vf_type = vec<float, _N>;
    using vhf_type = vec<double, _N>;
    vhf_type dh = round_to_zero_last_bits<29>(s);
    vhf_type dl = s - dh;
    h = cvt<vf_type>(dh);
    l = cvt<vf_type>(dl);
}

inline
double
cftal::
combine_f32pair_to_f64(const float& h, const float& l)
{
    double dh = double(h);
    double dl = double(l);
    return dh + dl;
}

template <cftal::size_t _N>
cftal::vec<double, _N>
cftal::
combine_f32pair_to_f64(const vec<float, _N>& h, const vec<float, _N>& l)
{
    using vhf_type = vec<double, _N>;
    vhf_type dh = cvt<vhf_type>(h);
    vhf_type dl = cvt<vhf_type>(l);
    return dh + dl;
}



// Local variables:
// mode: c++
// end:
#endif
