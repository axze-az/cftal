//
// Copyright (C) 2010-2026 Axel Zeuner
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
#include <cftal/config.h>
#if defined (__SSE2__)
#include <cftal/x86/ins_ext.h>

const cftal::x86::u_v2x64
cftal::x86::ins_msk_v2x64[2]={
    {{-1, 0}},
    {{0, -1}}
};

const cftal::x86::u_v4x32
cftal::x86::ins_msk_v4x32[4]={
    {{-1, 0, 0, 0}},
    {{0, -1, 0, 0}},
    {{0, 0, -1, 0}},
    {{0, 0, 0, -1}}
};

const cftal::x86::u_v8x16
cftal::x86::ins_msk_v8x16[8]={
    {{-1, 0, 0, 0, 0, 0, 0, 0}},
    {{0, -1, 0, 0, 0, 0, 0, 0}},
    {{0, 0, -1, 0, 0, 0, 0, 0}},
    {{0, 0, 0, -1, 0, 0, 0, 0}},
    {{0, 0, 0, 0, -1, 0, 0, 0}},
    {{0, 0, 0, 0, 0, -1, 0, 0}},
    {{0, 0, 0, 0, 0, 0, -1, 0}},
    {{0, 0, 0, 0, 0, 0, 0, -1}}
};

const cftal::x86::u_v16x8 cftal::x86::ins_msk_v16x8[16]={
    {{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0}},
    {{0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0}},
    {{0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0}},
    {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0}},
    {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0}},
    {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0}},
    {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0}},
    {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0}},
    {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1}}
};

#if defined (__AVX__)
const cftal::x86::u_v4x64
cftal::x86::ins_msk_v4x64[4]={
    {{-1, 0, 0, 0}},
    {{0, -1, 0, 0}},
    {{0, 0, -1, 0}},
    {{0, 0, 0, -1}}
};

const cftal::x86::u_v8x32
cftal::x86::ins_msk_v8x32[8]={
    {{-1, 0, 0, 0, 0, 0, 0, 0}},
    {{0, -1, 0, 0, 0, 0, 0, 0}},
    {{0, 0, -1, 0, 0, 0, 0, 0}},
    {{0, 0, 0, -1, 0, 0, 0, 0}},
    {{0, 0, 0, 0, -1, 0, 0, 0}},
    {{0, 0, 0, 0, 0, -1, 0, 0}},
    {{0, 0, 0, 0, 0, 0, -1, 0}},
    {{0, 0, 0, 0, 0, 0, 0, -1}}
};
#endif
#endif
