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
                bool check_div_s32();
                bool check_div_u32();
                bool check_div_s64();
                bool check_div_u64();

                struct div_type {
                        enum {
                                REF,
                                DIV,
                                CDIV,
                                LAST
                        };
                };

                template <class _V, class _REF, class _PR>
                bool check_div_16(const char* msg);

                template <class _V, class _REF, class _PR, class _RND>
                bool check_div_32_one_rnd(
			const typename _V::element_type i,
			const divisor<_V, typename _V::element_type>& dd,
                        _RND& rnd,
			const char* msg,
                        std::uint64_t* ts);
                template <class _T, class _REF, class _PR>
                bool check_div_32_rnd(const char* msg);

                template <class _V, class _REF, class _PR, class _RND>
                bool check_div_64_one_rnd(
			const typename _V::element_type i,
			const divisor<_V, typename _V::element_type>& dd,
                        _RND& rnd,
			const char* msg,
                        std::uint64_t* ts);
                template <class _T, class _REF, class _PR>
                bool check_div_64_rnd(const char* msg);
        }
}


template <class _T, class _REF, class _PR>
bool x86vec::test::check_div_16(const char* msg)
{
        std::uint64_t ts[div_type::LAST];
        std::uint64_t tcur[div_type::LAST+1];
        ts[div_type::REF] = ts[div_type::DIV] = ts[div_type::CDIV] =0;
	divisor<_T, typename _T::element_type> vd(1);
        for(int32_t i = 0; i < 0x10000; ++i) {
                typename _T::element_type ii= i;
                if ((i & 0xff)==0xff) {
                        std::cout << '\r' << msg << ": "
                                  << std::setw(6) << ii << std::flush;
                }
                _T v(ii);
		vd.set(ii);
                for(int32_t j = 0; j < 0x10000; j += 8) {
                        _T u(j, j + 1, j + 2, j + 3,
                             j + 4, j + 5, j + 6, j + 7);
                        __m128i __r_ref = impl::make_zero_int::v();
                        _T q_ref, q_div, q_cdiv;
                        _T r_ref, r_div, r_cdiv;
                        tcur[div_type::REF] = cftal::rdtsc();
                        q_ref =_REF::ref(u(), v(), &__r_ref);
                        r_ref = __r_ref;
                        tcur[div_type::DIV] = cftal::rdtsc();
                        q_div = u / v;
                        r_div = cftal::remainder(u, v, q_div);
                        tcur[div_type::CDIV] = cftal::rdtsc();
                        q_cdiv = u / vd;
                        r_cdiv = cftal::remainder(u, v, q_cdiv);
                        tcur[div_type::LAST] = cftal::rdtsc();
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
                                          << "Q_REF:  "
                                          << _PR(q_ref()) << std::endl
                                          << "R_REF:  "
                                          << _PR(r_ref()) << std::endl
                                          << "Q_DIV:  "
                                          << _PR(q_div()) << std::endl
                                          << "R_DIV:  "
                                          << _PR(r_div()) << std::endl
                                          << "Q_CDIV: "
                                          << _PR(q_cdiv()) << std::endl
                                          << "R_CDIV: "
                                          << _PR(r_cdiv()) << std::endl;
                                return false;
                        }
                        ts[div_type::REF] +=
                                tcur[div_type::DIV] - tcur[div_type::REF];
                        ts[div_type::DIV] +=
                                tcur[div_type::CDIV] - tcur[div_type::DIV];
                        ts[div_type::CDIV] +=
                                tcur[div_type::LAST] - tcur[div_type::CDIV];
                }
        }
        std::cout << '\n' << msg << " clocks per division " << std::endl
                  << "ref:  "
                  << double(ts[div_type::REF])/(0x10000LL*0x10000)
                  << std::endl
                  << "div:  "
                  << double(ts[div_type::DIV])/(0x10000LL*0x10000)
                  << std::endl
                  << "cdiv: "
                  << double(ts[div_type::CDIV])/(0x10000LL*0x10000)
                  << std::endl;
        return true;
}

template <class _T, class _REF, class _PR, class _RND>
bool x86vec::test::
check_div_32_one_rnd(typename _T::element_type ii,
		     const divisor<_T, typename _T::element_type>& dd,
		     _RND& rnd,
		     const char* msg,
		     std::uint64_t* ts)
{
        std::uint64_t tcur[div_type::LAST+1];
        _T v(ii);
	for(int32_t j = 0; j < 0x10000; j += 4) {
		typename _T::element_type j0= rnd.next();
		typename _T::element_type j1= rnd.next();
		typename _T::element_type j2= rnd.next();
		typename _T::element_type j3= rnd.next();
		_T u(j0, j1, j2, j3);
		__m128i __r_ref = impl::make_zero_int::v();
		_T q_ref, q_div, q_cdiv;
		_T r_ref, r_div, r_cdiv;
		tcur[div_type::REF] = cftal::rdtsc();
		q_ref =_REF::ref(u(), v(), &__r_ref);
		r_ref = __r_ref;
		tcur[div_type::DIV] = cftal::rdtsc();
		q_div = u / v;
		r_div = cftal::remainder(u, v, q_div);
		tcur[div_type::CDIV] = cftal::rdtsc();
		q_cdiv = u / dd;
		r_cdiv = cftal::remainder(u, v, q_cdiv);
		tcur[div_type::LAST] = cftal::rdtsc();
		r_div = u % v;
		r_cdiv = u % dd;
		_T q_cmp_div(q_ref == q_div);
		_T r_cmp_div(r_ref == r_div);
		_T q_cmp_cdiv(q_ref == q_cdiv);
		_T r_cmp_cdiv(r_ref == r_cdiv);
		if (!all_signs(q_cmp_div) || !all_signs(r_cmp_div) ||
		    !all_signs(q_cmp_cdiv) || !all_signs(r_cmp_cdiv)) {
			std::cout << '\r' << msg << std::endl
				  << _PR(u()) << " / "
				  << ii << std::endl
				  << "Q_REF:  "
				  << _PR(q_ref()) << std::endl
				  << "R_REF:  "
				  << _PR(r_ref()) << std::endl
				  << "Q_DIV:  "
				  << _PR(q_div()) << std::endl
				  << "R_DIV:  "
				  << _PR(r_div()) << std::endl
				  << "Q_CDIV: "
				  << _PR(q_cdiv()) << std::endl
				  << "R_CDIV: "
				  << _PR(r_cdiv()) << std::endl;
			return false;
		}
		ts[div_type::REF] +=
			tcur[div_type::DIV] - tcur[div_type::REF];
		ts[div_type::DIV] +=
			tcur[div_type::CDIV] - tcur[div_type::DIV];
		ts[div_type::CDIV] +=
			tcur[div_type::LAST] - tcur[div_type::CDIV];
	}
        return true;
}

template <class _T, class _REF, class _PR>
bool x86vec::test::check_div_32_rnd(const char* msg)
{
        std::uint64_t ts[div_type::LAST];
        ts[div_type::REF] = ts[div_type::DIV] = ts[div_type::CDIV] =0;
	typedef cmwc_rng<std::uint32_t> rng_t;
	rng_t rng(42);
	typedef typename _T::element_type element_type;
	element_type di;
	divisor<_T, element_type> dd(di);

	di = element_type(1U<< ((sizeof(element_type)*8)-1));
	dd.set(di);
	if (!check_div_32_one_rnd<_T, _REF, _PR, rng_t>(di, dd, rng, msg, ts))
		return false;
	di = 0;
	dd.set(di);
	if (!check_div_32_one_rnd<_T, _REF, _PR, rng_t>(di, dd, rng, msg, ts))
		return false;
	di = 1;
	dd.set(di);
	if (!check_div_32_one_rnd<_T, _REF, _PR, rng_t>(di, dd, rng, msg, ts))
		return false;
	di = element_type(-1ULL);
	dd.set(di);
	if (!check_div_32_one_rnd<_T, _REF, _PR, rng_t>(di, dd, rng, msg, ts))
		return false;

        for(std::int32_t i = 4; i < 0x10000; ++i) {
                di= rng.next();
                if ((i & 0x1ff)==0x1ff) {
                        std::cout << '\r' << msg << ": "
                                  << std::setw(18) << di << " "
				  << std::setw(10)
				  << 100*double(i)/0x10000 << "%"
				  << std::flush;
                }
		dd.set(di);
		if (!check_div_32_one_rnd<_T, _REF, _PR, rng_t>(di, dd, 
								rng, msg, ts))
			return false;
	}
        std::cout << '\n' << msg << " clocks per division " << std::endl
                  << "ref:  "
                  << double(ts[div_type::REF])/(0x10000LL*0x10000)
                  << std::endl
                  << "div:  "
                  << double(ts[div_type::DIV])/(0x10000LL*0x10000)
                  << std::endl
                  << "cdiv: "
                  << double(ts[div_type::CDIV])/(0x10000LL*0x10000)
                  << std::endl;
	return true;
}

template <class _T, class _REF, class _PR, class _RND>
bool x86vec::test::
check_div_64_one_rnd(typename _T::element_type ii,
		     const divisor<_T, typename _T::element_type>& dd,
		     _RND& rnd,
		     const char* msg,
		     std::uint64_t* ts)
{
        std::uint64_t tcur[div_type::LAST+1];
        _T v(ii);
	for(int32_t j = 0; j < 0x10000; j += 4) {
		typename _T::element_type j0= rnd.next();
		typename _T::element_type j1= rnd.next();
		_T u(j0, j1);
		__m128i __r_ref = impl::make_zero_int::v();
		_T q_ref, q_div, q_cdiv;
		_T r_ref, r_div, r_cdiv;
		tcur[div_type::REF] = cftal::rdtsc();
		q_ref =_REF::ref(u(), v(), &__r_ref);
		r_ref = __r_ref;
		tcur[div_type::DIV] = cftal::rdtsc();
		q_div = u / v;
		r_div = cftal::remainder(u, v, q_div);
		tcur[div_type::CDIV] = cftal::rdtsc();
		q_cdiv = u / dd;
		r_cdiv = cftal::remainder(u, v, q_cdiv);
		tcur[div_type::LAST] = cftal::rdtsc();
		r_div = u % v;
		r_cdiv = u % dd;
		_T q_cmp_div(q_ref == q_div);
		_T r_cmp_div(r_ref == r_div);
		_T q_cmp_cdiv(q_ref == q_cdiv);
		_T r_cmp_cdiv(r_ref == r_cdiv);
		if (!all_signs(q_cmp_div) || !all_signs(r_cmp_div) ||
		    !all_signs(q_cmp_cdiv) || !all_signs(r_cmp_cdiv)) {
			std::cout << '\r' << msg << std::endl
				  << _PR(u()) << " / "
				  << ii << std::endl
				  << "Q_REF:  "
				  << _PR(q_ref()) << std::endl
				  << "R_REF:  "
				  << _PR(r_ref()) << std::endl
				  << "Q_DIV:  "
				  << _PR(q_div()) << std::endl
				  << "R_DIV:  "
				  << _PR(r_div()) << std::endl
				  << "Q_CDIV: "
				  << _PR(q_cdiv()) << std::endl
				  << "R_CDIV: "
				  << _PR(r_cdiv()) << std::endl;
			return false;
		}
		ts[div_type::REF] +=
			tcur[div_type::DIV] - tcur[div_type::REF];
		ts[div_type::DIV] +=
			tcur[div_type::CDIV] - tcur[div_type::DIV];
		ts[div_type::CDIV] +=
			tcur[div_type::LAST] - tcur[div_type::CDIV];
	}
        return true;
}

template <class _T, class _REF, class _PR>
bool x86vec::test::check_div_64_rnd(const char* msg)
{
        std::uint64_t ts[div_type::LAST];
        ts[div_type::REF] = ts[div_type::DIV] = ts[div_type::CDIV] =0;
	typedef cmwc_rng<std::uint64_t> rng_t;
	rng_t rng(42);
	typedef typename _T::element_type element_type;
	element_type di;
	divisor<_T, element_type> dd(di);

	di = element_type(1UL<< ((sizeof(element_type)*8)-1));
	dd.set(di);
	if (!check_div_64_one_rnd<_T, _REF, _PR, rng_t>(di, dd, rng, msg, ts))
		return false;
	di = 0;
	dd.set(di);
	if (!check_div_64_one_rnd<_T, _REF, _PR, rng_t>(di, dd, rng, msg, ts))
		return false;
	di = 1;
	dd.set(di);
	if (!check_div_64_one_rnd<_T, _REF, _PR, rng_t>(di, dd, rng, msg, ts))
		return false;
	di = element_type(-1ULL);
	dd.set(di);
	if (!check_div_64_one_rnd<_T, _REF, _PR, rng_t>(di, dd, rng, msg, ts))
		return false;

        for(std::int32_t i = 4; i < 0x10000; ++i) {
                di= rng.next();
                if ((i & 0x1ff)==0x1ff) {
                        std::cout << '\r' << msg << ": "
                                  << std::setw(22) << di << " "
				  << std::setw(10)
				  << 100*double(i)/0x10000 << "%"
				  << std::flush;
                }
		dd.set(di);
		if (!check_div_64_one_rnd<_T, _REF, _PR, rng_t>(di, dd, 
								rng, msg, ts))
			return false;
	}
        std::cout << '\n' << msg << " clocks per division " << std::endl
                  << "ref:  "
                  << double(ts[div_type::REF])/(0x10000LL*0x10000)
                  << std::endl
                  << "div:  "
                  << double(ts[div_type::DIV])/(0x10000LL*0x10000)
                  << std::endl
                  << "cdiv: "
                  << double(ts[div_type::CDIV])/(0x10000LL*0x10000)
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

bool x86vec::test::check_div_u32()
{
        return check_div_32_rnd<v4u32, impl::div_u32, pr_v4u32>("div_u32");
}

bool x86vec::test::check_div_s32()
{
        return check_div_32_rnd<v4s32, impl::div_s32, pr_v4s32>("div_s32");
}

bool x86vec::test::check_div_u64()
{
        return check_div_64_rnd<v2u64, impl::div_u64, pr_v2u64>("div_u64");
}

bool x86vec::test::check_div_s64()
{
        return check_div_64_rnd<v2s64, impl::div_s64, pr_v2s64>("div_s64");
}


bool x86vec::test::check_div()
{
        bool rc(true);
        rc &= check_div_u64();
	if (rc == false)
		return rc;
        rc &= check_div_s64();
	if (rc == false)
		return rc;
        rc &= check_div_u32();
	if (rc == false)
		return rc;
        rc &= check_div_s32();
	if (rc == false)
		return rc;
        rc &= check_div_u16();
	if (rc == false)
		return rc;
        rc &= check_div_s16();
	return rc;
}
// kate: indent-mode cstyle; indent-width 8; replace-tabs on;
