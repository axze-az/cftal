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
#if !defined (__CFTAL_IMPL_HMINMAX_H__)
#define __CFTAL_IMPL_HMINMAX_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/type_traits.h>
#include <limits>

namespace cftal {
    namespace impl {

	// arguments for hminmax
	enum class opminmax {
	    max,
	    min
	};

        // horizontal maximization/minimization of _T arrays
        template <typename _T, opminmax _M>
        _T
        hminmax(size_t s, const _T* a);

        // error message for hmin/hmax with stride equal to zero
        [[noreturn]]
        void
        hminmax_stride_zero();

        // horizontal maximization/minimization of _T arrays with
        // stride and offset
        template <typename _T, opminmax _M>
        _T
        hminmax(size_t s,
		const _T* a, int32_t stride_a, size_t offset_a);
    }
}

template <typename _T, cftal::impl::opminmax _M>
_T
cftal::impl::
hminmax(size_t s, const _T* a)
{
    constexpr const size_t _N=max_vec_size_specialized<_T>();
    constexpr const size_t _N4=4*_N;
    const size_t n1= s & ~(_N-1);
    _T r(0);
    using std::min;
    using std::max;
    if (n1) {
        using v_t = vec<_T, _N>;
        const size_t n4 = s & ~(_N4 - 1);
        const _T init = _M == opminmax::min ?
	    std::numeric_limits<_T>::max() :  ( is_floating_point_v<_T> ?
						-std::numeric_limits<_T>::max()
						: std::numeric_limits<_T>::min());
        _T r0(init);
        if (n4) {
            v_t r1(init), r2(init), r3(init);
            for (size_t i=0; i<n4; i+=4*_N) {
                v_t a0 = mem<v_t>::load(a+i+0*_N);
                v_t a1 = mem<v_t>::load(a+i+1*_N);
                v_t a2 = mem<v_t>::load(a+i+2*_N);
                v_t a3 = mem<v_t>::load(a+i+3*_N);
		if ( _M == opminmax::max) {
		    r0 = max(r0, a0);
		    r1 = max(r1, a1);
		    r2 = max(r2, a2);
                    r3 = max(r3, a3);
                } else {
		    r0 = min(r0, a0);
		    r1 = min(r1, a1);
		    r2 = min(r2, a2);
                    r3 = min(r3, a3);
		}
            }
            r2 += r3;
            r0 += r1;
            r0 += r2;
	    if ( _M == opminmax::max) {
		r2 = max(r2, r3);
		r0 = max(r0, r1);
		r0 = max(r0, r2);
	    } else {
		r2 = max(r2, r3);
		r0 = max(r0, r1);
		r0 = max(r0, r2);
	    }
        }
        for (size_t i=n4; i<n1; i+= _N) {
            v_t a0 = mem<v_t>::load(a+i+0*_N);
	    if ( _M == opminmax::max) {
		r0 = max(r0, a0);
	    } else {
		r0 = min(r0, a0);
	    }
        }
	if ( _M == opminmax::max) {
	    r = hmax(r0);
        } else {
	    r = hmin(r0);
	}
    }
    for (size_t i = n1; i < s; ++i) {
	if ( _M == opminmax::max) {
	    r = max(r, a[i]);
	} else {
	    r = min(r, a[i]);
	}
    }
    return _T(r);
}

template <typename _T, cftal::impl::opminmax _M>
_T
cftal::impl::
hminmax(size_t s,
     const _T* a, int32_t stride_a, size_t offset_a)
{
    if (__unlikely(stride_a==0)) {
        hminmax_stride_zero();
    }
    if (__unlikely(stride_a==1)) {
        return impl::hminmax<_T, _M>(s, a+offset_a);
    }

    constexpr const size_t _N=max_vec_size_specialized<_T>();
    constexpr const size_t _N4=4*_N;
    const size_t n1= s & ~(_N-1);
    _T r(0);
    using std::min;
    using std::max;
    if (n1) {
        using v_t = vec<_T, _N>;
        const size_t n4 = s & ~(_N4 - 1);
        using vi_t = vec<int32_t, _N>;
        const _T init = _M == opminmax::min ?
	    std::numeric_limits<_T>::max() :  ( is_floating_point_v<_T> ?
						-std::numeric_limits<_T>::max()
						: std::numeric_limits<_T>::min());
        _T r0(init);
        vi_t idx_a=
            impl::indices_from_stride<vi_t, int32_t>::create(stride_a);
        auto lck_a=make_variable_lookup_table<_T>(idx_a);
        if (n4) {
            v_t r1(init), r2(init), r3(init);
            for (size_t i=0; i<n4; i+=4*_N) {
                v_t a0 = lck_a.fromp(a+(i+0*_N)*stride_a+offset_a);
                v_t a1 = lck_a.fromp(a+(i+1*_N)*stride_a+offset_a);
                v_t a2 = lck_a.fromp(a+(i+2*_N)*stride_a+offset_a);
                v_t a3 = lck_a.fromp(a+(i+3*_N)*stride_a+offset_a);
		if ( _M == opminmax::max) {
		    r0 = max(r0, a0);
		    r1 = max(r1, a1);
		    r2 = max(r2, a2);
                    r3 = max(r3, a3);
                } else {
		    r0 = min(r0, a0);
		    r1 = min(r1, a1);
		    r2 = min(r2, a2);
                    r3 = min(r3, a3);
		}
            }
            r2 += r3;
            r0 += r1;
            r0 += r2;
	    if ( _M == opminmax::max) {
		r2 = max(r2, r3);
		r0 = max(r0, r1);
		r0 = max(r0, r2);
	    } else {
		r2 = max(r2, r3);
		r0 = max(r0, r1);
		r0 = max(r0, r2);
	    }
        }
        for (size_t i=n4; i<n1; i+= _N) {
            v_t a0 = lck_a.fromp(a+(i+0*_N)*stride_a+offset_a);
	    if ( _M == opminmax::max) {
		r0 = max(r0, a0);
	    } else {
		r0 = min(r0, a0);
	    }
        }
	if ( _M == opminmax::max) {
	    r = hmax(r0);
        } else {
	    r = hmin(r0);
	}
    }
    for (size_t i = n1; i < s; ++i) {
	if ( _M == opminmax::max) {
	    r = max(r, a[i*stride_a+offset_a]);
	} else {
	    r = min(r, a[i*stride_a+offset_a]);
	}
    }
    return _T(r);
}

// Local variables:
// mode: c++
// end:
#endif
