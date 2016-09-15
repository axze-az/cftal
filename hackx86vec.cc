#include <iostream>
#include <iomanip>
#include <cstddef>
#include <iterator>
#include <cmath>
#include <cftal/math_func.h>
#include <cftal/d_real.h>
#include <cftal/vec_traits.h>
#include <cftal/test/call_mpfr.h>

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
