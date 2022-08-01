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

        // struct using a stride to load a vector
        template <typename _VEC, typename _STRIDE_TYPE>
        struct load_strided {
        };
    }

    template <typename _VEC, typename _T, typename _INDEX_VEC>
    _VEC
    load_indices(const _T* src, const _INDEX_VEC& indices,
                 ssize_t offset=0);

    template <typename _VEC, typename _T>
    _VEC
    load_strided(const _T* src, int32_t stride, ssize_t offset=0);

    template <typename _VEC, typename _T>
    _VEC
    load_strided(const _T* src, int64_t stride, ssize_t offset=0);

    // load an object of type _V with _STRIDE and _OFFSET from p
    // using indices of type _IDX_TYPE resulting in an object
    // containing the elements i=0..._N
    // _V[i] = p[_OFFSET + i * _STRIDE]
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


        template <typename _T, size_t _N, typename _STRIDE_TYPE>
        struct load_strided<vec<_T, _N>, _STRIDE_TYPE> {
            struct alignas(128) data {
                static constexpr size_t _NN=16+1;
                // stores the strides from 0 to _NN-1
                _STRIDE_TYPE _v[_NN*_N];
                data();
            };
            static const data _dta;
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

template <typename _V, int32_t _STRIDE=1, ssize_t _OFFSET, typename _T>
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

template <typename _T, size_t _N, typename _STRIDE_TYPE>
cftal::impl::load_strided<cftal::vec<_T, _N>, _STRIDE_TYPE>::data::data()
{
    for (size_t s=0, o=0; s <_NN; ++s) {
        for (size_t i=0; i<_N; ++i, ++o) {
            _v[o] = _STRIDE_TYPE(s)* _STRIDE_TYPE(i);
        }
    }
}

template <typename _T, size_t _N, typename _STRIDE_TYPE>
const typename cftal::impl::load_strided<cftal::vec<_T, _N>, _STRIDE_TYPE>::data
cftal::impl::load_strided<cftal::vec<_T, _N>, _STRIDE_TYPE>::_dta{};

template <typename _T, size_t _N, typename _STRIDE_TYPE>
cftal::vec<_T, _N>
cftal::impl::load_strided<cftal::vec<_T, _N>, _STRIDE_TYPE>::
from(const _T* src, const _STRIDE_TYPE& s, ssize_t offset)
{
    using v_t = vec<_T, _N>;
    using vi_t =vec<_STRIDE_TYPE, _N>;
    using u_t=std::make_unsigned_t<_STRIDE_TYPE>;
    if (u_t(s) < data::_NN) {
        // scalar load for stride 0
        if (s == 0) {
            _T v=src[offset];
            return vec<_T, _N>(v);
        }
        // standard vector load for stride 1
        if (s == 1) {
            return mem<vec<_T, _N> >::load(src+offset, _N);
        }
        // use direct index load for 2 ... NN-1
        auto iv=mem<vi_t>::load(_dta._v + s * _N);
        return load_indices<v_t, vi_t>::from(src, iv, offset);
    }
    // load index 1 with 0, 1, 2, 3, 4, ... _N-1
    auto iv=mem<vi_t>::load(_dta._v + 1 * _N);
    iv *= s;
    return load_indices<v_t, vi_t>::from(src, iv, offset);
}


/*
 * Local variables:
 * mode: c++
 * end:
 */
#endif
