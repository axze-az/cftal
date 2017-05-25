//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <iostream>
#include <iomanip>
#include <cftal/f16.h>

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

        template <std::size_t _N>
        bool test_cvt_f32_f16();

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
        f32_t r=ref_f16_to_f32(read_bits(f));
        f32_t t=cvt_f16_to_f32(f);
        bool c = as<uint32_t>(r)==as<uint32_t>(t);
        if (c==false) {
            std::cout << std::setprecision(16)
                    << t << " should be "
                    << r << " from "
                    << std::hex
                    << read_bits(f) << std::endl;
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
        bool c= read_bits(r) == read_bits(t);
        if (c==false) {
            std::cout << std::setprecision(16)
                      << read_bits(t) << " should be "
                      << read_bits(r) << " from "
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
        vec<f16_t, _N> df=as<vec<f16_t, _N> >(d);
        vec<float, _N> t=cvt_f16_to_f32(df);
        float vr[_N];
        mem<vec<float, _N> >::store(vr, t);
        for (uint32_t j=0; j<_N; ++j) {
            float ref=ref_f16_to_f32(a[j]);
            float rt=vr[j];
            if ( ! ((ref==rt) || (std::isnan(ref) && std::isnan(rt))) ) {
                r=false;
                std::cout << std::hex << a[j] << "--> " << rt << " should be "
                          << ref << std::endl;
                std::exit(3);
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

template <std::size_t _N>
bool cftal::test::test_cvt_f32_f16()
{
    bool r=true;
    for (uint64_t i=0; i<0x100000000u; i+=_N) {
        uint32_t a[_N];
        for (uint64_t j=0; j<_N; ++j)
            a[j] = i+j;
        vec<uint32_t, _N> du= mem<vec<uint32_t, _N> >::load(a, _N);
        vec<float, _N> d= as<vec<float, _N> >(du);
        vec<f16_t, _N> t= cvt_f32_to_f16(d);

        f16_t vr[_N];
        mem<vec<f16_t, _N> >::store(vr, t);
        for (uint32_t j=0; j<_N; ++j) {
            float faj=as<float>(a[j]);
            f16_t ref=f16_t(ref_f32_to_f16(faj));
            f16_t rt=vr[j];
            if (read_bits(ref) != read_bits(rt)) {
                r=false;
                std::cout << std::hex << a[j] << " --> "
                          << read_bits(rt) << " should be "
                          << read_bits(ref) << std::endl;
                std::exit(3);
            }
        }
    }
    std::cout << std::defaultfloat;
    std::cout << "vec " << _N << " f32 --> f16 ";
    if (r == true)
        std::cout << "passed\n";
    else
        std::cout << "failed\n";
    return r;
}

#if 0
int main(int argc, char** argv)
{
    using namespace cftal;
    uint32_t s=0x38800000;
    float sf=as<float>(s);
    vec<uint32_t, 1> vs(s);
    vec<f32_t, 1> vf32=as<vec<f32_t, 1> >(vs);
    vec<f16_t, 1> vd=cvt_f32_to_f16(vf32);
    f16_t ref=f16_t(test::ref_f32_to_f16(sf));
    std::cout << std::hex;
    std::cout << sf  << ' ' << vd().v() << ' ' << ref.v() << std::endl;
    return 0;
}

#else
int main(int argc, char** argv)
{
    // return main3(argc, argv);
    bool r=true;
    // r &=cftal::test::test_ref_cvt_f16_f32();
    // r &=cftal::test::test_ref_cvt_f32_f16();
#if 0
    r &=cftal::test::test_f16_to_f32();
    r &=cftal::test::test_f32_to_f16();
    r &= cftal::test::test_cvt_f16_f32<1>();
    r &= cftal::test::test_cvt_f16_f32<2>();
#endif
    r &= cftal::test::test_cvt_f16_f32<4>();
#if 1
    r &= cftal::test::test_cvt_f16_f32<8>();
    r &= cftal::test::test_cvt_f16_f32<16>();
    r &= cftal::test::test_cvt_f16_f32<32>();
    r &= cftal::test::test_cvt_f32_f16<1>();
    r &= cftal::test::test_cvt_f32_f16<2>();
    r &= cftal::test::test_cvt_f32_f16<4>();
    r &= cftal::test::test_cvt_f32_f16<8>();
    r &= cftal::test::test_cvt_f32_f16<16>();
    r &= cftal::test::test_cvt_f32_f16<32>();
#endif
    return r==true ? 0 : 1;

}
#endif
