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
#include "cftal/test/program.h"
#include "cftal/test/check_sqrt.h"
#include "cftal/vec_f16.h"
#include "cftal/math/elem_func_core_f16.h"
#include "cftal/math/vec_func_traits_f16.h"

namespace cftal {

    template <size_t _N>
    vec<f16_t, _N>
    sqrt(const vec<f16_t, _N>& x);

    vec<f16_t, 1>
    sqrt(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 2>
    sqrt(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 4>
    sqrt(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 8>
    sqrt(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 16>
    sqrt(arg_t<vec<f16_t, 16> > x);

    using v1f16 = vec<f16_t, 1>;
    using v2f16 = vec<f16_t, 2>;
    using v4f16 = vec<f16_t, 4>;
    using v8f16 = vec<f16_t, 8>;
    using v16f16 = vec<f16_t, 16>;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::sqrt(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(sqrt(low_half(v)), sqrt(high_half(v)));
    return r;
}

__attribute__((__flatten__))
cftal::v1f16
cftal::sqrt(arg_t<v1f16> x)
{
    using traits_t = cftal::math::func_traits<v1f16, v1s16>;
    using func_t = cftal::math::elem_func<f16_t, traits_t>;
    return func_t::sqrt(x);
}

__attribute__((__flatten__))
cftal::v2f16
cftal::sqrt(arg_t<v2f16> x)
{
    using traits_t = cftal::math::func_traits<v2f16, v2s16>;
    using func_t = cftal::math::elem_func<f16_t, traits_t>;
    return func_t::sqrt(x);
}

__attribute__((__flatten__))
cftal::v4f16
cftal::sqrt(arg_t<v4f16> x)
{
    using traits_t = cftal::math::func_traits<v4f16, v4s16>;
    using func_t = cftal::math::elem_func<f16_t, traits_t>;
    return func_t::sqrt(x);
}

__attribute__((__flatten__))
cftal::v8f16
cftal::sqrt(arg_t<v8f16> x)
{
    using traits_t = cftal::math::func_traits<v8f16, v8s16>;
    using func_t = cftal::math::elem_func<f16_t, traits_t>;
    return func_t::sqrt(x);
}

__attribute__((__flatten__))
cftal::v16f16
cftal::sqrt(arg_t<v16f16> x)
{
    using traits_t = cftal::math::func_traits<v16f16, v16s16>;
    using func_t = cftal::math::elem_func<f16_t, traits_t>;
    return func_t::sqrt(x);
}


int main(int argc, char** argv)
{
    using namespace cftal::test;
    using cftal::f16_t;
    int r=program<check_sqrt<f16_t>, 32, 1, 0x8000>(
        argc,
        argv,
        mpfr_sqrt,
        domain_sqrt<f16_t>::domains,
        domain_sqrt<f16_t>::shifts);
    return r;
}
