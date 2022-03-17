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
        bool spec_v32u8();
    }
}

bool cftal::test::spec_v32u8()
{
    bool r=true;
    using type=uint8_t;
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
                    0,  0,  2,  2,  4,  4,  6,  6,
                    8,  8, 10, 10, 12, 12, 14, 14,
                   16, 16, 18, 18, 20, 20, 22, 22,
                   24, 24, 26, 26, 28, 28, 30, 30>();
    r &= perm1_v32<type,
                    1,  1,  3,  3,  5,  5,  7,  7,
                    9,  9, 11, 11, 13, 13, 15, 15,
                   17, 17, 19, 19, 21, 21, 23, 23,
                   25, 25, 27, 27, 29, 29, 31, 31>();
    return r;
}

int main()
{
    bool r=true;
    r &= cftal::test::check_v32<uint8_t>();
    r &= cftal::test::spec_v32u8();
    return r == true ? 0 : 1;
}
