#if !defined (__CFTAL_X86_V2U64_INL__)
#define __CFTAL_X86_V2U64_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86_v2u64.h>
#include <cftal/x86_v2s64.h>
#include <cftal/x86_perm.h>
#include <cftal/x86_ops_1.h>
 
namespace cftal {

    namespace op {

        template <>
        struct bit_not<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a) {
                full_type all_set(0xffffffff);
                return _mm_xor_si128(a(), all_set());
            }
        };

        
        template <>
        struct lt<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return b > a;
            }
        };

        template <>
        struct le<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return ~(b > a);
            }
        };

        template <>
        struct eq<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__SSE4_1__)
                return _mm_cmpeq_epi64(a(), b());
#else
                // a == b : a_h == b_h && a_l == b_l
                __m128i r= _mm_cmpeq_epi32(a(), b());
                __m128i c32s = x86::impl::vpsllq_const<32>::v(r);
                r = _mm_and_si128(r, c32s);
                return x86::impl::vpshufd<1, 1, 3, 3>::v(r);
#endif
            }
        };

        template <>
        struct ne<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                mask_type a_eq_b(eq<uint64_t, 2>::v(a, b));
                return bit_not<uint64_t, 2>::v(a_eq_b);
            }
        };

        template <>
        struct ge<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return ~(a < b);
            }
        };

        template <>
        struct gt<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__SSE4_2__)
                const __m128i msk= _mm_set1_epi64x(sign_s64_msk::v._u64);
                __m128i ax= _mm_xor_si128(a(), msk);
                __m128i bx= _mm_xor_si128(b(), msk);
                return _mm_cmpgt_epi64(ax, bx);
#else
                // a > b: (a_h > b_h) || ((a_h == b_h) && (a_l > b_l))
                // c1 ---------^ 
                // c2 -------------------------^
                // c3 -----------------------------------------^
                const __m128i msk= _mm_set1_epi32(sign_s32_msk::v._u32);
                __m128i ax= _mm_xor_si128(a(), msk);
                __m128i bx= _mm_xor_si128(b(), msk);
                __m128i c2= _mm_cmpeq_epi32(a(), b());
                __m128i c1c3= _mm_cmpgt_epi32(ax, bx);
                // only elements 1, 3 are valid:
                __m128i c2_and_c3 =
                    _mm_and_si128(c2, 
                                  x86::impl::vpshufd<0, 0, 2, 2>::v(c1c3));
                // only elements 1, 3 are valid.
                __m128i r = _mm_or_si128(c1c3, c2_and_c3);
                r = x86::impl::vpshufd< 1, 1, 3, 3>::v(r);
                return r;
#endif

            }
        };

        template <>
        struct plus<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a) {
                const full_type zero(0);
                return _mm_sub_epi64(zero(), a());
            }
        };

        template <>
        struct add<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_add_epi64(a(), b());
            }
        };

        template <>
        struct sub<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_sub_epi64(a(), b());
            }
        };

        template <>
        struct mul<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::impl::vpmullq::v(a(), b());
            }
        };

        template <>
        struct div<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_u64::v(a(), b());
            }
        };

        template <>
        struct mod<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v2u64 q(a/b);
                v2u64 r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<uint64_t, 2>::v(
                    mul<uint64_t, 2>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<uint64_t, 2>::v(
                    mul<uint64_t, 2>::v(a , b), c);
            }
        };

        template <>
        struct fnma<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<uint64_t, 2>::v(
                    c, mul<uint64_t, 2>::v(a, b));
                                          
            }
        };
        
        template <>
        struct bit_or<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_or_si128(a(), b());
            }
        };

        template <>
        struct bit_and<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_and_si128(a(), b());
            }
        };

        template <>
        struct bit_xor<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_xor_si128(a(), b());
            }
        };

        template <>
        struct shl<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return x86::impl::vpsllq::v(a(), s);
            }
        };

        template <>
        struct shr<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return x86::impl::vpsrlq::v(a(), s);
            }
        };

    }

}

inline
cftal::vec<cftal::uint64_t, 2>::vec(const vec<int64_t, 2>& v)
    : base_type(v())
{
}

inline
cftal::vec<cftal::uint64_t, 2>::vec(uint64_t v)
    : base_type(_mm_set_epi64x(v, v))
{
}


inline
cftal::vec<cftal::uint64_t, 2>::
vec(std::initializer_list<uint64_t> l)
    : vec(mem<vec<uint64_t, 2> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::uint64_t, 2>::
vec(init_list<uint64_t> l)
    : vec(mem<vec<uint64_t, 2> >::load(l.begin(), l.size()))
{
}

template <template <class _U, std::size_t _M> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::uint64_t, 2>::vec(const expr<_OP<uint64_t, 2>, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::uint64_t, 2>
cftal::mem<cftal::vec<uint64_t, 2> >::load(const uint64_t* p, std::size_t s)
{
    __m128i v;
    switch (s) {
    default:
    case 4:
        v = _mm_loadu_si128(reinterpret_cast<const __m128i*>(p));
        break;
    case 1:
        v = _mm_set_epi64x(p[0], p[0]);
        break;
    case 0:
        v = _mm_set_epi64x(0, 0);
        break;
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<uint64_t, 2> >::store(uint64_t* p,
                                            const vec<uint64_t, 2>& v)
{
    _mm_storeu_si128(reinterpret_cast<__m128i*>(p), v());
}

inline
cftal::v2u64 cftal::max(const v2u64& a, const v2u64& b)
{
    v2u64 _gt(a > b);
    return select(_gt, a, b);
}

inline
cftal::v2u64 cftal::min(const v2u64& a, const v2u64& b)
{
    v2u64 _lt(a < b);
    return select(_lt, a, b);
}

inline
cftal::v2u64 cftal::select(const v2u64::mask_type& m,
                           const v2u64& on_true,
                           const v2u64& on_false)
{
    return x86::select(m(), on_true(), on_false());
}

template <bool _I0, bool _I1>
inline
cftal::v2u64 cftal::select(const v2u64& a, const v2u64& b)
{
    return x86::select_u64<_I0, _I1>(a(), b());
}

template <int _I0, int _I1>
inline
cftal::v2u64 cftal::permute(const v2u64& a)
{
    return x86::perm_u64<_I0, _I1>(a());
}

template <int _I0, int _I1>
inline
cftal::v2u64 cftal::permute(const v2u64& a, const v2u64& b)
{
    return x86::perm_u64<_I0, _I1>(a(), b());
}

inline
std::pair<cftal::v2u64, cftal::v2u64>
cftal::mul_lo_hi(const v2u64& x, const v2u64& y)
{
    //         0         0 (xl_yl)_h  (xl_yl)_l
    //         0 (xh_yl)_h (xh_yl)_l          0
    //         0 (xl_yh)_h (xl_yh)_l          0
    // (xh_yh)_h (xh_yh)_l 
    v2u64 xh = x >> 32;
    v2u64 yh = y >> 32;  
    // 2^ 0
    v2u64 xl_yl= _mm_mul_epu32(x(), y());
    // 2^ 32
    v2u64 xl_yh= _mm_mul_epu32(x(), yh());
    v2u64 xh_yl= _mm_mul_epu32(xh(), y());
    // 2^ 64
    v2u64 xh_yh= _mm_mul_epu32(xh(), yh());
    // sum of 2^32
    v2u64 s32_95 = xl_yh + xh_yl;
    v2u64 carry_96 = s32_95 < xl_yh;
    // 
    v2u64 s64_96 = s32_95 >> 32;
    v2u64 s32_63 = s32_95 << 32;
    // low part of the multiplication:
    xl_yl += s32_63;
    v2u64 neg_carry_64 = xl_yl < s32_63;
    v2u64 c96_msk(bytes8(0, 1)._u64);
    
    s64_96 |= carry_96 & c96_msk;
    xh_yh -= neg_carry_64;
    // high part of the multiplication:
    xh_yh += s64_96;
    return std::make_pair(xl_yl, xh_yh);
}



// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2U64_INL__
