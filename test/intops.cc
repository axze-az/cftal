#include <cftal/test/intops.h>
#include <cftal/bitops.h>
#include <cftal/x86/ops_1.h>
#include <iostream>

namespace {

    template <typename _T>
    bool chk(_T expected, _T res, int src, const char* pfx)
    {
        bool r(expected == res);
        if (!r) {
            std::cout << pfx << "("
                      << std::hex << "0x"
                      << unsigned(src) << std::dec
                      << ") =" << res
                      << " != " << expected
                      << std::endl;
        }
        return r;
    }
}

bool cftal::test::check_popcnt()
{
    std::uint8_t exp_u8[16];
    std::uint16_t exp_u16[8];
    std::uint32_t exp_u32[4];
    std::uint64_t exp_u64[2];
    std::uint64_t exp_u128;
    union {
        __m128i _v;
        uint8_t _u8[16];
        uint16_t _u16[8];
        uint32_t _u32[4];
        uint64_t _u64[2];
    } src;
    bool r(true);
    for (int i=0; i<256; i+=16) {
        for (int j=0; j<16;++j) {
            src._u8[j] = j+i;
            exp_u8[j] = cftal::popcnt(src._u8[j]);
        };
        for (int j=0; j<8; ++j)
            exp_u16[j] = cftal::popcnt(src._u16[j]);
        for (int j=0; j<4; ++j)
            exp_u32[j] = cftal::popcnt(src._u32[j]);
        for (int j=0; j<2; ++j)
            exp_u64[j] = cftal::popcnt(src._u64[j]);
        exp_u128 = exp_u64[0] + exp_u64[1];

        __m128i ru8 = x86::popcnt_u8(src._v);
        __m128i ru16= x86::popcnt_u16(src._v);
        __m128i ru32= x86::popcnt_u32(src._v);
        __m128i ru64= x86::popcnt_u64(src._v);
        std::uint64_t ru128 = x86::popcnt_u128(src._v);
        using namespace x86;
        r &= chk(extract_u8<0>(ru8), exp_u8[0], src._u8[0],
                 "popcnt_u8");
        r &= chk(extract_u8<1>(ru8), exp_u8[1], src._u8[1],
                 "popcnt_u8");
        r &= chk(extract_u8<2>(ru8), exp_u8[2], src._u8[2],
                 "popcnt_u8");
        r &= chk(extract_u8<3>(ru8), exp_u8[3], src._u8[3],
                 "popcnt_u8");
        r &= chk(extract_u8<4>(ru8), exp_u8[4], src._u8[4],
                 "popcnt_u8");
        r &= chk(extract_u8<5>(ru8), exp_u8[5], src._u8[5],
                 "popcnt_u8");
        r &= chk(extract_u8<6>(ru8), exp_u8[6], src._u8[6],
                 "popcnt_u8");
        r &= chk(extract_u8<7>(ru8), exp_u8[7], src._u8[7],
                 "popcnt_u8");
        r &= chk(extract_u8<8>(ru8), exp_u8[8], src._u8[8],
                 "popcnt_u8");
        r &= chk(extract_u8<9>(ru8), exp_u8[9], src._u8[9],
                 "popcnt_u8");
        r &= chk(extract_u8<10>(ru8), exp_u8[10], src._u8[10],
                 "popcnt_u8");
        r &= chk(extract_u8<11>(ru8), exp_u8[11], src._u8[11],
                 "popcnt_u8");
        r &= chk(extract_u8<12>(ru8), exp_u8[12], src._u8[12],
                 "popcnt_u8");
        r &= chk(extract_u8<13>(ru8), exp_u8[13], src._u8[13],
                 "popcnt_u8");
        r &= chk(extract_u8<14>(ru8), exp_u8[14], src._u8[14],
                 "popcnt_u8");
        r &= chk(extract_u8<15>(ru8), exp_u8[15], src._u8[15],
                 "popcnt_u8");

        r &= chk(extract_u16<0>(ru16), exp_u16[0], src._u16[0],
                 "popcnt_u16");
        r &= chk(extract_u16<1>(ru16), exp_u16[1], src._u16[1],
                 "popcnt_u16");
        r &= chk(extract_u16<2>(ru16), exp_u16[2], src._u16[2],
                 "popcnt_u16");
        r &= chk(extract_u16<3>(ru16), exp_u16[3], src._u16[3],
                 "popcnt_u16");
        r &= chk(extract_u16<4>(ru16), exp_u16[4], src._u16[4],
                 "popcnt_u16");
        r &= chk(extract_u16<5>(ru16), exp_u16[5], src._u16[5],
                 "popcnt_u16");
        r &= chk(extract_u16<6>(ru16), exp_u16[6], src._u16[6],
                 "popcnt_u16");
        r &= chk(extract_u16<7>(ru16), exp_u16[7], src._u16[7],
                 "popcnt_u16");

        r &= chk(extract_u32<0>(ru32), exp_u32[0], src._u32[0],
                 "popcnt_u32");
        r &= chk(extract_u32<1>(ru32), exp_u32[1], src._u32[1],
                 "popcnt_u32");
        r &= chk(extract_u32<2>(ru32), exp_u32[2], src._u32[2],
                 "popcnt_u32");
        r &= chk(extract_u32<3>(ru32), exp_u32[3], src._u32[3],
                 "popcnt_u32");

        r &= chk(extract_u64<0>(ru64), exp_u64[0], src._u64[0],
                 "popcnt_u64");
        r &= chk(extract_u64<1>(ru64), exp_u64[1], src._u64[1],
                 "popcnt_u64");
        r &= chk(ru128, exp_u128, -1, "popcnt_u128");
    }
    return r;
}

bool cftal::test::check_bitrev()
{
    std::uint8_t exp_u8[16];
    std::uint16_t exp_u16[8];
    std::uint32_t exp_u32[4];
    std::uint64_t exp_u64[2];
    union {
        __m128i _v;
        uint8_t _u8[16];
        uint16_t _u16[8];
        uint32_t _u32[4];
        uint64_t _u64[2];
    } src;
    bool r(true);
    for (int i=0; i<256; i+=16) {
        for (int j=0; j<16;++j) {
            src._u8[j] = j+i;
            exp_u8[j] = cftal::bitrev(src._u8[j]);
        };
        for (int j=0; j<8; ++j)
            exp_u16[j] = cftal::bitrev(src._u16[j]);
        for (int j=0; j<4; ++j)
            exp_u32[j] = cftal::bitrev(src._u32[j]);
        for (int j=0; j<2; ++j)
            exp_u64[j] = cftal::bitrev(src._u64[j]);
        __m128i ru8 = x86::bitrev_u8(src._v);
        __m128i ru16= x86::bitrev_u16(src._v);
        __m128i ru32= x86::bitrev_u32(src._v);
        __m128i ru64= x86::bitrev_u64(src._v);
        using namespace x86;
        r &= chk(extract_u8<0>(ru8), exp_u8[0], src._u8[0],
                 "bitrev_u8");
        r &= chk(extract_u8<1>(ru8), exp_u8[1], src._u8[1],
                 "bitrev_u8");
        r &= chk(extract_u8<2>(ru8), exp_u8[2], src._u8[2],
                 "bitrev_u8");
        r &= chk(extract_u8<3>(ru8), exp_u8[3], src._u8[3],
                 "bitrev_u8");
        r &= chk(extract_u8<4>(ru8), exp_u8[4], src._u8[4],
                 "bitrev_u8");
        r &= chk(extract_u8<5>(ru8), exp_u8[5], src._u8[5],
                 "bitrev_u8");
        r &= chk(extract_u8<6>(ru8), exp_u8[6], src._u8[6],
                 "bitrev_u8");
        r &= chk(extract_u8<7>(ru8), exp_u8[7], src._u8[7],
                 "bitrev_u8");
        r &= chk(extract_u8<8>(ru8), exp_u8[8], src._u8[8],
                 "bitrev_u8");
        r &= chk(extract_u8<9>(ru8), exp_u8[9], src._u8[9],
                 "bitrev_u8");
        r &= chk(extract_u8<10>(ru8), exp_u8[10], src._u8[10],
                 "bitrev_u8");
        r &= chk(extract_u8<11>(ru8), exp_u8[11], src._u8[11],
                 "bitrev_u8");
        r &= chk(extract_u8<12>(ru8), exp_u8[12], src._u8[12],
                 "bitrev_u8");
        r &= chk(extract_u8<13>(ru8), exp_u8[13], src._u8[13],
                 "bitrev_u8");
        r &= chk(extract_u8<14>(ru8), exp_u8[14], src._u8[14],
                 "bitrev_u8");
        r &= chk(extract_u8<15>(ru8), exp_u8[15], src._u8[15],
                 "bitrev_u8");

        r &= chk(extract_u16<0>(ru16), exp_u16[0], src._u16[0],
                 "bitrev_u16");
        r &= chk(extract_u16<1>(ru16), exp_u16[1], src._u16[1],
                 "bitrev_u16");
        r &= chk(extract_u16<2>(ru16), exp_u16[2], src._u16[2],
                 "bitrev_u16");
        r &= chk(extract_u16<3>(ru16), exp_u16[3], src._u16[3],
                 "bitrev_u16");
        r &= chk(extract_u16<4>(ru16), exp_u16[4], src._u16[4],
                 "bitrev_u16");
        r &= chk(extract_u16<5>(ru16), exp_u16[5], src._u16[5],
                 "bitrev_u16");
        r &= chk(extract_u16<6>(ru16), exp_u16[6], src._u16[6],
                 "bitrev_u16");
        r &= chk(extract_u16<7>(ru16), exp_u16[7], src._u16[7],
                 "bitrev_u16");

        r &= chk(extract_u32<0>(ru32), exp_u32[0], src._u32[0],
                 "bitrev_u32");
        r &= chk(extract_u32<1>(ru32), exp_u32[1], src._u32[1],
                 "bitrev_u32");
        r &= chk(extract_u32<2>(ru32), exp_u32[2], src._u32[2],
                 "bitrev_u32");
        r &= chk(extract_u32<3>(ru32), exp_u32[3], src._u32[3],
                 "bitrev_u32");

        r &= chk(extract_u64<0>(ru64), exp_u64[0], src._u64[0],
                 "bitrev_u64");
        r &= chk(extract_u64<1>(ru64), exp_u64[1], src._u64[1],
                 "bitrev_u64");
    }
    return r;
}
