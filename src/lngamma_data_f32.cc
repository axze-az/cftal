//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/math/func_data.h"

template struct cftal::math::lngamma_data<float>;

const float
cftal::math::lngamma_data<float>::
_12_tbl[cftal::math::lngamma_data<float>::ENTRIES]={
// const float lngamma_12_table[]={
    // 1:     // [0, 1.5625e-2] : | p - f | <= 2^-47.6875
    // x^ 5: -0xc.daf2ap-6f,
    -2.0086351037e-01f,
    // x^ 4: +0x8.a7dddp-5f,
    +2.7049151063e-01f,
    // x^ 3: -0xc.d269ap-5f,
    -4.0068513155e-01f,
    // x^ 2: +0xd.28d33p-4f,
    +8.2246702909e-01f,
    // x^ 2: +0xe.4cd38p-32f,
    +3.3295020074e-09f,
    // x^ 1: -0x9.3c468p-4f,
    -5.7721567154e-01f,
    // x^ 1: +0xe.41554p-31f,
    +6.6380980712e-09f,
    // x^ 0: +0x0p+0f,
    +0.0000000000e+00f,
    // x^ 0: +0x0p+0f,
    +0.0000000000e+00f,
    // 1.03125:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-43.1875
    // x^ 5: -0xb.73e44p-6f,
    -1.7894846201e-01f,
    // x^ 4: +0xf.656ebp-6f,
    +2.4056594074e-01f,
    // x^ 3: -0xb.cd1f1p-5f,
    -3.6878922582e-01f,
    // x^ 2: +0xc.9534cp-4f,
    +7.8642725945e-01f,
    // x^ 2: -0xd.651d4p-29f,
    -2.4950089994e-08f,
    // x^ 1: -0x8.6e669p-4f,
    -5.2695327997e-01f,
    // x^ 1: -0x9.482e8p-30f,
    -8.6444984504e-09f,
    // x^ 0: -0x8.d491cp-9f,
    -1.7246775329e-02f,
    // x^ 0: +0xb.3fe48p-35f,
    +3.2740588018e-10f,
    // 1.0625:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-43.75
    // x^ 5: -0x9.e1009p-6f,
    -1.5435804427e-01f,
    // x^ 4: +0xd.bcb1bp-6f,
    +2.1464197338e-01f,
    // x^ 3: -0xa.e46d6p-5f,
    -3.4038418531e-01f,
    // x^ 2: +0xc.0d25fp-4f,
    +7.5321000814e-01f,
    // x^ 2: +0xa.0fae8p-30f,
    +9.3702752224e-09f,
    // x^ 1: -0xf.52c49p-5f,
    -4.7885349393e-01f,
    // x^ 1: +0x8.4c868p-31f,
    +3.8644891731e-09f,
    // x^ 0: -0x8.6fe06p-8f,
    -3.2957099378e-02f,
    // x^ 0: -0xf.ba0a8p-34f,
    -9.1541574321e-10f,
    // 1.09375:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-44.125
    // x^ 5: -0x8.916c6p-6f,
    -1.3387593627e-01f,
    // x^ 4: +0xc.4ce9cp-6f,
    +1.9219440222e-01f,
    // x^ 3: -0xa.14708p-5f,
    -3.1499505043e-01f,
    // x^ 2: +0xb.8f67bp-4f,
    +7.2251099348e-01f,
    // x^ 2: +0xc.b9195p-29f,
    +2.3698513374e-08f,
    // x^ 1: -0xd.d915bp-5f,
    -4.3274959922e-01f,
    // x^ 1: -0x9.09644p-32f,
    -2.1040174047e-09f,
    // x^ 0: -0xc.1507ep-8f,
    -4.7195903957e-02f,
    // x^ 0: +0xa.90486p-33f,
    +1.2297654006e-09f,
    // 1.125:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-44.484375
    // x^ 5: -0xe.ecf45p-7f,
    -1.1660627276e-01f,
    // x^ 4: +0xb.0d147p-6f,
    +1.7267332971e-01f,
    // x^ 3: -0x9.59e41p-5f,
    -2.9222300649e-01f,
    // x^ 2: +0xb.1ae5bp-4f,
    +6.9406670332e-01f,
    // x^ 2: +0x8.c69fap-29f,
    +1.6346337617e-08f,
    // x^ 1: -0xc.6e883p-5f,
    -3.8849267364e-01f,
    // x^ 1: +0xb.19f4fp-30f,
    +1.0338978562e-08f,
    // x^ 0: -0xf.5dadfp-8f,
    -6.0023184866e-02f,
    // x^ 0: +0xc.b549ap-34f,
    +7.3971195835e-10f,
    // 1.15625:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-44.609375
    // x^ 5: -0xd.10e65p-7f,
    -1.0207823664e-01f,
    // x^ 4: +0x9.f5cf1p-6f,
    +1.5562798083e-01f,
    // x^ 3: -0x8.b2062p-5f,
    -2.7173143625e-01f,
    // x^ 2: +0xa.aeafbp-4f,
    +6.6764801741e-01f,
    // x^ 2: -0xf.51405p-29f,
    -2.8530857676e-08f,
    // x^ 1: -0xb.1203dp-5f,
    -3.4594908357e-01f,
    // x^ 1: +0xf.02f3p-33f,
    +1.7475709768e-09f,
    // x^ 0: -0x9.26bbap-7f,
    -7.1494534612e-02f,
    // x^ 0: -0xa.4e326p-32f,
    -2.3994259912e-09f,
    // 1.1875:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-45
    // x^ 5: -0xb.770bcp-7f,
    -8.9570492506e-02f,
    // x^ 4: +0x9.01047p-6f,
    +1.4068709314e-01f,
    // x^ 3: -0x8.1a805p-5f,
    -2.5323501229e-01f,
    // x^ 2: +0xa.49f3dp-4f,
    +6.4305478334e-01f,
    // x^ 2: -0x8.82f62p-29f,
    -1.5854030977e-08f,
    // x^ 1: -0x9.c28c8p-5f,
    -3.0499863625e-01f,
    // x^ 1: -0xe.cfb7p-30f,
    -1.3794178244e-08f,
    // x^ 0: -0xa.73e31p-7f,
    -8.1661589444e-02f,
    // x^ 0: -0xf.3e817p-32f,
    -3.5493081807e-09f,
    // 1.21875:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-45.140625
    // x^ 5: -0xa.1bdfap-7f,
    -7.8975632787e-02f,
    // x^ 4: +0x8.29a99p-6f,
    +1.2754286826e-01f,
    // x^ 3: -0xf.22a92p-6f,
    -2.3649051785e-01f,
    // x^ 2: +0x9.ebfa4p-4f,
    +6.2011170387e-01f,
    // x^ 2: +0x8.76454p-30f,
    +7.8808461978e-09f,
    // x^ 1: -0x8.7f3edp-5f,
    -2.6553288102e-01f,
    // x^ 1: +0x9.edbe6p-30f,
    +9.2468095403e-09f,
    // x^ 0: -0xb.97e08p-7f,
    -9.0572416782e-02f,
    // x^ 0: +0xb.0415cp-32f,
    +2.5648523305e-09f,
    // 1.25:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-45.34375
    // x^ 5: -0x8.f0937p-7f,
    -6.9841794670e-02f,
    // x^ 4: +0xe.d7188p-7f,
    +1.1593919992e-01f,
    // x^ 3: -0xe.299d7p-6f,
    -2.2128997743e-01f,
    // x^ 2: +0x9.94215p-4f,
    +5.9866458178e-01f,
    // x^ 2: -0xc.f5858p-31f,
    -6.0345364261e-09f,
    // x^ 1: -0xe.8e994p-6f,
    -2.2745352983e-01f,
    // x^ 1: -0xf.36bcp-32f,
    -3.5422402789e-09f,
    // x^ 0: -0xc.942bfp-7f,
    -9.8271839321e-02f,
    // x^ 0: +0xc.73568p-32f,
    +2.8988669243e-09f,
    // 1.28125:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-45.65625
    // x^ 5: -0xf.dac66p-8f,
    -6.1931990087e-02f,
    // x^ 4: +0xd.86536p-7f,
    +1.0566179454e-01f,
    // x^ 3: -0xd.46effp-6f,
    -2.0745466650e-01f,
    // x^ 2: +0x9.41da3p-4f,
    +5.7857722044e-01f,
    // x^ 2: -0xa.27a1ap-29f,
    -1.8914807498e-08f,
    // x^ 1: -0xc.33f63p-6f,
    -1.9067148864e-01f,
    // x^ 1: +0xe.35f12p-31f,
    +6.6173777569e-09f,
    // x^ 0: -0xd.6a25p-7f,
    -1.0480177402e-01f,
    // x^ 0: +0xe.58dc1p-32f,
    +3.3404463640e-09f,
    // 1.3125:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-45.75
    // x^ 5: -0xe.1d8bdp-8f,
    -5.5138338357e-02f,
    // x^ 4: +0xc.5b1c9p-7f,
    +9.6530504525e-02f,
    // x^ 3: -0xc.7819fp-6f,
    -1.9483040273e-01f,
    // x^ 2: +0x8.f4a66p-4f,
    +5.5972898006e-01f,
    // x^ 2: +0xb.7a72p-29f,
    +2.1380003545e-08f,
    // x^ 1: -0x9.ed3ffp-6f,
    -1.5510557592e-01f,
    // x^ 1: -0xa.0299p-35f,
    -2.9133362389e-10f,
    // x^ 0: -0xe.1b14fp-7f,
    -1.1020147055e-01f,
    // x^ 0: +0xd.7d9acp-34f,
    +7.8525874692e-10f,
    // 1.34375:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-46.046875
    // x^ 5: -0xc.97773p-8f,
    -4.9186181277e-02f,
    // x^ 4: +0xb.5079p-7f,
    +8.8393330574e-02f,
    // x^ 3: -0xb.baebdp-6f,
    -1.8328376114e-01f,
    // x^ 2: +0x8.ac15bp-4f,
    +5.4201287031e-01f,
    // x^ 2: -0xf.038d5p-29f,
    -2.7965521454e-08f,
    // x^ 1: -0xf.72802p-7f,
    -1.2068177760e-01f,
    // x^ 1: -0xc.e276fp-32f,
    -2.9999360773e-09f,
    // x^ 0: -0xe.a830cp-7f,
    -1.1450776458e-01f,
    // x^ 0: +0xa.233a8p-34f,
    +5.9008664621e-10f,
    // 1.375:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-46.171875
    // x^ 5: -0xb.436f9p-8f,
    -4.3997738510e-02f,
    // x^ 4: +0xa.622fdp-7f,
    +8.1121422350e-02f,
    // x^ 3: -0xb.0d7f2p-6f,
    -1.7269876599e-01f,
    // x^ 2: +0x8.67c3ep-4f,
    +5.2533328533e-01f,
    // x^ 2: -0xd.9f22fp-29f,
    -2.5372257184e-08f,
    // x^ 1: -0xb.2db52p-7f,
    -8.7332382798e-02f,
    // x^ 1: +0xa.fefe8p-35f,
    +3.2002778205e-10f,
    // x^ 0: -0xf.129adp-7f,
    -1.1775527149e-01f,
    // x^ 0: +0xc.f124cp-34f,
    +7.5332162730e-10f,
    // 1.40625:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-46.453125
    // x^ 5: -0xa.1c651p-8f,
    -3.9495769888e-02f,
    // x^ 4: +0x9.8ca8dp-7f,
    +7.4605084956e-02f,
    // x^ 3: -0xa.6e2bdp-6f,
    -1.6297431290e-01f,
    // x^ 2: +0x8.27578p-4f,
    +5.0960493088e-01f,
    // x^ 2: +0xf.c351p-30f,
    +1.4680395566e-08f,
    // x^ 1: -0xe.142c3p-8f,
    -5.4995309561e-02f,
    // x^ 1: -0xc.cf57fp-33f,
    -1.4912727719e-09f,
    // x^ 0: -0xf.5b648p-7f,
    -1.1997658014e-01f,
    // x^ 0: -0x9.2fefp-33f,
    -1.0695355712e-09f,
    // 1.4375:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-46.484375
    // x^ 5: -0x9.19a5cp-8f,
    -3.5547599196e-02f,
    // x^ 4: +0x8.ccd29p-7f,
    +6.8750686944e-02f,
    // x^ 3: -0x9.db7f1p-6f,
    -1.5402199328e-01f,
    // x^ 2: +0xf.d501p-5f,
    +4.9475145340e-01f,
    // x^ 2: +0xa.7d87cp-31f,
    +4.8849511103e-09f,
    // x^ 1: -0xc.17131p-9f,
    -2.3613544181e-02f,
    // x^ 1: +0xc.0acfcp-36f,
    +1.7523754670e-10f,
    // x^ 0: -0xf.838fap-7f,
    -1.2120242417e-01f,
    // x^ 0: -0xd.03fd6p-32f,
    -3.0304270204e-09f,
    // 1.46875:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-46.6875
    // x^ 5: -0x8.328ebp-8f,
    -3.2021444291e-02f,
    // x^ 4: +0x8.200b9p-7f,
    +6.3477940857e-02f,
    // x^ 3: -0x9.54339p-6f,
    -1.4576424658e-01f,
    // x^ 2: +0xf.61edap-5f,
    +4.8070412874e-01f,
    // x^ 2: -0xe.3adap-32f,
    -3.3131541954e-09f,
    // x^ 1: +0xe.0f73fp-11f,
    +6.8654115312e-03f,
    // x^ 1: -0x8.44662p-37f,
    -6.0151675307e-11f,
    // x^ 0: -0xf.8c0fbp-7f,
    -1.2146183103e-01f,
    // x^ 0: +0xf.4f6d8p-35f,
    +4.4558734480e-10f,
    // 1.5:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-46.78125
    // x^ 5: -0xe.d050fp-9f,
    -2.8933076188e-02f,
    // x^ 4: +0xf.0820fp-8f,
    +5.8717783540e-02f,
    // x^ 3: -0x8.d72aep-6f,
    -1.3813278079e-01f,
    // x^ 2: +0xe.f4f32p-5f,
    +4.6740108728e-01f,
    // x^ 2: +0xd.63897p-30f,
    +1.2469306476e-08f,
    // x^ 1: +0x9.57683p-8f,
    +3.6489974707e-02f,
    // x^ 1: -0xc.83398p-34f,
    -7.2832895270e-10f,
    // x^ 0: -0xf.75caep-7f,
    -1.2078224123e-01f,
    // x^ 0: +0xf.6b407p-32f,
    +3.5900045159e-09f,
    // 1.53125:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-47.140625
    // x^ 5: -0xd.6e7b4p-9f,
    -2.6233531535e-02f,
    // x^ 4: +0xd.edda4p-8f,
    +5.4410591722e-02f,
    // x^ 3: -0x8.63685p-6f,
    -1.3106735051e-01f,
    // x^ 2: +0xe.8d9c8p-5f,
    +4.5478653908e-01f,
    // x^ 2: +0xa.4e152p-30f,
    +9.5972882974e-09f,
    // x^ 1: +0x8.5be92p-7f,
    +6.5304890275e-02f,
    // x^ 1: -0xe.e208cp-33f,
    -1.7326029500e-09f,
    // x^ 0: -0xf.419b3p-7f,
    -1.1918964237e-01f,
    // x^ 0: +0xa.a0579p-32f,
    +2.4741366733e-09f,
    // 1.5625:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-47.296875
    // x^ 5: -0xc.30703p-9f,
    -2.3807054386e-02f,
    // x^ 4: +0xc.ede17p-8f,
    +5.0504770130e-02f,
    // x^ 3: -0xf.f018cp-7f,
    -1.2451466918e-01f,
    // x^ 2: +0xe.2b7fdp-5f,
    +4.4280996919e-01f,
    // x^ 2: -0xf.bccf8p-30f,
    -1.4656727387e-08f,
    // x^ 1: +0xb.f2f1dp-7f,
    +9.3351580203e-02f,
    // x^ 1: -0xa.79dep-37f,
    -7.6223249934e-11f,
    // x^ 0: -0xe.f04f6p-7f,
    -1.1670868099e-01f,
    // x^ 0: -0xa.482dep-32f,
    -2.3939530358e-09f,
    // 1.59375:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-47.46875
    // x^ 5: -0xb.17917p-9f,
    -2.1664185449e-02f,
    // x^ 4: +0xc.05469p-8f,
    +4.6955499798e-02f,
    // x^ 3: -0xf.28a14p-7f,
    -1.1842742562e-01f,
    // x^ 2: +0xd.ce3cep-5f,
    +4.3142551184e-01f,
    // x^ 2: -0xc.f211cp-32f,
    -3.0141285023e-09f,
    // x^ 1: +0xf.72107p-7f,
    +1.2066846341e-01f,
    // x^ 1: +0xd.007eap-32f,
    +3.0272482299e-09f,
    // x^ 0: -0xe.82abdp-7f,
    -1.1336276680e-01f,
    // x^ 0: -0x9.0e40cp-34f,
    -5.2710968923e-10f,
    // 1.625:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-47.59375
    // x^ 5: -0xa.1c792p-9f,
    -1.9748482853e-02f,
    // x^ 4: +0xb.317afp-8f,
    +4.3723758310e-02f,
    // x^ 3: -0xe.6f095p-7f,
    -1.1276356131e-01f,
    // x^ 2: +0xd.757c8p-5f,
    +4.2059159279e-01f,
    // x^ 2: -0xe.2987p-31f,
    -6.5947958205e-09f,
    // x^ 1: +0x9.6d383p-6f,
    +1.4729122818e-01f,
    // x^ 1: +0xf.90b25p-31f,
    +7.2481207702e-09f,
    // x^ 0: -0xd.f96bp-7f,
    -1.0917413235e-01f,
    // x^ 0: -0xc.1bed8p-33f,
    -1.4096839251e-09f,
    // 1.65625:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-47.703125
    // x^ 5: -0x9.3bfe2p-9f,
    -1.8035832793e-02f,
    // x^ 4: +0xa.70423p-8f,
    +4.0775429457e-02f,
    // x^ 3: -0xd.c2165p-7f,
    -1.0748557001e-01f,
    // x^ 2: +0xd.20ef2p-5f,
    +4.1027027369e-01f,
    // x^ 2: +0xd.92695p-30f,
    +1.2639834956e-08f,
    // x^ 1: +0xb.16942p-6f,
    +1.7325308919e-01f,
    // x^ 1: +0xc.71e7p-32f,
    +2.8975613020e-09f,
    // x^ 0: -0xd.553e9p-7f,
    -1.0416395217e-01f,
    // x^ 0: +0xe.55e4cp-32f,
    +3.3377487441e-09f,
    // 1.6875:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-47.984375
    // x^ 5: -0x8.719adp-9f,
    -1.6491735354e-02f,
    // x^ 4: +0x9.bfa7ep-8f,
    +3.8080684841e-02f,
    // x^ 3: -0xd.20af2p-7f,
    -1.0255993903e-01f,
    // x^ 2: +0xc.d04c6p-5f,
    +4.0042704344e-01f,
    // x^ 2: -0xa.51e58p-30f,
    -9.6111634207e-09f,
    // x^ 1: +0xc.b59dcp-6f,
    +1.9858497381e-01f,
    // x^ 1: +0xa.15e2p-31f,
    +4.6964174771e-09f,
    // x^ 0: -0xc.96cf9p-7f,
    -9.8352380097e-02f,
    // x^ 0: +0xd.68dbdp-32f,
    +3.1221667474e-09f,
    // 1.71875:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-48.046875
    // x^ 5: -0xf.7b7fep-10f,
    -1.5119550750e-02f,
    // x^ 4: +0x9.1df3fp-8f,
    +3.5613294691e-02f,
    // x^ 3: -0xc.89d7ep-7f,
    -9.7956642509e-02f,
    // x^ 2: +0xc.8351dp-5f,
    +3.9103022218e-01f,
    // x^ 2: +0xc.4d00cp-31f,
    +5.7280029608e-09f,
    // x^ 1: +0xe.4ace4p-6f,
    +2.2331577539e-01f,
    // x^ 1: -0xa.938cbp-31f,
    -4.9250039602e-09f,
    // x^ 0: -0xb.bebf5p-7f,
    -9.1758646071e-02f,
    // x^ 0: -0xa.195a4p-32f,
    -2.3513644365e-09f,
    // 1.75:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-48.234375
    // x^ 5: -0xe.3471ap-10f,
    -1.3871932402e-02f,
    // x^ 4: +0x8.89a37p-8f,
    +3.3350195736e-02f,
    // x^ 3: -0xb.fcaeap-7f,
    -9.3648746610e-02f,
    // x^ 2: +0xc.39c2ep-5f,
    +3.8205093145e-01f,
    // x^ 2: +0xe.197dp-32f,
    +3.2828104679e-09f,
    // x^ 1: +0xf.d696bp-6f,
    +2.4747245014e-01f,
    // x^ 1: +0xe.a514ep-32f,
    +3.4097697998e-09f,
    // x^ 0: -0xa.cda7fp-7f,
    -8.4401123226e-02f,
    // x^ 0: +0x9.78a66p-32f,
    +2.2052062398e-09f,
    // 1.78125:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-48.125
    // x^ 5: -0xd.0cd7p-10f,
    -1.2744292617e-02f,
    // x^ 4: +0x8.0160bp-8f,
    +3.1271021813e-02f,
    // x^ 3: -0xb.78681p-7f,
    -8.9612014592e-02f,
    // x^ 2: +0xb.f367ep-5f,
    +3.7346261740e-01f,
    // x^ 2: -0xb.81ecp-34f,
    -6.6982508429e-10f,
    // x^ 1: +0x8.acb09p-5f,
    +2.7108028531e-01f,
    // x^ 1: -0x8.eae48p-31f,
    -4.1525574090e-09f,
    // x^ 0: -0x9.c41c7p-7f,
    -7.6297335327e-02f,
    // x^ 0: -0xc.62c7p-33f,
    -1.4419025973e-09f,
    // 1.8125:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-48.359375
    // x^ 5: -0xc.05d35p-10f,
    -1.1740972288e-02f,
    // x^ 4: +0xf.07fb1p-9f,
    +2.9357763007e-02f,
    // x^ 3: -0xa.fc4cfp-7f,
    -8.5824601352e-02f,
    // x^ 2: +0xb.b00dbp-5f,
    +3.6524090171e-01f,
    // x^ 2: -0x8.ace4fp-30f,
    -8.0795663493e-09f,
    // x^ 1: +0x9.69c86p-5f,
    +2.9416292906e-01f,
    // x^ 1: -0xd.4342p-30f,
    -1.2351875966e-08f,
    // x^ 0: -0x8.a2a9bp-7f,
    -6.7464075983e-02f,
    // x^ 0: +0x9.d6debp-32f,
    +2.2908988040e-09f,
    // 1.84375:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-48.609375
    // x^ 5: -0xb.1796bp-10f,
    -1.0832170956e-02f,
    // x^ 4: +0xe.20dd1p-9f,
    +2.7594478801e-02f,
    // x^ 3: -0xa.87b7ep-7f,
    -8.2266792655e-02f,
    // x^ 2: +0xb.6f854p-5f,
    +3.5736334324e-01f,
    // x^ 2: -0xc.d9edbp-30f,
    -1.1968690039e-08f,
    // x^ 1: +0xa.22c15p-5f,
    +3.1674256921e-01f,
    // x^ 1: -0x8.15ae5p-30f,
    -7.5294552815e-09f,
    // x^ 0: -0xe.d3acap-8f,
    -5.7917393744e-02f,
    // x^ 0: +0x8.a3234p-35f,
    +2.5137725235e-10f,
    // 1.875:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-48.53125
    // x^ 5: -0xa.3d433p-10f,
    -9.9993227050e-03f,
    // x^ 4: +0xd.4b8acp-9f,
    +2.5966964662e-02f,
    // x^ 3: -0xa.1a134p-7f,
    -7.8920751810e-02f,
    // x^ 2: +0xb.31a33p-5f,
    +3.4980925918e-01f,
    // x^ 2: -0xa.6659cp-31f,
    -4.8427875043e-09f,
    // x^ 1: +0xa.d7c72p-5f,
    +3.3884006739e-01f,
    // x^ 1: +0x8.6cb3p-31f,
    +3.9230130255e-09f,
    // x^ 0: -0xc.3446fp-8f,
    -4.7672685236e-02f,
    // x^ 0: -0xb.3b67p-36f,
    -1.6344769982e-10f,
    // 1.90625:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-48.9375
    // x^ 5: -0x9.7b442p-10f,
    -9.2592854053e-03f,
    // x^ 4: +0xc.865dep-9f,
    +2.4462636560e-02f,
    // x^ 3: -0x9.b2d76p-7f,
    -7.5770303607e-02f,
    // x^ 2: +0xa.f63f8p-5f,
    +3.4255957603e-01f,
    // x^ 2: +0x8.83bc8p-31f,
    +3.9649172834e-09f,
    // x^ 1: +0xb.8903p-5f,
    +3.6047506332e-01f,
    // x^ 1: -0x8.d75f6p-31f,
    -4.1170507004e-09f,
    // x^ 0: -0x9.6819ep-8f,
    -3.6744706333e-02f,
    // x^ 0: -0x8.3edap-35f,
    -2.3997603904e-10f,
    // 1.9375:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-48.5
    // x^ 5: -0x8.c3d92p-10f,
    -8.5596013814e-03f,
    // x^ 4: +0xb.cfdacp-9f,
    +2.3070178926e-02f,
    // x^ 3: -0x9.51894p-7f,
    -7.2800785303e-02f,
    // x^ 2: +0xa.bd354p-5f,
    +3.3559668064e-01f,
    // x^ 2: -0xb.7d0d5p-30f,
    -1.0699484854e-08f,
    // x^ 1: +0xc.369bap-5f,
    +3.8166600466e-01f,
    // x^ 1: -0xd.6840dp-30f,
    -1.2486464307e-08f,
    // x^ 0: -0xc.e0261p-9f,
    -2.5147618726e-02f,
    // x^ 0: -0xb.a1e15p-34f,
    -6.7709154949e-10f,
    // 1.96875:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-48.328125
    // x^ 5: -0x8.1f697p-10f,
    -7.9323267564e-03f,
    // x^ 4: +0xb.26b11p-9f,
    +2.1779568866e-02f,
    // x^ 3: -0x8.f5b8dp-7f,
    -6.9998838007e-02f,
    // x^ 2: +0xa.86622p-5f,
    +3.2890421152e-01f,
    // x^ 2: -0xe.4639fp-30f,
    -1.3293997903e-08f,
    // x^ 1: +0xc.e0b57p-5f,
    +4.0243026614e-01f,
    // x^ 1: +0xa.df66ep-30f,
    +1.0125956962e-08f,
    // x^ 0: -0xd.345a9p-10f,
    -1.2895026244e-02f,
    // x^ 0: +0x9.12abp-35f,
    +2.6405677644e-10f,
    // 2:     // [-1.5625e-2, 0] : | p - f | <= 2^-53.390625
    // x^ 5: -0xf.5c01bp-11f,
    -7.4997073971e-03f,
    // x^ 4: +0xa.895ccp-9f,
    +2.0579241216e-02f,
    // x^ 3: -0x8.9f002p-7f,
    -6.7352309823e-02f,
    // x^ 2: +0xa.51a66p-5f,
    +3.2246702909e-01f,
    // x^ 2: +0x9.42b1p-31f,
    +4.3122625470e-09f,
    // x^ 1: +0xd.8773p-5f,
    +4.2278432846e-01f,
    // x^ 1: +0xe.4126ep-31f,
    +6.6377685570e-09f,
    // x^ 0: +0x0p+0f,
    +0.0000000000e+00f,
    // x^ 0: +0x0p+0f,
    +0.0000000000e+00f
};