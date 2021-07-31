//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_X86_V8U32_INL__)
#define __CFTAL_X86_V8U32_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/v8u32.h>
#include <cftal/x86/v8s32.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/ops_1.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;
            static
            full_type
            v(const full_type& a) {
                const full_type all_set(0xffffffff);
                return _mm256_xor_si256(a(), all_set());
            }
        };

        template <>
        struct lt<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmplt_epu32_mask(a(), b());
#else
                v8u32 ta(a ^ full_type(sign_s32_msk::v.u32()));
                v8u32 tb(b ^ full_type(sign_s32_msk::v.u32()));
                return _mm256_cmpgt_epi32(tb(), ta());
#endif
            }
        };

        template <>
        struct le<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmple_epu32_mask(a(), b());
#else
                // a<= b: a == min(a, b);
                __m256i min_ab = _mm256_min_epu32(b(), a());
                return _mm256_cmpeq_epi32(a(), min_ab);
#endif
            }
        };

        template <>
        struct eq<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmpeq_epu32_mask(a(), b());
#else
                return _mm256_cmpeq_epi32(a(), b());
#endif
            }
        };

        template <>
        struct ne<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmpneq_epu32_mask(a(), b());
#else
                mask_type a_eq_b(eq<uint32_t, 8>::v(a, b));
                return bit_not<uint32_t, 8>::v(a_eq_b);
#endif
            }
        };

        template <>
        struct ge<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmpge_epu32_mask(a(), b());
#else
                // a>= b: a == max(a, b);
                __m256i max_ab = _mm256_max_epu32(b(), a());
                return _mm256_cmpeq_epi32(a(), max_ab);
#endif
            }
        };

        template <>
        struct gt<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmpgt_epu32_mask(a(), b());
#else
                v8u32 ta(a ^ full_type(sign_s32_msk::v.u32()));
                v8u32 tb(b ^ full_type(sign_s32_msk::v.u32()));
                return _mm256_cmpgt_epi32(ta(), tb());
#endif
            }
        };

        template <>
        struct plus<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;
            static
            full_type
            v(const full_type& a) {
                const full_type sgn(sign_s32_msk::v.u32());
                return _mm256_sign_epi32(a(), sgn());
            }
        };

        template <>
        struct add<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_add_epi32(a(), b());
            }
        };

        template <>
        struct sub<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_sub_epi32(a(), b());
            }
        };

        template <>
        struct mul<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::vpmulld::v(a(), b());
            }
        };

        template <>
        struct div<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_u32::v(a(), b());
            }
        };

        template <>
        struct mod<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v8u32 q(a/b);
                v8u32 r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<uint32_t, 8>::v(
                    mul<uint32_t, 8>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<uint32_t, 8>::v(
                    mul<uint32_t, 8>::v(a , b), c);
            }
        };

        template <>
        struct fnma<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<uint32_t, 8>::v(
                    c, mul<uint32_t, 8>::v(a, b));

            }
        };

        template <>
        struct bit_or<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_or_si256(a(), b());
            }
        };

        template <>
        struct bit_and<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_and_si256(a(), b());
            }
        };

        template <>
        struct bit_xor<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_xor_si256(a(), b());
            }
        };

        template <>
        struct shl<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm256_slli_epi32(a(), s);
            }
        };

        template <>
        struct shr<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm256_srli_epi32(a(), s);
            }
        };

#if defined (__AVX2__)
        template <>
        struct vshl<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return _mm256_sllv_epi32(a(), s());
            }
        };

        template <>
        struct vshr<uint32_t, 8> {
            using full_type = vec<uint32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return _mm256_srlv_epi32(a(), s());
            }
        };
#endif

    }

}

inline
cftal::vec<cftal::uint32_t, 8>::vec(const vec<int32_t, 8>& v)
    : base_type(v())
{
}

inline
cftal::vec<cftal::uint32_t, 8>::vec(uint32_t v)
    : base_type(_mm256_setr_epi32(v, v, v, v, v, v, v, v))
{
}

inline
cftal::vec<cftal::uint32_t, 8>::vec(const vec<uint32_t, 4>& l,
                                    const vec<uint32_t, 4>& h)
    : base_type(_mm256_inserti128_si256(
                    _mm256_castsi128_si256(l()), h(), 1))
{
}

inline
cftal::vec<cftal::uint32_t, 8>::
vec(std::initializer_list<uint32_t> l)
    : vec(mem<vec<uint32_t, 8> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::uint32_t, 8>::
vec(init_list<uint32_t> l)
    : vec(mem<vec<uint32_t, 8> >::load(l.begin(), l.size()))
{
}

template <template <class _U, std::size_t _M> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::uint32_t, 8>::vec(const expr<_OP<uint32_t, 8>, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::uint32_t, 8>
cftal::mem<cftal::vec<uint32_t, 8> >::load(const uint32_t* p, std::size_t s)
{
    __m256i v;
    switch (s) {
    default:
    case 8:
        v = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p));
        break;
    case 7:
        v = _mm256_setr_epi32(p[0], p[1], p[2], p[3],
                              p[4], p[5], p[6], p[6]);
        break;
    case 6:
        v = _mm256_setr_epi32(p[0], p[1], p[2], p[3],
                              p[4], p[5], p[5], p[5]);
        break;
    case 5:
        v = _mm256_setr_epi32(p[0], p[1], p[2], p[3],
                              p[4], p[4], p[4], p[4]);
        break;
    case 4:
        v = _mm256_setr_epi32(p[0], p[1], p[2], p[3],
                              p[3], p[3], p[3], p[3]);
        break;
    case 3:
        v = _mm256_setr_epi32(p[0], p[1], p[2], p[2],
                              p[2], p[2], p[2], p[2]);
        break;
    case 2:
        v = _mm256_setr_epi32(p[0], p[1], p[1], p[1],
                              p[1], p[1], p[1], p[1]);
        break;
    case 1:
        v = _mm256_setr_epi32(p[0], p[0], p[0], p[0],
                              p[0], p[0], p[0], p[0]);
        break;
    case 0:
        v = _mm256_setr_epi32(0, 0, 0, 0, 0, 0, 0, 0);
        break;
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<uint32_t, 8> >::
store(uint32_t* p, const vec<uint32_t, 8>& v)
{
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(p), v());
}

inline
cftal::vec<uint32_t, 4>
cftal::low_half(const cftal::vec<uint32_t, 8>& v)
{
    return _mm256_castsi256_si128(v());
}

inline
cftal::vec<uint32_t, 4>
cftal::high_half(const cftal::vec<uint32_t, 8>& v)
{
    return _mm256_extracti128_si256(v(), 1);
}

#if !defined (__AVX512VL__)
inline
bool cftal::all_of(const vec<uint32_t, 8>::mask_type& v)
{
    return x86::all_of_s32(v());
}

inline
bool cftal::any_of(const vec<uint32_t, 8>::mask_type& v)
{
    return x86::any_of_s32(v());
}

inline
bool cftal::none_of(const vec<uint32_t, 8>::mask_type& v)
{
    return x86::none_of_s32(v());
}
#endif

inline
cftal::v8u32 cftal::max(const v8u32& a, const v8u32& b)
{
    return _mm256_max_epu32(a(), b());
}

inline
cftal::v8u32 cftal::min(const v8u32& a, const v8u32& b)
{
    return _mm256_min_epu32(a(), b());
}

inline
cftal::v8u32 cftal::select(const v8u32::mask_type& m,
                           const v8u32& on_true,
                           const v8u32& on_false)
{
    return x86::select_u32(m(), on_true(), on_false());
}

inline
cftal::v8u32
cftal::select_val_or_zero(const v8u32::mask_type& m,
                          const v8u32& on_true)
{
    return _mm256_and_si256(m(), on_true());
}

inline
cftal::v8u32
cftal::select_zero_or_val(const v8u32::mask_type& m,
                          const v8u32& on_false)
{
    return _mm256_andnot_si256(m(), on_false());
}

template <bool _P0, bool _P1, bool _P2, bool _P3,
          bool _P4, bool _P5, bool _P6, bool _P7>
inline
cftal::v8u32 cftal::select(const v8u32& a, const v8u32& b)
{
    return x86::select_u32<_P0, _P1, _P2, _P3,
                           _P4, _P5, _P6, _P7> (a(), b());
}

template <int _I0, int _I1, int _I2, int _I3,
          int _I4, int _I5, int _I6, int _I7>
inline
cftal::v8u32 cftal::permute(const v8u32& a)
{
    return x86::perm_v8u32<_I0, _I1, _I2, _I3, _I4, _I5, _I6, _I7>(a());
}

template <int _I0, int _I1, int _I2, int _I3,
          int _I4, int _I5, int _I6, int _I7>
inline
cftal::v8u32 cftal::permute(const v8u32& a, const v8u32& b)
{
    return x86::perm_v8u32<_I0, _I1, _I2, _I3, _I4, _I5, _I6, _I7>(a(), b());
}

inline
std::pair<cftal::v8u32, cftal::v8u32>
cftal::mul_lo_hi(const v8u32& x, const v8u32& y)
{
    // p0l p0h p2l p2h
    v8u32 e= _mm256_mul_epu32(x(), y());
    // p1l p1h p3l p3h
    v8u32 o= _mm256_mul_epu32(x86::vpshufd<1, 0, 3, 2>::v(x()),
                              x86::vpshufd<1, 0, 3, 2>::v(y()));
    // --------------------------------------
    v8s32 l= permute<0, 0+8,
                     2, 2+8,
                     4, 4+8,
                     6, 6+8>(e, o);
    v8s32 h= permute<1, 1+8,
                     3, 3+8,
                     5, 5+8,
                     7, 7+8>(e, o);
    return std::make_pair(l, h);
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V8U32_INL__
