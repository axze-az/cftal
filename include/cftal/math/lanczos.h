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

        template <typename _T, typename _C,
                  std::size_t _N1, std::size_t _N2>
        d_real<_T>
        lanczos_rational_at(const _T& x,
                            const d_real<_C>(&p)[_N1],
                            const _C (&q)[_N2]);

        // lanczos table for double
        struct lanczos_table_g_12_06815_N12 {
            static constexpr
            double g() {
                return +1.2068153090775012969971e+01;
            }
            static constexpr
            double g_l() {
                return +3.0029296875000000001258e-17;
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
            double exp_minus_gm0_5_h() {
                return +9.4626972802846135823362e-06;
            }
            static constexpr
            double exp_minus_gm0_5_l() {
                return -1.4263200000000000000343e-22;
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
            const d_real<double> ped[]={
                {+1.4386582485809036241540e-05, -6.0307700000000000001256e-22}, // 11
                {+1.8382958272201124945433e-03, +5.3090738000000000000421e-20}, // 10
                {+1.0677276938903343395104e-01, -6.0328891719999999999456e-18}, // 9
                {+3.7210629883471053602761e+00, -1.7814096063299999999836e-16}, // 8
                {+8.6455488825339742220422e+01, +4.9928518121300000001299e-16}, // 7
                {+1.4061336204384274424228e+03, +1.0674532976225299999797e-13}, // 6
                {+1.6335903253656080778455e+04, -7.7523875582596300002011e-13}, // 5
                {+1.3556338272678834619001e+05, +8.4921659110044759997122e-12}, // 4
                {+7.8749997817200166173279e+05, +6.8360639542013880000841e-12}, // 3
                {+3.0498498965619821101427e+06, +2.0987347456358037899585e-10}, // 2
                {+7.0871040267461650073528e+06, +1.9962809003946929399660e-10}, // 1
                {+7.4859652297629984095693e+06, -2.6659785613444481098982e-10}  // 0
            };
            static constexpr
            float gm0_5f() {
                return 1.1568153381e+01f;
            }
            static constexpr
            float gm0_5f_l() {
                return -2.9057264328e-07f;
            }
            static constexpr
            const d_real<float> pdf[]={
                { 2.5066282749e+00f, -2.8660185336e-10f },
                { 3.2029318237e+02f, 6.8077343940e-07f },
                { 1.8603419922e+04f, 5.2041606978e-04f },
                { 6.4833475000e+05f, 2.3562399670e-02f },
                { 1.5063464000e+07f, 3.7733951211e-01f },
                { 2.4499593600e+08f, 3.4023525715e+00f },
                { 2.8462658560e+09f, -1.0611519623e+02f },
                { 2.3619717120e+10f, -3.4112644196e+01f },
                { 1.3720907776e+11f, -2.3902764893e+02f },
                { 5.3138679398e+11f, 2.8208415527e+03f },
                { 1.2348127969e+12f, -5.6917207031e+04f },
                { 1.3043078267e+12f, -1.9257348633e+03f }
            };
            static constexpr
            const d_real<float> pedf[]={
                { 1.4386582734e-05f, -2.4819602211e-13f },
                { 1.8382958369e-03f, -9.7128451115e-12f },
                { 1.0677277297e-01f, -3.5787819375e-09f },
                { 3.7210628986e+00f, 8.9711242879e-08f },
                { 8.6455490112e+01f, -1.2869649026e-06f },
                { 1.4061336670e+03f, -4.6553759603e-05f },
                { 1.6335903320e+04f, -6.6656415584e-05f },
                { 1.3556337500e+05f, 7.7267885208e-03f },
                { 7.8750000000e+05f, -2.1827997640e-02f },
                { 3.0498500000e+06f, -1.0343801975e-01f },
                { 7.0871040000e+06f, 2.6746165007e-02f },
                { 7.4859650000e+06f, 2.2976300120e-01f }
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
                return +5.5917193591594696044922e+00;
            }
            static constexpr
            double g_l() {
                return -4.4921875000000000001429e-18;
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
            double exp_minus_gm0_5_h() {
                return +6.1474411362139429193530e-03;
            }
            static constexpr
            double exp_minus_gm0_5_l() {
                return -6.1398243999999999997915e-20;
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
            const d_real<double> ped[]={
                {+9.3462430798367194390019e-03, +6.4335292000000000001917e-19}, // 5
                {+2.3918901585658380870569e-01, +8.7915833409999999997686e-18}, // 4
                {+2.4486386624162488345746e+00, -7.8894501936000000001199e-17}, // 3
                {+1.2534212615190213568894e+01, -6.1433318384499999998008e-16}, // 2
                {+3.2081728235874031440744e+01, -5.9259608128899999999148e-16}, // 1
                {+3.2847039296463229618439e+01, -2.5378141120269999999321e-15}  // 0
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
            const d_real<float> pedf[]={
                { 9.3462429941e-03f, 8.5766664604e-11f },
                { 2.3918901384e-01f, 2.0178156923e-09f },
                { 2.4486386776e+00f, -1.5180797064e-08f },
                { 1.2534213066e+01f, -4.5091087486e-07f },
                { 3.2081729889e+01f, -1.6530419771e-06f },
                { 3.2847038269e+01f, 1.0274202396e-06f }
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
    const d_real<_C>* pp=p;
    ph = pp[0][0];
    pl = pp[0][1];
    using d_ops=cftal::impl::d_real_ops<_T, d_real_traits<_T>::fma>;
#pragma clang loop unroll(disable)
#pragma GCC unroll 0
    for (std::size_t i=1; i< _N1; ++i) {
        d_ops::mul122(ph, pl, x, ph, pl);
        d_ops::add22cond(ph, pl,
                         pp[i][0], pp[i][1],
                         ph, pl);
    }
    _T qh, ql;
    horner_comp(qh, ql, x, q);
    _T pqh, pql;
    d_ops::div22(pqh, pql, ph, pl, qh, ql);
    return d_real<_T>(pqh, pql);
}

// local variables:
// mode: c++
// end:
#endif
