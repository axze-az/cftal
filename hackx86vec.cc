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
    using namespace cftal;
    vec<f32_t, 1> af=cvt_f16_to_f32(a);
    vec<f32_t, 1> bf=cvt_f16_to_f32(b);
    vec<f32_t, 1> rf=af+bf;
    return cvt_f32_to_f16(rf);
}


int main(int argc, char** argv)
{
    using namespace cftal;

    // 1/3 = x/2^16
    // x=2^16/3;

    const int32_t shift_1_3=13;
    const int32_t fac_1_3=((1<<shift_1_3)+2)/3;

    std::cout << std::hex << "const int32_t shift= 0x" << shift_1_3 << ";\n";
    std::cout << std::hex << "const int32_t fac_1_3= 0x" << fac_1_3 << ";\n";
    std::cout << std::dec;

    for (int32_t i=-1024-53; i<1024+1; ++i) {
        // round down division
        int32_t q=i/3;
        if (i<0 && (i%3))
            --q;
        // int32_t p=((i*fac_1_3)>>shift_1_3) - (i>>31);
        int32_t p = (((i+3*1024)*fac_1_3)>>shift_1_3) - 1024;
        int32_t r=i-3*p;
        if (p != q) {
            std::cout << "i=" << i << " q=" << q << " qp="
                      << p << " r=" << r << std::endl;
        }
    }
}
