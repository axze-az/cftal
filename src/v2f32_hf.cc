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
#include "cftal/math/vec_func_traits.h"
#include "cftal/math/half_func.h"
#include "vec_def_math_half_funcs.h"
#include <cmath>
#include <limits>

#if V2F32_FUNCS>0
DEF_HALF_FUNCS(cftal, cftal::half_math, v2f32, v2s32, float)
#endif
