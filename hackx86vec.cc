//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <iterator>
#include <cmath>
#include <cftal/math/func.h>
#include <cftal/d_real.h>
#include <cftal/vec_traits.h>
#include <cftal/test/call_mpfr.h>
#include <cftal/bitops.h>
#include <cftal/vec.h>
#include <cftal/constants.h>

namespace cftal {

    namespace test {

        uint16_t ref_f32_to_f16(float v);
        float ref_f16_to_f32(uint16_t v);

        bool test_ref_cvt_f32_f16();
        bool test_ref_cvt_f16_f32();

        bool test_f16_to_f32();
        bool test_f32_to_f16();

        template <std::size_t _N>
        bool test_cvt_f16_f32();

    }

    // a 16 bit floating point number
    class f16_t {
    public:
        constexpr explicit f16_t(uint16_t f) : _f(f) {}
        constexpr uint16_t v() const { return _f; }
    private:
        uint16_t _f;
    };


    // conversion of a f32 to a f16 value
    f16_t
    cvt_f32_to_f16(f32_t f);
    // conversion of a f16 value to a f16 value
    f32_t
    cvt_f16_to_f32(f16_t f);


    // conversion of a f32 vector to a f16 vector
    template <std::size_t _N>
    vec<uint16_t, _N>
    f32_to_f16(const vec<float, _N>& s);

    // conversion of a f16 vector to a f32 vector
    template <std::size_t _N>
    vec<float, _N>
    f16_to_f32(const vec<uint16_t, _N>& s);


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
            _T a=agm<10>(std::make_pair(1.0, inv_s)).first;
            a*=2.0;
            d_real<_T> t= ctbl::m_pi.h()/a - ctbl::m_ln2.h()* p;
            return t.h();
        }


    }

}

cftal::uint16_t
cftal::test::ref_f32_to_f16(float v)
{
    uint32_t a= as<uint32_t>(v);
    uint16_t sign = (a >> 16) & 0x8000;
    int32_t aexp = (a >> 23) & 0xff;
    uint32_t mantissa = a & 0x007fffff;
    uint32_t mask;
    uint32_t increment;

    if (aexp == 0xff) {
        if (mantissa == 0)
            return sign | 0x7c00;   /* Infinity.  */
        /* Remaining cases are NaNs.  Convert SNaN to QNaN.  */
        return sign | 0x7e00 | (mantissa >> 13);
    }

    if (aexp == 0 && mantissa == 0)
        return sign;

    aexp -= 127;

    /* Decimal point between bits 22 and 23.  */
    mantissa |= 0x00800000;
    if (aexp < -14) {
        mask = 0x00ffffff;
        if (aexp >= -25)
            mask >>= 25 + aexp;
    } else {
        mask = 0x00001fff;
    }
    /* Round.  */
    if (mantissa & mask) {
        increment = (mask + 1) >> 1;
        if ((mantissa & mask) == increment)
            increment = mantissa & (increment << 1);
        mantissa += increment;
        if (mantissa >= 0x01000000) {
            mantissa >>= 1;
            aexp++;
        }
    }
    if (aexp > 15)
        return sign | 0x7c00;
    if (aexp < -24)
        return sign;
    if (aexp < -14) {
        mantissa >>= -14 - aexp;
        aexp = -14;
    }
    /* We leave the leading 1 in the mantissa, and subtract one
        from the exponent bias to compensate.  */
    return sign | (((aexp + 14) << 10) + (mantissa >> 13));
}


float
cftal::test::ref_f16_to_f32(uint16_t a)
{
    uint32_t sign = static_cast<uint32_t>(a & 0x8000) << 16;
    int32_t aexp = (uint32_t(a) >> 10) & 0x1f;
    uint32_t mantissa = a & 0x3ff;

    if (aexp == 0x1f)
        return as<float>(sign | 0x7f800000 | (mantissa << 13));

    if (aexp == 0) {
        if (mantissa == 0)
            return as<float>(sign);
        int shift = lzcnt(mantissa) - 21;
        mantissa <<= shift;
        aexp = -shift;
    }

    uint32_t r= sign | (((aexp + 0x70) << 23) + (mantissa << 13));
    return as<float>(r);
}


cftal::f32_t
cftal::cvt_f16_to_f32(f16_t t)
{
    uint32_t tt= t.v();
    const uint32_t exp_msk = 0x7c00 << 13;
    uint32_t r= (tt & 0x7fff) << 13;
    uint32_t s= (tt & 0x8000) << 16;
    uint32_t e= exp_msk & r;
    r += (127-15) << 23; // adust the exponent
    if (e == exp_msk) {
        // maximum exponent? inf/NaNs
        r += (128-16) << 23;
    } else if (e == 0) {
        // denormal numbers
        const f32_t magic = as<f32_t>(113 << 23);
        r += 1<<23;
        r = as<uint32_t>(as<f32_t>(r) - magic);
    }
    r |= s;
    return as<f32_t>(r);
}

cftal::f16_t
cftal::cvt_f32_to_f16(f32_t ff)
{
    const f32_t inf= std::numeric_limits<float>::infinity();
    const uint32_t inf_u= as<uint32_t>(inf);
    const uint32_t max_f16_u = (127+16)<<23;
    const f32_t denom_magic= 0.5f;

    const uint32_t sgn_msk = 0x80000000u;

    uint32_t f=as<uint32_t>(ff);
    uint32_t s=(f & sgn_msk);
    f ^= s;
    s >>= 16;
    if (f >= max_f16_u) {
        f = f > inf_u ?
            0x7e00 | ((f & 0x7fffff)>>13) : 0x7c00;
    } else {
        if (f < (113<<23)) {
            f = as<uint32_t>(as<f32_t>(f) + denom_magic);
            f = f - as<uint32_t>(denom_magic);
        } else {
            uint32_t mant_odd= (f>>13) & 1;
            f += (uint32_t(15-127)<<23)+ 0xfff;
            f += mant_odd;
            f >>=13;
        }
    }
    return f16_t(f|s);
}



template <std::size_t _N>
cftal::vec<cftal::uint16_t, _N>
cftal::f32_to_f16(const vec<float, _N> &sf)
{
    using uv_t = vec<uint32_t, _N>;
    uv_t s = as<uv_t>(sf);
    uv_t ue = (s >> exp_shift_f32) & uv_t(exp_msk_f32);
    using sv_t = vec<int32_t, _N>;
    sv_t e = as<sv_t>(ue) - sv_t(bias_f32);

    using um_t = typename uv_t::mask_type;

    // sign of result:
    uv_t sgn= (s >> 16) & 0x8000;

    // correct exp/mantissas too small for normal f16 numbers
    // numbers with exponents smaller than 2^-25 are flushed to
    // zero, normal numbers have an exponent above -14
    um_t is_ftz = ue < uv_t(-25+bias_f32);
    // this contains also nan and infs
    um_t is_norm= ue > uv_t(-13+bias_f32);



}

template <std::size_t _N>
cftal::vec<float, _N>
cftal::f16_to_f32(const vec<uint16_t, _N> &s)
{
    const vec<uint16_t, _N> z(0);
    using uv_t = vec<uint32_t, _N>;
    uv_t sl= as<uv_t>(combine_even_odd(s, z));
    uv_t sign = (sl << 16) & uv_t(sign_f32_msk::v.u32());
    uv_t mant = sl & uv_t(0x3ff);
    uv_t ue= (sl >> 10) & uv_t(0x1f);
    // sv_t e = as<sv_t>(ue);

    using um_t = typename uv_t::mask_type;

    // shifted mantissa
    uv_t mant_s = mant << 13;
    // e  == 0x1f --> inf or NaN
    um_t inf_nan = ue == uv_t(0x1f);
    uv_t f_inf_nan = sign | uv_t(exp_f32_msk::v.u32()) | mant_s;
    // default normal value:
    uv_t f= sign | ((ue + 0x70) << exp_shift_f32) | mant_s;
    // combine inf/nan and normal values
    f = select(inf_nan, f_inf_nan, f);

    um_t zero_or_sub_nor = ue == uv_t(0x0);
    if (any_of(zero_or_sub_nor)) {
        // combine zero values
        um_t zero = um_t(mant == 0) & zero_or_sub_nor;
        f = select(zero, sign, f);
        // e  == 0 & mant !=0 --> subnormal
        um_t sub_nor = um_t(mant != 0) & zero_or_sub_nor;
        // std::cout << ue << std::endl;
        // std::cout << mant << ' ' << sub_nor << std::endl;
        if (any_of(sub_nor)) {
            // the f16 hidden bit
            const uv_t dot = uv_t(0x400);
            // set the hidden bit for not sub normal components
            uv_t dm= select(sub_nor, mant, dot);
            // ue + the bias shift to reach f32 exponent with bias
            uv_t due= ue + (0x70 + 1);
            // shift mantissa left until we have normalized all numbers
            // to 1.xxxx and subtract for every step one from the exponent
            while (1) {
                um_t is_norm = (uv_t(dm & dot) == dot);
                if (all_of(is_norm))
                    break;
                dm = select(is_norm, dm, uv_t(dm << 1));
                due= select(is_norm, due, uv_t(due - 1));
            }
            // clear the hidden bit
            dm &= 0x3ff;
            // and align the mantissa
            dm <<=13;
            uv_t f_sub_nor = sign | (due << exp_shift_f32) | dm;
            f = select(sub_nor, f_sub_nor, f);
        }
    }
    return as<vec<float, _N> >(f);
}

namespace cftal {
    namespace test {
        template <int i>
        bool
        check_elem_x(v8f32 v, float r, uint16_t s);

        template <int i>
        bool
        check_elem_x(v8u16 v, uint16_t r);
    }
}

template <int i>
bool
cftal::test::check_elem_x(v8f32 v, float r, uint16_t s)
{
    float t=extract<i>(v);
    bool c = (t==r) || (std::isnan(t) && std::isnan(r));
    if (c==false) {
        std::cout << std::setprecision(16)
                  << t << " should be "
                  << r << " from " << std::hex << s << std::endl;
    }
    return c;
}

template <int i>
bool
cftal::test::check_elem_x(v8u16 v, uint16_t r)
{
    uint16_t t=extract<i>(v);
    return (t==r);
}

bool
cftal::test::test_ref_cvt_f16_f32()
{
#if defined (__F16C__)
    // _mm_cvtph_ps
    // _mm_cvtps_ph
    bool r=true;
    for (uint32_t i=0; i<0x10000u; i+=8) {
        uint16_t t=i;
        v8u16 s={uint16_t(t+0), uint16_t(t+1), uint16_t(t+2), uint16_t(t+3),
                 uint16_t(t+4), uint16_t(t+5), uint16_t(t+6), uint16_t(t+7)};
        v8f32 d=_mm256_cvtph_ps(s());
        float dr=ref_f16_to_f32(i);
        r &= check_elem_x<0>(d, dr, i);
        dr=ref_f16_to_f32(i+1);
        r &= check_elem_x<1>(d, dr, i+1);
        dr=ref_f16_to_f32(i+2);
        r &= check_elem_x<2>(d, dr, i+2);
        dr=ref_f16_to_f32(i+3);
        r &= check_elem_x<3>(d, dr, i+3);
        dr=ref_f16_to_f32(i+4);
        r &= check_elem_x<4>(d, dr, i+4);
        dr=ref_f16_to_f32(i+5);
        r &= check_elem_x<5>(d, dr, i+5);
        dr=ref_f16_to_f32(i+6);
        r &= check_elem_x<6>(d, dr, i+6);
        dr=ref_f16_to_f32(i+7);
        r &= check_elem_x<7>(d, dr, i+7);
    }
    std::cout << "f16 --> f32 ";
    if (r == true)
        std::cout << "passed\n";
    else
        std::cout << "failed\n";
    return r;
#else
    return true;
#endif
}

bool
cftal::test::test_f16_to_f32()
{
    bool rc=true;
    for (uint32_t i=0; i<0x10000u; ++i) {
        f16_t f(i);
        f32_t r=ref_f16_to_f32(f.v());
        f32_t t=cvt_f16_to_f32(f);
        bool c = as<uint32_t>(r)==as<uint32_t>(t);
        if (c==false) {
            std::cout << std::setprecision(16)
                    << t << " should be "
                    << r << " from " << std::hex << f.v() << std::endl;
        }
        rc &= c;
    }
    std::cout << "f16 --> f32 ";
    if (rc == true)
        std::cout << "passed\n";
    else
        std::cout << "failed\n";
    return rc;
}

bool
cftal::test::test_f32_to_f16()
{
    bool rc=true;
    for (uint64_t i=0; i<0x100000000u; ++i) {
        uint32_t j=i;
        f32_t s=as<float>(j);
        f16_t r(ref_f32_to_f16(s));
        f16_t t=cvt_f32_to_f16(s);
        bool c= r.v() == t.v();
        if (c==false) {
            std::cout << std::setprecision(16)
                      << t.v() << " should be "
                      << r.v() << " from "
                      << std::hex << s << std::endl;
        }
        rc &=c;
    }
    std::cout << "f32 --> f16 ";
    if (rc == true)
        std::cout << "passed\n";
    else
        std::cout << "failed\n";
    return rc;
}

bool
cftal::test::test_ref_cvt_f32_f16()
{
#if defined (__F16C__)
    // test code for processors with f16c
    bool r=true;
    for (uint64_t i=0; i<0x100000000u; i+=8) {
        if ((i & 0xFFFFFF8) == 0xFFFFFF8)
            std::cout << '.' << std::flush;
        uint32_t t=i;
        v8u32 s={uint32_t(t+0), uint32_t(t+1), uint32_t(t+2), uint32_t(t+3),
                 uint32_t(t+4), uint32_t(t+5), uint32_t(t+6), uint32_t(t+7)};
        v8f32 sf=as<v8f32>(s);
        v8u16 d=_mm256_cvtps_ph(sf(), 0);
        uint16_t dr=ref_f32_to_f16(as<float>(t));
        r &= check_elem_x<0>(d, dr);
        dr=ref_f32_to_f16(as<float>(t+1));
        r &= check_elem_x<1>(d, dr);
        dr=ref_f32_to_f16(as<float>(t+2));
        r &= check_elem_x<2>(d, dr);
        dr=ref_f32_to_f16(as<float>(t+3));
        r &= check_elem_x<3>(d, dr);
        dr=ref_f32_to_f16(as<float>(t+4));
        r &= check_elem_x<4>(d, dr);
        dr=ref_f32_to_f16(as<float>(t+5));
        r &= check_elem_x<5>(d, dr);
        dr=ref_f32_to_f16(as<float>(t+6));
        r &= check_elem_x<6>(d, dr);
        dr=ref_f32_to_f16(as<float>(t+7));
        r &= check_elem_x<7>(d, dr);
    }
    std::cout << "f32 --> f16 ";
    if (r == true)
        std::cout << "passed\n";
    else
        std::cout << "failed\n";
    return r;
#else
    return true;
#endif
}

template <std::size_t _N>
bool cftal::test::test_cvt_f16_f32()
{
    bool r=true;
    std::cout << std::hexfloat;
    for (uint32_t i=0; i<0x10000u; i+=_N) {
        uint16_t a[_N];
        for (uint32_t j=0; j<_N; ++j)
            a[j] = i+j;
        vec<uint16_t, _N> d= mem<vec<uint16_t, _N> >::load(a, _N);
        vec<float, _N> t=f16_to_f32(d);
        float vr[_N];
        mem<vec<float, _N> >::store(vr, t);
        for (uint32_t j=0; j<_N; ++j) {
            float ref=ref_f16_to_f32(a[j]);
            float rt=vr[j];
            if ( ! ((ref==rt) || (std::isnan(ref) && std::isnan(rt))) ) {
                r=false;
                std::cout << std::hex << a[j] << "--> " << rt << " should be "
                          << ref << std::endl;
            }
        }
    }
    std::cout << std::defaultfloat;
    std::cout << "vec " << _N << " f16 --> f32 ";
    if (r == true)
        std::cout << "passed\n";
    else
        std::cout << "failed\n";
    return r;
}


int main1(int argc, char** argv)
{
    using namespace cftal;
    uint16_t s=32678;
    vec<uint16_t, 1> vs(s);
    vec<float, 1> vd=f16_to_f32(vs);
    float ref=test::ref_f16_to_f32(s);
    std::cout << vs  << ' ' << vd << ' ' << ref << std::endl;
    return 0;
}

int main(int argc, char** argv)
{
    // return main3(argc, argv);
    bool r=true;
    // r &=cftal::test::test_ref_cvt_f16_f32();
    // r &=cftal::test::test_ref_cvt_f32_f16();
    r &=cftal::test::test_f16_to_f32();
    r &=cftal::test::test_f32_to_f16();
    return r==true ? 0 : 1;
#if 0
    bool r=true;
    r &= cftal::test::test_cvt_f16_f32<1>();
    r &= cftal::test::test_cvt_f16_f32<2>();
    r &= cftal::test::test_cvt_f16_f32<4>();
    r &= cftal::test::test_cvt_f16_f32<8>();
    r &= cftal::test::test_cvt_f16_f32<16>();
    r &= cftal::test::test_cvt_f16_f32<32>();
    return true;
#endif
}
