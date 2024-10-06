//
// Copyright (C) 2010-2024 Axel Zeuner
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
#if !defined (__CFTAL_ALIGNED_ALLOCATOR_H__)
#define __CFTAL_ALIGNED_ALLOCATOR_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <memory>
#include <new>

namespace cftal {

    template <typename _T, size_t _MIN_ALIGN>
    class aligned_allocator : public std::allocator<_T> {
        static_assert((_MIN_ALIGN & (_MIN_ALIGN-1)) == 0,
                      "_MIN_ALIGN must be a power of 2");
    public:
        using base_type = std::allocator<_T>;
        using size_type = size_t;
        using difference_type= ptrdiff_t;
        using pointer = _T*;
        using const_pointer= const _T*;
        using reference = _T&;
        using const_reference = const _T&;
        using value_type=_T;

        static constexpr size_t min_align() {
            return alignof(_T) < _MIN_ALIGN ? _MIN_ALIGN : alignof(_T);
        }

        template <typename _T1>
        struct rebind {
            using other=aligned_allocator<_T1, _MIN_ALIGN>;
        };

#if __cplusplus >= 201103L
        using propagate_on_container_move_assignment =
            typename base_type::propagate_on_container_move_assignment;
        using is_always_equal =
            typename base_type::is_always_equal;
#endif
        using base_type::base_type;

        pointer
        allocate(size_type n, const void* p=nullptr);

        void
        deallocate(pointer p, size_type n);
    };
}

template <typename _T, cftal::size_t _MIN_ALIGN>
inline
typename cftal::aligned_allocator<_T, _MIN_ALIGN>::pointer
cftal::aligned_allocator<_T,_MIN_ALIGN>::
allocate(size_type n, const void* p)
{
    static_cast<void>(p);
#if __cpp_aligned_new
    constexpr const
    std::align_val_t a= std::align_val_t(min_align());
    return static_cast<_T*>(::operator new(n*sizeof(_T), a));
#else
    return static_cast<_T*>(posix_memalign(n, min_align()));
#endif
}

template<typename _T, std::size_t _MIN_ALIGN>
inline
void cftal::aligned_allocator<_T, _MIN_ALIGN>::
deallocate(pointer p, size_type n)
{
    static_cast<void>(n);
#if __cpp_aligned_new
    constexpr const
    std::align_val_t a= std::align_val_t(min_align());
    ::operator delete (p, a);
#else
    free(p);
#endif
}

#endif
