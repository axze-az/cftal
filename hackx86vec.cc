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
    using vf_type = vec<double, 1>;
    using vi_type = vec<int32_t, 1>;
    using vf_traits = cftal::math::func_traits<vf_type, vi_type>;
    vf_type r= cftal::math::func<double, vf_traits>::expxx_k(xc, vf_type(-1));
    // using fc_t = math::func_constants<double>;
    // r= select(xx <= fc_t::exp_lo_zero, vf_type(0), r);
    return r();
#else
    // exp(-x*x):
    // log(exp(-x*x)) = -x*x
    // x = h + l;
    // x*x = (h+l)*(h+l) = h^2 + 2*h*l + l^ 2
    //
#if 0
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
    using vf_type = vec<double, 1>;
    using vli_type = vec<uint64_t, 1>;
    vf_type s=-1.0;
    vf_type x=abs(vf_type(xc));
    vli_type xi=as<vli_type>(x);
    xi = xi & vli_type(0xFFFFFFFFF8000000ULL);
    vf_type h= as<vf_type>(xi);
    vf_type l= x-h;

    vf_type uh= h*h;
    vf_type ul= 2*h*l + l*l;
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
#endif
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

int main1(int argc, char** argv)
{
    using namespace cftal;

    std::cout << std::setprecision(18) << std::scientific;
    const int64_t stp=1600000;
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

int main2(int argc, char** argv)
{
    using namespace cftal;
    v2f64 t2={0x1.4c31d59534535p+9};
    v1f64 t1={0x1.4c31d59534535p+9};

    std::pair<double, double> ti;
    double tr=test::call_mpfr::func(t1(), mpfr_expm1, &ti);
    
    v2f64 e2=expm1(t2);
    v1f64 e1=expm1(t1);
    std::cout << std::hexfloat;
    std::cout << e2 << std::endl;
    std::cout << e1 << std::endl;
    std::cout << tr << std::endl;
    std::cout << ti.first << ' ' << ti.second << std::endl;
    
    return 0;
}


int main(int argc, char** argv)
{
    return main2(argc, argv);
}
