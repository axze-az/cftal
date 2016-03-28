#include <iostream>
#include <iomanip>
#include <cstddef>
#include <iterator>
#include <cmath>
#include <cftal/vec.h>
#include <cftal/math_func.h>
#include <cftal/d_real.h>
#include <cftal/t_real.h>
#include <cftal/vec_traits.h>


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
            _T a=agm<10>(std::make_pair(1.0, inv_s)).first;
            a*=2.0;
            d_real<_T> t= ctbl::m_pi.h()/a - ctbl::m_ln2.h()* p;
            return t.h();
        }

    }
}

int main(int argc, char** argv)
{
    using namespace cftal;
#if 1
    std::cout << std::hexfloat << std::endl;
    std::cout << bytes8(0x0, 0x40862e42)._f64 << std::endl;
    std::cout << bytes8(0x0, 0x3ff00000)._f64 << std::endl;
    std::cout << bytes8(0x0, (0x3ff+2043/2)<<20)._f64 << std::endl;
#else
    std::cout << std::hex;
    double t=0x1p51-1.0;
    std::cout << bytes8(t)._u64 << std::endl;
    double t1=t+0x1p52+0x1p51;
    std::cout << bytes8(t1)._u64 << std::endl;
    std::cout << bytes8(t1)._u32[0] << std::endl;
    double t2=-t+0x1p52+0x1p51;
    std::cout << bytes8(t2)._u64 << std::endl;
    std::cout << bytes8(t2)._u32[0] << std::endl;

    std::cout << std::hexfloat << std::endl;
    std::cout << bytes8(0x1ul)._f64 << std::endl;
    std::cout << 0x1p-1074 << std::endl;
    std::cout << bytes8(0x1ul)._f64 * bytes8(0x1p53)._f64 << std::endl;


    std::cout << bytes8(0x1ul<<53)._f64 << std::endl;

    double Log2h= 0xb.17217f8p-16 ;
    double Log2l= -0x2.e308654361c4cp-48 ;


    std::cout << bytes8(Log2h)._u64 << std::endl;
    std::cout << bytes8(Log2l)._u64 << std::endl;

    std::cout << bytes8(+6.9314718036912381649017e-01)._u64 << std::endl;
    std::cout << bytes8(+6.9314718036912381649017e-01)._f64 << std::endl;
    std::cout << bytes8(+1.9082149292705877000220e-10)._u64 << std::endl;
    std::cout << bytes8(+1.9082149292705877000220e-10)._f64 << std::endl;

    std::cout << bytes8(1.57079632673412561417e+00)._u64 << std::endl;
    // v1f32 r=ldexp(v1f32(0x1.2352cf807b7dfp-503), v1s32(-1076));
    // double rd=std::ldexp(0x1.2352cf807b7dfp-503, -1076);
    // v1f32 r=ldexp(v1f32(0x1.a2e184p-127f), v1s32(-22));
    // float rd=std::ldexp(0x1.a2e184p-127f, -22);
    // v1f32 r=ldexp(v1f32(0x1.0p-127f), v1s32(-1));
    // float rd=std::ldexp(0x1.0p-127f, -1);
    // v1f64 r=ldexp(v1f64(0x1.a2e184p-1023), v1s32(+1023-1075));
    // double rd=std::ldexp(0x1.a2e184p-1023, +1023-1075);
    // std::cout << std::setprecision(22);
    // std::cout << std::hexfloat << r << std::endl;
    // std::cout << std::hexfloat << rd << std::endl;
    // std::cout << std::numeric_limits<double>::min() << std::endl;
    // std::cout << std::sqrt(std::numeric_limits<double>::min()) << std::endl;
#endif
    return 0;
}
