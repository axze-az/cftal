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
#include <cftal/test/x_real.h>
#include <functional>
#include <iomanip>
#include <random>

int main()
{
    std::cerr << std::setprecision(20);

    using namespace cftal::test;
    std::cerr << "d_real<double>:\n";
    bool rd= cftal::test::check_x_real<cftal::d_real, double,
                                       mpfr_real<128> >::v();
    std::cerr << "d_real<float>:\n";
    bool rf= cftal::test::check_x_real<cftal::d_real, float,
                                       mpfr_real<64> >::v();

    std::cerr << "d_real<f16_t>:\n";
    bool rh= cftal::test::check_x_real<cftal::d_real, cftal::f16_t,
                                       mpfr_real<32> >::v();

    bool r = rd == true && rf == true && rh == true;
    return r == true ? 0 : 1;
}
