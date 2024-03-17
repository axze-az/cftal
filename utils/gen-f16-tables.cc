//
// Copyright (C) 2010-2024 Axel Zeuner
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
#include <cftal/math/func_constants_f16.h>
#include <cftal/test/call_mpfr.h>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>

namespace cftal {

    namespace utils {

        extern const
        std::string copyright;

        extern const
        std::string header_name;

        extern const
        std::string header_guard;

        void
        prepare_header(std::ostream& h);

        void
        finalize_header(std::ostream& h);

        int16_t
        table_offset(f16_t v);

        // generate a table for f with f16 numbers between
        // [b, e) if e != inf and [b, e] if e == inf
        std::map<int16_t, std::pair<f16_t, uint16_t>>
        gen_f16_tbl(test::call_mpfr::f1_t f,
                    f16_t b, f16_t e);

        void
        gen_f16_tbl(test::call_mpfr::f1_t f,
                    const std::string& tblname, std::ostream& h,
                    f16_t b, f16_t e);

        // generate a table for f with f16 numbers between
        // l and high
        void
        gen_f16_tbl(test::call_mpfr::f1_t f,
                    const std::string& tblname, std::ostream& h,
                    uint32_t b, uint32_t e);

        // generate a table for f with all f16 numbers
        void
        gen_f16_tbl_full(test::call_mpfr::f1_t f,
                         const std::string& tblname, std::ostream& h);

        // generate a table for f with all positive f16 numbers
        void
        gen_f16_tbl_pos(test::call_mpfr::f1_t f,
                        const std::string& tblname, std::ostream& h);

        void
        gen_f16_tbls();

    }
}

const std::string
cftal::utils::copyright=
"//\n"
"// Copyright (C) 2010-2024 Axel Zeuner\n"
"//\n"
"// This library is free software; you can redistribute it and/or\n"
"// modify it under the terms of the GNU Lesser General Public\n"
"// License as published by the Free Software Foundation; either\n"
"// version 2.1 of the License, or (at your option) any later version.\n"
"//\n"
"// This library is distributed in the hope that it will be useful,\n"
"// but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU\n"
"// Lesser General Public License for more details.\n"
"//\n"
"// You should have received a copy of the GNU Lesser General Public\n"
"// License along with this library; if not, write to the Free Software\n"
"// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA\n"
"//\n";

const std::string
cftal::utils::header_name="f16_tables.h";

const std::string
cftal::utils::header_guard="__CFTAL_MATH_F16_TABLES_H__";

void
cftal::utils::
prepare_header(std::ostream& h)
{
    h << copyright
      << "#if !defined (" << header_guard << ")\n"
      << "#define " << header_guard << " 1\n\n"
      << "#include <cftal/config.h>\n"
      << "#include <cftal/types.h>\n"
      << "#include <cftal/f16_t.h>\n\n"
      << "namespace cftal {\n"
      << "    namespace math {\n\n";
}

void
cftal::utils::
finalize_header(std::ostream& h)
{
    h << "    }\n"
      << "}\n\n"
      << "#endif // " << header_guard << "\n";
}

cftal::int16_t
cftal::utils::table_offset(f16_t f)
{
    int16_t i=as<int16_t>(f);
    constexpr const int16_t offs=int16_t(0x7fff);
    int16_t r=i<0 ? i^offs : i;
    return r;
}

std::map<int16_t, std::pair<cftal::f16_t, uint16_t>>
cftal::utils::
gen_f16_tbl(test::call_mpfr::f1_t f,
            f16_t b, f16_t e)
{
    auto cmp_lt= [](f16_t a, f16_t b)->bool {
        return a < b;
    };
    auto cmp_le=[](f16_t a, f16_t b)->bool {
        return a <= b;
    };
    using std::isinf;
    auto cmp = isinf(e) ? cmp_le : cmp_lt;
    std::map<int16_t, std::pair<f16_t, uint16_t>> r;

    f16_t cur=b;
    while (cmp(cur, e)) {
        int16_t idx=table_offset(cur);
        f16_t fcur=test::call_mpfr::func(cur, f);
        uint16_t fcuri=as<uint16_t>(fcur);
        auto ri=std::make_pair(idx, std::make_pair(cur, fcuri));
        r.insert(ri);
        // leave loop if e == +inf
        if (cur == e)
            break;
        using std::nextafter;
        // nextafter(-0.0, infinity) is not +0.0, but min subnormal instead
        if (cur == -0.0_f16 && idx==-1) {
            cur = 0.0_f16;
        } else {
            cur = nextafter(cur, e);
        }
    }
    return r;
}

void
cftal::utils::
gen_f16_tbl(test::call_mpfr::f1_t f,
            const std::string& tblname, std::ostream& h,
            f16_t b, f16_t e)
{
    auto m=gen_f16_tbl(f, b, e);
    size_t size = std::size(m);

    std::string class_name=tblname + "_data";
    std::string fname=class_name + ".cc";
    std::ofstream s(fname.c_str(), std::ios::out|std::ios::trunc);

    s << copyright
      << "#include \"cftal/math/" << header_name << "\"\n\n"
      << "alignas(64) const cftal::uint16_t\n"
      << "cftal::math::" << class_name << "::_tbl"
      << '[' << size << "+2] = {\n";
    char fc=s.fill();
    s << std::scientific << std::setprecision(8);
    uint32_t zero_offset=0;
    auto mb0=std::cbegin(m);
    int16_t last_idx=0;
    for (auto mb=mb0, me=std::cend(m); mb!=me; ++mb) {
	const int16_t idx=mb->first;
	const auto& sr=mb->second;
	f16_t x=sr.first;
	uint16_t v=sr.second;
	int16_t xi=as<int16_t>(x);
	if (xi == 0) {
	    zero_offset=-std::cbegin(m)->first;
	}
	if (mb0 != mb) {
            if (idx != last_idx+1) {
                std::cerr << "idx " << idx << " last idx " << last_idx << '\n';
                // throw std::runtime_error(tblname+" generation failed, oops");
            }
        }
        last_idx=idx;
        s << "    // " << std::setw(6) << idx
          << " " << x << " " << std::hex
	  << " 0x" << std::setw(4) << std::setfill('0') << xi
	  << std::setfill(fc) << " " << as<f16_t>(v) << '\n'
          << "    0x" << std::setw(4) << std::setfill('0')
          << v << std::setfill(fc) << std::dec;
        if (std::next(mb) != me)
            s << ',';
        s << '\n';
    }
    s << "};\n\n" << std::dec;

    auto mi=std::cbegin(m);
    int32_t min_offset= int32_t(mi->first);
    int32_t max_offset= size + mi->first;

    h << "        struct " << class_name << " {\n"
      << "            static constexpr const uint32_t zero_offset="
      << zero_offset << ";\n"
      << "            static constexpr const int16_t min_offset="
      << min_offset << ";\n"
      << "            static constexpr const int32_t max_offset="
      << max_offset << ";\n"
      << "            alignas(64) static const uint16_t _tbl["
      <<  size << "+2];\n\n"
      << "            static const f16_t* tbl() {\n"
      << "                return reinterpret_cast<const f16_t*>(_tbl);\n"
      << "            }\n\n"
      << "            static const f16_t* tbl_zero() {\n"
      << "                return tbl() + zero_offset;\n"
      << "            }\n"
      << "        };\n\n";
}


void
cftal::utils::
gen_f16_tbl(test::call_mpfr::f1_t f,
            const std::string& tblname, std::ostream& h,
            uint32_t b, uint32_t e)
{
    uint32_t size=e-b;

    std::string class_name=tblname + "_data";
    std::string fname=class_name + ".cc";
    std::ofstream s(fname.c_str(), std::ios::out|std::ios::trunc);

    s << copyright
      << "#include \"cftal/math/" << header_name << "\"\n\n"
      << "alignas(64) const cftal::uint16_t\n"
      << "cftal::math::" << class_name << "::_tbl"
      << '[' << size << "+2] = {\n";
    char fc=s.fill();
    s << std::scientific << std::setprecision(8)
      << std::hex;
    uint32_t zero_offset=0;
    for (uint32_t o=0; b!=e; ++b, ++o) {
        int16_t bs=b;
        if (bs==0)
            zero_offset=o;
        f16_t x=as<f16_t>(bs);
        f16_t v=test::call_mpfr::func(x, f);
        if (isnan(x) && isnan(v)) {
            f16_t n=copysign(std::numeric_limits<f16_t>::quiet_NaN(),
                             x);
            v=n;
        }
        uint16_t vt=as<uint16_t>(v);
        s << "    // " << std::setw(6) << std::dec << bs << std::hex
          << " " << x << " " << v
          << " offs: 0x" << std::setw(4) << std::setfill('0')
          << o << std::setfill(fc) << '\n'
          << "    0x" << std::setw(4) << std::setfill('0')
          << vt << std::setfill(fc);
        if (b+1!=e)
            s << ',';
        s << '\n';
    }
    int32_t min_offset= -(zero_offset);
    int32_t max_offset=  (size-zero_offset);
    s << "};\n\n" << std::dec;

    h << "        struct " << class_name << " {\n"
      << "            static constexpr const uint32_t zero_offset="
      << zero_offset << ";\n"
      << "            static constexpr const int16_t min_offset="
      << min_offset << ";\n"
      << "            static constexpr const int32_t max_offset="
      << max_offset << ";\n"
      << "            alignas(64) static const uint16_t _tbl["
      <<  size << "+2];\n\n"
      << "            static const f16_t* tbl() {\n"
      << "                return reinterpret_cast<const f16_t*>(_tbl);\n"
      << "            }\n\n"
      << "            static const f16_t* tbl_zero() {\n"
      << "                return tbl() + zero_offset;\n"
      << "            }\n"
      << "        };\n\n";
}

void
cftal::utils::
gen_f16_tbl_full(test::call_mpfr::f1_t f,
                 const std::string& tblname, std::ostream& h)
{
    gen_f16_tbl(f, tblname, h, -32768, 0x8000);
}

void
cftal::utils::
gen_f16_tbl_pos(test::call_mpfr::f1_t f,
                const std::string& tblname, std::ostream& h)
{
    gen_f16_tbl(f, tblname, h, 0x0000, 0x8000);
}

void
cftal::utils::
gen_f16_tbls()
{
    std::ofstream h(header_name.c_str(), std::ios::out|std::ios::trunc);

    prepare_header(h);

    gen_f16_tbl(mpfr_sqrt, "f16_sqrt", h,
                0.0_f16,
                std::numeric_limits<f16_t>::infinity());

    gen_f16_tbl(mpfr_rec_sqrt, "f16_rsqrt", h,
                0.0_f16,
                std::numeric_limits<f16_t>::infinity());

    gen_f16_tbl(mpfr_j0, "f16_j0", h,
                0.0_f16,
                std::numeric_limits<f16_t>::infinity());

    gen_f16_tbl(mpfr_j1, "f16_j1", h,
                0.0_f16,
                std::numeric_limits<f16_t>::infinity());

    gen_f16_tbl(mpfr_y0, "f16_y0", h,
                0.0_f16,
                std::numeric_limits<f16_t>::infinity());

    gen_f16_tbl(mpfr_y1, "f16_y1", h,
                0.0_f16,
                std::numeric_limits<f16_t>::infinity());

    using std::nextafter;
    const f16_t tgamma_hi_inf=nextafter(
        math::func_constants<f16_t>::tgamma_hi_inf(),
        std::numeric_limits<f16_t>::infinity());
    gen_f16_tbl(mpfr_gamma, "f16_tgamma", h,
                -1025.0_f16,
                tgamma_hi_inf);

    const f16_t erfc_zero0=nextafter(
        math::func_constants<f16_t>::erfc_gt_zero_fin(),
        std::numeric_limits<f16_t>::infinity());
    const f16_t erfc_zero=nextafter(erfc_zero0,
        std::numeric_limits<f16_t>::infinity());
    gen_f16_tbl(mpfr_erfc, "f16_erfc", h,
                -erfc_zero, erfc_zero);

    const f16_t erf_one0=nextafter(
        math::func_constants<f16_t>::erf_lt_one_fin(),
        std::numeric_limits<f16_t>::infinity());
    const f16_t erf_one=nextafter(erf_one0,
        std::numeric_limits<f16_t>::infinity());
    gen_f16_tbl(mpfr_erf, "f16_erf", h,
                0.0_f16, erf_one);

    finalize_header(h);
}

int main()
{
#if 1
    cftal::utils::gen_f16_tbls();
#else
    using namespace cftal;

    const int16_t offs=int16_t(0x7fff);
    std::cout << int16_t(0x8000) << ' ' << int16_t(offs-int16_t(0x8000)) << std::endl;
    std::cout << int16_t(0x8001) << ' ' << int16_t(offs-int16_t(0x8001)) << std::endl;
    std::cout << int16_t(0x8002) << ' ' << int16_t(offs-int16_t(0x8002)) << std::endl;
    std::cout << int16_t(0xfffd) << ' ' << int16_t(offs-int16_t(0xfffd)) << std::endl;
    std::cout << int16_t(0xfffe) << ' ' << int16_t(offs-int16_t(0xfffe)) << std::endl;
    std::cout << int16_t(0xffff) << ' ' << int16_t(offs-int16_t(0xffff)) << std::endl;

    std::cout << int16_t(0x8000) << ' ' << int16_t(offs^int16_t(0x8000)) << std::endl;
    std::cout << int16_t(0x8001) << ' ' << int16_t(offs^int16_t(0x8001)) << std::endl;
    std::cout << int16_t(0x8002) << ' ' << int16_t(offs^int16_t(0x8002)) << std::endl;
    std::cout << int16_t(0xfffd) << ' ' << int16_t(offs^int16_t(0xfffd)) << std::endl;
    std::cout << int16_t(0xfffe) << ' ' << int16_t(offs^int16_t(0xfffe)) << std::endl;
    std::cout << int16_t(0xffff) << ' ' << int16_t(offs^int16_t(0xffff)) << std::endl;
#endif
}
