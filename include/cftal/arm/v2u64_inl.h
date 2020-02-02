//
// Copyright Axel Zeuner 2010-2020. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_ARM_V2U64_INL_H__)
#define __CFTAL_ARM_V2U64_INL_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/arm/v2u64.h>
#include <cftal/arm/v2s64.h>
#include <cftal/arm/perm.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a) {
                uint32x4_t t=vreinterpretq_u32_u64(a());
                return vreinterpretq_u64_u32(vmvnq_u32(t));
            }
        };


        template <>
        struct lt<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vcltq_u64(a(), b());
            }
        };

        template <>
        struct le<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vcleq_u64(a(), b());
            }
        };

        template <>
        struct eq<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vceqq_u64(a(), b());
            }
        };

        template <>
        struct ne<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return ~(a==b);
            }
        };

        template <>
        struct ge<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vcgeq_u64(a(), b());
            }
        };

        template <>
        struct gt<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vcgtq_u64(a(), b());
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
                static const full_type z{0, 0};
                return vsubq_u64(z(), a());
            }
        };

        template <>
        struct add<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vaddq_u64(a(), b());
            }
        };

        template <>
        struct sub<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vsubq_u64(a(), b());
            }
        };

        template <>
        struct mul<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                // return vmulq_u64(a(), b());
                // TODO mul_u64
                return a;
            }
        };

        template <>
        struct div<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                // return x86::div_u64::lh(a(), b());
                // TODO: div_u64
                return a;
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
                return vorrq_u64(a(), b());
            }
        };

        template <>
        struct bit_and<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vandq_u64(a(), b());
            }
        };

        template <>
        struct bit_xor<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return veorq_u64(a(), b());
            }
        };

        template <>
        struct shl<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return vshlq_n_u64(a(), s);
            }
        };

        template <>
        struct shr<uint64_t, 2> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return vshrq_n_u64(a(), s);
            }
        };

    }

}

inline
cftal::vec<cftal::uint64_t, 2>::vec(const vec<int64_t,2>& v)
    : base_type(vreinterpretq_u64_s64(v()))
{
}

inline
cftal::vec<cftal::uint64_t, 2>::vec(uint64_t v)
    : base_type(vmovq_n_u64(v))
{
}

inline
cftal::vec<cftal::uint64_t, 2>::vec(vec<uint64_t, 1> l, vec<uint64_t, 1> h)
    : base_type(uint64x2_t{l(), h()})
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
    uint64x2_t v;
    switch (s) {
    default:
    case 2:
        v = vld1q_u64(p);
        break;
    case 1:
        v = vld1q_dup_u64(p);
        break;
    case 0:
        v =uint64x2_t{0u, 0u};
        break;
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<uint64_t, 2> >::store(uint64_t* p,
                                            const vec<uint64_t, 2>& v)
{
    vst1q_u64(p, v());
}

inline
cftal::vec<uint64_t, 1>
cftal::low_half(const vec<uint64_t, 2>& v)
{
    return vec<uint64_t, 1>(vgetq_lane_u64(v(), 0));
}

inline
cftal::vec<uint64_t, 1>
cftal::high_half(const vec<uint64_t, 2>& v)
{
    return vec<uint64_t, 1>(vgetq_lane_u64(v(), 1));
}

inline
bool
cftal::any_of(const vec<uint64_t, 2>::mask_type& s)
{
    return arm::compress_mask_u64(s()) != 0;
}

inline
bool
cftal::all_of(const vec<uint64_t, 2>::mask_type& s)
{
    return arm::compress_mask_u64(s()) == 0x3;
}

inline
bool
cftal::none_of(const vec<uint64_t, 2>::mask_type& s)
{
    return arm::compress_mask_u64(s()) == 0;
}

inline
cftal::v2u64 cftal::max(const v2u64& a, const v2u64& b)
{
    // return vmax u64(a(), b());
    return select(a > b, a, b);
}

inline
cftal::v2u64 cftal::min(const v2u64& a, const v2u64& b)
{
    // return vminq_u64(a(), b());
    return select(a < b, a, b);
}

inline
cftal::v2u64 cftal::select(const v2u64::mask_type& m,
                           const v2u64& on_true,
                           const v2u64& on_false)
{
    return vbslq_u64(m(), on_true(), on_false());
}

template <bool _I0, bool _I1>
inline
cftal::v2u64 cftal::select(const v2u64& a, const v2u64& b)
{
    const uint64x2_t m{_I0 ? uint64_t(-1) : uint64_t(0),
                       _I1 ? uint64_t(-1) : uint64_t(0)};
    return vbslq_u64(m, a(), b());
}

template <int _I0, int _I1>
inline
cftal::v2u64 cftal::permute(const v2u64& a)
{
    return arm::perm_v2u64<_I0, _I1>(a());
}

template <int _I0, int _I1>
inline
cftal::v2u64 cftal::permute(const v2u64& a, const v2u64& b)
{
    return arm::perm_v2u64<_I0, _I1>(a(), b());
}

inline
std::pair<cftal::v2u64, cftal::v2u64>
cftal::mul_lo_hi(const v2u64& x, const v2u64& y)
{
    // TODO: mul_lo_hi u64
    return std::make_pair(x, y);
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2U32_INL__
