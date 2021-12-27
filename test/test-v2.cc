// 
// Copyright (C) 2010-2021 Axel Zeuner
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
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA  
//
#include <cftal/config.h>
#include <cftal/test/of_vec.h>
#include <cftal/test/of_vec_v2.h>

int main()
{
    bool rc(true);
    rc &= cftal::test::check_v2<double>();
    rc &= cftal::test::check_v2<float>();
    rc &= cftal::test::check_v2<int32_t>();
    rc &= cftal::test::check_v2<uint32_t>();
    rc &= cftal::test::check_v2<int64_t>();
    rc &= cftal::test::check_v2<uint64_t>();
    // rc &= cftal::test::check_v4<float>();
    // rc &= cftal::test::check_v4<int32_t>();
    // rc &= cftal::test::check_v4<uint32_t>();
    return rc == true ? 0 : 1;
}
