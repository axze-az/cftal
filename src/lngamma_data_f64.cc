//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/math/func_data.h"

template struct cftal::math::lngamma_data<double>;

const double
cftal::math::lngamma_data<double>::
_12_tbl[cftal::math::lngamma_data<double>::ENTRIES]={
// const double lngamma_12_table[]={
    // 1:     // [0, 1.5625e-2] : | p - f | <= 2^-88.5625
    // x^ 10: +0xb.f06de9288b3dp-7,
    +9.3274821135389901494150e-02,
    // x^ 9: -0xe.38df8a992f01p-7,
    -1.1111063258646683427067e-01,
    // x^ 8: +0x8.084892ac45cep-6,
    +1.2550558398751554545214e-01,
    // x^ 7: -0x9.381cde558ce78p-6,
    -1.4404985153505697748066e-01,
    // x^ 6: +0xa.da06582b0d078p-6,
    +1.6955717668697942168698e-01,
    // x^ 5: -0xd.45ce0bd4d54a8p-6,
    -2.0738555102737579738381e-01,
    // x^ 4: +0x8.a8991563ec08p-5,
    +2.7058080842778142738325e-01,
    // x^ 3: -0xc.d26aadf5596b8p-5,
    -4.0068563438653143071733e-01,
    // x^ 3: +0xd.faa035cf5f9p-61,
    +6.0624279526930819476124e-18,
    // x^ 2: +0xd.28d3312983e98p-4,
    +8.2246703342411320303285e-01,
    // x^ 2: +0x8.c35a7c952d07p-59,
    +1.5201554367246473935676e-17,
    // x^ 1: -0x9.3c467e37db0c8p-4,
    -5.7721566490153286554943e-01,
    // x^ 1: +0xb.65c83d89de2p-61,
    +4.9429152939957933998552e-18,
    // x^ 0: +0x0p+0,
    +0.0000000000000000000000e+00,
    // x^ 0: +0x0p+0,
    +0.0000000000000000000000e+00,
    // 1.03125:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-79.28125
    // x^ 10: +0x9.75a990081fa98p-7,
    +7.3903270080561342392222e-02,
    // x^ 9: -0xa.cfee82c05a338p-7,
    -8.4470571368642319298736e-02,
    // x^ 8: +0xc.90f927b3d643p-7,
    +9.8174232851009873845882e-02,
    // x^ 7: -0xe.e12c84cefac48p-7,
    -1.1624676213064878693704e-01,
    // x^ 6: +0x9.099c7e27e317p-6,
    +1.4121162719634255955370e-01,
    // x^ 5: -0xb.6a04ea303fe4p-6,
    -1.7834589834182978940191e-01,
    // x^ 4: +0xf.6497b0899b548p-6,
    +2.4051468124382793800642e-01,
    // x^ 3: -0xb.cd1f6dc26ffa8p-5,
    -3.6878940045744396103444e-01,
    // x^ 3: +0xf.3aa6e9a9ceb3p-60,
    +1.3209146785405997168017e-17,
    // x^ 2: +0xc.9534ba8b2f51p-4,
    +7.8642723911885448195846e-01,
    // x^ 2: -0xb.51a664c0c76e8p-58,
    -3.9270479973200066660110e-17,
    // x^ 1: -0x8.6e66925153abp-4,
    -5.2695328860611811983006e-01,
    // x^ 1: +0x9.c1161d8eb91ap-60,
    +8.4604577728391217174644e-18,
    // x^ 0: -0x8.d491bd30292e8p-9,
    -1.7246775001768067242525e-02,
    // x^ 0: -0xb.d53f88166a18p-66,
    -1.6036706285238001391643e-19,
    // 1.0625:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-80.09375
    // x^ 10: +0xe.02b2c555ec15p-8,
    +5.4728673150677600856007e-02,
    // x^ 9: -0x8.4469b680740b8p-7,
    -6.4587797271912314456266e-02,
    // x^ 8: +0x9.e701def26e6b8p-7,
    +7.7362283573950349491177e-02,
    // x^ 7: -0xc.15fc04a06be9p-7,
    -9.4420912036041998449676e-02,
    // x^ 6: +0xf.234b1b26be87p-7,
    +1.1826456857442144143810e-01,
    // x^ 5: -0x9.dcaf490fb01a8p-6,
    -1.5409452566996298394919e-01,
    // x^ 4: +0xd.bbfc653d2165p-6,
    +2.1459874998665490197780e-01,
    // x^ 3: -0xa.e46d873bfc208p-5,
    -3.4038425839378666504231e-01,
    // x^ 3: -0xe.8fe9b7a84502p-61,
    -6.3153302009253652972189e-18,
    // x^ 2: +0xc.0d25f392e28dp-4,
    +7.5321002145770710178851e-01,
    // x^ 2: +0x8.b5aa7f32a1f28p-58,
    +3.0217609059827086605816e-17,
    // x^ 1: -0xf.52c48dec4687p-5,
    -4.7885349006010435868319e-01,
    // x^ 1: -0x9.04ee77a8b804p-60,
    -7.8229642590526010670656e-18,
    // x^ 0: -0x8.6fe063ee9192p-8,
    -3.2957100293577817895496e-02,
    // x^ 0: -0xa.f46248dabe8cp-63,
    -1.1877027902615670772354e-18,
    // 1.09375:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-80.65625
    // x^ 10: +0xa.7aee0435708ap-8,
    +4.0938259151007155844937e-02,
    // x^ 9: -0xc.bde7022b8759p-8,
    -4.9772680311006026188103e-02,
    // x^ 8: +0xf.b72655acf3abp-8,
    +6.1388393322842446653276e-02,
    // x^ 7: -0x9.e07ff738bbc18p-7,
    -7.7163692201308406448668e-02,
    // x^ 6: +0xc.beb7703c343fp-7,
    +9.9570207407312566472157e-02,
    // x^ 5: -0x8.8f0e5144ed8f8p-6,
    -1.3373144089174446302870e-01,
    // x^ 4: +0xc.4c50dd3abb28p-6,
    +1.9215795139727953610986e-01,
    // x^ 3: -0xa.147094660c99p-5,
    -3.1499508842570655975379e-01,
    // x^ 3: +0xa.881024b48425p-59,
    +1.8269233918077041686072e-17,
    // x^ 2: +0xb.8f67b741b0fa8p-4,
    +7.2251102051364901601715e-01,
    // x^ 2: -0xf.74c8c9f4c9b8p-60,
    -1.3406106776203199070837e-17,
    // x^ 1: -0xd.d915b120df88p-5,
    -4.3274960132019746339438e-01,
    // x^ 1: +0x9.2867edc66be98p-59,
    +1.5886312799579080037127e-17,
    // x^ 0: -0xc.1507dab7e885p-8,
    -4.7195902727169850021660e-02,
    // x^ 0: -0xd.2b348b9e4145p-62,
    -2.8555219232843839803338e-18,
    // 1.125:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-81.1875
    // x^ 10: +0xf.d013666d7f2ep-9,
    +3.0884367230781570312637e-02,
    // x^ 9: -0x9.e4504367dcdbp-8,
    -3.8640037971947746586743e-02,
    // x^ 8: +0xc.8d823b8755ec8p-8,
    +4.9034251721728323858418e-02,
    // x^ 7: -0x8.1e577e793233p-7,
    -6.3425957445717523475182e-02,
    // x^ 6: +0xa.c8af983201b68p-7,
    +8.4249448122148698492317e-02,
    // x^ 5: -0xe.eaf47daa4a54p-7,
    -1.1654525886531763578802e-01,
    // x^ 4: +0xb.0c92f6f45f748p-6,
    +1.7264246098192551071016e-01,
    // x^ 3: -0x9.59e4171685b9p-5,
    -2.9222301968928043880425e-01,
    // x^ 3: +0xe.8669631ff5e1p-59,
    +2.5196937559258896602739e-17,
    // x^ 2: +0xb.1ae5b525a8cd8p-4,
    +6.9406672249401724084095e-01,
    // x^ 2: -0x9.d3b9b72b87acp-61,
    -4.2618046868302407654987e-18,
    // x^ 1: -0xc.6e882a72eeafp-5,
    -3.8849266329585485646447e-01,
    // x^ 1: -0xd.1288fa8705afp-60,
    -1.1338501863029058716717e-17,
    // x^ 0: -0xf.5dadecd2b8688p-8,
    -6.0023184126039581809398e-02,
    // x^ 0: -0xa.594469c5bdc9p-63,
    -1.1220083187399176535482e-18,
    // 1.15625:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-81.65625
    // x^ 10: +0xc.05f990c45bb9p-9,
    +2.3483084604030542152930e-02,
    // x^ 9: -0xf.775cfa5ac1518p-9,
    -3.0207543907979538672093e-02,
    // x^ 8: +0xa.16d17959dd4e8p-8,
    +3.9410678984372206345999e-02,
    // x^ 7: -0xd.6b5fdf0174d8p-8,
    -5.2419654793499304012983e-02,
    // x^ 6: +0x9.2aee440357ab8p-7,
    +7.1622641763210523335736e-02,
    // x^ 5: -0xd.0d58fb4a19c08p-7,
    -1.0196983594887677748719e-01,
    // x^ 4: +0x9.f56125b02204p-6,
    +1.5560177498312577348827e-01,
    // x^ 3: -0x8.b2062fd364ebp-5,
    -2.7173146573036655038180e-01,
    // x^ 3: +0xb.335e8e355a088p-59,
    +1.9430050541511641772670e-17,
    // x^ 2: +0xa.aeafa8fbe92d8p-4,
    +6.6764799126992657729573e-01,
    // x^ 2: +0xf.b48b69157e6p-64,
    +8.5138342964030286177357e-19,
    // x^ 1: -0xb.1203cf0f924e8p-5,
    -3.4594908181731814922344e-01,
    // x^ 1: -0xc.2e87e643b9f4p-62,
    -2.6414983831693218038194e-18,
    // x^ 0: -0x9.26bba5271db98p-7,
    -7.1494537011160194661663e-02,
    // x^ 0: +0x8.9a59809a210fp-62,
    +1.8654626882947960704421e-18,
    // 1.1875:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-82.09375
    // x^ 10: +0x9.35f4d67dfc198p-9,
    +1.7989779646988956346432e-02,
    // x^ 9: -0xc.2bd4ae2a4a3a8p-9,
    -2.3771902332687184361548e-02,
    // x^ 8: +0x8.282c37dc44a9p-8,
    +3.1862987172888282416672e-02,
    // x^ 7: -0xb.25f7a7f473828p-8,
    -4.3548086647616592037568e-02,
    // x^ 6: +0xf.a8376bfdbf848p-8,
    +6.1160529961624084116512e-02,
    // x^ 5: -0xb.766e32396aeep-7,
    -8.9551710628107128453479e-02,
    // x^ 4: +0x9.00a66db3b39ap-6,
    +1.4066467965204199064289e-01,
    // x^ 3: -0x8.1a80510ce9838p-5,
    -2.5323501424945543680778e-01,
    // x^ 3: -0xd.321d55c75547p-60,
    -1.1445497429756336892457e-17,
    // x^ 2: +0xa.49f3cc4ba6dfp-4,
    +6.4305476954398677058578e-01,
    // x^ 2: +0xb.89586f059ddep-60,
    +1.0006323582970047065790e-17,
    // x^ 1: -0x9.c28c8767db5p-5,
    -3.0499865003990045408955e-01,
    // x^ 1: -0xf.4afc068c19ecp-62,
    -3.3161208382322733050807e-18,
    // x^ 0: -0xa.73e3179f44a38p-7,
    -8.1661592993019657682474e-02,
    // x^ 0: +0xe.cf059886211ap-62,
    +3.2111204179790577147171e-18,
    // 1.21875:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-82.53125
    // x^ 10: +0xe.357393ad9113p-10,
    +1.3875776184606069402205e-02,
    // x^ 9: -0x9.a36e2409e3728p-9,
    -1.8824998759504735917902e-02,
    // x^ 8: +0xd.436f7a78abc08p-9,
    +2.5905116748922821928725e-02,
    // x^ 7: -0x9.4ea09fc795e7p-8,
    -3.6356009491633409225209e-02,
    // x^ 6: +0xd.6d3dd4b6184e8p-8,
    +5.2448143416854643705793e-02,
    // x^ 5: -0xa.1a3abed0c8448p-7,
    -7.8925460025461316448947e-02,
    // x^ 4: +0x8.2958fd11f2718p-6,
    +1.2752365793111328229337e-01,
    // x^ 3: -0xf.22a92d90747cp-6,
    -2.3649053048740831250996e-01,
    // x^ 3: +0x8.72ac7b1d13068p-60,
    +7.3274236937234060130558e-18,
    // x^ 2: +0x9.ebfa42967653p-4,
    +6.2011171351277449836914e-01,
    // x^ 2: +0xb.79af0660662dp-58,
    +3.9813037998876186616999e-17,
    // x^ 1: -0x8.7f3ecb090701p-5,
    -2.6553287177395656915024e-01,
    // x^ 1: +0xf.47b4a73b8e18p-63,
    +1.6566717940918897578780e-18,
    // x^ 0: -0xb.97e07a7df87ep-7,
    -9.0572414217550745174634e-02,
    // x^ 0: +0xb.06258c78fd5ap-62,
    +2.3904512154482999025253e-18,
    // 1.25:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-82.9375
    // x^ 10: +0xb.088b354441e1p-10,
    +1.0774779440056895390976e-02,
    // x^ 9: -0xf.5b41c96053e48p-10,
    -1.4996555248291703124619e-02,
    // x^ 8: +0xa.d73b442904378p-9,
    +2.1173336096133640177319e-02,
    // x^ 7: -0xf.9cdb61eea9efp-9,
    -3.0493598656295854698595e-02,
    // x^ 6: +0xb.8f79b2f9b002p-8,
    +4.5158010668899378758923e-02,
    // x^ 5: -0x8.ef0a19e15f288p-7,
    -6.9794905316251446003584e-02,
    // x^ 4: +0xe.d68dcfebdfe38p-7,
    +1.1592266704951646738575e-01,
    // x^ 3: -0xe.299d7d0e04858p-6,
    -2.2128998958948672970415e-01,
    // x^ 3: +0xf.830cda173e4ep-60,
    +1.3454441427894725544199e-17,
    // x^ 2: +0x9.94214ec93e338p-4,
    +5.9866457725355537444756e-01,
    // x^ 2: -0xb.17e4ce4f9898p-61,
    -4.8109671849595564532975e-18,
    // x^ 1: -0xe.8e9943cd7c2e8p-6,
    -2.2745353337626542100658e-01,
    // x^ 1: +0xe.e46b1b738ae4p-60,
    +1.2916975932143176470598e-17,
    // x^ 0: -0xc.942be9c657a08p-7,
    -9.8271836421813155149074e-02,
    // x^ 0: -0xe.8f9681b823e18p-61,
    -6.3147795587338672583865e-18,
    // 1.28125:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-83.34375
    // x^ 10: +0x8.9f169f52cfee8p-10,
    +8.4193739646280466720762e-03,
    // x^ 9: -0xc.4d89854678068p-10,
    -1.2014530906178344862867e-02,
    // x^ 8: +0x8.e7ca41a14539p-9,
    +1.7393417846174270835480e-02,
    // x^ 7: -0xd.27441394ab968p-9,
    -2.5690200224139637247278e-02,
    // x^ 6: +0x9.fde0b814de9bp-8,
    +3.9030117933061367341274e-02,
    // x^ 5: -0xf.d9e6f8ba5691p-8,
    -6.1918674206334026188792e-02,
    // x^ 4: +0xd.85db6df34b4d8p-7,
    +1.0564749592466642080790e-01,
    // x^ 3: -0xd.46eff219abae8p-6,
    -2.0745466845135754341278e-01,
    // x^ 3: +0xe.46445b8fdc96p-61,
    +6.1905691316088384929719e-18,
    // x^ 2: +0x9.41da2b4633a5p-4,
    +5.7857720283502911406970e-01,
    // x^ 2: +0xe.edc3fac01382p-60,
    +1.2948645332832443133774e-17,
    // x^ 1: -0xc.33f628e502bf8p-6,
    -1.9067148202524816791303e-01,
    // x^ 1: -0xc.ccfbc62f242cp-61,
    -5.5514259720202769678432e-18,
    // x^ 0: -0xd.6a24f8d3947ap-7,
    -1.0480177068453483402166e-01,
    // x^ 0: -0x9.a2f0e55e41898p-61,
    -4.1791606116629939113578e-18,
    // 1.3125:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-83.71875
    // x^ 10: +0xd.8e54838bf5efp-11,
    +6.6191294331429933323063e-03,
    // x^ 9: -0x9.e8e61c324ee08p-10,
    -9.6775011739528311177638e-03,
    // x^ 8: +0xe.b3a304ee0b2fp-10,
    +1.4357134986776983603951e-02,
    // x^ 7: -0xb.20db689700318p-9,
    -2.1735054509463568733763e-02,
    // x^ 6: +0x8.aad6f16997408p-8,
    +3.3856805742826352745301e-02,
    // x^ 5: -0xe.1af866818ba5p-8,
    -5.5099034334075883134751e-02,
    // x^ 4: +0xc.5ab498cb3e28p-7,
    +9.6518110853581307040372e-02,
    // x^ 3: -0xc.7819fb5a856e8p-6,
    -1.9483041330575803784519e-01,
    // x^ 3: -0xf.bb6f8df6a44dp-61,
    -6.8227415632391134963217e-18,
    // x^ 2: +0x8.f4a6660b1c8ep-4,
    +5.5972900257782809418927e-01,
    // x^ 2: -0xb.8539df2a2a648p-58,
    -3.9969466287501747676813e-17,
    // x^ 1: -0x9.ed3ff04fe7648p-6,
    -1.5510557620983991822250e-01,
    // x^ 1: +0x8.baed1f983d8p-62,
    +1.8930561797385840554950e-18,
    // x^ 0: -0xe.1b14ee504ecf8p-7,
    -1.1020146976863152976644e-01,
    // x^ 0: +0xe.8db9123064fdp-61,
    +6.3116201545268048232556e-18,
    // 1.34375:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-84.09375
    // x^ 10: +0xa.b7b3ff729b5fp-11,
    +5.2331983882376014588500e-03,
    // x^ 9: -0x8.05f4f87643c4p-10,
    -7.8352238320496120360659e-03,
    // x^ 8: +0xc.30e790af5b4d8p-10,
    +1.1905306058760436668797e-02,
    // x^ 7: -0x9.73fc71b5e32a8p-9,
    -1.8463028793979614078369e-02,
    // x^ 6: +0xf.16dce3c63ef4p-9,
    +2.9471304707042650372628e-02,
    // x^ 5: -0xc.969d671c6924p-8,
    -4.9173200296000418862974e-02,
    // x^ 4: +0xb.501e83b70d5p-7,
    +8.8382543863284812601933e-02,
    // x^ 3: -0xb.baebd2b3f65bp-6,
    -1.8328376366102866468211e-01,
    // x^ 3: -0xc.de364584c579p-61,
    -5.5806121955506324430007e-18,
    // x^ 2: +0x8.ac15a8c2003b8p-4,
    +5.4201284333249943880872e-01,
    // x^ 2: +0x9.3f04e8e2b19ap-60,
    +8.0197729240622404848006e-18,
    // x^ 1: -0xf.7280267129f9p-7,
    -1.2068178059628545395476e-01,
    // x^ 1: +0xa.166962cdfc89p-62,
    +2.1873877626878475734110e-18,
    // x^ 0: -0xe.a830bebb9a8f8p-7,
    -1.1450776398779226317171e-01,
    // x^ 0: -0xa.c730a9eb7b0bp-61,
    -4.6742498326295276021862e-18,
    // 1.375:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-84.46875
    // x^ 10: +0x8.84c0f1ff43998p-11,
    +4.1594575740491633239482e-03,
    // x^ 9: -0xd.0e4102224dc58p-11,
    -6.3748434807057259218754e-03,
    // x^ 8: +0xa.2746eb26c6428p-10,
    +9.9154549622595487129439e-03,
    // x^ 7: -0x8.0f984704651cp-9,
    -1.5743979138458125133226e-02,
    // x^ 6: +0xd.2da8a99a1f1c8p-9,
    +2.5738974288343128421497e-02,
    // x^ 5: -0xb.4402f73ab9f9p-8,
    -4.4006524428119933589620e-02,
    // x^ 4: +0xa.61e0a6b13876p-7,
    +8.1111985581120371602282e-02,
    // x^ 3: -0xb.0d7f1b8d865ap-6,
    -1.7269876185136967539080e-01,
    // x^ 3: -0xa.47b3222ff181p-61,
    -4.4582727748097488582588e-18,
    // x^ 2: +0x8.67c3d96bec9bp-4,
    +5.2533326082519837818552e-01,
    // x^ 2: -0xe.a937ef4935dcp-61,
    -6.3581994469578617586929e-18,
    // x^ 1: -0xb.2db51f503b22p-7,
    -8.7332382478472914133505e-02,
    // x^ 1: +0xb.9ccdf5b3ade5p-61,
    +5.0361267659286833990183e-18,
    // x^ 0: -0xf.129ace61dd12p-7,
    -1.1775527074107877689713e-01,
    // x^ 0: +0xb.4772d43f12fdp-62,
    +2.4457640563027002894491e-18,
    // 1.40625:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-84.8125
    // x^ 10: +0xd.9c9475324ed5p-12,
    +3.3231543667573042524777e-03,
    // x^ 9: -0xa.ac13107aab87p-11,
    -5.2110185054823465050644e-03,
    // x^ 8: +0x8.7de62ad57a568p-10,
    +8.2927669185387190703418e-03,
    // x^ 7: -0xd.cc53f97e7442p-10,
    -1.3474762061026497594884e-02,
    // x^ 6: +0xb.8bbf5cbb1df7p-9,
    +2.2550563878720390753596e-02,
    // x^ 5: -0xa.1bd423329b71p-8,
    -3.9487131684479384596820e-02,
    // x^ 4: +0x9.8c63845e0077p-7,
    +7.4596824295443758812141e-02,
    // x^ 3: -0xa.6e2bd1b5b9aep-6,
    -1.6297431449393229296874e-01,
    // x^ 3: -0xf.d78124415cc6p-60,
    -1.3740583579605269993886e-17,
    // x^ 2: +0x8.27578424ccd58p-4,
    +5.0960494631435915291462e-01,
    // x^ 2: +0x9.6c7610c9db598p-58,
    +3.2694945840205061644291e-17,
    // x^ 1: -0xe.142c3667964ap-8,
    -5.4995311052686762787189e-02,
    // x^ 1: -0xa.c4e17acda4b68p-62,
    -2.3351688523795311050884e-18,
    // x^ 0: -0xf.5b64824bfd3p-7,
    -1.1997658121252063878615e-01,
    // x^ 0: -0xa.ef151304d9dd8p-61,
    -4.7418298967008003765898e-18,
    // 1.4375:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-85.15625
    // x^ 10: +0xa.ee34439f4ebd8p-12,
    +2.6685754364341152632123e-03,
    // x^ 9: -0x8.c352c15da55d8p-11,
    -4.2787995586929762278916e-03,
    // x^ 8: +0xe.42d5154321c88p-11,
    +6.9634101022452302501287e-03,
    // x^ 7: -0xb.d9d8024fad0fp-10,
    -1.1573195591990045189013e-02,
    // x^ 6: +0xa.257417060f07p-9,
    +1.9816997347360802705918e-02,
    // x^ 5: -0x9.17f2b4e0ea34p-8,
    -3.5521668586547872070724e-02,
    // x^ 4: +0x8.cc95b5578d768p-7,
    +6.8743432565593301508677e-02,
    // x^ 3: -0x9.db7f17c91f1b8p-6,
    -1.5402200053039091787177e-01,
    // x^ 3: -0xe.469ce6334c18p-63,
    -1.5477887626198108657180e-18,
    // x^ 2: +0xf.d50102fa885dp-5,
    +4.9475145894781358268943e-01,
    // x^ 2: +0xb.1736a59caf018p-59,
    +1.9239258790022303622041e-17,
    // x^ 1: -0xc.17130e7da68d8p-9,
    -2.3613544005297897737661e-02,
    // x^ 1: -0xc.f34d348d60a38p-63,
    -1.4040848354993295410642e-18,
    // x^ 0: -0xf.838fa681fff1p-7,
    -1.2120242719902266093079e-01,
    // x^ 0: +0x9.0a39518a4528p-62,
    +1.9602238910074340177458e-18,
    // 1.46875:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-85.5
    // x^ 10: +0x8.d1eceb0227038p-12,
    +2.1533255204617715410087e-03,
    // x^ 9: -0xe.73da3ac1bf15p-12,
    -3.5284542646960752668162e-03,
    // x^ 8: +0xc.05584829c7f58p-11,
    +5.8695694944823446556614e-03,
    // x^ 7: -0xa.367be1cf760f8p-10,
    -9.9734646390655084385868e-03,
    // x^ 6: +0x8.f136a6fa6a28p-9,
    +1.7465312846259017920403e-02,
    // x^ 5: -0x8.333e633cb54ap-8,
    -3.2031916835611046190380e-02,
    // x^ 4: +0x8.1fd5eec7159e8p-7,
    +6.3471547690068200187063e-02,
    // x^ 3: -0x9.54338b87cc7d8p-6,
    -1.4576424242040517120778e-01,
    // x^ 3: +0x9.54e5841f72f48p-60,
    +8.0938963325286084054831e-18,
    // x^ 2: +0xf.61ed9e890506p-5,
    +4.8070412601387668694031e-01,
    // x^ 2: -0x8.61a2ba9a3286p-60,
    -7.2696963867041635779605e-18,
    // x^ 1: +0xe.0f73edec5363p-11,
    +6.8654114707357768304652e-03,
    // x^ 1: -0xf.1a3ef49f9fb4p-67,
    -1.0233867739256462748710e-19,
    // x^ 0: -0xf.8c0faf0b0a458p-7,
    -1.2146183058765040729821e-01,
    // x^ 0: +0xc.15b9e51f888p-61,
    +5.2409759617169787897381e-18,
    // 1.5:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-85.84375
    // x^ 10: +0xe.4c1430ca075a8p-13,
    +1.7452616069143893091226e-03,
    // x^ 9: -0xb.f79a312c1c13p-12,
    -2.9216788414094972334278e-03,
    // x^ 8: +0xa.2b78d79adfabp-11,
    +4.9657288358132180977611e-03,
    // x^ 7: -0x8.d45d248ea6078p-10,
    -8.6226037562138462683192e-03,
    // x^ 6: +0xf.ce51ced5344cp-10,
    +1.5435484170030641659643e-02,
    // x^ 5: -0xe.d2cea9ba5d08p-9,
    -2.8952081888912017948456e-02,
    // x^ 4: +0xf.07c206d6b0edp-8,
    +5.8712126416768220527054e-02,
    // x^ 3: -0x8.d72ad8c03936p-6,
    -1.3813277403905332985090e-01,
    // x^ 3: -0x8.f5ec63e38fcp-62,
    -1.9430286975862916984057e-18,
    // x^ 2: +0xe.f4f326f917798p-5,
    +4.6740110027233966460969e-01,
    // x^ 2: -0xb.6a4e4c1e0169p-60,
    -9.9011573440802023376835e-18,
    // x^ 1: +0x9.57682cdeb045p-8,
    +3.6489973978576520363681e-02,
    // x^ 1: +0xe.69b9d9538838p-66,
    +1.9533246655943507306589e-19,
    // x^ 0: -0xf.75cad84a60c88p-7,
    -1.2078223763524521816581e-01,
    // x^ 0: -0x9.a3431fa6a7a8p-61,
    -4.1797047487201099512489e-18,
    // 1.53125:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-86.1875
    // x^ 10: +0xb.a42b4526e3c58p-13,
    +1.4210553283331174827947e-03,
    // x^ 9: -0x9.f2c9c0d447e6p-12,
    -2.4288063989547966498028e-03,
    // x^ 8: +0x8.a25466891845p-11,
    +4.2158693114623477932179e-03,
    // x^ 7: -0xf.5083d4a9085dp-11,
    -7.4777888559120434669447e-03,
    // x^ 6: +0xe.019598b722108p-10,
    +1.3677918859487605066083e-02,
    // x^ 5: -0xd.6d930bda58d38p-9,
    -2.6226611325158490778398e-02,
    // x^ 4: +0xd.ed862bfe55de8p-8,
    +5.4405580273246802180953e-02,
    // x^ 3: -0x8.636851b1e983p-6,
    -1.3106735208534575631845e-01,
    // x^ 3: -0x8.eb8d86e20fap-64,
    -4.8356112294240518390776e-19,
    // x^ 2: +0xe.8d9c856622bcp-5,
    +4.5478654913411942217749e-01,
    // x^ 2: -0x9.664e7cf8d25ap-60,
    -8.1528838666787392023763e-18,
    // x^ 1: +0x8.5be91c478a968p-7,
    +6.5304888542489350489184e-02,
    // x^ 1: -0xc.97f0ad55e7b1p-62,
    -2.7307835226983506043069e-18,
    // x^ 0: -0xf.419b2aafd5188p-7,
    -1.1918963989561671967810e-01,
    // x^ 0: +0xe.be870e5fcd51p-61,
    +6.3942984125020658716592e-18,
    // 1.5625:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-86.5
    // x^ 10: +0x9.844916e910018p-13,
    +1.1617114571738091765435e-03,
    // x^ 9: -0x8.4d2fc596f739p-12,
    -2.0267358863160162343875e-03,
    // x^ 8: +0xe.b5cd4ff28c76p-12,
    +3.5913486491693149410542e-03,
    // x^ 7: -0xd.521853a258c78p-11,
    -6.5042400858995727194745e-03,
    // x^ 6: +0xc.716ff0601a7d8p-10,
    +1.2151478811598162219076e-02,
    // x^ 5: -0xc.309e6320fd188p-9,
    -2.3808431244555620237557e-02,
    // x^ 4: +0xc.ed96bd9425d2p-8,
    +5.0500317844260039779059e-02,
    // x^ 3: -0xf.f018bdeb13a08p-7,
    -1.2451466821053448763568e-01,
    // x^ 3: +0x9.3153b9248666p-62,
    +1.9933455417657354080073e-18,
    // x^ 2: +0xe.2b7fc859ad91p-5,
    +4.4280995493811492469405e-01,
    // x^ 2: -0xd.d0588aa1600c8p-59,
    -2.3963211686579084327403e-17,
    // x^ 1: +0xb.f2f1cfd60e0d8p-7,
    +9.3351580126281794025367e-02,
    // x^ 1: -0x9.a48306ca39468p-61,
    -4.1818216884449256239793e-18,
    // x^ 0: -0xe.f04f652417b88p-7,
    -1.1670868338131669406099e-01,
    // x^ 0: -0xb.b948ec935062p-63,
    -1.2710935801962677448407e-18,
    // 1.59375:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-86.78125
    // x^ 10: +0xf.a060f06678c2p-14,
    +9.5376459794453737409126e-04,
    // x^ 9: -0xd.e7ad661003c28p-13,
    -1.6973864262585802459987e-03,
    // x^ 8: +0xc.925ff55287e98p-12,
    +3.0692814226842362289316e-03,
    // x^ 7: -0xb.9e9840a0afc8p-11,
    -5.6735892031482132447096e-03,
    // x^ 6: +0xb.14e5da9c3ccf8p-10,
    +1.0821906536020274233745e-02,
    // x^ 5: -0xb.16b196504d0fp-9,
    -2.1657514189565067741494e-02,
    // x^ 4: +0xc.05040e6cdbfb8p-8,
    +4.6951535722527575067442e-02,
    // x^ 3: -0xf.28a1438f4cc6p-7,
    -1.1842742728058491818999e-01,
    // x^ 3: +0xc.48f44cc791fd8p-61,
    +5.3277598135961468275345e-18,
    // x^ 2: +0xd.ce3cde93a0898p-5,
    +4.3142550918584382513288e-01,
    // x^ 2: +0x9.34303624108p-63,
    +9.9788457108158659931945e-19,
    // x^ 1: +0xf.721076804d69p-7,
    +1.2066846643629539070908e-01,
    // x^ 1: -0xe.95d102ea263p-62,
    -3.1626655527633037122048e-18,
    // x^ 0: -0xe.82abd121c8c9p-7,
    -1.1336276732942554557049e-01,
    // x^ 0: -0xe.3fa38dad1106p-63,
    -1.5448351557578650826007e-18,
    // 1.625:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-87.125
    // x^ 10: +0xc.dff46203d8028p-14,
    +7.8581681742440122415833e-04,
    // x^ 9: -0xb.afa9c6d636a6p-13,
    -1.4265361739436875285203e-03,
    // x^ 8: +0xa.c71e46721d408p-12,
    +2.6313002227945085816085e-03,
    // x^ 7: -0xa.29d52a33e8f3p-11,
    -4.9626019958748154164985e-03,
    // x^ 6: +0x9.e475be69966fp-10,
    +9.6605679958856015276947e-03,
    // x^ 5: -0xa.1b52cc825d728p-9,
    -1.9739711250788345014984e-02,
    // x^ 4: +0xb.313f6fe64be78p-8,
    +4.3720211810338242830465e-02,
    // x^ 3: -0xe.6f09551f1c488p-7,
    -1.1276356369328001394425e-01,
    // x^ 3: +0xb.4048d5e4476p-62,
    +2.4396958805944109672949e-18,
    // x^ 2: +0xd.757c7ca2770bp-5,
    +4.2059158652020423030393e-01,
    // x^ 2: +0xd.738fc0f43a32p-60,
    +1.1667240314316411823925e-17,
    // x^ 1: +0x9.6d3837c863abp-6,
    +1.4729123542343341979333e-01,
    // x^ 1: +0xe.fbb58524d7248p-60,
    +1.2995887809313622287945e-17,
    // x^ 0: -0xd.f96b0306fc028p-7,
    -1.0917413375679536902130e-01,
    // x^ 0: -0xf.e2c33c237c5fp-62,
    -3.4446819416871771097964e-18,
    // 1.65625:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-87.4375
    // x^ 10: +0xa.a5f1af5480598p-14,
    +6.4991571463936801452549e-04,
    // x^ 9: -0x9.dac28a65c454p-13,
    -1.2029456731217722659233e-03,
    // x^ 8: +0x9.44819df01b2e8p-12,
    +2.2625983392632735037575e-03,
    // x^ 7: -0x8.e9cad9a40435p-11,
    -4.3521735829036099080236e-03,
    // x^ 6: +0x8.d9d3b16ce84fp-10,
    +8.6434437791711969667485e-03,
    // x^ 5: -0x9.3aad55d6fdae8p-9,
    -1.8025795677654488785580e-02,
    // x^ 4: +0xa.700d145b6fb98p-8,
    +4.0772263975155896564839e-02,
    // x^ 3: -0xd.c21656199971p-7,
    -1.0748557285405582750748e-01,
    // x^ 3: -0xa.fa6b77c39666p-63,
    -1.1902590815001765367292e-18,
    // x^ 2: +0xd.20ef26f108cap-5,
    +4.1027028661508180285011e-01,
    // x^ 2: -0xa.f2aca23360cep-59,
    -1.8991660118902759287641e-17,
    // x^ 1: +0xb.1694231c8679p-6,
    +1.7325309208727152077145e-01,
    // x^ 1: -0xc.8a1253b7be87p-60,
    -1.0876145598867914505093e-17,
    // x^ 0: -0xd.553e88d50e2d8p-7,
    -1.0416394883405770410700e-01,
    // x^ 0: +0xd.ae51ba5ef7c4p-64,
    +7.4164494914783314005881e-19,
    // 1.6875:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-87.71875
    // x^ 10: +0x8.d6b96ccc6f16p-14,
    +5.3947551641093027460783e-04,
    // x^ 9: -0x8.56411b36edd5p-13,
    -1.0176917655522013141101e-03,
    // x^ 8: +0xf.fbf13d6989a28p-13,
    +1.9511901585229235196045e-03,
    // x^ 7: -0xf.ac698b81845d8p-12,
    -3.8265345429816222631858e-03,
    // x^ 6: +0xf.df65ce4df696p-11,
    +7.7503160080099435524925e-03,
    // x^ 5: -0x8.71774926a3c7p-9,
    -1.6490676574285205446824e-02,
    // x^ 4: +0x9.bf78384bc8dp-8,
    +3.8077844375752123440293e-02,
    // x^ 3: -0xd.20af20145e2p-7,
    -1.0255993906388116698736e-01,
    // x^ 3: +0xf.d2a240f5724a8p-61,
    +6.8620405779786844211286e-18,
    // x^ 2: +0xc.d04c5afaddfap-5,
    +4.0042703408738522519172e-01,
    // x^ 2: -0xe.0243b58fd096p-61,
    -6.0753683597780928625962e-18,
    // x^ 1: +0xc.b59dc50af0d88p-6,
    +1.9858497850851855592857e-01,
    // x^ 1: +0xb.6aa7948fec28p-60,
    +9.9023389945905846199632e-18,
    // x^ 0: -0xc.96cf894b9299p-7,
    -9.8352376974749217142246e-02,
    // x^ 0: -0xe.ec592ef4eecp-65,
    -4.0449511771393730959920e-19,
    // 1.71875:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-87.90625
    // x^ 10: +0xe.b7d11ef5bf7fp-15,
    +4.4915877326266717955300e-04,
    // x^ 9: -0xe.2672daefd09e8p-14,
    -8.6365906076672045114245e-04,
    // x^ 8: +0xd.d298c5ae61f18p-13,
    +1.6873344261052406877627e-03,
    // x^ 7: -0xd.d072fdd3c43p-12,
    -3.3726207595786011905759e-03,
    // x^ 6: +0xe.43330e507b6bp-11,
    +6.9641102546122626154590e-03,
    // x^ 5: -0xf.79b77b4e83248p-10,
    -1.5112749959033016169951e-02,
    // x^ 4: +0x9.1dc92b79a1d8p-8,
    +3.5610745538753874050997e-02,
    // x^ 3: -0xc.89d7e414933cp-7,
    -9.7956644408577875360322e-02,
    // x^ 3: -0xc.fd53dc65428bp-62,
    -2.8166620221295920616125e-18,
    // x^ 2: +0xc.8351d33349218p-5,
    +3.9103022813859328321584e-01,
    // x^ 2: +0x9.126cd6e49212p-60,
    +7.8686824918965885527186e-18,
    // x^ 1: +0xe.4ace3ab642328p-6,
    +2.2331577046955711218779e-01,
    // x^ 1: -0xc.32f571c4801p-61,
    -5.2904979374794474692865e-18,
    // x^ 0: -0xb.bebf550cad91p-7,
    -9.1758648422324756710466e-02,
    // x^ 0: -0xe.54761cedcb42p-63,
    -1.5536538268374722052988e-18,
    // 1.75:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-88.0625
    // x^ 10: +0xc.4b8fa3e12685p-15,
    +3.7521852187545666566099e-04,
    // x^ 9: -0xc.0b70fb58e86bp-14,
    -7.3514970189461170506362e-04,
    // x^ 8: +0xb.fc4e9d8774838p-13,
    +1.4630828338640393306708e-03,
    // x^ 7: -0xc.344e810888edp-12,
    -2.9795710147786204705089e-03,
    // x^ 6: +0xc.d779932d0d9bp-11,
    +6.2703607596919421623971e-03,
    // x^ 5: -0xe.34d182e295aap-10,
    -1.3873361219017311951607e-02,
    // x^ 4: +0x8.897ce6dc0001p-8,
    +3.3347898828651537095347e-02,
    // x^ 3: -0xb.fcae9e8be2d48p-7,
    -9.3648745932816482295813e-02,
    // x^ 3: +0xc.346922ee76fp-64,
    +6.6161969863969813599349e-19,
    // x^ 2: +0xc.39c2e1e01a62p-5,
    +3.8205093494691433342325e-01,
    // x^ 2: +0xf.7fc18aff12aep-59,
    +2.6886560653414320735356e-17,
    // x^ 1: +0xf.d696b3a941e98p-6,
    +2.4747245354686117635445e-01,
    // x^ 1: -0xe.950896cdfcabp-60,
    -1.2648009643936602323692e-17,
    // x^ 0: -0xa.cda7eb43ad37p-7,
    -8.4401121020485553314572e-02,
    // x^ 0: -0xc.308e7b88ac65p-62,
    -2.6432142306593310735005e-18,
    // 1.78125:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-88.53125
    // x^ 10: +0xa.50bf8bee306d8p-15,
    +3.1480172025190122182467e-04,
    // x^ 9: -0xa.484591948f8f8p-14,
    -6.2758249107106370539427e-04,
    // x^ 8: +0xa.6b6c05545ef7p-13,
    +1.2719259053816061970366e-03,
    // x^ 7: -0xa.ce7be736af34p-12,
    -2.6383247344872635953283e-03,
    // x^ 6: +0xb.95c7601696a88p-11,
    +5.6567741583635903004912e-03,
    // x^ 5: -0xd.1000b62828cp-10,
    -1.2756358259175426539400e-02,
    // x^ 4: +0x8.013debd764b5p-8,
    +3.1268949583494201616141e-02,
    // x^ 3: -0xb.7868075afd6p-7,
    -8.9612010566251676380034e-02,
    // x^ 3: -0x9.f05d83bba981p-61,
    -4.3103224632252843465583e-18,
    // x^ 2: +0xb.f367dfbe0bcc8p-5,
    +3.7346261691743048993786e-01,
    // x^ 2: -0x8.16cf91db1b138p-59,
    -1.4032359932053481641448e-17,
    // x^ 1: +0x8.acb08dc53d7ep-5,
    +2.7108028115792115464444e-01,
    // x^ 1: -0xb.b7cb716cc0138p-59,
    -2.0327399563634365894954e-17,
    // x^ 0: -0x9.c41c7318b21ep-7,
    -7.6297336768576806687037e-02,
    // x^ 0: +0xa.202b2ea09bc6p-62,
    +2.1956522769932274353059e-18,
    // 1.8125:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-88.6875
    // x^ 10: +0x8.abe0c5a9af01p-15,
    +2.6463008118812758346500e-04,
    // x^ 9: -0x8.cd6d946958558p-14,
    -5.3725911279436011549343e-04,
    // x^ 8: +0x9.14b8e9c73cf8p-13,
    +1.1085139833323341684856e-03,
    // x^ 7: -0x9.97078ef3c541p-12,
    -2.3412986040381453603509e-03,
    // x^ 6: +0xa.789e183aed0d8p-11,
    +5.1128722328628540758078e-03,
    // x^ 5: -0xc.07980fc2231e8p-10,
    -1.1747718774617438644570e-02,
    // x^ 4: +0xf.07bc6b47be02p-9,
    +2.9355896087391655790988e-02,
    // x^ 3: -0xa.fc4ceb0ce1b1p-7,
    -8.5824599047339883428620e-02,
    // x^ 3: +0x9.da3b12097dc8p-64,
    +5.3410313518091127732291e-19,
    // x^ 2: +0xb.b00dabc0e4338p-5,
    +3.6524089379884688844058e-01,
    // x^ 2: +0xf.7026d6018eddp-60,
    +1.3390410819863752546670e-17,
    // x^ 1: +0x9.69c8595e59a68p-5,
    +2.9416291670604693964108e-01,
    // x^ 1: -0x8.757bb5730e67p-60,
    -7.3369425953838512965559e-18,
    // x^ 0: -0x8.a2a9ab1490f88p-7,
    -6.7464073691674078525615e-02,
    // x^ 0: -0xf.bfc3830b8e4ep-62,
    -3.4150367049786150762745e-18,
    // 1.84375:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-89
    // x^ 10: +0xe.a24cad489a9f8p-16,
    +2.2329685205805559276675e-04,
    // x^ 9: -0xf.1caf7bd817e9p-15,
    -4.6118324797883331490206e-04,
    // x^ 8: +0xf.dde8079d62c9p-14,
    +9.6843394427119562119233e-04,
    // x^ 7: -0x8.87445344443d8p-12,
    -2.0821255641446079730217e-03,
    // x^ 6: +0x9.7b4b96f8e1048p-11,
    +4.6296983192495389305976e-03,
    // x^ 5: -0xb.18648905ee8fp-10,
    -1.0835238326292680882679e-02,
    // x^ 4: +0xe.20a41f8716488p-9,
    +2.7592781876177033956177e-02,
    // x^ 3: -0xa.87b7dd9ce2368p-7,
    -8.2266791543376974193968e-02,
    // x^ 3: -0xa.ce269e3ae3f4p-64,
    -5.8575522715846188641772e-19,
    // x^ 2: +0xb.6f8539a86ea9p-5,
    +3.5736333142582055177883e-01,
    // x^ 2: +0xf.c856eb127d0a8p-59,
    +2.7378405562202648676106e-17,
    // x^ 1: +0xa.22c14bf52649p-5,
    +3.1674256167861714050815e-01,
    // x^ 1: +0xa.b089283ec8fep-60,
    +9.2717438352846656966377e-18,
    // x^ 0: -0xe.d3ac9eeb9c32p-8,
    -5.7917393492616736638823e-02,
    // x^ 0: +0x8.299883f6a183p-63,
    +8.8497822910683031529121e-19,
    // 1.875:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-89.09375
    // x^ 10: +0xc.5f251252f93ep-16,
    +1.8877654140316338631650e-04,
    // x^ 9: -0xd.0196a1467fep-15,
    -3.9691786746587007228548e-04,
    // x^ 8: +0xd.e4e9cfa44c228p-14,
    +8.4803422084146122626042e-04,
    // x^ 7: -0xf.332590cee615p-13,
    -1.8554433540571937423513e-03,
    // x^ 6: +0x8.99c9708a1dbe8p-11,
    +4.1995751828512980011188e-03,
    // x^ 5: -0xa.3f9b871724bdp-10,
    -1.0008268471015869388596e-02,
    // x^ 4: +0xd.4b5758ef2659p-9,
    +2.5965432745192536245771e-02,
    // x^ 3: -0xa.1a1339a88c4c8p-7,
    -7.8920748857031944312190e-02,
    // x^ 3: -0xa.2c996da7707d8p-61,
    -4.4123628928611828645555e-18,
    // x^ 2: +0xb.31a32d798b198p-5,
    +3.4980925447266314476380e-01,
    // x^ 2: +0xe.7bdee462910cp-61,
    +6.2813772473258234309737e-18,
    // x^ 1: +0xa.d7c7221b25f8p-5,
    +3.3884007130944748809043e-01,
    // x^ 1: -0xf.4d240f20cc92p-60,
    -1.3271789455718758582397e-17,
    // x^ 0: -0xc.3446f0b3b6f5p-8,
    -4.7672685399188299837370e-02,
    // x^ 0: +0xe.4510b0833f8p-66,
    +1.9339166107826125309108e-19,
    // 1.90625:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-89.40625
    // x^ 10: +0xa.7f963127ea158p-16,
    +1.6019264981506747803040e-04,
    // x^ 9: -0xb.38e21bfd389b8p-15,
    -3.4247436995273348786170e-04,
    // x^ 8: +0xc.31bf5934c5198p-14,
    +7.4428259251774762147308e-04,
    // x^ 7: -0xd.926627a04b1f8p-13,
    -1.6567225657210386032675e-03,
    // x^ 6: +0xf.a1441c07aa3p-12,
    +3.8159046675710212026544e-03,
    // x^ 5: -0x9.7acc0e59ca048p-10,
    -9.2574962386127324781571e-03,
    // x^ 4: +0xc.862eb944bbae8p-9,
    +2.4461231342108081393549e-02,
    // x^ 3: -0x9.b2d76109dd0f8p-7,
    -7.5770304090589921108823e-02,
    // x^ 3: +0xd.7be522d75b4ap-62,
    +2.9238688487281191112322e-18,
    // x^ 2: +0xa.f63f8232cfde8p-5,
    +3.4255958012954207392298e-01,
    // x^ 2: +0xc.acfd6bf45591p-59,
    +2.1988907063609339761134e-17,
    // x^ 1: +0xb.8902fdca2964p-5,
    +3.6047505920695899206407e-01,
    // x^ 1: -0x9.05a1c13214cep-59,
    -1.5650674212157250086530e-17,
    // x^ 0: -0x9.6819e107dbc4p-8,
    -3.6744706572661434140770e-02,
    // x^ 0: -0x9.440131b92b32p-63,
    -1.0045830511342194967197e-18,
    // 1.9375:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-89.5625
    // x^ 10: +0x8.edd2d53a2ccf8p-16,
    +1.3624570167598563301230e-04,
    // x^ 9: -0x9.b4e80336bea6p-15,
    -2.9622391450874886557887e-04,
    // x^ 8: +0xa.b9d163b0d2a8p-14,
    +6.5465400872458980041646e-04,
    // x^ 7: -0xc.243e83e87dcf8p-13,
    -1.4821263314528166418066e-03,
    // x^ 6: +0xe.39b4b4ea064c8p-12,
    +3.4730013709363791347962e-03,
    // x^ 5: -0x8.c7d2429c0052p-10,
    -8.5747578768862811604556e-03,
    // x^ 4: +0xb.cfb09f98d9418p-9,
    +2.3068923456252676124079e-02,
    // x^ 3: -0x9.51893593992b8p-7,
    -7.2800780449321464415924e-02,
    // x^ 3: +0xa.d587f0d641868p-61,
    +4.6985443060228242233650e-18,
    // x^ 2: +0xa.bd353a50e72ap-5,
    +3.3559667005395010797031e-01,
    // x^ 2: +0xc.6f7227cdf26ap-61,
    +5.3929671598612215101413e-18,
    // x^ 1: +0xc.369b994bd49c8p-5,
    +3.8166599217096891516476e-01,
    // x^ 1: -0xa.b2057be142e2p-59,
    -1.8553554834440419867667e-17,
    // x^ 0: -0xc.e02615d0f1778p-9,
    -2.5147619402988870968008e-02,
    // x^ 0: -0xd.c7b3cbbbfc6p-68,
    -4.6688751554513597058870e-20,
    // 1.96875:     // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-89.5
    // x^ 10: +0xf.37f2be15c23b8p-17,
    +1.1610830464860328063628e-04,
    // x^ 9: -0x8.6a6e8c609f3p-15,
    -2.5682828777904252726128e-04,
    // x^ 8: +0x9.7446cc87668ap-14,
    +5.7703889807783842816336e-04,
    // x^ 7: -0xa.e1d8dde50f79p-13,
    -1.3283954314448590157405e-03,
    // x^ 6: +0xc.f7be575567c6p-12,
    +3.1659541321804093166881e-03,
    // x^ 5: -0x8.24ccd0bb4433p-10,
    -7.9528810882189653053143e-03,
    // x^ 4: +0xb.268b8e9b286p-9,
    +2.1778451116532648867974e-02,
    // x^ 3: -0x8.f5b8c21ab985p-7,
    -6.9998831536804001496321e-02,
    // x^ 3: +0x8.fb86ac057cc9p-62,
    +1.9477743378709061611138e-18,
    // x^ 2: +0xa.866218ea02748p-5,
    +3.2890419832263134702899e-01,
    // x^ 2: +0xd.434e67bf49c98p-59,
    +2.3007490217446817361567e-17,
    // x^ 1: +0xc.e0b5756fa515p-5,
    +4.0243027626744043434570e-01,
    // x^ 1: -0xa.35b973d1350ap-61,
    -4.4278214034624055732735e-18,
    // x^ 0: -0xd.345a8b76abb4p-10,
    -1.2895025980167409973554e-02,
    // x^ 0: -0xb.f36362aa1188p-64,
    -6.4785065609501319655841e-19,
    // 2:     // [-1.5625e-2, 0] : | p - f | <= 2^-99.625
    // x^ 10: +0xd.830f18d49b148p-17,
    +1.0308799066046564539643e-04,
    // x^ 9: -0xe.9dd93c4e0b8bp-16,
    -2.2303155520136318202759e-04,
    // x^ 8: +0x8.59b7f7e55b55p-14,
    +5.0967183741131472270169e-04,
    // x^ 7: -0x9.c562ddc2fe2dp-13,
    -1.1927538854193038032891e-03,
    // x^ 6: +0xb.d6eb7570f9c7p-12,
    +2.8905103309270823927490e-03,
    // x^ 5: -0xf.2027e10c792a8p-11,
    -7.3855510286731833671792e-03,
    // x^ 4: +0xa.8991563ec242p-9,
    +2.0580808427784549885509e-02,
    // x^ 3: -0x8.9f000d2abb038p-7,
    -6.7352301053198102009922e-02,
    // x^ 3: +0xf.dccbe55beb658p-61,
    +6.8792568018124628186724e-18,
    // x^ 2: +0xa.51a6625307d3p-5,
    +3.2246703342411320303285e-01,
    // x^ 2: +0x8.c39ed13947848p-59,
    +1.5203363063936687840822e-17,
    // x^ 1: +0xd.8773039049e7p-5,
    +4.2278433509846713445057e-01,
    // x^ 1: +0xb.65c838110018p-61,
    +4.9429151525443432978187e-18,
    // x^ 0: +0x0p+0,
    +0.0000000000000000000000e+00,
    // x^ 0: +0x0p+0,
    +0.0000000000000000000000e+00
};
