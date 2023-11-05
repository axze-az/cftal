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
#include "cftal/math/vec_func_traits_f32.h"
#include "cftal/math/vec_func_traits_f64.h"

#if 0
const cftal::v4s32
cftal::math::func_traits<cftal::v2f64, cftal::v2s32>::_vmi_to_vmf_msk[4]= {
    {  0,  0,  0,  0},
    { -1, -1,  0,  0},
    {  0,  0, -1, -1},
    { -1, -1, -1, -1}
};

const cftal::vec<bool, 2>
cftal::math::func_traits<cftal::v2f64, cftal::v2s32>::_vmf_to_vmi_msk[4]= {
    {false, false},
    {true, false},
    {false, true},
    {true, true}
};
#endif
