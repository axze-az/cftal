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
#include "cftal/test/program.h"
#include "cftal/math/func_data.h"
#include "cftal/test/check_y0.h"
#include "cftal/vec_bf16.h"

int main(int argc, char** argv)
{
    using namespace cftal::test;
    using cftal::bf16_t;
    const int _N= 32;
    const int _ULP=1;
    int r=program<check_y0<bf16_t>, _N, _ULP, 0x4000>(
        argc,
        argv,
        mpfr_y0,
        domain_y0<bf16_t>::domains,
        domain_y0<bf16_t>::shifts);
    return r;
}

