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
#if !defined (__CFTAL_TEST_INTOPS_H__)
#define __CFTAL_TEST_INTOPS_H__ 1

#include <cftal/config.h>

namespace cftal {

    namespace test {

        bool check_div_s16();
        bool check_div_u16();
        bool check_div_s32();
        bool check_div_u32();
        bool check_div_s64();
        bool check_div_u64();
        
        bool check_xxx_of();
        bool check_bitrev();
        bool check_popcnt();
        bool check_div();
        
    }
}

// Local variables:
// mode: c++
// end:
#endif
