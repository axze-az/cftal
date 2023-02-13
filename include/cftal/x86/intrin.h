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
#if !defined (__CFTAL_X86_INTRIN_H__)
#define __CFTAL_X86_INTRIN_H__ 1

#include <cftal/config.h>

#if IN_KDEVELOP_PARSER !=0 || IN_IDE_PARSER !=0
#define __AVX__ 1
#define __SSE4_1__ 1
#define __SSE4_2__ 1
#define __SSE4A__ 1
#define __SSSE3__ 1
#define __AVX2__ 1
#define __FMA__ 1
#define alignas(x)
#endif

#if defined (__SSE4_1__) && !defined (__POPCNT__)
#define __POPCNT__
#endif

#if defined (__SSE4A__) && !defined (__POPCNT__)
#define __POPCNT__
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
#if !defined (__clang__)
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
#include <x86intrin.h>
#pragma GCC diagnostic pop

// Local variables:
// mode: c++
// end:
#endif
