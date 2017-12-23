//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <cftal/test/call_mpfr.h>
#include <cftal/cast.h>
#include <iostream>
#include <iomanip>

namespace cftal {
    namespace test {
        void
        gen_2_over_pi_bits(std::ostream& s);
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
    mpr_t f(0x1p24);
    s << std::setprecision(18);

    const int lines=158;
    s << "const cftal::int32_t cftal::math::impl::two_over_pi["
      << lines*6 << "]={\n";
    s << std::hex << std::setfill('0');
    for (int l=0; l<lines; ++l) {
        s << "    ";
        for (int r=0; r<6; ++r) {
            mpr_t t= rem*f;
            mpr_t k;
            mpfr_trunc(k(), t());
            double dk(k);
            uint32_t ik=dk;
            rem = t - k;
            s << "0x" << std::setw(6) << ik;
            if (r<5)
                s << ", ";
        }
        if (l<lines-1)
            s << ',';
        s << '\n';
    }
    s << "};\n\n";
    s << std::dec;
#if 0
    s << "const double cftal::math::impl::two_over_pi_dbl["
      << lines*6 << "]={\n";
    s << std::hex << std::hexfloat << std::setprecision(18);
    rem=two_over_pi;
    for (int l=0; l<lines; ++l) {
        s << "    ";
        for (int r=0; r<6; ++r) {
            mpr_t t= rem*f;
            mpr_t k;
            mpfr_trunc(k(), t());
            double dk(k);
            rem = t - k;
            s << dk;
            if (r<5)
                s << ", ";
            if (r==2)
                s << "\n    ";
        }
        if (l<lines-1)
            s << ',';
        s << '\n';
    }
    s << "};\n";
#endif
    mpr_t tpi=pi/mpr_t(2.0);
    s << std::scientific << std::setprecision(22);
    const int plines=8;
    s << "const double cftal::math::impl::pi_over_2[" << plines << "]={\n";
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
}

int main()
{
    cftal::test::gen_2_over_pi_bits(std::cout);
    return 0;
}
