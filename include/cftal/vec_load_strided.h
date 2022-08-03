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
#if !defined (__CFTAL_VEC_LOAD_STRIDED_H__)
#define __CFTAL_VEC_LOAD_STRIDED_H__ 1

#include <cftal/config.h>
#include <cftal/vec_lookup.h>

namespace cftal {

    namespace impl {

        // struct using a vector of indices to load a vector
        template <typename _VEC, typename _INDEX_VEC>
        struct load_indices {
        };

	template <typename _VEC, typename _STRIDE_TYPE>
	struct indices_from_stride {
	};
	
        // struct using a stride to load a vector
        template <typename _VEC, typename _STRIDE_TYPE>
        struct load_strided {
        };
    }

    // load a vector _VEC containing the elements
    // r[i] = src[indices[i] + offset] for i=[0, indices.size())
    template <typename _VEC, typename _T, typename _INDEX_VEC>
    _VEC
    load_indices(const _T* src, const _INDEX_VEC& indices,
                 ssize_t offset=0);

    // create an index vector from stride
    template <typename _INDEX_VEC>
    _INDEX_VEC
    make_indices_from_stride(int32_t stride);

    // create an index vector from stride
    template <typename _INDEX_VEC>
    _INDEX_VEC
    make_indices_from_stride(int64_t stride);
    
    // load a vector _VEC containing the elements
    // r[i] = src[offset + i * stride] for i=[0, _VEC.size())
    template <typename _VEC, typename _T>
    _VEC
    load_strided(const _T* src, int32_t stride, ssize_t offset=0);

    // load a vector _VEC containing the elements
    // r[i] = src[offset + i * stride] for i=[0, _VEC.size())
    template <typename _VEC, typename _T>
    _VEC
    load_strided(const _T* src, int64_t stride, ssize_t offset=0);

    // load an object of type _V with _STRIDE and _OFFSET from p
    // using indices of type _IDX_TYPE resulting in an object
    // containing the elements i=[0,__VEC.size())
    // r[i] = src[_OFFSET + i * _STRIDE]
    template <typename _V, int32_t _STRIDE=1, ssize_t _OFFSET=0,
              typename _T>
    _V
    load_strided(const _T* src);

    namespace impl {

        template <typename _T, typename _I, size_t _N>
        struct load_indices<vec<_T, _N>, vec<_I, _N> > {
            static
            vec<_T, _N>
            from(const _T* src, const vec<_I, _N>& iv, ssize_t offset);
        };

        template <typename _I, size_t _N>
        struct indices_from_stride<vec<_I, _N>, _I> {
            struct alignas(vec<_I, _N>) data {
                // stores only stride 1
                _I _v[_N];
                data();
            };
            static const data _dta;
            static
            vec<_I, _N>
            create(_I stride);
        };
	
        template <typename _T, size_t _N, typename _STRIDE_TYPE>
        struct load_strided<vec<_T, _N>, _STRIDE_TYPE> {
            static
            vec<_T, _N>
            from(const _T* src, const _STRIDE_TYPE& s, ssize_t offset);
        };

    }
}

template <typename _VEC, typename _T, typename _INDEX_VEC>
_VEC
cftal::load_indices(const _T* src, const _INDEX_VEC& indices, ssize_t offset)
{
    return impl::load_indices<_VEC, _INDEX_VEC>::from(src, indices, offset);
}

template <typename _INDEX_VEC>
_INDEX_VEC
cftal::make_indices_from_stride(int32_t stride)
{
    return impl::indices_from_stride<_INDEX_VEC, int32_t>::create(stride);
}

// create an index vector from stride
template <typename _INDEX_VEC>
_INDEX_VEC
cftal::make_indices_from_stride(int64_t stride) 
{
    return impl::indices_from_stride<_INDEX_VEC, int64_t>::create(stride);
}

template <typename _VEC, typename _T>
_VEC
cftal::load_strided(const _T* src, int32_t stride, ssize_t offset)
{
    return impl::load_strided<_VEC, int32_t>::from(src, stride, offset);
}

template <typename _VEC, typename _T>
_VEC
cftal::load_strided(const _T* src, int64_t stride, ssize_t offset)
{
    return impl::load_strided<_VEC, int64_t>::from(src, stride, offset);
}

template <typename _V, int32_t _STRIDE, ssize_t _OFFSET, typename _T>
_V
cftal::load_strided(const _T* src)
{
    return load_strided<_V>(src, _STRIDE, _OFFSET);
}

template <typename _T, typename _I, size_t _N>
cftal::vec<_T, _N>
cftal::impl::load_indices<cftal::vec<_T, _N>, cftal::vec<_I, _N> >::
from(const _T* src, const vec<_I, _N>& iv, ssize_t offset)
{
    auto lck=make_variable_lookup_table<_T>(iv);
    return lck.from(src+offset);
}

template <typename _I, size_t _N>
cftal::impl::indices_from_stride<cftal::vec<_I, _N>, _I>::
data::data()
{
    for (size_t i=0; i<_N; ++i) {
	_v[i] = _I(i);
    }
}

template <typename _I, size_t _N>
cftal::vec<_I, _N>
cftal::impl::indices_from_stride<cftal::vec<_I, _N>, _I>::
create(_I stride)
{
    vec<_I, _N> r=mem<vec<_I, _N> >::load(_dta._v, _N);
    return r*stride;
}

template <typename _I, size_t _N>
const typename
cftal::impl::
indices_from_stride<cftal::vec<_I, _N>, _I>::data
cftal::impl::indices_from_stride<cftal::vec<_I, _N>, _I>::_dta{};

template <typename _T, size_t _N, typename _STRIDE_TYPE>
cftal::vec<_T, _N>
cftal::impl::load_strided<cftal::vec<_T, _N>, _STRIDE_TYPE>::
from(const _T* src, const _STRIDE_TYPE& s, ssize_t offset)
{
    using v_t = vec<_T, _N>;
    using vi_t = vec<_STRIDE_TYPE, _N>;
    // scalar load for stride 0
    if (s == 0) {
	_T v=src[offset];
	return v_t(v);
    }
    // standard vector load for stride 1
    if (s == 1) {
	return mem<v_t>::load(src+offset, _N);
    }
    auto iv=indices_from_stride<vi_t, _STRIDE_TYPE>::create(s);
    return load_indices<v_t, vi_t>::from(src, iv, offset);
}


/*
 * Local variables:
 * mode: c++
 * end:
 */
#endif
