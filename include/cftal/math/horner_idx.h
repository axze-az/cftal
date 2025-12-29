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
#if !defined (__CFTAL_MATH_HORNER_IDX_H__)
#define __CFTAL_MATH_HORNER_IDX_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/math/horner.h>

namespace cftal {
    namespace math {

        // data layout of tbl[]:
        // /* idx == 0 */ a_{n-1}, a_{n-2}, ... a_1, a_0,
        //                pad_{n-1}, pad_{n-2}, ... pad_1, pad_0,
        // /* idx == 1 */ a_{n-1}, a_{n-2}, ... a_1, a_0,
        //                pad_{n-1}, pad_{n-2}, ... pad_1, pad_0
        // lookup should be able to access the values via
        // lck.from(tbl + i)
        template <std::size_t _N,
                  typename _X, typename _LCK, typename _C>
        _X
        horner_idx(const _X& x, const _LCK& lck, const _C* tbl);

        // data layout of tbl[]:
        // /* idx == 0 */ a_{n-1}, a_{n-2}, ... a_1, a_0,
        //                pad_{n-1}, pad_{n-2}, ... pad_1, pad_0,
        // /* idx == 1 */ a_{n-1}, a_{n-2}, ... a_1, a_0,
        //                pad_{n-1}, pad_{n-2}, ... pad_1, pad_0,
        template <std::size_t _N,
                  typename _X, typename _LCK, typename _C>
        _X
        horner2_idx(const _X& x, const _X& x2,
                    const _LCK& lck, const _C* tbl);

        // data layout of tbl[]:
        // /* idx == 0 */ a_{n-1}, a_{n-2}, ... a_1, a_0,
        //                pad_{n-1}, pad_{n-2}, ... pad_1, pad_0,
        // /* idx == 1 */ a_{n-1}, a_{n-2}, ... a_1, a_0,
        //                pad_{n-1}, pad_{n-2}, ... pad_1, pad_0,
        template <std::size_t _N,
                  typename _X, typename _LCK, typename _C>
        _X
        horner4_idx(const _X& x, const _X& x2, const _X& x4,
                    const _LCK& lck, const _C* tbl);
    }
}


template <std::size_t _N, typename _X, typename _LCK, typename _C>
inline
_X
cftal::math::
horner_idx(const _X& x,
           const _LCK& lck, const _C* tbl)
{
    _X c0 = lck.fromp(tbl+0);
    _X r=c0;
#pragma GCC unroll 256
#pragma clang unroll(256)
    for (std::size_t i=1; i<_N; ++i) {
        _X ci=lck.fromp(tbl+i);
        r = horner(x, r, ci);
    }
    return r;
}

template <std::size_t _N, typename _X, typename _LCK, typename _C>
inline
_X
cftal::math::
horner2_idx(const _X& x, const _X& x2,
            const _LCK& lck, const _C* tbl)
{
    static_assert(_N > 1,
                  "invalid call to horner2_idx(x, x2, lookup, array)");
    _X c0= lck.fromp(tbl+0);
    _X c1= lck.fromp(tbl+1);
    _X r0= c0;
    _X r1= c1;
    constexpr const std::size_t _NE= _N & ~std::size_t(1);
#pragma GCC unroll 256
#pragma clang unroll(256)
    for (std::size_t i=2; i<_NE; i+=2) {
        _X ci=lck.fromp(tbl+i);
        _X cip1=lck.fromp(tbl+i+1);
        r0= horner(x2, r0, ci);
        r1= horner(x2, r1, cip1);
    }
    _X r = horner(x, r0, r1);
    if (_N & 1) {
        _X cnm1=lck.fromp(tbl+_N-1);
        r = horner(x, r, cnm1);
    }
    return r;
}

template <std::size_t _N, typename _X, typename _LCK, typename _C>
inline
_X
cftal::math::
horner4_idx(const _X& x, const _X& x2, const _X& x4,
            const _LCK& lck, const _C* tbl)
{
    static_assert(_N > 3,
                  "invalid call to horner4_idx(x, x2, x4, lookup, array)");
    _X c0= lck.fromp(tbl+0);
    _X c1= lck.fromp(tbl+1);
    _X c2= lck.fromp(tbl+2);
    _X c3= lck.fromp(tbl+3);
    _X r0= c0;
    _X r1= c1;
    _X r2= c2;
    _X r3= c3;
    constexpr const std::size_t _NE= _N & ~std::size_t(3);
#pragma GCC unroll 256
#pragma clang unroll(256)
    for (std::size_t i=4; i<_NE; i+=4) {
        _X ci=lck.fromp(tbl+i);
        _X cip1=lck.fromp(tbl+i+1);
        _X cip2=lck.fromp(tbl+i+2);
        _X cip3=lck.fromp(tbl+i+3);
        r0= horner(x4, r0, ci);
        r1= horner(x4, r1, cip1);
        r2= horner(x4, r2, cip2);
        r3= horner(x4, r3, cip3);
    }
    _X r02 = horner(x2, r0, r2);
    _X r13 = horner(x2, r1, r3);
    _X r= horner(x, r02, r13);
    constexpr const std::size_t _NR= _N & std::size_t(3);
    if (_NR == 3) {
        _X cnm2=lck.fromp(tbl+_N-2);
        _X cnm3=lck.fromp(tbl+_N-3);
        _X cnm1=lck.fromp(tbl+_N-1);
        _X a = horner(x2, r, cnm2);
        _X b = horner(x2, cnm3, cnm1);
        r = horner(x, a, b);
    }
    if (_NR == 2) {
        _X cnm2=lck.fromp(tbl+_N-2);
        _X cnm1=lck.fromp(tbl+_N-1);
        _X a = horner(x2, r, cnm1);
        r = horner(x, cnm2, a);
    }
    if (_NR == 1) {
        _X cnm1=lck.fromp(tbl+_N-1);
        r = horner(x, r, cnm1);
    }
    return r;
}

// Local Variables:
// mode: c++
// end:
#endif
