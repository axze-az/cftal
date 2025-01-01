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
cftal::math::j01y01_data<float>::_max_small_j1;
alignas(64) const float
cftal::math::j01y01_data<float>::_j1_coeffs[j01y01_data<float>::ENTRIES]={
    // 0
    // +9.2059189081e-01f
    +0xe.babe9p-4f,
    // 1
    // +0.0000000000e+00f
    +0x0p+0f,
    // 2
    // +0.0000000000e+00f
    +0x0p+0f,
    // 3
    // +0.0000000000e+00f
    +0x0p+0f,
    // 4
    // +2.4125642994e-06f
    +0xa.1e78ap-22f,
    // 5
    // -5.7790275605e-05f
    -0xf.263d6p-18f,
    // 6
    // +2.7123237487e-06f
    +0xb.6055ep-22f,
    // 7
    // +2.6030137669e-03f
    +0xa.a9753p-12f,
    // 8
    // +2.6542076625e-07f
    +0x8.e7f27p-25f,
    // 9
    // -6.2500029802e-02f
    -0x8.00004p-7f,
    // 10
    // +1.2552177076e-09f
    +0xa.c840cp-33f,
    // 11
    // +5.0000000000e-01f
    +0x8p-4f,
    // 12
    // -8.3337781120e-12f
    -0x9.29cp-40f,
    // 13
    // +0.0000000000e+00f
    +0x0p+0f,
    // 14
    // +0.0000000000e+00f
    +0x0p+0f,
    // 15
    // +2.8364448547e+00f
    +0xb.5885p-2f,
    // 16
    // -1.8411837816e+00f
    -0xe.babe9p-3f,
    // 17
    // +2.8924679318e-10f
    +0x9.f03dep-35f,
    // 18
    // +1.0564516691e-17f
    +0xc.2e185p-60f,
    // 19
    // +6.0632382883e-06f
    +0xc.b72d2p-21f,
    // 20
    // +8.9461736934e-06f
    +0x9.61786p-20f,
    // 21
    // -3.9474255755e-04f
    -0xc.ef573p-15f,
    // 22
    // -3.7214028998e-04f
    -0xc.31bd3p-15f,
    // 23
    // +1.3801679015e-02f
    +0xe.2207p-10f,
    // 24
    // +6.0589024797e-03f
    +0xc.689c2p-11f,
    // 25
    // -2.0511069894e-01f
    -0xd.2088ap-6f,
    // 26
    // +3.2787297322e-09f
    +0xe.15006p-32f,
    // 27
    // -1.0760793250e-16f
    -0xf.82083p-57f,
    // 28
    // +5.8186525106e-01f
    +0x9.4f51fp-4f,
    // 29
    // -2.7097255995e-08f
    -0xe.8c37fp-29f,
    // 30
    // +4.5815744400e+00f
    +0x9.29c42p-1f,
    // 31
    // -3.8317060471e+00f
    -0xf.53aacp-2f,
    // 32
    // +7.6850589892e-08f
    +0xa.5090fp-27f,
    // 33
    // +3.2613163455e-15f
    +0xe.b00abp-52f,
    // 34
    // -2.4099990696e-06f
    -0xa.1bb78p-22f,
    // 35
    // +4.5576176490e-05f
    +0xb.f290cp-18f,
    // 36
    // +1.7402791127e-04f
    +0xb.67b43p-16f,
    // 37
    // -2.2328949999e-03f
    -0x9.255c3p-12f,
    // 38
    // -5.1795276813e-03f
    -0xa.9b907p-11f,
    // 39
    // +5.3410414606e-02f
    +0xd.ac4e1p-8f,
    // 40
    // +5.2556131035e-02f
    +0xd.74519p-8f,
    // 41
    // -4.0275940299e-01f
    -0xc.e367bp-5f,
    // 42
    // +7.9728748048e-09f
    +0x8.8f913p-30f,
    // 43
    // +0.0000000000e+00f
    +0x0p+0f,
    // 44
    // +0.0000000000e+00f
    +0x0p+0f,
    // 45
    // +6.1735148430e+00f
    +0xc.58d6fp-1f,
    // 46
    // -5.3314428329e+00f
    -0xa.a9b2ep-1f,
    // 47
    // +5.9439560829e-08f
    +0xf.f4a7dp-28f,
    // 48
    // -4.4405019339e-16f
    -0xf.ffa3ep-55f,
    // 49
    // -5.4492224990e-06f
    -0xb.6d877p-21f,
    // 50
    // -1.7089458197e-05f
    -0x8.f5b55p-19f,
    // 51
    // +3.5395880695e-04f
    +0xb.9938cp-15f,
    // 52
    // +6.6524400609e-04f
    +0xa.e63c5p-14f,
    // 53
    // -1.2099169195e-02f
    -0xc.63b98p-10f,
    // 54
    // -9.6782408655e-03f
    -0x9.e917cp-10f,
    // 55
    // +1.6697452962e-01f
    +0xa.afb5fp-6f,
    // 56
    // -1.3656811237e-09f
    -0xb.bb2a2p-33f,
    // 57
    // -3.2780608501e-17f
    -0x9.72c83p-58f,
    // 58
    // -3.4612619877e-01f
    -0xb.13774p-5f,
    // 59
    // -2.9899540621e-09f
    -0xc.d77d4p-32f,
    // 60
    // +7.7759513855e+00f
    +0xf.8d498p-1f,
    // 61
    // -7.0155868530e+00f
    -0xe.07fbp-1f,
    // 62
    // +1.8321172490e-07f
    +0xc.4b8dbp-26f,
    // 63
    // +9.4141657125e-17f
    +0xd.9136dp-57f,
    // 64
    // +2.2033805180e-06f
    +0x9.3ddcap-22f,
    // 65
    // -4.4281623559e-05f
    -0xb.9bb08p-18f,
    // 66
    // -1.2534171401e-04f
    -0x8.36e29p-16f,
    // 67
    // +2.1053035744e-03f
    +0x8.9f922p-12f,
    // 68
    // +3.1302513089e-03f
    +0xc.d24e7p-12f,
    // 69
    // -4.6970441937e-02f
    -0xc.06414p-8f,
    // 70
    // -2.1389210597e-02f
    -0xa.f386dp-9f,
    // 71
    // +3.0011576414e-01f
    +0x9.9a8c6p-5f,
    // 72
    // -1.2394134608e-08f
    -0xd.4edfbp-30f,
    // 73
    // +0.0000000000e+00f
    +0x0p+0f,
    // 74
    // +0.0000000000e+00f
    +0x0p+0f,
    // 75
    // +9.3548917770e+00f
    +0x9.5ada3p+0f,
    // 76
    // -8.5363159180e+00f
    -0x8.894cp+0f,
    // 77
    // -4.4837682367e-07f
    -0xf.0b871p-25f,
    // 78
    // -1.1411467576e-14f
    -0xc.d921bp-50f,
    // 79
    // +5.1367096603e-06f
    +0xa.c5cp-21f,
    // 80
    // +1.3110314285e-05f
    +0xd.bf45fp-20f,
    // 81
    // -3.2657798147e-04f
    -0xa.b388ep-15f,
    // 82
    // -4.4862262439e-04f
    -0xe.b351cp-15f,
    // 83
    // +1.0631781071e-02f
    +0xa.e30ecp-10f,
    // 84
    // +5.1163202152e-03f
    +0xa.7a6cep-11f,
    // 85
    // -1.3477467000e-01f
    -0x8.a025fp-6f,
    // 86
    // +9.1546342729e-10f
    +0xf.ba403p-34f,
    // 87
    // -8.9549745934e-19f
    -0x8.426fp-63f,
    // 88
    // +2.7329993248e-01f
    +0x8.bedf8p-5f,
    // 89
    // +8.9055607333e-09f
    +0x9.8ff12p-30f,
    // 90
    // +1.0939736366e+01f
    +0xa.f0929p+0f,
    // 91
    // -1.0173468590e+01f
    -0xa.2c687p+0f,
    // 92
    // +4.5471998078e-07f
    +0xf.4203dp-25f,
    // 93
    // +1.1986281921e-14f
    +0xd.7ecf8p-50f,
    // 94
    // -1.6656547359e-06f
    -0xd.f8f76p-23f,
    // 95
    // +4.1737977881e-05f
    +0xa.f0fdp-18f,
    // 96
    // +8.6506726802e-05f
    +0xb.56af2p-17f,
    // 97
    // -1.9113218877e-03f
    -0xf.a8552p-13f,
    // 98
    // -1.9267922034e-03f
    -0xf.c8c6bp-13f,
    // 99
    // +4.0411137044e-02f
    +0xa.58626p-8f,
    // 100
    // +1.2272356078e-02f
    +0xc.911fep-10f,
    // 101
    // -2.4970488250e-01f
    -0xf.fb2a3p-6f,
    // 102
    // +6.0588907225e-09f
    +0xd.02e91p-31f,
    // 103
    // +0.0000000000e+00f
    +0x0p+0f,
    // 104
    // +0.0000000000e+00f
    +0x0p+0f,
    // 105
    // +1.2514848709e+01f
    +0xc.83cd2p+0f,
    // 106
    // -1.1706005096e+01f
    -0xb.b4bccp+0f,
    // 107
    // +1.9386519057e-07f
    +0xd.02942p-26f,
    // 108
    // +5.0300708524e-15f
    +0xb.53a37p-51f,
    // 109
    // -4.8714910008e-06f
    -0xa.375cap-21f,
    // 110
    // -9.5932000477e-06f
    -0xa.0f27bp-20f,
    // 111
    // +2.9791373527e-04f
    +0x9.c314ep-15f,
    // 112
    // +3.0351182795e-04f
    +0x9.f20abp-15f,
    // 113
    // -9.3724830076e-03f
    -0x9.98f0bp-10f,
    // 114
    // -3.2489800360e-03f
    -0xd.4ecd7p-12f,
    // 115
    // +1.1580091715e-01f
    +0xe.d2908p-7f,
    // 116
    // -8.5048368348e-10f
    -0xe.9c778p-34f,
    // 117
    // +8.0846995253e-18f
    +0x9.522eap-60f,
    // 118
    // -2.3330441117e-01f
    -0xe.ee75ap-6f,
    // 119
    // -5.8820393001e-09f
    -0xc.a1af7p-31f,
    // 120
    // +1.4093640327e+01f
    +0xe.17f8dp+0f,
    // 121
    // -1.3323692322e+01f
    -0xd.52dd8p+0f,
    // 122
    // +3.8546312453e-07f
    +0xc.ef1a6p-25f,
    // 123
    // -3.8127544877e-15f
    -0x8.95e74p-51f,
    // 124
    // +1.2525556485e-06f
    +0xa.81d7cp-23f,
    // 125
    // -3.8751957618e-05f
    -0xa.28999p-18f,
    // 126
    // -6.1920880398e-05f
    -0x8.1db85p-17f,
    // 127
    // +1.7306286609e-03f
    +0xe.2d643p-13f,
    // 128
    // +1.3195520733e-03f
    +0xa.cf4d2p-13f,
    // 129
    // -3.5778179765e-02f
    -0x9.28c24p-8f,
    // 130
    // -8.1944018602e-03f
    -0x8.641dp-10f,
    // 131
    // +2.1835941076e-01f
    +0xd.f999cp-6f,
    // 132
    // -4.0650225408e-09f
    -0x8.bac51p-31f,
    // 133
    // +0.0000000000e+00f
    +0x0p+0f,
    // 134
    // +0.0000000000e+00f
    +0x0p+0f,
    // 135
    // +1.5667109489e+01f
    +0xf.aac7bp+0f,
    // 136
    // -1.4863588333e+01f
    -0xe.dd142p+0f,
    // 137
    // -3.0077552537e-07f
    -0xa.17a46p-25f,
    // 138
    // +5.2573831553e-15f
    +0xb.d6acdp-51f,
    // 139
    // +4.5566503104e-06f
    +0x9.8e554p-21f,
    // 140
    // +7.1954568739e-06f
    +0xf.17081p-21f,
    // 141
    // -2.7261997457e-04f
    -0x8.eee6fp-15f,
    // 142
    // -2.1957863646e-04f
    -0xe.63eb1p-16f,
    // 143
    // +8.4324022755e-03f
    +0x8.a280fp-10f,
    // 144
    // +2.2897154558e-03f
    +0x9.60f0dp-12f,
    // 145
    // -1.0303781182e-01f
    -0xd.3057dp-7f,
    // 146
    // +6.7666006132e-10f
    +0xb.9ffb8p-34f,
    // 147
    // -1.7968755111e-17f
    -0xa.5bb86p-59f,
    // 148
    // +2.0701265335e-01f
    +0xd.3fb2p-6f,
    // 149
    // -7.0695449494e-10f
    -0xc.2538p-34f,
    // 150
    // +1.7243078232e+01f
    +0x8.9f1d3p+1f,
    // 151
    // -1.6470630646e+01f
    -0x8.3c3dap+1f,
    // 152
    // +5.9487433646e-07f
    +0x9.faf74p-24f,
    // 153
    // -1.6144549619e-14f
    -0x9.16accp-49f,
    // 154
    // -9.6858104826e-07f
    -0x8.20031p-23f,
    // 155
    // +3.5969496821e-05f
    +0x9.6ddf4p-18f,
    // 156
    // +4.6599358029e-05f
    +0xc.373aep-18f,
    // 157
    // -1.5839959960e-03f
    -0xc.f9e16p-13f,
    // 158
    // -9.7201636527e-04f
    -0xf.eceeap-14f,
    // 159
    // +3.2382093370e-02f
    +0x8.4a316p-8f,
    // 160
    // +5.9641110711e-03f
    +0xc.36e97p-11f,
    // 161
    // -1.9646537304e-01f
    -0xc.92e38p-6f,
    // 162
    // +2.1473174350e-09f
    +0x9.39002p-32f,
    // 163
    // +0.0000000000e+00f
    +0x0p+0f,
    // 164
    // +0.0000000000e+00f
    +0x0p+0f,
    // 165
    // +1.8815692902e+01f
    +0x9.6868ap+1f,
    // 166
    // -1.8015527725e+01f
    -0x9.01fcdp+1f,
    // 167
    // -1.3127879583e-07f
    -0x8.cf5a4p-26f,
    // 168
    // -8.5888293819e-16f
    -0xf.78e6p-54f,
    // 169
    // -4.3128602556e-06f
    -0x9.0b73p-21f,
    // 170
    // -5.5904592955e-06f
    -0xb.b95aep-21f,
    // 171
    // +2.5180869852e-04f
    +0x8.40531p-15f,
    // 172
    // +1.6748976486e-04f
    +0xa.fa031p-16f,
    // 173
    // -7.7142687514e-03f
    -0xf.cc7fap-11f,
    // 174
    // -1.7233117251e-03f
    -0xe.1e0bfp-13f,
    // 175
    // +9.3719094992e-02f
    +0xb.fefccp-7f,
    // 176
    // -1.7747880943e-09f
    -0xf.3eccep-33f,
    // 177
    // -4.1922585470e-17f
    -0xc.15574p-58f,
    // 178
    // -1.8801748753e-01f
    -0xc.087a8p-6f,
    // 179
    // -1.0520326832e-09f
    -0x9.0971cp-33f,
    // 180
    // +2.0390113831e+01f
    +0xa.31ef4p+1f,
    // 181
    // -1.9615858078e+01f
    -0x9.ced47p+1f,
    // 182
    // -4.3246529913e-07f
    -0xe.82d94p-25f,
    // 183
    // -1.3206409165e-14f
    -0xe.de7dp-50f,
    // 184
    // +7.7795021980e-07f
    +0xd.0d455p-24f,
    // 185
    // -3.3571348467e-05f
    -0x8.ccef6p-18f,
    // 186
    // -3.6542482121e-05f
    -0x9.94531p-18f,
    // 187
    // +1.4658208238e-03f
    +0xc.020c9p-13f,
    // 188
    // +7.5301749166e-04f
    +0xc.56626p-14f,
    // 189
    // -2.9776554555e-02f
    -0xf.3edf6p-9f,
    // 190
    // -4.5897392556e-03f
    -0x9.66586p-11f,
    // 191
    // +1.8006338179e-01f
    +0xb.86289p-6f,
    // 192
    // -6.9583494522e-09f
    -0xe.f164ap-31f,
    // 193
    // +0.0000000000e+00f
    +0x0p+0f,
    // 194
    // +0.0000000000e+00f
    +0x0p+0f,
    // 195
    // +2.1962226868e+01f
    +0xa.fb2a4p+1f,
    // 196
    // -2.1164369583e+01f
    -0xa.950a1p+1f,
    // 197
    // -2.7605869946e-07f
    -0x9.43538p-25f,
    // 198
    // -8.2570525321e-17f
    -0xb.e6509p-57f,
    // 199
    // +4.0224695113e-06f
    +0x8.6f8cp-21f,
    // 200
    // +4.4889511628e-06f
    +0x9.69fccp-21f,
    // 201
    // -2.3457880889e-04f
    -0xf.5f945p-16f,
    // 202
    // -1.3290399511e-04f
    -0x8.b5c25p-16f,
    // 203
    // +7.1472036652e-03f
    +0xe.a3317p-11f,
    // 204
    // +1.3568095164e-03f
    +0xb.1d6f9p-13f,
    // 205
    // -8.6535900831e-02f
    -0xb.139bcp-7f,
    // 206
    // +4.5649123370e-10f
    +0xf.af56ep-35f,
    // 207
    // -2.0017605388e-18f
    -0x9.3b43p-62f,
    // 208
    // +1.7345905304e-01f
    +0xb.19f4p-6f,
    // 209
    // -3.7671328279e-09f
    -0x8.1700dp-31f,
    // 210
    // +2.3535705566e+01f
    +0xb.c492p+1f,
    // 211
    // -2.2760084152e+01f
    -0xb.614a7p+1f,
    // 212
    // -2.2837109270e-07f
    -0xf.5362bp-26f,
    // 213
    // +4.9257491100e-16f
    +0x8.df99dp-54f,
    // 214
    // -6.3225144231e-07f
    -0xa.9b7fdp-24f,
    // 215
    // +3.1524970836e-05f
    +0x8.439aep-18f,
    // 216
    // +2.9572842323e-05f
    +0xf.81332p-19f,
    // 217
    // -1.3691039057e-03f
    -0xb.37381p-13f,
    // 218
    // -6.0502573615e-04f
    -0x9.e9a97p-14f,
    // 219
    // +2.7702705935e-02f
    +0xe.2f0c9p-9f,
    // 220
    // +3.6727581173e-03f
    +0xf.0b2a8p-12f,
    // 221
    // -1.6718460619e-01f
    -0xa.b3271p-6f,
    // 222
    // +6.2170069093e-09f
    +0xd.59d5fp-31f,
    // 223
    // +0.0000000000e+00f
    +0x0p+0f,
    // 224
    // +0.0000000000e+00f
    +0x0p+0f,
    // 225
    // +2.5107500076e+01f
    +0xc.8dc29p+1f,
    // 226
    // -2.4311326981e+01f
    -0xc.27d99p+1f,
    // 227
    // +1.2338102806e-07f
    +0x8.47ab8p-26f,
    // 228
    // +4.1501255930e-15f
    +0x9.58627p-51f,
    // 229
    // -3.8336406760e-06f
    -0x8.0a2b9p-21f,
    // 230
    // -3.6937512959e-06f
    -0xf.7e22ap-22f,
    // 231
    // +2.2030544642e-04f
    +0xe.701cbp-16f,
    // 232
    // +1.0865757940e-04f
    +0xe.3df18p-17f,
    // 233
    // -6.6864546388e-03f
    -0xd.b1a0cp-11f,
    // 234
    // -1.1038440280e-03f
    -0x9.0aedcp-13f,
    // 235
    // +8.0782197416e-02f
    +0xa.57123p-7f,
    // 236
    // -4.4134879085e-10f
    -0xf.2a252p-35f,
    // 237
    // +1.3551536194e-17f
    +0xf.9fb52p-60f,
    // 238
    // -1.6183820367e-01f
    -0xa.5b8eap-6f,
    // 239
    // -5.9600009372e-09f
    -0xc.cc8b9p-31f,
    // 240
    // +2.6680360794e+01f
    +0xd.57161p+1f,
    // 241
    // -2.5903671265e+01f
    -0xc.f3ab8p+1f,
    // 242
    // -8.2296992332e-07f
    -0xd.cea1p-24f,
    // 243
    // -2.1805734979e-14f
    -0xc.4689ap-49f,
    // 244
    // +5.2938571571e-07f
    +0x8.e1b1cp-24f,
    // 245
    // -2.9776969313e-05f
    -0xf.9c98ep-19f,
    // 246
    // -2.4543269319e-05f
    -0xc.de245p-19f,
    // 247
    // +1.2885010801e-03f
    +0xa.8e2ecp-13f,
    // 248
    // +4.9967475934e-04f
    +0x8.2fc9bp-14f,
    // 249
    // -2.6004021987e-02f
    -0xd.50663p-9f,
    // 250
    // -3.0251494609e-03f
    -0xc.64196p-12f,
    // 251
    // +1.5672498941e-01f
    +0xa.07c84p-6f,
    // 252
    // -3.6365461753e-09f
    -0xf.9e6ccp-32f,
    // 253
    // +0.0000000000e+00f
    +0x0p+0f,
    // 254
    // +0.0000000000e+00f
    +0x0p+0f,
    // 255
    // +2.8251939774e+01f
    +0xe.203f9p+1f,
    // 256
    // -2.7457050323e+01f
    -0xd.ba80ap+1f,
    // 257
    // -2.4755942718e-07f
    -0x8.4e84fp-25f,
    // 258
    // -4.3297102891e-16f
    -0xf.9973fp-55f,
    // 259
    // +3.6278547668e-06f
    +0xf.37612p-22f,
    // 260
    // +3.1068350381e-06f
    +0xd.07f05p-22f,
    // 261
    // -2.0818215853e-04f
    -0xd.a4b79p-16f,
    // 262
    // -9.0930130682e-05f
    -0xb.eb1bep-17f,
    // 263
    // +6.3031427562e-03f
    +0xc.e8a98p-11f,
    // 264
    // +9.2067965306e-04f
    +0xf.159c4p-14f,
    // 265
    // -7.6040036976e-02f
    -0x9.bbae1p-7f,
    // 266
    // +3.6474265275e-10f
    +0xc.884f7p-35f,
    // 267
    // -4.3092933540e-18f
    -0x9.efc2p-61f,
    // 268
    // +1.5228205919e-01f
    +0x9.befd4p-6f,
    // 269
    // +7.2009238572e-09f
    +0xf.76bffp-31f,
    // 270
    // +2.9824375153e+01f
    +0xe.e9852p+1f,
    // 271
    // -2.9046829224e+01f
    -0xe.85fe8p+1f,
    // 272
    // +6.8871594294e-07f
    +0xb.8e033p-24f,
    // 273
    // +1.4490843150e-14f
    +0x8.2859cp-49f,
    // 274
    // -4.5365351298e-07f
    -0xf.38daap-25f,
    // 275
    // +2.8266276786e-05f
    +0xe.d1d5ep-19f,
    // 276
    // +2.0782026695e-05f
    +0xa.e551p-19f,
    // 277
    // -1.2201813515e-03f
    -0x9.fee7ep-13f,
    // 278
    // -4.2160792509e-04f
    -0xd.d0b42p-15f,
    // 279
    // +2.4580780417e-02f
    +0xc.95da2p-9f,
    // 280
    // +2.5478012394e-03f
    +0xa.6f903p-12f,
    // 281
    // -1.4801110327e-01f
    -0x9.79039p-6f,
    // 282
    // -6.2029288372e-09f
    -0xd.5218ap-31f,
    // 283
    // +0.0000000000e+00f
    +0x0p+0f,
    // 284
    // +0.0000000000e+00f
    +0x0p+0f,
    // 285
    // +3.1395801544e+01f
    +0xf.b2a9ap+1f,
    // 286
    // -3.0601922989e+01f
    -0xf.4d0bdp+1f,
    // 287
    // +1.6224673161e-08f
    +0x8.b5e6fp-29f,
    // 288
    // -5.3457076482e-18f
    -0xc.538c8p-61f,
    // 289
    // -3.4649599456e-06f
    -0xe.8878fp-22f,
    // 290
    // -2.6569769034e-06f
    -0xb.24e84p-22f,
    // 291
    // +1.9780895673e-04f
    +0xc.f6afp-16f,
    // 292
    // +7.7519522165e-05f
    +0xa.291fap-17f,
    // 293
    // -5.9781242162e-03f
    -0xc.3e424p-11f,
    // 294
    // -7.8306422802e-04f
    -0xc.d468dp-14f,
    // 295
    // +7.2044439614e-02f
    +0x9.38c09p-7f,
    // 296
    // -3.3232261387e-10f
    -0xb.6b24p-35f,
    // 297
    // +4.7528780565e-18f
    +0xa.f59aap-61f,
    // 298
    // -1.4424289763e-01f
    -0x9.3b469p-6f,
    // 299
    // -4.6190078429e-09f
    -0x9.eb539p-31f,
    // 300
    // +3.2967929840e+01f
    +0x8.3df29p+2f,
    // 301
    // -3.2189678192e+01f
    -0x8.0c23bp+2f,
    // 302
    // -1.7188357333e-06f
    -0xe.6b2bfp-23f,
    // 303
    // +1.5481608695e-15f
    +0xd.f1d0ep-53f,
    // 304
    // +3.8842858885e-07f
    +0xd.08938p-25f,
    // 305
    // -2.6958859962e-05f
    -0xe.225b6p-19f,
    // 306
    // -1.7877946448e-05f
    -0x9.5f899p-19f,
    // 307
    // +1.1614237446e-03f
    +0x9.83aeap-13f,
    // 308
    // +3.6188913509e-04f
    +0xb.dbbfp-15f,
    // 309
    // -2.3366428912e-02f
    -0xb.f6af4p-9f,
    // 310
    // -2.1840194240e-03f
    -0x8.f21c4p-12f,
    // 311
    // +1.4060579240e-01f
    +0x8.ffaf7p-6f,
    // 312
    // +5.3438720116e-09f
    +0xb.79d32p-31f,
    // 313
    // +0.0000000000e+00f
    +0x0p+0f,
    // 314
    // +0.0000000000e+00f
    +0x0p+0f,
    // 315
    // +3.4539245605e+01f
    +0x8.a283p+2f,
    // 316
    // -3.3746181488e+01f
    -0x8.6fc17p+2f,
    // 317
    // -1.4106300341e-06f
    -0xb.d54e1p-23f,
    // 318
    // -3.6441447868e-14f
    -0xa.41e21p-48f,
    // 319
    // +3.3002029340e-06f
    +0xd.d790ep-22f,
    // 320
    // +2.3064253583e-06f
    +0x9.ac816p-22f,
    // 321
    // -1.8877373077e-04f
    -0xc.5f19p-16f,
    // 322
    // -6.7095315899e-05f
    -0x8.cb586p-17f,
    // 323
    // +5.6981435046e-03f
    +0xb.ab77ep-11f,
    // 324
    // +6.7659135675e-04f
    +0xb.15d47p-14f,
    // 325
    // -6.8618290126e-02f
    -0x8.c87bfp-7f,
    // 326
    // +2.7002930447e-10f
    +0x9.4733fp-35f,
    // 327
    // -1.3101030471e-17f
    -0xf.1abdep-60f,
    // 328
    // +1.3735719025e-01f
    +0x8.ca75dp-6f,
    // 329
    // +3.4608720334e-09f
    +0xe.dd44ep-32f,
    // 330
    // +3.6111148834e+01f
    +0x9.071d1p+2f,
    // 331
    // -3.5332305908e+01f
    -0x8.d5448p+2f,
    // 332
    // -1.6418807718e-06f
    -0xd.c5e98p-23f,
    // 333
    // +3.1682874369e-14f
    +0x8.eafdep-48f,
    // 334
    // -3.3945025280e-07f
    -0xb.63dbp-25f,
    // 335
    // +2.5808281862e-05f
    +0xd.87eddp-19f,
    // 336
    // +1.5590429030e-05f
    +0x8.2c831p-19f,
    // 337
    // -1.1102363933e-03f
    -0x9.1855ap-13f,
    // 338
    // -3.1501814374e-04f
    -0xa.52905p-15f,
    // 339
    // +2.2314764559e-02f
    +0xb.6cd74p-9f,
    // 340
    // +1.8992704572e-03f
    +0xf.8f0f1p-13f,
    // 341
    // -1.3421124220e-01f
    -0x8.96eacp-6f,
    // 342
    // +2.2867667759e-09f
    +0x9.d253ap-32f,
    // 343
    // +0.0000000000e+00f
    +0x0p+0f,
    // 344
    // +0.0000000000e+00f
    +0x0p+0f,
    // 345
    // +3.7682376862e+01f
    +0x9.6bac1p+2f,
    // 346
    // -3.6889987946e+01f
    -0x9.38f59p+2f,
    // 347
    // +5.3631981700e-07f
    +0x8.ff79ep-24f,
    // 348
    // +1.7155637601e-14f
    +0x9.a8635p-49f,
    // 349
    // -3.1804609080e-06f
    -0xd.56fe7p-22f,
    // 350
    // -2.0240429421e-06f
    -0x8.7d4cbp-22f,
    // 351
    // +1.8087599892e-04f
    +0xb.da988p-16f,
    // 352
    // +5.8803456341e-05f
    +0xf.6a3bbp-18f,
    // 353
    // -5.4538031109e-03f
    -0xb.2b5d1p-11f,
    // 354
    // -5.9222080745e-04f
    -0x9.b3f44p-14f,
    // 355
    // +6.5638162196e-02f
    +0x8.66d4dp-7f,
    // 356
    // -2.6719823576e-10f
    -0x9.2e4cfp-35f,
    // 357
    // -6.1745103619e-18f
    -0xe.3cc9ap-61f,
    // 358
    // -1.3137285411e-01f
    -0x8.6869bp-6f,
    // 359
    // -2.1388490978e-09f
    -0x9.2fb08p-32f,
    // 360
    // +3.9254104614e+01f
    +0x9.d0434p+2f,
    // 361
    // -3.8474765778e+01f
    -0x9.9e629p+2f,
    // 362
    // -4.5718371666e-07f
    -0xf.572dap-25f,
    // 363
    // -7.8247946520e-15f
    -0x8.cf57fp-50f,
    // 364
    // +3.0238282989e-07f
    +0xa.2572ep-25f,
    // 365
    // -2.4782184482e-05f
    -0xc.fe356p-19f,
    // 366
    // -1.3752244740e-05f
    -0xe.6b971p-20f,
    // 367
    // +1.0651494376e-03f
    +0x8.b9c7cp-13f,
    // 368
    // +2.7744035469e-04f
    +0x9.1756ap-15f,
    // 369
    // -2.1392639726e-02f
    -0xa.f3f9ep-9f,
    // 370
    // -1.6714410158e-03f
    -0xd.b1441p-13f,
    // 371
    // +1.2861661613e-01f
    +0x8.3b413p-6f,
    // 372
    // +5.5040891844e-09f
    +0xb.d1e7bp-31f,
    // 373
    // +0.0000000000e+00f
    +0x0p+0f,
    // 374
    // +0.0000000000e+00f
    +0x0p+0f,
    // 375
    // +4.0825267792e+01f
    +0xa.34d13p+2f,
    // 376
    // -4.0033443451e+01f
    -0xa.0223fp+2f,
    // 377
    // -6.0242291511e-07f
    -0xa.1b63p-24f,
    // 378
    // -2.5992757751e-14f
    -0xe.a1f38p-49f,
    // 379
    // +3.0665353279e-06f
    +0xc.dcaadp-22f,
    // 380
    // +1.7947081687e-06f
    +0xf.0e1b4p-23f,
    // 381
    // -1.7386575928e-04f
    -0xb.64fbcp-16f,
    // 382
    // -5.2083680202e-05f
    -0xd.a746dp-18f,
    // 383
    // +5.2381786518e-03f
    +0xa.ba507p-11f,
    // 384
    // +5.2402686561e-04f
    +0x8.95ed9p-14f,
    // 385
    // -6.3015066087e-02f
    -0x8.10e0bp-7f,
    // 386
    // +2.5402688286e-10f
    +0x8.ba71bp-35f,
    // 387
    // +1.2215760273e-17f
    +0xe.1574cp-60f,
    // 388
    // +1.2610881031e-01f
    +0x8.122abp-6f,
    // 389
    // +3.4989167119e-09f
    +0xf.07198p-32f,
    // 390
    // +4.2396862030e+01f
    +0xa.99663p+2f,
    // 391
    // -4.1617095947e+01f
    -0xa.677e8p+2f,
    // 392
    // +1.7344511889e-06f
    +0xe.8cb4ap-23f,
    // 393
    // -1.4780899418e-14f
    -0x8.5226fp-49f,
    // 394
    // -2.6949160770e-07f
    -0x9.0aea5p-25f,
    // 395
    // +2.3871660233e-05f
    +0xc.84p-19f,
    // 396
    // +1.2245011021e-05f
    +0xc.d6fecp-20f,
    // 397
    // -1.0250709020e-03f
    -0x8.65bacp-13f,
    // 398
    // -2.4676905014e-04f
    -0x8.160c8p-15f,
    // 399
    // +2.0575605333e-02f
    +0xa.88e2cp-9f,
    // 400
    // +1.4857830247e-03f
    +0xc.2be9bp-13f,
    // 401
    // -1.2366796285e-01f
    -0xf.d45a1p-7f,
    // 402
    // +2.4820383526e-09f
    +0xa.a907bp-32f,
    // 403
    // +0.0000000000e+00f
    +0x0p+0f,
    // 404
    // +0.0000000000e+00f
    +0x0p+0f,
    // 405
    // +4.3967975616e+01f
    +0xa.fdf35p+2f,
    // 406
    // -4.3176628113e+01f
    -0xa.cb4dep+2f,
    // 407
    // -8.5265583039e-07f
    -0xe.4e21p-24f,
    // 408
    // -1.8079853885e-14f
    -0xa.2d94ep-49f,
    // 409
    // -2.9413674838e-06f
    -0xc.5644fp-22f,
    // 410
    // -1.6071119262e-06f
    -0xd.7b3f2p-23f,
    // 411
    // +1.6756916011e-04f
    +0xa.fb581p-16f,
    // 412
    // +4.6551045671e-05f
    +0xc.33fcep-18f,
    // 413
    // -5.0460826606e-03f
    -0xa.5599cp-11f,
    // 414
    // -4.6797978575e-04f
    -0xf.55b2fp-15f,
    // 415
    // +6.0683019459e-02f
    +0xf.88ec2p-8f,
    // 416
    // -2.0221989361e-10f
    -0xd.e57d7p-36f,
    // 417
    // +6.6711243727e-18f
    +0xf.61efdp-61f,
    // 418
    // -1.2143117189e-01f
    -0xf.8b0e8p-7f,
    // 419
    // -2.8676232500e-09f
    -0xc.50fc3p-32f,
    // 420
    // +4.5539459229e+01f
    +0xb.62868p+2f,
    // 421
    // -4.4759319305e+01f
    -0xb.3098bp+2f,
    // 422
    // +3.0776709536e-07f
    +0xa.53b3p-25f,
    // 423
    // +4.7778231702e-15f
    +0xa.c23a4p-51f,
    // 424
    // +2.4063771775e-07f
    +0x8.130ffp-25f,
    // 425
    // -2.3052152756e-05f
    -0xc.1601fp-19f,
    // 426
    // -1.0991395357e-05f
    -0xb.867afp-20f,
    // 427
    // +9.8914513364e-04f
    +0x8.1a634p-13f,
    // 428
    // +2.2135161271e-04f
    +0xe.81a9fp-16f,
    // 429
    // -1.9845187664e-02f
    -0xa.2926p-9f,
    // 430
    // -1.3321224833e-03f
    -0xa.e9a9dp-13f,
    // 431
    // +1.1924981326e-01f
    +0xf.4393fp-7f,
    // 432
    // -1.6187435836e-09f
    -0xd.e7a7ap-33f,
    // 433
    // +0.0000000000e+00f
    +0x0p+0f,
    // 434
    // +0.0000000000e+00f
    +0x0p+0f,
    // 435
    // +4.7110530853e+01f
    +0xb.c712fp+2f,
    // 436
    // -4.6319599152e+01f
    -0xb.94745p+2f,
    // 437
    // +1.5904374777e-06f
    +0xd.57704p-23f,
    // 438
    // -4.2059420996e-14f
    -0xb.d6b36p-48f,
    // 439
    // +2.8385518362e-06f
    +0xb.e7df3p-22f,
    // 440
    // +1.4493330127e-06f
    +0xc.286b4p-23f,
    // 441
    // -1.6191181203e-04f
    -0xa.9c6dfp-16f,
    // 442
    // -4.1930019506e-05f
    -0xa.fde04p-18f,
    // 443
    // +4.8735663295e-03f
    +0x9.fb27p-11f,
    // 444
    // +4.2125300388e-04f
    +0xd.cdb9fp-15f,
    // 445
    // -5.8591932058e-02f
    -0xe.ffe18p-8f,
    // 446
    // +1.7335086144e-10f
    +0xb.e99eep-36f,
    // 447
    // +4.0575967693e-18f
    +0x9.5b2ebp-61f,
    // 448
    // +1.1723850667e-01f
    +0xf.01abep-7f,
    // 449
    // +3.3520830556e-10f
    +0xb.8486p-35f,
    // 450
    // +4.8681926727e+01f
    +0xc.2ba4bp+2f,
    // 451
    // -4.7901462555e+01f
    -0xb.f9b19p+2f,
    // 452
    // +1.6677462327e-06f
    +0xd.fd753p-23f,
    // 453
    // -3.9166017434e-14f
    -0xb.06358p-48f,
    // 454
    // -2.1812175532e-07f
    -0xe.a34dap-26f,
    // 455
    // +2.2308700864e-05f
    +0xb.b2392p-19f,
    // 456
    // +9.9390381365e-06f
    +0xa.6bfd8p-20f,
    // 457
    // -9.5670850715e-04f
    -0xf.acb9fp-14f,
    // 458
    // -2.0001184021e-04f
    -0xd.1ba45p-16f,
    // 459
    // +1.9187144935e-02f
    +0x9.d2e5cp-9f,
    // 460
    // +1.2032375671e-03f
    +0x9.db5f4p-13f,
    // 461
    // -1.1527369171e-01f
    -0xe.c149dp-7f,
    // 462
    // -2.0530268596e-09f
    -0x8.d153bp-32f,
    // 463
    // +0.0000000000e+00f
    +0x0p+0f,
    // 464
    // +0.0000000000e+00f
    +0x0p+0f,
    // 465
    // +5.0252964020e+01f
    +0xc.90309p+2f,
    // 466
    // -4.9462390900e+01f
    -0xc.5d97dp+2f,
    // 467
    // -2.4004452825e-07f
    -0x8.0df78p-25f,
    // 468
    // -6.3654106705e-15f
    -0xe.5568dp-51f,
    // 469
    // -2.7403793865e-06f
    -0xb.7e75cp-22f,
    // 470
    // -1.3161281913e-06f
    -0xb.0a5d2p-23f,
    // 471
    // +1.5677699412e-04f
    +0xa.46481p-16f,
    // 472
    // +3.8024783862e-05f
    +0x9.f7ccdp-18f,
    // 473
    // -4.7175246291e-03f
    -0x9.a9577p-11f,
    // 474
    // -3.8181329728e-04f
    -0xc.82e1dp-15f,
    // 475
    // +5.6702997535e-02f
    +0xe.84167p-8f,
    // 476
    // -1.3976590718e-10f
    -0x9.9ac9bp-36f,
    // 477
    // -5.9759899100e-18f
    -0xd.c79a1p-61f,
    // 478
    // -1.1345236748e-01f
    -0xe.859b7p-7f,
    // 479
    // -1.2644301162e-09f
    -0xa.dc82ep-33f,
    // 480
    // +5.1824287415e+01f
    +0xc.f4c12p+2f,
    // 481
    // -5.1043533325e+01f
    -0xc.c2c94p+2f,
    // 482
    // -1.8583762085e-06f
    -0xf.96d52p-23f,
    // 483
    // +1.1505777071e-14f
    +0xc.f4508p-50f,
    // 484
    // +1.9784098981e-07f
    +0xd.46e1ep-26f,
    // 485
    // -2.1630796255e-05f
    -0xb.573c8p-19f,
    // 486
    // -9.0426938186e-06f
    -0x9.7b613p-20f,
    // 487
    // +9.2723645503e-04f
    +0xf.311c9p-14f,
    // 488
    // +1.8188920512e-04f
    +0xb.eb983p-16f,
    // 489
    // -1.8590301275e-02f
    -0x9.84abp-9f,
    // 490
    // -1.0938748019e-03f
    -0x8.f6059p-13f,
    // 491
    // +1.1167049408e-01f
    +0xe.4b38p-7f,
    // 492
    // +2.4314632530e-09f
    +0xa.716c1p-32f,
    // 493
    // +0.0000000000e+00f
    +0x0p+0f,
    // 494
    // +0.0000000000e+00f
    +0x0p+0f,
    // 495
    // +5.3395298004e+01f
    +0xd.594c9p+2f,
    // 496
    // -5.2605041504e+01f
    -0xd.26b9p+2f,
    // 497
    // +3.9234956262e-07f
    +0xd.2a41dp-25f,
    // 498
    // +2.7661764599e-15f
    +0xc.752f3p-52f,
    // 499
    // +2.6438576697e-06f
    +0xb.16d21p-22f,
    // 500
    // +1.2032198811e-06f
    +0xa.17e52p-23f,
    // 501
    // -1.5208679542e-04f
    -0x9.f797dp-16f,
    // 502
    // -3.4690274333e-05f
    -0x9.18066p-18f,
    // 503
    // +4.5755030587e-03f
    +0x9.5ee1ap-11f,
    // 504
    // +3.4816400148e-04f
    +0xb.689c8p-15f,
    // 505
    // -5.4985627532e-02f
    -0xe.1389cp-8f,
    // 506
    // +8.7046585218e-11f
    +0xb.f6adfp-37f,
    // 507
    // -1.6130673350e-18f
    -0xe.e0bf6p-63f,
    // 508
    // +1.1001101136e-01f
    +0xe.14d74p-7f,
    // 509
    // +8.9995100261e-10f
    +0xf.7606cp-34f,
    // 510
    // +5.4966564178e+01f
    +0xd.bddc3p+2f,
    // 511
    // -5.4185554504e+01f
    -0xd.8be02p+2f,
    // 512
    // +8.6333318450e-07f
    +0xe.7bfcep-24f,
    // 513
    // +2.6220294517e-14f
    +0xe.c2be2p-49f,
    // 514
    // -1.8204374896e-07f
    -0xc.377cep-26f,
    // 515
    // +2.1009336706e-05f
    +0xb.03d35p-19f,
    // 516
    // +8.2748720160e-06f
    +0x8.ad44ep-20f,
    // 517
    // -9.0030708816e-04f
    -0xe.c0296p-14f,
    // 518
    // -1.6634514031e-04f
    -0xa.e6cefp-16f,
    // 519
    // +1.8045749515e-02f
    +0x9.3d4aep-9f,
    // 520
    // +1.0001312476e-03f
    +0x8.316d6p-13f,
    // 521
    // -1.0838534683e-01f
    -0xd.df923p-7f,
    // 522
    // -1.7599317559e-09f
    -0xf.1e218p-33f,
    // 523
    // +0.0000000000e+00f
    +0x0p+0f,
    // 524
    // +0.0000000000e+00f
    +0x0p+0f,
    // 525
    // +5.6537548065e+01f
    +0xe.22673p+2f,
    // 526
    // -5.5747570038e+01f
    -0xd.efd83p+2f,
    // 527
    // -1.7544072080e-06f
    -0xe.b78f9p-23f,
    // 528
    // -1.2636288229e-14f
    -0xe.3a298p-50f,
    // 529
    // -2.5719789392e-06f
    -0xa.c9a43p-22f,
    // 530
    // -1.1040964409e-06f
    -0x9.43077p-23f,
    // 531
    // +1.4780955098e-04f
    +0x9.afd53p-16f,
    // 532
    // +3.1813851820e-05f
    +0x8.56fddp-18f,
    // 533
    // -4.4455402531e-03f
    -0x9.1abe5p-11f,
    // 534
    // -3.1918066088e-04f
    -0xa.757b4p-15f,
    // 535
    // +5.3415343165e-02f
    +0xd.aca0cp-8f,
    // 536
    // -7.8507735035e-11f
    -0xa.ca3edp-37f,
    // 537
    // +5.1607839776e-19f
    +0x9.851c8p-64f,
    // 538
    // -1.0686507821e-01f
    -0xd.adc14p-7f,
    // 539
    // +2.8879798553e-09f
    +0xc.675e1p-32f,
    // 540
    // +5.8108764648e+01f
    +0xe.86f6p+2f,
    // 541
    // -5.7327526093e+01f
    -0xe.54f63p+2f,
    // 542
    // +6.5462830889e-07f
    +0xa.fb9b7p-24f,
    // 543
    // -2.2763824110e-14f
    -0xc.d09cep-49f,
    // 544
    // +1.6770923139e-07f
    +0xb.4139p-26f,
    // 545
    // -2.0440991648e-05f
    -0xa.b78b2p-19f,
    // 546
    // -7.6090764196e-06f
    -0xf.f5178p-21f,
    // 547
    // +8.7558152154e-04f
    +0xe.58748p-14f,
    // 548
    // +1.5289340809e-04f
    +0xa.05203p-16f,
    // 549
    // -1.7546294257e-02f
    -0x8.fbd3fp-9f,
    // 550
    // -9.1905274894e-04f
    -0xf.0ec96p-14f,
    // 551
    // +1.0537405312e-01f
    +0xd.7ce5ap-7f,
    // 552
    // +1.9591166467e-09f
    +0x8.6a125p-32f,
    // 553
    // +0.0000000000e+00f
    +0x0p+0f,
    // 554
    // +0.0000000000e+00f
    +0x0p+0f,
    // 555
    // +5.9679729462e+01f
    +0xe.eb80bp+2f,
    // 556
    // -5.8890003204e+01f
    -0xe.b8f5dp+2f,
    // 557
    // +9.0516050477e-07f
    +0xf.2fa28p-24f,
    // 558
    // -8.2336320447e-15f
    -0x9.452edp-50f,
    // 559
    // +2.5202646157e-06f
    +0xa.921d1p-22f,
    // 560
    // +1.0159906196e-06f
    +0x8.85d2cp-23f,
    // 561
    // -1.4388957061e-04f
    -0x9.6e11p-16f,
    // 562
    // -2.9311559047e-05f
    -0xf.5e218p-19f,
    // 563
    // +4.3260273524e-03f
    +0x8.dc159p-11f,
    // 564
    // +2.9400520725e-04f
    +0x9.a24b6p-15f,
    // 565
    // -5.1972288638e-02f
    -0xd.4e0e5p-8f,
    // 566
    // +1.1234153885e-10f
    +0xf.70aaap-37f,
    // 567
    // -1.1323480132e-18f
    -0xa.71ae6p-63f,
    // 568
    // +1.0397455841e-01f
    +0xd.4f09dp-7f,
    // 569
    // +1.9936297058e-10f
    +0xd.b33bp-36f,
    // 570
    // +6.1250904083e+01f
    +0xf.500edp+2f,
    // 571
    // -6.0469459534e+01f
    -0xf.1e0bap+2f,
    // 572
    // +1.6883439002e-06f
    +0xe.29b0ep-23f,
    // 573
    // +1.4449294490e-14f
    +0x8.225cep-49f,
    // 574
    // -1.5478266846e-07f
    -0xa.63256p-26f,
    // 575
    // +1.9910525225e-05f
    +0xa.70587p-19f,
    // 576
    // +7.0272021730e-06f
    +0xe.bcb35p-21f,
    // 577
    // -8.5276848404e-04f
    -0xd.f8c53p-14f,
    // 578
    // -1.4116006787e-04f
    -0x9.4045ep-16f,
    // 579
    // +1.7086047679e-02f
    +0x8.bf80ap-9f,
    // 580
    // +8.4836670430e-04f
    +0xd.e64edp-14f,
    // 581
    // -1.0260056704e-01f
    -0xd.2203fp-7f,
    // 582
    // +2.8885449588e-10f
    +0x9.ecca8p-35f,
    // 583
    // +0.0000000000e+00f
    +0x0p+0f,
    // 584
    // +0.0000000000e+00f
    +0x0p+0f,
    // 585
    // +6.2821853638e+01f
    +0xf.b4994p+2f,
    // 586
    // -6.2032348633e+01f
    -0xf.8212p+2f,
    // 587
    // +7.6215059153e-07f
    +0xc.c9697p-24f,
    // 588
    // +6.7271293143e-15f
    +0xf.25ed1p-51f,
    // 589
    // -2.4593109629e-06f
    -0xa.50aa4p-22f,
    // 590
    // -9.4022800567e-07f
    -0xf.c63fap-24f,
    // 591
    // +1.4024812845e-04f
    +0x9.30f92p-16f,
    // 592
    // +2.7121763196e-05f
    +0xe.3838bp-19f,
    // 593
    // -4.2156265117e-03f
    -0x8.a233dp-11f,
    // 594
    // -2.7197331656e-04f
    -0x8.e97a4p-15f,
    // 595
    // +5.0640165806e-02f
    +0xc.f6c1p-8f,
    // 596
    // -1.0881071044e-10f
    -0xe.f46fcp-37f,
    // 597
    // +2.9209285985e-18f
    +0xd.786c8p-62f,
    // 598
    // -1.0130666196e-01f
    -0xc.f79dep-7f,
    // 599
    // +3.2245324189e-09f
    +0xd.d9693p-32f
};
