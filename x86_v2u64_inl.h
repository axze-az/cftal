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
                v2u64 ta(a ^ full_type(sign_s32_msk::v._u32));
                v2u64 tb(b ^ full_type(sign_s32_msk::v._u32));
                return _mm_cmpgt_epi32(tb(), ta());
            }
        };

        template <>
        struct le<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__SSE4_1__)
                // a<= b: a == min(a, b);
                __m128i min_ab = _mm_min_epu32(b(), a());
                return _mm_cmpeq_epi16(a(), min_ab);
#else
                return ~(b > a);
#endif
            }
        };

        template <>
        struct eq<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm_cmpeq_epi32(a(), b());
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
#if defined (__SSE4_1__)
                // a>= b: a == max(a, b);
                __m128i max_ab = _mm_max_epu32(b(), a());
                return _mm_cmpeq_epi32(a(), max_ab);
#else
                return ~(a < b);
#endif
            }
        };

        template <>
        struct gt<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                v2u64 ta(a ^ full_type(sign_s32_msk::v._u32));
                v2u64 tb(b ^ full_type(sign_s32_msk::v._u32));
                return _mm_cmpgt_epi32(ta(), tb());
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
#if defined (__SSSE3__)
                const full_type sgn(sign_s32_msk::v._u32);
                return _mm_sign_epi32(a(), sgn());
#else
                const full_type zero(0);
                return _mm_sub_epi32(zero(), a());
#endif
            }
        };

        template <>
        struct add<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_add_epi32(a(), b());
            }
        };

        template <>
        struct sub<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_sub_epi32(a(), b());
            }
        };

        template <>
        struct mul<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::impl::vpmulld::v(a(), b());
            }
        };

        template <>
        struct div<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_u32::v(a(), b());
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
                return _mm_slli_epi32(a(), s);
            }
        };

        template <>
        struct shr<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_srli_epi32(a(), s);
            }
        };

    }

}

inline
cftal::vec<cftal::uint64_t, 2>::vec(const vec<int64_t,4>& v)
    : base_type(v())
{
}

inline
cftal::vec<cftal::uint64_t, 2>::vec(uint64_t v)
    : base_type(_mm_setr_epi32(v, v, v, v))
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
cftal::mem<cftal::vec<uint64_t, 2> >::store(uint64_t* p,
                                            const vec<uint64_t, 2>& v)
{
    _mm_storeu_si128(reinterpret_cast<__m128i*>(p), v());
}

inline
cftal::v2u64 cftal::max(const v2u64& a, const v2u64& b)
{
#if defined (__SSE4_1__)
        return _mm_max_epu32(a(), b());
#else
        v2u64 _gt(a > b);
        return select(_gt, a, b);
#endif
}

inline
cftal::v2u64 cftal::min(const v2u64& a, const v2u64& b)
{
#if defined (__SSE4_1__)
        return _mm_min_epu32(a(), b());
#else
        v2u64 _lt(a < b);
        return select(_lt, a, b);
#endif
}

inline
cftal::v2u64 cftal::select(const v2u64::mask_type& m,
                           const v2u64& on_true,
                           const v2u64& on_false)
{
    return x86::select(m(), on_true(), on_false());
}


template <int _I0, int _I1, int _I2, int _I3>
inline
cftal::v2u64 cftal::permute(const v2u64& a)
{
    return x86::perm_u32<_I0, _I1, _I2, _I3>(a());
}

template <int _I0, int _I1, int _I2, int _I3>
inline
cftal::v2u64 cftal::permute(const v2u64& a, const v2u64& b)
{
    return x86::perm_u32<_I0, _I1, _I2, _I3>(a(), b());
}

inline
std::pair<cftal::v2u64, cftal::v2u64>
cftal::mul_lo_hi(const v2u64& x, const v2u64& y)
{
    // p0l p0h p2l p2h
    v2u64 e= _mm_mul_epu32(x(), y());
    // p1l p1h p3l p3h
    v2u64 o= _mm_mul_epu32(x86::impl::vpshufd<1, 0, 3, 2>::v(x()),
                           x86::impl::vpshufd<1, 0, 3, 2>::v(y()));
    // p0l p1l p0h p1h
    v2u64 t0= permute<0, 2, 1, 5>(e, o);
    // p2l p3l p2h p3h
    v2u64 t1= permute<2, 6, 3, 7>(e, o);
    // p0h p1h p2h p3h
    v2u64 h = permute<2, 3, 6, 7>(t0, t1);
    v2u64 l = permute<0, 1, 2, 5>(t0, t1);
    return std::make_pair(l, h);
}



// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2U64_INL__
