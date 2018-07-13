//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_MATH_LANCZOS_H__)
#define __CFTAL_MATH_LANCZOS_H__ 1

#include <cftal/config.h>
#include <cftal/math/horner.h>

namespace cftal {
    namespace math {

        // an evaluator for lanczos approximations for the gamma
        // functions
        template <typename _T, typename _TBL,
                  std::size_t _P_HIGH_PREC=0, std::size_t _Q_HIGH_PREC=0>
        struct lanczos_rational : public _TBL {
            static
            _T at(_T x, _T* res_lo=nullptr) {
                return eval_rational<_P_HIGH_PREC,
                                     _Q_HIGH_PREC>(x,
                                                   _TBL::p,
                                                   _TBL::q,
                                                   res_lo);
            }

        };

        template <typename _T, typename _C,
                  std::size_t _N1, std::size_t _N2>
        d_real<_T>
        lanczos_rational_at(_T x,
                            const d_real<_C>(&p)[_N1],
                            const _C (&q)[_N2]);


        // a lanczos table from boost
        struct lanczos_table_boost_g_6_0246_N13 {
            static
            constexpr double g() {
                return +6.0246800407767295837402e+00;
                // return  6.024680040776729583740234375;
            }

            static
            constexpr double gm0_5() {
                return +5.5246800407767295837402e+00;
            }
            static constexpr
            double exp_minus_gm0_5_h() {
                return +3.9871442116253151197180e-03;
            }
            static constexpr
            double exp_minus_gm0_5_l() {
                return -3.8417174999999999999696e-20;
            }
            static
            constexpr const double p[]={
                2.5066282746310002701649081771338373386264310793408,
                210.82427775157934587250973392071336271166969580291,
                8071.6720023658162106380029022722506138218516325024,
                186056.26539522349504029498971604569928220784236328,
                2876370.6289353724412254090516208496135991145378768,
                31426415.585400194380614231628318205362874684987640,
                248874557.86205415651146038641322942321632125127801,
                1439720407.3117216736632230727949123939715485786772,
                6039542586.3520280050642916443072979210699388420708,
                17921034426.037209699919755754458931112671403265390,
                35711959237.355668049440185451547166705960488635843,
                42919803642.649098768957899047001988850926355848959,
                23531376880.410759688572007674451636754734846804940
            };
            static
            constexpr const double q[]={
                +1.0000000000000000000000e+00, // 12
                +6.6000000000000000000000e+01, // 11
                +1.9250000000000000000000e+03, // 10
                +3.2670000000000000000000e+04, // 9
                +3.5742300000000000000000e+05, // 8
                +2.6375580000000000000000e+06, // 7
                +1.3339535000000000000000e+07, // 6
                +4.5995730000000000000000e+07, // 5
                +1.0525807600000000000000e+08, // 4
                +1.5091797600000000000000e+08, // 3
                +1.2054384000000000000000e+08, // 2
                +3.9916800000000000000000e+07, // 1
                +0.0000000000000000000000e+00  // 0
            };
        };

        struct lanczos_table_g_6_02468_N13 {
            static constexpr
            double g() {
                return +6.0246800407767295837402e+00;
            }
            static constexpr
            double gm0_5() {
                return +5.5246800407767295837402e+00;
            }
            static constexpr
            double gm0_5_l() {
                return +0.0000000000000000000000e+00;
            }
            static constexpr
            double exp_minus_gm0_5_h() {
                return +3.9871442116253151197180e-03;
            }
            static constexpr
            double exp_minus_gm0_5_l() {
                return -3.8417174999999999999696e-20;
            }
            static constexpr
            const double p[]={
                +2.5066282746310002416124e+00, // 12
                +2.1082427775157935911921e+02, // 11
                +8.0716720023658162972424e+03, // 10
                +1.8605626539522348321043e+05, // 9
                +2.8763706289353724569082e+06, // 8
                +3.1426415585400193929672e+07, // 7
                +2.4887455786205416917801e+08, // 6
                +1.4397204073117215633392e+09, // 5
                +6.0395425863520278930664e+09, // 4
                +1.7921034426037208557129e+10, // 3
                +3.5711959237355667114258e+10, // 2
                +4.2919803642649101257324e+10, // 1
                +2.3531376880410758972168e+10  // 0
            };
            static constexpr
            const double q[]={
                +1.0000000000000000000000e+00, // 12
                +6.6000000000000000000000e+01, // 11
                +1.9250000000000000000000e+03, // 10
                +3.2670000000000000000000e+04, // 9
                +3.5742300000000000000000e+05, // 8
                +2.6375580000000000000000e+06, // 7
                +1.3339535000000000000000e+07, // 6
                +4.5995730000000000000000e+07, // 5
                +1.0525807600000000000000e+08, // 4
                +1.5091797600000000000000e+08, // 3
                +1.2054384000000000000000e+08, // 2
                +3.9916800000000000000000e+07, // 1
                +0.0000000000000000000000e+00  // 0
            };
            static constexpr
            const d_real<double> pd[]={
                {+2.5066282746310002416124e+00, +2.8552552938000000000781e-17}, // 12
                {+2.1082427775157935911921e+02, -1.3246695303210999999630e-14}, // 11
                {+8.0716720023658162972424e+03, -8.6604415029283999997678e-14}, // 10
                {+1.8605626539522348321043e+05, +1.1829865440498822000107e-11}, // 9
                {+2.8763706289353724569082e+06, -1.5682816961562743999869e-11}, // 8
                {+3.1426415585400193929672e+07, +4.5094199041738072599603e-10}, // 7
                {+2.4887455786205416917801e+08, -1.2666548646789895102630e-08}, // 6
                {+1.4397204073117215633392e+09, +1.1032398967435740842272e-07}, // 5
                {+6.0395425863520278930664e+09, +1.1199788539430729796603e-07}, // 4
                {+1.7921034426037208557129e+10, +1.1427908495044589822821e-06}, // 3
                {+3.5711959237355667114258e+10, +9.3518237295154714030723e-07}, // 2
                {+4.2919803642649101257324e+10, -2.4883663197029980402415e-06}, // 1
                {+2.3531376880410758972168e+10, +7.1640403892445161914413e-07}  // 0
            };
            static constexpr
            const d_real<double> qd[]={
                {+1.0000000000000000000000e+00, +0.0000000000000000000000e+00}, // 12
                {+6.6000000000000000000000e+01, +0.0000000000000000000000e+00}, // 11
                {+1.9250000000000000000000e+03, +0.0000000000000000000000e+00}, // 10
                {+3.2670000000000000000000e+04, +0.0000000000000000000000e+00}, // 9
                {+3.5742300000000000000000e+05, +0.0000000000000000000000e+00}, // 8
                {+2.6375580000000000000000e+06, +0.0000000000000000000000e+00}, // 7
                {+1.3339535000000000000000e+07, +0.0000000000000000000000e+00}, // 6
                {+4.5995730000000000000000e+07, +0.0000000000000000000000e+00}, // 5
                {+1.0525807600000000000000e+08, +0.0000000000000000000000e+00}, // 4
                {+1.5091797600000000000000e+08, +0.0000000000000000000000e+00}, // 3
                {+1.2054384000000000000000e+08, +0.0000000000000000000000e+00}, // 2
                {+3.9916800000000000000000e+07, +0.0000000000000000000000e+00}, // 1
                {+0.0000000000000000000000e+00, +0.0000000000000000000000e+00}  // 0
            };
        };
#if 1
        template <typename _V>
        using lanczos_rational_f64 =
            lanczos_rational<_V, lanczos_table_g_6_02468_N13, 11, 8>;
#endif

        struct lanczos_table_g_5_00000_N7 {
            static constexpr
            float g() {
                return +5.0000000000000000000000e+00f;
            }
            static constexpr
            float gm0_5() {
                return +4.5000000000000000000000e+00f;
            }
            static constexpr
            const float p[]={
                +2.5066282751072970214068e+00f, // 6
                +6.8827834691751434093021e+01f, // 5
                +7.8718789720684446820087e+02f, // 4
                +4.8000827958065592611092e+03f, // 3
                +1.6459041605996226280695e+04f, // 2
                +3.0090365763899564626627e+04f, // 1
                +2.2914620627169169893023e+04f  // 0
            };
            static constexpr
            const float q[]={
                +1.0000000000000000000000e+00f, // 6
                +1.5000000000000000000000e+01f, // 5
                +8.5000000000000000000000e+01f, // 4
                +2.2500000000000000000000e+02f, // 3
                +2.7400000000000000000000e+02f, // 2
                +1.2000000000000000000000e+02f, // 1
                +0.0000000000000000000000e+00f  // 0
            };
        };

        template <typename _V>
        using lanczos_rational_f32 =
            lanczos_rational<_V, lanczos_table_g_5_00000_N7, 3, 2>;
    }
}

template <typename _T, typename _C, std::size_t _N1, std::size_t _N2>
cftal::d_real<_T>
cftal::math::
lanczos_rational_at(_T x,
                    const d_real<_C>(&p)[_N1],
                    const _C (&q)[_N2])
{
    _T ph, pl;
    ph = p[0].h();
    pl = p[0].l();
    using d_ops=cftal::impl::d_real_ops<_T,
                                        d_real_traits<_T>::fma>;
#pragma GCC unroll 0
#pragma clang loop unroll(disable)
    for (std::size_t i=1; i< _N1; ++i) {
        d_ops::mul122(ph, pl, x, ph, pl);
        d_ops::add22cond(ph, pl,
                         p[i].h(), p[i].l(),
                         ph, pl);
    }
    _T qh, ql;
    horner_comp(qh, ql, x, q);
    d_real<_T> dp(ph, pl), dq(qh, ql), pq=d_ops::sloppy_div(dp, dq);
    return pq;
}

// local variables:
// mode: c++
// end:
#endif
