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
#include <cftal/impl/hsum.h>
#include <stdexcept>
#include <sstream>

namespace cftal {

    template <typename _T, typename _A>
    _T
    hsum(const vsvec<_T, _A>& a);

    template <typename _T, typename _A>
    _T
    hsum(const vsvec<_T, _A>& a, int32_t stride_a, size_t offset_a);

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

    template <typename _A>
    bf16_t
    dot_product(const vsvec<bf16_t, _A>& a, int32_t stride_a, size_t offset_a,
                const vsvec<bf16_t, _A>& b);

    template <typename _A>
    bf16_t
    dot_product(const vsvec<bf16_t, _A>& a, int32_t stride_a, size_t offset_a,
                const vsvec<bf16_t, _A>& b, int32_t stride_b, size_t offset_b);

    template <typename _A>
    f16_t
    dot_product(const vsvec<f16_t, _A>& a, const vsvec<f16_t, _A>& b);

    template <typename _A>
    f16_t
    dot_product(const vsvec<f16_t, _A>& a, int32_t stride_a, size_t offset_a,
                const vsvec<f16_t, _A>& b);

    template <typename _A>
    f16_t
    dot_product(const vsvec<f16_t, _A>& a, int32_t stride_a, size_t offset_a,
                const vsvec<f16_t, _A>& b, int32_t stride_b, size_t offset_b);

}

template <typename _T, typename _A>
_T
cftal::
hsum(const vsvec<_T, _A>& a)
{
    return impl::hsum<_T>(a.size(), a.cbegin());
}

template <typename _T, typename _A>
_T
cftal::
hsum(const vsvec<_T, _A>& a, int32_t stride_a, size_t offset_a)
{
    if (stride_a==0)
        impl::hsum_stride_zero();
    return impl::hsum<_T>(a.size()/stride_a,
                          a.cbegin(), stride_a, offset_a);
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
        char ab=((stride_a == 0) ? 'a' : 'b');
        impl::dot_product_stride_a_or_b_zero(ab);
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
    return impl::dot_product<bf16_t, float>(
        a.size(), a.cbegin(), b.cbegin());
}

template <typename _A>
cftal::bf16_t
cftal::
dot_product(const vsvec<bf16_t, _A>& a, int32_t stride_a, size_t offset_a,
            const vsvec<bf16_t, _A>& b)
{
    return impl::dot_product<bf16_t, float>(
        b.size(), a.cbegin(), stride_a, offset_a, b.cbegin());
}

template <typename _A>
cftal::bf16_t
cftal::
dot_product(const vsvec<bf16_t, _A>& a, int32_t stride_a, size_t offset_a,
            const vsvec<bf16_t, _A>& b, int32_t stride_b, size_t offset_b)
{
    if (__unlikely(stride_a == 0 || stride_b == 0)) {
        std::ostringstream s;
        s << "stride_" << ((stride_a == 0) ? 'a' : 'b')
          << "==0 in "
             "bf16_t cftal::"
             "dot_product(const vsvec<bf16_t, _A>& a, "
             "int32_t stride_a, size_t offset_a, "
             "const vsvec<bf16_t, _A>& b, "
             "int32_t stride_b, size_t offset_b)";
        throw std::domain_error(s.str());
    }
    return impl::dot_product<bf16_t, float>(
        a.size()/stride_a,
        a.cbegin(), stride_a, offset_a,
        b.cbegin(), stride_b, offset_b);
}

template <typename _A>
cftal::f16_t
cftal::
dot_product(const vsvec<f16_t, _A>& a, const vsvec<f16_t, _A>& b)
{
    return impl::dot_product<f16_t, float>(
        a.size(), a.cbegin(), b.cbegin());
}

template <typename _A>
cftal::f16_t
cftal::
dot_product(const vsvec<f16_t, _A>& a, int32_t stride_a, size_t offset_a,
            const vsvec<f16_t, _A>& b)
{
    return impl::dot_product<f16_t, float>(
        b.size(), a.cbegin(), stride_a, offset_a, b.cbegin());
}

template <typename _A>
cftal::f16_t
cftal::
dot_product(const vsvec<f16_t, _A>& a, int32_t stride_a, size_t offset_a,
            const vsvec<f16_t, _A>& b, int32_t stride_b, size_t offset_b)
{
    if (__unlikely(stride_a == 0 || stride_b == 0)) {
        std::ostringstream s;
        s << "stride_" << ((stride_a == 0) ? 'a' : 'b')
          << "==0 in "
             "f16_t cftal::"
             "dot_product(const vsvec<f16_t, _A>& a, "
             "int32_t stride_a, size_t offset_a, "
             "const vsvec<f16_t, _A>& b, "
             "int32_t stride_b, size_t offset_b)";
        throw std::domain_error(s.str());
    }
    return impl::dot_product<f16_t, float>(
        a.size()/stride_a,
        a.cbegin(), stride_a, offset_a,
        b.cbegin(), stride_b, offset_b);
}

// Local variables:
// mode: c++
// end:
#endif
