//
// Copyright (C) 2010-2025 Axel Zeuner
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
#include <iterator>
#include <iostream>
#include <iomanip>

int main()
{

    auto make_df32=[](double d) ->std::pair<float, float> {
        float dh=static_cast<float>(d);
        float dl=static_cast<float>(d-static_cast<double>(dh));
        return std::make_pair(dh, dl);
    };
    constexpr
    const double b0_c0=+1.0000000000000000000000e+00;
    constexpr
    const double b0_c2=-6.2500000000000000000000e-02;
    constexpr
    const double b0_c4=+1.0351562500000000000000e-01;
    constexpr
    const double b0_c6=-5.4284667968750000000000e-01;
    constexpr
    const double b0_c8=+5.8486995697021479999160e+00;
    constexpr
    const double b0_c10=-1.0688679397106169999959e+02;
    constexpr
    const double b0_c12=+2.9681429378427570000554e+03;
    constexpr
    const double b0_c14=-1.1653847969683609999691e+05;

    static const double b0c[]={
        b0_c0, b0_c2, b0_c4, b0_c6, b0_c8, b0_c10, b0_c12, b0_c14
    };
    std::cout << "// amplitude j0/y0\n";
    int c=0;
    for (auto b=std::cbegin(b0c), e=std::cend(b0c); b!=e; ++b) {
        float f=static_cast<float>(*b);
        std::cout << "constexpr\nconst float b0_c" << c << "="
                  << std::scientific << std::showpos
                  << std::setprecision(10)
                  << f << "f;\n"
                  << std::noshowpos;
        c += 2;
    }


    constexpr
    const double b1_c0=+1.0000000000000000000000e+00;
    constexpr
    const double b1_c2=+1.8750000000000000000000e-01;
    constexpr
    const double b1_c4=-1.9335937500000000000000e-01;
    constexpr
    const double b1_c6=+8.0529785156250000000000e-01;
    constexpr
    const double b1_c8=-7.7399539947509770000840e+00;
    constexpr
    const double b1_c10=+1.3276182425022130000059e+02;
    constexpr
    const double b1_c12=-3.5433036653660240000718e+03;
    constexpr
    const double b1_c14=+1.3539422856918089999567e+05;
    constexpr const static double b1c[]={
        b1_c0, b1_c2, b1_c4, b1_c6, b1_c8, b1_c10, b1_c12, b1_c14
    };
    std::cout << "// amplitude j1/y1\n";
    c=0;
    for (auto b=std::cbegin(b1c), e=std::cend(b1c); b!=e; ++b) {
        float f=static_cast<float>(*b);
        std::cout << "constexpr\nconst float b1_c" << c << "="
                  << std::scientific << std::showpos
                  << std::setprecision(10)
                  << f << "f;\n"
                  << std::noshowpos;
        c += 2;
    }


    constexpr
    const double a0_c1=-1.2500000000000000000000e-01;
    constexpr
    const double a0_c3_h=+6.5104166666666671292596e-02;
    constexpr
    const double a0_c3_l=-4.6259292689999999998733e-18;
    constexpr
    const double a0_c5_h=-2.0957031249999999444888e-01;
    constexpr
    const double a0_c5_l=-5.5511151230000000001060e-18;
    constexpr
    const double a0_c7_h=+1.6380658830915177937015e+00;
    constexpr
    const double a0_c7_l=+6.3441315693000000002756e-17;
    constexpr
    const double a0_c9_h=-2.3475127749972873658635e+01;
    constexpr
    const double a0_c9_l=+3.9474596431099999998990e-16;
    constexpr
    const double a0_c11_h=+5.3564051951061594536441e+02;
    constexpr
    const double a0_c11_l=+1.0335167065600999999650e-14;
    constexpr
    const double a0_c13_h=-1.7837279688947477552574e+04;
    constexpr
    const double a0_c13_l=+1.6790671417346369999700e-12;
    constexpr
    const double a0_c15_h=+8.1673784219107672106475e+05;
    constexpr
    const double a0_c15_l=-3.8805107275644936000081e-11;

    constexpr const static double a0c[]={
        a0_c1, a0_c3_h, a0_c5_h, a0_c7_h, a0_c9_h, a0_c11_h,
        a0_c13_h, a0_c15_h
    };
    static_cast<void>(a0_c3_l);
    static_cast<void>(a0_c5_l);
    static_cast<void>(a0_c7_l);
    static_cast<void>(a0_c9_l);
    static_cast<void>(a0_c11_l);
    static_cast<void>(a0_c13_l);
    static_cast<void>(a0_c15_h);
    static_cast<void>(a0_c15_l);
    std::cout << "// phase j0/y0\n";
    c=1;
    for (auto b=std::cbegin(a0c), e=std::cend(a0c); b!=e; ++b) {
        auto  lh=make_df32(*b);
        if (lh.second == 0.0f) {
            std::cout << "constexpr\nconst float a0_c" << c << "="
                    << std::scientific << std::showpos
                    << std::setprecision(10)
                    << lh.first << "f;\n"
                    << std::noshowpos;
        } else {
            std::cout << "constexpr\nconst float a0_c" << c << "_h="
                    << std::scientific << std::showpos
                    << std::setprecision(10)
                    << lh.first << "f;\n"
                    << std::noshowpos;
            std::cout << "constexpr\nconst float a0_c" << c << "_l="
                    << std::scientific << std::showpos
                    << std::setprecision(10)
                    << lh.second << "f;\n"
                    << std::noshowpos;

        }
        c += 2;
    }

    constexpr
    const double a1_c1=+3.7500000000000000000000e-01;
    constexpr
    const double a1_c3=-1.6406250000000000000000e-01;
    constexpr
    const double a1_c5_h=+3.7089843750000001110223e-01;
    constexpr
    const double a1_c5_l=-1.1102230246000000000212e-17;
    constexpr
    const double a1_c7_h=-2.3693978445870533811046e+00;
    constexpr
    const double a1_c7_l=-1.9032394707900000000225e-16;
    constexpr
    const double a1_c9=+3.0624011993408203125000e+01;
    constexpr
    const double a1_c11_h=-6.5918522182377898843697e+02;
    constexpr
    const double a1_c11_l=-3.1005501196804000000324e-14;
    constexpr
    const double a1_c13_h=+2.1156314045527808048064e+04;
    constexpr
    const double a1_c13_l=-1.3992226181121969999522e-12;
    constexpr
    const double a1_c15_h=-9.4434660954805475194007e+05;
    constexpr
    const double a1_c15_l=+2.3283064365386964000079e-11;

    constexpr const static double a1c[]={
        a1_c1, a1_c3, a1_c5_h, a1_c7_h, a1_c9, a1_c11_h,
        a1_c13_h, a1_c15_h
    };
    static_cast<void>(a1_c5_l);
    static_cast<void>(a1_c7_l);
    static_cast<void>(a1_c11_l);
    static_cast<void>(a1_c13_l);
    static_cast<void>(a1_c15_h);
    static_cast<void>(a1_c15_l);
    std::cout << "// phase j1/y1\n";
    c=1;
    for (auto b=std::cbegin(a1c), e=std::cend(a1c); b!=e; ++b) {
        auto  lh=make_df32(*b);
        if (lh.second == 0.0f) {
            std::cout << "constexpr\nconst float a1_c" << c << "="
                    << std::scientific << std::showpos
                    << std::setprecision(10)
                    << lh.first << "f;\n"
                    << std::noshowpos;
        } else {
            std::cout << "constexpr\nconst float a1_c" << c << "_h="
                    << std::scientific << std::showpos
                    << std::setprecision(10)
                    << lh.first << "f;\n"
                    << std::noshowpos;
            std::cout << "constexpr\nconst float a1_c" << c << "_l="
                    << std::scientific << std::showpos
                    << std::setprecision(10)
                    << lh.second << "f;\n"
                    << std::noshowpos;

        }
        c += 2;
    }
    return 0;
}
