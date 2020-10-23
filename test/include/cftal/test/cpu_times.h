//
// Copyright Axel Zeuner 2010-2020. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_TEST_CPU_TIMES_H__)
#define __CFTAL_TEST_CPU_TIMES_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <iosfwd>

namespace cftal {
    namespace test {

        struct cpu_times {
            int64_t _user;
            int64_t _sys;
            int64_t _elapsed;
            cpu_times() : _user(0), _sys(0), _elapsed(0) {}
        };

        std::ostream&
        operator<<(std::ostream& s, const struct cpu_times& t);

        class cpu_timer {
            int64_t _time_at_start;

            static
            int64_t now();
        public:
            cpu_timer();
            cpu_times elapsed() const;
        };

        class cpu_times_to_stdout {
            cpu_timer _tmr;
        public:
            cpu_times_to_stdout();
            ~cpu_times_to_stdout();
        };
        
    }
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_TEST_SPINLOCK_H__
