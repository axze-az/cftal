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

namespace cftal {
    namespace test {

        template <typename _T>
        _T
        ref_dot_product(size_t n,
                        const _T* a, int32_t stride_a, size_t offset_a,
                        const _T* b, int32_t stride_b, size_t offset_b);

        template <typename _T>
        _T
        ref_dot_product(size_t n,
                        const _T* a, int32_t stride_a, size_t offset_a,
                        const _T* b);

        template <typename _T>
        _T
        ref_dot_product(size_t n,
                        const _T* a,
                        const _T* b);


        template <typename _T>
        bool
        test_dot_product();

    }
}

template <typename _T>
_T
cftal::test::
ref_dot_product(size_t n,
                const _T* a, int32_t stride_a, size_t offset_a,
                const _T* b, int32_t stride_b, size_t offset_b)
{
    _T r=_T(0);
    for (size_t i=0; i<n; ++i) {
        r += a[stride_a*i + offset_a] * b[stride_b*i + offset_b];
    }
    return r;
}

template <typename _T>
_T
cftal::test::
ref_dot_product(size_t n,
                const _T* a, int32_t stride_a, size_t offset_a,
                const _T* b)
{
    _T r=_T(0);
    for (size_t i=0; i<n; ++i) {
        r += a[stride_a*i + offset_a] * b[i];
    }
    return r;
}

template <typename _T>
_T
cftal::test::
ref_dot_product(size_t n,
                const _T* a,
                const _T* b)
{
    _T r=_T(0);
    for (size_t i=0; i<n; ++i) {
        r += a[i] * b[i];
    }
    return r;
}


template<typename _T>
bool cftal::test::
test_dot_product()
{
    constexpr const size_t _N = 511;


    vsvec<_T> a0(_T(0), _N), b0(_T(0), _N);
    for (size_t i=0; i<a0.size(); ++i) {
        a0[i] = _T(i%10+1);
        b0[i] = _T(i%10+1);
    }
    _T d0=dot_product(a0, b0);
    _T dr0=ref_dot_product(a0.size(), a0.cbegin(), b0.cbegin());
    if (d0 != dr0) {
        std::cout << "dot_product(vsvec, vsvec) failed\n";
        std::cout << std::setprecision(18) << std::fixed;
        std::cout << "result= "  << d0
                  << "\nexpected= " << dr0
                  << "\ndiff=" << d0 - dr0
                  << std::endl;
        return false;
    }

    vsvec<_T> a1(_T(0), _N*8);
    for (size_t i=0; i<a1.size(); ++i) {
        a1[i]= _T(i%10+1);
    }
    for (size_t o=0; o<8; ++o) {
        _T d1=dot_product(a1, 8, o, b0);
        _T dr1=ref_dot_product(b0.size(),
                               a1.cbegin(), 8, o,
                               b0.cbegin());

        if (d1 != dr1) {
            std::cout << "dot_product(vsvec, stride, offset, vsvec) failed\n";
            std::cout << std::setprecision(18) << std::scientific;
            std::cout << "result= "  << d1
                        << "\nexpected= " << dr1
                        << "\ndiff=" << d1 - dr1
                        << "\noffset=" << o
                        << std::endl;
            return false;
        }
    }
    vsvec<_T> b2(_T(0), _N*16);
    for (size_t i=0; i<b2.size(); ++i) {
        b2[i]= _T(i%10+1);
    }
    for (size_t oa=0; oa<8; ++oa) {
        for (size_t ob=0; ob <16; ++ob) {
            _T d2=dot_product(a1, 8, oa, b2, 16, ob);
            _T dr2=ref_dot_product(_N,
                                   a1.cbegin(), 8, oa,
                                   b2.cbegin(), 16, ob);

            if (d2 != dr2) {
                std::cout << "dot_product(vsvec, stride, offset, vsvec, stride, offset) failed\n";
                std::cout << std::setprecision(18) << std::scientific;
                std::cout << "result= "  << d2
                          << "\nexpected= " << dr2
                          << "\ndiff=" << d2 - dr2
                          << std::endl;
                return false;
            }
        }
    }
    return true;
}


int main()
{
    using namespace cftal::test;
    bool r=true;
    if (test_dot_product<float>()==true) {
        std::cout << "dot_product for float vectors passed\n";
    } else {
        r=false;
    }
    if (test_dot_product<double>()==true) {
        std::cout << "dot_product for double vectors passed\n";
    } else {
        r=false;
    }
    return r;
}
