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
#include <iostream>
#include <iomanip>
#include <cftal/vec.h>

using namespace cftal;

vec<int32_t, 8>
insert_exp(arg_t<vec<int32_t, 4> > v)
{
    vec<int32_t, 4> vs= v  << 20;
    vec<int32_t, 8> r=combine_zeroeven_odd(vs);
    return r;
}

int main(int argc, char** argv)
{
    using namespace cftal;

    v4f64 x4=0x1p-1;
    v4f64 fx4=erfc(x4);
    std::cout << std::hexfloat;
    std::cout << "x:\t" << x4 << std::endl
	      << "fx:\t" << fx4 << std::endl;


    v2f64 x2=0x1p-1;
    v2f64 fx2=erfc(x2);
    std::cout << std::hexfloat;
    std::cout << "x:\t" << x2 << std::endl
	      << "fx:\t" << fx2 << std::endl;
    return 0;
}
