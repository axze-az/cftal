//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_MATH_FUNC_TRAITS_H__)
#define __CFTAL_MATH_FUNC_TRAITS_H__ 1

#include <cftal/config.h>

namespace cftal {

    namespace math {

        // helper for func_core and func_common.
        // contains conversion functions between _FLOAT_T
        // _INT_T, extraction and insertion of integer
        // exponents, bias ...
        template <typename _FLOAT_T, typename _INT_T>
        struct func_traits;
    }

}

// Local Variables:
// mode: c++
// end:
#endif
