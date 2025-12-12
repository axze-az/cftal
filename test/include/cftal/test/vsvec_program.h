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
#if !defined (__CFTAL_TEST_VSVEC_PROGRAM_H__)
#define __CFTAL_TEST_VSVEC_PROGRAM_H__ 1

#include <cftal/config.h>
#include <cftal/test/of_vsvec_funcs.h>
#include <cftal/test/check_vsvec_funcs.h>
#include <cftal/test/program.h>
#include <cftal/test/cpu_times.h>

namespace cftal {
    namespace test {

        template <typename _CHECK,
                  size_t _CNT,
                  unsigned int _ULP,
                  typename _T,
                  size_t _M>
        int
        vsvec_program(int argc, char** argv,
                      const func_domain<_T> (&d)[_M],
                      const int (&count_shift)[_M]);

    }
}

template <typename _CHECK,
          cftal::size_t _CNT,
          unsigned _ULP,
          typename _T,
          cftal::size_t _M>
int
cftal::test::
vsvec_program(int argc, char** argv,
              const func_domain<_T> (&d)[_M],
              const int (&count_shift)[_M])
{
    cpu_times_to_stdout tt;
    pgm_args ags=parse(argc, argv, _CNT);
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    std::cout << "vsvec test of " << _CHECK::fname()
              << ' ' << ags << std::endl;;
    bool rc=true;
    exec_stats<1> st;
    constexpr const size_t VEC_LEN=64-1;
    auto us=std::make_shared<ulp_stats>();
    for (std::size_t i=0; i<_M; ++i) {
        std::size_t cnt= ags._cnt;
        uint32_t sh=std::abs(count_shift[i]);
        if (count_shift[i] < 0) {
            cnt >>= sh;
        } else if (count_shift[i]>0) {
            cnt <<= sh;
        }
        static_cast<void>(cnt);
        rc &= of_vsvec_func<_CHECK, _T>::v(st, d[i], ags._mt,
                                           cmp_ulp<_T>(_ULP, us),
                                           cnt, VEC_LEN);
    }
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << vsvec_exec_stats(st, VEC_LEN) << std::endl;
    return (rc == true) ? 0 : 1;
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_TEST_VSVEC_PROGRAM_H__
