#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <x86vec_fvec.h>
#include <bitops.h>
#include <unistd.h>

namespace x86vec {

	namespace test {

		template <class _T>
		_T rel_error(const _T& a, const _T& b);

		template <class _T>
		_T abs_error(const _T& a, const _T& b);

		int ulp(double c, double n);

		struct func_data {
			typedef v2f64::element_type fp_type;
			typedef arg<v2f64>::type arg_type;
			struct inp_res {
				fp_type _a0;
				fp_type _a1;
				fp_type _res;
				unsigned _rounding_mode;
			};
			
			std::string _fname;
			v2f64 (*_f1)(arg_type a);
			double (*_f1d)(double a);
			v2f64 (*_f2)(arg_type a, arg_type b);
			double (*_f2d)(double a, double b);
			std::vector<inp_res> _data;

			func_data() : _fname(), _f1(nullptr), _f1d(nullptr),
					      _f2(nullptr), _f2d(nullptr),_data() {
			}
		};

		std::string delete_comment(const std::string& s);
		bool read_func(func_data& tf, std::istream& is,
			       bool use_native);
		bool read_data(func_data& tf, std::istream& is);
		bool test_data(const func_data& tf, std::ostream& os);

		bool func(std::istream& is, bool use_native);
	}
}

template <typename _T>
_T x86vec::test::abs_error(const _T& a, const _T& b)
{
	return abs(a-b);
}

template <class _T>
_T x86vec::test::rel_error(const _T& a, const _T& b)
{
	_T ae(a - b);
	_T r((a + b) * _T(0.5));
	_T re(ae / r);
	re = select(r == _T(0.0), _T(0.0),  abs(re));
	return re;
}

int x86vec::test::ulp(double c, double n)
{
	if (std::isinf(c) && std::isinf(n))
		return 0;
	if (std::isnan(c) && std::isnan(n))
		return 0;
	if (c==0 && n == 0)
		return 0;
	int ce(-1), ne(-1);
	double cf(std::frexp(c, &ce));
	double nf(std::frexp(n, &ne));
	union d_i {
		double _d;
		std::uint64_t _u;
	};
	d_i ci, ni;
	ci._d = cf;
	ni._d = nf;
#if 0
	std::cout << std::hex << "ci: " << ci._u 
		  << " ni: " << ni._u << std::endl
		  << std::dec;
#endif
	int u(64);
	for (int i=63; i>=0; --i) {
		std::uint64_t msk(1L << i);
		if ((ci._u & msk) == (ni._u & msk)) {
			--u;
			continue;
		}
		break;
	}
	return u;
}

std::string x86vec::test::delete_comment(const std::string& s)
{
	std::string::size_type n(s.find('#'));
	std::string r(n == std::string::npos ? s : s.substr(0, n));
	return r;
}

bool x86vec::test::read_func(func_data& tf, 
			     std::istream& is,
			     bool use_native)
{
	std::string line;
	while (!getline(is, line).eof()) {
		line = delete_comment(line);
		if (line.empty())
			continue;
		std::stringstream t;
		t.str(line);
		std::string f;
		t >> f;
		std::cerr << "testing " << f << std::endl;
		tf._fname = f;
		if (f == "cos") {
			if (use_native)
				tf._f1 = x86vec::native_cos;
			else
				tf._f1 = x86vec::cos;
			tf._f1d= std::cos;
		} else if (f == "sin") {
			if (use_native)
				tf._f1 = x86vec::native_sin;
			else
				tf._f1 = x86vec::sin;
			tf._f1d= std::sin;
		} else if (f == "tan") {
			if (use_native)
				tf._f1 = x86vec::native_tan;
			else
				tf._f1 = x86vec::tan;
			tf._f1d= std::tan;
		} else if (f == "exp") {
			if (use_native)
				tf._f1= x86vec::native_exp;
			else
				tf._f1 = x86vec::exp;
			tf._f1d = std::exp;
		} else if (f == "log") {
			tf._f1 = x86vec::log;
			tf._f1d = std::log;
#if 0
		} else if (f == "sinh") {
			tf._f1 = x86vec::sinh;
			tf._f1d = std::sinh;
#endif
		} else if (f == "cosh") {
			tf._f1 = x86vec::cosh;
			tf._f1d = std::cosh;
		} else if (f == "tan") {
			tf._f1 = x86vec::tan;
			tf._f1d = std::tan;
		} else if (f == "asin") {
			tf._f1 = x86vec::asin;
			tf._f1d = std::asin;
		} else if (f == "acos") {
			tf._f1 = x86vec::acos;
			tf._f1d = std::acos;
		} else if (f == "atan") {
			tf._f1 = x86vec::atan;
			tf._f1d = std::atan;
		} else if (f == "atan2") {
			tf._f2 = x86vec::atan2;
			tf._f2d = std::atan2;
		} else {
			std::cerr << "unknown function " << f << std::endl;
			return false;
		}
		return true;
	}
	return false;
}

bool x86vec::test::read_data(func_data& tf, std::istream& is)
{
	std::string line;
	while (!getline(is, line).eof()) {
		line = delete_comment(line);
		if (line.empty())
			continue;
		std::stringstream t;
		t.str(line);
		std::uint32_t a0l, a0h, a1l, a1h, rl, rh;
		std::uint64_t a0, a1(0), r;
		std::string rm;
		t >> rm >> std::hex;
		if (tf._f1) {
			t >> a0h >> a0l
			  >> rh >> rl;
		} else if (tf._f2) {
			t >> a0h >> a0l
			  >> a1h >> a1l
			  >> rh >> rl;
			a1 = (uint64_t(a1h) << 32) | a1l;
		}
		a0 = (uint64_t(a0h) << 32) | a0l;
		r =  (uint64_t(rh) << 32) | rl;
		unsigned m;
		if (rm == "N" || rm == "RN") {
			m = impl::rounding_mode::nearest;
		} else if (rm == "P" || rm == "RU") {
			m = impl::rounding_mode::upward;
		} else if (rm == "M" || rm == "RD") {
			m = impl::rounding_mode::downward;
		} else if (rm == "Z" || rm == "RZ") {
			m = impl::rounding_mode::towardzero;
		} else {
			continue;
		}
		if (m != impl::rounding_mode::nearest)
			continue;
		func_data::inp_res c;
		union {
			double _d;
			uint64_t _u;
		} tt;
		tt._u = a0;
		c._a0 = tt._d;
		tt._u = a1;
		c._a1 = tt._d;
		tt._u = r;
		c._res = tt._d;
#if 0
		std::cerr << "inserting " 
			  << tf._fname 
			  << "( " << c._a0;
		if (tf._f2) 
			std::cerr << ", " << c._a1;
		std::cerr << ") ==" << c._res << std::endl;
#endif
		tf._data.push_back(c);
	}
	return true;
}

bool x86vec::test::test_data(const func_data& tf, std::ostream& os)
{
	bool rc(true);
	int errs(0);
	std::size_t calls(0);
	int64_t ticks(0);
	for (std::size_t i=0; i< tf._data.size(); ++i) {
		const func_data::inp_res& c= tf._data[i];
		v2f64 expected(c._res);
		v2f64 a0(c._a0);
		v2f64 a1(c._a1);
		v2f64 res;
		double rs;
		int64_t t0, t1;
		if (tf._f1) {
			res = tf._f1(a0);
			t0= cftal::rdtsc();
			rs = tf._f1d(c._a0);
			t1= cftal::rdtsc();
		} else {
			res = tf._f2(a0, a1);
			t0= cftal::rdtsc();
			rs = tf._f2d(c._a0, c._a1);
			t1= cftal::rdtsc();
		}
		ticks+= (t1 -t0);
		++calls;
		v2f64 ae(abs_error(expected, res));
		v2f64 re(rel_error(expected, res));
		v2f64 max_err(ae + re);
		v2f64 is_err(re > 1.0e-15);
		double tt=extract<0>(res);
#if 1
		std::cout << tf._fname << "( " 
			  << c._a0;
		if (tf._f2)
			std::cout << ", " << c._a1;
		std::cout << ")= " << tt 
			// << " :  "  << c._res 
			  << std::endl;
#endif
		double nt=c._res;
		int ulps(ulp(tt, nt));
		std::cout << "ulp: " << ulps << std::endl;
		if (ulps < 3 && no_signs(is_err)) {
			std::cout << "passed\n";
			continue;
		}
		// we found an error:
		double t=extract<0>(res);
		std::cerr << tf._fname << "( " 
			  << c._a0;
		if (tf._f2)
			std::cerr << ", " << c._a1;
		std::cerr << ")= " << t << " != "
			  << c._res << std::endl;
		std::cerr << "math lib: " << rs << std::endl;
		std::cerr << "rel_err = " << extract<0>(re)
			  << " abs_err = " << extract<0>(ae)
			  << std::endl;
		++errs;
		rc= false;
	}
	std::cout << "rc= " << rc 
		  << " test cases: " << tf._data.size()
		  << " errors: " << errs << std::endl;
	std::cout << "error rate = ";
	if (tf._data.size()) 
		std::cout << double(errs)/tf._data.size() << std::endl;
	else
		std::cout << 0.0 << std::endl;
	if (calls) {
		std::cout << "ticks per call: " 
			  << std::fixed << std::setprecision(2)
			  << double(ticks)/double(calls) 
			  << std::endl;
	}
	return rc;
}

bool x86vec::test::func(std::istream& is, bool use_native)
{
	std::cerr << std::setprecision(18) << std::scientific;
	std::cout << std::setprecision(18) << std::scientific;
	func_data tf;
	if (read_func(tf, is, use_native)==false)
		return false;
	if (read_data(tf, is)==false)
		return false;
	return test_data(tf, std::cout);
}

bool all_tests_03(bool use_native)
{
	return x86vec::test::func(std::cin, use_native);
}

void usage(const char* argv0)
{
	std::cerr << "usage: " << argv0 << " [--use-native]"
		  << std::endl;
	std::exit(3);
}

int main(int argc, char** argv)
{
	if (isatty(STDIN_FILENO))
		return 0;
	bool use_native(false);
	if (argc>2)
		usage(argv[0]);
	if (argc==2) {
		if (std::string("--use-native")!=argv[1])
			usage(argv[0]);
		use_native=true;
	}
	return (all_tests_03(use_native) ==  true) ? 0 : 3;
}
