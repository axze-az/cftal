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
            cpu_times _cputimes_at_start;

            static
            cpu_times now();
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
