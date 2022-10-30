//
// Copyright (C) 2010-2022 Axel Zeuner
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
#if !defined (__CFTAL_MATH_ELEM_FUNC_WRAPPER_F32_H__)
#define __CFTAL_MATH_ELEM_FUNC_WRAPPER_F32_H__ 1

#include <cftal/config.h>
#include <cftal/math/elem_func_core_f32.h>
#if  __CFTAL_CFG_USE_VF64_FOR_VF32__ > 0
#include <cftal/vec_cvt.h>
#include <cftal/math/elem_func_core_f64.h>
#include <cftal/math/func_traits_f64_s32.h>
#include <cftal/math/impl_d_real_constants_f64.h>

namespace cftal {
    namespace math {
        // specialization of elem_func_wrapper for float and different
        // traits
        template <typename _T>
        struct elem_func_wrapper<float, _T>
            : public elem_func_core<float, _T> {
        };
    }
}

#endif
#endif // __CFTAL_MATH_ELEM_FUNC_WRAPPER_F32_H__
