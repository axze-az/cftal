//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_TEST_SPINLOCK_H__)
#define __CFTAL_TEST_SPINLOCK_H__ 1

#include <cftal/config.h>
#include <atomic>
#include <thread>

namespace cftal {
    namespace test {
        class spinlock {
            std::atomic_flag _lck = ATOMIC_FLAG_INIT ;
            void _lock();
        public:
            void lock() {
                if (_lck.test_and_set(std::memory_order_acquire))
                    _lock();
            }
            void unlock() {
                _lck.clear(std::memory_order_release);
            }
        };

        bool
        bind_thread_to_cpu(std::thread& tid::id, unsigned cpu);

    }
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_TEST_SPINLOCK_H__
