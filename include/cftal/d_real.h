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
#if !defined (__CFTAL_D_REAL_H__)
#define __CFTAL_D_REAL_H__ 1

#include <cftal/config.h>
#include <cftal/d_real_traits.h>
#include <cftal/std_types.h>
#include <cftal/select.h>
#include <cftal/as.h>
#include <cftal/constants.h>
#include <cftal/fp_expansion.h>
#include <cmath>
#include <cftal/type_traits.h>
#include <limits>

namespace cftal {

    using std::fma;

    // fused multiply and subtract. return a*b -c
    template <class _T>
    _T fms(const _T& a, const _T& b, const _T& c) {
        return fma(a, b, -c);
    }

    // negated fused multipy and add. return -(a*b) + c = c - a*b;
    template <class _T>
    _T nfma(const _T& a, const _T& b, const _T& c) {
        return fma(-a, b, c);
    }

    // negated fused multipy and add. return -(a*b) - c = -c - a*b
    template <class _T>
    _T nfms(const _T& a, const _T& b, const _T& c) {
        return fma(-a, b, -c);
    }


    // specialization of a fp_expansion with 2 elements
    template <typename _T>
    class fp_expansion<_T, 2> {
        _T _e[2];
    public:
        using value_type = _T;
        constexpr fp_expansion() = default;

        template <typename _U>
        constexpr
        fp_expansion(const fp_expansion<_U, 2>& r) : _e{_T(r[0]), _T(r[1])} {}

        constexpr
        fp_expansion(const _T& h, const _T& l) : _e{h, l} {}
        constexpr
        fp_expansion(const _T& h) : _e{h, _T(0.0)} {}

        constexpr
        const _T& operator[](std::size_t i) const {
            return _e[i];
        }
        _T& operator[](std::size_t i) {
            return _e[i];
        }
        constexpr
        const _T* data() const {
            return _e;
        }
        _T* data() {
            return _e;
        }
    };

    // the double real class template
    template <typename _T>
    using d_real = fp_expansion<_T, 2>;

    // basic operations for double real class independent
    // of fused multiply and add
    template <class _T>
    struct d_real_ops_common {

        // return s + r = a + b
        // with |a| > |b|
        static
        void
        add12(_T& s, _T& r, const _T& a, const _T& b);

        // return s + r = a + b
        static
        void
        add12cond(_T& s, _T& r, const _T& a, const _T& b);

        // return (zh, zl) = (xh, xl) + (yh, yl)
        // |xh| > |yh|
        static
        void
        add22(_T& zh, _T& zl,
              const _T& xh, const _T& xl,
              const _T& yh, const _T& yl);

        // return (zh, zl) = (xh, xl) + (yh, yl)
        // |xh| > |yh|
        static
        void
        add22hp(_T& zh, _T& zl,
                const _T& xh, const _T& xl,
                const _T& yh, const _T& yl);

        // return (zh, zl) = (xh, xl) + (yh, yl)
        static
        void
        add22cond(_T& zh, _T& zl,
                  const _T& xh, const _T& xl,
                  const _T& yh, const _T& yl);

        // return (zh, zl) = (xh, xl) + (yh, yl)
        static
        void
        add22condhp(_T& zh, _T& zl,
                    const _T& xh, const _T& xl,
                    const _T& yh, const _T& yl);

        // return (zh, zl) = a + (bh, bl)
        // with |a| > |bh|
        static
        void
        add122(_T& zh, _T& zl,
               const _T& a, const _T& bh, const _T& bl);

        // return (zh, zl) = a + (bh, bl)
        static
        void
        add122cond(_T& zh, _T& zl,
                   const _T& a, const _T& bh, const _T& bl);

        // return (zh, zl) = (ah, bl) + b
        // with |ah| > b
        static
        void
        add212(_T& zh, _T& zl,
               const _T& ah, const _T& al, const _T& b);

        // return (zh, zl) = (ah, bl) + b
        static
        void
        add212cond(_T& zh, _T& zl,
                   const _T& ah, const _T& al, const _T& b);

    };

    // fused muliply and add dependent operations for double
    // real arithmetic
    template <class _T, bool _FMA>
    struct d_real_ops_fma : public d_real_ops_common<_T> {
    };

    // fused muliply and add dependent operations for double
    // real arithmetic, specialization using no fma
    template <class _T>
    struct d_real_ops_fma<_T, false> : public d_real_ops_common<_T> {
        using base_type=d_real_ops_common<_T>;
        using my_type=d_real_ops_fma<_T, false>;

        using base_type::add12;
        using base_type::add12cond;
        using base_type::add22;
        using base_type::add22cond;
        using base_type::add122;

        // fused multiply and add emulation without error,
        // underflow and overflow handling
        static
        _T
        xfma(const _T& a, const _T& b, const _T& c);

        // error compensated square: u^2 = rh + rl
        static
        void
        sqr12(_T& rh, _T& rl, const _T& u);

        // error compensated mulitpliction u*v = rh + rl
        static
        void
        mul12(_T& rh, _T& rl, const _T& u, const _T& v);

        // return (rh, rl) = c+ a*b
        // requires |c| > |a*b|
        static
        void
        muladd12(_T& rh, _T& rl, const _T& c, const _T& a, const _T& b);

        // multiplication (rh, rl) = xh * (yh, yl)
        // without final normalization
        static
        void
        unorm_mul122(_T& rh, _T& rl,
                     const _T& xh,
                     const _T& yh, const _T& yl);

        // multiplication (rh, rl) = xh * (yh, yl)
        static
        void
        mul122(_T& rh, _T& rl,
               const _T& xh,
               const _T& yh, const _T& yl);

        // square (rh, rl) = (xh, xl)^2
        // without final normalization
        static
        void
        unorm_sqr22(_T& rh, _T& rl,
                    const _T& xh, const _T& xl);

        // square (rh, rl) = (xh, xl)^2
        static
        void
        sqr22(_T& rh, _T& rl,
              const _T& xh, const _T& xl);

        // multiplication (rh, rl) = (xh, xl) * (yh, yl)
        // without final normalization
        static
        void
        unorm_mul22(_T& rh, _T& rl,
                    const _T& xh, const _T& xl,
                    const _T& yh, const _T& yl);

        // multiplication (rh, rl) = (xh, xl) * (yh, yl)
        static
        void
        mul22(_T& rh, _T& rl,
              const _T& xh, const _T& xl,
              const _T& yh, const _T& yl);

        // reciprocal r = 1/(ah, al)
        static
        void
        rcp21(_T& r,
              const _T& ah, const _T& al);

        // square r = (ah, al)^2
        static
        void
        sqr21(_T& rh,
              const _T& xh, const _T& xl);
    };

    // fused muliply and add dependent operations for double
    // real arithmetic, specialization using fma
    template <class _T>
    struct d_real_ops_fma<_T, true> : public d_real_ops_common<_T> {
        using base_type=d_real_ops_common<_T>;
        using my_type=d_real_ops_fma<_T, true>;

        using base_type::add12;
        using base_type::add12cond;
        using base_type::add22;
        using base_type::add22cond;
        using base_type::add122;

        // direct call to fma
        static
        _T
        xfma(const _T& a, const _T& b, const _T& c);

        // error compensated square: u^2 = rh + rl
        static
        void
        sqr12(_T& rh, _T& rl, const _T& u);

        // error compensated mulitpliction u*v = rh + rl
        static
        void
        mul12(_T& rh, _T& rl, const _T& u, const _T& v);

        // return (rh, rl) = c+ a*b
        // requires |c| > |a*b|
        static
        void
        muladd12(_T& rh, _T& rl, const _T& c, const _T& a, const _T& b);

        // multiplication (rh, rl) = xh * (yh, yl)
        // without final normalization
        static
        void
        unorm_mul122(_T& rh, _T& rl,
                     const _T& xh,
                     const _T& yh, const _T& yl);

        // multiplication (rh, rl) = xh * (yh, yl)
        static
        void
        mul122(_T& rh, _T& rl,
               const _T& xh,
               const _T& yh, const _T& yl);

        // square (rh, rl) = (xh, xl)^2
        // without final normalization
        static
        void
        unorm_sqr22(_T& rh, _T& rl,
                    const _T& xh, const _T& xl);

        // square (rh, rl) = (xh, xl)^2
        static
        void
        sqr22(_T& rh, _T& rl,
              const _T& xh, const _T& xl);

        // multiplication (rh, rl) = (xh, xl) * (yh, yl)
        // without final normalization
        static
        void
        unorm_mul22(_T& rh, _T& rl,
                    const _T& xh, const _T& xl,
                    const _T& yh, const _T& yl);

        // multiplication (rh, rl) = (xh, xl) * (yh, yl)
        static
        void
        mul22(_T& rh, _T& rl,
              const _T& xh, const _T& xl,
              const _T& yh, const _T& yl);

        // reciprocal r = 1/(ah, al)
        static
        void
        rcp21(_T& r,
              const _T& ah, const _T& al);

        // return (ah,al)^2
        static
        void
        sqr21(_T& r,
              const _T& ah, const _T& al);
    };

    // operation class for double real operations
    template <class _T, bool _FMA>
    struct d_real_ops : public d_real_ops_fma<_T, _FMA> {
        using base_type=d_real_ops_fma<_T, _FMA>;
        using my_type=d_real_ops<_T, _FMA>;

        using base_type::add12;
        using base_type::add12cond;
        using base_type::add22;
        using base_type::add22cond;
        using base_type::mul12;
        using base_type::mul122;
        using base_type::mul22;
        using base_type::add122;
        using base_type::add212;
        using base_type::rcp21;
        using base_type::sqr12;

        // c+ a*b
        static
        void
        muladd212(_T& rh, _T&rl,
                  const _T& ch, const _T& cl,
                  const _T& a,
                  const _T& bh, const _T& bl);

        // c+ a*b
        static
        void
        muladd22(_T& rh, _T&rl,
                 const _T& ch, const _T& cl,
                 const _T& ah, const _T& al,
                 const _T& bh, const _T& bl);

        // a/b
        static
        void
        div12(_T& rh, _T& rl,
              const _T& a, const _T& b);

        // a/b
        static
        void
        div212(_T& rh, _T& rl,
               const _T& ah, const _T& al,
               const _T& b);

        // a/b
        static
        void
        div122(_T& rh, _T& rl,
               const _T& ah,
               const _T& bh, const _T& bl);

        // a/b
        static
        void
        div22(_T& rh, _T& rl,
              const _T& ah, const _T& al,
              const _T& bh, const _T& bl);

        // a/b
        static
        void
        div21(_T& r,
              const _T& ah, const _T& al,
              const _T& bh, const _T& bl);

        // function for a/b with scaling
        static
        void
        __scaled_div22(_T& rh, _T& rl,
                       const _T& ah, const _T& al,
                       const _T& bh, const _T& bl);

        // a/b with scaling
        static
        void
        scaled_div22(_T& rh, _T& rl,
                     const _T& ah, const _T& al,
                     const _T& bh, const _T& bl);

        // reciprocal (rh, rl) = 1/a
        static
        void
        rcp12(_T& rh,  _T& rl,
              const _T& a);

        // reciprocal (rh, rl) = 1/(ah, al)
        static
        void
        rcp2(_T& rh,  _T& rl,
             const _T& ah, const _T& al);

        // square root (rh, rl) = sqrt((ah, al))
        static
        void
        sqrt12(_T& rh, _T& rl,
               const _T& ah);

        // square root (rh, rl) = sqrt((ah, al))
        static
        void
        sqrt2(_T& rh, _T& rl,
              const _T& ah, const _T& al);

        // square root rh = sqrt((ah, al))
        static
        void
        sqrt21(_T& rh,
               const _T& ah, const _T& al);
    };

    // unary minus
    template <typename _T>
    d_real<_T>
    operator-(const d_real<_T>& a);
    // unary plus
    template <typename _T>
    const d_real<_T>&
    operator+(const d_real<_T>& a);

    // addition
    template <typename _T>
    d_real<_T>
    operator+(const _T& a, const d_real<_T>& b);

    template <typename _T>
    d_real<_T>
    operator+(const d_real<_T>& a, const _T& b);

    template <typename _T>
    d_real<_T>
    operator+(const d_real<_T>& a,  const d_real<_T>& b);

    template <typename _T>
    d_real<_T>&
    operator+=(d_real<_T>& a, const _T& b);

    template <typename _T>
    d_real<_T>&
    operator+=(d_real<_T>& a, const d_real<_T>& b);

    // subtraction
    template <typename _T>
    d_real<_T>
    operator-(const _T& a, const d_real<_T>& b);

    template <typename _T>
    d_real<_T>
    operator-(const d_real<_T>& a, const _T& b);

    template <typename _T>
    d_real<_T>
    operator-(const d_real<_T>& a, const d_real<_T>& b);

    template <typename _T>
    d_real<_T>&
    operator-=(d_real<_T>& a, const _T& b);

    template <typename _T>
    d_real<_T>&
    operator-=(d_real<_T>& a, const d_real<_T>& b);

    // multiplication
    template <typename _T>
    d_real<_T>
    operator*(const _T& a, const d_real<_T>& b);

    template <typename _T>
    d_real<_T>
    operator*(const d_real<_T>& a, const _T& b);

    template <typename _T>
    d_real<_T>
    operator*(const d_real<_T>& a, const d_real<_T>& b);

    template <typename _T>
    d_real<_T>&
    operator*=(d_real<_T>& a, const _T& b);

    template <typename _T>
    d_real<_T>&
    operator*=(d_real<_T>& a, const d_real<_T>& b);

    // division
    template <typename _T>
    d_real<_T>
    operator/(const d_real<_T>& a, const d_real<_T>& b);

    template <typename _T>
    d_real<_T>
    operator/(const _T& a, const d_real<_T>& b);

    template <typename _T>
    d_real<_T>
    operator/(const d_real<_T>& a, const _T& b);

    template <typename _T>
    d_real<_T>&
    operator/=(d_real<_T>& a, const _T& b);

    template <typename _T>
    d_real<_T>&
    operator/=(d_real<_T>& a, const d_real<_T>& b);

    template <typename _T>
    d_real<_T> rcp(const d_real<_T>& r);

    template <typename _T>
    d_real<_T> abs(const d_real<_T>& r);
    template <typename _T>
    d_real<_T> rint(const d_real<_T>& r);
    template <typename _T>
    d_real<_T> floor(const d_real<_T>& r);
    template <typename _T>
    d_real<_T> ceil(const d_real<_T>& r);
    template <typename _T>
    d_real<_T> trunc(const d_real<_T>& r);

    template <typename _T>
    d_real<_T> powi(const d_real<_T>& r, int e);

    template <typename _T>
    d_real<_T> sqr(const d_real<_T>& r);
    template <typename _T>
    d_real<_T> mul_pwr2(const d_real<_T>& a, const _T& b);
    template <typename _T>
    d_real<_T> sqrt(const d_real<_T>& a);

    template <typename _T>
    std::enable_if_t<!std::is_same_v<typename d_real_traits<_T>::cmp_result_type,
                                     bool>,
                     d_real<_T> >
    select(const typename d_real_traits<_T>::cmp_result_type& m,
           const d_real<_T>& on_true,
           const d_real<_T>& on_false);

    template <typename _T>
    d_real<_T>
    select(const typename d_real_traits<_T>::cmp_result_type& m,
           const _T& on_true,
           const d_real<_T>& on_false);

    template <typename _T>
    d_real<_T>
    select(const typename d_real_traits<_T>::cmp_result_type& m,
           const d_real<_T>& on_true,
           const _T& on_false);

    template <typename _T>
    d_real<_T> min(const d_real<_T>& on_true,
                   const d_real<_T>& on_false);

    template <typename _T>
    d_real<_T> max(const d_real<_T>& on_true,
                   const d_real<_T>& on_false);
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_common<_T>::
add12(_T& s, _T& r, const _T& a, const _T& b)
{
#if 1
    _T _s = a + b;
    auto t = _s - a;
    _T _r = b - t;
    s = _s;
    r = _r;
#else
    _T _a = a;
    _T _b = b;
    s = _a + _b;
    _T t0 = s - _a;
    r = _b - t0;
#endif
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_common<_T>::
add12cond(_T& s, _T& r, const _T& a, const _T& b)
{
#if 1
    _T _s = a + b;
    auto u1 = _s - a;
    auto u2 = _s - u1;
    auto u3 = b - u1;
    auto u4 = a - u2;
    _T _r = u4 + u3;
    s = _s;
    r = _r;
#else
    _T _a= a;
    _T _b= b;
    s = _a + _b;
    _T _u1 = s - _a;
    _T _u2 = s - _u1;
    _T _u3 = _b - _u1;
    _T _u4 = _a - _u2;
    r = _u4 + _u3;
#endif
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_common<_T>::
add22(_T& zh, _T& zl,
      const _T& xh, const _T& xl,
      const _T& yh, const _T& yl)
{
    _T v1, v2;
    v1 = xh + yh;
    v2 = (((xh - v1) + yh) + yl) + xl;
    zh = v1 + v2;
    zl = (v1 - zh) + v2;
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_common<_T>::
add22hp(_T& zh, _T& zl,
        const _T& xh, const _T& xl,
        const _T& yh, const _T& yl)
{
    _T sh, sl;
    add12(sh, sl, xh, yh);
    _T th, tl;
    add12(th, tl, xl, yl);
    _T c = sl + th;
    _T vh, vl;
    add12(vh, vl, sh, c);
    _T w = tl +vl;
    add12(zh, zl, vh, w);
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_common<_T>::
add22cond(_T& zh, _T& zl,
          const _T& xh, const _T& xl,
          const _T& yh, const _T& yl)
{
    // sloppy add
    _T v1, v2;
    add12cond(v1, v2, xh, yh);
    _T v3 = xl + yl;
    _T v4 = v2 + v3;
    add12(zh, zl, v1, v4);
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_common<_T>::
add22condhp(_T& zh, _T& zl,
            const _T& xh, const _T& xl,
            const _T& yh, const _T& yl)
{
    _T sh, sl;
    add12cond(sh, sl, xh, yh);
    _T th, tl;
    add12cond(th, tl, xl, yl);
    _T c = sl + th;
    _T vh, vl;
    add12(vh, vl, sh, c);
    _T w = tl +vl;
    add12(zh, zl, vh, w);
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_common<_T>::
add122(_T& zh, _T& zl,
       const _T& a, const _T& bh, const _T& bl)
{
    _T _t1, _t2;
    add12(_t1,_t2, a, bh);
    _T _t3 = _t2 + (bl);
    add12(zh, zl,_t1,_t3);
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_common<_T>::
add122cond(_T& zh, _T& zl,
           const _T& a, const _T& bh, const _T& bl)
{
    _T _t1, _t2;
    add12cond(_t1,_t2, a, bh);
    _T _t3 = _t2 + (bl);
    add12(zh, zl,_t1,_t3);
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_common<_T>::
add212(_T& zh, _T& zl,
       const _T& ah, const _T& al, const _T& b)
{
    _T _t1, _t2;
    add12(_t1, _t2, ah, b);
    _T _t3 = _t2 + al;
    add12(zh, zl, _t1, _t3);
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_common<_T>::
add212cond(_T& zh, _T& zl,
           const _T& ah, const _T& al, const _T& b)
{
    _T _t1, _t2;
    add12cond(_t1, _t2, ah, b);
    _T _t3 = _t2 + al;
    add12(zh, zl, _t1, _t3);
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_fma<_T, true>::
sqr12(_T& rh, _T& rl, const _T& u)
{
    _T h = u * u;
    _T l = fms(u, u, h);
    rh = h;
    rl = l;
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_fma<_T, true>::
mul12(_T& rh, _T& rl, const _T& u, const _T& v)
{
    _T h = u * v;
    _T l = fms(u, v, h);
    rh = h;
    rl = l;
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_fma<_T, true>::
muladd12(_T& rh, _T& rl, const _T& c, const _T& a, const _T& b)
{
    _T h= fma(a, b, c);
    _T t= h - c;
    _T l= fms(a, b, t);
    rh = h;
    rl = l;
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_fma<_T, true>::
rcp21(_T& rh, const _T& ah, const _T& al)
{
    _T q0 = _T(1.0)/ah;
    // rh = q0 + q0 * ((_T(1.0) - q0*ah) - q0*al);
    _T t = nfma(q0, ah, _T(1.0));
    t = nfma(q0, al, t);
    rh = fma(q0, t, q0);
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_fma<_T, true>::
unorm_mul122(_T& rh, _T& rl,
             const _T& a,
             const _T& bh, const _T& bl)
{
    _T tl;
    mul12(rh, tl, a, bh);
    rl = fma(a, bl, tl);
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_fma<_T, true>::
mul122(_T& rh, _T& rl,
       const _T& a,
       const _T& bh, const _T& bl)
{
    _T t1, t2;
    unorm_mul122(t1, t2, a, bh, bl);
    add12(rh, rl, t1, t2);
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_fma<_T, true>::
unorm_sqr22(_T& pzh, _T& pzl,
            const _T& xh, const _T& xl)
{
    _T ph = xh * xh;
    _T pl = fms(xh, xh, ph);
    // _T xl2= _T(2.0)*xl;
    _T xl2 = xl+xl;
    pl = fma(xh, xl2, pl);
    pzh = ph;
    pzl = pl;
    // pzh = ph + pl;
    // pzl = ph - pzh;
    // pzl+= pl;
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_fma<_T, true>::
sqr22(_T& pzh, _T& pzl,
      const _T& xh, const _T& xl)
{
#if 1
    _T ph, pl;
    unorm_sqr22(ph, pl, xh, xl);
    add12(pzh, pzl, ph, pl);
#else
    _T ph = xh * xh;
    _T pl = fms(xh, xh, ph);
    _T xl2= _T(2.0)*xl;
    pl = fma(xh, xl2, pl);
    pzh = ph + pl;
    pzl = ph - pzh;
    pzl+= pl;
#endif
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_fma<_T, true>::
unorm_mul22(_T& pzh, _T& pzl,
            const _T& xh, const _T& xl,
            const _T& yh, const _T& yl)
{
    _T ph = xh * yh;
    _T pl = fms(xh, yh, ph);
    pl = fma(xh, yl, pl);
    pl = fma(xl, yh, pl);
    pzh = ph;
    pzl = pl;
    // pzh = ph + pl;
    // pzl = ph - pzh;
    // pzl+= pl;
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_fma<_T, true>::
mul22(_T& pzh, _T& pzl,
      const _T& xh, const _T& xl,
      const _T& yh, const _T& yl)
{
#if 1
    _T ph, pl;
    unorm_mul22(ph, pl, xh, xl, yh, yl);
    add12(pzh, pzl, ph, pl);
#else
    _T ph = xh * yh;
    _T pl = fms(xh, yh, ph);
    pl = fma(xh, yl, pl);
    pl = fma(xl, yh, pl);
    pzh = ph + pl;
    pzl = ph - pzh;
    pzl+= pl;
#endif
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_fma<_T, true>::
sqr21(_T& pzh,
      const _T& xh, const _T& xl)
{
#if 1
    _T ph, pl;
    unorm_sqr22(ph, pl, xh, xl);
    pzh = ph + pl;
#else
    _T ph = xh * xh;
    _T pl = fms(xh, xh, ph);
    _T xl2= _T(2.0)*xl;
    pl = fma(xh, xl2, pl);
    pzh = ph + pl;
#endif
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_fma<_T, false>::
sqr12(_T& rh, _T& rl, const _T& a)
{
    _T a_h, a_l;
    using traits=d_real_traits<_T>;
    traits::split(a, a_h, a_l);
    rh=a*a;
    _T t= a_h * a_l;
    rl=((a_h*a_h-rh)+t+t)+a_l*a_l;
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_fma<_T, false>::
mul12(_T& rh, _T& rl, const _T& a, const _T& b)
{
    _T a_h, a_l, b_h, b_l;
    using traits=d_real_traits<_T>;
    traits::split(a, a_h, a_l);
    traits::split(b, b_h, b_l);
#if 1
    rh = a*b;
    auto ahbh = a_h * b_h;
    auto ahbl = a_h * b_l;
    auto albh = a_l * b_h;
    auto albl = a_l * b_l;
    rl = (((ahbh - rh) + ahbl) + albh) + albl;
#else
    rh=a*b;
    rl=(((a_h*b_h-rh)+a_h*b_l)+a_l*b_h)+a_l*b_l;
#endif
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_fma<_T, false>::
muladd12(_T& rh, _T& rl, const _T& c, const _T& a, const _T& b)
{
#if 1
    // look into horner_comp_quick_s0
    _T ph, pl;
    mul12(ph, pl, a, b);
    _T tl;
    add12(rh, tl, c, ph);
    rl = pl + tl;
#else
    _T ph, pl;
    mul12(ph, pl, a, b);
    add122(rh, rl, c, ph, pl);
#endif
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_fma<_T, false>::
rcp21(_T& rh, const _T& ah, const _T& al)
{
    using traits=d_real_traits<_T>;
    _T ahh, ahl;
    traits::split(ah, ahh, ahl);
    ahl += al;
    _T q0 = _T(1.0)/ah;
    _T qh, ql;
    traits::split(q0, qh, ql);
    rh = qh + q0 * ((_T(1.0) - qh * ahh) - qh * ahl);
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_fma<_T, false>::
unorm_sqr22(_T& pzh, _T& pzl,
            const _T& xh, const _T& xl)
{
    _T p1, p2;
    sqr12(p1, p2, xh);
    _T xhl= xh*xl;
    p2+= (xhl + xhl);
    pzh = p1;
    pzl = p2;
    // add12(pzh, pzl, p1, p2);
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_fma<_T, false>::
sqr22(_T& pzh, _T& pzl,
      const _T& xh, const _T& xl)
{
#if 1
    _T ph, pl;
    unorm_sqr22(ph, pl, xh, xl);
    add12(pzh, pzl, ph, pl);
#else
    _T p1, p2;
    sqr12(p1, p2, xh);
    _T xhl= xh*xl;
    p2+= (xhl + xhl);
    add12(pzh, pzl, p1, p2);
#endif
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_fma<_T, false>::
unorm_mul122(_T& rh, _T& rl,
             const _T& a,
             const _T& bh, const _T& bl)
{
    _T tl;
    mul12(rh, tl, a, bh);
    _T pl = a*bl;
    rl = pl + tl;
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_fma<_T, false>::
mul122(_T& rh, _T& rl,
       const _T& a,
       const _T& bh, const _T& bl)
{
    _T t1, t2;
    unorm_mul122(t1, t2, a, bh, bl);
    add12(rh, rl, t1, t2);
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_fma<_T, false>::
sqr21(_T& pzh,
      const _T& xh, const _T& xl)
{
#if 1
    _T ph, pl;
    unorm_sqr22(ph, pl, xh, xl);
    pzh = ph + pl;
#else
    _T p1, p2;
    sqr12(p1, p2, xh);
    _T xhl= xh*xl;
    p2+= (xhl + xhl);
    pzh= p1+p2;
#endif
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_fma<_T, false>::
unorm_mul22(_T& pzh, _T& pzl,
            const _T& xh, const _T& xl,
            const _T& yh, const _T& yl)
{
    _T p1, p2;
    mul12(p1, p2, xh, yh);
    p2+= (xh*yl + xl * yh);
    pzh = p1;
    pzl = p2;
    // add12(pzh, pzl, p1, p2);
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops_fma<_T, false>::
mul22(_T& pzh, _T& pzl,
      const _T& xh, const _T& xl,
      const _T& yh, const _T& yl)
{
#if 1
    _T ph, pl;
    unorm_mul22(ph, pl, xh, xl, yh, yl);
    add12(pzh, pzl, ph, pl);
#else
    _T p1, p2;
    mul12(p1, p2, xh, yh);
    p2+= (xh*yl + xl * yh);
    add12(pzh, pzl, p1, p2);
#endif
}

template <typename _T>
_T
cftal::d_real_ops_fma<_T, true>::
xfma(const _T& a, const _T& b, const _T& c)
{
    return fma(a, b, c);
}

template <typename _T>
_T
cftal::d_real_ops_fma<_T, false>::
xfma(const _T& a, const _T& b, const _T& c)
{
    _T pl, ph;
    mul12(ph, pl, a, b);
    _T rh, rl;
    base_type::add122cond(rh, rl, c, ph, pl);
    return rh;
}

template <typename _T, bool _FMA>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops<_T, _FMA>::
muladd212(_T& rh, _T& rl,
          const _T& ch, const _T& cl,
          const _T& a,
          const _T& bh, const _T& bl)
{
    _T _t1, _t2;
    mul12(_t1, _t2, a, bh);
    _T _t3, _t4;
    add12(_t3,_t4,ch,_t1);
    auto _t5 = bl * a;
    auto _t6 = cl + _t2;
    auto _t7 = _t5 + _t6;
    _T _t8 = _t7 + _t4;
    add12(rh, rl, _t3, _t8);
}

template <typename _T, bool _FMA>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops<_T, _FMA>::
muladd22(_T& rh, _T& rl,
         const _T& ch, const _T& cl,
         const _T& ah, const _T& al,
         const _T& bh, const _T& bl)
{
    _T _t1, _t2;
    mul12(_t1, _t2, ah, bh);
    _T _t3, _t4;
    add12(_t3, _t4, ch, _t1);
    auto _t5 = ah * bl;
    auto _t6 = al * bh;
    auto _t7 = _t2 + cl;
    auto _t8 = _t4 + _t7;
    auto _t9 = _t5 + _t6;
    _T _t10 = _t8 + _t9;
    add12(rh, rl, _t3, _t10);
}

template <typename _T, bool _FMA>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops<_T, _FMA>::
div12(_T& rh, _T& rl,
      const _T& xh,
      const _T& yh)
{
    _T _ch = xh / yh;
    _T _uh, _ul;
    mul12(_uh, _ul, _ch, yh);
    auto _cl = ((xh - _uh) - _ul)/yh;
    rh = _ch + _cl;
    rl = (_ch - rh) + _cl;
}

template <typename _T, bool _FMA>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops<_T, _FMA>::
div212(_T& rh, _T& rl,
       const _T& xh, const _T& xl,
       const _T& yh)
{
    // DWDivFP2
    _T _t= xh / yh;
    _T _rh, _rl;
    mul12(_rh, _rl, _t,  yh);
    auto _u = xl - _rl;
    _T _v = ((xh - _rh) + _u) /yh;
    add12(rh, rl, _t, _v);
}

template <typename _T, bool _FMA>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops<_T, _FMA>::
div122(_T& rh, _T& rl,
       const _T& xh,
       const _T& yh, const _T& yl)
{
    // DWDivDW2
    _T _t= xh / yh;
    _T _rh, _rl;
    mul122(_rh, _rl, _t, yh, yl);
    _T _v = ((xh - _rh) - _rl)/yh;
    add12(rh, rl, _t, _v);
}

/*
  @unpublished{joldes:hal-01351529,
  TITLE = {{Tight and rigourous error bounds for basic building blocks of double-word arithmetic}},
  AUTHOR = {Joldes, Mioara and Muller, Jean-Michel and Popescu, Valentina},
  URL = {https://hal.archives-ouvertes.fr/hal-01351529},
  NOTE = {working paper or preprint},
  HAL_LOCAL_REFERENCE = {Rapport LAAS n{\textdegree} 16225},
  YEAR = {2016},
  MONTH = Jul,
  KEYWORDS = {Floating-point arithmetic ; double-word arithmetic ; double-double arithmetic ; error-free transforms},
  PDF = {https://hal.archives-ouvertes.fr/hal-01351529/file/Bailey2add2mult-revision-sent.pdf},
  HAL_ID = {hal-01351529},
  HAL_VERSION = {v2},
*/
template <typename _T, bool _FMA>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops<_T, _FMA>::
div22(_T& rh, _T& rl,
      const _T& xh, const _T& xl,
      const _T& yh, const _T& yl)
{
    // DWDivDW2
    _T _t= xh / yh;
    _T _rh, _rl;
    mul122(_rh, _rl, _t, yh, yl);
    auto _u = xl - _rl;
    _T _v = ((xh - _rh) + _u)/ yh;
    add12(rh, rl, _t, _v);
}

template <typename _T, bool _FMA>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops<_T, _FMA>::
div21(_T& r,
      const _T& xh, const _T& xl,
      const _T& yh, const _T& yl)
{
    // DWDivDW2
    _T _t= xh / yh;
    _T _rh, _rl;
    mul122(_rh, _rl, _t, yh, yl);
    auto _u = xl - _rl;
    _T _v = ((xh - _rh) + _u)/ yh;
    r = _t + _v;
}

template <typename _T, bool _FMA>
inline
void
cftal::d_real_ops<_T, _FMA>::
__scaled_div22(_T& rh, _T& rl,
               const _T& ah, const _T& al,
               const _T& bh, const _T& bl)
{
    using traits_t=d_real_traits<_T>;
    using std::frexp;
    using std::ldexp;
    using int_type = typename traits_t::int_type;
    int_type ea, eb;
    _T sah=frexp(ah, &ea);
    _T sbh=frexp(bh, &eb);
    int_type nea=-ea;
    _T sal=ldexp(al, nea);
    int_type neb=-eb;
    _T sbl=ldexp(bl, neb);
    _T th, tl;
    div22(th, tl, sah, sal, sbh, sbl);
    int_type eq= ea - eb;
    rh = ldexp(th, eq);
    rl = ldexp(tl, eq);
}

template <typename _T, bool _FMA>
inline
void
cftal::d_real_ops<_T, _FMA>::
scaled_div22(_T& rh, _T& rl,
             const _T& ah, const _T& al,
             const _T& bh, const _T& bl)
{
    using std::abs;
    using traits_t=d_real_traits<_T>;
    auto a_small = abs(ah) < traits_t::scale_div_threshold();
    auto b_small = abs(bh) < traits_t::scale_div_threshold();
    auto one_small = a_small | b_small;
    if (traits_t::any_of_v(one_small)) {
        __scaled_div22(rh, rl, ah, al, bh, bl);
    } else {
        div22(rh, rl, ah, al, bh, bl);
    }
}

template <typename _T, bool _FMA>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops<_T, _FMA>::
rcp12(_T& rh, _T& rl, const _T& a)
{
    // v4f32 rcp=_mm_rcp_ps(a());
    // rcp = rcp + rcp*(1-rcp*a);
    // return rcp;
    // rcp = rcp * (2-rcp*a)
    _T r0h= _T(1.0)/a;
    if (_FMA == true) {
        _T nr0h=-r0h;
        _T z= fma(nr0h, a, _T(1.0));
        _T d= r0h * z;
        add12(rh, rl, r0h, d);
    } else {
        // -rcp * a
        _T th, tl;
        mul12(th, tl, -r0h, a);
        // 2 - rcp * a
        add122(th, tl, _T(2.0), th, tl);
        // rcp ( 2 - rcp*a)
        mul122(rh, rl, r0h, th, tl);
    }
}

template <typename _T, bool _FMA>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops<_T, _FMA>::
rcp2(_T& rh, _T& rl, const _T& ah, const _T& al)
{
    // v4f32 rcp=_mm_rcp_ps(a());
    // rcp = rcp + rcp*(1-rcp*a);
    // return rcp;
    // rcp = rcp * (2-rcp*a)
    _T r0h= _T(1.0)/ah;
    // -rcp * a
    _T th, tl;
    mul122(th, tl, -r0h, ah, al);
    // 2 - rcp * a
    add122(th, tl, _T(2.0), th, tl);
    // rcp ( 2 - rcp*a)
    mul122(rh, rl, r0h, th, tl);
}

template <typename _T, bool _FMA>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops<_T, _FMA>::
sqrt12(_T& rh, _T& rl, const _T& ah)
{
    using std::sqrt;
    _T root=sqrt(ah);
    _T  inv_root= _T(1.0)/root;
    _T  ax= ah * inv_root;
    _T  max2h, max2l;
    if (_FMA==true) {
        mul12(max2h, max2l, ax, -ax);
    } else {
        sqr12(max2h, max2l, ax);
        max2h = -max2h;
        max2l = -max2l;
    }
    _T a0h, a0l;
    add122(a0h, a0l, ah, max2h, max2l);
    _T a1=a0h* (inv_root*_T(0.5));
    add12(rh, rl, ax, a1);
    auto is_zero= ah == _T(0);
    rh = select(is_zero, _T(0), rh);
    rl = select(is_zero, _T(0), rl);
}

template <typename _T, bool _FMA>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops<_T, _FMA>::
sqrt2(_T& rh, _T& rl, const _T& ah, const _T& al)
{
    using std::sqrt;
    _T root=sqrt(ah);
    _T  inv_root= _T(1.0)/root;
    _T  ax= ah * inv_root;
    _T  max2h, max2l;
    if (_FMA==true) {
        mul12(max2h, max2l, ax, -ax);
    } else {
        sqr12(max2h, max2l, ax);
        max2h = -max2h;
        max2l = -max2l;
    }
    _T a0h, a0l;
    add22(a0h, a0l, ah, al, max2h, max2l);
    _T a1=a0h* (inv_root*_T(0.5));
    add12(rh, rl, ax, a1);
    auto is_zero= ah == _T(0);
    rh = select(is_zero, _T(0), rh);
    rl = select(is_zero, _T(0), rl);
}

template <typename _T, bool _FMA>
inline
__attribute__((__always_inline__))
void
cftal::d_real_ops<_T, _FMA>::
sqrt21(_T& rh, const _T& ah, const _T& al)
{
    using std::sqrt;
    _T root=sqrt(ah);
    _T inv_root= _T(1.0)/root;
    _T ax= ah * inv_root;
    _T max2h, max2l;
    if (_FMA==true) {
        mul12(max2h, max2l, ax, -ax);
    } else {
        sqr12(max2h, max2l, ax);
        max2h = -max2h;
        max2l = -max2l;
    }
    _T a0h, a0l;
    add22(a0h, a0l, ah, al, max2h, max2l);
    _T a1=a0h* (inv_root*_T(0.5));
    rh=ax+a1;
    auto is_zero= ah == _T(0);
    rh = select(is_zero, _T(0), rh);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator-(const d_real<_T>& a)
{
    return d_real<_T>(-a[0], -a[1]);
}

template <typename _T>
inline
const cftal::d_real<_T>&
cftal::operator+(const d_real<_T>& a)
{
    return a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator+(const d_real<_T>& a, const _T& b)
{
    using impl_t=d_real_ops<_T, d_real_traits<_T>::fma>;
    _T h, l;
    impl_t::add122cond(h, l, b, a[0], a[1]);
    return d_real<_T>(h, l);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator+(const _T& a, const d_real<_T>& b)
{
    return b + a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator+(const d_real<_T>& a, const d_real<_T>& b)
{
    using impl_t=d_real_ops<_T, d_real_traits<_T>::fma>;
    _T h, l;
    impl_t::add22condhp(h, l, a[0], a[1], b[0], b[1]);
    return d_real<_T>(h, l);
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator+=(d_real<_T>& a, const _T& b)
{
    a= a + b;
    return a;
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator+=(d_real<_T>& a, const d_real<_T>& b)
{
    a= a + b;
    return a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator-(const d_real<_T>& a, const _T& b)
{
    using impl_t=d_real_ops<_T, d_real_traits<_T>::fma>;
    _T h, l;
    impl_t::add122cond(h, l, -b, a[0], a[1]);
    return d_real<_T>(h, l);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator-(const _T& a, const d_real<_T>& b)
{
    using impl_t=d_real_ops<_T, d_real_traits<_T>::fma>;
    _T h, l;
    impl_t::add122cond(h, l, -a[0], -a[1], b);
    return d_real<_T>(h, l);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator-(const d_real<_T>& a, const d_real<_T>& b)
{
    using impl_t=d_real_ops<_T, d_real_traits<_T>::fma>;
    _T h, l;
    impl_t::add22condhp(h, l, a[0], a[1], -b[0], -b[1]);
    return d_real<_T>(h, l);
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator-=(d_real<_T>& a, const _T& b)
{
    a= a - b;
    return a;
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator-=(d_real<_T>& a, const d_real<_T>& b)
{
    a= a - b;
    return a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator*(const d_real<_T>& a, const _T& b)
{
    using impl_t=d_real_ops<_T, d_real_traits<_T>::fma>;
    _T h, l;
    impl_t::mul122(h, l, b, a[0], a[1]);
    return d_real<_T>(h, l);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator*(const _T& a, const d_real<_T>& b)
{
    return b*a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator*(const d_real<_T>& a, const d_real<_T>& b)
{
    using impl_t=d_real_ops<_T, d_real_traits<_T>::fma>;
    _T h, l;
    impl_t::mul22(h, l, a[0], a[1], b[0], b[1]);
    return d_real<_T>(h, l);
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator*=(d_real<_T>& a, const _T& b)
{
    a= a * b;
    return a;
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator*=(d_real<_T>& a, const d_real<_T>& b)
{
    a= a * b;
    return a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator/(const d_real<_T>& a, const _T& b)
{
    using impl_t=d_real_ops<_T, d_real_traits<_T>::fma>;
    _T h, l;
    // impl_t::div212(h, l, a[0], a[1], b);
    impl_t::scaled_div22(h, l, a[0], a[1], b, _T(0));
    return d_real<_T>(h, l);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator/(const _T& a, const d_real<_T>& b)
{
    using impl_t=d_real_ops<_T, d_real_traits<_T>::fma>;
    _T h, l;
    impl_t::scaled_div22(h, l, a, _T(0), b[0], b[1]);
    return d_real<_T>(h, l);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator/(const d_real<_T>& a, const d_real<_T>& b)
{
    using impl_t=d_real_ops<_T, d_real_traits<_T>::fma>;
    _T h, l;
    impl_t::scaled_div22(h, l, a[0], a[1], b[0], b[1]);
    return d_real<_T>(h, l);
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator/=(d_real<_T>& a, const _T& b)
{
    a= a / b;
    return a;
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator/=(d_real<_T>& a, const d_real<_T>& b)
{
    a= a / b;
    return a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::rcp(const d_real<_T>& a)
{
    return _T(1)/a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::abs(const d_real<_T>& a)
{
    typename d_real_traits<_T>::cmp_result_type a_lt_z=
        a < d_real<_T>(0);
    d_real<_T> an(-a);
    _T hi_res = d_real_traits<_T>::sel(
        a_lt_z, an[0], a[0]);
    _T lo_res = d_real_traits<_T>::sel(
        a_lt_z, an[1], a[1]);
    return d_real<_T>(hi_res, lo_res);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::rint(const d_real<_T>& a)
{
    _T hi= rint(a[0]);

    // if rint(hi)==hi
    //      return (hi, rint(lo))
    // else
    //      if (abs(hi - rint(hi)) == 0.5 && lo < 0)
    //          return (hi-1, 0)
    //      else
    //          return (hi, 0)
    // _T lo;

    using impl_t=d_real_ops<_T, d_real_traits<_T>::fma>;

    // if hi == a[0]
    _T lo_hi_int = rint(a[1]);
    _T hi_hi_int;
    impl_t::add12(hi_hi_int, lo_hi_int, hi, lo_hi_int);

    // hi != a[0]
    _T lo_hi_no_int(0);
    _T hi_m1 = hi - 1.0;
    _T hi_hi_no_int = d_real_traits<_T>::sel(
        (abs(_T(hi - a[0]))==_T(0.5)) & (a[1] < _T(0.0)),
        hi_m1, hi);

    typename d_real_traits<_T>::cmp_result_type hi_eq_ah=
        hi == a[0];

    _T hi_res = d_real_traits<_T>::sel(
        hi_eq_ah, hi_hi_int, hi_hi_no_int);
    _T lo_res = d_real_traits<_T>::sel(
        hi_eq_ah, lo_hi_int, lo_hi_int);

    return d_real<_T>(hi_res, lo_res);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::floor(const d_real<_T>& a)
{
    // if ah == floor(ah), return ah, floor(al)
    // else return floor(ah), 0
    _T hi = floor(a[0]);
    _T lo(0);
    using impl_t=d_real_ops<_T, d_real_traits<_T>::fma>;
    typename d_real_traits<_T>::cmp_result_type r=
        hi == a[0];
    _T lo_hi_int = floor(a[1]);
    _T hi_hi_int;
    impl_t::add12(hi_hi_int, lo_hi_int, hi, lo_hi_int);

    _T hi_res = d_real_traits<_T>::sel(
        r, hi_hi_int, hi);
    _T lo_res = d_real_traits<_T>::sel(
        r, lo_hi_int, lo);
    return d_real<_T>(hi_res, lo_res);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::ceil(const d_real<_T>& a)
{
    // if ah == ceil(ah), return ah, ceil(al)
    // else return ceil(ah), 0
    _T hi = ceil(a[0]);
    _T lo(0);
    typename d_real_traits<_T>::cmp_result_type r=
        hi == a[0];
    using impl_t=d_real_ops<_T, d_real_traits<_T>::fma>;
    _T lo_hi_int = ceil(a[1]);
    _T hi_hi_int;
    impl_t::add12(hi_hi_int, lo_hi_int, hi, lo_hi_int);

    _T hi_res = d_real_traits<_T>::sel(
        r, hi_hi_int, hi);
    _T lo_res = d_real_traits<_T>::sel(
        r, lo_hi_int, lo);
    return d_real<_T>(hi_res, lo_res);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::trunc(const d_real<_T>& a)
{
    typename d_real_traits<_T>::cmp_result_type a_lt_z=
        a[0] < _T(0);
    d_real<_T> a_floor(floor(a));
    d_real<_T> a_ceil(ceil(a));
    _T hi_res= d_real_traits<_T>::sel(
        a_lt_z, a_ceil[0], a_floor[0]);
    _T lo_res= d_real_traits<_T>::sel(
        a_lt_z, a_ceil[1], a_floor[1]);
    return d_real<_T>(hi_res, lo_res);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::powi(const d_real<_T>& a, int e)
{
    d_real<_T> r = a;
    d_real<_T> s = 1.0;
    int np = std::abs(e);
    if (np > 1) {
        /* Use binary exponentiation */
        while (np > 0) {
            if ((np & 1) == 1) {
                s *= r;
            }
            np >>= 1;
            if (np > 0)
                r = r * r;
        }
    } else {
        s = r;
    }
    /* Compute the reciprocal if n is negative. */
    if (e < 0)
        s= (_T(1.0) / s);
    return s;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::sqr(const d_real<_T>& a)
{
    using impl_t=d_real_ops<_T, d_real_traits<_T>::fma>;
    _T h, l;
    impl_t::sqr2(h, l, a[0], a[1]);
    return d_real<_T>(h, l);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::mul_pwr2(const d_real<_T> &a, const _T& b)
{
    return d_real<_T>(a[0] * b, a[1] * b);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::sqrt(const d_real<_T>& a)
{
    using impl_t=d_real_ops<_T, d_real_traits<_T>::fma>;
    _T h, l;
    impl_t::sqrt2(h, l, a[0], a[1]);
    return d_real<_T>(h, l);
}

template <typename _T>
inline
std::enable_if_t<
    !std::is_same_v<typename cftal::d_real_traits<_T>::cmp_result_type,
                    bool>,
    cftal::d_real<_T> >
cftal::select(const typename d_real_traits<_T>::cmp_result_type& m,
              const d_real<_T>& a, const d_real<_T>& b)
{
    _T h= select(m, a[0], b[0]);
    _T l= select(m, a[1], b[1]);
    return d_real<_T>(h, l);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::select(const typename d_real_traits<_T>::cmp_result_type& m,
              const _T& a, const d_real<_T>& b)
{
    _T h= select(m, a, b[0]);
    _T l= select_zero_or_val(m, b[1]);
    return d_real<_T>(h, l);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::select(const typename d_real_traits<_T>::cmp_result_type& m,
              const d_real<_T>& a, const _T& b)
{
    _T h= select(m, a[0], b);
    _T l= select_val_or_zero(m, a[1]);
    return d_real<_T>(h, l);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::max(const d_real<_T>& a, const d_real<_T>& b)
{
    typename d_real_traits<_T>::cmp_result_type m= a > b;
    return select(m, a, b);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::min(const d_real<_T>& a, const d_real<_T>& b)
{
    typename d_real_traits<_T>::cmp_result_type m= a < b;
    return select(m, a, b);
}

// Local variables:
// mode: c++
// end:
#endif
