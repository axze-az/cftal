#if !defined (__CFTAL_X86_V8S16_INL__)
#define __CFTAL_X86_V8S16_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86_v8s16.h>
#include <cftal/x86_v8u16.h>
#include <cftal/x86_perm.h>
#include <cftal/x86_ops_1.h>
#include <cftal/divisor.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<int16_t, 8> {
            using full_type = vec<int16_t, 8>;
            static
            full_type
            v(const full_type& a) {
                full_type all_set(0xffff);
                return _mm_xor_si128(a(), all_set());
            }
        };


        template <>
        struct lt<int16_t, 8> {
            using full_type = vec<int16_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm_cmpgt_epi16(b(), a());
            }
        };

        template <>
        struct le<int16_t, 8> {
            using full_type = vec<int16_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                __m128i min_ab = _mm_min_epi16(b(), a());
                return _mm_cmpeq_epi16(a(), min_ab);
            }
        };

        template <>
        struct eq<int16_t, 8> {
            using full_type = vec<int16_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm_cmpeq_epi16(a(), b());
            }
        };

        template <>
        struct ne<int16_t, 8> {
            using full_type = vec<int16_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                mask_type a_eq_b(eq<int16_t, 8>::v(a, b));
                return bit_not<int16_t, 8>::v(a_eq_b);
            }
        };

        template <>
        struct ge<int16_t, 8> {
            using full_type = vec<int16_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                // a>= b: a == max(a, b);
                __m128i max_ab = _mm_max_epi16(b(), a());
                return _mm_cmpeq_epi16(a(), max_ab);
            }
        };

        template <>
        struct gt<int16_t, 8> {
            using full_type = vec<int16_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm_cmpgt_epi16(a(), b());
            }
        };

        template <>
        struct plus<int16_t, 8> {
            using full_type = vec<int16_t, 8>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<int16_t, 8> {
            using full_type = vec<int16_t, 8>;
            static
            full_type
            v(const full_type& a) {
#if defined (__SSSE3__)
                const full_type sgn(0x8000);
                return _mm_sign_epi16(a(), sgn());
#else
                const full_type zero(0);
                return _mm_sub_epi16(zero(), a());
#endif
            }
        };

        template <>
        struct add<int16_t, 8> {
            using full_type = vec<int16_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_add_epi16(a(), b());
            }
        };

        template <>
        struct sub<int16_t, 8> {
            using full_type = vec<int16_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_sub_epi16(a(), b());
            }
        };

        template <>
        struct mul<int16_t, 8> {
            using full_type = vec<int16_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::impl::vpmullw::v(a(), b());
            }
        };

        template <>
        struct div<int16_t, 8> {
            using full_type = vec<int16_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_s16::v(a(), b());
            }
        };

        template <>
        struct mod<int16_t, 8> {
            using full_type = vec<int16_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                full_type q(a/b);
                full_type r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<int16_t, 8> {
            using full_type = vec<int16_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<int16_t, 8>::v(
                    mul<int16_t, 8>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<int16_t, 8> {
            using full_type = vec<int16_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<int16_t, 8>::v(
                    mul<int16_t, 8>::v(a , b), c);
            }
        };

        template <>
        struct fnma<int16_t, 8> {
            using full_type = vec<int16_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<int16_t, 8>::v(
                    c, mul<int16_t, 8>::v(a, b));

            }
        };

        template <>
        struct bit_or<int16_t, 8> {
            using full_type = vec<int16_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_or_si128(a(), b());
            }
        };

        template <>
        struct bit_and<int16_t, 8> {
            using full_type = vec<int16_t, 8>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_and_si128(a(), b());
            }
        };

        template <>
        struct bit_xor<int16_t, 8> {
            using full_type = vec<int16_t, 8>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_xor_si128(a(), b());
            }
        };

        template <>
        struct shl<int16_t, 8> {
            using full_type = vec<int16_t, 8>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_slli_epi16(a(), s);
            }
        };

        template <>
        struct shr<int16_t, 8> {
            using full_type = vec<int16_t, 8>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_srai_epi16(a(), s);
            }
        };

    }

}

inline
cftal::vec<cftal::int16_t, 8>::vec(const vec<uint16_t, 8>& v)
    : base_type(v())
{
}

inline
cftal::vec<cftal::int16_t, 8>::vec(int16_t v)
    : base_type(_mm_setr_epi16(v, v, v, v, v, v, v, v))
{
}


inline
cftal::vec<cftal::int16_t, 8>::
vec(std::initializer_list<int16_t> l)
    : vec(mem<v8s16>::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::int16_t, 8>::
vec(init_list<int16_t> l)
    : vec(mem<v8s16>::load(l.begin(), l.size()))
{
}

template <template <class _U, std::size_t _M> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::int16_t, 8>::vec(const expr<_OP<int16_t, 8>, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::int16_t, 8>
cftal::mem<cftal::vec<int16_t, 8> >::load(const int16_t* p, std::size_t s)
{
    __m128i v;
    switch (s) {
    default:
    case 8:
        v = _mm_loadu_si128(reinterpret_cast<const __m128i*>(p));
        break;
    case 7:
        v = _mm_setr_epi16(p[0], p[1], p[2], p[3],
                           p[4], p[5], p[6], p[6]);
        break;
    case 6:
        v = _mm_setr_epi16(p[0], p[1], p[2], p[3],
                           p[4], p[5], p[5], p[5]);
        break;
    case 5:
        v = _mm_setr_epi16(p[0], p[1], p[2], p[3],
                           p[4], p[4], p[4], p[4]);
        break;
    case 4:
        v = _mm_setr_epi16(p[0], p[1], p[2], p[3],
                           p[3], p[3], p[3], p[3]);
        break;
    case 3:
        v = _mm_setr_epi16(p[0], p[1], p[2], p[2],
                           p[2], p[2], p[2], p[2]);
        break;
    case 2:
        v = _mm_setr_epi16(p[0], p[1], p[1], p[1],
                           p[1], p[1], p[1], p[1]);
        break;
    case 1:
        v = _mm_setr_epi16(p[0], p[0], p[0], p[0],
                           p[0], p[0], p[0], p[0]);
        break;
    case 0:
        v = _mm_setr_epi32(0, 0, 0, 0);
        break;
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<int16_t, 8> >::store(int16_t* p,
                                           const vec<int16_t, 8>& v)
{
    _mm_storeu_si128(reinterpret_cast<__m128i*>(p), v());
}

inline
cftal::v8s16 cftal::max(const v8s16& a, const v8s16& b)
{
#if defined (__SSE4_1__)
    return _mm_max_epi16(a(), b());
#else
    v8s16 _gt(a > b);
    return select(_gt, a, b);
#endif
}

inline
cftal::v8s16 cftal::min(const v8s16& a, const v8s16& b)
{
#if defined (__SSE4_1__)
    return _mm_min_epi16(a(), b());
#else
    v8s16 _lt(a < b);
    return select(_lt, a, b);
#endif
}

inline
cftal::v8s16 cftal::select(const v8s16::mask_type& m,
                           const v8s16& on_true,
                           const v8s16& on_false)
{
    return x86::select(m(), on_true(), on_false());
}


template <int _I0, int _I1, int _I2, int _I3,
          int _I4, int _I5, int _I6, int _I7>
inline
cftal::v8s16 cftal::permute(const v8s16& a)
{
    return x86::perm_u16<_I0, _I1, _I2, _I3, _I4, _I5, _I6, _I7>(a());
}

template <int _I0, int _I1, int _I2, int _I3,
          int _I4, int _I5, int _I6, int _I7>
inline
cftal::v8s16 cftal::permute(const v8s16& a, const v8s16& b)
{
    return x86::perm_u16<_I0, _I1, _I2, _I3, _I4, _I5, _I6, _I7>(a(), b());
}

inline
std::pair<cftal::v8s16, cftal::v8s16>
cftal::mul_lo_hi(const v8s16& a, const v8s16& b)
{
    v8s16 h(x86::impl::vpmulhw::v(a(), b()));
    v8s16 l(a*b);
    return std::make_pair(l, h);
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V8S16_INL_H__
