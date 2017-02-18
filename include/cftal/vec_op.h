//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
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

    namespace op {

        template <template <class _T,
                            std::size_t _N> class _OP,
                  typename _T, std::size_t _N,
                  typename _R>
        struct base {
            using full_type = vec<_T, _N>;
            using mask_type =
                typename vec<_T, _N>::mask_type;
            static
            _R
            v(const full_type& a, const full_type& b) {
                _R r(_OP<_T, _N/2>::v(low_half(a),
                                      low_half(b)),
                     _OP<_T, _N/2>::v(high_half(a),
                                      high_half(b)));
                return r;
            }
        };

        template <template <class _T,
                            std::size_t _N> class _OP,
                  typename _T, std::size_t _N>
        struct cmp :
            public base<_OP, _T, _N,
                        typename vec<_T, _N>::mask_type > {
        };

        template <template <class _T, std::size_t _N> class _OP,
                  typename _T, std::size_t _N>
        struct bin :
            public base<_OP, _T, _N, vec<_T, _N> > {
        };

        template <template <class _T, std::size_t _N> class _OP,
                  typename _T, std::size_t _N>
        struct unary {
            using full_type = vec<_T, _N>;
            static
            full_type
            v(const full_type& a) {
                return full_type(
                    _OP<_T, _N/2>::v(low_half(a)),
                    _OP<_T, _N/2>::v(high_half(a)));
            }
        };

        template <template <class _T, std::size_t _N> class _OP,
                  typename _T, std::size_t _N>
        struct ternary {
            using full_type = vec<_T, _N>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return full_type(
                    _OP<_T, _N/2>::v(low_half(a),
                                     low_half(b),
                                     low_half(c)),
                    _OP<_T, _N/2>::v(high_half(a),
                                     high_half(b),
                                     high_half(c)));
            }
        };

        // common comparison operations
        template <typename _T, std::size_t _N>
        struct lt : public cmp<lt, _T, _N> {};

        template <typename _T, std::size_t _N>
        struct le : public cmp<le, _T, _N> {};

        template <typename _T, std::size_t _N>
        struct eq : public cmp<eq, _T, _N> {};

        template <typename _T, std::size_t _N>
        struct ne : public cmp<ne, _T, _N> {};

        template <typename _T, std::size_t _N>
        struct ge : public cmp<ge, _T, _N> {};

        template <typename _T, std::size_t _N>
        struct gt : public cmp<gt, _T, _N> {};

        // arithmetic operations
        // +a
        template <typename _T, std::size_t _N>
        struct plus : public unary<plus, _T, _N> {};
        // -a
        template <typename _T, std::size_t _N>
        struct neg : public unary<neg, _T, _N> {};
        // a + b
        template <typename _T, std::size_t _N>
        struct add : public bin<add, _T, _N> {};
        // a - b
        template <typename _T, std::size_t _N>
        struct sub : public bin<sub, _T, _N> {};
        // a * b
        template <typename _T, std::size_t _N>
        struct mul : public bin<mul, _T, _N> {};
        // a / b
        template <typename _T, std::size_t _N>
        struct div : public bin<div, _T, _N> {};
        // a % b
        template <typename _T, std::size_t _N>
        struct mod : public bin<mod, _T, _N> {};

        // a*b + c
        template <typename _T, std::size_t _N>
        struct fma : public ternary<fma, _T, _N> {};
        // a*b -c
        template <typename _T, std::size_t _N>
        struct fms : public ternary<fms, _T, _N> {};
        // -a*b +c = (c-a*b)
        template <typename _T, std::size_t _N>
        struct fnma : public ternary<fnma, _T, _N> {};

        // bitwise logical operations
        template <typename _T, std::size_t _N>
        struct bit_or : public bin<bit_or, _T, _N> {};

        template <typename _T, std::size_t _N>
        struct bit_and : public bin<bit_and, _T, _N> {};

        template <typename _T, std::size_t _N>
        struct bit_xor : public bin<bit_xor, _T, _N> {};

        template <typename _T, std::size_t _N>
        struct bit_not : public unary<bit_not, _T, _N> {};

        // shift operators
        template <typename _T, std::size_t _N>
        struct shl : public bin<shl, _T, _N> {
            using full_type = vec<_T, _N>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                full_type r(shl<_T, _N/2>::v(low_half(a), s),
                            shl<_T, _N/2>::v(high_half(a), s));
                return r;
            }
        };

        template <typename _T, std::size_t _N>
        struct shr : public bin<shr, _T, _N> {
            using full_type = vec<_T, _N>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                full_type r(shr<_T, _N/2>::v(low_half(a), s),
                            shr<_T, _N/2>::v(high_half(a), s));
                return r;
            }
        };

        template <typename _T, std::size_t _N>
        struct vshl : public bin<vshl, _T, _N> {};

        template <typename _T, std::size_t _N>
        struct vshr : public bin<vshr, _T, _N> {};

    } // namespace op


    // a+ b*c
    template <typename _T, std::size_t _N,
              class _L1, class _L2, class _R2>
    inline
    vec<_T, _N>
    eval(const expr<op::add<_T, _N>,
         _L1,
         expr<op::mul<_T, _N>, _L2, _R2> >& e) {
        return op::fma<_T, _N>::v(eval(e._r._l),
                                  eval(e._r._r),
                                  eval(e._l));
    }
    // a*b +c
    template <typename _T, std::size_t _N,
              class _L1, class _R1, class _R2>
    inline
    vec<_T, _N>
    eval(const expr<op::add<_T, _N>,
         expr<op::mul<_T, _N>, _L1, _R1>,
         _R2>& e) {
        return op::fma<_T, _N>::v(eval(e._l._l),
                                  eval(e._l._r),
                                  eval(e._r));
    }

    // a*b +c*d
    template <typename _T, std::size_t _N,
              class _L1, class _R1, class _L2, class _R2>
    inline
    vec<_T, _N>
    eval(const expr<op::add<_T, _N>,
         expr<op::mul<_T, _N>, _L1, _R1>,
         expr<op::mul<_T, _N>, _L2, _R2> >& e) {
        return op::fma<_T, _N>::v(eval(e._r._l),
                                  eval(e._r._r),
                                  eval(e._l));
    }

    // a*b -c
    template <typename _T, std::size_t _N,
              class _L1, class _R1, class _R2>
    inline
    vec<_T, _N>
    eval(const expr<op::sub<_T, _N>,
         expr<op::mul<_T, _N>, _L1, _R1>,
         _R2>& e) {
        return op::fms<_T, _N>::v(eval(e._l._l),
                                  eval(e._l._r),
                                  eval(e._r));
    }
    // -a*b +c = c- a* b;
    template <typename _T, std::size_t _N,
              class _L1, class _L2, class _R2>
    inline
    vec<_T, _N>
    eval(const expr<op::sub<_T, _N>,
         _L1,
         expr<op::mul<_T, _N>, _L2, _R2> >& e) {
        return op::fnma<_T, _N>::v(eval(e._r._l),
                                   eval(e._r._r),
                                   eval(e._l));
    }

    // a*b - c*d
    template <typename _T, std::size_t _N,
              class _L1, class _R1, class _L2, class _R2>
    inline
    vec<_T, _N>
    eval(const expr<op::sub<_T, _N>,
         expr<op::mul<_T, _N>, _L1, _R1>,
         expr<op::mul<_T, _N>, _L2, _R2> >& e) {
#if 1
        return op::fnma<_T, _N>::v(eval(e._r._l),
                                   eval(e._r._r),
                                   eval(e._l));
#else
        return op::fms<_T, _N>::v(eval(e._l._l),
                                  eval(e._l._r),
                                  eval(e._r));
#endif
    }

    // a + -b = a - b
    template <typename _T, std::size_t _N,
              class _L, class _R>
    inline
    vec<_T, _N>
    eval(const expr<op::add<_T, _N>,
         _L,
         expr<op::neg<_T, _N>, _R, void> >& e) {
        return op::sub<_T, _N>::v(eval(e._l),
                                  eval(e._r._l));
    }

    // -a + b = b - a
    template <typename _T, std::size_t _N,
              class _L, class _R>
    inline
    vec<_T, _N>
    eval(const expr<op::add<_T, _N>,
         expr<op::neg<_T, _N>, _L, void>,
         _R>& e) {
        return op::sub<_T, _N>::v(eval(e._r._l),
                                  eval(e._l));
    }

    // a - -b = a + b
    template <typename _T, std::size_t _N,
              class _L, class _R>
    inline
    vec<_T, _N>
    eval(const expr<op::sub<_T, _N>,
         _L,
         expr<op::neg<_T, _N>, _R, void> >& e) {
        return op::add<_T, _N>::v(eval(e._l),
                                  eval(e._r._l));
    }

    // unary plus operator
    template <class _T>
    inline
    const _T& operator+(const _T& v) {
        return v;
    }

    // not v
    template <typename _T, std::size_t _N>
    expr<op:: bit_not<_T, _N>,
         vec<_T, _N>, void>
    operator~(const vec<_T, _N>& v);

    // not expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              typename _L, typename _R>
    expr<op:: bit_not <_T, _N>,
         expr<_OP<_T, _N>, _L, _R>, void>
    operator~(const expr<_OP<_T, _N>, _L, _R>& r);

    // bit_or operator: v, v
    template <typename _T, std::size_t _N>
    expr<op:: bit_or <_T, _N>,
         vec<_T, _N>,
         vec<_T, _N> >
    operator|(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // bit_or operator: value_type, v
    template <typename _T, std::size_t _N>
    expr<op:: bit_or <_T, _N>,
         typename vec<_T, _N>::value_type,
         vec<_T, _N> >
    operator|(const typename vec<_T, _N>::value_type& a,
              const vec<_T, _N>& b);

    // bit_or operator: v, value_type
    template <typename _T, std::size_t _N>
    expr<op:: bit_or <_T, _N>,
         vec<_T, _N>,
         typename vec<_T, _N>::value_type>
    operator|(const vec<_T, _N>& a,
              const typename vec<_T, _N>::value_type& b);

    // bit_or operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: bit_or <_T, _N>,
         vec<_T, _N>,
         expr<_OP<_T, _N>, _L, _R> >
    operator|(const vec<_T, _N>& a,
              const expr<_OP<_T, _N>, _L, _R>& b);

    // bit_or operator: expr, v
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: bit_or <_T, _N>,
         expr<_OP<_T, _N>, _L, _R>,
         vec<_T, _N> >
    operator|(const expr<_OP<_T, _N>, _L, _R>& a,
              const vec<_T, _N>& b);

    // bit_or operator: value_type, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: bit_or <_T, _N>,
         typename vec<_T, _N>::value_type,
         expr<_OP<_T, _N>, _L, _R> >
    operator|(const typename vec<_T, _N>::value_type& a,
              const expr<_OP<_T, _N>, _L, _R>& b);

    // bit_or operator: expr, value_type
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: bit_or <_T, _N>,
         expr<_OP<_T, _N>, _L, _R>,
         typename vec<_T, _N>::value_type >
    operator|(const expr<_OP<_T, _N>, _L, _R>& a,
              const typename vec<_T, _N>::value_type& b);

    // bit_or operator: expr, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP1,
              class _L1, class _R1,
              template <typename _T2, std::size_t _N2> class _OP2,
              class _L2, class _R2>
    expr<op:: bit_or <_T, _N>,
         expr<_OP1<_T, _N>, _L1, _R1>,
         expr<_OP2<_T, _N>, _L2, _R2> >
    operator|(const expr<_OP1<_T, _N>, _L1, _R1>& a,
              const expr<_OP2<_T, _N>, _L2, _R2>& b);

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
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    vec<_T, _N>&
    operator|=(vec<_T, _N>& a,
               const expr<_OP<_T, _N>, _L, _R>& b);

    // bit_and operator: v, v
    template <typename _T, std::size_t _N>
    expr<op:: bit_and <_T, _N>,
         vec<_T, _N>,
         vec<_T, _N> >
    operator&(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // bit_and operator: value_type, v
    template <typename _T, std::size_t _N>
    expr<op:: bit_and <_T, _N>,
         typename vec<_T, _N>::value_type,
         vec<_T, _N> >
    operator&(const typename vec<_T, _N>::value_type& a,
              const vec<_T, _N>& b);

    // bit_and operator: v, value_type
    template <typename _T, std::size_t _N>
    expr<op:: bit_and <_T, _N>,
         vec<_T, _N>,
         typename vec<_T, _N>::value_type>
    operator&(const vec<_T, _N>& a,
              const typename vec<_T, _N>::value_type& b);

    // bit_and operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: bit_and <_T, _N>,
         vec<_T, _N>,
         expr<_OP<_T, _N>, _L, _R> >
    operator&(const vec<_T, _N>& a,
              const expr<_OP<_T, _N>, _L, _R>& b);

    // bit_and operator: expr, v
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: bit_and <_T, _N>,
         expr<_OP<_T, _N>, _L, _R>,
         vec<_T, _N> >
    operator&(const expr<_OP<_T, _N>, _L, _R>& a,
              const vec<_T, _N>& b);

    // bit_and operator: value_type, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: bit_and <_T, _N>,
         typename vec<_T, _N>::value_type,
         expr<_OP<_T, _N>, _L, _R> >
    operator&(const typename vec<_T, _N>::value_type& a,
              const expr<_OP<_T, _N>, _L, _R>& b);

    // bit_and operator: expr, value_type
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: bit_and <_T, _N>,
         expr<_OP<_T, _N>, _L, _R>,
         typename vec<_T, _N>::value_type >
    operator&(const expr<_OP<_T, _N>, _L, _R>& a,
              const typename vec<_T, _N>::value_type& b);

    // bit_and operator: expr, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP1,
              class _L1, class _R1,
              template <typename _T2, std::size_t _N2> class _OP2,
              class _L2, class _R2>
    expr<op:: bit_and <_T, _N>,
         expr<_OP1<_T, _N>, _L1, _R1>,
         expr<_OP2<_T, _N>, _L2, _R2> >
    operator&(const expr<_OP1<_T, _N>, _L1, _R1>& a,
              const expr<_OP2<_T, _N>, _L2, _R2>& b);

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
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    vec<_T, _N>&
    operator&=(vec<_T, _N>& a,
               const expr<_OP<_T, _N>, _L, _R>& b);

    // bit_xor operator: v, v
    template <typename _T, std::size_t _N>
    expr<op:: bit_xor <_T, _N>,
         vec<_T, _N>,
         vec<_T, _N> >
    operator^(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // bit_xor operator: value_type, v
    template <typename _T, std::size_t _N>
    expr<op:: bit_xor <_T, _N>,
         typename vec<_T, _N>::value_type,
         vec<_T, _N> >
    operator^(const typename vec<_T, _N>::value_type& a,
              const vec<_T, _N>& b);

    // bit_xor operator: v, value_type
    template <typename _T, std::size_t _N>
    expr<op:: bit_xor <_T, _N>,
         vec<_T, _N>,
         typename vec<_T, _N>::value_type>
    operator^(const vec<_T, _N>& a,
              const typename vec<_T, _N>::value_type& b);

    // bit_xor operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: bit_xor <_T, _N>,
         vec<_T, _N>,
         expr<_OP<_T, _N>, _L, _R> >
    operator^(const vec<_T, _N>& a,
              const expr<_OP<_T, _N>, _L, _R>& b);

    // bit_xor operator: expr, v
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: bit_xor <_T, _N>,
         expr<_OP<_T, _N>, _L, _R>,
         vec<_T, _N> >
    operator^(const expr<_OP<_T, _N>, _L, _R>& a,
              const vec<_T, _N>& b);

    // bit_xor operator: value_type, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: bit_xor <_T, _N>,
         typename vec<_T, _N>::value_type,
         expr<_OP<_T, _N>, _L, _R> >
    operator^(const typename vec<_T, _N>::value_type& a,
              const expr<_OP<_T, _N>, _L, _R>& b);

    // bit_xor operator: expr, value_type
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: bit_xor <_T, _N>,
         expr<_OP<_T, _N>, _L, _R>,
         typename vec<_T, _N>::value_type >
    operator^(const expr<_OP<_T, _N>, _L, _R>& a,
              const typename vec<_T, _N>::value_type& b);

    // bit_xor operator: expr, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP1,
              class _L1, class _R1,
              template <typename _T2, std::size_t _N2> class _OP2,
              class _L2, class _R2>
    expr<op:: bit_xor <_T, _N>,
         expr<_OP1<_T, _N>, _L1, _R1>,
         expr<_OP2<_T, _N>, _L2, _R2> >
    operator^(const expr<_OP1<_T, _N>, _L1, _R1>& a,
              const expr<_OP2<_T, _N>, _L2, _R2>& b);

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
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    vec<_T, _N>&
    operator^=(vec<_T, _N>& a,
               const expr<_OP<_T, _N>, _L, _R>& b);

    // vshl operator: v, v
    template <typename _T, std::size_t _N>
    expr<op:: vshl <_T, _N>,
         vec<_T, _N>,
         vec<_T, _N> >
    operator<<(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // vshl operator: value_type, v
    template <typename _T, std::size_t _N>
    expr<op:: vshl <_T, _N>,
         typename vec<_T, _N>::value_type,
         vec<_T, _N> >
    operator<<(const typename vec<_T, _N>::value_type& a,
               const vec<_T, _N>& b);
    
    // vshl operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: vshl <_T, _N>,
         vec<_T, _N>,
         expr<_OP<_T, _N>, _L, _R> >
    operator<<(const vec<_T, _N>& a,
              const expr<_OP<_T, _N>, _L, _R>& b);

    // vshl operator: expr, v
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: vshl <_T, _N>,
         expr<_OP<_T, _N>, _L, _R>,
         vec<_T, _N> >
    operator<<(const expr<_OP<_T, _N>, _L, _R>& a,
              const vec<_T, _N>& b);

    // vshl operator: value_type, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: vshl <_T, _N>,
         typename vec<_T, _N>::value_type,
         expr<_OP<_T, _N>, _L, _R> >
    operator<<(const typename vec<_T, _N>::value_type& a,
               const expr<_OP<_T, _N>, _L, _R>& b);

    // vshl operator: expr, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP1,
              class _L1, class _R1,
              template <typename _T2, std::size_t _N2> class _OP2,
              class _L2, class _R2>
    expr<op:: vshl <_T, _N>,
         expr<_OP1<_T, _N>, _L1, _R1>,
         expr<_OP2<_T, _N>, _L2, _R2> >
    operator<<(const expr<_OP1<_T, _N>, _L1, _R1>& a,
              const expr<_OP2<_T, _N>, _L2, _R2>& b);

    // self vshl operator: v, v
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator<<=(vec<_T, _N>& a,
               const vec<_T, _N>& b);

    // self vshl operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    vec<_T, _N>&
    operator<<=(vec<_T, _N>& a,
               const expr<_OP<_T, _N>, _L, _R>& b);

    // vshr operator: v, v
    template <typename _T, std::size_t _N>
    expr<op:: vshr <_T, _N>,
         vec<_T, _N>,
         vec<_T, _N> >
    operator>>(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // vshr operator: value_type, v
    template <typename _T, std::size_t _N>
    expr<op:: vshr <_T, _N>,
         typename vec<_T, _N>::value_type,
         vec<_T, _N> >
    operator>>(const typename vec<_T, _N>::value_type& a,
              const vec<_T, _N>& b);

    // vshr operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: vshr <_T, _N>,
         vec<_T, _N>,
         expr<_OP<_T, _N>, _L, _R> >
    operator>>(const vec<_T, _N>& a,
              const expr<_OP<_T, _N>, _L, _R>& b);

    // vshr operator: expr, v
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: vshr <_T, _N>,
         expr<_OP<_T, _N>, _L, _R>,
         vec<_T, _N> >
    operator>>(const expr<_OP<_T, _N>, _L, _R>& a,
              const vec<_T, _N>& b);

    // vshr operator: value_type, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: vshr <_T, _N>,
         typename vec<_T, _N>::value_type,
         expr<_OP<_T, _N>, _L, _R> >
    operator>>(const typename vec<_T, _N>::value_type& a,
              const expr<_OP<_T, _N>, _L, _R>& b);

    // vshr operator: expr, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP1,
              class _L1, class _R1,
              template <typename _T2, std::size_t _N2> class _OP2,
              class _L2, class _R2>
    expr<op:: vshr <_T, _N>,
         expr<_OP1<_T, _N>, _L1, _R1>,
         expr<_OP2<_T, _N>, _L2, _R2> >
    operator>>(const expr<_OP1<_T, _N>, _L1, _R1>& a,
              const expr<_OP2<_T, _N>, _L2, _R2>& b);

    // self vshr operator: v, v
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator>>=(vec<_T, _N>& a,
               const vec<_T, _N>& b);

    // self vshr operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    vec<_T, _N>&
    operator>>=(vec<_T, _N>& a,
               const expr<_OP<_T, _N>, _L, _R>& b);

    
    // left shift v unsigned
    template <typename _T, std::size_t _N>
    expr<op:: shl<_T, _N>,
         vec<_T, _N>, unsigned >
    operator <<(const vec<_T, _N>& v, unsigned s);
    // left shift expr unsigned
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: shl<_T, _N>,
         expr<_OP<_T, _N>, _L, _R>, unsigned>
    operator <<(const expr<_OP<_T, _N>, _L, _R>& v,
                unsigned s);
    // self left shift
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator <<=(vec<_T, _N>& v, unsigned s);

    // right shift v unsigned
    template <typename _T, std::size_t _N>
    expr<op:: shr<_T, _N>,
         vec<_T, _N>, unsigned >
    operator >>(const vec<_T, _N>& v, unsigned s);
    // right shift expr unsigned
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: shr<_T, _N>,
         expr<_OP<_T, _N>, _L, _R>, unsigned>
    operator >>(const expr<_OP<_T, _N>, _L, _R>& v,
                unsigned s);
    // self right shift
    template <typename _T, std::size_t _N>
    vec<_T, _N>&
    operator >>=(vec<_T, _N>& v, unsigned s);
    
    // unary minus: v
    template <typename _T, std::size_t _N>
    expr<op:: neg<_T, _N>,
         vec<_T, _N>, void>
    operator-(const vec<_T, _N>& v);

    // unary minus: expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              typename _L, typename _R>
    expr<op:: neg<_T, _N>,
         expr<_OP<_T, _N>, _L, _R>, void>
    operator-(const expr<_OP<_T, _N>, _L, _R>& r);

    // add operator: v, v
    template <typename _T, std::size_t _N>
    expr<op:: add <_T, _N>,
         vec<_T, _N>,
         vec<_T, _N> >
    operator+(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // add operator: value_type, v
    template <typename _T, std::size_t _N>
    expr<op:: add <_T, _N>,
         typename vec<_T, _N>::value_type,
         vec<_T, _N> >
    operator+(const typename vec<_T, _N>::value_type& a,
              const vec<_T, _N>& b);

    // add operator: v, value_type
    template <typename _T, std::size_t _N>
    expr<op:: add <_T, _N>,
         vec<_T, _N>,
         typename vec<_T, _N>::value_type>
    operator+(const vec<_T, _N>& a,
              const typename vec<_T, _N>::value_type& b);

    // add operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: add <_T, _N>,
         vec<_T, _N>,
         expr<_OP<_T, _N>, _L, _R> >
    operator+(const vec<_T, _N>& a,
              const expr<_OP<_T, _N>, _L, _R>& b);

    // add operator: expr, v
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: add <_T, _N>,
         expr<_OP<_T, _N>, _L, _R>,
         vec<_T, _N> >
    operator+(const expr<_OP<_T, _N>, _L, _R>& a,
              const vec<_T, _N>& b);

    // add operator: value_type, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: add <_T, _N>,
         typename vec<_T, _N>::value_type,
         expr<_OP<_T, _N>, _L, _R> >
    operator+(const typename vec<_T, _N>::value_type& a,
              const expr<_OP<_T, _N>, _L, _R>& b);

    // add operator: expr, value_type
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: add <_T, _N>,
         expr<_OP<_T, _N>, _L, _R>,
         typename vec<_T, _N>::value_type >
    operator+(const expr<_OP<_T, _N>, _L, _R>& a,
              const typename vec<_T, _N>::value_type& b);

    // add operator: expr, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP1,
              class _L1, class _R1,
              template <typename _T2, std::size_t _N2> class _OP2,
              class _L2, class _R2>
    expr<op:: add <_T, _N>,
         expr<_OP1<_T, _N>, _L1, _R1>,
         expr<_OP2<_T, _N>, _L2, _R2> >
    operator+(const expr<_OP1<_T, _N>, _L1, _R1>& a,
              const expr<_OP2<_T, _N>, _L2, _R2>& b);

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
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    vec<_T, _N>&
    operator+=(vec<_T, _N>& a,
               const expr<_OP<_T, _N>, _L, _R>& b);

    // sub operator: v, v
    template <typename _T, std::size_t _N>
    expr<op:: sub <_T, _N>,
         vec<_T, _N>,
         vec<_T, _N> >
    operator-(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // sub operator: value_type, v
    template <typename _T, std::size_t _N>
    expr<op:: sub <_T, _N>,
         typename vec<_T, _N>::value_type,
         vec<_T, _N> >
    operator-(const typename vec<_T, _N>::value_type& a,
              const vec<_T, _N>& b);

    // sub operator: v, value_type
    template <typename _T, std::size_t _N>
    expr<op:: sub <_T, _N>,
         vec<_T, _N>,
         typename vec<_T, _N>::value_type>
    operator-(const vec<_T, _N>& a,
              const typename vec<_T, _N>::value_type& b);

    // sub operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: sub <_T, _N>,
         vec<_T, _N>,
         expr<_OP<_T, _N>, _L, _R> >
    operator-(const vec<_T, _N>& a,
              const expr<_OP<_T, _N>, _L, _R>& b);

    // sub operator: expr, v
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: sub <_T, _N>,
         expr<_OP<_T, _N>, _L, _R>,
         vec<_T, _N> >
    operator-(const expr<_OP<_T, _N>, _L, _R>& a,
              const vec<_T, _N>& b);

    // sub operator: value_type, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: sub <_T, _N>,
         typename vec<_T, _N>::value_type,
         expr<_OP<_T, _N>, _L, _R> >
    operator-(const typename vec<_T, _N>::value_type& a,
              const expr<_OP<_T, _N>, _L, _R>& b);

    // sub operator: expr, value_type
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: sub <_T, _N>,
         expr<_OP<_T, _N>, _L, _R>,
         typename vec<_T, _N>::value_type >
    operator-(const expr<_OP<_T, _N>, _L, _R>& a,
              const typename vec<_T, _N>::value_type& b);

    // sub operator: expr, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP1,
              class _L1, class _R1,
              template <typename _T2, std::size_t _N2> class _OP2,
              class _L2, class _R2>
    expr<op:: sub <_T, _N>,
         expr<_OP1<_T, _N>, _L1, _R1>,
         expr<_OP2<_T, _N>, _L2, _R2> >
    operator-(const expr<_OP1<_T, _N>, _L1, _R1>& a,
              const expr<_OP2<_T, _N>, _L2, _R2>& b);

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
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    vec<_T, _N>&
    operator-=(vec<_T, _N>& a,
               const expr<_OP<_T, _N>, _L, _R>& b);

    // mul operator: v, v
    template <typename _T, std::size_t _N>
    expr<op:: mul <_T, _N>,
         vec<_T, _N>,
         vec<_T, _N> >
    operator*(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // mul operator: value_type, v
    template <typename _T, std::size_t _N>
    expr<op:: mul <_T, _N>,
         typename vec<_T, _N>::value_type,
         vec<_T, _N> >
    operator*(const typename vec<_T, _N>::value_type& a,
              const vec<_T, _N>& b);

    // mul operator: v, value_type
    template <typename _T, std::size_t _N>
    expr<op:: mul <_T, _N>,
         vec<_T, _N>,
         typename vec<_T, _N>::value_type>
    operator*(const vec<_T, _N>& a,
              const typename vec<_T, _N>::value_type& b);

    // mul operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: mul <_T, _N>,
         vec<_T, _N>,
         expr<_OP<_T, _N>, _L, _R> >
    operator*(const vec<_T, _N>& a,
              const expr<_OP<_T, _N>, _L, _R>& b);

    // mul operator: expr, v
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: mul <_T, _N>,
         expr<_OP<_T, _N>, _L, _R>,
         vec<_T, _N> >
    operator*(const expr<_OP<_T, _N>, _L, _R>& a,
              const vec<_T, _N>& b);

    // mul operator: value_type, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: mul <_T, _N>,
         typename vec<_T, _N>::value_type,
         expr<_OP<_T, _N>, _L, _R> >
    operator*(const typename vec<_T, _N>::value_type& a,
              const expr<_OP<_T, _N>, _L, _R>& b);

    // mul operator: expr, value_type
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: mul <_T, _N>,
         expr<_OP<_T, _N>, _L, _R>,
         typename vec<_T, _N>::value_type >
    operator*(const expr<_OP<_T, _N>, _L, _R>& a,
              const typename vec<_T, _N>::value_type& b);

    // mul operator: expr, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP1,
              class _L1, class _R1,
              template <typename _T2, std::size_t _N2> class _OP2,
              class _L2, class _R2>
    expr<op:: mul <_T, _N>,
         expr<_OP1<_T, _N>, _L1, _R1>,
         expr<_OP2<_T, _N>, _L2, _R2> >
    operator*(const expr<_OP1<_T, _N>, _L1, _R1>& a,
              const expr<_OP2<_T, _N>, _L2, _R2>& b);

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
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    vec<_T, _N>&
    operator*=(vec<_T, _N>& a,
               const expr<_OP<_T, _N>, _L, _R>& b);


    // div operator: v, v
    template <typename _T, std::size_t _N>
    expr<op:: div <_T, _N>,
         vec<_T, _N>,
         vec<_T, _N> >
    operator/(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // div operator: value_type, v
    template <typename _T, std::size_t _N>
    expr<op:: div <_T, _N>,
         typename vec<_T, _N>::value_type,
         vec<_T, _N> >
    operator/(const typename vec<_T, _N>::value_type& a,
              const vec<_T, _N>& b);

    // div operator: v, value_type
    template <typename _T, std::size_t _N>
    expr<op:: div <_T, _N>,
         vec<_T, _N>,
         typename vec<_T, _N>::value_type>
    operator/(const vec<_T, _N>& a,
              const typename vec<_T, _N>::value_type& b);

    // div operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: div <_T, _N>,
         vec<_T, _N>,
         expr<_OP<_T, _N>, _L, _R> >
    operator/(const vec<_T, _N>& a,
              const expr<_OP<_T, _N>, _L, _R>& b);

    // div operator: expr, v
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: div <_T, _N>,
         expr<_OP<_T, _N>, _L, _R>,
         vec<_T, _N> >
    operator/(const expr<_OP<_T, _N>, _L, _R>& a,
              const vec<_T, _N>& b);

    // div operator: value_type, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: div <_T, _N>,
         typename vec<_T, _N>::value_type,
         expr<_OP<_T, _N>, _L, _R> >
    operator/(const typename vec<_T, _N>::value_type& a,
              const expr<_OP<_T, _N>, _L, _R>& b);

    // div operator: expr, value_type
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: div <_T, _N>,
         expr<_OP<_T, _N>, _L, _R>,
         typename vec<_T, _N>::value_type >
    operator/(const expr<_OP<_T, _N>, _L, _R>& a,
              const typename vec<_T, _N>::value_type& b);

    // div operator: expr, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP1,
              class _L1, class _R1,
              template <typename _T2, std::size_t _N2> class _OP2,
              class _L2, class _R2>
    expr<op:: div <_T, _N>,
         expr<_OP1<_T, _N>, _L1, _R1>,
         expr<_OP2<_T, _N>, _L2, _R2> >
    operator/(const expr<_OP1<_T, _N>, _L1, _R1>& a,
              const expr<_OP2<_T, _N>, _L2, _R2>& b);

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
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    vec<_T, _N>&
    operator/=(vec<_T, _N>& a,
               const expr<_OP<_T, _N>, _L, _R>& b);


    // mod operator: v, v
    template <typename _T, std::size_t _N>
    expr<op:: mod <_T, _N>,
         vec<_T, _N>,
         vec<_T, _N> >
    operator%(const vec<_T, _N>& a, const vec<_T, _N>& b);

    // mod operator: value_type, v
    template <typename _T, std::size_t _N>
    expr<op:: mod <_T, _N>,
         typename vec<_T, _N>::value_type,
         vec<_T, _N> >
    operator%(const typename vec<_T, _N>::value_type& a,
              const vec<_T, _N>& b);

    // mod operator: v, value_type
    template <typename _T, std::size_t _N>
    expr<op:: mod <_T, _N>,
         vec<_T, _N>,
         typename vec<_T, _N>::value_type>
    operator%(const vec<_T, _N>& a,
              const typename vec<_T, _N>::value_type& b);

    // mod operator: v, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: mod <_T, _N>,
         vec<_T, _N>,
         expr<_OP<_T, _N>, _L, _R> >
    operator%(const vec<_T, _N>& a,
              const expr<_OP<_T, _N>, _L, _R>& b);

    // mod operator: expr, v
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: mod <_T, _N>,
         expr<_OP<_T, _N>, _L, _R>,
         vec<_T, _N> >
    operator%(const expr<_OP<_T, _N>, _L, _R>& a,
              const vec<_T, _N>& b);

    // mod operator: value_type, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: mod <_T, _N>,
         typename vec<_T, _N>::value_type,
         expr<_OP<_T, _N>, _L, _R> >
    operator%(const typename vec<_T, _N>::value_type& a,
              const expr<_OP<_T, _N>, _L, _R>& b);

    // mod operator: expr, value_type
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    expr<op:: mod <_T, _N>,
         expr<_OP<_T, _N>, _L, _R>,
         typename vec<_T, _N>::value_type >
    operator%(const expr<_OP<_T, _N>, _L, _R>& a,
              const typename vec<_T, _N>::value_type& b);

    // mod operator: expr, expr
    template <typename _T, std::size_t _N,
              template <typename _T1, std::size_t _N1> class _OP1,
              class _L1, class _R1,
              template <typename _T2, std::size_t _N2> class _OP2,
              class _L2, class _R2>
    expr<op:: mod <_T, _N>,
         expr<_OP1<_T, _N>, _L1, _R1>,
         expr<_OP2<_T, _N>, _L2, _R2> >
    operator%(const expr<_OP1<_T, _N>, _L1, _R1>& a,
              const expr<_OP2<_T, _N>, _L2, _R2>& b);

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
              template <typename _T1, std::size_t _N1> class _OP,
              class _L, class _R>
    vec<_T, _N>&
    operator%=(vec<_T, _N>& a,
               const expr<_OP<_T, _N>, _L, _R>& b);

}

#define DEF_CMP_OPS(opname, opobj)                                      \
    template <class _T, std::size_t _N>                                 \
    inline                                                              \
    typename cftal::vec<_T, _N>::mask_type                              \
    cftal::operator opname(const vec<_T, _N>& a,                        \
                           const vec<_T, _N>& b)                        \
    {                                                                   \
        return opobj <_T, _N> ::v(a, b);                                \
    }                                                                   \
                                                                        \
    template <class _T, std::size_t _N>                                 \
    inline                                                              \
    typename cftal::vec<_T, _N>::mask_type                              \
    cftal::operator opname(const vec<_T, _N>& a,                        \
                           const typename vec<_T, _N>::value_type& b)   \
    {                                                                   \
        return opobj <_T, _N> ::v(a, b);                                \
    }                                                                   \
                                                                        \
    template <class _T, std::size_t _N>                                 \
    inline                                                              \
    typename cftal::vec<_T, _N>::mask_type                              \
    cftal::operator opname(const typename vec<_T, _N>::value_type& a,   \
                           const vec<_T, _N>& b)                        \
    {                                                                   \
        return  opobj <_T, _N> ::v(a, b);                               \
    }


DEF_CMP_OPS(<, op::lt)
DEF_CMP_OPS(<=, op::le)
DEF_CMP_OPS(==, op::eq)
DEF_CMP_OPS(!=, op::ne)
DEF_CMP_OPS(>=, op::ge)
DEF_CMP_OPS(>, op::gt)

#undef DEF_CMP_OPS

template <typename _T, std::size_t _N>
cftal::expr<cftal::op:: bit_not <_T, _N>,
            cftal::vec<_T, _N>, void>
cftal::operator~(const vec<_T, _N>& v)
{
    return expr<op:: bit_not <_T, _N>,
                vec<_T, _N>, void>(v);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          typename _L, typename _R>
cftal::expr<cftal::op:: bit_not<_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R>,
            void>
cftal::operator~(const expr<_OP<_T, _N>, _L, _R>& v)
{
    return expr<op:: bit_not <_T, _N>,
                expr<_OP<_T, _N>, _L, _R>,
                void>(v);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::bit_or <_T, _N>,
            cftal::vec<_T, _N>,
            cftal::vec<_T, _N> >
cftal::operator|(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return expr<op:: bit_or<_T, _N>,
                vec<_T, _N>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::bit_or <_T, _N>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::vec<_T, _N> >
cftal::operator|(const typename vec<_T, _N>::value_type& a,
                 const vec<_T, _N>& b)
{
    return expr<op::bit_or<_T, _N>,
                typename vec<_T, _N>::value_type,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::bit_or <_T, _N>,
            cftal::vec<_T, _N>,
            typename cftal::vec<_T, _N>::value_type>
cftal::operator|(const vec<_T, _N>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::bit_or<_T, _N>,
                vec<_T, _N>,
                typename vec<_T, _N>::value_type>(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_or <_T, _N>,
            cftal::vec<_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R> >
cftal::operator|(const vec<_T, _N>& a,
                 const expr<_OP<_T, _N>, _L, _R>& b)
{
    return expr<op::bit_or<_T, _N>,
                vec<_T, _N>,
                expr<_OP<_T, _N>, _L, _R> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_or <_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R>,
            cftal::vec<_T, _N> >
cftal::operator|(const expr<_OP<_T, _N>, _L, _R>& a,
                 const vec<_T, _N>& b)
{
    return expr<op::bit_or<_T, _N>,
                expr<_OP<_T, _N>, _L, _R>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_or <_T, _N>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::expr<_OP<_T, _N>, _L, _R> >
cftal::operator|(const typename vec<_T, _N>::value_type& a,
                 const expr<_OP<_T, _N>, _L, _R>& b)
{
    return expr<op::bit_or<_T, _N>,
                typename vec<_T, _N>::value_type,
                expr<_OP<_T, _N>, _L, _R> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_or <_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R>,
            typename cftal::vec<_T, _N>::value_type >
cftal::operator|(const expr<_OP<_T, _N>, _L, _R>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::bit_or<_T, _N>,
                expr<_OP<_T, _N>, _L, _R>,
                typename vec<_T, _N>::value_type >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP1,
          class _L1, class _R1,
          template <typename _T2, std::size_t _N2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::bit_or <_T, _N>,
            cftal::expr<_OP1<_T, _N>, _L1, _R1>,
            cftal::expr<_OP2<_T, _N>, _L2, _R2> >
cftal::operator|(const expr<_OP1<_T, _N>, _L1, _R1>& a,
                 const expr<_OP2<_T, _N>, _L2, _R2>& b)
{
    return expr<op::bit_or<_T, _N>,
                expr<_OP1<_T, _N>, _L1, _R1>,
                expr<_OP2<_T, _N>, _L2, _R2> >(a, b);
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
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::vec<_T, _N>&
cftal::operator|=(vec<_T, _N>& a,
                  const expr<_OP<_T, _N>, _L, _R>& b)
{
    a = a | b;
    return a;
}



template <typename _T, std::size_t _N>
cftal::expr<cftal::op::bit_and <_T, _N>,
            cftal::vec<_T, _N>,
            cftal::vec<_T, _N> >
cftal::operator&(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return expr<op:: bit_and<_T, _N>,
                vec<_T, _N>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::bit_and <_T, _N>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::vec<_T, _N> >
cftal::operator&(const typename vec<_T, _N>::value_type& a,
                 const vec<_T, _N>& b)
{
    return expr<op::bit_and<_T, _N>,
                typename vec<_T, _N>::value_type,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::bit_and <_T, _N>,
            cftal::vec<_T, _N>,
            typename cftal::vec<_T, _N>::value_type>
cftal::operator&(const vec<_T, _N>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::bit_and<_T, _N>,
                vec<_T, _N>,
                typename vec<_T, _N>::value_type>(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_and <_T, _N>,
            cftal::vec<_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R> >
cftal::operator&(const vec<_T, _N>& a,
                 const expr<_OP<_T, _N>, _L, _R>& b)
{
    return expr<op::bit_and<_T, _N>,
                vec<_T, _N>,
                expr<_OP<_T, _N>, _L, _R> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_and <_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R>,
            cftal::vec<_T, _N> >
cftal::operator&(const expr<_OP<_T, _N>, _L, _R>& a,
                 const vec<_T, _N>& b)
{
    return expr<op::bit_and<_T, _N>,
                expr<_OP<_T, _N>, _L, _R>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_and <_T, _N>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::expr<_OP<_T, _N>, _L, _R> >
cftal::operator&(const typename vec<_T, _N>::value_type& a,
                 const expr<_OP<_T, _N>, _L, _R>& b)
{
    return expr<op::bit_and<_T, _N>,
                typename vec<_T, _N>::value_type,
                expr<_OP<_T, _N>, _L, _R> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_and <_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R>,
            typename cftal::vec<_T, _N>::value_type >
cftal::operator&(const expr<_OP<_T, _N>, _L, _R>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::bit_and<_T, _N>,
                expr<_OP<_T, _N>, _L, _R>,
                typename vec<_T, _N>::value_type >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP1,
          class _L1, class _R1,
          template <typename _T2, std::size_t _N2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::bit_and <_T, _N>,
            cftal::expr<_OP1<_T, _N>, _L1, _R1>,
            cftal::expr<_OP2<_T, _N>, _L2, _R2> >
cftal::operator&(const expr<_OP1<_T, _N>, _L1, _R1>& a,
                 const expr<_OP2<_T, _N>, _L2, _R2>& b)
{
    return expr<op::bit_and<_T, _N>,
                expr<_OP1<_T, _N>, _L1, _R1>,
                expr<_OP2<_T, _N>, _L2, _R2> >(a, b);
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
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::vec<_T, _N>&
cftal::operator&=(vec<_T, _N>& a,
                  const expr<_OP<_T, _N>, _L, _R>& b)
{
    a = a & b;
    return a;
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::bit_xor <_T, _N>,
            cftal::vec<_T, _N>,
            cftal::vec<_T, _N> >
cftal::operator^(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return expr<op:: bit_xor<_T, _N>,
                vec<_T, _N>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::bit_xor <_T, _N>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::vec<_T, _N> >
cftal::operator^(const typename vec<_T, _N>::value_type& a,
                 const vec<_T, _N>& b)
{
    return expr<op::bit_xor<_T, _N>,
                typename vec<_T, _N>::value_type,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::bit_xor <_T, _N>,
            cftal::vec<_T, _N>,
            typename cftal::vec<_T, _N>::value_type>
cftal::operator^(const vec<_T, _N>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::bit_xor<_T, _N>,
                vec<_T, _N>,
                typename vec<_T, _N>::value_type>(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_xor <_T, _N>,
            cftal::vec<_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R> >
cftal::operator^(const vec<_T, _N>& a,
                 const expr<_OP<_T, _N>, _L, _R>& b)
{
    return expr<op::bit_xor<_T, _N>,
                vec<_T, _N>,
                expr<_OP<_T, _N>, _L, _R> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_xor <_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R>,
            cftal::vec<_T, _N> >
cftal::operator^(const expr<_OP<_T, _N>, _L, _R>& a,
                 const vec<_T, _N>& b)
{
    return expr<op::bit_xor<_T, _N>,
                expr<_OP<_T, _N>, _L, _R>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_xor <_T, _N>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::expr<_OP<_T, _N>, _L, _R> >
cftal::operator^(const typename vec<_T, _N>::value_type& a,
                 const expr<_OP<_T, _N>, _L, _R>& b)
{
    return expr<op::bit_xor<_T, _N>,
                typename vec<_T, _N>::value_type,
                expr<_OP<_T, _N>, _L, _R> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::bit_xor <_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R>,
            typename cftal::vec<_T, _N>::value_type >
cftal::operator^(const expr<_OP<_T, _N>, _L, _R>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::bit_xor<_T, _N>,
                expr<_OP<_T, _N>, _L, _R>,
                typename vec<_T, _N>::value_type >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP1,
          class _L1, class _R1,
          template <typename _T2, std::size_t _N2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::bit_xor <_T, _N>,
            cftal::expr<_OP1<_T, _N>, _L1, _R1>,
            cftal::expr<_OP2<_T, _N>, _L2, _R2> >
cftal::operator^(const expr<_OP1<_T, _N>, _L1, _R1>& a,
                 const expr<_OP2<_T, _N>, _L2, _R2>& b)
{
    return expr<op::bit_xor<_T, _N>,
                expr<_OP1<_T, _N>, _L1, _R1>,
                expr<_OP2<_T, _N>, _L2, _R2> >(a, b);
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
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::vec<_T, _N>&
cftal::operator^=(vec<_T, _N>& a,
                  const expr<_OP<_T, _N>, _L, _R>& b)
{
    a = a ^ b;
    return a;
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::vshl <_T, _N>,
            cftal::vec<_T, _N>,
            cftal::vec<_T, _N> >
cftal::operator<<(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return expr<op:: vshl<_T, _N>,
                vec<_T, _N>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::vshl <_T, _N>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::vec<_T, _N> >
cftal::operator<<(const typename vec<_T, _N>::value_type& a,
                  const vec<_T, _N>& b)
{
    return expr<op::vshl<_T, _N>,
                typename vec<_T, _N>::value_type,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::vshl <_T, _N>,
            cftal::vec<_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R> >
cftal::operator<<(const vec<_T, _N>& a,
                 const expr<_OP<_T, _N>, _L, _R>& b)
{
    return expr<op::vshl<_T, _N>,
                vec<_T, _N>,
                expr<_OP<_T, _N>, _L, _R> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::vshl <_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R>,
            cftal::vec<_T, _N> >
cftal::operator<<(const expr<_OP<_T, _N>, _L, _R>& a,
                  const vec<_T, _N>& b)
{
    return expr<op::vshl<_T, _N>,
                expr<_OP<_T, _N>, _L, _R>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::vshl <_T, _N>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::expr<_OP<_T, _N>, _L, _R> >
cftal::operator<<(const typename vec<_T, _N>::value_type& a,
                  const expr<_OP<_T, _N>, _L, _R>& b)
{
    return expr<op::vshl<_T, _N>,
                typename vec<_T, _N>::value_type,
                expr<_OP<_T, _N>, _L, _R> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP1,
          class _L1, class _R1,
          template <typename _T2, std::size_t _N2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::vshl <_T, _N>,
            cftal::expr<_OP1<_T, _N>, _L1, _R1>,
            cftal::expr<_OP2<_T, _N>, _L2, _R2> >
cftal::operator<<(const expr<_OP1<_T, _N>, _L1, _R1>& a,
                  const expr<_OP2<_T, _N>, _L2, _R2>& b)
{
    return expr<op::vshl<_T, _N>,
                expr<_OP1<_T, _N>, _L1, _R1>,
                expr<_OP2<_T, _N>, _L2, _R2> >(a, b);
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
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::vec<_T, _N>&
cftal::operator<<=(vec<_T, _N>& a,
                  const expr<_OP<_T, _N>, _L, _R>& b)
{
    a = a << b;
    return a;
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::vshr <_T, _N>,
            cftal::vec<_T, _N>,
            cftal::vec<_T, _N> >
cftal::operator>>(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return expr<op:: vshr<_T, _N>,
                vec<_T, _N>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::vshr <_T, _N>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::vec<_T, _N> >
cftal::operator>>(const typename vec<_T, _N>::value_type& a,
                  const vec<_T, _N>& b)
{
    return expr<op::vshr<_T, _N>,
                typename vec<_T, _N>::value_type,
                vec<_T, _N> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::vshr <_T, _N>,
            cftal::vec<_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R> >
cftal::operator>>(const vec<_T, _N>& a,
                 const expr<_OP<_T, _N>, _L, _R>& b)
{
    return expr<op::vshr<_T, _N>,
                vec<_T, _N>,
                expr<_OP<_T, _N>, _L, _R> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::vshr <_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R>,
            cftal::vec<_T, _N> >
cftal::operator>>(const expr<_OP<_T, _N>, _L, _R>& a,
                  const vec<_T, _N>& b)
{
    return expr<op::vshr<_T, _N>,
                expr<_OP<_T, _N>, _L, _R>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::vshr <_T, _N>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::expr<_OP<_T, _N>, _L, _R> >
cftal::operator>>(const typename vec<_T, _N>::value_type& a,
                  const expr<_OP<_T, _N>, _L, _R>& b)
{
    return expr<op::vshr<_T, _N>,
                typename vec<_T, _N>::value_type,
                expr<_OP<_T, _N>, _L, _R> >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP1,
          class _L1, class _R1,
          template <typename _T2, std::size_t _N2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::vshr <_T, _N>,
            cftal::expr<_OP1<_T, _N>, _L1, _R1>,
            cftal::expr<_OP2<_T, _N>, _L2, _R2> >
cftal::operator>>(const expr<_OP1<_T, _N>, _L1, _R1>& a,
                 const expr<_OP2<_T, _N>, _L2, _R2>& b)
{
    return expr<op::vshr<_T, _N>,
                expr<_OP1<_T, _N>, _L1, _R1>,
                expr<_OP2<_T, _N>, _L2, _R2> >(a, b);
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
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::vec<_T, _N>&
cftal::operator>>=(vec<_T, _N>& a,
                   const expr<_OP<_T, _N>, _L, _R>& b)
{
    a = a >> b;
    return a;
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op:: shl<_T, _N>,
            cftal::vec<_T, _N>,
            unsigned>
cftal::operator<<(const vec<_T, _N>& v, unsigned s)
{
    return expr<op:: shl<_T, _N>,
                vec<_T, _N>, unsigned>(v, s);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op:: shl<_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R>,
            unsigned>
cftal::operator<<(const expr<_OP<_T, _N>, _L, _R>& e,
                  unsigned s)
{
    return expr<op:: shl<_T, _N>,
                expr<_OP<_T, _N>, _L, _R>,
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
cftal::expr<cftal::op:: shr<_T, _N>,
            cftal::vec<_T, _N>,
            unsigned>
cftal::operator>>(const vec<_T, _N>& v, unsigned s)
{
    return expr<op:: shr<_T, _N>,
                vec<_T, _N>, unsigned>(v, s);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op:: shr<_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R>,
            unsigned>
cftal::operator>>(const expr<_OP<_T, _N>, _L, _R>& e,
                  unsigned s)
{
    return expr<op:: shr<_T, _N>,
                expr<_OP<_T, _N>, _L, _R>,
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
cftal::expr<cftal::op:: neg <_T, _N>,
            cftal::vec<_T, _N>, void>
cftal::operator-(const vec<_T, _N>& v)
{
    return expr<op:: neg <_T, _N>,
                vec<_T, _N>, void>(v);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          typename _L, typename _R>
cftal::expr<cftal::op:: neg<_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R>,
            void>
cftal::operator-(const expr<_OP<_T, _N>, _L, _R>& v)
{
    return expr<op:: neg<_T, _N>,
                expr<_OP<_T, _N>, _L, _R>,
                void>(v);
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::add <_T, _N>,
            cftal::vec<_T, _N>,
            cftal::vec<_T, _N> >
cftal::operator+(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return expr<op:: add<_T, _N>,
                vec<_T, _N>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::add <_T, _N>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::vec<_T, _N> >
cftal::operator+(const typename vec<_T, _N>::value_type& a,
                 const vec<_T, _N>& b)
{
    return expr<op::add<_T, _N>,
                typename vec<_T, _N>::value_type,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::add <_T, _N>,
            cftal::vec<_T, _N>,
            typename cftal::vec<_T, _N>::value_type>
cftal::operator+(const vec<_T, _N>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::add<_T, _N>,
                vec<_T, _N>,
                typename vec<_T, _N>::value_type>(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::add <_T, _N>,
            cftal::vec<_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R> >
cftal::operator+(const vec<_T, _N>& a,
                 const expr<_OP<_T, _N>, _L, _R>& b)
{
    return expr<op::add<_T, _N>,
                vec<_T, _N>,
                expr<_OP<_T, _N>, _L, _R> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::add <_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R>,
            cftal::vec<_T, _N> >
cftal::operator+(const expr<_OP<_T, _N>, _L, _R>& a,
                 const vec<_T, _N>& b)
{
    return expr<op::add<_T, _N>,
                expr<_OP<_T, _N>, _L, _R>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::add <_T, _N>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::expr<_OP<_T, _N>, _L, _R> >
cftal::operator+(const typename vec<_T, _N>::value_type& a,
                 const expr<_OP<_T, _N>, _L, _R>& b)
{
    return expr<op::add<_T, _N>,
                typename vec<_T, _N>::value_type,
                expr<_OP<_T, _N>, _L, _R> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::add <_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R>,
            typename cftal::vec<_T, _N>::value_type >
cftal::operator+(const expr<_OP<_T, _N>, _L, _R>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::add<_T, _N>,
                expr<_OP<_T, _N>, _L, _R>,
                typename vec<_T, _N>::value_type >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP1,
          class _L1, class _R1,
          template <typename _T2, std::size_t _N2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::add <_T, _N>,
            cftal::expr<_OP1<_T, _N>, _L1, _R1>,
            cftal::expr<_OP2<_T, _N>, _L2, _R2> >
cftal::operator+(const expr<_OP1<_T, _N>, _L1, _R1>& a,
                 const expr<_OP2<_T, _N>, _L2, _R2>& b)
{
    return expr<op::add<_T, _N>,
                expr<_OP1<_T, _N>, _L1, _R1>,
                expr<_OP2<_T, _N>, _L2, _R2> >(a, b);
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
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::vec<_T, _N>&
cftal::operator+=(vec<_T, _N>& a,
                  const expr<_OP<_T, _N>, _L, _R>& b)
{
    a = a + b;
    return a;
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::sub <_T, _N>,
            cftal::vec<_T, _N>,
            cftal::vec<_T, _N> >
cftal::operator-(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return expr<op:: sub<_T, _N>,
                vec<_T, _N>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::sub <_T, _N>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::vec<_T, _N> >
cftal::operator-(const typename vec<_T, _N>::value_type& a,
                 const vec<_T, _N>& b)
{
    return expr<op::sub<_T, _N>,
                typename vec<_T, _N>::value_type,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::sub <_T, _N>,
            cftal::vec<_T, _N>,
            typename cftal::vec<_T, _N>::value_type>
cftal::operator-(const vec<_T, _N>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::sub<_T, _N>,
                vec<_T, _N>,
                typename vec<_T, _N>::value_type>(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::sub <_T, _N>,
            cftal::vec<_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R> >
cftal::operator-(const vec<_T, _N>& a,
                 const expr<_OP<_T, _N>, _L, _R>& b)
{
    return expr<op::sub<_T, _N>,
                vec<_T, _N>,
                expr<_OP<_T, _N>, _L, _R> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::sub <_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R>,
            cftal::vec<_T, _N> >
cftal::operator-(const expr<_OP<_T, _N>, _L, _R>& a,
                 const vec<_T, _N>& b)
{
    return expr<op::sub<_T, _N>,
                expr<_OP<_T, _N>, _L, _R>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::sub <_T, _N>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::expr<_OP<_T, _N>, _L, _R> >
cftal::operator-(const typename vec<_T, _N>::value_type& a,
                 const expr<_OP<_T, _N>, _L, _R>& b)
{
    return expr<op::sub<_T, _N>,
                typename vec<_T, _N>::value_type,
                expr<_OP<_T, _N>, _L, _R> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::sub <_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R>,
            typename cftal::vec<_T, _N>::value_type >
cftal::operator-(const expr<_OP<_T, _N>, _L, _R>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::sub<_T, _N>,
                expr<_OP<_T, _N>, _L, _R>,
                typename vec<_T, _N>::value_type >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP1,
          class _L1, class _R1,
          template <typename _T2, std::size_t _N2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::sub <_T, _N>,
            cftal::expr<_OP1<_T, _N>, _L1, _R1>,
            cftal::expr<_OP2<_T, _N>, _L2, _R2> >
cftal::operator-(const expr<_OP1<_T, _N>, _L1, _R1>& a,
                 const expr<_OP2<_T, _N>, _L2, _R2>& b)
{
    return expr<op::sub<_T, _N>,
                expr<_OP1<_T, _N>, _L1, _R1>,
                expr<_OP2<_T, _N>, _L2, _R2> >(a, b);
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
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::vec<_T, _N>&
cftal::operator-=(vec<_T, _N>& a,
                  const expr<_OP<_T, _N>, _L, _R>& b)
{
    a = a - b;
    return a;
}




template <typename _T, std::size_t _N>
cftal::expr<cftal::op::mul <_T, _N>,
            cftal::vec<_T, _N>,
            cftal::vec<_T, _N> >
cftal::operator*(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return expr<op:: mul<_T, _N>,
                vec<_T, _N>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::mul <_T, _N>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::vec<_T, _N> >
cftal::operator*(const typename vec<_T, _N>::value_type& a,
                 const vec<_T, _N>& b)
{
    return expr<op::mul<_T, _N>,
                typename vec<_T, _N>::value_type,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::mul <_T, _N>,
            cftal::vec<_T, _N>,
            typename cftal::vec<_T, _N>::value_type>
cftal::operator*(const vec<_T, _N>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::mul<_T, _N>,
                vec<_T, _N>,
                typename vec<_T, _N>::value_type>(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::mul <_T, _N>,
            cftal::vec<_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R> >
cftal::operator*(const vec<_T, _N>& a,
                 const expr<_OP<_T, _N>, _L, _R>& b)
{
    return expr<op::mul<_T, _N>,
                vec<_T, _N>,
                expr<_OP<_T, _N>, _L, _R> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::mul <_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R>,
            cftal::vec<_T, _N> >
cftal::operator*(const expr<_OP<_T, _N>, _L, _R>& a,
                 const vec<_T, _N>& b)
{
    return expr<op::mul<_T, _N>,
                expr<_OP<_T, _N>, _L, _R>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::mul <_T, _N>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::expr<_OP<_T, _N>, _L, _R> >
cftal::operator*(const typename vec<_T, _N>::value_type& a,
                 const expr<_OP<_T, _N>, _L, _R>& b)
{
    return expr<op::mul<_T, _N>,
                typename vec<_T, _N>::value_type,
                expr<_OP<_T, _N>, _L, _R> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::mul <_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R>,
            typename cftal::vec<_T, _N>::value_type >
cftal::operator*(const expr<_OP<_T, _N>, _L, _R>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::mul<_T, _N>,
                expr<_OP<_T, _N>, _L, _R>,
                typename vec<_T, _N>::value_type >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP1,
          class _L1, class _R1,
          template <typename _T2, std::size_t _N2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::mul <_T, _N>,
            cftal::expr<_OP1<_T, _N>, _L1, _R1>,
            cftal::expr<_OP2<_T, _N>, _L2, _R2> >
cftal::operator*(const expr<_OP1<_T, _N>, _L1, _R1>& a,
                 const expr<_OP2<_T, _N>, _L2, _R2>& b)
{
    return expr<op::mul<_T, _N>,
                expr<_OP1<_T, _N>, _L1, _R1>,
                expr<_OP2<_T, _N>, _L2, _R2> >(a, b);
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
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::vec<_T, _N>&
cftal::operator*=(vec<_T, _N>& a,
                  const expr<_OP<_T, _N>, _L, _R>& b)
{
    a = a * b;
    return a;
}



template <typename _T, std::size_t _N>
cftal::expr<cftal::op::div <_T, _N>,
            cftal::vec<_T, _N>,
            cftal::vec<_T, _N> >
cftal::operator/(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return expr<op:: div<_T, _N>,
                vec<_T, _N>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::div <_T, _N>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::vec<_T, _N> >
cftal::operator/(const typename vec<_T, _N>::value_type& a,
                 const vec<_T, _N>& b)
{
    return expr<op::div<_T, _N>,
                typename vec<_T, _N>::value_type,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::div <_T, _N>,
            cftal::vec<_T, _N>,
            typename cftal::vec<_T, _N>::value_type>
cftal::operator/(const vec<_T, _N>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::div<_T, _N>,
                vec<_T, _N>,
                typename vec<_T, _N>::value_type>(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::div <_T, _N>,
            cftal::vec<_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R> >
cftal::operator/(const vec<_T, _N>& a,
                 const expr<_OP<_T, _N>, _L, _R>& b)
{
    return expr<op::div<_T, _N>,
                vec<_T, _N>,
                expr<_OP<_T, _N>, _L, _R> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::div <_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R>,
            cftal::vec<_T, _N> >
cftal::operator/(const expr<_OP<_T, _N>, _L, _R>& a,
                 const vec<_T, _N>& b)
{
    return expr<op::div<_T, _N>,
                expr<_OP<_T, _N>, _L, _R>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::div <_T, _N>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::expr<_OP<_T, _N>, _L, _R> >
cftal::operator/(const typename vec<_T, _N>::value_type& a,
                 const expr<_OP<_T, _N>, _L, _R>& b)
{
    return expr<op::div<_T, _N>,
                typename vec<_T, _N>::value_type,
                expr<_OP<_T, _N>, _L, _R> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::div <_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R>,
            typename cftal::vec<_T, _N>::value_type >
cftal::operator/(const expr<_OP<_T, _N>, _L, _R>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::div<_T, _N>,
                expr<_OP<_T, _N>, _L, _R>,
                typename vec<_T, _N>::value_type >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP1,
          class _L1, class _R1,
          template <typename _T2, std::size_t _N2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::div <_T, _N>,
            cftal::expr<_OP1<_T, _N>, _L1, _R1>,
            cftal::expr<_OP2<_T, _N>, _L2, _R2> >
cftal::operator/(const expr<_OP1<_T, _N>, _L1, _R1>& a,
                 const expr<_OP2<_T, _N>, _L2, _R2>& b)
{
    return expr<op::div<_T, _N>,
                expr<_OP1<_T, _N>, _L1, _R1>,
                expr<_OP2<_T, _N>, _L2, _R2> >(a, b);
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
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::vec<_T, _N>&
cftal::operator/=(vec<_T, _N>& a,
                  const expr<_OP<_T, _N>, _L, _R>& b)
{
    a = a / b;
    return a;
}

template <typename _T, std::size_t _N>
cftal::expr<cftal::op::mod <_T, _N>,
            cftal::vec<_T, _N>,
            cftal::vec<_T, _N> >
cftal::operator%(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return expr<op:: mod<_T, _N>,
                vec<_T, _N>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::mod <_T, _N>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::vec<_T, _N> >
cftal::operator%(const typename vec<_T, _N>::value_type& a,
                 const vec<_T, _N>& b)
{
    return expr<op::mod<_T, _N>,
                typename vec<_T, _N>::value_type,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N>
cftal::expr<cftal::op::mod <_T, _N>,
            cftal::vec<_T, _N>,
            typename cftal::vec<_T, _N>::value_type>
cftal::operator%(const vec<_T, _N>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::mod<_T, _N>,
                vec<_T, _N>,
                typename vec<_T, _N>::value_type>(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::mod <_T, _N>,
            cftal::vec<_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R> >
cftal::operator%(const vec<_T, _N>& a,
                 const expr<_OP<_T, _N>, _L, _R>& b)
{
    return expr<op::mod<_T, _N>,
                vec<_T, _N>,
                expr<_OP<_T, _N>, _L, _R> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::mod <_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R>,
            cftal::vec<_T, _N> >
cftal::operator%(const expr<_OP<_T, _N>, _L, _R>& a,
                 const vec<_T, _N>& b)
{
    return expr<op::mod<_T, _N>,
                expr<_OP<_T, _N>, _L, _R>,
                vec<_T, _N> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::mod <_T, _N>,
            typename cftal::vec<_T, _N>::value_type,
            cftal::expr<_OP<_T, _N>, _L, _R> >
cftal::operator%(const typename vec<_T, _N>::value_type& a,
                 const expr<_OP<_T, _N>, _L, _R>& b)
{
    return expr<op::mod<_T, _N>,
                typename vec<_T, _N>::value_type,
                expr<_OP<_T, _N>, _L, _R> >(a, b);
}


template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::expr<cftal::op::mod <_T, _N>,
            cftal::expr<_OP<_T, _N>, _L, _R>,
            typename cftal::vec<_T, _N>::value_type >
cftal::operator%(const expr<_OP<_T, _N>, _L, _R>& a,
                 const typename vec<_T, _N>::value_type& b)
{
    return expr<op::mod<_T, _N>,
                expr<_OP<_T, _N>, _L, _R>,
                typename vec<_T, _N>::value_type >(a, b);
}

template <typename _T, std::size_t _N,
          template <typename _T1, std::size_t _N1> class _OP1,
          class _L1, class _R1,
          template <typename _T2, std::size_t _N2> class _OP2,
          class _L2, class _R2>
cftal::expr<cftal::op::mod <_T, _N>,
            cftal::expr<_OP1<_T, _N>, _L1, _R1>,
            cftal::expr<_OP2<_T, _N>, _L2, _R2> >
cftal::operator%(const expr<_OP1<_T, _N>, _L1, _R1>& a,
                 const expr<_OP2<_T, _N>, _L2, _R2>& b)
{
    return expr<op::mod<_T, _N>,
                expr<_OP1<_T, _N>, _L1, _R1>,
                expr<_OP2<_T, _N>, _L2, _R2> >(a, b);
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
          template <typename _T1, std::size_t _N1> class _OP,
          class _L, class _R>
cftal::vec<_T, _N>&
cftal::operator%=(vec<_T, _N>& a,
                  const expr<_OP<_T, _N>, _L, _R>& b)
{
    a = a % b;
    return a;
}


// Local variables:
// mode: c++
// end:
#endif
