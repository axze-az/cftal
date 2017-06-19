//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <iostream>
#include <iomanip>
#include <cftal/std_types.h>

int main(int argc, char** argv)
{
    using namespace cftal;

    // 1/3 = x/2^16
    // x=2^16/3;

    const int32_t divisor=3;
    const int32_t shift_1_d=13;
    const int32_t fac_1_d=((1<<shift_1_d)+(divisor-1))/divisor;
#if 1
    const int32_t bias=1023;
    const int32_t bits=53;
#else
    const int32_t bias=126;
    const int32_t bits=24;
#endif

    std::cout << "const int32_t shift_1_" << divisor
              << "= 0x" << std::hex << shift_1_d << std::dec << ";\n";
    std::cout << std::hex << "const int32_t fac_1_" << divisor
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
}
