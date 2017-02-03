#if !defined (__CFTAL_VEC_DEF_MATH_SPEC_FUNCS_H__)
#define __CFTAL_VEC_DEF_MATH_SPEC_FUNCS_H__ 1


#define DEF_TRAITS_SFUNC(vec_float, vec_int, real_type) \
    using traits_t=cftal::math::func_traits<vec_float,  \
                                            vec_int>;   \
    using func_t=cftal::math::spec_func<real_type,      \
                                        traits_t>

#define DEF_SPEC_FUNCS(ns, vec_float, vec_int, real_type)               \
    ns::vec_float                                                       \
    ns::erf(arg<vec_float>::type d)                                     \
    {                                                                   \
        DEF_TRAITS_SFUNC(vec_float, vec_int, real_type);                \
        return func_t::erf(d);                                          \
    }                                                                   \
                             

#define DEF_SPEC_FUNCS_NO_YET(ns, vec_float, vec_int, real_type)        \
ns::vec_float                                                           \
    ns::erfc(arg<vec_float>::type d)                                    \
    {                                                                   \
        DEF_TRAITS_SFUNC(vec_float, vec_int, real_type);                \
        return func_t::erfc(d);                                         \
    }                                                                   
                                                                        

// Local variables:
// mode: c++
// end:
#endif
