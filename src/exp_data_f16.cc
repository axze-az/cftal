//
// Copyright (C) 2010-2026 Axel Zeuner
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
cftal::math::exp_data<cftal::f16_t>::table_t
cftal::math::exp_data<cftal::f16_t>::_tbl={
    // static const cftal::f16_t _2_pow_i_n_f[32]=
    {
        // 0
        // +0.00000e+00_f16
        +0x0p+0_f16,
        // 1
        // +4.04119e-04_f16
        +0xd.3ep-15_f16,
        // 2
        // +3.14713e-04_f16
        +0xa.5p-15_f16,
        // 3
        // -2.27094e-04_f16
        -0xe.e2p-16_f16,
        // 4
        // -2.86579e-04_f16
        -0x9.64p-15_f16,
        // 5
        // +1.15693e-04_f16
        +0xf.2ap-17_f16,
        // 6
        // +1.02520e-04_f16
        +0xd.7p-17_f16,
        // 7
        // -2.90155e-04_f16
        -0x9.82p-15_f16,
        // 8
        // -2.06828e-04_f16
        -0xd.8ep-16_f16,
        // 9
        // +3.32117e-04_f16
        +0xa.e2p-15_f16,
        // 10
        // -2.65360e-04_f16
        -0x8.b2p-15_f16,
        // 11
        // -3.78370e-04_f16
        -0xc.66p-15_f16,
        // 12
        // -2.73585e-05_f16
        -0xe.58p-19_f16,
        // 13
        // +3.11732e-05_f16
        +0x8.2cp-18_f16,
        // 14
        // -1.74761e-04_f16
        -0xb.74p-16_f16,
        // 15
        // +8.73208e-05_f16
        +0xb.72p-17_f16,
        // 16
        // +1.06812e-04_f16
        +0xep-17_f16,
        // 17
        // -9.11355e-05_f16
        -0xb.f2p-17_f16,
        // 18
        // +1.78576e-04_f16
        +0xb.b4p-16_f16,
        // 19
        // +2.48671e-04_f16
        +0x8.26p-15_f16,
        // 20
        // +1.41740e-04_f16
        +0x9.4ap-16_f16,
        // 21
        // -1.21176e-04_f16
        -0xf.e2p-17_f16,
        // 22
        // +8.61883e-05_f16
        +0xb.4cp-17_f16,
        // 23
        // +1.50561e-04_f16
        +0x9.dep-16_f16,
        // 24
        // +9.05395e-05_f16
        +0xb.dep-17_f16,
        // 25
        // -7.60555e-05_f16
        -0x9.f8p-17_f16,
        // 26
        // +2.23756e-04_f16
        +0xe.aap-16_f16,
        // 27
        // -1.18554e-04_f16
        -0xf.8ap-17_f16,
        // 28
        // +1.29342e-05_f16
        +0xd.9p-20_f16,
        // 29
        // +7.69496e-05_f16
        +0xa.16p-17_f16,
        // 30
        // +8.74400e-05_f16
        +0xb.76p-17_f16,
        // 31
        // +5.76973e-05_f16
        +0xf.2p-18_f16
    },
    // static const cftal::f16_t _2_pow_i_n_h[32]=
    {
        // 0
        // +1.00000e+00_f16
        +0x8p-3_f16,
        // 1
        // +1.02148e+00_f16
        +0x8.2cp-3_f16,
        // 2
        // +1.04395e+00_f16
        +0x8.5ap-3_f16,
        // 3
        // +1.06738e+00_f16
        +0x8.8ap-3_f16,
        // 4
        // +1.09082e+00_f16
        +0x8.bap-3_f16,
        // 5
        // +1.11426e+00_f16
        +0x8.eap-3_f16,
        // 6
        // +1.13867e+00_f16
        +0x9.1cp-3_f16,
        // 7
        // +1.16406e+00_f16
        +0x9.5p-3_f16,
        // 8
        // +1.18945e+00_f16
        +0x9.84p-3_f16,
        // 9
        // +1.21484e+00_f16
        +0x9.b8p-3_f16,
        // 10
        // +1.24219e+00_f16
        +0x9.fp-3_f16,
        // 11
        // +1.26953e+00_f16
        +0xa.28p-3_f16,
        // 12
        // +1.29688e+00_f16
        +0xa.6p-3_f16,
        // 13
        // +1.32520e+00_f16
        +0xa.9ap-3_f16,
        // 14
        // +1.35449e+00_f16
        +0xa.d6p-3_f16,
        // 15
        // +1.38379e+00_f16
        +0xb.12p-3_f16,
        // 16
        // +1.41406e+00_f16
        +0xb.5p-3_f16,
        // 17
        // +1.44531e+00_f16
        +0xb.9p-3_f16,
        // 18
        // +1.47656e+00_f16
        +0xb.dp-3_f16,
        // 19
        // +1.50879e+00_f16
        +0xc.12p-3_f16,
        // 20
        // +1.54199e+00_f16
        +0xc.56p-3_f16,
        // 21
        // +1.57617e+00_f16
        +0xc.9cp-3_f16,
        // 22
        // +1.61035e+00_f16
        +0xc.e2p-3_f16,
        // 23
        // +1.64551e+00_f16
        +0xd.2ap-3_f16,
        // 24
        // +1.68164e+00_f16
        +0xd.74p-3_f16,
        // 25
        // +1.71875e+00_f16
        +0xd.cp-3_f16,
        // 26
        // +1.75586e+00_f16
        +0xe.0cp-3_f16,
        // 27
        // +1.79492e+00_f16
        +0xe.5cp-3_f16,
        // 28
        // +1.83398e+00_f16
        +0xe.acp-3_f16,
        // 29
        // +1.87402e+00_f16
        +0xe.fep-3_f16,
        // 30
        // +1.91504e+00_f16
        +0xf.52p-3_f16,
        // 31
        // +1.95703e+00_f16
        +0xf.a8p-3_f16
    },
    // static const cftal::f16_t _2_pow_i_n_l[32]=
    {
        // 0
        // +0.00000e+00_f16
        +0x0p+0_f16,
        // 1
        // +4.12703e-04_f16
        +0xd.86p-15_f16,
        // 2
        // +3.28541e-04_f16
        +0xa.c4p-15_f16,
        // 3
        // -2.42352e-04_f16
        -0xf.e2p-16_f16,
        // 4
        // -3.12567e-04_f16
        -0xa.3ep-15_f16,
        // 5
        // +1.28984e-04_f16
        +0x8.74p-16_f16,
        // 6
        // +1.16765e-04_f16
        +0xf.4ep-17_f16,
        // 7
        // -3.37601e-04_f16
        -0xb.1p-15_f16,
        // 8
        // -2.46048e-04_f16
        -0x8.1p-15_f16,
        // 9
        // +4.03643e-04_f16
        +0xd.3ap-15_f16,
        // 10
        // -3.29733e-04_f16
        -0xa.cep-15_f16,
        // 11
        // -4.80175e-04_f16
        -0xf.bcp-15_f16,
        // 12
        // -3.54648e-05_f16
        -0x9.4cp-18_f16,
        // 13
        // +4.13060e-05_f16
        +0xa.d4p-18_f16,
        // 14
        // -2.36630e-04_f16
        -0xf.82p-16_f16,
        // 15
        // +1.20819e-04_f16
        +0xf.d6p-17_f16,
        // 16
        // +1.51038e-04_f16
        +0x9.e6p-16_f16,
        // 17
        // -1.31726e-04_f16
        -0x8.a2p-16_f16,
        // 18
        // +2.63691e-04_f16
        +0x8.a4p-15_f16,
        // 19
        // +3.75271e-04_f16
        +0xc.4cp-15_f16,
        // 20
        // +2.18630e-04_f16
        +0xe.54p-16_f16,
        // 21
        // -1.90973e-04_f16
        -0xc.84p-16_f16,
        // 22
        // +1.38760e-04_f16
        +0x9.18p-16_f16,
        // 23
        // +2.47717e-04_f16
        +0x8.1ep-15_f16,
        // 24
        // +1.52230e-04_f16
        +0x9.fap-16_f16,
        // 25
        // -1.30653e-04_f16
        -0x8.9p-16_f16,
        // 26
        // +3.92675e-04_f16
        +0xc.dep-15_f16,
        // 27
        // -2.12789e-04_f16
        -0xd.f2p-16_f16,
        // 28
        // +2.37226e-05_f16
        +0xc.7p-19_f16,
        // 29
        // +1.44243e-04_f16
        +0x9.74p-16_f16,
        // 30
        // +1.67489e-04_f16
        +0xa.fap-16_f16,
        // 31
        // +1.12891e-04_f16
        +0xe.ccp-17_f16
    }
};

namespace {
    __attribute__((used)) cftal::int64_t _pad=-1LL;
}

template struct cftal::math::exp_data<cftal::f16_t>;


