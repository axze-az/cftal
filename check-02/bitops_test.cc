#include <bitops.h>
#include <iostream>
#include <iomanip>

template <class _T>
bool check_div_res(_T n, _T d, _T q, _T qr, _T r, _T rr)
{
	if (qr != q) {
		std::cout << n << " / " << d << " = "
			  << q << " != expected " << qr
			  << std::endl;
		return false;
	}
	if (rr != r) {
		std::cout << n << " % " << d << " = "
			  << r << " != expected " << rr
			  << std::endl;
		return false;
	}
	return true;
}

bool bitops::test::div_u16()
{
	const unsigned N =0x10000;
	for (unsigned d = 0; d < N; ++d) {
		divisor<uint16_t, uint16_t> di(d);
		uint16_t dd(d);
		if ( (d & 0x3FF) == 0x3FF) {
			std::cout << "udiv_16:  " 
				  << std::setw(8) 
				  << "xxx"
				  << " / "
				  << std::setw(8)
				  << dd
				  << '\r' << std::flush;
		}
		for (unsigned n= 0; n< N; ++n) {
			uint16_t nn(n);
			uint16_t qr, rr, q, r;
			qr = d == 0 ? -1 : nn / dd;
			rr = d == 0 ? nn : nn % dd;
			q = nn / di;
			r = nn % di;
			if (check_div_res(nn, dd, q, qr, r, rr)==false)
				return false;
		}
	}
	std::cout << "\ndiv_u16 passed\n";
	return true;
}

bool bitops::test::div_s16()
{
	const unsigned N =0x10000;
	for (unsigned d = 0; d < N; ++d) {
		divisor<int16_t, int16_t> di(d);
		int16_t dd(d);
		if ( (d & 0x3FF) == 0x3FF) {
			std::cout << "sdiv_16:  " 
				  << std::setw(8) 
				  << "xxx"
				  << " / "
				  << std::setw(8)
				  << dd
				  << '\r' << std::flush;
		}
		for (unsigned n= 0; n< N; ++n) {
			int16_t nn(n);
			int16_t qr, rr, q, r;
			qr = d == 0 ? -1 : nn / dd;
			rr = d == 0 ? nn : nn % dd;
			q = nn / di;
			r = nn % di;
			if (check_div_res(nn, dd, q, qr, r, rr)==false)
				return false;
		}
	}
	std::cout << "\ndiv_s16 passed\n";
	return true;
}

bool bitops::test::div_u32()
{
	return true;
}

bool bitops::test::div_s32()
{
	return true;
}
