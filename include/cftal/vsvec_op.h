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
#if !defined (__CFTAL_VSVEC_OP_H__)
#define __CFTAL_VSVEC_OP_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/expr.h>
#include <cftal/expr_func.h>
#include <cftal/vsvec_bit_a.h>

namespace cftal {

    namespace op_4_vsvec {
        // ternary operations
        template <typename _T, class _B>
        struct t_base : public _B {
            using base_type = _B;
            using base_type::v;

            template <size_t _N>
            static
            vec<_T, _N>
            v(const _T& a, const vec<_T, _N>& b, const vec<_T, _N>& c) {
                return v(vec<_T, _N>(a), b, c);
            }

            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const _T& b, const vec<_T, _N>& c) {
                return v(a, vec<_T, _N>(b), c);
            }

            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b, const _T& c) {
                return v(a, b, vec<_T, _N>(c));
            }

            template <size_t _N>
            static
            vec<_T, _N>
            v(const _T& a, const _T& b, const vec<_T, _N>& c) {
                return v(vec<_T, _N>(a), vec<_T, _N>(b), c);
            }

            template <size_t _N>
            static
            vec<_T, _N>
            v(const _T& a, const vec<_T, _N>& b, const _T& c) {
                return v(vec<_T, _N>(a), b, vec<_T, _N>(c));
            }

            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const _T& b, const _T& c) {
                return v(a, vec<_T, _N>(b), vec<_T, _N>(c));
            }
        };

        // binary operations
        template <typename _T, class _B>
        struct b_base : public _B {
            using base_type = _B;
            using base_type::v;

            template <size_t _N, typename _R>
            static
            vec<_T, _N>
            v(const _T& a, const vec<_R, _N>& b) {
                return v(vec<_T, _N>(a), b);
            }

            template <size_t _N, typename _R>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const _R& b) {
                return v(a, vec<_R, _N>(b));
            }
        };

        // comparison operations
        template <typename _T, class _B>
        struct c_base : public _B {
            using base_type = _B;
            using base_type::v;
            template <size_t _N>
            static
            typename vec<_T, _N>::mask_type
            v(const _T& a, const vec<_T, _N>& b) {
                return _B::v(vec<_T, _N>(a), b);
            }

            template <size_t _N>
            static
            typename vec<_T, _N>::mask_type
            v(const vec<_T, _N>& a, const _T& b) {
                return _B::v(a, vec<_T, _N>(b));
            }
        };

        template <typename _T>
        struct lt {
            template <size_t _N>
            static
            typename vec<_T, _N>::mask_type
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return a<b;
            }
        };

        template <typename _T>
        struct le {
            template <size_t _N>
            static
            typename vec<_T, _N>::mask_type
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return a<=b;
            }
        };

        template <typename _T>
        struct eq {
            template <size_t _N>
            static
            typename vec<_T, _N>::mask_type
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return a==b;
            }
        };

        template <typename _T>
        struct ne {
            template <size_t _N>
            static
            typename vec<_T, _N>::mask_type
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return a!=b;
            }
        };

        template <typename _T>
        struct ge {
            template <size_t _N>
            static
            typename vec<_T, _N>::mask_type
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return a>=b;
            }
        };

        template <typename _T>
        struct gt {
            template <size_t _N>
            static
            typename vec<_T, _N>::mask_type
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return a>b;
            }
        };

        template <typename _T>
        struct neg {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return -a;
            }
        };

        template <typename _T>
        struct bit_not {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return ~a;
            }
        };

        template <typename _T>
        struct bit_or {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return a|b;
            }
        };

        template <typename _T>
        struct bit_and {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return a&b;
            }
        };

        template <typename _T>
        struct bit_xor {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return a^b;
            }
        };

        template <typename _T>
        struct shl {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, unsigned s) {
                return a<<s;
            }
        };

        template <typename _T>
        struct shr {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, unsigned s) {
                return a>>s;
            }
        };

        template <typename _T>
        struct add {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return a+b;
            }
        };

        template <typename _T>
        struct sub {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return a-b;
            }
        };

        template <typename _T>
        struct mul {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return a*b;
            }
        };

        template <typename _T>
        struct div {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return a/b;
            }
        };

        template <typename _T>
        struct fma {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b,
                const vec<_T, _N>& c) {
                return a*b+c;
            }
        };

        template <typename _T>
        struct fms {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b,
                const vec<_T, _N>& c) {
                return a*b-c;
            }
        };

        template <typename _T>
        struct fnma {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b,
                const vec<_T, _N>& c) {
                return c-a*b;
            }
        };
    }

    namespace op {

        template <typename _T, typename _A>
        struct lt<vsvec<_T, _A>> :
            public op_4_vsvec::c_base<_T, op_4_vsvec::lt<_T> > {};

        template <typename _T, typename _A>
        struct le<vsvec<_T, _A>> :
            public op_4_vsvec::c_base<_T, op_4_vsvec::le<_T> > {};

        template <typename _T, typename _A>
        struct eq<vsvec<_T, _A>> :
            public op_4_vsvec::c_base<_T, op_4_vsvec::eq<_T> > {};

        template <typename _T, typename _A>
        struct ne<vsvec<_T, _A>> :
            public op_4_vsvec::c_base<_T, op_4_vsvec::ne<_T> > {};

        template <typename _T, typename _A>
        struct ge<vsvec<_T, _A>> :
            public op_4_vsvec::c_base<_T, op_4_vsvec::ge<_T> > {};

        template <typename _T, typename _A>
        struct gt<vsvec<_T, _A>> :
            public op_4_vsvec::c_base<_T, op_4_vsvec::gt<_T> > {};

        template <typename _T, typename _A>
        struct neg<vsvec<_T, _A>> :
            public op_4_vsvec::neg<_T> {};

        template <typename _T, typename _A>
        struct bit_not<vsvec<_T, _A>> :
            public op_4_vsvec::bit_not<_T> {};

        template <typename _T, typename _A>
        struct bit_or<vsvec<_T, _A>> :
            public op_4_vsvec::b_base<_T, op_4_vsvec::bit_or<_T> > {};

        template <typename _T, typename _A>
        struct bit_and<vsvec<_T, _A>> :
            public op_4_vsvec::b_base<_T, op_4_vsvec::bit_and<_T> > {};

        template <typename _T, typename _A>
        struct bit_xor<vsvec<_T, _A>> :
            public op_4_vsvec::b_base<_T, op_4_vsvec::bit_xor<_T> > {};

        template <typename _T, typename _A>
        struct shl<vsvec<_T, _A>> :
            public op_4_vsvec::shl<_T> {};

        template <typename _T, typename _A>
        struct shr<vsvec<_T, _A>> :
            public op_4_vsvec::shr<_T> {};

        template <typename _T, typename _A>
        struct add<vsvec<_T, _A>> :
            public op_4_vsvec::b_base<_T, op_4_vsvec::add<_T> > {};

        template <typename _T, typename _A>
        struct sub<vsvec<_T, _A>> :
            public op_4_vsvec::b_base<_T, op_4_vsvec::sub<_T> > {};

        template <typename _T, typename _A>
        struct mul<vsvec<_T, _A>> :
            public op_4_vsvec::b_base<_T, op_4_vsvec::mul<_T> > {};

        template <typename _T, typename _A>
        struct div<vsvec<_T, _A>> :
            public op_4_vsvec::b_base<_T, op_4_vsvec::div<_T> > {};

        template <typename _T, typename _A>
        struct fma<vsvec<_T, _A>> :
            public op_4_vsvec::t_base<_T, op_4_vsvec::fma<_T> > {};

        template <typename _T, typename _A>
        struct fms<vsvec<_T, _A>> :
            public op_4_vsvec::t_base<_T, op_4_vsvec::fms<_T> > {};

        template <typename _T, typename _A>
        struct fnma<vsvec<_T, _A>> :
            public op_4_vsvec::t_base<_T, op_4_vsvec::fnma<_T> > {};

    }

    // expression template filters
    // a+b*c
    template <size_t _N, typename _T, typename _A,
              class _L,
              class _LR, class _RR>
    inline
    vec<_T, _N>
    eval_i(const expr<op::add<vsvec<_T, _A>>, _L,
           expr<op::mul<vsvec<_T, _A>>, _LR, _RR> >& e,
           size_t i) {
        return op::fma<vsvec<_T, _A>>::v(eval_i<_N, _T>(e._r._l, i),
                                   eval_i<_N, _T>(e._r._r, i),
                                   eval_i<_N, _T>(e._l, i));
    }

    // a*b+c
    template <size_t _N, typename _T, typename _A,
              class _LL, class _LR,
              class _R>
    inline
    vec<_T, _N>
    eval_i(const expr<op::add<vsvec<_T, _A>>,
           expr<op::mul<vsvec<_T, _A>>, _LL, _LR>, _R>& e,
           size_t i) {
        return op::fma<vsvec<_T, _A>>::v(eval_i<_N, _T>(e._l._l, i),
                                   eval_i<_N, _T>(e._l._r, i),
                                   eval_i<_N, _T>(e._r, i));
    }

    // a*b + c*d
    template <size_t _N, typename _T, typename _A,
              class _LL, class _LR,
              class _RL, class _RR>
    inline
    vec<_T, _N>
    eval_i(const expr<op::add<vsvec<_T, _A>>,
           expr<op::mul<vsvec<_T, _A>>, _LL, _LR>,
           expr<op::mul<vsvec<_T, _A>>, _RL, _RR> >& e,
           size_t i) {
        return op::fma<vsvec<_T, _A>>::v(eval_i<_N, _T>(e._r._l, i),
                                   eval_i<_N, _T>(e._r._r, i),
                                   eval_i<_N, _T>(e._l, i));
    }

    // a*b -c
    template <size_t _N, typename _T, typename _A,
              class _LL, class _LR,
              class _R>
    inline
    vec<_T, _N>
    eval_i(const expr<op::sub<vsvec<_T, _A>>,
           expr<op::mul<vsvec<_T, _A>>, _LL, _LR>, _R>& e,
           size_t i) {
        return op::fms<vsvec<_T, _A>>::v(eval_i<_N, _T>(e._l._l, i),
                                   eval_i<_N, _T>(e._l._r, i),
                                   eval_i<_N, _T>(e._r, i));
    }

    // c - a*b
    template <size_t _N, typename _T, typename _A,
              class _L,
              class _LR, class _RR>
    inline
    vec<_T, _N>
    eval_i(const expr<op::sub<vsvec<_T, _A>>, _L,
           expr<op::mul<vsvec<_T, _A>>, _LR, _RR> >& e,
           size_t i) {
        return op::fnma<vsvec<_T, _A>>::v(eval_i<_N, _T>(e._r._l, i),
                                    eval_i<_N, _T>(e._r._r, i),
                                    eval_i<_N, _T>(e._l, i));
    }

    // a*b - c*d
    template <size_t _N, typename _T, typename _A,
              class _LL, class _LR,
              class _RL, class _RR>
    inline
    vec<_T, _N>
    eval_i(const expr<op::sub<vsvec<_T, _A>>,
           expr<op::mul<vsvec<_T, _A>>, _LL, _LR>,
           expr<op::mul<vsvec<_T, _A>>, _RL, _RR> >& e,
           size_t i) {
        return op::fnma<vsvec<_T, _A>>::v(eval_i<_N, _T>(e._r._l, i),
                                    eval_i<_N, _T>(e._r._r, i),
                                    eval_i<_N, _T>(e._l, i));
    }

    // a + -b = a - b
    template <size_t _N, typename _T, typename _A,
              class _L, class _R>
    inline
    vec<_T, _N>
    eval_i(const expr<op::add<vsvec<_T, _A>>, _L,
           expr<op::neg<vsvec<_T, _A>>, _R, void> >& e,
           size_t i) {
        return op::sub<vsvec<_T, _A>>::v(eval_i<_N, _T>(e._l, i),
                                   eval_i<_N, _T>(e._r._l, i));
    }

    // -a + b = b - a
    template <size_t _N, typename _T, typename _A,
              class _L, class _R>
    inline
    vec<_T, _N>
    eval_i(const expr<op::add<vsvec<_T, _A>>,
           expr<op::neg<vsvec<_T, _A>>, _L, void>, _R >& e,
           size_t i) {
        return op::sub<vsvec<_T, _A>>::v(eval_i<_N, _T>(e._r._l, i),
                                   eval_i<_N, _T>(e._l, i));
    }

    // a - -b = a + b
    template <size_t _N, typename _T, typename _A,
              class _L, class _R>
    inline
    vec<_T, _N>
    eval_i(const expr<op::sub<vsvec<_T, _A>>, _L,
           expr<op::neg<vsvec<_T, _A>>, _R, void> >& e,
           size_t i) {
        return op::add<vsvec<_T, _A>>::v(eval_i<_N, _T>(e._l, i),
                                   eval_i<_N, _T>(e._r._l, i));
    }

    // unary plus operator for vsvec
    template <typename _T, typename _A>
    inline
    const vsvec<_T, _A>& operator+(const vsvec<_T, _A>& v) {
        return v;
    }

#define UNARY_OP(the_op, op_type)                                       \
    /* unary vsvec */                                                    \
    template <typename _T, typename _A>                                 \
    expr<op_type <vsvec<_T, _A>>, vsvec<_T, _A>, void>                    \
    operator the_op (const vsvec<_T, _A>& l) {                           \
        return expr<op_type<vsvec<_T, _A>>, vsvec<_T, _A>, void>(l);      \
    }                                                                   \
    /* unary expr */                                                    \
    template <typename _T, typename _A,                                 \
              template <class _U> class _OP,                            \
              typename _L, typename _R>                                 \
    expr<op_type <vsvec<_T, _A>>,                                        \
         expr<_OP<vsvec<_T, _A>>, _L, _R>, void>                         \
    operator the_op (const expr<_OP<vsvec<_T, _A>>, _L, _R>& l) {        \
        return expr<op_type <vsvec<_T, _A>>,                             \
                    expr<_OP<vsvec<_T, _A>>, _L, _R>,                    \
                    void>(l);                                           \
    }

    UNARY_OP(-, op::neg)
    UNARY_OP(~, op::bit_not)

#undef UNARY_OP

#define BINARY_OP(the_op, the_op_assign, op_type)                       \
    /* vsvec, scalar */                                                  \
    template <typename _T, typename _A>                                 \
    expr<op_type <vsvec<_T, _A>>, vsvec<_T, _A>, _T>                      \
    operator the_op (const vsvec<_T, _A>& l, const _T& r) {              \
        return expr<op_type <vsvec<_T, _A>>, vsvec<_T, _A>, _T>(l, r);    \
    }                                                                   \
    /* scalar, vsvec */                                                  \
    template <typename _T, typename _A>                                 \
    expr<op_type <vsvec<_T, _A>>, _T, vsvec<_T, _A> >                     \
    operator the_op (const _T& l, const vsvec<_T, _A>& r) {              \
        return expr<op_type <vsvec<_T, _A>>, _T, vsvec<_T, _A> >(l, r);   \
    }                                                                   \
    /* vsvec, vsvec */                                                    \
    template <typename _T, typename _A>                                 \
    expr<op_type <vsvec<_T, _A>>, vsvec<_T, _A>, vsvec<_T, _A> >           \
    operator the_op (const vsvec<_T, _A>& l, const vsvec<_T, _A>& r) {    \
        return expr<op_type <vsvec<_T, _A>>,                             \
                    vsvec<_T, _A>,                                       \
                    vsvec<_T, _A> >(l, r);                               \
    }                                                                   \
    /* vsvec, expr */                                                    \
    template <typename _T, typename _A,                                 \
              template <class _U> class _OP,                            \
              class _L, class _R>                                       \
    expr<op_type <vsvec<_T, _A>>, vsvec<_T, _A>,                          \
         expr<_OP<vsvec<_T, _A>>, _L, _R> >                              \
    operator the_op (const vsvec<_T, _A>& l,                             \
                     const expr<_OP<vsvec<_T, _A>>, _L, _R>& r) {        \
        return expr<op_type <vsvec<_T, _A>>,                             \
                    vsvec<_T, _A>,                                       \
                    expr<_OP<vsvec<_T, _A>>, _L, _R> >(l, r);            \
    }                                                                   \
    /* expr, vsvec */                                                    \
    template <typename _T, typename _A,                                 \
              template <class _U> class _OP,                            \
              class _L, class _R>                                       \
    expr<op_type <vsvec<_T, _A>>,                                        \
         expr<_OP<vsvec<_T, _A>>, _L, _R>,                               \
         vsvec<_T, _A> >                                                 \
    operator the_op (const expr<_OP<vsvec<_T, _A>>, _L, _R>& l,          \
                     const vsvec<_T, _A>& r) {                           \
        return expr<op_type <vsvec<_T, _A>>,                             \
                    expr<_OP<vsvec<_T, _A>>, _L, _R>,                    \
                    vsvec<_T, _A> >(l, r);                               \
    }                                                                   \
    /* scalar, expr */                                                  \
    template <typename _T, typename _A,                                 \
              template <class _U> class _OP,                            \
              class _L, class _R>                                       \
    expr<op_type <vsvec<_T, _A>>, _T,                                    \
         expr<_OP<vsvec<_T, _A>>, _L, _R> >                              \
    operator the_op (const _T& l,                                       \
                     const expr<_OP<vsvec<_T, _A>>, _L, _R>& r) {        \
        return expr<op_type <vsvec<_T, _A>>, _T,                         \
                    expr<_OP<vsvec<_T, _A>>, _L, _R> >(l, r);            \
    }                                                                   \
    /* expr, scalar */                                                  \
    template <typename _T, typename _A,                                 \
              template <class _U> class _OP,                            \
              class _L, class _R>                                       \
    expr<op_type <vsvec<_T, _A>>, expr<_OP<vsvec<_T, _A>>, _L, _R>, _T >  \
    operator the_op (const expr<_OP<vsvec<_T, _A>>, _L, _R>& l,          \
                     const _T& r) {                                     \
        return expr<op_type <vsvec<_T, _A>>,                             \
                    expr<_OP<vsvec<_T, _A>>, _L, _R>, _T >(l, r);        \
    }                                                                   \
    /* expr, expr */                                                    \
    template <typename _T, typename _A,                                 \
              template <class _U1> class _LOP,                          \
              class _LL, class _LR,                                     \
              template <class _U2> class _ROP,                          \
              class _RL, class _RR>                                     \
    expr<op_type <vsvec<_T, _A>>,                                        \
         expr<_LOP<vsvec<_T, _A>>, _LL, _LR>,                            \
         expr<_ROP<vsvec<_T, _A>>, _RL, _RR> >                           \
    operator the_op (const expr<_LOP<vsvec<_T, _A>>, _LL, _LR>& l,       \
                     const expr<_ROP<vsvec<_T, _A>>, _RL, _RR>& r) {     \
        return expr<op_type <vsvec<_T, _A>>,                             \
                    expr<_LOP<vsvec<_T, _A>>, _LL, _LR>,                 \
                    expr<_ROP<vsvec<_T, _A>>, _RL, _RR> > (l, r);        \
    }                                                                   \
    /* assign scalar */                                                 \
    template <typename _T, typename _A>                                 \
    vsvec<_T, _A>&                                                       \
    operator the_op_assign (vsvec<_T, _A>& a, const _T& b) {             \
        expr <op_type <vsvec<_T, _A>>, vsvec<_T, _A>, _T> e(a, b);        \
        a = e;                                                          \
        return a;                                                       \
    }                                                                   \
    /* assign vsvec */                                                   \
    template <typename _T, typename _A>                                 \
    vsvec<_T, _A>&                                                       \
    operator the_op_assign (vsvec<_T, _A>& a,                            \
                            const vsvec<_T, _A>& b) {                    \
        expr <op_type <vsvec<_T, _A>>,                                   \
              vsvec<_T, _A>, vsvec<_T, _A> > e(a, b);                     \
        a = e;                                                          \
        return a;                                                       \
    }                                                                   \
    /* assign expr */                                                   \
    template <typename _T, typename _A,                                 \
              template <class _U> class _OP,                            \
              class _L, class _R>                                       \
    vsvec<_T, _A>&                                                       \
    operator the_op_assign (vsvec<_T, _A>& a,                            \
                            const expr<_OP<vsvec<_T, _A>>, _L, _R>& b) { \
        expr <op_type <vsvec<_T, _A>>, vsvec<_T, _A>,                     \
              expr<_OP<vsvec<_T, _A>>, _L, _R > > e(a, b);               \
        a = e;                                                          \
        return a;                                                       \
    }                                                                   \


    BINARY_OP(|, |=, op::bit_or)
    BINARY_OP(&, &=, op::bit_and)
    BINARY_OP(^, ^=, op::bit_xor)

    BINARY_OP(+, +=, op::add)
    BINARY_OP(-, -=, op::sub)
    BINARY_OP(*, *=, op::mul)
    BINARY_OP(/, /=, op::div)

#undef BINARY_OP

#define CMP_OP(the_op, op_type)                                         \
    /* cmp vsvec, vsvec */                                                \
    template <typename _T, typename _A>                                 \
    typename vsvec<_T, _A>::mask_type                                    \
    operator the_op (const vsvec<_T, _A>& l, const vsvec<_T, _A>& r) {    \
        expr< op_type <vsvec<_T, _A>>,                                   \
              vsvec<_T, _A>, vsvec<_T, _A> > e(l, r);                     \
        typename vsvec<_T, _A>::mask_type rr(e);                         \
        return rr;                                                      \
    }                                                                   \
                                                                        \
    /* cmp scalar, vsvec */                                              \
    template <typename _T, typename _A>                                 \
    typename vsvec<_T, _A>::mask_type                                    \
    operator the_op (const _T& l, const vsvec<_T, _A>& r) {              \
        expr< op_type <vsvec<_T, _A>>, _T, vsvec<_T, _A> > e(l, r);       \
        typename vsvec<_T, _A>::mask_type rr(e);                         \
        return rr;                                                      \
    }                                                                   \
                                                                        \
    /* cmp vsvec, scalar */                                              \
    template <typename _T, typename _A>                                 \
    typename vsvec<_T, _A>::mask_type                                    \
    operator the_op (const vsvec<_T, _A>& l, const _T& r) {              \
        expr< op_type <vsvec<_T, _A>>, vsvec<_T, _A>, _T> e(l, r);        \
        typename vsvec<_T, _A>::mask_type rr(e);                         \
        return rr;                                                      \
    }                                                                   \
                                                                        \
    /* cmp expr, vsvec */                                                \
    template <typename _T, typename _A,                                 \
              template <class _U> class _OP,                            \
              class _L, class _R>                                       \
    typename vsvec<_T, _A>::mask_type                                    \
    operator the_op (const expr<_OP<vsvec<_T, _A>>, _L, _R>& l,          \
                     const vsvec<_T, _A>& r) {                           \
        expr<op_type <vsvec<_T, _A>>,                                    \
             expr<_OP<vsvec<_T, _A>>, _L, _R>,                           \
             vsvec<_T, _A> > e(l, r);                                    \
        typename vsvec<_T, _A>::mask_type rr(e);                         \
        return rr;                                                      \
    }                                                                   \
                                                                        \
    /* cmp expr, scalar */                                              \
    template <typename _T, typename _A,                                 \
              template <class _U> class _OP,                            \
              class _L, class _R>                                       \
    typename vsvec<_T>::mask_type                                        \
    operator the_op (const expr<_OP<vsvec<_T, _A>>, _L, _R>& l,          \
                     const _T& r) {                                     \
        expr<op_type <vsvec<_T, _A>>,                                    \
             expr<_OP<vsvec<_T, _A>>, _L, _R>,                           \
             _T> e(l, r);                                               \
        typename vsvec<_T>::mask_type rr(e);                             \
        return rr;                                                      \
    }                                                                   \
                                                                        \
    /* cmp vsvec, expr */                                                \
    template <typename _T, typename _A,                                 \
              template <class _U> class _OP,                            \
              class _L, class _R>                                       \
    typename vsvec<_T, _A>::mask_type                                    \
    operator the_op (const vsvec<_T, _A>& l,                             \
                     const expr<_OP<vsvec<_T, _A>>, _L, _R>& r) {        \
        expr<op_type <vsvec<_T, _A>>,                                    \
             vsvec<_T, _A>,                                              \
             expr<_OP<vsvec<_T, _A>>, _L, _R> > e(l, r);                 \
        typename vsvec<_T, _A>::mask_type rr(e);                         \
        return rr;                                                      \
    }                                                                   \
                                                                        \
    /* cmp vsvec, expr */                                                \
    template <typename _T, typename _A,                                 \
              template <class _U> class _OP,                            \
              class _L, class _R>                                       \
    typename vsvec<_T>::mask_type                                        \
    operator the_op (const _T& l,                                       \
                     const expr<_OP<vsvec<_T, _A>>, _L, _R>& r) {        \
        expr<op_type <vsvec<_T, _A>>,                                    \
             _T,                                                        \
             expr<_OP<vsvec<_T, _A>>, _L, _R> > e(l, r);                 \
        typename vsvec<_T>::mask_type rr(e);                             \
        return rr;                                                      \
    }                                                                   \


    CMP_OP(<, op::lt)
    CMP_OP(<=, op::le)
    CMP_OP(==, op::eq)
    CMP_OP(!=, op::ne)
    CMP_OP(>=, op::ge)
    CMP_OP(>, op::gt)

#undef CMP_OP

#define SHIFT_OP(the_op, the_op_assign, op_type)                        \
    /* vsvec, unsigned */                                                \
    template <typename _T, typename _A>                                 \
    expr<op_type <vsvec<_T, _A>>, vsvec<_T, _A>, unsigned>                \
    operator the_op (const vsvec<_T, _A>& v, unsigned s)  {              \
        expr<op_type <vsvec<_T, _A>>, vsvec<_T, _A>, unsigned> e(v, s);   \
        return e;                                                       \
    }                                                                   \
    /* expr, unsigned */                                                \
    template <typename _T, typename _A,                                 \
              template <class _U> class _OP,                            \
              class _L, class _R>                                       \
    expr<op_type <vsvec<_T, _A>>,                                        \
         expr<_OP<vsvec<_T, _A>>, _L, _R>, unsigned>                     \
    operator the_op (const expr<_OP<vsvec<_T, _A>>, _L, _R>& v,          \
                     unsigned s)  {                                     \
        expr<op_type <vsvec<_T, _A>>,                                    \
             expr<_OP<vsvec<_T, _A>>, _L, _R>, unsigned> e(v, s);        \
        return e;                                                       \
    }                                                                   \
    /* self vsvec, unsigned */                                           \
    template <typename _T, typename _A>                                 \
    vsvec<_T, _A>&                                                       \
    operator the_op_assign (vsvec<_T, _A>& v, unsigned s)  {             \
        v = v the_op s;                                                 \
        return v;                                                       \
    }                                                                   \

    SHIFT_OP(<<, <<=, op::shl)
    SHIFT_OP(>>, >>=, op::shr)

#undef SHIFT_OP
}

// Local variables:
// mode: c++
// end:
#endif
