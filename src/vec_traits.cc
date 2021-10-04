//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/math/vec_func_traits.h"

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
