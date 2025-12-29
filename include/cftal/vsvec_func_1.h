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
#if !defined (__CFTAL_VSVEC_FUNC_1_H__)
#define __CFTAL_VSVEC_FUNC_1_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/vsvec_func_0.h>
#include <cftal/vsvec_lookup.h>
#include <cftal/as.h>
#include <cftal/math/horner.h>
#include <sstream>

namespace cftal {

    template <std::size_t _BITS, typename _T, typename _A>
    vsvec<_T, _A>
    round_to_nearest_even_last_bits(const  vsvec<_T, _A>& v);

    template <std::size_t _BITS, typename _T, typename _A>
    vsvec<_T, _A>
    round_to_zero_last_bits(const vsvec<_T, _A>& v);

    template <typename _AD, typename _AF>
    void
    split_f64_to_f32pair(const vsvec<double, _AD>& s,
                         vsvec<float, _AF>& h, vsvec<float, _AF>& l);

    namespace impl {

        // vsvec casts between types of different sizes, must return
        // a new object because of the size member
        template <typename _D, typename _S, typename _AD, typename _AS,
                  bool _SIZEOF_D_EQ_S>
        struct vsvec_cast_bits {
            static
            vsvec<_D, _AD>
            v(const vsvec<_S, _AS>& s) {
                const _D* b=reinterpret_cast<const _D*>(s.begin());
                const _D* e=reinterpret_cast<const _D*>(s.end());
                vsvec<_D, _AD> rs{b, e};
                return rs;
            }
        };

        // vsvec casts between types of same sizes
        template <typename _D, typename _S, typename _AD, typename _AS>
        struct vsvec_cast_bits<_D, _S, _AD, _AS, true> {
            static
            const vsvec<_D, _AD>&
            v(const vsvec<_S, _AS>& s) {
                const vsvec<_D, _AD>& rs=
                    reinterpret_cast<const vsvec<_D, _AD>&>(s);
                return rs;
            }
        };

        template <typename _D, typename _S, typename _AD, typename _AS>
        struct cast_bits<vsvec<_D, _AD>, vsvec<_S, _AS> >
            : public vsvec_cast_bits<_D, _S, _AD, _AS,
                                     sizeof(_D) == sizeof(_S)> {
        };

        template <typename _DS, typename _ADS>
        struct cast_bits<vsvec<_DS, _ADS>, vsvec<_DS, _ADS> > {
            static
            const vsvec<_DS, _ADS>&
            v(const vsvec<_DS, _ADS>& s) {
                return s;
            }
        };
    }

    namespace op_4_vsvec {

        template <typename _T>
        struct f_select {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const typename vec<_T, _N>::mask_type& s,
              const vec<_T, _N>& on_true,
              const vec<_T, _N>& on_false) {
                return select(s, on_true, on_false);
            }

            template <size_t _N>
            static
            vec<_T, _N>
            v(const typename vec<_T, _N>::mask_type& s,
              const vec<_T, _N>& on_true,
              const _T& on_false) {
                vec<_T, _N> f=on_false;
                return select(s, on_true, f);
            }

            template <size_t _N>
            static
            vec<_T, _N>
            v(const typename vec<_T, _N>::mask_type& s,
              const _T& on_true,
              const vec<_T, _N> & on_false) {
                vec<_T, _N> t=on_true;
                return select(s, t, on_false);
            }

            template <size_t _N, typename _U>
            static
            vec<_T, _N>
            v(const vec<_U, _N>& s,
              const _T& on_true,
              const _T& on_false) {
                vec<_T, _N> t=on_true;
                vec<_T, _N> f=on_false;
                return select(s, t, f);
            }
        };

        template <typename _T>
        struct f_combine_even_odd {
            template <size_t _N>
            static
            vec<_T, 2*_N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return combine_even_odd(a, b);
            }
        };

        template <typename _T>
        struct f_even_elements {
            template <size_t _N>
            static
            vec<_T, _N/2>
            v(const vec<_T, _N>& a) {
                return even_elements(a);
            }
        };

        template <typename _T>
        struct f_odd_elements {
            template <size_t _N>
            static
            vec<_T, _N/2>
            v(const vec<_T, _N>& a) {
                return odd_elements(a);
            }
        };

        template <typename _T>
        struct f_select_even_odd {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return select_even_odd(a, b);
            }
        };

        template <typename _T>
        struct f_copy_even_to_odd {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return copy_even_to_odd(a);
            }
        };

        template <typename _T>
        struct f_copy_odd_to_even {
            template <size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return copy_odd_to_even(a);
            }
        };
    }

    namespace func {
        template <typename _T> struct f_select {};
        template <typename _T> struct f_combine_even_odd {};
        template <typename _T> struct f_even_elements {};
        template <typename _T> struct f_odd_elements {};
        template <typename _T> struct f_select_even_odd {};
        template <typename _T> struct f_copy_even_to_odd {};
        template <typename _T> struct f_copy_odd_to_even {};

        template <typename _T, typename _A>
        struct f_select<vsvec<_T, _A>> :
            public op_4_vsvec::f_select<_T> {};

        template <typename _T, typename _A>
        struct f_combine_even_odd<vsvec<_T, _A>> :
            public op_4_vsvec::f_combine_even_odd<_T> {};

        template <typename _T, typename _A>
        struct f_even_elements<vsvec<_T, _A>> :
            public op_4_vsvec::f_even_elements<_T> {};

        template <typename _T, typename _A>
        struct f_odd_elements<vsvec<_T, _A>> :
            public op_4_vsvec::f_odd_elements<_T> {};

        template <typename _T, typename _A>
        struct f_select_even_odd<vsvec<_T, _A>> :
            public op_4_vsvec::f_select_even_odd<_T> {};

        template <typename _T, typename _A>
        struct f_copy_even_to_odd<vsvec<_T, _A>> :
            public op_4_vsvec::f_copy_even_to_odd<_T> {};

        template <typename _T, typename _A>
        struct f_copy_odd_to_even<vsvec<_T, _A>> :
            public op_4_vsvec::f_copy_odd_to_even<_T> {};
    }


    // select helper
    template <size_t _N,
              typename _T, typename _A,
              typename _U, typename _AU,
              typename _L, typename _R>
    vec<_T, _N>
    eval_i(const expr<func::f_select<vsvec<_T, _A>>, vsvec<_U, _AU>,
           expr<func::tri_data<vsvec<_T, _A>>, _L, _R> >& e,
           size_t i) {
        return func::f_select<vsvec<_T, _A>>::v(
            eval_i<_N, typename vec<_T, _N>::mask_value_type>(e._l, i),
            eval_i<_N, _T>(e._r._l, i),
            eval_i<_N, _T>(e._r._r, i));
    }

    // select _T, _T using vsvec<_U> as mask type
    template <typename _T, typename _U, typename _UA>
    expr<func::f_select<vsvec<_T>>,
         vsvec<_U, _UA> /* typename vsvec<_T, _A>::mask_type*/ ,
         expr<func::tri_data<vsvec<_T>>, _T, _T> >
    select(const vsvec<_U, _UA>& m, const _T& on_true, const _T& on_false) {
        using r_expr_t= expr<func::tri_data<vsvec<_T>>, _T, _T>;
        r_expr_t er(on_true, on_false);
        expr<func::f_select<vsvec<_T>>,
             typename vsvec<_T>::mask_type, r_expr_t>
            e(m, er);
        return e;
    }

    // select _T, vsvec
    template <typename _U, typename _UA, typename _T, typename _A>
    expr<func::f_select<vsvec<_T, _A>>,
         typename vsvec<_T, _A>::mask_type,
         expr<func::tri_data<vsvec<_T, _A>>, _T, vsvec<_T, _A> > >
    select(const vsvec<_U, _UA>& m,
           const _T& on_true, const vsvec<_T, _A>& on_false) {
        using r_expr_t= expr<func::tri_data<vsvec<_T, _A>>, _T, vsvec<_T, _A> >;
        r_expr_t er(on_true, on_false);
        expr<func::f_select<vsvec<_T, _A>>,
             typename vsvec<_T, _A>::mask_type, r_expr_t>
            e(m, er);
        return e;
    }

    // select vsvec, _T
    template <typename _U, typename _UA, typename _T, typename _A>
    // vsvec<_T, _A>
    expr<func::f_select<vsvec<_T, _A>>,
         typename vsvec<_T, _A>::mask_type,
         expr<func::tri_data<vsvec<_T, _A>>, vsvec<_T, _A>, _T > >
    select(const vsvec<_U, _UA>& m,
           const vsvec<_T, _A>& on_true, const _T& on_false) {
        using r_expr_t= expr<func::tri_data<vsvec<_T, _A>>, vsvec<_T, _A>, _T>;
        r_expr_t er(on_true, on_false);
        expr<func::f_select<vsvec<_T, _A>>,
             typename vsvec<_T, _A>::mask_type, r_expr_t>
            e(m, er);
        return e;
    }

    // select vsvec, vsvec
    template <typename _U, typename _UA,
              typename _T, typename _A>
    expr<func::f_select<vsvec<_T, _A>>,
         typename vsvec<_T, _A>::mask_type,
         expr<func::tri_data<vsvec<_T, _A>>, vsvec<_T, _A>, vsvec<_T, _A> > >
    select(const vsvec<_U, _UA>& m,
           const vsvec<_T, _A>& on_true, const vsvec<_T, _A>& on_false) {
        using r_expr_t= expr<func::tri_data<vsvec<_T, _A>>,
                             vsvec<_T, _A>, vsvec<_T, _A> >;
        r_expr_t er(on_true, on_false);
        expr<func::f_select<vsvec<_T, _A>>,
             typename vsvec<_T, _A>::mask_type, r_expr_t>
            e(m, er);
        return e;
    }

    // select vsvec, expr
    template <typename _U, typename _UA,
              typename _T, typename _A,
              template <class _TT> class _OP,
              class _L, class _R>
    expr<func::f_select<vsvec<_T, _A>>,
         typename vsvec<_T, _A>::mask_type,
         expr<func::tri_data<vsvec<_T, _A>>, vsvec<_T, _A>,
              expr<_OP<vsvec<_T, _A>>, _L, _R> > >
    select(const vsvec<_U, _UA>& m,
           const vsvec<_T, _A>& on_true,
           const expr<_OP<vsvec<_T, _A>>, _L, _R>& on_false) {
        using r_expr_t= expr<func::tri_data<vsvec<_T, _A>>,
                             vsvec<_T, _A>,
                             expr<_OP<vsvec<_T, _A>>, _L, _R> >;
        r_expr_t er(on_true, on_false);
        expr<func::f_select<vsvec<_T, _A>>,
             typename vsvec<_T, _A>::mask_type, r_expr_t>
            e(m, er);
        return e;
    }

    // select expr, vsvec
    template <typename _U, typename _UA,
              typename _T, typename _A,
              template <class _TT> class _OP,
              class _L, class _R>
    expr<func::f_select<vsvec<_T, _A>>,
         typename vsvec<_T, _A>::mask_type,
         expr<func::tri_data<vsvec<_T, _A>>,
              expr<_OP<vsvec<_T, _A>>, _L, _R>,
              vsvec<_T, _A> > >
    select(const vsvec<_U, _UA>& m,
           const expr<_OP<vsvec<_T, _A>>, _L, _R>& on_true,
           const vsvec<_T, _A>& on_false) {
        using r_expr_t= expr<func::tri_data<vsvec<_T, _A>>,
                             expr<_OP<vsvec<_T, _A>>, _L, _R>,
                             vsvec<_T, _A> >;
        r_expr_t er(on_true, on_false);
        expr<func::f_select<vsvec<_T, _A>>,
             typename vsvec<_T, _A>::mask_type, r_expr_t>
            e(m, er);
        return e;
    }

    // select expr, expr
    template <typename _U, typename _UA,
              typename _T, typename _A,
              template <class _TT1> class _LOP,
              class _LL, class _LR,
              template <class _TT> class _ROP,
              class _RL, class _RR>
    expr<func::f_select<vsvec<_T, _A>>,
         typename vsvec<_T, _A>::mask_type,
         expr<func::tri_data<vsvec<_T, _A>>,
              expr<_LOP<vsvec<_T, _A>>, _LL, _LR>,
              expr<_ROP<vsvec<_T, _A>>, _RL, _RR> > >
    select(const vsvec<_U, _UA>& m,
           const expr<_LOP<vsvec<_T, _A>>, _LL, _LR>& on_true,
           const expr<_ROP<vsvec<_T, _A>>, _RL, _RR>& on_false) {
        using r_expr_t= expr<func::tri_data<vsvec<_T, _A>>,
                             expr<_LOP<vsvec<_T, _A>>, _LL, _LR>,
                             expr<_ROP<vsvec<_T, _A>>, _RL, _RR> >;
        r_expr_t er(on_true, on_false);
        expr<func::f_select<vsvec<_T, _A>>,
             typename vsvec<_T, _A>::mask_type, r_expr_t>
            e(m, er);
        return e;
    }

    // combine even odd helper, returns a double length vector
    template <size_t _N,
              typename _T, typename _A,
              typename _L, typename _R>
    vec<_T, 2*_N>
    eval_i(const expr<func::f_combine_even_odd<vsvec<_T, _A>>, _L, _R>& e,
           size_t i) {
        return func::f_combine_even_odd<vsvec<_T, _A>>::v(
            eval_i<_N, _T>(e._l, i),
            eval_i<_N, _T>(e._r, i));
    }

    template <typename _T, typename _A,
              typename _L, typename _R>
    size_t
    eval_result_size(const expr<func::f_combine_even_odd<vsvec<_T, _A>>, _L, _R>& e) {
        size_t l = eval_result_size(e._l);
        size_t r = eval_result_size(e._r);
        size_t res;
        if (l==1) {
            res = r+r;
        } else if (r==1) {
            res = l+l;
        } else {
            if (__unlikely(l!=r)) {
                std::ostringstream s;
                s << "invalid call to combine_even_odd "
                  << " l==r | (l==1 & r>1) | (l>1 & r==1)): l="
                  << l << " r=" << r;
                throw std::runtime_error(s.str());
            }
            res = l+r;
        }
        return res;
    }

    template <typename _T, typename _A,
              typename _L, typename _R>
    struct operand<expr<func::f_combine_even_odd<vsvec<_T, _A>>, _L, _R> >{
        static
        constexpr
        size_t count() {
            return operand<_L>::count() + operand<_R>::count();
        }
        static
        constexpr
        result_size sizes() {
            return result_size::gt_size;
        }
    };

    TFUNC_A2(combine_even_odd, func::f_combine_even_odd)

    // even elements helper, this method ensures that the argument vector
    // length is greater than 1
    template <size_t _N,
              typename _T,  typename _A,
              typename _L>
    vec<_T, _N/2>
    eval_i(const expr<func::f_even_elements<vsvec<_T, _A>>, _L, void>& e,
           size_t i) {
        return func::f_even_elements<vsvec<_T, _A>>::v(
            eval_i<_N, _T>(e._l, i));
    }

    template <typename _T,  typename _A,
              typename _L>
    size_t
    eval_result_size(const expr<func::f_even_elements<vsvec<_T, _A>>, _L, void>& e) {
        size_t rs = eval_result_size(e._l) >> 1;
        return rs;
    }

    template <typename _T,  typename _A,
              typename _L>
    struct operand<expr<func::f_even_elements<vsvec<_T, _A>>, _L, void> >{
        static
        constexpr
        size_t count() {
            return operand<_L>::count();
        }
        static
        constexpr
        result_size sizes() {
            return result_size::lt_size;
        }
    };

    TFUNC_A1(even_elements, func::f_even_elements)

    // odd elements helper, this method ensures that the argument vector
    // length is greater than 1
    template <size_t _N,
              typename _T, typename _A,
              typename _L>
    vec<_T, _N/2>
    eval_i(const expr<func::f_odd_elements<vsvec<_T, _A>>, _L, void>& e,
           size_t i) {
        return func::f_odd_elements<vsvec<_T, _A>>::v(
            eval_i<_N, _T>(e._l, i));
    }

    template <typename _T,  typename _A,
              typename _L>
    size_t
    eval_result_size(const expr<func::f_odd_elements<vsvec<_T, _A>>, _L, void>& e) {
        size_t rs = eval_result_size(e._l) >> 1;
        return rs;
    }

    template <typename _T,  typename _A,
              typename _L>
    struct operand<expr<func::f_odd_elements<vsvec<_T, _A>>, _L, void> >{
        static
        constexpr
        size_t count() {
            return operand<_L>::count();
        }
        static
        constexpr
        result_size sizes() {
            return result_size::lt_size;
        }
    };

    TFUNC_A1(odd_elements, func::f_odd_elements)

    // select even_odd helper, this method ensures the argument vector
    // length is greater than 1
    template <size_t _N,
              typename _T, typename _A,
              typename _L, typename _R>
    vec<_T, _N*2>
    eval_i(const expr<func::f_select_even_odd<vsvec<_T, _A>>, _L, _R>& e,
           size_t i) {
        return func::f_select_even_odd<vsvec<_T, _A>>::v(
            eval_i<_N*2, _T>(e._l, i),
            eval_i<_N*2, _T>(e._r, i));
    }

    TFUNC_A2(select_even_odd, func::f_select_even_odd)

    // copy even_odd helper, this method ensures the argument vector
    // length is greather than 1
    template <size_t _N,
              typename _T, typename _A,
              typename _L>
    vec<_T, _N*2>
    eval_i(const expr<func::f_copy_even_to_odd<vsvec<_T, _A>>, _L, void>& e,
           size_t i) {
        return func::f_copy_even_to_odd<vsvec<_T, _A>>::v(
            eval_i<_N*2, _T>(e._l, i));
    }

    TFUNC_A1(copy_even_to_odd, func::f_copy_even_to_odd)

    // copy odd to even helper, this method ensures the argument vector
    // length is greather than 1
    template <size_t _N,
              typename _T, typename _A,
              typename _L>
    vec<_T, _N*2>
    eval_i(const expr<func::f_copy_odd_to_even<vsvec<_T, _A>>, _L, void>& e,
           size_t i) {
        return func::f_copy_even_to_odd<vsvec<_T, _A>>::v(
            eval_i<_N*2, _T>(e._l, i));
    }

    TFUNC_A1(copy_odd_to_even, func::f_copy_odd_to_even)

    namespace op_4_vsvec {
        // cvt<> helper class
        template <typename _T>
        struct f_cvt {
            template <typename _S, size_t _N>
            static
            vec<_T, _N>
            v(const vec<_S, _N>& s) {
                return ::cftal::impl::cvt<vec<_T, _N>, vec<_S, _N> >::v(s);
            }
        };
    }

    namespace func {
        // template definition
        template <typename _T> struct f_cvt {};

        // template specialization
        template <typename _T, typename _A>
        struct f_cvt<vsvec<_T, _A>> : public op_4_vsvec::f_cvt<_T> {};
    }

    namespace impl {

        // cvt<> worker class
        template <typename _D, typename _AD, typename _S, typename _AS>
        struct cvt<vsvec<_D, _AD>, vsvec<_S, _AS> > {
            static
            vsvec<_D, _AD>
            v(const vsvec<_S, _AS>& s) {
                using expr_t = expr<func::f_cvt<vsvec<_D, _AD>>,
                                    vsvec<_S, _AS>, void>;
                expr_t e(s);
                vsvec<_D, _AD> r(e);
                return r;
            }
        };

        // cvt<> worker class if destination and src are the same
        // types
        template <typename _DS, typename _ADS>
        struct cvt<vsvec<_DS, _ADS>, vsvec<_DS, _ADS> > {
            static
            const vsvec<_DS, _ADS>&
            v(const vsvec<_DS, _ADS>& s) {
                return s;
            }
        };

    }

    template <size_t _N,
              typename _T, typename _A,
              typename _S, typename _AS>
    inline
    vec<_T, _N>
    eval_i(const expr<func::f_cvt<vsvec<_T, _A>>,
           vsvec<_S, _AS>, void>& e, size_t i) {
        return func::f_cvt<vsvec<_T, _A>>::v(eval_i<_N, _S>(e._l, i));
    }

    namespace impl {

        struct inspect_any_of {
            bool _ret;
            inspect_any_of() : _ret(false) {}

            template <typename _T, size_t _N>
            bool operator()(const vec<_T, _N>& v) {
                bool t=any_of(v);
                _ret = t;
                // if we found something we can stop inspection
                return _ret == true ? false : true;
            }
        };

        struct inspect_all_of {
            bool _ret;
            inspect_all_of() : _ret(true) {}

            template <typename _T, size_t _N>
            bool operator()(const vec<_T, _N>& v) {
                bool t=all_of(v);
                _ret = t;
                // if we not found all_of(v) we can stop inspection
                return _ret == false ? false : true;
            }
        };

        struct inspect_none_of {
            bool _ret;
            inspect_none_of() : _ret(true) {}

            template <typename _T, size_t _N>
            bool operator()(const vec<_T, _N>& v) {
                bool t=none_of(v);
                _ret = t;
                // if we found not none_of(v) we can stop inspection
                return _ret == false ? false : true;
            }
        };
    }

    template <typename _T, typename _A>
    bool
    any_of(const vsvec<_T, _A>& v);

    template <typename _T, typename _A>
    bool
    all_of(const vsvec<_T, _A>& v);

    template <typename _T, typename _A>
    bool
    none_of(const vsvec<_T, _A>& v);

#if 0
    // extern template class vsvec<float, aligned_allocator<float, 64>>;
    // extern template class vsvec<double, aligned_allocator<double, 64>>;

    template <typename _T, size_t _N>
    struct array_ref {
        const _T (&_v)[_N];
        constexpr
        array_ref(const _T (&v) [_N]) : _v(v) {}
    };

    // return the array stored in the array ref
    template <size_t _N, typename _T, typename _U, size_t _M>
    constexpr
    const _U (&eval_i(const array_ref<_U, _M>& v, size_t))[_M] {
        return v._v;
    }

    // operand count of array_refs is large to avoid unrolling
    template <typename _T, size_t _N>
    struct operand<array_ref<_T, _N> > {
        static
        constexpr
        size_t count() {
            return 16;
        }
    };

    namespace math {

        template <typename _T, typename _A>
        struct vhorner {
            template <std::size_t _N, typename _C, std::size_t _M>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& x, const _C(&a)[_M]) {
                return horner(x, a);
            }
        };

        template <typename _T, typename _A, typename _C, size_t _N>
        vsvec<_T, _A>
        horner(const vsvec<_T, _A>& x, const _C (&a)[_N]) {
            const array_ref<_C, _N> ar(a);
            expr <vhorner<_T, _A>, vsvec<_T, _A>, array_ref<_C, _N> > e(x, ar);
            vsvec<_T, _A> r(e);
            return r;
        }

        template <typename _T, typename _A>
        struct vhorner2 {
            template <std::size_t _N, typename _C, std::size_t _M>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& x, const vec<_T, _N>& x2,
              const _C(&a)[_M]) {
                return horner2(x, x2, a);
            }
        };

    }

    template <size_t _N, typename _T, typename _A, typename _C, size_t _M>
    vec<_T, _N>
    eval_i(const expr<math::vhorner2<_T, _A>,
           expr<math::vhorner2<_T, _A>, vsvec<_T, _A>, vsvec<_T, _A> >,
           array_ref<_C, _M> >& e,
           size_t i) {
        return math::vhorner2<_T, _A>::v(eval_i<_N, _T>(e._l._l, i),
                                         eval_i<_N, _T>(e._l._r, i),
                                         eval_i<_N, _T>(e._r, i));
    }

    namespace math {

        template <typename _T, typename _A,
                  typename _C, size_t _N>
        vsvec<_T, _A>
        horner2(const vsvec<_T, _A>& x, const vsvec<_T, _A>& x2,
                const _C (&a)[_N]) {
            using expr_t = expr<vhorner2<_T, _A>, vsvec<_T, _A>, vsvec<_T, _A> >;
            expr_t e0(x, x2);
            array_ref<_C, _N> ar(a);
            expr <vhorner2<_T, _A>, expr_t, array_ref<_C, _N> > e(e0, ar);
            vsvec<_T, _A> r(e);
            return r;
        }
    }
#endif

}

template <std::size_t _BITS, typename _T, typename _A>
cftal::vsvec<_T, _A>
cftal::round_to_nearest_even_last_bits(const  vsvec<_T, _A>& v)
{
    static_assert(_BITS>0 && _BITS < sizeof(_T)*8);

    using int_type =
        select_t<std::is_same_v<_T, double>,
                 int64_t,
                 select_t<std::is_same_v<_T, float>,
                          int32_t,
                          select_t<std::is_same_v<_T, f16_t>,
                                   int16_t,
                                   _T>
                          >
                 >;
    using _IA= typename std::allocator_traits<_A>::template
        rebind_alloc<int_type>;
    using vi_type= vsvec<int_type, _IA>;
    using vmi_type = typename vi_type::mask_type;
    return impl::round_to_nearest_even_last_bits<vsvec<_T, _A>, _T,
                                                 vi_type,
                                                 int_type,
                                                 vmi_type,
                                                 _BITS>(v);
}

template <std::size_t _BITS, typename _T, typename _A>
cftal::vsvec<_T, _A>
cftal::round_to_zero_last_bits(const  vsvec<_T, _A>& v)
{
    static_assert(_BITS>0 && _BITS < sizeof(_T)*8);

    using int_type =
        select_t<std::is_same_v<_T, double>,
                 int64_t,
                 select_t<std::is_same_v<_T, float>,
                          int32_t,
                          select_t<std::is_same_v<_T, f16_t>,
                                   int16_t,
                                   _T>
                          >
                 >;
    using _IA= typename std::allocator_traits<_A>::template
        rebind_alloc<int_type>;
    using vi_type= vsvec<int_type, _IA>;
    using vmi_type = typename vi_type::mask_type;
    return impl::round_to_zero_last_bits<vsvec<_T, _A>, _T,
                                         vi_type,
                                         int_type,
                                         vmi_type,
                                         _BITS>(v);
}

template <typename _AD, typename _AF>
void
cftal::split_f64_to_f32pair(const vsvec<double, _AD>& s,
                            vsvec<float, _AF>& h, vsvec<float, _AF>& l)
{
    using vf_type = vsvec<float, _AF>;
    using vhf_type = vsvec<double, _AD>;
    vf_type th = cvt<vf_type>(s);
    vhf_type dh = cvt<vhf_type>(th);
    vhf_type dl = s - dh;
    h = th;
    l = cvt<vf_type>(dl);
}

template <typename _T, typename _A>
bool
cftal::any_of(const vsvec<_T, _A>& v)
{
    impl::inspect_any_of c;
    v.inspect(c);
    return c._ret;
}

template <typename _T, typename _A>
bool
cftal::all_of(const vsvec<_T, _A>& v)
{
    impl::inspect_all_of c;
    v.inspect(c);
    return c._ret;
}

template <typename _T, typename _A>
bool
cftal::none_of(const vsvec<_T, _A>& v)
{
    impl::inspect_none_of c;
    v.inspect(c);
    return c._ret;
}

// Local variables:
// mode: c++
// end:
#endif
