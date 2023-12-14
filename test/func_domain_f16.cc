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
#include "cftal/test/check_exp.h"
#include "cftal/test/check_exp10.h"
#include "cftal/test/check_exp2.h"
#include "cftal/test/check_exp10m1.h"
#include "cftal/test/check_exp2m1.h"
#include "cftal/test/check_expm1.h"

// non constexpr f16_t function domains not defined in func_domain_common.cc
const cftal::test::func_domain<cftal::f16_t>
cftal::test::domain_exp<cftal::f16_t>::domains[1]= {
    std::make_pair(-18.0_f16, 12.0_f16)
};

const cftal::test::func_domain<cftal::f16_t>
cftal::test::domain_exp10<cftal::f16_t>::domains[1]= {
    std::make_pair(-7.6_f16, 4.9_f16)
};

const cftal::test::func_domain<cftal::f16_t>
cftal::test::domain_exp2<cftal::f16_t>::domains[1]={
    std::make_pair(-25.5_f16, 16.5_f16)
};

const cftal::test::func_domain<cftal::f16_t>
cftal::test::domain_exp10m1<cftal::f16_t>::domains[2]={
    std::make_pair(-3.7_f16, 4.9_f16),
    std::make_pair(-0x1p-3_f16, 0x1p-3_f16)
};

const cftal::test::func_domain<cftal::f16_t>
cftal::test::domain_exp2m1<cftal::f16_t>::domains[2]={
    std::make_pair(-26.5_f16, 16.5_f16),
    std::make_pair(-0x1p-3_f16, 0x1p-3_f16)
};

const cftal::test::func_domain<cftal::f16_t>
cftal::test::domain_expm1<cftal::f16_t>::domains[2]={
    std::make_pair(-8.5_f16, 11.5_f16),
    std::make_pair(-0x1p-3_f16, 0x1p-3_f16)
};


