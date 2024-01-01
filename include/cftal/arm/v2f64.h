//
// Copyright (C) 2010-2024 Axel Zeuner
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
#if !defined (__CFTAL_ARM_V2F64_H__)
#define __CFTAL_ARM_V2F64_H__ 1

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

#define V2F64_SPECIALIZED 1

    template <>
    class vec<double, 2> : public impl::vreg<float64x2_t> {
    public:
        using base_type= impl::vreg<float64x2_t>;

        using value_type = double;
        using mask_value_type = uint64_t;
        using mask_type= vec<mask_value_type, 2>;
        using impl::vreg<float64x2_t>::vreg;
        vec() = default;
        // create vec{v,v}
        vec(double v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<double> l);
        // allow construction from init_list
        vec(init_list<double> l);
        // allow construction from two halfes
        vec(const vec<double, 1>& lh, const vec<double, 1>& hh);
        // expression template constructor
        template <template <class _U> class _OP,
                  class _L, class _R>
        vec(const expr<_OP<vec<double, 2>>, _L, _R>& r);
    };

    template <>
    struct arg< vec<double, 2> > {
        using type = vec<double, 2>;
    };

    template <>
    struct is_vec_specialized<vec<double, 2> > : public std::true_type {};

    template <>
    struct mem< vec<double, 2> > {
        static
        vec<double, 2> load(const double* p, std::size_t n=2);
        static
        void store(double* p, const vec<double, 2>& v);
    };

    vec<double, 1>
    low_half(const vec<double, 2>& s);

    vec<double, 1>
    high_half(const vec<double, 2>& s);

    template <std::size_t _I>
    double
    extract(const vec<double, 2>& s);

    vec<double, 2>
    select(const typename vec<double, 2>::mask_type& msk,
           const vec<double, 2>& on_true,
           const vec<double, 2>& on_false);

    unsigned
    read_signs(const vec<double, 2>& b);

    bool
    elements_equal(const v2f64& a);


    v2f64 max(const v2f64& a, const v2f64& b);
    v2f64 min(const v2f64& a, const v2f64& b);

    float max_element(const v2f64& v);
    float min_element(const v2f64& v);

    v2f64 abs(const v2f64& a);
    v2f64 fabs(const v2f64& a);
    v2f64 sqrt(const v2f64& a);
    v2f64 cbrt(arg<v2f64>::type a);

    namespace arm {
        v2f64 round(const v2f64& v, rounding_mode::type m);
    }

    v2f64 rint(const v2f64& a);
    v2f64 floor(const v2f64& a);
    v2f64 ceil(const v2f64& a);
    v2f64 trunc(const v2f64& a);
    // returns (~a) & (b)
    v2f64 andnot(const v2f64& a, const v2f64& b);
    v2f64 copysign(const v2f64& x, const v2f64& y);
    v2f64 mulsign(const v2f64& x, const v2f64& y);

    // a*b +c
    v2f64 fma(const v2f64& a, const v2f64& b, const v2f64& c);
    // a*b -c
    v2f64 fms(const v2f64& a, const v2f64& b, const v2f64& c);
    // -(a*b) + c
    v2f64 nfma(const v2f64& a, const v2f64& b, const v2f64& c);
    // -(a*b) - c
    v2f64 nfms(const v2f64& a, const v2f64& b, const v2f64& c);

    template <bool _P0, bool _P1>
    vec<double, 2>
    select(const vec<double, 2>& on_true,
           const vec<double, 2>& on_false);

    template <int32_t _P0, int32_t _P1>
    vec<double, 2>
    permute(const vec<double, 2>& s);

    template <int32_t _P0, int32_t _P1>
    vec<double, 2>
    permute(const vec<double, 2>& s0,
            const vec<double, 2>& s1);

    namespace op {

        template <>
        struct bit_not<vec<double, 2>> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a) {
                uint32x4_t ai= vreinterpretq_u32_f64(a());
                uint32x4_t ri= vmvnq_u32(ai);
                return vreinterpretq_f64_u32(ri);
            }
        };


        template <>
        struct lt<vec<double, 2>> {
            using full_type = vec<double, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vcltq_f64(a(), b());
            }
        };

        template <>
        struct le<vec<double, 2>> {
            using full_type = vec<double, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vcleq_f64(a(), b());
            }
        };

        template <>
        struct eq<vec<double, 2>> {
            using full_type = vec<double, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vceqq_f64(a(), b());
            }
        };

        template <>
        struct ne<vec<double, 2>> {
            using full_type = vec<double, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return ~(a==b);
            }
        };

        template <>
        struct ge<vec<double, 2>> {
            using full_type = vec<double, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vcgeq_f64(a(), b());
            }
        };

        template <>
        struct gt<vec<double, 2>> {
            using full_type = vec<double, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vcgtq_f64(a(), b());
            }
        };

        template <>
        struct plus<vec<double, 2>> {
            using full_type = vec<double, 2>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<double, 2>> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a) {
#if 1
                return vnegq_f64(a());
#else
                const full_type neg_bits(sign_f64_msk::v._f64);
                uint32x2_t ai= vreinterpret_u32_f64(a());
                uint32x2_t i = vreinterpret_u32_f64(neg_bits());
                uint32x2_t ri= veor_u32(ai, i);
                return vreinterpret_f64_u32(ri);
#endif
            }
        };

        template <>
        struct add<vec<double, 2>> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vaddq_f64(a(), b());
            }
        };

        template <>
        struct sub<vec<double, 2>> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vsubq_f64(a(), b());
            }
        };

        template <>
        struct mul<vec<double, 2>> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vmulq_f64(a(), b());
            }
        };

        template <>
        struct div<vec<double, 2>> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
#if defined (__aarch64__)
                return vdivq_f64(a(), b());
#else
                // get an initial estimate of 1/b.
                float64x2_t rcp0 = vrecpeq_f64(b());
                float64x2_t rcp1 = rcp0;
                // newton raphson steps
                for (int i=0; i< 2; ++i)
                    rcp1 = vmulq_f64(vrecpsq_f64(b(), rcp1), rcp1);
                float64x2_t q = vmulq_f64(a(), rcp1);
                return q;
#endif
            }
        };

        template <>
        struct fma<vec<double, 2>> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return vaddq_f64(vmulq_f64(a(), b()), c());
                return vmlaq_f64(c(), a(), b());
            }
        };

        template <>
        struct fms<vec<double, 2>> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return vsubq_f64(vmulq_f64(a(), b()), c());
                return vmlaq_f64(vnegq_f64(c()), a(), b());
            }
        };

        template <>
        struct fnma<vec<double, 2>> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return vsubq_f64(c(), vmulq_f64(a(), b()));
                return vmlsq_f64(c(), a(), b());
            }
        };

        template <>
        struct bit_or<vec<double, 2>> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                uint32x4_t ai= vreinterpretq_u32_f64(a());
                uint32x4_t bi = vreinterpretq_u32_f64(b());
                uint32x4_t ri= vorrq_u32(ai, bi);
                return vreinterpretq_f64_u32(ri);
            }
        };

        template <>
        struct bit_and<vec<double, 2>> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                uint32x4_t ai= vreinterpretq_u32_f64(a());
                uint32x4_t bi = vreinterpretq_u32_f64(b());
                uint32x4_t ri= vandq_u32(ai, bi);
                return vreinterpretq_f64_u32(ri);
            }
        };

        template <>
        struct bit_xor<vec<double, 2>> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                uint32x4_t ai= vreinterpretq_u32_f64(a());
                uint32x4_t bi = vreinterpretq_u32_f64(b());
                uint32x4_t ri= veorq_u32(ai, bi);
                return vreinterpretq_f64_u32(ri);
            }
        };
    }
}

inline
cftal::vec<double, 2>::vec(double v)
    : base_type(vmovq_n_f64(v))
{
}

inline
cftal::vec<double, 2>::
vec(std::initializer_list<double> l)
    : vec(mem<vec<double,2> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<double, 2>::
vec(init_list<double> l)
    : vec(mem<vec<double,2> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<double, 2>::
vec(const vec<double, 1>& l, const vec<double, 1>& h)
    : base_type(float64x2_t{l(), h()})
{
}

template <template <class _U> class _OP,
          class _L, class _R>
inline
cftal::
vec<double, 2>::vec(const expr<_OP<vec<double, 2> >, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<double, 2>
cftal::mem<cftal::vec<double, 2>>::load(const double* p, std::size_t s)
{
    float64x2_t v;
    switch (s) {
    default:
    case 2:
        v = vld1q_f64(p);
        break;
    case 1:
        v = vld1q_dup_f64(p);
        break;
    case 0:
        v = float64x2_t{0.0f, 0.0f};
        break;
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<double, 2>>::store(double* p, const vec<double, 2>& v)
{
    vst1q_f64(p, v());
}

inline
cftal::vec<double, 1>
cftal::low_half(const v2f64& v)
{
    return vec<double, 1>(extract<0>(v));
}

inline
cftal::vec<double, 1>
cftal::high_half(const v2f64& v)
{
    return vec<double, 1>(extract<1>(v));
}

template <std::size_t _I>
double
cftal::extract(const vec<double, 2>& v)
{
    return vgetq_lane_f64(v(), _I);
}

inline
cftal::v2f64
cftal::select(const v2f64::mask_type& m,
              const v2f64& on_true, const v2f64& on_false)
{
    // float64x2_t vbsl_f64(uint32x2_t a, float64x2_t b, float64x2_t c);
    return vbslq_f64(m(), on_true(), on_false());
    // return arm::select(m(), on_true(), on_false());
}


inline
cftal::v2f64
cftal::max(const v2f64& a, const v2f64& b)
{
    return vmaxq_f64(a(), b());
}

inline
cftal::v2f64
cftal::min(const v2f64& a, const v2f64& b)
{
    return vminq_f64(a(), b());
}

inline
float
cftal::max_element(const v2f64& v)
{
    v2f64 vp=permute<1, 0>(v);
    v2f64 r=max(v, vp);
    return extract<0>(r);
}

inline
float
cftal::min_element(const v2f64& v)
{
    v2f64 vp=permute<1, 0>(v);
    v2f64 r=min(v, vp);
    return extract<0>(r);
}

inline
cftal::v2f64 cftal::sqrt(const v2f64& a)
{
#if defined (__aarch64__)
    return vsqrtq_f64(a());
#else
    // return _mm_sqrt_ps(a());
    // approximative quadword float inverse square root
    // static inline float64x4_t invsqrtv(float64x4_t x) {
    //    float64x4_t sqrt_reciprocal = vrsqrteq_f64(x);
    //
    //    return vrsqrtsq_f64(x * sqrt_reciprocal, sqrt_reciprocal) * sqrt_reciprocal;
    // }
    // approximative quadword float square root
    // static inline float64x4_t sqrtv(float64x4_t x) {
    //    return x * invsqrtv(x);
    // }
    // calculate inverse square root
    float64x2_t af=a();
    float64x2_t rsqrt0 = vrsqrte_f64(af);
    float64x2_t rsqrt1 = rsqrt0;
    // newton raphson steps
    for (int i=0; i< 2; ++i) {
        float64x2_t a_rsqrt1 = vmul_f64(af, rsqrt1);
        float64x2_t rsqrti= vrsqrts_f64(a_rsqrt1, rsqrt1);
        rsqrt1 = vmul_f64(rsqrti, rsqrt1);
    }
    float64x2_t r = vmul_f64(af, rsqrt1);
    return r;
#endif
}

inline
cftal::v2f64 cftal::abs(const v2f64& a)
{
#if defined (__aarch64__)
    return vabsq_f64(a());
#else
    const v2f64 msk(not_sign_f64_msk::v._f64);
    uint32x2_t ai= vreinterpret_u32_f64(a());
    uint32x2_t mski= vreinterpret_u32_f64(msk());
    uint32x2_t ri= vand_u32(ai, mski);
    return vreinterpret_f64_u32(ri);
#endif
}

inline
cftal::v2f64 cftal::andnot(const v2f64& a, const v2f64& b)
{
    // return _mm_andnot_ps(a(), b());
    uint32x4_t ai= vreinterpretq_u32_f64(a());
    uint32x4_t bi= vreinterpretq_u32_f64(b());
    uint32x4_t ri= vbicq_u32(bi, ai);
    return vreinterpretq_f64_u32(ri);
}

inline
cftal::v2f64
cftal::fma(const v2f64& a, const v2f64& b, const v2f64& c)
{
    // return impl::fma(a, b, c);
    return a * b + c;
}

inline
cftal::v2f64
cftal::fms(const v2f64& a, const v2f64& b, const v2f64& c)
{
    // return impl::fma(a, b, -c);
    return a * b - c;
}

inline
cftal::v2f64
cftal::nfma(const v2f64& a, const v2f64& b, const v2f64& c)
{
    // return impl::fma(-a, b, c);
    return c - a*b;
}

inline
cftal::v2f64
cftal::nfms(const v2f64& a, const v2f64& b, const v2f64& c)
{
    // return impl::fma(-a, b, -c);
    return -(a*b) - c;
}

inline
cftal::v2f64 cftal::copysign(const v2f64& x, const v2f64& y)
{
    // return abs(x) * sgn(y)
    const v2f64 msk(not_sign_f64_msk::v._f64);
    v2f64 abs_x(x & msk);
    v2f64 sgn_y(andnot(msk, y));
    return abs_x | sgn_y;
}

inline
cftal::v2f64 cftal::mulsign(const v2f64& x, const v2f64& y)
{
    const v2f64 msk(sign_f64_msk::v._f64);
    v2f64 sgn_y = y & msk;
    return x ^ sgn_y;
}


inline
unsigned cftal::read_signs(const v2f64& a)
{
    return arm::read_signs_s64(vreinterpretq_s64_f64(a()));
}

inline
bool cftal::elements_equal(const v2f64& a)
{
    double t0= extract<0>(a);
    v2f64 cmp0(t0);
    v2f64::mask_type rv(cmp0 == a);
    return all_of(rv);
}

inline
cftal::v2f64 cftal::arm::round(const v2f64& a, const rounding_mode::type m)
{
    v2f64 r;
#if defined (__aarch64__)
    switch (m) {
    case rounding_mode::nearest:
        r= vrndnq_f64(a());
        break;
    case rounding_mode::downward:
        r= vrndmq_f64(a());
        break;
    case rounding_mode::upward:
        r= vrndpq_f64(a());
        break;
    case rounding_mode::towardzero:
        r= vrndq_f64(a());
        break;
    case rounding_mode::current:
        r= vrndiq_f64(a());
        break;
    }
#else
#pragma message("implement me")
    //
#endif
    return r;
}

inline
cftal::v2f64 cftal::rint(const v2f64& a)
{
    return arm::round(a, rounding_mode::current);
}

inline
cftal::v2f64 cftal::floor(const v2f64& a)
{
    return arm::round(a, rounding_mode::downward);
}

inline
cftal::v2f64 cftal::ceil(const v2f64& a)
{
    return arm::round(a, rounding_mode::upward);
}

inline
cftal::v2f64 cftal::trunc(const v2f64& a)
{
    return arm::round(a, rounding_mode::towardzero);
}

template <bool _I0, bool _I1>
inline
cftal::vec<double, 2>
cftal::select(const vec<double, 2>& l, const vec<double,2>& r)
{
    const uint64x2_t h{_I0 ? uint64_t(-1LL) : uint64_t(0),
                       _I1 ? uint64_t(-1LL) : uint64_t(0)};
    return vbslq_f64(h, l(), r());
    // return arm::select_f64<_I0, _I1>(l(), r());
}

template <int _I0, int _I1>
inline
cftal::vec<double, 2>
cftal::permute(const vec<double, 2>& v)
{
    return arm::perm_v2f64<_I0, _I1>(v());
}

template <int _I0, int _I1>
inline
cftal::vec<double, 2>
cftal::permute(const vec<double, 2>& l, const vec<double, 2>& r)
{
    return arm::perm_v2f64<_I0, _I1>(l(), r());
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_ARM_V2F64__
