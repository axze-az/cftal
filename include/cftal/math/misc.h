//
// Copyright Axel Zeuner 2010-2018. Use, modification and
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

template <typename _T>
_T
cftal::math::impl::root12::pow12(_T x)
{
    // _T x12=powu<_T, 12>::v(x);
#if 0
    using d_ops=cftal::impl::d_real_ops<_T, d_real_traits<_T>::fma>;
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
    using d_ops=cftal::impl::d_real_ops<_T, d_real_traits<_T>::fma>;
    _T x12h, x12l;
    _T t;
    // compensated product with first multiplication unrolled
    d_ops::sqr12(x12h, x12l, x);
    for (int i=2; i<12; ++i) {
        d_ops::mul12(x12h, t, x12h, x);
        x12l = x12l * x + t;
    }
    return x12h;
#if 0
    // avoid rounding errors, but is also slow
    _T x12=x;
    for (int i=0; i<11; ++i)
        x12*=x;
    return x12;
#endif
#endif
}

template <typename _C, typename _T>
_T
cftal::math::impl::root12::nr(_T x, _T y)
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
#if 0
    using d_ops=cftal::impl::
        d_real_ops<_T, d_real_traits<_T>::fma>;
    _T xn = x - _C(1.0/12.0) * d_ops::xfma(-1.0/x11, y, x);
#else
    _T xn = x - _C(1.0/12.0) * (x - y/x11);
#endif
#endif
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root12::halley(_T x, _T y)
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
cftal::math::impl::root12::order3(_T x, _T y)
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
cftal::math::impl::root12::order4(_T x, _T y)
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
cftal::math::impl::root12::order5(_T x, _T y)
{
    // _T x12=powu<_T, 12>::v(x);
    _T x12=pow12(x);
    _T z = (y-x12)/x12;
    _T d= z* horner(z,
                    _C(-8855.0/497664.0),
                    _C(253.0/10368.0),
                    _C(-11.0/288.0),
                    _C(1.0/12.0));
    _T xn= x + x*d;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root12::order6(_T x, _T y)
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
cftal::math::impl::root12::order8(_T x, _T y)
{
    // _T x12=powu<_T, 12>::v(x);
    _T x12=pow12(x);
    _T z = (y-x12)/x12;
    _T d= z* horner(z,
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
cftal::math::impl::root12::order9(_T x, _T y)
{
    // _T x12=powu<_T, 12>::v(x);
    _T x12=pow12(x);
    _T z = (y-x12)/x12;
    _T d= z* horner(z,
                    _C(4134346117.0/495338913792.0),
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
cftal::math::impl::root12::order10(_T x, _T y)
{
    // _T x12=powu<_T, 12>::v(x);
    _T x12=pow12(x);
    _T z = (y-x12)/x12;
    _T d= z* horner(z,
                    _C(392762881115.0/53496602689536.0),
                    _C(4134346117.0/495338913792.0),
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
cftal::math::impl::root12::householder3(_T x, _T y)
{
    _T x12=pow12(x);
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
    _T x12=pow12(x);
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
    _T x12=pow12(x);
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
    _T x12= pow12(x);
    _T y1=y;
    _T y2=y*y;
    _T y3=y2*y;
    _T y4=y3*y;
    _T y5=y4*y;
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
    _T x12=pow12(x);
    _T y1=y;
    _T y2=y*y;
    _T y3=y2*y;
    _T y4=y3*y;
    _T y5=y4*y;
    _T y6=y5*y;
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

template <typename _C, typename _T>
_T
cftal::math::impl::root12::householder8(_T x, _T y)
{
    _T x12=pow12(x);
    _T y1=y;
    _T y2=y*y;
    _T y3=y2*y;
    _T y4=y3*y;
    _T y5=y4*y;
    _T y6=y5*y;
    _T y7=y6*y;
    _T num= x*horner(x12,
                     _C(-3536.0),
                     _C(-194376.0)*y1,
                     _C(-1089088.0)*y2,
                     _C(-545688.0)*y3,
                     _C(1210352.0)*y4,
                     _C(584584.0)*y5,
                     _C(37664.0)*y6,
                     _C(88.0)*y7);
    _T denom= horner(x12,
                     _C(8398.0),
                     _C(800943.0)*y1,
                     _C(8525660.0)*y2,
                     _C(21126105.0)*y3,
                     _C(14604590.0)*y4,
                     _C(2628769.0)*y5,
                     _C(81224.0)*y6,
                     _C(55.0)*y7);
    _T xn = x + num/denom;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root12::householder9(_T x, _T y)
{
    _T x12=pow12(x);
    _T y1=y;
    _T y2=y*y;
    _T y3=y2*y;
    _T y4=y3*y;
    _T y5=y4*y;
    _T y6=y5*y;
    _T y7=y6*y;
    _T y8=y7*y;
    _T num = x*horner(x12,
                      _C(-75582.0),
                      _C(-7132905.0)*y1,
                      _C(-69522453.0)*y2,
                      _C(-113404005.0)*y3,
                      _C(58693635.0)*y4,
                      _C(107782389.0)*y5,
                      _C(22927905.0)*y6,
                      _C(730521.0)*y7,
                      _C(495.0)*y8);
    _T denom=horner(x12,
                    _C(167960.0),
                    _C(26369200.0)*y1,
                    _C(436000708.0)*y2,
                    _C(1728704120.0)*y3,
                    _C(2091669580.0)*y4,
                    _C(794485120.0)*y5,
                    _C(81078140.0)*y6,
                    _C(1305304.0)*y7,
                    _C(220.0)*y8);
    _T xn = x + num/denom;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root12::householder10(_T x, _T y)
{
    _T x12=pow12(x);
    _T y1=y;
    _T y2=y*y;
    _T y3=y2*y;
    _T y4=y3*y;
    _T y5=y4*y;
    _T y6=y5*y;
    _T y7=y6*y;
    _T y8=y7*y;
    _T y9=y8*y;
    _T num = x*horner(x12,
                      _C(-83980.0),
                      _C(-13100620.0)*y1,
                      _C(-204815754.0)*y2,
                      _C(-646351706.0)*y3,
                      _C(-181482730.0)*y4,
                      _C(648592230.0)*y5,
                      _C(356703490.0)*y6,
                      _C(39886418.0)*y7,
                      _C(652542.0)*y8,
                      _C(110.0)*y9);
    _T denom = horner(x12,
                      _C(176358.0),
                      _C(44340582.0)* y1,
                      _C(1095707613.0)* y2,
                      _C(6561809397.0)* y3,
                      _C(12661678029.0)* y4,
                      _C(8551422165.0)* y5,
                      _C(1926259335.0)* y6,
                      _C(116308335.0)* y7,
                      _C(980265.0)* y8,
                      _C(33.0)*y9);
    _T xn = x + num/denom;
    return xn;
}

template <typename _C, typename _T>
_T
cftal::math::impl::root12::householder16(_T x, _T y)
{
    _T x12=pow12(x);
    _T y1=y;
    _T y2=y*y;
    _T y3=y2*y;
    _T y4=y3*y;
    _T y5=y4*y;
    _T y6=y5*y;
    _T y7=y6*y;
    _T y8=y7*y;
    _T y9=y8*y;
    _T y10=y9*y;
    _T y11=y10*y;
    _T y12=y11*y;
    _T y13=y12*y;
    _T y14=y13*y;
    _T num = x*horner(x12,
                      _C(-7726160),
                      _C(-15339941840.0)*y1,
                      _C(-1988868461360.0)* y2,
                      _C(-56887488326240.0)* y3,
                      _C(-537724136350544.0)* y4,
                      _C(-1937247572120432.0)* y5,
                      _C(-2433001887386928.0)* y6,
                      _C(292591938944448.0)* y7,
                      _C(2569584379005072.0)* y8,
                      _C(1672264804393040.0)* y9,
                      _C(396054833942768.0)* y10,
                      _C(35365013489312.0)* y11,
                      _C(998783556368.0)* y12,
                      _C(5545674992.0)* y13,
                      _C(1307504.0)* y14);
    _T denom = horner(x12,
                      _C(13037895),
                      _C(37489616775.0)* y1,
                      _C(6535200987585.0)* y2,
                      _C(249548240933910.0)* y3,
                      _C(3271451120952075.0)* y4,
                      _C(18140635643683185.0)* y5,
                      _C(47360957693020461.0)* y6,
                      _C(61297676002570068.0)* y7,
                      _C(39843305443853973.0)* y8,
                      _C(12725050238074521.0)* y9,
                      _C(1874654482280355.0)* y10,
                      _C(112269314809206.0)* y11,
                      _C(2130715111833.0)* y12,
                      _C(7295369103.0)* y13,
                      _C(735471.0)*y14);
    _T xn = x + num/denom;
    return xn;
}



// Local Variables:
// mode: c++
// end:
#endif
