//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <iostream>
#include <cmath>
#if defined (__clang__)

int main()
{
    return 0;
}

#else

#include <boost/operators.hpp>
#include <cftal/boost_compat.h>

//[point3d
class point3d : boost::additive1<
    point3d,
    boost::additive2<
        point3d, double,
        boost::multiplicative2<
            point3d, double > > > {
public:
    double x, y, z;
    point3d(): x(0.0), y(0.0), z(0.0) { }
    point3d(double val)
        : x(val), y(val), z(val) { }
    point3d(double _x, double _y, double _z)
        : x(_x), y(_y), z(_z) {
    }
    point3d& operator+=(const point3d& p) {
        x += p.x;
        y += p.y;
        z += p.z;
        return *this;
    }

    point3d& operator*=(const double a) {
        x *= a;
        y *= a;
        z *= a;
        return *this;
    }
};
//]

//[point3d_abs_div
// only required for steppers with error control
point3d operator/(const point3d& p1, const point3d& p2)
{
    return point3d(p1.x / p2.x, p1.y / p2.y, p1.z / p2.z);
}

point3d abs(const point3d& p)
{
    return point3d(std::abs(p.x), std::abs(p.y), std::abs(p.z));
}
//]

//[point3d_norm
// also only for steppers with error control
namespace boost {
    namespace numeric {
        namespace odeint {
            template<>
            struct vector_space_norm_inf< point3d > {
                using result_type = double;
                result_type operator()(const point3d& p) const {
                    using std::max;
                    using std::abs;
                    return max(max(abs(p.x), abs(p.y)), abs(p.z));
                }
            };
        }
    }
}
//]

std::ostream& operator<<(std::ostream& out, const point3d& p)
{
    out << p.x << " " << p.y << " " << p.z;
    return out;
}

//[point3d_main
const double sigma = 10.0;
const double R = 28.0;
const double b = 8.0 / 3.0;

void lorenz(const point3d& x, point3d& dxdt, const double t)
{
    dxdt.x = sigma * (x.y - x.x);
    dxdt.y = R * x.x - x.y - x.x * x.z;
    dxdt.z = -b * x.z + x.x * x.y;
}

void lorenza(const std::array<double, 3>& x,
             std::array<double, 3>& dxdt, const double t)
{
    double xx = x[0];
    double xy = x[1];
    double xz = x[2];

    double dx = sigma * (xy - xx);
    double dy = R * xx - xy - xx * xz;
    double dz = -b * xz + xx * xy;

    // std::cout << dx << ", " << dy << ", " << dz << std::endl;
    dxdt[0] =dx;
    dxdt[1] =dy;
    dxdt[2] =dz;
}

cftal::v4f64 lorenzv(cftal::v4f64 x, cftal::v4f64& dxdt, const double t)
{
    using namespace cftal;
    double xx = low_half(low_half(x))();
    double xy = high_half(low_half(x))();
    double xz = low_half(high_half(x))();

    double dx = sigma * (xy - xx);
    double dy = R * xx - xy - xx * xz;
    v2f64 dz(-b * xz + xx * xy, 0);
    v2f64 lh(dx, dy);
    // std::cout << "lh ";
    // std::cout << lh << ' ' << dz << std::endl;
    v4f64 r(lh, dz);
    // std::cout << r << std::endl;
    dxdt = r;
    return r;
}


using namespace boost::numeric::odeint;

int main()
{
    const double end_p = 10.0;
    const double abs_err = 1e-15;
    const double rel_err = 1e-15;

    std::cout << "point3d dopri5" << std::endl;
    point3d x(10.0, 5.0, 5.0);
    // point type defines it's own operators -> use vector_space_algebra !
    using stepper= runge_kutta_dopri5<point3d, double,
                                      point3d, double,
                                      vector_space_algebra>;
    int steps = integrate_adaptive(make_controlled<stepper>(abs_err, rel_err),
                                   lorenz, x,
                                   0.0, end_p, 0.1);

    std::cout << std::scientific << std::setprecision(12);

    std::cout << x << std::endl;
    std::cout << "steps: " << steps << std::endl;

    std::cout << "vector dopri5" << std::endl;
    cftal::v4f64 xv{10.0, 5.0, 5.0, 0.0};

    using vec_stepper=runge_kutta_dopri5<cftal::v4f64, double,
                                         cftal::v4f64, double,
                                         vector_space_algebra>;

    int stepsv = integrate_adaptive(
        make_controlled<vec_stepper>(abs_err, rel_err),
        lorenzv, xv, 0.0, end_p, 0.1);

    std::cout << xv << std::endl;
    std::cout << "steps: " << stepsv << std::endl;

    std::cout << "vector rk78" << std::endl;
    cftal::v4f64 xv2{10.0, 5.0, 5.0, 0.0};

    using vec_stepper2=runge_kutta_fehlberg78<cftal::v4f64, double,
                                              cftal::v4f64, double,
                                              vector_space_algebra>;

    int stepsv2 = integrate_adaptive(
        make_controlled<vec_stepper2>(abs_err, rel_err),
        lorenzv, xv2,
        0.0, end_p, 0.1);

    std::cout << xv2 << std::endl;
    std::cout << "steps: " << stepsv2 << std::endl;

    std::cout << "array version" << std::endl;
    std::array<double, 3> xa{{10.0, 5.0, 5.0}};

    using a_stepper=runge_kutta_dopri5<std::array<double, 3>, double,
                                       std::array<double, 3>, double,
                                       array_algebra>;

    int stepsa = integrate_adaptive(
        make_controlled<a_stepper>(abs_err, rel_err),
        lorenza, xa, 0.0, end_p, 0.1);

    for(const auto& v: xa) {
        std::cout << v << ' ';
    }
    std::cout << std::endl;
    std::cout << "steps: " << stepsa << std::endl;
    return 0;
}
#endif
