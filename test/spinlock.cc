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
#include "cftal/test/spinlock.h"
#include <thread>
#include <chrono>

#if defined (__linux__)
#include <pthread.h>
#endif

void
cftal::test::impl::flag_spinlock::_lock()
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
    if (tid.get_id() == std::thread::id()) {
        t = pthread_self();
    }
    int r=pthread_setaffinity_np(t, sizeof(s), &s);
    return r==0;
#else
    return true;
#endif
}

void
cftal::test::impl::char_spinlock::_lock()
{
    do {
        do {
            std::this_thread::yield();
        } while (_lck.load() == LOCK);
    } while (_lck.exchange(LOCK, std::memory_order_acquire) != FREE);
}

