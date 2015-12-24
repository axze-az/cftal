#include <cftal/vec.h>
#include <cftal/test/f32_f64.h>
#include <cmath>
#include <random>
#include <iostream>
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
    return check(vr, r, "ldexp");
}

template <typename _T, std::size_t _N>
bool
cftal::test::check_ldexp<_T, _N>::v()
{
    std::mt19937 rnd;
    std::uniform_real_distribution<_T>
        distrib(0, std::numeric_limits<_T>::max());

    const int32_t min_exp = std::numeric_limits<_T>::min_exponent;
    const int32_t max_exp = std::numeric_limits<_T>::max_exponent;

    bool rc=true;
    const int64_t N0=0x100ULL;
    const int64_t N=72*N0;
    for (int64_t i=0; i<N; ++i) {
        if ((i & (N0-1)) == (N0-1))
            std::cout << '.' << std::flush;
        _T ah=distrib(rnd);
        for (int32_t i= min_exp-2; i < max_exp+2; ++i) {
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
    std::cout << "testing ldexp vXf64" << std::endl;
    bool rd=cftal::test::check_ldexp_up_to<double, 8>::v();
    if (rd==false)
        std::cerr << "double test failed" << std::endl;
    std::cout << "testing ldexp vXf32" << std::endl;
    bool rf=cftal::test::check_ldexp_up_to<float, 16>::v();
    if (rf==false)
        std::cerr<< "float test failed" << std::endl;
    bool rc = rd && rf;
    return rc==true ? 0 : 1;
}
