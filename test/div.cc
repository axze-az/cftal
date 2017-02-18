//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <cftal/test/intops.h>
#include <iostream>
#include <iomanip>
#include <random>
#include <cftal/vec.h>
#include <cftal/divisor.h>

namespace cftal {

    namespace test {

        struct div_type {
            enum {
                REF,
                DIV,
                CDIV,
                LAST
            };
        };
        
        template <class _V, class _REF>
        bool check_div_16(const char* msg);

        template <class _V, class _REF, class _RND>
        bool check_div_32_one_rnd(
            const typename _V::value_type i,
            const divisor<_V, typename _V::value_type>& dd,
            _RND& rnd,
            const char* msg,
            std::uint64_t* ts);
        template <class _T, class _REF>
        bool check_div_32_rnd(const char* msg);

        template <class _V, class _REF, class _RND>
        bool check_div_64_one_rnd(
            const typename _V::value_type i,
            const divisor<_V, typename _V::value_type>& dd,
            _RND& rnd,
            const char* msg,
            std::uint64_t* ts);
        template <class _T, class _REF>
        bool check_div_64_rnd(const char* msg);
    }
}

template <class _T, class _REF>
bool cftal::test::check_div_16(const char* msg)
{
#if !defined (__SSE2__)
    return true;
#else
    std::uint64_t ts[div_type::LAST];
    std::uint64_t tcur[div_type::LAST+1];
    ts[div_type::REF] = ts[div_type::DIV] = ts[div_type::CDIV] =0;
    divisor<_T, typename _T::value_type> vd(1);
    for(int32_t i = 0; i < 0x10000; ++i) {
        typename _T::value_type ii= i;
        if ((i & 0xff)==0xff) {
            std::cout << '\r' << msg << ": "
                      << std::setw(6) << ii << std::flush;
        }
        _T v(ii);
        vd.set(ii);
        for(int32_t j = 0; j < 0x10000; j += 8) {
            using value_type = typename _T::value_type;
            _T u= { value_type(j),
                    value_type(j + 1),
                    value_type(j + 2),
                    value_type(j + 3),
                    value_type(j + 4),
                    value_type(j + 5),
                    value_type(j + 6),
                    value_type(j + 7)};
            __m128i __r_ref = x86::impl::make_zero_int::v();
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
            // r_div = u % v;
            // r_cdiv = u % vd;
            typename _T::mask_type q_cmp_div(q_ref == q_div);
            typename _T::mask_type r_cmp_div(r_ref == r_div);
            typename _T::mask_type q_cmp_cdiv(q_ref == q_cdiv);
            typename _T::mask_type r_cmp_cdiv(r_ref == r_cdiv);
            if (!all_of(q_cmp_div) || !all_of(r_cmp_div) ||
                !all_of(q_cmp_cdiv) || !all_of(r_cmp_cdiv)) {
                std::cout << '\r' << msg << std::endl
                          << u << " / "
                          << ii << std::endl
                          << "Q_REF:  "
                          << q_ref << std::endl
                          << "R_REF:  "
                          << r_ref << std::endl
                          << "Q_DIV:  "
                          << q_div << std::endl
                          << "R_DIV:  "
                          << r_div << std::endl
                          << "Q_CDIV: "
                          << q_cdiv << std::endl
                          << "R_CDIV: "
                          << r_cdiv << std::endl;
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
#endif
}

template <class _T, class _REF, class _RND>
bool cftal::test::
check_div_32_one_rnd(typename _T::value_type ii,
                     const divisor<_T, typename _T::value_type>& dd,
                     _RND& rnd,
                     const char* msg,
                     std::uint64_t* ts)
{
#if !defined (__SSE2__)
    return true;
#else
    std::uint64_t tcur[div_type::LAST+1];
    _T v(ii);
    for(int32_t j = 0; j < 0x10000; j += 4) {
        typename _T::value_type j0= rnd.next();
        typename _T::value_type j1= rnd.next();
        typename _T::value_type j2= rnd.next();
        typename _T::value_type j3= rnd.next();
        _T u={j0, j1, j2, j3};
        __m128i __r_ref = x86::impl::make_zero_int::v();
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
        // r_div = u % v;
        // r_cdiv = u % dd;
        typename _T::mask_type q_cmp_div(q_ref == q_div);
        typename _T::mask_type r_cmp_div(r_ref == r_div);
        typename _T::mask_type q_cmp_cdiv(q_ref == q_cdiv);
        typename _T::mask_type r_cmp_cdiv(r_ref == r_cdiv);
        if (!all_of(q_cmp_div) || !all_of(r_cmp_div) ||
            !all_of(q_cmp_cdiv) || !all_of(r_cmp_cdiv)) {
            std::cout << '\r' << msg << std::endl
                      << u << " / "
                      << ii << std::endl
                      << "Q_REF:  "
                      << q_ref << std::endl
                      << "R_REF:  "
                      << r_ref << std::endl
                      << "Q_DIV:  "
                      << q_div << std::endl
                      << "R_DIV:  "
                      << r_div << std::endl
                      << "Q_CDIV: "
                      << q_cdiv << std::endl
                      << "R_CDIV: "
                      << r_cdiv << std::endl;
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
#endif
}

template <class _T, class _REF>
bool cftal::test::check_div_32_rnd(const char* msg)
{
    std::uint64_t ts[div_type::LAST];
    ts[div_type::REF] = ts[div_type::DIV] = ts[div_type::CDIV] =0;

    struct rng_t {
        std::uniform_int_distribution<std::uint32_t> _distribution;
        std::mt19937 _rnd;
        uint32_t next() { return _distribution(_rnd); }
    } rng;
    
    
    typedef typename _T::value_type element_type;
    element_type di(0);
    divisor<_T, element_type> dd(di);

    di = element_type(1U<< ((sizeof(element_type)*8)-1));
    dd.set(di);
    if (!check_div_32_one_rnd<_T, _REF, rng_t>(di, dd, rng, msg, ts))
        return false;
    di = 0;
    dd.set(di);
    if (!check_div_32_one_rnd<_T, _REF, rng_t>(di, dd, rng, msg, ts))
        return false;
    di = 1;
    dd.set(di);
    if (!check_div_32_one_rnd<_T, _REF, rng_t>(di, dd, rng, msg, ts))
        return false;
    di = element_type(-1ULL);
    dd.set(di);
    if (!check_div_32_one_rnd<_T, _REF, rng_t>(di, dd, rng, msg, ts))
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
        if (!check_div_32_one_rnd<_T, _REF, rng_t>(di, dd,
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

template <class _T, class _REF, class _RND>
bool cftal::test::
check_div_64_one_rnd(typename _T::value_type ii,
                     const divisor<_T, typename _T::value_type>& dd,
                     _RND& rnd,
                     const char* msg,
                     std::uint64_t* ts)
{
#if !defined (__SSE2__)
    return true;
#else
    std::uint64_t tcur[div_type::LAST+1];
    _T v(ii);
    for(int32_t j = 0; j < 0x10000; j += 2) {
        typename _T::value_type j0= rnd.next();
        typename _T::value_type j1= rnd.next();
        _T u={j0, j1};
        __m128i __r_ref = x86::impl::make_zero_int::v();
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
        // r_div = u % v;
        // r_cdiv = u % dd;
        typename _T::mask_type q_cmp_div(q_ref == q_div);
        typename _T::mask_type r_cmp_div(r_ref == r_div);
        typename _T::mask_type q_cmp_cdiv(q_ref == q_cdiv);
        typename _T::mask_type r_cmp_cdiv(r_ref == r_cdiv);
        if (!all_of(q_cmp_div) || !all_of(r_cmp_div) ||
            !all_of(q_cmp_cdiv) || !all_of(r_cmp_cdiv)) {
            std::cout << '\r' << msg << std::endl
                      << u << " / "
                      << ii << std::endl
                      << "Q_REF:  "
                      << q_ref << std::endl
                      << "R_REF:  "
                      << r_ref << std::endl
                      << "Q_DIV:  "
                      << q_div << std::endl
                      << "R_DIV:  "
                      << r_div << std::endl
                      << "Q_CDIV: "
                      << q_cdiv << std::endl
                      << "R_CDIV: "
                      << r_cdiv << std::endl;
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
#endif
}

template <class _T, class _REF>
bool cftal::test::check_div_64_rnd(const char* msg)
{
    std::uint64_t ts[div_type::LAST];
    ts[div_type::REF] = ts[div_type::DIV] = ts[div_type::CDIV] =0;

    struct rng_t {
        std::uniform_int_distribution<std::uint64_t> _distribution;
        std::mt19937_64 _rnd;
        uint64_t next() { return _distribution(_rnd); }
    } rng;
    
    typedef typename _T::value_type element_type;
    element_type di(0);
    divisor<_T, element_type> dd(di);

    di = element_type(1UL<< ((sizeof(element_type)*8)-1));
    dd.set(di);
    if (!check_div_64_one_rnd<_T, _REF, rng_t>(di, dd, rng, msg, ts))
        return false;
    di = 0;
    dd.set(di);
    if (!check_div_64_one_rnd<_T, _REF, rng_t>(di, dd, rng, msg, ts))
        return false;
    di = 1;
    dd.set(di);
    if (!check_div_64_one_rnd<_T, _REF, rng_t>(di, dd, rng, msg, ts))
        return false;
    di = element_type(-1ULL);
    dd.set(di);
    if (!check_div_64_one_rnd<_T, _REF, rng_t>(di, dd, rng, msg, ts))
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
        if (!check_div_64_one_rnd<_T, _REF, rng_t>(di, dd,
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

bool cftal::test::check_div_u16()
{
#if !defined (__SSE2__)
    return true;
#else
    return check_div_16<v8u16, x86::div_u16>("div_u16");
#endif
}

bool cftal::test::check_div_s16()
{
#if !defined (__SSE2__)
    return true;
#else
    return check_div_16<v8s16, x86::div_s16>("div_s16");
#endif
}

bool cftal::test::check_div_u32()
{
#if !defined (__SSE2__)
    return true;
#else
    return check_div_32_rnd<v4u32, x86::div_u32>("div_u32");
#endif
}

bool cftal::test::check_div_s32()
{
#if !defined (__SSE2__)
    return true;
#else
    return check_div_32_rnd<v4s32, x86::div_s32>("div_s32");
#endif
}

bool cftal::test::check_div_u64()
{
#if !defined (__SSE2__)
    return true;
#else
    return check_div_64_rnd<v2u64, x86::div_u64>("div_u64");
#endif
}

bool cftal::test::check_div_s64()
{
#if !defined (__SSE2__)
    return true;
#else
    return check_div_64_rnd<v2s64, x86::div_s64>("div_s64");
#endif
}


bool cftal::test::check_div()
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
// kate: indent-mode cstyle; indent-width 4; replace-tabs on;
