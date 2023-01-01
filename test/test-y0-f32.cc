//
// Copyright (C) 2010-2023 Axel Zeuner
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
#include "cftal/test/program.h"
#include "cftal/math/func_data.h"
#include "cftal/test/check_y0.h"

int main(int argc, char** argv)
{
    using namespace cftal::test;
    using namespace cftal::math;

    const int _N= 16;
    const int _ULP=1;
    const func_domain<float> di[]={
        std::make_pair(0,
                       std::numeric_limits<float>::max()),
        std::make_pair(j01y01_data<float>::_max_small_y0,
                       2*j01y01_data<float>::_max_small_y0),
        std::make_pair(0,
                       j01y01_data<float>::_max_small_y0)
    };
    const int shifts[]= {
        0,
        -2,
        -2
    };
    int r=program<check_y0<float>, _N, _ULP, 0x8000>(argc,
                                                     argv,
                                                     mpfr_y0,
                                                     di,
                                                     shifts);
    return r;
}

