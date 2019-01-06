//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/program.h"
#include "cftal/test/check_exp.h"

int main(int argc, char** argv)
{
    using namespace cftal::test;
    const func_domain<float> di[]={
        std::make_pair(-104.0f, 89.0f)
    };
    const int shifts[]={
        0
    };
    int r=program<check_exp<float>, 16, 1, 0x8000>(argc,
                                                   argv,
                                                   mpfr_exp,
                                                   di,
                                                   shifts);
    return r;
}
