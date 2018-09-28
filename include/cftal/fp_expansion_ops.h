//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_FP_EXPANSION_OPS_H__)
#define __CFTAL_FP_EXPANSION_OPS_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <iosfwd>

namespace cftal {

    template <typename _T, std::size_t _N>
    void
    vec_sum(fp_expansion<_T, _N>& r, std::size_t m);

    template <typename _T, std::size_t _N>
    void
    vec_sum(fp_expansion<_T, _N>& r);

    template <typename _T, std::size_t _N>
    void
    vec_sum_cond(fp_expansion<_T, _N>& r);

    template <typename _T, std::size_t _N>
    bool
    vec_sum_err_branch(fp_expansion<_T, _N>& r);

    template <typename _T>
    void
    normalize(fp_expansion<_T, 2>& r);

    template <typename _T, std::size_t _N>
    void
    normalize(fp_expansion<_T, _N>& r);

    template <typename _T>
    void
    normalize_random(fp_expansion<_T, 2>& r);

    template <typename _T, std::size_t _N>
    void
    normalize_random(fp_expansion<_T, _N>& r);

    template <std::size_t _M,
              typename _T, std::size_t _N0, std::size_t _N1>
    fp_expansion<_T, _M>
    add(const fp_expansion<_T, _N0>& a, const fp_expansion<_T, _N1>& b);

}

template <typename _T, std::size_t _N>
__attribute__((__always_inline__))
inline
void
cftal::
vec_sum(fp_expansion<_T, _N>& r, std::size_t n)
{
    using d_ops=impl::d_real_ops<_T,
                                 d_real_traits<_T>::fma>;
    _T s;
    d_ops::add12(s, r[n-1], r[n-2], r[n-1]);
    if (n >2) {
        for (std::size_t i= 2; i<n; ++i) {
            d_ops::add12(s, r[n-i], r[n-i-1], s);
        }
    }
    r[0] = s;
}


template <typename _T, std::size_t _N>
__attribute__((__always_inline__))
inline
void
cftal::
vec_sum(fp_expansion<_T, _N>& r)
{
    using d_ops=impl::d_real_ops<_T,
                                 d_real_traits<_T>::fma>;
    _T s;
    d_ops::add12(s, r[_N-1], r[_N-2], r[_N-1]);
    for (std::size_t i= 2; i<_N; ++i) {
        d_ops::add12(s, r[_N-i], r[_N-i-1], s);
    }
    r[0] = s;
}

template <typename _T, std::size_t _N>
__attribute__((__always_inline__))
inline
void
cftal::
vec_sum_cond(fp_expansion<_T, _N>& r)
{
    using d_ops=impl::d_real_ops<_T,
                                 d_real_traits<_T>::fma>;
    _T s;
    d_ops::add12cond(s, r[_N-1], r[_N-2], r[_N-1]);
    for (std::size_t i= 2; i<_N; ++i) {
        d_ops::add12cond(s, r[_N-i], r[_N-i-1], s);
    }
    r[0] = s;
}

template <typename _T, std::size_t _N>
__attribute__((__always_inline__))
inline
bool
cftal::
vec_sum_err_branch(fp_expansion<_T, _N>& r)
{
    using d_ops=impl::d_real_ops<_T,
                                 d_real_traits<_T>::fma>;
    _T e=r[0], rt;
    bool sort_req=false;
// #pragma GCC unroll(1<<16-1)
// #pragma clang loop unroll(enable)
    for (std::size_t i=0; i<_N-1; ++i) {
        d_ops::add12(rt, e, e, r[i+1]);
        auto noerr = e == _T(0);
        sort_req |= any_of(noerr);
        r[i] = select(noerr, _T(0), rt);
        e = select(noerr, rt, e);
    }
    r[_N-1] = e;
    return sort_req;
}

template <typename _T>
__attribute__((__always_inline__))
inline
void
cftal::
normalize(fp_expansion<_T, 2>& r)
{
    using d_ops=impl::d_real_ops<_T,
                                 d_real_traits<_T>::fma>;
    d_ops::add12(r[0], r[1], r[0], r[1]);
}

template <typename _T, std::size_t _N>
__attribute__((__always_inline__))
inline
void
cftal::
normalize(fp_expansion<_T, _N>& r)
{
    vec_sum(r);
    auto srt=vec_sum_err_branch(r);
    if (srt) {
        sort_lanes(r, greater_than_mag<_T>());
    }
}

template <typename _T>
__attribute__((__always_inline__))
inline
void
cftal::
normalize_random(fp_expansion<_T, 2>& r)
{
    using d_ops=impl::d_real_ops<_T,
                                 d_real_traits<_T>::fma>;
    d_ops::add12cond(r[0], r[1], r[0], r[1]);
}

template <typename _T, std::size_t _N>
__attribute__((__always_inline__))
inline
void
cftal::
normalize_random(fp_expansion<_T, _N>& r)
{
    for (std::size_t i=2; i<_N; ++i)
        vec_sum(r, i);
    auto srt=vec_sum_err_branch(r);
    if (srt) {
        sort_lanes(r, greater_than_mag<_T>());
    }
}

template <std::size_t _M, typename _T, std::size_t _N0, std::size_t _N1>
__attribute__((__always_inline__))
inline
cftal::fp_expansion<_T, _M>
cftal::
add(const fp_expansion<_T, _N0>& a, const fp_expansion<_T, _N1>& b)
{
    // static_assert(_M <= _N0+_N1, "constraint failed");
    const std::size_t _N = _N0 + _N1;
    fp_expansion<_T, _N> t;
    for (std::size_t i=0; i<_N0; ++i)
        t[i] = a[i];
    for (std::size_t i=0; i<_N1; ++i)
        t[i+_N0]=b[i];
    sort_lanes(t, greater_than_mag<_T>());
    normalize(t);
    fp_expansion<_T, _M> r;
    const std::size_t _R=_N < _M ? _N : _M;
    for (std::size_t i=0; i<_R; ++i)
        r[i] = t[i];
    return r;
}


template <typename _T>
__attribute__((__always_inline__))
inline
void
cftal::
vec_sum(_T& d0, _T& d1, _T& d2, _T& d3, _T& d4,
        const _T& s0, const _T& s1,
        const _T& s2, const _T& s3,
        const _T& s4)
{
    using d_ops=impl::d_real_ops<_T,
                                 d_real_traits<_T>::fma>;
    _T s;
    d_ops::add12(s, d4, s3, s4);
    d_ops::add12(s, d3, s2, s);
    d_ops::add12(s, d2, s1, s);
    d_ops::add12(d0, d1, s0, s);
}

template <typename _T>
__attribute__((__always_inline__))
inline
void
cftal::
vec_sum(_T& d0, _T& d1, _T& d2, _T& d3,
        _T& d4, _T& d5, _T& d6, _T& d7,
        const _T& s0, const _T& s1,
        const _T& s2, const _T& s3,
        const _T& s4, const _T& s5,
        const _T& s6, const _T& s7)
{
    using d_ops=impl::d_real_ops<_T,
                                 d_real_traits<_T>::fma>;
    _T s;
    d_ops::add12(s, d7, s6, s7);
    d_ops::add12(s, d6, s5, s);
    d_ops::add12(s, d5, s4, s);
    d_ops::add12(s, d4, s3, s);
    d_ops::add12(s, d3, s2, s);
    d_ops::add12(s, d2, s1, s);
    d_ops::add12(d0, d1, s0, s);
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_FP_EXPANSION_OPS_H__
