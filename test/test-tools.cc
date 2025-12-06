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
#include <iostream>
#include <iomanip>
#include <cftal/test/f32_f64.h>
#include <cftal/test/cpu_times.h>

namespace cftal{
    namespace test {

	bool
	test_ulp_stats();

	bool
	test_distance();
    }
}

bool
cftal::test::test_ulp_stats()
{
    bool rc=true;
    ulp_stats st;
    for (uint64_t i=0; i<0x7fff'ffffULL; ++i) {
	if ((i & 0xFFFFFFFULL)==0xFFFFFFFULL) {
	    std::cout << i << '\r' << std::flush;
	}
	int32_t ii=i;
	st.inc(ii, false, false, false);
    }
    std::cout << std::endl;
#if 0
    uint64_t s=0;
    for (size_t i=0; i<ulp_stats::deviations::_size; ++i) {
	std::cout << std::setw(2) << i << ' '
		  << std::setw(20) << st._devs._v[i].first
		  << ' '  << st._devs._v[i].second << '\n';
	s+= st._devs._v[i].second;
    }
    if (s != 0x100000000ULL) {
	std::cerr << __PRETTY_FUNCTION__ << " failed\n";
	rc=false;
    }
#endif
    std::cout << st << std::endl;
    return rc;
}

bool
cftal::test::test_distance()
{
    std::cout << "float: zero distances\n";
    std::cout << distance(+0.0f, +0.0f) << std::endl;
    std::cout << distance(+0.0f, -0.0f) << std::endl;
    std::cout << distance(-0.0f, +0.0f) << std::endl;
    std::cout << distance(-0.0f, -0.0f) << std::endl;

    std::cout << "double: zero distances\n";
    std::cout << distance(+0.0, +0.0) << std::endl;
    std::cout << distance(+0.0, -0.0) << std::endl;
    std::cout << distance(-0.0, +0.0) << std::endl;
    std::cout << distance(-0.0, -0.0) << std::endl;

    std::cout << "float: inf distances\n";
    const float pinf32= std::numeric_limits<float>::infinity();
    const float ninf32= -std::numeric_limits<float>::infinity();
    std::cout << distance(pinf32, pinf32) << std::endl;
    std::cout << distance(pinf32, ninf32) << std::endl;
    std::cout << distance(ninf32, pinf32) << std::endl;
    std::cout << distance(ninf32, ninf32) << std::endl;

    std::cout << "double: inf distances\n";
    const double pinf64= std::numeric_limits<double>::infinity();
    const double ninf64= -std::numeric_limits<double>::infinity();
    std::cout << distance(pinf64, pinf64) << std::endl;
    std::cout << distance(pinf64, ninf64) << std::endl;
    std::cout << distance(ninf64, pinf64) << std::endl;
    std::cout << distance(ninf64, ninf64) << std::endl;

    std::cout << "float: std distances\n";
    float one_f=1.0f;
    float next_up_f=one_f;
    float next_down_f=one_f;
    for (int i=0; i<10; ++i) {
        std::cout << distance(one_f, next_up_f) << std::endl;
        std::cout << distance(one_f, next_down_f) << std::endl;
        next_up_f= std::nextafter(next_up_f, 2.0f);
        next_down_f= std::nextafter(next_down_f, 0.0f);
    }
    std::cout << "float: std distances around 0\n";
    float min_f=std::numeric_limits<float>::denorm_min();
    std::cout << distance(min_f, 0.0f) << std::endl;
    std::cout << distance(min_f, -0.0f) << std::endl;
    std::cout << distance(-min_f, 0.0f) << std::endl;
    std::cout << distance(-min_f, -0.0f) << std::endl;
    for (int i=0; i<10; ++i) {
        std::cout << distance(min_f, -min_f) << std::endl;
        std::cout << distance(-min_f, min_f) << std::endl;
        min_f*= 2.0f;
    }

    std::cout << "double: std distances\n";
    double one_d=1.0;
    double next_up_d=one_d;
    double next_down_d=one_d;
    for (int i=0; i<10; ++i) {
        std::cout << distance(one_d, next_up_d) << std::endl;
        std::cout << distance(one_d, next_down_d) << std::endl;
        next_up_d= std::nextafter(next_up_d, 2.0);
        next_down_d= std::nextafter(next_down_d, 0.0);
    }
    std::cout << "double: std distances around 0\n";
    double min_d=std::numeric_limits<double>::denorm_min();
    std::cout << distance(min_d, 0.0) << std::endl;
    std::cout << distance(min_d, -0.0) << std::endl;
    std::cout << distance(-min_d, 0.0) << std::endl;
    std::cout << distance(-min_d, -0.0) << std::endl;
    for (int i=0; i<10; ++i) {
        std::cout << distance(min_d, -min_d) << std::endl;
        std::cout << distance(-min_d, min_d) << std::endl;
        min_d*= 2.0;
    }
    return true;
}

int main(int argc, char** argv)
{
    cftal::test::cpu_times_to_stdout tt;
    bool rc=true;
    rc &= cftal::test::test_distance();
    rc &= cftal::test::test_ulp_stats();
    return rc==true ? 0 : 1;
}
