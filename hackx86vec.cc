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
#include <cftal/math/func_constants.h>
#include <cftal/math/impl_d_real_constants_f64.h>
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

cftal::vec<cftal::f16_t, 8>
fp16_add(cftal::vec<cftal::f16_t, 8> a,
         cftal::vec<cftal::f16_t, 8> b)
{
    using namespace cftal;
    vec<f32_t, 8> af=cvt_f16_to_f32(a);
    vec<f32_t, 8> bf=cvt_f16_to_f32(b);
    vec<f32_t, 8> rf=af+bf;
    return cvt_f32_to_f16(rf);
}

cftal::vec<cftal::f16_t, 4>
fp16_add(cftal::vec<cftal::f16_t, 4> a,
         cftal::vec<cftal::f16_t, 4> b)
{
    using namespace cftal;
    vec<f32_t, 4> af=cvt_f16_to_f32(a);
    vec<f32_t, 4> bf=cvt_f16_to_f32(b);
    vec<f32_t, 4> rf=af+bf;
    return cvt_f32_to_f16(rf);
}

cftal::vec<cftal::f16_t, 2>
fp16_add(cftal::vec<cftal::f16_t, 2> a,
         cftal::vec<cftal::f16_t, 2> b)
{
    using namespace cftal;
    vec<f32_t, 2> af=cvt_f16_to_f32(a);
    vec<f32_t, 2> bf=cvt_f16_to_f32(b);
    vec<f32_t, 2> rf=af+bf;
    return cvt_f32_to_f16(rf);
}

cftal::vec<cftal::f16_t, 1>
fp16_add(cftal::vec<cftal::f16_t, 1> a,
         cftal::vec<cftal::f16_t, 1> b)
{
#if 0
    return a + b;
#else
    using namespace cftal;
    vec<f32_t, 1> af=cvt_f16_to_f32(a);
    vec<f32_t, 1> bf=cvt_f16_to_f32(b);
    vec<f32_t, 1> rf=af+bf;
    return cvt_f32_to_f16(rf);
#endif
}


int main(int argc, char** argv)
{
    using namespace cftal;
    std::cout << std::setprecision(18) << std::scientific;

    v1f64 a=1.293872646225411094e+00;
    v1f64 b=-1.778789453749938048e+03;
    v1f64 r=pow(a, b);
    double rt=std::pow(a(), b());
    std::cout << r << std::endl
              << rt << std::endl;
#if 1
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
