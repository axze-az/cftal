//
// Copyright (C) 2010-2022 Axel Zeuner
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
#include <cftal/config.h>
#include <cftal/test/of_vec.h>
#include <cftal/test/of_vec_v32.h>

namespace cftal {
    namespace test {
        bool spec_v32s8();
    }
}

bool cftal::test::spec_v32s8()
{
    bool r=true;
    using type=int8_t;
    r &= perm1_v32<type,
                   -1, -1, -1, -1, -1, -1, -1, -1,
                   -1, -1, -1, -1, -1, -1, -1, -1,
                   -1, -1, -1, -1, -1, -1, -1, -1,
                   -1, -1, -1, -1, -1, -1, -1, -1>();
    r &= perm1_v32<type,
                    0,  1,  2,  3,  4,  5,  6,  7,
                    8,  9, 10, 11, 12, 13, 14, 15,
                   16, 17, 18, 19, 20, 21, 22, 23,
                   24, 25, 26, 27, 28, 29, 30, 31>();
    r &= perm1_v32<type,
                    0,  0,  1,  1,  2,  2,  3,  3,
                    4,  4,  5,  5,  6,  6,  7,  7,
                   16, 16, 17, 17, 18, 18, 19, 19,
                   20, 20, 21, 21, 22, 22, 23, 23>();
    r &= perm1_v32<type,
                    8,  8,  9,  9, 10, 10, 11, 11,
                   12, 12, 13, 13, 14, 14, 15, 15,
                   24, 24, 25, 25, 26, 26, 27, 27,
                   28, 28, 29, 29, 30, 30, 31, 31>();
    return r;
}

int main()
{
    bool rc(true);
    rc &= cftal::test::check_v32<int8_t>();
    rc &= cftal::test::spec_v32s8();
    return rc == true ? 0 : 1;
}
