//
// Copyright (C) 2010-2024 Axel Zeuner
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
#include "cftal/test/program.h"
#include "cftal/test/check_log1p.h"
#include "cftal/vec_f16.h"

namespace cftal {
    namespace test {
        template <>
        struct domain_logx1p<f16_t> {
            static
            const func_domain<f16_t> domains[];

            constexpr static
            const int shifts[]={
                0
            };
        };
    }
}

const cftal::test::func_domain<cftal::f16_t>
cftal::test::domain_logx1p<cftal::f16_t>::domains[]={
    std::make_pair(-1.0_f16, std::numeric_limits<f16_t>::max())
};


int main(int argc, char** argv)
{
    using namespace cftal::test;
    using cftal::f16_t;
    int r=program<check_log1p<f16_t>, 32, 1, 0x4000>(
        argc,
        argv,
        mpfr_log1p,
        domain_log1p<f16_t>::domains,
        domain_log1p<f16_t>::shifts);
    return r;
}
