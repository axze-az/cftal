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
    r &= perm1_v32<type,
                    0, -1,  1, -1,  2, -1,  3, -1,
                    4, -1,  5, -1,  6, -1,  7, -1,
                    8, -1,  9, -1, 10, -1, 11, -1,
                   12, -1, 13, -1, 14, -1, 15, -1>();
    r &= perm1_v32<type,
                    0,  1, -1, -1,  2,  3, -1, -1,
                    4,  5, -1, -1,  6,  7, -1, -1,
                    8,  9, -1, -1, 10, 11, -1, -1,
                   12, 13, -1, -1, 14, 15, -1, -1>();
    // perm2 specializations
    r &= perm2_v32<type,
                    0, 32,  1, 33,  2, 34,  3, 35,
                    4, 36,  5, 37,  6, 38,  7, 39,
                   16, 48, 17, 49, 18, 50, 19, 51,
                   20, 52, 21, 53, 22, 54, 23, 55>();
    r &= perm2_v32<type,
                   32,  0, 33,  1, 34,  2, 35,  3,
                   36,  4, 37,  5, 38,  6, 39,  7,
                   48, 16, 49, 17, 50, 18, 51, 19,
                   52, 20, 53, 21, 54, 22, 55, 23>();
    r &= perm2_v32<type,
                    8, 40,  9, 41, 10, 42, 11, 43,
                   12, 44, 13, 45, 14, 46, 15, 47,
                   24, 56, 25, 57, 26, 58, 27, 59,
                   28, 60, 29, 61, 30, 62, 31, 63>();
    r &= perm2_v32<type,
                   40,  8, 41,  9, 42, 10, 43, 11,
                   44, 12, 45, 13, 46, 14, 47, 15,
                   56, 24, 57, 25, 58, 26, 59, 27,
                   60, 28, 61, 29, 62, 30, 63, 31>();

    r &= perm2_v32<type,
                    0,  1, 32, 33,  2,  3, 34, 35,
                    4,  5, 36, 37,  6,  7, 38, 39,
                   16, 17, 48, 49, 18, 19, 50, 51,
                   20, 21, 52, 53, 22, 23, 54, 55>();
    r &= perm2_v32<type,
                   32, 33,  0,  1, 34, 35,  2,  3,
                   36, 37,  4,  5, 38, 39,  6,  7,
                   48, 49, 16, 17, 50, 51, 18, 19,
                   52, 53, 20, 21, 54, 55, 22, 23>();
    r &= perm2_v32<type,
                    8,  9, 40, 41, 10, 11, 42, 43,
                   12, 13, 44, 45, 14, 15, 46, 47,
                   24, 25, 56, 57, 26, 27, 58, 59,
                   28, 29, 60, 61, 30, 31, 62, 63>();
    r &= perm2_v32<type,
                   40, 41,  8,  9, 42, 43, 10, 11,
                   44, 45, 12, 13, 46, 47, 14, 15,
                   56, 57, 24, 25, 58, 59, 26, 27,
                   60, 61, 28, 29, 62, 63, 30, 31>();
    return r;
}

int main()
{
    bool rc(true);
    rc &= cftal::test::check_v32<int8_t>();
    rc &= cftal::test::spec_v32s8();
    return rc == true ? 0 : 1;
}
