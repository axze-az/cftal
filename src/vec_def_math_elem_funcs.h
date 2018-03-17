//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
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
    ns::rsqrt(arg<vec_float>::type a)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::rsqrt(a);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::cbrt(arg<vec_float>::type a)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::cbrt(a);                                         \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::root12(arg<vec_float>::type a)                                  \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::root12(a);                                       \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::frexp(arg<vec_float>::type d, vec_int* pe)                      \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::frexp(d, pe);                                    \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::ldexp(arg<vec_float>::type d, arg<vec_int>::type q)             \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::ldexp(d, q);                                     \
    }                                                                   \
                                                                        \
    nsr::vec_int                                                        \
    ns::ilogbp1(arg<vec_float>::type d)                                 \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::ilogb(d);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_int                                                        \
    ns::ilogb(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::ilogb(d);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::exp(arg<vec_float>::type d)                                     \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp(d);                                          \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::expm1(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::expm1(d);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::exp2(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp2(d);                                         \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::exp2m1(arg<vec_float>::type d)                                  \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp2m1(d);                                       \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::exp10(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp10(d);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::exp10m1(arg<vec_float>::type d)                                 \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp10m1(d);                                      \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::atan2(arg<vec_float>::type x, arg<vec_float>::type y)           \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::atan2(x, y);                                     \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::atan(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::atan(d);                                         \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::asin(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::asin(d);                                         \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::acos(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::acos(d);                                         \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::log(arg<vec_float>::type d)                                     \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::log(d);                                          \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::log1p(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::log1p(d);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::log10(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::log10(d);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::log2(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::log2(d);                                         \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::sinh(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::sinh(d);                                         \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::cosh(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::cosh(d);                                         \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::tanh(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::tanh(d);                                         \
    }                                                                   \
                                                                        \
    void                                                                \
    ns::sincos(arg<vec_float>::type d,                                  \
               vec_float* psin, vec_float* pcos)                        \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::sincos(d, psin, pcos);                           \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::sin(arg<vec_float>::type d)                                     \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::sin(d);                                          \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::cos(arg<vec_float>::type d)                                     \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::cos(d);                                          \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::tan(arg<vec_float>::type d)                                     \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::tan(d);                                          \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::asinh(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::asinh(d);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::acosh(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::acosh(d);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::atanh(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::atanh(d);                                        \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::exp_mx2(arg<vec_float>::type d)                                 \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp_mx2(d);                                      \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::exp_px2(arg<vec_float>::type d)                                 \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp_px2(d);                                      \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::exp2_mx2(arg<vec_float>::type d)                                \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp2_mx2(d);                                     \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::exp2_px2(arg<vec_float>::type d)                                \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp2_px2(d);                                     \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::exp10_mx2(arg<vec_float>::type d)                               \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp10_mx2(d);                                    \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::exp10_px2(arg<vec_float>::type d)                               \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp10_px2(d);                                    \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::pow(arg<vec_float>::type b, arg<vec_float>::type e)             \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::pow(b, e);                                       \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::nextafter(arg<vec_float>::type b, arg<vec_float>::type e)       \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::nextafter(b, e);                                 \
    }                                                                   \
                                                                        \
    nsr::vec_float                                                      \
    ns::hypot(arg<vec_float>::type b, arg<vec_float>::type e)           \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::hypot(b, e);                                     \
    }


// Local variables:
// mode: c++
// end:
#endif
