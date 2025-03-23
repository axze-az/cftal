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

#include <cftal/as.h>
#include <cftal/vsvec.h>
#include <iomanip>
#include <chrono>

namespace cftal {
    namespace test {
        template <typename _T>
        float gflops_st();
    }
}

template <typename _T>
float
cftal::test::gflops_st()
{
    constexpr const size_t COEFF_COUNT=256+1;
    _T coeffs[COEFF_COUNT];
    _T ci=_T(1);
    for (size_t i=0; i<COEFF_COUNT; ++i) {
        coeffs[i]= (i & 1)==1 ? -ci : ci;
        // ci *= 0.75;
    }
    constexpr const size_t elem_count=(8*1024ULL)/sizeof(_T);
    constexpr const size_t _N=8192;
    float gflops=0.0f;
    try {
        for (size_t i=0; i<_N; ++i) {
            vsvec<_T> v_src(_T(0.25), elem_count);
            vsvec<_T> v_src_2=v_src*v_src;
            vsvec<_T> v_src_4=v_src_2*v_src_2;
            vsvec<_T> v_dst(v_src);
            auto start = std::chrono::steady_clock::now();
            // v_dst=math::horner(v_src, coeffs);
            v_dst=math::horner4(v_src, v_src_2, v_src_4, coeffs);
            auto end = std::chrono::steady_clock::now();
            auto ns_elapsed=(end - start).count();
            // std::cout << ns_elapsed << std::endl;
            float gflops_i=(elem_count * (COEFF_COUNT-1)*2)/float(ns_elapsed);
            // std::cout << gflops_i << '\n';
            gflops += gflops_i;
        }
        gflops *= 1.0f/float(_N);
        std::cout << "mean: " << gflops << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << "caught exception: runtime error: " << e.what()
                  << std::endl;
    }
    return gflops;
}

int main()
{
    using namespace cftal::test;
    std::cout << "testing single thread float gflops\n";
    gflops_st<float>();
    std::cout << "testing single thread double gflops\n";
    gflops_st<double>();
    std::cout << "testing single thread f16_t gflops\n";
    gflops_st<cftal::f16_t>();
    std::cout << "testing single thread bf16_t gflops\n";
    gflops_st<cftal::bf16_t>();
    return 0;
}
