//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/math/func_data.h"

template <>
const
cftal::math::log_data<double>::table_t
cftal::math::log_data<double>::_tbl={
// static const double invc[64]=
{
    // 0
    // +1.4143676757812500000000e+00
    +0xb.50ap-3,
    // 1
    // +1.3989105224609375000000e+00
    +0xb.30f8p-3,
    // 2
    // +1.3837814331054687500000e+00
    +0xb.11fcp-3,
    // 3
    // +1.3689804077148437500000e+00
    +0xa.f3acp-3,
    // 4
    // +1.3544998168945312500000e+00
    +0xa.d604p-3,
    // 5
    // +1.3403167724609375000000e+00
    +0xa.b8f8p-3,
    // 6
    // +1.3264236450195312500000e+00
    +0xa.9c84p-3,
    // 7
    // +1.3128204345703125000000e+00
    +0xa.80a8p-3,
    // 8
    // +1.2994918823242187500000e+00
    +0xa.655cp-3,
    // 9
    // +1.2864303588867187500000e+00
    +0xa.4a9cp-3,
    // 10
    // +1.2736282348632812500000e+00
    +0xa.3064p-3,
    // 11
    // +1.2610855102539062500000e+00
    +0xa.16b4p-3,
    // 12
    // +1.2487792968750000000000e+00
    +0x9.fd8p-3,
    // 13
    // +1.2367172241210937500000e+00
    +0x9.e4ccp-3,
    // 14
    // +1.2248840332031250000000e+00
    +0x9.cc9p-3,
    // 15
    // +1.2132720947265625000000e+00
    +0x9.b4c8p-3,
    // 16
    // +1.2018814086914062500000e+00
    +0x9.9d74p-3,
    // 17
    // +1.1906967163085937500000e+00
    +0x9.868cp-3,
    // 18
    // +1.1797256469726562500000e+00
    +0x9.7014p-3,
    // 19
    // +1.1689529418945312500000e+00
    +0x9.5a04p-3,
    // 20
    // +1.1583709716796875000000e+00
    +0x9.4458p-3,
    // 21
    // +1.1479797363281250000000e+00
    +0x9.2f1p-3,
    // 22
    // +1.1377792358398437500000e+00
    +0x9.1a2cp-3,
    // 23
    // +1.1277542114257812500000e+00
    +0x9.05a4p-3,
    // 24
    // +1.1179046630859375000000e+00
    +0x8.f178p-3,
    // 25
    // +1.1082229614257812500000e+00
    +0x8.dda4p-3,
    // 26
    // +1.0987091064453125000000e+00
    +0x8.ca28p-3,
    // 27
    // +1.0893630981445312500000e+00
    +0x8.b704p-3,
    // 28
    // +1.0801696777343750000000e+00
    +0x8.a43p-3,
    // 29
    // +1.0711288452148437500000e+00
    +0x8.91acp-3,
    // 30
    // +1.0622406005859375000000e+00
    +0x8.7f78p-3,
    // 31
    // +1.0534973144531250000000e+00
    +0x8.6d9p-3,
    // 32
    // +1.0448989868164062500000e+00
    +0x8.5bf4p-3,
    // 33
    // +1.0364379882812500000000e+00
    +0x8.4aap-3,
    // 34
    // +1.0281143188476562500000e+00
    +0x8.3994p-3,
    // 35
    // +1.0199203491210937500000e+00
    +0x8.28ccp-3,
    // 36
    // +1.0118560791015625000000e+00
    +0x8.1848p-3,
    // 37
    // +1.0039215087890625000000e+00
    +0x8.0808p-3,
    // 38
    // +9.9610900878906250000000e-01
    +0xf.f01p-4,
    // 39
    // +9.7710037231445312500000e-01
    +0xf.a234p-4,
    // 40
    // +9.6240615844726562500000e-01
    +0xf.6604p-4,
    // 41
    // +9.4814682006835937500000e-01
    +0xf.2b9cp-4,
    // 42
    // +9.3430709838867187500000e-01
    +0xe.f2ecp-4,
    // 43
    // +9.2086410522460937500000e-01
    +0xe.bbdcp-4,
    // 44
    // +9.0780258178710937500000e-01
    +0xe.865cp-4,
    // 45
    // +8.9510345458984375000000e-01
    +0xe.5258p-4,
    // 46
    // +8.8275909423828125000000e-01
    +0xe.1fc8p-4,
    // 47
    // +8.7074661254882812500000e-01
    +0xd.ee94p-4,
    // 48
    // +8.5906219482421875000000e-01
    +0xd.beb8p-4,
    // 49
    // +8.4768295288085937500000e-01
    +0xd.901cp-4,
    // 50
    // +8.3660125732421875000000e-01
    +0xd.62b8p-4,
    // 51
    // +8.2580566406250000000000e-01
    +0xd.368p-4,
    // 52
    // +8.1528472900390625000000e-01
    +0xd.0b68p-4,
    // 53
    // +8.0503082275390625000000e-01
    +0xc.e168p-4,
    // 54
    // +7.9503250122070312500000e-01
    +0xc.b874p-4,
    // 55
    // +7.8527450561523437500000e-01
    +0xc.907cp-4,
    // 56
    // +7.7575683593750000000000e-01
    +0xc.698p-4,
    // 57
    // +7.6646804809570312500000e-01
    +0xc.4374p-4,
    // 58
    // +7.5739669799804687500000e-01
    +0xc.1e4cp-4,
    // 59
    // +7.4853897094726562500000e-01
    +0xb.fa04p-4,
    // 60
    // +7.3988342285156250000000e-01
    +0xb.d69p-4,
    // 61
    // +7.3143005371093750000000e-01
    +0xb.b3fp-4,
    // 62
    // +7.2316360473632812500000e-01
    +0xb.9214p-4,
    // 63
    // +7.1508407592773437500000e-01
    +0xb.70fcp-4
},
// static const double logc_h[64]=
{
    // 0
    // -3.4668255897864647119277e-01
    -0xb.1806059d05248p-5,
    // 1
    // -3.3569373542559127754359e-01
    -0xa.be00c9e3ffed8p-5,
    // 2
    // -3.2481992066741871560964e-01
    -0xa.64ecbf0b635ap-5,
    // 3
    // -3.1406623481956680299376e-01
    -0xa.0cd4a1ea7e1f8p-5,
    // 4
    // -3.0343224735993329366224e-01
    -0x9.b5b78b5ece678p-5,
    // 5
    // -2.9290598338427575875187e-01
    -0x9.5f7c5e6e059ap-5,
    // 6
    // -2.8248633170225612154525e-01
    -0x9.0a20c6874d66p-5,
    // 7
    // -2.7217782631116910208036e-01
    -0x8.b5ae45d67da98p-5,
    // 8
    // -2.6197332831130787367258e-01
    -0x8.6215e3b0aecd8p-5,
    // 9
    // -2.5187121904493686708193e-01
    -0x8.0f543b1340c48p-5,
    // 10
    // -2.4186970519585199168588e-01
    -0xf.7acb126d65ebp-6,
    // 11
    // -2.3197286614594636589004e-01
    -0xe.d8a4b869ff98p-6,
    // 12
    // -2.2216651166638315406665e-01
    -0xe.37f9e377e7b88p-6,
    // 13
    // -2.1246046915420660483598e-01
    -0xd.98f3cbad72d68p-6,
    // 14
    // -2.0284617274254934660149e-01
    -0xc.fb6e838312b2p-6,
    // 15
    // -1.9332092032760994637641e-01
    -0xc.5f5eb59c2426p-6,
    // 16
    // -1.8388816959123055472247e-01
    -0xb.c4d2e2a10032p-6,
    // 17
    // -1.7453861168887147004014e-01
    -0xb.2ba3ff45f2d5p-6,
    // 18
    // -1.6528190887911611839378e-01
    -0xa.93fa9250667e8p-6,
    // 19
    // -1.5610842667072144518414e-01
    -0x9.fdae32cb919ep-6,
    // 20
    // -1.4701468335716311175432e-01
    -0x9.68b04643407dp-6,
    // 21
    // -1.3800364645946788799691e-01
    -0x8.d50d3f116b15p-6,
    // 22
    // -1.2907832377418390623625e-01
    -0x8.42d1bacee33b8p-6,
    // 23
    // -1.2022823166054052990148e-01
    -0xf.63a38184dbp-7,
    // 24
    // -1.1145609657620041132997e-01
    -0xe.443180de07518p-7,
    // 25
    // -1.0275779680493744849823e-01
    -0xd.272ae057d60b8p-7,
    // 26
    // -9.4135951072358045599309e-02
    -0xc.0ca5979de7b78p-7,
    // 27
    // -8.5593211834445070973487e-02
    -0xa.f4b7e6cb5556p-7,
    // 28
    // -7.7118137809109976732458e-02
    -0x9.df01d3e8c632p-7,
    // 29
    // -6.8713087885023602097156e-02
    -0x8.cb9728a2fd238p-7,
    // 30
    // -6.0380451384260930280945e-02
    -0xf.7517e0035bbep-8,
    // 31
    // -5.2115405092388628061073e-02
    -0xd.576f687d567ep-8,
    // 32
    // -4.3920217410990669559823e-02
    -0xb.3e5af969d58cp-8,
    // 33
    // -3.5789823107066791318953e-02
    -0x9.298597c6441f8p-8,
    // 34
    // -2.7726365954868055496707e-02
    -0xe.32267606b339p-9,
    // 35
    // -1.9724535150100534069972e-02
    -0xa.195592cc06208p-9,
    // 36
    // -1.1786346425338338830824e-02
    -0xc.11b851be9f548p-10,
    // 37
    // -3.9138397164897769167635e-03
    -0x8.03faacac419a8p-11,
    // 38
    // +3.8985808110143238547352e-03
    +0xf.f7f551588dep-12,
    // 39
    // +2.3165896991636718976748e-02
    +0xb.dc6683ec54cd8p-9,
    // 40
    // +3.8318715290535765305435e-02
    +0x9.cf415cff61dp-8,
    // 41
    // +5.3245915228945499275692e-02
    +0xd.a186388dccff8p-8,
    // 42
    // +6.7950095664542700668598e-02
    +0x8.b296b751d4008p-7,
    // 43
    // +8.2442804944098821429144e-02
    +0xa.8d7c5f8340af8p-7,
    // 44
    // +9.6728344959509562905886e-02
    +0xc.61982b1941208p-7,
    // 45
    // +1.1081597566699401269386e-01
    +0xe.2f37c7ae99e18p-7,
    // 46
    // +1.2470294205929814690403e-01
    +0xf.f64418ee099d8p-7,
    // 47
    // +1.3840426001195060834448e-01
    +0x8.db9d8a9837d8p-6,
    // 48
    // +1.5191395586545086704433e-01
    +0x9.b8f5500fe0dap-6,
    // 49
    // +1.6524858941915199217476e-01
    +0xa.936ed1d0fc24p-6,
    // 50
    // +1.7840771707746486129942e-01
    +0xb.6b08338ce92e8p-6,
    // 51
    // +1.9139580667440062033968e-01
    +0xc.3fd4329084888p-6,
    // 52
    // +2.0421786601253896775710e-01
    +0xd.11e7cff218d18p-6,
    // 53
    // +2.1687471316129663945205e-01
    +0xd.e1467a16db8bp-6,
    // 54
    // +2.2937228312483262659960e-01
    +0xe.ae0915a852108p-6,
    // 55
    // +2.4172193364473865129227e-01
    +0xf.785f45eeb8e3p-6,
    // 56
    // +2.5391616365573460578631e-01
    +0x8.2014ca5a78208p-5,
    // 57
    // +2.6596226699809638605032e-01
    +0x8.82c34cd7424e8p-5,
    // 58
    // +2.7786812317796377724832e-01
    +0x8.e44bb0b4cee18p-5,
    // 59
    // +2.8963201108400110639352e-01
    +0x9.44aa59ef60358p-5,
    // 60
    // +3.0126264188120660536541e-01
    +0x9.a3f18d4c5cea8p-5,
    // 61
    // +3.1275368344802800812943e-01
    +0xa.021403439c32p-5,
    // 62
    // +3.2411979647981198349171e-01
    +0xa.5f307abbbe348p-5,
    // 63
    // +3.3535515449102182294894e-01
    +0xa.bb3abba2afdap-5
},
// static const double logc_l[64]=
{
    // 0
    // -1.6197891082500569986700e-17
    -0x9.5663060605aa8p-59,
    // 1
    // +2.3189187904172362254728e-18
    +0xa.b1b2332823b78p-62,
    // 2
    // +5.3502637092628996114232e-18
    +0xc.563cfe1374dbp-61,
    // 3
    // -1.5009195942898397610784e-18
    -0xd.d7f239b09e9b8p-63,
    // 4
    // +2.1485489227864330007544e-18
    +0x9.e88f111e17cp-62,
    // 5
    // +1.8434795710917270117202e-17
    +0xa.a07ee41d2e888p-59,
    // 6
    // -1.3389471621653522308164e-17
    -0xf.6fdfdf4547ee8p-60,
    // 7
    // -1.9460473776725560432106e-17
    -0xb.37dbe9af57fp-59,
    // 8
    // -3.7505723773645297746923e-18
    -0x8.a5f279216b208p-61,
    // 9
    // +2.8144985567813080558219e-18
    +0xc.fac5fe5f353ep-62,
    // 10
    // +1.1151787809685646400280e-17
    +0xc.db6d437ce5dc8p-60,
    // 11
    // -6.6903768573285810407375e-18
    -0xf.6d4d2a6cc343p-61,
    // 12
    // +1.1086323702892287863265e-17
    +0xc.c81aef8127dbp-60,
    // 13
    // +7.6284434454069316394070e-18
    +0x8.cb84e3e9f933p-60,
    // 14
    // -1.0921382737904816221510e-17
    -0xc.976c593e73438p-60,
    // 15
    // -6.0197844299110559385289e-18
    -0xd.e1741a6d3a998p-61,
    // 16
    // +1.2986747822759631679678e-17
    +0xe.f902ec1795e6p-60,
    // 17
    // +1.7569722201851900960945e-18
    +0x8.1a4445347853p-62,
    // 18
    // -1.3764782621255599626087e-18
    -0xc.b21e0e3c849cp-63,
    // 19
    // +6.1580310935198649294631e-18
    +0xe.330f592ea91dp-61,
    // 20
    // +4.4670177710831138844119e-18
    +0xa.4cdca3d82f5a8p-61,
    // 21
    // +5.8570724662735775772418e-18
    +0xd.8167c437f7df8p-61,
    // 22
    // +1.2239463075360749527645e-17
    +0xe.1c73aee1604ep-60,
    // 23
    // +2.6638816136858565019023e-18
    +0xc.48f4d0d7f748p-62,
    // 24
    // -5.7799079438903024179217e-18
    -0xd.53dafe5900e8p-61,
    // 25
    // -6.7470656797946013862014e-18
    -0xf.8ec3bd05a5d38p-61,
    // 26
    // -6.0118330453619818031652e-18
    -0xd.dcc28622d20a8p-61,
    // 27
    // +6.4064052397981882641798e-18
    +0xe.c5ac9691dee5p-61,
    // 28
    // -2.7591239429126627730248e-18
    -0xc.b9660b2485438p-62,
    // 29
    // +2.7035496168998981702249e-18
    +0xc.77c9bbef47d28p-62,
    // 30
    // +2.1570343234230611951164e-18
    +0x9.f2939f31408b8p-62,
    // 31
    // -6.3978158782315102573957e-19
    -0xb.cd487afdafcbp-64,
    // 32
    // -2.0794365259718618912091e-18
    -0x9.96f7206a72f08p-62,
    // 33
    // +2.6190119950508072482773e-18
    +0xc.13fbce40ac5a8p-62,
    // 34
    // -4.3735248804661850210147e-19
    -0x8.1156b70ef9bp-64,
    // 35
    // +1.3445891630570812341205e-18
    +0xc.66d2472acd74p-63,
    // 36
    // -5.6619147398833087995845e-19
    -0xa.71c37de3569ep-64,
    // 37
    // -4.2801927622471922146239e-19
    -0xf.ca871bcff0908p-65,
    // 38
    // +1.2534600430726730489464e-19
    +0x9.3fb8157f1454p-66,
    // 39
    // -1.7003409890253169459955e-18
    -0xf.aed10fd814d58p-63,
    // 40
    // -2.3590990647114303805763e-18
    -0xa.e121f14d8d328p-62,
    // 41
    // -7.4951754542953326044902e-19
    -0xd.d37f1ce895648p-64,
    // 42
    // -1.3407328377892456848954e-18
    -0xc.5db745bc49e08p-63,
    // 43
    // +5.4852474283985451830972e-18
    +0xc.a5eb27c80389p-61,
    // 44
    // -1.2612499966541128483578e-18
    -0xb.a20ad7cd0382p-63,
    // 45
    // +2.5730958114937875281932e-18
    +0xb.ddc67d9f735fp-62,
    // 46
    // -4.7037181944925047952187e-18
    -0xa.d895cbf3d1bcp-61,
    // 47
    // +6.8708685628167005047237e-18
    +0xf.d7d84d149fb98p-61,
    // 48
    // +3.4574897250712229924030e-18
    +0xf.f1e2266155e3p-62,
    // 49
    // -1.0412016878289859463341e-17
    -0xc.0115c09d66988p-60,
    // 50
    // -1.2432483202619037251510e-17
    -0xe.556bdf210f67p-60,
    // 51
    // -1.1840376119668105409201e-17
    -0xd.a6a9867af1448p-60,
    // 52
    // +6.9209310183333186602332e-18
    +0xf.f5658685d0cep-61,
    // 53
    // +4.7061038987834392446048e-18
    +0xa.d9fe506aba798p-61,
    // 54
    // +7.9249622066604665724253e-18
    +0x9.230936e5cb2c8p-60,
    // 55
    // +1.1554704103729265050783e-17
    +0xd.5258c21067fdp-60,
    // 56
    // -7.7589766082994226484497e-18
    -0x8.f20bb27d2b8ep-60,
    // 57
    // +4.6378700281063149820844e-18
    +0xa.b1b71a665af88p-61,
    // 58
    // -9.2776205090512203962931e-19
    -0x8.8e9dbfb7d6cfp-63,
    // 59
    // +1.9834442971833057681879e-17
    +0xb.6f0c11cf82618p-59,
    // 60
    // -8.2969098363358714164068e-18
    -0x9.90d0c862f6abp-60,
    // 61
    // -1.7292394560837026322699e-17
    -0x9.f7e83223f6368p-59,
    // 62
    // -7.9464706201230977389260e-18
    -0x9.2962581e9f09p-60,
    // 63
    // +1.8326259674299083382370e-17
    +0xa.907a83fa4fd08p-59
},
// static const double log2c_h[64]=
{
    // 0
    // -5.0015720860118884072421e-01
    -0x8.00a4d85ccfe58p-4,
    // 1
    // -4.8430368735599227392186e-01
    -0xf.7f6a7250d698p-5,
    // 2
    // -4.6861608872883148135813e-01
    -0xe.fee72aef08518p-5,
    // 3
    // -4.5310179948485773682165e-01
    -0xe.7fcf58517a95p-5,
    // 4
    // -4.3776019851196901200296e-01
    -0xe.0221ad032e14p-5,
    // 5
    // -4.2257400967519970214070e-01
    -0xd.85b9edf639eb8p-5,
    // 6
    // -4.0754162986575970251124e-01
    -0xd.0a94be8105fp-5,
    // 7
    // -3.9266960025906133546769e-01
    -0xc.90bfd667dfbc8p-5,
    // 8
    // -3.7794762159990014094291e-01
    -0xc.18259c4bebf7p-5,
    // 9
    // -3.6337335865878822582786e-01
    -0xb.a0c12a75ab688p-5,
    // 10
    // -3.4894422422733117894467e-01
    -0xb.2a8d13e5e73fp-5,
    // 11
    // -3.3466610360955612035738e-01
    -0xa.b595b042a6398p-5,
    // 12
    // -3.2051852463269098203469e-01
    -0xa.41b010a1e8108p-5,
    // 13
    // -3.0651566523371642780660e-01
    -0x9.cef9f0bc7ef2p-5,
    // 14
    // -2.9264516747898200454969e-01
    -0x9.5d5965f4f30f8p-5,
    // 15
    // -2.7890313305673325450229e-01
    -0x8.ecc64367611f8p-5,
    // 16
    // -2.6529455034741700192313e-01
    -0x8.7d4aff3192e5p-5,
    // 17
    // -2.5180598952717930805179e-01
    -0x8.0ecb6f3e98cf8p-5,
    // 18
    // -2.3845139028856235374754e-01
    -0xf.42c99ebe68288p-6,
    // 19
    // -2.2521685299882820974204e-01
    -0xe.69f3f288d51ap-6,
    // 20
    // -2.1209735461724044114362e-01
    -0xd.9300c8698bep-6,
    // 21
    // -1.9909717637166807202576e-01
    -0xc.be02154f8129p-6,
    // 22
    // -1.8622065759527509087867e-01
    -0xb.eb0a0c8d86468p-6,
    // 23
    // -1.7345267359151128605532e-01
    -0xb.19d93e1eaceap-6,
    // 24
    // -1.6079715780732570240552e-01
    -0xa.4a8029849f2b8p-6,
    // 25
    // -1.4824816386315903260495e-01
    -0x9.7ce5dddeff0dp-6,
    // 26
    // -1.3580946978145705394958e-01
    -0x8.b11a33ccb38a8p-6,
    // 27
    // -1.2348490224731242803635e-01
    -0xf.ce5a7059d9f3p-7,
    // 28
    // -1.1125795497979464043770e-01
    -0xe.3db35f076e748p-7,
    // 29
    // -9.9132031135891057749276e-02
    -0xc.b05bbfdb7b7bp-7,
    // 30
    // -8.7110577778710382435001e-02
    -0xb.26707d58fd258p-7,
    // 31
    // -7.5186636480708501917292e-02
    -0x9.9fb73863f3fep-7,
    // 32
    // -6.3363479853601342717262e-02
    -0x8.1c4b64ddb1478p-7,
    // 33
    // -5.1633800310858485316245e-02
    -0xd.37df6bb40d8ep-8,
    // 34
    // -4.0000690664960730780209e-02
    -0xa.3d7c3a3931fap-8,
    // 35
    // -2.8456489044890082712458e-02
    -0xe.91d9539d12f28p-9,
    // 36
    // -1.7004103538034984199889e-02
    -0x8.b4c3092ff3f6p-9,
    // 37
    // -5.6464771498140687092104e-03
    -0xb.9061559189548p-11,
    // 38
    // +5.6244632025552378923328e-03
    +0xb.84d6ac19a96bp-11,
    // 39
    // +3.3421324707578844992462e-02
    +0x8.8e4cc89ba907p-8,
    // 40
    // +5.5282220522892042136043e-02
    +0xe.26f9c1323263p-8,
    // 41
    // +7.6817617848393804358409e-02
    +0x9.d528e2352e5cp-7,
    // 42
    // +9.8031266043166406798370e-02
    +0xc.8c49dcd208318p-7,
    // 43
    // +1.1893982584982748518243e-01
    +0xf.396b931bc4d6p-7,
    // 44
    // +1.3954950358648141039986e-01
    +0x8.ee610a84ed1d8p-6,
    // 45
    // +1.5987365854604429493691e-01
    +0xa.3b5eb9bc9dccp-6,
    // 46
    // +1.7990831609321317197114e-01
    +0xb.839e2b7985a1p-6,
    // 47
    // +1.9967513955714782936113e-01
    +0xc.c77a3c8e384bp-6,
    // 48
    // +2.1916551076891083171816e-01
    +0xe.06cec74a788dp-6,
    // 49
    // +2.3840332046890699846386e-01
    +0xf.4200002afe2ap-6,
    // 50
    // +2.5738792868397974977768e-01
    +0x8.3c859c02a6e6p-5,
    // 51
    // +2.7612578113610053431870e-01
    +0x8.d605bbf1fbf3p-5,
    // 52
    // +2.9462410255721677154739e-01
    +0x9.6d8f86a317508p-5,
    // 53
    // +3.1288407317201905044612e-01
    +0xa.032575b6d1a8p-5,
    // 54
    // +3.3091425538157531738293e-01
    +0xa.96d97e149c1f8p-5,
    // 55
    // +3.4873103494335555563310e-01
    +0xb.28cdfcc5d27fp-5,
    // 56
    // +3.6632359010767873153114e-01
    +0xb.b8ec3fe881588p-5,
    // 57
    // +3.8370244366174005579140e-01
    +0xc.474a58dd84c28p-5,
    // 58
    // +4.0087896332997197124115e-01
    +0xc.d4001ea502f9p-5,
    // 59
    // +4.1785066607358573032016e-01
    +0xd.5f085c2cbb548p-5,
    // 60
    // +4.3463011944712448553219e-01
    +0xd.e87d6c9c392p-5,
    // 61
    // +4.5120818813022667281842e-01
    +0xe.704c27769d9bp-5,
    // 62
    // +4.6760602303536485946367e-01
    +0xe.f6a0e80b2f398p-5,
    // 63
    // +4.8381521832074941835700e-01
    +0xf.7b6a0d7fd4bc8p-5
},
//static const double log2c_l[64]=
{
    // 0
    // -2.1449646602370978761715e-17
    -0xc.5d68bccb317c8p-59,
    // 1
    // +5.2146353663799522560634e-18
    +0xc.062d6ab285cc8p-61,
    // 2
    // -4.9911634993316000157795e-18
    -0xb.82434d9389dd8p-61,
    // 3
    // +2.2786621042627201325080e-17
    +0xd.22b6342961c98p-59,
    // 4
    // -6.9106738560925063137055e-18
    -0xf.ef5781c732658p-61,
    // 5
    // -2.3432462826625259852546e-17
    -0xd.82056aa04a978p-59,
    // 6
    // +7.8687081412765151042915e-18
    +0x9.126ec70625eep-60,
    // 7
    // +1.9334184611228573151587e-17
    +0xb.2538d7d259a6p-59,
    // 8
    // -1.2301436748356163374887e-17
    -0xe.2ebe480e1b4ap-60,
    // 9
    // -2.2461998578051584616937e-17
    -0xc.f2ce5054485dp-59,
    // 10
    // -1.9214096659164119435142e-17
    -0xb.13800c6a284e8p-59,
    // 11
    // -1.6974525910993281378673e-17
    -0x9.c8ff75323622p-59,
    // 12
    // -1.2294856587670808210191e-17
    -0xe.2ccd193c98e68p-60,
    // 13
    // -7.7085999881752423002610e-18
    -0x8.e32d58f0c9abp-60,
    // 14
    // +2.4605116721149353008412e-17
    +0xe.2f130730cd4f8p-59,
    // 15
    // -2.2922727532473166616922e-17
    -0xd.36cc295c27e28p-59,
    // 16
    // +1.8051491661434902403894e-17
    +0xa.67ee12d1086a8p-59,
    // 17
    // -2.1400669358352541783370e-17
    -0xc.562e6df46cbdp-59,
    // 18
    // -7.2119480348141028679711e-19
    -0xd.4dbf04d6ab09p-64,
    // 19
    // -2.4533908164552988290980e-18
    -0xb.5073e03b47f1p-62,
    // 20
    // +3.9401222803953128183520e-18
    +0x9.15d671d4a77ap-61,
    // 21
    // +5.6386072973613977120831e-18
    +0xd.00723e59aee68p-61,
    // 22
    // +4.4302215713766639771574e-19
    +0x8.2c1ceca71f7cp-64,
    // 23
    // +5.2128388530119103136865e-18
    +0xc.051def73e32a8p-61,
    // 24
    // -1.2788248543265998940800e-17
    -0xe.be6cbda02aec8p-60,
    // 25
    // -2.7681705141296884471315e-18
    -0xc.c41433b02a58p-62,
    // 26
    // -4.0342283409637298560351e-18
    -0x9.4d6359b730dp-61,
    // 27
    // -1.0062848752975346631305e-18
    -0x9.4805e241dc12p-63,
    // 28
    // +3.6546503557352190237837e-18
    +0x8.6d5325a7a02p-61,
    // 29
    // -1.1531969795681585130565e-19
    -0x8.8253d76b46208p-66,
    // 30
    // -4.4356440636938957938928e-18
    -0xa.3a579453b8b3p-61,
    // 31
    // -2.5487055733884416210246e-18
    -0xb.c0fafe5a5b91p-62,
    // 32
    // -6.8646289014644676165177e-18
    -0xf.d42963dfaaf78p-61,
    // 33
    // -2.7879546995496710098907e-18
    -0xc.db6f9ae495038p-62,
    // 34
    // -2.1232494281301189700919e-18
    -0x9.cab0c3878d8f8p-62,
    // 35
    // -1.3274341378741031428158e-18
    -0xc.3e50b3993c648p-63,
    // 36
    // +9.5138544796024040755048e-19
    +0x8.c665375a599dp-63,
    // 37
    // +4.3295656944126515208369e-19
    +0xf.f928c04a9f32p-65,
    // 38
    // +3.6431069408919455803426e-19
    +0xd.70d13579f75fp-65,
    // 39
    // +3.2283276544656401801676e-18
    +0xe.e35629f6530bp-62,
    // 40
    // -2.2804182937545901178314e-18
    -0xa.843e238285c38p-62,
    // 41
    // +1.0255517789147907332820e-18
    +0x9.7584032f53b4p-63,
    // 42
    // -2.0374635588294027769192e-18
    -0x9.65699360f4f28p-62,
    // 43
    // +6.4721957557270087219230e-18
    +0xe.ec8291e0dbe2p-61,
    // 44
    // -5.8590729402733756240804e-18
    -0xd.829611cedd0bp-61,
    // 45
    // +9.9172552756265835753194e-18
    +0xb.6f0e9f660c9dp-60,
    // 46
    // -4.0566924450845088410617e-18
    -0x9.5aa607a6b167p-61,
    // 47
    // -1.3491646822497843886751e-17
    -0xf.8e080315deadp-60,
    // 48
    // -5.6498242895573683459841e-18
    -0xd.07114eb7c2dbp-61,
    // 49
    // -4.2571126038940253831057e-18
    -0x9.d0f4ab00dad8p-61,
    // 50
    // +1.5529488478198704813906e-17
    +0x8.f3bf7cb190fbp-59,
    // 51
    // -1.3008093011306182228893e-17
    -0xe.ff4fb815c6ebp-60,
    // 52
    // -4.9584351046722244076565e-18
    -0xb.6ef187222cfp-61,
    // 53
    // +2.2031557497388569062982e-17
    +0xc.b348b5a3abafp-59,
    // 54
    // -8.3636320123576760496788e-18
    -0x9.a4822af7c93ep-60,
    // 55
    // -1.0881083264393581412186e-17
    -0xc.8b87680f29dd8p-60,
    // 56
    // +1.8626447835897357522770e-17
    +0xa.bcc74dbb6f8b8p-59,
    // 57
    // +1.9596154913078208083364e-17
    +0xb.4be1cd1de07a8p-59,
    // 58
    // -2.6681796702632682552335e-19
    -0x9.d806424a932cp-65,
    // 59
    // -2.2702931111502476654609e-17
    -0xd.165c7cd02221p-59,
    // 60
    // +5.9107830589502188115885e-18
    +0xd.a11c4821a2308p-61,
    // 61
    // -1.2554345523305600867095e-17
    -0xe.796387394aeep-60,
    // 62
    // -2.3540445902129353010042e-17
    -0xd.91f4e6d9c138p-59,
    // 63
    // -2.2605549555268049648892e-17
    -0xd.07fd843108438p-59
},
//static const double log10c_h[64]=
{
    // 0
    // -1.5056232233652483420983e-01
    -0x9.a2d0269c7de7p-6,
    // 1
    // -1.4578993690482444645085e-01
    -0x9.549f50c5e55ep-6,
    // 2
    // -1.4106749915811198081705e-01
    -0x9.073ff9da68038p-6,
    // 3
    // -1.3639723273426879179837e-01
    -0x8.babb7576f30fp-6,
    // 4
    // -1.3177895065992156764523e-01
    -0x8.6f10fad8ad07p-6,
    // 5
    // -1.2720745230023652871942e-01
    -0x8.242ab9dbf7bd8p-6,
    // 6
    // -1.2268225507138147412078e-01
    -0xf.b40d58aa61eep-7,
    // 7
    // -1.1820532806336245257306e-01
    -0xf.215a291f5f33p-7,
    // 8
    // -1.1377357089142994817088e-01
    -0xe.9021e3105cb5p-7,
    // 9
    // -1.0938628058146131205586e-01
    -0xe.005ea0dd3e0d8p-7,
    // 10
    // -1.0504267830612479261987e-01
    -0xd.7209da0128b4p-7,
    // 11
    // -1.0074453571846617161434e-01
    -0xc.e5326b14ac8fp-7,
    // 12
    // -9.6485690080404626356447e-02
    -0xc.59a4a1b6b2bb8p-7,
    // 13
    // -9.2270409376247974897467e-02
    -0xb.cf844b546b0cp-7,
    // 14
    // -8.8094973497282999530533e-02
    -0xb.46b2330e70cb8p-7,
    // 15
    // -8.3958208934739195217212e-02
    -0xa.bf2480cd7f0d8p-7,
    // 16
    // -7.9861617340760776562192e-02
    -0xa.38e7cd5794fbp-7,
    // 17
    // -7.5801155935531286389484e-02
    -0x9.b3da2edefd3c8p-7,
    // 18
    // -7.1781020984636206838658e-02
    -0x9.301ed8cd1ecbp-7,
    // 19
    // -6.7797028281692747753162e-02
    -0x8.ad92b19e30938p-7,
    // 20
    // -6.3847665740769776743235e-02
    -0x8.2c290a242a76p-7,
    // 21
    // -5.9934222139874135382165e-02
    -0xf.57d96400805bp-8,
    // 22
    // -5.6058003748449387881880e-02
    -0xe.59d13cc754a88p-8,
    // 23
    // -5.2214457579158587985368e-02
    -0xd.5ded3bae4d33p-8,
    // 24
    // -4.8404767717519760206191e-02
    -0xc.64413e5135968p-8,
    // 25
    // -4.4627144124919936041263e-02
    -0xb.6caf3c87c8ed8p-8,
    // 26
    // -4.0882724099439604614759e-02
    -0xa.774a4afa7dfp-8,
    // 27
    // -3.7172659588075598890988e-02
    -0x9.8425bd3c72b9p-8,
    // 28
    // -3.3491981705150997150611e-02
    -0x8.92ee361a1318p-8,
    // 29
    // -2.9841714902998934394462e-02
    -0xf.4769cb213f528p-9,
    // 30
    // -2.6222896851012082730659e-02
    -0xd.6d1668c3511fp-9,
    // 31
    // -2.2633432853777012833119e-02
    -0xb.969bfbce6e298p-9,
    // 32
    // -1.9074308065584372889889e-02
    -0x9.c41b92abc87a8p-9,
    // 33
    // -1.5543322683692600838512e-02
    -0xf.ea96ba63fa58p-10,
    // 34
    // -1.2041407737429381946681e-02
    -0xc.549531b861cbp-10,
    // 35
    // -8.5662567737953901336745e-03
    -0x8.c597c2c5363ap-10,
    // 36
    // -5.1187452143245581667741e-03
    -0xa.7bb25a562e4b8p-11,
    // 37
    // -1.6997589919252979739905e-03
    -0xd.eca729013cd8p-13,
    // 38
    // +1.6931321334774252634903e-03
    +0xd.dec16483d3e4p-13,
    // 39
    // +1.0060821231806968759082e-02
    +0xa.4d6248a563c28p-10,
    // 40
    // +1.6641606604301441979521e-02
    +0x8.853fa83c9b4b8p-9,
    // 41
    // +2.3124407167819351766047e-02
    +0xb.d6f6590ce35b8p-9,
    // 42
    // +2.9510351591908970392275e-02
    +0xf.1bfb15f61fb2p-9,
    // 43
    // +3.5804455259848246007071e-02
    +0x9.2a7b146463828p-8,
    // 44
    // +4.2008586459549225600174e-02
    +0xa.c11320feb5328p-8,
    // 45
    // +4.8126766738900525477440e-02
    +0xc.52092934af33p-8,
    // 46
    // +5.4157799613454120357670e-02
    +0xd.dd491a29c15f8p-8,
    // 47
    // +6.0108206395093045915079e-02
    +0xf.63405cb02a1e8p-8,
    // 48
    // +6.5975392756459444454364e-02
    +0x8.71e1b51d6867p-7,
    // 49
    // +7.1766550527033790007891e-02
    +0x9.2fa575baec7ap-7,
    // 50
    // +7.7481487055699529986619e-02
    +0x9.eae9d2798f028p-7,
    // 51
    // +8.3122142698113757330880e-02
    +0xa.a3bf123b1db28p-7,
    // 52
    // +8.8690692315303312764918e-02
    +0xb.5a37737a16fa8p-7,
    // 53
    // +9.4187491190301675381136e-02
    +0xc.0e55f12d64a4p-7,
    // 54
    // +9.9615116862665178953939e-02
    +0xc.c0302a8e61fa8p-7,
    // 55
    // +1.0497850193689399478369e-01
    +0xd.6fef804d0f658p-7,
    // 56
    // +1.1027438874172855454159e-01
    +0xe.1d789e9db5ef8p-7,
    // 57
    // +1.1550594495175260656428e-01
    +0xe.c8e61807da708p-7,
    // 58
    // +1.2067659259300274332549e-01
    +0xf.7254a14a32628p-7,
    // 59
    // +1.2578558419632315801273e-01
    +0x8.0cdefa9b9d148p-6,
    // 60
    // +1.3083670297260352466395e-01
    +0x8.5fa0e8189026p-6,
    // 61
    // +1.3582719891639494225188e-01
    +0x8.b1649050347ap-6,
    // 62
    // +1.4076343908678737304463e-01
    +0x9.0244a7d66a548p-6,
    // 63
    // +1.4564289307326330757952e-01
    +0x9.523691a93f568p-6
},
//static const double log10c_l[64]=
{
    // 0
    // +1.2873790413732614284748e-17
    +0xe.d7ac1a0a1c93p-60,
    // 1
    // -1.0595180375899312805760e-17
    -0xc.372531eb1b1fp-60,
    // 2
    // +1.1434927288288698410931e-17
    +0xd.2efead81f554p-60,
    // 3
    // -2.8087576099586598074953e-18
    -0xc.f3fee6203ecfp-62,
    // 4
    // -1.3383480788079102681503e-17
    -0xf.6e1b37b247738p-60,
    // 5
    // +7.6957313490734651390703e-18
    +0x8.df610542682ep-60,
    // 6
    // +4.0737186321040003072743e-18
    +0x9.64b2f45bb71d8p-61,
    // 7
    // -4.6314160937244337183957e-18
    -0xa.ade7cfe818eb8p-61,
    // 8
    // -4.7885470708690165045221e-19
    -0x8.d553d1b9cd2e8p-64,
    // 9
    // +1.9760091085170511517270e-18
    +0x9.1cdc1b96d05a8p-62,
    // 10
    // +1.0939812941245914080991e-19
    +0x8.1278e49f63288p-66,
    // 11
    // +6.1688964292205635966952e-18
    +0xe.3979457f7e75p-61,
    // 12
    // +6.4231209519675620699063e-18
    +0xe.cf8a985ce8648p-61,
    // 13
    // +4.7292916677209082933994e-18
    +0xa.e7ae59c7718cp-61,
    // 14
    // +3.4265082619812953522205e-18
    +0xf.cd4e93c72e4ep-62,
    // 15
    // +6.3617586466923428186059e-18
    +0xe.ab51c928155a8p-61,
    // 16
    // +1.0210269827037338395907e-18
    +0x9.6ad4f0e28cd98p-63,
    // 17
    // -1.4079267192682916689254e-18
    -0xc.fc5f7b452e7e8p-63,
    // 18
    // -6.4084295992121602217623e-18
    -0xe.c6de802e734bp-61,
    // 19
    // +7.9367260193374655553605e-19
    +0xe.a4034d01203bp-64,
    // 20
    // +5.9976404763036243501469e-18
    +0xd.d461cdb6d6d38p-61,
    // 21
    // -1.9149588205326397220567e-18
    -0x8.d4c8ca58522cp-62,
    // 22
    // +5.8081273772390582774010e-19
    +0xa.b6cf83d6be91p-64,
    // 23
    // +1.5466019084952071453767e-18
    +0xe.43cf7d6b90988p-63,
    // 24
    // +1.7015851903831986136962e-19
    +0xc.8e341bbe37db8p-66,
    // 25
    // -2.0914167689571339469030e-18
    -0x9.a51beed1ff948p-62,
    // 26
    // +1.2903418609941665092853e-18
    +0xb.e6bbcbc2e6edp-63,
    // 27
    // -3.3721768268101543636224e-18
    -0xf.8d29e8975679p-62,
    // 28
    // +2.6142633043372212669022e-18
    +0xc.0e609a1ac6dap-62,
    // 29
    // +4.0736382438166164879490e-19
    +0xf.07714a6115c6p-65,
    // 30
    // -1.6847272593237159082277e-18
    -0xf.89f32432f48cp-63,
    // 31
    // +1.3827002207602254008032e-18
    +0xc.c0ceffb3733d8p-63,
    // 32
    // -1.1928366933481471563567e-18
    -0xb.008189e0c848p-63,
    // 33
    // -7.2503426368970574835871e-19
    -0xd.5fe0a438049bp-64,
    // 34
    // -5.5153890863433443416821e-19
    -0xa.2c91a08e3896p-64,
    // 35
    // -2.4801656783625494072008e-19
    -0x9.267343dd8591p-65,
    // 36
    // -1.4107072955772745154079e-19
    -0xa.68c0307d9f32p-66,
    // 37
    // +1.0317956782756884341184e-19
    +0xf.3a038c7ff417p-67,
    // 38
    // -1.0420075893535816355043e-19
    -0xf.6097e73852688p-67,
    // 39
    // -4.9210696389008524972886e-19
    -0x9.13e8d08d7c218p-64,
    // 40
    // +1.0206168257815889931594e-18
    +0x9.69dd042ce87ep-63,
    // 41
    // -6.0833690523919354181566e-20
    -0x8.fa3b5a795f53p-67,
    // 42
    // -5.8727368391241899758397e-19
    -0xa.d55251d55d248p-64,
    // 43
    // +2.2828665468989873957762e-18
    +0xa.872213ec05c98p-62,
    // 44
    // -1.4083347717135106557244e-19
    -0xa.6444e8431f7ap-66,
    // 45
    // +1.7671817782479621006980e-18
    +0x8.2651eb7fd1adp-62,
    // 46
    // -2.1379853640846611929009e-18
    -0x9.dc166d59b45c8p-62,
    // 47
    // +1.1279969218760795054071e-18
    +0xa.67684d38fe758p-63,
    // 48
    // +5.4624032897859985574898e-18
    +0xc.986f0bf933c08p-61,
    // 49
    // +1.7815011692934730031960e-18
    +0x8.3739b0b808a78p-62,
    // 50
    // -1.3492403448724202328792e-19
    -0x9.f4a4988dbddep-66,
    // 51
    // +3.1068248101626431033541e-18
    +0xe.53e42eb8ba848p-62,
    // 52
    // +1.4499865966219676623751e-18
    +0xd.5faf1e0c55cc8p-63,
    // 53
    // +1.0148256150727199471149e-18
    +0x9.5c3071b94f53p-63,
    // 54
    // +2.2137845799587356418872e-18
    +0xa.3593559e22c28p-62,
    // 55
    // -4.7395840577196047711394e-19
    -0x8.be348ddd80a58p-64,
    // 56
    // +4.2746406505147707173073e-18
    +0x9.db4d6e76a2138p-61,
    // 57
    // -2.8301077467152796188100e-18
    -0xd.0d3394f268be8p-62,
    // 58
    // -4.3450693084262342239858e-18
    -0xa.04e04f32f78cp-61,
    // 59
    // +1.8637512159937790592672e-18
    +0x8.98543dd8ba6dp-62,
    // 60
    // -1.0054106379997972397863e-17
    -0xb.9772ccbc22e68p-60,
    // 61
    // +6.8121156957540855452307e-19
    +0xc.90ee414ceae5p-64,
    // 62
    // -5.5993206437131504661633e-18
    -0xc.e941698d3295p-61,
    // 63
    // -1.6570052336257987544435e-18
    -0xf.487e3480587d8p-63
}
};

template struct cftal::math::log_data<double>;

