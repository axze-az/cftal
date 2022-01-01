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
#if !defined (__CFTAL_CONSTANTS_H__)
#define __CFTAL_CONSTANTS_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>

namespace cftal {

    // compile time min
    template <uint32_t _N1, uint32_t _N2>
    struct const_min_u32 {
        enum { v = (_N1 < _N2 ? _N1 : _N2) };
    };

    template <uint32_t _N1, uint32_t _N2>
    struct const_max_u32 {
        enum { v = (_N1 > _N2 ? _N1 : _N2) };
    };

    // 8 byte union
    union __attribute__((__visibility__("hidden"))) bytes8  {
    private:
        const double _f64;
        const uint64_t _u64;
    public:
        constexpr bytes8(double d) : _f64{d} {}
        constexpr bytes8(int32_t l, int32_t h)
            : _u64((uint64_t(h) << 32) | uint32_t(l)) {}
        constexpr bytes8(uint32_t l, uint32_t h)
            : _u64((uint64_t(h) << 32) | uint32_t(l)) {}
        constexpr bytes8(int64_t s) : _u64(s) {}
        constexpr bytes8(uint64_t u) : _u64{u} {}
        constexpr uint64_t u64() const { return _u64; }
        constexpr int64_t s64() const { return _u64; }
        constexpr double f64() const { return _f64; }
        constexpr uint32_t u32l() const { return uint32_t(_u64); }
        constexpr uint32_t u32h() const { return uint32_t(_u64>>32); }
        constexpr int32_t s32l() const { return int32_t(_u64); }
        constexpr int32_t s32h() const { return int32_t(_u64>>32); }
    };

    // compile time 8 byte union
    template <uint32_t _L, uint32_t _H>
    struct const_u64 {
        constexpr const_u64() {} // keep clang happy
        static
        const bytes8 v;
    };
    template <uint32_t _L, uint32_t _H>
    const bytes8 const_u64<_L, _H>::v{_L, _H};

    // 4 byte union
    union __attribute__((__visibility__("hidden"))) bytes4 {
    private:
        const float _f32;
        const uint32_t _u32;
    public:
        constexpr bytes4(float f) : _f32{f} {}
        constexpr bytes4(int32_t s) : _u32{uint32_t(s)} {}
        constexpr bytes4(uint32_t u) : _u32{u} {}
        constexpr float f32() const { return _f32; }
        constexpr uint32_t u32() const { return _u32; }
        constexpr int32_t s32() const { return int32_t(_u32); }
        constexpr uint16_t u16l() const { return _u32; }
        constexpr uint16_t u16h() const { return _u32>>16; }
        constexpr uint8_t u8ll() const { return _u32; }
        constexpr uint8_t u8lh() const { return _u32>>8; }
        constexpr uint8_t u8hl() const { return _u32>>16; }
        constexpr uint8_t u8hh() const { return _u32>>24; }
        constexpr int16_t s16l() const { return _u32; }
        constexpr int16_t s16h() const { return _u32 >>16; }
        constexpr int8_t s8ll() const { return _u32; }
        constexpr int8_t s8lh() const { return _u32>>8; }
        constexpr int8_t s8hl() const { return _u32>>16; }
        constexpr int8_t s8hh() const { return _u32>>24; }
    };

    // compile time 4 byte union
    template <uint32_t _N>
    struct const_u32 {
        constexpr const_u32() {} // keep clang happy
        static
        const bytes4 v;
    };


    template <uint32_t _N>
    const bytes4 const_u32<_N>::v{_N};

    // 2 byte compile time union
    class bytes2 {
    private:
        uint16_t _u16;
    public:
        constexpr bytes2(int16_t i) : _u16(i) {}
        constexpr bytes2(uint16_t u) : _u16(u) {}
        constexpr uint16_t u16() const { return _u16; }
        constexpr int16_t s16() const { return int16_t(_u16); }
    };
    template <uint16_t _N>
    struct const_u16 {
        constexpr const_u16() {}
        static
        const bytes2 v;
    };

    template <uint16_t _N>
    const bytes2 const_u16<_N>::v{_N};

    using sign_s8_msk = const_u32<0x80808080>;
    using not_sign_s8_msk = const_u32<0x7f7f7f7f>;
    
    using sign_s16_msk = const_u32<0x80008000>;
    using not_sign_s16_msk = const_u32<0x7fff7fff>;

    using sign_s32_msk = const_u32<0x80000000>;
    using not_sign_s32_msk = const_u32<0x7fffffff>;
    using sign_f32_msk = sign_s32_msk;
    using not_sign_f32_msk = not_sign_s32_msk;
    using exp_f32_msk = const_u32<0x7f800000>;
    using not_exp_f32_msk = const_u32<0x807fffff>;
    using sig_f32_msk = const_u32<0x007fffff>;
    const int bias_f32 = 0x7f;
    const int exp_shift_f32 = 23;
    const int exp_msk_f32 = 0xff;

    using sign_s64_msk= const_u64<0x00000000, 0x80000000>;
    using not_sign_s64_msk = const_u64<0xffffffff, 0x7fffffff>;
    using sign_f64_msk = sign_s64_msk;
    using not_sign_f64_msk = not_sign_s64_msk;
    using exp_f64_msk = const_u64<0x00000000,0x7ff00000>;
    using sig_f64_msk = const_u64<0xffffffff, 0x000fffff>;
    const int bias_f64 = 0x3ff;
    const int exp_shift_f64 = 52;
    const int exp_msk_f64 = 0x7ff;

    namespace const_shift {
        constexpr static const const_u32<0> _0;
        constexpr static const const_u32<1> _1;
        constexpr static const const_u32<2> _2;
        constexpr static const const_u32<3> _3;
        constexpr static const const_u32<4> _4;
        constexpr static const const_u32<5> _5;
        constexpr static const const_u32<6> _6;
        constexpr static const const_u32<7> _7;
        constexpr static const const_u32<8> _8;
        constexpr static const const_u32<9> _9;

        constexpr static const const_u32<10> _10;
        constexpr static const const_u32<11> _11;
        constexpr static const const_u32<12> _12;
        constexpr static const const_u32<13> _13;
        constexpr static const const_u32<14> _14;
        constexpr static const const_u32<15> _15;
        constexpr static const const_u32<16> _16;
        constexpr static const const_u32<17> _17;
        constexpr static const const_u32<18> _18;
        constexpr static const const_u32<19> _19;

        constexpr static const const_u32<20> _20;
        constexpr static const const_u32<21> _21;
        constexpr static const const_u32<22> _22;
        constexpr static const const_u32<23> _23;
        constexpr static const const_u32<24> _24;
        constexpr static const const_u32<25> _25;
        constexpr static const const_u32<26> _26;
        constexpr static const const_u32<27> _27;
        constexpr static const const_u32<28> _28;
        constexpr static const const_u32<29> _29;

        constexpr static const const_u32<30> _30;
        constexpr static const const_u32<31> _31;
        constexpr static const const_u32<32> _32;
        constexpr static const const_u32<33> _33;
        constexpr static const const_u32<34> _34;
        constexpr static const const_u32<35> _35;
        constexpr static const const_u32<36> _36;
        constexpr static const const_u32<37> _37;
        constexpr static const const_u32<38> _38;
        constexpr static const const_u32<39> _39;

        constexpr static const const_u32<40> _40;
        constexpr static const const_u32<41> _41;
        constexpr static const const_u32<42> _42;
        constexpr static const const_u32<43> _43;
        constexpr static const const_u32<44> _44;
        constexpr static const const_u32<45> _45;
        constexpr static const const_u32<46> _46;
        constexpr static const const_u32<47> _47;
        constexpr static const const_u32<48> _48;
        constexpr static const const_u32<49> _49;

        constexpr static const const_u32<50> _50;
        constexpr static const const_u32<51> _51;
        constexpr static const const_u32<52> _52;
        constexpr static const const_u32<53> _53;
        constexpr static const const_u32<54> _54;
        constexpr static const const_u32<55> _55;
        constexpr static const const_u32<56> _56;
        constexpr static const const_u32<57> _57;
        constexpr static const const_u32<58> _58;
        constexpr static const const_u32<59> _59;

        constexpr static const const_u32<60> _60;
        constexpr static const const_u32<61> _61;
        constexpr static const const_u32<62> _62;
        constexpr static const const_u32<63> _63;
    }
}

// Local variables:
// mode: c++
// end:
#endif
