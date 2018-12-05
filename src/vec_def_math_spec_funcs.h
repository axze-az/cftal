//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_VEC_DEF_MATH_SPEC_FUNCS_H__)
#define __CFTAL_VEC_DEF_MATH_SPEC_FUNCS_H__ 1


#define DEF_TRAITS_SFUNC(vec_float, vec_int, real_type) \
    using traits_t=cftal::math::func_traits<vec_float,  \
                                            vec_int>;   \
    using func_t=cftal::math::spec_func<real_type,      \
                                        traits_t>

#define DEF_SPEC_FUNCS(nsr, ns, vec_float, vec_int, real_type)  \
    nsr::vec_float                                              \
    __attribute__((__flatten__))                                \
    ns::erf(arg<vec_float>::type d)                             \
    {                                                           \
        DEF_TRAITS_SFUNC(vec_float, vec_int, real_type);        \
        return func_t::erf(d);                                  \
    }                                                           \
                                                                \
    nsr::vec_float                                              \
    __attribute__((__flatten__))                                \
    ns::erfc(arg<vec_float>::type d)                            \
    {                                                           \
        DEF_TRAITS_SFUNC(vec_float, vec_int, real_type);        \
        return func_t::erfc(d);                                 \
    }                                                           \
                                                                \
    nsr::vec_float                                              \
    __attribute__((__flatten__))                                \
    ns::tgamma(arg<vec_float>::type d)                          \
    {                                                           \
        DEF_TRAITS_SFUNC(vec_float, vec_int, real_type);        \
        return func_t::tgamma(d);                               \
    }                                                           \
    nsr::vec_float                                              \
    __attribute__((__flatten__))                                \
    ns::lgamma(arg<vec_float>::type d, vec_int * i)             \
    {                                                           \
        DEF_TRAITS_SFUNC(vec_float, vec_int, real_type);        \
        return func_t::lgamma(d, i);                            \
    }
    

// Local variables:
// mode: c++
// end:
#endif
