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
#include "cftal/vec.h"
#include "cftal/math/vec_func_traits_bf16.h"
#include "cftal/math/spec_func_wrapper_bf16.h"
#include "vec_def_math_spec_funcs.h"

DEF_SPEC_FUNCS(cftal, cftal, v1bf16, v1s16, bf16_t)
DEF_SLOW_SPEC_FUNCS(cftal, cftal, v1bf16, v1s16, bf16_t)
