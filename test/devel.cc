//
// Copyright (C) 2010-2025 Axel Zeuner
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
//
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <limits>
#include <cftal/vec.h>
#include <cftal/d_real.h>
#include <cftal/math/func_traits.h>
#include <cftal/math/vec_func_traits_f64.h>
#include <cftal/test/f32_f64.h>
#include <cftal/test/call_mpfr.h>

namespace cftal { namespace devel {

    template <typename _T>
    uint32_t
    calc_m_kahan(int nm1, _T x, _T rcp_eps);

    template <typename _T, size_t _N>
    vec<int, _N>
    calc_m_kahan(int nm1, arg_t<vec<_T, _N> >  x, _T rcp_eps);

    template <typename _T>
    _T
    bessel_recurrence_forward(int nm1,
                              _T x,
                              _T j0x,
                              _T j1x);

    template <typename _T>
    _T
    bessel_recurrence_backward(int nm1, _T x);

    double
    bessel_recurrence_backward(int nm1, double x);

    double bessel_j(int n, double x);
}}


template <typename _T>
_T
cftal::devel::
bessel_recurrence_forward(int nm1, _T x, _T j0x, _T j1x)
{
    switch (nm1) {
    case -1:
        return j0x;
    case 0:
        return j1x;
    default:
        break;
    }
    _T jnm1=j0x;
    _T jn=j1x;
    _T rcp_x= 1.0/x;
    for (int i=1; i<=nm1; ++i) {
        _T tmp = jn;
        // _T t= (i+i)*rcp_x;
        jn= jn* rcp_x * (i+i) - jnm1;
        // jn= (jn* _T(i+i))*rcp_x - jnm1;
        jnm1= tmp;
    }
    // std::cout << ": " << jn << std::endl;
    return jn;
}

template <typename _T>
cftal::uint32_t
cftal::devel::
calc_m_kahan(int nm1, _T x, _T rcp_eps)
{
    using std::max;
    using std::rint;
    uint32_t k= max(static_cast<uint32_t>(nm1+1),
                    static_cast<uint32_t>(rint(x)));
    const auto beta=_T(1.0);
    _T yk = 0.0, ykp1=beta;
    _T _2_x= _T(2.0)/x;
    uint32_t m=k+1;
    _T md=static_cast<_T>(m);
    for (;m<std::numeric_limits<uint32_t>::max(); ++m) {
        _T t= md * _2_x * ykp1 - yk;
        yk   = ykp1;
        ykp1 = t;
        // because beta == 1.0
        if (ykp1 >= rcp_eps)
            break;
        md += 1.0;
    }
    // std::cout << ykp1 << std::endl;
    return m;
}

template <typename _R, cftal::size_t _N>
cftal::vec<int, _N>
cftal::devel::
calc_m_kahan(int nm1, arg_t<vec<_R, _N> > x, _R rcp_eps)
{
    using std::max;
    using std::rint;

    using _T = math::func_traits<vec<_R, _N>, vec<int32_t, _N> >;

    // using vf_type = typename _T::vf_type;
    using vi_type = typename _T::vi_type;

    vi_type xi=_T::cvt_f_to_i(x);
    vi_type k= max(nm1+1, xi);
    const auto beta=_R(1.0);
    _R yk = 0.0, ykp1=beta;
    _R _2_x= _R(2.0)/x;
    int m=k+1;
    _R md=static_cast<_R>(m);
    for (;m<std::numeric_limits<int>::max(); ++m) {
        _R t= md * _2_x * ykp1 - yk;
        yk   = ykp1;
        ykp1 = t;
        // because beta == 1.0
        if (ykp1 >= rcp_eps)
            break;
        md += 1.0;
    }
    // std::cout << ykp1 << std::endl;
    return m;
}

template <typename _T>
_T
cftal::devel::bessel_recurrence_backward(int nm1, _T x)
{
    using v_t = d_real<_T>;
    using ops=d_real_ops<_T, d_real_traits<_T>::fma>;
    uint32_t _N=calc_m_kahan(nm1, x, 0x1.0p52);
    // std::cout << "jn(" << nm1+1 << ", " << x << ") _N=" << _N  <<'\n';

    v_t rec_x;
    ops::rcp12(rec_x[0], rec_x[1], x);
    v_t yn=_T(1.0);
    v_t ynp1=_T(0.0);
    v_t rn=ynp1;
    v_t norm = _T(0.0);
    _T vi(2*_N);
    for (uint32_t i=_N; i > 0; --i) {
        v_t ynm1=(vi*rec_x) * yn - ynp1;
        if ((i&1)==0) {
            v_t yn2=mul_pwr2(yn, 2.0);
            norm += yn2;
        }
        ynp1 = yn;
        yn = ynm1;
        vi -= _T(2.0);
        if (yn[0] > _T(0x1p512)) {
            // scale if required
            ynp1 = mul_pwr2(ynp1, 0x1p-512);
            norm = mul_pwr2(norm, 0x1p-512);
            rn = mul_pwr2(rn, 0x1p-512);
            yn = mul_pwr2(yn, 0x1p-512);
        }
        if (i == static_cast<uint32_t>(nm1+2)) {
            rn=yn;
        }
    }
    norm += yn;
    _T jn;
    ops::div21(jn, rn[0], rn[1], norm[0], norm[1]);
    return jn;
}

double
cftal::devel::bessel_recurrence_backward(int nm1, double x)
{
    using v_t = double;
    uint32_t _N=calc_m_kahan(nm1, x, 0x1.0p75);
    // std::cout << "jn(" << nm1+1 << ", " << x << ") _N=" << _N  <<'\n';
    v_t rec_x=1.0/x;
    v_t yn=1.0;
    v_t ynp1=0.0;
    v_t rn=ynp1;
    v_t norm =0.0;
    double vi(2*_N);
    for (uint32_t i=_N; i > 0; --i) {
        v_t ynm1=(vi*rec_x) * yn - ynp1;
        if ((i&1)==0) {
            norm += 2.0*yn;
        }
        ynp1 = yn;
        yn = ynm1;
        vi -= 2.0;
        if (yn> 0x1p512) {
            // scale if required
            ynp1 *= 0x1p-512;
            norm *= 0x1p-512;
            rn *= 0x1p-512;
            yn *= 0x1p-512;
        }
        if (i == static_cast<uint32_t>(nm1+2)) {
            rn=yn;
        }
    }
    norm += yn;
    v_t jn=rn/norm;
    return jn;
}

// j(n-1, x) = 2*n/x * j(n, x) - j(n+1, x)
// 1 = j(0, x) + 2*j(2, x) + 2 * j(4, x) + ....
double
cftal::devel::
bessel_j(int n, double x)
{
    int nm1=n-1;
#if 0
    if (n <= x /* && x > 126.0 */ ) {
        return bessel_recurrence_forward(nm1, x, ::j0(x), ::j1(x));
    }
#endif
#if 1
    return bessel_recurrence_backward<double>(nm1, x);
#else
    using v_t = d_real<double>;
    size_t _N=calc_m_kahan(nm1, x, 0x1.0p72);
    std::cout << "jn(" << n << ", " << x << ") _N=" << _N  <<'\n';
    std::vector<v_t> vj(_N+2, v_t(0.0));
    v_t _rec_x=v_t(1.0)/x;
    vj[_N] = 1.0;
    vj[_N+1] = 0.0;
    v_t norm=0.0;
    v_t vi(2*_N);
    for (ssize_t i=_N; i > 0; --i) {
        v_t vj_im1=(vi)*_rec_x * vj[i] - vj[i+1];
        if (i && (i&1)==0) {
            norm += 2.0*vj[i];
        }
        vj[i-1] = vj_im1;
        vi -= 2.0;
    }
    norm += vj[0];
    // for (size_t i=0; i<vj.size(); ++i) {
    //     std::cout << std::setw(2) << i << ' ' << vj[i] << std::endl;
    // }
    v_t jn=vj[n]/norm;
    return jn[0];
#endif
    // return jn;
}

using namespace cftal;

int main(int argc, char** argv)
{
    using namespace cftal;
    using namespace cftal::devel;
    using namespace cftal::test;

    bool verbose=false;

    if (argc > 1) {
        std::string_view argv1=argv[1];
        using namespace std::string_view_literals;
        if (argv1=="--verbose"sv) {
            verbose=true;
        }
    }

    std::cout << std::scientific << std::setprecision(18);
    // const int n=0; // avoid compile time evaluation of jn)x, x)
    for (int n=0; n<2000; ++n) {
        const double xd=128.0;
        for (double x=1.0/xd; x<256; x+=1.0/xd) {
            double jn= bessel_j(n, x);
            double jn_mpfr, jn_glibc;
            std::pair<double, double> ulp1_interval;
            switch (n) {
            case 0:
                jn_mpfr=call_mpfr::func(x, mpfr_j0, &ulp1_interval);
                jn_glibc=::j0(x);
                break;
            case 1:
                jn_mpfr=call_mpfr::func(x, mpfr_j1, &ulp1_interval);
                jn_glibc=::j1(x);
                break;
            default:
                jn_mpfr=call_mpfr::func(n, x, mpfr_jn, &ulp1_interval);
                jn_glibc=::jn(n, x);
                break;
            }
            if (verbose) {
                std::cout << "n=" << std::setw(5) << n
                          << " x=" << x << std::endl;
                std::cout << std::hexfloat;
                std::cout << "bessel_j: " << jn << std::endl;
                std::cout << "glibc:    " << jn_glibc << std::endl;
                std::cout << "mfpr:     " << jn_mpfr << std::endl;
                std::cout << std::scientific;
            }
            if (jn != ulp1_interval.first &&  jn != ulp1_interval.second) {
                if (!verbose) {
                    std::cout << "n=" << std::setw(5) << n
                              << " x=" << x << std::endl;
                    std::cout << std::hexfloat;
                    std::cout << "bessel_j: " << jn << std::endl;
                    std::cout << "glibc:    " << jn_glibc << std::endl;
                    std::cout << "mfpr:     " << jn_mpfr << std::endl;
                }
                std::cout << "delta: " << jn - jn_mpfr
                          << " distance: " << test::distance(jn, jn_mpfr)
                          << std::endl;
                std::cout << std::scientific;
            }
        }
        std::cout << "n="  << n << std::endl;
    }
    return 0;
}
