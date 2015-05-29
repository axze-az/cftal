#if !defined (__CFTAL_X86_V8S32_INL__)
#define __CFTAL_X86_V8S32_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86_v8s32.h>
#include <cftal/x86_v8u32.h>
#include <cftal/x86_perm.h>
#include <cftal/x86_ops_1.h>
#include <cftal/divisor.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<int32_t, 8> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a) {
                full_type all_set(0xffffffff);
                return _mm256_xor_si256(a(), all_set());
            }
        };


        template <>
        struct lt<int32_t, 8> {
            using full_type = vec<int32_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm256_cmpgt_epi32(b(), a());
            }
        };

        template <>
        struct le<int32_t, 8> {
            using full_type = vec<int32_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__SSE4_1__)
                // a <= b: a == min(a, b);
                __m256i min_ab = _mm256_min_epi32(b(), a());
                return _mm256_cmpeq_epi32(a(), min_ab);
#else
                mask_type b_gt_a(lt<int32_t, 8>::v(b(), a()));
                const mask_type all_set(uint32_t(-1));
                return _mm256_xor_si128(b_gt_a(), all_set());
#endif
            }
        };

        template <>
        struct eq<int32_t, 8> {
            using full_type = vec<int32_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm256_cmpeq_epi32(a(), b());
            }
        };

        template <>
        struct ne<int32_t, 8> {
            using full_type = vec<int32_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                mask_type a_eq_b(eq<int32_t, 8>::v(a, b));
                return bit_not<int32_t, 8>::v(a_eq_b);
            }
        };

        template <>
        struct ge<int32_t, 8> {
            using full_type = vec<int32_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__SSE4_1__)
                // a >= b: a == max(a, b);
                __m256i max_ab = _mm256_max_epi32(b(), a());
                return _mm256_cmpeq_epi32(a(), max_ab);
#else
                mask_type a_lt_b( lt<int32_t, 8>::v(a(), b()));
                return bit_not<int32_t, 8>::v(a_lt_b);
#endif
            }
        };

        template <>
        struct gt<int32_t, 8> {
            using full_type = vec<int32_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm256_cmpgt_epi32(a(), b());
            }
        };

        template <>
        struct plus<int32_t, 8> {
            using full_type = vec<int32_t, 8>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<int32_t, 8> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a) {
#if defined (__SSSE3__)
                const full_type sgn(sign_s32_msk::v._s32);
                return _mm256_sign_epi32(a(), sgn());
#else
                const full_type zero(0);
                return _mm256_sub_epi32(zero(), a());
#endif
            }
        };

        template <>
        struct add<int32_t, 8> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_add_epi32(a(), b());
            }
        };

        template <>
        struct sub<int32_t, 8> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_sub_epi32(a(), b());
            }
        };

        template <>
        struct mul<int32_t, 8> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::impl::vpmulld::v(a(), b());
            }
        };

        template <>
        struct div<int32_t, 8> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_s32::v(a(), b());
            }
        };

        template <>
        struct mod<int32_t, 8> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v8s32 q(a/b);
                v8s32 r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<int32_t, 8> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<int32_t, 8>::v(
                    mul<int32_t, 8>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<int32_t, 8> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<int32_t, 8>::v(
                    mul<int32_t, 8>::v(a , b), c);
            }
        };

        template <>
        struct fnma<int32_t, 8> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<int32_t, 8>::v(
                    c, mul<int32_t, 8>::v(a, b));

            }
        };

        template <>
        struct bit_or<int32_t, 8> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_or_si256(a(), b());
            }
        };

        template <>
        struct bit_and<int32_t, 8> {
            using full_type = vec<int32_t, 8>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_and_si256(a(), b());
            }
        };

        template <>
        struct bit_xor<int32_t, 8> {
            using full_type = vec<int32_t, 8>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_xor_si256(a(), b());
            }
        };

        template <>
        struct shl<int32_t, 8> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm256_slli_epi32(a(), s);
            }
        };

        template <>
        struct shr<int32_t, 8> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm256_srai_epi32(a(), s);
            }
        };

    }

}

inline
cftal::vec<cftal::int32_t, 8>::vec(const vec<uint32_t, 8>& v)
    : base_type(v())
{
}

inline
cftal::vec<cftal::int32_t, 8>::vec(int32_t v)
    : base_type(_mm256_setr_epi32(v, v, v, v, v, v, v, v))
{
}

inline
cftal::vec<cftal::int32_t, 8>::vec(const vec<int32_t, 4>& l,
                                   const vec<int32_t, 4>& h)
    : base_type(_mm256_inserti128_si256(
                    _mm256_castsi128_si256(l()), h(), 1))
{
}


inline
cftal::vec<cftal::int32_t, 8>::
vec(std::initializer_list<int32_t> l)
    : vec(mem<v8s32>::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::int32_t, 8>::
vec(init_list<int32_t> l)
    : vec(mem<v8s32>::load(l.begin(), l.size()))
{
}

template <template <class _U, std::size_t _M> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::int32_t, 8>::vec(const expr<_OP<int32_t, 8>, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::int32_t, 8>
cftal::mem<cftal::vec<int32_t, 8> >::load(const int32_t* p, std::size_t s)
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
cftal::mem<cftal::vec<int32_t, 8> >::store(int32_t* p,
                                           const vec<int32_t, 8>& v)
{
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(p), v());
}

inline
cftal::vec<int32_t, 4>
cftal::low_half(const cftal::vec<int32_t, 8>& v)
{
    return _mm256_castsi256_si128(v());
}

inline
cftal::vec<int32_t, 4>
cftal::high_half(const cftal::vec<int32_t, 8>& v)
{
    return _mm256_extracti128_si256(v(), 1);
}

inline
bool cftal::all_of(const vec<int32_t, 8>::mask_type& v)
{
    return x86::all_of_s32(v());
}

inline
bool cftal::any_of(const vec<int32_t, 8>::mask_type& v)
{
    return x86::any_of_s32(v());
}

inline
bool cftal::none_of(const vec<int32_t, 8>::mask_type& v)
{
    return x86::none_of_s32(v());
}

inline
cftal::v8s32 cftal::max(const v8s32& a, const v8s32& b)
{
    return _mm256_max_epi32(a(), b());
}

inline
cftal::v8s32 cftal::min(const v8s32& a, const v8s32& b)
{
    return _mm256_min_epi32(a(), b());
}

inline
cftal::v8s32 cftal::select(const v8s32::mask_type& m,
                           const v8s32& on_true,
                           const v8s32& on_false)
{
    return x86::select(m(), on_true(), on_false());
}

template <bool _P0, bool _P1, bool _P2, bool _P3,
          bool _P4, bool _P5, bool _P6, bool _P7>
inline
cftal::v8s32 cftal::select(const v8s32& a, const v8s32& b)
{
    return x86::select_u32<_P0, _P1, _P2, _P3,
                           _P4, _P5, _P6, _P7> (a(), b());
}

template <int _I0, int _I1, int _I2, int _I3,
          int _I4, int _I5, int _I6, int _I7>
inline
cftal::v8s32 cftal::permute(const v8s32& a)
{
    return x86::perm_u32<_I0, _I1, _I2, _I3, _I4, _I5, _I6, _I7>(a());
}

template <int _I0, int _I1, int _I2, int _I3,
          int _I4, int _I5, int _I6, int _I7>
inline
cftal::v8s32 cftal::permute(const v8s32& a, const v8s32& b)
{
    return x86::perm_u32<_I0, _I1, _I2, _I3, _I4, _I5, _I6, _I7>(a(), b());
}

inline
std::pair<cftal::v8s32, cftal::v8s32>
cftal::mul_lo_hi(const v8s32& x, const v8s32& y)
{
#if 0    
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
#endif
    // p0l p0h p2l p2h p4l p4h p6l p6h
    v8s32 e= _mm256_mul_epi32(x(), y());
    // p1l p1h p3l p3h p5l p5h p7l p7h
    v8s32 o= _mm256_mul_epi32(
        x86::impl::vpshufd<1, 0, 3, 2>::v(x()),
        x86::impl::vpshufd<1, 0, 3, 2>::v(y()));
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
#endif // __CFTAL_X86_V8S32_INL__
