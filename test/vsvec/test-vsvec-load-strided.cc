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
#include <cftal/vsvec.h>
#include <cftal/test/cpu_times.h>
#include <iostream>
#include <iomanip>
#include <array>

namespace cftal {
    namespace test {
        bool vsvec_strided_loads();
    }
}

bool cftal::test::vsvec_strided_loads()
{

    constexpr const int S=128;
    constexpr const int N=31;
    constexpr const int K=S*(N-1)+S+1;
    std::array<float, 2*K+1> vp;
    for (ssize_t i=0; i<ssize_t(vp.size()); ++i) {
        vp[i]=float(i-K);
    }
    const float* p= &vp[K];

    auto cmp=[](const vxf32& res, const vxf32& expected)->bool {
        // std::cout << res << '\n';
        return all_of(res == expected);
    };

    bool rc=true;
    std::cout << std::setprecision(3) << std::showpos << std::scientific;
    std::cout << "checking flexible strided loads with offsets ["
	      << -S << ", " << S << "]\n";
    vxf32 r;
    const vxf32 r0{
        0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
        8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f,
        16.0f, 17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f, 23.0f,
        24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f
    };
    for (int i=-S; i<=S; ++i) {
        r=r0*float(i) + float(i+1);
        if (cmp(load_strided<vxf32>(size(r), p, i, i+1), r)==false) {
            std::cout << "load_strided<vxf32>(" << size(r)
                      << ", p, " << i
                      << ", " << i+1 << ") failed, expected result\n"
                      << r << '\n';
            rc=false;
            break;
        }
    }

    std::cout << "strided load test";
    if (rc==true) {
        std::cout << " passed";
    } else {
        std::cout << " FAILED";
    }
    std::cout << std::endl;
    return rc;
}

int main()
{
    using namespace cftal;
    using namespace cftal::test;
    cpu_times_to_stdout tt;
    bool r=vsvec_strided_loads();
    return r==true ? 0 : 1;
}
