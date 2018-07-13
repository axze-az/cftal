//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_MATH_LANCZOS_H__)
#define __CFTAL_MATH_LANCZOS_H__ 1

#include <cftal/config.h>
#include <cftal/arg.h>
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
        lanczos_rational_at(const _T& x,
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

        // lanczos table for double
        struct lanczos_table_g_12_06815_N12 {
            static constexpr
            double g() {
                return +1.2068153090775013000328e+01;
            }
            static constexpr
            double gm0_5() {
                return +1.1568153090775012969971e+01;
            }
            static constexpr
            double gm0_5_l() {
                return +3.0029296875000000001258e-17;
            }
            static constexpr
            const double p[]={
                +2.5066282746310006857016e+00, // 11
                +3.2029318305382031439876e+02, // 10
                +1.8603420442291077051777e+04, // 9
                +6.4833477356239920482039e+05, // 8
                +1.5063464377339523285627e+07, // 7
                +2.4499593940235260128975e+08, // 6
                +2.8462657498848071098328e+09, // 5
                +2.3619717085887355804443e+10, // 4
                +1.3720907752097235107422e+11, // 3
                +5.3138679680484149169922e+11, // 2
                +1.2348127400107939453125e+12, // 1
                +1.3043078247622651367188e+12  // 0
            };
            static constexpr
            const double q[]={
                +1.0000000000000000000000e+00, // 11
                +5.5000000000000000000000e+01, // 10
                +1.3200000000000000000000e+03, // 9
                +1.8150000000000000000000e+04, // 8
                +1.5777300000000000000000e+05, // 7
                +9.0205500000000000000000e+05, // 6
                +3.4169300000000000000000e+06, // 5
                +8.4095000000000000000000e+06, // 4
                +1.2753576000000000000000e+07, // 3
                +1.0628640000000000000000e+07, // 2
                +3.6288000000000000000000e+06, // 1
                +0.0000000000000000000000e+00  // 0
            };
            static constexpr
            const d_real<double> pd[]={
                {+2.5066282746310006857016e+00, -1.8355995526300000000569e-16}, // 11
                {+3.2029318305382031439876e+02, -1.5562510298410999999708e-14}, // 10
                {+1.8603420442291077051777e+04, -1.7703785498287650000126e-12}, // 9
                {+6.4833477356239920482039e+05, -2.7968716077836410000456e-11}, // 8
                {+1.5063464377339523285627e+07, +5.2128776597100833399746e-10}, // 7
                {+2.4499593940235260128975e+08, +3.0344795767343300669474e-09}, // 6
                {+2.8462657498848071098328e+09, +1.3524610308245197200453e-10}, // 5
                {+2.3619717085887355804443e+10, +2.1136549031633034807863e-07}, // 4
                {+1.3720907752097235107422e+11, +1.3557212616507916535944e-06}, // 3
                {+5.3138679680484149169922e+11, -2.3012915684149977418481e-05}, // 2
                {+1.2348127400107939453125e+12, +1.2028057546573336813837e-04}, // 1
                {+1.3043078247622651367188e+12, +6.0095846807122496949227e-05}  // 0
            };
            static constexpr
            const d_real<double> qd[]={
                {+1.0000000000000000000000e+00, +0.0000000000000000000000e+00}, // 11
                {+5.5000000000000000000000e+01, +0.0000000000000000000000e+00}, // 10
                {+1.3200000000000000000000e+03, +0.0000000000000000000000e+00}, // 9
                {+1.8150000000000000000000e+04, +0.0000000000000000000000e+00}, // 8
                {+1.5777300000000000000000e+05, +0.0000000000000000000000e+00}, // 7
                {+9.0205500000000000000000e+05, +0.0000000000000000000000e+00}, // 6
                {+3.4169300000000000000000e+06, +0.0000000000000000000000e+00}, // 5
                {+8.4095000000000000000000e+06, +0.0000000000000000000000e+00}, // 4
                {+1.2753576000000000000000e+07, +0.0000000000000000000000e+00}, // 3
                {+1.0628640000000000000000e+07, +0.0000000000000000000000e+00}, // 2
                {+3.6288000000000000000000e+06, +0.0000000000000000000000e+00}, // 1
                {+0.0000000000000000000000e+00, +0.0000000000000000000000e+00}  // 0
            };
            static constexpr
            float gm0_5f() {
                return 1.1568153381e+01f;
            }
            static constexpr
            float gm0_5f_l() {
                return 2.9057264328e-07f;
            }
            static constexpr
            const d_real<float> pdf[]={
                { 2.5066282749e+00f, 2.8660185336e-10f },
                { 3.2029318237e+02f, -6.8077343940e-07f },
                { 1.8603419922e+04f, -5.2041606978e-04f },
                { 6.4833475000e+05f, -2.3562399670e-02f },
                { 1.5063464000e+07f, -3.7733951211e-01f },
                { 2.4499593600e+08f, -3.4023525715e+00f },
                { 2.8462658560e+09f, 1.0611519623e+02f },
                { 2.3619717120e+10f, 3.4112644196e+01f },
                { 1.3720907776e+11f, 2.3902764893e+02f },
                { 5.3138679398e+11f, -2.8208415527e+03f },
                { 1.2348127969e+12f, 5.6917207031e+04f },
                { 1.3043078267e+12f, 1.9257348633e+03f }
            };
            static constexpr
            const float qf[]={
                1.0000000000e+00f,
                5.5000000000e+01f,
                1.3200000000e+03f,
                1.8150000000e+04f,
                1.5777300000e+05f,
                9.0205500000e+05f,
                3.4169300000e+06f,
                8.4095000000e+06f,
                1.2753576000e+07f,
                1.0628640000e+07f,
                3.6288000000e+06f,
                0.0000000000e+00f
            };
        };

        // lanczos table for float
        struct lanczos_table_g_5_59172_N6 {
            static constexpr
            double g() {
                return +5.5917193591594696001554e+00;
            }
            static constexpr
            double gm0_5() {
                return +5.0917193591594696044922e+00;
            }
            static constexpr
            double gm0_5_l() {
                return -4.4921875000000000001429e-18;
            }
            static constexpr
            const double p[]={
                +2.5066282743377215069813e+00, // 5
                +6.4149620862161540912894e+01, // 4
                +6.5671595018651021291589e+02, // 3
                +3.3616300656226057981257e+03, // 2
                +8.6042023943449112266535e+03, // 1
                +8.8094560269274898018921e+03  // 0
            };
            static constexpr
            const double q[]={
                +1.0000000000000000000000e+00, // 5
                +1.0000000000000000000000e+01, // 4
                +3.5000000000000000000000e+01, // 3
                +5.0000000000000000000000e+01, // 2
                +2.4000000000000000000000e+01, // 1
                +0.0000000000000000000000e+00  // 0
            };
            static constexpr
            const d_real<double> pd[]={
                {+2.5066282743377215069813e+00, -1.9375103537599999999837e-16}, // 5
                {+6.4149620862161540912894e+01, -3.8788904139549999998430e-15}, // 4
                {+6.5671595018651021291589e+02, +5.2657628064317999998744e-14}, // 3
                {+3.3616300656226057981257e+03, +1.8966565356428200000165e-13}, // 2
                {+8.6042023943449112266535e+03, +6.4088413798479900002335e-13}, // 1
                {+8.8094560269274898018921e+03, +5.1397786672407999999271e-14}  // 0
            };
            static constexpr
            const d_real<double> qd[]={
                {+1.0000000000000000000000e+00, +0.0000000000000000000000e+00}, // 5
                {+1.0000000000000000000000e+01, +0.0000000000000000000000e+00}, // 4
                {+3.5000000000000000000000e+01, +0.0000000000000000000000e+00}, // 3
                {+5.0000000000000000000000e+01, +0.0000000000000000000000e+00}, // 2
                {+2.4000000000000000000000e+01, +0.0000000000000000000000e+00}, // 1
                {+0.0000000000000000000000e+00, +0.0000000000000000000000e+00}  // 0
            };

            static constexpr
            float gm0_5f() {
                return 5.0917191505e+00f;
            }
            static constexpr
            float gm0_5f_l() {
                return 2.0861625671e-07f;
            }
            static constexpr
            const d_real<float> pdf[]={
                { 2.5066282749e+00f, -5.7988103208e-10f },
                { 6.4149620056e+01f, 8.0600921137e-07f },
                { 6.5671594238e+02f, 7.8036973719e-06f },
                { 3.3616301270e+03f, -6.1330516473e-05f },
                { 8.6042021484e+03f, 2.4590740213e-04f },
                { 8.8094560547e+03f, -2.7760010198e-05f }
            };
            static constexpr
            const float qf[]={
                1.0000000000e+00f,
                1.0000000000e+01f,
                3.5000000000e+01f,
                5.0000000000e+01f,
                2.4000000000e+01f,
                0.0000000000e+00f
            };

        };


    }
}

template <typename _T, typename _C, std::size_t _N1, std::size_t _N2>
inline
__attribute__((optimize("no-unroll-loops")))
__attribute__((__always_inline__))
cftal::d_real<_T>
cftal::math::
lanczos_rational_at(const _T& x,
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
