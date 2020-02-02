//
// Copyright Axel Zeuner 2010-2020. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_TEST_STREAM_SAVE_FMT_H__)
#define __CFTAL_TEST_STREAM_SAVE_FMT_H__ 1

#include <cftal/config.h>
#include <iosfwd>
#include <utility>

namespace cftal {
    namespace test {
        namespace impl {

            template <typename _C>
            class stream_save_fmt {
                std::basic_ios<_C>* _p;
                std::basic_ios<_C> _s;
            public:
                stream_save_fmt(const stream_save_fmt&) = delete;
                stream_save_fmt& operator=(const stream_save_fmt&) = delete;

                stream_save_fmt(std::basic_ios<_C>& s)
                    : _p(&s), _s(nullptr)  {
                    _s.copyfmt(s);
                }
                stream_save_fmt(stream_save_fmt&& r)
                    : _s(std::move(r._s)), _p(std::move(r._p)) {
                    r._p = nullptr;
                }
                stream_save_fmt& operator=(stream_save_fmt&& r) {
                    _s = std::move(r._s);
                    _p = r._p;
                    r._p = nullptr;
                }
                ~stream_save_fmt() {
                    if (_p != nullptr)
                        _p->copyfmt(_s);
                }
            };

        }

        template <typename _C>
        impl::stream_save_fmt<_C> stream_save_fmt(std::basic_ios<_C>& s) {
            return impl::stream_save_fmt<_C>(s);
        }
    }
}

// local variables:
// mode: c++
// end:
#endif //__CFTAL_TEST_STREAM_SAVE_FMT_H__
