//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/check_exp.h"
#include "cftal/test/program.h"

int main(int argc, char** argv)
{
    using namespace cftal::test;

    const func_domain<double> di[]={
        std::make_pair(-750.0, 710.0),
        // check the denormal result range
        std::make_pair(-750.0, -7.083964185322641924358322e+02)
    };
    const int shifts[]= {
        0,
        -3
    };
    int r=program<check_exp<double>, 8, 1, 0x8000>(argc,
                                                   argv,
                                                   mpfr_exp,
                                                   di,
                                                   shifts);
    return r;
}
