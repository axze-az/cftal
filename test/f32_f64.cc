//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/f32_f64.h"
#include "cftal/cast.h"
#include <cmath>
#include <iomanip>

double cftal::test::make_double(unsigned sgn, unsigned exp, uint64_t sig)
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

float cftal::test::make_float(unsigned sgn, unsigned exp, uint32_t sig)
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


std::ostream&
cftal::test::operator<<(std::ostream& s, const ulp_stats& us)
{
    s << ulp_stats_to_stream(us, true);
    return s;
}

std::ostream&
cftal::test::operator<<(std::ostream& s, const ulp_stats_to_stream& uss)
{
    const ulp_stats& us= *(uss._us);
    bool pr_hist= uss._hist;
    s << us._cnt << " cases (with " << us._nans
      << " NAN results), with delta: "
      << us._ulps << " rate: " << double(us._ulps)/double(us._cnt) << '\n';
    double _ulps=0.0;
    for (const auto& t : us._devs) {
        if (pr_hist) {
            int32_t tfa=std::abs(t.first);
            if (tfa <= us.lin_max) {
                // std::numeric_limits<int32_t>::min() also lands here
                s << std::setw(27) << t.first << " "
                  << std::setw(11) << t.second << '\n';
            } else if (t.first < 0) {
                int32_t ts= -((tfa>>1)+1);
                s << std::setw(11) << t.first << " ... "
                  << std::setw(11) << ts << " "
                  << std::setw(11) << t.second << '\n';
            } else if (t.first > 0) {
                int32_t ts= (tfa>>1)+1;
                s << std::setw(11) << ts << " ... "
                  << std::setw(11) << t.first << " "
                  << std::setw(11) << t.second << '\n';
            }
        }
        if (t.first)
            _ulps += std::fabs(double(t.first)*double(t.second));
    }
    _ulps /= us._cnt;
    _ulps += 0.5;
    s << "ulps: " << _ulps;
    if (!us._devs.empty()) {
        s << " , max delta: "
          << std::begin(us._devs)->first
          << " / "
          << std::prev(std::end(us._devs))->first
          << " bits\n";
    } else {
        s << '\n';
    }
    if (us._faithful.first) {
        s << "faithful: "
          << (us._faithful.second ? "perhaps yes" : "no") << '\n';
    }
    return s;
}

bool cftal::test::f_eq(double a, double b)
{
    return (a == b) || ((a != a) && (b != b));
}

bool cftal::test::f_eq(float a, float b)
{
    return (a == b) || ((a != a) && (b != b));
}

cftal::int32_t
cftal::test::distance(double a, double b)
{
    int64_t ai = as<int64_t>(a);
    int64_t bi = as<int64_t>(b);
    int64_t abs_ai = ai & ~(1ULL<<63);
    int64_t abs_bi = bi & ~(1ULL<<63);
    bool sgn_a = abs_ai != ai;
    bool sgn_b = abs_bi != bi;
    int32_t d=0;
    if ((sgn_a == sgn_b) || ((abs_ai|abs_bi) == 0)) {
        d= abs_bi - abs_ai;
    } else {
        // a < 0 | b < 0 --> d = abs_ai + abs_bi
        d= abs_bi + abs_ai;
    }
    // a < b positive sign
    // a > b negative sign
    if (sgn_b)
        d = -d;
    return d;
}

cftal::int32_t
cftal::test::distance(float a, float b)
{
    int32_t ai = as<int32_t>(a);
    int32_t bi = as<int32_t>(b);
    int32_t abs_ai = ai & ~(1U<<31);
    int32_t abs_bi = bi & ~(1U<<31);
    bool sgn_a = abs_ai != ai;
    bool sgn_b = abs_bi != bi;
    int32_t d=0;
    if ((sgn_a == sgn_b) || ((abs_ai|abs_bi) == 0)) {
        d= abs_bi - abs_ai;
    } else {
        // a < 0 | b < 0 --> d = abs_ai + abs_bi
        d= abs_bi + abs_ai;
    }
    // a < b positive sign
    // a > b negative sign
    if (sgn_b)
        d = -d;
    return d;
}

namespace {

    template <typename _T>
    bool cmp_ulp(_T a, _T b, uint32_t ulp, cftal::test::ulp_stats* us)
    {
        bool r;
        int32_t u=0;
        if ((r=cftal::test::f_eq(a, b)) == false) {
            u = cftal::test::distance(a, b);
            //(u >= -int32_t(ulp)) && (u <= int32_t(ulp)))
            if (std::abs(u) <= int32_t(ulp))
                r=true;
#if 0
            else
                std::cout << "distance " << u << std::endl;
#endif
        }
        if (us != nullptr) {
            int32_t isn= ((a!=a) || (b!=b)) ? 1 : 0;
            us->inc(u, isn);
        }
        return r;
    }

    template <typename _T>
    bool is_faithful(_T a, const std::tuple<_T, _T, _T>& b)
    {
        _T b0, b1, b2;
        std::tie(b0, b1, b2) = b;
        if ((a!=a) &&
            ((b0!=b0) || (b1!=b1) || (b2!=b2)))
            return true;
        return a == b0 || a == b1 || a == b2;
    }

}

bool cftal::test::f_eq_ulp(double a, double b, uint32_t ulp, ulp_stats* us)
{
    return cmp_ulp(a, b, ulp, us);
}

bool cftal::test::f_eq_ulp(float a, float b, uint32_t ulp, ulp_stats* us)
{
    return cmp_ulp(a, b, ulp, us);
}

bool cftal::test::f_eq_ulp(double a,
                           const std::tuple<double, double, double>& b,
                           uint32_t ulp, ulp_stats* us)
{
    bool r=cmp_ulp(a, std::get<0>(b), ulp, us);
    if (us != nullptr) {
        bool f= is_faithful(a, b);
#if 0
        if (f==false) {
            r=false;
        }
#endif
        us->faithful(f);
    }
    return r;
}

bool cftal::test::f_eq_ulp(float a,
                           const std::tuple<float, float, float>& b,
                           uint32_t ulp, ulp_stats* us)
{
    bool r=cmp_ulp(a, std::get<0>(b), ulp, us);
    if (us != nullptr) {
        bool f= is_faithful(a, b);
#if 0
        if (f==false) {
            r=false;
        }
#endif
        us->faithful(f);
    }
    return r;
}


