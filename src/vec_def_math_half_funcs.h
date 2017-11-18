//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_VEC_DEF_MATH_HALF_FUNCS_H__)
#define __CFTAL_VEC_DEF_MATH_HALF_FUNCS_H__ 1


#define DEF_TRAITS_HFUNC(vec_float, vec_int, real_type) \
    using traits_t=cftal::math::func_traits<vec_float,  \
                                            vec_int>;   \
    using func_t=cftal::math::half_func<real_type,      \
                                        traits_t>

#define DEF_HALF_FUNCS(ns, vec_float, vec_int, real_type)       \
                                                                \
    ns::vec_float                                               \
    ns::cos(arg<vec_float>::type a)                             \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::cos(a);                                  \
    }                                                           \
                                                                \
    ns::vec_float                                               \
    ns::exp(arg<vec_float>::type a)                             \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::exp(a);                                  \
    }                                                           \
                                                                \
    ns::vec_float                                               \
    ns::exp2(arg<vec_float>::type d)                            \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::exp2(d);                                 \
    }                                                           \
                                                                \
    ns::vec_float                                               \
    ns::exp10(arg<vec_float>::type d)                           \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::exp10(d);                                \
    }                                                           \
                                                                \
    ns::vec_float                                               \
    ns::log(arg<vec_float>::type d)                             \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::log(d);                                  \
    }                                                           \
                                                                \
    ns::vec_float                                               \
    ns::log2(arg<vec_float>::type d)                            \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::log2(d);                                 \
    }                                                           \
                                                                \
    ns::vec_float                                               \
    ns::log10(arg<vec_float>::type d)                           \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::log10(d);                                \
    }                                                           \
                                                                \
    ns::vec_float                                               \
    ns::rsqrt(arg<vec_float>::type d)                           \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::rsqrt(d);                                \
    }                                                           \
                                                                \
    ns::vec_float                                               \
    ns::sin(arg<vec_float>::type d)                             \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::sin(d);                                  \
    }                                                           \
                                                                \
    ns::vec_float                                               \
    ns::tan(arg<vec_float>::type d)                             \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::tan(d);                                  \
    }                                                           \


// Local variables:
// mode: c++
// end:
#endif
