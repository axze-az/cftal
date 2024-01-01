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
#include "cftal/math/func_data.h"

template <>
const
cftal::math::pow_log_data<double>::table_t
cftal::math::pow_log_data<double>::_tbl={
// static const double p_invc[64]=
{
    // 0
    // +1.4218750000000000000000e+00
    +0xb.6p-3,
    // 1
    // +1.4062500000000000000000e+00
    +0xb.4p-3,
    // 2
    // +1.3906250000000000000000e+00
    +0xb.2p-3,
    // 3
    // +1.3750000000000000000000e+00
    +0xbp-3,
    // 4
    // +1.3593750000000000000000e+00
    +0xa.ep-3,
    // 5
    // +1.3437500000000000000000e+00
    +0xa.cp-3,
    // 6
    // +1.3281250000000000000000e+00
    +0xa.ap-3,
    // 7
    // +1.3125000000000000000000e+00
    +0xa.8p-3,
    // 8
    // +1.2968750000000000000000e+00
    +0xa.6p-3,
    // 9
    // +1.2812500000000000000000e+00
    +0xa.4p-3,
    // 10
    // +1.2812500000000000000000e+00
    +0xa.4p-3,
    // 11
    // +1.2656250000000000000000e+00
    +0xa.2p-3,
    // 12
    // +1.2500000000000000000000e+00
    +0xap-3,
    // 13
    // +1.2343750000000000000000e+00
    +0x9.ep-3,
    // 14
    // +1.2187500000000000000000e+00
    +0x9.cp-3,
    // 15
    // +1.2187500000000000000000e+00
    +0x9.cp-3,
    // 16
    // +1.2031250000000000000000e+00
    +0x9.ap-3,
    // 17
    // +1.1875000000000000000000e+00
    +0x9.8p-3,
    // 18
    // +1.1875000000000000000000e+00
    +0x9.8p-3,
    // 19
    // +1.1718750000000000000000e+00
    +0x9.6p-3,
    // 20
    // +1.1562500000000000000000e+00
    +0x9.4p-3,
    // 21
    // +1.1406250000000000000000e+00
    +0x9.2p-3,
    // 22
    // +1.1406250000000000000000e+00
    +0x9.2p-3,
    // 23
    // +1.1250000000000000000000e+00
    +0x9p-3,
    // 24
    // +1.1250000000000000000000e+00
    +0x9p-3,
    // 25
    // +1.1093750000000000000000e+00
    +0x8.ep-3,
    // 26
    // +1.0937500000000000000000e+00
    +0x8.cp-3,
    // 27
    // +1.0937500000000000000000e+00
    +0x8.cp-3,
    // 28
    // +1.0781250000000000000000e+00
    +0x8.ap-3,
    // 29
    // +1.0781250000000000000000e+00
    +0x8.ap-3,
    // 30
    // +1.0625000000000000000000e+00
    +0x8.8p-3,
    // 31
    // +1.0468750000000000000000e+00
    +0x8.6p-3,
    // 32
    // +1.0468750000000000000000e+00
    +0x8.6p-3,
    // 33
    // +1.0312500000000000000000e+00
    +0x8.4p-3,
    // 34
    // +1.0312500000000000000000e+00
    +0x8.4p-3,
    // 35
    // +1.0156250000000000000000e+00
    +0x8.2p-3,
    // 36
    // +1.0156250000000000000000e+00
    +0x8.2p-3,
    // 37
    // +1.0000000000000000000000e+00
    +0x8p-3,
    // 38
    // +1.0000000000000000000000e+00
    +0x8p-3,
    // 39
    // +9.7656250000000000000000e-01
    +0xf.ap-4,
    // 40
    // +9.6093750000000000000000e-01
    +0xf.6p-4,
    // 41
    // +9.4531250000000000000000e-01
    +0xf.2p-4,
    // 42
    // +9.3750000000000000000000e-01
    +0xfp-4,
    // 43
    // +9.2187500000000000000000e-01
    +0xe.cp-4,
    // 44
    // +9.0625000000000000000000e-01
    +0xe.8p-4,
    // 45
    // +8.9843750000000000000000e-01
    +0xe.6p-4,
    // 46
    // +8.8281250000000000000000e-01
    +0xe.2p-4,
    // 47
    // +8.6718750000000000000000e-01
    +0xd.ep-4,
    // 48
    // +8.5937500000000000000000e-01
    +0xd.cp-4,
    // 49
    // +8.5156250000000000000000e-01
    +0xd.ap-4,
    // 50
    // +8.3593750000000000000000e-01
    +0xd.6p-4,
    // 51
    // +8.2812500000000000000000e-01
    +0xd.4p-4,
    // 52
    // +8.1250000000000000000000e-01
    +0xdp-4,
    // 53
    // +8.0468750000000000000000e-01
    +0xc.ep-4,
    // 54
    // +7.9687500000000000000000e-01
    +0xc.cp-4,
    // 55
    // +7.8906250000000000000000e-01
    +0xc.ap-4,
    // 56
    // +7.7343750000000000000000e-01
    +0xc.6p-4,
    // 57
    // +7.6562500000000000000000e-01
    +0xc.4p-4,
    // 58
    // +7.5781250000000000000000e-01
    +0xc.2p-4,
    // 59
    // +7.5000000000000000000000e-01
    +0xcp-4,
    // 60
    // +7.4218750000000000000000e-01
    +0xb.ep-4,
    // 61
    // +7.3437500000000000000000e-01
    +0xb.cp-4,
    // 62
    // +7.2656250000000000000000e-01
    +0xb.ap-4,
    // 63
    // +7.1875000000000000000000e-01
    +0xb.8p-4
},
// static const double p_logc_h[64]=
{
    // 0
    // -3.5197642315717819760934e-01
    -0xb.43640f4d8a578p-5,
    // 1
    // -3.4092658697059319283795e-01
    -0xa.e8dedfac04e5p-5,
    // 2
    // -3.2975328637246797969240e-01
    -0xa.8d56c396fc168p-5,
    // 3
    // -3.1845373111853458869547e-01
    -0xa.30c5e10e2f61p-5,
    // 4
    // -3.0702503529491187439504e-01
    -0x9.d3262ab4a2f5p-5,
    // 5
    // -2.9546421289383589803279e-01
    -0x9.74715d708e988p-5,
    // 6
    // -2.8376817313064461867356e-01
    -0x9.14a0fde7bcb3p-5,
    // 7
    // -2.7193371548364175804835e-01
    -0x8.b3ae55d5d307p-5,
    // 8
    // -2.5995752443692604627401e-01
    -0x8.51927139c8718p-5,
    // 9
    // -2.4783616390458126921281e-01
    -0xf.dc8c36af1f158p-6,
    // 10
    // -2.4783616390458126921281e-01
    -0xf.dc8c36af1f158p-6,
    // 11
    // -2.3556607131276691147193e-01
    -0xf.1383b7157973p-6,
    // 12
    // -2.2314355131420976485757e-01
    -0xe.47fbe3cd4d11p-6,
    // 13
    // -2.1056476910734964191896e-01
    -0xd.79e4a7405ff98p-6,
    // 14
    // -1.9782574332991986754138e-01
    -0xc.a92d4e7a2b5ap-6,
    // 15
    // -1.9782574332991986754138e-01
    -0xc.a92d4e7a2b5ap-6,
    // 16
    // -1.8492233849401198964024e-01
    -0xb.d5c481086c848p-6,
    // 17
    // -1.7185025692665922836255e-01
    -0xa.ff983853c9eap-6,
    // 18
    // -1.7185025692665922836255e-01
    -0xa.ff983853c9eap-6,
    // 19
    // -1.5860503017663857283637e-01
    -0xa.2695b665be8fp-6,
    // 20
    // -1.4518200984449788903952e-01
    -0x9.4aa97c0ffa918p-6,
    // 21
    // -1.3157635778871926146572e-01
    -0x8.6bbf3e68472c8p-6,
    // 22
    // -1.3157635778871926146572e-01
    -0x8.6bbf3e68472c8p-6,
    // 23
    // -1.1778303565638345573596e-01
    -0xf.1383b7157973p-7,
    // 24
    // -1.1778303565638345573596e-01
    -0xf.1383b7157973p-7,
    // 25
    // -1.0379679368164355934834e-01
    -0xd.49369d256ab18p-7,
    // 26
    // -8.9612158689687138046764e-02
    -0xb.78694572b5a6p-7,
    // 27
    // -8.9612158689687138046764e-02
    -0xb.78694572b5a6p-7,
    // 28
    // -7.5223421237587531629210e-02
    -0x9.a0ebcb0de8e88p-7,
    // 29
    // -7.5223421237587531629210e-02
    -0x9.a0ebcb0de8e88p-7,
    // 30
    // -6.0624621816434839938204e-02
    -0xf.85186008b153p-8,
    // 31
    // -4.5809536031294201263719e-02
    -0xb.ba2c7b196e7ep-8,
    // 32
    // -4.5809536031294201263719e-02
    -0xb.ba2c7b196e7ep-8,
    // 33
    // -3.0771658666753687327855e-02
    -0xf.c14d873c198p-9,
    // 34
    // -3.0771658666753687327855e-02
    -0xf.c14d873c198p-9,
    // 35
    // -1.5504186535965254478686e-02
    -0xf.e054587e01f2p-10,
    // 36
    // -1.5504186535965254478686e-02
    -0xf.e054587e01f2p-10,
    // 37
    // +0.0000000000000000000000e+00
    +0x0p+0,
    // 38
    // +0.0000000000000000000000e+00
    +0x0p+0,
    // 39
    // +2.3716526617316043695771e-02
    +0xc.24929464655f8p-9,
    // 40
    // +3.9845908547199673788164e-02
    +0xa.33576a16f1f5p-8,
    // 41
    // +5.6239718322876081080253e-02
    +0xe.65b9e6eed966p-8,
    // 42
    // +6.4538521137571178143411e-02
    +0x8.42cc5acf1d038p-7,
    // 43
    // +8.1345639453952400810266e-02
    +0xa.6988ae903f56p-7,
    // 44
    // +9.8440072813252524341898e-02
    +0xc.99af2eaca4c48p-7,
    // 45
    // +1.0709813555636710225016e-01
    +0xd.b56446d6ad8ep-7,
    // 46
    // +1.2464244520727660314741e-01
    +0xf.f4489cedeab3p-7,
    // 47
    // +1.4250006260728304008367e-01
    +0x9.1eb89524e101p-6,
    // 48
    // +1.5154989812720093267373e-01
    +0x9.b2fe580ac80bp-6,
    // 49
    // +1.6068238169047346919349e-01
    +0xa.489ec199dab08p-6,
    // 50
    // +1.7920142945771100340124e-01
    +0xb.780945bab55ep-6,
    // 51
    // +1.8859116980755002979109e-01
    +0xc.11e0b2a8d1e1p-6,
    // 52
    // +2.0763936477824448956220e-01
    +0xd.49f69e456cf18p-6,
    // 53
    // +2.1730127568998139353518e-01
    +0xd.e8439c1dec568p-6,
    // 54
    // +2.2705745063534607530720e-01
    +0xe.881bf932af3d8p-6,
    // 55
    // +2.3690974707835771306819e-01
    +0xf.29877ff38809p-6,
    // 56
    // +2.5691041378502721403976e-01
    +0x8.389c3026ac31p-5,
    // 57
    // +2.6706278524904525362160e-01
    +0x8.8bc74113f23ep-5,
    // 58
    // +2.7731928541623435124919e-01
    +0x8.dfccb1ad35ca8p-5,
    // 59
    // +2.8768207245178090136761e-01
    +0x9.34b1089a6dc9p-5,
    // 60
    // +2.9815337231907634851780e-01
    +0x9.8a78f0e9ae72p-5,
    // 61
    // +3.0873548164961328588163e-01
    +0x9.e1293b9998c2p-5,
    // 62
    // +3.1943077076636122724196e-01
    +0xa.38c6e138e20d8p-5,
    // 63
    // +3.3024168687057686710773e-01
    +0xa.9157039c51ecp-5
},
// static const double p_logc_l[64]=
{
    // 0
    // +1.2953893030191962901522e-17
    +0xe.ef507bfac71e8p-60,
    // 1
    // -1.7467136443544747117130e-17
    -0xa.11b1c1ee3ff08p-59,
    // 2
    // -2.1220206161969460233328e-18
    -0x9.c93d60cfaaf18p-62,
    // 3
    // -2.7114779367326235963230e-17
    -0xf.a16f66f6678e8p-59,
    // 4
    // +1.2319916200101964284686e-17
    +0xe.34328ca2fcbep-60,
    // 5
    // +2.1646108604059899663845e-17
    +0xc.7a66dcaf5efc8p-59,
    // 6
    // +2.0326655811266561230291e-17
    +0xb.b7af584b14578p-59,
    // 7
    // -7.8331963769744201243220e-19
    -0xe.731f55c41b8b8p-64,
    // 8
    // -2.0698069389789350259276e-17
    -0xb.ee7ef4030e018p-59,
    // 9
    // +1.2432209578702523181819e-17
    +0xe.555732790d658p-60,
    // 10
    // +1.2432209578702523181819e-17
    +0xe.555732790d658p-60,
    // 11
    // +2.3943371495187354598708e-18
    +0xb.0abc000f00b1p-62,
    // 12
    // +9.0912705973247990487110e-18
    +0xa.7b44fc21a009p-60,
    // 13
    // +4.2494053147298953285036e-18
    +0x9.cc67f9b20cc28p-61,
    // 14
    // -1.2821194372980141925963e-17
    -0xe.c8260ea71713p-60,
    // 15
    // -1.2821194372980141925963e-17
    -0xe.c8260ea71713p-60,
    // 16
    // -3.0236614153574064265771e-18
    -0xd.f1b596b50304p-62,
    // 17
    // +6.0224538210113704760318e-18
    +0xd.e3077d7e37b7p-61,
    // 18
    // +6.0224538210113704760318e-18
    +0xd.e3077d7e37b7p-61,
    // 19
    // -1.1257003872182592244744e-17
    -0xc.fa7b2a1f0fc4p-60,
    // 20
    // -8.2424187830224753896228e-18
    -0x9.80bb8e203edf8p-60,
    // 21
    // -1.1123000879729588029913e-17
    -0xc.d2ee2f481856p-60,
    // 22
    // -1.1123000879729588029913e-17
    -0xc.d2ee2f481856p-60,
    // 23
    // +1.1971685747593677299354e-18
    +0xb.0abc000f00b1p-63,
    // 24
    // +1.1971685747593677299354e-18
    +0xb.0abc000f00b1p-63,
    // 25
    // -5.4777241572665901259271e-18
    -0xc.a17a455387548p-61,
    // 26
    // +5.4268129336647135340291e-18
    +0xc.836cc8c25cc9p-61,
    // 27
    // +5.4268129336647135340291e-18
    +0xc.836cc8c25cc9p-61,
    // 28
    // +5.9306041962932407170822e-18
    +0xd.accf913df65d8p-61,
    // 29
    // +5.9306041962932407170822e-18
    +0xd.accf913df65d8p-61,
    // 30
    // -2.6424025938726934181575e-18
    -0xc.2f992e2ddd668p-62,
    // 31
    // -1.9029598664742570632553e-18
    -0x8.c69e543dc94bp-62,
    // 32
    // -1.9029598664742570632553e-18
    -0x8.c69e543dc94bp-62,
    // 33
    // -1.0431732029005967805060e-18
    -0x9.9f1f8278f7918p-63,
    // 34
    // -1.0431732029005967805060e-18
    -0x9.9f1f8278f7918p-63,
    // 35
    // +3.2783210228924291296299e-19
    +0xc.184962cb21508p-65,
    // 36
    // +3.2783210228924291296299e-19
    +0xc.184962cb21508p-65,
    // 37
    // +0.0000000000000000000000e+00
    +0x0p+0,
    // 38
    // +0.0000000000000000000000e+00
    +0x0p+0,
    // 39
    // -1.5774243488668214501978e-18
    -0xe.8c96830cfd338p-63,
    // 40
    // -3.1295476803152080939367e-18
    -0xe.6eb7bfa509bfp-62,
    // 41
    // -3.2835149805605612909474e-18
    -0xf.247d828077eap-62,
    // 42
    // -6.4704866616929329974162e-18
    -0xe.eb804c815f99p-61,
    // 43
    // +5.0770763559311699301706e-18
    +0xb.b4fa163c2166p-61,
    // 44
    // -4.4390096336751358765623e-18
    -0xa.3c542b82665b8p-61,
    // 45
    // -1.7370510401590600102694e-18
    -0x8.02bf768e52cf8p-62,
    // 46
    // -5.8089126789409707143484e-18
    -0xd.64fa10afc9c98p-61,
    // 47
    // -9.9263882342257491397107e-18
    -0xb.71c0b0828eb48p-60,
    // 48
    // +5.1669593684615594400308e-18
    +0xb.ea08d2dca2568p-61,
    // 49
    // -3.6501835530478371170631e-18
    -0x8.6ab02498789a8p-61,
    // 50
    // -1.0785017454858423021806e-17
    -0xc.6f2ce10f0b36p-60,
    // 51
    // -7.4321642191969250529700e-18
    -0x8.91967385f3c08p-60,
    // 52
    // +1.2053243216686128949047e-17
    +0xd.e57d4ef4b9018p-60,
    // 53
    // +1.6168452453763015357460e-18
    +0xe.e9aafb528b6b8p-63,
    // 54
    // +9.5514157627384884314921e-18
    +0xb.0314921238d1p-60,
    // 55
    // +1.9682402978398163668954e-18
    +0x9.13b020fa1821p-62,
    // 56
    // +2.5028432961525040476288e-17
    +0xe.6d8b76a7489cp-59,
    // 57
    // -7.3289153273201694886199e-18
    -0x8.731d2f80e3488p-60,
    // 58
    // -7.4452840558351296763783e-18
    -0x8.9575c21249118p-60,
    // 59
    // +2.6071606164425639760503e-17
    +0xf.077d6eced8158p-59,
    // 60
    // -1.7206958674458660371517e-17
    -0x9.eb4c84f2e1eep-59,
    // 61
    // -1.6199186085148102239334e-17
    -0x9.5693f2854763p-59,
    // 62
    // +1.3542568572648110745998e-18
    +0xc.7da60a62b7778p-63,
    // 63
    // -1.0828321637483857903422e-17
    -0xc.7bf4d9c534bc8p-60
}
};

template struct cftal::math::pow_log_data<double>;
