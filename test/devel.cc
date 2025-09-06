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
#include <cftal/test/call_mpfr.h>

namespace cftal { namespace devel {
    int
    calc_m_kahan(int nm1, double x, double rcp_eps);

    double bessel_j(int n, double x);
}}

int
cftal::devel::
calc_m_kahan(int nm1, double x, double rcp_eps)
{
    using std::max;
    using std::rint;
    int k= max(nm1+1, static_cast<int>(rint(x)));
    const auto beta=1.0;
    double yk = 0.0, ykp1=beta;
    double _2_x= 2.0/x;
    int m=k+1;
    double md=static_cast<double>(m);
    for (;m<std::numeric_limits<int>::max(); ++m) {
        double t= md * _2_x * ykp1 - yk;
        yk   = ykp1;
        ykp1 = t;
        // because beta == 1.0
        if (ykp1 >= rcp_eps)
            break;
        md += 2.0;
    }
    std::cout << ykp1 << std::endl;
    return m;
}

// j(n-1, x) = 2*n/x * j(n, x) - j(n+1, x)
// 1 = j(0, x) + 2*j(2, x) + 2 * j(4, x) + ....
double
cftal::devel::
bessel_j(int n, double x)
{
    using v_t = d_real<double>;
    size_t _N=calc_m_kahan(n-1, x, 0x1.0p68);
    std::cout << "jn(" << n << ", " << x << ") _N=" << _N  <<'\n';
    std::vector<v_t> vj(_N+2, v_t(0.0));
    v_t rec_x=v_t(1.0)/x;
    vj[_N] = 1.0;
    vj[_N+1] = 0.0;
    v_t norm=0.0;
    v_t vi(_N);
    for (ssize_t i=_N; i > 0; --i) {
        v_t vj_im1=(2.0*vi)*rec_x * vj[i] - vj[i+1];
        if (i && (i&1)==0) {
            norm += 2.0*vj[i];
        }
        vj[i-1] = vj_im1;
        vi -= 1.0;
    }
    norm += vj[0];
    v_t jn=vj[n]/norm;
    return jn[0];
}

using namespace cftal;

int main(int argc, char** argv)
{
    using namespace cftal;
    using namespace cftal::devel;
    using namespace cftal::test;


    std::cout << std::scientific << std::setprecision(18);
    const double x=99;
    const int n=100;
    double jn= bessel_j(n, x);
    std::cout << jn << std::endl;
    // double j1v= j1(v1f64(x))();
    // std::cout << j1v << std::endl;
    double jn_glibc=::jn(n, x);
    std::cout << jn_glibc << std::endl;
    double jn_mpfr=call_mpfr::func(n, x, mpfr_jn, nullptr);
    std::cout << jn_mpfr << std::endl;
    return 0;
}
