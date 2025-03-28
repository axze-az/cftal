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
#include <cftal/test/of_vec_v16.h>

#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__>0)
namespace cftal {
    namespace test {
        bool spec_v16s32();
    }
}

bool cftal::test::spec_v16s32()
{
    bool r=true;
    return r;
}

int main()
{
    bool rc(true);
    rc &= cftal::test::check_v16<int32_t>();
    rc &= cftal::test::spec_v16s16();
    return rc == true ? 0 : 1;
}
#else

int main()
{
    return 0;
}

#endif
