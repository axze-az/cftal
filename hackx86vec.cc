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

namespace cftal {
    namespace impl {
        
        uint16_t f32_to_f16(float v);
        float f16_to_f32(uint16_t v);
        
        bool test_cvt_f32_f16();
        
        
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
cftal::impl::f32_to_f16(float v)
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
cftal::impl::f16_to_f32(uint16_t a)
{
    uint32_t sign = static_cast<uint32_t>(a & 0x8000) << 16;
    int32_t aexp = (a >> 10) & 0x1f;
    uint32_t mantissa = a & 0x3ff;

    if (aexp == 0x1f)
        return sign | 0x7f800000 | (mantissa << 13);

    if (aexp == 0) {
        if (mantissa == 0)
            return sign;
        int shift = lzcnt(mantissa) - 21;
        mantissa <<= shift;
        aexp = -shift;
    }

    uint32_t r= sign | (((aexp + 0x70) << 23) + (mantissa << 13));
    return as<float>(r);
}




int main3(int argc, char** argv)
{
    using namespace cftal;
    v1f32 t=9.419280052185058594e+00f;
    v1f32 l=exp_px2(t);
    v1f32 r=exp(t);
    std::cout << l << std::endl;
    std::cout << r << std::endl;
    return 0;
}

int main(int argc, char** argv)
{
    return main3(argc, argv);
}
