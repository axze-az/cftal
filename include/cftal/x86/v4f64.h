//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_X86_V4F64__)
#define __CFTAL_X86_V4F64__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/constants.h>
#include <cftal/vec_double_n.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/v2f64.h>
#include <cftal/x86/ops_1.h>

namespace cftal {

#if defined (__AVX__)
    template <>
    class vec<double, 4> : public x86::vreg<__m256d> {
    public:
        using base_type = x86::vreg<__m256d>;

        using value_type = double;
#if defined (__AVX512VL__)
        using mask_value_type = bit;
#else
        using mask_value_type = double;
#endif
        using mask_type= vec<mask_value_type, 4>;

        using x86::vreg<__m256d>::vreg;
        vec() = default;
        // create vec{v,v,v,v}
        vec(double v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<double> l);
        // allow construction from vec<double, 8>
        vec(init_list<double> l);
        // allow construction from two halfes
        vec(const vec<double, 2>& lh, const vec<double, 2>& hh);

        // expression template constructor
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<double, 4>, _L, _R>& r);
    };

    template <>
    struct arg< vec<double, 4> > {
        using type = vec<double, 4>;
    };

    template <>
    struct mem< vec<double, 4> > {
        static
        vec<double, 4> load(const double* p, std::size_t n=4);
        static
        void store(double* p, const vec<double, 4>& v);
    };

    vec<double, 2>
    low_half(const vec<double, 4>& s);

    vec<double, 2>
    high_half(const vec<double, 4>& s);

#if !defined (__AVX512VL__)
    bool
    any_of(const vec<double, 4>::mask_type& s);
    bool
    all_of(const vec<double, 4>::mask_type& s);
    bool
    none_of(const vec<double, 4>::mask_type& s);
#endif

    template <std::size_t _I>
    double
    extract(const vec<double, 4>& s);

    vec<double, 4>
    select(const vec<double, 4>::mask_type& msk,
           const vec<double, 4>& on_true,
           const vec<double, 4>& on_false);

    vec<double, 4>
    select_val_or_zero(const vec<double, 4>::mask_type& msk,
                       const vec<double, 4>& on_true);

    vec<double, 4>
    select_zero_or_val(const vec<double, 4>::mask_type& msk,
                       const vec<double, 4>& on_false);

    unsigned
    read_signs(const vec<double, 4>& b);

    bool
    elements_equal(const vec<double, 4>& v);

    v4f64 max(const v4f64& a, const v4f64& b);
    v4f64 min(const v4f64& a, const v4f64& b);
    double max_element(const v4f64& v);
    double min_element(const v4f64& v);

    v4f64 abs(const v4f64& a);
    v4f64 fabs(const v4f64& a);
    v4f64 sqrt(const v4f64& a);

    namespace x86 {
        v4f64 round(const v4f64& v, rounding_mode::type m);
    }

    v4f64 rint(const v4f64& a);
    v4f64 floor(const v4f64& a);
    v4f64 ceil(const v4f64& a);
    v4f64 trunc(const v4f64& a);
    // returns (~a) & (b)
    v4f64 andnot(const v4f64& a, const v4f64& b);
    v4f64 copysign(const v4f64& x, const v4f64& y);
    v4f64 mulsign(const v4f64& x, const v4f64& y);

#endif

#if defined (__AVX__)
    // a*b +c
    v4f64 fma(const v4f64& a, const v4f64& b, const v4f64& c);
    // a*b -c
    v4f64 fms(const v4f64& a, const v4f64& b, const v4f64& c);
    // -(a*b) + c
    v4f64 nfma(const v4f64& a, const v4f64& b, const v4f64& c);
    // -(a*b) - c
    v4f64 nfms(const v4f64& a, const v4f64& b, const v4f64& c);

    template <bool _P0, bool _P1,
              bool _P2, bool _P3>
    vec<double, 4>
    select(const vec<double, 4>& on_true,
           const vec<double, 4>& on_false);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3>
    vec<double, 4>
    permute(const vec<double, 4>& s);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3>
    vec<double, 4>
    permute(const vec<double, 4>& s0,
            const vec<double, 4>& s1);

    namespace impl {
#if defined (__AVX2__)
        template <std::size_t _L>
        struct lookup<_L, int32_t, double, 4> {
            static
            vec<double, 4>
            v(const vec<int32_t, 4>& idx, const double* tbl) {
                return _mm256_i32gather_pd(tbl, idx(), sizeof(double));
            }
        };
#endif
    }

    namespace op {

        template <>
        struct bit_not<double, 4> {
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
        struct lt<double, 4> {
            using full_type = vec<double, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmp_pd_mask(a(), b(), _CMP_LT_OS);
#else
                return _mm256_cmp_pd(a(), b(), _CMP_LT_OS);
#endif
            }
        };

        template <>
        struct le<double, 4> {
            using full_type = vec<double, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmp_pd_mask(a(), b(), _CMP_LE_OS);
#else
                return _mm256_cmp_pd(a(), b(), _CMP_LE_OS);
#endif
            }
        };

        template <>
        struct eq<double, 4> {
            using full_type = vec<double, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmp_pd_mask(a(), b(), _CMP_EQ_OQ);
#else
                return _mm256_cmp_pd(a(), b(), _CMP_EQ_OQ);
#endif
            }
        };

        template <>
        struct ne<double, 4> {
            using full_type = vec<double, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmp_pd_mask(a(), b(), _CMP_NEQ_UQ);
#else
                return _mm256_cmp_pd(a(), b(), _CMP_NEQ_UQ);
#endif
            }
        };

        template <>
        struct ge<double, 4> {
            using full_type = vec<double, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmp_pd_mask(a(), b(), _CMP_GE_OS);
#else
                return _mm256_cmp_pd(a(), b(), _CMP_GE_OS);
#endif
            }
        };

        template <>
        struct gt<double, 4> {
            using full_type = vec<double, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmp_pd_mask(a(), b(), _CMP_GT_OS);
#else
                return _mm256_cmp_pd(a(), b(), _CMP_GT_OS);
#endif
            }
        };

        template <>
        struct plus<double, 4> {
            using full_type = vec<double, 4>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<double, 4> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a) {
                const full_type neg_bits(sign_f64_msk::v.f64());
                return _mm256_xor_pd(a(), neg_bits());
            }
        };

        template <>
        struct add<double, 4> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_add_pd(a(), b());
            }
        };

        template <>
        struct sub<double, 4> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_sub_pd(a(), b());
            }
        };

        template <>
        struct mul<double, 4> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_mul_pd(a(), b());
            }
        };

        template <>
        struct div<double, 4> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_div_pd(a(), b());
            }
        };

#if 0
        template <>
        struct mod<double, 4> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return full_type(a() % b());
            }
        };
#endif

        template <>
        struct fma<double, 4> {
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
        struct fms<double, 4> {
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
        struct fnma<double, 4> {
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
        struct bit_or<double, 4> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_or_pd(a(), b());
            }
        };

        template <>
        struct bit_and<double, 4> {
            using full_type = vec<double, 4>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_and_pd(a(), b());
            }
        };

        template <>
        struct bit_xor<double, 4> {
            using full_type = vec<double, 4>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_xor_pd(a(), b());
            }
        };

#if 0
        template <>
        struct shl<double, 4> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_slli_epi32(a(), s);
            }
        };

        template <>
        struct shr<double, 4> {
            using full_type = vec<double, 4>;
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
    : base_type(x86::impl::vinsertf128<1>::v(as<__m256d>(lh()),
                                             hh()))
{
}

template <template <class _U, std::size_t _M> class _OP,
          class _L, class _R>
inline
cftal::
vec<double, 4>::vec(const expr<_OP<double, 4>, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<double, 4>
cftal::mem<cftal::vec<double, 4> >::load(const double* p, std::size_t s)
{
    __m256d v;
    switch (s) {
    default:
    case 4:
        v = _mm256_loadu_pd(p);
        break;
    case 3:
        v = _mm256_setr_pd(p[0], p[1], p[2], p[2]);
        break;
    case 2:
        v = _mm256_setr_pd(p[0], p[1], p[1], p[1]);
        break;
    case 1:
        v = _mm256_setr_pd(p[0], p[0], p[0], p[0]);
        break;
    case 0:
        v = _mm256_setr_pd(0, 0, 0, 0);
        break;
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<double, 4>>::store(double* p, const vec<double, 4>& v)
{
    _mm256_storeu_pd(p, v());
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

template <std::size_t _I>
double
cftal::extract(const vec<double, 4>& v)
{
    return x86::extract_f64<_I>(v());
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
    return _mm256_and_pd(m(), on_true());
}

inline
cftal::v4f64
cftal::select_zero_or_val(const v4f64::mask_type& m,
                          const v4f64& on_false)
{
    return _mm256_andnot_pd(m(), on_false());
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

#if 0
inline
cftal::v4f64
cftal::mad(const v4f64& a, const v4f64& b, const v4f64& c)
{
    return a * b + c;
}

inline
cftal::v4f64
cftal::nmad(const v4f64& a, const v4f64& b, const v4f64& c)
{
    return c -(a * b);
}

inline
cftal::vec<double, 4>::mask_type
cftal::isnan(const v4f64& x)
{
    // exponent = 0x7FF and significand !=0
    // x != x  if x == NAN
    return x != x;
}

inline
cftal::vec<double, 4>::mask_type
cftal::isinf(const v4f64& x)
{
    v4f64 absx(abs(x));
    return absx == v4f64(exp_f64_msk::v.f64());
}
#endif

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

#if !defined (__AVX512VL__)
inline
bool cftal::any_of(const vec<double, 4>::mask_type& s)
{
    return x86::read_signs_f64(s()) != 0;
}

inline
bool
cftal::all_of(const vec<double, 4>::mask_type& s)
{
    return x86::read_signs_f64(s()) == 0xf;
}

inline
bool
cftal::none_of(const vec<double, 4>::mask_type& s)
{
    return x86::read_signs_f64(s()) == 0;
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
cftal::max_element(const v4f64& v)
{
    v2f64 hh= high_half(v);
    v2f64 lh= low_half(v);
    return max_element(max(lh, hh));
}

inline
double
cftal::min_element(const v4f64& v)
{
    v2f64 hh= high_half(v);
    v2f64 lh= low_half(v);
    return min_element(min(lh, hh));
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


#endif // __AVX__

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V4F64__
