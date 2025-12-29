//
// Copyright (C) 2010-2026 Axel Zeuner
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
#include "cftal/test/of_ops.h"
#include "cftal/test/cpu_times.h"

int main()
{
    cftal::test::cpu_times_to_stdout tt;
    std::cout << "testing vXf64" << std::endl;
    bool rc=cftal::test::of_ops_up_to<double, 8>::v();
    if (rc==false)
        std::cerr << "double test failed" << std::endl;
    return rc==true ? 0 : 1;
}

