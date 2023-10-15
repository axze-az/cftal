//
// Copyright (C) 2010-2023 Axel Zeuner
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
//
#include "cftal/test/f32_f64.h"
#include "cftal/as.h"
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

cftal::test::ulp_stats::deviations::deviations()
{
#if __USE_ARRAY_DEVIATIONS>0
    for (int i=0; i<32; ++i) {
        int64_t k=(1LL << (31-i));
        _v[i].first = -k;
        _v[_size-1-i].first = k;
    }
    _v[_zero_offset].first=0;
    for (int i=1; i<=lin_max; ++i) {
        _v[_zero_offset + i].first = i;
        _v[_zero_offset - i].first =-i;
    }
#endif
}

void
cftal::test::ulp_stats::deviations::inc(int32_t ulp)
{
#if __USE_ARRAY_DEVIATIONS>0
    int32_t aulp=std::abs(ulp);
    int32_t rulp;
    if (__likely(aulp <= lin_max)) {
        // std::numeric_limits<int32_t>::min() also lands here
        rulp = ulp;
    } else {
        // round up/down to the next power of 2
        uint32_t log2_u= sizeof(int32_t)*8-lzcnt(uint32_t(aulp-1))+1;
        rulp = ulp < 0 ?
               -int32_t(log2_u)-lin_max : int32_t(log2_u)+lin_max;
    }
    ++_v[_zero_offset + rulp].second;
#else
    int32_t aulp=std::abs(ulp);
    int64_t rulp;
    if (__likely(aulp <= lin_max)) {
        // std::numeric_limits<int32_t>::min() also lands here
        rulp = ulp;
    } else {
        // round up/down to the next power of 2
        uint32_t log2_u= sizeof(int32_t)*8-lzcnt(uint32_t(aulp-1));
        rulp= 1U << log2_u;
        rulp= ulp < 0 ? -rulp : rulp;
    }
    std::lock_guard<lock_type> _lck(_mtx);
    _v[rulp] += 1;
#endif
}

bool
cftal::test::ulp_stats::deviations::empty()
    const
{
#if __USE_ARRAY_DEVIATIONS>0
    for (size_t i=0; i<std::size(_v); ++i) {
        if (_v[i].second != 0)
            return false;
    }
    return true;
#else
    return _v.empty();
#endif
}

cftal::test::ulp_stats::deviations::const_iterator
cftal::test::ulp_stats::deviations::begin()
    const
{
    return std::cbegin(_v);
}

cftal::test::ulp_stats::deviations::const_iterator
cftal::test::ulp_stats::deviations::end()
    const
{
    return std::cend(_v);
}

cftal::test::ulp_stats::deviations::const_iterator
cftal::test::ulp_stats::deviations::min_ulp()
    const
{
#if __USE_ARRAY_DEVIATIONS>0
    const_iterator p=nullptr;
    for (size_t i=0; i<std::size(_v); ++i) {
        if (_v[i].second != 0) {
            p= _v+i;
            break;
        }
    }
    return p;
#else
    return std::cbegin(_v);
#endif
}

cftal::test::ulp_stats::deviations::const_iterator
cftal::test::ulp_stats::deviations::max_ulp()
    const
{
#if __USE_ARRAY_DEVIATIONS>0
    const value_type* p=nullptr;
    for (int i=std::size(_v); i>0; --i) {
        int o=i-1;
        if (_v[o].second != 0) {
            p= _v+o;
            break;
        }
    }
    return p;
#else
    return std::prev(std::cend(_v));
#endif
}

void
cftal::test::ulp_stats::
inc(int32_t ulp, bool is_nan,
    bool nan_not_calculated, bool nan_unexpected)
{
    _cnt += 1;
    uint32_t au= ulp != 0 ? 1 : 0;
    _ulps += au;
    if (is_nan)
        _nans += 1;
    if (nan_not_calculated| nan_unexpected) {
        if (nan_not_calculated)
            _nans_not_calculated += 1;
        if (nan_unexpected)
            _nans_unexpected += 1;
    } else {
        _devs.inc(ulp);
    }
}

void
cftal::test::ulp_stats::
faithful(bool v)
{
#if 1
    _faithful &= (v==true ? 1 : 0);
#else
    std::lock_guard<lock_type> _lck(_mtx_faithful);
    _faithful.first = true;
    if (_faithful.second == true)
        _faithful.second =v;
#endif
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
      << us._ulps << " rate: "
      << double(us._ulps)/double(us._cnt-us._nans) << '\n'
      << std::setw(28)
      << "nans not calculated "
      << std::setw(11)
      << us._nans_not_calculated << '\n'
      << std::setw(28)
      << "nans unexpected "
      << std::setw(11)
      << us._nans_unexpected << '\n';
    double _ulps=0.0;
    for (const auto& t : us._devs) {
        if (!t.second)
            continue;
        if (pr_hist) {
            int64_t tfa=std::abs(t.first);
            if (tfa <= us._devs.lin_max) {
                // std::numeric_limits<int32_t>::min() also lands here
                s << std::setw(27) << t.first << " "
                  << std::setw(11) << t.second << '\n';
            } else if (t.first < 0) {
                int64_t ts= -((tfa>>1)+1);
                s << std::setw(11) << t.first << " ... "
                  << std::setw(11) << ts << " "
                  << std::setw(11) << t.second << '\n';
            } else if (t.first > 0) {
                int64_t ts= (tfa>>1)+1;
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
          << us._devs.min_ulp()->first
          << " / "
          << us._devs.max_ulp()->first
          << " bits\n";
    } else {
        s << '\n';
    }
#if 1
    uint32_t t= us._faithful;
    if ((t & 2)==0) {
        s << "faithful: "
          << (t & 1 ? "perhaps yes" : "no") << '\n';
    }
#else
    if (us._faithful.first) {
        s << "faithful: "
          << (us._faithful.second ? "perhaps yes" : "no") << '\n';
    }
#endif
    return s;
}

bool cftal::test::f_eq(double a, double b)
{
    return ((a != 0.0) && (a == b)) || ((a != a) && (b != b)) ||
        ((a==0.0) && (a==b) &&
         (std::copysign(1.0, a) == std::copysign(1.0, b)));
}

bool cftal::test::f_eq(float a, float b)
{
    return ((a !=0.0f) && (a == b)) || ((a != a) && (b != b)) ||
        ((a==b) && (a==0.0f) &&
         (std::copysign(1.0f, a) == std::copysign(1.0f, b)));
}

bool cftal::test::f_eq(f16_t a, f16_t b)
{
    using std::copysign;
    return ((a !=0.0_f16) && (a == b)) || ((a != a) && (b != b)) ||
        ((a==b) && (a==0.0_f16) &&
         (copysign(1.0_f16, a) == copysign(1.0_f16, b)));
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
    int64_t d=0;
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
    // +-0 gives 2
    if ((sgn_a != sgn_b) && ((abs_ai|abs_bi) == 0)) {
        if (sgn_a)
            d=+2;
        else
            d=-2;
    }
    // +-Inf gives +- max-2
    if ((sgn_a != sgn_b) && ((abs_ai|abs_bi) == 0x7FF0'0000'0000'0000L)) {
        if (sgn_a)
            d=(std::numeric_limits<int32_t>::max()-2);
        else
            d=-(std::numeric_limits<int32_t>::max()-2);
    }
    // saturate d
    static const auto d_min=-int64_t(std::numeric_limits<int32_t>::max()-2);
    d = std::max(d, d_min);
    static const auto d_max=int64_t(std::numeric_limits<int32_t>::max()-2);
    d = std::min(d, d_max);
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
    // +-0 gives 2
    if ((sgn_a != sgn_b) && ((abs_ai|abs_bi) == 0)) {
        if (sgn_a)
            d=+2;
        else
            d=-2;
    }
    // +-Inf gives +-max-2
    if ((sgn_a != sgn_b) && ((abs_ai|abs_bi) == 0x7F800000)) {
        if (sgn_a)
            d=std::numeric_limits<int32_t>::max()-2;
        else
            d=-(std::numeric_limits<int32_t>::max()-2);
    }
    return d;
}

cftal::int32_t
cftal::test::distance(f16_t a, f16_t b)
{
    int16_t ai = as<int16_t>(a);
    int16_t bi = as<int16_t>(b);
    int16_t abs_ai = ai & ~(1U<<15);
    int16_t abs_bi = bi & ~(1U<<15);
    bool sgn_a = abs_ai != ai;
    bool sgn_b = abs_bi != bi;
    int16_t d=0;
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
    // +-0 gives 2
    if ((sgn_a != sgn_b) && ((abs_ai|abs_bi) == 0)) {
        if (sgn_a)
            d=+2;
        else
            d=-2;
    }
    // +-Inf gives +-max-2
    if ((sgn_a != sgn_b) && ((abs_ai|abs_bi) == 0x7c00)) {
        if (sgn_a)
            d=std::numeric_limits<int16_t>::max()-2;
        else
            d=-(std::numeric_limits<int16_t>::max()-2);
    }
    return d;
}


namespace {

    template <typename _T>
    int32_t get_ulp(_T a, _T b)
    {
        int32_t u=0;
        if (a != b ||(a==_T(0)) || (b==_T(0))) {
            u = cftal::test::distance(a, b);
        }
        return u;
    }

    template <typename _T>
    bool cmp_ulp(_T a, _T b, int32_t ulp, cftal::test::ulp_stats* us)
    {
        bool ref_nan = b!=b;
        bool res_nan = a!=a;
        int32_t iu=0;
        if (ref_nan == false) {
            iu = get_ulp(a, b);
        }
        if (us != nullptr) {
            bool nan_not_calculated= (ref_nan == true) && (res_nan == false);
            bool nan_unexpected= (ref_nan == false) && (res_nan == true);
            us->inc(iu, ref_nan, nan_not_calculated, nan_unexpected);
        }
        int32_t u=abs(iu);
        return (u <= ulp) && (ref_nan == res_nan);
    }


    template <typename _T>
    bool is_faithful(_T a, const std::tuple<_T, _T, _T>& b)
    {
        _T b0, b1, b2;
        std::tie(b0, b1, b2) = b;
        if ((a!=a) &&
            ((b0!=b0) || (b1!=b1) || (b2!=b2))) {
            return true;
        }
        using cftal::test::f_eq;
        return  f_eq(a, b0) || f_eq(a, b1) || f_eq(a, b2);
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

bool cftal::test::f_eq_ulp(f16_t a, f16_t b, uint32_t ulp, ulp_stats* us)
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

bool cftal::test::f_eq_ulp(f16_t a,
                           const std::tuple<f16_t, f16_t, f16_t>& b,
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

