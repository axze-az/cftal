//
// Copyright (C) 2010-2023 Axel Zeuner
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
#include <cftal/test/f32_f64.h>
#include <cftal/test/uniform_distribution.h>
#include <cftal/test/of_math_funcs.h>
#include <cftal/math/func_constants.h>
#include <cftal/vec_f16.h>
#include <cmath>
#include <random>
#include <iostream>
#include <iomanip>
#include <limits>

namespace cftal {
    namespace test {

        template <typename _T, typename _I, std::size_t _N>
        class check_ldexp {

            static
            bool v(_T a, _I e);

        public:
            static
            bool v();
        };

        template <class _T, typename _I, std::size_t _N>
        struct check_ldexp_up_to {
            static bool v() {
                bool r=check_ldexp<_T, _I, _N>::v();
                r &= check_ldexp_up_to<_T, _I, _N/2>::v();
                return r;
            }
        };

        template <class _T, typename _I>
        struct check_ldexp_up_to<_T, _I, 1> {
            static bool v() {
                return check_ldexp<_T, _I, 1>::v();
            }
        };
    }
}

template <typename _T, typename _I, std::size_t _N>
bool
cftal::test::check_ldexp<_T, _I, _N>::v(_T a, _I e)
{
    vec<_T, _N> va=a;
    using std::ldexp;
    _T r= ldexp(a, e);
    vec<_I, _N> ve=e;
    vec<_T, _N> vr= ldexp(va, ve);
    bool rc=check(vr, r, "ldexp");
    if (rc==false) {
        std::cerr << "ldexp("
                  << std::setprecision(22) << std::hexfloat
                  << a << ", " << e << ") failed\n"
                  << extract<0>(vr)
                  << " expected "
                  << r
                  << '\n'
                  << std::scientific;
    }
    return rc;
}

template <typename _T, typename _I, std::size_t _N>
bool
cftal::test::check_ldexp<_T, _I, _N>::v()
{
    std::mt19937 rnd;
    uniform_real_distribution<_T>
        distrib(0, std::numeric_limits<_T>::max());

    const _I min_exp = 3*std::numeric_limits<_T>::min_exponent;
    const _I max_exp = 3*std::numeric_limits<_T>::max_exponent;

    bool rc=true;

    const _T inf_nan_args []= {
        _T(0.0),
        _T(-0.0),
        _T(1),
        _T(2),
        _T(7),
        _T(8),
        _T(uint64_t(1ULL<<23)),
        _T(uint64_t(1ULL<<52)),
        std::numeric_limits<_T>::infinity(),
        std::numeric_limits<_T>::quiet_NaN(),
    };

    for (auto b=std::begin(inf_nan_args), e=std::end(inf_nan_args);
         b!=e; ++b) {
        const auto& ah= *b;
        for (_I i= min_exp; i < max_exp; ++i) {
            rc &= v(ah, i);
            rc &= v(-ah, i);
        }
    }
    const int64_t N0=0x100ULL;
    const int64_t N=72*N0;
    for (int64_t i=0; i<N; ++i) {
        if ((i & (N0-1)) == (N0-1))
            std::cout << '.' << std::flush;
        _T ah=distrib(rnd);
        for (_I i= min_exp; i < max_exp; ++i) {
            rc &= v(ah, i);
            rc &= v(-ah, i);
        }
    }
    std::cout << std::endl;

    if (rc == true) {
        std::cout << __func__ << _N << " test passed " << std::endl;
    } else {
        std::cerr << __func__ << _N << " test failed " << std::endl;
    }
    return rc;
}

int main()
{
#if 1
    std::cerr << std::setprecision(22) << std::hexfloat;
    std::cout << "testing ldexp vXf64" << std::endl;
    bool rd=cftal::test::check_ldexp_up_to<double, int32_t, 8>::v();
    if (rd==false)
        std::cerr << "double test failed" << std::endl;
    std::cout << "testing ldexp vXf32" << std::endl;
    bool rf=cftal::test::check_ldexp_up_to<float, int32_t, 16>::v();
    if (rf==false)
        std::cerr<< "float test failed" << std::endl;
    bool rh=true;
#else
    bool rd=true, rf=true;
    using cftal::f16_t;
    std::cout << "testing ldexp vXf16" << std::endl;
    bool rh=cftal::test::check_ldexp_up_to<f16_t, int16_t, 1>::v();
    if (rh==false)
        std::cerr<< "f16_t test failed" << std::endl;
#endif
    bool rc = rd && rf && rh;
    return rc==true ? 0 : 1;
}
