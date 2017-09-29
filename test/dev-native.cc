//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/vec.h"
#include "cftal/vec_traits.h"
#include "cftal/math/elem_func.h"
#include "cftal/math/elem_func_core_f64.h"
#include "cftal/math/elem_func_core_f32.h"
#include "cftal/math/impl_estrin.h"
#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_expm1.h"
#include <tuple>
#include <iostream>
#include <iomanip>
#include <memory>
#include </home/axel/iaca-lin64/include/iacaMarks.h>

/*
    floatn cos(floatn x);
    floatn exp(floatn x); +
    floatn exp2(floatn x); +
    floatn exp10(floatn x); +
    floatn log(floatn x); +
    floatn log2(floatn x); +
    floatn log10(floatn x); +
    floatn recip(floatn x);
    floatn rsqrt(floatn x);
    floatn sin(floatn x);
    floatn sqrt(floatn x);
    floatn tan(floatn x);
    floatn divide(floatn x, floatn y);
    floatn powr(floatn x, floatn y);
 */

#define EXP 1

namespace cftal {

    namespace math {
        template <typename _FLOAT_T, typename _TRAITS_T>
        struct test_func : public elem_func_core< _FLOAT_T, _TRAITS_T> {
            using base_type = elem_func_core<_FLOAT_T, _TRAITS_T>;
            using my_type = test_func<_FLOAT_T, _TRAITS_T>;
            using vf_type = typename base_type::vf_type;
            using vi_type = typename base_type::vi_type;
            using vmf_type = typename base_type::vmf_type;
            using vmi_type = typename base_type::vmi_type;
            using dvf_type = typename base_type::dvf_type;

            static vf_type func(arg_t<vf_type> vf);
        };

        template <typename _T>
        struct test_func<double, _T> : public elem_func_core<double, _T> {
            using base_type = elem_func_core<double, _T>;
            using vf_type = typename _T::vf_type;
            using vi_type = typename _T::vi_type;
            // using vli_type = typename _T::vli_type;
            using vi2_type = typename _T::vi2_type;
            using vmf_type = typename _T::vmf_type;
            using vmi_type = typename _T::vmi_type;
            using vmi2_type = typename _T::vmi2_type;

            using dvf_type = d_real<vf_type>;
            using tvf_type = t_real<vf_type>;
            using my_type = test_func<double, _T>;

            using d_ops = typename base_type::d_ops;

            // static vf_type func_k(arg_t<vf_type> vf);

            using base_type::ilogbp1_k;
            using base_type::ldexp_k;
            using base_type::pow_k;


            template <bool _EXP_M1>
            static
            vf_type
            __native_exp_div_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
                               arg_t<vf_type> kf, arg_t<vi2_type> k);

            template <bool _EXP_M1>
            static
            vf_type
            __native_exp_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
                           arg_t<vf_type> kf, arg_t<vi2_type> k);

            static
            vf_type
            native_log_k(arg_t<vf_type> x);

            template <bool _EXP_M1>
            static
            vf_type
            native_exp_k(arg_t<vf_type> x);

            static
            vf_type
            native_exp(arg_t<vf_type> x);

            static
            vf_type
            native_expm1(arg_t<vf_type> x);

            static
            vf_type
            native_log(arg_t<vf_type> x);
        };

        template <typename _T>
        struct test_func<float, _T> : public elem_func_core<float, _T> {
            using base_type = elem_func_core<float, _T>;
            using vf_type = typename _T::vf_type;
            using vi_type = typename _T::vi_type;
            // using vli_type = typename _T::vli_type;
            using vmf_type = typename _T::vmf_type;
            using vmi_type = typename _T::vmi_type;

            using dvf_type = d_real<vf_type>;
            using tvf_type = t_real<vf_type>;
            using my_type = test_func<float, _T>;

            using d_ops = typename base_type::d_ops;

            static vf_type func(arg_t<vf_type> vf);
            static vf_type func_k(arg_t<vf_type> vf);

            using base_type::ilogbp1;
            using base_type::ldexp;
            using base_type::__reduce_exp_arg;
            using base_type::__scale_exp_k;
            using base_type::__exp_k;

            static
            vf_type
            __half_exp_k(arg_t<vf_type> xrh,
                         arg_t<vf_type> kf,
                         arg_t<vi_type> k);

            static
            vf_type
            half_exp_k(arg_t<vf_type> x);

            static
            vf_type
            half_exp(arg_t<vf_type> x);

            static
            vf_type
            half_exp2_k(arg_t<vf_type> x);

            static
            vf_type
            half_exp2(arg_t<vf_type> x);

            static
            vf_type
            half_exp10_k(arg_t<vf_type> x);

            static
            vf_type
            half_exp10(arg_t<vf_type> x);

            static
            vf_type
            half_log_k(arg_t<vf_type> x);

            static
            vf_type
            half_log(arg_t<vf_type> x);

            static
            vf_type
            half_log2(arg_t<vf_type> x);

            static
            vf_type
            half_log10(arg_t<vf_type> x);

            static
            std::pair<vf_type, vi_type>
            __half_reduce_trig_arg(arg_t<vf_type> x);

            static
            void
            half_sin_cos_k(arg_t<vf_type> x, vf_type* s, vf_type* c);

            static
            vf_type
            half_sin(arg_t<vf_type> x);

            static
            vf_type
            half_cos(arg_t<vf_type> x);

            static
            vf_type
            half_tan(arg_t<vf_type> x);

        };
    }

    namespace math {

        template <typename _FLOAT_T, typename _TRAITS_T>
        struct half_elem_func_core {
        };

        // common implementation of base and elementary functions
        // special argument handling like inf, nan, overflow, underflow
        // is done here
        template <typename _FLOAT_T, typename _TRAITS_T>
        struct half_elem_func
            : public half_elem_func_core< _FLOAT_T, _TRAITS_T> {
        };

        template <typename _T>
        struct half_elem_func_core<float, _T>
            : public elem_func_core<float, _T> {
            using base_type = elem_func_core<float, _T>;
        };
    }


    namespace test {

        template <typename _T>
        struct check_pow {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::pow(a, b);
            }
            static
            auto
            r(const _T& a, const _T& b) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, b, mpfr_pow, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a, const _T& b) {
                return std::pow(a, b);
            }
            static
            const char* fname() {
                return "pow";
            }
        };

        template <typename _T>
        struct check_native_exp {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                auto r=func_t::native_exp(a);
                return r;
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_exp, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::exp(a);
            }
            static
            const char* fname() {
                return "native_exp";
            }
        };

        template <typename _T>
        struct check_native_expm1 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                auto r=func_t::native_expm1(a);
                return r;
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_expm1, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::expm1(a);
            }
            static
            const char* fname() {
                return "native_expm1";
            }
        };

        template <typename _T>
        struct check_native_log {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                auto r=func_t::native_log(a);
                return r;
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_log, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::log(a);
            }
            static
            const char* fname() {
                return "native_log";
            }
        };

    }
}

template <typename _T>
template <bool _EXP_M1>
__attribute__((always_inline))
inline
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::
__native_exp_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
               arg_t<vf_type> kf, arg_t<vi2_type> k2)
{
   // [-0.3465735912322998046875, 0.3465735912322998046875] : | p - f | <= 2^-67.5
    // coefficients for exp generated by sollya
    // x^0 : +0x8p-3
    const double nat_exp_c0=+1.0000000000000000000000e+00;
    // x^1 : +0x8p-3
    const double nat_exp_c1=+1.0000000000000000000000e+00;
    // x^2 : +0x8p-4
    const double nat_exp_c2=+5.0000000000000000000000e-01;
    // x^3 : +0xa.aaaaaaaaaaaa8p-6
    const double nat_exp_c3=+1.6666666666666665741481e-01;
    // x^4 : +0xa.aaaaaaaaaaacp-8
    const double nat_exp_c4=+4.1666666666666685170384e-02;
    // x^5 : +0x8.888888888961p-10
    const double nat_exp_c5=+8.3333333333340843529502e-03;
    // x^6 : +0xb.60b60b60a81p-13
    const double nat_exp_c6=+1.3888888888873365812238e-03;
    // x^7 : +0xd.00d00cfa88cc8p-16
    const double nat_exp_c7=+1.9841269839039331096715e-04;
    // x^8 : +0xd.00d00d6b5b978p-19
    const double nat_exp_c8=+2.4801587348902822885563e-05;
    // x^9 : +0xb.8ef1e87f81768p-22
    const double nat_exp_c9=+2.7557322326013774747291e-06;
    // x^10 : +0x9.3f26623e02258p-25
    const double nat_exp_c10=+2.7557252167692825528943e-07;
    // x^11 : +0xd.72da4d99dd1ep-29
    const double nat_exp_c11=+2.5050050656120229688701e-08;
    // x^12 : +0x8.fc5bcb2f9dd7p-32
    const double nat_exp_c12=+2.0921639307947297714762e-09;
    // x^13 : +0xb.675e3aadcbc88p-36
    const double nat_exp_c13=+1.6594686274338619941159e-10;
    vf_type xx=xrh*xrh;
    vf_type i=horner(xx,
                     nat_exp_c13,
                     nat_exp_c11,
                     nat_exp_c9,
                     nat_exp_c7,
                     nat_exp_c5);
    vf_type j=horner(xx,
                     nat_exp_c12,
                     nat_exp_c10,
                     nat_exp_c8,
                     nat_exp_c6,
                     nat_exp_c4);
    vf_type y=horner(xrh, i, j,
                     nat_exp_c3, nat_exp_c2);
    vf_type ye;
#if 1
    if (_EXP_M1 == false) {
        y = horner(xrh, y, nat_exp_c1);
    } else {
        // y = horner(xrh, y, nat_exp_c1);
        y *= xrh;
        d_ops::add12cond(y, ye, nat_exp_c1, y);
        // horner_comp_quick(y, ye, xrh, y, nat_exp_c1);
    }
#endif
    // calculate expm1/xrh for correction term
    if (_EXP_M1 == false) {
        vf_type yl=y;
        y= horner(xrh, y, nat_exp_c0);
        // correction for errors in argument reduction
        vf_type yee= xrl + xrl * xrh * yl;
        ye= yee;
        y += ye;
        y = base_type::__scale_exp_k(y, kf, k2);
    } else {
        vf_type yl=y;
        // y = xrh * y;
        d_ops::mul122(y, ye, xrh, y, ye);
        // correction for errors in argument reduction
        vf_type yee= xrl + xrl * xrh*yl;
        ye= +yee;
        // 2^kf = 2*2^s ; s = kf/2
        vf_type scale = base_type::__scale_exp_k(vf_type(0.5), kf, k2);
        // e^x-1 = 2*(y * 2^s - 0.5)
        horner_comp_si(y, ye, scale, y, ye, vf_type(-0.5));
        y *= 2;
        y  = y + 2*ye;
        // x small, required for handling of subnormal numbers
        y = _T::sel((abs(xrh) < 0x1p-54) & (kf==0.0), xrh, y);
    }
    return y;
}

template <typename _T>
template <bool _EXP_M1>
__attribute__((always_inline))
inline
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::
__native_exp_div_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
                   arg_t<vf_type> kf, arg_t<vi2_type> k2)
{
    // IACA_START
    vf_type y;
    if (_EXP_M1 == false) {
        // exp(x) = 1 + 2x/(2-x+x^2*P(x^2)
        //                    x [x - x^2 * P]
        //        = 1 + x + ------------------
        //                    2 - [x - x^2 * P]
        // [0, 0.3465735912322998046875] : | p - f | <= 2^-56.578125
        // coefficients for expn generated by sollya
        // x^0 : +0xa.aaaaaaaaaaaa8p-6
        const vf_type expn_c0=+1.6666666666666665741481e-01;
        // x^2 : -0xb.60b60b60af088p-12
        const vf_type expn_c2=-2.7777777777762209694690e-03;
        // x^4 : +0x8.ab355dd7070ep-17
        const vf_type expn_c4=+6.6137566063822030622971e-05;
        // x^6 : -0xd.debafedf4fbdp-23
        const vf_type expn_c6=-1.6534377129482213292548e-06;
        // x^8 : +0xb.3469aa5968fdp-28
        const vf_type expn_c8=+4.1740899259070261892474e-08;
        // x^10 : -0x8.b38f6a7d59358p-33
        const vf_type expn_c10=-1.0129771083725208005378e-09;
        vf_type xx= xrh*xrh;
        vf_type P= horner(xx,
                          expn_c10,
                          expn_c8,
                          expn_c6,
                          expn_c4,
                          expn_c2,
                          expn_c0);
        vf_type br= xrh- xx*P;
        y = (xrh*br)/(2.0-br);
        y += xrh;
        vf_type yee= xrl + xrl * y;
        y += yee;
        y += 1;
        y = base_type::__scale_exp_k(y, kf, k2);
    } else {
    /* expm1(x)
    * Returns exp(x)-1, the exponential of x minus 1.
    *
    * Method
    *   1. Argument reduction:
    *      Given x, find r and integer k such that
    *
    *               x = k*ln2 + r,  |r| <= 0.5*ln2 ~ 0.34658
    *
    *      Here a correction term c will be computed to compensate
    *      the error in r when rounded to a floating-point number.
    *
    *   2. Approximating expm1(r) by a special rational function on
    *      the interval [0,0.34658]:
    *      Since
    *          r*(exp(r)+1)/(exp(r)-1) = 2+ r^2/6 - r^4/360 + ...
    *      we define R1(r*r) by
    *          r*(exp(r)+1)/(exp(r)-1) = 2+ r^2/6 * R1(r*r)
    *      That is,
    *          R1(r**2) = 6/r *((exp(r)+1)/(exp(r)-1) - 2/r)
    *                   = 6/r * ( 1 + 2.0*(1/(exp(r)-1) - 1/r))
    *                   = 1 - r^2/60 + r^4/2520 - r^6/100800 + ...
    *      We use a special Remez algorithm on [0,0.347] to generate
    *      a polynomial of degree 5 in r*r to approximate R1. The
    *      maximum error of this polynomial approximation is bounded
    *      by 2**-61. In other words,
    *          R1(z) ~ 1.0 + Q1*z + Q2*z**2 + Q3*z**3 + Q4*z**4 + Q5*z**5
    *      where   Q1  =  -1.6666666666666567384E-2,
    *              Q2  =   3.9682539681370365873E-4,
    *              Q3  =  -9.9206344733435987357E-6,
    *              Q4  =   2.5051361420808517002E-7,
    *              Q5  =  -6.2843505682382617102E-9;
    *              z   =  r*r,
    *      with error bounded by
    *          |                  5           |     -61
    *          | 1.0+Q1*z+...+Q5*z   -  R1(z) | <= 2
    *          |                              |
    *
    *      expm1(r) = exp(r)-1 is then computed by the following
    *      specific way which minimize the accumulation rounding error:
    *                             2     3
    *                            r     r    [ 3 - (R1 + R1*r/2)  ]
    *            expm1(r) = r + --- + --- * [--------------------]
    *                            2     2    [ 6 - r*(3 - R1*r/2) ]
    *
    *      To compensate the error in the argument reduction, we use
    *              expm1(r+c) = expm1(r) + c + expm1(r)*c
    *                         ~ expm1(r) + c + r*c
    *      Thus c+r*c will be added in as the correction terms for
    *      expm1(r+c). Now rearrange the term to avoid optimization
    *      screw up:
    *                      (      2                                    2 )
    *                      ({  ( r    [ R1 -  (3 - R1*r/2) ]  )  }    r  )
    *       expm1(r+c)~r - ({r*(--- * [--------------------]-c)-c} - --- )
    *                      ({  ( 2    [ 6 - r*(3 - R1*r/2) ]  )  }    2  )
    *                      (                                             )
    *
    *                 = r - E
    *   3. Scale back to obtain expm1(x):
    *      From step 1, we have
    *         expm1(x) = either 2^k*[expm1(r)+1] - 1
    *                  = or     2^k*[expm1(r) + (1-2^-k)]
    *   4. Implementation notes:
    *      (A). To save one multiplication, we scale the coefficient Qi
    *           to Qi*2^i, and replace z by (x^2)/2.
    *      (B). To achieve maximum accuracy, we compute expm1(x) by
    *        (i)   if x < -56*ln2, return -1.0, (raise inexact if x!=inf)
    *        (ii)  if k=0, return r-E
    *        (iii) if k=-1, return 0.5*(r-E)-0.5
    *        (iv)  if k=1 if r < -0.25, return 2*((r+0.5)- E)
    *                     else          return  1.0+2.0*(r-E);
    *        (v)   if (k<-2||k>56) return 2^k(1-(E-r)) - 1 (or exp(x)-1)
    *        (vi)  if k <= 20, return 2^k((1-2^-k)-(E-r)), else
    *        (vii) return 2^k(1-((E+2^-k)-r))
    *
    * Special cases:
    *      expm1(INF) is INF, expm1(NaN) is NaN;
    *      expm1(-INF) is -1, and
    *      for finite argument, only expm1(0)=0 is exact.
    *
    * Accuracy:
    *      according to an error analysis, the error is always less than
    *      1 ulp (unit in the last place).
    *
    * Misc. info.
    *      For IEEE double
    *          if x >  7.09782712893383973096e+02 then expm1(x) overflow
    *
    * Constants:
    * The hexadecimal values are the intended ones for the following
    * constants. The decimal values may be used, provided that the
    * compiler will convert from decimal to binary accurately enough
    * to produce the hexadecimal values shown.
    */
        // vf_type e= xr - y;
        // [0, 0.3465735912322998046875] : | p - f | <= 2^-61.734375
        // coefficients for expm1 generated by sollya
        // x^2 : -0x8.88888888887a8p-8
        const vf_type expm1_c2=-3.3333333333333138581711e-02;
        // x^4 : +0xd.00d00cff30828p-13
        const vf_type expm1_c4=+1.5873015872554529798882e-03;
        // x^6 : -0xa.670ccf68a8e2p-17
        const vf_type expm1_c6=-7.9365075820909145119103e-05;
        // x^8 : +0x8.67e55d0229b4p-21
        const vf_type expm1_c8=+4.0082185537485440587381e-06;
        // x^10 : -0xd.7ef32948d0b58p-26
        const vf_type expm1_c10=-2.0110454926619305237525e-07;
        /* x is now in primary range */
        vf_type hfx = 0.5*xrh;
        vf_type hxs = xrh*hfx;
        vf_type r1 = 1.0+hxs*horner(hxs,
                                    expm1_c10,
                                    expm1_c8,
                                    expm1_c6,
                                    expm1_c4,
                                    expm1_c2);
        vf_type tt  = 3.0-r1*hfx;
        vf_type e  = (hxs*(r1-tt))/(6.0 - xrh*tt);
        // if (k == 0)   /* c is 0 */
        //      return x - (x*e-hxs);
        vf_type cr = xrl;
        e  = xrh*(e-cr) - cr;
        e -= hxs;
        vi2_type t= _T::bias() - k2;
        vf_type two_pow_minus_k=_T::insert_exp(t);
        // xr - e = y --> xr -y = e
        t = _T::bias() + k2;
        vf_type two_pow_k=_T::insert_exp(t);
        // default cases:
        vf_type ym = _T::sel(kf < vf_type(20),
                            (xrh - e + (1.0 - two_pow_minus_k))*two_pow_k,
                            (xrh - (e+two_pow_minus_k)+1.0)*two_pow_k);
        // k < 0 || k > 56
        vf_type yt= xrh - e  + 1.0;
        yt= _T::sel(kf == vf_type(1024),
                    yt * 2.0 * 0x1p1023,
                    yt * two_pow_k);
        yt -= 1.0;
        ym = _T::sel((kf < vf_type(0)) | (kf>vf_type(56)), yt, ym);
        // k == 1
        yt = _T::sel(xrh < -0.25, -2.0*(e-(xrh+0.5)),1.0+2.0*(xrh-e));
        ym = _T::sel(kf == vf_type(1.0), yt, ym);
        // k == -1
        yt = 0.5 *(xrh-e) - 0.5;
        ym = _T::sel(kf == vf_type(-1.0), yt, ym);
        // k == 0
        ym = _T::sel(kf == vf_type(0.0), xrh-e, ym);
        // x small
        // ym = _T::sel(abs(x) < 0x1p-54, x, ym);
        y = ym;
    }
    // IACA_END
    return y;
}

template <typename _T>
inline
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::
native_log_k(arg_t<vf_type> xc)
{
    using fc = func_constants<double>;
    vmf_type is_denom=xc <= fc::max_denormal();
    vf_type x=_T::sel(is_denom, xc*0x1p54, xc);
    vi2_type k=_T::sel_val_or_zero(_T::vmf_to_vmi2(is_denom), vi2_type(-54));
    vi2_type lx, hx;
    _T::extract_words(lx, hx, x);
    /* reduce x into [sqrt(2)/2, sqrt(2)] */
    hx += 0x3ff00000 - 0x3fe6a09e;
    k += (hx>>20) - _T::bias();
    hx = (hx&0x000fffff) + 0x3fe6a09e;
    vf_type xr = _T::combine_words(lx, hx);

    vf_type xm = xr - 1.0;
    vf_type xp = xr + 1.0;
    vf_type s= xm/xp;
    vf_type z= s*s;

    vf_type P= base_type::log_k_poly(z);
    vf_type kf= _T::cvt_i_to_f(_T::vi2_odd_to_vi(k));

    vf_type log_x = s*(P-xm);
    using ctbl=impl::d_real_constants<d_real<double>, double>;
    log_x += kf * ctbl::m_ln2_cw[1];
    log_x += xm;
    log_x += kf * ctbl::m_ln2_cw[0];
    return log_x;
}

template <typename _T>
template <bool _EXP_M1>
inline
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::
native_exp_k(arg_t<vf_type> xc)
{
    vf_type xrh, xrl, kf;
    auto k=base_type::__reduce_exp_arg(xrh, xrl, kf, xc);
    vf_type y;
    if (_EXP_M1)
        y=__native_exp_k<_EXP_M1>(xrh, xrl, kf, k);
    else
        y=__native_exp_k<_EXP_M1>(xrh, xrl, kf, k);
    return y;
}

template <typename  _T>
inline
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::
native_exp(arg_t<vf_type> d)
{
    vf_type res=native_exp_k<false>(d);
    using fc= func_constants<double>;
    const vf_type exp_hi_inf= fc::exp_hi_inf();
    const vf_type exp_lo_zero= fc::exp_lo_zero();
    res = _T::sel_zero_or_val(d <= exp_lo_zero, res);
    res = _T::sel(d >= exp_hi_inf, _T::pinf(), res);
    // res = _T::sel(d == 0.0, 1.0, res);
    // res = _T::sel(d == 1.0, M_E, res);
    return res;
}

template <typename  _T>
inline
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::
native_log(arg_t<vf_type> d)
{
    vf_type x = native_log_k(d);
    const vf_type pinf(_T::pinf());
    const vf_type ninf(_T::ninf());
    x = _T::sel(isinf(d), pinf, x);
    // if (d < 0) x = NAN;
    x = _T::sel(d < vf_type(0.0), vf_type(_T::nan()), x);
    // if (d == 0) x = -INFINITY;
    x = _T::sel(d == vf_type(0.0), ninf, x);
    // NAN --> n_and_1
    x = _T::sel(isnan(d), d, x);
    // using fc= func_constants<_FLOAT_T>;
    // const vf_type log_lo_fin= fc::log_lo_fin;
    // const vf_type log_lo_val= fc::log_lo_val;
    // x = _T::sel(d == log_lo_fin, log_lo_val, x);
    return x;
}

template <typename _T>
inline
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::
native_expm1(arg_t<vf_type> d)
{
    vf_type res = native_exp_k<true>(d);
    using fc= func_constants<double>;
    const vf_type expm1_hi_inf= fc::expm1_hi_inf();
    const vf_type expm1_lo_minus_one= fc::expm1_lo_minus_one();
    res = _T::sel(d <= expm1_lo_minus_one, -1.0, res);
    res = _T::sel(d >= expm1_hi_inf, _T::pinf(), res);
    // res = _T::sel(d == 0.0, 0.0, res);
    // res = _T::sel(d == 1.0, M_E-1.0, res);
    return res;
}

int main_native_exp(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=8;
    const int _N=8;
    bool rc=true;
    std::size_t cnt=update_cnt(0x8000);
    bool speed_only=false;
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    } else {
        std::string test_data_dir = dirname(argv[0]);
        std::string test_data_file=
            append_filename(test_data_dir, "../../test/data/exp.testdata");
        if (argc > 1) {
            test_data_dir = argv[1];
            test_data_file = append_filename(test_data_dir, "exp.testdata");
        }
        std::vector<func_arg_result<double> > v=
            read_double_file(test_data_file, false);
        rc &= check_func_1<double, 1, check_native_exp<double> >(v, ulp, 0, false);
        rc &= check_func_1<double, 2, check_native_exp<double> >(v, ulp, 0, false);
        rc &= check_func_1<double, 4, check_native_exp<double> >(v, ulp, 0, false);
        rc &= check_func_1<double, 8, check_native_exp<double> >(v, ulp, 0, false);
    }
    func_domain<double> d=std::make_pair(-750.0, 710.0);
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        double, _N, check_native_exp<double> >::v(st, d, speed_only,
                                           cmp_ulp<double>(ulp, us),
                                           cnt);
    // check the denormal result range
    d= std::make_pair(-750, -7.083964185322641924358322e+02);
    rc &= of_fp_func_up_to<
        double, _N, check_native_exp<double> >::v(st, d, speed_only,
                                           cmp_ulp<double>(ulp, us),
                                           cnt>>3);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}


int main_native_expm1(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=8;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    } else {
#if 0
        std::string test_data_dir = dirname(argv[0]);
        std::string test_data_file=
            append_filename(test_data_dir, "../../test/data/expm1.testdata");
        if (argc > 1) {
            test_data_dir = argv[1];
            test_data_file = append_filename(test_data_dir, "expm1.testdata");
        }
        std::vector<func_arg_result<double> > v=
            read_double_file(test_data_file, false);
        rc &= check_func_1<double, 1, check_native_expm1<double> >(v, ulp,
                                                            0, false);
        rc &= check_func_1<double, 2, check_native_expm1<double> >(v, ulp,
                                                            0, false);
        rc &= check_func_1<double, 4, check_native_expm1<double> >(v, ulp,
                                                            0, false);
        rc &= check_func_1<double, 8, check_native_expm1<double> >(v, ulp,
                                                            0, false);
#endif
    }
    // func_domain<double> d=std::make_pair(-M_LN2/2, M_LN2/2);
    func_domain<double> d=std::make_pair(-380.0, 710.0);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        double, _N, check_native_expm1<double> >::v(st, d, speed_only,
                                             cmp_ulp<double>(ulp, us),
                                             cnt, true);
    d=std::make_pair(-0x1p-4, 0x1p-4);
    rc &= of_fp_func_up_to<
        double, _N, check_native_expm1<double> >::v(st, d, speed_only,
                                             cmp_ulp<double>(ulp, us),
                                             cnt>>2,
                                             true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_native_log(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=8;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    } else {
        std::string test_data_dir = dirname(argv[0]);
        std::string test_data_file=
            append_filename(test_data_dir, "../../test/data/log.testdata");
        if (argc > 1) {
            test_data_dir = argv[1];
            test_data_file = append_filename(test_data_dir, "log.testdata");
        }
        std::vector<func_arg_result<double> > v=
            read_double_file(test_data_file, false);
        rc&= check_func_1<double, 1, check_native_log<double> >(v, ulp, 0, false);
        rc&= check_func_1<double, 2, check_native_log<double> >(v, ulp, 0, false);
        rc&= check_func_1<double, 4, check_native_log<double> >(v, ulp, 0, false);
        rc&= check_func_1<double, 8, check_native_log<double> >(v, ulp, 0, false);
    }
    func_domain<double> d=std::make_pair(0.0,
                                         std::numeric_limits< double >::max());
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        double, _N, check_native_log<double> >::v(st, d, speed_only,
                                           cmp_ulp<double>(ulp, us),
                                           cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}


int main(int argc, char** argv)
{
    int r=0;
    // r |= main_native_exp(argc, argv);
    // r |= main_native_expm1(argc, argv);
    r = main_native_log(argc, argv);
    return r;
}
