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
#include <cftal/test/of_vec_v8.h>

#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__>0)
namespace cftal {
    namespace test {
        bool spec_v8u64();
    }
}

bool cftal::test::spec_v8u64()
{
    bool r=true;
    using type=uint64_t;
    r &= perm1_v8<type, -1, -1, -1, -1, -1, -1, -1, -1>();
    r &= perm1_v8<type,  0,  1,  2,  3,  4,  5,  6,  7>();
    r &= perm1_v8<type,  0, 0, 0, 0, 0, 0, 0, 0>();

    r &= perm1_v8<type, -1, 0, 1, 2,-1, 4, 5, 6>();
    r &= perm1_v8<type, -1,-1, 0, 1,-1,-1, 4, 5>();
    r &= perm1_v8<type, -1,-1,-1, 0,-1,-1,-1, 4>();

    r &= perm1_v8<type,  1, 2, 3,-1, 5, 6, 7,-1>();
    r &= perm1_v8<type,  2, 3,-1,-1, 6, 7,-1,-1>();
    r &= perm1_v8<type,  3,-1,-1,-1, 7,-1,-1,-1>();
    
    r &= perm1_v8<type,  0, 1, 0, 1, 4, 5, 4, 5>();
    r &= perm1_v8<type,  2, 3, 2, 3, 6, 7, 6, 7>();
    r &= perm1_v8<type,  0, -1, 1, -1, 2, -1, 3, -1>();
    r &= perm1_v8<type,  0, 1, 2, 3,  0, 1, 2, 3>();

    r &= perm2_v8<type,  0, 1, 8, 9, 4, 5, 12, 13>();
    r &= perm2_v8<type,  8, 9, 0, 1, 12, 13, 4, 5>();
	
    r &= perm2_v8<type,  2, 3, 10, 11, 6, 7, 14, 15>();
    r &= perm2_v8<type, 10, 11, 2, 3, 14, 15, 6, 7>();
    
    r &= perm2_v8<type,  0, 8, 1, 9, 4, 12, 5, 13>();
    r &= perm2_v8<type,  8, 0, 9, 1, 12, 4, 13, 5>();
	
    r &= perm2_v8<type,  2, 10, 3, 11, 6, 14, 7, 15>();
    r &= perm2_v8<type, 10, 2, 11, 3, 14, 6, 15, 7>();

    r &= perm2_v8<type, 0, 1, 2, 3, 8, 9, 10, 11>();
    r &= perm2_v8<type, 0, 1, 2, 3, 12, 13, 14, 15>();
    r &= perm2_v8<type, 4, 5, 6, 7, 8, 9, 10, 11>();
    r &= perm2_v8<type, 4, 5, 6, 7, 12, 13, 14, 15 >();
    
    return r;
}

int main()
{
    bool r=true;
    r &= cftal::test::check_v8<uint64_t>();
    r &= cftal::test::spec_v8u64();
    return r == true ? 0 : 1;
}
#else

int main()
{
    return 0;
}

#endif
