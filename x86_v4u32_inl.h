#if !defined (__CFTAL_X86_V4U32_INL__)
#define __CFTAL_X86_V4U32_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86_v4u32.h>
#include <cftal/x86_v4s32.h>
#include <cftal/x86_perm.h>
#include <cftal/x86_ops_1.h>
 
namespace cftal {

    namespace op {

        template <>
        struct bit_not<uint32_t, 4> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a) {
                full_type all_set(0xffffffff);
                return _mm_xor_si128(a(), all_set());
            }
        };

        
        template <>
        struct lt<uint32_t, 4> {
            using full_type = vec<uint32_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                v4u32 ta(a ^ full_type(x86::v_sign_s32_msk::iv()));
                v4u32 tb(b ^ full_type(x86::v_sign_s32_msk::iv()));
                return _mm_cmpgt_epi32(tb(), ta());
            }
        };

        template <>
        struct le<uint32_t, 4> {
            using full_type = vec<uint32_t, 4>;
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
        struct eq<uint32_t, 4> {
            using full_type = vec<uint32_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm_cmpeq_epi32(a(), b());
            }
        };

        template <>
        struct ne<uint32_t, 4> {
            using full_type = vec<uint32_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                mask_type a_eq_b(eq<uint32_t, 4>::v(a, b));
                return bit_not<uint32_t, 4>::v(a_eq_b);
            }
        };

        template <>
        struct ge<uint32_t, 4> {
            using full_type = vec<uint32_t, 4>;
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
        struct gt<uint32_t, 4> {
            using full_type = vec<uint32_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                v4u32 ta(a ^ full_type(x86::v_sign_s32_msk::iv()));
                v4u32 tb(b ^ full_type(x86::v_sign_s32_msk::iv()));
                return _mm_cmpgt_epi32(ta(), tb());
            }
        };

        template <>
        struct plus<uint32_t, 4> {
            using full_type = vec<uint32_t, 4>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<uint32_t, 4> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a) {
#if defined (__SSSE3__)
                const full_type sgn(0x80000000);
                return _mm_sign_epi32(a(), sgn());
#else
                const full_type zero(0);
                return _mm_sub_epi32(zero(), a());
#endif
            }
        };

        template <>
        struct add<uint32_t, 4> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_add_epi32(a(), b());
            }
        };

        template <>
        struct sub<uint32_t, 4> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_sub_epi32(a(), b());
            }
        };

        template <>
        struct mul<uint32_t, 4> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::impl::vpmulld::v(a(), b());
            }
        };

        template <>
        struct div<uint32_t, 4> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_u32::v(a(), b());
            }
        };

        template <>
        struct mod<uint32_t, 4> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v4u32 q(a/b);
                v4u32 r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<uint32_t, 4> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<uint32_t, 4>::v(
                    mul<uint32_t, 4>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<uint32_t, 4> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<uint32_t, 4>::v(
                    mul<uint32_t, 4>::v(a , b), c);
            }
        };

        template <>
        struct fnma<uint32_t, 4> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<uint32_t, 4>::v(
                    c, mul<uint32_t, 4>::v(a, b));
                                          
            }
        };
        
        template <>
        struct bit_or<uint32_t, 4> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_or_si128(a(), b());
            }
        };

        template <>
        struct bit_and<uint32_t, 4> {
            using full_type = vec<uint32_t, 4>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_and_si128(a(), b());
            }
        };

        template <>
        struct bit_xor<uint32_t, 4> {
            using full_type = vec<uint32_t, 4>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_xor_si128(a(), b());
            }
        };

        template <>
        struct shl<uint32_t, 4> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_slli_epi32(a(), s);
            }
        };

        template <>
        struct shr<uint32_t, 4> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_srli_epi32(a(), s);
            }
        };

    }

}

inline
cftal::vec<cftal::uint32_t, 4>::vec(const vec<int32_t,4>& v)
    : base_type(v())
{
}

inline
cftal::vec<cftal::uint32_t, 4>::vec(uint32_t v)
    : base_type(_mm_setr_epi32(v, v, v, v))
{
}


inline
cftal::vec<cftal::uint32_t, 4>::
vec(std::initializer_list<uint32_t> l)
    : vec(load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::uint32_t, 4>::
vec(init_list<uint32_t> l)
    : vec(load(l.begin(), l.size()))
{
}

template <template <class _U, std::size_t _M> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::uint32_t, 4>::vec(const expr<_OP<uint32_t, 4>, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::uint32_t, 4>
cftal::load(const uint32_t* p, std::size_t s)
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
cftal::store(uint32_t* p, const vec<int32_t, 4>& v)
{
    _mm_storeu_si128(reinterpret_cast<__m128i*>(p), v());
}

inline
cftal::v4u32 cftal::max(const v4u32& a, const v4u32& b)
{
#if defined (__SSE4_1__)
        return _mm_max_epu32(a(), b());
#else
        v4u32 _gt(a > b);
        return select(_gt, a, b);
#endif
}

inline
cftal::v4u32 cftal::min(const v4u32& a, const v4u32& b)
{
#if defined (__SSE4_1__)
        return _mm_min_epu32(a(), b());
#else
        v4u32 _lt(a < b);
        return select(_lt, a, b);
#endif
}

inline
cftal::v4u32 cftal::select(const v4u32::mask_type& m,
                           const v4u32& on_true,
                           const v4u32& on_false)
{
    return x86::select(m(), on_true(), on_false());
}


template <int _I0, int _I1, int _I2, int _I3>
inline
cftal::v4u32 cftal::permute(const v4u32& a)
{
    return x86::perm_u32<_I0, _I1, _I2, _I3>(a());
}

template <int _I0, int _I1, int _I2, int _I3>
inline
cftal::v4u32 cftal::permute(const v4u32& a, const v4u32& b)
{
    return x86::perm_u32<_I0, _I1, _I2, _I3>(a(), b());
}

inline
std::pair<cftal::v4u32, cftal::v4u32>
cftal::mul_lo_hi(const v4u32& x, const v4u32& y)
{
    // p0l p0h p2l p2h
    v4u32 e= _mm_mul_epu32(x(), y());
    // p1l p1h p3l p3h
    v4u32 o= _mm_mul_epu32(x86::impl::vpshufd<1, 0, 3, 2>::v(x()),
                           x86::impl::vpshufd<1, 0, 3, 2>::v(y()));
    // p0l p1l p0h p1h
    v4u32 t0= permute<0, 4, 1, 5>(e, o);
    // p2l p3l p2h p3h
    v4u32 t1= permute<2, 6, 3, 7>(e, o);
    // p0h p1h p2h p3h
    v4u32 h = permute<2, 3, 6, 7>(t0, t1);
    v4u32 l = permute<0, 1, 4, 5>(t0, t1);
    return std::make_pair(l, h);
}



// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V4U32_INL__
