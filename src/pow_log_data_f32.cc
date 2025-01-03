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

template <>
const
cftal::math::pow_log_data<float>::table_t
cftal::math::pow_log_data<float>::_tbl={
// static const float p_invc[64]=
{
    // 0
    // +1.4218750000e+00f
    +0xb.6p-3f,
    // 1
    // +1.4062500000e+00f
    +0xb.4p-3f,
    // 2
    // +1.3906250000e+00f
    +0xb.2p-3f,
    // 3
    // +1.3750000000e+00f
    +0xbp-3f,
    // 4
    // +1.3593750000e+00f
    +0xa.ep-3f,
    // 5
    // +1.3437500000e+00f
    +0xa.cp-3f,
    // 6
    // +1.3281250000e+00f
    +0xa.ap-3f,
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
    // +1.2812500000e+00f
    +0xa.4p-3f,
    // 11
    // +1.2656250000e+00f
    +0xa.2p-3f,
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
    // +1.2187500000e+00f
    +0x9.cp-3f,
    // 16
    // +1.2031250000e+00f
    +0x9.ap-3f,
    // 17
    // +1.1875000000e+00f
    +0x9.8p-3f,
    // 18
    // +1.1875000000e+00f
    +0x9.8p-3f,
    // 19
    // +1.1718750000e+00f
    +0x9.6p-3f,
    // 20
    // +1.1562500000e+00f
    +0x9.4p-3f,
    // 21
    // +1.1406250000e+00f
    +0x9.2p-3f,
    // 22
    // +1.1406250000e+00f
    +0x9.2p-3f,
    // 23
    // +1.1250000000e+00f
    +0x9p-3f,
    // 24
    // +1.1250000000e+00f
    +0x9p-3f,
    // 25
    // +1.1093750000e+00f
    +0x8.ep-3f,
    // 26
    // +1.0937500000e+00f
    +0x8.cp-3f,
    // 27
    // +1.0937500000e+00f
    +0x8.cp-3f,
    // 28
    // +1.0781250000e+00f
    +0x8.ap-3f,
    // 29
    // +1.0781250000e+00f
    +0x8.ap-3f,
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
    // +1.0000000000e+00f
    +0x8p-3f,
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
// static const float p_logc_h[64]=
{
    // 0
    // -3.5197642446e-01f
    -0xb.43641p-5f,
    // 1
    // -3.4092658758e-01f
    -0xa.e8deep-5f,
    // 2
    // -3.2975327969e-01f
    -0xa.8d56cp-5f,
    // 3
    // -3.1845372915e-01f
    -0xa.30c5ep-5f,
    // 4
    // -3.0702504516e-01f
    -0x9.d3263p-5f,
    // 5
    // -2.9546421766e-01f
    -0x9.74716p-5f,
    // 6
    // -2.8376817703e-01f
    -0x9.14a1p-5f,
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
    // -2.4783615768e-01f
    -0xf.dc8c3p-6f,
    // 11
    // -2.3556606472e-01f
    -0xf.1383bp-6f,
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
    // -1.9782574475e-01f
    -0xc.a92d5p-6f,
    // 16
    // -1.8492233753e-01f
    -0xb.d5c48p-6f,
    // 17
    // -1.7185026407e-01f
    -0xa.ff984p-6f,
    // 18
    // -1.7185026407e-01f
    -0xa.ff984p-6f,
    // 19
    // -1.5860502422e-01f
    -0xa.2695bp-6f,
    // 20
    // -1.4518201351e-01f
    -0x9.4aa98p-6f,
    // 21
    // -1.3157635927e-01f
    -0x8.6bbf4p-6f,
    // 22
    // -1.3157635927e-01f
    -0x8.6bbf4p-6f,
    // 23
    // -1.1778303236e-01f
    -0xf.1383bp-7f,
    // 24
    // -1.1778303236e-01f
    -0xf.1383bp-7f,
    // 25
    // -1.0379679501e-01f
    -0xd.4936ap-7f,
    // 26
    // -8.9612156153e-02f
    -0xb.78694p-7f,
    // 27
    // -8.9612156153e-02f
    -0xb.78694p-7f,
    // 28
    // -7.5223423541e-02f
    -0x9.a0ebdp-7f,
    // 29
    // -7.5223423541e-02f
    -0x9.a0ebdp-7f,
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
    // +0.0000000000e+00f
    +0x0p+0f,
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
// static const float p_logc_l[64]=
{
    // 0
    // +1.2984645581e-09f
    +0xb.275a9p-33f,
    // 1
    // +6.1104132865e-10f
    +0xa.7f636p-34f,
    // 2
    // -6.6864940251e-09f
    -0xe.5bf06p-31f,
    // 3
    // -1.9658552564e-09f
    -0x8.717b1p-32f,
    // 4
    // +9.8615666744e-09f
    +0xa.96ba1p-30f,
    // 5
    // +4.7689754368e-09f
    +0xa.3dc5ap-31f,
    // 6
    // +3.9018259734e-09f
    +0x8.610d3p-31f,
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
    // -6.2250236077e-09f
    -0xd.5e3e3p-31f,
    // 11
    // -6.5973813079e-09f
    -0xe.2af2ep-31f,
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
    // +1.4181956720e-09f
    +0xc.2ea53p-33f,
    // 16
    // -9.6196850485e-10f
    -0x8.43642p-33f,
    // 17
    // +7.1457590956e-09f
    +0xf.586c3p-31f,
    // 18
    // +7.1457590956e-09f
    +0xf.586c3p-31f,
    // 19
    // -5.9580793632e-09f
    -0xc.cb7d2p-31f,
    // 20
    // +3.6671599091e-09f
    +0xf.c015cp-32f,
    // 21
    // +1.4832839401e-09f
    +0xc.bdc6ap-33f,
    // 22
    // +1.4832839401e-09f
    +0xc.bdc6ap-33f,
    // 23
    // -3.2986906540e-09f
    -0xe.2af2ep-32f,
    // 24
    // -3.2986906540e-09f
    -0xe.2af2ep-32f,
    // 25
    // +1.3289231937e-09f
    +0xb.6a554p-33f,
    // 26
    // -2.5369619738e-09f
    -0xa.e56b5p-32f,
    // 27
    // -2.5369619738e-09f
    -0xa.e56b5p-32f,
    // 28
    // +2.3030046759e-09f
    +0x9.e42e3p-32f,
    // 29
    // +2.3030046759e-09f
    +0x9.e42e3p-32f,
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
    // +0.0000000000e+00f
    +0x0p+0f,
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
}
};

template struct cftal::math::pow_log_data<float>;
