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

    template <typename _T, typename _A>
    _T
    dot_product(const vsvec<_T, _A>& b,
                const vsvec<_T, _A>& a, int32_t stride_a, size_t offset_a);

    template <typename _T, typename _A>
    _T
    dot_product(const vsvec<_T, _A>& a, int32_t stride_a, size_t offset_a,
                const vsvec<_T, _A>& b, int32_t stride_b, size_t offset_b);

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
        using v_t = vec<_T, _N>;
        const size_t n4= s & ~(_N4-1);
        v_t r0(_T(0));
        if (n4) {
            v_t r1(_T(0)), r2(_T(0)), r3(_T(0));
            for (size_t i=0; i<n4; i+=4*_N) {
                v_t a0 = a.template loadv<_N>(i+0*_N);
                v_t a1 = a.template loadv<_N>(i+1*_N);
                v_t a2 = a.template loadv<_N>(i+2*_N);
                v_t a3 = a.template loadv<_N>(i+3*_N);

                r0 += a0 * b.template loadv<_N>(i+0*_N);
                r1 += a1 * b.template loadv<_N>(i+1*_N);
                r2 += a2 * b.template loadv<_N>(i+2*_N);
                r3 += a3 * b.template loadv<_N>(i+3*_N);
            }
            r2 += r3;
            r0 += r1;
            r0 += r2;
        }
        for (size_t i=n4; i<n1; i+= _N) {
            r0 +=a.template loadv<_N>(i+0*_N)
                * b.template loadv<_N>(i+0*_N);
        }
        r = hadd(r0);
    }
    for (size_t i=n1; i<s; ++i) {
        r += a[i] * b[i];
    }
    return r;
}

template <typename _T, typename _A>
cftal::vsvec<_T, _A>
cftal::
dot_product(const vsvec<_T, _A>& a, int32_t stride_a, size_t offset_a,
            const vsvec<_T, _A>& b)
{
    constexpr const size_t _N=max_vec_size_specialized<_T>();
    constexpr const size_t _N4=4*_N;

    const size_t s= a.size();
    const size_t n1= s & ~(_N-1);
    _T r(0);
    if (n1) {
        using v_t = vec<_T, _N>;
        using vi_t = vec<int32_t, _N>;
        const size_t n4= s & ~(_N4-1);
        vec<_T, _N> r0(_T(0));
        vi_t idx_a=
            impl::indices_from_stride<vi_t, int32_t>::create(stride_a);
        auto lck_a=make_variable_lookup_table<_T>(idx_a);
        if (n4) {
            vec<_T, _N> r1(_T(0)), r2(_T(0)), r3(_T(0));
            for (size_t i=0; i<n4; i+=4*_N) {
                v_t a0 = lck_a.fromp(&a[(i+0*_N)*stride_a+offset_a]);
                v_t a1 = lck_a.fromp(&a[(i+1*_N)*stride_a+offset_a]);
                v_t a2 = lck_a.fromp(&a[(i+1*_N)*stride_a+offset_a]);
                v_t a3 = lck_a.fromp(&a[(i+1*_N)*stride_a+offset_a]);

                r0 += a0 * b.template loadv<_N>(i+0*_N);
                r1 += a1 * b.template loadv<_N>(i+1*_N);
                r2 += a2 * b.template loadv<_N>(i+2*_N);
                r3 += a3 * b.template loadv<_N>(i+3*_N);
            }
            r2 += r3;
            r0 += r1;
            r0 += r2;
        }
        for (size_t i=n4; i<n1; i+= _N) {
            v_t a0 = lck_a.fromp(&a[(i+0*_N)*stride_a+offset_a]);
            r0 += a0 * b.template loadv<_N>(i+0*_N);
        }
        r = hadd(r0);
    }
    for (size_t i=n1; i<s; ++i) {
        r += a[i*stride_a+offset_a] * b[i];
    }
    return r;
}

template <typename _T, typename _A>
cftal::vsvec<_T, _A>
cftal::
dot_product(const vsvec<_T, _A>& b,
            const vsvec<_T, _A>& a, int32_t stride_a, size_t offset_a)
{
    return dot_product(a, stride_a, offset_a, b);
}

template <typename _T, typename _A>
cftal::vsvec<_T, _A>
cftal::
dot_product(const vsvec<_T, _A>& a, int32_t stride_a, size_t offset_a,
            const vsvec<_T, _A>& b, int32_t stride_b, size_t offset_b)
{
    constexpr const size_t _N=max_vec_size_specialized<_T>();
    constexpr const size_t _N4=4*_N;

    const size_t s= a.size();
    const size_t n1= s & ~(_N-1);
    _T r(0);
    if (n1) {
        using v_t = vec<_T, _N>;
        using vi_t = vec<int32_t, _N>;
        const size_t n4= s & ~(_N4-1);
        vec<_T, _N> r0(_T(0));
        vi_t idx_a=
            impl::indices_from_stride<vi_t, int32_t>::create(stride_a);
        vi_t idx_b=
            impl::indices_from_stride<vi_t, int32_t>::create(stride_b);
        auto lck_a=make_variable_lookup_table<_T>(idx_a);
        auto lck_b=make_variable_lookup_table<_T>(idx_b);
        if (n4) {
            vec<_T, _N> r1(_T(0)), r2(_T(0)), r3(_T(0));
            for (size_t i=0; i<n4; i+=4*_N) {
                v_t a0 = lck_a.fromp(&a[(i+0*_N)*stride_a+offset_a]);
                v_t a1 = lck_a.fromp(&a[(i+1*_N)*stride_a+offset_a]);
                v_t a2 = lck_a.fromp(&a[(i+1*_N)*stride_a+offset_a]);
                v_t a3 = lck_a.fromp(&a[(i+1*_N)*stride_a+offset_a]);
                v_t b0 = lck_b.fromp(&b[(i+0*_N)*stride_b+offset_b]);
                v_t b1 = lck_b.fromp(&b[(i+1*_N)*stride_b+offset_b]);
                v_t b2 = lck_b.fromp(&b[(i+1*_N)*stride_b+offset_b]);
                v_t b3 = lck_b.fromp(&b[(i+1*_N)*stride_b+offset_b]);

                r0 += a0 * b0;
                r1 += a1 * b1;
                r2 += a2 * b2;
                r3 += a3 * b3;
            }
            r2 += r3;
            r0 += r1;
            r0 += r2;
        }
        for (size_t i=n4; i<n1; i+= _N) {
            v_t a0 = lck_a.fromp(&a[(i+0*_N)*stride_a+offset_a]);
            v_t b0 = lck_b.fromp(&b[(i+0*_N)*stride_b+offset_b]);
            r0 += a0 * b0;
        }
        r = hadd(r0);
    }
    for (size_t i=n1; i<s; ++i) {
        r += a[i*stride_a+offset_a] * b[i*stride_b+offset_b];
    }
    return r;
}

// Local variables:
// mode: c++
// end:
#endif
