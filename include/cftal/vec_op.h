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
#if !defined (__CFTAL_VEC_OP_H__)
#define __CFTAL_VEC_OP_H__ 1

#include <cftal/config.h>
#include <cftal/vec_t_n.h>

namespace cftal {

#define DECL_CMP_OPS(op)                                        \
    template <typename _T, std::size_t _N>                      \
    typename vec<_T, _N>::mask_type                             \
    operator op (const vec<_T, _N>& a,                          \
                 const vec<_T, _N>& b);                         \
                                                                \
    template <typename _T, std::size_t  _N>                     \
    typename vec<_T, _N>::mask_type                             \
    operator op (const vec<_T, _N>& a,                          \
                 const typename vec<_T, _N>::value_type& b);    \
                                                                \
    template <typename _T, std::size_t  _N>                     \
    typename vec<_T, _N>::mask_type                             \
    operator op (const typename vec<_T, _N>::value_type& a,     \
                 const vec<_T, _N>& b)

    DECL_CMP_OPS(<);
    DECL_CMP_OPS(<=);
    DECL_CMP_OPS(==);
    DECL_CMP_OPS(!=);
    DECL_CMP_OPS(>=);
    DECL_CMP_OPS(>);

#undef DECL_CMP_OPS

    namespace op_4_vec {

        // base class for binary operator classes
        template <template <class _V> class _OP,
                  typename _T, std::size_t _N,
                  typename _R>
        struct base {
            using full_type = vec<_T, _N>;
            using mask_type =
                typename vec<_T, _N>::mask_type;
            static
            _R
            v(const full_type& a, const full_type& b) {
                _R r(_OP<vec<_T, _N/2>>::v(low_half(a),
                                           low_half(b)),
                     _OP<vec<_T, _N/2>>::v(high_half(a),
                                           high_half(b)));
                return r;
            }
        };

        // base class for comparison operations
        template <template <class _V> class _OP,
                  typename _T, std::size_t _N>
        struct cmp :
            public base<_OP, _T, _N,
                        typename vec<_T, _N>::mask_type > {
        };

        // base class for binary operations
        template <template <class _V> class _OP,
                  typename _T, std::size_t _N>
        struct bin :
            public base<_OP, _T, _N, vec<_T, _N> > {
        };

        // base class for unary operations
        template <template <class _V> class _OP,
                  typename _T, std::size_t _N>
        struct unary {
            using full_type = vec<_T, _N>;
            static
            full_type
            v(const full_type& a) {
                return full_type(
                    _OP<vec<_T, _N/2>>::v(low_half(a)),
                    _OP<vec<_T, _N/2>>::v(high_half(a)));
            }
        };

        // base class for ternary operations
        template <template <class _V> class _OP,
                  typename _T, std::size_t _N>
        struct ternary {
            using full_type = vec<_T, _N>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return full_type(
                    _OP<vec<_T, _N/2>>::v(low_half(a),
                                          low_half(b),
                                          low_half(c)),
                    _OP<vec<_T, _N/2>>::v(high_half(a),
                                          high_half(b),
                                          high_half(c)));
            }
        };
    }

    namespace op {
        // common comparison operations
        template <typename _T, std::size_t _N>
        struct lt<vec<_T, _N>> : public op_4_vec::cmp<lt, _T, _N> {};

        template <typename _T, std::size_t _N>
        struct le<vec<_T, _N>> : public op_4_vec::cmp<le, _T, _N> {};

        template <typename _T, std::size_t _N>
        struct eq<vec<_T, _N>> : public op_4_vec::cmp<eq, _T, _N> {};

        template <typename _T, std::size_t _N>
        struct ne<vec<_T, _N>> : public op_4_vec::cmp<ne, _T, _N> {};

        template <typename _T, std::size_t _N>
        struct ge<vec<_T, _N>> : public op_4_vec::cmp<ge, _T, _N> {};

        template <typename _T, std::size_t _N>
        struct gt<vec<_T, _N>> : public op_4_vec::cmp<gt, _T, _N> {};

        // arithmetic operations
        // +a
        template <typename _T, std::size_t _N>
        struct plus<vec<_T, _N>> : public op_4_vec::unary<plus, _T, _N> {};
        // -a
        template <typename _T, std::size_t _N>
        struct neg<vec<_T, _N>> : public op_4_vec::unary<neg, _T, _N> {};
        // a + b
        template <typename _T, std::size_t _N>
        struct add<vec<_T, _N>> : public op_4_vec::bin<add, _T, _N> {};
        // a - b
        template <typename _T, std::size_t _N>
        struct sub<vec<_T, _N>> : public op_4_vec::bin<sub, _T, _N> {};
        // a * b
        template <typename _T, std::size_t _N>
        struct mul<vec<_T, _N>> : public op_4_vec::bin<mul, _T, _N> {};
        // a / b
        template <typename _T, std::size_t _N>
        struct div<vec<_T, _N>> : public op_4_vec::bin<div, _T, _N> {};
        // a % b
        template <typename _T, std::size_t _N>
        struct mod<vec<_T, _N>> : public op_4_vec::bin<mod, _T, _N> {};

        // a*b + c
        template <typename _T, std::size_t _N>
        struct fma<vec<_T, _N>> : public op_4_vec::ternary<fma, _T, _N> {};
        // a*b -c
        template <typename _T, std::size_t _N>
        struct fms<vec<_T, _N>> : public op_4_vec::ternary<fms, _T, _N> {};
        // -a*b +c = (c-a*b)
        template <typename _T, std::size_t _N>
        struct fnma<vec<_T, _N>> : public op_4_vec::ternary<fnma, _T, _N> {};

        // bitwise logical operations
        template <typename _T, std::size_t _N>
        struct bit_or<vec<_T, _N>> : public op_4_vec::bin<bit_or, _T, _N> {};

        template <typename _T, std::size_t _N>
        struct bit_and<vec<_T, _N>> : public op_4_vec::bin<bit_and, _T, _N> {};

        template <typename _T, std::size_t _N>
        struct bit_xor<vec<_T, _N>> : public op_4_vec::bin<bit_xor, _T, _N> {};

        template <typename _T, std::size_t _N>
        struct bit_not<vec<_T, _N>> : public op_4_vec::unary<bit_not, _T, _N> {};

        // scalar shift left operator
        template <typename _T, std::size_t _N>
        struct shl<vec<_T, _N>> : public op_4_vec::bin<shl, _T, _N> {
            using full_type = vec<_T, _N>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                full_type r(shl<vec<_T, _N/2>>::v(low_half(a), s),
                            shl<vec<_T, _N/2>>::v(high_half(a), s));
                return r;
            }
        };

        // scalar shift right operator
        template <typename _T, std::size_t _N>
        struct shr<vec<_T, _N>> : public op_4_vec::bin<shr, _T, _N> {
            using full_type = vec<_T, _N>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                full_type r(shr<vec<_T, _N/2>>::v(low_half(a), s),
                            shr<vec<_T, _N/2>>::v(high_half(a), s));
                return r;
            }
        };

        // vector shift left operator
        template <typename _T, std::size_t _N>
        struct vshl<vec<_T, _N>> : public op_4_vec::bin<vshl, _T, _N> {};

        // vector shift right operator
        template <typename _T, std::size_t _N>
        struct vshr<vec<_T, _N>> : public op_4_vec::bin<vshr, _T, _N> {};

    } // namespace op


    // a+ b*c
    template <typename _T, std::size_t _N,
              class _L1, class _L2, class _R2>
    inline
    vec<_T, _N>
    eval(const expr<op::add<vec<_T, _N>>,
         _L1,
         expr<op::mul<vec<_T, _N>>, _L2, _R2> >& e) {
        return op::fma<vec<_T, _N>>::v(eval(e._r._l),
                                       eval(e._r._r),
                                       eval(e._l));
    }
    // a*b +c
    template <typename _T, std::size_t _N,
              class _L1, class _R1, class _R2>
    inline
    vec<_T, _N>
    eval(const expr<op::add<vec<_T, _N>>,
         expr<op::mul<vec<_T, _N>>, _L1, _R1>,
         _R2>& e) {
        return op::fma<vec<_T, _N>>::v(eval(e._l._l),
                                       eval(e._l._r),
                                       eval(e._r));
    }

    // a*b +c*d
    template <typename _T, std::size_t _N,
              class _L1, class _R1, class _L2, class _R2>
    inline
    vec<_T, _N>
    eval(const expr<op::add<vec<_T, _N>>,
         expr<op::mul<vec<_T, _N>>, _L1, _R1>,
         expr<op::mul<vec<_T, _N>>, _L2, _R2> >& e) {
        return op::fma<vec<_T, _N>>::v(eval(e._r._l),
                                       eval(e._r._r),
                                       eval(e._l));
    }

    // a*b -c
    template <typename _T, std::size_t _N,
              class _L1, class _R1, class _R2>
    inline
    vec<_T, _N>
    eval(const expr<op::sub<vec<_T, _N>>,
         expr<op::mul<vec<_T, _N>>, _L1, _R1>,
         _R2>& e) {
        return op::fms<vec<_T, _N>>::v(eval(e._l._l),
                                       eval(e._l._r),
                                       eval(e._r));
    }
    // -a*b +c = c- a* b;
    template <typename _T, std::size_t _N,
              class _L1, class _L2, class _R2>
    inline
    vec<_T, _N>
    eval(const expr<op::sub<vec<_T, _N>>,
         _L1,
         expr<op::mul<vec<_T, _N>>, _L2, _R2> >& e) {
        return op::fnma<vec<_T, _N>>::v(eval(e._r._l),
                                        eval(e._r._r),
                                        eval(e._l));
    }

    // a*b - c*d
    template <typename _T, std::size_t _N,
              class _L1, class _R1, class _L2, class _R2>
    inline
    vec<_T, _N>
    eval(const expr<op::sub<vec<_T, _N>>,
         expr<op::mul<vec<_T, _N>>, _L1, _R1>,
         expr<op::mul<vec<_T, _N>>, _L2, _R2> >& e) {
#if 1
        return op::fnma<vec<_T, _N>>::v(eval(e._r._l),
                                        eval(e._r._r),
                                        eval(e._l));
#else
        return op::fms<vec<_T, _N>>::v(eval(e._l._l),
                                       eval(e._l._r),
                                       eval(e._r));
#endif
    }

    // evaluation of
    // a + -b = a - b
    template <typename _T, std::size_t _N,
              class _L, class _R>
    inline
    vec<_T, _N>
    eval(const expr<op::add<vec<_T, _N>>,
         _L,
         expr<op::neg<vec<_T, _N>>, _R, void> >& e) {
        return op::sub<vec<_T, _N>>::v(eval(e._l),
                                       eval(e._r._l));
    }

    // evaluation of
    // -a + b = b - a
    template <typename _T, std::size_t _N,
              class _L, class _R>
    inline
    vec<_T, _N>
    eval(const expr<op::add<vec<_T, _N>>,
         expr<op::neg<vec<_T, _N>>, _L, void>,
         _R>& e) {
        return op::sub<vec<_T, _N>>::v(eval(e._r._l),
                                       eval(e._l));
    }

    // evaluation of
    // a - -b = a + b
    template <typename _T, std::size_t _N,
              class _L, class _R>
    inline
    vec<_T, _N>
    eval(const expr<op::sub<vec<_T, _N>>,
         _L,
         expr<op::neg<vec<_T, _N>>, _R, void> >& e) {
        return op::add<vec<_T, _N>>::v(eval(e._l),
                                       eval(e._r._l));
    }

    // unary plus operator
    template <class _T, std::size_t _N>
    inline
    const vec<_T, _N>& operator+(const vec<_T, _N>& v) {
        return v;
    }

    // not v
    template <typename _T, std::size_t _N>
    expr<op:: bit_not<vec<_T, _N>>,
         vec<_T, _N>, void>
    operator~(const vec<_T, _N>& v);

    // not expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              typename _L, typename _R>
    expr<op:: bit_not <vec<_T, _N>>,
         expr<_OP<vec<_T, _N>>, _L, _R>, void>
    operator~(const expr<_OP<vec<_T, _N>>, _L, _R>& r);

    // bit_or operator: v, v
    template <typename _T, std::size_t _N>
    expr<op:: bit_or <vec<_T, _N>>,
         vec<_T, _N>,
         vec<_T, _N> >
    operator|(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // bit_or operator: value_type, v
    template <typename _T, std::size_t _N>
    expr<op:: bit_or <vec<_T, _N>>,
         typename vec<_T, _N>::value_type,
         vec<_T, _N> >
    operator|(const typename vec<_T, _N>::value_type& a,
              const vec<_T, _N>& b);

    // bit_or operator: v, value_type
    template <typename _T, std::size_t _N>
    expr<op:: bit_or <vec<_T, _N>>,
         vec<_T, _N>,
         typename vec<_T, _N>::value_type>
    operator|(const vec<_T, _N>& a,
              const typename vec<_T, _N>::value_type& b);

    // bit_or operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: bit_or <vec<_T, _N>>,
         vec<_T, _N>,
         expr<_OP<vec<_T, _N>>, _L, _R> >
    operator|(const vec<_T, _N>& a,
              const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // bit_or operator: expr, v
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: bit_or <vec<_T, _N>>,
         expr<_OP<vec<_T, _N>>, _L, _R>,
         vec<_T, _N> >
    operator|(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
              const vec<_T, _N>& b);

    // bit_or operator: value_type, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: bit_or <vec<_T, _N>>,
         typename vec<_T, _N>::value_type,
         expr<_OP<vec<_T, _N>>, _L, _R> >
    operator|(const typename vec<_T, _N>::value_type& a,
              const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // bit_or operator: expr, value_type
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: bit_or <vec<_T, _N>>,
         expr<_OP<vec<_T, _N>>, _L, _R>,
         typename vec<_T, _N>::value_type >
    operator|(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
              const typename vec<_T, _N>::value_type& b);

    // bit_or operator: expr, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP1,
              class _L1, class _R1,
              template <typename _T2> class _OP2,
              class _L2, class _R2>
    expr<op:: bit_or <vec<_T, _N>>,
         expr<_OP1<vec<_T, _N>>, _L1, _R1>,
         expr<_OP2<vec<_T, _N>>, _L2, _R2> >
    operator|(const expr<_OP1<vec<_T, _N>>, _L1, _R1>& a,
              const expr<_OP2<vec<_T, _N>>, _L2, _R2>& b);

    // self bit_or operator: v, v
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator|=(vec<_T, _N>& a,
               const vec<_T, _N>& b);

    // self bit_or operator: v, value_type
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator|=(vec<_T, _N>& a,
               const typename vec<_T, _N>::value_type& b);

    // self bit_or operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    vec<_T, _N>&
    operator|=(vec<_T, _N>& a,
               const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // bit_and operator: v, v
    template <typename _T, std::size_t _N>
    expr<op:: bit_and <vec<_T, _N>>,
         vec<_T, _N>,
         vec<_T, _N> >
    operator&(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // bit_and operator: value_type, v
    template <typename _T, std::size_t _N>
    expr<op:: bit_and <vec<_T, _N>>,
         typename vec<_T, _N>::value_type,
         vec<_T, _N> >
    operator&(const typename vec<_T, _N>::value_type& a,
              const vec<_T, _N>& b);

    // bit_and operator: v, value_type
    template <typename _T, std::size_t _N>
    expr<op:: bit_and <vec<_T, _N>>,
         vec<_T, _N>,
         typename vec<_T, _N>::value_type>
    operator&(const vec<_T, _N>& a,
              const typename vec<_T, _N>::value_type& b);

    // bit_and operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: bit_and <vec<_T, _N>>,
         vec<_T, _N>,
         expr<_OP<vec<_T, _N>>, _L, _R> >
    operator&(const vec<_T, _N>& a,
              const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // bit_and operator: expr, v
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: bit_and <vec<_T, _N>>,
         expr<_OP<vec<_T, _N>>, _L, _R>,
         vec<_T, _N> >
    operator&(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
              const vec<_T, _N>& b);

    // bit_and operator: value_type, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: bit_and <vec<_T, _N>>,
         typename vec<_T, _N>::value_type,
         expr<_OP<vec<_T, _N>>, _L, _R> >
    operator&(const typename vec<_T, _N>::value_type& a,
              const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // bit_and operator: expr, value_type
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: bit_and <vec<_T, _N>>,
         expr<_OP<vec<_T, _N>>, _L, _R>,
         typename vec<_T, _N>::value_type >
    operator&(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
              const typename vec<_T, _N>::value_type& b);

    // bit_and operator: expr, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP1,
              class _L1, class _R1,
              template <typename _T2> class _OP2,
              class _L2, class _R2>
    expr<op:: bit_and <vec<_T, _N>>,
         expr<_OP1<vec<_T, _N>>, _L1, _R1>,
         expr<_OP2<vec<_T, _N>>, _L2, _R2> >
    operator&(const expr<_OP1<vec<_T, _N>>, _L1, _R1>& a,
              const expr<_OP2<vec<_T, _N>>, _L2, _R2>& b);

    // self bit_and operator: v, v
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator&=(vec<_T, _N>& a,
               const vec<_T, _N>& b);

    // self bit_and operator: v, value_type
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator&=(vec<_T, _N>& a,
               const typename vec<_T, _N>::value_type& b);

    // self bit_and operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    vec<_T, _N>&
    operator&=(vec<_T, _N>& a,
               const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // bit_xor operator: v, v
    template <typename _T, std::size_t _N>
    expr<op:: bit_xor <vec<_T, _N>>,
         vec<_T, _N>,
         vec<_T, _N> >
    operator^(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // bit_xor operator: value_type, v
    template <typename _T, std::size_t _N>
    expr<op:: bit_xor <vec<_T, _N>>,
         typename vec<_T, _N>::value_type,
         vec<_T, _N> >
    operator^(const typename vec<_T, _N>::value_type& a,
              const vec<_T, _N>& b);

    // bit_xor operator: v, value_type
    template <typename _T, std::size_t _N>
    expr<op:: bit_xor <vec<_T, _N>>,
         vec<_T, _N>,
         typename vec<_T, _N>::value_type>
    operator^(const vec<_T, _N>& a,
              const typename vec<_T, _N>::value_type& b);

    // bit_xor operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: bit_xor <vec<_T, _N>>,
         vec<_T, _N>,
         expr<_OP<vec<_T, _N>>, _L, _R> >
    operator^(const vec<_T, _N>& a,
              const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // bit_xor operator: expr, v
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: bit_xor <vec<_T, _N>>,
         expr<_OP<vec<_T, _N>>, _L, _R>,
         vec<_T, _N> >
    operator^(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
              const vec<_T, _N>& b);

    // bit_xor operator: value_type, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: bit_xor <vec<_T, _N>>,
         typename vec<_T, _N>::value_type,
         expr<_OP<vec<_T, _N>>, _L, _R> >
    operator^(const typename vec<_T, _N>::value_type& a,
              const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // bit_xor operator: expr, value_type
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: bit_xor <vec<_T, _N>>,
         expr<_OP<vec<_T, _N>>, _L, _R>,
         typename vec<_T, _N>::value_type >
    operator^(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
              const typename vec<_T, _N>::value_type& b);

    // bit_xor operator: expr, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP1,
              class _L1, class _R1,
              template <typename _T2> class _OP2,
              class _L2, class _R2>
    expr<op:: bit_xor <vec<_T, _N>>,
         expr<_OP1<vec<_T, _N>>, _L1, _R1>,
         expr<_OP2<vec<_T, _N>>, _L2, _R2> >
    operator^(const expr<_OP1<vec<_T, _N>>, _L1, _R1>& a,
              const expr<_OP2<vec<_T, _N>>, _L2, _R2>& b);

    // self bit_xor operator: v, v
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator^=(vec<_T, _N>& a,
               const vec<_T, _N>& b);

    // self bit_xor operator: v, value_type
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator^=(vec<_T, _N>& a,
               const typename vec<_T, _N>::value_type& b);

    // self bit_xor operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    vec<_T, _N>&
    operator^=(vec<_T, _N>& a,
               const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // vshl operator: v, v
    template <typename _T, std::size_t _N>
    expr<op:: vshl <vec<_T, _N>>,
         vec<_T, _N>,
         vec<_T, _N> >
    operator<<(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // vshl operator: value_type, v
    template <typename _T, std::size_t _N>
    expr<op:: vshl <vec<_T, _N>>,
         typename vec<_T, _N>::value_type,
         vec<_T, _N> >
    operator<<(const typename vec<_T, _N>::value_type& a,
               const vec<_T, _N>& b);

    // vshl operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: vshl <vec<_T, _N>>,
         vec<_T, _N>,
         expr<_OP<vec<_T, _N>>, _L, _R> >
    operator<<(const vec<_T, _N>& a,
               const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // vshl operator: expr, v
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: vshl <vec<_T, _N>>,
         expr<_OP<vec<_T, _N>>, _L, _R>,
         vec<_T, _N> >
    operator<<(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
               const vec<_T, _N>& b);

    // vshl operator: value_type, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: vshl <vec<_T, _N>>,
         typename vec<_T, _N>::value_type,
         expr<_OP<vec<_T, _N>>, _L, _R> >
    operator<<(const typename vec<_T, _N>::value_type& a,
               const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // vshl operator: expr, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP1,
              class _L1, class _R1,
              template <typename _T2> class _OP2,
              class _L2, class _R2>
    expr<op:: vshl <vec<_T, _N>>,
         expr<_OP1<vec<_T, _N>>, _L1, _R1>,
         expr<_OP2<vec<_T, _N>>, _L2, _R2> >
    operator<<(const expr<_OP1<vec<_T, _N>>, _L1, _R1>& a,
               const expr<_OP2<vec<_T, _N>>, _L2, _R2>& b);

    // self vshl operator: v, v
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator<<=(vec<_T, _N>& a,
                const vec<_T, _N>& b);

    // self vshl operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    vec<_T, _N>&
    operator<<=(vec<_T, _N>& a,
                const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // vshr operator: v, v
    template <typename _T, std::size_t _N>
    expr<op:: vshr <vec<_T, _N>>,
         vec<_T, _N>,
         vec<_T, _N> >
    operator>>(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // vshr operator: value_type, v
    template <typename _T, std::size_t _N>
    expr<op:: vshr <vec<_T, _N>>,
         typename vec<_T, _N>::value_type,
         vec<_T, _N> >
    operator>>(const typename vec<_T, _N>::value_type& a,
               const vec<_T, _N>& b);

    // vshr operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: vshr <vec<_T, _N>>,
         vec<_T, _N>,
         expr<_OP<vec<_T, _N>>, _L, _R> >
    operator>>(const vec<_T, _N>& a,
               const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // vshr operator: expr, v
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: vshr <vec<_T, _N>>,
         expr<_OP<vec<_T, _N>>, _L, _R>,
         vec<_T, _N> >
    operator>>(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
               const vec<_T, _N>& b);

    // vshr operator: value_type, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: vshr <vec<_T, _N>>,
         typename vec<_T, _N>::value_type,
         expr<_OP<vec<_T, _N>>, _L, _R> >
    operator>>(const typename vec<_T, _N>::value_type& a,
               const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // vshr operator: expr, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP1,
              class _L1, class _R1,
              template <typename _T2> class _OP2,
              class _L2, class _R2>
    expr<op:: vshr <vec<_T, _N>>,
         expr<_OP1<vec<_T, _N>>, _L1, _R1>,
         expr<_OP2<vec<_T, _N>>, _L2, _R2> >
    operator>>(const expr<_OP1<vec<_T, _N>>, _L1, _R1>& a,
               const expr<_OP2<vec<_T, _N>>, _L2, _R2>& b);

    // self vshr operator: v, v
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator>>=(vec<_T, _N>& a,
                const vec<_T, _N>& b);

    // self vshr operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    vec<_T, _N>&
    operator>>=(vec<_T, _N>& a,
                const expr<_OP<vec<_T, _N>>, _L, _R>& b);


    // left shift v unsigned
    template <typename _T, std::size_t _N>
    expr<op:: shl<vec<_T, _N>>,
         vec<_T, _N>, unsigned >
    operator <<(const vec<_T, _N>& v, unsigned s);
    // left shift expr unsigned
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: shl<vec<_T, _N>>,
         expr<_OP<vec<_T, _N>>, _L, _R>, unsigned>
    operator <<(const expr<_OP<vec<_T, _N>>, _L, _R>& v,
                unsigned s);
    // self left shift
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator <<=(vec<_T, _N>& v, unsigned s);

    // right shift v unsigned
    template <typename _T, std::size_t _N>
    expr<op:: shr<vec<_T, _N>>,
         vec<_T, _N>, unsigned >
    operator >>(const vec<_T, _N>& v, unsigned s);
    // right shift expr unsigned
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: shr<vec<_T, _N>>,
         expr<_OP<vec<_T, _N>>, _L, _R>, unsigned>
    operator >>(const expr<_OP<vec<_T, _N>>, _L, _R>& v,
                unsigned s);
    // self right shift
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator >>=(vec<_T, _N>& v, unsigned s);

    // unary minus: v
    template <typename _T, std::size_t _N>
    expr<op:: neg<vec<_T, _N>>,
         vec<_T, _N>, void>
    operator-(const vec<_T, _N>& v);

    // unary minus: expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              typename _L, typename _R>
    expr<op:: neg<vec<_T, _N>>,
         expr<_OP<vec<_T, _N>>, _L, _R>, void>
    operator-(const expr<_OP<vec<_T, _N>>, _L, _R>& r);

    // add operator: v, v
    template <typename _T, std::size_t _N>
    expr<op:: add <vec<_T, _N>>,
         vec<_T, _N>,
         vec<_T, _N> >
    operator+(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // add operator: value_type, v
    template <typename _T, std::size_t _N>
    expr<op:: add <vec<_T, _N>>,
         typename vec<_T, _N>::value_type,
         vec<_T, _N> >
    operator+(const typename vec<_T, _N>::value_type& a,
              const vec<_T, _N>& b);

    // add operator: v, value_type
    template <typename _T, std::size_t _N>
    expr<op:: add <vec<_T, _N>>,
         vec<_T, _N>,
         typename vec<_T, _N>::value_type>
    operator+(const vec<_T, _N>& a,
              const typename vec<_T, _N>::value_type& b);

    // add operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: add <vec<_T, _N>>,
         vec<_T, _N>,
         expr<_OP<vec<_T, _N>>, _L, _R> >
    operator+(const vec<_T, _N>& a,
              const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // add operator: expr, v
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: add <vec<_T, _N>>,
         expr<_OP<vec<_T, _N>>, _L, _R>,
         vec<_T, _N> >
    operator+(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
              const vec<_T, _N>& b);

    // add operator: value_type, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: add <vec<_T, _N>>,
         typename vec<_T, _N>::value_type,
         expr<_OP<vec<_T, _N>>, _L, _R> >
    operator+(const typename vec<_T, _N>::value_type& a,
              const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // add operator: expr, value_type
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: add <vec<_T, _N>>,
         expr<_OP<vec<_T, _N>>, _L, _R>,
         typename vec<_T, _N>::value_type >
    operator+(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
              const typename vec<_T, _N>::value_type& b);

    // add operator: expr, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP1,
              class _L1, class _R1,
              template <typename _T2> class _OP2,
              class _L2, class _R2>
    expr<op:: add <vec<_T, _N>>,
         expr<_OP1<vec<_T, _N>>, _L1, _R1>,
         expr<_OP2<vec<_T, _N>>, _L2, _R2> >
    operator+(const expr<_OP1<vec<_T, _N>>, _L1, _R1>& a,
              const expr<_OP2<vec<_T, _N>>, _L2, _R2>& b);

    // self add operator: v, v
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator+=(vec<_T, _N>& a,
               const vec<_T, _N>& b);

    // self add operator: v, value_type
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator+=(vec<_T, _N>& a,
               const typename vec<_T, _N>::value_type& b);

    // self add operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    vec<_T, _N>&
    operator+=(vec<_T, _N>& a,
               const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // sub operator: v, v
    template <typename _T, std::size_t _N>
    expr<op:: sub <vec<_T, _N>>,
         vec<_T, _N>,
         vec<_T, _N> >
    operator-(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // sub operator: value_type, v
    template <typename _T, std::size_t _N>
    expr<op:: sub <vec<_T, _N>>,
         typename vec<_T, _N>::value_type,
         vec<_T, _N> >
    operator-(const typename vec<_T, _N>::value_type& a,
              const vec<_T, _N>& b);

    // sub operator: v, value_type
    template <typename _T, std::size_t _N>
    expr<op:: sub <vec<_T, _N>>,
         vec<_T, _N>,
         typename vec<_T, _N>::value_type>
    operator-(const vec<_T, _N>& a,
              const typename vec<_T, _N>::value_type& b);

    // sub operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: sub <vec<_T, _N>>,
         vec<_T, _N>,
         expr<_OP<vec<_T, _N>>, _L, _R> >
    operator-(const vec<_T, _N>& a,
              const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // sub operator: expr, v
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: sub <vec<_T, _N>>,
         expr<_OP<vec<_T, _N>>, _L, _R>,
         vec<_T, _N> >
    operator-(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
              const vec<_T, _N>& b);

    // sub operator: value_type, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: sub <vec<_T, _N>>,
         typename vec<_T, _N>::value_type,
         expr<_OP<vec<_T, _N>>, _L, _R> >
    operator-(const typename vec<_T, _N>::value_type& a,
              const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // sub operator: expr, value_type
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: sub <vec<_T, _N>>,
         expr<_OP<vec<_T, _N>>, _L, _R>,
         typename vec<_T, _N>::value_type >
    operator-(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
              const typename vec<_T, _N>::value_type& b);

    // sub operator: expr, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP1,
              class _L1, class _R1,
              template <typename _T2> class _OP2,
              class _L2, class _R2>
    expr<op:: sub <vec<_T, _N>>,
         expr<_OP1<vec<_T, _N>>, _L1, _R1>,
         expr<_OP2<vec<_T, _N>>, _L2, _R2> >
    operator-(const expr<_OP1<vec<_T, _N>>, _L1, _R1>& a,
              const expr<_OP2<vec<_T, _N>>, _L2, _R2>& b);

    // self sub operator: v, v
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator-=(vec<_T, _N>& a,
               const vec<_T, _N>& b);

    // self sub operator: v, value_type
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator-=(vec<_T, _N>& a,
               const typename vec<_T, _N>::value_type& b);

    // self sub operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    vec<_T, _N>&
    operator-=(vec<_T, _N>& a,
               const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // mul operator: v, v
    template <typename _T, std::size_t _N>
    expr<op:: mul <vec<_T, _N>>,
         vec<_T, _N>,
         vec<_T, _N> >
    operator*(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // mul operator: value_type, v
    template <typename _T, std::size_t _N>
    expr<op:: mul <vec<_T, _N>>,
         typename vec<_T, _N>::value_type,
         vec<_T, _N> >
    operator*(const typename vec<_T, _N>::value_type& a,
              const vec<_T, _N>& b);

    // mul operator: v, value_type
    template <typename _T, std::size_t _N>
    expr<op:: mul <vec<_T, _N>>,
         vec<_T, _N>,
         typename vec<_T, _N>::value_type>
    operator*(const vec<_T, _N>& a,
              const typename vec<_T, _N>::value_type& b);

    // mul operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: mul <vec<_T, _N>>,
         vec<_T, _N>,
         expr<_OP<vec<_T, _N>>, _L, _R> >
    operator*(const vec<_T, _N>& a,
              const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // mul operator: expr, v
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: mul <vec<_T, _N>>,
         expr<_OP<vec<_T, _N>>, _L, _R>,
         vec<_T, _N> >
    operator*(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
              const vec<_T, _N>& b);

    // mul operator: value_type, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: mul <vec<_T, _N>>,
         typename vec<_T, _N>::value_type,
         expr<_OP<vec<_T, _N>>, _L, _R> >
    operator*(const typename vec<_T, _N>::value_type& a,
              const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // mul operator: expr, value_type
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: mul <vec<_T, _N>>,
         expr<_OP<vec<_T, _N>>, _L, _R>,
         typename vec<_T, _N>::value_type >
    operator*(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
              const typename vec<_T, _N>::value_type& b);

    // mul operator: expr, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP1,
              class _L1, class _R1,
              template <typename _T2> class _OP2,
              class _L2, class _R2>
    expr<op:: mul <vec<_T, _N>>,
         expr<_OP1<vec<_T, _N>>, _L1, _R1>,
         expr<_OP2<vec<_T, _N>>, _L2, _R2> >
    operator*(const expr<_OP1<vec<_T, _N>>, _L1, _R1>& a,
              const expr<_OP2<vec<_T, _N>>, _L2, _R2>& b);

    // self mul operator: v, v
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator*=(vec<_T, _N>& a,
               const vec<_T, _N>& b);

    // self mul operator: v, value_type
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator*=(vec<_T, _N>& a,
               const typename vec<_T, _N>::value_type& b);

    // self mul operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    vec<_T, _N>&
    operator*=(vec<_T, _N>& a,
               const expr<_OP<vec<_T, _N>>, _L, _R>& b);


    // div operator: v, v
    template <typename _T, std::size_t _N>
    expr<op:: div <vec<_T, _N>>,
         vec<_T, _N>,
         vec<_T, _N> >
    operator/(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // div operator: value_type, v
    template <typename _T, std::size_t _N>
    expr<op:: div <vec<_T, _N>>,
         typename vec<_T, _N>::value_type,
         vec<_T, _N> >
    operator/(const typename vec<_T, _N>::value_type& a,
              const vec<_T, _N>& b);

    // div operator: v, value_type
    template <typename _T, std::size_t _N>
    expr<op:: div <vec<_T, _N>>,
         vec<_T, _N>,
         typename vec<_T, _N>::value_type>
    operator/(const vec<_T, _N>& a,
              const typename vec<_T, _N>::value_type& b);

    // div operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: div <vec<_T, _N>>,
         vec<_T, _N>,
         expr<_OP<vec<_T, _N>>, _L, _R> >
    operator/(const vec<_T, _N>& a,
              const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // div operator: expr, v
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: div <vec<_T, _N>>,
         expr<_OP<vec<_T, _N>>, _L, _R>,
         vec<_T, _N> >
    operator/(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
              const vec<_T, _N>& b);

    // div operator: value_type, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: div <vec<_T, _N>>,
         typename vec<_T, _N>::value_type,
         expr<_OP<vec<_T, _N>>, _L, _R> >
    operator/(const typename vec<_T, _N>::value_type& a,
              const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // div operator: expr, value_type
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: div <vec<_T, _N>>,
         expr<_OP<vec<_T, _N>>, _L, _R>,
         typename vec<_T, _N>::value_type >
    operator/(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
              const typename vec<_T, _N>::value_type& b);

    // div operator: expr, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP1,
              class _L1, class _R1,
              template <typename _T2> class _OP2,
              class _L2, class _R2>
    expr<op:: div <vec<_T, _N>>,
         expr<_OP1<vec<_T, _N>>, _L1, _R1>,
         expr<_OP2<vec<_T, _N>>, _L2, _R2> >
    operator/(const expr<_OP1<vec<_T, _N>>, _L1, _R1>& a,
              const expr<_OP2<vec<_T, _N>>, _L2, _R2>& b);

    // self div operator: v, v
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator/=(vec<_T, _N>& a,
               const vec<_T, _N>& b);

    // self div operator: v, value_type
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator/=(vec<_T, _N>& a,
               const typename vec<_T, _N>::value_type& b);

    // self div operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    vec<_T, _N>&
    operator/=(vec<_T, _N>& a,
               const expr<_OP<vec<_T, _N>>, _L, _R>& b);


    // mod operator: v, v
    template <typename _T, std::size_t _N>
    expr<op:: mod <vec<_T, _N>>,
         vec<_T, _N>,
         vec<_T, _N> >
    operator%(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // mod operator: value_type, v
    template <typename _T, std::size_t _N>
    expr<op:: mod <vec<_T, _N>>,
         typename vec<_T, _N>::value_type,
         vec<_T, _N> >
    operator%(const typename vec<_T, _N>::value_type& a,
              const vec<_T, _N>& b);

    // mod operator: v, value_type
    template <typename _T, std::size_t _N>
    expr<op:: mod <vec<_T, _N>>,
         vec<_T, _N>,
         typename vec<_T, _N>::value_type>
    operator%(const vec<_T, _N>& a,
              const typename vec<_T, _N>::value_type& b);

    // mod operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: mod <vec<_T, _N>>,
         vec<_T, _N>,
         expr<_OP<vec<_T, _N>>, _L, _R> >
    operator%(const vec<_T, _N>& a,
              const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // mod operator: expr, v
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: mod <vec<_T, _N>>,
         expr<_OP<vec<_T, _N>>, _L, _R>,
         vec<_T, _N> >
    operator%(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
              const vec<_T, _N>& b);

    // mod operator: value_type, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: mod <vec<_T, _N>>,
         typename vec<_T, _N>::value_type,
         expr<_OP<vec<_T, _N>>, _L, _R> >
    operator%(const typename vec<_T, _N>::value_type& a,
              const expr<_OP<vec<_T, _N>>, _L, _R>& b);

    // mod operator: expr, value_type
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    expr<op:: mod <vec<_T, _N>>,
         expr<_OP<vec<_T, _N>>, _L, _R>,
         typename vec<_T, _N>::value_type >
    operator%(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
              const typename vec<_T, _N>::value_type& b);

    // mod operator: expr, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP1,
              class _L1, class _R1,
              template <typename _T2> class _OP2,
              class _L2, class _R2>
    expr<op:: mod <vec<_T, _N>>,
         expr<_OP1<vec<_T, _N>>, _L1, _R1>,
         expr<_OP2<vec<_T, _N>>, _L2, _R2> >
    operator%(const expr<_OP1<vec<_T, _N>>, _L1, _R1>& a,
              const expr<_OP2<vec<_T, _N>>, _L2, _R2>& b);

    // self mod operator: v, v
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator%=(vec<_T, _N>& a,
               const vec<_T, _N>& b);

    // self mod operator: v, value_type
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator%=(vec<_T, _N>& a,
               const typename vec<_T, _N>::value_type& b);

    // self mod operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1> class _OP,
              class _L, class _R>
    vec<_T, _N>&
    operator%=(vec<_T, _N>& a,
               const expr<_OP<vec<_T, _N>>, _L, _R>& b);

}

#define DEF_CMP_OPS(opname, opobj)                                      \
    template <class _T, std::size_t _N>                                 \
    inline                                                              \
    typename cftal::vec<_T, _N>::mask_type                              \
    cftal::operator opname(const vec<_T, _N>& a,                        \
                           const vec<_T, _N>& b)                        \
    {                                                                   \
        return opobj <vec<_T, _N>> ::v(a, b);                                \
    }                                                                   \
                                                                        \
    template <class _T, std::size_t _N>                                 \
    inline                                                              \
    typename cftal::vec<_T, _N>::mask_type                              \
    cftal::operator opname(const vec<_T, _N>& a,                        \
                           const typename vec<_T, _N>::value_type& b)   \
    {                                                                   \
        return opobj <vec<_T, _N>> ::v(a, b);                                \
    }                                                                   \
                                                                        \
    template <class _T, std::size_t _N>                                 \
    inline                                                              \
    typename cftal::vec<_T, _N>::mask_type                              \
    cftal::operator opname(const typename vec<_T, _N>::value_type& a,   \
                           const vec<_T, _N>& b)                        \
    {                                                                   \
        return  opobj <vec<_T, _N>> ::v(a, b);                               \
    }


DEF_CMP_OPS(<, op::lt)
DEF_CMP_OPS(<=, op::le)
DEF_CMP_OPS(==, op::eq)
DEF_CMP_OPS(!=, op::ne)
DEF_CMP_OPS(>=, op::ge)
DEF_CMP_OPS(>, op::gt)

#undef DEF_CMP_OPS

template <typename _T, std::size_t _N>
cftal::expr<cftal::op:: bit_not <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>, void>
cftal::operator~(const vec<_T, _N>& v)
{
    return expr<op:: bit_not <vec<_T, _N>>,
                vec<_T, _N>, void>(v);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          typename _L, typename _R>
cftal::expr<cftal::op:: bit_not<cftal::vec<_T, _N>>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R>,
            void>
cftal::operator~(const expr<_OP<vec<_T, _N>>, _L, _R>& v)
{
    return expr<op:: bit_not <vec<_T, _N>>,
                expr<_OP<vec<_T, _N>>, _L, _R>,
                void>(v);
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::bit_or <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            cftal::vec<_T, _N> >
cftal::operator|(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return expr<op:: bit_or<vec<_T, _N>>,
                vec<_T, _N>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::bit_or <cftal::vec<_T, _N>>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::vec<_T, _N> >
cftal::operator|(const typename vec<_T, _N>::value_type& a,
                 const vec<_T, _N>& b)
{
    return expr<op::bit_or<vec<_T, _N>>,
                typename vec<_T, _N>::value_type,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::bit_or <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            typename cftal::vec<_T, _N>::value_type>
cftal::operator|(const vec<_T, _N>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::bit_or<vec<_T, _N>>,
                vec<_T, _N>,
                typename vec<_T, _N>::value_type>(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_or <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R> >
cftal::operator|(const vec<_T, _N>& a,
                 const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    return expr<op::bit_or<vec<_T, _N>>,
                vec<_T, _N>,
                expr<_OP<vec<_T, _N>>, _L, _R> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_or <cftal::vec<_T, _N>>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R>,
            cftal::vec<_T, _N> >
cftal::operator|(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
                 const vec<_T, _N>& b)
{
    return expr<op::bit_or<vec<_T, _N>>,
                expr<_OP<vec<_T, _N>>, _L, _R>,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_or <cftal::vec<_T, _N>>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R> >
cftal::operator|(const typename vec<_T, _N>::value_type& a,
                 const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    return expr<op::bit_or<vec<_T, _N>>,
                typename vec<_T, _N>::value_type,
                expr<_OP<vec<_T, _N>>, _L, _R> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_or <cftal::vec<_T, _N>>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R>,
            typename cftal::vec<_T, _N>::value_type >
cftal::operator|(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::bit_or<vec<_T, _N>>,
                expr<_OP<vec<_T, _N>>, _L, _R>,
                typename vec<_T, _N>::value_type >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP1,
          class _L1, class _R1,
          template <typename _T2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::bit_or <cftal::vec<_T, _N>>,
            cftal::expr<_OP1<cftal::vec<_T, _N>>, _L1, _R1>,
            cftal::expr<_OP2<cftal::vec<_T, _N>>, _L2, _R2> >
cftal::operator|(const expr<_OP1<vec<_T, _N>>, _L1, _R1>& a,
                 const expr<_OP2<vec<_T, _N>>, _L2, _R2>& b)
{
    return expr<op::bit_or<vec<_T, _N>>,
                expr<_OP1<vec<_T, _N>>, _L1, _R1>,
                expr<_OP2<vec<_T, _N>>, _L2, _R2> >(a, b);
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>&
cftal::operator|=(vec<_T, _N>& a,
                  const vec<_T, _N>& b)
{
    a = a | b;
    return a;
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>&
cftal::operator|=(vec<_T, _N>& a,
                  const typename vec<_T, _N>::value_type& b)
{
    a = a | b;
    return a;
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::vec<_T, _N>&
cftal::operator|=(vec<_T, _N>& a,
                  const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    a = a | b;
    return a;
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::bit_and <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            cftal::vec<_T, _N> >
cftal::operator&(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return expr<op:: bit_and<vec<_T, _N>>,
                vec<_T, _N>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::bit_and <cftal::vec<_T, _N>>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::vec<_T, _N> >
cftal::operator&(const typename vec<_T, _N>::value_type& a,
                 const vec<_T, _N>& b)
{
    return expr<op::bit_and<vec<_T, _N>>,
                typename vec<_T, _N>::value_type,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::bit_and <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            typename cftal::vec<_T, _N>::value_type>
cftal::operator&(const vec<_T, _N>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::bit_and<vec<_T, _N>>,
                vec<_T, _N>,
                typename vec<_T, _N>::value_type>(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_and <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R> >
cftal::operator&(const vec<_T, _N>& a,
                 const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    return expr<op::bit_and<vec<_T, _N>>,
                vec<_T, _N>,
                expr<_OP<vec<_T, _N>>, _L, _R> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_and <cftal::vec<_T, _N>>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R>,
            cftal::vec<_T, _N> >
cftal::operator&(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
                 const vec<_T, _N>& b)
{
    return expr<op::bit_and<vec<_T, _N>>,
                expr<_OP<vec<_T, _N>>, _L, _R>,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_and <cftal::vec<_T, _N>>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R> >
cftal::operator&(const typename vec<_T, _N>::value_type& a,
                 const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    return expr<op::bit_and<vec<_T, _N>>,
                typename vec<_T, _N>::value_type,
                expr<_OP<vec<_T, _N>>, _L, _R> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_and <cftal::vec<_T, _N>>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R>,
            typename cftal::vec<_T, _N>::value_type >
cftal::operator&(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::bit_and<vec<_T, _N>>,
                expr<_OP<vec<_T, _N>>, _L, _R>,
                typename vec<_T, _N>::value_type >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP1,
          class _L1, class _R1,
          template <typename _T2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::bit_and <cftal::vec<_T, _N>>,
            cftal::expr<_OP1<cftal::vec<_T, _N>>, _L1, _R1>,
            cftal::expr<_OP2<cftal::vec<_T, _N>>, _L2, _R2> >
cftal::operator&(const expr<_OP1<vec<_T, _N>>, _L1, _R1>& a,
                 const expr<_OP2<vec<_T, _N>>, _L2, _R2>& b)
{
    return expr<op::bit_and<vec<_T, _N>>,
                expr<_OP1<vec<_T, _N>>, _L1, _R1>,
                expr<_OP2<vec<_T, _N>>, _L2, _R2> >(a, b);
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>&
cftal::operator&=(vec<_T, _N>& a,
                  const vec<_T, _N>& b)
{
    a = a & b;
    return a;
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>&
cftal::operator&=(vec<_T, _N>& a,
                  const typename vec<_T, _N>::value_type& b)
{
    a = a & b;
    return a;
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::vec<_T, _N>&
cftal::operator&=(vec<_T, _N>& a,
                  const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    a = a & b;
    return a;
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::bit_xor <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            cftal::vec<_T, _N> >
cftal::operator^(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return expr<op:: bit_xor<vec<_T, _N>>,
                vec<_T, _N>,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::bit_xor <cftal::vec<_T, _N>>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::vec<_T, _N> >
cftal::operator^(const typename vec<_T, _N>::value_type& a,
                 const vec<_T, _N>& b)
{
    return expr<op::bit_xor<vec<_T, _N>>,
                typename vec<_T, _N>::value_type,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::bit_xor <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            typename cftal::vec<_T, _N>::value_type>
cftal::operator^(const vec<_T, _N>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::bit_xor<vec<_T, _N>>,
                vec<_T, _N>,
                typename vec<_T, _N>::value_type>(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_xor <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R> >
cftal::operator^(const vec<_T, _N>& a,
                 const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    return expr<op::bit_xor<vec<_T, _N>>,
                vec<_T, _N>,
                expr<_OP<vec<_T, _N>>, _L, _R> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_xor <cftal::vec<_T, _N>>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R>,
            cftal::vec<_T, _N> >
cftal::operator^(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
                 const vec<_T, _N>& b)
{
    return expr<op::bit_xor<vec<_T, _N>>,
                expr<_OP<vec<_T, _N>>, _L, _R>,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_xor <cftal::vec<_T, _N>>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R> >
cftal::operator^(const typename vec<_T, _N>::value_type& a,
                 const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    return expr<op::bit_xor<vec<_T, _N>>,
                typename vec<_T, _N>::value_type,
                expr<_OP<vec<_T, _N>>, _L, _R> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_xor <cftal::vec<_T, _N>>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R>,
            typename cftal::vec<_T, _N>::value_type >
cftal::operator^(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::bit_xor<vec<_T, _N>>,
                expr<_OP<vec<_T, _N>>, _L, _R>,
                typename vec<_T, _N>::value_type >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP1,
          class _L1, class _R1,
          template <typename _T2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::bit_xor <cftal::vec<_T, _N>>,
            cftal::expr<_OP1<cftal::vec<_T, _N>>, _L1, _R1>,
            cftal::expr<_OP2<cftal::vec<_T, _N>>, _L2, _R2> >
cftal::operator^(const expr<_OP1<vec<_T, _N>>, _L1, _R1>& a,
                 const expr<_OP2<vec<_T, _N>>, _L2, _R2>& b)
{
    return expr<op::bit_xor<vec<_T, _N>>,
                expr<_OP1<vec<_T, _N>>, _L1, _R1>,
                expr<_OP2<vec<_T, _N>>, _L2, _R2> >(a, b);
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>&
cftal::operator^=(vec<_T, _N>& a,
                  const vec<_T, _N>& b)
{
    a = a ^ b;
    return a;
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>&
cftal::operator^=(vec<_T, _N>& a,
                  const typename vec<_T, _N>::value_type& b)
{
    a = a ^ b;
    return a;
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::vec<_T, _N>&
cftal::operator^=(vec<_T, _N>& a,
                  const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    a = a ^ b;
    return a;
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::vshl <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            cftal::vec<_T, _N> >
cftal::operator<<(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return expr<op:: vshl<vec<_T, _N>>,
                vec<_T, _N>,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::vshl <cftal::vec<_T, _N>>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::vec<_T, _N> >
cftal::operator<<(const typename vec<_T, _N>::value_type& a,
                  const vec<_T, _N>& b)
{
    return expr<op::vshl<vec<_T, _N>>,
                typename vec<_T, _N>::value_type,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::vshl <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R> >
cftal::operator<<(const vec<_T, _N>& a,
                  const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    return expr<op::vshl<vec<_T, _N>>,
                vec<_T, _N>,
                expr<_OP<vec<_T, _N>>, _L, _R> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::vshl <cftal::vec<_T, _N>>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R>,
            cftal::vec<_T, _N> >
cftal::operator<<(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
                  const vec<_T, _N>& b)
{
    return expr<op::vshl<vec<_T, _N>>,
                expr<_OP<vec<_T, _N>>, _L, _R>,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::vshl <cftal::vec<_T, _N>>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R> >
cftal::operator<<(const typename vec<_T, _N>::value_type& a,
                  const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    return expr<op::vshl<vec<_T, _N>>,
                typename vec<_T, _N>::value_type,
                expr<_OP<vec<_T, _N>>, _L, _R> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP1,
          class _L1, class _R1,
          template <typename _T2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::vshl <cftal::vec<_T, _N>>,
            cftal::expr<_OP1<cftal::vec<_T, _N>>, _L1, _R1>,
            cftal::expr<_OP2<cftal::vec<_T, _N>>, _L2, _R2> >
cftal::operator<<(const expr<_OP1<vec<_T, _N>>, _L1, _R1>& a,
                  const expr<_OP2<vec<_T, _N>>, _L2, _R2>& b)
{
    return expr<op::vshl<vec<_T, _N>>,
                expr<_OP1<vec<_T, _N>>, _L1, _R1>,
                expr<_OP2<vec<_T, _N>>, _L2, _R2> >(a, b);
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>&
cftal::operator<<=(vec<_T, _N>& a,
                   const vec<_T, _N>& b)
{
    a = a << b;
    return a;
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::vec<_T, _N>&
cftal::operator<<=(vec<_T, _N>& a,
                   const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    a = a << b;
    return a;
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::vshr <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            cftal::vec<_T, _N> >
cftal::operator>>(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return expr<op:: vshr<vec<_T, _N>>,
                vec<_T, _N>,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::vshr <cftal::vec<_T, _N>>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::vec<_T, _N> >
cftal::operator>>(const typename vec<_T, _N>::value_type& a,
                  const vec<_T, _N>& b)
{
    return expr<op::vshr<vec<_T, _N>>,
                typename vec<_T, _N>::value_type,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::vshr <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R> >
cftal::operator>>(const vec<_T, _N>& a,
                  const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    return expr<op::vshr<vec<_T, _N>>,
                vec<_T, _N>,
                expr<_OP<vec<_T, _N>>, _L, _R> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::vshr <cftal::vec<_T, _N>>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R>,
            cftal::vec<_T, _N> >
cftal::operator>>(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
                  const vec<_T, _N>& b)
{
    return expr<op::vshr<vec<_T, _N>>,
                expr<_OP<vec<_T, _N>>, _L, _R>,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::vshr <cftal::vec<_T, _N>>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R> >
cftal::operator>>(const typename vec<_T, _N>::value_type& a,
                  const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    return expr<op::vshr<vec<_T, _N>>,
                typename vec<_T, _N>::value_type,
                expr<_OP<vec<_T, _N>>, _L, _R> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP1,
          class _L1, class _R1,
          template <typename _T2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::vshr <cftal::vec<_T, _N>>,
            cftal::expr<_OP1<cftal::vec<_T, _N>>, _L1, _R1>,
            cftal::expr<_OP2<cftal::vec<_T, _N>>, _L2, _R2> >
cftal::operator>>(const expr<_OP1<vec<_T, _N>>, _L1, _R1>& a,
                  const expr<_OP2<vec<_T, _N>>, _L2, _R2>& b)
{
    return expr<op::vshr<vec<_T, _N>>,
                expr<_OP1<vec<_T, _N>>, _L1, _R1>,
                expr<_OP2<vec<_T, _N>>, _L2, _R2> >(a, b);
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>&
cftal::operator>>=(vec<_T, _N>& a,
                   const vec<_T, _N>& b)
{
    a = a >> b;
    return a;
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::vec<_T, _N>&
cftal::operator>>=(vec<_T, _N>& a,
                   const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    a = a >> b;
    return a;
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op:: shl<cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            unsigned>
cftal::operator<<(const vec<_T, _N>& v, unsigned s)
{
    return expr<op:: shl<vec<_T, _N>>,
                vec<_T, _N>, unsigned>(v, s);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op:: shl<cftal::vec<_T, _N>>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R>,
            unsigned>
cftal::operator<<(const expr<_OP<vec<_T, _N>>, _L, _R>& e,
                  unsigned s)
{
    return expr<op:: shl<vec<_T, _N>>,
                expr<_OP<vec<_T, _N>>, _L, _R>,
                unsigned>(e, s);
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>&
cftal::operator<<=(vec<_T, _N>& v, unsigned s)
{
    v = v << s;
    return v;
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op:: shr<cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            unsigned>
cftal::operator>>(const vec<_T, _N>& v, unsigned s)
{
    return expr<op:: shr<vec<_T, _N>>,
                vec<_T, _N>, unsigned>(v, s);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op:: shr<cftal::vec<_T, _N>>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R>,
            unsigned>
cftal::operator>>(const expr<_OP<vec<_T, _N>>, _L, _R>& e,
                  unsigned s)
{
    return expr<op:: shr<vec<_T, _N>>,
                expr<_OP<vec<_T, _N>>, _L, _R>,
                unsigned>(e, s);
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>&
cftal::operator>>=(vec<_T, _N>& v, unsigned s)
{
    v = v >> s;
    return v;
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op:: neg <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>, void>
cftal::operator-(const vec<_T, _N>& v)
{
    return expr<op:: neg <vec<_T, _N>>,
                vec<_T, _N>, void>(v);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          typename _L, typename _R>
cftal::expr<cftal::op:: neg<cftal::vec<_T, _N>>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R>,
            void>
cftal::operator-(const expr<_OP<vec<_T, _N>>, _L, _R>& v)
{
    return expr<op:: neg<vec<_T, _N>>,
                expr<_OP<vec<_T, _N>>, _L, _R>,
                void>(v);
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::add <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            cftal::vec<_T, _N> >
cftal::operator+(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return expr<op:: add<vec<_T, _N>>,
                vec<_T, _N>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::add <cftal::vec<_T, _N>>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::vec<_T, _N> >
cftal::operator+(const typename vec<_T, _N>::value_type& a,
                 const vec<_T, _N>& b)
{
    return expr<op::add<vec<_T, _N>>,
                typename vec<_T, _N>::value_type,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::add <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            typename cftal::vec<_T, _N>::value_type>
cftal::operator+(const vec<_T, _N>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::add<vec<_T, _N>>,
                vec<_T, _N>,
                typename vec<_T, _N>::value_type>(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::add <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R> >
cftal::operator+(const vec<_T, _N>& a,
                 const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    return expr<op::add<vec<_T, _N>>,
                vec<_T, _N>,
                expr<_OP<vec<_T, _N>>, _L, _R> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::add <cftal::vec<_T, _N>>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R>,
            cftal::vec<_T, _N> >
cftal::operator+(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
                 const vec<_T, _N>& b)
{
    return expr<op::add<vec<_T, _N>>,
                expr<_OP<vec<_T, _N>>, _L, _R>,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::add <cftal::vec<_T, _N>>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R> >
cftal::operator+(const typename vec<_T, _N>::value_type& a,
                 const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    return expr<op::add<vec<_T, _N>>,
                typename vec<_T, _N>::value_type,
                expr<_OP<vec<_T, _N>>, _L, _R> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::add <cftal::vec<_T, _N>>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R>,
            typename cftal::vec<_T, _N>::value_type >
cftal::operator+(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::add<vec<_T, _N>>,
                expr<_OP<vec<_T, _N>>, _L, _R>,
                typename vec<_T, _N>::value_type >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP1,
          class _L1, class _R1,
          template <typename _T2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::add <cftal::vec<_T, _N>>,
            cftal::expr<_OP1<cftal::vec<_T, _N>>, _L1, _R1>,
            cftal::expr<_OP2<cftal::vec<_T, _N>>, _L2, _R2> >
cftal::operator+(const expr<_OP1<vec<_T, _N>>, _L1, _R1>& a,
                 const expr<_OP2<vec<_T, _N>>, _L2, _R2>& b)
{
    return expr<op::add<vec<_T, _N>>,
                expr<_OP1<vec<_T, _N>>, _L1, _R1>,
                expr<_OP2<vec<_T, _N>>, _L2, _R2> >(a, b);
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>&
cftal::operator+=(vec<_T, _N>& a,
                  const vec<_T, _N>& b)
{
    a = a + b;
    return a;
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>&
cftal::operator+=(vec<_T, _N>& a,
                  const typename vec<_T, _N>::value_type& b)
{
    a = a + b;
    return a;
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::vec<_T, _N>&
cftal::operator+=(vec<_T, _N>& a,
                  const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    a = a + b;
    return a;
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::sub <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            cftal::vec<_T, _N> >
cftal::operator-(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return expr<op:: sub<vec<_T, _N>>,
                vec<_T, _N>,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::sub <cftal::vec<_T, _N>>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::vec<_T, _N> >
cftal::operator-(const typename vec<_T, _N>::value_type& a,
                 const vec<_T, _N>& b)
{
    return expr<op::sub<vec<_T, _N>>,
                typename vec<_T, _N>::value_type,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::sub <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            typename cftal::vec<_T, _N>::value_type>
cftal::operator-(const vec<_T, _N>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::sub<vec<_T, _N>>,
                vec<_T, _N>,
                typename vec<_T, _N>::value_type>(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::sub <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R> >
cftal::operator-(const vec<_T, _N>& a,
                 const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    return expr<op::sub<vec<_T, _N>>,
                vec<_T, _N>,
                expr<_OP<vec<_T, _N>>, _L, _R> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::sub <cftal::vec<_T, _N>>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R>,
            cftal::vec<_T, _N> >
cftal::operator-(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
                 const vec<_T, _N>& b)
{
    return expr<op::sub<vec<_T, _N>>,
                expr<_OP<vec<_T, _N>>, _L, _R>,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::sub <cftal::vec<_T, _N>>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R> >
cftal::operator-(const typename vec<_T, _N>::value_type& a,
                 const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    return expr<op::sub<vec<_T, _N>>,
                typename vec<_T, _N>::value_type,
                expr<_OP<vec<_T, _N>>, _L, _R> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::sub <cftal::vec<_T, _N>>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R>,
            typename cftal::vec<_T, _N>::value_type >
cftal::operator-(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::sub<vec<_T, _N>>,
                expr<_OP<vec<_T, _N>>, _L, _R>,
                typename vec<_T, _N>::value_type >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP1,
          class _L1, class _R1,
          template <typename _T2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::sub <cftal::vec<_T, _N>>,
            cftal::expr<_OP1<cftal::vec<_T, _N>>, _L1, _R1>,
            cftal::expr<_OP2<cftal::vec<_T, _N>>, _L2, _R2> >
cftal::operator-(const expr<_OP1<vec<_T, _N>>, _L1, _R1>& a,
                 const expr<_OP2<vec<_T, _N>>, _L2, _R2>& b)
{
    return expr<op::sub<vec<_T, _N>>,
                expr<_OP1<vec<_T, _N>>, _L1, _R1>,
                expr<_OP2<vec<_T, _N>>, _L2, _R2> >(a, b);
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>&
cftal::operator-=(vec<_T, _N>& a,
                  const vec<_T, _N>& b)
{
    a = a - b;
    return a;
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>&
cftal::operator-=(vec<_T, _N>& a,
                  const typename vec<_T, _N>::value_type& b)
{
    a = a - b;
    return a;
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::vec<_T, _N>&
cftal::operator-=(vec<_T, _N>& a,
                  const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    a = a - b;
    return a;
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::mul <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            cftal::vec<_T, _N> >
cftal::operator*(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return expr<op:: mul<vec<_T, _N>>,
                vec<_T, _N>,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::mul <cftal::vec<_T, _N>>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::vec<_T, _N> >
cftal::operator*(const typename vec<_T, _N>::value_type& a,
                 const vec<_T, _N>& b)
{
    return expr<op::mul<vec<_T, _N>>,
                typename vec<_T, _N>::value_type,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::mul <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            typename cftal::vec<_T, _N>::value_type>
cftal::operator*(const vec<_T, _N>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::mul<vec<_T, _N>>,
                vec<_T, _N>,
                typename vec<_T, _N>::value_type>(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::mul <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R> >
cftal::operator*(const vec<_T, _N>& a,
                 const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    return expr<op::mul<vec<_T, _N>>,
                vec<_T, _N>,
                expr<_OP<vec<_T, _N>>, _L, _R> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::mul <cftal::vec<_T, _N>>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R>,
            cftal::vec<_T, _N> >
cftal::operator*(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
                 const vec<_T, _N>& b)
{
    return expr<op::mul<vec<_T, _N>>,
                expr<_OP<vec<_T, _N>>, _L, _R>,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::mul <cftal::vec<_T, _N>>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R> >
cftal::operator*(const typename vec<_T, _N>::value_type& a,
                 const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    return expr<op::mul<vec<_T, _N>>,
                typename vec<_T, _N>::value_type,
                expr<_OP<vec<_T, _N>>, _L, _R> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::mul <cftal::vec<_T, _N>>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R>,
            typename cftal::vec<_T, _N>::value_type >
cftal::operator*(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::mul<vec<_T, _N>>,
                expr<_OP<vec<_T, _N>>, _L, _R>,
                typename vec<_T, _N>::value_type >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP1,
          class _L1, class _R1,
          template <typename _T2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::mul <cftal::vec<_T, _N>>,
            cftal::expr<_OP1<cftal::vec<_T, _N>>, _L1, _R1>,
            cftal::expr<_OP2<cftal::vec<_T, _N>>, _L2, _R2> >
cftal::operator*(const expr<_OP1<vec<_T, _N>>, _L1, _R1>& a,
                 const expr<_OP2<vec<_T, _N>>, _L2, _R2>& b)
{
    return expr<op::mul<vec<_T, _N>>,
                expr<_OP1<vec<_T, _N>>, _L1, _R1>,
                expr<_OP2<vec<_T, _N>>, _L2, _R2> >(a, b);
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>&
cftal::operator*=(vec<_T, _N>& a,
                  const vec<_T, _N>& b)
{
    a = a * b;
    return a;
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>&
cftal::operator*=(vec<_T, _N>& a,
                  const typename vec<_T, _N>::value_type& b)
{
    a = a * b;
    return a;
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::vec<_T, _N>&
cftal::operator*=(vec<_T, _N>& a,
                  const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    a = a * b;
    return a;
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::div <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            cftal::vec<_T, _N> >
cftal::operator/(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return expr<op:: div<vec<_T, _N>>,
                vec<_T, _N>,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::div <cftal::vec<_T, _N>>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::vec<_T, _N> >
cftal::operator/(const typename vec<_T, _N>::value_type& a,
                 const vec<_T, _N>& b)
{
    return expr<op::div<vec<_T, _N>>,
                typename vec<_T, _N>::value_type,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::div <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            typename cftal::vec<_T, _N>::value_type>
cftal::operator/(const vec<_T, _N>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::div<vec<_T, _N>>,
                vec<_T, _N>,
                typename vec<_T, _N>::value_type>(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::div <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R> >
cftal::operator/(const vec<_T, _N>& a,
                 const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    return expr<op::div<vec<_T, _N>>,
                vec<_T, _N>,
                expr<_OP<vec<_T, _N>>, _L, _R> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::div <cftal::vec<_T, _N>>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R>,
            cftal::vec<_T, _N> >
cftal::operator/(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
                 const vec<_T, _N>& b)
{
    return expr<op::div<vec<_T, _N>>,
                expr<_OP<vec<_T, _N>>, _L, _R>,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::div <cftal::vec<_T, _N>>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R> >
cftal::operator/(const typename vec<_T, _N>::value_type& a,
                 const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    return expr<op::div<vec<_T, _N>>,
                typename vec<_T, _N>::value_type,
                expr<_OP<vec<_T, _N>>, _L, _R> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::div <cftal::vec<_T, _N>>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R>,
            typename cftal::vec<_T, _N>::value_type >
cftal::operator/(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::div<vec<_T, _N>>,
                expr<_OP<vec<_T, _N>>, _L, _R>,
                typename vec<_T, _N>::value_type >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP1,
          class _L1, class _R1,
          template <typename _T2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::div <cftal::vec<_T, _N>>,
            cftal::expr<_OP1<cftal::vec<_T, _N>>, _L1, _R1>,
            cftal::expr<_OP2<cftal::vec<_T, _N>>, _L2, _R2> >
cftal::operator/(const expr<_OP1<vec<_T, _N>>, _L1, _R1>& a,
                 const expr<_OP2<vec<_T, _N>>, _L2, _R2>& b)
{
    return expr<op::div<vec<_T, _N>>,
                expr<_OP1<vec<_T, _N>>, _L1, _R1>,
                expr<_OP2<vec<_T, _N>>, _L2, _R2> >(a, b);
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>&
cftal::operator/=(vec<_T, _N>& a,
                  const vec<_T, _N>& b)
{
    a = a / b;
    return a;
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>&
cftal::operator/=(vec<_T, _N>& a,
                  const typename vec<_T, _N>::value_type& b)
{
    a = a / b;
    return a;
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::vec<_T, _N>&
cftal::operator/=(vec<_T, _N>& a,
                  const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    a = a / b;
    return a;
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::mod <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            cftal::vec<_T, _N> >
cftal::operator%(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return expr<op:: mod<vec<_T, _N>>,
                vec<_T, _N>,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::mod <cftal::vec<_T, _N>>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::vec<_T, _N> >
cftal::operator%(const typename vec<_T, _N>::value_type& a,
                 const vec<_T, _N>& b)
{
    return expr<op::mod<vec<_T, _N>>,
                typename vec<_T, _N>::value_type,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::mod <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            typename cftal::vec<_T, _N>::value_type>
cftal::operator%(const vec<_T, _N>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::mod<vec<_T, _N>>,
                vec<_T, _N>,
                typename vec<_T, _N>::value_type>(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::mod <cftal::vec<_T, _N>>,
            cftal::vec<_T, _N>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R> >
cftal::operator%(const vec<_T, _N>& a,
                 const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    return expr<op::mod<vec<_T, _N>>,
                vec<_T, _N>,
                expr<_OP<vec<_T, _N>>, _L, _R> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::mod <cftal::vec<_T, _N>>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R>,
            cftal::vec<_T, _N> >
cftal::operator%(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
                 const vec<_T, _N>& b)
{
    return expr<op::mod<vec<_T, _N>>,
                expr<_OP<vec<_T, _N>>, _L, _R>,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::mod <cftal::vec<_T, _N>>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R> >
cftal::operator%(const typename vec<_T, _N>::value_type& a,
                 const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    return expr<op::mod<vec<_T, _N>>,
                typename vec<_T, _N>::value_type,
                expr<_OP<vec<_T, _N>>, _L, _R> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::mod <cftal::vec<_T, _N>>,
            cftal::expr<_OP<cftal::vec<_T, _N>>, _L, _R>,
            typename cftal::vec<_T, _N>::value_type >
cftal::operator%(const expr<_OP<vec<_T, _N>>, _L, _R>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::mod<vec<_T, _N>>,
                expr<_OP<vec<_T, _N>>, _L, _R>,
                typename vec<_T, _N>::value_type >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP1,
          class _L1, class _R1,
          template <typename _T2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::mod <cftal::vec<_T, _N>>,
            cftal::expr<_OP1<cftal::vec<_T, _N>>, _L1, _R1>,
            cftal::expr<_OP2<cftal::vec<_T, _N>>, _L2, _R2> >
cftal::operator%(const expr<_OP1<vec<_T, _N>>, _L1, _R1>& a,
                 const expr<_OP2<vec<_T, _N>>, _L2, _R2>& b)
{
    return expr<op::mod<vec<_T, _N>>,
                expr<_OP1<vec<_T, _N>>, _L1, _R1>,
                expr<_OP2<vec<_T, _N>>, _L2, _R2> >(a, b);
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>&
cftal::operator%=(vec<_T, _N>& a,
                  const vec<_T, _N>& b)
{
    a = a % b;
    return a;
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>&
cftal::operator%=(vec<_T, _N>& a,
                  const typename vec<_T, _N>::value_type& b)
{
    a = a % b;
    return a;
}

template <typename _T, std::size_t _N,
          template <typename _T1> class _OP,
          class _L, class _R>
cftal::vec<_T, _N>&
cftal::operator%=(vec<_T, _N>& a,
                  const expr<_OP<vec<_T, _N>>, _L, _R>& b)
{
    a = a % b;
    return a;
}

// Local variables:
// mode: c++
// end:
#endif
