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
#if !defined (__CFTAL_MATH_FUNC_CONSTANTS_H__)
#define __CFTAL_MATH_FUNC_CONSTANTS_H__ 1

#include <cftal/config.h>
#include <limits>

namespace cftal {

    namespace math {

        template <typename _T>
        struct func_constants {};

        namespace impl {

            template <class _VEC, typename _FLOAT_T>
            struct d_real_constants {};

            template <class _VEC, typename _FLOAT_T>
            struct t_real_constants {};
        }
    }
} // end namespace cftal


// Local Variables:
// mode: c++
// end:
#endif
