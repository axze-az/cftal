//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/math/func_data.h"

template <>
const
cftal::math::log_data<float>::table_t
cftal::math::log_data<float>::_tbl={
// static const float invc[64]=
{
    // 0
    // +1.4062500000e+00f
    +0xb.4p-3f,
    // 1
    // +1.3906250000e+00f
    +0xb.2p-3f,
    // 2
    // +1.3750000000e+00f
    +0xbp-3f,
    // 3
    // +1.3593750000e+00f
    +0xa.ep-3f,
    // 4
    // +1.3437500000e+00f
    +0xa.cp-3f,
    // 5
    // +1.3281250000e+00f
    +0xa.ap-3f,
    // 6
    // +1.3125000000e+00f
    +0xa.8p-3f,
    // 7
    // +1.3125000000e+00f
    +0xa.8p-3f,
    // 8
    // +1.2968750000e+00f
    +0xa.6p-3f,
    // 9
    // +1.2812500000e+00f
    +0xa.4p-3f,
    // 10
    // +1.2656250000e+00f
    +0xa.2p-3f,
    // 11
    // +1.2500000000e+00f
    +0xap-3f,
    // 12
    // +1.2500000000e+00f
    +0xap-3f,
    // 13
    // +1.2343750000e+00f
    +0x9.ep-3f,
    // 14
    // +1.2187500000e+00f
    +0x9.cp-3f,
    // 15
    // +1.2031250000e+00f
    +0x9.ap-3f,
    // 16
    // +1.2031250000e+00f
    +0x9.ap-3f,
    // 17
    // +1.1875000000e+00f
    +0x9.8p-3f,
    // 18
    // +1.1718750000e+00f
    +0x9.6p-3f,
    // 19
    // +1.1562500000e+00f
    +0x9.4p-3f,
    // 20
    // +1.1562500000e+00f
    +0x9.4p-3f,
    // 21
    // +1.1406250000e+00f
    +0x9.2p-3f,
    // 22
    // +1.1250000000e+00f
    +0x9p-3f,
    // 23
    // +1.1250000000e+00f
    +0x9p-3f,
    // 24
    // +1.1093750000e+00f
    +0x8.ep-3f,
    // 25
    // +1.1093750000e+00f
    +0x8.ep-3f,
    // 26
    // +1.0937500000e+00f
    +0x8.cp-3f,
    // 27
    // +1.0781250000e+00f
    +0x8.ap-3f,
    // 28
    // +1.0781250000e+00f
    +0x8.ap-3f,
    // 29
    // +1.0625000000e+00f
    +0x8.8p-3f,
    // 30
    // +1.0625000000e+00f
    +0x8.8p-3f,
    // 31
    // +1.0468750000e+00f
    +0x8.6p-3f,
    // 32
    // +1.0468750000e+00f
    +0x8.6p-3f,
    // 33
    // +1.0312500000e+00f
    +0x8.4p-3f,
    // 34
    // +1.0312500000e+00f
    +0x8.4p-3f,
    // 35
    // +1.0156250000e+00f
    +0x8.2p-3f,
    // 36
    // +1.0156250000e+00f
    +0x8.2p-3f,
    // 37
    // +1.0000000000e+00f
    +0x8p-3f,
    // 38
    // +9.9218750000e-01f
    +0xf.ep-4f,
    // 39
    // +9.7656250000e-01f
    +0xf.ap-4f,
    // 40
    // +9.6093750000e-01f
    +0xf.6p-4f,
    // 41
    // +9.4531250000e-01f
    +0xf.2p-4f,
    // 42
    // +9.3750000000e-01f
    +0xfp-4f,
    // 43
    // +9.2187500000e-01f
    +0xe.cp-4f,
    // 44
    // +9.0625000000e-01f
    +0xe.8p-4f,
    // 45
    // +8.9843750000e-01f
    +0xe.6p-4f,
    // 46
    // +8.8281250000e-01f
    +0xe.2p-4f,
    // 47
    // +8.6718750000e-01f
    +0xd.ep-4f,
    // 48
    // +8.5937500000e-01f
    +0xd.cp-4f,
    // 49
    // +8.5156250000e-01f
    +0xd.ap-4f,
    // 50
    // +8.3593750000e-01f
    +0xd.6p-4f,
    // 51
    // +8.2812500000e-01f
    +0xd.4p-4f,
    // 52
    // +8.1250000000e-01f
    +0xdp-4f,
    // 53
    // +8.0468750000e-01f
    +0xc.ep-4f,
    // 54
    // +7.9687500000e-01f
    +0xc.cp-4f,
    // 55
    // +7.8906250000e-01f
    +0xc.ap-4f,
    // 56
    // +7.7343750000e-01f
    +0xc.6p-4f,
    // 57
    // +7.6562500000e-01f
    +0xc.4p-4f,
    // 58
    // +7.5781250000e-01f
    +0xc.2p-4f,
    // 59
    // +7.5000000000e-01f
    +0xcp-4f,
    // 60
    // +7.4218750000e-01f
    +0xb.ep-4f,
    // 61
    // +7.3437500000e-01f
    +0xb.cp-4f,
    // 62
    // +7.2656250000e-01f
    +0xb.ap-4f,
    // 63
    // +7.1875000000e-01f
    +0xb.8p-4f
},
// static const float logc_h[64]=
{
    // 0
    // -3.4092658758e-01f
    -0xa.e8deep-5f,
    // 1
    // -3.2975327969e-01f
    -0xa.8d56cp-5f,
    // 2
    // -3.1845372915e-01f
    -0xa.30c5ep-5f,
    // 3
    // -3.0702504516e-01f
    -0x9.d3263p-5f,
    // 4
    // -2.9546421766e-01f
    -0x9.74716p-5f,
    // 5
    // -2.8376817703e-01f
    -0x9.14a1p-5f,
    // 6
    // -2.7193370461e-01f
    -0x8.b3ae5p-5f,
    // 7
    // -2.7193370461e-01f
    -0x8.b3ae5p-5f,
    // 8
    // -2.5995752215e-01f
    -0x8.51927p-5f,
    // 9
    // -2.4783615768e-01f
    -0xf.dc8c3p-6f,
    // 10
    // -2.3556606472e-01f
    -0xf.1383bp-6f,
    // 11
    // -2.2314354777e-01f
    -0xe.47fbep-6f,
    // 12
    // -2.2314354777e-01f
    -0xe.47fbep-6f,
    // 13
    // -2.1056476235e-01f
    -0xd.79e4ap-6f,
    // 14
    // -1.9782574475e-01f
    -0xc.a92d5p-6f,
    // 15
    // -1.8492233753e-01f
    -0xb.d5c48p-6f,
    // 16
    // -1.8492233753e-01f
    -0xb.d5c48p-6f,
    // 17
    // -1.7185026407e-01f
    -0xa.ff984p-6f,
    // 18
    // -1.5860502422e-01f
    -0xa.2695bp-6f,
    // 19
    // -1.4518201351e-01f
    -0x9.4aa98p-6f,
    // 20
    // -1.4518201351e-01f
    -0x9.4aa98p-6f,
    // 21
    // -1.3157635927e-01f
    -0x8.6bbf4p-6f,
    // 22
    // -1.1778303236e-01f
    -0xf.1383bp-7f,
    // 23
    // -1.1778303236e-01f
    -0xf.1383bp-7f,
    // 24
    // -1.0379679501e-01f
    -0xd.4936ap-7f,
    // 25
    // -1.0379679501e-01f
    -0xd.4936ap-7f,
    // 26
    // -8.9612156153e-02f
    -0xb.78694p-7f,
    // 27
    // -7.5223423541e-02f
    -0x9.a0ebdp-7f,
    // 28
    // -7.5223423541e-02f
    -0x9.a0ebdp-7f,
    // 29
    // -6.0624621809e-02f
    -0xf.85186p-8f,
    // 30
    // -6.0624621809e-02f
    -0xf.85186p-8f,
    // 31
    // -4.5809537172e-02f
    -0xb.ba2c8p-8f,
    // 32
    // -4.5809537172e-02f
    -0xb.ba2c8p-8f,
    // 33
    // -3.0771657825e-02f
    -0xf.c14d8p-9f,
    // 34
    // -3.0771657825e-02f
    -0xf.c14d8p-9f,
    // 35
    // -1.5504186973e-02f
    -0xf.e0546p-10f,
    // 36
    // -1.5504186973e-02f
    -0xf.e0546p-10f,
    // 37
    // +0.0000000000e+00f
    +0x0p+0f,
    // 38
    // +7.8431777656e-03f
    +0x8.080acp-10f,
    // 39
    // +2.3716526106e-02f
    +0xc.24929p-9f,
    // 40
    // +3.9845909923e-02f
    +0xa.33577p-8f,
    // 41
    // +5.6239716709e-02f
    +0xe.65b9ep-8f,
    // 42
    // +6.4538523555e-02f
    +0x8.42cc6p-7f,
    // 43
    // +8.1345640123e-02f
    +0xa.6988bp-7f,
    // 44
    // +9.8440073431e-02f
    +0xc.99af3p-7f,
    // 45
    // +1.0709813237e-01f
    +0xd.b5644p-7f,
    // 46
    // +1.2464244664e-01f
    +0xf.f448ap-7f,
    // 47
    // +1.4250005782e-01f
    +0x9.1eb89p-6f,
    // 48
    // +1.5154990554e-01f
    +0x9.b2fe6p-6f,
    // 49
    // +1.6068238020e-01f
    +0xa.489ecp-6f,
    // 50
    // +1.7920142412e-01f
    +0xb.78094p-6f,
    // 51
    // +1.8859116733e-01f
    +0xc.11e0bp-6f,
    // 52
    // +2.0763936639e-01f
    +0xd.49f6ap-6f,
    // 53
    // +2.1730127931e-01f
    +0xd.e843ap-6f,
    // 54
    // +2.2705745697e-01f
    +0xe.881cp-6f,
    // 55
    // +2.3690974712e-01f
    +0xf.29878p-6f,
    // 56
    // +2.5691041350e-01f
    +0x8.389c3p-5f,
    // 57
    // +2.6706278324e-01f
    +0x8.8bc74p-5f,
    // 58
    // +2.7731928229e-01f
    +0x8.dfccbp-5f,
    // 59
    // +2.8768208623e-01f
    +0x9.34b11p-5f,
    // 60
    // +2.9815337062e-01f
    +0x9.8a78fp-5f,
    // 61
    // +3.0873548985e-01f
    +0x9.e1294p-5f,
    // 62
    // +3.1943076849e-01f
    +0xa.38c6ep-5f,
    // 63
    // +3.3024168015e-01f
    +0xa.9157p-5f
},
// static const float logc_l[64]=
{
    // 0
    // +6.1104132865e-10f
    +0xa.7f636p-34f,
    // 1
    // -6.6864940251e-09f
    -0xe.5bf06p-31f,
    // 2
    // -1.9658552564e-09f
    -0x8.717b1p-32f,
    // 3
    // +9.8615666744e-09f
    +0xa.96ba1p-30f,
    // 4
    // +4.7689754368e-09f
    +0xa.3dc5ap-31f,
    // 5
    // +3.9018259734e-09f
    +0x8.610d3p-31f,
    // 6
    // -1.0869002587e-08f
    -0xb.aba61p-30f,
    // 7
    // -1.0869002587e-08f
    -0xb.aba61p-30f,
    // 8
    // -2.2830717317e-09f
    -0x9.ce439p-32f,
    // 9
    // -6.2250236077e-09f
    -0xd.5e3e3p-31f,
    // 10
    // -6.5973813079e-09f
    -0xe.2af2ep-31f,
    // 11
    // -3.5408485033e-09f
    -0xf.35344p-32f,
    // 12
    // -3.5408485033e-09f
    -0xf.35344p-32f,
    // 13
    // -6.7534524639e-09f
    -0xe.80bffp-31f,
    // 14
    // +1.4181956720e-09f
    +0xc.2ea53p-33f,
    // 15
    // -9.6196850485e-10f
    -0x8.43642p-33f,
    // 16
    // -9.6196850485e-10f
    -0x8.43642p-33f,
    // 17
    // +7.1457590956e-09f
    +0xf.586c3p-31f,
    // 18
    // -5.9580793632e-09f
    -0xc.cb7d2p-31f,
    // 19
    // +3.6671599091e-09f
    +0xf.c015cp-32f,
    // 20
    // +3.6671599091e-09f
    +0xf.c015cp-32f,
    // 21
    // +1.4832839401e-09f
    +0xc.bdc6ap-33f,
    // 22
    // -3.2986906540e-09f
    -0xe.2af2ep-32f,
    // 23
    // -3.2986906540e-09f
    -0xe.2af2ep-32f,
    // 24
    // +1.3289231937e-09f
    +0xb.6a554p-33f,
    // 25
    // +1.3289231937e-09f
    +0xb.6a554p-33f,
    // 26
    // -2.5369619738e-09f
    -0xa.e56b5p-32f,
    // 27
    // +2.3030046759e-09f
    +0x9.e42e3p-32f,
    // 28
    // +2.3030046759e-09f
    +0x9.e42e3p-32f,
    // 29
    // -7.9059423938e-12f
    -0x8.b1533p-40f,
    // 30
    // -7.9059423938e-12f
    -0x8.b1533p-40f,
    // 31
    // +1.1410232759e-09f
    +0x9.cd23p-33f,
    // 32
    // +1.1410232759e-09f
    +0x9.cd23p-33f,
    // 33
    // -8.4223739094e-10f
    -0xe.7833p-34f,
    // 34
    // -8.4223739094e-10f
    -0xe.7833p-34f,
    // 35
    // +4.3701048336e-10f
    +0xf.03fc2p-35f,
    // 36
    // +4.3701048336e-10f
    +0xf.03fc2p-35f,
    // 37
    // +0.0000000000e+00f
    +0x0p+0f,
    // 38
    // -3.0458194300e-10f
    -0xa.77219p-35f,
    // 39
    // +5.1131610057e-10f
    +0x8.c8cacp-34f,
    // 40
    // -1.3761153328e-09f
    -0xb.d21c1p-33f,
    // 41
    // +1.6142159831e-09f
    +0xd.ddb2dp-33f,
    // 42
    // -2.4172308599e-09f
    -0xa.61c6p-32f,
    // 43
    // -6.6893807160e-10f
    -0xb.7e055p-34f,
    // 44
    // -6.1728566703e-10f
    -0xa.9ad9ep-34f,
    // 45
    // +3.1844646919e-09f
    +0xd.ad5b2p-32f,
    // 46
    // -1.4298769946e-09f
    -0xc.48553p-33f,
    // 47
    // +4.7907775524e-09f
    +0xa.49c2p-31f,
    // 48
    // -7.4113581938e-09f
    -0xf.ea6ffp-31f,
    // 49
    // +1.4910410684e-09f
    +0xc.ced58p-33f,
    // 50
    // +5.3358544250e-09f
    +0xb.756acp-31f,
    // 51
    // +2.4768080920e-09f
    +0xa.a3478p-32f,
    // 52
    // -1.6100764055e-09f
    -0xd.d4987p-33f,
    // 53
    // -3.6164302664e-09f
    -0xf.884eap-32f,
    // 54
    // -6.3348686297e-09f
    -0xd.9aa18p-31f,
    // 55
    // -4.5360545181e-11f
    -0xc.77f6fp-38f,
    // 56
    // +2.8138039121e-10f
    +0x9.ab0c5p-35f,
    // 57
    // +2.0077732810e-09f
    +0x8.9f91fp-32f,
    // 58
    // +3.1229145936e-09f
    +0xd.69ae5p-32f,
    // 59
    // -1.3777543550e-08f
    -0xe.cb247p-30f,
    // 60
    // +1.7002561581e-09f
    +0xe.9ae72p-33f,
    // 61
    // -8.1956628151e-09f
    -0x8.ccce8p-30f,
    // 62
    // +2.2765236363e-09f
    +0x9.c7107p-32f,
    // 63
    // +6.7253131952e-09f
    +0xe.7147bp-31f
},
// static const float log2c_h[64]=
{
    // 0
    // -4.9185308814e-01f
    -0xf.bd42bp-5f,
    // 1
    // -4.7573342919e-01f
    -0xf.39355p-5f,
    // 2
    // -4.5943161845e-01f
    -0xe.b3a9fp-5f,
    // 3
    // -4.4294348359e-01f
    -0xe.2c97dp-5f,
    // 4
    // -4.2626476288e-01f
    -0xd.a3f6p-5f,
    // 5
    // -4.0939092636e-01f
    -0xd.19bbp-5f,
    // 6
    // -3.9231741428e-01f
    -0xc.8ddd4p-5f,
    // 7
    // -3.9231741428e-01f
    -0xc.8ddd4p-5f,
    // 8
    // -3.7503942847e-01f
    -0xc.0052bp-5f,
    // 9
    // -3.5755199194e-01f
    -0xb.7110ep-5f,
    // 10
    // -3.3985000849e-01f
    -0xa.e00d2p-5f,
    // 11
    // -3.2192808390e-01f
    -0xa.4d3c2p-5f,
    // 12
    // -3.2192808390e-01f
    -0xa.4d3c2p-5f,
    // 13
    // -3.0378073454e-01f
    -0x9.b8926p-5f,
    // 14
    // -2.8540220857e-01f
    -0x9.2203dp-5f,
    // 15
    // -2.6678654552e-01f
    -0x8.8983fp-5f,
    // 16
    // -2.6678654552e-01f
    -0x8.8983fp-5f,
    // 17
    // -2.4792751670e-01f
    -0xf.de0b6p-6f,
    // 18
    // -2.2881868482e-01f
    -0xe.a4f72p-6f,
    // 19
    // -2.0945335925e-01f
    -0xd.67af1p-6f,
    // 20
    // -2.0945335925e-01f
    -0xd.67af1p-6f,
    // 21
    // -1.8982456625e-01f
    -0xc.2615fp-6f,
    // 22
    // -1.6992500424e-01f
    -0xa.e00d2p-6f,
    // 23
    // -1.6992500424e-01f
    -0xa.e00d2p-6f,
    // 24
    // -1.4974711835e-01f
    -0x9.9574fp-6f,
    // 25
    // -1.4974711835e-01f
    -0x9.9574fp-6f,
    // 26
    // -1.2928301096e-01f
    -0x8.462c4p-6f,
    // 27
    // -1.0852445662e-01f
    -0xd.e4212p-7f,
    // 28
    // -1.0852445662e-01f
    -0xd.e4212p-7f,
    // 29
    // -8.7462842464e-02f
    -0xb.31fb8p-7f,
    // 30
    // -8.7462842464e-02f
    -0xb.31fb8p-7f,
    // 31
    // -6.6089190543e-02f
    -0x8.759c5p-7f,
    // 32
    // -6.6089190543e-02f
    -0x8.759c5p-7f,
    // 33
    // -4.4394120574e-02f
    -0xb.5d69cp-8f,
    // 34
    // -4.4394120574e-02f
    -0xb.5d69cp-8f,
    // 35
    // -2.2367812693e-02f
    -0xb.73cb4p-9f,
    // 36
    // -2.2367812693e-02f
    -0xb.73cb4p-9f,
    // 37
    // +0.0000000000e+00f
    +0x0p+0f,
    // 38
    // +1.1315313168e-02f
    +0xb.963ddp-10f,
    // 39
    // +3.4215714782e-02f
    +0x8.c25c7p-8f,
    // 40
    // +5.7485494763e-02f
    +0xe.b75e9p-8f,
    // 41
    // +8.1136763096e-02f
    +0xa.62b08p-7f,
    // 42
    // +9.3109406531e-02f
    +0xb.eb025p-7f,
    // 43
    // +1.1735694855e-01f
    +0xf.058d7p-7f,
    // 44
    // +1.4201900363e-01f
    +0x9.16d6ep-6f,
    // 45
    // +1.5450994670e-01f
    +0x9.e37dbp-6f,
    // 46
    // +1.7982104421e-01f
    +0xb.82302p-6f,
    // 47
    // +2.0558413863e-01f
    +0xd.284a6p-6f,
    // 48
    // +2.1864028275e-01f
    +0xd.fe33dp-6f,
    // 49
    // +2.3181568086e-01f
    +0xe.d6117p-6f,
    // 50
    // +2.5853300095e-01f
    +0x8.45e7p-5f,
    // 51
    // +2.7207955718e-01f
    +0x8.b4e03p-5f,
    // 52
    // +2.9956027865e-01f
    +0x9.95ff7p-5f,
    // 53
    // +3.1349948049e-01f
    +0xa.08301p-5f,
    // 54
    // +3.2757467031e-01f
    +0xa.7b7dep-5f,
    // 55
    // +3.4178853035e-01f
    +0xa.efee8p-5f,
    // 56
    // +3.7064337730e-01f
    +0xb.dc4f8p-5f,
    // 57
    // +3.8529014587e-01f
    +0xc.544cp-5f,
    // 58
    // +4.0008714795e-01f
    +0xc.cd839p-5f,
    // 59
    // +4.1503751278e-01f
    +0xd.47fccp-5f,
    // 60
    // +4.3014439940e-01f
    +0xd.c3be3p-5f,
    // 61
    // +4.4541114569e-01f
    +0xe.40ceep-5f,
    // 62
    // +4.6084117889e-01f
    +0xe.bf36p-5f,
    // 63
    // +4.7643804550e-01f
    +0xf.3efbp-5f
},
// static const float log2c_l[64]=
{
    // 0
    // -8.1891871062e-09f
    -0x8.cb06dp-30f,
    // 1
    // -1.7729010482e-09f
    -0xf.3aa69p-33f,
    // 2
    // -1.8522511303e-10f
    -0xc.ba83cp-36f,
    // 3
    // -1.2257648230e-08f
    -0xd.295b5p-30f,
    // 4
    // +8.1763200654e-09f
    +0x8.c77d6p-30f,
    // 5
    // -9.7766177376e-09f
    -0xa.7f605p-30f,
    // 6
    // -8.4950082524e-09f
    -0x9.1f171p-30f,
    // 7
    // -8.4950082524e-09f
    -0x9.1f171p-30f,
    // 8
    // -2.8744058245e-09f
    -0xc.58715p-32f,
    // 9
    // -1.2678539107e-08f
    -0xd.9d0cep-30f,
    // 10
    // +5.6030766693e-09f
    +0xc.0852fp-31f,
    // 11
    // -1.0990725663e-08f
    -0xb.cd1b9p-30f,
    // 12
    // -1.0990725663e-08f
    -0xb.cd1b9p-30f,
    // 13
    // -1.3638071117e-08f
    -0xe.a4cdfp-30f,
    // 14
    // -1.0295583053e-08f
    -0xb.0e074p-30f,
    // 15
    // +4.8201589387e-09f
    +0xa.59e91p-31f,
    // 16
    // +4.8201589387e-09f
    +0xa.59e91p-31f,
    // 17
    // +3.2552518459e-09f
    +0xd.fb2ffp-32f,
    // 18
    // -5.6795204095e-09f
    -0xc.32597p-31f,
    // 19
    // -6.3826957053e-09f
    -0xd.b4ec9p-31f,
    // 20
    // -6.3826957053e-09f
    -0xd.b4ec9p-31f,
    // 21
    // +7.3650618937e-09f
    +0xf.d0fc5p-31f,
    // 22
    // +2.8015383347e-09f
    +0xc.0852fp-32f,
    // 23
    // +2.8015383347e-09f
    +0xc.0852fp-32f,
    // 24
    // -1.1508384246e-09f
    -0x9.e2b87p-33f,
    // 25
    // -1.1508384246e-09f
    -0x9.e2b87p-33f,
    // 26
    // -5.9853411116e-09f
    -0xc.da79ep-31f,
    // 27
    // -1.5795267871e-10f
    -0xa.dabbap-36f,
    // 28
    // -1.5795267871e-10f
    -0xa.dabbap-36f,
    // 29
    // +1.2141075922e-09f
    +0xa.6dd9dp-33f,
    // 30
    // +1.2141075922e-09f
    +0xa.6dd9dp-33f,
    // 31
    // +8.4925476374e-11f
    +0xb.ac0cbp-37f,
    // 32
    // +8.4925476374e-11f
    +0xb.ac0cbp-37f,
    // 33
    // +1.2155441098e-09f
    +0xa.71028p-33f,
    // 34
    // +1.2155441098e-09f
    +0xa.71028p-33f,
    // 35
    // -3.3533545385e-10f
    -0xb.85a45p-35f,
    // 36
    // -3.3533545385e-10f
    -0xb.85a45p-35f,
    // 37
    // +0.0000000000e+00f
    +0x0p+0f,
    // 38
    // +5.9964103127e-11f
    +0x8.3dccap-37f,
    // 39
    // +5.5543653010e-10f
    +0x9.8ad5fp-34f,
    // 40
    // -1.0189894761e-10f
    -0xe.01402p-37f,
    // 41
    // -3.7045022605e-10f
    -0xc.ba83cp-35f,
    // 42
    // -2.1393755656e-09f
    -0x9.3044bp-32f,
    // 43
    // +2.0836428138e-09f
    +0x8.f2fd5p-32f,
    // 44
    // +1.2427434637e-09f
    +0xa.acd26p-33f,
    // 45
    // +2.3517139347e-09f
    +0xa.19bcap-32f,
    // 46
    // -6.6218071026e-09f
    -0xe.38608p-31f,
    // 47
    // -4.9819264270e-09f
    -0xa.b2d7dp-31f,
    // 48
    // +3.7252108065e-09f
    +0xf.ffe9ap-32f,
    // 49
    // -5.6383995251e-09f
    -0xc.1bbe3p-31f,
    // 50
    // +1.2652807690e-08f
    +0xd.95fa3p-30f,
    // 51
    // -1.1743603423e-08f
    -0xc.9c0eap-30f,
    // 52
    // +3.2048093068e-09f
    +0xd.c3b9ap-32f,
    // 53
    // -7.6691346607e-09f
    -0x8.3c136p-30f,
    // 54
    // -1.2286283990e-08f
    -0xd.313a6p-30f,
    // 55
    // -1.3101526086e-08f
    -0xe.1151fp-30f,
    // 56
    // +2.6163131661e-09f
    +0xb.3caabp-32f,
    // 57
    // +1.0010768214e-08f
    +0xa.bfbd3p-30f,
    // 58
    // +9.8617460864e-09f
    +0xa.96c6bp-30f,
    // 59
    // -1.3500391915e-08f
    -0xe.7ef5ap-30f,
    // 60
    // -7.7354735950e-09f
    -0x8.4e4f9p-30f,
    // 61
    // +2.6352593441e-09f
    +0xb.517f9p-32f,
    // 62
    // +9.9979260426e-09f
    +0xa.bc358p-30f,
    // 63
    // -1.5587218183e-09f
    -0xd.63aa6p-33f
},
// static const float log10c_h[64]=
{
    // 0
    // -1.4806254208e-01f
    -0x9.79db5p-6f,
    // 1
    // -1.4321003854e-01f
    -0x9.2a5a7p-6f,
    // 2
    // -1.3830269873e-01f
    -0x8.d9f39p-6f,
    // 3
    // -1.3333928585e-01f
    -0x8.88a18p-6f,
    // 4
    // -1.2831847370e-01f
    -0x8.365ebp-6f,
    // 5
    // -1.2323895097e-01f
    -0xf.c64b4p-7f,
    // 6
    // -1.1809930950e-01f
    -0xf.1de0dp-7f,
    // 7
    // -1.1809930950e-01f
    -0xf.1de0dp-7f,
    // 8
    // -1.1289811879e-01f
    -0xe.73721p-7f,
    // 9
    // -1.0763388127e-01f
    -0xd.c6f27p-7f,
    // 10
    // -1.0230504721e-01f
    -0xd.1854fp-7f,
    // 11
    // -9.6910014749e-02f
    -0xc.678c2p-7f,
    // 12
    // -9.6910014749e-02f
    -0xc.678c2p-7f,
    // 13
    // -9.1447114944e-02f
    -0xb.b48ap-7f,
    // 14
    // -8.5914626718e-02f
    -0xa.ff402p-7f,
    // 15
    // -8.0310754478e-02f
    -0xa.479f7p-7f,
    // 16
    // -8.0310754478e-02f
    -0xa.479f7p-7f,
    // 17
    // -7.4633620679e-02f
    -0x9.8d983p-7f,
    // 18
    // -6.8881288171e-02f
    -0x8.d11a2p-7f,
    // 19
    // -6.3051745296e-02f
    -0x8.12146p-7f,
    // 20
    // -6.3051745296e-02f
    -0x8.12146p-7f,
    // 21
    // -5.7142887264e-02f
    -0xe.a0ea9p-8f,
    // 22
    // -5.1152523607e-02f
    -0xd.1854fp-8f,
    // 23
    // -5.1152523607e-02f
    -0xd.1854fp-8f,
    // 24
    // -4.5078374445e-02f
    -0xb.8a41ap-8f,
    // 25
    // -4.5078374445e-02f
    -0xb.8a41ap-8f,
    // 26
    // -3.8918066770e-02f
    -0x9.f688dp-8f,
    // 27
    // -3.2669115812e-02f
    -0x8.5d00dp-8f,
    // 28
    // -3.2669115812e-02f
    -0x8.5d00dp-8f,
    // 29
    // -2.6328938082e-02f
    -0xd.7afc9p-9f,
    // 30
    // -2.6328938082e-02f
    -0xd.7afc9p-9f,
    // 31
    // -1.9894829020e-02f
    -0xa.2fa7bp-9f,
    // 32
    // -1.9894829020e-02f
    -0xa.2fa7bp-9f,
    // 33
    // -1.3363961130e-02f
    -0xd.af484p-10f,
    // 34
    // -1.3363961130e-02f
    -0xd.af484p-10f,
    // 35
    // -6.7333825864e-03f
    -0xd.ca3b5p-11f,
    // 36
    // -6.7333825864e-03f
    -0xd.ca3b5p-11f,
    // 37
    // +0.0000000000e+00f
    +0x0p+0f,
    // 38
    // +3.4062487539e-03f
    +0xd.f3b5fp-12f,
    // 39
    // +1.0299956426e-02f
    +0xa.8c126p-10f,
    // 40
    // +1.7304858193e-02f
    +0x8.dc2ebp-9f,
    // 41
    // +2.4424599484e-02f
    +0xc.81619p-9f,
    // 42
    // +2.8028722852e-02f
    +0xe.59c7ep-9f,
    // 43
    // +3.5327963531e-02f
    +0x9.0b40ep-8f,
    // 44
    // +4.2751979083e-02f
    +0xa.f1cb3p-8f,
    // 45
    // +4.6512130648e-02f
    +0xb.e8381p-8f,
    // 46
    // +5.4131526500e-02f
    +0xd.db905p-8f,
    // 47
    // +6.1886992306e-02f
    +0xf.d7d37p-8f,
    // 48
    // +6.5817281604e-02f
    +0x8.6cb36p-7f,
    // 49
    // +6.9783471525e-02f
    +0x8.eeaa3p-7f,
    // 50
    // +7.7826194465e-02f
    +0x9.f6357p-7f,
    // 51
    // +8.1904105842e-02f
    +0xa.7bd57p-7f,
    // 52
    // +9.0176627040e-02f
    +0xb.8ae86p-7f,
    // 53
    // +9.4372741878e-02f
    +0xc.1467fp-7f,
    // 54
    // +9.8609797657e-02f
    +0xc.9f3efp-7f,
    // 55
    // +1.0288859904e-01f
    +0xd.2b742p-7f,
    // 56
    // +1.1157477647e-01f
    +0xe.48151p-7f,
    // 57
    // +1.1598389596e-01f
    +0xe.d88f7p-7f,
    // 58
    // +1.2043823302e-01f
    +0xf.6a852p-7f,
    // 59
    // +1.2493873388e-01f
    +0xf.fdfe1p-7f,
    // 60
    // +1.2948636711e-01f
    +0x8.49813p-6f,
    // 61
    // +1.3408210874e-01f
    +0x8.94cd2p-6f,
    // 62
    // +1.3872702420e-01f
    +0x8.e0e75p-6f,
    // 63
    // +1.4342214167e-01f
    +0x9.2dd41p-6f
},
// static const float log10c_l[64]=
{
    // 0
    // +6.6254415287e-09f
    +0xe.3a6p-31f,
    // 1
    // +5.8817217763e-09f
    +0xc.a182cp-31f,
    // 2
    // +5.6514098956e-10f
    +0x9.b5843p-34f,
    // 3
    // +7.2157937403e-09f
    +0xf.7eecbp-31f,
    // 4
    // -3.5629719175e-09f
    -0xf.4d877p-32f,
    // 5
    // -7.6261685855e-10f
    -0xd.1a064p-34f,
    // 6
    // -2.5739623766e-09f
    -0xb.0e1ap-32f,
    // 7
    // -2.5739623766e-09f
    -0xb.0e1ap-32f,
    // 8
    // +4.0177766669e-10f
    +0xd.ce12ep-35f,
    // 9
    // +2.8710560596e-09f
    +0xc.54c27p-32f,
    // 10
    // +2.3192685550e-09f
    +0x9.f6101p-32f,
    // 11
    // +1.7405168418e-09f
    +0xe.f36fep-33f,
    // 12
    // +1.7405168418e-09f
    +0xe.f36fep-33f,
    // 13
    // -2.3620962963e-09f
    -0xa.2527p-32f,
    // 14
    // -1.9890258329e-09f
    -0x8.8af5p-32f,
    // 15
    // +3.2893829882e-09f
    +0xe.20b7p-32f,
    // 16
    // +3.2893829882e-09f
    +0xe.20b7p-32f,
    // 17
    // +2.3824742179e-09f
    +0xa.3b8eep-32f,
    // 18
    // -1.2369983926e-09f
    -0xa.a0303p-33f,
    // 19
    // -4.5156442474e-10f
    -0xf.8400bp-35f,
    // 20
    // -4.5156442474e-10f
    -0xf.8400bp-35f,
    // 21
    // +1.1279214229e-09f
    +0x9.b0535p-33f,
    // 22
    // +1.1596342775e-09f
    +0x9.f6101p-33f,
    // 23
    // +1.1596342775e-09f
    +0x9.f6101p-33f,
    // 24
    // -2.8974972421e-10f
    -0x9.f4aa6p-35f,
    // 25
    // -2.8974972421e-10f
    -0x9.f4aa6p-35f,
    // 26
    // +7.3946865298e-10f
    +0xc.b437bp-34f,
    // 27
    // -9.4178176369e-10f
    -0x8.17p-33f,
    // 28
    // -9.4178176369e-10f
    -0x8.17p-33f,
    // 29
    // -6.4048860660e-10f
    -0xb.00e61p-34f,
    // 30
    // -6.4048860660e-10f
    -0xb.00e61p-34f,
    // 31
    // +3.0296487541e-10f
    +0xa.68e84p-35f,
    // 32
    // +3.0296487541e-10f
    +0xa.68e84p-35f,
    // 33
    // -4.2760087138e-10f
    -0xe.b1379p-35f,
    // 34
    // -4.2760087138e-10f
    -0xe.b1379p-35f,
    // 35
    // -7.2578623667e-11f
    -0x9.f9a22p-37f,
    // 36
    // -7.2578623667e-11f
    -0x9.f9a22p-37f,
    // 37
    // +0.0000000000e+00f
    +0x0p+0f,
    // 38
    // -6.1978894239e-11f
    -0x8.84b04p-37f,
    // 39
    // +2.1378751547e-10f
    +0xe.b0fd6p-36f,
    // 40
    // +1.5668959186e-11f
    +0x8.9d35cp-39f,
    // 41
    // -1.5219091265e-10f
    -0xa.755efp-36f,
    // 42
    // +7.4777506409e-10f
    +0xc.d8bfep-34f,
    // 43
    // -1.1892743457e-09f
    -0xa.373dfp-33f,
    // 44
    // +1.3381270536e-09f
    +0xb.7e929p-33f,
    // 45
    // -1.3536410881e-09f
    -0xb.a0b03p-33f,
    // 46
    // -3.3553801404e-10f
    -0xb.876c7p-35f,
    // 47
    // -1.4443062302e-09f
    -0xc.68102p-33f,
    // 48
    // +2.8858302414e-09f
    +0xc.6501p-32f,
    // 49
    // +1.8252931111e-10f
    +0xc.8b16fp-36f,
    // 50
    // -2.5025015393e-09f
    -0xa.bf879p-32f,
    // 51
    // -1.4590153530e-09f
    -0xc.8868ap-33f,
    // 52
    // +3.3091787088e-09f
    +0xe.367bp-32f,
    // 53
    // +3.0646634119e-09f
    +0xd.29a21p-32f,
    // 54
    // +2.2941470945e-10f
    +0xf.c3e8p-36f,
    // 55
    // -3.1728983885e-09f
    -0xd.a0a38p-32f,
    // 56
    // -1.4203427323e-09f
    -0xc.335dep-33f,
    // 57
    // -2.0020964886e-09f
    -0x8.99541p-32f,
    // 58
    // +2.3637021229e-09f
    +0xa.26ebp-32f,
    // 59
    // +2.7325484098e-09f
    +0xb.bc78p-32f,
    // 60
    // -2.7474171826e-09f
    -0xb.ccd13p-32f,
    // 61
    // +7.3121313449e-09f
    +0xf.b3e3p-31f,
    // 62
    // -3.1036451187e-09f
    -0xd.547e7p-32f,
    // 63
    // +6.3113236859e-10f
    +0xa.d7bfep-34f
}
};


template struct cftal::math::log_data<float>;
