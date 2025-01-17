//
// Copyright (C) 2010-2025 Axel Zeuner
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
#if !defined (__CFTAL_TEST_WORK_QUEUE_H__)
#define __CFTAL_TEST_WORK_QUEUE_H__ 1

#include <cftal/config.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>

namespace cftal {
    namespace test {

        template <typename _T>
        class work_queue {
            std::mutex _mtx;
            std::size_t _readers;
            std::condition_variable _read_cv;
            std::size_t _writers;
            std::condition_variable _write_cv;
            std::deque<_T> _queue;
            std::size_t _max_entries;
            bool _active;

            work_queue(const work_queue&) = delete;
            work_queue& operator=(const work_queue&) = delete;
        public:
            work_queue(std::size_t max_entries);
            ~work_queue();

            bool
            write(_T&& v);

            bool
            read(_T& v);

            bool
            deactivate();
        };

    }
}

template <typename _T>
cftal::test::work_queue<_T>::
work_queue(std::size_t max_entries)
    : _mtx(),
      _readers(0),
      _read_cv(),
      _writers(0),
      _write_cv(),
      _queue(),
      _max_entries(max_entries),
      _active(true)
{
    // std::cout << "created with " << _max_entries << std::endl;
}

template <typename _T>
cftal::test::work_queue<_T>::
~work_queue()
{
    deactivate();
}


template <typename _T>
bool
cftal::test::work_queue<_T>::
write(_T&& t)
{
    bool rc=false;
    std::unique_lock<std::mutex> _lck(_mtx);
    ++_writers;
    while (_active && _queue.size() == _max_entries)
        _write_cv.wait(_lck);
    if (this->_active==true) {
        _queue.emplace_back(std::move(t));
        rc=true;
        // std::cout << "data written" << std::endl;
    }
    --_writers;
    if (_readers)
        _read_cv.notify_one();
    return rc;
}

template <typename _T>
bool
cftal::test::work_queue<_T>::
read(_T& t)
{
    bool rc=false;
    std::unique_lock<std::mutex> _lck(_mtx);
    ++_readers;
    while (_active && _queue.empty())
        _read_cv.wait(_lck);
    if (!_queue.empty()) {
        t = std::move(_queue.front());
        _queue.pop_front();
        rc= true;
        // std::cout << "data fetched" << std::endl;
    }
    --_readers;
    if (_writers)
        _write_cv.notify_one();
    return rc;
}

template <typename _T>
bool
cftal::test::work_queue<_T>::
deactivate()
{
    std::unique_lock<std::mutex> _lck(_mtx);
    bool rc = _active == true ? true : false;
    _active = false;
    if (_writers)
        _write_cv.notify_all();
    if (_readers)
        _read_cv.notify_all();
    // std::cout << "deactivate" << std::endl;
    return rc;
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_TEST_WORK_QUEUE_H__
