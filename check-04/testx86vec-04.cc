#include <cmath>
#include <x86vec_test.h>
#include <cftal/math_func.h>
#include <cstdint>
#include <iostream>
#include <iomanip>

namespace x86vec {
        namespace test {

                double make_double(unsigned sgn, unsigned exp, uint64_t sig);
		float make_float(unsigned sgn, unsigned exp, uint32_t sig);

                // compare a and b, returns also true for a==NAN and b
                // == NAN
                bool f_eq(double a, double b);
                bool f_eq(float a, float b);

		template <class _FV, class _IV>
                bool check_frexp(typename _FV::element_type vp, 
				 typename _FV::element_type vn);
	
		template <class _FV, class _IV>
                bool check_frexp_f64();

		template <class _FV, class _IV>
		bool check_frexp_f32();

		template <class _V>
		int check_cbrt_f64(const _V& v0, double x);

		template <class _V>
		bool check_cbrt_f64(const _V& v0);

	}
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

float x86vec::test::make_float(unsigned sgn, unsigned exp, uint32_t sig)
{
        uint32_t _sgn= uint64_t(sgn & 1) << 31;
        uint32_t _exp= uint64_t(exp & 0xFF) << 23;
        uint32_t _sig= sig & 0x007fffff;
        union {
                uint32_t _u;
                float _d;
        } t;
        t._u = _sgn | _exp | _sig;
        return t._d;
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

template <class _FV, class _IV>
bool x86vec::test::check_frexp(typename _FV::element_type vp, 
			       typename _FV::element_type vm)
{
	using real_type = typename _FV::element_type;

	const int FN=sizeof(_FV)/sizeof(real_type);
	union v_d {
		_FV _v;
		real_type _d[FN];
	};

	using int_type = typename _IV::element_type;
	const int IN=sizeof(_IV)/sizeof(int_type);
	union v_i {
		_IV _v;
		int_type _i[IN];
	};

	v_d arg;

	for (int i=0; i<FN; i+=2) {
		arg._d[i]= vp;
		arg._d[i+1] = vm;
	}

	real_type ref[FN];
	int_type e_ref[FN];

	for (int i=0; i<FN; ++i)
		ref[i] = std::frexp(arg._d[i], &e_ref[i]);

	v_d res;
	v_i e;
	res._v = frexp(arg._v, &e._v);

	bool rc(true);

	for (int i=0; i<FN; ++i) {
		real_type r_i= res._d[i];
		real_type ref_i = ref[i];
		int_type e_i= e._i[i];
		int_type ref_e_i= e_ref[i];
		if (!f_eq(r_i, ref_i) || e_i != ref_e_i) {
			std::cout << "frexp(" << arg._d[i] << ")="
				  << r_i << " exp= " << e_i
				  << std::endl
				  << "expect: "
				  << ref_i << " exp= " << ref_e_i
				  << std::endl;
			rc= false;
		}
	}
        if (!rc)
                std::exit(3);
        return true;
}

template <class _FV, class _IV>
bool x86vec::test::check_frexp_f64()
{
        // check zero
        double vp = make_double(0, 0, 0);
        check_frexp<_FV, _IV>(vp, -vp);
        // check +- inf
        check_frexp<_FV, _IV>(make_double(0, 0x7FF, 0),
			      make_double(1, 0x7FF, 0));
        // check +-nan
        for (int i=0; i<53; ++i) {
                uint64_t sig= uint64_t(1) << i;
                check_frexp<_FV, _IV>(make_double(0, 0x7FF, sig),
				      make_double(1, 0x7FF, sig));
        }
        // denormals and normals
        for (int e=0; e<=0x7ff; ++e) {
                for (int i=0; i<52; ++i) {
                        uint64_t sig= uint64_t(1) << i;
                        vp = make_double(0, e, sig);
                        check_frexp<_FV, _IV>(vp, -vp);
                }
        }
        return true;
}

template <class _FV, class _IV>
bool x86vec::test::check_frexp_f32()
{
        // check zero
        float vp = make_float(0, 0, 0);
        check_frexp<_FV, _IV>(vp, -vp);
        // check +- inf
        check_frexp<_FV, _IV>(make_float(0, 0xFF, 0),
			      make_float(1, 0xFF, 0));
        // check +-nan
        for (int i=0; i<23; ++i) {
                uint64_t sig= uint64_t(1) << i;
                check_frexp<_FV, _IV>(make_float(0, 0x7FF, sig),
				      make_float(1, 0x7FF, sig));
        }
        // denormals and normals
        for (int e=0; e<=0x7ff; ++e) {
                for (int i=0; i<23; ++i) {
                        uint32_t sig= uint32_t(1) << i;
                        vp = make_float(0, e, sig);
                        check_frexp<_FV, _IV>(vp, -vp);
                }
        }
        return true;
}


std::uint64_t as_uint64(double d)
{
	union u_d {
		double _d;
		int64_t _i;
	} t;
	t._d = d;
	return t._i;
}

template <class _V>
int x86vec::test::check_cbrt_f64(const _V& v, double x)
{
	double r3(std::cbrt(x));
	_V vx(x);
	_V vr3(cbrt(vx));

	double p3(cftal::math::pow<3>(r3));
	_V vp3(cftal::math::pow<3>(vr3));
	
	if (!elements_equal(vr3)) {
		std::cerr << "Invalid vector values\n";
		std::cout << "Invalid vector values\n";
		const int N=sizeof(_V)/sizeof(double);
		union v_d {
			_V _v;
			double _d[sizeof(_V)/sizeof(double)];
		};
		std::cout << std::setprecision(18);
		std::cout << x << std::endl;
		std::cout << r3 << std::endl;
		v_d t;
		t._v = vx;
		for (unsigned i=0; i<N; ++i) {
			std::cout << t._d[i] << std::endl;
		}
		t._v = vr3;
		for (unsigned i=0; i<N; ++i) {
			std::cout << t._d[i] << std::endl;
		}
 
		t._v = vp3;
		for (unsigned i=0; i<N; ++i) {
			std::cout << t._d[i] << std::endl;
		}

		
		std::exit(3);
	}

	double vr3_0(extract<0>(vr3));
	double vp3_0(extract<0>(vp3));
	int rc(0);
	if (std::fabs(x - vp3_0) > std::fabs(x - p3)) {
		std::cerr << "cbrt(" << x << ")= " 
			  << vr3_0 << " != " << r3 << std::endl;
		std::cerr << vp3_0 << " " << p3 << std::endl;

		std::cerr << std::fabs(x - vp3_0) << " " 
			  << std::fabs(x - p3)
			  << std::endl;
		std::cerr << std::hex 
			  << std::setw(16 )
			  << as_uint64(vr3_0)
			  << ' '
			  << as_uint64(r3)
			  << std::dec
			  << std::endl;
		rc = -1;
	} else if (std::fabs(x - vp3_0) < std::fabs(x - p3)) {
		rc = 1;
	}
	return rc;
}

template <class _V>
bool x86vec::test::check_cbrt_f64(const _V& v)
{
	bool res(true);
	static_cast<void>(v);
	std::cerr << std::setprecision(19)
		  << std::scientific;
	int r(0), e(0), f(0);
	int rc;
	for (int i=0; i<1000000; ++i) {
		double x(double(i)*0.01);
		
		rc=check_cbrt_f64(v, x);
		switch (rc) {
		case 0:
			++e; break;
		case 1:
			++r; break;
		case -1:
			++f; break;
		}
		rc= check_cbrt_f64(v, -x);
		switch (rc) {
		case 0:
			++e; break;
		case 1:
			++r; break;
		case -1:
			++f; break;
		}
	}
	rc = check_cbrt_f64(v, 1.0/0.0);
	switch (rc) {
	case 0:
		++e; break;
	case 1:
		++r; break;
	case -1:
			++f; break;
	}
	rc = check_cbrt_f64(v, -1.0/0.0);
	switch (rc) {
	case 0:
		++e; break;
	case 1:
		++r; break;
	case -1:
		++f; break;
	}
	rc = check_cbrt_f64(v, +0.0/0.0);
	switch (rc) {
	case 0:
		++e; break;
	case 1:
		++r; break;
	case -1:
		++f; break;
	}
	rc = check_cbrt_f64(v, -0.0/0.0);
	switch (rc) {
	case 0:
		++e; break;
	case 1:
		++r; break;
	case -1:
		++f; break;
	}
	std::cout << "r: " << r << " e: " << e << " f: " << f << std::endl;
	return res;
}


bool all_tests_04()
{
        x86vec::test::check_frexp_f64<x86vec::v2f64, 
				      x86vec::v4s32>();
#if defined (__AVX__)
	x86vec::test::check_frexp_f64<x86vec::v4f64,
				      x86vec::v4s32>();
#endif
        x86vec::test::check_frexp_f64<x86vec::v4f32, 
				      x86vec::v4s32>();
#if defined (__AVX__)
	x86vec::test::check_frexp_f64<x86vec::v8f32,
				      x86vec::v8s32>();
#endif

	x86vec::test::check_cbrt_f64(x86vec::v2f64());
#if defined (__AVX__)
	x86vec::test::check_cbrt_f64(x86vec::v4f64());
#endif
	return true;
}

int main(int argc, char** argv)
{
	return all_tests_04()==true ? 0 : 3;
}
