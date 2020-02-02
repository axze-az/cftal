//
// Copyright Axel Zeuner 2010-2020. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/program.h"
#include "cftal/test/check_sinpi.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    const func_domain<float> di[]={
        std::make_pair(-0x1.5p25f, 0x1.5p25f)
    };
    const int shifts[]={0};
    int r=program<check_sinpi<float>, 16, 1, 0x8000>(argc,
                                                     argv,
                                                     mpfr_ext::sinpi,
                                                     di,
                                                     shifts);
    return r;
}
