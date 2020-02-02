//
// Copyright Axel Zeuner 2010-2020. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <cftal/vec.h>
#include <cftal/test/f32_f64.h>
#include <cftal/test/uniform_distribution.h>
#include <cftal/test/of_math_funcs.h>
#include <cftal/math/func_constants.h>
#include <cmath>
#include <random>
#include <iostream>
#include <iomanip>
#include <limits>

namespace cftal {
    namespace test {

        template <typename _T, std::size_t _N>
        class check_ldexp {

            static
            bool v(_T a, int32_t e);

        public:
            static
            bool v();
        };

        template <class _T, std::size_t _N>
        struct check_ldexp_up_to {
            static bool v() {
                bool r=check_ldexp<_T, _N>::v();
                r &= check_ldexp_up_to<_T, _N/2>::v();
                return r;
            }
        };

        template <class _T>
        struct check_ldexp_up_to<_T, 1> {
            static bool v() {
                return check_ldexp<_T, 1>::v();
            }
        };
    }
}

template <typename _T, std::size_t _N>
bool
cftal::test::check_ldexp<_T, _N>::v(_T a, int32_t e)
{
    vec<_T, _N> va=a;
    _T r= std::ldexp(a, e);
    vec<int32_t, _N> ve=e;
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

template <typename _T, std::size_t _N>
bool
cftal::test::check_ldexp<_T, _N>::v()
{
    std::mt19937 rnd;
    uniform_real_distribution<_T>
        distrib(0, std::numeric_limits<_T>::max());

    const int32_t min_exp = 3* std::numeric_limits<_T>::min_exponent;
    const int32_t max_exp = 3*std::numeric_limits<_T>::max_exponent;

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
        for (int32_t i= min_exp; i < max_exp; ++i) {
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
        for (int32_t i= min_exp; i < max_exp; ++i) {
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
    std::cerr << std::setprecision(22) << std::hexfloat;
    std::cout << "testing ldexp vXf64" << std::endl;
    bool rd=cftal::test::check_ldexp_up_to<double, 8>::v();
    if (rd==false)
        std::cerr << "double test failed" << std::endl;
    std::cout << "testing ldexp vXf32" << std::endl;
    bool rf=cftal::test::check_ldexp_up_to<float, 8>::v();
    if (rf==false)
        std::cerr<< "float test failed" << std::endl;
    bool rc = rd && rf;
    return rc==true ? 0 : 1;
}
