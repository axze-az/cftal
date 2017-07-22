//
// Copyright Axel Zeuner 2010-2017. Use, modification and
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
#include <type_traits>
#include <limits>
#include <utility>
#include <stdexcept>

namespace cftal {

    namespace math {

        namespace impl {

            // sin(x + y) = sin(x) * cos(y) + sin(y) * cos(x);
            // sin(x - y) = sin(x) * cos(y) - sin(y) * cos(x);
            // sin(2x) = 2 * sin(x) * cos(x);

            // cos(x + y) = cos(x) * cos(y) - sin(x) * sin(y);
            // cos(x - y) = cos(x) * cos(y) + sin(x) * sin(y);
            // cos(2x) = cos(x)^2 - sin(x)^2 = 1 - 2 sin(x)^2

            template <class _T>
            _T sin2x(const _T& sinx, const _T& cosx);
            template <class _T>
            d_real<_T> sin2x(const d_real<_T>& sinx,
                             const d_real<_T>& cosx);
            template <class _T>
            _T cos2x(const _T& sinx, const _T& cosx);
            template <class _T>
            d_real<_T> cos2x(const d_real<_T>& sinx,
                             const d_real<_T>& cosx);
            template <class _T>
            _T sin4x(const _T& sinx, const _T& cosx);
            template <class _T>
            _T cos4x(const _T& sinx, const _T& cosx);

            // unsigned integer power
            template <class _T>
            struct powvu {
                static _T v(const _T& xx, unsigned p);
            };

            // integer power
            template <class _T>
            struct powvi {
                static _T v(const _T& xx, int p);
            };

            // unsigned integer pow
            template <class _T, unsigned _P>
            struct powu {
                static _T v(const _T& x);
            };

            // unsigned integer pow, specialized for _P==0
            template <class _T>
            struct powu<_T, 0U> {
                static _T v(const _T& x);
            };

            // unsigned integer pow, specialized for _P==1
            template <class _T>
            struct powu<_T, 1U> {
                static _T v(const _T& x);
            };

            // unsigned integer pow, specialized for _P==2
            template <class _T>
            struct powu<_T, 2U> {
                static _T v(const _T& x);
            };

            // helper functions for different root3 iteration steps
            struct root3 {
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

                // x^3 = y
                template <typename _C, typename _T>
                static
                _T
                order3(_T y, _T x);

                // x^3 = y
                template <typename _C, typename _T>
                static
                _T
                order4(_T y, _T x);

                // x^3 = y
                template <typename _C, typename _T>
                static
                _T
                order5(_T y, _T x);
            };

            // helper functions for different root12 iteration steps
            struct root12 {
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
                order7(_T y, _T x);

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
            };


            // n-th root calculator: newton raphson step with n variable
            template <class _RT, class _T=_RT>
            struct nth_root_vnr {
                static
                _RT v(const _T& xi, const _T& x, unsigned r);
            };

            // n-th root calculator: newton raphson step with n=_R
            template <unsigned _R, class _RT, class _T = _RT>
            struct nth_root_nr : public nth_root_vnr<_T> {
                // one newton raphson step
                static
                _RT v(const _T& xi, const _T& x);
            };

            // n-th root calculator: halley step with n=_R
            template <unsigned _R, class _RT, class _T = _RT>
            struct nth_root_halley : public nth_root_vnr<_T> {
                // one halley step
                static _RT v(const _T& xi, const _T& x);
            };

            template <unsigned _R, typename _T>
            struct nth_root_approx {
                // return a guess for root _R in [2^-R, 1)
                static _T v(_T x) { return _T(0.75); }
            };

            template <typename _T>
            struct nth_root_approx<3, _T> {
                static _T v(_T x);
            };

            // the initial guess for a vector of _SCALAR_FLOAT
            // using traits for root r
            template <typename _SCALAR_FLOAT,
                      typename _TRAITS>
            struct nth_root_guess {
                typedef typename _TRAITS::vf_type vf_type;
                static vf_type v(const vf_type& f, unsigned r);
            };

            // the initial guess for a vector of float
            // with int32_t using traits
            // for root _R
            template <typename _TRAITS>
            struct nth_root_guess<float, _TRAITS> {
                typedef typename _TRAITS::vf_type vf_type;
                typedef typename _TRAITS::vi_type vi_type;
                static vf_type v(const vf_type& f, unsigned r) {
                    // const int ebits = 8;
                    // const int fbits = 23;
                    vi_type i(_TRAITS::as_int(f));
                    const int bias = (1 << (8-1))-1;
                    const int bias_shl_23(bias << 23);
                    const divisor<vi_type, int32_t> rr(r);
                    i = vi_type(i - bias_shl_23) / rr +
                        bias_shl_23;
                    vf_type x(_TRAITS::as_float(i));
                    return x;
                }
            };

            // the initial guess for a vector of double
            // using traits for root _R
            template <typename _TRAITS>
            struct nth_root_guess<double, _TRAITS> {
                typedef typename _TRAITS::vf_type vf_type;
                typedef typename _TRAITS::vi_type vi_type;

                static vf_type v(const vf_type& f, unsigned r) {
                    vi_type hw=
                        _TRAITS::extract_high_word(f);
                    const int32_t bias = (1 << (11-1))-1;
                    vi_type bias_shl_20(bias << 20);
                    const divisor<vi_type, int32_t> rr(r);
                    hw = vi_type(hw - bias_shl_20)/rr +
                        bias_shl_20;
                    vf_type g0;
                    g0 = _TRAITS::combine_words(vi_type(0),
                                                hw  );
                    return g0;
#if 0
                    const int ebits = 11;
                    const int fbits = 52;
                    int64& i = (int64&) x;
                    const _int64 bias = (1 << (ebits-1))-1;
                    i = (i - (bias << fbits)) / n +
                        (bias << fbits);
                    return x;
#endif

                }
            };

            template <typename _FLOAT_T, typename _TRAITS,
                      unsigned _R>
            struct root_guess : public nth_root_guess<_FLOAT_T, _TRAITS> {
                using vf_type = typename _TRAITS::vf_type;

                static vf_type v(const vf_type& x) {
                    return nth_root_guess<_FLOAT_T, _TRAITS>::v(x, _R);
                }
            };

            // nth root implementation for double/float
            template <typename _FLOAT_T, typename _TRAITS,
                      unsigned _R>
            struct nth_root : public elem_func<_FLOAT_T, _TRAITS> {

                using vf_type = typename _TRAITS::vf_type;
                using vi_type = typename _TRAITS::vi_type;
                using vmf_type= typename _TRAITS::vmf_type;
                using vmi_type = typename _TRAITS::vmi_type;
                using dvf_type = typename _TRAITS::dvf_type;

                using base_type = elem_func<_FLOAT_T, _TRAITS>;
                using base_type::frexp;
                using base_type::ldexp;
                using base_type::ilogbp1;
                using base_type::scale_exp_k;

                template <unsigned _STEPS=6>
                static vf_type v(arg_t<vf_type> f);
            };
        } // impl

        // integer power with constant _I
        template <int _I, class _T>
        _T pow(const _T& x) {
            const unsigned _N= _I < 0 ? -_I : _I;
            _T r=impl::powu<_T, _N>::v(x);
            if (_I<0)
                r=_T(1)/r;
            return r;
        }
    }
}

template <class _T>
_T
cftal::math::impl::sin2x(const _T& sinx, const _T& cosx)
{
    return _T(2.0) * sinx * cosx;
}

template <class _T>
cftal::d_real<_T>
cftal::math::impl::sin2x(const d_real<_T>& sinx,
                         const d_real<_T>& cosx)
{
    return mul_pwr2(sinx* cosx, _T(2.0));
}

template <class _T>
_T
cftal::math::impl::cos2x(const _T& sinx, const _T& cosx)
{
    return cosx * cosx - sinx * sinx;
}

template <class _T>
cftal::d_real<_T>
cftal::math::impl::cos2x(const d_real<_T>& sinx,
                         const d_real<_T>& cosx)
{
    return sqr(cosx) - sqr(sinx);
}

template <class _T>
_T
cftal::math::impl::sin4x(const _T& sinx, const _T& cosx)
{
    return sin2x(sin2x(sinx, cosx),
                 cos2x(sinx, cosx));
}

template <class _T>
_T
cftal::math::impl::cos4x(const _T& sinx, const _T& cosx)
{
    return cos2x(sin2x(sinx, cosx),
                 cos2x(sinx, cosx));
}

template <class _T>
_T
cftal::math::impl::powvu<_T>::v(const _T& xx, unsigned n)
{
    _T x(xx);
    _T r(1);
    while (1) {
        if (n & 1)
            r*= x;
        n >>= 1;
        if (n == 0)
            break;
        x *= x;
    }
    return r;
}

template <class _T>
_T
cftal::math::impl::powvi<_T>::v(const _T& xx, int i)
{
    unsigned n= i < 0 ? -i : i;
    _T r=powvu<_T>::v(xx, n);
    if (i<0)
        r= _T(1)/r;
    return r;
}


template <class _T, unsigned _P>
inline
_T
cftal::math::impl::powu<_T, _P>::v(const _T& x)
{
    _T r(powu<_T, _P/2>::v(x*x));
    if (_P & 1)
        r *= x;
    return r;
}

template <class _T>
inline
_T
cftal::math::impl::powu<_T, 0U>::v(const _T& x)
{
    return _T(1);
}

template <class _T>
inline
_T
cftal::math::impl::powu<_T, 1U>::v(const _T& x)
{
    return x;
}

template <class _T>
inline
_T
cftal::math::impl::powu<_T, 2U>::v(const _T& x)
{
    return x*x;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root3::nr(_T x, _T y)
{
    _T d= _C(1.0/3.0) * (y/(x*x) - x);
    _T xn= x + d;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root3::halley(_T x, _T y)
{
    _T s=x*x*x;
    _T xn = x -(s - y) * x/(_C(2.0)*s+y);
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root3::order3(_T x, _T y)
{
#if 1
    _T x3= x*x*x;
    _T z= (y -x3)/x3;
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
cftal::math::impl::root3::order4(_T x, _T y)
{
#if 1
    _T x3= x*x*x;
    _T z= (y -x3)/x3;
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
cftal::math::impl::root3::order5(_T x, _T y)
{
    _T x3= x*x*x;
    _T z= (y -x3)/x3;
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
cftal::math::impl::root12::nr(_T x, _T y)
{
    _T x11=powu<_T, 11>::v(x);
    _T xn = x - _C(1.0/12.0) * (x - y/x11);
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root12::halley(_T x, _T y)
{
    _T x12=powu<_T, 12>::v(x);
    _T num= _C(2.0/11.0) * x * (y - x12);
    _T denom= y + _C(13.0/11.0) *x12;
    _T xn = x + num/denom;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root12::order3(_T x, _T y)
{
    _T x12=powu<_T, 12>::v(x);
    _T z = (y-x12)/x12;
    _T d= z* horner(z,
                    _C(-11.0/288.0),
                    _C(1.0/12.0));
    _T xn= x + x*d;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root12::order7(_T x, _T y)
{
    _T x12=powu<_T, 12>::v(x);
    _T z = (y-x12)/x12;
    _T d= z* horner(z,
                    _C(-4910983/429981696.0),
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
cftal::math::impl::root12::householder3(_T x, _T y)
{
    _T x12=powu<_T, 12>::v(x);
    _T y1=y;
    _T y2=y*y;
    _T num= x*horner(x12,
                     _C(-39.0),
                     _C(6.0)*y1,
                     _C(33.0)*y2);
    _T denom= horner(x12,
                     _C(182.0),
                     _C(572.0)*y1,
                     _C(110)*y2);
    _T xn = x + num/denom;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root12::householder4(_T x, _T y)
{
    _T x12=powu<_T, 12>::v(x);
    _T y1=y;
    _T y2=y*y;
    _T y3=y1*y2;
    _T num= x*horner(x12,
                     _C(-364.0),
                     _C(-780)*y1,
                     _C(924.0)*y2,
                     _C(220.0)*y3);
    _T denom= horner(x12,
                     _C(1365.0),
                     _C(10725.0)*y1,
                     _C(8151.0)*y2,
                     _C(495.0)*y3);
    _T xn = x + num/denom;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root12::householder5(_T x, _T y)
{
    _T x12=powu<_T, 12>::v(x);
    _T y1=y;
    _T y2=y*y;
    _T y3=y1*y2;
    _T y4=y2*y2;
    _T num= x*horner(x12,
                     _C(-455.0),
                     _C(-3120.0)*y1,
                     _C(858.0)*y2,
                     _C(2552.0)*y3,
                     _C(165.0)*y4);
    _T denom= horner(x12,
                     _C(1456.0),
                     _C(24024.0)*y1,
                     _C(44616.0)*y2,
                     _C(12584.0)*y3,
                     _C(264.0)*y4);
    _T xn = x + num/denom;
    return xn;
}


template <typename _C, typename _T>
_T
cftal::math::impl::root12::householder6(_T x, _T y)
{
    _T x12= powu<_T, 12>::v(x);
    _T y1=y;
    _T y2=y*y;
    _T y3=y2*y;
    _T y4=y2*y2;
    _T y5=y3*y2;
    _T num= x*horner(x12,
                     _C(-1092.0),
                     _C(-16926.0)*y1,
                     _C(-15444.0)*y2,
                     _C(24024.0)*y3,
                     _C(9240.0)*y4,
                     _C(198.0)*y5);
    _T denom= horner(x12,
                     _C(3094.0),
                     _C(97097.0)*y1,
                     _C(357786.0)*y2,
                     _C(256256.0)*y3,
                     _C(32032.0)*y4,
                     _C(231.0)*y5);
    _T xn = x + num/denom;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root12::householder7(_T x, _T y)
{
    _T x12= powu<_T,12>::v(x);
    _T y1=y;
    _T y2=y*y;
    _T y3=y2*y;
    _T y4=y2*y2;
    _T y5=y3*y2;
    _T y6=y3*y3;
    _T num= x*horner(x12,
                     _C(-3094.0),
                     _C(-94003.0)*y1,
                     _C(-260689.0)*y2,
                     _C(101530.0)*y3,
                     _C(224224.0)*y4,
                     _C(31801.0)*y5,
                     _C(231.0)*y6);
    _T denom= horner(x12,
                     _C(7956.0),
                     _C(445302.0)*y1,
                     _C(2895750.0)*y2,
                     _C(4123548.0)*y3,
                     _C(1400256.0)*y4,
                     _C(84942.0)*y5,
                     _C(198.0)*y6);
    _T xn = x + num/denom;
    return xn;
}


template <class _RT, class _T>
_RT
cftal::math::impl::nth_root_vnr<_RT, _T>::
v(const _T& xi, const _T& x, unsigned r)
{
    const _T rr(r);
    _T x_pow_nm1(powvu<_T>::v(xi, r-1));
    _T en( x - xi * x_pow_nm1);
    _T den(rr * x_pow_nm1);
    _T xip1( xi + en / den);
    return xip1;
};


template <unsigned _R, class _RT, class _T>
_RT
cftal::math::impl::nth_root_nr<_R, _RT, _T>::v(const _T& xi, const _T& x)
{
#if 1
    const _T rcp_r(1.0/_R);
    _RT x_pow_nm1=powu<_RT, _R-1>::v(_RT(xi));
    _RT corr = rcp_r*(xi-x/x_pow_nm1);
    _RT xip1 = xi - corr;
    return xip1;
#else
    const _T r(_R);
    _RT x_pow_nm1(powu<_RT, _R-1>::v(xi));
    _RT en( x - xi * x_pow_nm1);
    _RT den(r * x_pow_nm1);
    _RT xip1( xi + en / den);
    return xip1;
#endif
};

template <unsigned _R, class _RT, class _T>
_RT
cftal::math::impl::nth_root_halley<_R, _RT, _T>::v(const _T& xi, const _T& x)
{
    const _T r(_R);
    const _T two(2.0);
    _RT x_pow(powu<_RT, _R>::v(xi));
    _RT en(_T(two* xi) * (x - x_pow));
    _RT den(r * (x+x_pow) - x + x_pow);
    _RT xip1(xi + en /den);
    return xip1;
}


template <typename _T>
_T
cftal::math::impl::nth_root_approx<3, _T>::v(_T x)
{
#if 0
    // maximum error 6.774866715814284b-4 in [2^-3, 2^0)
    static const _T a[]= {
        +1.431375762469744e0 /* x^5 */,
        -4.691579063121689e0 /* x^4 */,
        +6.15346734720791e0  /* x^3 */,
        -4.287580954173022e0 /* x^2 */,
        +2.101233104609554e0 /* x^1 */
        +2.937612896790845e-1 /* x^0 */
    };
    // maximum error 2.651222503616686b-4 in [2^-3, 2^0)
    static const _T a[]={
        -2.462358311592589e0 /* x^6 */,
        +9.368149930890834e0 /* x^5 */,
        -1.463283356717269e1 /* x^4 */,
        +1.226301448576061e1 /* x^3 */,
        -6.200836296768183e0 /* x^2 */,
        +2.38655227371457e0  /* x^1 */,
        +2.780463629170873e-1 /* x^0 */
    };
    // maximum error 1.070325426252539b-4 in [2^-3, 2^0)
    static const _T a[]={
        +4.407940728992934e0, // x^7
        -1.914086520846586e1, // x^6
        +3.491722222528436e1, // x^5
        -3.498415183424161e1, // x^4
        +2.127308275625481e1, // x^3
        -8.394369046537729e0, // x^2
        +2.656039417162971e0, // x
        +2.652079940927634e-1
    };
    // maximum error 4.395396547265176b-5 in [2^-3, 2^0)
    static const _T a[]= {
        -8.082321821879138e0  /* x^8*/ ,
        +3.951186826818802e1  /* x^7*/ ,
        -8.271122758768972e1  /* x^6*/ ,
        +9.719626611621892e1  /* x^5*/ ,
        -7.082056933547489e1  /* x^4*/ ,
        +3.357862597275239e1  /* x^3*/ ,
        -1.083848841889517e1  /* x^2*/ ,
        +2.911304691900277e0  /* x^1 */ ,
        +2.544981609138214e-1 /* x^0 */
    };
    // maximum error 7.794566660340572b-6 in [2^-3, 2^0)
    static const _T a[] = {
        -2.893793723365649e1, // x^10
        +1.733287884346741e2, // x^9
        -4.574701604941978e2, // x^8
        +7.010147297308644e2, // x^7
        -6.921659085115613e2, // x^6
        +4.62560031574252e2, // x^5
        -2.14374717173087e2, // x^4
        +6.988046400220901e1, // x^3
        -1.646473046613031e1, // x^2
        +3.392112926339188e0, // x^1
        2.373194157275016e-1
    };
    // maximum error 1.429853296572885b-6 in [2^-3, 2^0)
    static const _T a[]= {
        -1.086223987436328e2, // x^12
        +7.713403390094619e2, // x^11
        -2.462544006306743e3, // x^10
        +4.672629599539334e3, // x^9
        -5.870886414752144e3, // x^8
        +5.152410559174283e3, // x^7
        -3.248621593913108e3, // x^6
        +1.492090997687755e3, // x^5
        -5.01902172146935e2, // x^4
        +1.240088668410992e2, // x^3
        -2.296653315520015e1, // x^2
        +3.838691064614486e0, // x
        +2.240642713619926e-1
    };
    // maximum error 1.070325426252539b-4 in [2^-3, 2^0)
    static const _T a[]={
        +4.407940728992934e0, // x^7
        -1.914086520846586e1, // x^6
        +3.491722222528436e1, // x^5
        -3.498415183424161e1, // x^4
        +2.127308275625481e1, // x^3
        -8.394369046537729e0, // x^2
        +2.656039417162971e0, // x
        +2.652079940927634e-1
    };
    _T g=poly(x, a);
#endif
    using vf_type = _T;
  // coefficients for cbrt generated by sollya
    // x^4
    const vf_type cbrt_c4=-0x1.c517452d08a9ep-1;  // 0xbfec517452d08a9e
    // x^3
    const vf_type cbrt_c3=0x1.3a0af15bcfa1ap1;  // 0x4003a0af15bcfa1a
    // x^2
    const vf_type cbrt_c2=-0x1.5724904ed69cap1;  // 0xc005724904ed69ca
    // x^1
    const vf_type cbrt_c1=0x1.cbf973dd98759p0;  // 0x3ffcbf973dd98759
    // x^0
    const vf_type cbrt_c0=0x1.412cc5a825c41p-2;  // 0x3fd412cc5a825c41
    _T g= poly(x,
               cbrt_c4,
               cbrt_c3,
               cbrt_c2,
               cbrt_c1,
               cbrt_c0);
    return g;
};

template <typename _FLOAT_T, typename _TRAITS, unsigned _R>
template <unsigned _STEPS>
typename cftal::math::impl::nth_root<_FLOAT_T, _TRAITS, _R>::vf_type
cftal::math::impl::nth_root<_FLOAT_T, _TRAITS, _R>::v(arg_t<vf_type> x)
{
    using std::abs;
    vf_type xp=abs(x);
    // m in [0.5, 1)
    const divisor<vi_type, int32_t> idivr(_R);
    vi_type e = ilogbp1(xp);
    vi_type en= e / idivr;
    vi_type rn= remainder(e, vi_type(_R), en);
    // select rnc so that rnc [-R, -R+1, -R2,-1,0]
    vmi_type rngt0 = rn > 0;
    vi_type rnc= _TRAITS::sel(rngt0, rn-vi_type(_R), rn);
    vi_type re= _TRAITS::sel(rngt0, en+1, en);
    vi_type sc= rnc - e;
    // mm0 in [2^-R, 2^0)
    vf_type mm0 = ldexp(xp, sc);
    vf_type mm = nth_root_approx<_R, vf_type>::v(mm0);
    if (_STEPS>1) {
        using step_t= nth_root_halley<_R, vf_type, vf_type>;
        for (uint32_t i=0; i<_STEPS-1; ++i) {
            mm= step_t::v(mm, mm0);
        }
    }
    if (_STEPS>0) {
        if (_R==3) {
            using step_t= nth_root_nr<_R, vf_type, vf_type>;
            mm= step_t::v(mm, mm0);
        } else {
            using step_t=nth_root_nr<_R, dvf_type, vf_type>;
            dvf_type dmm;
            for (uint32_t i=_STEPS-1; i< _STEPS; ++i)
                dmm = step_t::v(mm, mm0);
            mm = dmm.h() + dmm.l();
        }
    }
    // scale back
    vf_type res=ldexp(mm, re);
    if ((_R&1) != 0) {
        // restore sign
        res=copysign(res, x);
    }
    vmf_type is_zero_or_inf_or_nan=
        (x == vf_type(0)) | isinf(x) | isnan(x);
    res=_TRAITS::sel(is_zero_or_inf_or_nan,
                     x, res);
    if ((_R&1) == 0) {
        res = _TRAITS::sel(x<0, _TRAITS::nan(), res);
    }
    return res;
}


// Local Variables:
// mode: c++
// end:
#endif
