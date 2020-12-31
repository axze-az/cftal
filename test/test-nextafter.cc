//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/program.h"

namespace cftal {

    namespace test {

        template <typename _T>
        struct check_nextafter {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return nextafter(a, b);
            }

            static
            auto
            r(const _T& a, const _T& b) {
                return std::nextafter(a, b);
            }

            static
            _T
            s(const _T& a, const _T& b) {
                return std::nextafter(a, b);
            }

            static
            const char* fname() { return "nextafter"; }
        };
    }
}


int main(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int _N64=8;
    const int _N32=16;
    bool rc=true;

    pgm_args ags=parse(argc, argv, 0x8000);

    func_domain<double> d=std::make_pair(-std::numeric_limits< double >::max(),
                                         std::numeric_limits< double >::max());
    std::cout << "testing nextafter vXf64" << std::endl;
    exec_stats<_N64> d_st;
    bool rd= of_fp_func_2_up_to<
        double, _N64, check_nextafter<double> >::v(d_st, d, d,
                                                   ags._speed_only,
                                                   ags._mt,
                                                   cmp_t<double>(),
                                                   ags._cnt);
    if (rd==false)
        std::cerr << "double test failed" << std::endl;
    std::cout << d_st << std::endl;
    std::cout << "testing nextafter vXf32" << std::endl;
    rc &= rd;

    func_domain<double> f=std::make_pair(-std::numeric_limits<float>::max(),
                                         std::numeric_limits< float >::max());
    exec_stats<_N32> f_st;
    bool rf= of_fp_func_2_up_to<
        float, _N32, check_nextafter<float> >::v(f_st, f, f,
                                                 ags._speed_only,
                                                 ags._mt,
                                                 cmp_t<float>(),
                                                 ags._cnt);
    std::cout << f_st << std::endl;
    if (rf==false)
        std::cerr << "float test failed" << std::endl;
    rc &= rf;
    return (rc == true) ? 0 : 1;
}

