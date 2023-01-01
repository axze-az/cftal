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
