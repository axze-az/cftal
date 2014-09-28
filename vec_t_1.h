#if !defined (__CFTAL_SIMD_VEC_T_1_H__)
#define __CFTAL_SIMD_VEC_T_1_H__ 1

namespace cftal {

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

        namespace op {
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
        }
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



// Local variables:
// mode: c++
// end:
#endif
