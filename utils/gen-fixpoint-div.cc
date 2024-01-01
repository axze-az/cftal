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
#include <iostream>
#include <iomanip>
#include <cftal/std_types.h>

int main(int argc, char** argv)
{
    using namespace cftal;

    // 1/3 = x/2^16
    // x=2^16/3;

    const int32_t divisor=9;
    const int32_t shift_1_d=14;
    const int32_t fac_1_d=((1<<shift_1_d)+(divisor-1))/divisor;
#if 0
    const int32_t bias=1023;
    const int32_t bits=53;
#else
    const int32_t bias=127;
    const int32_t bits=24;
#endif

    std::cout << "const int32_t shift_1_" << divisor
              << "= 0x" << std::hex << shift_1_d << std::dec << ";\n";
    std::cout << "const int32_t fac_1_" << divisor
              << "= 0x" << std::hex << fac_1_d << std::dec<<";\n";

    for (int32_t i=-bias-bits; i<bias+1; ++i) {
        // round down division
        int32_t q=i/divisor;
        if (i<0 && (i%divisor))
            --q;
        // int32_t p=((i*fac_1_3)>>shift_1_3) - (i>>31);
        int32_t p = (((i+divisor*bias)*fac_1_d)>>shift_1_d) - bias;
        int32_t r=i-divisor*p;
        if (p != q) {
            std::cout << "i=" << i << " q=" << q << " qp="
                      << p << " r=" << r << std::endl;
        }
    }
    for (int32_t i=-(bias+bits+bias+2); i<bias+bits+bias+2; ++i) {
        // round down division
        int32_t q=i/divisor;
        if (i<0 && (i%divisor))
            --q;
        // int32_t p=((i*fac_1_3)>>shift_1_3) - (i>>31);
        int32_t p = (((i+divisor*bias)*fac_1_d)>>shift_1_d) - bias;
        int32_t r=i-divisor*p;
        if (p != q) {
            std::cout << "i=" << i << " q=" << q << " qp="
                      << p << " r=" << r << std::endl;
        }
    }
}
