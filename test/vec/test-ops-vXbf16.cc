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
#include "cftal/vec.h"
#include "cftal/test/of_ops.h"
#include "cftal/test/cpu_times.h"


namespace cftal {
    namespace test {
    }
}

int main()
{
    cftal::test::cpu_times_to_stdout tt;
    std::cout << "testing vXbf16" << std::endl;
    using cftal::bf16_t;
    bool rc=cftal::test::of_ops_up_to<bf16_t, 32>::v();
    if (rc==false)
        std::cerr << "bf16_t test failed" << std::endl;
    return rc==true ? 0 : 1;
}

