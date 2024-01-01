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
#include <iostream>
#include <cftal/test/call_mpfr.h>
#include <cftal/as.h>
#include <iomanip>

namespace cftal {
    namespace test {
        void
        gen_2_over_pi_bits(std::ostream& s);

        void
        gen_2_over_pi_tables(std::ostream& s);
    }
}

void
cftal::test::gen_2_over_pi_bits(std::ostream& s)
{
    const std::size_t bits=16384*16;
    using mpr_t =mpfr_real<bits>;
    mpr_t pi;
    mpr_t two(2.0);
    mpfr_const_pi(pi(), MPFR_RNDN);
    mpr_t two_over_pi = two/pi;
    mpr_t rem=two_over_pi;
    mpr_t f24(0x1p24);
    s << std::setprecision(18);

    // for double 11*6*24 bits are enough (396 hex digits)
    // we use 5688 hex digits for future __float128_t
    const int b24_lines=158;
    s << "const cftal::int32_t cftal::math::impl::two_over_pi_b24["
      << b24_lines*6 << "]={\n";
    s << std::hex << std::setfill('0');
    for (int l=0; l<b24_lines; ++l) {
        s << "    ";
        for (int r=0; r<6; ++r) {
            mpr_t t= rem*f24;
            mpr_t k;
            mpfr_trunc(k(), t());
            double dk(k);
            uint32_t ik=dk;
            rem = t - k;
            s << "0x" << std::setw(6) << ik;
            if (r<5)
                s << ", ";
        }
        if (l<b24_lines-1)
            s << ',';
        s << '\n';
    }
    s << "};\n\n";
    s << std::dec;

    mpr_t tpi=pi/mpr_t(2.0);
    s << std::scientific << std::setprecision(22);
    const int plines=8;
    s << "const double cftal::math::impl::pi_over_2_f64["
      << plines << "]={\n";
    s << std::hex;
    for (int l=0; l<plines; ++l) {
        double t(tpi);
        uint64_t ti=as<uint64_t>(t);
        ti &= 0xFFFFFFFFE0000000ULL;
        t = as<double>(ti);
        s << "   " << t;
        if (l < plines-1)
            s << ',';
        else
            s << ' ';
        s << " // 0x" << std::setw(8) << uint32_t(ti>>32)
          << ", 0x" << std::setw(8) << uint32_t(ti);
        s << '\n';
        mpr_t tn(t);
        tpi -= tn;
    }
    s << "};\n";
    s << std::dec;
    // float two_over_pi: 396 hex digits=1584 bits,
    // 9 bits per entry, 8 entries per line, 22 lines
    const int b9_lines=22;
    s << "const cftal::int16_t cftal::math::impl::two_over_pi_b9["
      << b9_lines*8 << "]={\n";
    s << std::hex << std::setfill('0');
    rem=two_over_pi;
    mpr_t f9(0x1p9);
    for (int l=0; l<b9_lines; ++l) {
        s << "    ";
        for (int r=0; r<8; ++r) {
            mpr_t t= rem*f9;
            mpr_t k;
            mpfr_trunc(k(), t());
            float dk(k);
            uint32_t ik=dk;
            rem = t - k;
            s << "0x" << std::setw(3) << ik;
            if (r<7)
                s << ", ";
        }
        if (l<b9_lines-1)
            s << ',';
        s << '\n';
    }
    s << "};\n\n";
    s << std::dec;

    tpi=pi/mpr_t(2.0);
    s << std::scientific << std::setprecision(12);
    s << "const float cftal::math::impl::pi_over_2_f32["
      << plines << "]={\n";
    s << std::hex;
    for (int l=0; l<plines; ++l) {
        float t(tpi);
        uint32_t ti=as<uint32_t>(t);
        ti &= 0xFFFFC000;
        t = as<float>(ti);
        s << "   " << t << 'f';
        if (l < plines-1)
            s << ',';
        else
            s << ' ';
        s << " // 0x" << std::setw(8) << uint32_t(ti);
        s << '\n';
        mpr_t tn(t);
        tpi -= tn;
    }
    s << "};\n";
    s << std::dec;
}

void
cftal::test::gen_2_over_pi_tables(std::ostream& s)
{
    const std::size_t bits=16384*16;
    using mpr_t =mpfr_real<bits>;
    mpr_t pi;
    mpr_t two(2.0);
    mpfr_const_pi(pi(), MPFR_RNDN);
    mpr_t two_over_pi = two/pi;
    const int max_exp=1024;
    const int elems_per_exp=3;
    s << "const double\n"
      << "cftal::math::payne_hanek_pi_over_2_base::rempi_table_dbl["
      << max_exp*4 << "]={\n";
    s << std::scientific << std::setprecision(22);
    for (int i=0; i < max_exp; ++i) {
        if (i) {
            s << ",\n";
        }
        mpr_t pa;
        mpr_t two_pow_i;
        mpr_t two_pow_minus_i;
        int r=i>512+128 ? i-128 : i;
        s  << "    " "// " << i <<  " scaled by "
           << "2^" << (r==i ? 0: 128) << '\n';
        mpfr_set_ui_2exp(two_pow_i(), 1, i, MPFR_RNDN);
        mpfr_set_ui_2exp(two_pow_minus_i(), 1, -r, MPFR_RNDN);
        pa = (two_pow_i/two_over_pi);
        mpfr_frac(pa(), pa(), MPFR_RNDN);
        pa *=two_pow_minus_i;
        for (int j=0; j < elems_per_exp; ++j) {
            double di=mpfr_get_d(pa(), MPFR_RNDN);
            s << "    " << di;
            mpr_t r(di);
            pa -= r;
            if (j< elems_per_exp-1)
                s << ",\n";
        }
    }
    s << "\n};\n";
}

int main()
{
    cftal::test::gen_2_over_pi_bits(std::cout);
    cftal::test::gen_2_over_pi_tables(std::cout);
    return 0;
}
