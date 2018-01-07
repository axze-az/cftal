//
// Copyright Axel Zeuner 2010-2018. Use, modification and
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
    ns::half_math::cos(arg<vec_float>::type a)                  \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::half_cos(a);                             \
    }                                                           \
                                                                \
    ns::vec_float                                               \
    ns::half_math::exp(arg<vec_float>::type a)                  \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::half_exp(a);                             \
    }                                                           \
                                                                \
    ns::vec_float                                               \
    ns::half_math::exp2(arg<vec_float>::type d)                 \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::half_exp2(d);                            \
    }                                                           \
                                                                \
    ns::vec_float                                               \
    ns::half_math::exp10(arg<vec_float>::type d)                \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::half_exp10(d);                           \
    }                                                           \
                                                                \
    ns::vec_float                                               \
    ns::half_math::log(arg<vec_float>::type d)                  \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::half_log(d);                             \
    }                                                           \
                                                                \
    ns::vec_float                                               \
    ns::half_math::log2(arg<vec_float>::type d)                 \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::half_log2(d);                            \
    }                                                           \
                                                                \
    ns::vec_float                                               \
    ns::half_math::log10(arg<vec_float>::type d)                \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::half_log10(d);                           \
    }                                                           \
                                                                \
    ns::vec_float                                               \
    ns::half_math::rsqrt(arg<vec_float>::type d)                \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::half_rsqrt(d);                           \
    }                                                           \
                                                                \
    ns::vec_float                                               \
    ns::half_math::sqrt(arg<vec_float>::type d)                 \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::half_sqrt(d);                            \
    }                                                           \
                                                                \
    ns::vec_float                                               \
    ns::half_math::sin(arg<vec_float>::type d)                  \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::half_sin(d);                             \
    }                                                           \
                                                                \
    ns::vec_float                                               \
    ns::half_math::tan(arg<vec_float>::type d)                  \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::half_tan(d);                             \
    }                                                           \


// Local variables:
// mode: c++
// end:
#endif
