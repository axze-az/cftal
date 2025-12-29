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
#if !defined (__CFTAL_X86_V4F64_INL__)
#define __CFTAL_X86_V4F64_INL__ 1

#if defined (__AVX__)

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/constants.h>
#include <cftal/x86/v4f64.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/v2f64.h>
#include <cftal/x86/ops_1.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<vec<double, 4>> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a) {
                constexpr const bytes8 all_one{-1, -1};
                const full_type all_set(all_one.f64());
                return _mm256_xor_pd(a(), all_set());
            }
        };

        template <>
        struct lt<vec<double, 4>> {
            using full_type = vec<double, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmp_pd_mask(a(), b(), _CMP_LT_OS);
#else
                return _mm256_cmp_pd(a(), b(), _CMP_LT_OS);
#endif
            }
        };

        template <>
        struct le<vec<double, 4>> {
            using full_type = vec<double, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmp_pd_mask(a(), b(), _CMP_LE_OS);
#else
                return _mm256_cmp_pd(a(), b(), _CMP_LE_OS);
#endif
            }
        };

        template <>
        struct eq<vec<double, 4>> {
            using full_type = vec<double, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmp_pd_mask(a(), b(), _CMP_EQ_OQ);
#else
                return _mm256_cmp_pd(a(), b(), _CMP_EQ_OQ);
#endif
            }
        };

        template <>
        struct ne<vec<double, 4>> {
            using full_type = vec<double, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmp_pd_mask(a(), b(), _CMP_NEQ_UQ);
#else
                return _mm256_cmp_pd(a(), b(), _CMP_NEQ_UQ);
#endif
            }
        };

        template <>
        struct ge<vec<double, 4>> {
            using full_type = vec<double, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmp_pd_mask(a(), b(), _CMP_GE_OS);
#else
                return _mm256_cmp_pd(a(), b(), _CMP_GE_OS);
#endif
            }
        };

        template <>
        struct gt<vec<double, 4>> {
            using full_type = vec<double, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmp_pd_mask(a(), b(), _CMP_GT_OS);
#else
                return _mm256_cmp_pd(a(), b(), _CMP_GT_OS);
#endif
            }
        };

        template <>
        struct plus<vec<double, 4>> {
            using full_type = vec<double, 4>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<double, 4>> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a) {
                const full_type neg_bits(sign_f64_msk::v.f64());
                return _mm256_xor_pd(a(), neg_bits());
            }
        };

        template <>
        struct add<vec<double, 4>> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_add_pd(a(), b());
            }
        };

        template <>
        struct sub<vec<double, 4>> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_sub_pd(a(), b());
            }
        };

        template <>
        struct mul<vec<double, 4>> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_mul_pd(a(), b());
            }
        };

        template <>
        struct div<vec<double, 4>> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_div_pd(a(), b());
            }
        };

        template <>
        struct fma<vec<double, 4>> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (__FMA4__)
                return _mm256_macc_pd(a(), b(), c());
#elif defined (__FMA__)
                return _mm256_fmadd_pd(a(), b(), c());
#else
                return _mm256_add_pd(_mm256_mul_pd(a(), b()), c());
#endif
            }
        };

        template <>
        struct fms<vec<double, 4>> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (__FMA4__)
                return _mm256_msub_pd(a(), b(), c());
#elif defined (__FMA__)
                return _mm256_fmsub_pd(a(), b(), c());
#else
                return _mm256_sub_pd(_mm256_mul_pd(a(), b()), c());
#endif
            }
        };

        template <>
        struct fnma<vec<double, 4>> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (__FMA4__)
                return _mm256_nmacc_pd(a(), b(), c());
#elif defined (__FMA__)
                return _mm256_fnmadd_pd(a(), b(), c());
#else
                return _mm256_sub_pd(c(), _mm256_mul_pd(a(), b()));
#endif
            }
        };

        template <>
        struct bit_or<vec<double, 4>> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_or_pd(a(), b());
            }
        };

        template <>
        struct bit_and<vec<double, 4>> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_and_pd(a(), b());
            }
        };

        template <>
        struct bit_xor<vec<double, 4>> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_xor_pd(a(), b());
            }
        };


    }
#endif // __AVX__
}

#if defined (__AVX__)

inline
cftal::vec<double, 4>::vec(double v)
    : base_type(_mm256_set1_pd(v))
{
}


inline
cftal::vec<double, 4>::
vec(std::initializer_list<double> l)
    : vec(mem<vec<double,4>>::load(l.begin(), l.size()))
{
}

inline
cftal::vec<double, 4>::
vec(init_list<double> l)
    : vec(mem<vec<double,4>>::load(l.begin(), l.size()))
{
}

inline
cftal::vec<double, 4>::
vec(const vec<double, 2>& lh, const vec<double, 2>& hh)
    : base_type(x86::vinsertf128<1>::v(as<__m256d>(lh()),
                                             hh()))
{
}

template <template <class _U> class _OP,
          class _L, class _R>
inline
cftal::
vec<double, 4>::vec(const expr<_OP<vec<double, 4> >, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<double, 4>
cftal::mem<cftal::vec<double, 4> >::load(const double* p, ssize_t s)
{
    vec<double, 4> v;
    if (s>=4) {
        v = _mm256_loadu_pd(p);
    } else if (s<=0) {
        v = _mm256_setr_pd(0, 0, 0, 0);
    } else {
        auto lh= mem<vec<double, 2> >::load(p, s);
        ssize_t sh = s > 2 ? s-2 : 0;
        auto hh= mem<vec<double, 2> >::load(p+2, sh);
        v=vec<double, 4>(lh, hh);
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<double, 4>>::
store(double* p, const vec<double, 4>& v, ssize_t s)
{
    if (s>=4) {
        _mm256_storeu_pd(p, v());
    } else if (s>2) {
        mem<cftal::vec<double, 2> >::store(p, low_half(v), s);
        mem<cftal::vec<double, 2> >::store(p+2, high_half(v), s-2);
    } else if (s>0) {
        mem<cftal::vec<double, 2> >::store(p, low_half(v), s);
    }
}

inline
cftal::vec<double, 2>
cftal::low_half(const cftal::vec<double, 4>& v)
{
    return _mm256_castpd256_pd128(v());
}

inline
cftal::vec<double, 2>
cftal::high_half(const cftal::vec<double, 4>& v)
{
    return _mm256_extractf128_pd(v(), 1);
}

template <cftal::size_t _I>
inline
double
cftal::extract(const vec<double, 4>& v)
{
    return x86::extract_f64<_I>(v());
}

inline
double
cftal::extract(const vec<double, 4>& v, size_t i)
{
    return x86::extract_f64(v(), i);
}

template <cftal::size_t _I>
inline
void
cftal::insert(vec<double, 4>& v, const double& vi)
{
    v= x86::insert_f64<_I>(v(), vi);
}

inline
void
cftal::insert(vec<double, 4>& v, const double& vi, size_t i)
{
    v= x86::insert_f64(v(), vi, i);
}

inline
cftal::v4f64
cftal::select(const v4f64::mask_type& m,
              const v4f64& on_true, const v4f64& on_false)
{
    return x86::select_f64(m(), on_true(), on_false());
}

inline
cftal::v4f64
cftal::select_val_or_zero(const v4f64::mask_type& m,
                          const v4f64& on_true)
{
#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm256_and_pd(m(), on_true());
#else
    return _mm256_maskz_mov_pd(m(), on_true());
#endif
}

inline
cftal::v4f64
cftal::select_zero_or_val(const v4f64::mask_type& m,
                          const v4f64& on_false)
{
#if !defined (__AVX512VL__)  || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm256_andnot_pd(m(), on_false());
#else
    return _mm256_maskz_mov_pd(_knot_mask8(m()), on_false());
#endif
}

inline
cftal::v4f64 cftal::sqrt(const v4f64& a)
{
    return _mm256_sqrt_pd(a());
}

inline
cftal::v4f64 cftal::abs(const v4f64& a)
{
    const v4f64 msk(not_sign_f64_msk::v.f64());
    return _mm256_and_pd(a(), msk());
}

inline
cftal::v4f64 cftal::andnot(const v4f64& a, const v4f64& b)
{
    return _mm256_andnot_pd(a(), b());
}

inline
cftal::v4f64
cftal::fma(const v4f64& a, const v4f64& b, const v4f64& c)
{
#if defined (__FMA4__)
    return _mm256_macc_pd(a(), b(), c());
#elif defined (__FMA__)
    return _mm256_fmadd_pd(a(), b(), c());
#else
    // return impl::fma(a, b, c);
    return a * b + c;
#endif
}

inline
cftal::v4f64
cftal::fms(const v4f64& a, const v4f64& b, const v4f64& c)
{
#if defined (__FMA4__)
    return _mm256_msub_pd(a(), b(), c());
#elif defined (__FMA__)
    return _mm256_fmsub_pd(a(), b(), c());
#else
    // return impl::fma(a, b, -c);
    return a * b - c;
#endif
}

inline
cftal::v4f64
cftal::nfma(const v4f64& a, const v4f64& b, const v4f64& c)
{
#if defined (__FMA4__)
    return _mm256_nmacc_pd(a(), b(), c());
#elif defined (__FMA__)
    return _mm256_fnmadd_pd(a(), b(), c());
#else
    // return impl::fma(-a, b, c);
    return c - a*b;
#endif
}

inline
cftal::v4f64
cftal::nfms(const v4f64& a, const v4f64& b, const v4f64& c)
{
#if defined (__FMA4__)
    return _mm256_nmsub_pd(a(), b(), c());
#elif defined (__FMA__)
    return _mm256_fnmsub_pd(a(), b(), c());
#else
    // return impl::fma(-a, b, -c);
    return -(a*b) - c;
#endif
}

inline
cftal::v4f64 cftal::copysign(const v4f64& x, const v4f64& y)
{
    // return abs(x) * sgn(y)
    const v4f64 msk(not_sign_f64_msk::v.f64());
    v4f64 abs_x(x & msk);
    v4f64 sgn_y(andnot(msk, y));
    return abs_x | sgn_y;
}

inline
cftal::v4f64 cftal::mulsign(const v4f64& x, const v4f64& y)
{
    const v4f64 msk(sign_f64_msk::v.f64());
    v4f64 sgn_y = y & msk;
    return x ^ sgn_y;
}

#if !defined (__AVX512VL__)  || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
inline
bool cftal::any_of(const vec<double, 4>::mask_type& s)
{
    return x86::any_of_f64(s());
}

inline
bool
cftal::all_of(const vec<double, 4>::mask_type& s)
{
    return x86::all_of_f64(s());
}

inline
bool
cftal::none_of(const vec<double, 4>::mask_type& s)
{
    return x86::none_of_f64(s());
}

inline
cftal::vec<cftal::bit, 4>
cftal::compress_mask(const vec<double, 4>::mask_type& v)
{
    return x86::compress_mask_f64(v());
}

inline
cftal::vec<double, 4>
cftal::expand_mask<cftal::vec<double, 4> >::
from(const vec<bit, 4>& s)
{
    return x86::expand_mask_v4f64(s());
}

#endif

inline
unsigned cftal::read_signs(const v4f64& a)
{
    return x86::read_signs_f64(a());
}

inline
bool cftal::elements_equal(const v4f64& a)
{
    double t0= extract<0>(a);
    v4f64 cmp0(t0);
    v4f64::mask_type rv(cmp0 == a);
    return all_of(rv);
}

inline
cftal::v4f64
cftal::max(const v4f64& a, const v4f64& b)
{
    return _mm256_max_pd(a(), b());
}

inline
cftal::v4f64
cftal::min(const v4f64& a, const v4f64& b)
{
    return _mm256_min_pd(a(), b());
}

inline
double
cftal::hmax(const v4f64& v)
{
    v2f64 hh= high_half(v);
    v2f64 lh= low_half(v);
    return hmax(max(lh, hh));
}

inline
double
cftal::hmin(const v4f64& v)
{
    v2f64 hh= high_half(v);
    v2f64 lh= low_half(v);
    return hmin(min(lh, hh));
}


inline
cftal::v4f64 cftal::x86::round(const v4f64& a, rounding_mode::type m)
{
    v4f64 r;
    switch (m) {
    case rounding_mode::nearest:
        r= _mm256_round_pd(a(), 0+8);
        break;
    case rounding_mode::downward:
        r= _mm256_round_pd(a(), 1+8);
        break;
    case rounding_mode::upward:
        r= _mm256_round_pd(a(), 2+8);
        break;
    case rounding_mode::towardzero:
        r= _mm256_round_pd(a(), 3+8);
        break;
    case rounding_mode::current:
        r= _mm256_round_pd(a(), 4+8);
        break;
    }
    return r;
}

inline
cftal::v4f64 cftal::rint(const v4f64& a)
{
    return x86::round(a, rounding_mode::current);
}

inline
cftal::v4f64 cftal::floor(const v4f64& a)
{
    return x86::round(a, rounding_mode::downward);
}

inline
cftal::v4f64 cftal::ceil(const v4f64& a)
{
    return x86::round(a, rounding_mode::upward);
}

inline
cftal::v4f64 cftal::trunc(const v4f64& a)
{
    return x86::round(a, rounding_mode::towardzero);
}

template <bool _I0, bool _I1, bool _I2, bool _I3>
inline
cftal::vec<double, 4>
cftal::select(const vec<double, 4>& l, const vec<double, 4>& r)
{
    return x86::select_f64<_I0, _I1, _I2, _I3>(l(), r());
}

template <int _I0, int _I1, int _I2, int _I3>
inline
cftal::vec<double, 4>
cftal::permute(const vec<double, 4>& v)
{
    return x86::perm_v4f64<_I0, _I1, _I2, _I3>(v());
}

template <int _I0, int _I1, int _I2, int _I3>
inline
cftal::vec<double, 4>
cftal::permute(const vec<double, 4>& l, const vec<double, 4>& r)
{
    return x86::perm_v4f64<_I0, _I1, _I2, _I3>(l(), r());
}

#if defined (__AVX2__)
inline
cftal::vec<double, 4>
cftal::permute(const vec<double, 4>& s, const vec<int64_t, 4>& idx)
{
    return x86::permute_v4f64_v4s64(s(), idx());
}

inline
cftal::impl::variable_vec_lookup_table<double, int32_t, 4>::
variable_vec_lookup_table(const vec<int32_t, 4>& idx)
    : _msk(idx)
{
}

inline
cftal::vec<double, 4>
cftal::impl::variable_vec_lookup_table<double, int32_t, 4>::
fromp(const double* tbl) const
{
    return x86::vgatherdpd<__m256d, __m128i>::v<sizeof(double)>(tbl, _msk());
}
#endif

inline
__m256i
cftal::impl::fixed_vec_lookup_table<2, double, int32_t, 4>::
setup_msk(const vec<int32_t, 4>& idx)
{
    // the selector bit is bit 1 not bit 0
    vec<int32_t, 4> idx2=idx+idx;
#if defined (__AVX2__)
    __m256i t=x86::vpmovzxdq::v(
        _mm256_castsi128_si256(idx2()));
    return t;
#else
    __m128i l=x86::vpmovzxdq::v(idx2());
    vec<int32_t, 4> idx2perm=permute<2, 3, 0, 1>(idx2);
    __m128i h=x86::vpmovzxdq::v(idx2perm());
    __m256i t=x86::vinsertf128<1>::v(
        _mm256_castsi128_si256(l), h);
    return t;
#endif
}

inline
cftal::impl::fixed_vec_lookup_table<2, double, int32_t, 4>::
fixed_vec_lookup_table(const vec<int32_t, 4>& idx)
    : _msk(setup_msk(idx))
{
}

inline
cftal::v4f64
cftal::impl::fixed_vec_lookup_table<2, double, int32_t, 4>::
fromp(const double* tbl) const
{
    vec<double, 2> r=mem<vec<double, 2> >::load(tbl, 2);
    __m128d rn=r();
    __m256d r2=x86::vinsertf128<1>::v(
        _mm256_castpd128_pd256(rn), rn);
    return _mm256_permutevar_pd(r2, _msk);
}

#if defined (__AVX2__)
inline
__m256i
cftal::impl::fixed_vec_lookup_table<4, double, int32_t, 4>::
setup_msk(const vec<int32_t, 4>& idx)
{
    vec<int32_t, 4> i2=idx+idx;
#if 1
    vec<int32_t, 8> t(_mm256_castsi128_si256(i2()));
    t=permute<0, 0, 1, 1, 2, 2, 3, 3>(t);
#else
    vec<int32_t, 8> t(i2, i2);
    t=permute<0, 0, 1, 1, 6, 6, 7, 7>(t);
#endif
    const __m256i offs=x86::const_v8u32<0, 1, 0, 1, 0, 1, 0, 1>::iv();
    __m256i r=_mm256_add_epi32(t(), offs);
    return r;
}

inline
cftal::impl::fixed_vec_lookup_table<4, double, int32_t, 4>::
fixed_vec_lookup_table(const vec<int32_t, 4>& idx)
    : _msk(setup_msk(idx))
{
}

inline
cftal::vec<double, 4>
cftal::impl::fixed_vec_lookup_table<4, double, int32_t, 4>::
fromp(const double* tbl) const
{
    vec<double, 4> r=mem<vec<double, 4> >::load(tbl, 4);
    __m256i ir=_mm256_permutevar8x32_epi32(_mm256_castpd_si256(r()), _msk);
    r=_mm256_castsi256_pd(ir);
    return r;
}

#endif

#endif // __AVX__

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V4F64_INL__
