//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/of_math_funcs.h"

void
cftal::test::exec_stats::
insert(uint64_t tics_before, uint64_t tics_after, unsigned n)
{
    if (_tics.size() <= n) {
        _tics.resize(n+1, uint64_t(0));
        _evals.resize(n+1, uint64_t(0));
    }
    uint64_t ta=std::max(tics_before, tics_after);
    uint64_t tb=std::min(tics_before, tics_after);
    uint64_t d=ta - tb;
    _tics[n] += d;
    _evals[n] += 1;
}

cftal::uint64_t
cftal::test::exec_stats::hr_timer()
{
    return rdtsc();
}

std::ostream&
cftal::test::operator<<(std::ostream& s, const exec_stats& st)
{
    std::size_t n= st._tics.size();
    s << "execution statistics\n";
    for (std::size_t i=0; i<n; i=((i==0) ? 1: i*2)) {
        double t=st._tics[i];
        uint64_t ei=st._evals[i];
        double tc=t/double(ei);
        double te=i ? tc/i : tc;
        s << "vec-len: " << std::setw(2) << i << " calls: "
          << std::setw(16) << ei << " tics/call: "
          << std::setprecision(1)
          << std::fixed
          << std::setw(9)
          << tc
          << " tics/elem: "
          << std::setw(7)
          << te
          << std::scientific
          << std::setprecision(22)
          << "\n";
    }
    return s;
}

