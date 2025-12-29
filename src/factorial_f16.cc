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
#include <cftal/config.h>
#include <cftal/math/factorial.h>
#include <limits>

const cftal::f16_t
cftal::math::rcp_factorial<cftal::f16_t>::
_recip_factorial_f16[12]={
    // 0
    // +1.00000e+00_f16
    +0x8p-3_f16,
    // 1
    // +1.00000e+00_f16
    +0x8p-3_f16,
    // 2
    // +5.00000e-01_f16
    +0x8p-4_f16,
    // 3
    // +1.66626e-01_f16
    +0xa.aap-6_f16,
    // 4
    // +4.16565e-02_f16
    +0xa.aap-8_f16,
    // 5
    // +8.33130e-03_f16
    +0x8.88p-10_f16,
    // 6
    // +1.38855e-03_f16
    +0xb.6p-13_f16,
    // 7
    // +1.98364e-04_f16
    +0xdp-16_f16,
    // 8
    // +2.47955e-05_f16
    +0xdp-19_f16,
    // 9
    // +2.74181e-06_f16
    +0xb.8p-22_f16,
    // 10
    // +2.98023e-07_f16
    +0xap-25_f16,
    // 11
    // +0.00000e+00_f16
    +0x0p+0_f16
};

const cftal::f16_t
cftal::math::factorial<cftal::f16_t>::
_factorial_f16[10]={
    // 0
    // +1.00000e+00_f16
    +0x8p-3_f16,
    // 1
    // +1.00000e+00_f16
    +0x8p-3_f16,
    // 2
    // +2.00000e+00_f16
    +0x8p-2_f16,
    // 3
    // +6.00000e+00_f16
    +0xcp-1_f16,
    // 4
    // +2.40000e+01_f16
    +0xcp+1_f16,
    // 5
    // +1.20000e+02_f16
    +0xfp+3_f16,
    // 6
    // +7.20000e+02_f16
    +0xb.4p+6_f16,
    // 7
    // +5.04000e+03_f16
    +0x9.d8p+9_f16,
    // 8
    // +4.03200e+04_f16
    +0x9.d8p+12_f16,
    // 9
    // +inf_f16
    std::numeric_limits<f16_t>::infinity()
};
