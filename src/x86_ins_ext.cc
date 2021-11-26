//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
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
