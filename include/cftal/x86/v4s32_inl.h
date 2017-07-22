//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_X86_V4S32_INL__)
#define __CFTAL_X86_V4S32_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/v4s32.h>
#include <cftal/x86/v4u32.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/ops_1.h>
#include <cftal/divisor.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a) {
                full_type all_set(0xffffffff);
                return _mm_xor_si128(a(), all_set());
            }
        };


        template <>
        struct lt<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm_cmp_epi32_mask(a(), b(), _CMP_LT_OS & 7);
#else
                return _mm_cmpgt_epi32(b(), a());
#endif
            }
        };

        template <>
        struct le<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm_cmp_epi32_mask(a(), b(), _CMP_LE_OS & 7);
#else
#if defined (__SSE4_1__)
                // a <= b: a == min(a, b);
                __m128i min_ab = _mm_min_epi32(b(), a());
                return _mm_cmpeq_epi32(a(), min_ab);
#else
                mask_type b_gt_a(lt<int32_t, 4>::v(b(), a()));
                const mask_type all_set(uint32_t(-1));
                return _mm_xor_si128(b_gt_a(), all_set());
#endif
#endif
            }
        };

        template <>
        struct eq<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm_cmp_epi32_mask(a(), b(), _CMP_EQ_OQ & 7);
#else
                return _mm_cmpeq_epi32(a(), b());
#endif
            }
        };

        template <>
        struct ne<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm_cmp_epi32_mask(a(), b(), _CMP_UNORD_Q & 7);
#else
                mask_type a_eq_b(eq<int32_t, 4>::v(a, b));
                return bit_not<int32_t, 4>::v(a_eq_b);
#endif
            }
        };

        template <>
        struct ge<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm_cmp_epi32_mask(a(), b(), _CMP_GE_OS & 7);
#else
#if defined (__SSE4_1__)
                // a >= b: a == max(a, b);
                __m128i max_ab = _mm_max_epi32(b(), a());
                return _mm_cmpeq_epi32(a(), max_ab);
#else
                mask_type a_lt_b( lt<int32_t, 4>::v(a(), b()));
                return bit_not<int32_t, 4>::v(a_lt_b);
#endif
#endif
            }
        };

        template <>
        struct gt<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm_cmp_epi32_mask(a(), b(), _CMP_GT_OS & 7);
#else
                return _mm_cmpgt_epi32(a(), b());
#endif
            }
        };

        template <>
        struct plus<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a) {
#if defined (__SSSE3__)
                const full_type sgn(sign_s32_msk::v.s32());
                return _mm_sign_epi32(a(), sgn());
#else
                const full_type zero(0);
                return _mm_sub_epi32(zero(), a());
#endif
            }
        };

        template <>
        struct add<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_add_epi32(a(), b());
            }
        };

        template <>
        struct sub<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_sub_epi32(a(), b());
            }
        };

        template <>
        struct mul<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::impl::vpmulld::v(a(), b());
            }
        };

        template <>
        struct div<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_s32::v(a(), b());
            }
        };

        template <>
        struct mod<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v4s32 q(a/b);
                v4s32 r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<int32_t, 4>::v(
                    mul<int32_t, 4>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<int32_t, 4>::v(
                    mul<int32_t, 4>::v(a , b), c);
            }
        };

        template <>
        struct fnma<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<int32_t, 4>::v(
                    c, mul<int32_t, 4>::v(a, b));

            }
        };

        template <>
        struct bit_or<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_or_si128(a(), b());
            }
        };

        template <>
        struct bit_and<int32_t, 4> {
            using full_type = vec<int32_t, 4>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_and_si128(a(), b());
            }
        };

        template <>
        struct bit_xor<int32_t, 4> {
            using full_type = vec<int32_t, 4>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_xor_si128(a(), b());
            }
        };

        template <>
        struct shl<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_slli_epi32(a(), s);
            }
        };

        template <>
        struct shr<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_srai_epi32(a(), s);
            }
        };

        template <>
        struct vshl<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return x86::impl::vpsllvd::v(a(), s());
            }
        };

        template <>
        struct vshr<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return x86::impl::vpsravd::v(a(), s());
            }
        };

    }

}

inline
cftal::vec<cftal::int32_t, 4>::vec(const vec<uint32_t, 4>& v)
    : base_type(v())
{
}

inline
cftal::vec<cftal::int32_t, 4>::vec(int32_t v)
    : base_type(_mm_setr_epi32(v, v, v, v))
{
}

inline
cftal::vec<cftal::int32_t, 4>::vec(vec<int32_t, 2> l, vec<int32_t, 2> h)
    : base_type(_mm_setr_epi32(low_half(l)(),
                               high_half(l)(),
                               low_half(h)(),
                               high_half(h)()))
{
}

inline
cftal::vec<cftal::int32_t, 4>::
vec(std::initializer_list<int32_t> l)
    : vec(mem<v4s32>::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::int32_t, 4>::
vec(init_list<int32_t> l)
    : vec(mem<v4s32>::load(l.begin(), l.size()))
{
}

template <template <class _U, std::size_t _M> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::int32_t, 4>::vec(const expr<_OP<int32_t, 4>, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::int32_t, 4>
cftal::mem<cftal::vec<int32_t, 4> >::load(const int32_t* p, std::size_t s)
{
    __m128i v;
    switch (s) {
    default:
    case 4:
        v = _mm_loadu_si128(reinterpret_cast<const __m128i*>(p));
        break;
    case 3:
        v = _mm_setr_epi32(p[0], p[1], p[2], p[2]);
        break;
    case 2:
        v = _mm_setr_epi32(p[0], p[1], p[1], p[1]);
        break;
    case 1:
        v = _mm_setr_epi32(p[0], p[0], p[0], p[0]);
        break;
    case 0:
        v = _mm_setr_epi32(0, 0, 0, 0);
        break;
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<int32_t, 4> >::store(int32_t* p,
                                           const vec<int32_t, 4>& v)
{
    _mm_storeu_si128(reinterpret_cast<__m128i*>(p), v());
}

inline
cftal::vec<int32_t, 2>
cftal::low_half(const vec<int32_t, 4>& v)
{
    int32_t e0= _mm_cvtsi128_si32(v());
    vec<int32_t, 4> t= permute<1, 0, 2, 3>(v);
    int32_t e1= _mm_cvtsi128_si32(t());
    vec<int32_t, 2> r={e0, e1};
    return r;
}

inline
cftal::vec<int32_t, 2>
cftal::high_half(const vec<int32_t, 4>& v)
{
    vec<int32_t, 4> h= permute<2, 3, 0, 1>(v);
    return low_half(h);
}

#if !defined (__AVX512VL__)
inline
bool cftal::all_of(const vec<int32_t, 4>::mask_type& v)
{
    return x86::all_of_v4s32(v());
}

inline
bool cftal::any_of(const vec<int32_t, 4>::mask_type& v)
{
    return x86::any_of_v4s32(v());
}

inline
bool cftal::none_of(const vec<int32_t, 4>::mask_type& v)
{
    return x86::none_of_v4s32(v());
}
#endif

inline
cftal::v4s32 cftal::max(const v4s32& a, const v4s32& b)
{
#if defined (__SSE4_1__)
    return _mm_max_epi32(a(), b());
#else
    v4s32 _gt(a > b);
    return select(_gt, a, b);
#endif
}

inline
cftal::v4s32 cftal::min(const v4s32& a, const v4s32& b)
{
#if defined (__SSE4_1__)
    return _mm_min_epi32(a(), b());
#else
    v4s32 _lt(a < b);
    return select(_lt, a, b);
#endif
}

inline
cftal::v4s32 cftal::abs(const v4s32& a)
{
#if defined (__SSSE3__)
    return _mm_sign_epi32(a(), a());
#else
    v4s32 sgn= a >> 31;
    // invert if negative
    v4s32 inv= a ^ sgn;
    // add 1
    return inv - sgn;
#endif
}

inline
cftal::v4s32 cftal::select(const v4s32::mask_type& m,
                           const v4s32& on_true,
                           const v4s32& on_false)
{
    return x86::select_u32(m(), on_true(), on_false());
}

template <bool _I0, bool _I1, bool _I2, bool _I3>
inline
cftal::v4s32 cftal::select(const v4s32& a, const v4s32& b)
{
    return x86::select_u32<_I0, _I1, _I2, _I3>(a(), b());
}

template <int _I0, int _I1, int _I2, int _I3>
inline
cftal::v4s32 cftal::permute(const v4s32& a)
{
    return x86::perm_v4u32<_I0, _I1, _I2, _I3>(a());
}

template <int _I0, int _I1, int _I2, int _I3>
inline
cftal::v4s32 cftal::permute(const v4s32& a, const v4s32& b)
{
    return x86::perm_v4u32<_I0, _I1, _I2, _I3>(a(), b());
}


inline
std::pair<cftal::v4s32, cftal::v4s32>
cftal::mul_lo_hi(const v4s32& x, const v4s32& y)
{
#if defined (__SSE4_1__)
    // p0l p0h p2l p2h
    v4s32 e= _mm_mul_epi32(x(), y());
    // p1l p1h p3l p3h
    v4s32 o= _mm_mul_epi32(x86::impl::vpshufd<1, 0, 3, 2>::v(x()),
                           x86::impl::vpshufd<1, 0, 3, 2>::v(y()));
    // p0l p1l p0h p1h
    v4s32 t0= permute<0, 4, 1, 5>(e, o);
    // p2l p3l p2h p3h
    v4s32 t1= permute<2, 6, 3, 7>(e, o);
    // p0h p1h p2h p3h
    v4s32 h = permute<2, 3, 6, 7>(t0, t1);
    v4s32 l = permute<0, 1, 4, 5>(t0, t1);
    return std::make_pair(l, h);
#else
    // muluh(x,y) = mulsh(x,y) + and(x, xsign(y)) + and(y, xsign(x));
    // mulsh(x,y) = muluh(x,y) - and(x, xsign(y)) - and(y, xsign(x));
    std::pair<v4u32, v4u32> ur(mul_lo_hi(v4u32(x), v4u32(y)));
    v4s32 xsgn_y= y >> 31; // x86::const_shift::_31;
    v4s32 xsgn_x= x >> 31; // x86::const_shift::_31;
    v4s32 x_and_xsgn_y = x & xsgn_y;
    v4s32 y_and_xsgn_x = y & xsgn_x;
    v4s32 sh = v4s32(ur.second) - x_and_xsgn_y - y_and_xsgn_x;
    v4s32 sl = v4s32(ur.first);
    return std::make_pair(sl, sh);
#endif
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V4S32_INL__
