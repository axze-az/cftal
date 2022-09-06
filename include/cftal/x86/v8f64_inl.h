//
// Copyright (C) 2010-2022 Axel Zeuner
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

#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)

namespace cftal {

    namespace op {

        template <>
        struct bit_not<vec<double, 8>> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a) {
                constexpr const bytes8 all_one{-1, -1};
                const full_type all_set(all_one.f64());
                return _mm512_xor_pd(a(), all_set());
            }
        };

        template <>
        struct lt<vec<double, 8>> {
            using full_type = vec<double, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmp_pd_mask(a(), b(), _CMP_LT_OS);
            }
        };

        template <>
        struct le<vec<double, 8>> {
            using full_type = vec<double, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmp_pd_mask(a(), b(), _CMP_LE_OS);
            }
        };

        template <>
        struct eq<vec<double, 8>> {
            using full_type = vec<double, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmp_pd_mask(a(), b(), _CMP_EQ_OQ);
            }
        };

        template <>
        struct ne<vec<double, 8>> {
            using full_type = vec<double, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmp_pd_mask(a(), b(), _CMP_UNORD_Q);
            }
        };

        template <>
        struct ge<vec<double, 8>> {
            using full_type = vec<double, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmp_pd_mask(a(), b(), _CMP_GE_OS);
            }
        };

        template <>
        struct gt<vec<double, 8>> {
            using full_type = vec<double, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmp_pd_mask(a(), b(), _CMP_GT_OS);
            }
        };

        template <>
        struct plus<vec<double, 8>> {
            using full_type = vec<double, 8>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<double, 8>> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a) {
                const full_type neg_bits(sign_f64_msk::v.f64());
                return _mm512_xor_pd(a(), neg_bits());
            }
        };

        template <>
        struct add<vec<double, 8>> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_add_pd(a(), b());
            }
        };

        template <>
        struct sub<vec<double, 8>> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_sub_pd(a(), b());
            }
        };

        template <>
        struct mul<vec<double, 8>> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_mul_pd(a(), b());
            }
        };

        template <>
        struct div<vec<double, 8>> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_div_pd(a(), b());
            }
        };

        template <>
        struct fma<vec<double, 8>> {
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
        struct fms<vec<double, 8>> {
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
        struct fnma<vec<double, 8>> {
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
        struct bit_or<vec<double, 8>> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_or_pd(a(), b());
            }
        };

        template <>
        struct bit_and<vec<double, 8>> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_and_pd(a(), b());
            }
        };

        template <>
        struct bit_xor<vec<double, 8>> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_xor_pd(a(), b());
            }
        };

#if 0
        template <>
        struct shl<vec<double, 8>> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_slli_epi32(a(), s);
            }
        };

        template <>
        struct shr<vec<double, 8>> {
            using full_type = vec<double, 8>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_srli_epi32(a(), s);
            }
        };
#endif

    }
}

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

template <template <class _U> class _OP,
	  class _L, class _R>
inline
cftal::vec<double, 8>::
vec(const expr<_OP<vec<double, 8> >, _L, _R>& r)
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
        v = _mm512_set1_pd(0.0);
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
cftal::v8f64
cftal::select_val_or_zero(const v8f64::mask_type& m,
                          const v8f64& on_true)
{
    return _mm512_maskz_mov_pd(m(), on_true());
}

inline
cftal::v8f64
cftal::select_zero_or_val(const v8f64::mask_type& m,
                          const v8f64& on_false)
{
    return _mm512_maskz_mov_pd(_knot_mask8(m()), on_false());
}

inline
cftal::v8f64 cftal::sqrt(const v8f64& a)
{
    return _mm512_sqrt_pd(a());
}

inline
cftal::v8f64 cftal::abs(const v8f64& a)
{
    const v8f64 msk(not_sign_f64_msk::v.f64());
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


inline
cftal::v8f64 cftal::copysign(const v8f64& x, const v8f64& y)
{
    // return abs(x) * sgn(y)
    const v8f64 msk(not_sign_f64_msk::v.f64());
    v8f64 abs_x(x & msk);
    v8f64 sgn_y(andnot(msk, y));
    return abs_x | sgn_y;
}

inline
cftal::v8f64 cftal::mulsign(const v8f64& x, const v8f64& y)
{
    const v8f64 msk(sign_f64_msk::v.f64());
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
cftal::v8f64
cftal::max(const v8f64& a, const v8f64& b)
{
    return _mm512_max_pd(a(), b());
}

inline
cftal::v8f64
cftal::min(const v8f64& a, const v8f64& b)
{
    return _mm512_min_pd(a(), b());
}

inline
cftal::v8f64 cftal::x86::round(const v8f64& a, rounding_mode::type m)
{
    v8f64 r;
    switch (m) {
    case rounding_mode::nearest:
        r= _mm512_roundscale_round_pd(a(), 0, 8);
        break;
    case rounding_mode::downward:
        r= _mm512_roundscale_round_pd(a(), 1, 8);
        break;
    case rounding_mode::upward:
        r= _mm512_roundscale_round_pd(a(), 2, 8);
        break;
    case rounding_mode::towardzero:
        r= _mm512_roundscale_round_pd(a(), 3, 8);
        break;
    case rounding_mode::current:
        r= _mm512_roundscale_round_pd(a(), 4, 8);
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

template <bool _P0, bool _P1, bool _P2, bool _P3,
          bool _P4, bool _P5, bool _P6, bool _P7>
inline
cftal::v8f64 cftal::select(const v8f64& a, const v8f64& b)
{
    return x86::select_f64<_P0, _P1, _P2, _P3,
                           _P4, _P5, _P6, _P7> (a(), b());
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
cftal::v8f64 cftal::permute(const v8f64& a)
{
    return x86::perm_v8f64<_P0, _P1, _P2, _P3,
                           _P4, _P5, _P6, _P7>(a());
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
cftal::v8f64 cftal::permute(const v8f64& a, const v8f64& b)
{
    return x86::perm_v8f64<_P0, _P1, _P2, _P3,
                           _P4, _P5, _P6, _P7>(a(), b());
}

#endif // __AVX512F__

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V8F64__
