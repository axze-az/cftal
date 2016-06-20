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

        struct v2 {
            union {
                float _l[2];
                double _d;
            } _u;
        };

        // exp(-x*x)
        // exp(-x*x) = exp(-z*z) * exp(-2*z*m) * exp(-m*m)
        // where z 
        double expmxx(double x);

        double ref_expmxx(double x);
        
    }
    
}

double
cftal::impl::expmxx(double xc)
{
#if 1
    using vf_type=vec<double, 1>;
    vf_type s=-1.0;
    vf_type x=abs(vf_type(xc));
    const vf_type ML=128.0;
    const vf_type ML_INV=1.0/ML;

    const vf_type MS=512.0;
    const vf_type MS_INV=1.0/MS;

    vf_type M = select(x > 13, ML, MS);
    vf_type MINV = select(x > 13, ML_INV, MS_INV);
    
    vf_type m=MINV*rint(vf_type(M*x));
    vf_type f=x-m;
    vf_type uh=m*m;
    vf_type ul= 2*m*f + f*f;
    vf_type sgn=copysign(vf_type(1.0), s);
    uh *= sgn;
    ul *= sgn;
    vf_type eh=exp(uh);
    vf_type el=exp(ul);
    vf_type r=eh*el;
    vf_type xx=xc*xc*sgn;
    using fc_t = math::func_constants<double>;
    r= select(xx <= fc_t::exp_lo_zero, vf_type(0), r);
    return r();
#else
    using namespace std;
    double x = std::abs(xc);
    double z = std::rint(x);
    double m = x - z;
    if (m > 0.5) {
        z += 1.0;
        m -= 1.0;
    }
    using vf_type = cftal::vec<double, 1>;
    double exp_zz= ref_expmxx(z);
    double exp_2zm= exp(vf_type(-2*z*m))();
    double exp_mm= exp(vf_type(-m*m))();
    double r=exp_zz * exp_2zm * exp_mm;
    return r;
#endif
}

double
cftal::impl::ref_expmxx(double xa)
{
    using mp_t=cftal::test::mpfr_real<1024>;
    mp_t x=xa;
    x *= x;
    x = -x;
    mp_t r= exp(x);
    double dr(r);
    return dr;
}

int main(int argc, char** argv)
{
    using namespace cftal;

    std::cout << std::setprecision(18) << std::scientific;
    const int64_t stp=10000;
    const int64_t cnt=27*stp;
    int errs=0;
    double max_err=0;
    for (int i=0; i<cnt; ++i) {
        double x=double(i)/stp;
        double z1, z2;
        if ((i & 0xffff)==0xffff)
            std::cout << '.' << std::flush;
        z1 = impl::ref_expmxx(x);
        z2 = impl::expmxx(x);
        double err=fabs(z2-z1)/((z1+z2)*0.5);
        bool e=!isnan(err) && err!=0;
        if (e && x <= 26.615717) {
            ++errs;
            max_err = std::max(fabs(err), max_err);
            #if 0
            double e2=z2/z1-1;
            std::cout // << std::hexfloat
                      << -x*x
                      << std::scientific 
                      << "\n";
            std::cout << x << " " << z1 << " "
                      << std::hexfloat
                      << e2
                      << "\n"
                      << std::scientific 
                      << x << " " << z2 << " "
                      << std::hexfloat
                      << err
                      << std::scientific
                      << std::endl;
            #endif
        }
    }
    std::cout << "\nerrors: " << errs << std::endl;
    std::cout << "max rel_err: "
              << std::hexfloat
              << max_err
              << std::scientific
              << " "
              << max_err
              << std::endl;
    return 0;
}
