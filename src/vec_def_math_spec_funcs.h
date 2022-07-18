//
// Copyright (C) 2010-2022 Axel Zeuner
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
    ns::j0(arg<vec_float>::type d)                              \
    {                                                           \
        DEF_TRAITS_SFUNC(vec_float, vec_int, real_type);        \
        return func_t::j0(d);                                   \
    }                                                           \
                                                                \
    nsr::vec_float                                              \
    __attribute__((__flatten__))                                \
    ns::j1(arg<vec_float>::type d)                              \
    {                                                           \
        DEF_TRAITS_SFUNC(vec_float, vec_int, real_type);        \
        return func_t::j1(d);                                   \
    }                                                           \
                                                                \
    nsr::vec_float                                              \
    __attribute__((__flatten__))                                \
    ns::y0(arg<vec_float>::type d)                              \
    {                                                           \
        DEF_TRAITS_SFUNC(vec_float, vec_int, real_type);        \
        return func_t::y0(d);                                   \
    }                                                           \
                                                                \
    nsr::vec_float                                              \
    __attribute__((__flatten__))                                \
    ns::y1(arg<vec_float>::type d)                              \
    {                                                           \
        DEF_TRAITS_SFUNC(vec_float, vec_int, real_type);        \
        return func_t::y1(d);                                   \
    }


#define DEF_SLOW_SPEC_FUNCS(nsr, ns, vec_float, vec_int, real_type)  \
    nsr::vec_float                                                   \
    __attribute__((__flatten__))                                     \
    ns::lgamma(arg<vec_float>::type d, vec_int * i)                  \
    {                                                                \
        DEF_TRAITS_SFUNC(vec_float, vec_int, real_type);             \
        return func_t::lgamma(d, i);                                 \
    }                                                                \
    nsr::vec_float                                                   \
    __attribute__((__flatten__))                                     \
    ns::tgamma(arg<vec_float>::type d)                               \
    {                                                                \
        DEF_TRAITS_SFUNC(vec_float, vec_int, real_type);             \
        return func_t::tgamma(d);                                    \
    }

// Local variables:
// mode: c++
// end:
#endif
