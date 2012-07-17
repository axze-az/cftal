#include "bitops.h"
#include "x86vec_test.h"
#include "x86vec_ref.h"
#include <iostream>
#include <iomanip>

namespace x86vec
{
        namespace test
        {
                bool check_div_s16();
                bool check_div_u16();

                template <class _T, class _REF, class _PR>
                bool check_div_16(const char* msg);
        }
}

template <class _T, class _REF, class _PR>
bool x86vec::test::check_div_16(const char* msg)
{
	enum {
		REF,
		DIV,
		CDIV,
		LAST
	};
	std::uint64_t ts[LAST];
	std::uint64_t tcur[LAST+1];
	ts[REF] = ts[DIV] = ts[CDIV] =0;
        for(int32_t i = 0; i < 0x10000; ++i) {
		typename _T::element_type ii= i;
                if ((i & 0xff)==0xff) {
                        std::cout << '\r' << msg << ": " 
				  << std::setw(6) << ii << std::flush;
		}
		_T v(ii);
		divisor<_T, typename _T::element_type> vd(ii);
                for(int32_t j = 0; j < 0x10000; j += 8) {
			_T u(j, j + 1, j + 2, j + 3,
			     j + 4, j + 5, j + 6, j + 7);
			__m128i __r_ref = impl::make_zero_int::v();
			_T q_ref, q_div, q_cdiv;
			_T r_ref, r_div, r_cdiv;
			tcur[REF] = cftal::rdtsc();
                        q_ref =_REF::ref(u(), v(), &__r_ref);
			r_ref = __r_ref;
			tcur[DIV] = cftal::rdtsc();
			q_div = u / v;
			r_div = cftal::remainder(u, v, q_div);
			tcur[CDIV] = cftal::rdtsc();
			q_cdiv = u / vd;
			r_cdiv = cftal::remainder(u, v, q_cdiv);
			tcur[LAST] = cftal::rdtsc();
			r_div = u % v;
			r_cdiv = u % vd;
			_T q_cmp_div(q_ref == q_div);
			_T r_cmp_div(r_ref == r_div);
			_T q_cmp_cdiv(q_ref == q_cdiv);
			_T r_cmp_cdiv(r_ref == r_cdiv);
			if (!all_signs(q_cmp_div) || !all_signs(r_cmp_div) || 
			    !all_signs(q_cmp_cdiv) || !all_signs(r_cmp_cdiv)) {
				std::cout << '\r' << msg << std::endl
                                          << _PR(u()) << " / " 
                                          << ii << std::endl
					  << "Q_REF: "
                                          << _PR(q_ref()) << std::endl
					  << "R_REF: " 
					  << _PR(r_ref()) << std::endl
					  << "Q_DIV: "
					  << _PR(q_div()) << std::endl
					  << "Q_DIV:"
					  << _PR(r_div()) << std::endl
					  << "Q_CDIV: "
					  << _PR(q_cdiv()) << std::endl
					  << "R_CDIV: "
					  << _PR(r_cdiv()) << std::endl;
                                return false;
			}
			ts[REF] += tcur[DIV] - tcur[REF];
			ts[DIV] += tcur[CDIV] - tcur[DIV];
			ts[CDIV] += tcur[LAST] - tcur[CDIV];
                }
        }
	std::cout << '\n' << msg << std::endl
		  << "ref:  " << double(ts[REF])/(0x10000LL*0x10000/8)
		  << std::endl
		  << "div:  " << double(ts[DIV])/(0x10000LL*0x10000/8)
		  << std::endl
		  << "cdiv: " << double(ts[CDIV])/(0x10000LL*0x10000/8)
		  << std::endl;
        return true;
}

bool x86vec::test::check_div_u16()
{
        return check_div_16<v8u16, impl::div_u16, pr_v8u16>("div_u16");
}

bool x86vec::test::check_div_s16()
{
        return check_div_16<v8s16, impl::div_s16, pr_v8s16>("div_s16");
}

bool x86vec::test::check_div()
{
        bool rc(true);
        rc &= check_div_u16();
        rc &= check_div_s16();
        return true;
}
// kate: indent-mode cstyle; indent-width 8; replace-tabs on;
