//
// Copyright (C) 2010-2022 Axel Zeuner
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
#include <cftal/vec.h>
#include <iomanip>
#include <array>

namespace cftal {

    namespace test {
        bool
        strided_loads();
    }
}

bool cftal::test::strided_loads()
{
#if 0
    using namespace cftal::impl;
    std::cout << load_indices<int32_t, 4, 8>() << '\n'
              << load_indices<int32_t, 4, 4>() << '\n'
              << load_indices<int32_t, 4, 2>() << '\n'
              << load_indices<int32_t, 4>() << '\n'
              << load_indices<int32_t, 4, 0>() << '\n'
              << load_indices<int32_t, 4, -1>() << '\n'
              << load_indices<int32_t, 4, -2>() << '\n'
              << load_indices<int32_t, 4, -4>() << '\n'
              << load_indices<int32_t, 4, -8>() << '\n';

    std::cout << load_indices<int32_t, 8, 8>() << '\n'
              << load_indices<int32_t, 8, 4>() << '\n'
              << load_indices<int32_t, 8, 2>() << '\n'
              << load_indices<int32_t, 8>() << '\n'
              << load_indices<int32_t, 8, 0>() << '\n'
              << load_indices<int32_t, 8, -1>() << '\n'
              << load_indices<int32_t, 8, -2>() << '\n'
              << load_indices<int32_t, 8, -4>() << '\n'
              << load_indices<int32_t, 8, -8>() << '\n';
#endif
    constexpr const int S=32;
    constexpr const int N=8;
    constexpr const int K=S*(N-1)+S+1;
    std::array<float, 2*K+1> vp;
    for (ssize_t i=0; i<ssize_t(vp.size()); ++i) {
        vp[i]=float(i-K);
    }
    const float* p= &vp[K];

    auto cmp=[](const v8f32& res, const v8f32& expected)->bool {
        std::cout << res << '\n';
        return all_of(res == expected);
    };

    bool rc=true;

    std::cout << std::setprecision(2) << std::showpos << std::scientific;
    std::cout << "checking strided loads without offset\n";
    v8f32 r;
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*0.0f;
    if (cmp(load_strided<v8f32, 0>(p), r)==false) {
        std::cout << "load_strided<v8f32, 0> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*1.0f;
    if (cmp(load_strided<v8f32, 1>(p), r)==false) {
        std::cout << "load_strided<v8f32, 1> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*2.0f;
    if (cmp(load_strided<v8f32, 2>(p), r)==false) {
        std::cout << "load_strided<v8f32, 2> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*3.0f;
    if (cmp(load_strided<v8f32, 3>(p), r)==false) {
        std::cout << "load_strided<v8f32, 3> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*4.0f;
    if (cmp(load_strided<v8f32, 4>(p), r)==false) {
        std::cout << "load_strided<v8f32, 4> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*5.0f;
    if (cmp(load_strided<v8f32, 5>(p), r)==false) {
        std::cout << "load_strided<v8f32, 5> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*6.0f;
    if (cmp(load_strided<v8f32, 6>(p), r)==false) {
        std::cout << "load_strided<v8f32, 6> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*7.0f;
    if (cmp(load_strided<v8f32, 7>(p), r)==false) {
        std::cout << "load_strided<v8f32, 7> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*8.0f;
    if (cmp(load_strided<v8f32, 8>(p), r)==false) {
        std::cout << "load_strided<v8f32, 8> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*9.0f;
    if (cmp(load_strided<v8f32, 9>(p), r)==false) {
        std::cout << "load_strided<v8f32, 9> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*10.0f;
    if (cmp(load_strided<v8f32, 10>(p), r)==false) {
        std::cout << "load_strided<v8f32, 10> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*11.0f;
    if (cmp(load_strided<v8f32, 11>(p), r)==false) {
        std::cout << "load_strided<v8f32, 11> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*12.0f;
    if (cmp(load_strided<v8f32, 12>(p), r)==false) {
        std::cout << "load_strided<v8f32, 12> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*13.0f;
    if (cmp(load_strided<v8f32, 13>(p), r)==false) {
        std::cout << "load_strided<v8f32, 13> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*14.0f;
    if (cmp(load_strided<v8f32, 14>(p), r)==false) {
        std::cout << "load_strided<v8f32, 14> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*15.0f;
    if (cmp(load_strided<v8f32, 15>(p), r)==false) {
        std::cout << "load_strided<v8f32, 15> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*16.0f;
    if (cmp(load_strided<v8f32, 16>(p), r)==false) {
        std::cout << "load_strided<v8f32, 16> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*17.0f;
    if (cmp(load_strided<v8f32, 17>(p), r)==false) {
        std::cout << "load_strided<v8f32, 17> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*18.0f;
    if (cmp(load_strided<v8f32, 18>(p), r)==false) {
        std::cout << "load_strided<v8f32, 18> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }

    // strided loads with offset
    std::cout << "checking strided loads with offset\n";

    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*0.0f+1.0f;
    if (cmp(load_strided<v8f32, 0, 1>(p), r)==false) {
        std::cout << "load_strided<v8f32, 0, 1> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*1.0f+2.0f;
    if (cmp(load_strided<v8f32, 1, 2>(p), r)==false) {
        std::cout << "load_strided<v8f32, 1, 2> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*2.0f+3.0f;
    if (cmp(load_strided<v8f32, 2, 3>(p), r)==false) {
        std::cout << "load_strided<v8f32, 2, 3> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*3.0f+4.0f;
    if (cmp(load_strided<v8f32, 3, 4>(p), r)==false) {
        std::cout << "load_strided<v8f32, 3, 4> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*4.0f+5.0f;
    if (cmp(load_strided<v8f32, 4, 5>(p), r)==false) {
        std::cout << "load_strided<v8f32, 4, 5> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*5.0f+6.0f;
    if (cmp(load_strided<v8f32, 5, 6>(p), r)==false) {
        std::cout << "load_strided<v8f32, 5, 6> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*6.0f+7.0f;
    if (cmp(load_strided<v8f32, 6, 7>(p), r)==false) {
        std::cout << "load_strided<v8f32, 6, 7> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*7.0f+8.0f;
    if (cmp(load_strided<v8f32, 7, 8>(p), r)==false) {
        std::cout << "load_strided<v8f32, 7, 8> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*8.0f+9.0f;
    if (cmp(load_strided<v8f32, 8, 9>(p), r)==false) {
        std::cout << "load_strided<v8f32, 8, 9> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*9.0f+10.0f;
    if (cmp(load_strided<v8f32, 9, 10>(p), r)==false) {
        std::cout << "load_strided<v8f32, 9, 10> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*10.0f+11.0f;
    if (cmp(load_strided<v8f32, 10, 11>(p), r)==false) {
        std::cout << "load_strided<v8f32, 10, 11> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*11.0f+12.0f;
    if (cmp(load_strided<v8f32, 11, 12>(p), r)==false) {
        std::cout << "load_strided<v8f32, 11, 12> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*12.0f+13.0f;
    if (cmp(load_strided<v8f32, 12, 13>(p), r)==false) {
        std::cout << "load_strided<v8f32, 12, 13> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*13.0f+14.0f;
    if (cmp(load_strided<v8f32, 13, 14>(p), r)==false) {
        std::cout << "load_strided<v8f32, 13, 14> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*14.0f+15.0f;
    if (cmp(load_strided<v8f32, 14, 15>(p), r)==false) {
        std::cout << "load_strided<v8f32, 14, 15> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*15.0f+16.0f;
    if (cmp(load_strided<v8f32, 15, 16>(p), r)==false) {
        std::cout << "load_strided<v8f32, 15, 16> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*16.0f+17.0f;
    if (cmp(load_strided<v8f32, 16, 17>(p), r)==false) {
        std::cout << "load_strided<v8f32, 16, 17> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*17.0f+18.0f;
    if (cmp(load_strided<v8f32, 17, 18>(p), r)==false) {
        std::cout << "load_strided<v8f32, 17, 18> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }
    r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*18.0f+19.0f;
    if (cmp(load_strided<v8f32, 18, 19>(p), r)==false) {
        std::cout << "load_strided<v8f32, 18, 19> failed, expected result\n"
                  << r << '\n';
        rc=false;
    }

    std::cout << "checking flexible strided loads without offset\n";
    for (int i=-S; i<=S; ++i) {
        r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*float(i);
        if (cmp(load_strided<v8f32>(p, i), r)==false) {
            std::cout << "load_strided<v8f32>(p, " << i
                      << ") failed, expected result\n"
                      << r << '\n';
            rc=false;
        }
    }
    std::cout << "checking flexible strided loads with offset\n";
    for (int i=-S; i<=S; ++i) {
        r=v8f32{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f}*float(i) +
            float(i+1);
        if (cmp(load_strided<v8f32>(p, i, i+1), r)==false) {
            std::cout << "load_strided<v8f32>(p, " << i
                      << ", " << i+1 << ") failed, expected result\n"
                      << r << '\n';
            rc=false;
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
    return cftal::test::strided_loads() ? 0 : 1;
}
