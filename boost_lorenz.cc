#include <iostream>
#include <cmath>

#include <boost/operators.hpp>
#include <boost/numeric/odeint.hpp>

#include <cftal/vec.h>


namespace boost {
    namespace numeric {
        namespace odeint {

            template <std::size_t _N>
            struct vector_space_norm_inf<cftal::vec<double, _N> > {
                typedef double result_type;
                double operator()(const cftal::vec<double, _N>& v) const {
                    cftal::vec<double, _N> va= abs(v);
                    return max_element(va);
                }
            };
        }
    }
}


//[point3D
class point3D : boost::additive1< point3D,
    boost::additive2< point3D, double,
    boost::multiplicative2< point3D, double > > > {
public:
    double x, y, z;
    point3D(): x(0.0), y(0.0), z(0.0) { }
    point3D(const double val)
        : x(val), y(val), z(val) { }
    point3D(const double _x, const double _y, const double _z)
        : x(_x), y(_y), z(_z) {
    }
    point3D& operator+=(const point3D& p) {
        x += p.x;
        y += p.y;
        z += p.z;
        return *this;
    }

    point3D& operator*=(const double a) {
        x *= a;
        y *= a;
        z *= a;
        return *this;
    }

};
//]

//[point3D_abs_div
// only required for steppers with error control
point3D operator/(const point3D& p1, const point3D& p2)
{
    return point3D(p1.x / p2.x, p1.y / p2.y, p1.z / p1.z);
}

point3D abs(const point3D& p)
{
    return point3D(std::abs(p.x), std::abs(p.y), std::abs(p.z));
}
//]

//[point3D_norm
// also only for steppers with error control
namespace boost {
    namespace numeric {
        namespace odeint {
            template<>
            struct vector_space_norm_inf< point3D > {
                typedef double result_type;
                double operator()(const point3D& p) const {
                    using std::max;
                    using std::abs;
                    return max(max(abs(p.x), abs(p.y)), abs(p.z));
                }
            };
        }
    }
}
//]

std::ostream& operator<<(std::ostream& out, const point3D& p)
{
    out << p.x << " " << p.y << " " << p.z;
    return out;
}

//[point3D_main
const double sigma = 10.0;
const double R = 28.0;
const double b = 8.0 / 3.0;

void lorenz(const point3D& x, point3D& dxdt, const double t)
{
    dxdt.x = sigma * (x.y - x.x);
    dxdt.y = R * x.x - x.y - x.x * x.z;
    dxdt.z = -b * x.z + x.x * x.y;
}

void lorenzv(cftal::v4f64 x, cftal::v4f64& dxdt, const double t)
{
    double xx = low_half(low_half(x))();
    double xy = high_half(low_half(x))();
    double xz = low_half(high_half(x))();

    double dx = sigma * (xy - xx);
    double dy = R * xx - xy - xx * xz;
    // double dz = -b * xz + xx * xy;
    double dz = xx * xy - b * xz;
    
    dxdt = cftal::v4f64{dx, dy, dz, 0.0};
}

using namespace boost::numeric::odeint;

int main()
{
    const double end_p = 10.0;
    
    point3D x(10.0, 5.0, 5.0);
    // point type defines it's own operators -> use vector_space_algebra !
    typedef runge_kutta_dopri5<point3D, double,
                               point3D, double,
                               vector_space_algebra> stepper;
    int steps = integrate_adaptive(make_controlled<stepper>(1E-10, 1E-10),
                                   lorenz, x,
                                   0.0, end_p, 0.1);

    std::cout << std::scientific << std::setprecision(12);
    
    std::cout << x << std::endl;
    std::cout << "steps: " << steps << std::endl;

    cftal::v4f64 xv{10.0, 5.0, 5.0, 0.0};

    typedef runge_kutta_dopri5<cftal::v4f64, double,
                               cftal::v4f64, double,
                               vector_space_algebra> vec_stepper;

    int stepsv = integrate_adaptive(make_controlled<vec_stepper>(1e-10, 1e-10),
                                    lorenzv, xv,
                                    0.0, end_p, 0.1);

    std::cout << xv << std::endl;
    std::cout << "steps: " << stepsv << std::endl;
    return 0;
}
