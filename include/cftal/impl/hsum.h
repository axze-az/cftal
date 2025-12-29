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
#if !defined (__CFTAL_IMPL_HSUM_H__)
#define __CFTAL_IMPL_HSUM_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/type_traits.h>

namespace cftal {
    namespace impl {

        // horizontal addition _T arrays using type _A as accumulator
        template <typename _T, typename _A=_T>
        _T
        hsum(size_t s, const _T* a);

        // error message for hsum with stride equal to zero
        [[noreturn]]
        void
        hsum_stride_zero();

        // horizontal addition of_T arrays using type _A as accumulator
        template <typename _T, typename _A=_T>
        _T
        hsum(size_t s,
	     const _T* a, int32_t stride_a, size_t offset_a);
    }
}

template <typename _T, typename _A>
_T
cftal::impl::
hsum(size_t s, const _T* a)
{
    constexpr const size_t _N=max_vec_size_specialized<_T>();
    constexpr const size_t _N4=4*_N;
    constexpr const bool _A_is_T= std::is_same_v<_A, _T>;
    const size_t n1= s & ~(_N-1);
    _A r(0);
    if (n1) {
        using v_t = vec<_T, _N>;
        using va_t = vec<_A, _N>;
        const size_t n4= s & ~(_N4-1);
        va_t r0(_A(0));
        if (n4) {
            va_t r1(_A(0)), r2(_A(0)), r3(_A(0));
            for (size_t i=0; i<n4; i+=4*_N) {
                v_t a0 = mem<v_t>::load(a+i+0*_N);
                v_t a1 = mem<v_t>::load(a+i+1*_N);
                v_t a2 = mem<v_t>::load(a+i+2*_N);
                v_t a3 = mem<v_t>::load(a+i+3*_N);
                if constexpr (_A_is_T) {
                    r0 += a0;
                    r1 += a1;
                    r2 += a2;
                    r3 += a3;
                } else {
                    r0 += cftal::cvt<va_t>(a0);
                    r1 += cftal::cvt<va_t>(a1);
                    r2 += cftal::cvt<va_t>(a2);
                    r3 += cftal::cvt<va_t>(a3);
                }
            }
            r2 += r3;
            r0 += r1;
            r0 += r2;
        }
        for (size_t i=n4; i<n1; i+= _N) {
            v_t a0 = mem<v_t>::load(a+i+0*_N);
            if constexpr (_A_is_T) {
                r0 += a0;
            } else {
                r0 += cftal::cvt<va_t>(a0);
            }
        }
        r = hsum(r0);
    }
    for (size_t i=n1; i<s; ++i) {
        if constexpr (_A_is_T) {
            r += a[i];
        } else {
            r += _A(a[i]);
        }
    }
    return _T(r);
}

template <typename _T, typename _A>
_T
cftal::impl::
hsum(size_t s,
     const _T* a, int32_t stride_a, size_t offset_a)
{
    constexpr const size_t _N=max_vec_size_specialized<_T>();
    constexpr const size_t _N4=4*_N;

    if (__unlikely(stride_a==0)) {
        hsum_stride_zero();
    }
    if (__unlikely(stride_a==1)) {
        return impl::hsum<_T, _A>(s, a+offset_a);
    }
    constexpr const bool _A_is_T= std::is_same_v<_A, _T>;
    const size_t n1= s & ~(_N-1);
    _A r(0);
    if (n1) {
        using v_t = vec<_T, _N>;
        using va_t = vec<_A, _N>;
        using vi_t = vec<int32_t, _N>;
        const size_t n4= s & ~(_N4-1);
        va_t r0(_A(0));
        vi_t idx_a=
            impl::indices_from_stride<vi_t, int32_t>::create(stride_a);
        auto lck_a=make_variable_lookup_table<_T>(idx_a);
        if (n4) {
            va_t r1(_A(0)), r2(_A(0)), r3(_A(0));
            for (size_t i=0; i<n4; i+=4*_N) {
                v_t a0 = lck_a.fromp(a+(i+0*_N)*stride_a+offset_a);
                v_t a1 = lck_a.fromp(a+(i+1*_N)*stride_a+offset_a);
                v_t a2 = lck_a.fromp(a+(i+2*_N)*stride_a+offset_a);
                v_t a3 = lck_a.fromp(a+(i+3*_N)*stride_a+offset_a);

                if constexpr (_A_is_T) {
                    r0 += a0;
                    r1 += a1;
                    r2 += a2;
                    r3 += a3;
                } else {
                    r0 += cftal::cvt<va_t>(a0);
                    r1 += cftal::cvt<va_t>(a1);
                    r2 += cftal::cvt<va_t>(a2);
                    r3 += cftal::cvt<va_t>(a3);
                }
            }
            r2 += r3;
            r0 += r1;
            r0 += r2;
        }
        for (size_t i=n4; i<n1; i+= _N) {
            v_t a0 = lck_a.fromp(a+(i+0*_N)*stride_a+offset_a);
            if constexpr (_A_is_T) {
                r0 += a0;
            } else {
                r0 += cftal::cvt<va_t>(a0);
            }
        }
        r = hsum(r0);
    }
    for (size_t i=n1; i<s; ++i) {
        if constexpr (_A_is_T) {
            r += a[i*stride_a+offset_a];
        } else {
            r += _A(a[i*stride_a+offset_a]);
        }
    }
    return _T(r);
}

// Local variables:
// mode: c++
// end:
#endif
