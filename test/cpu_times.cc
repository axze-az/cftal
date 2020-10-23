//
// Copyright Axel Zeuner 2010-2020. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/cpu_times.h"
#include <cftal/test/stream_save_fmt.h>
#include <cstring>
#include <time.h>
#include <sys/resource.h>
#include <iostream>
#include <iomanip>

std::ostream&
cftal::test::operator<<(std::ostream& s, const cpu_times& ct)
{
    auto fmt=stream_save_fmt(s);

    constexpr const double to_sec= 1e-9;
    
    double uu=double(ct._user);
    double ss=double(ct._sys);
    double tt=double(ct._elapsed);

    double u_s= uu*to_sec;
    double s_s= ss*to_sec;

    constexpr const int64_t min_div=(60 * 1'000'000'000LL);
    int64_t minutes = ct._elapsed / min_div;
    int64_t r= ct._elapsed - minutes*min_div;
    double seconds=double(r)*to_sec;

    double ratio=(tt == 0.0) ? 0.0 : (uu+ss)/tt;
        
    s << std::fixed;
    s << std::setprecision(2) << u_s << "user "
      << std::setprecision(2) << s_s << "system "
      << minutes << ':'
      << std::setw(5) << std::setfill('0') << std::setprecision(2)
      << seconds << "elapsed "
      << std::setprecision(0) << 100*ratio <<  "%CPU";
    return s;
}

namespace {

    inline
    cftal::int64_t
    to_int(const timespec& ts) {
        return int64_t(ts.tv_sec)*1'000'000'000LL + ts.tv_nsec;
    }

    inline
    cftal::int64_t
    to_int(const timeval& tv) {
        return (int64_t(tv.tv_sec)*1'000'000LL + tv.tv_usec)*1'000LL;
    }
    
}

cftal::int64_t
cftal::test::cpu_timer::now()
{
    int64_t r=0;
    timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts)==0) {
        r=to_int(ts);
    }
    return r;
}

cftal::test::cpu_timer::cpu_timer()
    : _time_at_start{now()}
{
}

cftal::test::cpu_times
cftal::test::cpu_timer::elapsed() const
{
    rusage usg;
    std::memset(&usg, 0, sizeof(usg));
    cpu_times r;
    if (getrusage(RUSAGE_SELF, &usg)==0) {
        r._user= to_int(usg.ru_utime);
        r._sys= to_int(usg.ru_stime);
    }
    r._elapsed= now() - _time_at_start;
    return r;
}

cftal::test::cpu_times_to_stdout::cpu_times_to_stdout()
    : _tmr()
{
}

cftal::test::cpu_times_to_stdout::~cpu_times_to_stdout()
{
    std::cout << _tmr.elapsed() << '\n';
}
