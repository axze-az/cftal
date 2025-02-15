//
// Copyright (C) 2010-2025 Axel Zeuner
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
#if !defined (__CFTAL_VSVEC_MISC_H__)
#define __CFTAL_VSVEC_MISC_H__ 1

#include <cftal/config.h>
#include <cftal/vec_load_strided.h>
#include <cftal/impl/dot_product.h>
#include <stdexcept>
#include <sstream>

namespace cftal {

    template <typename _T, typename _A>
    _T
    dot_product(const vsvec<_T, _A>& a, const vsvec<_T, _A>& b);

    template <typename _T, typename _A>
    _T
    dot_product(const vsvec<_T, _A>& a, int32_t stride_a, size_t offset_a,
                const vsvec<_T, _A>& b);

    template <typename _T, typename _A>
    _T
    dot_product(const vsvec<_T, _A>& b,
                const vsvec<_T, _A>& a, int32_t stride_a, size_t offset_a);

    template <typename _T, typename _A>
    _T
    dot_product(const vsvec<_T, _A>& a, int32_t stride_a, size_t offset_a,
                const vsvec<_T, _A>& b, int32_t stride_b, size_t offset_b);

    template <typename _A>
    bf16_t
    dot_product(const vsvec<bf16_t, _A>& a, const vsvec<bf16_t, _A>& b);
}

template <typename _T, typename _A>
_T
cftal::
dot_product(const vsvec<_T, _A>& a, const vsvec<_T, _A>& b)
{
    return impl::dot_product<_T>(a.size(), a.cbegin(), b.cbegin());
}

template <typename _T, typename _A>
_T
cftal::
dot_product(const vsvec<_T, _A>& a, int32_t stride_a, size_t offset_a,
            const vsvec<_T, _A>& b)
{
    return impl::dot_product<_T>(b.size(),
                                 a.cbegin(), stride_a, offset_a,
                                 b.cbegin());
}

template <typename _T, typename _A>
_T
cftal::
dot_product(const vsvec<_T, _A>& b,
            const vsvec<_T, _A>& a, int32_t stride_a, size_t offset_a)
{
    return dot_product(a, stride_a, offset_a, b);
}

template <typename _T, typename _A>
_T
cftal::
dot_product(const vsvec<_T, _A>& a, int32_t stride_a, size_t offset_a,
            const vsvec<_T, _A>& b, int32_t stride_b, size_t offset_b)
{
    if (__unlikely(stride_a == 0 || stride_b == 0)) {
        std::ostringstream s;
        s << "stride_" << ((stride_a == 0) ? 'a' : 'b')
          << "==0 in "
             "cftal::vsvec<_T, _A> cftal::"
             "dot_product(const vsvec<_T, _A>& a, "
             "int32_t stride_a, size_t offset_a, "
             "const vsvec<_T, _A>& b, "
             "int32_t stride_b, size_t offset_b)";
        throw std::domain_error(s.str());
    }
    return impl::dot_product<_T>(a.size()/stride_a,
                                 a.cbegin(), stride_a, offset_a,
                                 b.cbegin(), stride_b, offset_b);
}

template <typename _A>
cftal::bf16_t
cftal::
dot_product(const vsvec<bf16_t, _A>& a, const vsvec<bf16_t, _A>& b)
{
    constexpr const size_t _N=max_vec_size_specialized<float>();
    constexpr const size_t _N4=4*_N;
    const size_t s= a.size();
    const size_t n1= s & ~(_N-1);
    float r(0);
    if (n1) {
        using v_t = vec<float, _N>;
        const size_t n4= s & ~(_N4-1);
        v_t r0(0.0f);
        if (n4) {
            v_t r1(0.0f), r2(0.0f), r3(0.0f);
            for (size_t i=0; i<n4; i+=4*_N) {
                v_t a0 = cvt<v_t>(a.template loadv<_N>(i+0*_N));
                v_t a1 = cvt<v_t>(a.template loadv<_N>(i+1*_N));
                v_t a2 = cvt<v_t>(a.template loadv<_N>(i+2*_N));
                v_t a3 = cvt<v_t>(a.template loadv<_N>(i+3*_N));

                r0 += a0 * cvt<v_t>(b.template loadv<_N>(i+0*_N));
                r1 += a1 * cvt<v_t>(b.template loadv<_N>(i+1*_N));
                r2 += a2 * cvt<v_t>(b.template loadv<_N>(i+2*_N));
                r3 += a3 * cvt<v_t>(b.template loadv<_N>(i+3*_N));
            }
            r2 += r3;
            r0 += r1;
            r0 += r2;
        }
        for (size_t i=n4; i<n1; i+= _N) {
            r0 += cvt<v_t>(a.template loadv<_N>(i+0*_N))
                * cvt<v_t>(b.template loadv<_N>(i+0*_N));
        }
        r = hadd(r0);
    }
    for (size_t i=n1; i<s; ++i) {
        r += float(a[i]) * float(b[i]);
    }
    return bf16_t(r);
}


// Local variables:
// mode: c++
// end:
#endif
