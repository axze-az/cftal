//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/math/func_data.h"

const
cftal::math::exp_data<double>::table_t
cftal::math::exp_data<double>::_tbl={
    // static const double exp_fxi_h_tbl[32]=
    {
        // 0
        // +1.0000000000000000000000e+00
        +0x8p-3,
        // 1
        // +1.0218971486541166271422e+00
        +0x8.2cd8698ac2bap-3,
        // 2
        // +1.0442737824274137548031e+00
        +0x8.5aac367cc4878p-3,
        // 3
        // +1.0671404006768236971681e+00
        +0x8.8980e8092da88p-3,
        // 4
        // +1.0905077326652576896748e+00
        +0x8.b95c1e3ea8bd8p-3,
        // 5
        // +1.1143867425958924322060e+00
        +0x8.ea4398b45cd5p-3,
        // 6
        // +1.1387886347566915645757e+00
        +0x9.1c3d373ab11cp-3,
        // 7
        // +1.1637248587775774755215e+00
        +0x9.4f4efa8fef708p-3,
        // 8
        // +1.1892071150027210268973e+00
        +0x9.837f0518db8a8p-3,
        // 9
        // +1.2152473599804689552428e+00
        +0x9.b8d39b9d54e58p-3,
        // 10
        // +1.2418578120734840020134e+00
        +0x9.ef5326091a11p-3,
        // 11
        // +1.2690509571917332198865e+00
        +0xa.27043030c4968p-3,
        // 12
        // +1.2968395546510096405513e+00
        +0xa.5fed6a9b15138p-3,
        // 13
        // +1.3252366431597413232168e+00
        +0xa.9a15ab4ea7c1p-3,
        // 14
        // +1.3542555469368926512885e+00
        +0xa.d583eea42a148p-3,
        // 15
        // +1.3839098819638320225778e+00
        +0xb.123f581d2ac28p-3,
        // 16
        // +1.4142135623730951454746e+00
        +0xb.504f333f9de68p-3,
        // 17
        // +1.4451808069770466502746e+00
        +0xb.8fbaf4762fbap-3,
        // 18
        // +1.4768261459394993462269e+00
        +0xb.d08a39f580c38p-3,
        // 19
        // +1.5091644275934228414116e+00
        +0xc.12c4cca667098p-3,
        // 20
        // +1.5422108254079407441139e+00
        +0xc.5672a115506d8p-3,
        // 21
        // +1.5759808451078864965922e+00
        +0xc.9b9bd866e2f28p-3,
        // 22
        // +1.6104903319492542834723e+00
        +0xc.e248c151f848p-3,
        // 23
        // +1.6457554781539649457756e+00
        +0xd.2a81d91f12ae8p-3,
        // 24
        // +1.6817928305074290040722e+00
        +0xd.744fccad69d68p-3,
        // 25
        // +1.7186192981224779341431e+00
        +0xd.bfbb797daf238p-3,
        // 26
        // +1.7562521603732994535108e+00
        +0xe.0ccdeec2a94ep-3,
        // 27
        // +1.7947090750031071682002e+00
        +0xe.5b906e77c8348p-3,
        // 28
        // +1.8340080864093424306560e+00
        +0xe.ac0c6e7dd2438p-3,
        // 29
        // +1.8741676341102999625576e+00
        +0xe.fe4b99bdcdaf8p-3,
        // 30
        // +1.9152065613971474000721e+00
        +0xf.5257d152486dp-3,
        // 31
        // +1.9571441241754001794106e+00
        +0xf.a83b2db722ap-3
    },
    // static const double exp_fxi_l_tbl[32]=
    {
        // 0
        // +0.0000000000000000000000e+00
        +0x0p+0,
        // 1
        // +5.1092250289734438935898e-17
        +0xe.b9f1523ada328p-58,
        // 2
        // +8.5518897055379648921708e-17
        +0xc.5317256e30858p-57,
        // 3
        // -7.8998539668415821222633e-17
        -0xb.62881ca24d9dp-57,
        // 4
        // -3.0467820798124711469655e-17
        -0x8.c820dcebc53bp-58,
        // 5
        // +1.0410278456845570954946e-16
        +0xf.00b70051321ep-57,
        // 6
        // +8.9128126760254077778202e-17
        +0xc.d83f5b6382b98p-57,
        // 7
        // +3.8292048369240934987216e-17
        +0xb.097457d6892a8p-58,
        // 8
        // +3.9820152314656461109803e-17
        +0xb.7a356918c172p-58,
        // 9
        // -7.7126306926814881309126e-17
        -0xb.1d755fa17571p-57,
        // 10
        // +4.6580275918369367912262e-17
        +0xd.6d0488f84f5ep-58,
        // 11
        // +2.6679321313421860952300e-18
        +0xc.4dbd0277c068p-62,
        // 12
        // +2.5382502794888314959291e-17
        +0xe.a1cbd7f62171p-59,
        // 13
        // -2.8587312100388613732703e-17
        -0x8.3d5f0ed89e568p-58,
        // 14
        // +7.7009483798029894616234e-17
        +0xb.192602a323d68p-57,
        // 15
        // -6.7705116587947862871574e-17
        -0x9.c1e0bf205a4b8p-57,
        // 16
        // -9.6672933134529134510547e-17
        -0xd.ee9a09d9322bp-57,
        // 17
        // -3.0237581349939873193998e-17
        -0x8.b723c3443d4c8p-58,
        // 18
        // -3.4839945568927957957915e-17
        -0xa.0abbf7024c978p-58,
        // 19
        // -1.0164553277542950391050e-16
        -0xe.a60eea0a996cp-57,
        // 20
        // +7.9498348096976208561610e-17
        +0xb.74f8ab4325938p-57,
        // 21
        // -1.0136916471278303980796e-17
        -0xb.afe3c0dabf5ep-60,
        // 22
        // +2.4707192569797887852245e-17
        +0xe.3e235838f95fp-59,
        // 23
        // -1.0125679913674772603788e-16
        -0xe.97b76dc6a0f08p-57,
        // 24
        // +8.1990100205814965201272e-17
        +0xb.d0e69a2ee6408p-57,
        // 25
        // -1.8513804182631109882109e-17
        -0xa.ac27bf2a561d8p-59,
        // 26
        // +2.9601406954488733070309e-17
        +0x8.8832c4a8246e8p-58,
        // 27
        // +1.8227458427912086769763e-17
        +0xa.81e5e8f4a4ed8p-59,
        // 28
        // +3.2831072242456272035141e-17
        +0x9.76816bad9b838p-58,
        // 29
        // -6.1227634130041425616366e-17
        -0x8.d2e6a78c25aep-57,
        // 30
        // -1.0619946056195962637628e-16
        -0xf.4e118bce14498p-57,
        // 31
        // +8.9607677910366677676016e-17
        +0xc.e9f096ec50c58p-57
    }
};

template struct cftal::math::exp_data<double>;
