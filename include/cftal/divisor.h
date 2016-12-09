#if !defined (__CFTAL_DIVISOR_H__)
#define __CFTAL_DIVISOR_H__ 1

#include <cftal/config.h>
#include <cftal/mul_div.h>
#include <cftal/types.h>
#include <algorithm>
#include <type_traits>

namespace cftal {

    // perform _V/_D via _V * (1/_D)
    template <class _V, class _D = _V>
    class divisor {
        _V _rec;
        _D _d;
    public:
                explicit
        divisor(const _D& dd) : _rec(_V(_D(1)/dd)), _d(dd) {}
        const _D& d() const { return _d; }
        _V divide(const _V& n) const { return n * _rec; }
    };


    template <class _V, class _D>
    _V operator/(const _V& n, const divisor<_V, _D>& d)
    {
        return d.divide(n);
    }

    template <class _V, class _D>
    _V& operator/=(_V& n, const divisor<_V, _D>& d)
    {
        _V q(d.divide(n));
        n = q;
        return n;
    }

    namespace impl {

        template <typename _T>
        struct udiv_setup_traits {
            // sword udword types
            // ceil_log2 of _T
            // _N as sizeof(uword) in bits
        };

        template <typename _T>
        struct sdiv_setup_traits {
            // sword, udword types
            // ceil_log2 of _T
            // _N as sizeof(sword) in bits
        };

        template <typename _V, typename _D>
        struct udiv_traits {
            static
            _V muluh(_V a, _V b) {
                return mul_lo_hi(a, b).second;
            }
        };

        template <typename _V, typename _D>
        struct sdiv_traits {
            static
            _V mulsh(_V a, _V b) {
                return mul_lo_hi(a, b).second;
            }
        };

        template <typename _D, typename _TR= udiv_setup_traits<_D> >
        class udiv_setup {
        public:
            typedef typename _TR::uword uword;
            typedef typename _TR::udword udword;
                        explicit
            udiv_setup(const uword& d);
            const uword& m() const { return _m; }
            const uword& s1() const { return _s1; }
            const uword& s2() const { return _s2; }
            bool shift_only() const { return _shift_only; }
        private:
            uword _m;
            uword _s1;
            uword _s2;
            bool _shift_only;
        };

        template <typename _D, typename _TR= sdiv_setup_traits<_D> >
        class sdiv_setup {
        public:
            typedef typename _TR::sword sword;
            typedef typename std::make_unsigned<sword>::type uword;
            typedef typename _TR::udword udword;
                        explicit
            sdiv_setup(const sword& d);
            const sword& m() const { return _m; }
            const sword& s() const { return _s; }
            const sword& xsgn_d() const { return _xsgn_d; }
        private:
            sword _m;
            sword _s;
            sword _xsgn_d;
        };

        template <typename _V, typename _D,
                  typename _UDIV_TRAITS= udiv_traits<_V, _D>,
                  typename _UDIV_SETUP_TRAITS = udiv_setup_traits<_D> >
        class udiv {
            _V _m;
            _D _d;
            uint32_t _s1;
            uint32_t _s2;
            bool _shift_only;
        public:
                        explicit
            udiv(const _D& d) { set(d); }
            void set(const _D& d);
            const _D& d() const { return _d; }
            _V divide(const _V& n) const;
        };

        template <typename _V, typename _D,
                  typename _SDIV_TRAITS= sdiv_traits<_V, _D>,
                  typename _SDIV_SETUP_TRAITS = sdiv_setup_traits<_D> >
        class sdiv {
            _V _m;
            _V _xsgn_d;
            _D _d;
            uint32_t _s;
        public:
                        explicit
            sdiv(const _D& d) { set(d); }
            void set(const _D& d);
            const _D& d() const { return _d; }
            _V divide(const _V& n) const;
        };

        struct div16_traits {
            typedef int16_t sword;
            typedef uint16_t uword;
            typedef uint32_t udword;
            static
            uword ceil_log2(uword t) {
                return 16 - lzcnt(uword(t-1));
            }
            static
            sword ceil_log2(sword t) {
                return ceil_log2(uint16_t(t));
            }
            static
            uword muluh(uword a, uword b) {
                return mul_lo_hi(a, b).second;
            }
            static
            sword mulsh(sword a, sword b) {
                return mul_lo_hi(a, b).second;
            }
            enum {
                _N = 16
            };
        };

        struct div32_traits {
            typedef int32_t sword;
            typedef uint32_t uword;
            typedef uint64_t udword;
            static
            uword ceil_log2(uword t) {
                return 32 - lzcnt(t-1);
            }
            static
            sword ceil_log2(sword t) {
                return ceil_log2(uint32_t(t));
            }
            static
            uword muluh(uword a, uword b) {
                return mul_lo_hi(a, b).second;
            }
            static
            sword mulsh(sword a, sword b) {
                return mul_lo_hi(a, b).second;
            }
            enum {
                _N =32
            };
        };

        struct div64_traits {
            typedef int64_t sword;
            typedef uint64_t uword;
            typedef duint<uint64_t> udword;
            static
            uword ceil_log2(uword t) {
                return 64 - lzcnt(t-1);
            }
            static
            sword ceil_log2(sword t) {
                return ceil_log2(uint64_t(t));
            }
            static
            uword muluh(uword a, uword b) {
                return mul_lo_hi(a, b).second;
            }
            static
            sword mulsh(sword a, sword b) {
                return mul_lo_hi(a, b).second;
            }
            enum {
                _N =64
            };
        };

        // unsigned div 16
        template <>
        struct udiv_setup_traits<uint16_t>
            : public div16_traits {};
        template <>
        struct udiv_traits<uint16_t, uint16_t>
            : public div16_traits {};
        // signed div 16
        template <>
        struct sdiv_setup_traits<int16_t>
            : public div16_traits {};
        template <>
        struct sdiv_traits<int16_t, int16_t>
            : public div16_traits {};

        // unsigned div 32
        template <>
        struct udiv_setup_traits<uint32_t>
            : public div32_traits {};
        template <>
        struct udiv_traits<uint32_t, uint32_t>
            : public div32_traits {};

        // signed div 32
        template <>
        struct sdiv_setup_traits<int32_t>
            : public div32_traits {};
        template <>
        struct sdiv_traits<int32_t, int32_t>
            : public div32_traits {};


        // unsigned div 64
        template <>
        struct udiv_setup_traits<uint64_t>
            : public div64_traits {};
        template <>
        struct udiv_traits<uint64_t, uint64_t>
            : public div64_traits {};

        // signed div 64
        template <>
        struct sdiv_setup_traits<int64_t>
            : public div64_traits {};
        template <>
        struct sdiv_traits<int64_t, int64_t>
            : public div64_traits {};

        template <typename _U, typename _V>
        struct div_sel {
            using type = typename
                std::conditional<std::is_signed<_V>::value,
                                 sdiv<_U, _V>,
                                 udiv<_U, _V> >::type;
        };
    }

    template <typename _T>
    class divisor<_T, int16_t>
        : public impl::sdiv<_T, int16_t> {
    public:
        divisor(int16_t d) :
            impl::sdiv<_T, int16_t>(d) {}
    };

    template <typename _T>
    class divisor<_T, uint16_t>
        : public impl::udiv<_T, uint16_t> {
    public:
        divisor(int16_t d) :
            impl::udiv<_T, uint16_t>(d) {}
    };

    template <typename _T>
    class divisor<_T, int32_t>
        : public impl::sdiv<_T, int32_t> {
    public:
        divisor(int32_t d) :
            impl::sdiv<_T, int32_t>(d) {}
    };

    template <typename _T>
    class divisor<_T, uint32_t>
        : public impl::udiv<_T, uint32_t> {
    public:
        divisor(uint32_t d) :
            impl::udiv<_T, uint32_t>(d) {}
    };

    template <typename _T>
    class divisor<_T, int64_t>
        : public impl::sdiv<_T, int64_t> {
    public:
        divisor(int64_t d) :
            impl::sdiv<_T, int64_t>(d) {}
    };

    template <typename _T>
    class divisor<_T, uint64_t>
        : public impl::udiv<_T, uint64_t> {
    public:
        divisor(uint64_t d) :
            impl::udiv<_T, uint64_t>(d) {}
    };


    template <class _V>
    _V operator%(const _V& n, const divisor<_V, int16_t>& d)
    {
        _V q(d.divide(n));
        _V dd(d.d());
        return remainder(n, dd, q);
    }

    template <class _V>
    _V operator%(const _V& n, const divisor<_V, uint16_t>& d)
    {
        _V q(d.divide(n));
        _V dd(d.d());
        return remainder(n, dd, q);
    }

    template <class _V>
    _V operator%(const _V& n, const divisor<_V, int32_t>& d)
    {
        _V q(d.divide(n));
        _V dd(d.d());
        return remainder(n, dd, q);
    }

    template <class _V>
    _V operator%(const _V& n, const divisor<_V, uint32_t>& d)
    {
        _V q(d.divide(n));
        _V dd(d.d());
        return remainder(n, dd, q);
    }

    template <class _V>
    _V operator%(const _V& n, const divisor<_V, int64_t>& d)
    {
        _V q(d.divide(n));
        _V dd(d.d());
        return remainder(n, dd, q);
    }

    template <class _V>
    _V operator%(const _V& n, const divisor<_V, uint64_t>& d)
    {
        _V q(d.divide(n));
        _V dd(d.d());
        return remainder(n, dd, q);
    }

    namespace test {
        bool div_u16();
        bool div_s16();
        bool div_u32();
        bool div_s32();
    }
}

template <typename _D, class _TR>
cftal::impl::udiv_setup<_D, _TR>::udiv_setup(const uword& d)
{
    int l = _TR::ceil_log2(d);
    if ( (d & (d-1)) == uword(0)) {
        _m = uword(0);
        _s1 = l;
        _s2 = 0;
        _shift_only = true;
    } else {
        udword ms0= ((udword(1) << l) - d)<<_TR::_N;
        udword ms= ms0/d + uword(1);
        _m = uword(ms);
        _s1= std::min(l, 1);
        _s2= std::max(l-1, 0);
        _shift_only = false;
    }
}

template <typename _V, typename _D,
          class _UDIV_TRAITS, class _UDIV_SETUP_TRAITS>
void
cftal::impl::
udiv<_V, _D, _UDIV_TRAITS, _UDIV_SETUP_TRAITS>::set(const _D& d)
{
    udiv_setup<_D, _UDIV_SETUP_TRAITS> setup(d);
    _d = d;
    _m = _V(setup.m());
    _s1 = setup.s1();
    _s2 = setup.s2();
    _shift_only = setup.shift_only();
}

template <typename _V, typename _D,
          class _UDIV_TRAITS, class _UDIV_SETUP_TRAITS>
_V
cftal::impl::
udiv<_V, _D, _UDIV_TRAITS, _UDIV_SETUP_TRAITS>::divide(const _V& n)
    const
{
    if (_d == _D(0))
        return _V(_D(-1));
    _V q;
    if (_shift_only) {
        q = n >> _s1;
    } else {
        _V t1 = _UDIV_TRAITS::muluh(_m, n);
        _V t2 = (n - t1) >> _s1;
        q = (t1 + t2) >> _s2;
    }
    return q;
}

template <typename _D, class _TR>
cftal::impl::sdiv_setup<_D, _TR>::sdiv_setup(const sword& d)
{
    const sword min_sword=sword(_D(1) << (_TR::_N-1));
    if (d==0) {
        _m = 0;
        _s = 0;
    } else if (d == min_sword) {
        _m = d +1;
        _s = _TR::_N -2;
    } else {
        sword ad = d < _D(0) ? -d : d;
        int l = std::max(_TR::ceil_log2(ad), sword(1));
        udword ms0= (udword(1) << (_TR::_N + l -1))/uword(ad)
            + uword(1);
        udword ms = ms0 - (udword(1) << (_TR::_N));
        _m = sword(uword(ms));
        _s = l-1;
    }
    _xsgn_d = d >> (_TR::_N-1);
}

template <typename _V, typename _D,
          class _SDIV_TRAITS, class _SDIV_SETUP_TRAITS>
void
cftal::impl::
sdiv<_V, _D, _SDIV_TRAITS, _SDIV_SETUP_TRAITS>::set(const _D& d)
{
    sdiv_setup<_D, _SDIV_SETUP_TRAITS> setup(d);
    _d = d;
    _m = _V(setup.m());
    _s = setup.s();
    _xsgn_d = _V(setup.xsgn_d());
}

template <typename _V, typename _D,
          class _SDIV_TRAITS, class _SDIV_SETUP_TRAITS>
_V
cftal::impl::
sdiv<_V, _D, _SDIV_TRAITS, _SDIV_SETUP_TRAITS>::divide(const _V& n)
    const
{
    if (_d == _D(0))
        return _V(_D(-1));
    _V q0 = n + _SDIV_TRAITS::mulsh(_m, n);
    _V xsgn_n = n >> (_SDIV_SETUP_TRAITS::_N-1);
    _V q1 = (q0 >> _s) - xsgn_n;
    _V q = (q1 ^ _xsgn_d) - _xsgn_d;
    return q;
}

// Local variables:
// mode: c++
// end:
#endif
