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

const float
cftal::math::j01y01_data<float>::_max_small_y1;
alignas(64) const float
cftal::math::j01y01_data<float>::_y1_coeffs[j01y01_data<float>::ENTRIES]={
    // 0
    // +1.5985707045e+00f
    +0xc.c9df7p-3f,
    // 1
    // -1.0000000000e+00f
    -0x8p-3f,
    // 2
    // +0.0000000000e+00f
    +0x0p+0f,
    // 3
    // +0.0000000000e+00f
    +0x0p+0f,
    // 4
    // -1.9661766291e-01f
    -0xc.95624p-6f,
    // 5
    // +5.1086789370e-01f
    +0x8.2c83dp-4f,
    // 6
    // -6.5241867304e-01f
    -0xa.704e9p-4f,
    // 7
    // +6.4314693213e-01f
    +0xa.4a547p-4f,
    // 8
    // -6.2374818325e-01f
    -0x9.fadf6p-4f,
    // 9
    // +5.4953688383e-01f
    +0x8.cae73p-4f,
    // 10
    // -4.3467679620e-01f
    -0xd.e8df5p-5f,
    // 11
    // +8.6947637796e-01f
    +0xd.e9601p-4f,
    // 12
    // +4.0603378437e-09f
    +0x8.b831cp-31f,
    // 13
    // -7.8121310472e-01f
    -0xc.7fd95p-4f,
    // 14
    // +2.0719305382e-08f
    +0xb.1fa3cp-29f,
    // 15
    // +2.9400820732e+00f
    +0xb.c2a4ep-2f,
    // 16
    // -2.1971414089e+00f
    -0x8.c9df7p-2f,
    // 17
    // +8.2889272335e-08f
    +0xb.200dcp-27f,
    // 18
    // -1.2840078215e-15f
    -0xb.90b87p-53f,
    // 19
    // -4.8140125000e-04f
    -0xf.c6495p-15f,
    // 20
    // +1.2651742436e-03f
    +0xa.5d434p-13f,
    // 21
    // -2.6483149268e-03f
    -0xa.d8f5ap-12f,
    // 22
    // +7.3727681302e-03f
    +0xf.19743p-11f,
    // 23
    // -4.7860830091e-03f
    -0x9.cd493p-11f,
    // 24
    // -3.2853301615e-02f
    -0x8.6912fp-8f,
    // 25
    // -1.1851511151e-01f
    -0xf.2b80dp-7f,
    // 26
    // +5.2078634501e-01f
    +0x8.55241p-4f,
    // 27
    // +1.2171629038e-08f
    +0xd.11b64p-30f,
    // 28
    // +0.0000000000e+00f
    +0x0p+0f,
    // 29
    // +0.0000000000e+00f
    +0x0p+0f,
    // 30
    // +4.5563521385e+00f
    +0x9.1cda3p-1f,
    // 31
    // -3.6830227375e+00f
    -0xe.bb6a5p-2f,
    // 32
    // -1.1908200293e-07f
    -0xf.fba06p-27f,
    // 33
    // -6.4075787235e-16f
    -0xb.8af96p-54f,
    // 34
    // +1.0221268667e-06f
    +0x8.93003p-23f,
    // 35
    // +3.6088764318e-05f
    +0x9.75e04p-18f,
    // 36
    // -4.2695718003e-04f
    -0xd.fd939p-15f,
    // 37
    // -5.2573473658e-04f
    -0x8.9d176p-14f,
    // 38
    // +1.2095886283e-02f
    +0xc.62dd3p-10f,
    // 39
    // +1.4687557705e-02f
    +0xf.0a415p-10f,
    // 40
    // -1.9300410151e-01f
    -0xc.5a2dep-6f,
    // 41
    // -6.8214136562e-09f
    -0xe.a61cap-31f,
    // 42
    // -2.6189702864e-17f
    -0xf.18ebp-59f,
    // 43
    // +4.1672992706e-01f
    +0xd.55dap-5f,
    // 44
    // +1.1340386408e-09f
    +0x9.bdc7p-33f,
    // 45
    // +6.1855902672e+00f
    +0xc.5f05bp-1f,
    // 46
    // -5.4296808243e+00f
    -0xa.dbff2p-1f,
    // 47
    // -2.1651435134e-07f
    -0xe.87b03p-26f,
    // 48
    // +1.3601054732e-15f
    +0xc.40309p-53f,
    // 49
    // -2.5832407573e-06f
    -0xa.d5bbdp-22f,
    // 50
    // +4.5782642701e-05f
    +0xc.006bdp-18f,
    // 51
    // +1.4636613196e-04f
    +0x9.979dcp-16f,
    // 52
    // -2.1657298785e-03f
    -0x8.deeebp-12f,
    // 53
    // -4.1600484401e-03f
    -0x8.85104p-11f,
    // 54
    // +5.0947904587e-02f
    +0xd.0aecp-8f,
    // 55
    // +3.1338673085e-02f
    +0x8.05cfbp-8f,
    // 56
    // -3.4031805396e-01f
    -0xa.e3e2bp-5f,
    // 57
    // +9.1772660582e-09f
    +0x9.daa0bp-30f,
    // 58
    // +0.0000000000e+00f
    +0x0p+0f,
    // 59
    // +0.0000000000e+00f
    +0x0p+0f,
    // 60
    // +7.7687530518e+00f
    +0xf.899ap-1f,
    // 61
    // -6.9415001869e+00f
    -0xd.e20c5p-1f,
    // 62
    // +2.3326600740e-07f
    +0xf.a77acp-26f,
    // 63
    // -3.9225528275e-15f
    -0x8.d532ap-51f,
    // 64
    // -5.4028323575e-06f
    -0xb.549fap-21f,
    // 65
    // -1.5084633560e-05f
    -0xf.d1402p-20f,
    // 66
    // +3.4034744021e-04f
    +0xb.270a9p-15f,
    // 67
    // +5.5588810937e-04f
    +0x9.1b905p-14f,
    // 68
    // -1.1386692524e-02f
    -0xb.a8f4p-10f,
    // 69
    // -6.8260151893e-03f
    -0xd.facc4p-11f,
    // 70
    // +1.4844089746e-01f
    +0x9.800e4p-6f,
    // 71
    // -1.4459301534e-09f
    -0xc.6ba25p-33f,
    // 72
    // -3.5864377530e-17f
    -0xa.5652fp-58f,
    // 73
    // -3.0317375064e-01f
    -0x9.b3997p-5f,
    // 74
    // +1.0441010723e-08f
    +0xb.3600dp-30f,
    // 75
    // +9.3597049713e+00f
    +0x9.5c15ap+0f,
    // 76
    // -8.5960054398e+00f
    -0x8.9893dp+0f,
    // 77
    // -4.2857286076e-07f
    -0xe.6169bp-25f,
    // 78
    // -7.3895857356e-15f
    -0x8.51e73p-50f,
    // 79
    // +1.8943993609e-06f
    +0xf.e4311p-23f,
    // 80
    // -4.3120628106e-05f
    -0xb.4dc6cp-18f,
    // 81
    // -1.0403675697e-04f
    -0xd.a2e4fp-17f,
    // 82
    // +2.0112253260e-03f
    +0x8.3cec3p-12f,
    // 83
    // +2.4179129396e-03f
    +0x9.e75d9p-12f,
    // 84
    // -4.3406393379e-02f
    -0xb.1cae7p-8f,
    // 85
    // -1.5789881349e-02f
    -0x8.159c8p-9f,
    // 86
    // +2.7145987749e-01f
    +0x8.afccap-5f,
    // 87
    // -8.2747675378e-10f
    -0xe.3748p-34f,
    // 88
    // +0.0000000000e+00f
    +0x0p+0f,
    // 89
    // +0.0000000000e+00f
    +0x0p+0f,
    // 90
    // +1.0936279297e+01f
    +0xa.efbp+0f,
    // 91
    // -1.0123404503e+01f
    -0xa.1f977p+0f,
    // 92
    // -1.5254148877e-07f
    -0xa.3ca49p-26f,
    // 93
    // +8.8425268669e-16f
    +0xf.ede55p-54f,
    // 94
    // +5.1049019021e-06f
    +0xa.b4ac6p-21f,
    // 95
    // +1.1195570551e-05f
    +0xb.bd49cp-20f,
    // 96
    // -3.1219908851e-04f
    -0xa.3aea7p-15f,
    // 97
    // -3.6577528226e-04f
    -0xb.fc587p-15f,
    // 98
    // +9.9565600976e-03f
    +0xa.320d7p-10f,
    // 99
    // +4.0099518374e-03f
    +0x8.365eap-11f,
    // 100
    // -1.2423210591e-01f
    -0xf.e6d67p-7f,
    // 101
    // +1.1235011810e-09f
    +0x9.a69afp-33f,
    // 102
    // +5.4418405937e-17f
    +0xf.af5eap-58f,
    // 103
    // +2.5091254711e-01f
    +0x8.0779cp-5f,
    // 104
    // -1.0784167337e-08f
    -0xb.94545p-30f,
    // 105
    // +1.2517456055e+01f
    +0xc.8478p+0f,
    // 106
    // -1.1749155045e+01f
    -0xb.bfc8ap+0f,
    // 107
    // +2.1371577930e-07f
    +0xe.579bfp-26f,
    // 108
    // +3.5232473084e-15f
    +0xf.de071p-52f,
    // 109
    // -1.4436039919e-06f
    -0xc.1c1dbp-23f,
    // 110
    // +4.0240378439e-05f
    +0xa.8c7c7p-18f,
    // 111
    // +7.2710849054e-05f
    +0x9.87c57p-17f,
    // 112
    // -1.8167246599e-03f
    -0xe.e1f2ap-13f,
    // 113
    // -1.5770961763e-03f
    -0xc.eb691p-13f,
    // 114
    // +3.7901602685e-02f
    +0x9.b3eb6p-8f,
    // 115
    // +9.8927002400e-03f
    +0xa.214fep-10f,
    // 116
    // -2.3246176541e-01f
    -0xe.e0a75p-6f,
    // 117
    // +3.2336799904e-11f
    +0x8.e38p-38f,
    // 118
    // +0.0000000000e+00f
    +0x0p+0f,
    // 119
    // +0.0000000000e+00f
    +0x0p+0f,
    // 120
    // +1.4091600418e+01f
    +0xe.17732p+0f,
    // 121
    // -1.3285758018e+01f
    -0xd.49277p+0f,
    // 122
    // -1.3828915257e-07f
    -0x9.47ca2p-26f,
    // 123
    // +1.4868382252e-15f
    +0xd.646a6p-53f,
    // 124
    // -4.7662201723e-06f
    -0x9.fed85p-21f,
    // 125
    // -8.2646693045e-06f
    -0x8.aa87cp-20f,
    // 126
    // +2.8476817533e-04f
    +0x9.54cfp-15f,
    // 127
    // +2.5619126973e-04f
    +0x8.65169p-15f,
    // 128
    // -8.8690044358e-03f
    -0x9.14f4dp-10f,
    // 129
    // -2.7002810966e-03f
    -0xb.0f733p-12f,
    // 130
    // +1.0886710882e-01f
    +0xd.ef5b8p-7f,
    // 131
    // -8.6237250674e-10f
    -0xe.d0c12p-34f,
    // 132
    // +1.9184718883e-17f
    +0xb.0f2a3p-59f,
    // 133
    // -2.1897478402e-01f
    -0xe.03aedp-6f,
    // 134
    // -3.9203871260e-09f
    -0x8.6b417p-31f,
    // 135
    // +1.5668749809e+01f
    +0xf.ab333p+0f,
    // 136
    // -1.4897441864e+01f
    -0xe.e5becp+0f,
    // 137
    // -2.6432306299e-07f
    -0x8.de849p-25f,
    // 138
    // +9.4889992470e-15f
    +0xa.af049p-50f,
    // 139
    // +1.0998627431e-06f
    +0x9.39effp-23f,
    // 140
    // -3.7317051465e-05f
    -0x9.c84e1p-18f,
    // 141
    // -5.3411553381e-05f
    -0xe.00638p-18f,
    // 142
    // +1.6532840673e-03f
    +0xd.8b302p-13f,
    // 143
    // +1.1241295142e-03f
    +0x9.35787p-13f,
    // 144
    // -3.3959154040e-02f
    -0x8.b18c1p-8f,
    // 145
    // -6.9323000498e-03f
    -0xe.32859p-11f,
    // 146
    // +2.0654711127e-01f
    +0xd.38116p-6f,
    // 147
    // -1.4704775175e-09f
    -0xc.a19d4p-33f,
    // 148
    // +0.0000000000e+00f
    +0x0p+0f,
    // 149
    // +0.0000000000e+00f
    +0x0p+0f,
    // 150
    // +1.7241729736e+01f
    +0x8.9ef1p+1f,
    // 151
    // -1.6440057755e+01f
    -0x8.3853dp+1f,
    // 152
    // -2.5277168447e-07f
    -0x8.7b4adp-25f,
    // 153
    // +1.1101825365e-14f
    +0xc.7fe22p-50f,
    // 154
    // +4.4357348088e-06f
    +0x9.4d6acp-21f,
    // 155
    // +6.3148604568e-06f
    +0xd.3e43dp-21f,
    // 156
    // -2.6170443743e-04f
    -0x8.9356p-15f,
    // 157
    // -1.9068858819e-04f
    -0xc.7f394p-16f,
    // 158
    // +8.0507667735e-03f
    +0x8.3e75dp-10f,
    // 159
    // +1.9732448272e-03f
    +0x8.1518ep-12f,
    // 160
    // -9.8049677908e-02f
    -0xc.8ce45p-7f,
    // 161
    // +6.4403071764e-10f
    +0xb.107a2p-34f,
    // 162
    // +2.6940974766e-18f
    +0xc.6ca1p-62f,
    // 163
    // +1.9682760537e-01f
    +0xc.98d2dp-6f,
    // 164
    // +3.1038993598e-10f
    +0xa.aa38p-35f,
    // 165
    // +1.8816822052e+01f
    +0x9.688dap+1f,
    // 166
    // -1.8043401718e+01f
    -0x9.058e3p+1f,
    // 167
    // -5.5858822634e-07f
    -0x9.5f1e4p-24f,
    // 168
    // +1.9213556663e-14f
    +0xa.d0f72p-49f,
    // 169
    // -8.7127955339e-07f
    -0xe.9e1ep-24f,
    // 170
    // +3.4717973904e-05f
    +0x9.19e24p-18f,
    // 171
    // +4.1087507270e-05f
    +0xa.c556p-18f,
    // 172
    // -1.5218167100e-03f
    -0xc.777b2p-13f,
    // 173
    // -8.5103523452e-04f
    -0xd.f1802p-14f,
    // 174
    // +3.0999839306e-02f
    +0xf.df36p-9f,
    // 175
    // +5.2021527663e-03f
    +0xa.a76d2p-11f,
    // 176
    // -1.8772909045e-01f
    -0xc.03c0ep-6f,
    // 177
    // -8.6305762537e-10f
    -0xe.d3c48p-34f,
    // 178
    // +0.0000000000e+00f
    +0x0p+0f,
    // 179
    // +0.0000000000e+00f
    +0x0p+0f,
    // 180
    // +2.0389154434e+01f
    +0xa.31cfdp+1f,
    // 181
    // -1.9590242386e+01f
    -0x9.cb8d1p+1f,
    // 182
    // +6.2924760869e-07f
    +0xa.8e991p-24f,
    // 183
    // +2.0488820669e-14f
    +0xb.88c01p-49f,
    // 184
    // -4.1595280891e-06f
    -0x8.b9213p-21f,
    // 185
    // -4.9917548495e-06f
    -0xa.77ed9p-21f,
    // 186
    // +2.4278248020e-04f
    +0xf.e936dp-16f,
    // 187
    // +1.4856489724e-04f
    +0x9.bc816p-16f,
    // 188
    // -7.4151228182e-03f
    -0xf.2fa8fp-11f,
    // 189
    // -1.5219035558e-03f
    -0xc.77a9cp-13f,
    // 190
    // +8.9913807809e-02f
    +0xb.824bbp-7f,
    // 191
    // -5.3311460801e-10f
    -0x9.28a9bp-34f,
    // 192
    // +2.2657542386e-17f
    +0xd.0fa9cp-59f,
    // 193
    // -1.8029741943e-01f
    -0xb.89fe3p-6f,
    // 194
    // +6.7838761275e-09f
    +0xe.9179bp-31f,
    // 195
    // +2.1963052750e+01f
    +0xa.fb455p+1f,
    // 196
    // -2.1188068390e+01f
    -0xa.9812ap+1f,
    // 197
    // -5.4424964446e-07f
    -0x9.2188dp-24f,
    // 198
    // +9.5718373752e-15f
    +0xa.c6e4fp-50f,
    // 199
    // +7.0151378395e-07f
    +0xb.c4fa9p-24f,
    // 200
    // -3.2502368413e-05f
    -0x8.85327p-18f,
    // 201
    // -3.2760868635e-05f
    -0x8.968b7p-18f,
    // 202
    // +1.4151497744e-03f
    +0xb.97c8cp-13f,
    // 203
    // +6.7234283779e-04f
    +0xb.0402ap-14f,
    // 204
    // -2.8684670106e-02f
    -0xe.afc1dp-9f,
    // 205
    // -4.0887636133e-03f
    -0x8.5fb09p-11f,
    // 206
    // +1.7326603830e-01f
    +0xb.16ca7p-6f,
    // 207
    // -3.5935765474e-09f
    -0xf.6f2dep-32f,
    // 208
    // +0.0000000000e+00f
    +0x0p+0f,
    // 209
    // +0.0000000000e+00f
    +0x0p+0f,
    // 210
    // +2.3534988403e+01f
    +0xb.c47a8p+1f,
    // 211
    // -2.2738035202e+01f
    -0xb.5e77fp+1f,
    // 212
    // +4.8463061830e-07f
    +0x8.2179p-24f,
    // 213
    // +8.2080770606e-15f
    +0x9.3dd13p-50f,
    // 214
    // +3.8934144868e-06f
    +0x8.2a42dp-21f,
    // 215
    // +4.0628506213e-06f
    +0x8.8539fp-21f,
    // 216
    // -2.2708825418e-04f
    -0xe.e1e8ap-16f,
    // 217
    // -1.1978109251e-04f
    -0xf.b32fcp-17f,
    // 218
    // +6.9056116045e-03f
    +0xe.24878p-11f,
    // 219
    // +1.2194972951e-03f
    +0x9.fd78ap-13f,
    // 220
    // -8.3511158824e-02f
    -0xa.b07e6p-7f,
    // 221
    // +3.9754963210e-10f
    +0xd.a8e23p-35f,
    // 222
    // +6.5600716531e-18f
    +0xf.2062p-61f,
    // 223
    // +1.6734600067e-01f
    +0xa.b5ccp-6f,
    // 224
    // -3.7480072379e-09f
    -0x8.0c7d2p-31f,
    // 225
    // +2.5108129501e+01f
    +0xc.8dd73p+1f,
    // 226
    // -2.4331943512e+01f
    -0xc.2a7d2p+1f,
    // 227
    // +9.4060595757e-07f
    +0xf.c7df3p-24f,
    // 228
    // +2.1022275243e-14f
    +0xb.d5a11p-49f,
    // 229
    // -5.7805505094e-07f
    -0x9.b2ba4p-24f,
    // 230
    // +3.0618699384e-05f
    +0x8.06c94p-18f,
    // 231
    // +2.6867579436e-05f
    +0xe.161bp-19f,
    // 232
    // -1.3270591153e-03f
    -0xa.df0b7p-13f,
    // 233
    // -5.4818281205e-04f
    -0x8.fb3edp-14f,
    // 234
    // +2.6813684031e-02f
    +0xd.ba85fp-9f,
    // 235
    // +3.3228255343e-03f
    +0xd.9c3c3p-12f,
    // 236
    // -1.6170161963e-01f
    -0xa.5951cp-6f,
    // 237
    // -6.5602447918e-09f
    -0xe.16886p-31f,
    // 238
    // +0.0000000000e+00f
    +0x0p+0f,
    // 239
    // +0.0000000000e+00f
    +0x0p+0f,
    // 240
    // +2.6679803848e+01f
    +0xd.5703dp+1f,
    // 241
    // -2.5884315491e+01f
    -0xc.f1314p+1f,
    // 242
    // +8.7193376430e-07f
    +0xe.a0ed5p-24f,
    // 243
    // +2.6040935291e-14f
    +0xe.a8e4fp-49f,
    // 244
    // -3.6719100081e-06f
    -0xf.66aefp-22f,
    // 245
    // -3.3839453408e-06f
    -0xe.317bdp-22f,
    // 246
    // +2.1392728377e-04f
    +0xe.051abp-16f,
    // 247
    // +9.9147619039e-05f
    +0xc.fed79p-17f,
    // 248
    // -6.4864554442e-03f
    -0xd.48c55p-11f,
    // 249
    // -1.0053608567e-03f
    -0x8.3c65p-13f,
    // 250
    // +7.8303843737e-02f
    +0xa.05dc4p-7f,
    // 251
    // -3.1432029202e-10f
    -0xa.ccca6p-35f,
    // 252
    // -1.1692612376e-17f
    -0xd.7b0cdp-60f,
    // 253
    // -1.5684178472e-01f
    -0xa.09b22p-6f,
    // 254
    // -1.4899468326e-09f
    -0xc.cc6d8p-33f,
    // 255
    // +2.8252435684e+01f
    +0xe.204fdp+1f,
    // 256
    // -2.7475294113e+01f
    -0xd.bcd67p+1f,
    // 257
    // -8.6729005488e-07f
    -0xe.8cfb8p-24f,
    // 258
    // +1.1059793896e-14f
    +0xc.73c4cp-50f,
    // 259
    // +4.8759807214e-07f
    +0x8.2e37cp-24f,
    // 260
    // -2.8997888876e-05f
    -0xf.3407ep-19f,
    // 261
    // -2.2532543881e-05f
    -0xb.d0445p-19f,
    // 262
    // +1.2530004606e-03f
    +0xa.43bb8p-13f,
    // 263
    // +4.5789376600e-04f
    +0xf.01176p-15f,
    // 264
    // -2.5262722746e-02f
    -0xc.ef3c5p-9f,
    // 265
    // -2.7694194578e-03f
    -0xb.57f26p-12f,
    // 266
    // +1.5218125284e-01f
    +0x9.bd567p-6f,
    // 267
    // +4.5766483936e-09f
    +0x9.d40ap-31f,
    // 268
    // +0.0000000000e+00f
    +0x0p+0f,
    // 269
    // +0.0000000000e+00f
    +0x0p+0f,
    // 270
    // +2.9823930740e+01f
    +0xe.e9769p+1f,
    // 271
    // -2.9029575348e+01f
    -0xe.83c92p+1f,
    // 272
    // -4.7147213422e-07f
    -0xf.d1ea3p-25f,
    // 273
    // -6.6955324443e-15f
    -0xf.13b63p-51f,
    // 274
    // +3.5477280562e-06f
    +0xe.e1581p-22f,
    // 275
    // +2.8672998269e-06f
    +0xc.06bd6p-22f,
    // 276
    // -2.0281033358e-04f
    -0xd.4a97cp-16f,
    // 277
    // -8.3782688307e-05f
    -0xa.fb47dp-17f,
    // 278
    // +6.1342865229e-03f
    +0xc.9022p-11f,
    // 279
    // +8.4724172484e-04f
    +0xd.e196ep-14f,
    // 280
    // -7.3961548507e-02f
    -0x9.77927p-7f,
    // 281
    // +3.5145550359e-10f
    +0xc.136f7p-35f,
    // 282
    // -1.3791307729e-17f
    -0xf.e679cp-60f,
    // 283
    // +1.4809882641e-01f
    +0x9.7a738p-6f,
    // 284
    // +6.3213176915e-09f
    +0xd.932e6p-31f,
    // 285
    // +3.1396202087e+01f
    +0xf.b2b6cp+1f,
    // 286
    // -3.0618286133e+01f
    -0xf.4f24p+1f,
    // 287
    // -3.5882860061e-07f
    -0xc.0a507p-25f,
    // 288
    // -1.4105111969e-14f
    -0xf.e1859p-50f,
    // 289
    // -4.1724675270e-07f
    -0xe.001f5p-25f,
    // 290
    // +2.7589836463e-05f
    +0xe.770b9p-19f,
    // 291
    // +1.9237839297e-05f
    +0xa.160f2p-19f,
    // 292
    // -1.1897457298e-03f
    -0x9.bf13ep-13f,
    // 293
    // -3.8985619904e-04f
    -0xc.c659dp-15f,
    // 294
    // +2.3950753734e-02f
    +0xc.4345fp-9f,
    // 295
    // +2.3542463314e-03f
    +0x9.a49b3p-12f,
    // 296
    // -1.4416600764e-01f
    -0x9.3a041p-6f,
    // 297
    // +3.2950131512e-09f
    +0xe.26e7cp-32f,
    // 298
    // +0.0000000000e+00f
    +0x0p+0f,
    // 299
    // +0.0000000000e+00f
    +0x0p+0f,
    // 300
    // +3.2967567444e+01f
    +0x8.3decap+2f,
    // 301
    // -3.2174118042e+01f
    -0x8.0b24cp+2f,
    // 302
    // -1.9137394247e-07f
    -0xc.d7c78p-26f,
    // 303
    // +8.1120340065e-16f
    +0xe.9d03fp-54f,
    // 304
    // -3.3326323319e-06f
    -0xd.fa63p-22f,
    // 305
    // -2.4752646368e-06f
    -0xa.61cb9p-22f,
    // 306
    // +1.9307590264e-04f
    +0xc.a746bp-16f,
    // 307
    // +7.1999747888e-05f
    +0x9.6fe92p-17f,
    // 308
    // -5.8331359178e-03f
    -0xb.f23e4p-11f,
    // 309
    // -7.2659354191e-04f
    -0xb.e78dep-14f,
    // 310
    // +7.0268876851e-02f
    +0x8.fe921p-7f,
    // 311
    // -2.1951672424e-10f
    -0xf.15c77p-36f,
    // 312
    // +1.0496888886e-18f
    +0x9.ae82p-63f,
    // 313
    // -1.4067365229e-01f
    -0x9.00cc1p-6f,
    // 314
    // +3.2561064955e-11f
    +0x8.f348p-38f,
    // 315
    // +3.4539577484e+01f
    +0x8.a2887p+2f,
    // 316
    // -3.3761016846e+01f
    -0x8.70b48p+2f,
    // 317
    // -9.5040621773e-07f
    -0xf.f1f6bp-24f,
    // 318
    // +1.7033214235e-14f
    +0x9.96bebp-49f,
    // 319
    // +3.6498414602e-07f
    +0xc.3f30ap-25f,
    // 320
    // -2.6360503398e-05f
    -0xd.d20cp-19f,
    // 321
    // -1.6672147467e-05f
    -0x8.bdb2ap-19f,
    // 322
    // +1.1349800043e-03f
    +0x9.4c39cp-13f,
    // 323
    // +3.3710512798e-04f
    +0xb.0bd7cp-15f,
    // 324
    // -2.2822575644e-02f
    -0xb.af669p-9f,
    // 325
    // -2.0333649591e-03f
    -0x8.54234p-12f,
    // 326
    // +1.3729695976e-01f
    +0x8.c9793p-6f,
    // 327
    // +6.7739369669e-10f
    +0xb.a3358p-34f,
    // 328
    // +0.0000000000e+00f
    +0x0p+0f,
    // 329
    // +0.0000000000e+00f
    +0x0p+0f,
    // 330
    // +3.6110843658e+01f
    +0x9.07181p+2f,
    // 331
    // -3.5318134308e+01f
    -0x8.d45c5p+2f,
    // 332
    // -1.5033060663e-07f
    -0xa.16a9p-26f,
    // 333
    // -3.7935878261e-15f
    -0x8.8adacp-51f,
    // 334
    // +3.2175894376e-06f
    +0xd.7edc4p-22f,
    // 335
    // +2.1594412374e-06f
    +0x9.0eaebp-22f,
    // 336
    // -1.8467365589e-04f
    -0xc.1a4f5p-16f,
    // 337
    // -6.2724648160e-05f
    -0x8.38b0ap-17f,
    // 338
    // +5.5719879456e-03f
    +0xb.69539p-11f,
    // 339
    // +6.3206942286e-04f
    +0xa.5b176p-14f,
    // 340
    // -6.7078679800e-02f
    -0x8.9608cp-7f,
    // 341
    // +2.2996621274e-10f
    +0xf.cd9bcp-36f,
    // 342
    // -4.1900159777e-18f
    -0x9.a9595p-61f,
    // 343
    // +1.3426500559e-01f
    +0x8.97cc4p-6f,
    // 344
    // -7.0563666021e-09f
    -0xf.27475p-31f,
    // 345
    // +3.7682655334e+01f
    +0x9.6bb0ap+2f,
    // 346
    // -3.6903556824e+01f
    -0x9.39d3ep+2f,
    // 347
    // +1.5075875126e-06f
    +0xc.a585p-23f,
    // 348
    // +6.0905882896e-15f
    +0xd.b6fc3p-51f,
    // 349
    // -3.2000571082e-07f
    -0xa.bcd4p-25f,
    // 350
    // +2.5278604880e-05f
    +0xd.40d64p-19f,
    // 351
    // +1.4623557945e-05f
    +0xf.557b4p-20f,
    // 352
    // -1.0870038532e-03f
    -0x8.e79ccp-13f,
    // 353
    // -2.9523787089e-04f
    -0x9.aca28p-15f,
    // 354
    // +2.1839203313e-02f
    +0xb.2e821p-9f,
    // 355
    // +1.7792949220e-03f
    +0xe.9373bp-13f,
    // 356
    // -1.3132463396e-01f
    -0x8.679f7p-6f,
    // 357
    // -4.0103738108e-09f
    -0x8.9cb9fp-31f,
    // 358
    // +0.0000000000e+00f
    +0x0p+0f,
    // 359
    // +0.0000000000e+00f
    +0x0p+0f,
    // 360
    // +3.9253849030e+01f
    +0x9.d03f1p+2f,
    // 361
    // -3.8461753845e+01f
    -0x9.9d8d6p+2f,
    // 362
    // -2.5782608049e-08f
    -0xd.d788ep-29f,
    // 363
    // -4.0010180952e-16f
    -0xe.6a49bp-55f,
    // 364
    // -3.0693388453e-06f
    -0xc.dfad7p-22f,
    // 365
    // -1.9082121980e-06f
    -0x8.00ed6p-22f,
    // 366
    // +1.7719993775e-04f
    +0xb.9cebfp-16f,
    // 367
    // +5.5279124354e-05f
    +0xe.7db82p-18f,
    // 368
    // -5.3427284583e-03f
    -0xa.f120ep-11f,
    // 369
    // -5.5638956837e-04f
    -0x9.1daacp-14f,
    // 370
    // +6.4286544919e-02f
    +0x8.3a8aap-7f,
    // 371
    // -1.6053071372e-10f
    -0xb.08161p-36f,
    // 372
    // +1.5866502881e-18f
    +0xe.a25f4p-63f,
    // 373
    // -1.2866006792e-01f
    -0x8.3bf77p-6f,
    // 374
    // +8.3927353955e-10f
    +0xe.6b2ap-34f,
    // 375
    // +4.0825504303e+01f
    +0xa.34d51p+2f,
    // 376
    // -4.0045944214e+01f
    -0xa.02f0cp+2f,
    // 377
    // -4.2639968001e-07f
    -0xe.4ebedp-25f,
    // 378
    // -8.5799380770e-15f
    -0x9.a8ffbp-50f,
    // 379
    // +2.8306104127e-07f
    +0x9.7f79dp-25f,
    // 380
    // -2.4316215786e-05f
    -0xc.bfaadp-19f,
    // 381
    // -1.2959998458e-05f
    -0xd.96ec5p-20f,
    // 382
    // +1.0445447406e-03f
    +0x8.8e91bp-13f,
    // 383
    // +2.6135725784e-04f
    +0x8.906c7p-15f,
    // 384
    // -2.0972257480e-02f
    -0xa.bce03p-9f,
    // 385
    // -1.5740605304e-03f
    -0xc.e50b5p-13f,
    // 386
    // +1.2606950104e-01f
    +0x8.1185dp-6f,
    // 387
    // +3.8178011863e-09f
    +0x8.32dbcp-31f,
    // 388
    // +0.0000000000e+00f
    +0x0p+0f,
    // 389
    // +0.0000000000e+00f
    +0x0p+0f,
    // 390
    // +4.2396640778e+01f
    +0xa.99629p+2f,
    // 391
    // -4.1605068207e+01f
    -0xa.66b97p+2f,
    // 392
    // +1.5879168132e-06f
    +0xd.52068p-23f,
    // 393
    // -3.2948487282e-14f
    -0x9.46305p-48f,
    // 394
    // +2.9859868391e-06f
    +0xc.862ddp-22f,
    // 395
    // +1.6980292230e-06f
    +0xe.3e7d7p-23f,
    // 396
    // -1.7061087419e-04f
    -0xb.2e602p-16f,
    // 397
    // -4.9189879064e-05f
    -0xc.e513bp-18f,
    // 398
    // +5.1394505426e-03f
    +0xa.868d6p-11f,
    // 399
    // +4.9468450015e-04f
    +0x8.1adb7p-14f,
    // 400
    // -6.1816100031e-02f
    -0xf.d32e1p-8f,
    // 401
    // +1.9546450569e-10f
    +0xd.6ea5ep-36f,
    // 402
    // +1.5106894653e-18f
    +0xd.ef03cp-63f,
    // 403
    // +1.2370366603e-01f
    +0xf.d5859p-7f,
    // 404
    // -2.2087600637e-09f
    -0x9.7c8ebp-32f,
    // 405
    // +4.3968177795e+01f
    +0xa.fdf6ap+2f,
    // 406
    // -4.3188217163e+01f
    -0xa.cc0bcp+2f,
    // 407
    // -9.3430725201e-07f
    -0xf.acd1bp-24f,
    // 408
    // -2.1758873728e-14f
    -0xc.3fc8cp-49f,
    // 409
    // -2.5428624895e-07f
    -0x8.884d6p-25f,
    // 410
    // +2.3452521418e-05f
    +0xc.4bbe8p-19f,
    // 411
    // +1.1590060240e-05f
    +0xc.272eep-20f,
    // 412
    // -1.0066351388e-03f
    -0x8.3f112p-13f,
    // 413
    // -2.3348601826e-04f
    -0xf.4d3edp-16f,
    // 414
    // +2.0200543106e-02f
    +0xa.57b9cp-9f,
    // 415
    // +1.4054598287e-03f
    +0xb.83768p-13f,
    // 416
    // -1.2139862776e-01f
    -0xf.89fd8p-7f,
    // 417
    // -2.4368584928e-09f
    -0xa.775abp-32f,
    // 418
    // +0.0000000000e+00f
    +0x0p+0f,
    // 419
    // +0.0000000000e+00f
    +0x0p+0f,
    // 420
    // +4.5539268494e+01f
    +0xb.62836p+2f,
    // 421
    // -4.4748138428e+01f
    -0xb.2fe18p+2f,
    // 422
    // +9.7865415682e-07f
    +0x8.35a4dp-23f,
    // 423
    // -2.2940159429e-14f
    -0xc.ea068p-49f,
    // 424
    // -2.8600434234e-06f
    -0xb.fef2cp-22f,
    // 425
    // -1.5274129055e-06f
    -0xc.d0182p-23f,
    // 426
    // +1.6463114298e-04f
    +0xa.ca0d6p-16f,
    // 427
    // +4.4142871047e-05f
    +0xb.9260cp-18f,
    // 428
    // -4.9575725570e-03f
    -0xa.27322p-11f,
    // 429
    // -4.4359421008e-04f
    -0xe.89235p-15f,
    // 430
    // +5.9610001743e-02f
    +0xf.4299ep-8f,
    // 431
    // -1.2946500816e-10f
    -0x8.e5929p-36f,
    // 432
    // -3.4638936749e-18f
    -0xf.f971ap-62f,
    // 433
    // -1.1927957833e-01f
    -0xf.448dap-7f,
    // 434
    // +3.1797313671e-09f
    +0xd.a826dp-32f,
    // 435
    // +4.7110706329e+01f
    +0xb.c715dp+2f,
    // 436
    // -4.6330398560e+01f
    -0xb.95254p+2f,
    // 437
    // -6.9113139034e-07f
    -0xb.9863p-24f,
    // 438
    // +1.6252436205e-14f
    +0x9.26391p-49f,
    // 439
    // +2.2883065753e-07f
    +0xf.5b47ep-26f,
    // 440
    // -2.2672993509e-05f
    -0xb.e31e2p-19f,
    // 441
    // -1.0443194697e-05f
    -0xa.f352ep-20f,
    // 442
    // +9.7252760315e-04f
    +0xf.ef139p-14f,
    // 443
    // +2.1023191221e-04f
    +0xd.c71b3p-16f,
    // 444
    // -1.9507879391e-02f
    -0x9.fcefdp-9f,
    // 445
    // -1.2649489800e-03f
    -0xa.5cca5p-13f,
    // 446
    // +1.1721120030e-01f
    +0xf.00c6dp-7f,
    // 447
    // +2.4764548190e-09f
    +0xa.a2e41p-32f,
    // 448
    // +0.0000000000e+00f
    +0x0p+0f,
    // 449
    // +0.0000000000e+00f
    +0x0p+0f,
    // 450
    // +4.8681758881e+01f
    +0xc.2ba1fp+2f,
    // 451
    // -4.7891014099e+01f
    -0xb.f9066p+2f,
    // 452
    // +2.8330093826e-08f
    +0xf.35a89p-29f,
    // 453
    // -7.5082578043e-16f
    -0xd.8692ap-54f,
    // 454
    // +2.7593430332e-06f
    +0xb.92d27p-22f,
    // 455
    // +1.3828273495e-06f
    +0xb.99996p-23f,
    // 456
    // -1.5924542095e-04f
    -0xa.6fb1ep-16f,
    // 457
    // -3.9900944103e-05f
    -0xa.75b5p-18f,
    // 458
    // +4.7936360352e-03f
    +0x9.d13efp-11f,
    // 459
    // +4.0072700358e-04f
    +0xd.218abp-15f,
    // 460
    // -5.7624269277e-02f
    -0xe.c076dp-8f,
    // 461
    // +9.3510629795e-11f
    +0xc.da1cep-37f,
    // 462
    // -1.3401711451e-18f
    -0xc.5c63cp-63f,
    // 463
    // +1.1529881507e-01f
    +0xe.c21c9p-7f,
    // 464
    // -1.0542398066e-09f
    -0x9.0e4c4p-33f,
    // 465
    // +5.0253120422e+01f
    +0xc.90332p+2f,
    // 466
    // -4.9472507477e+01f
    -0xc.5e3d9p+2f,
    // 467
    // +1.7968825432e-06f
    +0xf.12c6ap-23f,
    // 468
    // +1.5973346261e-15f
    +0xe.6333fp-53f,
    // 469
    // -2.0872930406e-07f
    -0xe.01f13p-26f,
    // 470
    // +2.1959294827e-05f
    +0xb.8353ap-19f,
    // 471
    // +9.4745828392e-06f
    +0x9.ef506p-20f,
    // 472
    // -9.4162748428e-04f
    -0xf.6d78dp-14f,
    // 473
    // -1.9059298211e-04f
    -0xc.7d9eap-16f,
    // 474
    // +1.8881674856e-02f
    +0x9.aadbep-9f,
    // 475
    // +1.1463860283e-03f
    +0x9.64255p-13f,
    // 476
    // -1.1342919618e-01f
    -0xe.84d91p-7f,
    // 477
    // +8.0044815221e-10f
    +0xd.c0688p-34f,
    // 478
    // +0.0000000000e+00f
    +0x0p+0f,
    // 479
    // +0.0000000000e+00f
    +0x0p+0f,
    // 480
    // +5.1824142456e+01f
    +0xc.f4becp+2f,
    // 481
    // -5.1033733368e+01f
    -0xc.c228bp+2f,
    // 482
    // +9.5180382687e-07f
    +0xf.f7f76p-24f,
    // 483
    // -7.8917475243e-15f
    -0x8.e2a43p-50f,
    // 484
    // -2.7125965971e-06f
    -0xb.60a0ep-22f,
    // 485
    // -1.2552989119e-06f
    -0xa.87bbep-23f,
    // 486
    // +1.5440736024e-04f
    +0xa.1e869p-16f,
    // 487
    // +3.6291592551e-05f
    +0x9.837cdp-18f,
    // 488
    // -4.6449056827e-03f
    -0x9.8344bp-11f,
    // 489
    // -3.6434171489e-04f
    -0xb.f051ep-15f,
    // 490
    // +5.5824521929e-02f
    +0xe.4a841p-8f,
    // 491
    // -1.6245131629e-10f
    -0xb.29dfbp-36f,
    // 492
    // +1.9615301961e-18f
    +0x9.0bc42p-62f,
    // 493
    // -1.1169192940e-01f
    -0xe.4bebdp-7f,
    // 494
    // +1.5845276202e-09f
    +0xd.9c69cp-33f,
    // 495
    // +5.3395435333e+01f
    +0xd.594edp+2f,
    // 496
    // -5.2614551544e+01f
    -0xd.2754dp+2f,
    // 497
    // +7.7701650980e-07f
    +0xd.0942bp-24f,
    // 498
    // -1.4481007403e-14f
    -0x8.26eeep-49f,
    // 499
    // +1.8876583852e-07f
    +0xc.aaf8fp-26f,
    // 500
    // -2.1314281184e-05f
    -0xb.2cc12p-19f,
    // 501
    // -8.6435902631e-06f
    -0x9.103fp-20f,
    // 502
    // +9.1347773559e-04f
    +0xe.f7674p-14f,
    // 503
    // +1.7382795340e-04f
    +0xb.64596p-16f,
    // 504
    // -1.8311973661e-02f
    -0x9.602fep-9f,
    // 505
    // -1.0452538263e-03f
    -0x8.900e6p-13f,
    // 506
    // +1.0999114811e-01f
    +0xe.1430ap-7f,
    // 507
    // -3.0242250926e-09f
    -0xc.fd2bbp-32f,
    // 508
    // +0.0000000000e+00f
    +0x0p+0f,
    // 509
    // +0.0000000000e+00f
    +0x0p+0f,
    // 510
    // +5.4966430664e+01f
    +0xd.bddap+2f,
    // 511
    // -5.4176319122e+01f
    -0xd.8b48dp+2f,
    // 512
    // -9.4108645499e-07f
    -0xf.c9ef8p-24f,
    // 513
    // +2.0143132971e-14f
    +0xb.56ee7p-49f,
    // 514
    // +2.6032523692e-06f
    +0xa.eb389p-22f,
    // 515
    // +1.1522390650e-06f
    +0x9.aa6a2p-23f,
    // 516
    // -1.4989767806e-04f
    -0x9.d2ddap-16f,
    // 517
    // -3.3200671169e-05f
    -0x8.b40f3p-18f,
    // 518
    // +4.5091211796e-03f
    +0x9.3c14p-11f,
    // 519
    // +3.3314796747e-04f
    +0xa.eaa5dp-15f,
    // 520
    // -5.4183434695e-02f
    -0xd.def73p-8f,
    // 521
    // +1.7615038594e-10f
    +0xc.1adedp-36f,
    // 522
    // +2.7433887557e-18f
    +0xc.a6d26p-62f,
    // 523
    // +1.0840380937e-01f
    +0xd.e02d1p-7f,
    // 524
    // -2.4044766178e-09f
    -0xa.53cp-32f,
    // 525
    // +5.6537670135e+01f
    +0xe.22693p+2f,
    // 526
    // -5.5756546021e+01f
    -0xd.f06b4p+2f,
    // 527
    // +1.1412996628e-06f
    +0x9.92ec2p-23f,
    // 528
    // +1.4836495273e-14f
    +0x8.5a2a1p-49f,
    // 529
    // -1.7455285217e-07f
    -0xb.b6cb9p-26f,
    // 530
    // +2.0718645828e-05f
    +0xa.dccf4p-19f,
    // 531
    // +7.9302544691e-06f
    +0x8.50c2fp-20f,
    // 532
    // -8.8768743444e-04f
    -0xe.8b3b2p-14f,
    // 533
    // -1.5938322758e-04f
    -0xa.7201cp-16f,
    // 534
    // +1.7790779471e-02f
    +0x9.1bdf8p-9f,
    // 535
    // +9.5816439716e-04f
    +0xf.b2d53p-14f,
    // 536
    // -1.0684788972e-01f
    -0xd.ad311p-7f,
    // 537
    // -2.8660851470e-11f
    -0xf.c1a8p-39f,
    // 538
    // +0.0000000000e+00f
    +0x0p+0f,
    // 539
    // +0.0000000000e+00f
    +0x0p+0f,
    // 540
    // +5.8108646393e+01f
    +0xe.86f41p+2f,
    // 541
    // -5.7318798065e+01f
    -0xe.54673p+2f,
    // 542
    // -4.7142683002e-07f
    -0xf.d1869p-25f,
    // 543
    // +6.0818860849e-16f
    +0xa.f4c66p-54f,
    // 544
    // -2.5240569812e-06f
    -0xa.962f8p-22f,
    // 545
    // -1.0610049230e-06f
    -0x8.e67dap-23f,
    // 546
    // +1.4578219270e-04f
    +0x9.8dd1cp-16f,
    // 547
    // +3.0522656743e-05f
    +0x8.00574p-18f,
    // 548
    // -4.3845553882e-03f
    -0x8.fac51p-11f,
    // 549
    // -3.0616304139e-04f
    -0xa.08482p-15f,
    // 550
    // +5.2679002285e-02f
    +0xd.7c5fp-8f,
    // 551
    // -4.0728583700e-11f
    -0xb.3204fp-38f,
    // 552
    // -7.5799388195e-19f
    -0xd.fb866p-64f,
    // 553
    // -1.0539008677e-01f
    -0xd.7d6c2p-7f,
    // 554
    // -5.9562377253e-10f
    -0xa.3b94cp-34f,
    // 555
    // +5.9679840088e+01f
    +0xe.eb828p+2f,
    // 556
    // -5.8898494720e+01f
    -0xe.b980fp+2f,
    // 557
    // -1.4509740822e-06f
    -0xc.2bf17p-23f,
    // 558
    // +1.2556675602e-14f
    +0xe.23372p-50f,
    // 559
    // +1.6103240341e-07f
    +0xa.ce84p-26f,
    // 560
    // -2.0172648874e-05f
    -0xa.9386fp-19f,
    // 561
    // -7.3085843724e-06f
    -0xf.53c43p-21f,
    // 562
    // +8.6395285325e-04f
    +0xe.27ae5p-14f,
    // 563
    // +1.4683183690e-04f
    +0x9.9f6dfp-16f,
    // 564
    // -1.7311595380e-02f
    -0x8.dd10cp-9f,
    // 565
    // -8.8253151625e-04f
    -0xe.759bp-14f,
    // 566
    // +1.0395957530e-01f
    +0xd.4e8c2p-7f,
    // 567
    // -1.2975078789e-09f
    -0xb.254p-33f,
    // 568
    // +0.0000000000e+00f
    +0x0p+0f,
    // 569
    // +0.0000000000e+00f
    +0x0p+0f,
    // 570
    // +6.1250797272e+01f
    +0xf.500d1p+2f,
    // 571
    // -6.0461185455e+01f
    -0xf.1d841p+2f,
    // 572
    // +5.8194541452e-07f
    +0x9.c36fcp-24f,
    // 573
    // -1.8064941023e-14f
    -0xa.2b6ebp-49f,
    // 574
    // +2.4679691251e-06f
    +0xa.59f63p-22f,
    // 575
    // +9.7935935628e-07f
    +0x8.37288p-23f,
    // 576
    // -1.4200658188e-04f
    -0x9.4e79ap-16f,
    // 577
    // -2.8183854738e-05f
    -0xe.c6c5ep-19f,
    // 578
    // +4.2697489262e-03f
    +0x8.be94p-11f,
    // 579
    // +2.8263268177e-04f
    +0x9.42e51p-15f,
    // 580
    // -5.1293261349e-02f
    -0xd.218e2p-8f,
    // 581
    // +5.5724605486e-11f
    +0xf.51454p-38f,
    // 582
    // -7.1147200353e-19f
    -0xd.1fd4ep-64f,
    // 583
    // +1.0261459649e-01f
    +0xd.2279ap-7f,
    // 584
    // +5.7636007078e-10f
    +0x9.e6dbcp-34f,
    // 585
    // +6.2821952820e+01f
    +0xf.b49aep+2f,
    // 586
    // -6.2040412903e+01f
    -0xf.82962p+2f,
    // 587
    // +1.7551612927e-06f
    +0xe.b92e2p-23f,
    // 588
    // +4.5027180498e-14f
    +0xc.ac8cep-48f,
    // 589
    // -1.4808171045e-07f
    -0x9.f0064p-26f,
    // 590
    // +1.9665065338e-05f
    +0xa.4f668p-19f,
    // 591
    // +6.7625774136e-06f
    +0xe.2ea19p-21f,
    // 592
    // -8.4201165009e-04f
    -0xd.cba72p-14f,
    // 593
    // -1.3584377302e-04f
    -0x8.e7149p-16f,
    // 594
    // +1.6869075596e-02f
    +0x8.a3104p-9f,
    // 595
    // +8.1635080278e-04f
    +0xd.6006p-14f,
    // 596
    // -1.0129349679e-01f
    -0xc.f72f7p-7f,
    // 597
    // -2.9801481283e-09f
    -0xc.ccb52p-32f,
    // 598
    // +0.0000000000e+00f
    +0x0p+0f,
    // 599
    // +0.0000000000e+00f
    +0x0p+0f
};
