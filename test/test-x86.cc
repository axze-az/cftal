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
#if defined (__SSE2__)
#include <iostream>
#include <cftal/test/f32_f64.h>
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


    template <typename _T, size_t _N>
    bool
    expand_and_compress_mask();

    bool
    expand_and_compress_masks();

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
    return true;
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

int main()
{
    bool r=cftal::test::of_emul_vpshufb();
    r &= cftal::test::expand_and_compress_masks();
    return r==true;
}

#else
int main()
{
    return 0;
}
#endif
