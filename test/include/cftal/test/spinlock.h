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

        namespace impl {

            class flag_spinlock {
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

            class char_spinlock {
                enum {
                    FREE=0,
                    LOCK=1
                };
                std::atomic_char _lck=FREE;
                // static_assert(ATOMIC_CHAR_LOCK_FREE==2, "oops");
                void _lock();
            public:
                void lock() {
                    if (_lck.exchange(LOCK, std::memory_order_acquire)!= FREE)
                        _lock();
                }
                void unlock() {
                    _lck.store(FREE, std::memory_order_release);
                }
            };
        }

        class spinlock {
            using spinlock_t =
                std::conditional_t<ATOMIC_CHAR_LOCK_FREE==2,
                                   impl::char_spinlock,
                                   impl::flag_spinlock>;
            spinlock_t _lck;
        public:
            void lock() { _lck.lock(); }
            void unlock() { _lck.unlock(); }
        };

        // use an unitialized thread to refer to the current
        // thread
        bool
        bind_thread_to_cpu(std::thread& tid, unsigned cpu);



    }
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_TEST_SPINLOCK_H__
