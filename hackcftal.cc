//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <iterator>
#include <cmath>
#include <cftal/math/func_constants.h>
#include <cftal/math/elem_func_core_f32.h>

#include <cftal/f16.h>

namespace cftal {

    namespace impl {

        template <typename _T>
        std::pair<_T, _T>
        agm_step(std::pair<_T, _T> p) {
            using std::sqrt;
            using std::make_pair;
            auto t=make_pair((p.first + p.second)* 0.5,
                             sqrt(p.first * p.second));
            // std::cout << t.first << " " << t.second << std::endl;
            return t;
        }

        template <std::size_t _N, typename _T>
        std::pair<_T, _T>
        agm(std::pair<_T, _T> p) {
            for (std::size_t i=0; i<_N; ++i)
                p=agm_step(p);
            return p;
        }

        template <typename _T>
        _T
        xlog(_T v) {
            using ctbl = math::impl::d_real_constants<d_real<_T>, _T>;
            _T p=0.0;
            _T s= v;
            while (s < 0x1p64) {
                s *= 0x1p64;
                p += 64;
            }
            _T inv_s= 4.0 / s;
            _T a=agm<20>(std::make_pair(1.0, inv_s)).first;
            a*=2.0;
            d_real<_T> t= ctbl::m_pi.h()/a - ctbl::m_ln2.h()* p;
            return t.h();
        }
    }
}

namespace cftal {
    // a 16 bit floating point number
    class f16_t {
    public:
        constexpr f16_t() : _f(0) {}
        constexpr explicit f16_t(uint16_t f) : _f(f) {}
        constexpr uint16_t operator()() const { return _f; }
    private:
        uint16_t _f;
    };

    inline
    uint16_t read_bits(f16_t v) {
        return v();
    }

    template <size_t _N>
    class vec<f16_t, _N> : public vec<int16_t, _N> {
    public:
        using value_type = f16_t;
        using half_type = vec<f16_t, _N/2>;
        using base_type = vec<int16_t, _N>;
        using mask_value_type = typename half_type::mask_value_type;
        using mask_type = vec<mask_value_type, _N>;
        vec() = default;
        vec(const vec& r) = default;
        vec(vec&& r) = default;
        vec& operator=(const vec& r) = default;
        vec& operator=(vec&& r) = default;
        vec(const half_type& lh, const half_type& hh) :
            base_type(lh, hh) {}
        const half_type& lh() const {
            return static_cast<const half_type&>(base_type::lh());
        }
        const half_type& hh() const {
            return static_cast<const half_type&>(base_type::hh());
        }
        const base_type& operator()() const { return *this; }
        vec(f16_t v) : base_type(read_bits(v)) {}
        vec(const base_type& r) : base_type(r) {}
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<f16_t, _N>, _L, _R>& r) : vec(eval(r)) {}
    };

    template <>
    class vec<f16_t, 1> : public vec<int16_t, 1> {
    public:
        using base_type = vec<int16_t, 1>;
        using mask_type = vec<f16_t, 1>;
        using mask_value_type = f16_t;
        vec() = default;
        vec(const vec& r) = default;
        vec(vec&& r) = default;
        vec& operator=(const vec& r) = default;
        vec& operator=(vec&& r) = default;
        vec(f16_t v) : base_type(read_bits(v)) {}
        vec(const base_type& v) : base_type(v) {}
        f16_t operator()() const { return f16_t(base_type::operator()()); }
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<f16_t, 1>, _L, _R>& r) : vec(eval(r)) {}
    };

    template <size_t _N>
    struct arg< vec<f16_t, _N> > {
        using type = typename arg <vec<int16_t, _N> >::type;
    };

    template <>
    struct mem< vec<f16_t, 1> > {
        static
        vec<f16_t, 1> load(const f16_t* p, std::size_t n=1) {
            return vec<f16_t, 1>(*p);
        }
        static
        void store(f16_t* p, const vec<f16_t, 1>& v) {
            *p = v();
        }
    };

    template <size_t _N>
    struct mem< vec<f16_t, _N> > {
        static
        vec<f16_t, _N> load(const f16_t* p, std::size_t n=_N) {
            using v_t= vec<uint16_t, _N>;
            v_t r(mem<typename v_t::base_type>::load(
                reinterpret_cast<const uint16_t*>(p), n));
            return r;
        }
        static
        void store(f16_t* p, const vec<f16_t, _N>& v) {
            using v_t = vec<f16_t, _N>;
            mem<typename v_t::base_type>::store(
                reinterpret_cast<uint16_t*>(p), v);
        }
    };

    template <std::size_t _N>
    vec<f16_t, _N>
    cvt_f32_msk_to_f16_msk(const vec<f32_t, _N>& m) {
        vec<uint16_t, 2*_N> tm=as<vec<uint16_t, 2*_N>>(m);
        return even_elements(tm);
    }

    // abs
    template <size_t _N>
    vec<f16_t, _N>
    abs(const vec<f16_t, _N>& a);

    // nan
    template <size_t _N>
    typename vec<f16_t, _N>::mask_type
    isnan(const vec<f16_t, _N>& a);

    // inf
    template <size_t _N>
    typename vec<f16_t, _N>::mask_type
    isinf(const vec<f16_t, _N>& a);

    namespace op {

        template <size_t _N>
        struct lt<mf_f16_t, _N> {
            using full_type = vec<mf_f16_t, _N>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b);
        };

        namespace impl {

            template <size_t _N>
            struct f16_add {
                using full_type = vec<mf_f16_t, _N>;
                static
                full_type
                v(const full_type& a, const full_type& b) {
#if 0
                    auto af=cvt_f16_to_f32(a), bf=cvt_f16_to_f32(b);
                    auto rf=af+bf;
                    auto r=cvt_f32_to_f16(rf);
                    return r;
#else
                    vec<mf_f16_t, 2*_N> ab(a, b);
                    auto abf=cvt_f16_to_f32(ab);
                    auto af=low_half(abf), bf=high_half(abf);
                    auto rf=af+bf;
                    auto r=cvt_f32_to_f16(rf);
                    return r;
#endif
                }
            };
        }

        template <size_t _N>
        struct eq<f16_t, _N> {
            using full_type = vec<f16_t, _N>;
            static
            typename full_type::mask_type
            v(const full_type& a, const full_type& b);
        };

        template <size_t _N>
        struct ne<f16_t, _N> {
            using full_type = vec<f16_t, _N>;
            static
            typename full_type::mask_type
            v(const full_type& a, const full_type& b);
        };

        template <size_t _N>
        struct le<f16_t, _N> {
            using full_type = vec<f16_t, _N>;
            static
            typename full_type::mask_type
            v(const full_type& a, const full_type& b);
        };


        template <size_t _N>
        struct add<mf_f16_t, _N> : public impl::f16_add<_N> {};

        template <>
        struct add<mf_f16_t, 1>  : public impl::f16_add<1> {};

    }

    const uint16_t not_sign_f16_msk = 0x7fffu;
    // const uint16_t sign_f16_msk=  0x8000;
    // const uint16_t exp_f16_msk = 0x7c00;
    // const uint16_t not_exp16_msk = ~exp_f16_msk;
    // const uint16_t sig_f16_msk = 0x03ff;
    // const uint16_t bias_f16 = 0xf;
    // const uint16_t exp_shift_f16 = 10;
    // const uint16_t exp_msk_f16 = 0x1f;

}

template <std::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::abs(const vec<f16_t, _N>& a)
{
    vec<f16_t, _N> r(a() & vec<f16_t, _N>(not_sign_f16_msk)());
    return r;
}

template <std::size_t _N>
typename cftal::vec<cftal::f16_t, _N>::mask_type
cftal::isnan(const vec<f16_t, _N>& a)
{
    using v_t = vec<f16_t, _N>;
    using bv_t = typename vec<f16_t, _N>::base_type;
    v_t aa=abs(a);
    bv_t an= aa() > 0x7c00u;
    return an;
}

template <std::size_t _N>
typename cftal::vec<cftal::f16_t, _N>::mask_type
cftal::isinf(const vec<f16_t, _N>& a)
{
    using v_t = vec<f16_t, _N>;
    using bv_t = typename vec<f16_t, _N>::base_type;
    v_t aa=abs(a);
    bv_t an= aa() == 0x7c00u;
    return an;
}

template <std::size_t _N>
typename cftal::vec<cftal::f16_t, _N>::mask_type
cftal::op::eq<cftal::f16_t, _N>::
v(const vec<f16_t, _N>& a, const vec<f16_t, _N>& b)
{
    using bv_t = typename vec<f16_t, _N>::base_type;
    using m_bv_t = typename bv_t::mask_type;
    bv_t x= a(), y=b();
    bv_t a_x = abs(a)(), a_y = abs(b)();
    m_bv_t x_nan = a_x > 0x7c00u;
    m_bv_t y_nan = a_y > 0x7c00u;
    m_bv_t x_eq_y = (x == y) | (bv_t(a_x|a_y) == 0);
    x_eq_y = select(x_nan | y_nan, x_eq_y, 0);
    return x_eq_y;
}

template <std::size_t _N>
typename cftal::vec<cftal::f16_t, _N>::mask_type
cftal::op::le<cftal::f16_t, _N>::
v(const vec<f16_t, _N>& x, const vec<f16_t, _N>& y)
{
    return 0;
#if 0
    using bv_t = typename vec<f16_t, _N>::base_type;
    using m_bv_t = typename bv_t::mask_type;
    bv_t a= x(), b=y();
    m_bv_t asgn = (a & sign_f16_msk) < 0;
    m_bv_t bsgn = (b & sign_f16_msk) < 0;

    m_bv_t x_is_nan = (x & not_sign_f16_msk) <= (0x7c00u);
    m_bv_t y_is_nan = (y & not_sign_f16_msk) <= (0x7c00u);




    m_bv_t diff_signs = asgn != ysgn;

    m_bv_t b_le_a = x <= y;



    m_bv_t x_eq_y = (x == y) | (bv_t(xs|ys) == 0);
    m_bv_t r= x_not_nan & y_not_nan & x_eq_y;
    return r;
#endif
}

template <std::size_t _N>
typename cftal::vec<cftal::f16_t, _N>::mask_type
cftal::op::ne<cftal::f16_t, _N>::
v(const vec<f16_t, _N>& a, const vec<f16_t, _N>& b)
{
    auto t=eq<cftal::f16_t, _N>::v(a, b)();
    using bv_t = typename vec<f16_t, _N>::base_type;
    using m_bv_t = typename bv_t::mask_type;
    m_bv_t nt= ~t;
    return nt;
}

cftal::vec<cftal::f16_t, 8>::mask_type
fp16_eq(cftal::vec<cftal::f16_t, 8> a,
        cftal::vec<cftal::f16_t, 8> b)
{
    return a == b;
}

cftal::vec<cftal::f16_t, 8>::mask_type
fp16_ne(cftal::vec<cftal::f16_t, 8> a,
        cftal::vec<cftal::f16_t, 8> b)
{
    return a != b;
}

cftal::vec<cftal::mf_f16_t, 8>
fp16_add(cftal::vec<cftal::mf_f16_t, 8> a,
         cftal::vec<cftal::mf_f16_t, 8> b)
{
#if 1
    return a + b;
#else
    using namespace cftal;
    vec<f32_t, 8> af=cvt_f16_to_f32(a);
    vec<f32_t, 8> bf=cvt_f16_to_f32(b);
    vec<f32_t, 8> rf=af+bf;
    return cvt_f32_to_f16(rf);
#endif
}

cftal::vec<cftal::mf_f16_t, 4>
fp16_add(cftal::vec<cftal::mf_f16_t, 4> a,
         cftal::vec<cftal::mf_f16_t, 4> b)
{
#if 1
    return a + b;
#else
    using namespace cftal;
    vec<f32_t, 4> af=cvt_f16_to_f32(a);
    vec<f32_t, 4> bf=cvt_f16_to_f32(b);
    vec<f32_t, 4> rf=af+bf;
    return cvt_f32_to_f16(rf);
#endif
}

cftal::vec<cftal::mf_f16_t, 2>
fp16_add(cftal::vec<cftal::mf_f16_t, 2> a,
         cftal::vec<cftal::mf_f16_t, 2> b)
{
#if 1
    return a + b;
#else
    using namespace cftal;
    vec<f32_t, 2> af=cvt_f16_to_f32(a);
    vec<f32_t, 2> bf=cvt_f16_to_f32(b);
    vec<f32_t, 2> rf=af+bf;
    return cvt_f32_to_f16(rf);
#endif
}

cftal::vec<cftal::mf_f16_t, 1>
fp16_add(cftal::vec<cftal::mf_f16_t, 1> a,
         cftal::vec<cftal::mf_f16_t, 1> b)
{
#if 1
    return a + b;
#else
    using namespace cftal;
    vec<f32_t, 1> af=cvt_f16_to_f32(a);
    vec<f32_t, 1> bf=cvt_f16_to_f32(b);
    vec<f32_t, 1> rf=af+bf;
    return cvt_f32_to_f16(rf);
#endif
}


void
transpose4x4(double* d,
             const double* a)
{
    using namespace cftal;
    v4f64 a0=mem<v4f64>::load(a, 4),
        a1=mem<v4f64>::load(a+4, 4),
        a2=mem<v4f64>::load(a+8, 4),
        a3=mem<v4f64>::load(a+12, 4);
    transpose_4x4(a0, a1, a2, a3);
    mem<v4f64>::store(d+0, a0);
    mem<v4f64>::store(d+4, a1);
    mem<v4f64>::store(d+8, a2);
    mem<v4f64>::store(d+12, a3);
}


int main(int argc, char** argv)
{
    using namespace cftal;
#if 1
    v4f64 x=0x1.7ffffffffffffp-1;
    v4s32 e=-1073;
    v4f64 t= ldexp(x, e);
    std::cout << std::hexfloat << t << std::endl;
    v4f64 t1=0x1p-1073, t2= 0x1p-1074;
    std::cout << t1 << std::endl << t2 << std::endl;
#else
    std::cout << std::setprecision(18) << std::scientific;

    bytes4 t0(-1.0f);
    bytes4 t1(-1.1f);
    bytes4 t2(1.0f);
    bytes4 t3(1.1f);
    std::cout << t0.s32() << std::endl
              << t1.s32() << std::endl;
    std::cout << t2.s32() << std::endl
              << t3.s32() << std::endl;

    std::cout << rsqrt(v1f32(0.0/0.0)) << std::endl;
    d_real<float> f=9.419280052185058594;
    f *= f;
    std::cout << std::hexfloat << f.h() << ' ' << f.l()
              << std::endl
              << 8.872283935546875000000000e+01f
              << std::endl
              << std::numeric_limits<float>::max()
              << std::endl;
#endif
#if 0
    bytes8 t(0, 0x3fe6a09e);
    const double d=(M_SQRT2/2) - t.f64();
    std::cout << std::setprecision(18) << t.f64() << std::endl
              << d << std::endl
              << std::hexfloat
              << d << std::endl
              << std::scientific
              << 0x1p-22 << std::endl;
    bytes8 k(0.5);
    std::cout << std::hex << k.u32h() <<  std::dec << std::endl;
    std::cout << std::hex << bytes8(1.0).u64() << std::dec << std::endl;
    std::cout << std::hex << bytes8(0.5).u64() << std::dec << std::endl;
#endif
    return 0;
}
