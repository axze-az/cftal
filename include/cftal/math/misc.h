//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_MATH_MISC_H__)
#define __CFTAL_MATH_MISC_H__ 1

#include <cftal/config.h>
#include <cftal/arg.h>
#include <cftal/d_real.h>
#include <cftal/t_real.h>
#include <cftal/std_types.h>
#include <cftal/divisor.h>
#include <cftal/constants.h>
#include <cftal/mem.h>
#include <cftal/math/func_constants.h>
#include <cftal/math/horner.h>
#include <cftal/type_traits.h>
#include <limits>
#include <utility>
#include <stdexcept>

namespace cftal {

    namespace math {

        namespace impl {

            // xn contains the power of x required
            template <typename _C, typename _T, size_t _N>
            _T
            householder_step(_T xn, _T x, _T y,
                             const _C(&p)[_N],
                             const _C(&q)[_N]);

            // helper functions for different reciprocal root  2 iterations
            struct root_r2 {
                // calculate x^2*y - 1.0
                template <typename _C, bool _HIGH_PREC, typename _T>
                static
                _T
                calc_z(_T y, _T x);

                // x^-2 = y
                template <typename _C, bool _HIGH_PREC, typename _T>
                static
                _T
                order2(_T x, _T y);

                // x^-2 = y
                template <typename _C, bool _HIGH_PREC, typename _T>
                static
                _T
                order3(_T x, _T y);

                // x^-2 = y
                template <typename _C, bool _HIGH_PREC, typename _T>
                static
                _T
                order4(_T x, _T y);

                // x^-2 = y
                template <typename _C, bool _HIGH_PREC, typename _T>
                static
                _T
                order5(_T x, _T y);

                // x^-2 = y
                template <typename _C, bool _HIGH_PREC, typename _T>
                static
                _T
                order6(_T x, _T y);
            };

            // helper functions for different root 3 iteration steps
            struct root_3 {
                // x^3 = y
                template <typename _C, typename _T>
                static
                _T
                nr(_T y, _T x);

                // x^3 = y
                template <typename _C, typename _T>
                static
                _T
                halley(_T y, _T x);

                // calculate z = (y -x^3)/x^3;
                template <typename _T>
                static
                _T
                calc_z(_T x, _T y);

                // x^3 = y
                template <typename _C, typename _T>
                static
                _T
                order3(_T x, _T y);

                // x^3 = y
                template <typename _C, typename _T>
                static
                _T
                order4(_T x, _T y);

                // x^3 = y
                template <typename _C, typename _T>
                static
                _T
                order5(_T x, _T y);

                // x^3 = y
                template <typename _C, typename _T>
                static
                _T
                order6(_T y, _T x);
            };

            // helper functions for different reciprocal root3 iteration
            // steps
            struct root_r3 {
                template <typename _T>
                // calculate x^3*y - 1.0
                static
                _T
                calc_z(_T y, _T x);

                // x^-3 = y
                template <typename _C, typename _T>
                static
                _T
                order3(_T y, _T x);

                // x^-3 = y
                template <typename _C, typename _T>
                static
                _T
                order4(_T y, _T x);

                // x^-3 = y
                template <typename _C, typename _T>
                static
                _T
                order5(_T y, _T x);
                // x^-3 = y
                template <typename _C, typename _T>
                static
                _T
                order6(_T y, _T x);
            };

            // helper functions for different root12 iteration steps
            struct root_12 {
                // calculate x^12
                template <typename _T>
                static
                _T
                pow12(_T x);

                // x^12 = y
                template <typename _C, typename _T>
                static
                _T
                nr(_T y, _T x);

                template <typename _C, typename _T>
                static
                _T
                halley(_T y, _T x);

                template <typename _C, typename _T>
                static
                _T
                order3(_T y, _T x);

                template <typename _C, typename _T>
                static
                _T
                order4(_T y, _T x);

                template <typename _C, typename _T>
                static
                _T
                order5(_T y, _T x);

                template <typename _C, typename _T>
                static
                _T
                order6(_T y, _T x);

                template <typename _C, typename _T>
                static
                _T
                order8(_T y, _T x);

                template <typename _C, typename _T>
                static
                _T
                order9(_T y, _T x);

                template <typename _C, typename _T>
                static
                _T
                order10(_T y, _T x);

                template <typename _C, typename _T>
                static
                _T
                householder3(_T x, _T y);

                template <typename _C, typename _T>
                static
                _T
                householder4(_T x, _T y);

                template <typename _C, typename _T>
                static
                _T
                householder5(_T x, _T y);

                template <typename _C, typename _T>
                static
                _T
                householder6(_T x, _T y);

                template <typename _C, typename _T>
                static
                _T
                householder7(_T x, _T y);

                template <typename _C, typename _T>
                static
                _T
                householder8(_T x, _T y);

                template <typename _C, typename _T>
                static
                _T
                householder9(_T x, _T y);

                template <typename _C, typename _T>
                static
                _T
                householder10(_T x, _T y);

                template <typename _C, typename _T>
                static
                _T
                householder16(_T x, _T y);
            };
        }
    }
}

template <typename _C, typename _T, cftal::size_t _N>
_T
cftal::math::impl::
householder_step(_T xn, _T x, _T y, const _C(&pa)[_N], const _C(&qa)[_N])
{
    static_assert(_N>1, "_N must be greater than one");
    const _C* pp=pa;
    const _C* pq=qa;
    _T yi=y;
    _T p=horner(xn, pp[0], pp[1]*yi);
    _T q=horner(xn, pq[0], pq[1]*yi);
#pragma clang loop unroll(disable)
#pragma GCC unroll 0
    for (size_t i=2; i<_N; ++i) {
        yi *= y;
        _T pi=pp[i] * yi;
        _T qi=pq[i] * yi;
        p=horner(xn, p, pi);
        q=horner(xn, q, qi);
    }
    return x + x * p/q;
}

template <typename _C, bool _HIGH_PREC, typename _T>
_T
cftal::math::impl::root_r2::calc_z(_T x, _T y)
{
    // z = x*x*y - 1.0
    // _HIGH_PREC == true:
    // calculated as z = x * (x * y) - 1.0 with error compensation
    // to avoid overflows
    // _HIGH_PREC == false:
    // calculated as z = (x * x) * y - 1.0 without error compensation
    constexpr const _C minus_one(-1.0);
    _T z;
    if constexpr (_HIGH_PREC) {
        using traits_t= d_real_traits<_T>;
        using d_ops = d_real_ops<_T, traits_t::fma>;
        _T xyh, xyl;
        d_ops::mul12(xyh, xyl, x, y);
        if constexpr (d_real_traits<_T>::fma == true) {
            z = xyh * x + minus_one;
            z = xyl * x + z;
        } else {
            _T xyxh, xyxl;
            d_ops::mul12(xyxh, xyxl, xyh, x);
            z = xyxh + minus_one;
            _T zl = xyxl + xyl * x;
            z += zl;
        }
    } else {
        _T x2 = x * x;
        z = y * x2 + minus_one;
    }
    return z;
}

template <typename _C, bool _HIGH_PREC, typename _T>
_T
cftal::math::impl::root_r2::order2(_T x, _T y)
{
    _T z= calc_z<_C, _HIGH_PREC>(x, y);
    _T d= z*_C(-0.5);
    _T xn= x+ x*d;
    return xn;
}

template <typename _C, bool _HIGH_PREC, typename _T>
_T
cftal::math::impl::root_r2::order3(_T x, _T y)
{
    _T z= calc_z<_C, _HIGH_PREC>(x, y);
    _T d= z*horner(z,
                   // _C(-63/256.0),
                   // _C(35.0/128.0),
                   // _C(-5.0/16.0),
                   _C(3.0/8.0),
                   _C(-0.5));
    _T xn= x+ x*d;
    return xn;
}

template <typename _C, bool _HIGH_PREC, typename _T>
_T
cftal::math::impl::root_r2::order4(_T x, _T y)
{
    _T z= calc_z<_C, _HIGH_PREC>(x, y);
    _T d= z*horner(z,
                   // _C(-63/256.0),
                   // _C(35.0/128.0),
                   _C(-5.0/16.0),
                   _C(3.0/8.0),
                   _C(-0.5));
    _T xn= x + x*d;
    return xn;
}

template <typename _C, bool _HIGH_PREC, typename _T>
_T
cftal::math::impl::root_r2::order5(_T x, _T y)
{
    _T z= calc_z<_C, _HIGH_PREC>(x, y);
    _T d= z*horner(z,
                   // _C(-63/256.0),
                   _C(35.0/128.0),
                   _C(-5.0/16.0),
                   _C(3.0/8.0),
                   _C(-0.5));
    _T xn= x + x*d;
    return xn;
}

template <typename _C, bool _HIGH_PREC, typename _T>
_T
cftal::math::impl::root_r2::order6(_T x, _T y)
{
    _T z= calc_z<_C, _HIGH_PREC>(x, y);
    _T d= z*horner(z,
                   _C(-63/256.0),
                   _C(35.0/128.0),
                   _C(-5.0/16.0),
                   _C(3.0/8.0),
                   _C(-0.5));
    _T xn= x + x*d;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_3::nr(_T x, _T y)
{
    _T d= _C(1.0/3.0) * (y/(x*x) - x);
    _T xn= x + d;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_3::halley(_T x, _T y)
{
    _T s=x*x*x;
    _T xn = x -(s - y) * x/(_C(2.0)*s+y);
    return xn;
}

template <typename _T>
_T
cftal::math::impl::root_3::calc_z(_T x, _T y)
{
    _T x3= x*x*x;
    _T z= (y -x3)/x3;
    return z;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_3::order3(_T x, _T y)
{
#if 1
    _T z= calc_z(x, y);
    _T d= z*horner(z,
                   _C(-1.0/9.0),
                   _C(1.0/3.0));
    _T xn= x+ x*d;
    return xn;
#else
    _T x3= x*x*x;
    _T d = (x3 - y)*x/(_C(2.0)*x3+y);
    _T xn= x - d;
    return xn;
#endif
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_3::order4(_T x, _T y)
{
#if 1
    _T z= calc_z(x, y);
    _T d= z*horner(z,
                   _C(5.0/81.0),
                   _C(-1.0/9.0),
                   _C(1.0/3.0));
    _T xn= x + x*d;
    return xn;
#else
    _T s= (x*x*x-y)/y;
    _T xn= x - x * (((_C(14.0/81.0) * s -_C(2.0/9.0))*s)+_C(1.0/3.0))*s;
#endif
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_3::order5(_T x, _T y)
{
    _T z= calc_z(x, y);
    _T d= z*horner(z,
                   _C(-10.0/243.0),
                   _C(5.0/81.0),
                   _C(-1.0/9.0),
                   _C(1.0/3.0));
    _T xn= x + x*d;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_3::order6(_T x, _T y)
{
    _T z= calc_z(x, y);
    _T d= z*horner(z,
                   _C(22.0/729.0),
                   _C(-10.0/243.0),
                   _C(5.0/81.0),
                   _C(-1.0/9.0),
                   _C(1.0/3.0));
    _T xn= x + x*d;
    return xn;
}

template <typename _T>
_T
cftal::math::impl::root_r3::calc_z(_T x, _T y)
{
    _T x3= x*x*x;
    // _T z= y*x3 -_C(1.0);
    using traits_t= d_real_traits<_T>;
    using d_ops = d_real_ops<_T, traits_t::fma>;
    const _T minus_one(-1.0);
    _T z;
    if constexpr (traits_t::fma) {
        z = y * x3 + minus_one;
    } else {
#if 1
        _T yx3h, yx3l;
        d_ops::mul12(yx3h, yx3l, y, x3);
        z = yx3h + minus_one;
        z += yx3l;
#else
        z= d_ops::xfma(y, x3, minus_one);
#endif
    }
    return z;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_r3::order3(_T x, _T y)
{
    _T z= calc_z(x, y);
    _T d= z*horner(z,
                   _C(2.0/9.0),
                   _C(-1.0/3.0));
    _T xn= x+ x*d;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_r3::order4(_T x, _T y)
{
    _T z= calc_z(x, y);
    _T d= z*horner(z,
                   _C(-14.0/81.0),
                   _C(2.0/9.0),
                   _C(-1.0/3.0));
    _T xn= x + x*d;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_r3::order5(_T x, _T y)
{
    _T z= calc_z(x, y);
    _T d= z*horner(z,
                   _C(35.0/243.0),
                   _C(-14.0/81.0),
                   _C(2.0/9.0),
                   _C(-1.0/3.0));
    _T xn= x + x*d;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_r3::order6(_T x, _T y)
{
    _T z= calc_z(x, y);
    _T d= z*horner(z,
                   _C(-91.0/729.0),
                   _C(35.0/243.0),
                   _C(-14.0/81.0),
                   _C(2.0/9.0),
                   _C(-1.0/3.0));
    _T xn= x + x*d;
    return xn;
}


template <typename _T>
inline
__attribute__((__always_inline__))
_T
cftal::math::impl::root_12::pow12(_T x)
{
    // _T x12=powu<_T, 12>::v(x);
#if 0
    using d_ops=d_real_ops<_T, d_real_traits<_T>::fma>;
    _T x2h, x2l;
    d_ops::sqr12(x2h, x2l, x);
    _T x3h, x3l;
    d_ops::mul122(x3h, x3l, x, x2h, x2l);
    _T x6h, x6l;
    d_ops::sqr22(x6h, x6l, x3h, x3l);
    _T x12h, x12l;
    d_ops::sqr22(x12h, x12l, x6h, x6l);
    return x12h;
#else
    // same as above but without normalizations:
    using d_ops=d_real_ops<_T, d_real_traits<_T>::fma>;
    _T x2h, x2l;
    // x^2
    d_ops::sqr12(x2h, x2l, x);
    // x^3
    _T x3h, x3l;
    d_ops::mul12(x3h, x3l, x2h, x);
    x3l = x2l * x + x3l;
    // x^6
    _T x6h, x6l;
    d_ops::sqr12(x6h, x6l, x3h);
    _T t0=x3l*x3h;
    x6l = 2.0 * t0 + x6l;
    // x^12
    _T x12, x12l;
    d_ops::sqr12(x12, x12l, x6h);
    _T t1=x6l*x6h;
    x12l= 2.0 * t1 + x12l;
    x12 += x12l;
    return x12;
#endif
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_12::nr(_T x, _T y)
{
#if 1
    _T x12=pow12(x);
    _T z= (y-x12)/x12;
    _T d= (z * _C(1.0/12.0));
    _T xn= x + x*d;
#else
    // _T x11=powu<_T, 11>::v(x);
    _T x11=x;
    for (int i=0; i<10;++i)
        x11*=x;
    _T xn = x - _C(1.0/12.0) * (x - y/x11);
#endif
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_12::halley(_T x, _T y)
{
    // _T x12=powu<_T, 12>::v(x);
    _T x12=pow12(x);
    _T num= _C(2.0/11.0) * x * (y - x12);
    _T denom= y + _C(13.0/11.0) *x12;
    _T xn = x + num/denom;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_12::order3(_T x, _T y)
{
    // _T x12=powu<_T, 12>::v(x);
    _T x12=pow12(x);
    _T z= (y-x12)/x12;
    _T d= z* horner(z,
                    _C(-11.0/288.0),
                    _C(1.0/12.0));
    _T xn= x + x*d;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_12::order4(_T x, _T y)
{
    // _T x12=powu<_T, 12>::v(x);
    _T x12=pow12(x);
    _T z= (y-x12)/x12;
    _T d= z* horner(z,
                    _C(253.0/10368.0),
                    _C(-11.0/288.0),
                    _C(1.0/12.0));
    _T xn= x + x*d;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_12::order5(_T x, _T y)
{
    // _T x12=powu<_T, 12>::v(x);
    _T x12=pow12(x);
    _T z = (y-x12)/x12;
    static
    constexpr const _C ci[]= {
        _C(-8855.0/497664.0),
        _C(253.0/10368.0),
        _C(-11.0/288.0),
        _C(1.0/12.0)
    };
    _T d= z* horner(z, ci);
    _T xn= x + x*d;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_12::order6(_T x, _T y)
{
    // _T x12=powu<_T, 12>::v(x);
    _T x12=pow12(x);
    _T z = (y-x12)/x12;
    _T d= z* horner(z,
                    _C(83237.0/5971968.0),
                    _C(-8855.0/497664.0),
                    _C(253.0/10368.0),
                    _C(-11.0/288.0),
                    _C(1.0/12.0));
    _T xn= x + x*d;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_12::order8(_T x, _T y)
{
    // _T x12=powu<_T, 12>::v(x);
    _T x12=pow12(x);
    _T z = (y-x12)/x12;

    static
    constexpr const _C ci[]={
        _C(49811399.0/5159780352.0),
        _C(-4910983.0/429981696.0),
        _C(83237.0/5971968.0),
        _C(-8855.0/497664.0),
        _C(253.0/10368.0),
        _C(-11.0/288.0),
        _C(1.0/12.0)
    };
    _T d= z* horner2(z,_T(z*z), ci);
    _T xn= x + x*d;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_12::order9(_T x, _T y)
{
    // _T x12=powu<_T, 12>::v(x);
    _T x12=pow12(x);
    _T z = (y-x12)/x12;
    _T d= z* horner(z,
                    _C(-4134346117.0/495338913792.0),
                    _C(49811399.0/5159780352.0),
                    _C(-4910983.0/429981696.0),
                    _C(83237.0/5971968.0),
                    _C(-8855.0/497664.0),
                    _C(253.0/10368.0),
                    _C(-11.0/288.0),
                    _C(1.0/12.0));
    _T xn= x + x*d;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_12::order10(_T x, _T y)
{
    // _T x12=powu<_T, 12>::v(x);
    _T x12=pow12(x);
    _T z = (y-x12)/x12;
    _T d= z* horner(z,
                    _C(392762881115.0/53496602689536.0),
                    _C(-4134346117.0/495338913792.0),
                    _C(49811399.0/5159780352.0),
                    _C(-4910983.0/429981696.0),
                    _C(83237.0/5971968.0),
                    _C(-8855.0/497664.0),
                    _C(253.0/10368.0),
                    _C(-11.0/288.0),
                    _C(1.0/12.0));
    _T xn= x + x*d;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_12::householder3(_T x, _T y)
{
    static constexpr const _C p[]={
        _C(-3.9000000000000000000000e+01), // 24
        _C(+6.0000000000000000000000e+00), // 12
        _C(+3.3000000000000000000000e+01)  // 0
    };
    static constexpr
        const _C q[]={
        _C(+1.8200000000000000000000e+02), // 24
        _C(+5.7200000000000000000000e+02), // 12
        _C(+1.1000000000000000000000e+02)  // 0
    };
    _T x12=pow12(x);
    _T r=householder_step(x12, x, y, p, q);
    return r;
}

template <typename _C, typename _T>
inline
__attribute__((__always_inline__))
_T
cftal::math::impl::root_12::householder4(_T x, _T y)
{
    static constexpr const _C p[]={
        _C(-3.6400000000000000000000e+02), // 36
        _C(-7.8000000000000000000000e+02), // 24
        _C(+9.2400000000000000000000e+02), // 12
        _C(+2.2000000000000000000000e+02)  // 0
    };
    static constexpr const _C q[]={
        _C(+1.3650000000000000000000e+03), // 36
        _C(+1.0725000000000000000000e+04), // 24
        _C(+8.1510000000000000000000e+03), // 12
        _C(+4.9500000000000000000000e+02)  // 0
    };
    _T x12=pow12(x);
    _T r=householder_step(x12, x, y, p, q);
    return r;
}

template <typename _C, typename _T>
inline
__attribute__((__always_inline__))
_T
cftal::math::impl::root_12::householder5(_T x, _T y)
{
    static constexpr const _C p[]={
        _C(-4.5500000000000000000000e+02), // 48
        _C(-3.1200000000000000000000e+03), // 36
        _C(+8.5800000000000000000000e+02), // 24
        _C(+2.5520000000000000000000e+03), // 12
        _C(+1.6500000000000000000000e+02)  // 0
    };
    static constexpr const _C q[]={
        _C(+1.4560000000000000000000e+03), // 48
        _C(+2.4024000000000000000000e+04), // 36
        _C(+4.4616000000000000000000e+04), // 24
        _C(+1.2584000000000000000000e+04), // 12
        _C(+2.6400000000000000000000e+02)  // 0
    };
    _T x12=pow12(x);
    _T r=householder_step(x12, x, y, p, q);
    return r;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_12::householder6(_T x, _T y)
{
    static constexpr const _C p[]={
        _C(-1.0920000000000000000000e+03), // 60
        _C(-1.6926000000000000000000e+04), // 48
        _C(-1.5444000000000000000000e+04), // 36
        _C(+2.4024000000000000000000e+04), // 24
        _C(+9.2400000000000000000000e+03), // 12
        _C(+1.9800000000000000000000e+02)  // 0
    };
    static constexpr const _C q[]={
        _C(+3.0940000000000000000000e+03), // 60
        _C(+9.7097000000000000000000e+04), // 48
        _C(+3.5778600000000000000000e+05), // 36
        _C(+2.5625600000000000000000e+05), // 24
        _C(+3.2032000000000000000000e+04), // 12
        _C(+2.3100000000000000000000e+02)  // 0
    };
    _T x12=pow12(x);
    _T r=householder_step(x12, x, y, p, q);
    return r;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_12::householder7(_T x, _T y)
{
    static constexpr const _C p[]={
        _C(-3.0940000000000000000000e+03), // 72
        _C(-9.4003000000000000000000e+04), // 60
        _C(-2.6068900000000000000000e+05), // 48
        _C(+1.0153000000000000000000e+05), // 36
        _C(+2.2422400000000000000000e+05), // 24
        _C(+3.1801000000000000000000e+04), // 12
        _C(+2.3100000000000000000000e+02)  // 0
    };
    static constexpr const _C q[]={
        _C(+7.9560000000000000000000e+03), // 72
        _C(+4.4530200000000000000000e+05), // 60
        _C(+2.8957500000000000000000e+06), // 48
        _C(+4.1235480000000000000000e+06), // 36
        _C(+1.4002560000000000000000e+06), // 24
        _C(+8.4942000000000000000000e+04), // 12
        _C(+1.9800000000000000000000e+02)  // 0
    };
    _T x12=pow12(x);
    _T r=householder_step(x12, x, y, p, q);
    return r;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_12::householder8(_T x, _T y)
{
    static constexpr const _C p[]={
        _C(-3.5360000000000000000000e+03), // 84
        _C(-1.9437600000000000000000e+05), // 72
        _C(-1.0890880000000000000000e+06), // 60
        _C(-5.4568800000000000000000e+05), // 48
        _C(+1.2103520000000000000000e+06), // 36
        _C(+5.8458400000000000000000e+05), // 24
        _C(+3.7664000000000000000000e+04), // 12
        _C(+8.8000000000000000000000e+01)  // 0
    };
    static constexpr const _C q[]={
        _C(+8.3980000000000000000000e+03), // 84
        _C(+8.0094300000000000000000e+05), // 72
        _C(+8.5256600000000000000000e+06), // 60
        _C(+2.1126105000000000000000e+07), // 48
        _C(+1.4604590000000000000000e+07), // 36
        _C(+2.6287690000000000000000e+06), // 24
        _C(+8.1224000000000000000000e+04), // 12
        _C(+5.5000000000000000000000e+01)  // 0
    };
    _T x12=pow12(x);
    _T r=householder_step(x12, x, y, p, q);
    return r;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_12::householder9(_T x, _T y)
{
    static constexpr const _C p[]={
        _C(-7.5582000000000000000000e+04), // 96
        _C(-7.1329050000000000000000e+06), // 84
        _C(-6.9522453000000000000000e+07), // 72
        _C(-1.1340400500000000000000e+08), // 60
        _C(+5.8693635000000000000000e+07), // 48
        _C(+1.0778238900000000000000e+08), // 36
        _C(+2.2927905000000000000000e+07), // 24
        _C(+7.3052100000000000000000e+05), // 12
        _C(+4.9500000000000000000000e+02)  // 0
    };
    static constexpr const _C q[]={
        _C(+1.6796000000000000000000e+05), // 96
        _C(+2.6369200000000000000000e+07), // 84
        _C(+4.3600070800000000000000e+08), // 72
        _C(+1.7287041200000000000000e+09), // 60
        _C(+2.0916695800000000000000e+09), // 48
        _C(+7.9448512000000000000000e+08), // 36
        _C(+8.1078140000000000000000e+07), // 24
        _C(+1.3053040000000000000000e+06), // 12
        _C(+2.2000000000000000000000e+02)  // 0
    };
    _T x12=pow12(x);
    _T r=householder_step(x12, x, y, p, q);
    return r;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_12::householder10(_T x, _T y)
{
    static constexpr const _C p[]={
        _C(-8.3980000000000000000000e+04), // 108
        _C(-1.3100620000000000000000e+07), // 96
        _C(-2.0481575400000000000000e+08), // 84
        _C(-6.4635170600000000000000e+08), // 72
        _C(-1.8148273000000000000000e+08), // 60
        _C(+6.4859223000000000000000e+08), // 48
        _C(+3.5670349000000000000000e+08), // 36
        _C(+3.9886418000000000000000e+07), // 24
        _C(+6.5254200000000000000000e+05), // 12
        _C(+1.1000000000000000000000e+02)  // 0
    };
    static constexpr const _C q[]={
        _C(+1.7635800000000000000000e+05), // 108
        _C(+4.4340582000000000000000e+07), // 96
        _C(+1.0957076130000000000000e+09), // 84
        _C(+6.5618093970000000000000e+09), // 72
        _C(+1.2661678029000000000000e+10), // 60
        _C(+8.5514221650000000000000e+09), // 48
        _C(+1.9262593350000000000000e+09), // 36
        _C(+1.1630833500000000000000e+08), // 24
        _C(+9.8026500000000000000000e+05), // 12
        _C(+3.3000000000000000000000e+01)  // 0
    };
    _T x12=pow12(x);
    _T r=householder_step(x12, x, y, p, q);
    return r;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root_12::householder16(_T x, _T y)
{
    static constexpr const _C p[]={
        _C(-7.7261600000000000000000e+06), // 168
        _C(-1.5339941840000000000000e+10), // 156
        _C(-1.9888684613600000000000e+12), // 144
        _C(-5.6887488326240000000000e+13), // 132
        _C(-5.3772413635054400000000e+14), // 120
        _C(-1.9372475721204320000000e+15), // 108
        _C(-2.4330018873869280000000e+15), // 96
        _C(+2.9259193894444800000000e+14), // 84
        _C(+2.5695843790050720000000e+15), // 72
        _C(+1.6722648043930400000000e+15), // 60
        _C(+3.9605483394276800000000e+14), // 48
        _C(+3.5365013489312000000000e+13), // 36
        _C(+9.9878355636800000000000e+11), // 24
        _C(+5.5456749920000000000000e+09), // 12
        _C(+1.3075040000000000000000e+06)  // 0
    };
    static constexpr const _C q[]={
        _C(+1.3037895000000000000000e+07), // 168
        _C(+3.7489616775000000000000e+10), // 156
        _C(+6.5352009875850000000000e+12), // 144
        _C(+2.4954824093391000000000e+14), // 132
        _C(+3.2714511209520750000000e+15), // 120
        _C(+1.8140635643683185000000e+16), // 108
        _C(+4.7360957693020461000000e+16), // 96
        _C(+6.1297676002570068000000e+16), // 84
        _C(+3.9843305443853973000000e+16), // 72
        _C(+1.2725050238074521000000e+16), // 60
        _C(+1.8746544822803550000000e+15), // 48
        _C(+1.1226931480920600000000e+14), // 36
        _C(+2.1307151118330000000000e+12), // 24
        _C(+7.2953691030000000000000e+09), // 12
        _C(+7.3547100000000000000000e+05)  // 0
    };
    _T x12=pow12(x);
    _T r=householder_step(x12, x, y, p, q);
    return r;
}



// Local Variables:
// mode: c++
// end:
#endif
