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
#include <iostream>
#include <iomanip>
#include <cftal/vec.h>

#if !defined (__SSE2__)

int main()
{
    return 0;
}

#else

namespace cftal {

    namespace test {

        bool
        test_sat_add_sub_ui8();

        bool
        test_sat_add_sub_ui16();
    }
}

bool
cftal::test::test_sat_add_sub_ui8()
{
    bool r=true;
    std::cout << "int8_t: checking saturated addition and subtraction" << std::endl;
    for (int i=std::numeric_limits<int8_t>::min();
         i <= std::numeric_limits<int8_t>::max(); ++i) {
        for (int j=std::numeric_limits<int8_t>::min();
             j <= std::numeric_limits<int8_t>::max(); ++j) {
            int8_t i8=i, j8=j;
            int8_t a=sat_add(i8, j8);
            vec<int8_t, 16> vi8=i, vj8=j, va=_mm_adds_epi8(vi8(), vj8());
            // using v_t=vec<int8_t, 1>;
            // v_t vr=sat_add(v_t(i8), v_t(j8));
            int8_t ra=_mm_extract_epi16(va(), 0) & 0xFF;
            if (a != ra) {
                std::cout << "i8 adds: " << i << " " << j << " "
                          << int(ra) << " " << int(a) << std::endl;
                r=false;
            }
            int8_t s=sat_sub(i8, j8);
            vec<int8_t, 16> vs=_mm_subs_epi8(vi8(), vj8());
            int8_t rs=_mm_extract_epi16(vs(), 0) & 0xFF;
            if (s != rs) {
                std::cout << "i8 subs: " << i << " " << j << " "
                          << int(rs) << " " << int(s) << std::endl;
                r=false;
            }
        }
    }
    std::cout << "uint8_t: checking saturated addition and subtraction" << std::endl;
    for (int i=std::numeric_limits<uint8_t>::min();
         i <= std::numeric_limits<uint8_t>::max(); ++i) {
        for (int j=std::numeric_limits<uint8_t>::min();
             j <= std::numeric_limits<uint8_t>::max(); ++j) {
            uint8_t i8=i, j8=j;
            uint8_t a=sat_add(i8, j8);
            vec<uint8_t, 16> vi8=i, vj8=j, va=_mm_adds_epu8(vi8(), vj8());
            uint8_t ra=_mm_extract_epi16(va(), 0) & 0xFF;
            if (a != ra) {
                std::cout << "u8 adds: " << i << " " << j << " "
                          << int(ra) << " " << int(a) << std::endl;
                r=false;
            }
            uint8_t s=sat_sub(i8, j8);
            vec<uint8_t, 16> vs=_mm_subs_epu8(vi8(), vj8());
            uint8_t rs=_mm_extract_epi16(vs(), 0) & 0xFF;
            if (s != rs) {
                std::cout << "u8 subs: " << i << " " << j << " "
                          << int(rs) << " " << int(s) << std::endl;
                r=false;
            }
        }
    }
    return r;
}

bool
cftal::test::test_sat_add_sub_ui16()
{
    bool r=true;
    std::cout << "int16_t: checking saturated addition and subtraction" << std::endl;
    for (int i=std::numeric_limits<int16_t>::min();
         i <= std::numeric_limits<int16_t>::max(); ++i) {
        for (int j=std::numeric_limits<int16_t>::min();
             j <= std::numeric_limits<int16_t>::max(); ++j) {
            int16_t i16=i, j16=j;
            int16_t a=sat_add(i16, j16);
            vec<int16_t, 8> vi16=i, vj16=j, va=_mm_adds_epi16(vi16(), vj16());
            int16_t ra=_mm_extract_epi16(va(), 0);
            if (a != ra) {
                std::cout << "i16 adds: " << i << " " << j << " "
                          << int(ra) << " " << int(a) << std::endl;
                r=false;
            }
            int16_t s=sat_sub(i16, j16);
            vec<int16_t, 8> vs=_mm_subs_epi16(vi16(), vj16());
            int16_t rs=_mm_extract_epi16(vs(), 0);
            if (s != rs) {
                std::cout << "i16 subs: " << i << " " << j << " "
                          << int(rs) << " " << int(s) << std::endl;
                r=false;
            }
        }
    }
    std::cout << "uint16_t: checking saturated addition and subtraction" << std::endl;
    for (int i=std::numeric_limits<uint16_t>::min();
         i <= std::numeric_limits<uint16_t>::max(); ++i) {
        for (int j=std::numeric_limits<uint16_t>::min();
             j <= std::numeric_limits<uint16_t>::max(); ++j) {
            uint16_t i16=i, j16=j;
            uint16_t a=sat_add(i16, j16);
            vec<uint16_t, 8> vi16=i, vj16=j, va=_mm_adds_epu16(vi16(), vj16());
            uint16_t ra=_mm_extract_epi16(va(), 0);
            if (a != ra) {
                std::cout << "u16 adds: " << i << " " << j << " "
                          << int(ra) << " " << int(a) << std::endl;
                r=false;
            }
            uint16_t s=sat_sub(i16, j16);
            vec<uint16_t, 8> vs=_mm_subs_epu16(vi16(), vj16());
            uint16_t rs=_mm_extract_epi16(vs(), 0);
            if (s != rs) {
                std::cout << "u16 subs: " << i << " " << j << " "
                          << int(rs) << " " << int(s) << std::endl;
                r=false;
            }
        }
    }
    return r;
}

int main(int argc, char** argv)
{
    // return cftal::test::test_reduce_exp();
    bool r=cftal::test::test_sat_add_sub_ui8();
    r &= cftal::test::test_sat_add_sub_ui16();
    return r==true ? 0 : 1;
}

#endif
