//
// Copyright (C) 2010-2023 Axel Zeuner
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
#if !defined (__CFTAL_VEC_DEF_MATH_ELEM_FUNCS_H__)
#define __CFTAL_VEC_DEF_MATH_ELEM_FUNCS_H__ 1


#define DEF_TRAITS_FUNC(vec_float, vec_int, real_type)  \
    using traits_t=cftal::math::func_traits<vec_float,  \
                                            vec_int>;   \
    using func_t=cftal::math::elem_func<real_type,      \
                                        traits_t>


#define DEF_ELEM_FUNCS(nsr, ns, vec_float, vec_int, real_type)          \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::rsqrt(arg<vec_float>::type a)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::rsqrt(a);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::cbrt(arg<vec_float>::type a)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::cbrt(a);                                         \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::rcbrt(arg<vec_float>::type a)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::rcbrt(a);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::root12(arg<vec_float>::type a)                                  \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::root12(a);                                       \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::frexp(arg<vec_float>::type d, vec_int* pe)                      \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::frexp(d, pe);                                    \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::ldexp(arg<vec_float>::type d, arg<vec_int>::type q)             \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::ldexp(d, q);                                     \
    }                                                                   \
                                                                        \
    nsr::vec_int                                                        \
    __attribute__((__flatten__))                                        \
    ns::ilogbp1(arg<vec_float>::type d)                                 \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::ilogb(d);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_int                                                        \
    __attribute__((__flatten__))                                        \
    ns::ilogb(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::ilogb(d);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::exp(arg<vec_float>::type d)                                     \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp(d);                                          \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::expm1(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::expm1(d);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::exp2(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp2(d);                                         \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::exp2m1(arg<vec_float>::type d)                                  \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp2m1(d);                                       \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::exp10(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp10(d);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::exp10m1(arg<vec_float>::type d)                                 \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp10m1(d);                                      \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::atan2(arg<vec_float>::type x, arg<vec_float>::type y)           \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::atan2(x, y);                                     \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::atan(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::atan(d);                                         \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::asin(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::asin(d);                                         \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::acos(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::acos(d);                                         \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::log(arg<vec_float>::type d)                                     \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::log(d);                                          \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::log1p(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::log1p(d);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::log10(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::log10(d);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::log10p1(arg<vec_float>::type d)                                 \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::log10p1(d);                                      \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::log2(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::log2(d);                                         \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::log2p1(arg<vec_float>::type d)                                  \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::log2p1(d);                                       \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::sinh(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::sinh(d);                                         \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::cosh(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::cosh(d);                                         \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::tanh(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::tanh(d);                                         \
    }                                                                   \
                                                                        \
    void                                                                \
    __attribute__((__flatten__))                                        \
    ns::sincos(arg<vec_float>::type d,                                  \
               vec_float* psin, vec_float* pcos)                        \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::sincos(d, psin, pcos);                           \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::sin(arg<vec_float>::type d)                                     \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::sin(d);                                          \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::cos(arg<vec_float>::type d)                                     \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::cos(d);                                          \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::tan(arg<vec_float>::type d)                                     \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::tan(d);                                          \
    }                                                                   \
                                                                        \
    void                                                                \
    __attribute__((__flatten__))                                        \
    ns::sinpicospi(arg<vec_float>::type d,                              \
                   vec_float* psin, vec_float* pcos)                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::sinpicospi(d, psin, pcos);                       \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::sinpi(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::sinpi(d);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::cospi(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::cospi(d);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::tanpi(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::tanpi(d);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::asinh(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::asinh(d);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::acosh(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::acosh(d);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::atanh(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::atanh(d);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::exp_mx2(arg<vec_float>::type d)                                 \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp_mx2(d);                                      \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::exp_px2(arg<vec_float>::type d)                                 \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp_px2(d);                                      \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::exp2_mx2(arg<vec_float>::type d)                                \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp2_mx2(d);                                     \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::exp2_px2(arg<vec_float>::type d)                                \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp2_px2(d);                                     \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::exp10_mx2(arg<vec_float>::type d)                               \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp10_mx2(d);                                    \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::exp10_px2(arg<vec_float>::type d)                               \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp10_px2(d);                                    \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::sig(arg<vec_float>::type d)                                     \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::sig(d);                                          \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::pow(arg<vec_float>::type b, arg<vec_float>::type e)             \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::pow(b, e);                                       \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::pow(arg<vec_float>::type b, arg<vec_int>::type e)               \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::pow(b, e);                                       \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::rootn(arg<vec_float>::type b, arg<vec_int>::type e)             \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::rootn(b, e);                                     \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::nextafter(arg<vec_float>::type b, arg<vec_float>::type e)       \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::nextafter(b, e);                                 \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::hypot(arg<vec_float>::type b, arg<vec_float>::type e)           \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::hypot(b, e);                                     \
    }


#define DEF_ELEM_FUNCS_F16(nsr, ns, vec_float, vec_int, real_type)      \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::sqrt(arg<vec_float>::type a)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::sqrt(a);                                         \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::rsqrt(arg<vec_float>::type a)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::rsqrt(a);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::exp(arg<vec_float>::type a)                                     \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp(a);                                          \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    __attribute__((__flatten__))                                        \
    ns::expm1(arg<vec_float>::type a)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::expm1(a);                                        \
    }                                                                   \


// Local variables:
// mode: c++
// end:
#endif
