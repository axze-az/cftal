//
// Copyright (C) 2010-2026 Axel Zeuner
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
#if !defined (__CFTAL_VSVEC_LOAD_STRIDED_H__)
#define __CFTAL_VSVEC_LOAD_STRIDED_H__ 1

#include <cftal/config.h>
#include <cftal/vsvec_lookup.h>

namespace cftal {


    namespace impl {

        template <typename _T, typename _I, typename _A, typename _AI>
        struct load_indices <vsvec<_T, _A>, vsvec<_I, _AI> > {
            static
            vsvec<_T, _A>
            from(const _T* src, const vsvec<_I, _AI>& iv, ssize_t offset);
        };

        template <typename _I, typename _A>
        struct indices_from_stride<vsvec<_I, _A>, _I> {
            static
            vsvec<_I, _A>
            create(size_t n, _I stride);
        };

        template <typename _T, typename _A, typename _STRIDE_TYPE>
        struct load_strided<vsvec<_T, _A>, _STRIDE_TYPE> {
            static
            vsvec<_T, _A>
            from(size_t n, const _T* src, const _STRIDE_TYPE& s,
                 ssize_t offset);
        };
    }

    // create an index vector from stride
    // r[i] = i * stride for i=[0, n)
    template <typename _INDEX_VEC>
    _INDEX_VEC
    make_indices_from_stride(ssize_t n, int32_t stride);

    // create an index vector from stride
    // r[i] = i * stride for i=[0, n)
    template <typename _INDEX_VEC>
    _INDEX_VEC
    make_indices_from_stride(ssize_t n, int64_t stride);

    // load a vector _VEC containing the elements
    // r[i] = src[offset + i * stride] for i=[0, n)
    template <typename _VEC, typename _T>
    _VEC
    load_strided(size_t vec_size, const _T* src, int32_t stride,
                 ssize_t offset=0);

    // load a vector _VEC containing the elements
    // r[i] = src[offset + i * stride] for i=[0, n)
    template <typename _VEC, typename _T>
    _VEC
    load_strided(size_t vec_size, const _T* src, int64_t stride,
                 ssize_t offset=0);
}

template <typename _T, typename _I, typename _A, typename _AI>
cftal::vsvec<_T, _A>
cftal::impl::load_indices<cftal::vsvec<_T, _A>, cftal::vsvec<_I, _AI> >::
from(const _T* src, const vsvec<_I, _AI>& iv, ssize_t offset)
{
    constexpr const size_t _N=max_vec_size_specialized<_T>();
    const size_t n=iv.size();
    const size_t nm= n & (~(_N-1));
    vsvec<_T, _A> r(_T(0), n);
    size_t i=0;
    if (nm) {
        using iv_t=vec<_I, _N>;
        using v_t =vec<_T, _N>;
        using idx_ld=load_indices<v_t, iv_t>;
        while (i < nm) {
            auto iv_i=iv.template loadv<_N>(i);
            v_t vi=idx_ld::from(src, iv_i, offset);
            r.storev(i, vi);
            i += _N;
        }
    }
    if (i < n) {
        auto d=r.begin();
        std::advance(d, i);
        while (i < n) {
            _T vi=src[offset + iv[i]];
            *d = vi;
            ++d;
            ++i;
        }
    }
    return r;
}

template <typename _I, typename _A>
cftal::vsvec<_I, _A>
cftal::impl::indices_from_stride<cftal::vsvec<_I, _A>, _I>::
create(size_t n, _I stride)
{
    constexpr const size_t _N=max_vec_size_specialized<_I>();
    size_t nm= n & (~(_N-1));
    vsvec<_I, _A> r(_I(0), n);
    size_t i=0;
    if (nm) {
        _I offset_n=0;
        _I stride_n=stride*_N;
        using iv_t=vec<_I, _N>;
        iv_t iv0=indices_from_stride<iv_t, _I>::create(stride);
        while (i < nm) {
            iv_t iv_i=iv0 + offset_n;
            r.storev(i, iv_i);
            i += _N;
            offset_n += stride_n;
        }
    }
    if (i < n) {
        auto d=r.begin();
        std::advance(d, i);
        while (i < n) {
            _I vi=i*stride;
            *d = vi;
            ++d;
            ++i;
        }
    }
    return r;
}

template <typename _T, typename _A, typename _STRIDE_TYPE>
cftal::vsvec<_T, _A>
cftal::impl::load_strided<cftal::vsvec<_T, _A>, _STRIDE_TYPE>::
from(size_t n, const _T* src, const _STRIDE_TYPE& s, ssize_t offset)
{
#if TEST_INDICES_FROM_STRIDE_AND_LOAD>0
    auto iv=indices_from_stride<vsvec<_STRIDE_TYPE>, _STRIDE_TYPE>::
        create(n, s);
    auto r=load_indices<vsvec<_T, _A>, vsvec<_STRIDE_TYPE> >::
        from(src, iv, offset);
    return r;
#else
    constexpr const size_t _N=max_vec_size_specialized<_T>();
    size_t nm= n & (~(_N-1));
    vsvec<_T, _A> r(_T(0), n);
    size_t i=0;
    if (nm) {
        _STRIDE_TYPE offset_n=offset;
        using iv_t=vec<_STRIDE_TYPE, _N>;
        using v_t =vec<_T, _N>;
        if (s==0) {
            v_t v=src[offset];
            while (i < nm) {
                r.storev(i, v);
                i += _N;
            }
        } else if (s==1) {
            while (i < nm) {
                v_t v=mem<v_t>::load(src+offset_n, _N);
                r.storev(i, v);
                i += _N;
                offset_n += _N;
            }
        } else {
            const _STRIDE_TYPE stride_n=_N*s;
            auto iv=indices_from_stride<iv_t, _STRIDE_TYPE>::create(s);
            using idx_ld=load_indices<vec<_T, _N>, iv_t>;
            while (i < nm) {
                v_t vi=idx_ld::from(src, iv, offset_n);
                r.storev(i, vi);
                i += _N;
                offset_n += stride_n;
            }
        }
    }
    if (i < n) {
        auto d=r.begin();
        std::advance(d, i);
        while (i < n) {
            _T vi=src[offset + _STRIDE_TYPE(s * _STRIDE_TYPE(i))];
            *d = vi;
            ++d;
            ++i;
        }
    }
    return r;
#endif
};

template <typename _INDEX_VEC>
_INDEX_VEC
cftal::make_indices_from_stride(ssize_t n, int32_t stride)
{
    return impl::indices_from_stride<vsvec<_INDEX_VEC>, int32_t>::
        create(n, stride);
}

template <typename _INDEX_VEC>
_INDEX_VEC
cftal::make_indices_from_stride(ssize_t n, int64_t stride)
{
    return impl::indices_from_stride<vsvec<_INDEX_VEC>, int64_t>::
        create(n, stride);
}

template <typename _VEC, typename _T>
_VEC
cftal::load_strided(size_t vec_size, const _T* src, int32_t stride,
                    ssize_t offset)
{
    return impl::load_strided<_VEC, int32_t>::from(vec_size, src,
                                                   stride, offset);
}

template <typename _VEC, typename _T>
_VEC
cftal::load_strided(size_t vec_size, const _T* src, int64_t stride,
                    ssize_t offset)
{
    return impl::load_strided<_VEC, int64_t>::from(vec_size, src,
                                                   stride, offset);
}

#endif
