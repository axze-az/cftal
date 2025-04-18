//
// Copyright (C) 2010-2025 Axel Zeuner
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
//
#if !defined (__CFTAL_ARM_V2S64_INL_H__)
#define __CFTAL_ARM_V2S64_INL_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/arm/v2s64.h>
#include <cftal/arm/v2s64.h>
#include <cftal/arm/perm.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a) {
                uint32x4_t t=vreinterpretq_u32_s64(a());
                return vreinterpretq_s64_u32(
                    vmvnq_u32(t));
            }
        };


        template <>
        struct lt<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vcltq_s64(a(), b());
            }
        };

        template <>
        struct le<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vcleq_s64(a(), b());
            }
        };

        template <>
        struct eq<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vceqq_s64(a(), b());
            }
        };

        template <>
        struct ne<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return ~(a==b);
            }
        };

        template <>
        struct ge<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vcgeq_s64(a(), b());
            }
        };

        template <>
        struct gt<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vcgtq_s64(a(), b());
            }
        };

        template <>
        struct plus<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a) {
                static const full_type z{0, 0};
                return vsubq_s64(z(), a());
            }
        };

        template <>
        struct add<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vaddq_s64(a(), b());
            }
        };

        template <>
        struct sub<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vsubq_s64(a(), b());
            }
        };

        template <>
        struct mul<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                // return vmulq_s64(a(), b());
                // TODO mul_s64
                return a;
            }
        };

        template <>
        struct div<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                // return x86::div_s64::lh(a(), b());
                // TODO: div_s64
                return a;
            }
        };

        template <>
        struct mod<vec<int64_t, 2>> {
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
        struct fma<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<vec<int64_t, 2>>::v(
                    mul<vec<int64_t, 2>>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<vec<int64_t, 2>>::v(
                    mul<vec<int64_t, 2>>::v(a , b), c);
            }
        };

        template <>
        struct fnma<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<vec<int64_t, 2>>::v(
                    c, mul<vec<int64_t, 2>>::v(a, b));

            }
        };

        template <>
        struct bit_or<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vorrq_s64(a(), b());
            }
        };

        template <>
        struct bit_and<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vandq_s64(a(), b());
            }
        };

        template <>
        struct bit_xor<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return veorq_s64(a(), b());
            }
        };

        template <>
        struct shl<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return vshlq_n_s64(a(), s);
            }
        };

        template <>
        struct shr<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return vshrq_n_s64(a(), s);
            }
        };

    }

}

inline
cftal::vec<cftal::int64_t, 2>::vec(const vec<uint64_t,2>& v)
    : base_type(vreinterpretq_s64_u64(v()))
{
}

inline
cftal::vec<cftal::int64_t, 2>::vec(int64_t v)
    : base_type(vmovq_n_s64(v))
{
}

inline
cftal::vec<cftal::int64_t, 2>::vec(vec<int64_t, 1> l, vec<int64_t, 1> h)
    : base_type(int64x2_t{l(), h()})
{
}

inline
cftal::vec<cftal::int64_t, 2>::
vec(std::initializer_list<int64_t> l)
    : vec(mem<vec<int64_t, 2> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::int64_t, 2>::
vec(init_list<int64_t> l)
    : vec(mem<vec<int64_t, 2> >::load(l.begin(), l.size()))
{
}

template <template <class _U> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::int64_t, 2>::vec(const expr<_OP<vec<int64_t, 2> >, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::int64_t, 2>
cftal::mem<cftal::vec<int64_t, 2> >::load(const int64_t* p, std::size_t s)
{
    int64x2_t v;
    switch (s) {
    default:
    case 2:
        v = vld1q_s64(p);
        break;
    case 1:
        v = vld1q_dup_s64(p);
        break;
    case 0:
        v =int64x2_t{0u, 0u};
        break;
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<int64_t, 2> >::store(int64_t* p,
                                           const vec<int64_t, 2>& v)
{
    vst1q_s64(p, v());
}

inline
cftal::vec<int64_t, 1>
cftal::low_half(const vec<int64_t, 2>& v)
{
    return vec<int64_t, 1>(vgetq_lane_s64(v(), 0));
}

inline
cftal::vec<int64_t, 1>
cftal::high_half(const vec<int64_t, 2>& v)
{
    return vec<int64_t, 1>(vgetq_lane_s64(v(), 1));
}

inline
cftal::v2s64 cftal::max(const v2s64& a, const v2s64& b)
{
    return select(a>b, a, b);
    // return vmaxq_s64(a(), b());
}

inline
cftal::v2s64 cftal::min(const v2s64& a, const v2s64& b)
{
    return select(a<b, a, b);
    // return vminq_s64(a(), b());
}

inline
cftal::v2s64 cftal::select(const v2s64::mask_type& m,
                           const v2s64& on_true,
                           const v2s64& on_false)
{
    return vbslq_s64(m(), on_true(), on_false());
}

template <bool _I0, bool _I1>
inline
cftal::v2s64 cftal::select(const v2s64& a, const v2s64& b)
{
    const uint64x2_t m{_I0 ? uint64_t(-1ll) : uint64_t(0),
                       _I1 ? uint64_t(-1ll) : uint64_t(0)};
    return vbslq_s64(m, a(), b());
}

template <int _I0, int _I1>
inline
cftal::v2s64 cftal::permute(const v2s64& a)
{
    return arm::perm_v2s64<_I0, _I1>(a());
}

template <int _I0, int _I1>
inline
cftal::v2s64 cftal::permute(const v2s64& a, const v2s64& b)
{
    return arm::perm_v2s64<_I0, _I1>(a(), b());
}

inline
std::pair<cftal::v2s64, cftal::v2s64>
cftal::mul_lo_hi(const v2s64& x, const v2s64& y)
{
    // TODO: mul_lo_hi s64
    return std::make_pair(x, y);
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2U32_INL__
