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
                    : _p(std::move(r._p)), _s(std::move(r._s)) {
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
