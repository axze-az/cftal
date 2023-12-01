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
#if !defined (__CFTAL_VEC_F16_H__)
#define __CFTAL_VEC_F16_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
// this file should be included in vec_spec.h:
#include <cftal/vxf16.h>

#define V2F16_FUNCS 1
#define V4F16_FUNCS                                                     \
    ((V4F16_SPECIALIZED>0) || ((V2F16_SPECIALIZED>0) && (V2S16_SPECIALIZED>0)))
#define V8F16_FUNCS                                                     \
    ((V8F16_SPECIALIZED>0) || ((V4F16_SPECIALIZED>0) && (V4S16_SPECIALIZED>0)))
#define V16F16_FUNCS                                                    \
    ((V16F16_SPECIALIZED>0) || ((V8F16_SPECIALIZED>0) && (V8S16_SPECIALIZED>0)))

namespace cftal {

    using v1f16 = vec<f16_t, 1>;
    using v2f16 = vec<f16_t, 2>;
    using v4f16 = vec<f16_t, 4>;
    using v8f16 = vec<f16_t, 8>;
    using v16f16 = vec<f16_t, 16>;

    template <size_t _N>
    vec<f16_t, _N>
    sqrt(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    rsqrt(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    exp(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    expm1(const vec<f16_t, _N>& x);

    vec<f16_t, 1>
    sqrt(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    rsqrt(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    exp(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    expm1(arg_t<vec<f16_t, 1> > x);

#if V2F16_FUNCS>0

    vec<f16_t, 2>
    sqrt(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    rsqrt(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    exp(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    expm1(arg_t<vec<f16_t, 2> > x);

#endif

#if V4F16_FUNCS>0

    vec<f16_t, 4>
    sqrt(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    rsqrt(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    exp(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    expm1(arg_t<vec<f16_t, 4> > x);

#endif
#if V8F16_FUNCS>0

    vec<f16_t, 8>
    sqrt(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    rsqrt(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    exp(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    expm1(arg_t<vec<f16_t, 8> > x);

#endif
#if V16F16_FUNCS>0

    vec<f16_t, 16>
    sqrt(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    rsqrt(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    exp(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    expm1(arg_t<vec<f16_t, 16> > x);

#endif
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::sqrt(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(sqrt(low_half(v)), sqrt(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::rsqrt(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(rsqrt(low_half(v)), rsqrt(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::exp(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(exp(low_half(v)), exp(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::expm1(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(expm1(low_half(v)), expm1(high_half(v)));
    return r;
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_VEC_F16_H__
