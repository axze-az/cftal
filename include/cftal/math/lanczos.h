//
// Copyright (C) 2010-2024 Axel Zeuner
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
#if !defined (__CFTAL_MATH_LANCZOS_H__)
#define __CFTAL_MATH_LANCZOS_H__ 1

#include <cftal/config.h>
#include <cftal/arg.h>
#include <cftal/math/horner.h>

namespace cftal {
    namespace math {

        // calculation of a lanczos rational
        template <typename _T, typename _C,
                  std::size_t _N1, std::size_t _N2>
        d_real<_T>
        lanczos_rational_at(const _T& x,
                            const d_real<_C>(&p)[_N1],
                            const _C (&q)[_N2]);

        // calculation of a lanczos rational
        template <typename _T, typename _C,
                  std::size_t _N1, std::size_t _N2>
        _T
        lanczos_rational_at(const _T& x,
                            const _C(&p)[_N1],
                            const _C(&q)[_N2]);

        // lanczos table for double, not used
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

        // lanczos table for float, not used
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

        // lanczos table for double
        struct lanczos_table_g_10_90990_N11 {
            static constexpr
            double g() {
                return +1.0909898534417152404785e+01;
            }
            static constexpr
            double g_l() {
                return -4.0478515624999999998911e-16;
            }
            static constexpr
            double gm0_5() {
                return +1.0409898534417152404785e+01;
            }
            static constexpr
            double gm0_5_l() {
                return -4.0478515624999999998911e-16;
            }
            static constexpr
            double exp_minus_gm0_5_h() {
                return +3.0132732023154958056997e-05;
            }
            static constexpr
            double exp_minus_gm0_5_l() {
                return -1.1971360000000000000281e-21;
            }
            static constexpr
            const double p[]={
                +2.5066282746310006857016e+00, // 10
                +2.6187065518312238054932e+02, // 9
                +1.2311319767111477631261e+04, // 8
                +3.4299443207995168631896e+05, // 7
                +6.2711532085765050724149e+06, // 6
                +7.8624812015718936920166e+07, // 5
                +6.8457039664262735843658e+08, // 4
                +4.0872263850670909881592e+09, // 3
                +1.6014654956325389862061e+10, // 2
                +3.7185344427643363952637e+10, // 1
                +3.8855076805286621093750e+10  // 0
            };
            static constexpr
            const double q[]={
                +1.0000000000000000000000e+00, // 10
                +4.5000000000000000000000e+01, // 9
                +8.7000000000000000000000e+02, // 8
                +9.4500000000000000000000e+03, // 7
                +6.3273000000000000000000e+04, // 6
                +2.6932500000000000000000e+05, // 5
                +7.2368000000000000000000e+05, // 4
                +1.1727000000000000000000e+06, // 3
                +1.0265760000000000000000e+06, // 2
                +3.6288000000000000000000e+05, // 1
                +0.0000000000000000000000e+00  // 0
            };
            static constexpr
            const d_real<double> pd[]={
                {+2.5066282746310006857016e+00, -1.6773475855199999999913e-16}, // 10
                {+2.6187065518312238054932e+02, -1.2812429541626000000275e-14}, // 9
                {+1.2311319767111477631261e+04, +6.2201294658791100001415e-13}, // 8
                {+3.4299443207995168631896e+05, -4.3477764530887790001205e-12}, // 7
                {+6.2711532085765050724149e+06, +5.7137835076712168000887e-11}, // 6
                {+7.8624812015718936920166e+07, -2.0888657751873848870233e-09}, // 5
                {+6.8457039664262735843658e+08, +3.3146818638551557162211e-08}, // 4
                {+4.0872263850670909881592e+09, +1.0948108501573320361921e-07}, // 3
                {+1.6014654956325389862061e+10, +5.7745485035403720986856e-07}, // 2
                {+3.7185344427643363952637e+10, -1.6442761256697506217216e-06}, // 1
                {+3.8855076805286621093750e+10, -2.7172921628903544035295e-06}  // 0
            };
            static constexpr
            const d_real<double> qd[]={
                {+1.0000000000000000000000e+00, +0.0000000000000000000000e+00}, // 10
                {+4.5000000000000000000000e+01, +0.0000000000000000000000e+00}, // 9
                {+8.7000000000000000000000e+02, +0.0000000000000000000000e+00}, // 8
                {+9.4500000000000000000000e+03, +0.0000000000000000000000e+00}, // 7
                {+6.3273000000000000000000e+04, +0.0000000000000000000000e+00}, // 6
                {+2.6932500000000000000000e+05, +0.0000000000000000000000e+00}, // 5
                {+7.2368000000000000000000e+05, +0.0000000000000000000000e+00}, // 4
                {+1.1727000000000000000000e+06, +0.0000000000000000000000e+00}, // 3
                {+1.0265760000000000000000e+06, +0.0000000000000000000000e+00}, // 2
                {+3.6288000000000000000000e+05, +0.0000000000000000000000e+00}, // 1
                {+0.0000000000000000000000e+00, +0.0000000000000000000000e+00}  // 0
            };
            static constexpr
            const d_real<double> ped[]={
                {+4.5812205752064319886230e-05, +1.0564479999999999999847e-21}, // 10
                {+4.7860596072798805220017e-03, +3.0699525000000000001306e-20}, // 9
                {+2.2500692262932167619915e-01, +8.1487113929999999999415e-18}, // 8
                {+6.2687122990234156461042e+00, +2.1528517438599999999516e-16}, // 7
                {+1.1461426650360344581259e+02, +3.5212217414830000000113e-15}, // 6
                {+1.4369805454347792874614e+03, +2.7663712860809999999870e-14}, // 5
                {+1.2511500081670890722307e+04, +5.6288996846778399999424e-13}, // 4
                {+7.4699889889147554640658e+04, -1.3919483467340759999526e-12}, // 3
                {+2.9269065354953682981431e+05, +2.8602525060603640000742e-12}, // 2
                {+6.7961518950445647351444e+05, +1.9333034673525960000213e-12}, // 1
                {+7.1013192946532566566020e+05, -1.3530750527567787000055e-11}  // 0
            };
        };

        // lanczos table for float
        struct lanczos_table_g_4_35169_N5 {
            static constexpr
            double g() {
                return +4.3516943305730819702148e+00;
            }
            static constexpr
            double g_l() {
                return +2.9785156250000000000342e-17;
            }
            static constexpr
            double gm0_5() {
                return +3.8516943305730819702148e+00;
            }
            static constexpr
            double gm0_5_l() {
                return +2.9785156250000000000342e-17;
            }
            static constexpr
            double exp_minus_gm0_5_h() {
                return +2.1243712057565491968525e-02;
            }
            static constexpr
            double exp_minus_gm0_5_l() {
                return +1.1678894220000000000006e-18;
            }
            static constexpr
            const double p[]={
                +2.5066282851359193983853e+00, // 4
                +3.8669641557894443906207e+01, // 3
                +2.2368963390537291502369e+02, // 2
                +5.7504301631454700327595e+02, // 1
                +5.5430239062940745498054e+02  // 0
            };
            static constexpr
            const double q[]={
                +1.0000000000000000000000e+00, // 4
                +6.0000000000000000000000e+00, // 3
                +1.1000000000000000000000e+01, // 2
                +6.0000000000000000000000e+00, // 1
                +0.0000000000000000000000e+00  // 0
            };
            static constexpr
            const d_real<double> pd[]={
                {+2.5066282851359193983853e+00, -1.4386361349600000000127e-16}, // 4
                {+3.8669641557894443906207e+01, -3.1862923974699999999993e-15}, // 3
                {+2.2368963390537291502369e+02, +6.9682633233740000001718e-15}, // 2
                {+5.7504301631454700327595e+02, +5.4938602473891000001085e-14}, // 1
                {+5.5430239062940745498054e+02, -2.0356668284519000000637e-14}  // 0
            };
            static constexpr
            const d_real<double> qd[]={
                {+1.0000000000000000000000e+00, +0.0000000000000000000000e+00}, // 4
                {+6.0000000000000000000000e+00, +0.0000000000000000000000e+00}, // 3
                {+1.1000000000000000000000e+01, +0.0000000000000000000000e+00}, // 2
                {+6.0000000000000000000000e+00, +0.0000000000000000000000e+00}, // 1
                {+0.0000000000000000000000e+00, +0.0000000000000000000000e+00}  // 0
            };
            static constexpr
            const d_real<double> ped[]={
                {+3.2297811929219565063587e-02, +2.5523372809999999999165e-18}, // 4
                {+4.9825688867126349812509e-01, -1.7292132799000000000530e-17}, // 3
                {+2.8822325867913680674803e+00, -3.1763008602999999999492e-17}, // 2
                {+7.4094078097947013716862e+00, +2.9115928386500000000305e-16}, // 1
                {+7.1421656216947386752736e+00, +2.7467653356400000000558e-16}  // 0
            };

            static constexpr
            float gm0_5f() {
                return 3.8516943455e+00f;
            }
            static constexpr
            float gm0_5f_l() {
                return -1.4901161194e-08f;
            }
            static constexpr
            const d_real<float> pdf[]={
                { 2.5066282749e+00f, 1.0218316859e-08f },
                { 3.8669643402e+01f, -1.8442051442e-06f },
                { 2.2368963623e+02f, -2.3250959202e-06f },
                { 5.7504302979e+02f, -1.3470609701e-05f },
                { 5.5430236816e+02f, 2.2465344955e-05f }
            };
            static constexpr
            const d_real<float> pedf[]={
                { 3.2297812402e-02f, -4.7302883832e-10f },
                { 4.9825689197e-01f, -3.2946025907e-09f },
                { 2.8822326660e+00f, -7.9224257377e-08f },
                { 7.4094076157e+00f, 1.9413307939e-07f },
                { 7.1421656609e+00f, -3.9163417398e-08f }
            };
            static constexpr
            const float qf[]={
                1.0000000000e+00f,
                6.0000000000e+00f,
                1.1000000000e+01f,
                6.0000000000e+00f,
                0.0000000000e+00f
            };
        };
    }
}

template <typename _T, typename _C, std::size_t _N1, std::size_t _N2>
inline
__attribute__((__always_inline__))
cftal::d_real<_T>
cftal::math::
lanczos_rational_at(const _T& x,
                    const d_real<_C>(&p)[_N1],
                    const _C (&q)[_N2])
{
    using d_ops=d_real_ops<_T, d_real_traits<_T>::fma>;
    const d_real<_C>* pp=p;
    _T ph = pp[0][0];
    _T pl = pp[0][1];
#pragma clang unroll(1)
#pragma GCC unroll 1
    for (std::size_t i=1; i< _N1; ++i) {
#if 1
#if 1
        horner_comp_dpc_si(ph, pl, x, ph, pl, pp[i][0], pp[i][1]);
#else
        // compensated horner step with higher precision coefficients
        _T p_i, o_i;
        d_ops::mul12(ph, p_i, ph, x);
        d_ops::add12cond(ph, o_i, ph, pp[i][0]);
        pl = pl*x + (p_i + o_i + pp[i][1]);
#endif
#else
        d_ops::mul122(ph, pl, x, ph, pl);
        d_ops::add22cond(ph, pl,
                        pp[i][0], pp[i][1],
                        ph, pl);
#endif
    }
    _T qh, ql;
    if (__likely(q[_N2-1] == _C(0))) {
        const _C* pq=q;
        horner_comp_s0(qh, ql, x, pq[0], pq[1]);
#pragma clang unroll(1)
#pragma GCC unroll 1
        for (std::size_t i=2; i< _N2-1; ++i) {
            horner_comp_si(qh, ql, x, qh, ql, pq[i]);
        }
        // last step is without addition
        _T p_i;
        d_ops::mul12(qh, p_i, qh, x);
        ql = ql * x + p_i;
    } else {
        horner_comp(qh, ql, x, q);
    }
    _T pqh, pql;
#if 0
    _T inv_qh, inv_ql;
    d_ops::rcp2(inv_qh, inv_ql, qh, ql);
    d_ops::mul22(pqh, pql, ph, pl, inv_qh, inv_ql);
#else
    d_ops::div22(pqh, pql, ph, pl, qh, ql);
#endif
    return d_real<_T>(pqh, pql);
}

// calculation of a lanczos rational
template <typename _T, typename _C,
          std::size_t _N1, std::size_t _N2>
inline
__attribute__((__always_inline__))
_T
cftal::math::
lanczos_rational_at(const _T& x,
                    const _C(&p)[_N1],
                    const _C(&q)[_N2])
{
    _T rp=horner(x, p);
    _T rq=horner(x, q);
    _T r=rp/rq;
    return r;
}


// local variables:
// mode: c++
// end:
#endif
