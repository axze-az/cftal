#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <x86vec_fvec.h>

namespace x86vec {

	namespace test {

		template <class _T>
		_T rel_error(const _T& a, const _T& b);

		template <class _T>
		_T abs_error(const _T& a, const _T& b);

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
			v2f64 (*_f2)(arg_type a, arg_type b);
			std::vector<inp_res> _data;

			func_data() : _f1(nullptr), _f2(nullptr), _data() {}
		};

		std::string delete_comment(const std::string& s);
		bool read_func(func_data& tf, std::istream& is);
		bool read_data(func_data& tf, std::istream& is);
		bool test_data(const func_data& tf, std::ostream& os);

		bool func(std::istream& is);
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

std::string x86vec::test::delete_comment(const std::string& s)
{
	std::string::size_type n(s.find('#'));
	std::string r(n == std::string::npos ? s : s.substr(0, n));
	return r;
}

bool x86vec::test::read_func(func_data& tf, std::istream& is)
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
			tf._f1 = x86vec::cos;
		} else if (f == "sin") {
			tf._f1 = x86vec::sin;
		} else if (f == "exp") {
			tf._f1 = x86vec::exp;
		} else if (f == "log") {
			tf._f1 = x86vec::log;
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
	for (std::size_t i=0; i< tf._data.size(); ++i) {
		const func_data::inp_res& c= tf._data[i];
		v2f64 expected(c._res);
		v2f64 a0(c._a0);
		v2f64 a1(c._a1);
		v2f64 res;
		if (tf._f1) {
			res = tf._f1(a0);
		} else {
			res = tf._f2(a0, a1);
		}
		v2f64 ae(abs_error(expected, res));
		v2f64 re(rel_error(expected, res));
		v2f64 max_err(ae + re);
		v2f64 is_err(max_err > 1.0e-16);

		double tt=extract<0>(res);
		std::cout << tf._fname << "( " 
			  << c._a0;
		if (tf._f2)
			std::cout << ", " << c._a1;
		std::cout << ")= " << tt << " :  "
			  << c._res << std::endl;
		if (no_signs(is_err))
			continue;
		rc= false;
		// we found an error:
		double t=extract<0>(res);
		std::cerr << tf._fname << "( " 
			  << c._a0;
		if (tf._f2)
			std::cerr << ", " << c._a1;
		std::cerr << ")= " << t << " != "
			  << c._res << std::endl;
	}
	return rc;
}

bool x86vec::test::func(std::istream& is)
{
	std::cerr << std::setprecision(18) << std::scientific;
	std::cout << std::setprecision(18) << std::scientific;
	func_data tf;
	if (read_func(tf, is)==false)
		return false;
	if (read_data(tf, is)==false)
		return false;
	return test_data(tf, std::cout);
}


bool all_tests_03()
{
	return x86vec::test::func(std::cin);
}

int main(int argc, char** argv)
{
	return all_tests_03() ==  true ? 0 : 3;
}
