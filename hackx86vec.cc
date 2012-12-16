#include <cftal/d_int.h>
#include <cftal/mul_div.h>
#include <cftal/emuvec.h>
#include <cmath>
#include <x86vec.h>
#include <x86vec_test.h>
#include <cstdint>
#include <iostream>
#include <iomanip>

namespace x86vec {
        namespace test {

                double make_double(unsigned sgn, unsigned exp, uint64_t sig);
                bool check_frexp(double vp, double vn);
                bool check_frexp_f64();

                // compare a and b, returns also true for a==NAN and b
                // == NAN
                bool f_eq(double a, double b);
                bool f_eq(float a, float b);
        }
}

inline
bool x86vec::test::f_eq(double a, double b)
{
        return (a == b) || (std::isnan(a) && std::isnan(b));
}

inline
bool x86vec::test::f_eq(float a, float b)
{
        return (a == b) || (std::isnan(a) && std::isnan(b));
}

double x86vec::test::make_double(unsigned sgn, unsigned exp, uint64_t sig)
{
        uint64_t _sgn= uint64_t(sgn & 1) << 63;
        uint64_t _exp= uint64_t(exp & 0x7FF) << 52;
        uint64_t _sig= sig & 0x000fffffffffffffULL;
        union {
                uint64_t _u;
                double _d;
        } t;
        t._u = _sgn | _exp | _sig;
        return t._d;
}

bool x86vec::test::check_frexp(double vp, double vm)
{
        int ep, em;
        double frp=std::frexp(vp, &ep);
        double frm=std::frexp(vm, &em);
        v2s64 e;
        v2f64 v(vp, vm), fr= frexp(v, &e);

        int r_ep= extract<0>(e);
        int r_em= extract<1>(e);
        double r_frp = extract<0>(fr);
        double r_frm = extract<1>(fr);

        bool rc(true);
        if (!f_eq(r_frp,frp) || r_ep != ep) {
                std::cout << "frexp(" << vp << ")="
                          << r_frp << " exp= " << r_ep
                          << std::endl
                          << "expect: "
                          << frp << " exp= " << ep
                          << std::endl;
                rc = false;
        }
        if (!f_eq(r_frm, frm) || r_em != em) {
                std::cout << "frexp(" << vm << ")="
                          << r_frm << " exp= " << r_em
                          << std::endl
                          << "expect: "
                          << frm << " exp= " << em
                          << std::endl;
                rc = false;
        }
        if (!rc)
                std::exit(3);
        return true;
}

bool x86vec::test::check_frexp_f64()
{
        // check zero
        double vp = make_double(0, 0, 0);
        check_frexp(vp, -vp);
        // check +- inf
        check_frexp(make_double(0, 0x7FF, 0),
                    make_double(1, 0x7FF, 0));
        // check +-nan
        for (int i=0; i<52; ++i) {
                uint64_t sig= uint64_t(1) << i;
                check_frexp(make_double(0, 0x7FF, sig),
                            make_double(1, 0x7FF, sig));
        }
        return true;
        // denormals and normals
        for (int e=0; e<=0x7ff; ++e) {
                for (int i=0; i<52; ++i) {
                        uint64_t sig= uint64_t(1) << i;
                        vp = make_double(0, e, sig);
                        check_frexp(vp, -vp);
                }
        }
        return true;
}

namespace vec=x86vec;
//namespace vec=emuvec;

// v2f64 compile tests
vec::v2f64 test1a(vec::v2f64 a, vec::v2f64 b, vec::v2f64 c)
{
        return a*b + c;
}

vec::v2f64 test1b(vec::v2f64 a, vec::v2f64 b, vec::v2f64 c)
{
        return c+ a*b;
}

vec::v2f64 test1c(vec::v2f64 a, vec::v2f64 b, vec::v2f64 c)
{
        return a*b - c;
}

vec::v2f64 test1d(vec::v2f64 a, vec::v2f64 b, vec::v2f64 c)
{
        return c- a*b;
}

vec::v2f64 test2a(vec::v2f64 a, vec::v2f64 b,
		  vec::v2f64 c, vec::v2f64 d)
{
        return a*b + c*d;
}

vec::v2f64 test2b(vec::v2f64 a, vec::v2f64 b,
		  vec::v2f64 c, vec::v2f64 d)
{
        return a*b - c*d;
}

vec::v2f64 test2c(vec::v2f64 a, vec::v2f64 b,
		  vec::v2f64 c, vec::v2f64 d)
{
        return (a*b + c) * d;
}

vec::v2f64 test2d(vec::v2f64 a, vec::v2f64 b,
		  vec::v2f64 c, vec::v2f64 d)
{
        return (a*b - c) * d;
}

vec::v2f64 test3a(vec::v2f64 a, vec::v2f64 b,
		  vec::v2f64 c, vec::v2f64 d)
{
	return 1.0 + a * b + 1.0 + c * d;
}

// v4f32 compile tests
vec::v4f32 test1a(vec::v4f32 a, vec::v4f32 b, vec::v4f32 c)
{
        return a*b + c;
}

vec::v4f32 test1b(vec::v4f32 a, vec::v4f32 b, vec::v4f32 c)
{
        return c+ a*b;
}

vec::v4f32 test1c(vec::v4f32 a, vec::v4f32 b, vec::v4f32 c)
{
        return a*b - c;
}

vec::v4f32 test1d(vec::v4f32 a, vec::v4f32 b, vec::v4f32 c)
{
        return c- a*b;
}

vec::v4f32 test2a(vec::v4f32 a, vec::v4f32 b,
		  vec::v4f32 c, vec::v4f32 d)
{
        return a*b + c*d;
}

vec::v4f32 test2b(vec::v4f32 a, vec::v4f32 b,
		  vec::v4f32 c, vec::v4f32 d)
{
        return a*b - c*d;
}

vec::v4f32 test2c(vec::v4f32 a, vec::v4f32 b,
		  vec::v4f32 c, vec::v4f32 d)
{
        return (a*b + c) * d;
}

vec::v4f32 test2d(vec::v4f32 a, vec::v4f32 b,
                  vec::v4f32 c, vec::v4f32 d)
{
        return (a*b - c) * d;
}

vec::v4f32 test3a(vec::v4f32 a, vec::v4f32 b,
		  vec::v4f32 c, vec::v4f32 d)
{
	return 1.0 + a * b + 1.0 + c * d;
}

vec::v4f32 test4a(vec::v4f32 a, vec::v4f32 b,
		  vec::v4f32 c, vec::v4f32 d)
{
	return (1.0+a*b) * (a*b + a*c + a*d + b* c + b* d +
			    c * d);
}



int main(int argc, char** argv)
{
        // x86vec::test::check_frexp_f64();
        x86vec::v2f64 t=exp(x86vec::v2f64(0.0));
        static_cast<void>(t);
        return 0;
}
