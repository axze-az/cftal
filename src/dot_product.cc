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
#include "cftal/impl/dot_product.h"
#include <sstream>

void
cftal::impl::dot_product_stride_a_zero()
{
    const char* pe=
        "stride_a==0 in "
        "_T cftal::impl::"
        "dot_product(size_t s, const _T* a, "
        "int32_t stride_a, size_t offset_a, "
        "const _T* b)";
    throw std::domain_error(pe);
}

void
cftal::impl::dot_product_stride_a_or_b_zero(char ab)
{
    std::ostringstream es;
    es << "stride_" << ab
        << "==0 in "
            "_T cftal::impl::"
            "dot_product(size_t s, const _T*a, "
            "int32_t stride_a, size_t offset_a, "
            "const _T* b, "
            "int32_t stride_b, size_t offset_b)";
    throw std::domain_error(es.str());
}
