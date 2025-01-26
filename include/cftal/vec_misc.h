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
#if !defined (__CFTAL_VEC_MISC_H__)
#define __CFTAL_VEC_MISC_H__

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/type_traits.h>

namespace cftal {

    // horizontal add 
    template <typename _T, std::size_t _N>
    _T hadd(const vec<_T, _N>& n);

    // horizontal add 
    template <typename _T>
    _T hadd(const vec<_T, 1>& n);

    // dot product
    template <typename _T, std::size_t _N>
    _T dot_product(const vec<_T, _N>& a, const vec<_T, _N>& b);

    template <typename _T>
    _T dot_product(const vec<_T, 1>& a, const vec<_T, 1>& b);

    // execute on_true or on_false in dependence of m
    template <typename _T, std::size_t _N,
              typename _ON_TRUE, typename _ON_FALSE>
    auto
    select_branch(const vec<_T, _N>& m,
                  _ON_TRUE on_true, _ON_FALSE on_false)
        -> typename std::invoke_result<_ON_TRUE()>::type;

    // execute on_true or on_false in dependence of m
    template <typename _T, typename _ON_TRUE, typename _ON_FALSE>
    auto
    select_branch(const vec<_T, 1>& m,
                  _ON_TRUE on_true, _ON_FALSE on_false)
        -> typename std::invoke_result<_ON_TRUE()>::type;

    // execute a scalar function f(x) on every element of x
    template <typename _T, size_t _N, typename _F>
    vec<_T, _N>
    call_scalar_func(const vec<_T, _N>& x, _F f);

    // execute a scalar function f(x, y) on every element of x, y
    template <typename _TR, typename _TX, typename _TY, size_t _N, typename _F>
    vec<_TR, _N>
    call_scalar_func(const vec<_TX, _N>& x,
                     const vec<_TY, _N>& y,
                     _F f);

    // transpose a 4x4 matrix
    template <class _V4>
    void
    transpose_4x4(_V4& r0, _V4& r1, _V4& r2, _V4& r3);

    // transpose a 8x8 matrix
    template <class _V8>
    void
    transpose_8x8(_V8& r0, _V8& r1, _V8& r2, _V8& r3,
                  _V8& r4, _V8& r5, _V8& r6, _V8& r7);

    // r0-r3, a0-a3, b0-b3 rows/columns of a 4x4 matrix
    template <class _V4, class _T>
    void
    mat_mul_1x4(_V4& r0,
                const _T* a0,
                const _V4& b0, const _V4& b1, const _V4& b2, const _V4& b3);

    // r0-r3, a0-a3, b0-b3 rows/columns of a 4x4 matrix
    template <class _V4>
    void
    mat_mul_4x4(_V4& r0, _V4& r1, _V4& r2, _V4& r3,
                const _V4& a0, const _V4& a1, const _V4& a2, const _V4& a3,
                const _V4& b0, const _V4& b1, const _V4& b2, const _V4& b3);

}

template <typename _T, std::size_t _N>
inline
_T
cftal::hadd(const vec<_T, _N>& v)
{
    vec<_T, _N/2> t=high_half(v)+low_half(v);
    return hadd(t);
}

template <typename _T>
inline
_T
cftal::hadd(const vec<_T, 1>& v)
{
    return v();
}

template <typename _T, std::size_t _N>
inline
_T
cftal::dot_product(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return
        dot_product(high_half(a),
                    high_half(b)) +
        dot_product(low_half(a),
                    low_half(b));
}

template <typename _T>
inline
_T
cftal::dot_product(const vec<_T, 1>& a, const vec<_T, 1>& b)
{
    return a()*b();
}

template <typename _T, std::size_t _N, typename _ON_TRUE, typename _ON_FALSE>
auto
cftal::select_branch(const vec<_T, _N>& m,
                     _ON_TRUE on_true, _ON_FALSE on_false)
    -> typename std::invoke_result<_ON_TRUE()>::type
{
    using v_t = typename std::invoke_result<_ON_TRUE()>::type;
    v_t r;
#if 1
    v_t t=on_true();
    v_t f=on_false();
    r=select(m, t, f);
#else
    if (all_of(m)) {
        r=on_true();
    } else if (none_of(m)) {
        r=on_false();
    } else {
        v_t t=on_true();
        v_t f=on_false();
        r=select(m, t, f);
    }
#endif
    return r;
}

template <typename _T, typename _ON_TRUE, typename _ON_FALSE>
auto
cftal::select_branch(const vec<_T, 1>& m,
                     _ON_TRUE on_true, _ON_FALSE on_false)
    -> typename std::invoke_result<_ON_TRUE()>::type
{
    using mvt= typename vec<_T, 1>::value_type;
    if (impl::mask_to_bool<mvt>::v(m()))
        return on_true();
    return on_false();
}

template <typename _T, size_t _N, typename _F>
cftal::vec<_T, _N>
cftal::call_scalar_func(const vec<_T, _N>& x, _F f)
{
    using vf_type = vec<_T, _N>;
    struct alignas(_N*sizeof(_T)) v_x {
        _T _a[_N];
    } ax, ar;
    mem<vf_type>::store(ax._a, x);
    for (std::size_t i=0; i<_N; ++i) {
        ar._a[i] = f(ax._a[i]);
    }
    vf_type r=mem<vf_type>::load(ar._a, _N);
    return r;
}

template <typename _TR, typename _TX, typename _TY, size_t _N, typename _F>
cftal::vec<_TR, _N>
cftal::call_scalar_func(const vec<_TX, _N>& x, const vec<_TY, _N>& y, _F f)
{
    using vx_type = vec<_TX, _N>;
    using vy_type = vec<_TY, _N>;
    using vr_type = vec<_TR, _N>;
    struct alignas(_N*sizeof(_TX)) v_x {
        _TX _a[_N];
    } ax;
    struct alignas(_N*sizeof(_TY)) v_y {
        _TY _a[_N];
    } ay;
    using vr_type = vec<_TR, _N>;
    struct alignas(_N*sizeof(_TR)) v_r {
        _TR _a[_N];
    } ar;
    mem<vx_type>::store(ax._a, x);
    mem<vy_type>::store(ay._a, y);
    for (std::size_t i=0; i<_N; ++i) {
        ar._a[i] = f(ax._a[i], ay._a[i]);
    }
    vr_type r=mem<vr_type>::load(ar._a, _N);
    return r;
}

template <class _V4>
inline
void cftal::transpose_4x4(_V4& r0, _V4& r1, _V4& r2, _V4& r3)
{
    // r0: 0x00, 0x01, 0x02, 0x03
    // r1: 0x10, 0x11, 0x12, 0x13
    // r2: 0x20, 0x21, 0x22, 0x23
    // r3: 0x30, 0x31, 0x32, 0x33

    // first pass:
    // 0x00 0x10 0x01 0x11
    _V4 t0(permute<0, 4+0, 1, 4+1>(r0, r1));
    // 0x02 0x12 0x03 0x13
    _V4 t1(permute<2, 4+2, 3, 4+3>(r0, r1));
    // 0x20 0x30 0x21 0x31
    _V4 t2(permute<0, 4+0, 1, 4+1>(r2, r3));
    // 0x22 0x32 0x23 0x33
    _V4 t3(permute<2, 4+2, 3, 4+3>(r2, r3));

    // second pass:
    // 0x00 0x10 0x20 0x30
    r0 = permute<0, 1, 4+0, 4+1>(t0, t2);
    // 0x01 0x11 0x21 0x31
    r1 = permute<2, 3, 4+2, 4+3>(t0, t2);
    // 0x02 0x12 0x22 0x32
    r2 = permute<0, 1, 4+0, 4+1>(t1, t3);
    // 0x03 0x13 0x23 0x33
    r3 = permute<2, 3, 4+2, 4+3>(t1, t3);
}

template <class _V8>
inline
void cftal::transpose_8x8(_V8& r0, _V8& r1, _V8& r2, _V8& r3,
                          _V8& r4, _V8& r5, _V8& r6, _V8& r7)
{
    // r0: 0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07
    // r1: 0x10 0x11 0x12 0x13 0x14 0x15 0x16 0x17
    // r2: 0x20 0x21 0x22 0x23 0x24 0x25 0x26 0x27
    // r3: 0x30 0x31 0x32 0x33 0x34 0x35 0x36 0x37
    // r4: 0x40 0x41 0x42 0x43 0x44 0x45 0x46 0x47
    // r5: 0x50 0x51 0x52 0x53 0x54 0x55 0x56 0x57
    // r6: 0x60 0x61 0x62 0x63 0x64 0x65 0x66 0x67
    // r7: 0x70 0x71 0x72 0x73 0x74 0x75 0x76 0x77

    // pass 1
    // t0: 0x00 0x10 0x01 0x11 0x02 0x12 0x03 0x13
    _V8 t0(permute<0, 8+0, 1, 8+1, 2, 8+2, 3, 8+3>(r0, r1));
    // t1: 0x04 0x14 0x05 0x15 0x06 0x16 0x07 0x17
    _V8 t1(permute<4, 8+4, 5, 8+5, 6, 8+6, 7, 8+7>(r0, r1));
    // t2: 0x20 0x30 0x21 0x31 0x22 0x32 0x23 0x33
    _V8 t2(permute<0, 8+0, 1, 8+1, 2, 8+2, 3, 8+3>(r2, r3));
    // t3: 0x24 0x34 0x25 0x35 0x26 0x36 0x27 x37
    _V8 t3(permute<4, 8+4, 5, 8+5, 6, 8+6, 7, 8+7>(r2, r3));
    // t4: 0x40 0x50 0x41 0x51 0x42 0x52 0x43 0x53
    _V8 t4(permute<0, 8+0, 1, 8+1, 2, 8+2, 3, 8+3>(r4, r5));
    // t5: 0x44 0x54 0x45 0x55 0x46 0x56 0x47 0x57
    _V8 t5(permute<4, 8+4, 5, 8+5, 6, 8+6, 7, 8+7>(r4, r5));
    // t6: 0x60 0x70 0x61 0x71 0x62 0x72 0x63 0x73
    _V8 t6(permute<0, 8+0, 1, 8+1, 2, 8+2, 3, 8+3>(r6, r7));
    // t7: 0x64 0x74 0x65 0x75 0x66 0x76 0x67 0x77
    _V8 t7(permute<4, 8+4, 5, 8+5, 6, 8+6, 7, 8+7>(r6, r7));

    // pass 2
    // s0: 0x00 0x10 0x20 0x30 0x01 0x11 0x21 0x31
    _V8 s0(permute<0, 1, 8+0, 8+1, 2, 3, 8+2, 8+3>(t0, t2));
    // s1: 0x02 0x12 0x22 0x32 0x03 0x13 0x23 0x33
    _V8 s1(permute<4, 5, 8+4, 8+5, 6, 7, 8+6, 8+7>(t0, t2));
    // s2: 0x04 0x14 0x24 0x34 0x05 0x15 0x25 0x35
    _V8 s2(permute<0, 1, 8+0, 8+1, 2, 3, 8+2, 8+3>(t1, t3));
    // s3: 0x06 0x16 0x26 0x36 0x07 0x17 0x27 x37
    _V8 s3(permute<4, 5, 8+4, 8+5, 6, 7, 8+6, 8+7>(t1, t3));
    // s4: 0x40 0x50 0x60 0x70 0x41 0x51 0x61 0x71
    _V8 s4(permute<0, 1, 8+0, 8+1, 2, 3, 8+2, 8+3>(t4, t6));
    // s5: 0x42 0x52 0x62 0x72 0x43 0x53 0x63 0x73
    _V8 s5(permute<4, 5, 8+4, 8+5, 6, 7, 8+6, 8+7>(t4, t6));
    // s6: 0x44 0x54 0x64 0x74 0x45 0x55 0x65 0x75
    _V8 s6(permute<0, 1, 8+0, 8+1, 2, 3, 8+2, 8+3>(t5, t7));
    // s7: 0x46 0x56 0x66 0x76 0x47 0x57 0x67 0x77
    _V8 s7(permute<4, 5, 8+4, 8+5, 6, 7, 8+6, 8+7>(t5, t7));

    // pass 3
    // r0: 0x00 0x10 0x20 0x30 0x40 0x50 0x60 0x70
    r0 = permute<0, 1, 2, 3, 8+0, 8+1, 8+2, 8+3>(s0, s4);
    // r1: 0x01 0x11 0x21 0x31 0x41 0x51 0x61 0x71
    r1 = permute<4, 5, 6, 7, 8+4, 8+5, 8+6, 8+7>(s0, s4);
    // r2: 0x02 0x12 0x22 0x32 0x42 0x52 0x62 0x72
    r2 = permute<0, 1, 2, 3, 8+0, 8+1, 8+2, 8+3>(s1, s5);
    // r3: 0x03 0x13 0x23 0x33 0x43 0x53 0x63 0x73
    r3 = permute<4, 5, 6, 7, 8+4, 8+5, 8+6, 8+7>(s1, s5);
    // r4: 0x04 0x14 0x24 0x34 0x44 0x54 0x64 0x74
    r4 = permute<0, 1, 2, 3, 8+0, 8+1, 8+2, 8+3>(s2, s6);
    // r5: 0x05 0x15 0x25 0x35 0x45 0x55 0x65 0x75
    r5 = permute<4, 5, 6, 7, 8+4, 8+5, 8+6, 8+7>(s2, s6);
    // r6: 0x06 0x16 0x26 0x36 0x46 0x56 0x66 0x76
    r6 = permute<0, 1, 2, 3, 8+0, 8+1, 8+2, 8+3>(s3, s7);
    // r7: 0x07 0x17 0x27 x37 0x47 0x57 0x67 0x77
    r7 = permute<4, 5, 6, 7, 8+4, 8+5, 8+6, 8+7>(s3, s7);
}

template <class _V4, class _T>
inline
void
cftal::
mat_mul_1x4(_V4& r0,
            const _T* a0,
            const _V4& b0, const _V4& b1, const _V4& b2, const _V4& b3)
{
    // layout in memory:
    //                       b00, b01, b02, b03,
    //                       b10, b11, b12, b13,
    //                       b20, b21, b22, b23,
    //                       b30, b31, b32, b33
    //
    // a00, a01, a02, a03,   r00, r01, r02, r03,

    // r00 = a00*b00 + a01*b10 + a02*b20 + a03*b30
    // r01 = a00*b01 + a01*b11 + a02*b21 + a03*b31
    // r02 = a00*b02 + a01*b12 + a02*b22 + a03*b32
    // r03 = a00*b03 + a01*b13 + a02*b23 + a03*b33

    r0= _V4(a0[0]) * b0 +
        _V4(a0[1]) * b1 +
        _V4(a0[2]) * b2 +
        _V4(a0[3]) * b3;
}

template <class _V4>
inline
void
cftal::
mat_mul_4x4(_V4& r0, _V4& r1, _V4& r2, _V4& r3,
            const _V4& a0, const _V4& a1, const _V4& a2, const _V4& a3,
            const _V4& b0, const _V4& b1, const _V4& b2, const _V4& b3)
{
    // layout in memory:
    //                       b00, b01, b02, b03,
    //                       b10, b11, b12, b13,
    //                       b20, b21, b22, b23,
    //                       b30, b31, b32, b33
    //
    // a00, a01, a02, a03,   r00, r01, r02, r03,
    // a10, a11, a12, a13,   r10, r11, r12, r13,
    // a20, a21, a22, a23,   r20, r21, r22, r23,
    // a30, a31, a32, a33    r30, r31, r32, r33

    // r00 = a00*b00 + a01*b10 + a02*b20 + a03*b30
    // r01 = a00*b01 + a01*b11 + a02*b21 + a03*b31
    // r02 = a00*b02 + a01*b12 + a02*b22 + a03*b32
    // r03 = a00*b03 + a01*b13 + a02*b23 + a03*b33

    r0= permute<0, 0, 0, 0>(a0) * b0 +
        permute<1, 1, 1, 1>(a0) * b1 +
        permute<2, 2, 2, 2>(a0) * b2 +
        permute<3, 3, 3, 3>(a0) * b3;

    // r10 = a10*b00 + a11*b10 + a12*b20 + a13*b30
    // r11 = a10*b01 + a11*b11 + a12*b21 + a13*b31
    // r12 = a10*b02 + a11*b12 + a12*b22 + a13*b32
    // r13 = a10*b03 + a11*b13 + a12*b23 + a13*b33

    r1= permute<0, 0, 0, 0>(a1) * b0 +
        permute<1, 1, 1, 1>(a1) * b1 +
        permute<2, 2, 2, 2>(a1) * b2 +
        permute<3, 3, 3, 3>(a1) * b3;

    // r20 = a20*b00 + a21*b10 + a22*b20 + a23*b30
    // r21 = a20*b01 + a21*b11 + a22*b21 + a23*b31
    // r22 = a20*b02 + a21*b12 + a22*b22 + a23*b32
    // r23 = a20*b03 + a21*b13 + a22*b23 + a23*b33

    r2= permute<0, 0, 0, 0>(a2) * b0 +
        permute<1, 1, 1, 1>(a2) * b1 +
        permute<2, 2, 2, 2>(a2) * b2 +
        permute<3, 3, 3, 3>(a2) * b3;

    // r30 = a30*b00 + a31*b10 + a32*b20 + a33*b30
    // r31 = a30*b01 + a31*b11 + a32*b21 + a33*b31
    // r32 = a30*b02 + a31*b12 + a32*b22 + a33*b32
    // r33 = a30*b03 + a31*b13 + a32*b23 + a33*b33

    r3= permute<0, 0, 0, 0>(a3) * b0 +
        permute<1, 1, 1, 1>(a3) * b1 +
        permute<2, 2, 2, 2>(a3) * b2 +
        permute<3, 3, 3, 3>(a3) * b3;
}

// Local variables:
// mode: c++
// end:
#endif
