#if !defined (__CFTAL_X86_V2S64_INL__)
#define __CFTAL_X86_V2S64_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86_v2s64.h>
#include <cftal/x86_v2u64.h>
#include <cftal/x86_perm.h>
#include <cftal/x86_ops_1.h>
#include <cftal/divisor.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<int64_t, 2> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a) {
                full_type all_set(0xffffffff);
                return _mm_xor_si128(a(), all_set());
            }
        };

        
        template <>
        struct lt<int64_t, 2> {
            using full_type = vec<int64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm_cmpgt_epi32(b(), a());
            }
        };

        template <>
        struct le<int64_t, 2> {
            using full_type = vec<int64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__SSE4_1__)
                // a <= b: a == min(a, b);
                __m128i min_ab = _mm_min_epi32(b(), a());
                return _mm_cmpeq_epi32(a(), min_ab);
#else
                mask_type b_gt_a(lt<int64_t, 2>::v(b(), a()));
                const mask_type all_set(uint64_t(-1));
                return _mm_xor_si128(b_gt_a(), all_set());
#endif
            }
        };

        template <>
        struct eq<int64_t, 2> {
            using full_type = vec<int64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm_cmpeq_epi32(a(), b());
            }
        };

        template <>
        struct ne<int64_t, 2> {
            using full_type = vec<int64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                mask_type a_eq_b(eq<int64_t, 2>::v(a, b));
                return bit_not<int64_t, 2>::v(a_eq_b);
            }
        };

        template <>
        struct ge<int64_t, 2> {
            using full_type = vec<int64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__SSE4_1__)
                // a >= b: a == max(a, b);
                __m128i max_ab = _mm_max_epi32(b(), a());
                return _mm_cmpeq_epi32(a(), max_ab);
#else
                mask_type a_lt_b( lt<int64_t, 2>::v(a(), b()));
                return bit_not<int64_t, 2>::v(a_lt_b);
#endif
            }
        };

        template <>
        struct gt<int64_t, 2> {
            using full_type = vec<int64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm_cmpgt_epi32(a(), b());
            }
        };

        template <>
        struct plus<int64_t, 2> {
            using full_type = vec<int64_t, 2>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<int64_t, 2> {
            using full_type = vec<int64_t, 2>;
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
        struct add<int64_t, 2> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_add_epi32(a(), b());
            }
        };

        template <>
        struct sub<int64_t, 2> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_sub_epi32(a(), b());
            }
        };

        template <>
        struct mul<int64_t, 2> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::impl::vpmulld::v(a(), b());
            }
        };

        template <>
        struct div<int64_t, 2> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_s32::v(a(), b());
            }
        };

        template <>
        struct mod<int64_t, 2> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v2s64 q(a/b);
                v2s64 r(remainder(a, b, q));
                return r;                
            }
        };

        template <>
        struct fma<int64_t, 2> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<int64_t, 2>::v(
                    mul<int64_t, 2>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<int64_t, 2> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<int64_t, 2>::v(
                    mul<int64_t, 2>::v(a , b), c);
            }
        };

        template <>
        struct fnma<int64_t, 2> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<int64_t, 2>::v(
                    c, mul<int64_t, 2>::v(a, b));
                                          
            }
        };
        
        template <>
        struct bit_or<int64_t, 2> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_or_si128(a(), b());
            }
        };

        template <>
        struct bit_and<int64_t, 2> {
            using full_type = vec<int64_t, 2>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_and_si128(a(), b());
            }
        };

        template <>
        struct bit_xor<int64_t, 2> {
            using full_type = vec<int64_t, 2>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_xor_si128(a(), b());
            }
        };

        template <>
        struct shl<int64_t, 2> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_slli_epi32(a(), s);
            }
        };

        template <>
        struct shr<int64_t, 2> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_srai_epi32(a(), s);
            }
        };

    }

}

inline
cftal::vec<cftal::int64_t, 2>::vec(const vec<uint64_t, 2>& v)
    : base_type(v())
{
}

inline
cftal::vec<cftal::int64_t, 2>::vec(int64_t v)
    : base_type(_mm_setr_epi32(v, v, v, v))
{
}


inline
cftal::vec<cftal::int64_t, 2>::
vec(std::initializer_list<int64_t> l)
    : vec(mem<v2s64>::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::int64_t, 2>::
vec(init_list<int64_t> l)
    : vec(mem<v2s64>::load(l.begin(), l.size()))
{
}

template <template <class _U, std::size_t _M> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::int64_t, 2>::vec(const expr<_OP<int64_t, 2>, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::int64_t, 2>
cftal::mem<cftal::vec<int64_t, 2> >::load(const int64_t* p, std::size_t s)
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
cftal::mem<cftal::vec<int64_t, 2> >::store(int64_t* p,
                                           const vec<int64_t, 2>& v)
{
    _mm_storeu_si128(reinterpret_cast<__m128i*>(p), v());
}

inline
cftal::v2s64 cftal::max(const v2s64& a, const v2s64& b)
{
#if defined (__SSE4_1__)
        return _mm_max_epi32(a(), b());
#else
        v2s64 _gt(a > b);
        return select(_gt, a, b);
#endif
}

inline
cftal::v2s64 cftal::min(const v2s64& a, const v2s64& b)
{
#if defined (__SSE4_1__)
        return _mm_min_epi32(a(), b());
#else
        v2s64 _lt(a < b);
        return select(_lt, a, b);
#endif
}

inline
cftal::v2s64 cftal::select(const v2s64::mask_type& m,
                           const v2s64& on_true,
                           const v2s64& on_false)
{
    return x86::select(m(), on_true(), on_false());
}


template <int _I0, int _I1, int _I2, int _I3>
inline
cftal::v2s64 cftal::permute(const v2s64& a)
{
    return x86::perm_u32<_I0, _I1, _I2, _I3>(a());
}

template <int _I0, int _I1, int _I2, int _I3>
inline
cftal::v2s64 cftal::permute(const v2s64& a, const v2s64& b)
{
    return x86::perm_u32<_I0, _I1, _I2, _I3>(a(), b());
}


inline
std::pair<cftal::v2s64, cftal::v2s64>
cftal::mul_lo_hi(const v2s64& x, const v2s64& y)
{
#if defined (__SSE4_1__) 
        // p0l p0h p2l p2h
        v2s64 e= _mm_mul_epi32(x(), y());
        // p1l p1h p3l p3h
        v2s64 o= _mm_mul_epi32(x86::impl::vpshufd<1, 0, 3, 2>::v(x()),
                               x86::impl::vpshufd<1, 0, 3, 2>::v(y()));
        // p0l p1l p0h p1h
        v2s64 t0= permute<0, 2, 1, 5>(e, o);
        // p2l p3l p2h p3h
        v2s64 t1= permute<2, 6, 3, 7>(e, o);
        // p0h p1h p2h p3h
        v2s64 h = permute<2, 3, 6, 7>(t0, t1);
        v2s64 l = permute<0, 1, 2, 5>(t0, t1);
        return std::make_pair(l, h);
#else
        // muluh(x,y) = mulsh(x,y) + and(x, xsign(y)) + and(y, xsign(x));
        // mulsh(x,y) = muluh(x,y) - and(x, xsign(y)) - and(y, xsign(x));
        std::pair<v4u32, v4u32> ur(mul_lo_hi(v4u32(x), v4u32(y)));
        v2s64 xsgn_y= y >> 31; // x86::const_shift::_31;
        v2s64 xsgn_x= x >> 31; // x86::const_shift::_31;
        v2s64 x_and_xsgn_y = x & xsgn_y;
        v2s64 y_and_xsgn_x = y & xsgn_x;
        v2s64 sh = v2s64(ur.second) - x_and_xsgn_y - y_and_xsgn_x;
        v2s64 sl = v2s64(ur.first);
        return std::make_pair(sl, sh);
#endif
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2S64_INL__
