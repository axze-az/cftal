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
#include <cftal/config.h>
#include <cftal/math/factorial.h>
#include <limits>

const float
cftal::math::rcp_factorial<float>::
_recip_factorial_f32[40]={
    // 0
    // +1.0000000000e+00f
    +0x8p-3f,
    // 1
    // +1.0000000000e+00f
    +0x8p-3f,
    // 2
    // +5.0000000000e-01f
    +0x8p-4f,
    // 3
    // +1.6666667163e-01f
    +0xa.aaaabp-6f,
    // 4
    // +4.1666667908e-02f
    +0xa.aaaabp-8f,
    // 5
    // +8.3333337680e-03f
    +0x8.88889p-10f,
    // 6
    // +1.3888889225e-03f
    +0xb.60b61p-13f,
    // 7
    // +1.9841270114e-04f
    +0xd.00d01p-16f,
    // 8
    // +2.4801587642e-05f
    +0xd.00d01p-19f,
    // 9
    // +2.7557318845e-06f
    +0xb.8ef1dp-22f,
    // 10
    // +2.7557319981e-07f
    +0x9.3f27ep-25f,
    // 11
    // +2.5052107944e-08f
    +0xd.7322bp-29f,
    // 12
    // +2.0876755880e-09f
    +0x8.f76c7p-32f,
    // 13
    // +1.6059044372e-10f
    +0xb.09231p-36f,
    // 14
    // +1.1470745361e-11f
    +0xc.9cba5p-40f,
    // 15
    // +7.6471636098e-13f
    +0xd.73f9fp-44f,
    // 16
    // +4.7794772561e-14f
    +0xd.73f9fp-48f,
    // 17
    // +2.8114573590e-15f
    +0xc.a963cp-52f,
    // 18
    // +1.5619206815e-16f
    +0xb.413c3p-56f,
    // 19
    // +8.2206350785e-18f
    +0x9.7a4dap-60f,
    // 20
    // +4.1103175909e-19f
    +0xf.2a15dp-65f,
    // 21
    // +1.9572941525e-20f
    +0xb.8dc78p-69f,
    // 22
    // +8.8967909596e-22f
    +0x8.671cbp-73f,
    // 23
    // +3.8681702980e-23f
    +0xb.b0da1p-78f,
    // 24
    // +1.6117375913e-24f
    +0xf.96781p-83f,
    // 25
    // +6.4469503405e-26f
    +0x9.f9e67p-87f,
    // 26
    // +2.4795962848e-27f
    +0xc.4743p-92f,
    // 27
    // +9.1836898100e-29f
    +0xe.8d58ep-97f,
    // 28
    // +3.2798891641e-30f
    +0x8.50c51p-101f,
    // 29
    // +1.1309962473e-31f
    +0x9.2cfccp-106f,
    // 30
    // +3.7699878093e-33f
    +0x9.c9963p-111f,
    // 31
    // +1.2161250146e-34f
    +0xa.1a697p-116f,
    // 32
    // +3.8003906706e-36f
    +0xa.1a697p-121f,
    // 33
    // +1.1516336011e-37f
    +0x9.cc093p-126f,
    // 34
    // +3.3871569908e-39f
    +0x9.3881p-131f,
    // 35
    // +9.6776474543e-41f
    +0x8.6e3p-136f,
    // 36
    // +2.6876904546e-42f
    +0xe.fcp-142f,
    // 37
    // +7.2867520145e-44f
    +0xdp-147f,
    // 38
    // +1.4012984643e-45f
    +0x8p-152f,
    // 39
    // +0.0000000000e+00f
    +0x0p+0f
};

const float
cftal::math::factorial<float>::
_factorial_f32[36]={
    // 0
    // +1.0000000000e+00f
    +0x8p-3f,
    // 1
    // +1.0000000000e+00f
    +0x8p-3f,
    // 2
    // +2.0000000000e+00f
    +0x8p-2f,
    // 3
    // +6.0000000000e+00f
    +0xcp-1f,
    // 4
    // +2.4000000000e+01f
    +0xcp+1f,
    // 5
    // +1.2000000000e+02f
    +0xfp+3f,
    // 6
    // +7.2000000000e+02f
    +0xb.4p+6f,
    // 7
    // +5.0400000000e+03f
    +0x9.d8p+9f,
    // 8
    // +4.0320000000e+04f
    +0x9.d8p+12f,
    // 9
    // +3.6288000000e+05f
    +0xb.13p+15f,
    // 10
    // +3.6288000000e+06f
    +0xd.d7cp+18f,
    // 11
    // +3.9916800000e+07f
    +0x9.8454p+22f,
    // 12
    // +4.7900160000e+08f
    +0xe.467ep+25f,
    // 13
    // +6.2270208000e+09f
    +0xb.99466p+29f,
    // 14
    // +8.7178289152e+10f
    +0xa.261d9p+33f,
    // 15
    // +1.3076744110e+12f
    +0x9.83bbcp+37f,
    // 16
    // +2.0922790576e+13f
    +0x9.83bbcp+41f,
    // 17
    // +3.5568741463e+14f
    +0xa.1bf77p+45f,
    // 18
    // +6.4023735304e+15f
    +0xb.5f766p+49f,
    // 19
    // +1.2164510459e+17f
    +0xd.815cap+53f,
    // 20
    // +2.4329020232e+18f
    +0x8.70d9ep+58f,
    // 21
    // +5.1090940837e+19f
    +0xb.141dfp+62f,
    // 22
    // +1.1240007248e+21f
    +0xf.3ba93p+66f,
    // 23
    // +2.5852017445e+22f
    +0xa.f2e1ap+71f,
    // 24
    // +6.2044838264e+23f
    +0x8.36293p+76f,
    // 25
    // +1.5511209926e+25f
    +0xc.d4a06p+80f,
    // 26
    // +4.0329146270e+26f
    +0xa.6cc25p+85f,
    // 27
    // +1.0888869235e+28f
    +0x8.cbc3fp+90f,
    // 28
    // +3.0488835273e+29f
    +0xf.6496fp+94f,
    // 29
    // +8.8417618704e+30f
    +0xd.f328cp+99f,
    // 30
    // +2.6525285128e+32f
    +0xd.13f63p+104f,
    // 31
    // +8.2228384476e+33f
    +0xc.ab568p+109f,
    // 32
    // +2.6313083032e+35f
    +0xc.ab568p+114f,
    // 33
    // +8.6833178760e+36f
    +0xd.10b14p+119f,
    // 34
    // +2.9523280271e+38f
    +0xd.e1bc5p+124f,
    // 35
    // +inff
    std::numeric_limits<float>::infinity()
};
