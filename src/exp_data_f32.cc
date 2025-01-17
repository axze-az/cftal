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

#include "cftal/math/func_data.h"

template<>
const
cftal::math::exp_data<float>::table_t
cftal::math::exp_data<float>::_tbl={
    // static const float _2_pow_i_n_f[32]=
    {
        // 0
        // +0.0000000000e+00f
        +0x0p+0f,
        // 1
        // -4.7084576238e-08f
        -0xc.a3a0ap-28f,
        // 2
        // +4.6285471456e-08f
        +0xc.6cb6ap-28f,
        // 3
        // -5.5604225224e-08f
        -0xe.ed17ep-28f,
        // 4
        // -1.1992157489e-08f
        -0xc.e0611p-30f,
        // 5
        // -4.8776062300e-08f
        -0xd.17dd9p-28f,
        // 6
        // +4.7297824324e-08f
        +0xc.b2482p-28f,
        // 7
        // -3.4814426897e-08f
        -0x9.586dep-28f,
        // 8
        // +3.1934181521e-08f
        +0x8.92801p-28f,
        // 9
        // -2.6886665339e-08f
        -0xe.6f467p-29f,
        // 10
        // +3.6210572318e-08f
        +0x9.b85f2p-28f,
        // 11
        // +1.1184210225e-09f
        +0x9.9b6f1p-33f,
        // 12
        // -3.0990719324e-08f
        -0x8.51aa8p-28f,
        // 13
        // -2.6383009555e-08f
        -0xe.2a0dap-29f,
        // 14
        // -7.4752133372e-09f
        -0x8.06c56p-30f,
        // 15
        // -4.2456356653e-08f
        -0xb.65942p-28f,
        // 16
        // +1.7114270889e-08f
        +0x9.302aep-29f,
        // 17
        // +2.3001966554e-08f
        +0xc.595dcp-29f,
        // 18
        // -3.0476833501e-08f
        -0x8.2e5a2p-28f,
        // 19
        // -1.6538537650e-08f
        -0x8.e10a1p-29f,
        // 20
        // +5.2333342104e-09f
        +0xb.3d0e5p-31f,
        // 21
        // -3.5920646013e-08f
        -0x9.a472bp-28f,
        // 22
        // +6.1075917657e-09f
        +0xd.1daf2p-31f,
        // 23
        // -3.1140544365e-08f
        -0x8.5bf64p-28f,
        // 24
        // -1.4719605090e-08f
        -0xf.ce182p-30f,
        // 25
        // -2.8218101633e-08f
        -0xf.26443p-29f,
        // 26
        // -5.2587951771e-09f
        -0xb.4b0dap-31f,
        // 27
        // -6.3603873279e-09f
        -0xd.a8a8fp-31f,
        // 28
        // -6.1282596775e-09f
        -0xd.290bep-31f,
        // 29
        // -2.4880408844e-08f
        -0xd.5b899p-29f,
        // 30
        // +5.1406092716e-09f
        +0xb.0a147p-31f,
        // 31
        // -8.6972669067e-09f
        -0x9.56afcp-30f
    },
    // static const float _2_pow_i_n_h[32]=
    {
        // 0
        // +1.0000000000e+00f
        +0x8p-3f,
        // 1
        // +1.0218971968e+00f
        +0x8.2cd87p-3f,
        // 2
        // +1.0442737341e+00f
        +0x8.5aac3p-3f,
        // 3
        // +1.0671404600e+00f
        +0x8.8980fp-3f,
        // 4
        // +1.0905077457e+00f
        +0x8.b95c2p-3f,
        // 5
        // +1.1143867970e+00f
        +0x8.ea43ap-3f,
        // 6
        // +1.1387885809e+00f
        +0x9.1c3d3p-3f,
        // 7
        // +1.1637248993e+00f
        +0x9.4f4fp-3f,
        // 8
        // +1.1892070770e+00f
        +0x9.837fp-3f,
        // 9
        // +1.2152473927e+00f
        +0x9.b8d3ap-3f,
        // 10
        // +1.2418577671e+00f
        +0x9.ef532p-3f,
        // 11
        // +1.2690509558e+00f
        +0xa.27043p-3f,
        // 12
        // +1.2968395948e+00f
        +0xa.5fed7p-3f,
        // 13
        // +1.3252366781e+00f
        +0xa.9a15bp-3f,
        // 14
        // +1.3542555571e+00f
        +0xa.d583fp-3f,
        // 15
        // +1.3839099407e+00f
        +0xb.123f6p-3f,
        // 16
        // +1.4142135382e+00f
        +0xb.504f3p-3f,
        // 17
        // +1.4451807737e+00f
        +0xb.8fbafp-3f,
        // 18
        // +1.4768261909e+00f
        +0xb.d08a4p-3f,
        // 19
        // +1.5091644526e+00f
        +0xc.12c4dp-3f,
        // 20
        // +1.5422108173e+00f
        +0xc.5672ap-3f,
        // 21
        // +1.5759809017e+00f
        +0xc.9b9bep-3f,
        // 22
        // +1.6104903221e+00f
        +0xc.e248cp-3f,
        // 23
        // +1.6457555294e+00f
        +0xd.2a81ep-3f,
        // 24
        // +1.6817928553e+00f
        +0xd.744fdp-3f,
        // 25
        // +1.7186193466e+00f
        +0xd.bfbb8p-3f,
        // 26
        // +1.7562521696e+00f
        +0xe.0ccdfp-3f,
        // 27
        // +1.7947090864e+00f
        +0xe.5b907p-3f,
        // 28
        // +1.8340080976e+00f
        +0xe.ac0c7p-3f,
        // 29
        // +1.8741676807e+00f
        +0xe.fe4bap-3f,
        // 30
        // +1.9152065516e+00f
        +0xf.5257dp-3f,
        // 31
        // +1.9571441412e+00f
        +0xf.a83b3p-3f
    },
    // static const float _2_pow_i_n_l[32]=
    {
        // 0
        // +0.0000000000e+00f
        +0x0p+0f,
        // 1
        // -4.8115598617e-08f
        -0xc.ea7a9p-28f,
        // 2
        // +4.8334701575e-08f
        +0xc.f9891p-28f,
        // 3
        // -5.9337519787e-08f
        -0xf.eda4bp-28f,
        // 4
        // -1.3077539940e-08f
        -0xe.0aba1p-30f,
        // 5
        // -5.4355400181e-08f
        -0xe.97465p-28f,
        // 6
        // +5.3862223126e-08f
        +0xe.75624p-28f,
        // 7
        // -4.0514414934e-08f
        -0xa.e0212p-28f,
        // 8
        // +3.7976352729e-08f
        +0xa.31b71p-28f,
        // 9
        // -3.2673948880e-08f
        -0x8.c5563p-28f,
        // 10
        // +4.4968381019e-08f
        +0xc.12342p-28f,
        // 11
        // +1.4193333175e-09f
        +0xc.3125ap-33f,
        // 12
        // -4.0189995332e-08f
        -0xa.c9d5ep-28f,
        // 13
        // -3.4963733242e-08f
        -0x9.62b08p-28f,
        // 14
        // -1.0123349270e-08f
        -0xa.deaf6p-30f,
        // 15
        // -5.8755773580e-08f
        -0xf.c5aa8p-28f,
        // 16
        // +2.4203234972e-08f
        +0xc.fe77ap-29f,
        // 17
        // +3.3241999375e-08f
        +0x8.ec5f7p-28f,
        // 18
        // -4.5008988536e-08f
        -0xc.14fe8p-28f,
        // 19
        // -2.4959373235e-08f
        -0xd.6663ep-29f,
        // 20
        // +8.0709048333e-09f
        +0x8.aa837p-30f,
        // 21
        // -5.6610254262e-08f
        -0xf.323a2p-28f,
        // 22
        // +9.8362171741e-09f
        +0xa.8fc24p-30f,
        // 23
        // -5.1249720912e-08f
        -0xd.c1daap-28f,
        // 24
        // -2.4755326677e-08f
        -0xd.4a58ap-29f,
        // 25
        // -4.8496175964e-08f
        -0xd.04a1cp-28f,
        // 26
        // -9.2357703707e-09f
        -0x9.eab59p-30f,
        // 27
        // -1.1415044909e-08f
        -0xc.41be6p-30f,
        // 28
        // -1.1239277953e-08f
        -0xc.116dep-30f,
        // 29
        // -4.6630056261e-08f
        -0xc.8464ap-28f,
        // 30
        // +9.8453281083e-09f
        +0xa.92436p-30f,
        // 31
        // -1.7021804410e-08f
        -0x9.23758p-29f
    }
};

template struct cftal::math::exp_data<float>;

