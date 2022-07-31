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

        // strided loader for _V objects, requires specialization for
        // vector classes
        template <typename _V, ssize_t _STRIDE=1, ssize_t _OFFSET=0,
                  typename _IDX_TYPE=int32_t>
        struct strided_loader {
#if 0
	    // implementation for scalars
	    static
	    _V
	    v(const _V* p) {
		return p[_OFFSET];
	    }
#endif
        };

        // flexible strided loader for _V objects, requires specialization for
        // vector classes
        template <typename _V, typename _IDX_TYPE>
        struct flexible_strided_loader {
#if 0
	    // implementation for scalars
	    static
	    _V
	    v(const _V* p, _IDX_TYPE stride, _IDX_TYPE offset) {
		return p[_OFFSET];
	    }
#endif
        };

    }

    // load an object of type _V with _STRIDE and _OFFSET from p
    // using indices of type _IDX_TYPE resulting in an object
    // containing the elements i=0..._N
    // _V[i] = p[_OFFSET + i * _STRIDE]
    template <typename _V, ssize_t _STRIDE=1, ssize_t _OFFSET=0,
              typename _IDX_TYPE=int32_t, typename _T>
    _V
    load_strided(const _T* p) {
        return impl::strided_loader<_V, _STRIDE, _OFFSET, _IDX_TYPE>::v(p);
    }

    // load an object of type _V with stride and offset from p
    // using indices of type _IDX_TYPE resulting in an object
    // containing the elements i=0..._N
    // _V[i] = p[offset + i * stride]
    // PLEASE NOTE: this may be not very efficient
    template <typename _V, typename _IDX_TYPE=int32_t, typename _T>
    _V
    load_strided(const _T* p, _IDX_TYPE stride, _IDX_TYPE offset=0) {
        using int_type=std::make_signed_t<_IDX_TYPE>;
        int_type s=stride, o=offset;
        return impl::flexible_strided_loader<_V, int_type>::v(p, s, o);
    }

    namespace impl {

	// helper classes for strided loader for vec<_T, _N> objects

        // helper class for initializing arrays
        template <typename _T, size_t _I, ssize_t _STRIDE, ssize_t _OFFSET>
        struct init_index_data {
            void
            operator()(_T* v) {
                constexpr size_t i=_I-1;
                init_index_data<_T, i, _STRIDE, _OFFSET>()(v);
                v[i] = _T(_STRIDE * i + _OFFSET);
            }
        };

        // helper class for initializing arrays, first element with idx 0
        template <typename _T, ssize_t _STRIDE, ssize_t _OFFSET>
        struct init_index_data<_T, 1, _STRIDE, _OFFSET> {
            void
            operator()(_T* v) {
                v[0] = _T(_OFFSET);
            }
        };

        // class containing an initialized array with
        // v[i] = _STRIDE*i + _OFFSET
        template <typename _T, size_t _N, ssize_t _STRIDE, ssize_t _OFFSET>
        struct alignas(64) index_data {
            _T _v[_N];
            index_data() : _v() {
                init_index_data<_T, _N, _STRIDE, _OFFSET>()(_v);
            }
        };

        // template wrapper around a static initialized array with
        // v[i] = _STRIDE*i + _OFFSET
        template <typename _T, size_t _N, ssize_t _STRIDE, ssize_t _OFFSET>
        struct index_array {
            static const index_data<_T, _N, _STRIDE, _OFFSET> _v;
        };

        template <typename _T, size_t _N, ssize_t _STRIDE, ssize_t _OFFSET>
        const index_data<_T, _N, _STRIDE, _OFFSET>
        index_array<_T, _N, _STRIDE, _OFFSET>::_v{};

        template <typename _T, size_t _N, ssize_t _STRIDE=1, ssize_t _OFFSET=0>
        vec<_T, _N>
        load_indices(){
            const _T* s=impl::index_array<_T, _N, _STRIDE, _OFFSET>::_v._v;
            return mem<vec<_T, _N> >::load(s, _N);
        }

        // strided loader specialization of vec<_T, _N>
        template <typename _T, size_t _N, ssize_t _STRIDE, ssize_t _OFFSET,
                  typename _IDX_TYPE>
        struct strided_loader<vec<_T, _N>, _STRIDE, _OFFSET, _IDX_TYPE> {
            static
            vec<_T, _N>
            v(const _T* p) {
                vec<_IDX_TYPE, _N> idx=
                    load_indices<_IDX_TYPE, _N, _STRIDE, _OFFSET>();
                auto lck=make_variable_lookup_table<_T>(idx);
                return lck.from(p);
            }
        };

        // strided loader specialization of vec<_T, _N> for stride 0
        // i.e. scalar load at offset INIT
        template <typename _T, size_t _N, ssize_t _OFFSET,
                  typename _IDX_TYPE>
        struct strided_loader<vec<_T, _N>, 0, _OFFSET, _IDX_TYPE> {
            static
            vec<_T, _N>
            v(const _T* p) {
                _T v=p[_OFFSET];
                return vec<_T, _N>(v);
            }
        };

        // strided loader specialization of vec<_T, _N> for stride 1
        // i.e. vector load at offset _OFFSET
        template <typename _T, size_t _N, ssize_t _OFFSET,
                  typename _IDX_TYPE>
        struct strided_loader<vec<_T, _N>, 1, _OFFSET, _IDX_TYPE> {
            static
            vec<_T, _N>
            v(const _T* p) {
                return mem<vec<_T, _N> >::load(p+_OFFSET, _N);
            }
        };

        // flexible strided loader for vec<_T, _N> objects
        template <typename _T, size_t _N, typename _IDX_TYPE>
        struct flexible_strided_loader<vec<_T, _N>, _IDX_TYPE> {
	    static
	    vec<_T, _N>
	    v(const _T* p, _IDX_TYPE stride, _IDX_TYPE offset) {
                union {
                    _IDX_TYPE _s[_N];
                    vec<_IDX_TYPE, _N> _v;
                } idx;
                constexpr const auto n=static_cast<_IDX_TYPE>(_N);
                for (_IDX_TYPE i=0; i<n; ++i) {
                    idx._s[i]=offset + stride * i;
                }
                auto lck=make_variable_lookup_table<_T>(idx._v);
                return lck.from(p);
	    }
        };
    }

}

/*
 * Local variables:
 * mode: c++
 * end:
 */
#endif
