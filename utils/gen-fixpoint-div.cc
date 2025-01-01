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
#include <iostream>
#include <iomanip>
#include <cftal/std_types.h>

int main(int argc, char** argv)
{
    using namespace cftal;

    // 1/d = x/2^s
    // x=2^s/d;
    // d --> divisor
    // s --> shift_1_d

    const int32_t divisor=12;
    const int32_t shift_1_d=0x11;
    const int32_t fac_1_d=((1<<shift_1_d)+(divisor-1))/divisor;
#define FP_BITS 32
#if FP_BITS==64
    const int32_t bias=1023;
    const int32_t bits=53;
    using int_type=int32_t;
#elif FP_BITS==32
    const int32_t bias=127;
    const int32_t bits=24;
    using int_type=int32_t;
#elif FP_BITS==16
    const int32_t bias=15;
    const int32_t bits=11;
    using int_type=int16_t;
#endif

    std::cout << "const int32_t shift_1_" << divisor
              << "= 0x" << std::hex << shift_1_d << std::dec << ";\n";
    std::cout << "const int32_t fac_1_" << divisor
              << "= 0x" << std::hex << fac_1_d << std::dec<<";\n";

    for (int_type i=-bias-bits; i<bias+1; ++i) {
        // round down division
        int_type q=i/divisor;
        if (i<0 && (i%divisor))
            --q;
        // int32_t p=((i*fac_1_3)>>shift_1_3) - (i>>31);
        int_type p = (((i+divisor*bias)*fac_1_d)>>shift_1_d) - bias;
        int_type r=i-divisor*p;
        if (p != q) {
            std::cout << "i=" << i << " q=" << q << " qp="
                      << p << " r=" << r << std::endl;
        }
    }
    for (int_type i=-(bias+bits+bias+2); i<bias+bits+bias+2; ++i) {
        // round down division
        int_type q=i/divisor;
        if (i<0 && (i%divisor))
            --q;
        // int32_t p=((i*fac_1_3)>>shift_1_3) - (i>>31);
        int_type p = (((i+divisor*bias)*fac_1_d)>>shift_1_d) - bias;
        int_type r=i-divisor*p;
        if (p != q) {
            std::cout << "i=" << i << " q=" << q << " qp="
                      << p << " r=" << r << std::endl;
        }
    }
}
