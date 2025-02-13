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
#include <cftal/config.h>
#include <cftal/test/of_vec.h>
#include <cftal/test/of_vec_v8.h>

namespace cftal {
    namespace test {
        bool spec_v8s16();
    }
}

bool cftal::test::spec_v8s16()
{
    bool r=true;
    r &= perm1_v8<int16_t, -1, -1, -1, -1, -1, -1, -1, -1>();
    r &= perm1_v8<int16_t,  0,  1,  2,  3,  4,  5,  6,  7>();
    r &= perm1_v8<int16_t,  0, 0, 1, 1, 2, 2, 3, 3>();
    r &= perm1_v8<int16_t,  4, 4, 5, 5, 6, 6, 6, 6>();
    r &= perm1_v8<int16_t,  0, 1, 0, 1, 2, 3, 2, 3>();
    r &= perm1_v8<int16_t,  4, 5, 4, 5, 6, 7, 6, 7>();
    r &= perm1_v8<int16_t,  0, 1, 3, 4, 0, 1, 2, 3>();
    r &= perm1_v8<int16_t,  4, 5, 6, 7, 4, 5, 6, 7>();
    r &= perm1_v8<int16_t,  0, -1, 1, -1, 2, -1, 3, -1>();
    r &= perm1_v8<int16_t,  4, -1, 5, -1, 6, -1, 7, -1>();
    r &= perm1_v8<int16_t,  -1, 0, -1, 1, -1, 2, -1, 3>();
    r &= perm1_v8<int16_t,  -1, 4, -1, 5, -1, 6, -1, 7>();
    
    r &= perm1_v8<int16_t,  0, 0, 0, 0, 0, 0, 0, 0>();
    r &= perm1_v8<int16_t,  1, 1, 1, 1, 1, 1, 1, 1>();
    r &= perm1_v8<int16_t,  2, 2, 2, 2, 2, 2, 2, 2>();
    r &= perm1_v8<int16_t,  3, 3, 3, 3, 3, 3, 3, 3>();
    r &= perm1_v8<int16_t,  4, 4, 4, 4, 4, 4, 4, 4>();
    r &= perm1_v8<int16_t,  5, 5, 5, 5, 5, 5, 5, 5>();
    r &= perm1_v8<int16_t,  6, 6, 6, 6, 6, 6, 6, 6>();
    r &= perm1_v8<int16_t,  7, 7, 7, 7, 7, 7, 7, 7>();

    r &= perm1_v8<int16_t, -1, 0,  1,  2,  3,  4,  5,  6>();
    r &= perm1_v8<int16_t, -1, -1, 0,  1,  2,  3,  4,  5>();
    r &= perm1_v8<int16_t, -1, -1, -1, 0,  1,  2,  3,  4>();
    r &= perm1_v8<int16_t, -1, -1, -1, -1, 0,  1,  2,  3>();
    r &= perm1_v8<int16_t, -1, -1, -1, -1, -1, 0,  1,  2>();
    r &= perm1_v8<int16_t, -1, -1, -1, -1, -1, -1, 0,  1>();
    r &= perm1_v8<int16_t, -1, -1, -1, -1, -1, -1, -1, 0>();

    r &= perm1_v8<int16_t, 1,  2,  3,  4,  5,  6,  7, -1>();
    r &= perm1_v8<int16_t, 2,  3,  4,  5,  6,  7, -1, -1>();
    r &= perm1_v8<int16_t, 3,  4,  5,  6,  7, -1, -1, -1>();
    r &= perm1_v8<int16_t, 4,  5,  6,  7, -1, -1, -1, -1>();
    r &= perm1_v8<int16_t, 5,  6,  7, -1, -1, -1, -1, -1>();
    r &= perm1_v8<int16_t, 6,  7, -1, -1, -1, -1, -1, -1>();
    r &= perm1_v8<int16_t, 7, -1, -1, -1, -1, -1, -1, -1>();

    r &= perm1_v8<int16_t, -1, 0,-1, 2,-1, 4,-1, 6>();
    r &= perm1_v8<int16_t,  1,-1, 3,-1, 5,-1, 7,-1>();
    r &= perm1_v8<int16_t, -1, 0, 1, 2,-1, 4, 5, 6>();
    r &= perm1_v8<int16_t, -1,-1, 0, 1,-1,-1, 4, 5>();
    r &= perm1_v8<int16_t, -1,-1,-1, 0,-1,-1,-1, 4>();
    r &= perm1_v8<int16_t,  1, 2, 3,-1, 5, 6, 7,-1>();
    r &= perm1_v8<int16_t,  2, 3,-1,-1, 6, 7,-1,-1>();
    r &= perm1_v8<int16_t,  3,-1,-1,-1, 7,-1,-1,-1>();

    r &= perm2_v8<int16_t,  0, 8, 1, 9, 2,10, 3,11>();
    r &= perm2_v8<int16_t,  8, 0, 9, 1,10, 2,11, 3>();
    r &= perm2_v8<int16_t,  4,12, 5,13, 6,14, 7,15>();
    r &= perm2_v8<int16_t, 12, 4,13, 5,14, 6,15, 7>();
    r &= perm2_v8<int16_t,  0, 1, 2, 3, 8, 9,10,11>();
    r &= perm2_v8<int16_t,  8, 9,10,11, 0, 1, 2, 3>();
    r &= perm2_v8<int16_t,  4, 5, 6, 7,12,13,14,15>();
    r &= perm2_v8<int16_t, 12,13,14,15, 4, 5, 6, 7>();

    return r;
}

int main()
{
    bool rc(true);
    rc &= cftal::test::check_v8<int16_t>();
    rc &= cftal::test::spec_v8s16();
    return rc == true ? 0 : 1;
}
