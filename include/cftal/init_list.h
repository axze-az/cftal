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
#if !defined (__CFTAL_INIT_LIST_H__)
#define __CFTAL_INIT_LIST_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <initializer_list>

namespace cftal {

    template <typename _T>
    class init_list {
        const _T* _begin;
        const _T* _end;
    public:
        constexpr init_list(const _T* b, const _T* e)
            : _begin(b), _end(e) {}
        constexpr const _T* begin() const { return _begin; }
        constexpr const _T* end() const { return _end; }
        constexpr std::size_t size() const { return end() - begin(); }
    };

    template <typename _T, std::size_t _N>
    constexpr init_list<_T>
    low_half(const init_list<_T>& l) {
        const std::size_t s = l.size();
        const std::size_t ns= (s < _N/2 ? s : _N/2);
        const _T* p= l.begin();
        return init_list<_T>(p, p+ ns);
    }

    template <typename _T, std::size_t _N>
    constexpr init_list<_T>
    high_half(const init_list<_T>& l) {
        const std::size_t s = l.size();
        const std::size_t offs= (s > _N/2 ? s - _N/2 : s - 1);
        const std::size_t ns= (s > _N/2 ? s - _N/2 : 1);
        const _T* p= l.begin() + offs;
        return init_list<_T>(p, p+ ns);
    }
}


// Local variables:
// mode: c++
// end:
#endif
