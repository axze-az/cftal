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
#include <cftal/config.h>
#include <cftal/test/call_mpfr.h>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

namespace cftal {

    namespace utils {

        // generate a table for f with f16 numbers between
        // l and high
        void
        gen_f16_tbl(test::call_mpfr::f1_t f,
                    const std::string& tblname,
                    uint32_t b, uint32_t e);

        // generate a table for f with all f16 numbers
        void
        gen_f16_tbl_full(test::call_mpfr::f1_t f,
                         const std::string& tblname);

        // generate a table for f with all positive f16 numbers
        void
        gen_f16_tbl_pos(test::call_mpfr::f1_t f,
                        const std::string& tblname);

        void
        gen_f16_tbls();

    }
}

void
cftal::utils::
gen_f16_tbl(test::call_mpfr::f1_t f,
            const std::string& tblname,
            uint32_t b, uint32_t e)
{
    uint32_t size=e-b;

    std::string fname=tblname + ".cc";
    std::ofstream s(fname.c_str(), std::ios::out|std::ios::trunc);

    s << "const cftal::uint16_t " << tblname
              << '[' << size << "] = {\n";
    char fc=s.fill();
    s << std::scientific << std::setprecision(8)
      << std::hex;
    for (; b!=e; ++b) {
        uint16_t bs=b;
        f16_t x=as<f16_t>(bs);
        f16_t v=test::call_mpfr::func(x, f);
        if (isnan(x) && isnan(v)) {
            f16_t n=copysign(std::numeric_limits<f16_t>::quiet_NaN(),
                             x);
            v=n;
        }
        uint16_t vt=as<uint16_t>(v);
        s << "    // 0x" << std::setw(4) << std::setfill('0') << bs
          << " " << x << " " << v << '\n'
          << "    0x" << std::setw(4) << std::setfill('0')
          << vt << std::setfill(fc);
        if (b+1<e)
            s << ',';
        s << '\n';
    }
    s << "};\n\n" << std::dec;
}

void
cftal::utils::
gen_f16_tbl_full(test::call_mpfr::f1_t f,
                 const std::string& tblname)
{
    gen_f16_tbl(f, tblname, 0x0000, 0x10000);
}

void
cftal::utils::
gen_f16_tbl_pos(test::call_mpfr::f1_t f,
                const std::string& tblname)
{
    gen_f16_tbl(f, tblname, 0x0000, 0x8000);
}

void
cftal::utils::
gen_f16_tbls()
{
    gen_f16_tbl_pos(mpfr_sqrt, "f16_sqrt");
    gen_f16_tbl_pos(mpfr_cbrt, "f16_cbrt");

    gen_f16_tbl_pos(mpfr_sin, "f16_sin");
    gen_f16_tbl_pos(mpfr_cos, "f16_cos");
    gen_f16_tbl_pos(mpfr_tan, "f16_tan");


    gen_f16_tbl_pos(mpfr_j0, "f16_j0");
    gen_f16_tbl_pos(mpfr_j1, "f16_j1");
    gen_f16_tbl_pos(mpfr_y0, "f16_y0");
    gen_f16_tbl_pos(mpfr_y1, "f16_y1");

    gen_f16_tbl_full(mpfr_gamma, "f16_tgamma");

}

int main()
{
    cftal::utils::gen_f16_tbls();
}
