#if !defined (__CFTAL_SVEC_H__)
#define __CFTAL_SVEC_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <cftal/x86vec_expr.h>
#include <initializer_list>


namespace cftal {
        
        namespace simd {

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

                template <class _OP, class _L, class _R>
                inline
                typename _OP::vector_type 
                eval(const expr<_OP, _L, _R>& e) {
                        return _OP::v(eval(e._l), eval(e._r)); 
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
                vec<_T, _N> select(const typename vec<_T, _N>::mask_type& m,
                                   const vec<_T, _N>& on_true,
                                   const vec<_T, _N>& on_false);
                
                /* permute low and high halves of s */
                template <int _LH, int _HH,
                          typename _T, std::size_t _N>
                vec<_T, _N> permute(const vec<_T, _N>& s);

                /* permute low and high halves of s */
                template <int _LH, int _HH,
                          typename _T, std::size_t _N>
                vec<_T, _N> permute(const vec<_T, _N>& s0,
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
                private:
                        _T _v;
                };

#define DECL_CMP_OPS(op)                                        \
        template <typename _T>                                  \
        typename vec<_T, 1>::mask_type                          \
        operator op (const vec<_T, 1>& a,                       \
                     const vec<_T, 1>& b);                      \
                                                                \
        template <typename _T>                                  \
        typename vec<_T, 1>::mask_type                          \
        operator op (const vec<_T, 1>& a,                       \
                     const typename vec<_T, 1>::value_type& b); \
                                                                \
        template <typename _T>                                  \
        typename vec<_T, 1>::mask_type                          \
        operator op (const typename vec<_T, 1>::value_type& a,  \
                     const vec<_T, 1>& b)

                DECL_CMP_OPS(<);
                DECL_CMP_OPS(<=);
                DECL_CMP_OPS(==);
                DECL_CMP_OPS(!=);
                DECL_CMP_OPS(>=);
                DECL_CMP_OPS(>);

#undef DECL_CMP_OPS


                template <typename _T>
                vec<_T, 1> select(const typename vec<_T, 1>::mask_type& m,
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
                        struct ternary {
                                using full_type = vec<_T, _N>;
                                static 
                                full_type
                                v(const full_type& a, const full_type& b, 
                                  const full_type& c) {
                                        return _R(
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
                        struct fma<_T, 1> {
                                using full_type = vec<_T, 1>;
                                static
                                full_type
                                v(const full_type& a, const full_type& b,
                                  const full_type& c) {
                                        return full_type(a() * b() + c());
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
                                using cvt = bitrep<_T>;
                                
                                static
                                full_type
                                v(const full_type& a, const full_type& b) {
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
                                using cvt = bitrep<_T>;
                                
                                static
                                full_type
                                v(const full_type& a, const full_type& b) {
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
                                using cvt = bitrep<_T>;
                                
                                static
                                full_type
                                v(const full_type& a, const full_type& b) {
                                        typename cvt::int_type ai(
                                                cvt::as_int(a()));
                                        typename cvt::int_type bi(
                                                cvt::as_int(a()));
                                        typename cvt::type r(
                                                cvt::as_type(ai ^ bi));
                                        return full_type(r);
                                }
                        };
                } // namespace ops
                
                template <typename _T, std::size_t _N>
                expr<op:: add <_T, _N>, 
                     vec<_T, _N>, 
                     vec<_T, _N> >
                operator+(const vec<_T, _N>& a, const vec<_T, _N>& b);

                template <typename _T, std::size_t _N>
                expr<op:: add <_T, _N>, 
                     typename vec<_T, _N>::value_type, 
                     vec<_T, _N> >
                operator+(const typename vec<_T, _N>::value_type& a, 
                          const vec<_T, _N>& b);

                template <typename _T, std::size_t _N>
                expr<op:: add <_T, _N>, 
                     vec<_T, _N>,
                     typename vec<_T, _N>::value_type>
                operator+(const vec<_T, _N>& a, 
                          const typename vec<_T, _N>::value_type& b);

                template <typename _T, std::size_t _N, 
                          template <typename _T1, std::size_t _N1> class _OP,
                          class _L, class _R>
                expr<op:: add <_T, _N>, 
                     vec<_T, _N>, 
                     expr<_OP<_T, _N>, _L, _R> >
                operator+(const vec<_T, _N>& a,
                          const expr<_OP<_T, _N>, _L, _R>& b);

                template <typename _T, std::size_t _N,
                          template <typename _T1, std::size_t _N1> class _OP,
                          class _L, class _R>
                expr<op:: add <_T, _N>, 
                     expr<_OP<_T, _N>, _L, _R>, 
                     vec<_T, _N> >
                operator+(const expr<_OP<_T, _N>, _L, _R>& a,
                          const vec<_T, _N>& b);

                template <typename _T, std::size_t _N, 
                          template <typename _T1, std::size_t _N1> class _OP,
                          class _L, class _R>
                expr<op:: add <_T, _N>, 
                     typename vec<_T, _N>::value_type, 
                     expr<_OP<_T, _N>, _L, _R> >
                operator+(const typename vec<_T, _N>::value_type& a,
                          const expr<_OP<_T, _N>, _L, _R>& b);

                template <typename _T, std::size_t _N,
                          template <typename _T1, std::size_t _N1> class _OP,
                          class _L, class _R>
                expr<op:: add <_T, _N>, 
                     expr<_OP<_T, _N>, _L, _R>, 
                     typename vec<_T, _N>::value_type >
                operator+(const expr<_OP<_T, _N>, _L, _R>& a,
                          const typename vec<_T, _N>::value_type& b);
        }
}

template <typename _M, typename _T>
inline
_T 
cftal::simd::select(const _M& m, const _T& on_true, const _T& on_false)
{
        return m ? on_true : on_false;
}

template <class _T, std::size_t _N>
inline
cftal::simd::vec<_T, _N>::vec(const _T& v)
        : _l(v), _h(v)
{
}

template <class _T, std::size_t _N>
inline
cftal::simd::vec<_T, _N>::vec(const _T& v, bool splat)
        : _l(v, splat), _h(splat ? v : _T(0))
{
}

template <class _T, std::size_t _N>
inline
cftal::simd::vec<_T, _N>::vec(std::initializer_list<_T> l)
        : _l(std::initializer_list<_T>(begin(l), l.size()/2)),
          _h(std::initializer_list<_T>(begin(l) + l.size()/2, 
                                       l.size()/2)) 
{
}

template <class _T, std::size_t _N>
inline
cftal::simd::vec<_T, _N>::vec(const half_type& l,
                              const half_type& h)
        : _l(l), _h(h)
{
}

template <class _T, std::size_t _N>
inline
const typename cftal::simd::vec<_T, _N>::half_type&
cftal::simd::vec<_T, _N>::lh() const
{
        return _l;
}

template <class _T, std::size_t _N>
inline
const typename cftal::simd::vec<_T, _N>::half_type&
cftal::simd::vec<_T, _N>::hh() const
{
        return _h;
}

template <class _T, std::size_t _N>
inline
const typename cftal::simd::vec<_T, _N>::half_type&
cftal::simd::lo_half(const vec<_T, _N>& v) 
{
        return v.lh();
}

template <class _T, std::size_t _N>
inline
const typename cftal::simd::vec<_T, _N>::half_type&
cftal::simd::hi_half(const vec<_T, _N>& v)
{
        return v.hh();
}


template <class _T, std::size_t _N>
inline
cftal::simd::vec<_T, _N>
cftal::simd::select(const typename vec<_T, _N>::mask_type& m,
                    const vec<_T, _N>& on_true,
                    const vec<_T, _N>& on_false)
{
        return vec<_T, _N>();
}

template <class _T>
inline
cftal::simd::vec<_T, 1>::vec(const _T& v)
        : _v(v) 
{
}

template <class _T>
inline
cftal::simd::vec<_T, 1>::vec(const _T& v, bool splat)
        : _v(v) 
{
        static_cast<void>(splat);
}


template <class _T>
inline
_T
cftal::simd::vec<_T, 1>::operator()() const
{
        return _v;
}


#define DEF_CMP_OPS(op)                                                 \
template <class _T, std::size_t _N>                                     \
inline                                                                  \
typename cftal::simd::vec<_T, _N>::mask_type                            \
cftal::simd::operator op(const vec<_T, _N>& a,                          \
                         const vec<_T, _N>& b)                          \
{                                                                       \
        using mask_type =  typename cftal::simd::vec<_T, _N>::mask_type; \
        return mask_type(lo_half(a) op lo_half(b),                      \
                         hi_half(a) op hi_half(b));                     \
}                                                                       \
                                                                        \
template <class _T, std::size_t _N>                                     \
inline                                                                  \
typename cftal::simd::vec<_T, _N>::mask_type                            \
cftal::simd::operator op(const vec<_T, _N>& a,                          \
                         const typename vec<_T, _N>::value_type& b)    \
{                                                                       \
        using mask_type =  typename cftal::simd::vec<_T, _N>::mask_type; \
        return mask_type(lo_half(a) op b,                               \
                         hi_half(a) op b);                              \
}                                                                       \
                                                                        \
template <class _T, std::size_t _N>                                     \
inline                                                                  \
typename cftal::simd::vec<_T, _N>::mask_type                            \
cftal::simd::operator op(const typename vec<_T, _N>::value_type& a,     \
                         const vec<_T, _N>& b)                          \
{                                                                       \
        using mask_type =  typename cftal::simd::vec<_T, _N>::mask_type; \
        return mask_type(a op lo_half(b),                               \
                         a op hi_half(b));                              \
}


DEF_CMP_OPS(<)
DEF_CMP_OPS(<=)
DEF_CMP_OPS(==)
DEF_CMP_OPS(!=)
DEF_CMP_OPS(>=)
DEF_CMP_OPS(>)

#undef DEF_CMP_OPS


#define DEF_CMP_OPS(op)                                                 \
template <class _T>                                                     \
inline                                                                  \
typename cftal::simd::vec<_T, 1>::mask_type                             \
cftal::simd::operator op(const vec<_T, 1>& a,                           \
                         const vec<_T, 1>& b)                           \
{                                                                       \
        using mask_type =  typename cftal::simd::vec<_T, 1>::mask_type; \
        return mask_type(a() op b());                                   \
}                                                                       \
                                                                        \
template <class _T>                                                     \
inline                                                                  \
typename cftal::simd::vec<_T, 1>::mask_type                             \
cftal::simd::operator op(const vec<_T, 1>& a,                           \
                         const typename vec<_T, 1>::value_type& b)      \
{                                                                       \
        using mask_type =  typename cftal::simd::vec<_T, 1>::mask_type; \
        using mask_type =  typename cftal::simd::vec<_T, 1>::mask_type; \
        return mask_type(a() op b);                                     \
}                                                                       \
                                                                        \
template <class _T>                                                     \
inline                                                                  \
typename cftal::simd::vec<_T, 1>::mask_type                             \
cftal::simd::operator op(const typename vec<_T, 1>::value_type& a,      \
                         const vec<_T, 1>& b)                           \
{                                                                       \
        using mask_type =  typename cftal::simd::vec<_T, 1>::mask_type; \
        return mask_type(a op b());                                     \
}

DEF_CMP_OPS(<)
DEF_CMP_OPS(<=)
DEF_CMP_OPS(==)
DEF_CMP_OPS(!=)
DEF_CMP_OPS(>=)
DEF_CMP_OPS(>)

#undef DEC_CMP_OPS

// Local variables:
// mode: c++
// end:
#endif
