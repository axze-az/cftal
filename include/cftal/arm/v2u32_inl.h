//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_ARM_V2U32_INL_H__)
#define __CFTAL_ARM_V2U32_INL_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/arm/v2u32.h>
#include <cftal/arm/v2s32.h>
#include <cftal/arm/perm.h>
#include <cftal/impl/divide.h>

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
                auto r=impl::udiv_double_shift<v2u32, v2u32, 32>(a, b);
                return r.first;
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
                return vshl_n_u32(a(), s);
            }
        };

        template <>
        struct shr<uint32_t, 2> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return vshr_n_u32(a(), s);
            }
        };

    }

}

inline
cftal::vec<cftal::uint32_t, 2>::vec(const vec<int32_t,2>& v)
    : base_type(vreinterpret_u32_s32(v()))
{
}

inline
cftal::vec<cftal::uint32_t, 2>::vec(uint32_t v)
    : base_type(vmov_n_u32(v))
{
}

inline
cftal::vec<cftal::uint32_t, 2>::vec(vec<uint32_t, 1> l, vec<uint32_t, 1> h)
    : base_type(uint32x2_t{l(), h()})
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
    uint32x2_t v;
    switch (s) {
    default:
    case 2:
        v = vld1_u32(p);
        break;
    case 1:
        v = vld1_dup_u32(p);
        break;
    case 0:
        v =uint32x2_t{0u, 0u};
        break;
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<uint32_t, 2> >::store(uint32_t* p,
                                            const vec<uint32_t, 2>& v)
{
    vst1_u32(p, v());
}

inline
cftal::vec<uint32_t, 1>
cftal::low_half(const vec<uint32_t, 2>& v)
{
    return vec<uint32_t, 1>(vget_lane_u32(v(), 0));
}

inline
cftal::vec<uint32_t, 1>
cftal::high_half(const vec<uint32_t, 2>& v)
{
    return vec<uint32_t, 1>(vget_lane_u32(v(), 1));
}

inline
bool
cftal::any_of(const vec<uint32_t, 2>::mask_type& s)
{
    return arm::compress_mask_u32(s()) != 0;
}

inline
bool
cftal::all_of(const vec<uint32_t, 2>::mask_type& s)
{
    return arm::compress_mask_u32(s()) == 0x3;
}

inline
bool
cftal::none_of(const vec<uint32_t, 2>::mask_type& s)
{
    return arm::compress_mask_u32(s()) == 0;
}

inline
cftal::v2u32 cftal::max(const v2u32& a, const v2u32& b)
{
    return vmax_u32(a(), b());

}

inline
cftal::v2u32 cftal::min(const v2u32& a, const v2u32& b)
{
    return vmin_u32(a(), b());
}

inline
cftal::v2u32 cftal::select(const v2u32::mask_type& m,
                           const v2u32& on_true,
                           const v2u32& on_false)
{
    return vbsl_u32(m(), on_true(), on_false());
}

template <bool _I0, bool _I1>
inline
cftal::v2u32 cftal::select(const v2u32& a, const v2u32& b)
{
    const uint32x2_t m{_I0 ? uint32_t(-1) : uint32_t(0),
                       _I1 ? uint32_t(-1) : uint32_t(0)};
    return vbsl_u32(m, a(), b());
}

template <int _I0, int _I1>
inline
cftal::v2u32 cftal::permute(const v2u32& a)
{
    return arm::perm_v2u32<_I0, _I1>(a());
}

template <int _I0, int _I1>
inline
cftal::v2u32 cftal::permute(const v2u32& a, const v2u32& b)
{
    return arm::perm_v2u32<_I0, _I1>(a(), b());
}

inline
std::pair<cftal::v2u32, cftal::v2u32>
cftal::mul_lo_hi(const v2u32& x, const v2u32& y)
{
    uint64x2_t r0=vmull_u32(x(), y());
    // p0l p0h p1l p1h
    uint32x4_t r1=vreinterpretq_u32_u64(r0);
    uint32x4_t rs=arm::impl::perm1_v4u32<0, 2, 1, 3>::v(r1);
    uint32x2_t l= vget_low_u32(rs);
    uint32x2_t h= vget_high_u32(rs);
    return std::make_pair(l, h);
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2U32_INL__
