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
#if !defined (__CFTAL_VSVEC_FUNC_0_H__)
#define __CFTAL_VSVEC_FUNC_0_H__ 1

#include <cftal/config.h>
#include <cftal/vsvec_op.h>
#include <cftal/expr_func.h>
#include <cftal/vsvec_bit_a.h>

namespace cftal {

    namespace op_4_vsvec {
        template <typename _T>
        struct f_fmax {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return fmax(a, b);
            }
        };

        template <typename _T>
        struct f_fmin {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return fmin(a, b);
            }
        };

        template <typename _T>
        struct f_max {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return max(a, b);
            }
        };

        template <typename _T>
        struct f_min {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return min(a, b);
            }
        };

        template <typename _T>
        struct f_fabs {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return fabs(a);
            }
        };

        template <typename _T>
        struct f_abs {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return abs(a);
            }
        };

        template <typename _T>
        struct f_iszero {
            template <size_t _N>
            static
            vec<typename vec<_T, _N>::mask_value_type, _N>
            v(const vec<_T, _N>& a) {
                return iszero(a);
            }
        };

        template <typename _T>
        struct f_isinf {
            template <size_t _N>
            static
            vec<typename vec<_T, _N>::mask_value_type, _N>
            v(const vec<_T, _N>& a) {
                return isinf(a);
            }
        };

        template <typename _T>
        struct f_isnan {
            template <size_t _N>
            static
            vec<typename vec<_T, _N>::mask_value_type, _N>
            v(const vec<_T, _N>& a) {
                return isnan(a);
            }
        };

        template <typename _T>
        struct f_signbit {
            template <size_t _N>
            static
            vec<typename vec<_T, _N>::mask_value_type, _N>
            v(const vec<_T, _N>& a) {
                return signbit(a);
            }
        };

        template <typename _T>
        struct f_rint {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return rint(a);
            }
        };

        template <typename _T>
        struct f_sqrt {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return sqrt(a);
            }
        };

        template <typename _F>
        struct int_of_fp {
            using int_type=int32_t;
        };

        template <typename _F>
        using int_of_fp_t = typename int_of_fp<_F>::int_type;

        template <>
        struct int_of_fp<f16_t> {
            using int_type=int16_t;
        };

        template <typename _T>
        struct f_rsqrt {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return rsqrt(a);
            }
        };

        template <typename _T>
        struct f_cbrt {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return cbrt(a);
            }
        };

        template <typename _T>
        struct f_rcbrt {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return rcbrt(a);
            }
        };

        template <typename _T>
        struct f_root12 {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return root12(a);
            }
        };

        template <typename _T>
        struct f_pow {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return pow(a, b);
            }
        };

        template <typename _T>
        struct f_copysign {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return copysign(a, b);
            }
        };

        template <typename _T>
        struct f_mulsign {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return mulsign(a, b);
            }
        };

        template <typename _T>
        struct f_exp {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return exp(a);
            }
        };

        template <typename _T>
        struct f_exp2 {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return exp2(a);
            }
        };

        template <typename _T>
        struct f_exp10 {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return exp10(a);
            }
        };

        template <typename _T>
        struct f_expm1 {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return expm1(a);
            }
        };

        template <typename _T>
        struct f_exp2m1 {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return exp2m1(a);
            }
        };

        template <typename _T>
        struct f_exp10m1 {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return exp10m1(a);
            }
        };

        template <typename _T>
        struct f_sinh {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return sinh(a);
            }
        };

        template <typename _T>
        struct f_cosh {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return cosh(a);
            }
        };

        template <typename _T>
        struct f_tanh {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return tanh(a);
            }
        };


        template <typename _T>
        struct f_asinh {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return asinh(a);
            }
        };

        template <typename _T>
        struct f_acosh {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return acosh(a);
            }
        };

        template <typename _T>
        struct f_atanh {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return atanh(a);
            }
        };

        template <typename _T>
        struct f_log {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return log(a);
            }
        };

        template <typename _T>
        struct f_log2 {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return log2(a);
            }
        };

        template <typename _T>
        struct f_log10 {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return log10(a);
            }
        };

        template <typename _T>
        struct f_log1p {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return log1p(a);
            }
        };

        template <typename _T>
        struct f_log2p1 {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return log2p1(a);
            }
        };

        template <typename _T>
        struct f_log10p1 {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return log10p1(a);
            }
        };

        template <typename _T>
        struct f_sin {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return sin(a);
            }
        };

        template <typename _T>
        struct f_cos {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return cos(a);
            }
        };

        template <typename _T>
        struct f_tan {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return tan(a);
            }
        };

        template <typename _T>
        struct f_asin {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return asin(a);
            }
        };

        template <typename _T>
        struct f_acos {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return acos(a);
            }
        };

        template <typename _T>
        struct f_atan {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return atan(a);
            }
        };

        template <typename _T>
        struct f_atan2 {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return atan2(a, b);
            }
        };

        template <typename _T>
        struct f_erf {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return erf(a);
            }
        };

        template <typename _T>
        struct f_erfc {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return erfc(a);
            }
        };

        template <typename _T>
        struct f_tgamma {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return tgamma(a);
            }
        };

    }

    namespace func {

        template <typename _T, typename _A>
        struct f_fmax<vsvec<_T, _A>> :
            public op_4_vsvec::b_base<_T, op_4_vsvec::f_fmax<_T> > {};

        template <typename _T, typename _A>
        struct f_fmin<vsvec<_T, _A>> :
            public op_4_vsvec::b_base<_T, op_4_vsvec::f_fmin<_T> > {};

        template <typename _T, typename _A>
        struct f_max<vsvec<_T, _A>> :
            public op_4_vsvec::b_base<_T, op_4_vsvec::f_max<_T> > {};

        template <typename _T, typename _A>
        struct f_min<vsvec<_T, _A>> :
            public op_4_vsvec::b_base<_T, op_4_vsvec::f_min<_T> > {};

        template <typename _T, typename _A>
        struct f_fabs<vsvec<_T, _A>> :
            public op_4_vsvec::f_fabs<_T> {};

        template <typename _T, typename _A>
        struct f_abs<vsvec<_T, _A>> :
            public op_4_vsvec::f_abs<_T> {};

        template <typename _T, typename _A>
        struct f_iszero<vsvec<_T, _A>> :
            public op_4_vsvec::f_iszero<_T> {};

        template <typename _T, typename _A>
        struct f_isinf<vsvec<_T, _A>> :
            public op_4_vsvec::f_isinf<_T> {};

        template <typename _T, typename _A>
        struct f_isnan<vsvec<_T, _A>> :
            public op_4_vsvec::f_isnan<_T> {};

        template <typename _T, typename _A>
        struct f_signbit<vsvec<_T, _A>> :
            public op_4_vsvec::f_signbit<_T> {};

        template <typename _T, typename _A>
        struct f_rint<vsvec<_T, _A>> :
            public op_4_vsvec::f_rint<_T> {};

        template <typename _T, typename _A>
        struct f_sqrt<vsvec<_T, _A>> :
            public op_4_vsvec::f_sqrt<_T> {};

        template <typename _T, typename _A>
        struct f_rsqrt<vsvec<_T, _A>> :
            public op_4_vsvec::f_rsqrt<_T> {};

        template <typename _T, typename _A>
        struct f_cbrt<vsvec<_T, _A>> :
            public op_4_vsvec::f_cbrt<_T> {};

        template <typename _T, typename _A>
        struct f_rcbrt<vsvec<_T, _A>> :
            public op_4_vsvec::f_rcbrt<_T> {};

        template <typename _T, typename _A>
        struct f_root12<vsvec<_T, _A>> :
            public op_4_vsvec::f_root12<_T> {};

        template <typename _T, typename _A>
        struct f_pow<vsvec<_T, _A>> :
            public op_4_vsvec::b_base<_T, op_4_vsvec::f_pow<_T> > {};

        template <typename _T, typename _A>
        struct f_copysign<vsvec<_T, _A>> :
            public op_4_vsvec::b_base<_T, op_4_vsvec::f_copysign<_T> > {};

        template <typename _T, typename _A>
        struct f_mulsign<vsvec<_T, _A>> :
            public op_4_vsvec::b_base<_T, op_4_vsvec::f_mulsign<_T> > {};

        template <typename _T, typename _A>
        struct f_exp<vsvec<_T, _A>> :
            public op_4_vsvec::f_exp<_T> {};

        template <typename _T, typename _A>
        struct f_exp2<vsvec<_T, _A>> :
            public op_4_vsvec::f_exp2<_T> {};

        template <typename _T, typename _A>
        struct f_exp10<vsvec<_T, _A>> :
            public op_4_vsvec::f_exp10<_T> {};

        template <typename _T, typename _A>
        struct f_expm1<vsvec<_T, _A>> :
            public op_4_vsvec::f_expm1<_T> {};

        template <typename _T, typename _A>
        struct f_exp2m1<vsvec<_T, _A>> :
            public op_4_vsvec::f_exp2m1<_T> {};

        template <typename _T, typename _A>
        struct f_exp10m1<vsvec<_T, _A>> :
            public op_4_vsvec::f_exp10m1<_T> {};

        template <typename _T, typename _A>
        struct f_sinh<vsvec<_T, _A>> :
            public op_4_vsvec::f_sinh<_T> {};

        template <typename _T, typename _A>
        struct f_cosh<vsvec<_T, _A>> :
            public op_4_vsvec::f_cosh<_T> {};

        template <typename _T, typename _A>
        struct f_tanh<vsvec<_T, _A>> :
            public op_4_vsvec::f_tanh<_T> {};

        template <typename _T, typename _A>
        struct f_asinh<vsvec<_T, _A>> :
            public op_4_vsvec::f_asinh<_T> {};

        template <typename _T, typename _A>
        struct f_acosh<vsvec<_T, _A>> :
            public op_4_vsvec::f_acosh<_T> {};

        template <typename _T, typename _A>
        struct f_atanh<vsvec<_T, _A>> :
            public op_4_vsvec::f_atanh<_T> {};

        template <typename _T, typename _A>
        struct f_log<vsvec<_T, _A>> :
            public op_4_vsvec::f_log<_T> {};

        template <typename _T, typename _A>
        struct f_log2<vsvec<_T, _A>> :
            public op_4_vsvec::f_log2<_T> {};

        template <typename _T, typename _A>
        struct f_log10<vsvec<_T, _A>> :
            public op_4_vsvec::f_log10<_T> {};

        template <typename _T, typename _A>
        struct f_log1p<vsvec<_T, _A>> :
            public op_4_vsvec::f_log1p<_T> {};

        template <typename _T, typename _A>
        struct f_log2p1<vsvec<_T, _A>> :
            public op_4_vsvec::f_log2p1<_T> {};

        template <typename _T, typename _A>
        struct f_log10p1<vsvec<_T, _A>> :
            public op_4_vsvec::f_log10p1<_T> {};

        template <typename _T, typename _A>
        struct f_sin<vsvec<_T, _A>> :
            public op_4_vsvec::f_sin<_T> {};

        template <typename _T, typename _A>
        struct f_cos<vsvec<_T, _A>> :
            public op_4_vsvec::f_cos<_T> {};

        template <typename _T, typename _A>
        struct f_tan<vsvec<_T, _A>> :
            public op_4_vsvec::f_tan<_T> {};

        template <typename _T, typename _A>
        struct f_asin<vsvec<_T, _A>> :
            public op_4_vsvec::f_asin<_T> {};

        template <typename _T, typename _A>
        struct f_acos<vsvec<_T, _A>> :
            public op_4_vsvec::f_acos<_T> {};

        template <typename _T, typename _A>
        struct f_atan<vsvec<_T, _A>> :
            public op_4_vsvec::f_atan<_T> {};

        template <typename _T, typename _A>
        struct f_atan2<vsvec<_T, _A>> :
            public op_4_vsvec::b_base<_T, op_4_vsvec::f_atan2<_T> > {};

        template <typename _T, typename _A>
        struct f_erf<vsvec<_T, _A>> :
            public op_4_vsvec::f_erf<_T> {};

        template <typename _T, typename _A>
        struct f_erfc<vsvec<_T, _A>> :
            public op_4_vsvec::f_erfc<_T> {};

        template <typename _T, typename _A>
        struct f_tgamma<vsvec<_T, _A>> :
            public op_4_vsvec::f_tgamma<_T> {};

    }

#define OPINFO(optype, opcount)                                 \
    template <typename _T, typename _A,                         \
              typename _L, typename _R>                         \
    struct operand<expr< optype <vsvec<_T, _A>>, _L, _R> >{     \
        static                                                  \
        constexpr                                               \
        size_t count() {                                        \
            return opcount;                                     \
        }                                                       \
        static                                                  \
        constexpr                                               \
        result_size sizes() {                                   \
            return result_size::eq_size;                        \
        }                                                       \
    }

    OPINFO(func::f_iszero, 8);
    OPINFO(func::f_isinf, 8);
    OPINFO(func::f_isnan, 8);
    OPINFO(func::f_signbit, 8);

    OPINFO(func::f_fmax, 16);
    OPINFO(func::f_fmin, 16);
    OPINFO(func::f_max, 16);
    OPINFO(func::f_min, 16);

    OPINFO(func::f_fabs, 16);
    OPINFO(func::f_abs, 16);

    OPINFO(func::f_rint, 16);

    OPINFO(func::f_sqrt, 16);
    OPINFO(func::f_rsqrt, 64);
    OPINFO(func::f_cbrt, 64);
    OPINFO(func::f_rcbrt, 64);
    OPINFO(func::f_root12, 64);

    OPINFO(func::f_exp, 64);
    OPINFO(func::f_exp2, 64);
    OPINFO(func::f_exp10, 64);
    OPINFO(func::f_expm1, 64);
    OPINFO(func::f_exp2m1, 64);
    OPINFO(func::f_exp10m1, 64);

    OPINFO(func::f_log, 64);
    OPINFO(func::f_log2, 64);
    OPINFO(func::f_log10, 64);
    OPINFO(func::f_log1p, 64);
    OPINFO(func::f_log2p1, 64);
    OPINFO(func::f_log10p1, 64);

    OPINFO(func::f_sinh, 64);
    OPINFO(func::f_cosh, 64);
    OPINFO(func::f_tanh, 64);

    OPINFO(func::f_asinh, 64);
    OPINFO(func::f_acosh, 64);
    OPINFO(func::f_atanh, 64);

    OPINFO(func::f_sin, 64);
    OPINFO(func::f_cos, 64);
    OPINFO(func::f_tan, 64);

    OPINFO(func::f_asin, 64);
    OPINFO(func::f_acos, 64);
    OPINFO(func::f_atan, 64);
    OPINFO(func::f_atan2, 64);

    OPINFO(func::f_pow, 64);

    OPINFO(func::f_erf, 64);
    OPINFO(func::f_erfc, 64);
    OPINFO(func::f_tgamma, 64);

#undef OPINFO

    // expression template filters
    // fma
    template <size_t _N, typename _T, typename _A,
              class _L,
              class _LR, class _RR>
    inline
    vec<_T, _N>
    eval_i(const expr<op::fma<vsvec<_T, _A>>, _L,
           expr<func::tri_data<vsvec<_T, _A>>, _LR, _RR> >& e,
           size_t i) {
        return op::fma<vsvec<_T, _A>>::v(eval_i<_N, _T>(e._l, i),
                                         eval_i<_N, _T>(e._r._l, i),
                                         eval_i<_N, _T>(e._r._r, i));
    }

    // fms
    template <size_t _N, typename _T, typename _A,
              class _L,
              class _LR, class _RR>
    inline
    vec<_T, _N>
    eval_i(const expr<op::fms<vsvec<_T, _A>>, _L,
           expr<func::tri_data<vsvec<_T, _A>>, _LR, _RR> >& e,
           size_t i) {
        return op::fms<vsvec<_T, _A>>::v(eval_i<_N, _T>(e._l, i),
                                         eval_i<_N, _T>(e._r._l, i),
                                         eval_i<_N, _T>(e._r._r, i));
    }

    // nfma
    template <size_t _N, typename _T, typename _A,
              class _L,
              class _LR, class _RR>
    inline
    vec<_T, _N>
    eval_i(const expr<op::fnma<vsvec<_T, _A>>, _L,
           expr<op::mul<vsvec<_T, _A>>, _LR, _RR> >& e,
           size_t i) {
        return op::fnma<vsvec<_T, _A>>::v(eval_i<_N, _T>(e._l, i),
                                          eval_i<_N, _T>(e._r._l, i),
                                          eval_i<_N, _T>(e._r._r, i));
    }

#define TFUNC_A1(the_func, op_type)                                     \
    /* unary vsvec */                                                   \
    template <typename _T, typename _A>                                 \
    expr<op_type <vsvec<_T, _A>>, vsvec<_T, _A>, void>                  \
    the_func (const vsvec<_T, _A>& l) {                                 \
        return expr<op_type <vsvec<_T, _A>>, vsvec<_T, _A>, void>(l);   \
    }                                                                   \
        /* unary expr */                                                \
    template <typename _T, typename _A,                                 \
              template <class _U> class _OP,                            \
              typename _L, typename _R>                                 \
    expr<op_type <vsvec<_T, _A>>,                                       \
         expr<_OP<vsvec<_T, _A>>, _L, _R>, void>                        \
    the_func (const expr<_OP<vsvec<_T, _A>>, _L, _R>& l) {              \
        return expr<op_type <vsvec<_T, _A>>,                            \
                    expr<_OP<vsvec<_T, _A>>, _L, _R>, void>(l);         \
    }                                                                   \

#define FUNC_A1(the_func, type, op_type)                                \
    /* unary vsvec */                                                   \
    template <typename _A>                                              \
    expr<op_type <vsvec<type, _A>>, vsvec<type, _A>, void>              \
    the_func (const vsvec<type, _A>& l) {                               \
        return expr<op_type <vsvec<type, _A>>, vsvec<type, _A>, void>(l); \
    }                                                                   \
        /* unary expr */                                                \
    template <typename _A,                                              \
              template <class _U> class _OP,                            \
              typename _L, typename _R>                                 \
    expr<op_type <vsvec<type, _A>>,                                     \
         expr<_OP<vsvec<type, _A>>, _L, _R>, void>                      \
    the_func (const expr<_OP<vsvec<type, _A>>, _L, _R>& l) {            \
        return expr<op_type <vsvec<type, _A>>,                          \
                    expr<_OP<vsvec<type, _A>>, _L, _R>, void>(l);       \
    }                                                                   \

#define MFUNC_A1(the_func, type, op_type)                               \
    /* unary vsvec */                                                   \
    template <typename _A>                                              \
    expr<op_type <typename vsvec<type, _A>::mask_type>,                 \
        vsvec<type, _A>, void>                                          \
    the_func (const vsvec<type, _A>& l) {                               \
        return expr<op_type<typename vsvec<type, _A>::mask_type>,       \
            vsvec<type, _A>, void>(l);                                  \
    }                                                                   \
        /* unary expr */                                                \
    template <typename _A,                                              \
              template <class _U> class _OP,                            \
              typename _L, typename _R>                                 \
    expr<op_type <typename vsvec<type, _A>::mask_type>,                 \
         expr<_OP<vsvec<type, _A>>, _L, _R>, void>                      \
    the_func (const expr<_OP<vsvec<type, _A>>, _L, _R>& l) {            \
        return expr<op_type<typename vsvec<type, _A>::mask_type>,       \
                    expr<_OP<vsvec<type, _A>>, _L, _R>, void>(l);       \
    }                                                                   \


    FUNC_A1(abs, int8_t, func::f_abs)
    FUNC_A1(abs, int16_t, func::f_abs)
    FUNC_A1(abs, int32_t, func::f_abs)
    FUNC_A1(abs, int64_t, func::f_abs)
    FUNC_A1(abs, float, func::f_abs)
    FUNC_A1(abs, double, func::f_abs)
    FUNC_A1(abs, f16_t, func::f_abs)
    FUNC_A1(abs, bf16_t, func::f_abs)

    FUNC_A1(fabs, float, func::f_fabs)
    FUNC_A1(fabs, double, func::f_fabs)
    FUNC_A1(fabs, f16_t, func::f_fabs)
    FUNC_A1(fabs, bf16_t, func::f_fabs)

    FUNC_A1(rint, float, func::f_rint)
    FUNC_A1(rint, double, func::f_rint)
    FUNC_A1(rint, f16_t, func::f_rint)
    FUNC_A1(rint, bf16_t, func::f_rint)

    FUNC_A1(sqrt, float, func::f_sqrt)
    FUNC_A1(sqrt, double, func::f_sqrt)
    FUNC_A1(sqrt, f16_t, func::f_sqrt)
    FUNC_A1(sqrt, bf16_t, func::f_sqrt)

    FUNC_A1(rsqrt, float, func::f_rsqrt)
    FUNC_A1(rsqrt, double, func::f_rsqrt)
    FUNC_A1(rsqrt, f16_t, func::f_rsqrt)
    FUNC_A1(rsqrt, bf16_t, func::f_rsqrt)

    FUNC_A1(cbrt, float, func::f_cbrt)
    FUNC_A1(cbrt, double, func::f_cbrt)
    FUNC_A1(cbrt, f16_t, func::f_cbrt)
    FUNC_A1(cbrt, bf16_t, func::f_cbrt)

    FUNC_A1(rcbrt, float, func::f_rcbrt)
    FUNC_A1(rcbrt, double, func::f_rcbrt)
    FUNC_A1(rcbrt, f16_t, func::f_rcbrt)
    FUNC_A1(rcbrt, bf16_t, func::f_rcbrt)

    FUNC_A1(root12, float, func::f_root12)
    FUNC_A1(root12, double, func::f_root12)
    FUNC_A1(root12, f16_t, func::f_root12)
    FUNC_A1(root12, bf16_t, func::f_root12)

    FUNC_A1(exp, float, func::f_exp)
    FUNC_A1(exp, double, func::f_exp)
    FUNC_A1(exp, f16_t, func::f_exp)
    FUNC_A1(exp, bf16_t, func::f_exp)

    FUNC_A1(exp2, float, func::f_exp2)
    FUNC_A1(exp2, double, func::f_exp2)
    FUNC_A1(exp2, f16_t, func::f_exp2)
    FUNC_A1(exp2, bf16_t, func::f_exp2)

    FUNC_A1(exp10, float, func::f_exp10)
    FUNC_A1(exp10, double, func::f_exp10)
    FUNC_A1(exp10, f16_t, func::f_exp10)
    FUNC_A1(exp10, bf16_t, func::f_exp10)

    FUNC_A1(expm1, float, func::f_expm1)
    FUNC_A1(expm1, double, func::f_expm1)
    FUNC_A1(expm1, f16_t, func::f_expm1)
    FUNC_A1(expm1, bf16_t, func::f_expm1)

    FUNC_A1(exp2m1, float, func::f_exp2m1)
    FUNC_A1(exp2m1, double, func::f_exp2m1)
    FUNC_A1(exp2m1, f16_t, func::f_exp2m1)
    FUNC_A1(exp2m1, bf16_t, func::f_exp2m1)

    FUNC_A1(exp10m1, float, func::f_exp10m1)
    FUNC_A1(exp10m1, double, func::f_exp10m1)
    FUNC_A1(exp10m1, f16_t, func::f_exp10m1)
    FUNC_A1(exp10m1, bf16_t, func::f_exp10m1)

    FUNC_A1(sinh, float, func::f_sinh)
    FUNC_A1(sinh, double, func::f_sinh)
    FUNC_A1(sinh, f16_t, func::f_sinh)
    FUNC_A1(sinh, bf16_t, func::f_sinh)

    FUNC_A1(cosh, float, func::f_cosh)
    FUNC_A1(cosh, double, func::f_cosh)
    FUNC_A1(cosh, f16_t, func::f_cosh)
    FUNC_A1(cosh, bf16_t, func::f_cosh)

    FUNC_A1(tanh, float, func::f_tanh)
    FUNC_A1(tanh, double, func::f_tanh)
    FUNC_A1(tanh, f16_t, func::f_tanh)
    FUNC_A1(tanh, bf16_t, func::f_tanh)

    FUNC_A1(asinh, float, func::f_asinh)
    FUNC_A1(asinh, double, func::f_asinh)
    FUNC_A1(asinh, f16_t, func::f_asinh)
    FUNC_A1(asinh, bf16_t, func::f_asinh)

    FUNC_A1(acosh, float, func::f_acosh)
    FUNC_A1(acosh, double, func::f_acosh)
    FUNC_A1(acosh, f16_t, func::f_acosh)
    FUNC_A1(acosh, bf16_t, func::f_acosh)

    FUNC_A1(atanh, float, func::f_atanh)
    FUNC_A1(atanh, double, func::f_atanh)
    FUNC_A1(atanh, f16_t, func::f_atanh)
    FUNC_A1(atanh, bf16_t, func::f_atanh)

    FUNC_A1(log, float, func::f_log)
    FUNC_A1(log, double, func::f_log)
    FUNC_A1(log, f16_t, func::f_log)
    FUNC_A1(log, bf16_t, func::f_log)

    FUNC_A1(log2, float, func::f_log2)
    FUNC_A1(log2, double, func::f_log2)
    FUNC_A1(log2, f16_t, func::f_log2)
    FUNC_A1(log2, bf16_t, func::f_log2)

    FUNC_A1(log10, float, func::f_log10)
    FUNC_A1(log10, double, func::f_log10)
    FUNC_A1(log10, f16_t, func::f_log10)
    FUNC_A1(log10, bf16_t, func::f_log10)

    FUNC_A1(log1p, float, func::f_log1p)
    FUNC_A1(log1p, double, func::f_log1p)
    FUNC_A1(log1p, f16_t, func::f_log1p)
    FUNC_A1(log1p, bf16_t, func::f_log1p)

    FUNC_A1(log2p1, float, func::f_log2p1)
    FUNC_A1(log2p1, double, func::f_log2p1)
    FUNC_A1(log2p1, f16_t, func::f_log2p1)
    FUNC_A1(log2p1, bf16_t, func::f_log2p1)

    FUNC_A1(log10p1, float, func::f_log10p1)
    FUNC_A1(log10p1, double, func::f_log10p1)
    FUNC_A1(log10p1, f16_t, func::f_log10p1)
    FUNC_A1(log10p1, bf16_t, func::f_log10p1)

    FUNC_A1(sin, float, func::f_sin)
    FUNC_A1(sin, double, func::f_sin)
    FUNC_A1(sin, f16_t, func::f_sin)
    FUNC_A1(sin, bf16_t, func::f_sin)

    FUNC_A1(cos, float, func::f_cos)
    FUNC_A1(cos, double, func::f_cos)
    FUNC_A1(cos, f16_t, func::f_cos)
    FUNC_A1(cos, bf16_t, func::f_cos)

    FUNC_A1(tan, float, func::f_tan)
    FUNC_A1(tan, double, func::f_tan)
    FUNC_A1(tan, f16_t, func::f_tan)
    FUNC_A1(tan, bf16_t, func::f_tan)

    FUNC_A1(asin, float, func::f_asin)
    FUNC_A1(asin, double, func::f_asin)
    FUNC_A1(asin, f16_t, func::f_asin)
    FUNC_A1(asin, bf16_t, func::f_asin)

    FUNC_A1(acos, float, func::f_acos)
    FUNC_A1(acos, double, func::f_acos)
    FUNC_A1(acos, f16_t, func::f_acos)
    FUNC_A1(acos, bf16_t, func::f_acos)

    FUNC_A1(atan, float, func::f_atan)
    FUNC_A1(atan, double, func::f_atan)
    FUNC_A1(atan, f16_t, func::f_atan)
    FUNC_A1(atan, bf16_t, func::f_atan)

    FUNC_A1(erf, float, func::f_erf)
    FUNC_A1(erf, double, func::f_erf)
    FUNC_A1(erf, f16_t, func::f_erf)
    FUNC_A1(erf, bf16_t, func::f_erf)

    FUNC_A1(erfc, float, func::f_erfc)
    FUNC_A1(erfc, double, func::f_erfc)
    FUNC_A1(erfc, f16_t, func::f_erfc)
    FUNC_A1(erfc, bf16_t, func::f_erfc)

    FUNC_A1(tgamma, float, func::f_tgamma)
    FUNC_A1(tgamma, double, func::f_tgamma)
    FUNC_A1(tgamma, f16_t, func::f_tgamma)
    FUNC_A1(tgamma, bf16_t, func::f_tgamma)

    MFUNC_A1(iszero, float, func::f_iszero)
    MFUNC_A1(iszero, double, func::f_iszero)
    MFUNC_A1(iszero, f16_t, func::f_iszero)
    MFUNC_A1(iszero, bf16_t, func::f_iszero)

    MFUNC_A1(isinf, float, func::f_isinf)
    MFUNC_A1(isinf, double, func::f_isinf)
    MFUNC_A1(isinf, f16_t, func::f_isinf)
    MFUNC_A1(isinf, bf16_t, func::f_isinf)

    MFUNC_A1(isnan, float, func::f_isnan)
    MFUNC_A1(isnan, double, func::f_isnan)
    MFUNC_A1(isnan, f16_t, func::f_isnan)
    MFUNC_A1(isnan, bf16_t, func::f_isnan)

    MFUNC_A1(signbit, float, func::f_isnan)
    MFUNC_A1(signbit, double, func::f_isnan)
    MFUNC_A1(signbit, f16_t, func::f_isnan)
    MFUNC_A1(signbit, bf16_t, func::f_isnan)

    // #undef FUNC_A1
#define TFUNC_A2(the_func, op_type)                                     \
    /* vsvec, scalar */                                                 \
    template <typename _T, typename _A>                                 \
    expr<op_type <vsvec<_T, _A>>, vsvec<_T, _A>, _T>                    \
    the_func (const vsvec<_T, _A>& l, const _T& r) {                    \
        return expr<op_type <vsvec<_T, _A>>, vsvec<_T, _A>, _T>(l, r);  \
    }                                                                   \
        /* scalar, vsvec */                                             \
    template <typename _T, typename _A>                                 \
    expr<op_type <vsvec<_T, _A>>, _T, vsvec<_T, _A> >                   \
    the_func (const _T& l, const vsvec<_T, _A>& r) {                    \
        return expr<op_type <vsvec<_T, _A>>, _T, vsvec<_T, _A> >(l, r); \
    }                                                                   \
    /* vsvec, vsvec */                                                  \
    template <typename _T, typename _A>                                 \
    expr<op_type <vsvec<_T, _A>>, vsvec<_T, _A>, vsvec<_T, _A> >        \
    the_func (const vsvec<_T, _A>& l, const vsvec<_T, _A>& r) {         \
        return expr<op_type <vsvec<_T, _A>>,                            \
                    vsvec<_T, _A>, vsvec<_T, _A> >(l, r);               \
    }                                                                   \
    /* vsvec, expr */                                                   \
    template <typename _T, typename _A,                                 \
              template <class _U> class _OP,                            \
              class _L, class _R>                                       \
    expr<op_type <vsvec<_T, _A>>, vsvec<_T, _A>,                        \
        expr<_OP<vsvec<_T, _A>>, _L, _R> >                              \
    the_func (const vsvec<_T, _A>& l,                                   \
              const expr<_OP<vsvec<_T, _A>>, _L, _R>& r) {              \
        return expr<op_type <vsvec<_T, _A>>,                            \
                    vsvec<_T, _A>,                                      \
                    expr<_OP<vsvec<_T, _A>>, _L, _R> >(l, r);           \
    }                                                                   \
    /* expr, vsvec */                                                   \
    template <typename _T, typename _A,                                 \
              template <class _U> class _OP,                            \
              class _L, class _R>                                       \
    expr<op_type <vsvec<_T, _A>>,                                       \
         expr<_OP<vsvec<_T, _A>>, _L, _R>, vsvec<_T, _A> >              \
    the_func (const expr<_OP<vsvec<_T, _A>>, _L, _R>& l,                \
              const vsvec<_T, _A>& r) {                                 \
        return expr<op_type <vsvec<_T, _A>>,                            \
            expr<_OP<vsvec<_T, _A>>, _L, _R>,                           \
                    vsvec<_T, _A> >(l, r);                              \
    }                                                                   \
    /* scalar, expr */                                                  \
    template <typename _T, typename _A,                                 \
              template <class _U> class _OP,                            \
              class _L, class _R>                                       \
    expr<op_type <vsvec<_T, _A>>, _T,                                   \
         expr<_OP<vsvec<_T, _A>>, _L, _R> >                             \
    the_func (const _T& l, const expr<_OP<vsvec<_T, _A>>, _L, _R>& r) { \
        return expr<op_type <vsvec<_T, _A>>, _T,                        \
                    expr<_OP<vsvec<_T, _A>>, _L, _R> >(l, r);           \
    }                                                                   \
    /* expr, scalar */                                                  \
    template <typename _T, typename _A,                                 \
              template <class _U> class _OP,                            \
              class _L, class _R>                                       \
    expr<op_type <vsvec<_T, _A>>, expr<_OP<vsvec<_T, _A>>, _L, _R>, _T > \
    the_func (const expr<_OP<vsvec<_T, _A>>, _L, _R>& l, const _T& r) { \
        return expr<op_type <vsvec<_T, _A>>,                            \
            expr<_OP<vsvec<_T, _A>>, _L, _R>, _T >(l, r);               \
    }                                                                   \
    /* expr, expr */                                                    \
    template <typename _T,  typename _A,                                \
              template <class _U1> class _LOP,                          \
              class _LL, class _LR,                                     \
              template <class _U2> class _ROP,                          \
              class _RL, class _RR>                                     \
    expr<op_type <vsvec<_T, _A>>,                                       \
         expr<_LOP<vsvec<_T, _A>>, _LL, _LR>,                           \
         expr<_ROP<vsvec<_T, _A>>, _RL, _RR> >                          \
    the_func (const expr<_LOP<vsvec<_T, _A>>, _LL, _LR>& l,             \
              const expr<_ROP<vsvec<_T, _A>>, _RL, _RR>& r) {           \
        return expr<op_type <vsvec<_T, _A>>,                            \
                    expr<_LOP<vsvec<_T, _A>>, _LL, _LR>,                \
                    expr<_ROP<vsvec<_T, _A>>, _RL, _RR> > (l, r);       \
    }

    TFUNC_A2(fmax, func::f_fmax)
    TFUNC_A2(max, func::f_max)
    TFUNC_A2(fmin, func::f_fmin)
    TFUNC_A2(min, func::f_min)

    TFUNC_A2(copysign, func::f_copysign)
    TFUNC_A2(mulsign, func::f_mulsign)

    TFUNC_A2(pow, func::f_pow)
    TFUNC_A2(atan2, func::f_atan2)

#define TFUNC_A3(the_func, op_type)                                     \
    /* vsvec, scalar, scalar */                                         \
    template <typename _T, typename _A>                                 \
    expr<op_type <vsvec<_T, _A>>,                                       \
        vsvec<_T, _A>,                                                  \
        expr<func::tri_data<vsvec<_T, _A>>, _T, _T> >                   \
    the_func (const vsvec<_T, _A>& a,                                   \
              const _T& b,                                              \
              const _T& c) {                                            \
        using r_expr_t= expr<func::tri_data<vsvec<_T, _A>>, _T, _T >;   \
        r_expr_t bc(b, c);                                              \
        expr<op_type <vsvec<_T, _A>>, vsvec<_T, _A>, r_expr_t>          \
            e(a, bc);                                                   \
        return e;                                                       \
    }                                                                   \
        /* vsvec, scalar, vsvec */                                      \
        template <typename _T, typename _A>                             \
        expr<op_type <vsvec<_T, _A>>,                                   \
             vsvec<_T, _A>,                                             \
             expr<func::tri_data<vsvec<_T, _A>>, _T, vsvec<_T, _A> > >  \
        the_func (const vsvec<_T, _A>& a,                               \
                  const _T& b,                                          \
                  const vsvec<_T, _A>& c) {                             \
            using r_expr_t= expr<func::tri_data<vsvec<_T, _A>>,         \
                                 _T, vsvec<_T, _A> >;                   \
            r_expr_t bc(b, c);                                          \
            expr<op_type <vsvec<_T, _A>>, vsvec<_T, _A>, r_expr_t>      \
                e(a, bc);                                               \
            return e;                                                   \
        }                                                               \
        /* vsvec, scalar, expr */                                       \
        template <typename _T, typename _A,                             \
                  template <class _U> class _OP,                        \
                  class _V >                                            \
        expr<op_type <vsvec<_T, _A>>,                                   \
             vsvec<_T, _A>,                                             \
             expr<func::tri_data<vsvec<_T, _A>>, _T,                    \
                  expr<_OP<vsvec<_T, _A>>, _T, _V> > >                  \
        the_func (const vsvec<_T, _A>& a,                               \
                  const _T& b,                                          \
                  const expr<_OP<vsvec<_T, _A>>, _T, _V>& c) {          \
            using r_expr_t= expr<func::tri_data<vsvec<_T, _A>>,         \
                                 _T,                                    \
                                 expr<_OP<vsvec<_T, _A>>, _T, _V> >;    \
            r_expr_t bc(b, c);                                          \
            expr<op_type <vsvec<_T, _A>>, vsvec<_T, _A>, r_expr_t>      \
                e(a, bc);                                               \
            return e;                                                   \
        }                                                               \
        /* vsvec, vsvec, scalar */                                      \
        template <typename _T, typename _A>                             \
        expr<op_type <vsvec<_T, _A>>,                                   \
             vsvec<_T, _A>,                                             \
             expr<func::tri_data<vsvec<_T, _A>>, vsvec<_T, _A>, _T> >   \
        the_func (const vsvec<_T, _A>& a,                               \
                  const vsvec<_T, _A>& b,                               \
                  const _T& c) {                                        \
            using r_expr_t= expr<func::tri_data<vsvec<_T, _A>>,         \
                                 vsvec<_T, _A>,_T >;                    \
            r_expr_t bc(b, c);                                          \
            expr<op_type <vsvec<_T, _A>>, vsvec<_T, _A>, r_expr_t>      \
                e(a, bc);                                               \
            return e;                                                   \
        }                                                               \
        /* vsvec, vsvec, vsvec */                                       \
        template <typename _T, typename _A>                             \
        expr<op_type <vsvec<_T, _A>>,                                   \
             vsvec<_T, _A>,                                             \
             expr<func::tri_data<vsvec<_T, _A>>,                        \
                  vsvec<_T, _A>, vsvec<_T, _A> > >                      \
        the_func (const vsvec<_T, _A>& a,                               \
                  const vsvec<_T, _A>& b,                               \
                  const vsvec<_T, _A>& c) {                             \
            using r_expr_t= expr<func::tri_data<vsvec<_T, _A>>,         \
                                 vsvec<_T, _A>, vsvec<_T, _A> >;        \
            r_expr_t bc(b, c);                                          \
            expr<op_type< vsvec<_T, _A>>, vsvec<_T, _A>, r_expr_t>      \
                e(a, bc);                                               \
            return e;                                                   \
        }                                                               \
        /* vsvec, vsvec, expr */                                        \
        template <typename _T, typename _A,                             \
                  template <class _U> class _OP,                        \
                  class _O1, class _O2>                                 \
        expr<op_type <vsvec<_T, _A>>,                                   \
             vsvec<_T, _A>,                                             \
             expr<func::tri_data<vsvec<_T, _A>>, vsvec<_T, _A>,         \
                  expr<_OP<vsvec<_T, _A>>, _O1, _O2> > >                \
        the_func (const vsvec<_T, _A>& a,                               \
                  const vsvec<_T, _A>& b,                               \
                  const expr<_OP<vsvec<_T, _A>>, _O1, _O2>& c) {        \
            using r_expr_t= expr<func::tri_data<vsvec<_T, _A>>,         \
                                 vsvec<_T, _A>,                         \
                                 expr<_OP<vsvec<_T, _A>>, _O1, _O2> >;  \
            r_expr_t bc(b, c);                                          \
            expr<op_type <vsvec<_T, _A>>, vsvec<_T, _A>, r_expr_t>      \
                e(a, bc);                                               \
            return e;                                                   \
        }                                                               \

    TFUNC_A3(fma, op::fma)
    TFUNC_A3(fms, op::fms)
    TFUNC_A3(fnma, op::fnma)

    // #undef FUNC_A2
}

// Local variables:
// mode: c++
// end:
#endif
