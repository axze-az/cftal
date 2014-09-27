#if !defined (__CFTAL_SIMD_VEC_H__)
#define __CFTAL_SIMD_VEC_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <cftal/x86vec_expr.h>
#include <initializer_list>
#include <type_traits>
#include <cmath>

namespace cftal {


        template <typename _T>
        class init_list {
                const _T* _begin;
                const _T* _end;
        public:
                constexpr init_list(const _T* b, const _T* e)
                        : _begin(b), _end(e) {}
                constexpr const _T* begin() const { return _begin; }
                constexpr const _T* end() const { return _end; }
                constexpr std::size_t size() const { return end() - begin(); }
        };

        template <typename _T, std::size_t _N>
        constexpr init_list<_T>
        init_lo_half(init_list<_T> l) {
                constexpr std::size_t s = l.size();
                constexpr std::size_t ns= (s < _N/2 ? s : _N/2);
                constexpr const _T* p= l.begin();
                return init_list<_T>(p, p+ ns);
        }

        template <typename _T, std::size_t _N>
        constexpr init_list<_T>
        init_hi_half(init_list<_T> l) {
                constexpr std::size_t s = l.size();
                constexpr std::size_t ns= (s > _N/2 ? s - _N/2 : 0);
                constexpr const _T* p= l.begin() + _N/2;
                return init_list<_T>(p, p+ ns);
        }



        template <unsigned _N>
        struct const_uint {
                enum { v = _N };
        };

        template <typename _T>
        struct expr_traits {
                using type = const _T;
        };

        template <class _OP, class _L, class _R>
        struct expr {
                typename expr_traits<_L>::type _l;
                typename expr_traits<_R>::type _r;
                constexpr expr(const _L& l, const _R& r) :
                        _l(l), _r(r) {}
        };

        template <class _OP, class _L>
        struct expr<_OP, _L, void> {
                typename expr_traits<_L>::type _l;
                constexpr expr(const _L& l) : _l(l) {}
        };

        template <typename _T>
        inline
        const _T&
        eval(const _T& v) {
                return v;
        }

        template <class _OP, class _L, class _R>
        inline
        typename _OP::full_type
        eval(const expr<_OP, _L, _R>& e) {
                return _OP::v(eval(e._l), eval(e._r));
        }

        template <class _OP, class _L>
        inline
        typename _OP::full_type
        eval(const expr<_OP, _L, void>& e) {
                return _OP::v(eval(e._l));
        }

        template <class _M, class _T>
        _T select(const _M& m,
                  const _T& on_true, const _T& on_false);

        template <typename _T, std::size_t _N >
        class alignas(sizeof(_T)*_N) vec {
        public:
                // value type
                using value_type = _T;
                // vector with half the length
                using half_type = vec<_T, _N/2>;
                // type of value of a mask vector
                using mask_value_type =
                        typename half_type::mask_value_type;
                // vector of mask values
                using mask_type = vec<mask_value_type, _N>;

                vec() = default;
                vec(const vec& r) = default;
                vec(vec&& r) = default;
                vec& operator=(const vec& r) = default;
                vec& operator=(vec&& r) = default;

                vec(const _T& v);
                vec(const _T& v, bool splat);
                vec(std::initializer_list<_T> l);
                vec(init_list<_T> l);
                vec(const half_type& lh, bool splat=true);
                vec(const half_type& lh, const half_type& hh);
                const half_type& lh() const;
                const half_type& hh() const;

                template <template <class _U, std::size_t _M>
                          class _OP,
                          class _L, class _R>
                        vec(const expr<_OP<_T, _N>, _L, _R>& r);

        private:
                static_assert(0==(_N & (_N-1)),
                              "_N is not a power of 2");
                vec<_T, _N/2> _l;
                vec<_T, _N/2> _h;
        };

        template <typename _T, std::size_t _N>
        const typename vec<_T, _N>::half_type&
        lo_half(const vec<_T, _N>& v);

        template <typename _T, std::size_t _N>
        const typename vec<_T, _N>::half_type&
        hi_half(const vec<_T, _N>& v);

        template <typename _T, std::size_t _N>
        vec<_T, _N>
        select(const typename vec<_T, _N>::mask_type& m,
               const vec<_T, _N>& on_true,
               const vec<_T, _N>& on_false);

        /* permute low and high halves of s */
        template <int _LH, int _HH,
                  typename _T, std::size_t _N>
        vec<_T, _N>
        permute(const vec<_T, _N>& s);

        /* permute low and high halves of s */
        template <int _LH, int _HH,
                  typename _T, std::size_t _N>
        vec<_T, _N>
        permute(const vec<_T, _N>& s0,
                const vec<_T, _N>& s1);



#define DECL_CMP_OPS(op)                                                \
        template <typename _T, std::size_t _N>                          \
        typename vec<_T, _N>::mask_type                                 \
        operator op (const vec<_T, _N>& a,                              \
                     const vec<_T, _N>& b);                             \
                                                                        \
        template <typename _T, std::size_t  _N>                         \
        typename vec<_T, _N>::mask_type                                 \
        operator op (const vec<_T, _N>& a,                              \
                     const typename vec<_T, _N>::value_type& b);        \
                                                                        \
        template <typename _T, std::size_t  _N>                         \
        typename vec<_T, _N>::mask_type                                 \
        operator op (const typename vec<_T, _N>::value_type& a,         \
                     const vec<_T, _N>& b)

                DECL_CMP_OPS(<);
        DECL_CMP_OPS(<=);
        DECL_CMP_OPS(==);
        DECL_CMP_OPS(!=);
        DECL_CMP_OPS(>=);
        DECL_CMP_OPS(>);

#undef DECL_CMP_OPS

        template <typename _T>
        class vec<_T, 1> {
        public:
                using value_type = _T;
                using mask_value_type = bool;
                using mask_type = vec<mask_value_type, 1>;

                vec() = default;
                vec(const vec& r) = default;
                vec(vec&& r) = default;
                vec& operator=(const vec& r) = default;
                vec& operator=(vec&& r) = default;

                vec(const _T& v);
                vec(const _T& v, bool splat);
                _T operator()() const;

                template <template <class _U, std::size_t _M>
                          class _OP,
                          class _L, class _R>
                vec(const expr<_OP<_T, 1>, _L, _R>& r);

        private:
                _T _v;
        };

        template <typename _T>
        vec<_T, 1>
        select(const typename vec<_T, 1>::mask_type& m,
               const vec<_T, 1>& on_true,
               const vec<_T, 1>& on_false);

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
                                return _R(
                                        _OP<_T, _N/2>::v(lo_half(a),
                                                         lo_half(b)),
                                        _OP<_T, _N/2>::v(hi_half(a),
                                                         hi_half(b)));
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
                                        _OP<_T, _N/2>::v(lo_half(a)),
                                        _OP<_T, _N/2>::v(hi_half(a)));
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
                                        _OP<_T, _N/2>::v(lo_half(a),
                                                         lo_half(b),
                                                         lo_half(c)),
                                        _OP<_T, _N/2>::v(hi_half(a),
                                                         hi_half(b),
                                                         hi_half(c)));
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
                };

                template <typename _T, std::size_t _N>
                struct shr : public bin<shr, _T, _N> {
                };

                // constant shift operators
                template <typename _T, std::size_t _N, unsigned _S>
                struct const_shl {
                        using full_type = vec<_T, _N>;
                        static
                        full_type
                        v(const full_type& a) {
                                return full_type(
                                        const_shl<_T, _N/2, _S>::v(lo_half(a)),
                                        const_shl<_T, _N/2, _S>::v(hi_half(a)));
                        }
                };

                template <typename _T, std::size_t _N, unsigned _S>
                struct const_shr {
                        using full_type = vec<_T, _N>;
                        static
                        full_type
                        v(const full_type& a) {
                                return full_type(
                                        const_shr<_T, _N/2, _S>::v(lo_half(a)),
                                        const_shr<_T, _N/2, _S>::v(hi_half(a)));
                        }
                };

                template <typename _T>
                struct lt<_T, 1> {
                        using full_type = vec<_T, 1>;
                        using mask_type = typename full_type::mask_type;
                        static
                        mask_type
                        v(const full_type& a, const full_type& b) {
                                return mask_type(a() < b());
                        }
                };

                template <typename _T>
                struct le<_T, 1> {
                        using full_type = vec<_T, 1>;
                        using mask_type = typename full_type::mask_type;
                        static
                        mask_type
                        v(const full_type& a, const full_type& b) {
                                return mask_type(a() <= b());
                        }
                };

                template <typename _T>
                struct eq<_T, 1> {
                        using full_type = vec<_T, 1>;
                        using mask_type = typename full_type::mask_type;
                        static
                        mask_type
                        v(const full_type& a, const full_type& b) {
                                return mask_type(a() == b());
                        }
                };

                template <typename _T>
                struct ne<_T, 1> {
                        using full_type = vec<_T, 1>;
                        using mask_type = typename full_type::mask_type;
                        static
                        mask_type
                        v(const full_type& a, const full_type& b) {
                                return mask_type(a() != b());
                        }
                };

                template <typename _T>
                struct ge<_T, 1> {
                        using full_type = vec<_T, 1>;
                        using mask_type = typename full_type::mask_type;
                        static
                        mask_type
                        v(const full_type& a, const full_type& b) {
                                return mask_type(a() >= b());
                        }
                };

                template <typename _T>
                struct gt<_T, 1> {
                        using full_type = vec<_T, 1>;
                        using mask_type = typename full_type::mask_type;
                        static
                        mask_type
                        v(const full_type& a, const full_type& b) {
                                return mask_type(a() > b());
                        }
                };

                template <typename _T>
                struct plus<_T, 1> {
                        using full_type = vec<_T, 1>;
                        static
                        const full_type&
                        v(const full_type& a) {
                                return a;
                        }
                };

                template <typename _T>
                struct neg<_T, 1> {
                        using full_type = vec<_T, 1>;
                        static
                        full_type
                        v(const full_type& a) {
                                return full_type(-a());
                        }
                };

                template <typename _T>
                struct add<_T, 1> {
                        using full_type = vec<_T, 1>;
                        static
                        full_type
                        v(const full_type& a, const full_type& b) {
                                return full_type(a() + b());
                        }
                };

                template <typename _T>
                struct sub<_T, 1> {
                        using full_type = vec<_T, 1>;
                        static
                        full_type
                        v(const full_type& a, const full_type& b) {
                                return full_type(a() - b());
                        }
                };

                template <typename _T>
                struct mul<_T, 1> {
                        using full_type = vec<_T, 1>;
                        static
                        full_type
                        v(const full_type& a, const full_type& b) {
                                return full_type(a() * b());
                        }
                };

                template <typename _T>
                struct div<_T, 1> {
                        using full_type = vec<_T, 1>;
                        static
                        full_type
                        v(const full_type& a, const full_type& b) {
                                return full_type(a() / b());
                        }
                };

                template <typename _T>
                struct mod<_T, 1> {
                        using full_type = vec<_T, 1>;
                        static
                        full_type
                        v(const full_type& a, const full_type& b) {
                                return full_type(a() % b());
                        }
                };

                template <typename _T>
                struct fma<_T, 1> {
                        using full_type = vec<_T, 1>;
                        static
                        full_type
                        v(const full_type& a, const full_type& b,
                          const full_type& c) {
                                return full_type(a() * b() + c());
                                // return full_type(std::fma(a(), b(), c()));
                        }
                };

                template <typename _T>
                struct fms<_T, 1> {
                        using full_type = vec<_T, 1>;
                        static
                        full_type
                        v(const full_type& a, const full_type& b,
                          const full_type& c) {
                                return full_type(a() * b() - c());
                                // return full_type(std::fma(a(), b(), -c()));
                        }
                };

                template <typename _T>
                struct fnma<_T, 1> {
                        using full_type = vec<_T, 1>;
                        static
                        full_type
                        v(const full_type& a, const full_type& b,
                          const full_type& c) {
                                return full_type(c() - a() * b());
                                // return full_type(std::fma(-a(), b(), c()));
                        }
                };

                template <class _T>
                struct bitrep {
                        using int_type = _T;
                        using type = _T;
                        static
                        _T as_int(const _T& v) { return v; }
                        static
                        _T as_type(const _T& v) { return v; }
                };

                template <class _D, class _U>
                struct bitrep_helper {
                        using int_type = _U;
                        using type = _D;
                        union di {
                                _D _d;
                                _U _u;
                                di(const _D& d) : _d(d) {}
                                di(const _U& u) : _u(u) {}
                        };
                        static
                        int_type as_int(type v) {
                                di t(v);
                                return t._u;
                        }
                        static
                        type as_type(int_type u) {
                                di t(u);
                                return t._d;
                        }
                };

                template <>
                struct bitrep<double> :
                        public bitrep_helper<double, std::uint64_t> {
                };

                template <>
                struct bitrep<float>  :
                        public bitrep_helper<float, std::uint32_t> {
                };

                template <typename _T>
                struct bit_or<_T, 1> {
                        using full_type = vec<_T, 1>;
                        static
                        full_type
                        v(const full_type& a, const full_type& b) {
                                using cvt = bitrep<_T>;
                                typename cvt::int_type ai(
                                        cvt::as_int(a()));
                                typename cvt::int_type bi(
                                        cvt::as_int(b()));
                                typename cvt::type r(
                                        cvt::as_type(ai | bi));
                                return full_type(r);
                        }
                };

                template <typename _T>
                struct bit_and<_T, 1> {
                        using full_type = vec<_T, 1>;

                        static
                        full_type
                        v(const full_type& a, const full_type& b) {
                                using cvt = bitrep<_T>;
                                typename cvt::int_type ai(
                                        cvt::as_int(a()));
                                typename cvt::int_type bi(
                                        cvt::as_int(a()));
                                typename cvt::type r(
                                        cvt::as_type(ai & bi));
                                return full_type(r);
                        }
                };

                template <typename _T>
                struct bit_xor<_T, 1> {
                        using full_type = vec<_T, 1>;

                        static
                        full_type
                        v(const full_type& a, const full_type& b) {
                                using cvt = bitrep<_T>;
                                typename cvt::int_type ai(
                                        cvt::as_int(a()));
                                typename cvt::int_type bi(
                                        cvt::as_int(a()));
                                typename cvt::type r(
                                        cvt::as_type(ai ^ bi));
                                return full_type(r);
                        }
                };

                template <typename _T>
                struct bit_not<_T, 1> {
                        using full_type = vec<_T, 1>;
                        static
                        full_type
                        v(const full_type& a) {
                                using cvt = bitrep<_T>;
                                typename cvt::int_type ai(
                                        cvt::as_int(a()));
                                typename cvt::type r(
                                        cvt::as_type(~ai));
                                return full_type(r);
                        }
                };

                template <typename _T>
                struct shl<_T, 1> {
                        using full_type = vec<_T, 1>;
                        static
                        full_type
                        v(const full_type& a, unsigned s) {
                                using cvt = bitrep<_T>;
                                typename cvt::int_type ai(
                                        cvt::as_int(a()));
                                typename cvt::type r(
                                        cvt::as_type(ai << s));
                                return full_type(r);
                        }
                };

                template <typename _T>
                struct shr<_T, 1> {
                        using full_type = vec<_T, 1>;
                        static
                        full_type
                        v(const full_type& a, unsigned s) {
                                using cvt = bitrep<_T>;
                                typename cvt::int_type ai(
                                        cvt::as_int(a()));
                                typename cvt::type r(
                                        cvt::as_type(ai << s));
                                return full_type(r);
                        }
                };


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
                return op::fma<_T, _N>::v(eval(e._l._l),
                                          eval(e._l._r),
                                          eval(e._r));
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
                return op::fms<_T, _N>::v(eval(e._l._l),
                                          eval(e._l._r),
                                          eval(e._r));
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

template <typename _M, typename _T>
inline
_T
cftal::select(const _M& m, const _T& on_true, const _T& on_false)
{
        return m ? on_true : on_false;
}

template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>::vec(const _T& v)
        : _l(v), _h(v)
{
}

template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>::vec(const _T& v, bool splat)
        : _l(v, splat), _h(splat ? v : _T(0))
{
}

template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>::vec(std::initializer_list<_T> l)
        : vec(init_list<_T>(l.begin(), l.end()))
{
}

template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>::vec(init_list<_T> l)
        : _l(init_lo_half(l)),
          _h(init_hi_half(l))
{
}



template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>::vec(const half_type& l,
                        const half_type& h)
        : _l(l), _h(h)
{
}

template <typename _T, std::size_t _N>
template <template <class _U, std::size_t _M>
          class _OP,
          class _L, class _R>
cftal::vec<_T, _N>::vec(const expr<_OP<_T, _N>, _L, _R>& r)
        : vec(eval(r))
{
}


template <class _T, std::size_t _N>
inline
const typename cftal::vec<_T, _N>::half_type&
cftal::vec<_T, _N>::lh() const
{
        return _l;
}

template <class _T, std::size_t _N>
inline
const typename cftal::vec<_T, _N>::half_type&
cftal::vec<_T, _N>::hh() const
{
        return _h;
}

template <class _T, std::size_t _N>
inline
const typename cftal::vec<_T, _N>::half_type&
cftal::lo_half(const vec<_T, _N>& v)
{
        return v.lh();
}

template <class _T, std::size_t _N>
inline
const typename cftal::vec<_T, _N>::half_type&
cftal::hi_half(const vec<_T, _N>& v)
{
        return v.hh();
}


template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>
cftal::select(const typename vec<_T, _N>::mask_type& m,
              const vec<_T, _N>& on_true,
              const vec<_T, _N>& on_false)
{
        vec<_T, _N> res(
                select(lo_half(m), lo_half(on_true), lo_half(on_false)),
                select(hi_half(m), hi_half(on_true), hi_half(on_false)));
        return res;
}

template <class _T>
inline
cftal::vec<_T, 1>::vec(const _T& v)
        : _v(v)
{
}

template <class _T>
inline
cftal::vec<_T, 1>::vec(const _T& v, bool splat)
        : _v(v)
{
        static_cast<void>(splat);
}

template <typename _T>
template <template <class _U, std::size_t _M>
          class _OP,
          class _L, class _R>
cftal::vec<_T, 1>::vec(const expr<_OP<_T, 1>, _L, _R>& r)
        : vec(eval(r))
{
}


template <class _T>
inline
_T
cftal::vec<_T, 1>::operator()() const
{
        return _v;
}

template <class _T>
inline
cftal::vec<_T, 1>
cftal::select(const typename vec<_T, 1>::mask_type& vm,
              const vec<_T, 1>& on_true,
              const vec<_T, 1>& on_false)
{
        typename vec<_T, 1>::value_type r{
                select(vm(), on_true(), on_false())};
        return vec<_T, 1>{r};
}


#define DEF_CMP_OPS(opname, opobj)                                      \
        template <class _T, std::size_t _N>                             \
        inline                                                          \
        typename cftal::vec<_T, _N>::mask_type                          \
        cftal::operator opname(const vec<_T, _N>& a,                    \
                               const vec<_T, _N>& b)                    \
        {                                                               \
                return opobj <_T, _N> ::v(a, b);                        \
        }                                                               \
                                                                        \
        template <class _T, std::size_t _N>                             \
        inline                                                          \
        typename cftal::vec<_T, _N>::mask_type                          \
        cftal::operator opname(const vec<_T, _N>& a,                    \
                               const typename vec<_T, _N>::value_type& b) \
        {                                                               \
                return opobj <_T, _N> ::v(a, b);                        \
        }                                                               \
                                                                        \
        template <class _T, std::size_t _N>                             \
        inline                                                          \
        typename cftal::vec<_T, _N>::mask_type                          \
        cftal::operator opname(const typename vec<_T, _N>::value_type& a, \
                               const vec<_T, _N>& b)                    \
        {                                                               \
                return  opobj <_T, _N> ::v(a, b);                       \
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

// include vector specializations
#if defined (__SSE__)
#if 0
#include <cftal/simd/x86_v4f32.h>
#endif
#endif
#if defined (__SSE2__)
#include <cftal/x86_v4s32.h>
#if 0
#include <cftal/simd/x86_v4u32.h>
#include <cftal/simd/x86_v2s64.h>
#include <cftal/simd/x86_v2u64.h>
#include <cftal/simd/x86_v2f64.h>
#endif
#endif
#if defined (__AVX__)
#if 0
#include <cftal/simd/x86_v8f32.h>
#include <cftal/simd/x86_v4f64.h>
#endif
#endif
#if defined (__AVX2__)
#if 0
#include <cftal/simd/x86_v8s32.h>
#include <cftal/simd/x86_v8u32.h>
#include <cftal/simd/x86_v4s64.h>
#include <cftal/simd/x86_v4u64.h>
#endif
#endif
#if defined (__AVX512__)
#if 0
#include <cftal/simd/x86_v16f32.h>
#include <cftal/simd/x86_v8f64.h>
#include <cftal/simd/x86_v16s32.h>
#include <cftal/simd/x86_v16u32.h>
#include <cftal/simd/x86_v8s64.h>
#include <cftal/simd/x86_v8u64.h>
#endif
#endif

// Local variables:
// mode: c++
// end:
#endif
