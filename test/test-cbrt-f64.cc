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
