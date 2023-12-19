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
#include "cftal/test/program.h"
#include "cftal/vec_f16.h"

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
                using std::nextafter;
                return nextafter(a, b);
            }

            static
            _T
            s(const _T& a, const _T& b) {
                using std::nextafter;
                return nextafter(a, b);
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
    const int _N16=32;
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

    func_domain<float> f=std::make_pair(-std::numeric_limits<float>::max(),
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

    using cftal::f16_t;
    func_domain<f16_t> h=std::make_pair(-std::numeric_limits<f16_t>::max(),
                                         std::numeric_limits<f16_t>::max());
    exec_stats<_N16> h_st;
    bool rh= of_fp_func_2_up_to<
        f16_t, _N16, check_nextafter<f16_t> >::v(h_st, h, h,
                                                 ags._speed_only,
                                                 ags._mt,
                                                 cmp_t<f16_t>(),
                                                 ags._cnt);
    std::cout << h_st << std::endl;
    if (rh==false)
        std::cerr << "f16_t test failed" << std::endl;
    rc &= rf;

    return (rc == true) ? 0 : 1;
}

