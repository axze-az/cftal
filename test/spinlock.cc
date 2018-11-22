//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/spinlock.h"
#include <thread>

#if defined (__linux__)
#include <pthread.h>
#endif

void
cftal::test::spinlock::_lock()
{
    do {
        std::this_thread::yield();
    } while (_lck.test_and_set(std::memory_order_acquire));
}


bool
cftal::test::bind_thread_to_cpu(std::thread& tid, unsigned cpu)
{
#if defined (__linux__)
    cpu_set_t s;
    CPU_ZERO(&s);
    CPU_SET(cpu, &s);
    pthread_t t=tid.native_handle();
    int r=pthread_setaffinity_np(t, sizeof(s), &s);
    return r==0;
#else
    return true;
#endif
}
