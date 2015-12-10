#if !defined (__CFTAL_ARM_V2U32_INL__)
#define __CFTAL_ARM_V2U32_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/arm/v2u32.h>
#include <cftal/arm/v2s32.h>
#include <cftal/arm/perm.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a) {
                return vmvn_u32(a());
            }
        };


        template <>
        struct lt<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vclt_u32(a(), b());
            }
        };

        template <>
        struct le<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vcle_u32(a(), b());
            }
        };

        template <>
        struct eq<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vceq_u32(a(), b());
            }
        };

        template <>
        struct ne<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return ~(a==b);
            }
        };

        template <>
        struct ge<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vcge_u32(a(), b());
            }
        };

        template <>
        struct gt<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vcgt_u32(a(), b());
            }
        };

        template <>
        struct plus<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a) {
                static const full_type z{0, 0};
                return vsub_u32(z(), a());
            }
        };

        template <>
        struct add<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vadd_u32(a(), b());
            }
        };

        template <>
        struct sub<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vsub_u32(a(), b());
            }
        };

        template <>
        struct mul<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vmul_u32(a(), b());
            }
        };

        template <>
        struct div<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                // return x86::div_u32::lh(a(), b());
                return a;
            }
        };

        template <>
        struct mod<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v2u32 q(a/b);
                v2u32 r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<uint32_t, 2>::v(
                    mul<uint32_t, 2>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<uint32_t, 2>::v(
                    mul<uint32_t, 2>::v(a , b), c);
            }
        };

        template <>
        struct fnma<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<uint32_t, 2>::v(
                    c, mul<uint32_t, 2>::v(a, b));

            }
        };

        template <>
        struct bit_or<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vorr_u32(a(), b());
            }
        };

        template <>
        struct bit_and<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vand_u32(a(), b());
            }
        };

        template <>
        struct bit_xor<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return veor_u32(a(), b());
            }
        };

        template <>
        struct shl<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_slli_epi32(a(), s);
            }
        };

        template <>
        struct shr<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_srli_epi32(a(), s);
            }
        };

    }

}

inline
cftal::vec<cftal::uint32_t, 2>::vec(__m128i v)
    : base_type(x86::impl::pack(v))
{
}

inline
cftal::vec<cftal::uint32_t, 2>::vec(const vec<int32_t,2>& v)
    : base_type(v)
{
}

inline
__m128i
cftal::vec<cftal::uint32_t, 2>::operator()() const
{
    x86::impl::u32_pair_type v=base_type::operator()();
    return x86::impl::unpack_v2u32(v);
}

inline
cftal::vec<cftal::uint32_t, 2>::vec(uint32_t v)
    : base_type(x86::impl::set(v))
{
}

inline
cftal::vec<cftal::uint32_t, 2>::vec(vec<uint32_t, 1> l, vec<uint32_t, 1> h)
    : base_type(x86::impl::set(l(), h()))
{
}

inline
cftal::vec<cftal::uint32_t, 2>::
vec(std::initializer_list<uint32_t> l)
    : vec(mem<vec<uint32_t, 2> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::uint32_t, 2>::
vec(init_list<uint32_t> l)
    : vec(mem<vec<uint32_t, 2> >::load(l.begin(), l.size()))
{
}

template <template <class _U, std::size_t _M> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::uint32_t, 2>::vec(const expr<_OP<uint32_t, 2>, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::uint32_t, 2>
cftal::mem<cftal::vec<uint32_t, 2> >::load(const uint32_t* p, std::size_t s)
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
cftal::mem<cftal::vec<uint32_t, 2> >::store(uint32_t* p,
                                            const vec<uint32_t, 2>& v)
{
    uint64_t r= v.base_type::operator()();
    uint64_t* d=reinterpret_cast<uint64_t*>(p);
    *d = r;
}

inline
cftal::vec<uint32_t, 1>
cftal::low_half(const vec<uint32_t, 2>& v)
{
    return as<vec<uint32_t, 1> >(v);
}

inline
cftal::vec<uint32_t, 1>
cftal::high_half(const vec<uint32_t, 2>& v)
{
    vec<uint32_t, 2> h= permute<1, 0>(v);
    return as<vec<uint32_t, 1> >(h);
}

#if !defined (__AVX512VL__)
inline
bool
cftal::any_of(const vec<float, 2>::mask_type& s)
{
    return arm::compress_mask_u32(s()) != 0;
}

inline
bool
cftal::all_of(const vec<float, 2>::mask_type& s)
{
    return arm::compress_mask_u32(s()) == 0x3;
}

inline
bool
cftal::none_of(const vec<float, 2>::mask_type& s)
{
    return arm::compress_mask_u32(s()) == 0;
}
#endif


inline
cftal::v2u32 cftal::max(const v2u32& a, const v2u32& b)
{
#if defined (__SSE4_1__)
        return _mm_max_epu32(a(), b());
#else
        v2u32 _gt(a > b);
        return select(_gt, a, b);
#endif
}

inline
cftal::v2u32 cftal::min(const v2u32& a, const v2u32& b)
{
#if defined (__SSE4_1__)
        return _mm_min_epu32(a(), b());
#else
        v2u32 _lt(a < b);
        return select(_lt, a, b);
#endif
}

inline
cftal::v2u32 cftal::select(const v2u32::mask_type& m,
                           const v2u32& on_true,
                           const v2u32& on_false)
{
    return x86::select_u32(m(), on_true(), on_false());
}

template <bool _I0, bool _I1>
inline
cftal::v2u32 cftal::select(const v2u32& a, const v2u32& b)
{
    return x86::select_u32<_I0, _I1, true, true>(a(), b());
}

template <int _I0, int _I1>
inline
cftal::v2u32 cftal::permute(const v2u32& a)
{
    return x86::perm_v4u32<_I0, _I1, 2, 3>(a());
}

template <int _I0, int _I1>
inline
cftal::v2u32 cftal::permute(const v2u32& a, const v2u32& b)
{
    __m128i lh= x86::impl::vpunpcklqdq::v(a(), b());
    return x86::perm_v4u32<_I0, _I1, 2, 3>(lh);
}

inline
std::pair<cftal::v2u32, cftal::v2u32>
cftal::mul_lo_hi(const v2u32& x, const v2u32& y)
{
    __m128i tx= x86::impl::vpshufd<0, 0, 1, 1>::v(x());
    __m128i ty= x86::impl::vpshufd<0, 0, 1, 1>::v(y());
    // p0l p0h p1l p1h
    __m128i eo= _mm_mul_epu32(tx, ty);
    __m128i l= x86::impl::vpshufd<0, 2, 1, 3>::v(eo);
    __m128i h= x86::impl::vpshufd<1, 3, 0, 2>::v(eo);
    v2u32 rl = l;
    v2u32 rh = h;
    return std::make_pair(rl, rh);
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2U32_INL__
