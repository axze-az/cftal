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
#if !defined (__CFTAL_EXPR_FUNC_H__)
#define __CFTAL_EXPR_FUNC_H__ 1

#include <cftal/config.h>
#include <cftal/expr.h>

namespace cftal {
    namespace func {
        // data structure for expressions requiring three arguments
        template <typename _T>
        struct tri_data {};

        template <typename _T>
        struct f_fmax {};

        template <typename _T>
        struct f_fmin {};

        template <typename _T>
        struct f_max {};

        template <typename _T>
        struct f_min {};

        template <typename _T>
        struct f_fabs {};

        template <typename _T>
        struct f_abs {};

        template <typename _T>
        struct f_iszero {};

        template <typename _T>
        struct f_isinf {};

        template <typename _T>
        struct f_isnan {};

        template <typename _T>
        struct f_signbit {};

        template <typename _T>
        struct f_rint {};

        template <typename _T>
        struct f_sqrt {};

        template <typename _T>
        struct f_rsqrt {};

        template <typename _T>
        struct f_cbrt {};

        template <typename _T>
        struct f_rcbrt {};

        template <typename _T>
        struct f_root12 {};

        template <typename _T>
        struct f_pow {};

        template <typename _T>
        struct f_copysign {};

        template <typename _T>
        struct f_mulsign {};

        template <typename _T>
        struct f_exp {};

        template <typename _T>
        struct f_exp2 {};

        template <typename _T>
        struct f_exp10 {};

        template <typename _T>
        struct f_expm1 {};

        template <typename _T>
        struct f_exp2m1 {};

        template <typename _T>
        struct f_exp10m1 {};

        template <typename _T>
        struct f_sinh {};

        template <typename _T>
        struct f_cosh {};

        template <typename _T>
        struct f_tanh {};

        template <typename _T>
        struct f_asinh {};

        template <typename _T>
        struct f_acosh {};

        template <typename _T>
        struct f_atanh {};

        template <typename _T>
        struct f_log {};

        template <typename _T>
        struct f_log2 {};

        template <typename _T>
        struct f_log10 {};

        template <typename _T>
        struct f_log1p {};

        template <typename _T>
        struct f_log2p1 {};

        template <typename _T>
        struct f_log10p1 {};
	
        template <typename _T>
        struct f_sin {};

        template <typename _T>
        struct f_cos {};

        template <typename _T>
        struct f_tan {};

        template <typename _T>
        struct f_asin {};

        template <typename _T>
        struct f_acos {};

        template <typename _T>
        struct f_atan {};

        template <typename _T>
        struct f_atan2 {};

        template <typename _T>
        struct f_erf {};

        template <typename _T>
        struct f_erfc {};

        template <typename _T>
        struct f_tgamma {};

    }
}

// Local variables:
// mode: c++
// end:
#endif
