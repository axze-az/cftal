//
// Copyright Axel Zeuner 2010-2021. Use, modification and
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

#define DEF_HALF_FUNCS(nsr, ns, vec_float, vec_int, real_type)  \
                                                                \
    nsr::vec_float                                              \
    __attribute__((__flatten__))                                \
    ns::cos(arg<vec_float>::type a)                             \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::half_cos(a);                             \
    }                                                           \
                                                                \
    nsr::vec_float                                              \
    __attribute__((__flatten__))                                \
    ns::exp(arg<vec_float>::type a)                             \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::half_exp(a);                             \
    }                                                           \
                                                                \
    nsr::vec_float                                              \
    __attribute__((__flatten__))                                \
    ns::exp2(arg<vec_float>::type d)                            \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::half_exp2(d);                            \
    }                                                           \
                                                                \
    nsr::vec_float                                              \
    __attribute__((__flatten__))                                \
    ns::exp10(arg<vec_float>::type d)                           \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::half_exp10(d);                           \
    }                                                           \
                                                                \
    nsr::vec_float                                              \
    __attribute__((__flatten__))                                \
    ns::log(arg<vec_float>::type d)                             \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::half_log(d);                             \
    }                                                           \
                                                                \
    nsr::vec_float                                              \
    __attribute__((__flatten__))                                \
    ns::log2(arg<vec_float>::type d)                            \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::half_log2(d);                            \
    }                                                           \
                                                                \
    nsr::vec_float                                              \
    __attribute__((__flatten__))                                \
    ns::log10(arg<vec_float>::type d)                           \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::half_log10(d);                           \
    }                                                           \
                                                                \
    nsr::vec_float                                              \
    __attribute__((__flatten__))                                \
    ns::rsqrt(arg<vec_float>::type d)                           \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::half_rsqrt(d);                           \
    }                                                           \
                                                                \
    nsr::vec_float                                              \
    __attribute__((__flatten__))                                \
    ns::sqrt(arg<vec_float>::type d)                            \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::half_sqrt(d);                            \
    }                                                           \
                                                                \
    nsr::vec_float                                              \
    __attribute__((__flatten__))                                \
    ns::sin(arg<vec_float>::type d)                             \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::half_sin(d);                             \
    }                                                           \
                                                                \
    nsr::vec_float                                              \
    __attribute__((__flatten__))                                \
    ns::tan(arg<vec_float>::type d)                             \
    {                                                           \
        DEF_TRAITS_HFUNC(vec_float, vec_int, real_type);        \
        return func_t::half_tan(d);                             \
    }                                                           \


// Local variables:
// mode: c++
// end:
#endif
