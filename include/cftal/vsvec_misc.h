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
#include <cftal/vsvec_load_strided.h>

namespace cftal {

    template <typename _T, typename _A>
    _T
    dot_product(const vsvec<_T, _A>& a, const vsvec<_T, _A>& b);

    template <typename _T, typename _A>
    _T
    dot_product(const vsvec<_T, _A>& a, int32_t stride_a, size_t offset_a,
		const vsvec<_T, _A>& b);
    
}

template <typename _T, typename _A>
cftal::vsvec<_T, _A>
cftal::
dot_product(const vsvec<_T, _A>& a, const vsvec<_T, _A>& b)
{
    constexpr const size_t _N=max_vec_size_specialized<_T>();
    constexpr const size_t _N4=4*_N;
    const size_t s= a.size();
    const size_t n1= s & ~(_N-1);
    _T r(0);
    if (n1) {
        const size_t n4= s & ~(_N4-1);
        vec<_T, _N> a0(_T(0));
        if (n4) {
            vec<_T, _N> a1(_T(0)), a2(_T(0)), a3(_T(0));
            for (size_t i=0; i<n4; i+=4*_N) {
                a0 += a.template loadv<_N>(i+0*_N) *
                    b.template loadv<_N>(i+0*_N);
                a1 += a.template loadv<_N>(i+1*_N) *
                    b.template loadv<_N>(i+1*_N);
                a2 += a.template loadv<_N>(i+2*_N) *
                    b.template loadv<_N>(i+2*_N);
                a3 += a.template loadv<_N>(i+3*_N) *
                    b.template loadv<_N>(i+3*_N);
            }
            a2 += a3;
            a0 += a1;
            a0 += a2;
        }
        for (size_t i=n4; i<n1; i+= _N) {
            a0 +=a.template loadv<_N>(i+0*_N)
                * b.template loadv<_N>(i+0*_N);
        }
        r = hadd(a0);
    }
    for (size_t i=n1; i<s; ++i) {
        r += a[i] * b[i];
    }
    return r;
}

// Local variables:
// mode: c++
// end:
#endif
