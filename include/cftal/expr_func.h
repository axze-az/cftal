//
// Copyright (C) 2010-2026 Axel Zeuner
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

    // namespace containing class which may be returned as operation classes
    // in expressions.
    namespace func {

        // data structure for expressions requiring three arguments
        template <typename _T>
        struct tri_data {};

        // fmax
        template <typename _T>
        struct f_fmax {};

        // fmin
        template <typename _T>
        struct f_fmin {};

        // max
        template <typename _T>
        struct f_max {};

        // min
        template <typename _T>
        struct f_min {};

        // fabs
        template <typename _T>
        struct f_fabs {};

        // abs
        template <typename _T>
        struct f_abs {};

        // iszero
        template <typename _T>
        struct f_iszero {};

        // isinf
        template <typename _T>
        struct f_isinf {};

        // isnan
        template <typename _T>
        struct f_isnan {};

        // signbit
        template <typename _T>
        struct f_signbit {};

        // rint
        template <typename _T>
        struct f_rint {};

        // sqrt
        template <typename _T>
        struct f_sqrt {};

        // rsqrt
        template <typename _T>
        struct f_rsqrt {};

        // cbrt
        template <typename _T>
        struct f_cbrt {};

        // rcbrt
        template <typename _T>
        struct f_rcbrt {};

        // root12
        template <typename _T>
        struct f_root12 {};

        // pow
        template <typename _T>
        struct f_pow {};

        // copysign
        template <typename _T>
        struct f_copysign {};

        // mulsign
        template <typename _T>
        struct f_mulsign {};

        // exp
        template <typename _T>
        struct f_exp {};

        // exp2
        template <typename _T>
        struct f_exp2 {};

        // exp10
        template <typename _T>
        struct f_exp10 {};

        // expm1
        template <typename _T>
        struct f_expm1 {};

        // exp2m1
        template <typename _T>
        struct f_exp2m1 {};

        // exp10m1
        template <typename _T>
        struct f_exp10m1 {};

        // sinh
        template <typename _T>
        struct f_sinh {};

        // cosh
        template <typename _T>
        struct f_cosh {};

        // tanh
        template <typename _T>
        struct f_tanh {};

        // asinh
        template <typename _T>
        struct f_asinh {};

        // acosh
        template <typename _T>
        struct f_acosh {};

        // atanh
        template <typename _T>
        struct f_atanh {};

        // log
        template <typename _T>
        struct f_log {};

        // log2
        template <typename _T>
        struct f_log2 {};

        // log10
        template <typename _T>
        struct f_log10 {};

        // log1p == logep1
        template <typename _T>
        struct f_log1p {};

        // log2p1
        template <typename _T>
        struct f_log2p1 {};

        // log10p1
        template <typename _T>
        struct f_log10p1 {};

        // sin
        template <typename _T>
        struct f_sin {};

        // cos
        template <typename _T>
        struct f_cos {};

        // tan
        template <typename _T>
        struct f_tan {};

        // asin
        template <typename _T>
        struct f_asin {};

        // acos
        template <typename _T>
        struct f_acos {};

        // atan
        template <typename _T>
        struct f_atan {};

        // atan2
        template <typename _T>
        struct f_atan2 {};

        // erf
        template <typename _T>
        struct f_erf {};

        // erfc
        template <typename _T>
        struct f_erfc {};

        // tgamma
        template <typename _T>
        struct f_tgamma {};

        // j0
        template <typename _T>
        struct f_j0 {};

        // y0
        template <typename _T>
        struct f_y0 {};

        // j1
        template <typename _T>
        struct f_j1 {};

        // y1
        template <typename _T>
        struct f_y1 {};
    }
}

// Local variables:
// mode: c++
// end:
#endif
