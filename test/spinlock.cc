//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/spinlock.h"
#include <thread>

void
cftal::test::spinlock::_lock()
{
    do {
        std::this_thread::yield();
    } while (_lck.test_and_set(std::memory_order_acquire));
}

