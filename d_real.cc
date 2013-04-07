#include "d_real.h"
#include <cstring>
#include <stdexcept>

cftal::d_real<double>
cftal::str_to_d_double(const char* p, std::size_t n)
{
	const char* pe=p+n;
	char ch;
	int sign = 0;
	int point = -1;
	int digits =0;
	int exponent= 0;
	bool sign_exponent=0;
	int pos=0;
	int in_exp=-1;
	d_real<double> r(0.0);

	// skip leading spaces
	while (*p == ' ')
		++p;

	while (p < pe) {
		ch = *p;
		switch (ch) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			if (in_exp>=0 ) {
				exponent *= 10;
				exponent += ch - '0';
			} else {
				r *= 10.0;
				r += double(ch - '0');
				++digits;
			}
			break;
		case '.':
			if (point >= 0)
				throw std::runtime_error("double decimal point");
			point = digits;
			break;
		case '+':
			if (in_exp>=0) {
				if (in_exp != pos-1)
					throw std::runtime_error("double + in exponent");
				sign_exponent = +1;
			} else { 
				if (digits > 0) 
					throw std::runtime_error("double + ");
				sign = +1;
			}
			break;
		case '-':
			if (in_exp>=0) {
				if (in_exp != pos-1)
					throw std::runtime_error("double - in exponent");
				sign_exponent = -1;
			} else { 
				if (digits > 0) 
					throw std::runtime_error("double - ");
				sign = -1;
			}
			break;
		case 'e':
		case 'E':
			in_exp = pos;
			break;
		default:
			throw std::runtime_error("invalid character");
		}
		++pos;
		++p;
	}

	if (in_exp>=0) {
		if (sign_exponent == -1)
			exponent = -exponent;
	}

	if (point >= 0) {
		exponent -= (digits - point);
	}

	if (exponent != 0) {
		r *= powi(d_real<double>(10.0), exponent);
	}
	r = (sign == -1) ? -r : r;
	r += d_real<double>(0.0);
	return r;
}

cftal::d_real<double>
cftal::operator "" _dd(const char* pp)
{
	return str_to_d_double(pp, std::strlen(pp));
}

cftal::d_real<double>
test1()
{
	using namespace cftal;

	return 1.234234234_dd;
}
