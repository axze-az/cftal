#include <cftal/d_int.h>
#include <cftal/d_real.h>
#include <cftal/mul_div.h>
#include <cftal/vec.h>
#include <cmath>
#include <x86vec_test.h>
#include <cstdint>
#include <iostream>
#include <iomanip>

namespace {

        using namespace cftal;
#if 0
        const d_real<double> inv_fac[] = {
		1.0000000000000000000000000000000000000000000000000000000000000000_dd,
		1.0000000000000000000000000000000000000000000000000000000000000000_dd,
		.5000000000000000000000000000000000000000000000000000000000000000_dd,
		.1666666666666666666666666666666666666666666666666666666666666666_dd,
		.0416666666666666666666666666666666666666666666666666666666666666_dd,
		.0083333333333333333333333333333333333333333333333333333333333333_dd,
		.0013888888888888888888888888888888888888888888888888888888888888_dd,
		.0001984126984126984126984126984126984126984126984126984126984126_dd,
		.0000248015873015873015873015873015873015873015873015873015873015_dd,
		.0000027557319223985890652557319223985890652557319223985890652557_dd,
		.0000002755731922398589065255731922398589065255731922398589065255_dd,
		.0000000250521083854417187750521083854417187750521083854417187750_dd,
		.0000000020876756987868098979210090321201432312543423654534765645_dd,
		.0000000001605904383682161459939237717015494793272571050348828126_dd,
		.0000000000114707455977297247138516979786821056662326503596344866_dd,
		.0000000000007647163731819816475901131985788070444155100239756324_dd,
		.0000000000000477947733238738529743820749111754402759693764984770_dd,
		.0000000000000028114572543455207631989455830103200162334927352045_dd,
		.0000000000000001561920696858622646221636435005733342351940408446_dd,
		.0000000000000000082206352466243297169559812368722807492207389918_dd,
		.0000000000000000004110317623312164858477990618436140374610369495_dd,
		.0000000000000000000195729410633912612308475743735054303552874737_dd,
		.0000000000000000000008896791392450573286748897442502468343312488_dd,
		.0000000000000000000000386817017063068403771691193152281232317934_dd,
		.0000000000000000000000016117375710961183490487133048011718013247_dd,
		.0000000000000000000000000644695028438447339619485321920468720529_dd,
		.0000000000000000000000000024795962632247974600749435458479566174_dd,
		.0000000000000000000000000000918368986379554614842571683647391339_dd,
		.0000000000000000000000000000032798892370698379101520417273121119_dd,
		.0000000000000000000000000000001130996288644771693155876457693831_dd,
		.0000000000000000000000000000000037699876288159056438529215256461_dd,
		.0000000000000000000000000000000001216125041553517949629974685692_dd
        };
#endif
}


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

//namespace vec=x86vec;
//namespace vec=emuvec;



// v2f64 compile tests
cftal::vec::v2f64 test1a(cftal::vec::v2f64 a, cftal::vec::v2f64 b, cftal::vec::v2f64 c)
{
        return a*b + c;
}

cftal::vec::v2f64 test1b(cftal::vec::v2f64 a, cftal::vec::v2f64 b, cftal::vec::v2f64 c)
{
        return c+ a*b;
}

cftal::vec::v2f64 test1c(cftal::vec::v2f64 a, cftal::vec::v2f64 b, cftal::vec::v2f64 c)
{
        return a*b - c;
}

cftal::vec::v2f64 test1d(cftal::vec::v2f64 a, cftal::vec::v2f64 b, cftal::vec::v2f64 c)
{
        return c- a*b;
}

cftal::vec::v2f64 test2a(cftal::vec::v2f64 a, cftal::vec::v2f64 b,
                  cftal::vec::v2f64 c, cftal::vec::v2f64 d)
{
        return a*b + c*d;
}

cftal::vec::v2f64 test2b(cftal::vec::v2f64 a, cftal::vec::v2f64 b,
                  cftal::vec::v2f64 c, cftal::vec::v2f64 d)
{
        return a*b - c*d;
}

cftal::vec::v2f64 test2c(cftal::vec::v2f64 a, cftal::vec::v2f64 b,
                  cftal::vec::v2f64 c, cftal::vec::v2f64 d)
{
        return (a*b + c) * d;
}

cftal::vec::v2f64 test2d(cftal::vec::v2f64 a, cftal::vec::v2f64 b,
                  cftal::vec::v2f64 c, cftal::vec::v2f64 d)
{
        return (a*b - c) * d;
}

cftal::vec::v2f64 test3a(cftal::vec::v2f64 a, cftal::vec::v2f64 b,
                  cftal::vec::v2f64 c, cftal::vec::v2f64 d)
{
        return 1.0 + a * b + 1.0 + c * d;
}

// v4f32 compile tests
cftal::vec::v4f32 test1a(cftal::vec::v4f32 a, cftal::vec::v4f32 b, cftal::vec::v4f32 c)
{
        return a*b + c;
}

cftal::vec::v4f32 test1b(cftal::vec::v4f32 a, cftal::vec::v4f32 b, cftal::vec::v4f32 c)
{
        return c+ a*b;
}

cftal::vec::v4f32 test1c(cftal::vec::v4f32 a, cftal::vec::v4f32 b, cftal::vec::v4f32 c)
{
        return a*b - c;
}

cftal::vec::v4f32 test1d(cftal::vec::v4f32 a, cftal::vec::v4f32 b, cftal::vec::v4f32 c)
{
        return c- a*b;
}

cftal::vec::v4f32 test2a(cftal::vec::v4f32 a, cftal::vec::v4f32 b,
                  cftal::vec::v4f32 c, cftal::vec::v4f32 d)
{
        return a*b + c*d;
}

cftal::vec::v4f32 test2b(cftal::vec::v4f32 a, cftal::vec::v4f32 b,
                  cftal::vec::v4f32 c, cftal::vec::v4f32 d)
{
        return a*b - c*d;
}

cftal::vec::v4f32 test2c(cftal::vec::v4f32 a, cftal::vec::v4f32 b,
                  cftal::vec::v4f32 c, cftal::vec::v4f32 d)
{
        return (a*b + c) * d;
}

cftal::vec::v4f32 test2d(cftal::vec::v4f32 a, cftal::vec::v4f32 b,
                  cftal::vec::v4f32 c, cftal::vec::v4f32 d)
{
        return (a*b - c) * d;
}

cftal::vec::v4f32 test3a(cftal::vec::v4f32 a, cftal::vec::v4f32 b,
                  cftal::vec::v4f32 c, cftal::vec::v4f32 d)
{
        return 1.0 + a * b + 1.0 + c * d;
}

cftal::vec::v4f32 test4a(cftal::vec::v4f32 a, cftal::vec::v4f32 b,
                  cftal::vec::v4f32 c, cftal::vec::v4f32 d)
{
        return (1.0+a*b) * (a*b + a*c + a*d + b* c + b* d +
                            c * d);
}

cftal::vec::v4f32 test_mask(cftal::vec::v4f32 a, cftal::vec::v4f32 b,
                     cftal::vec::v4f32 c, cftal::vec::v4f32 d,
                     cftal::vec::mask<cftal::vec::v4f32> m)
{
        cftal::vec::v4f32 r(a);
        r(m) = (1.0+a*b) * (a*b + a*c + a*d + b* c + b* d +
                            c * d);
        return r;
}

void calc_pi()
{
        using dpf64 = cftal::d_real<double>;
        // arctan(x) = x/1 - {x^3}/3 + x^5/5
        // arctan(1) = PI/4
        dpf64 pi(0);
        double pi_d(0);
        for (std::int64_t i=100000000; i>=0 ; --i) {
                const std::int64_t i0=2*i+2;
                dpf64 t0(i0);
                dpf64 t1(t0+1.0);
                dpf64 t2(t0+2.0);
                dpf64 p(t0*t1*t2);
                dpf64 rp(1.0/p);
                if ((i&1)==0) {
                        // std::cout << i0 << std::endl;
                        pi += rp;
                } else {
                        // std::cout << -i0 << std::endl;
                        pi -= rp;
                }
                // std::cout << pi.h() << ' ' << pi.l() << std::endl;
        }
        pi *= 4.0;
        pi += 3.0;
        std::cout << std::scientific
                  << std::setprecision(18)
                  << pi.h()
                  << ' '
                  << pi.l()
                  << std::endl
                  << pi_d
                  << std::endl;
}

struct print_dpf64 {
	const cftal::d_real<double> _f;
	print_dpf64(const cftal::d_real<double>& f) : _f(f) {}
};

std::ostream& operator<<(std::ostream& s, const print_dpf64& p)
{
	const cftal::d_real<double>& d=p._f;
	s << std::scientific
	  << std::setprecision(22);
	if (d.h() >= 0.0)
		std::cout << ' ';
	s << std::setw(27) 
	  << d.h()
	  << std::setw(0)
	  << ", " ;
	if (d.l() >= 0.0)
		std::cout << ' ';
	std::cout << std::setw(27)
		  << d.l()
		  << std::setw(0);
	return s;
}


void print_inv_fac()
{
        using dpf64 = cftal::d_real<double>;

	dpf64 fac(1.0);
	std::vector<dpf64> v; 
	
	const std::size_t MAX_FAC=30;

	std::cout << "template <class _T>\n"
		  << "const _T\n" 
		  << "cftal::impl::d_real_constants_dbl<_T>::\n"
		  << "inv_fac[MAX_FAC+1]= {"
		  << std::endl;
	for (std::size_t i=0; i<MAX_FAC+1; ++i) {
		dpf64  inv_fac(1.0);
		if (i>1) {
			fac *= double(i);
			inv_fac /= fac;
		}
		v.push_back(inv_fac);
		std::cout << std::scientific
			  << std::setprecision(22)
			  << "\t_T( " 
			  << print_dpf64(inv_fac)
			  << ")";
		if (i != MAX_FAC)
			std::cout << ',';
		std::cout << std::endl;
	}
	std::cout << "};" << std::endl;

	// parameters for sin
	std::cout << "template <typename _T>" << std::endl
		  << "const " << std::endl
 		  << "typename cftal::math::func<double, cftal::int32_t, _T>::dvf_type" << std::endl
		  << "cftal::math::func<double, cftal::int32_t, _T>::m_sin_c_k2[]= {" << std::endl;
	
	std::cout << "\t// +1/21!\n"
		  << "\tdvf_type( " << print_dpf64(v[21]) <<"),\n";

	std::cout << "\t// -1/19!\n"
		  << "\tdvf_type( " << print_dpf64(-v[19]) <<"),\n";

	std::cout << "\t// +1/17!\n"
		  << "\tdvf_type( " << print_dpf64(v[17]) <<"),\n";

	std::cout << "\t// -1/15!\n"
		  << "\tdvf_type( " << print_dpf64(-v[15]) <<"),\n";

	std::cout << "\t// +1/13!\n"
		  << "\tdvf_type( " << print_dpf64(v[13]) <<"),\n";

	std::cout << "\t// -1/11!\n"
		  << "\tdvf_type( " << print_dpf64(-v[11]) <<"),\n";

	std::cout << "\t// +1/9!\n"
		  << "\tdvf_type( " << print_dpf64(v[9]) <<"),\n";

	std::cout << "\t// -1/7!\n"
		  << "\tdvf_type( " << print_dpf64(-v[7]) <<"),\n";

	std::cout << "\t// +1/5!\n"
		  << "\tdvf_type( " << print_dpf64(v[5]) <<"),\n";

	std::cout << "\t// -1/3!\n"
		  << "\tdvf_type( " << print_dpf64(-v[3]) <<")\n};\n\n";

	// parameters for cos
	std::cout << "template <typename _T>" << std::endl
		  << "const " << std::endl
 		  << "typename cftal::math::func<double, cftal::int32_t, _T>::dvf_type" << std::endl
		  << "cftal::math::func<double, cftal::int32_t, _T>::m_cos_c_k2[]= {" << std::endl;
	
	std::cout << "\t// -1/22!\n"
		  << "\tdvf_type( " << print_dpf64(-v[22]) <<"),\n";

	std::cout << "\t// +1/20!\n"
		  << "\tdvf_type( " << print_dpf64(v[20]) <<"),\n";

	std::cout << "\t// -1/18!\n"
		  << "\tdvf_type( " << print_dpf64(-v[18]) <<"),\n";

	std::cout << "\t// +1/16!\n"
		  << "\tdvf_type( " << print_dpf64(v[16]) <<"),\n";

	std::cout << "\t// -1/14!\n"
		  << "\tdvf_type( " << print_dpf64(-v[14]) <<"),\n";

	std::cout << "\t// +1/12!\n"
		  << "\tdvf_type( " << print_dpf64(v[12]) <<"),\n";

	std::cout << "\t// -1/10!\n"
		  << "\tdvf_type( " << print_dpf64(-v[10]) <<"),\n";

	std::cout << "\t// +1/8!\n"
		  << "\tdvf_type( " << print_dpf64(v[8]) <<"),\n";

	std::cout << "\t// -1/6!\n"
		  << "\tdvf_type( " << print_dpf64(-v[6]) <<"),\n";

	std::cout << "\t// +1/4!\n"
		  << "\tdvf_type( " << print_dpf64(v[4]) <<")\n};\n\n";
	// parameters for exp
}

void print_2_over_i()
{
        using dpf64 = cftal::d_real<double>;

	const std::size_t MAX_2_OVER_I=30;

	std::cout << "template <class _T>\n"
		  << "const _T\n" 
		  << "cftal::impl::d_real_constants_dbl<_T>::\n"
		  << "_2_over_i[MAX_2_OVER_I]= {"
		  << std::endl;
	for (std::size_t i=0; i<MAX_2_OVER_I; ++i) {
		dpf64 two_over_i(2.0);
		if (i>1) {
			two_over_i /= double(i);
		}
		std::cout << std::scientific
			  << std::setprecision(22)
			  << "\t_T( " 
			  << std::setw(27)
			  << two_over_i.h()
			  << std::setw(0)
			  << ", " ;
		if (two_over_i.l() >= 0.0)
			std::cout << ' ';
		std::cout << std::setw(27)
			  << two_over_i.l()
			  << std::setw(0)
			  << ")";
		if (i != MAX_2_OVER_I)
			std::cout << ',';
		std::cout << std::endl;
	}
	std::cout << "};" << std::endl;
}

void print_sqrtx()
{
        using dpf64 = cftal::d_real<double>;
	dpf64 sqrt12(sqrt(dpf64(0.5)));
	std::cout << "template <class _T>\n"
		  << "const _T\n" 
		  << "cftal::impl::d_real_constants_dbl<_T>::\n"
		  << "m_sqrt1_2("
		  << std::endl;
	std::cout << std::scientific
		  << std::setprecision(22)
		  << "\t_T( " 
		  << std::setw(27)
		  << sqrt12.h()
		  << std::setw(0)
		  << ", " ;
	if (sqrt12.l() >= 0.0)
		std::cout << ' ';
	std::cout << std::scientific
		  << std::setprecision(22)
		  << std::setw(27)
		  << sqrt12.l()
		  << std::setw(0)
		  << ");";
	std::cout << std::endl;

	__float128 t2= __builtin_sqrtl(__float128(0.5));
	std::cout << std::setprecision(22)
		  << double(t2)
		  << ' '
		  << double(t2 - double(t2))
		  << std::endl;
}


void testpowi()
{
        using dpf64 = cftal::d_real<double>;
	dpf64 base(1.0);
	dpf64 t1=cftal::str_to_d_double("0.025e1");
	std::cout.setf(std::ios_base::fixed | 
		       std::ios_base::scientific, 
		       std::ios_base::floatfield);
	std::cout << std::setprecision(22)
		  << t1.h()
		  << ", "
		  << t1.l()
		  << std::endl;
	base+= t1;
	for (std::size_t i=0; i<10; ++i) {
		dpf64 t= powi(base, i);
		std::cout << std::setprecision(22)
			  << t.h()
			  << ", "
			  << t.l()
			  << std::endl;
	}

}

__m256d tr1(__m256d a, __m256d b)
{
	return x86vec::perm_f64<0, 4, 1, 5>(a, b);
}

__m256d tr2(__m256d a, __m256d b)
{
	return x86vec::perm_f64<2, 6, 3, 7>(a, b);
}

__m256d tr1a(__m256d a, __m256d b)
{
	// x86vec::perm_f64<0, 4, 1, 5>(a, b);
#if 0
	// 5 operations
	__m256d a0= x86vec::perm_f64<0, 0, 1, 1>(a);
	__m256d b0= x86vec::perm_f64<0, 0, 1, 1>(b);
	return x86vec::select_f64<true, false, true, false>(a0, b0);
#endif
	using namespace x86vec;
	using namespace x86vec::impl;
	// 0 4 2 6
	__m256d t0= vunpcklpd::v(a, b);
	// 1 5 3 7
	__m256d t1= vunpckhpd::v(a, b);
	__m256d r= vperm2f128<0, 2>::v(t0, t1);
	return r;
	
}

__m256d tr2a(__m256d a, __m256d b)
{
	// x86vec::perm_f64<2, 6, 3, 7>(a, b);
#if 0
	// 5 operations
	__m256d a0= x86vec::perm_f64<2, 2, 3, 3>(a);
	__m256d b0= x86vec::perm_f64<2, 2, 3, 3>(b);
	return x86vec::select_f64<true, false, true, false>(a0, b0);
#endif
	using namespace x86vec;
	using namespace x86vec::impl;
	// 0 4 2 6
	__m256d t0= vunpcklpd::v(a, b);
	// 1 5 3 7
	__m256d t1= vunpckhpd::v(a, b);
	__m256d r= vperm2f128<1, 3>::v(t0, t1);
	return r;
}

__m256d tr2b(__m256d a)
{
	return x86vec::perm_f64< 2, -1, 3, -1>(a);
}


int main(int argc, char** argv)
{
        // x86cftal::vec::test::check_frexp_f64();
        // x86cftal::vec::v2f64 t=exp(x86cftal::vec::v2f64(0.0));
        // static_cast<void>(t);
        // calc_pi();
	// print_inv_fac();
	// print_2_over_i();
	// print_sqrtx();
	// testpowi();

	using namespace x86vec;
	using namespace x86vec::test;

        bool rc(true);
        __m256d a = load_v4f64(false);
	__m256d b = load_v4f64(true);
        __m256d r;
        idx id(-2,-2);
        r=tr1a(a, b);
        id.assign(0, 4, 1, 5);
        rc &= check_v4f64("perm2_v4f64", r, id);

	a = load_v4f64(false);
	b = load_v4f64(true);
	r=tr2a(a, b);
        id.assign(2, 6, 3, 7);
        rc &= check_v4f64("perm2_v4f64", r, id);

        return 0;
}
