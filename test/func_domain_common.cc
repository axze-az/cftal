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
#include "cftal/test/func_domain_common.h"

// non constexpr f16_t function domains
const cftal::test::func_domain<cftal::f16_t>
cftal::test::domain_sin_cos_tan<cftal::f16_t>::domains2[1]={
    std::make_pair(-6.28_f16, 6.28_f16)
};

const cftal::test::func_domain<cftal::f16_t>
cftal::test::domain_sinh_cosh<cftal::f16_t>::domains[1]={
    std::make_pair(-11.9_f16, 11.9_f16)
};
