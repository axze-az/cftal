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
#include <cftal/vec.h>
#include <cftal/d_real.h>

namespace cftal { namespace devel {
    double bessel_j(int n, double x);
}}


// j(n-1, x) = 2*n/x * j(n, x) - j(n+1, x)
// 1 = j(0, x) + 2*j(2, x) + 2 * j(4, x) + ....
double
cftal::devel::
bessel_j(int n, double x)
{
    constexpr const int _N=30;
    using v_t = double;
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
    return jn;
}


using namespace cftal;

int main(int argc, char** argv)
{
    using namespace cftal;
    using namespace cftal::devel;

    std::cout << std::scientific << std::setprecision(18);
    const double x=2.5;
    const int n=1;
    double j1nv= bessel_j(n, x);
    std::cout << j1nv << std::endl;
    double j1v= j1(v1f64(x))();
    std::cout << j1v << std::endl;
    double jnx=::jn(n, x);
    std::cout << jnx << std::endl;
    return 0;
}
