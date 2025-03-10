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
#include "cftal/test/program.h"
#include "cftal/math/func_data.h"
#include "cftal/test/check_j1.h"

int main(int argc, char** argv)
{
    using namespace cftal::test;
    const int _N= 8;
    const int _ULP=1;
    int r=program<check_j1<double>, _N, _ULP, 0x8000>(
        argc,
        argv,
        mpfr_j1,
        domain_j1<double>::domains,
        domain_j1<double>::shifts);
    return r;
}

