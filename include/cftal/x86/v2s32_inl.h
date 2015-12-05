#if !defined (__CFTAL_X86_V2S32_INL__)
#define __CFTAL_X86_V2S32_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/v2s32.h>
#include <cftal/x86/v2u32.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/ops_1.h>
#include <cftal/divisor.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a) {
                full_type all_set(0xffffffff);
                return _mm_xor_si128(a(), all_set());
            }
        };


        template <>
        struct lt<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
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
        struct le<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
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
                mask_type b_gt_a(lt<int32_t, 2>::v(b(), a()));
                const mask_type all_set(uint32_t(-1));
                return _mm_xor_si128(b_gt_a(), all_set());
#endif
#endif
            }
        };

        template <>
        struct eq<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
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
        struct ne<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm_cmp_epi32_mask(a(), b(), _CMP_UNORD_Q & 7);
#else
                mask_type a_eq_b(eq<int32_t, 2>::v(a, b));
                return bit_not<int32_t, 2>::v(a_eq_b);
#endif
            }
        };

        template <>
        struct ge<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
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
                mask_type a_lt_b( lt<int32_t, 2>::v(a(), b()));
                return bit_not<int32_t, 2>::v(a_lt_b);
#endif
#endif
            }
        };

        template <>
        struct gt<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
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
        struct plus<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a) {
#if defined (__SSSE3__)
                const full_type sgn(sign_s32_msk::v._s32);
                return _mm_sign_epi32(a(), sgn());
#else
                const full_type zero(0);
                return _mm_sub_epi32(zero(), a());
#endif
            }
        };

        template <>
        struct add<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_add_epi32(a(), b());
            }
        };

        template <>
        struct sub<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_sub_epi32(a(), b());
            }
        };

        template <>
        struct mul<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::impl::vpmulld::v(a(), b());
            }
        };

        template <>
        struct div<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_s32::v(a(), b());
            }
        };

        template <>
        struct mod<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v2s32 q(a/b);
                v2s32 r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<int32_t, 2>::v(
                    mul<int32_t, 2>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<int32_t, 2>::v(
                    mul<int32_t, 2>::v(a , b), c);
            }
        };

        template <>
        struct fnma<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<int32_t, 2>::v(
                    c, mul<int32_t, 2>::v(a, b));

            }
        };

        template <>
        struct bit_or<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_or_si128(a(), b());
            }
        };

        template <>
        struct bit_and<int32_t, 2> {
            using full_type = vec<int32_t, 2>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_and_si128(a(), b());
            }
        };

        template <>
        struct bit_xor<int32_t, 2> {
            using full_type = vec<int32_t, 2>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_xor_si128(a(), b());
            }
        };

        template <>
        struct shl<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_slli_epi32(a(), s);
            }
        };

        template <>
        struct shr<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_srai_epi32(a(), s);
            }
        };

    }
}

inline
cftal::vec<cftal::int32_t, 2>::vec(__m128i v)
    : base_type(_mm_cvtsi128_si64(v))
{
}

inline
cftal::vec<cftal::int32_t, 2>::vec(const vec<uint32_t, 2>& v)
    : base_type(v)
{
}

inline
__m128i
cftal::vec<cftal::int32_t, 2>::operator()() const
{
    uint64_t v=base_type::operator()();
    return _mm_cvtsi64_si128(v);
}

inline
cftal::vec<cftal::int32_t, 2>::vec(int32_t v)
    : base_type((uint64_t(v)<<32) | uint32_t(v))
{
}

inline
cftal::vec<cftal::int32_t, 2>::vec(vec<int32_t, 1> l, vec<int32_t, 1> h)
    : base_type((uint64_t(h())<<32) | uint32_t(l()))
{
}

inline
cftal::vec<cftal::int32_t, 2>::
vec(std::initializer_list<int32_t> l)
    : vec(mem<v2s32>::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::int32_t, 2>::
vec(init_list<int32_t> l)
    : vec(mem<v2s32>::load(l.begin(), l.size()))
{
}

template <template <class _U, std::size_t _M> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::int32_t, 2>::vec(const expr<_OP<int32_t, 2>, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::int32_t, 2>
cftal::mem<cftal::vec<int32_t, 2> >::load(const int32_t* p, std::size_t s)
{
    __m128i v;
    switch (s) {
    default:
    case 2:
        v = _mm_setr_epi32(p[0], p[1], 0, 0);
        break;
    case 1:
        v = _mm_setr_epi32(p[0], p[0], 0, 0);
        break;
    case 0:
        v = _mm_setr_epi32(0, 0, 0, 0);
        break;
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<int32_t, 2> >::store(int32_t* p,
                                           const vec<int32_t, 2>& v)
{
    uint64_t r= v.base_type::operator()();
    uint64_t* d=reinterpret_cast<uint64_t*>(p);
    *d = r;
}

inline
cftal::vec<int32_t, 1>
cftal::low_half(const vec<int32_t, 2>& v)
{
    return as<vec<int32_t, 1> >(v);
}

inline
cftal::vec<int32_t, 1>
cftal::high_half(const vec<int32_t, 2>& v)
{
    vec<int32_t, 2> h= permute<1, 0>(v);
    return as<vec<int32_t, 1> >(h);
}

#if !defined (__AVX512VL__)
inline
bool cftal::all_of(const vec<int32_t, 2>::mask_type& v)
{
    return x86::all_of_s32(v());
}

inline
bool cftal::any_of(const vec<int32_t, 2>::mask_type& v)
{
    return x86::any_of_s32(v());
}

inline
bool cftal::none_of(const vec<int32_t, 2>::mask_type& v)
{
    return x86::none_of_s32(v());
}
#endif

inline
cftal::v2s32 cftal::max(const v2s32& a, const v2s32& b)
{
#if defined (__SSE4_1__)
    return _mm_max_epi32(a(), b());
#else
    v2s32 _gt(a > b);
    return select(_gt, a, b);
#endif
}

inline
cftal::v2s32 cftal::min(const v2s32& a, const v2s32& b)
{
#if defined (__SSE4_1__)
    return _mm_min_epi32(a(), b());
#else
    v2s32 _lt(a < b);
    return select(_lt, a, b);
#endif
}

inline
cftal::v2s32 cftal::select(const v2s32::mask_type& m,
                           const v2s32& on_true,
                           const v2s32& on_false)
{
    return x86::select_u32(m(), on_true(), on_false());
}

template <bool _I0, bool _I1>
inline
cftal::v2s32 cftal::select(const v2s32& a, const v2s32& b)
{
    return x86::select_u32<_I0, _I1, true, true>(a(), b());
}

template <int _I0, int _I1>
inline
cftal::v2s32 cftal::permute(const v2s32& a)
{
    return x86::perm_v4u32<_I0, _I1, 2, 3>(a());
}

template <int _I0, int _I1>
inline
cftal::v2s32 cftal::permute(const v2s32& a, const v2s32& b)
{
    __m128i lh= x86::impl::vpunpcklqdq::v(a(), b());
    return x86::perm_v4u32<_I0, _I1, 2, 3>(lh);
}

inline
std::pair<cftal::v2s32, cftal::v2s32>
cftal::mul_lo_hi(const v2s32& x, const v2s32& y)
{
#if defined (__SSE4_1__)
    __m128i tx= x86::impl::vpshufd<0, 0, 1, 1>::v(x());
    __m128i ty= x86::impl::vpshufd<0, 0, 1, 1>::v(y());
    // p0l p0h p1l p1h
    __m128i eo= _mm_mul_epi32(tx, ty);
    __m128i l= x86::impl::vpshufd<0, 2, 1, 3>::v(eo);
    __m128i h= x86::impl::vpshufd<1, 3, 0, 2>::v(eo);
    v2s32 rh = l;
    v2s32 rl = h;
    return std::make_pair(rl, rh);
#else
    // muluh(x,y) = mulsh(x,y) + and(x, xsign(y)) + and(y, xsign(x));
    // mulsh(x,y) = muluh(x,y) - and(x, xsign(y)) - and(y, xsign(x));
    std::pair<v2u32, v2u32> ur(mul_lo_hi(v2u32(x), v2u32(y)));
    v2s32 xsgn_y= y >> 31; // x86::const_shift::_31;
    v2s32 xsgn_x= x >> 31; // x86::const_shift::_31;
    v2s32 x_and_xsgn_y = x & xsgn_y;
    v2s32 y_and_xsgn_x = y & xsgn_x;
    v2s32 sh = v2s32(ur.second) - x_and_xsgn_y - y_and_xsgn_x;
    v2s32 sl = v2s32(ur.first);
    return std::make_pair(sl, sh);
#endif
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2S32_INL__
