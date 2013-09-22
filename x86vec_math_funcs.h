#if !defined (__X86VEC_MATH_FUNCS_H__)
#define __X86VEC_MATH_FUNCS_H__ 1

#define DEF_TRAITS_FUNC(vec_float, vec_int, real_type)          \
        using traits_t=cftal::math::func_traits<vec_float,      \
                                                vec_int>;       \
        using func_t=cftal::math::func<real_type,               \
                                       int32_t,                 \
                                       traits_t>


#define DEF_MATH_FUNCS(ns, vec_float, vec_int, real_type, cbrt_iter)    \
                                                                        \
        ns::vec_float							\
        ns::cbrt(arg<vec_float>::type a)				\
        {                                                               \
                using traits_t=cftal::math::func_traits<vec_float,      \
                                                        vec_int>;       \
                using func_t=cftal::math::impl::nth_root<real_type,     \
                                                         int32_t,       \
                                                         traits_t, 3>;  \
                return func_t::v< cbrt_iter >(a);                       \
        }                                                               \
                                                                        \
        ns::vec_float							\
        ns::frexp(arg<vec_float>::type d, vec_int* pe)			\
        {                                                               \
                DEF_TRAITS_FUNC(vec_float, vec_int, real_type);         \
                return func_t::frexp(d, pe);                            \
        }                                                               \
                                                                        \
        ns::vec_float							\
        ns::ldexp(arg<vec_float>::type d, arg<vec_int>::type q)		\
        {                                                               \
                DEF_TRAITS_FUNC(vec_float, vec_int, real_type);         \
                return func_t::ldexp(d, q);                             \
        }                                                               \
                                                                        \
        ns::vec_int							\
        ns::ilogbp1(arg<vec_float>::type d)				\
        {                                                               \
                DEF_TRAITS_FUNC(vec_float, vec_int, real_type);         \
                return func_t::ilogb(d);                                \
        }                                                               \
                                                                        \
        ns::vec_int							\
        ns::ilogb(arg<vec_float>::type d)				\
        {                                                               \
                DEF_TRAITS_FUNC(vec_float, vec_int, real_type);         \
                return func_t::ilogb(d);                                \
        }                                                               \
                                                                        \
        ns::vec_float							\
        ns::exp(arg<vec_float>::type d)					\
        {                                                               \
                DEF_TRAITS_FUNC(vec_float, vec_int, real_type);         \
                return func_t::exp(d);                                  \
        }                                                               \
                                                                        \
        ns::vec_float							\
        ns::expm1(arg<vec_float>::type d)				\
        {                                                               \
                DEF_TRAITS_FUNC(vec_float, vec_int, real_type);         \
                return func_t::expm1(d);                                \
        }                                                               \
                                                                        \
        ns::vec_float							\
        ns::log(arg<vec_float>::type d)					\
        {                                                               \
                DEF_TRAITS_FUNC(vec_float, vec_int, real_type);         \
                return func_t::log(d);                                  \
        }                                                               \
                                                                        \
        ns::vec_float							\
        ns::pow(arg<vec_float>::type b, arg<vec_float>::type e)		\
        {                                                               \
                DEF_TRAITS_FUNC(vec_float, vec_int, real_type);         \
                return func_t::pow(b, e);                               \
        }                                                               \
                                                                        \
        ns::vec_float							\
        ns::sinh(arg<vec_float>::type d)				\
        {                                                               \
                DEF_TRAITS_FUNC(vec_float, vec_int, real_type);         \
                return func_t::sinh(d);                                 \
        }                                                               \
                                                                        \
        ns::vec_float							\
        ns::cosh(arg<vec_float>::type d)				\
        {                                                               \
                DEF_TRAITS_FUNC(vec_float, vec_int, real_type);         \
                return func_t::cosh(d);                                 \
        }                                                               \
                                                                        \
        void                                                            \
        ns::sincos(arg<vec_float>::type d,				\
		   vec_float* psin, vec_float* pcos)			\
        {                                                               \
                DEF_TRAITS_FUNC(vec_float, vec_int, real_type);         \
                return func_t::sincos(d, psin, pcos);                   \
        }                                                               \
                                                                        \
        ns::vec_float							\
        ns::sin(arg<vec_float>::type d)					\
        {                                                               \
                DEF_TRAITS_FUNC(vec_float, vec_int, real_type);         \
                return func_t::sin(d);                                  \
        }                                                               \
                                                                        \
        ns::vec_float							\
        ns::cos(arg<vec_float>::type d)					\
        {                                                               \
                DEF_TRAITS_FUNC(vec_float, vec_int, real_type);         \
                return func_t::cos(d);                                  \
        }                                                               \
                                                                        \
        ns::vec_float							\
        ns::tan(arg<vec_float>::type d)					\
        {                                                               \
                DEF_TRAITS_FUNC(vec_float, vec_int, real_type);         \
                return func_t::tan(d);                                  \
        }                                                               \
                                                                        \
        ns::vec_float							\
        ns::cot(arg<vec_float>::type d)					\
        {                                                               \
                DEF_TRAITS_FUNC(vec_float, vec_int, real_type);         \
                return func_t::cot(d);                                  \
        }                                                               \
                                                                        \
        void                                                            \
        ns::native_sincos(arg<vec_float>::type d,			\
			  vec_float* psin, vec_float* pcos)		\
        {                                                               \
                DEF_TRAITS_FUNC(vec_float, vec_int, real_type);         \
                return func_t::native_sincos(d, psin, pcos);            \
        }                                                               \
                                                                        \
        ns::vec_float							\
        ns::native_sin(arg<vec_float>::type d)				\
        {                                                               \
                DEF_TRAITS_FUNC(vec_float, vec_int, real_type);         \
                return func_t::native_sin(d);                           \
        }                                                               \
                                                                        \
        ns::vec_float							\
        ns::native_cos(arg<vec_float>::type d)				\
        {                                                               \
                DEF_TRAITS_FUNC(vec_float, vec_int, real_type);         \
                return func_t::native_cos(d);                           \
        }                                                               \
                                                                        \
        ns::vec_float							\
        ns::native_tan(arg<vec_float>::type d)				\
        {                                                               \
                DEF_TRAITS_FUNC(vec_float, vec_int, real_type);         \
                return func_t::native_tan(d);                           \
        }                                                               \
                                                                        \
        ns::vec_float							\
        ns::native_cot(arg<vec_float>::type d)				\
        {                                                               \
                DEF_TRAITS_FUNC(vec_float, vec_int, real_type);         \
                return func_t::native_cot(d);                           \
        }


// Local variables:
// mode: c++
// end:
#endif
