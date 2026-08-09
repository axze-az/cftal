//
// Copyright (C) 2026-2026 Axel Zeuner
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
#include <vector>
#include <cstdlib>
#include <limits>
#include <cftal/vec.h>
#include <cftal/test/check_rcbrt.h>


namespace cftal { namespace test {

	void rcbrt_f64();
	
    }
}


void cftal::test::
rcbrt_f64()
{
    const double z=-std::numeric_limits<double>::infinity();
    const v1f64 vz(z);
    using test_t = check_rcbrt<double>;

    double r=test_t::s(z);
    v1f64 vr=test_t::v(vz);
    auto mr=test_t::r(z);
    auto mr0=std::get<0>(mr);
    std::cout << std::scientific << std::setprecision(22) << std::showpos;
    std::cout << "glibc: " << r << " " << std::hexfloat <<  r << '\n'
	      << std::scientific 
	      << "cftal: " << vr << " " << std::hexfloat << vr << '\n'
	      << std::scientific 
	      << "mpfr;  " << mr0 << " " << std::hexfloat << mr0 << '\n';
}


int main(int argc, char** argv)
{
    cftal::test::rcbrt_f64();
    return 0;
}

