#if !defined (__CFTAL_X86_V4U64_INL__)
#define __CFTAL_X86_V4U64_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86_v4u64.h>
#include <cftal/x86_v4s64.h>
#include <cftal/x86_perm.h>
#include <cftal/x86_ops_1.h>
 
namespace cftal {

    namespace op {

        template <>
        struct bit_not<uint64_t, 4> {
            using full_type = vec<uint64_t, 4>;
            static
            full_type
            v(const full_type& a) {
                full_type all_set(0xffffffff);
                return _mm256_xor_si256(a(), all_set());
            }
        };

        
        template <>
        struct lt<uint64_t, 4> {
            using full_type = vec<uint64_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmplt_epu64_mask(a(), b());
#else
                return b > a;
#endif
            }
        };

        template <>
        struct le<uint64_t, 4> {
            using full_type = vec<uint64_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmple_epu64_mask(a(), b());
#else
                return ~(b > a);
#endif
            }
        };

        template <>
        struct eq<uint64_t, 4> {
            using full_type = vec<uint64_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmpeq_epu64_mask(a(), b());
#else
                return _mm256_cmpeq_epi64(a(), b());
#endif
            }
        };

        template <>
        struct ne<uint64_t, 4> {
            using full_type = vec<uint64_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmpneq_epu64_mask(a(), b());
#else
                mask_type a_eq_b(eq<uint64_t, 4>::v(a, b));
                return bit_not<uint64_t, 4>::v(a_eq_b);
#endif
            }
        };

        template <>
        struct ge<uint64_t, 4> {
            using full_type = vec<uint64_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmpge_epu64_mask(a(), b());
#else
                return ~(a < b);
#endif
            }
        };

        template <>
        struct gt<uint64_t, 4> {
            using full_type = vec<uint64_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmpgt_epu64_mask(a(), b());
#else
                const __m256i msk= _mm256_set1_epi64x(sign_s64_msk::v._u64);
                __m256i ax= _mm256_xor_si256(a(), msk);
                __m256i bx= _mm256_xor_si256(b(), msk);
                return _mm256_cmpgt_epi64(ax, bx);
#endif
            }
        };

        template <>
        struct plus<uint64_t, 4> {
            using full_type = vec<uint64_t, 4>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<uint64_t, 4> {
            using full_type = vec<uint64_t, 4>;
            static
            full_type
            v(const full_type& a) {
                const full_type zero(0);
                return _mm256_sub_epi64(zero(), a());
            }
        };

        template <>
        struct add<uint64_t, 4> {
            using full_type = vec<uint64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_add_epi64(a(), b());
            }
        };

        template <>
        struct sub<uint64_t, 4> {
            using full_type = vec<uint64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_sub_epi64(a(), b());
            }
        };

        template <>
        struct mul<uint64_t, 4> {
            using full_type = vec<uint64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::impl::vpmullq::v(a(), b());
            }
        };

        template <>
        struct div<uint64_t, 4> {
            using full_type = vec<uint64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_u64::v(a(), b());
            }
        };

        template <>
        struct mod<uint64_t, 4> {
            using full_type = vec<uint64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v4u64 q(a/b);
                v4u64 r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<uint64_t, 4> {
            using full_type = vec<uint64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<uint64_t, 4>::v(
                    mul<uint64_t, 4>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<uint64_t, 4> {
            using full_type = vec<uint64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<uint64_t, 4>::v(
                    mul<uint64_t, 4>::v(a , b), c);
            }
        };

        template <>
        struct fnma<uint64_t, 4> {
            using full_type = vec<uint64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<uint64_t, 4>::v(
                    c, mul<uint64_t, 4>::v(a, b));
                                          
            }
        };
        
        template <>
        struct bit_or<uint64_t, 4> {
            using full_type = vec<uint64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_or_si256(a(), b());
            }
        };

        template <>
        struct bit_and<uint64_t, 4> {
            using full_type = vec<uint64_t, 4>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_and_si256(a(), b());
            }
        };

        template <>
        struct bit_xor<uint64_t, 4> {
            using full_type = vec<uint64_t, 4>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_xor_si256(a(), b());
            }
        };

        template <>
        struct shl<uint64_t, 4> {
            using full_type = vec<uint64_t, 4>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return x86::impl::vpsllq::v(a(), s);
            }
        };

        template <>
        struct shr<uint64_t, 4> {
            using full_type = vec<uint64_t, 4>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return x86::impl::vpsrlq::v(a(), s);
            }
        };

    }

}

inline
cftal::vec<cftal::uint64_t, 4>::vec(const vec<int64_t, 4>& v)
    : base_type(v())
{
}

inline
cftal::vec<cftal::uint64_t, 4>::vec(uint64_t v)
    : base_type(_mm256_set_epi64x(v, v, v, v))
{
}


inline
cftal::vec<cftal::uint64_t, 4>::
vec(std::initializer_list<uint64_t> l)
    : vec(mem<vec<uint64_t, 4> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::uint64_t, 4>::
vec(init_list<uint64_t> l)
    : vec(mem<vec<uint64_t, 4> >::load(l.begin(), l.size()))
{
}

template <template <class _U, std::size_t _M> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::uint64_t, 4>::vec(const expr<_OP<uint64_t, 4>, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::uint64_t, 4>
cftal::mem<cftal::vec<uint64_t, 4> >::load(const uint64_t* p, std::size_t s)
{
    __m256i v;
    switch (s) {
    default:
    case 4:
        v = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p));
        break;
    case 3:
        v = _mm256_setr_epi64x(p[0], p[1], p[2], p[2]);
        break;
    case 2:
        v = _mm256_setr_epi64x(p[0], p[1], p[1], p[1]);
        break;
    case 1:
        v = _mm256_setr_epi64x(p[0], p[0], p[0], p[0]);
        break;
    case 0:
        v = _mm256_set_epi64x(0, 0, 0,0 );
        break;
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<uint64_t, 4> >::store(uint64_t* p,
                                            const vec<uint64_t, 4>& v)
{
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(p), v());
}

inline
cftal::vec<uint64_t, 2>
cftal::low_half(const cftal::vec<uint64_t, 4>& v)
{
    return _mm256_castsi256_si128(v());
}

inline
cftal::vec<uint64_t, 2>
cftal::high_half(const cftal::vec<uint64_t, 4>& v)
{
    return _mm256_extracti128_si256(v(), 1);
}

#if !defined (__AVX512VL__)
inline
bool cftal::all_of(const vec<uint64_t, 4>::mask_type& v)
{
    return x86::all_of_s64(v());
}

inline
bool cftal::any_of(const vec<uint64_t, 4>::mask_type& v)
{
    return x86::any_of_s64(v());
}

inline
bool cftal::none_of(const vec<uint64_t, 4>::mask_type& v)
{
    return x86::none_of_s64(v());
}
#endif

inline
cftal::v4u64 cftal::max(const v4u64& a, const v4u64& b)
{
    v4u64::mask_type _gt(a > b);
    return select(_gt, a, b);
}

inline
cftal::v4u64 cftal::min(const v4u64& a, const v4u64& b)
{
    v4u64::mask_type _lt(a < b);
    return select(_lt, a, b);
}

inline
cftal::v4u64 cftal::select(const v4u64::mask_type& m,
                           const v4u64& on_true,
                           const v4u64& on_false)
{
#if defined (__AVX512VL__)
    return x86::select_u64(m(), on_true(), on_false());
#else
    return x86::select(m(), on_true(), on_false());
#endif
}

template <bool _I0, bool _I1, bool _I2, bool _I3>
inline
cftal::v4u64 cftal::select(const v4u64& a, const v4u64& b)
{
    return x86::select_u64<_I0, _I1, _I2, _I3>(a(), b());
}

template <int _I0, int _I1, int _I2, int _I3>
inline
cftal::v4u64 cftal::permute(const v4u64& a)
{
    return x86::perm_u64<_I0, _I1, _I2, _I3>(a());
}

template <int _I0, int _I1, int _I2, int _I3>
inline
cftal::v4u64 cftal::permute(const v4u64& a, const v4u64& b)
{
    return x86::perm_u64<_I0, _I1, _I2, _I3>(a(), b());
}

inline
std::pair<cftal::v4u64, cftal::v4u64>
cftal::mul_lo_hi(const v4u64& x, const v4u64& y)
{
    //         0         0 (xl_yl)_h  (xl_yl)_l
    //         0 (xh_yl)_h (xh_yl)_l          0
    //         0 (xl_yh)_h (xl_yh)_l          0
    // (xh_yh)_h (xh_yh)_l 
    v4u64 xh = x >> 32;
    v4u64 yh = y >> 32;  
    // 2^ 0
    v4u64 xl_yl= _mm256_mul_epu32(x(), y());
    // 2^ 32
    v4u64 xl_yh= _mm256_mul_epu32(x(), yh());
    v4u64 xh_yl= _mm256_mul_epu32(xh(), y());
    // 2^ 64
    v4u64 xh_yh= _mm256_mul_epu32(xh(), yh());
    // sum of 2^32
    v4u64 s32_95 = xl_yh + xh_yl;
    v4u64::mask_type carry_96 = s32_95 < xl_yh;
    // 
    v4u64 s64_96 = s32_95 >> 32;
    v4u64 s32_63 = s32_95 << 32;
    // low part of the multiplication:
    xl_yl += s32_63;
    v4u64::mask_type neg_carry_64 = xl_yl < s32_63;
    v4u64 c96_msk(bytes8(0, 1)._u64);
    
    s64_96 |= select(carry_96, c96_msk, v4u64(0));
    xh_yh -= select(neg_carry_64, v4u64(-1LL), v4u64(0));
    // high part of the multiplication:
    xh_yh += s64_96;
    return std::make_pair(xl_yl, xh_yh);
}



// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V4U64_INL__
