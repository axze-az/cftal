#if !defined (__CFTAL_CONSTANTS_H__)
#define __CFTAL_CONSTANTS_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>

namespace cftal {

    template <unsigned _N1, unsigned _N2>
    struct const_min {
        enum { v = (_N1 < _N2 ? _N1 : _N2) };
    };    


    template <unsigned _N1, unsigned _N2>
    struct const_max {
        enum { v = (_N1 > _N2 ? _N1 : _N2) };
    };
    
    union __attribute__((__visibility__("hidden"))) bytes8  {
        const double _f64;
        const float _f32[2];
        const int32_t _s32[2];
        const uint32_t _u32[2];
        const int64_t _s64;
        const uint64_t _u64;
        constexpr bytes8(double d) : _f64{d} {}
        constexpr bytes8(float l, float h) : _f32{l, h} {}
        constexpr bytes8(int32_t l, int32_t h) : _s32{l, h} {}
        constexpr bytes8(uint32_t l, uint32_t h) : _u32{l, h} {}
        constexpr bytes8(int64_t s) : _s64{s} {}
        constexpr bytes8(uint64_t u) : _u64{u} {}
    };
    
    template <uint32_t _L, uint32_t _H> 
    struct const_u64 {
        static
        const bytes8 v;
    };

    template <uint32_t _L, uint32_t _H>
    const bytes8 const_u64<_L, _H>::v{_L, _H};
    
    union __attribute__((__visibility__("hidden"))) bytes4 {
        const float _f32;
        const uint32_t _u32;
        const int32_t _s32;
        const uint16_t _u16[2];
        const int16_t _s16[2];
        constexpr bytes4(int16_t l, int16_t h) : _s16{l, h} {}
        constexpr bytes4(uint16_t l, uint16_t h) : _u16{l, h} {}
        constexpr bytes4(float f) : _f32{f} {}
        constexpr bytes4(int32_t u) : _s32{u} {}
        constexpr bytes4(uint32_t u) : _u32{u} {}
    };      

    template <uint32_t _N>
    struct const_u32 {
        static 
        const bytes4 v;
    };

    template <uint32_t _N>
    const bytes4 const_u32<_N>::v{_N};

    using sign_s16_msk = const_u32<0x80008000>;
    using not_sign_s16_msk = const_u32<0x7fff7fff>;
    
    using sign_s32_msk = const_u32<0x80000000>;
    using not_sign_s32_msk = const_u32<0x7fffffff>;
    using sign_f32_msk = sign_s32_msk;
    using not_sign_f32_msk = not_sign_s32_msk;
    using exp_f32_msk = const_u32<0x7f800000>;
    using not_exp_f32_msk = const_u32<0x807fffff>;
    using sig_f32_msk = const_u32<0x007fffff>;
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
        static const const_u32<0> _0;
        static const const_u32<1> _1;
        static const const_u32<2> _2;
        static const const_u32<3> _3;
        static const const_u32<4> _4;
        static const const_u32<5> _5;
        static const const_u32<6> _6;
        static const const_u32<7> _7;
        static const const_u32<8> _8;
        static const const_u32<9> _9;

        static const const_u32<10> _10;
        static const const_u32<11> _11;
        static const const_u32<12> _12;
        static const const_u32<13> _13;
        static const const_u32<14> _14;
        static const const_u32<15> _15;
        static const const_u32<16> _16;
        static const const_u32<17> _17;
        static const const_u32<18> _18;
        static const const_u32<19> _19;

        static const const_u32<20> _20;
        static const const_u32<21> _21;
        static const const_u32<22> _22;
        static const const_u32<23> _23;
        static const const_u32<24> _24;
        static const const_u32<25> _25;
        static const const_u32<26> _26;
        static const const_u32<27> _27;
        static const const_u32<28> _28;
        static const const_u32<29> _29;

        static const const_u32<30> _30;
        static const const_u32<31> _31;
        static const const_u32<32> _32;
        static const const_u32<33> _33;
        static const const_u32<34> _34;
        static const const_u32<35> _35;
        static const const_u32<36> _36;
        static const const_u32<37> _37;
        static const const_u32<38> _38;
        static const const_u32<39> _39;

        static const const_u32<40> _40;
        static const const_u32<41> _41;
        static const const_u32<42> _42;
        static const const_u32<43> _43;
        static const const_u32<44> _44;
        static const const_u32<45> _45;
        static const const_u32<46> _46;
        static const const_u32<47> _47;
        static const const_u32<48> _48;
        static const const_u32<49> _49;

        static const const_u32<50> _50;
        static const const_u32<51> _51;
        static const const_u32<52> _52;
        static const const_u32<53> _53;
        static const const_u32<54> _54;
        static const const_u32<55> _55;
        static const const_u32<56> _56;
        static const const_u32<57> _57;
        static const const_u32<58> _58;
        static const const_u32<59> _59;

        static const const_u32<60> _60;
        static const const_u32<61> _61;
        static const const_u32<62> _62;
        static const const_u32<63> _63;            
    }
}

// Local variables:
// mode: c++
// end:
#endif
