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
#if defined (__SSE2__)
#include <iostream>
#include <cftal/test/f32_f64.h>
#include <cftal/test/cpu_times.h>
#include <cftal/vec.h>
#include <random>
#include <sstream>
#include <iomanip>

namespace cftal::test {

    bool of_emul_vpshufb();

    template <typename _T, size_t _N>
    struct expand_and_compress {
        static
        uint64_t mask(uint64_t msk);
    };

    template <>
    struct expand_and_compress<int8_t, 16> {
        static
        uint64_t mask(uint64_t msk) {
            auto t=x86::expand_mask_v16u8(msk);
            return x86::compress_mask_u8(t);
        }
    };

    template <>
    struct expand_and_compress<uint8_t, 16> {
        static
        uint64_t mask(uint64_t msk) {
            auto t=x86::expand_mask_v16u8(msk);
            return x86::compress_mask_u8(t);
        }
    };

    template <>
    struct expand_and_compress<int16_t, 8> {
        static
        uint64_t mask(uint64_t msk) {
            auto t=x86::expand_mask_v8u16(msk);
            return x86::compress_mask_u16(t);
        }
    };

    template <>
    struct expand_and_compress<uint16_t, 8> {
        static
        uint64_t mask(uint64_t msk) {
            auto t=x86::expand_mask_v8u16(msk);
            return x86::compress_mask_u16(t);
        }
    };

    template <>
    struct expand_and_compress<int32_t, 4> {
        static
        uint64_t mask(uint64_t msk) {
            auto t=x86::expand_mask_v4u32(msk);
            return x86::compress_mask_u32(t);
        }
    };

    template <>
    struct expand_and_compress<uint32_t, 4> {
        static
        uint64_t mask(uint64_t msk) {
            auto t=x86::expand_mask_v4u32(msk);
            return x86::compress_mask_u32(t);
        }
    };

    template <>
    struct expand_and_compress<int64_t, 2> {
        static
        uint64_t mask(uint64_t msk) {
            auto t=x86::expand_mask_v2u64(msk);
            return x86::compress_mask_u64(t);
        }
    };

    template <>
    struct expand_and_compress<uint64_t, 2> {
        static
        uint64_t mask(uint64_t msk) {
            auto t=x86::expand_mask_v2u64(msk);
            return x86::compress_mask_u64(t);
        }
    };

    template <>
    struct expand_and_compress<float, 4> {
        static
        uint64_t mask(uint64_t msk) {
            auto t=x86::expand_mask_v4f32(msk);
            return x86::compress_mask_f32(t);
        }
    };

    template <>
    struct expand_and_compress<double, 2> {
        static
        uint64_t mask(uint64_t msk) {
            auto t=x86::expand_mask_v2f64(msk);
            return x86::compress_mask_f64(t);
        }
    };

#if defined (__AVX__)
    template <>
    struct expand_and_compress<float, 8> {
        static
        uint64_t mask(uint64_t msk) {
            auto t=x86::expand_mask_v8f32(msk);
            return x86::compress_mask_f32(t);
        }
    };

    template <>
    struct expand_and_compress<double, 4> {
        static
        uint64_t mask(uint64_t msk) {
            auto t=x86::expand_mask_v4f64(msk);
            return x86::compress_mask_f64(t);
        }
    };
#endif

#if defined (__AVX2__)
    template <>
    struct expand_and_compress<int8_t, 32> {
        static
        uint64_t mask(uint64_t msk) {
            auto t=x86::expand_mask_v32u8(msk);
            return x86::compress_mask_u8(t);
        }
    };

    template <>
    struct expand_and_compress<uint8_t, 32> {
        static
        uint64_t mask(uint64_t msk) {
            auto t=x86::expand_mask_v32u8(msk);
            return x86::compress_mask_u8(t);
        }
    };

    template <>
    struct expand_and_compress<int16_t, 16> {
        static
        uint64_t mask(uint64_t msk) {
            auto t=x86::expand_mask_v16u16(msk);
            return x86::compress_mask_u16(t);
        }
    };

    template <>
    struct expand_and_compress<uint16_t, 16> {
        static
        uint64_t mask(uint64_t msk) {
            auto t=x86::expand_mask_v16u16(msk);
            return x86::compress_mask_u16(t);
        }
    };

    template <>
    struct expand_and_compress<int32_t, 8> {
        static
        uint64_t mask(uint64_t msk) {
            auto t=x86::expand_mask_v8u32(msk);
            return x86::compress_mask_u32(t);
        }
    };

    template <>
    struct expand_and_compress<uint32_t, 8> {
        static
        uint64_t mask(uint64_t msk) {
            auto t=x86::expand_mask_v8u32(msk);
            return x86::compress_mask_u32(t);
        }
    };

    template <>
    struct expand_and_compress<int64_t, 4> {
        static
        uint64_t mask(uint64_t msk) {
            auto t=x86::expand_mask_v4u64(msk);
            return x86::compress_mask_u64(t);
        }
    };

    template <>
    struct expand_and_compress<uint64_t, 4> {
        static
        uint64_t mask(uint64_t msk) {
            auto t=x86::expand_mask_v4u64(msk);
            return x86::compress_mask_u64(t);
        }
    };
#endif

    template <typename _T, size_t _N>
    bool
    expand_and_compress_mask();

    bool
    expand_and_compress_masks();

    bool of_bit_pack_unpack();
}

bool
cftal::test::of_emul_vpshufb()
{
#if !defined (__SSSE3__)
    std::cout << "test of vpshufb emulation not possible\n";
    return true;
#else
    auto prv=[](const v16u8& v)->std::string {
        std::ostringstream s;
        s << std::hex << std::setfill('0');
        x86::vecunion <uint8_t, 16, __m128, __m128d, __m128i> t;
        t._vi=v();
        for (int i=0; i<16; ++i) {
            if (i)
                s << ' ';
            s << std::setw(2) << uint32_t(t._s[i]);
        }
        return s.str();
    };
    bool r=true;
    x86::vecunion <uint8_t, 16, __m128, __m128d, __m128i>
        msk;
    v16u8 vr, ve;
    v16u8 s{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    std::uniform_int_distribution<> d_m1_15(-1, 15);
    std::mt19937 rnd;
    for (int i=0; i<10'000'000L; ++i) {
        for (int p=0; p<16; ++p) {
            msk._s[p] = d_m1_15(rnd);
        }
        v16u8 vmsk=msk._vi;
        vr=_mm_shuffle_epi8(s(), vmsk());
        ve=x86::vpshufb::emul(s(), vmsk());
        v16u8::mask_type eq=vr==ve;
        if (!all_of(eq)) {
            std::cout << "vpshufb emulation failed\ns:  "
                      << prv(s)
                      << "\nm:  " << prv(vmsk)
                      << "\nvr: " << prv(vr)
                      << "\nve: " << prv(ve)
                      << '\n';
            r=false;
        }
    }
    if (r == true) {
        std::cout << "test of vpshufb emulation passed\n";
    }
    return r;
#endif
}

template <typename _T, size_t _N>
bool
cftal::test::expand_and_compress_mask()
{
    bool r=true;
    uint64_t c0=1<<_N/2, c1=1<<(_N-_N/2);
    for (uint64_t i0=0; i0<c0; ++i0) {
        // std::cout << std::setw(12) << i0 << '\r' << std::flush;
        for (uint64_t i1=0; i1<c1; ++i1) {
            uint64_t msk= (i0 << (_N-_N/2)) + i1;
            uint64_t rmsk=expand_and_compress<_T, _N>::mask(msk);
            if (msk != rmsk) {
                std::cerr << __PRETTY_FUNCTION__
                          << " FAILURE: "
                          << std::hex << rmsk
                          << " expected: "
                          << msk
                          << '\n';
                r=false;
                break;
            }
        }
    }
    if (r==true) {
        std::cout << "test of\n" << __PRETTY_FUNCTION__ << "\npassed\n";
    }
    return r;
}

bool
cftal::test::expand_and_compress_masks()
{
    bool r=true;
    r &= expand_and_compress_mask<int8_t, 16>();
    r &= expand_and_compress_mask<uint8_t, 16>();
    r &= expand_and_compress_mask<int16_t, 8>();
    r &= expand_and_compress_mask<uint16_t, 8>();
    r &= expand_and_compress_mask<int32_t, 4>();
    r &= expand_and_compress_mask<uint32_t, 4>();
    r &= expand_and_compress_mask<int64_t, 2>();
    r &= expand_and_compress_mask<uint64_t, 2>();
    r &= expand_and_compress_mask<float, 4>();
    r &= expand_and_compress_mask<double, 2>();
#if defined (__AVX__)
    r &= expand_and_compress_mask<float, 8>();
    r &= expand_and_compress_mask<double, 4>();
#endif
#if defined (__AVX2__)
    r &= expand_and_compress_mask<int8_t, 32>();
    r &= expand_and_compress_mask<uint8_t, 32>();
    r &= expand_and_compress_mask<int16_t, 16>();
    r &= expand_and_compress_mask<uint16_t, 16>();
    r &= expand_and_compress_mask<int32_t, 8>();
    r &= expand_and_compress_mask<uint32_t, 8>();
    r &= expand_and_compress_mask<int64_t, 4>();
    r &= expand_and_compress_mask<uint64_t, 4>();
#endif
    return r;
}


bool
cftal::test::of_bit_pack_unpack()
{
#if !defined (__BMI2__)
    std::cout << "test of pdep/pext emulation not possible\n";
    return true;
#else
    static const uint32_t bits[]= {
        0x55555555,
        0xAAAAAAAA,
        0x33333333,
        0xCCCCCCCC,
        0x0F0F0F0F,
        0xF0F0F0F0
    };
    const uint64_t mcnt=0x1'0000'0000U;
    const double f=100.0/double(mcnt);
    std::cout << mcnt << " masks to check\n";
    std::cout << std::fixed << std::setprecision(3);
    for (uint64_t m=0; m<mcnt; ++m) {
        uint32_t mu32=m;
        for (auto b=std::cbegin(bits), e=std::cend(bits); b!= e; ++b) {
            uint32_t v=*b;
            uint32_t ref=_pdep_u32(_pext_u32(v, mu32), mu32);
            uint32_t res=::cftal::impl::bit_unpack(
                ::cftal::impl::bit_pack(v, mu32), mu32);
            if (ref != res) {
                std::cout << std::hex
                          << " value: " << v
                          <<  " mask: "  << mu32
                          << " expected: " << ref
                          << " got: " << res
                          << std::endl;
                return false;
            }
        }
        if ( (m & 0x1FFFFF) == 0x1FFFFF) {
            std::cout << std::setw(8)
                      << double(m)*f << "%\r" << std::flush;
        }
    }
    std::cout << '\n' << __PRETTY_FUNCTION__   << " passed\n";
    return true;
#endif
}

int main()
{
    cftal::test::cpu_times_to_stdout tt;
    bool r=cftal::test::of_emul_vpshufb();
    r &= cftal::test::expand_and_compress_masks();
    r &= cftal::test::of_bit_pack_unpack();
    return r==true;
}

#else
int main()
{
    return 0;
}
#endif
