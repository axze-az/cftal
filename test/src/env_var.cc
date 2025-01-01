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
#include "cftal/test/env_var.h"
#include <cstdlib>
#include <string_view>

namespace {
    const char cftal_dev[]="CFTAL_DEV\0";
}

bool
cftal::test::env_use_cache()
{
    const char* p=std::getenv(cftal_dev);
    bool r=false;
    if (p != nullptr) {
        const std::string_view sv(p);
        if ((sv == "cf") || (sv == "fc") || (sv =="c"))
            r=true;
    }
    return r;
}

bool
cftal::test::env_faster_tests()
{
    const char* p=std::getenv(cftal_dev);
    bool r=false;
    if (p != nullptr) {
        const std::string_view sv(p);
        if ((sv == "cf") || (sv == "fc") || (sv =="f"))
            r=true;
    }
    return r;
}
