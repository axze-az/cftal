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
#if !defined (__CFTAL_ARM_V2F32_H__)
#define __CFTAL_ARM_V2F32_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/fenv.h>
#include <cftal/constants.h>
#include <cftal/impl/vreg.h>
#include <cftal/arm/intrin.h>
#include <cftal/arm/perm.h>
#include <cftal/arm/v2u32.h>
#include <cftal/vec_float_n.h>

namespace cftal {

#define V2F32_SPECIALIZED 1

    template <>
    class vec<float, 2> : public impl::vreg<float32x2_t> {
    public:
        using base_type= impl::vreg<float32x2_t>;

        using value_type = float;
        using mask_value_type = uint32_t;
        using mask_type= vec<mask_value_type, 2>;
        using impl::vreg<float32x2_t>::vreg;
        vec() = default;
        // create vec{v,v}
        vec(float v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<float> l);
        // allow construction from init_list
        vec(init_list<float> l);
        // allow construction from two halfes
        vec(const vec<float, 1>& lh, const vec<float, 1>& hh);
        // expression template constructor
        template <template <class _U> class _OP,
                  class _L, class _R>
        vec(const expr<_OP<vec<float, 2> >, _L, _R>& r);
    };

    template <>
    struct arg< vec<float, 2> > {
        using type = vec<float, 2>;
    };

    template <>
    struct is_vec_specialized<vec<float, 2> > : public std::true_type {};

    template <>
    struct mem< vec<float, 2> > {
        static
        vec<float, 2> load(const float* p, std::size_t n=2);
        static
        void store(float* p, const vec<float, 2>& v);
    };

    vec<float, 1>
    low_half(const vec<float, 2>& s);

    vec<float, 1>
    high_half(const vec<float, 2>& s);

    template <std::size_t _I>
    float
    extract(const vec<float, 2>& s);

    vec<float, 2>
    select(const typename vec<float, 2>::mask_type& msk,
           const vec<float, 2>& on_true,
           const vec<float, 2>& on_false);

    unsigned
    read_signs(const vec<float, 2>& b);

    bool
    elements_equal(const v2f32& a);


    v2f32 max(const v2f32& a, const v2f32& b);
    v2f32 min(const v2f32& a, const v2f32& b);

    float hmax(const v2f32& v);
    float hmin(const v2f32& v);

    v2f32 abs(const v2f32& a);
    v2f32 fabs(const v2f32& a);
    v2f32 sqrt(const v2f32& a);
    v2f32 cbrt(arg<v2f32>::type a);

    v2f32 rsqrt(const v2f32& a);

    namespace arm {
        v2f32 round(const v2f32& v, rounding_mode::type m);
    }

    v2f32 rint(const v2f32& a);
    v2f32 floor(const v2f32& a);
    v2f32 ceil(const v2f32& a);
    v2f32 trunc(const v2f32& a);
    // returns (~a) & (b)
    v2f32 andnot(const v2f32& a, const v2f32& b);
    v2f32 copysign(const v2f32& x, const v2f32& y);
    v2f32 mulsign(const v2f32& x, const v2f32& y);

    // a*b +c
    v2f32 fma(const v2f32& a, const v2f32& b, const v2f32& c);
    // a*b -c
    v2f32 fms(const v2f32& a, const v2f32& b, const v2f32& c);
    // -(a*b) + c
    v2f32 nfma(const v2f32& a, const v2f32& b, const v2f32& c);
    // -(a*b) - c
    v2f32 nfms(const v2f32& a, const v2f32& b, const v2f32& c);

    template <bool _P0, bool _P1>
    vec<float, 2>
    select(const vec<float, 2>& on_true,
           const vec<float, 2>& on_false);

    template <int32_t _P0, int32_t _P1>
    vec<float, 2>
    permute(const vec<float, 2>& s);

    template <int32_t _P0, int32_t _P1>
    vec<float, 2>
    permute(const vec<float, 2>& s0,
            const vec<float, 2>& s1);

    namespace op {

        template <>
        struct bit_not<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a) {
                uint32x2_t ai= vreinterpret_u32_f32(a());
                uint32x2_t ri= vmvn_u32(ai);
                return vreinterpret_f32_u32(ri);
            }
        };


        template <>
        struct lt<vec<float, 2>> {
            using full_type = vec<float, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vclt_f32(a(), b());
            }
        };

        template <>
        struct le<vec<float, 2>> {
            using full_type = vec<float, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vcle_f32(a(), b());
            }
        };

        template <>
        struct eq<vec<float, 2>> {
            using full_type = vec<float, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vceq_f32(a(), b());
            }
        };

        template <>
        struct ne<vec<float, 2>> {
            using full_type = vec<float, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                v2u32 m=eq<vec<float, 2>>::v(a, b);
                return ~m;
            }
        };

        template <>
        struct ge<vec<float, 2>> {
            using full_type = vec<float, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vcge_f32(a(), b());
            }
        };

        template <>
        struct gt<vec<float, 2>> {
            using full_type = vec<float, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vcgt_f32(a(), b());
            }
        };

        template <>
        struct plus<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a) {
#if 1
                return vneg_f32(a());
#else
                const full_type neg_bits(sign_f32_msk::v._f32);
                uint32x2_t ai= vreinterpret_u32_f32(a());
                uint32x2_t i = vreinterpret_u32_f32(neg_bits());
                uint32x2_t ri= veor_u32(ai, i);
                return vreinterpret_f32_u32(ri);
#endif
            }
        };

        template <>
        struct add<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vadd_f32(a(), b());
            }
        };

        template <>
        struct sub<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vsub_f32(a(), b());
            }
        };

        template <>
        struct mul<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vmul_f32(a(), b());
            }
        };

        template <>
        struct div<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
#if defined (__aarch64__)
                return vdiv_f32(a(), b());
#else
                // get an initial estimate of 1/b.
                float32x2_t rcp0 = vrecpe_f32(b());
                float32x2_t rcp1 = rcp0;
                // newton raphson steps
                for (int i=0; i< 2; ++i)
                    rcp1 = vmul_f32(vrecps_f32(b(), rcp1), rcp1);
                float32x2_t q = vmul_f32(a(), rcp1);
                return q;
#endif
            }
        };


        template <>
        struct fma<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return vadd_f32(vmul_f32(a(), b()), c());
                return vmla_f32(c(), a(), b());
            }
        };

        template <>
        struct fms<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return vsub_f32(vmul_f32(a(), b()), c());
                return vmla_f32(vneg_f32(c()), a(), b());
            }
        };

        template <>
        struct fnma<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return vsub_f32(c(), vmul_f32(a(), b()));
                return vmls_f32(c(), a(), b());
            }
        };

        template <>
        struct bit_or<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                uint32x2_t ai= vreinterpret_u32_f32(a());
                uint32x2_t bi = vreinterpret_u32_f32(b());
                uint32x2_t ri= vorr_u32(ai, bi);
                return vreinterpret_f32_u32(ri);
            }
        };

        template <>
        struct bit_and<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                uint32x2_t ai= vreinterpret_u32_f32(a());
                uint32x2_t bi = vreinterpret_u32_f32(b());
                uint32x2_t ri= vand_u32(ai, bi);
                return vreinterpret_f32_u32(ri);
            }
        };

        template <>
        struct bit_xor<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                uint32x2_t ai= vreinterpret_u32_f32(a());
                uint32x2_t bi = vreinterpret_u32_f32(b());
                uint32x2_t ri= veor_u32(ai, bi);
                return vreinterpret_f32_u32(ri);
            }
        };
    }
}

inline
cftal::vec<float, 2>::vec(float v)
    : base_type(vmov_n_f32(v))
{
}

inline
cftal::vec<float, 2>::
vec(std::initializer_list<float> l)
    : vec(mem<vec<float,2> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<float, 2>::
vec(init_list<float> l)
    : vec(mem<vec<float,2> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<float, 2>::
vec(const vec<float, 1>& l, const vec<float, 1>& h)
    : base_type(float32x2_t{l(), h()})
{
}

template <template <class _U> class _OP,
          class _L, class _R>
inline
cftal::
vec<float, 2>::vec(const expr<_OP<vec<float, 2> >, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<float, 2>
cftal::mem<cftal::vec<float, 2>>::load(const float* p, std::size_t s)
{
    float32x2_t v;
    switch (s) {
    default:
    case 2:
        v = vld1_f32(p);
        break;
    case 1:
        v = vld1_dup_f32(p);
        break;
    case 0:
        v = float32x2_t{0.0f, 0.0f};
        break;
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<float, 2>>::store(float* p, const vec<float, 2>& v)
{
    vst1_f32(p, v());
}

inline
cftal::vec<float, 1>
cftal::low_half(const v2f32& v)
{
    return vec<float, 1>(extract<0>(v));
}

inline
cftal::vec<float, 1>
cftal::high_half(const v2f32& v)
{
    return vec<float, 1>(extract<1>(v));
}

template <std::size_t _I>
float
cftal::extract(const vec<float, 2>& v)
{
    return vget_lane_f32(v(), _I);
}

inline
cftal::v2f32
cftal::select(const v2f32::mask_type& m,
              const v2f32& on_true, const v2f32& on_false)
{
    // float32x2_t vbsl_f32(uint32x2_t a, float32x2_t b, float32x2_t c);
    return vbsl_f32(m(), on_true(), on_false());
    // return arm::select(m(), on_true(), on_false());
}


inline
cftal::v2f32
cftal::max(const v2f32& a, const v2f32& b)
{
    return vmax_f32(a(), b());
}

inline
cftal::v2f32
cftal::min(const v2f32& a, const v2f32& b)
{
    return vmin_f32(a(), b());
}

inline
float
cftal::hmax(const v2f32& v)
{
    v2f32 vp=permute<1, 0>(v);
    v2f32 r=max(v, vp);
    return extract<0>(r);
}

inline
float
cftal::hmin(const v2f32& v)
{
    v2f32 vp=permute<1, 0>(v);
    v2f32 r=min(v, vp);
    return extract<0>(r);
}

inline
cftal::v2f32 cftal::sqrt(const v2f32& a)
{
#if defined (__aarch64__)
    return vsqrt_f32(a());
#else
    // return _mm_sqrt_ps(a());
    // approximative quadword float inverse square root
    // static inline float32x4_t invsqrtv(float32x4_t x) {
    //    float32x4_t sqrt_reciprocal = vrsqrteq_f32(x);
    //
    //    return vrsqrtsq_f32(x * sqrt_reciprocal, sqrt_reciprocal) * sqrt_reciprocal;
    // }
    // approximative quadword float square root
    // static inline float32x4_t sqrtv(float32x4_t x) {
    //    return x * invsqrtv(x);
    // }
    // calculate inverse square root
    float32x2_t af=a();
    float32x2_t rsqrt0 = vrsqrte_f32(af);
    float32x2_t rsqrt1 = rsqrt0;
    // newton raphson steps
    for (int i=0; i< 2; ++i) {
        float32x2_t a_rsqrt1 = vmul_f32(af, rsqrt1);
        float32x2_t rsqrti= vrsqrts_f32(a_rsqrt1, rsqrt1);
        rsqrt1 = vmul_f32(rsqrti, rsqrt1);
    }
    float32x2_t r = vmul_f32(af, rsqrt1);
    return r;
#endif
}

inline
cftal::v2f32 cftal::abs(const v2f32& a)
{
#if defined (__aarch64__)
    return vabs_f32(a());
#else
    const v2f32 msk(not_sign_f32_msk::v._f32);
    uint32x2_t ai= vreinterpret_u32_f32(a());
    uint32x2_t mski= vreinterpret_u32_f32(msk());
    uint32x2_t ri= vand_u32(ai, mski);
    return vreinterpret_f32_u32(ri);
#endif
}

inline
cftal::v2f32 cftal::andnot(const v2f32& a, const v2f32& b)
{
    // return _mm_andnot_ps(a(), b());
    uint32x2_t ai= vreinterpret_u32_f32(a());
    uint32x2_t bi= vreinterpret_u32_f32(b());
    uint32x2_t ri= vbic_u32(bi, ai);
    return vreinterpret_f32_u32(ri);
}

inline
cftal::v2f32
cftal::fma(const v2f32& a, const v2f32& b, const v2f32& c)
{
    // return impl::fma(a, b, c);
    return a * b + c;
}

inline
cftal::v2f32
cftal::fms(const v2f32& a, const v2f32& b, const v2f32& c)
{
    // return impl::fma(a, b, -c);
    return a * b - c;
}

inline
cftal::v2f32
cftal::nfma(const v2f32& a, const v2f32& b, const v2f32& c)
{
    // return impl::fma(-a, b, c);
    return c - a*b;
}

inline
cftal::v2f32
cftal::nfms(const v2f32& a, const v2f32& b, const v2f32& c)
{
    // return impl::fma(-a, b, -c);
    return -(a*b) - c;
}

inline
cftal::v2f32 cftal::copysign(const v2f32& x, const v2f32& y)
{
    // return abs(x) * sgn(y)
    const v2f32 msk(not_sign_f32_msk::v._f32);
    v2f32 abs_x(x & msk);
    v2f32 sgn_y(andnot(msk, y));
    return abs_x | sgn_y;
}

inline
cftal::v2f32 cftal::mulsign(const v2f32& x, const v2f32& y)
{
    const v2f32 msk(sign_f32_msk::v._f32);
    v2f32 sgn_y = y & msk;
    return x ^ sgn_y;
}


inline
unsigned cftal::read_signs(const v2f32& a)
{
    return arm::read_signs_s32(vreinterpret_s32_f32(a()));
}

inline
bool cftal::elements_equal(const v2f32& a)
{
    float t0= extract<0>(a);
    v2f32 cmp0(t0);
    v2f32::mask_type rv(cmp0 == a);
    return all_of(rv);
}

inline
cftal::v2f32 cftal::arm::round(const v2f32& a, const rounding_mode::type m)
{
    v2f32 r;
#if defined (__aarch64__)
    switch (m) {
    case rounding_mode::nearest:
        r= vrndn_f32(a());
        break;
    case rounding_mode::downward:
        r= vrndm_f32(a());
        break;
    case rounding_mode::upward:
        r= vrndp_f32(a());
        break;
    case rounding_mode::towardzero:
        r= vrnd_f32(a());
        break;
    case rounding_mode::current:
        r= vrndi_f32(a());
        break;
    }
#else
#pragma message("implement me")
    //
#endif
    return r;
}

inline
cftal::v2f32 cftal::rint(const v2f32& a)
{
    return arm::round(a, rounding_mode::current);
}

inline
cftal::v2f32 cftal::floor(const v2f32& a)
{
    return arm::round(a, rounding_mode::downward);
}

inline
cftal::v2f32 cftal::ceil(const v2f32& a)
{
    return arm::round(a, rounding_mode::upward);
}

inline
cftal::v2f32 cftal::trunc(const v2f32& a)
{
    return arm::round(a, rounding_mode::towardzero);
}

template <bool _I0, bool _I1>
inline
cftal::vec<float, 2>
cftal::select(const vec<float, 2>& l, const vec<float,2>& r)
{
    const uint32x2_t h{_I0 ? uint32_t(-1) : uint32_t(0),
                       _I1 ? uint32_t(-1) : uint32_t(0)};
    return vbsl_f32(h, l(), r());
    // return arm::select_f32<_I0, _I1>(l(), r());
}

template <int _I0, int _I1>
inline
cftal::vec<float, 2>
cftal::permute(const vec<float, 2>& v)
{
    return arm::perm_v2f32<_I0, _I1>(v());
}

template <int _I0, int _I1>
inline
cftal::vec<float, 2>
cftal::permute(const vec<float, 2>& l, const vec<float, 2>& r)
{
    return arm::perm_v2f32<_I0, _I1>(l(), r());
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_ARM_V2F32__
