// 
// Copyright (C) 2010-2021 Axel Zeuner
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
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA  
//
#include "cftal/math/func_data.h"

const float
cftal::math::erfc_data<float>::
_tbl[cftal::math::erfc_data<float>::ENTRIES]={
// const float erfc_table[]={
    // 0:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-29.8515625
    // x^ 5: -0x9.ec7a9p-5f,
    -3.1011703610e-01f,
    // x^ 4: +0x8.040e2p-4f,
    +5.0099003315e-01f,
    // x^ 3: -0xc.09076p-4f,
    -7.5220429897e-01f,
    // x^ 2: +0xf.fffe7p-4f,
    +9.9999850988e-01f,
    // x^ 1: -0x9.06ebbp-3f,
    -1.1283792257e+00f,
    // x^ 0: +0x8p-3f,
    +1.0000000000e+00f,
    // x^ 0: +0xc.60ap-35f,
    +3.6023095618e-10f,
    // 0.125:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-31.6328125
    // x^ 5: -0xc.be59fp-6f,
    -1.9911812246e-01f,
    // x^ 4: +0xb.15afdp-5f,
    +3.4639731050e-01f,
    // x^ 3: -0x8.b1e79p-4f,
    -5.4343372583e-01f,
    // x^ 2: +0xc.26c15p-4f,
    +7.5946170092e-01f,
    // x^ 1: -0xe.8fa97p-4f,
    -9.1007369757e-01f,
    // x^ 0: +0xd.f8b78p-4f,
    +8.7322187424e-01f,
    // x^ 0: -0xf.8aee7p-29f,
    -2.8950536191e-08f,
    // 0.25:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-31.8046875
    // x^ 5: -0x8.c2bc2p-6f,
    -1.3688567281e-01f,
    // x^ 4: +0xf.8c104p-6f,
    +2.4292379618e-01f,
    // x^ 3: -0xc.bcb76p-5f,
    -3.9803665876e-01f,
    // x^ 2: +0x9.5a4b5p-4f,
    +5.8454447985e-01f,
    // x^ 1: -0xb.e42bep-4f,
    -7.4320590496e-01f,
    // x^ 0: +0xc.5356ep-4f,
    +7.7034652233e-01f,
    // x^ 0: +0xd.b4df2p-29f,
    +2.5530400904e-08f,
    // 0.375:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-32.0625
    // x^ 5: -0xc.0c858p-7f,
    -9.4132125378e-02f,
    // x^ 4: +0xb.0d3a7p-6f,
    +1.7268238962e-01f,
    // x^ 3: -0x9.7402fp-5f,
    -2.9541155696e-01f,
    // x^ 2: +0xe.945fap-5f,
    +4.5561200380e-01f,
    // x^ 1: -0x9.d2e34p-4f,
    -6.1398625374e-01f,
    // x^ 0: +0xa.f9457p-4f,
    +6.8585723639e-01f,
    // x^ 0: -0xd.bdd58p-32f,
    -3.1994513705e-09f,
    // 0.5:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-32.640625
    // x^ 5: -0x8.0e9dfp-7f,
    -6.2946073711e-02f,
    // x^ 4: +0xf.eaad2p-7f,
    +1.2434925139e-01f,
    // x^ 3: -0xe.3584ap-6f,
    -2.2201648355e-01f,
    // x^ 2: +0xb.7fc28p-5f,
    +3.5934567451e-01f,
    // x^ 1: -0x8.33f93p-4f,
    -5.1268881559e-01f,
    // x^ 0: +0x9.d9de2p-4f,
    +6.1569035053e-01f,
    // x^ 0: -0xd.80574p-31f,
    -6.2870473272e-09f,
    // 0.625:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-33.265625
    // x^ 5: -0xb.543fap-8f,
    -4.4254280627e-02f,
    // x^ 4: +0xb.9aa6p-7f,
    +9.0656995773e-02f,
    // x^ 3: -0xa.ce2a8p-6f,
    -1.6883337498e-01f,
    // x^ 2: +0x9.2bb9bp-5f,
    +2.8658756614e-01f,
    // x^ 1: -0xd.d5e87p-5f,
    -4.3236181140e-01f,
    // x^ 0: +0x8.e8b5bp-4f,
    +5.5681389570e-01f,
    // x^ 0: -0xf.e1986p-30f,
    -1.4790549230e-08f,
    // 0.75:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-32.5625
    // x^ 5: -0x8.9006bp-8f,
    -3.3447664231e-02f,
    // x^ 4: +0x8.8f675p-7f,
    +6.6876329482e-02f,
    // x^ 3: -0x8.4f18fp-6f,
    -1.2982772291e-01f,
    // x^ 2: +0xe.c8041p-6f,
    +2.3095799983e-01f,
    // x^ 1: -0xb.c66ebp-5f,
    -3.6797270179e-01f,
    // x^ 0: +0x8.1c6aap-4f,
    +5.0693762302e-01f,
    // x^ 0: +0xe.a8751p-29f,
    +2.7302720085e-08f,
    // 0.875:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-35.515625
    // x^ 5: -0xb.bdbccp-9f,
    -2.2931955755e-02f,
    // x^ 4: +0xc.c5591p-8f,
    +4.9886289984e-02f,
    // x^ 3: -0xc.eac3cp-7f,
    -1.0091444850e-01f,
    // x^ 2: +0xc.077c2p-6f,
    +1.8795683980e-01f,
    // x^ 1: -0xa.1b4fbp-5f,
    -3.1583389640e-01f,
    // x^ 0: +0xe.dba3fp-5f,
    +4.6431156993e-01f,
    // x^ 0: +0xe.457d7p-30f,
    +1.3291319156e-08f,
    // 1:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-35.34375
    // x^ 5: -0x8.9a4ebp-9f,
    -1.6802271828e-02f,
    // x^ 4: +0x9.a109fp-8f,
    +3.7613507360e-02f,
    // x^ 3: -0xa.24161p-7f,
    -7.9226262867e-02f,
    // x^ 2: +0x9.e139p-6f,
    +1.5437150002e-01f,
    // x^ 1: -0x8.be272p-5f,
    -2.7321201563e-01f,
    // x^ 0: +0xd.aec3cp-5f,
    +4.2758357525e-01f,
    // x^ 0: +0xf.d2edp-34f,
    +9.2107388383e-10f,
    // 1.125:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-33.765625
    // x^ 5: -0xd.38f31p-10f,
    -1.2912557460e-02f,
    // x^ 4: +0xe.aae1dp-9f,
    +2.8647476807e-02f,
    // x^ 3: -0x8.09834p-7f,
    -6.2790304422e-02f,
    // x^ 2: +0x8.2f39p-6f,
    +1.2788224220e-01f,
    // x^ 1: -0xf.3c59bp-6f,
    -2.3805849254e-01f,
    // x^ 0: +0xc.a98fp-5f,
    +3.9569807053e-01f,
    // x^ 0: +0x9.b3531p-30f,
    +9.0342817671e-09f,
    // 1.25:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-34.921875
    // x^ 5: -0x9.97e8fp-10f,
    -9.3685528263e-03f,
    // x^ 4: +0xb.47c54p-9f,
    +2.2031940520e-02f,
    // x^ 3: -0xc.db01p-8f,
    -5.0216734409e-02f,
    // x^ 2: +0xd.ab79fp-7f,
    +1.0679554194e-01f,
    // x^ 1: -0xd.5d567p-6f,
    -2.0882187784e-01f,
    // x^ 0: +0xb.c5349p-5f,
    +3.6782291532e-01f,
    // x^ 0: +0x9.d19ap-33f,
    +1.1430536517e-09f,
    // 1.375:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-34.4375
    // x^ 5: -0xe.d350fp-11f,
    -7.2389910929e-03f,
    // x^ 4: +0x8.c170bp-9f,
    +1.7100831494e-02f,
    // x^ 3: -0xa.5e465p-8f,
    -4.0501017123e-02f,
    // x^ 2: +0xb.8099ep-7f,
    +8.9862093329e-02f,
    // x^ 1: -0xb.cbd32p-6f,
    -1.8431547284e-01f,
    // x^ 0: +0xa.fc47bp-5f,
    +3.4329590201e-01f,
    // x^ 0: -0xd.0a4c6p-30f,
    -1.2144658612e-08f,
    // 1.5:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-34.9375
    // x^ 5: -0x9.f00a3p-11f,
    -4.8523708247e-03f,
    // x^ 4: +0xd.b5df7p-10f,
    +1.3389102183e-02f,
    // x^ 3: -0x8.6e442p-8f,
    -3.2932527363e-02f,
    // x^ 2: +0x9.bf511p-7f,
    +7.6151020825e-02f,
    // x^ 1: -0xa.78cc4p-6f,
    -1.6362291574e-01f,
    // x^ 0: +0xa.4a6d8p-5f,
    +3.2158541679e-01f,
    // x^ 0: -0xb.7f38p-35f,
    -3.3460523241e-10f,
    // 1.625:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-33.859375
    // x^ 5: -0xd.6b639p-12f,
    -3.2762421761e-03f,
    // x^ 4: +0xa.d289ap-10f,
    +1.0568762198e-02f,
    // x^ 3: -0xd.d0841p-9f,
    -2.6981474832e-02f,
    // x^ 2: +0x8.50ad5p-7f,
    +6.4962066710e-02f,
    // x^ 1: -0x9.588f3p-6f,
    -1.4603023231e-01f,
    // x^ 0: +0x9.ac1fbp-5f,
    +3.0226120353e-01f,
    // x^ 0: +0xc.8851cp-31f,
    +5.8358988753e-09f,
    // 1.75:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-34.171875
    // x^ 5: -0xe.974e9p-12f,
    -3.5622662399e-03f,
    // x^ 4: +0x8.9cbf5p-10f,
    +8.4104435518e-03f,
    // x^ 3: -0xb.65467p-9f,
    -2.2257043049e-02f,
    // x^ 2: +0xe.46865p-8f,
    +5.5763620883e-02f,
    // x^ 1: -0x8.61eaap-6f,
    -1.3097634912e-01f,
    // x^ 0: +0x9.1e7e1p-5f,
    +2.8497222066e-01f,
    // x^ 0: +0xf.1e76cp-30f,
    +1.4080665522e-08f,
    // 1.875:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-34.453125
    // x^ 5: -0xf.a2839p-13f,
    -1.9085473614e-03f,
    // x^ 4: +0xd.ceeep-11f,
    +6.7423433065e-03f,
    // x^ 3: -0x9.78197p-9f,
    -1.8494410440e-02f,
    // x^ 2: +0xc.5377ep-8f,
    +4.8148624599e-02f,
    // x^ 1: -0xf.1b2cp-7f,
    -1.1801671982e-01f,
    // x^ 0: +0x8.9f2bap-5f,
    +2.6942998171e-01f,
    // x^ 0: +0xe.d88cp-32f,
    +3.4565772467e-09f,
    // 2:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-34.203125
    // x^ 5: -0xa.baf5fp-13f,
    -1.3098529307e-03f,
    // x^ 4: +0xb.2628ap-11f,
    +5.4438756779e-03f,
    // x^ 3: -0xf.d5a9ap-10f,
    -1.5463495627e-02f,
    // x^ 2: +0xa.b395cp-8f,
    +4.1802749038e-02f,
    // x^ 1: -0xd.ab81ap-7f,
    -1.0679645836e-01f,
    // x^ 0: +0x8.2c339p-5f,
    +2.5539568067e-01f,
    // x^ 0: -0x9.5a812p-31f,
    -4.3555781204e-09f,
    // 2.125:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-36.65625
    // x^ 5: -0xc.93d42p-13f,
    -1.5353339259e-03f,
    // x^ 4: +0x9.1040bp-11f,
    +4.4255307876e-03f,
    // x^ 3: -0xd.51003p-10f,
    -1.3004305772e-02f,
    // x^ 2: +0x9.56d7bp-8f,
    +3.6481361836e-02f,
    // x^ 1: -0xc.6b7bap-7f,
    -9.7030118108e-02f,
    // x^ 0: +0xf.87e94p-6f,
    +2.4267035723e-01f,
    // x^ 0: +0xf.dc605p-31f,
    +7.3857813199e-09f,
    // 2.25:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-34.5625
    // x^ 5: -0xc.0f26bp-14f,
    -7.3603418423e-04f,
    // x^ 4: +0xe.d4b28p-12f,
    +3.6208126694e-03f,
    // x^ 3: -0xb.44b59p-10f,
    -1.1004292406e-02f,
    // x^ 2: +0x8.30ab3p-8f,
    +3.1992625445e-02f,
    // x^ 1: -0xb.53869p-7f,
    -8.8486500084e-02f,
    // x^ 0: +0xe.ca223p-6f,
    +2.3108725250e-01f,
    // x^ 0: +0xd.625f4p-31f,
    +6.2325344885e-09f,
    // 2.375:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-34.90625
    // x^ 5: -0x9.a6239p-14f,
    -5.8892701054e-04f,
    // x^ 4: +0xc.35bc6p-12f,
    +2.9809339903e-03f,
    // x^ 3: -0x9.95bc7p-10f,
    -9.3602603301e-03f,
    // x^ 2: +0xe.6e43fp-9f,
    +2.8185008094e-02f,
    // x^ 1: -0xa.5d756p-7f,
    -8.0977126956e-02f,
    // x^ 0: +0xe.1cc3fp-6f,
    +2.2050569952e-01f,
    // x^ 0: -0xf.b2bd8p-31f,
    -7.3100459019e-09f,
    // 2.5:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-38.078125
    // x^ 5: -0xc.9763ap-14f,
    -7.6851586346e-04f,
    // x^ 4: +0xa.1c4bdp-12f,
    +2.4683915544e-03f,
    // x^ 3: -0x8.31838p-10f,
    -8.0013796687e-03f,
    // x^ 2: +0xc.c4ac4p-9f,
    +2.4937994778e-02f,
    // x^ 1: -0x9.8436cp-7f,
    -7.4347347021e-02f,
    // x^ 0: +0xd.7ddap-6f,
    +2.1080636978e-01f,
    // x^ 0: -0xc.48699p-31f,
    -5.7196527514e-09f,
    // 2.625:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-34.140625
    // x^ 5: -0xa.5a00fp-18f,
    -3.9488131733e-05f,
    // x^ 4: +0x8.6b17dp-12f,
    +2.0552568603e-03f,
    // x^ 3: -0xe.16051p-11f,
    -6.8779368885e-03f,
    // x^ 2: +0xb.57e9dp-9f,
    +2.2155100480e-02f,
    // x^ 1: -0x8.c39bdp-7f,
    -6.8469502032e-02f,
    // x^ 0: +0xc.ebb9cp-6f,
    +2.0188754797e-01f,
    // x^ 0: +0xe.1f586p-31f,
    +6.5762746360e-09f,
    // 2.75:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-37.84375
    // x^ 5: -0xe.70064p-15f,
    -4.4060044456e-04f,
    // x^ 4: +0xe.180f4p-13f,
    +1.7204568721e-03f,
    // x^ 3: -0xc.276cp-11f,
    -5.9345662594e-03f,
    // x^ 2: +0xa.1dcc5p-9f,
    +1.9758591428e-02f,
    // x^ 1: -0x8.182bcp-7f,
    -6.3237637281e-02f,
    // x^ 0: +0xc.64f5bp-6f,
    +1.9366209209e-01f,
    // x^ 0: +0x8.ff6a4p-31f,
    +4.1898875480e-09f,
    // 2.875:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-36.671875
    // x^ 5: -0x9.d1262p-15f,
    -2.9959069798e-04f,
    // x^ 4: +0xb.db4eep-13f,
    +1.4473476913e-03f,
    // x^ 3: -0xa.89c23p-11f,
    -5.1455660723e-03f,
    // x^ 2: +0x9.0e11dp-9f,
    +1.7685467377e-02f,
    // x^ 1: -0xe.fe01p-8f,
    -5.8563292027e-02f,
    // x^ 0: +0xb.e852fp-6f,
    +1.8605493009e-01f,
    // x^ 0: +0x9.dd6dp-31f,
    +4.5937227355e-09f,
    // 3:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-35.40625
    // x^ 5: -0xc.97545p-17f,
    -9.6062700322e-05f,
    // x^ 4: +0xa.056cbp-13f,
    +1.2232897570e-03f,
    // x^ 3: -0x9.2d2a8p-11f,
    -4.4806785882e-03f,
    // x^ 2: +0x8.21ff1p-9f,
    +1.5884371474e-02f,
    // x^ 1: -0xd.eb572p-8f,
    -5.4372258484e-02f,
    // x^ 0: +0xb.74c14p-6f,
    +1.7900115252e-01f,
    // x^ 0: -0xb.76bdcp-33f,
    -1.3345657912e-09f,
    // 3.125:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-38.203125
    // x^ 5: -0x9.debb4p-15f,
    -3.0120986048e-04f,
    // x^ 4: +0x8.83417p-13f,
    +1.0391500546e-03f,
    // x^ 3: -0x8.04bc2p-11f,
    -3.9152810350e-03f,
    // x^ 2: +0xe.a81fp-10f,
    +1.4313206077e-02f,
    // x^ 1: -0xc.f4402p-8f,
    -5.0601966679e-02f,
    // x^ 0: +0xb.09541p-6f,
    +1.7244435847e-01f,
    // x^ 0: -0xd.ab84ap-31f,
    -6.3655862803e-09f,
    // 3.25:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-37.671875
    // x^ 5: -0xb.77fdcp-16f,
    -1.7499871319e-04f,
    // x^ 4: +0xe.85569p-14f,
    +8.8628247613e-04f,
    // x^ 3: -0xe.129ffp-12f,
    -3.4357307013e-03f,
    // x^ 2: +0xd.3f6eep-10f,
    +1.2937290594e-02f,
    // x^ 1: -0xc.15429p-8f,
    -4.7199402004e-02f,
    // x^ 0: +0xa.a53dp-6f,
    +1.6633534431e-01f,
    // x^ 0: +0x8.d4b83p-31f,
    +4.1122247829e-09f,
    // 3.375:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-35.546875
    // x^ 5: -0xc.f99e9p-15f,
    -3.9596788702e-04f,
    // x^ 4: +0xc.707cap-14f,
    +7.5924082194e-04f,
    // x^ 3: -0xc.62f13p-12f,
    -3.0240460765e-03f,
    // x^ 2: +0xc.0266p-10f,
    +1.1727899313e-02f,
    // x^ 1: -0xb.4b69bp-8f,
    -4.4119458646e-02f,
    // x^ 0: +0xa.47c79p-6f,
    +1.6063107550e-01f,
    // x^ 0: -0xf.d638ap-31f,
    -7.3745853868e-09f,
    // 3.5:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-35.25
    // x^ 5: +0xd.366fp-17f,
    +1.0080437642e-04f,
    // x^ 4: +0xa.b1cdcp-14f,
    +6.5274327062e-04f,
    // x^ 3: -0xa.f4643p-12f,
    -2.6744760107e-03f,
    // x^ 2: +0xa.eac09p-10f,
    +1.0661133565e-02f,
    // x^ 1: -0xa.942e9p-8f,
    -4.1323576123e-02f,
    // x^ 0: +0x9.f054dp-6f,
    +1.5529365838e-01f,
    // x^ 0: -0xb.e2a72p-32f,
    -2.7672766301e-09f,
    // 3.625:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-35.375
    // x^ 5: +0xd.c25fbp-17f,
    +1.0497491894e-04f,
    // x^ 4: +0x9.3b7c4p-14f,
    +5.6349881925e-04f,
    // x^ 3: -0x9.b623ap-12f,
    -2.3709670641e-03f,
    // x^ 2: +0x9.f3419p-10f,
    +9.7170108929e-03f,
    // x^ 1: -0x9.ed664p-8f,
    -3.8778677583e-02f,
    // x^ 0: +0x9.9e58dp-6f,
    +1.5028972924e-01f,
    // x^ 0: -0xe.865f8p-31f,
    -6.7636811707e-09f,
    // 3.75:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-37.25
    // x^ 5: -0xc.32c4ap-18f,
    -4.6532870329e-05f,
    // x^ 4: +0x8.004c5p-14f,
    +4.8835232155e-04f,
    // x^ 3: -0x8.a2038p-12f,
    -2.1076332778e-03f,
    // x^ 2: +0x9.17833p-10f,
    +8.8787553832e-03f,
    // x^ 1: -0x9.55328p-8f,
    -3.6456257105e-02f,
    // x^ 0: +0x9.51579p-6f,
    +1.4558972418e-01f,
    // x^ 0: -0xc.7d728p-32f,
    -2.9080613473e-09f,
    // 3.875:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-37
    // x^ 5: -0xb.2aecbp-16f,
    -1.7040518287e-04f,
    // x^ 4: +0xd.e9834p-15f,
    +4.2456539813e-04f,
    // x^ 3: -0xf.64cb4p-13f,
    -1.8791169859e-03f,
    // x^ 2: +0x8.53d03p-10f,
    +8.1322221085e-03f,
    // x^ 1: -0x8.c9f5cp-8f,
    -3.4331664443e-02f,
    // x^ 0: +0x9.08e31p-6f,
    +1.4116741717e-01f,
    // x^ 0: +0xb.2485cp-32f,
    +2.5943540649e-09f,
    // 4:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-36.28125
    // x^ 5: +0xc.08829p-18f,
    +4.5903176215e-05f,
    // x^ 4: +0xc.2324cp-15f,
    +3.7040037569e-04f,
    // x^ 3: -0xd.c7233p-13f,
    -1.6818701988e-03f,
    // x^ 2: +0xf.4a098p-11f,
    +7.4654333293e-03f,
    // x^ 1: -0x8.4a491p-8f,
    -3.2383505255e-02f,
    // x^ 0: +0x8.c4996p-6f,
    +1.3699945807e-01f,
    // x^ 0: -0xf.7334p-35f,
    -4.4965453583e-10f,
    // 4.125:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-36.78125
    // x^ 5: -0xa.55427p-16f,
    -1.5766975412e-04f,
    // x^ 4: +0xa.a025p-15f,
    +3.2426649705e-04f,
    // x^ 3: -0xc.592fep-13f,
    -1.5073714312e-03f,
    // x^ 2: +0xe.10eb7p-11f,
    +6.8682092242e-03f,
    // x^ 1: -0xf.a9e7fp-9f,
    -3.0593154952e-02f,
    // x^ 0: +0x8.8422fp-6f,
    +1.3306497037e-01f,
    // x^ 0: +0xe.e642p-34f,
    +8.6726181792e-10f,
    // 4.25:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-36.484375
    // x^ 5: -0xb.15f1bp-16f,
    -1.6915464948e-04f,
    // x^ 4: +0x9.53ce1p-15f,
    +2.8464852949e-04f,
    // x^ 3: -0xb.1a548p-13f,
    -1.3553285971e-03f,
    // x^ 2: +0xc.f7b8bp-11f,
    +6.3318661414e-03f,
    // x^ 1: -0xe.d1caap-9f,
    -2.8944332153e-02f,
    // x^ 0: +0x8.47316p-6f,
    +1.2934526801e-01f,
    // x^ 0: +0xe.8c94bp-31f,
    +6.7749730270e-09f,
    // 4.375:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-37.125
    // x^ 5: -0xf.cf3f9p-17f,
    -1.2061739835e-04f,
    // x^ 4: +0x8.36d5dp-15f,
    +2.5067749084e-04f,
    // x^ 3: -0xa.02aa4p-13f,
    -1.2219739147e-03f,
    // x^ 2: +0xb.fa8b2p-11f,
    +5.8489674702e-03f,
    // x^ 1: -0xe.0a5b8p-9f,
    -2.7422770858e-02f,
    // x^ 0: +0x8.0d7e6p-6f,
    +1.2582358718e-01f,
    // x^ 0: +0x8.ba1acp-33f,
    +1.0159530994e-09f,
    // 4.5:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-36.734375
    // x^ 5: +0xc.c3749p-18f,
    +4.8688878451e-05f,
    // x^ 4: +0xe.817c6p-16f,
    +2.2134100436e-04f,
    // x^ 3: -0x9.0d85ap-13f,
    -1.1050805915e-03f,
    // x^ 2: +0xb.16096p-11f,
    +5.4131252691e-03f,
    // x^ 1: -0xd.51f5bp-9f,
    -2.6015928015e-02f,
    // x^ 0: +0xf.ad95p-7f,
    +1.2248480320e-01f,
    // x^ 0: +0x9.39ff8p-33f,
    +1.0741123546e-09f,
    // 4.625:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-37.640625
    // x^ 5: +0xc.85c56p-20f,
    +1.1942427591e-05f,
    // x^ 4: +0xc.d85bbp-16f,
    +1.9600141968e-04f,
    // x^ 3: -0x8.32a08p-13f,
    -1.0007033125e-03f,
    // x^ 2: +0xa.47504p-11f,
    +5.0188321620e-03f,
    // x^ 1: -0xc.a7263p-9f,
    -2.4712746963e-02f,
    // x^ 0: +0xf.45b93p-7f,
    +1.1931528896e-01f,
    // x^ 0: -0xb.7752p-35f,
    -3.3370728403e-10f,
    // 4.75:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-38.25
    // x^ 5: -0x8.89cdbp-17f,
    -6.5142019594e-05f,
    // x^ 4: +0xb.66b26p-16f,
    +1.7396788462e-04f,
    // x^ 3: -0xe.e019cp-14f,
    -9.0792193078e-04f,
    // x^ 2: +0x9.8be0ap-11f,
    +4.6613262966e-03f,
    // x^ 1: -0xc.08a4ep-9f,
    -2.3503448814e-02f,
    // x^ 0: +0xe.e301dp-7f,
    +1.1630270630e-01f,
    // x^ 0: +0xf.9e1f8p-34f,
    +9.0906793204e-10f,
    // 4.875:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-36.859375
    // x^ 5: -0xe.de48ep-17f,
    -1.1343612277e-04f,
    // x^ 4: +0xa.25fd3p-16f,
    +1.5485221229e-04f,
    // x^ 3: -0xd.86aap-14f,
    -8.2556344569e-04f,
    // x^ 2: +0x8.e19p-11f,
    +4.3364763260e-03f,
    // x^ 1: -0xb.754eep-9f,
    -2.2379364818e-02f,
    // x^ 0: +0xe.85112p-7f,
    +1.1343587935e-01f,
    // x^ 0: -0x9.2b4f3p-32f,
    -2.1348653956e-09f,
    // 5:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-36.890625
    // x^ 5: +0xf.25421p-18f,
    +5.7775647292e-05f,
    // x^ 4: +0x9.0df82p-16f,
    +1.3816173305e-04f,
    // x^ 3: -0xc.57c6ap-14f,
    -7.5334927533e-04f,
    // x^ 2: +0x8.467c1p-11f,
    +4.0406887420e-03f,
    // x^ 1: -0xa.ec21ap-9f,
    -2.1332789212e-02f,
    // x^ 0: +0xe.2b91dp-7f,
    +1.1070463806e-01f,
    // x^ 0: -0xb.5d958p-35f,
    -3.3078140227e-10f,
    // 5.125:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-37.75
    // x^ 5: +0xc.9d21cp-19f,
    +2.4058907002e-05f,
    // x^ 4: +0x8.1899dp-16f,
    +1.2353663624e-04f,
    // x^ 3: -0xb.44f66p-14f,
    -6.8782863673e-04f,
    // x^ 2: +0xf.71fffp-12f,
    +3.7708280142e-03f,
    // x^ 1: -0xa.6c36ep-9f,
    -2.0356860012e-02f,
    // x^ 0: +0xd.d6365p-7f,
    +1.0809973627e-01f,
    // x^ 0: +0x8.5c4a6p-33f,
    +9.7329144744e-10f,
    // 5.25:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-36.515625
    // x^ 5: -0x8.4a9d9p-16f,
    -1.2651774159e-04f,
    // x^ 4: +0xe.8254cp-17f,
    +1.1069569155e-04f,
    // x^ 3: -0xa.4c2e7p-14f,
    -6.2851462280e-04f,
    // x^ 2: +0xe.6f571p-12f,
    +3.5241509322e-03f,
    // x^ 1: -0x9.f4c0ep-9f,
    -1.9445445389e-02f,
    // x^ 0: +0xd.84b7dp-7f,
    +1.0561273247e-01f,
    // x^ 0: +0xc.e14ep-32f,
    +2.9988811434e-09f,
    // 5.375:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-40.09375
    // x^ 5: -0xd.894a3p-19f,
    -2.5818420909e-05f,
    // x^ 4: +0xd.07a61p-17f,
    +9.9410077382e-05f,
    // x^ 3: -0x9.72623p-14f,
    -5.7658756850e-04f,
    // x^ 2: +0xd.82779p-12f,
    +3.2982511912e-03f,
    // x^ 1: -0x9.85076p-9f,
    -1.8593054265e-02f,
    // x^ 0: +0xd.36d5ap-7f,
    +1.0323591530e-01f,
    // x^ 0: +0x9.574eep-32f,
    +2.1748820522e-09f,
    // 5.5:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-36.296875
    // x^ 5: -0x9.231acp-16f,
    -1.3942149235e-04f,
    // x^ 4: +0xb.bc2bap-17f,
    +8.9531255071e-05f,
    // x^ 3: -0x8.a9e07p-14f,
    -5.2878301358e-04f,
    // x^ 2: +0xc.a9295p-12f,
    +3.0910123605e-03f,
    // x^ 1: -0x9.1c654p-9f,
    -1.7794765532e-02f,
    // x^ 0: +0xc.ec548p-7f,
    +1.0096222162e-01f,
    // x^ 0: -0xd.d78bcp-32f,
    -3.2228362201e-09f,
    // 5.625:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-36.140625
    // x^ 5: -0x9.f379p-16f,
    -1.5184120275e-04f,
    // x^ 4: +0xa.95721p-17f,
    +8.0747769971e-05f,
    // x^ 3: -0xf.ee954p-15f,
    -4.8620498274e-04f,
    // x^ 2: +0xb.e177bp-12f,
    +2.9005694669e-03f,
    // x^ 1: -0x8.ba45ep-9f,
    -1.7046149820e-02f,
    // x^ 0: +0xc.a4fdfp-7f,
    +9.8785154521e-02f,
    // x^ 0: +0xb.63fc1p-32f,
    +2.6520725616e-09f,
    // 5.75:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-36.359375
    // x^ 5: +0xe.2f5f7p-17f,
    +1.0822334298e-04f,
    // x^ 4: +0x9.8f50fp-17f,
    +7.2935705248e-05f,
    // x^ 3: -0xe.b8988p-15f,
    -4.4925161637e-04f,
    // x^ 2: +0xb.29a82p-12f,
    +2.7252738364e-03f,
    // x^ 1: -0x8.5e236p-9f,
    -1.6343217343e-02f,
    // x^ 0: +0xc.60a02p-7f,
    +9.6698775887e-02f,
    // x^ 0: +0x9.cd4bcp-32f,
    +2.2821913248e-09f,
    // 5.875:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-37
    // x^ 5: +0x8.c7ec7p-17f,
    +6.6993343353e-05f,
    // x^ 4: +0x8.a7fcdp-17f,
    +6.6041575337e-05f,
    // x^ 3: -0xd.938a6p-15f,
    -4.1431671707e-04f,
    // x^ 2: +0xa.80329p-12f,
    +2.5636649225e-03f,
    // x^ 1: -0x8.07851p-9f,
    -1.5682371333e-02f,
    // x^ 0: +0xc.1f0d1p-7f,
    +9.4697602093e-02f,
    // x^ 0: -0xa.ba6a6p-32f,
    -2.4978503710e-09f,
    // 6:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-37.375
    // x^ 5: +0xd.202b7p-18f,
    +5.0070430007e-05f,
    // x^ 4: +0xf.b416dp-18f,
    +5.9903995862e-05f,
    // x^ 3: -0xc.8aee3p-15f,
    -3.8277273416e-04f,
    // x^ 2: +0x9.e3bb2p-12f,
    +2.4144467898e-03f,
    // x^ 1: -0xf.6bfb3p-10f,
    -1.5060353093e-02f,
    // x^ 0: +0xb.e01a4p-7f,
    +9.2776566744e-02f,
    // x^ 0: +0x9.13bc2p-33f,
    +1.0567122732e-09f,
    // 6.125:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-39.390625
    // x^ 5: +0xd.5c64ap-21f,
    +6.3709785536e-06f,
    // x^ 4: +0xe.4307dp-18f,
    +5.4404594266e-05f,
    // x^ 3: -0xb.996e1p-15f,
    -3.5398363252e-04f,
    // x^ 2: +0x9.530c5p-12f,
    +2.2764664609e-03f,
    // x^ 1: -0xe.d253fp-10f,
    -1.4474212192e-02f,
    // x^ 0: +0xb.a3a0ap-7f,
    +9.0931013227e-02f,
    // x^ 0: +0xe.ffd61p-32f,
    +3.4923106629e-09f,
    // 6.25:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-37.390625
    // x^ 5: -0x8.ac7c8p-17f,
    -6.6175649408e-05f,
    // x^ 4: +0xc.fbfeep-18f,
    +4.9531394325e-05f,
    // x^ 3: -0xa.bc531p-15f,
    -3.2762580668e-04f,
    // x^ 2: +0x8.cd122p-12f,
    +2.1486957557e-03f,
    // x^ 1: -0xe.4160ap-10f,
    -1.3921270147e-02f,
    // x^ 0: +0xb.697c1p-7f,
    +8.9156635106e-02f,
    // x^ 0: -0xe.407edp-32f,
    -3.3182872006e-09f,
    // 6.375:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-37.890625
    // x^ 5: -0xc.9691cp-18f,
    -4.8020025133e-05f,
    // x^ 4: +0xb.d5318p-18f,
    +4.5138498535e-05f,
    // x^ 3: -0x9.f6cc7p-15f,
    -3.0407888698e-04f,
    // x^ 2: +0x8.50d63p-12f,
    +2.0302168559e-03f,
    // x^ 1: -0xd.b87dcp-10f,
    -1.3399090618e-02f,
    // x^ 0: +0xb.318aep-7f,
    +8.7449416518e-02f,
    // x^ 0: +0xa.e0e24p-33f,
    +1.2664185256e-09f,
    // 6.5:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-37.375
    // x^ 5: -0x8.8360dp-17f,
    -6.4950530941e-05f,
    // x^ 4: +0xa.cf3f6p-18f,
    +4.1235201934e-05f,
    // x^ 3: -0x9.410f1p-15f,
    -2.8241382097e-04f,
    // x^ 2: +0xf.baf7bp-13f,
    +1.9202077528e-03f,
    // x^ 1: -0xd.37168p-10f,
    -1.2905456126e-02f,
    // x^ 0: +0xa.fbae2p-7f,
    +8.5805669427e-02f,
    // x^ 0: +0xb.a60f8p-34f,
    +6.7804206694e-10f,
    // 6.625:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-38.234375
    // x^ 5: +0xe.68e92p-19f,
    +2.7484526072e-05f,
    // x^ 4: +0x9.e152bp-18f,
    +3.7689849705e-05f,
    // x^ 3: -0x8.9ff2dp-15f,
    -2.6320797042e-04f,
    // x^ 2: +0xe.e47adp-13f,
    +1.8179320032e-03f,
    // x^ 1: -0xc.bca3p-10f,
    -1.2438341975e-02f,
    // x^ 0: +0xa.c7c8fp-7f,
    +8.4221951663e-02f,
    // x^ 0: -0xb.3a84bp-32f,
    -2.6143591736e-09f,
    // 6.75:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-38.28125
    // x^ 5: +0xd.f70bcp-19f,
    +2.6636167604e-05f,
    // x^ 4: +0x9.0b7c9p-18f,
    +3.4503438656e-05f,
    // x^ 3: -0x8.08988p-15f,
    -2.4516531266e-04f,
    // x^ 2: +0xe.1cd25p-13f,
    +1.7227275530e-03f,
    // x^ 1: -0xc.48a74p-10f,
    -1.1995900422e-02f,
    // x^ 0: +0xa.95c07p-7f,
    +8.2695059478e-02f,
    // x^ 0: -0xb.9c459p-32f,
    -2.7032653893e-09f,
    // 6.875:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-37.78125
    // x^ 5: -0xc.cce1p-18f,
    -4.8829300795e-05f,
    // x^ 4: +0x8.4d13fp-18f,
    +3.1666128052e-05f,
    // x^ 3: -0xe.f4ecdp-16f,
    -2.2822171741e-04f,
    // x^ 2: +0xd.62be6p-13f,
    +1.6339987051e-03f,
    // x^ 1: -0xb.dab1bp-10f,
    -1.1576439254e-02f,
    // x^ 0: +0xa.657bbp-7f,
    +8.1222020090e-02f,
    // x^ 0: -0xf.05c25p-32f,
    -3.4976974650e-09f,
    // 7:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-37.359375
    // x^ 5: -0x8.5b3cfp-17f,
    -6.3754261646e-05f,
    // x^ 4: +0xf.3e1f1p-19f,
    +2.9073069527e-05f,
    // x^ 3: -0xd.f5065p-16f,
    -2.1296886553e-04f,
    // x^ 2: +0xc.b51efp-13f,
    +1.5512089012e-03f,
    // x^ 1: -0xb.725a3p-10f,
    -1.1178406887e-02f,
    // x^ 0: +0xa.36e36p-7f,
    +7.9800054431e-02f,
    // x^ 0: -0xd.fd58p-37f,
    -1.0178791143e-10f,
    // 7.125:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-38.8125
    // x^ 5: -0xd.5e636p-19f,
    -2.5498778996e-05f,
    // x^ 4: +0xe.0300bp-19f,
    +2.6725252610e-05f,
    // x^ 3: -0xd.0e9e1p-16f,
    -1.9923552463e-04f,
    // x^ 2: +0xc.12efbp-13f,
    +1.4738732716e-03f,
    // x^ 1: -0xb.0f414p-10f,
    -1.0800380260e-02f,
    // x^ 0: +0xa.09e1ep-7f,
    +7.8426584601e-02f,
    // x^ 0: -0xd.2330bp-32f,
    -3.0588036548e-09f,
    // 7.25:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-38.3125
    // x^ 5: +0xe.809e6p-19f,
    +2.7661164495e-05f,
    // x^ 4: +0xc.e6501p-19f,
    +2.4604147256e-05f,
    // x^ 3: -0xc.3c3c4p-16f,
    -1.8669577548e-04f,
    // x^ 2: +0xb.7b454p-13f,
    +1.4015533961e-03f,
    // x^ 1: -0xa.b10f2p-10f,
    -1.0441051796e-02f,
    // x^ 0: +0x9.de62dp-7f,
    +7.7099181712e-02f,
    // x^ 0: -0xb.afadp-33f,
    -1.3604566362e-09f,
    // 7.375:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-37.265625
    // x^ 5: +0x8.0b66fp-17f,
    +6.1374965298e-05f,
    // x^ 4: +0xb.e5355p-19f,
    +2.2688569516e-05f,
    // x^ 3: -0xb.78fb5p-16f,
    -1.7505775031e-04f,
    // x^ 2: +0xa.ed4a7p-13f,
    +1.3338521821e-03f,
    // x^ 1: -0xa.57731p-10f,
    -1.0099218227e-02f,
    // x^ 0: +0x9.b4534p-7f,
    +7.5815588236e-02f,
    // x^ 0: +0xc.c9e88p-33f,
    +1.4888010824e-09f,
    // 7.5:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-39.03125
    // x^ 5: -0xb.4e393p-19f,
    -2.1563644623e-05f,
    // x^ 4: +0xa.fbc9ap-19f,
    +2.0949450118e-05f,
    // x^ 3: -0xa.ba611p-16f,
    -1.6369695368e-04f,
    // x^ 2: +0xa.683dep-13f,
    +1.2704094406e-03f,
    // x^ 1: -0xa.0222bp-10f,
    -9.7737712786e-03f,
    // x^ 0: +0x9.8ba18p-7f,
    +7.4573695660e-02f,
    // x^ 0: -0xb.272dbp-32f,
    -2.5967696882e-09f,
    // 7.625:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-39.875
    // x^ 5: -0xd.983f5p-20f,
    -1.2964931557e-05f,
    // x^ 4: +0xa.27b04p-19f,
    +1.9369188522e-05f,
    // x^ 3: -0xa.12227p-16f,
    -1.5366879234e-04f,
    // x^ 2: +0x9.eb6fep-13f,
    +1.2108979281e-03f,
    // x^ 1: -0x9.b0d94p-10f,
    -9.4636864960e-03f,
    // x^ 0: +0x9.643cdp-7f,
    +7.3371507227e-02f,
    // x^ 0: -0xa.3f608p-35f,
    -2.9824342995e-10f,
    // 7.75:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-40.359375
    // x^ 5: -0xa.303acp-20f,
    -9.7164120234e-06f,
    // x^ 4: +0x9.64613p-19f,
    +1.7914024284e-05f,
    // x^ 3: -0x9.761bcp-16f,
    -1.4436891070e-04f,
    // x^ 2: +0x9.7640ap-13f,
    +1.1550199706e-03f,
    // x^ 1: -0x9.63576p-10f,
    -9.1680195183e-03f,
    // x^ 0: +0x9.3e15ap-7f,
    +7.2207167745e-02f,
    // x^ 0: +0xd.2f844p-32f,
    +3.0700144649e-09f,
    // 7.875:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-37.265625
    // x^ 5: -0x8.a60e5p-17f,
    -6.5984007961e-05f,
    // x^ 4: +0x8.b6e2bp-19f,
    +1.6621392206e-05f,
    // x^ 3: -0x8.e0357p-16f,
    -1.3543419482e-04f,
    // x^ 2: +0x9.081e6p-13f,
    +1.1025040876e-03f,
    // x^ 1: -0x9.19627p-10f,
    -8.8858967647e-03f,
    // x^ 0: +0x9.191d6p-7f,
    +7.1078941226e-02f,
    // x^ 0: -0xe.9a663p-32f,
    -3.4000542382e-09f,
    // 8:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-39.3125
    // x^ 5: -0x9.13a77p-19f,
    -1.7312571799e-05f,
    // x^ 4: +0x8.1360ep-19f,
    +1.5403169527e-05f,
    // x^ 3: -0x8.5e83ep-16f,
    -1.2770385365e-04f,
    // x^ 2: +0x8.a0847p-13f,
    +1.0531031294e-03f,
    // x^ 1: -0x8.d2c41p-10f,
    -8.6165079847e-03f,
    // x^ 0: +0x8.f5462p-7f,
    +6.9985166192e-02f,
    // x^ 0: +0x9.b84p-40f,
    +8.8400398113e-12f,
    // 8.125:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-37.765625
    // x^ 5: -0xc.4da17p-18f,
    -4.6933153499e-05f,
    // x^ 4: +0xe.ff70bp-20f,
    +1.4303029275e-05f,
    // x^ 3: -0xf.be9dap-17f,
    -1.2012170919e-04f,
    // x^ 2: +0x8.3ef95p-13f,
    +1.0065907845e-03f,
    // x^ 1: -0x8.8f4ap-10f,
    -8.3591043949e-03f,
    // x^ 0: +0x8.d2831p-7f,
    +6.8924315274e-02f,
    // x^ 0: -0xf.e8f7ep-32f,
    -3.7043430545e-09f,
    // 8.25:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-37.609375
    // x^ 5: -0xd.93b8bp-18f,
    -5.1792285376e-05f,
    // x^ 4: +0xd.eff8fp-20f,
    +1.3291733012e-05f,
    // x^ 3: -0xe.d671ep-17f,
    -1.1320247722e-04f,
    // x^ 2: +0xf.c61c1p-14f,
    +9.6276035765e-04f,
    // x^ 1: -0x8.4ec58p-10f,
    -8.1129893661e-03f,
    // x^ 0: +0x8.b0c7ep-7f,
    +6.7894920707e-02f,
    // x^ 0: -0xe.28054p-34f,
    -8.2400686274e-10f,
    // 8.375:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-37.671875
    // x^ 5: -0xd.19343p-18f,
    -4.9966631195e-05f,
    // x^ 4: +0xc.f7e58p-20f,
    +1.2367578165e-05f,
    // x^ 3: -0xd.ffb89p-17f,
    -1.0680320702e-04f,
    // x^ 2: +0xf.18b9dp-14f,
    +9.2142244102e-04f,
    // x^ 1: -0x8.110b3p-10f,
    -7.8775165603e-03f,
    // x^ 0: +0x8.90092p-7f,
    +6.6895619035e-02f,
    // x^ 0: +0x8.365bdp-32f,
    +1.9120840467e-09f,
    // 8.5:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-38.265625
    // x^ 5: -0x8.b4375p-18f,
    -3.3203006751e-05f,
    // x^ 4: +0xc.144a6p-20f,
    +1.1519679902e-05f,
    // x^ 3: -0xd.3a9ecp-17f,
    -1.0092914454e-04f,
    // x^ 2: +0xe.75117p-14f,
    +8.8240340119e-04f,
    // x^ 1: -0xf.abe57p-11f,
    -7.6520848088e-03f,
    // x^ 0: +0x8.703cp-7f,
    +6.5925121307e-02f,
    // x^ 0: +0xa.3ea04p-33f,
    +1.1926322152e-09f,
    // 8.625:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-38.28125
    // x^ 5: +0x8.027e6p-18f,
    +3.0554736441e-05f,
    // x^ 4: +0xb.40e34p-20f,
    +1.0732142982e-05f,
    // x^ 3: -0xc.8bdp-17f,
    -9.5719471574e-05f,
    // x^ 2: +0xd.da77dp-14f,
    +8.4554386558e-04f,
    // x^ 1: -0xf.3aad1p-11f,
    -7.4361343868e-03f,
    // x^ 0: +0x8.51564p-7f,
    +6.4982205629e-02f,
    // x^ 0: -0xe.8cdacp-34f,
    -8.4693385638e-10f,
    // 8.75:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-38.34375
    // x^ 5: -0x8.3dc6cp-18f,
    -3.1438117730e-05f,
    // x^ 4: +0xa.7ecfdp-20f,
    +1.0009153812e-05f,
    // x^ 3: -0xb.d2802p-17f,
    -9.0196743258e-05f,
    // x^ 2: +0xd.484f9p-14f,
    +8.1069726730e-04f,
    // x^ 1: -0xe.ce277p-11f,
    -7.2291451506e-03f,
    // x^ 0: +0x8.334e3p-7f,
    +6.4065717161e-02f,
    // x^ 0: -0xd.d328ep-33f,
    -1.6094234834e-09f,
    // 8.875:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-40
    // x^ 5: -0xb.34881p-20f,
    -1.0686112546e-05f,
    // x^ 4: +0x9.cd849p-20f,
    +9.3486823971e-06f,
    // x^ 3: -0xb.33f21p-17f,
    -8.5471438069e-05f,
    // x^ 2: +0xc.be07fp-14f,
    +7.7772879740e-04f,
    // x^ 1: -0xe.66132p-11f,
    -7.0306295529e-03f,
    // x^ 0: +0x8.161abp-7f,
    +6.3174568117e-02f,
    // x^ 0: -0xb.3e296p-32f,
    -2.6176727452e-09f,
    // 9:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-39.515625
    // x^ 5: -0xf.0f4a7p-20f,
    -1.4362077309e-05f,
    // x^ 4: +0x9.2a131p-20f,
    +8.7398084361e-06f,
    // x^ 3: -0xa.9b92fp-17f,
    -8.0930411059e-05f,
    // x^ 2: +0xc.3b1bap-14f,
    +7.4651429895e-04f,
    // x^ 1: -0xe.02335p-11f,
    -6.8401345052e-03f,
    // x^ 0: +0xf.f3662p-8f,
    +6.2307722867e-02f,
    // x^ 0: +0xa.0f95ep-33f,
    +1.1712406600e-09f,
    // 9.125:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-40.40625
    // x^ 5: -0x8.8fba7p-20f,
    -8.1648240666e-06f,
    // x^ 4: +0x8.92ed4p-20f,
    +8.1767393567e-06f,
    // x^ 3: -0xa.0edacp-17f,
    -7.6736643678e-05f,
    // x^ 2: +0xb.bf0fbp-14f,
    +7.1693927748e-04f,
    // x^ 1: -0xd.a24f1p-11f,
    -6.6572357900e-03f,
    // x^ 0: +0xf.bc1e7p-8f,
    +6.1464216560e-02f,
    // x^ 0: -0x9.d27cdp-33f,
    -1.1434565517e-09f,
    // 9.25:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-38.828125
    // x^ 5: -0xb.d63abp-19f,
    -2.2576967240e-05f,
    // x^ 4: +0x8.07ab2p-20f,
    +7.6579617598e-06f,
    // x^ 3: -0x9.8770fp-17f,
    -7.2701011959e-05f,
    // x^ 2: +0xb.4972ap-14f,
    +6.8889802787e-04f,
    // x^ 1: -0xd.46313p-11f,
    -6.4815371297e-03f,
    // x^ 0: +0xf.864eap-8f,
    +6.0643114150e-02f,
    // x^ 0: +0x8.84829p-33f,
    +9.9158115052e-10f,
    // 9.375:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-38.875
    // x^ 5: +0xa.a78bep-19f,
    +2.0321804186e-05f,
    // x^ 4: +0xf.09472p-21f,
    +7.1698386819e-06f,
    // x^ 3: -0x9.12f23p-17f,
    -6.9229186920e-05f,
    // x^ 2: +0xa.d9dbap-14f,
    +6.6229293589e-04f,
    // x^ 1: -0xc.eda7dp-11f,
    -6.3126669265e-03f,
    // x^ 0: +0xf.51e82p-8f,
    +5.9843547642e-02f,
    // x^ 0: -0x8.5dff4p-33f,
    -9.7406749333e-10f,
    // 9.5:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-38.9375
    // x^ 5: +0xa.2a2d1p-19f,
    +1.9387722205e-05f,
    // x^ 4: +0xe.19f48p-21f,
    +6.7240653152e-06f,
    // x^ 3: -0x8.9e2eap-17f,
    -6.5749351052e-05f,
    // x^ 2: +0xa.6fe9ap-14f,
    +6.3703360502e-04f,
    // x^ 1: -0xc.98846p-11f,
    -6.1502782628e-03f,
    // x^ 0: +0xf.1edcep-8f,
    +5.9064678848e-02f,
    // x^ 0: -0x8.8218ep-34f,
    -4.9524195855e-10f,
    // 9.625:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-40.015625
    // x^ 5: -0xa.9d615p-20f,
    -1.0123029824e-05f,
    // x^ 4: +0xd.42268p-21f,
    +6.3220977609e-06f,
    // x^ 3: -0x8.2b603p-17f,
    -6.2327853811e-05f,
    // x^ 2: +0xa.0b42dp-14f,
    +6.1303639086e-04f,
    // x^ 1: -0xc.469b2p-11f,
    -5.9940451756e-03f,
    // x^ 0: +0xe.ed1fbp-8f,
    +5.8305721730e-02f,
    // x^ 0: -0x9.835b7p-33f,
    -1.1074722250e-09f,
    // 9.75:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-38.21875
    // x^ 5: +0x8.8d9bbp-18f,
    +3.2627704059e-05f,
    // x^ 4: +0xc.6f49ep-21f,
    +5.9293370214e-06f,
    // x^ 3: -0xf.9902fp-18f,
    -5.9500507632e-05f,
    // x^ 2: +0x9.ab942p-14f,
    +5.9022393543e-04f,
    // x^ 1: -0xb.f7c2fp-11f,
    -5.8436612599e-03f,
    // x^ 0: +0xe.bca3fp-8f,
    +5.7565923780e-02f,
    // x^ 0: -0xe.45ea8p-35f,
    -4.1540215712e-10f,
    // 9.875:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-38.640625
    // x^ 5: -0xd.3abf8p-19f,
    -2.5233239285e-05f,
    // x^ 4: +0xb.b6064p-21f,
    +5.5842556321e-06f,
    // x^ 3: -0xe.c2bdp-18f,
    -5.6307588238e-05f,
    // x^ 2: +0x9.50903p-14f,
    +5.6852417765e-04f,
    // x^ 1: -0xb.abd57p-11f,
    -5.6988405995e-03f,
    // x^ 0: +0xe.8d5dbp-8f,
    +5.6844573468e-02f,
    // x^ 0: +0x9.4ef2p-38f,
    +3.3863689630e-11f,
    // 10:     // [-6.25e-2, 6.25e-2] : | p - f | <= 2^-40.703125
    // x^ 5: +0xb.4cc5cp-21f,
    +5.3882085922e-06f,
    // x^ 4: +0xb.0402cp-21f,
    +5.2526793297e-06f,
    // x^ 3: -0xe.18726p-18f,
    -5.3770047089e-05f,
    // x^ 2: +0x8.f9ef8p-14f,
    +5.4787052795e-04f,
    // x^ 1: -0xb.62ae4p-11f,
    -5.5593121797e-03f,
    // x^ 0: +0xe.5f419p-8f,
    +5.6140992790e-02f,
    // x^ 0: -0xc.d0eap-38f,
    -4.6624593075e-11f,
};

template struct cftal::math::erfc_data<float>;
