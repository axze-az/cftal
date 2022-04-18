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
#if !defined (__CFTAL_TEST_EXEC_STATS_H__)
#define __CFTAL_TEST_EXEC_STATS_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <atomic>
#include <iostream>
#include <iomanip>

namespace cftal {
    namespace test {

        // execution statistics
        template <std::size_t _N>
        struct alignas(64) exec_stats {
#if 1
            struct data_type {
                uint64_t _v;
            };
#else
            struct alignas(64) data_type {
                std::atomic<uint64_t> _v;
                char _pad[64-sizeof(_v)];
            };
#endif
            // the tics for the vectors of length [0, _N]
            data_type _tics[_N+1];
            // number of function calls
            data_type _evals[_N+1];
            // insert into _tics and increment evals[n]
            void insert(uint64_t tics_before, uint64_t tics_after,
                        unsigned idx) {
                uint64_t ta=tics_after;
                uint64_t tb=tics_before;
                // if (ta < tb) {
                //     ta = 0 - tics_before + tics_after;
                //     tb = 0;
                //     // ta - tb --> tics_after - tics_before
                // }
                uint64_t d=ta - tb;
                _tics[idx]._v += d;
                ++(_evals[idx]._v);
            }
            // constructor
            exec_stats() {
                for (std::size_t i=0; i<_N+1; ++i) {
                    _tics[i]._v = 0;
                    _evals[i]._v = 0;
                }
            }
            // high resolution timer function
            static
            uint64_t hr_timer() { return rdtsc(); }
        };

        template <std::size_t _N>
        exec_stats<_N>&
        operator+=(exec_stats<_N>& a, const exec_stats<_N>& b);

        // output operator for exec_stats
        template <std::size_t _N>
        std::ostream&
        operator<<(std::ostream& s, const exec_stats<_N>& st);
    }
}

template <std::size_t _N>
std::ostream&
cftal::test::operator<<(std::ostream& s, const exec_stats<_N>& st)
{
    std::size_t n= _N + 1;
    s << "execution statistics\n";
    for (std::size_t i=0; i<n; i=((i==0) ? 1: i*2)) {
        double t=st._tics[i]._v;
        uint64_t ei=st._evals[i]._v;
        double tc=ei ? t/double(ei) : 0.0;
        double te=i ? tc/i : tc;
        if (i==0) {
            s << "reference:  calls: ";
        } else {
            s << "vec-len: " << std::setw(2) << i << " calls: ";
        }
        s << std::setw(16) << ei << " tics/call: "
          << std::setprecision(1)
          << std::fixed
          << std::setw(9)
          << tc
          << " tics/elem: "
          << std::setw(7)
          << te
          << std::scientific
          << std::setprecision(22)
          << '\n';
    }
    return s;
}

template <std::size_t _N>
cftal::test::exec_stats<_N>&
cftal::test::
operator+=(exec_stats<_N>& res, const exec_stats<_N>& src)
{
    for (std::size_t i=0; i<_N+1; ++i) {
        res._tics[i]._v += src._tics[i]._v;
        res._evals[i]._v += src._evals[i]._v;
    }
    return res;
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_TEST_EXEC_STATS_H__
