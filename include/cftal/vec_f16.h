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
#if !defined (__CFTAL_VEC_F16_H__)
#define __CFTAL_VEC_F16_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
// this file should be included in vec_spec.h:
#include <cftal/vxf16.h>

#define V2F16_FUNCS 1
#define V4F16_FUNCS                                                     \
    ((V4F16_SPECIALIZED>0) || ((V2F16_SPECIALIZED>0) && (V2S16_SPECIALIZED>0)))
#define V8F16_FUNCS                                                     \
    ((V8F16_SPECIALIZED>0) || ((V4F16_SPECIALIZED>0) && (V4S16_SPECIALIZED>0)))
#define V16F16_FUNCS                                                    \
    ((V16F16_SPECIALIZED>0) || ((V8F16_SPECIALIZED>0) && (V8S16_SPECIALIZED>0)))

namespace cftal {


#if V2F16_FUNCS>0
#endif
#if V4F16_FUNCS>0
#endif
#if V8F16_FUNCS>0
#endif
#if V16F16_FUNCS>0
#endif

}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_VEC_F16_H__
