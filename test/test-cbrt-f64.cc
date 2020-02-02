//
// Copyright Axel Zeuner 2010-2020. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/program.h"
#include "cftal/test/check_cbrt.h"

int main(int argc, char** argv)
{
    using namespace cftal::test;
    const func_domain<double> di[]={
        std::make_pair(-std::numeric_limits<double>::max(),
                        std::numeric_limits<double>::max())
    };
    const int shifts[]={0};
    int r=program<check_cbrt<double>, 8, 1, 0x8000>(argc,
                                                    argv,
                                                    mpfr_cbrt,
                                                    di,
                                                    shifts);
    return r;
}
