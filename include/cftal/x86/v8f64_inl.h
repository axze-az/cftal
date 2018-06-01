//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_X86_V8F64_INL__)
#define __CFTAL_X86_V8F64_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/constants.h>
#include <cftal/x86/v8f64.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/v4f64.h>
#include <cftal/x86/ops_1.h>

#if defined (__AVX512F__)

namespace cftal {


    namespace op {

        template <>
        struct bit_not<double, 8> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a) {
                constexpr const bytes8 all_one{-1, -1};
                const full_type all_set(all_one._f64);
                return _mm512_xor_pd(a(), all_set());
            }
        };


        template <>
        struct lt<double, 8> {
            using full_type = vec<double, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmp_pd_mask(a(), b(), _CMP_LT_OS);
            }
        };

        template <>
        struct le<double, 8> {
            using full_type = vec<double, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmp_pd_mask(a(), b(), _CMP_LE_OS);
            }
        };

        template <>
        struct eq<double, 8> {
            using full_type = vec<double, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmp_pd_mask(a(), b(), _CMP_EQ_OQ);
            }
        };

        template <>
        struct ne<double, 8> {
            using full_type = vec<double, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmp_pd_mask(a(), b(), _CMP_UNORD_Q);
            }
        };

        template <>
        struct ge<double, 8> {
            using full_type = vec<double, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmp_pd_mask(a(), b(), _CMP_GE_OS);
            }
        };

        template <>
        struct gt<double, 8> {
            using full_type = vec<double, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmp_pd_mask(a(), b(), _CMP_GT_OS);
            }
        };

        template <>
        struct plus<double, 8> {
            using full_type = vec<double, 8>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<double, 8> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a) {
                const full_type neg_bits(sign_f64_msk::v._f64);
                return _mm512_xor_pd(a(), neg_bits());
            }
        };

        template <>
        struct add<double, 8> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_add_pd(a(), b());
            }
        };

        template <>
        struct sub<double, 8> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_sub_pd(a(), b());
            }
        };

        template <>
        struct mul<double, 8> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_mul_pd(a(), b());
            }
        };

        template <>
        struct div<double, 8> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_div_pd(a(), b());
            }
        };

#if 0
        template <>
        struct mod<double, 8> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return full_type(a() % b());
            }
        };
#endif

        template <>
        struct fma<double, 8> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (__FMA4__)
                return _mm512_macc_pd(a(), b(), c());
#elif defined (__FMA__)
                return _mm512_fmadd_pd(a(), b(), c());
#else
                return _mm512_add_pd(_mm512_mul_pd(a(), b()), c());
#endif
            }
        };

        template <>
        struct fms<double, 8> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (__FMA4__)
                return _mm512_msub_pd(a(), b(), c());
#elif defined (__FMA__)
                return _mm512_fmsub_pd(a(), b(), c());
#else
                return _mm512_sub_pd(_mm512_mul_pd(a(), b()), c());
#endif
            }
        };

        template <>
        struct fnma<double, 8> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (__FMA4__)
                return _mm512_nmacc_pd(a(), b(), c());
#elif defined (__FMA__)
                return _mm512_fnmadd_pd(a(), b(), c());
#else
                return _mm512_sub_pd(c(), _mm512_mul_pd(a(), b()));
#endif
            }
        };

        template <>
        struct bit_or<double, 8> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_or_pd(a(), b());
            }
        };

        template <>
        struct bit_and<double, 8> {
            using full_type = vec<double, 8>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_and_pd(a(), b());
            }
        };

        template <>
        struct bit_xor<double, 8> {
            using full_type = vec<double, 8>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_xor_pd(a(), b());
            }
        };

#if 0
        template <>
        struct shl<double, 8> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_slli_epi32(a(), s);
            }
        };

        template <>
        struct shr<double, 8> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_srli_epi32(a(), s);
            }
        };
#endif

    }
#endif // __AVX__
}

#if defined (__AVX512F__)

inline
cftal::vec<double, 8>::vec(double v)
    : base_type(_mm512_set1_pd(v))
{
}


inline
cftal::vec<double, 8>::
vec(std::initializer_list<double> l)
    : vec(mem<vec<double,8>>::load(l.begin(), l.size()))
{
}

inline
cftal::vec<double, 8>::
vec(init_list<double> l)
    : vec(mem<vec<double,8>>::load(l.begin(), l.size()))
{
}

inline
cftal::vec<double, 8>::
vec(const vec<double, 4>& lh, const vec<double, 4>& hh)
    : base_type(_mm512_insertf64x4(as<__m512d>(lh()),
                                   hh(),1))
{
}

template <template <class _U, std::size_t _M> class _OP,
          class _L, class _R>
inline
cftal::
vec<double, 8>::vec(const expr<_OP<double, 8>, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<double, 8>
cftal::mem<cftal::vec<double, 8> >::load(const double* p, std::size_t s)
{
    __m512d v;
    switch (s) {
    default:
    case 8:
        v = _mm512_loadu_pd(p);
        break;
    case 7:
        v = _mm512_setr_pd(p[0], p[1], p[2], p[3],
                           p[4], p[5], p[6], p[6]);
        break;
    case 6:
        v = _mm512_setr_pd(p[0], p[1], p[2], p[3],
                           p[4], p[5], p[5], p[5]);
        break;
    case 5:
        v = _mm512_setr_pd(p[0], p[1], p[2], p[3],
                           p[4], p[4], p[4], p[4]);
        break;
    case 4:
        v = _mm512_setr_pd(p[0], p[1], p[2], p[3],
                           p[3], p[3], p[3], p[3]);
        break;
    case 3:
        v = _mm512_setr_pd(p[0], p[1], p[2], p[2],
                           p[2], p[2], p[2], p[2]);
        break;
    case 2:
        v = _mm512_setr_pd(p[0], p[1], p[1], p[1],
                           p[1], p[1], p[1], p[1]);
        break;
    case 1:
        v = _mm512_setr_pd(p[0], p[0], p[0], p[0],
                           p[0], p[0], p[0], p[0]);
        break;
    case 0:
        v = _mm512_setr_pd(0, 0, 0, 0,
                           0, 0, 0, 0);
        break;
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<double, 8>>::store(double* p, const vec<double, 8>& v)
{
    _mm512_storeu_pd(p, v());
}

inline
cftal::vec<double, 4>
cftal::low_half(const cftal::vec<double, 8>& v)
{
    return _mm512_castpd512_pd256(v());
}

inline
cftal::vec<double, 4>
cftal::high_half(const cftal::vec<double, 8>& v)
{
    return _mm512_extractf64x4_pd(v(), 1);
}

template <std::size_t _I>
double
cftal::extract(const vec<double, 8>& v)
{
    // return x86::extract_f64<_I>(v());
    if (_I>3) {
        constexpr std::size_t _J= _I > 3 ? _I-4 : 0;
        return extract<_J>(high_half(v));
    }
    return extract<_I & 3>(low_half(v));
}

inline
cftal::v8f64
cftal::select(const v8f64::mask_type& m,
              const v8f64& on_true, const v8f64& on_false)
{
    return x86::select_f64(m(), on_true(), on_false());
}

inline
cftal::v8f64 cftal::sqrt(const v8f64& a)
{
    return _mm512_sqrt_pd(a());
}

inline
cftal::v8f64 cftal::abs(const v8f64& a)
{
    const v8f64 msk(not_sign_f64_msk::v._f64);
    return _mm512_and_pd(a(), msk());
}

inline
cftal::v8f64 cftal::andnot(const v8f64& a, const v8f64& b)
{
    return _mm512_andnot_pd(a(), b());
}

inline
cftal::v8f64
cftal::fma(const v8f64& a, const v8f64& b, const v8f64& c)
{
#if defined (__FMA4__)
    return _mm512_macc_pd(a(), b(), c());
#elif defined (__FMA__)
    return _mm512_fmadd_pd(a(), b(), c());
#else
    // return impl::fma(a, b, c);
    return a * b + c;
#endif
}

inline
cftal::v8f64
cftal::fms(const v8f64& a, const v8f64& b, const v8f64& c)
{
#if defined (__FMA4__)
    return _mm512_msub_pd(a(), b(), c());
#elif defined (__FMA__)
    return _mm512_fmsub_pd(a(), b(), c());
#else
    // return impl::fma(a, b, -c);
    return a * b - c;
#endif
}

inline
cftal::v8f64
cftal::nfma(const v8f64& a, const v8f64& b, const v8f64& c)
{
#if defined (__FMA4__)
    return _mm512_nmacc_pd(a(), b(), c());
#elif defined (__FMA__)
    return _mm512_fnmadd_pd(a(), b(), c());
#else
    // return impl::fma(-a, b, c);
    return c - a*b;
#endif
}

inline
cftal::v8f64
cftal::nfms(const v8f64& a, const v8f64& b, const v8f64& c)
{
#if defined (__FMA4__)
    return _mm512_nmsub_pd(a(), b(), c());
#elif defined (__FMA__)
    return _mm512_fnmsub_pd(a(), b(), c());
#else
    // return impl::fma(-a, b, -c);
    return -(a*b) - c;
#endif
}

#if 0
inline
cftal::v8f64
cftal::mad(const v8f64& a, const v8f64& b, const v8f64& c)
{
    return a * b + c;
}

inline
cftal::v8f64
cftal::nmad(const v8f64& a, const v8f64& b, const v8f64& c)
{
    return c -(a * b);
}

inline
cftal::vec<double, 8>::mask_type
cftal::isnan(const v8f64& x)
{
    // exponent = 0x7FF and significand !=0
    // x != x  if x == NAN
    return x != x;
}

inline
cftal::vec<double, 8>::mask_type
cftal::isinf(const v8f64& x)
{
    v8f64 absx(abs(x));
    return absx == v8f64(exp_f64_msk::v._f64);
}
#endif

inline
cftal::v8f64 cftal::copysign(const v8f64& x, const v8f64& y)
{
    // return abs(x) * sgn(y)
    const v8f64 msk(not_sign_f64_msk::v._f64);
    v8f64 abs_x(x & msk);
    v8f64 sgn_y(andnot(msk, y));
    return abs_x | sgn_y;
}

inline
cftal::v8f64 cftal::mulsign(const v8f64& x, const v8f64& y)
{
    const v8f64 msk(sign_f64_msk::v._f64);
    v8f64 sgn_y = y & msk;
    return x ^ sgn_y;
}

inline
unsigned cftal::read_signs(const v8f64::mask_type& a)
{
    return x86::read_signs_f64(a());
}

inline
bool cftal::elements_equal(const v8f64& a)
{
    double t0= extract<0>(a);
    v8f64 cmp0(t0);
    v8f64::mask_type rv(cmp0 == a);
    return all_of(rv);
}

inline
cftal::v8f64 cftal::x86::round(const v8f64& a, rounding_mode::type m)
{
    v8f64 r;
    switch (m) {
    case rounding_mode::nearest:
        r= _mm512_roundscale_round_pd(a(), 0, 0+8);
        break;
    case rounding_mode::downward:
        r= _mm512_roundscale_round_pd(a(), 0, 1+8);
        break;
    case rounding_mode::upward:
        r= _mm512_roundscale_round_pd(a(), 0, 2+8);
        break;
    case rounding_mode::towardzero:
        r= _mm512_roundscale_round_pd(a(), 0, 3+8);
        break;
    case rounding_mode::current:
        r= _mm512_roundscale_round_pd(a(), 0, 4+8);
        break;
    }
    return r;
}

inline
cftal::v8f64 cftal::rint(const v8f64& a)
{
    return x86::round(a, rounding_mode::current);
}

inline
cftal::v8f64 cftal::floor(const v8f64& a)
{
    return x86::round(a, rounding_mode::downward);
}

inline
cftal::v8f64 cftal::ceil(const v8f64& a)
{
    return x86::round(a, rounding_mode::upward);
}

inline
cftal::v8f64 cftal::trunc(const v8f64& a)
{
    return x86::round(a, rounding_mode::towardzero);
}

template <bool _I0, bool _I1, bool _I2, bool _I3>
inline
cftal::vec<double, 8>
cftal::select(const vec<double, 8>& l, const vec<double, 8>& r)
{
    return x86::select_f64<_I0, _I1, _I2, _I3>(l(), r());
}

template <int _I0, int _I1, int _I2, int _I3>
inline
cftal::vec<double, 8>
cftal::permute(const vec<double, 8>& v)
{
    return x86::perm_f64<_I0, _I1, _I2, _I3>(v());
}

template <int _I0, int _I1, int _I2, int _I3>
inline
cftal::vec<double, 8>
cftal::permute(const vec<double, 8>& l, const vec<double, 8>& r)
{
    return x86::perm_f64<_I0, _I1, _I2, _I3>(l(), r());
}


#endif // __AVX512F__

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V8F64__