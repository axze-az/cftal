#if !defined (__CFTAL_VEC_DEF_MATH_FUNCS_H__)
#define __CFTAL_VEC_DEF_MATH_FUNCS_H__ 1

#define DEF_TRAITS_FUNC(vec_float, vec_int, real_type)  \
    using traits_t=cftal::math::func_traits<vec_float,  \
                                            vec_int>;   \
    using func_t=cftal::math::func<real_type,           \
                                   traits_t>


#define DEF_MATH_FUNCS(ns, vec_float, vec_int, real_type, cbrt_iter)    \
                                                                        \
    ns::vec_float                                                       \
    ns::cbrt(arg<vec_float>::type a)                                    \
    {                                                                   \
        using traits_t=cftal::math::func_traits<vec_float,              \
                                                vec_int>;               \
        using func_t=cftal::math::impl::nth_root<real_type,             \
                                                 traits_t, 3>;          \
        return func_t::v< cbrt_iter >(a);                               \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::frexp(arg<vec_float>::type d, vec_int* pe)                      \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::frexp(d, pe);                                    \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::ldexp(arg<vec_float>::type d, arg<vec_int>::type q)             \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::ldexp(d, q);                                     \
    }                                                                   \
                                                                        \
    ns::vec_int                                                         \
    ns::ilogbp1(arg<vec_float>::type d)                                 \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::ilogb(d);                                        \
    }                                                                   \
                                                                        \
    ns::vec_int                                                         \
    ns::ilogb(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::ilogb(d);                                        \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::exp(arg<vec_float>::type d)                                     \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp(d);                                          \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::expm1(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::expm1(d);                                        \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::exp2(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp2(d);                                         \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::exp10(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::exp10(d);                                        \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::atan2(arg<vec_float>::type x, arg<vec_float>::type y)           \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::atan2(x, y);                                     \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::atan(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::atan(d);                                         \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::asin(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::asin(d);                                         \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::acos(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::acos(d);                                         \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::log(arg<vec_float>::type d)                                     \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::log(d);                                          \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::log1p(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::log1p(d);                                        \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::log10(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::log10(d);                                        \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::log2(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::log2(d);                                         \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::sinh(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::sinh(d);                                         \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::cosh(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::cosh(d);                                         \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
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
    ns::vec_float                                                       \
    ns::sin(arg<vec_float>::type d)                                     \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::sin(d);                                          \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::cos(arg<vec_float>::type d)                                     \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::cos(d);                                          \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::tan(arg<vec_float>::type d)                                     \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::tan(d);                                          \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::asinh(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::asinh(d);                                        \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::acosh(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::acosh(d);                                        \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::atanh(arg<vec_float>::type d)                                   \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::atanh(d);                                        \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::native_exp(arg<vec_float>::type d)                              \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::native_exp(d);                                   \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::native_exp2(arg<vec_float>::type d)                             \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::native_exp2(d);                                  \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::native_expm1(arg<vec_float>::type d)                            \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::native_expm1(d);                                 \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::native_log(arg<vec_float>::type d)                              \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::native_log(d);                                   \
    }                                                                   \
                                                                        \
    void                                                                \
    ns::native_sincos(arg<vec_float>::type d,                           \
                      vec_float* psin, vec_float* pcos)                 \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::native_sincos(d, psin, pcos);                    \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::native_sin(arg<vec_float>::type d)                              \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::native_sin(d);                                   \
    }                                                                   \
                                                                        \
    ns::vec_float                                                       \
    ns::native_cos(arg<vec_float>::type d)                              \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::native_cos(d);                                   \
    }                                                                   \


#define DEF_MATH_POW(ns, vec_float, vec_int, real_type)                 \
    ns::pow(arg<vec_float>::type b, arg<vec_float>::type e)             \
    {                                                                   \
        DEF_TRAITS_FUNC(vec_float, vec_int, real_type);                 \
        return func_t::pow(b, e);                                       \
    }                                                                   \


// Local variables:
// mode: c++
// end:
#endif
