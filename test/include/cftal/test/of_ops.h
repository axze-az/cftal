//
// Copyright (C) 2010-2022 Axel Zeuner
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
#if !defined (__CFTAL_TEST_OF_OPS_H__)
#define __CFTAL_TEST_OF_OPS_H__ 1

#include <cftal/config.h>
#include <cftal/select.h>
#include <cftal/test/uniform_distribution.h>
#include <cftal/test/f32_f64.h>
#include <cftal/type_traits.h>
#include <iostream>
#include <sstream>
#include <random>
#include <limits>

namespace cftal {
    namespace test {

        class err_msg {
            bool _id_valid;
            int _id;
            const char* _m;
        public:
            err_msg(const char* pm) : _id_valid(false), _id(0), _m(pm) {}
            err_msg(const char* pm, int vv)
                : _id_valid(true), _id(vv), _m(pm) {}
            const char* m() const { return _m; }
            bool id_valid() const { return _id_valid; }
            int id() const { return _id; }
        };
        std::ostream& operator<<(std::ostream& s, const err_msg& m);

        template <class _T, std::size_t _N, bool _IS_SIGNED>
        struct of_signed_ops {
            static bool v(_T ai, _T bi) { return true; }
        };

        template <class _T, std::size_t _N>
        struct of_signed_ops<_T, _N, true> {
            static bool v(_T ai, _T bi);
        };

        template <class _T, std::size_t _N, bool _IS_INTEGRAL>
        struct of_integral_ops {
            static bool v(_T ai, _T bi) { return true; }
        };

        template <class _T, std::size_t _N>
        struct of_integral_ops<_T, _N, true> {
            static bool v(_T ai, _T bi);
        };

        template <class _T, std::size_t _N>
        struct of_ops {
            static bool v();
            static bool v(_T ai, _T bi);
        };

        template <class _T, std::size_t _N>
        struct of_ops_up_to {
            static bool v() {
                bool r=of_ops<_T, _N>::v();
                r &= of_ops_up_to<_T, _N/2>::v();
                return r;
            }
        };

        template <class _T>
        struct of_ops_up_to<_T, 1> {
            static bool v() {
                return of_ops<_T, 1>::v();
            }
        };

        template <class _T>
        typename std::enable_if<is_integral<_T>::value, _T>::type
        do_div(_T u, _T v) {
            if (v==0)
                return ~_T(0);
            return u/v;
        }

        inline
        double do_div(double u, double v)
        {
            return u/v;
        }

        inline
        float do_div(float u, float v)
        {
            return u/v;
        }
    }
}

inline
std::ostream&
cftal::test::operator<<(std::ostream& s, const err_msg& m)
{
    s << m.m();
    if (m.id_valid()) {
        s << ' ' << m.id();
    }
    return s;
}


template <class _T, std::size_t _N>
inline
bool
cftal::test::of_signed_ops<_T, _N, true>::v(_T ai, _T bi)
{
    bool rc=true;
    _T a=ai, b=bi, r;
    vec<_T, _N> va(a), vb(b), vr;
    using std::abs;
    r = abs(a);
    vr = abs(va);
    rc &= check(vr, r, "abs");
    return rc;
}

template <class _T, std::size_t _N>
inline
bool
cftal::test::of_integral_ops<_T, _N, true>::v(_T ai, _T bi)
{
    bool rc=true;
    _T a=ai, b=bi, r;

    using v_t = vec<_T, _N>;

    v_t va(a), vb(b), vr;

    // mul_lo_hi
    std::pair<_T, _T> rp=mul_lo_hi(a, b);
    std::pair<v_t, v_t> vrp=mul_lo_hi(va, vb);
    rc &= check(vrp.first, rp.first, "mul_lo_hi.first");
    rc &= check(vrp.second, rp.second, "mul_lo_hi.second");

    // left and right shifts by integer
    for (std::size_t i=0; i<sizeof(_T)*8; ++i) {
        // <<
        r = ai << i;
        vr = va << i;
        rc &= check(vr, r, err_msg("<<", i));
        // <<=
        r = ai;
        r <<= i;
        vr = va;
        vr <<= i;
        rc &= check(vr, r, err_msg("<<=", i));
        // >>
        r = ai >> i;
        vr = va >> i;
        rc &= check(vr, r, err_msg(">>", i));
        // >>=
        r = ai;
        r >>= i;
        vr = va;
        vr >>= i;
        rc &= check(vr, r, err_msg(">>=", i));
    }
    // left and right shifts by vector
    _T ss[_N], sr[_N], sref[_N];
    for (std::size_t i=0; i<sizeof(_T)*8; i+= _N) {
        for (std::size_t j=0; j<_N; ++j) {
            ss[j] = i+j;
        }
        v_t s= mem<v_t>::load(ss, _N);
        // <<
        vr = va << s;
        mem<v_t>::store(sr, vr);
        for (std::size_t j=0; j<_N; ++j) {
            sref[j] = ai << ss[j];
        }
        rc &= check(vr, sref, err_msg("<< (vec)"));
        if (rc==false) {
            std::cout << va << std::endl
                      << s << std::endl
                      << vr << std::endl;
            std::exit(3);
        }
        // <<=
        vr = va;
        vr <<= s;
        rc &= check(vr, sref, err_msg("<<= (vec)"));
        if (rc==false) {
            std::cout << va << std::endl
                      << s << std::endl
                      << vr << std::endl;
            std::exit(3);
        }
        // >>
        vr = va >> s;
        mem<v_t>::store(sr, vr);
        for (std::size_t j=0; j<_N; ++j) {
            sref[j] = ai >> ss[j];
        }
        rc &= check(vr, sref, err_msg(">> (vec)"));
        if (rc==false) {
            std::cout << va << std::endl
                      << s << std::endl
                      << vr << std::endl;
            std::exit(3);
        }
        // >>=
        vr = va;
        vr >>= s;
        rc &= check(vr, sref, err_msg(">>= (vec)"));
        if (rc==false) {
            std::cout << va << std::endl
                      << s << std::endl
                      << vr << std::endl;
            std::exit(3);
        }
    }
    return rc;
}

template <class _T, std::size_t _N>
bool
cftal::test::of_ops<_T, _N>::v(_T ai, _T bi)
{
    bool rc=true;
    _T a=ai, b=bi, r;
    vec<_T, _N> va(a), vb(b), vr(0);
    r = -a;
    vr = -va;
    rc &= check(vr, r, "-a");

    r = +a;
    vr = +va;
    rc &= check(vr, r, "+a");

    r = a + b;
    vr = va + vb;
    rc &= check(vr, r, "a+b");
    vr = va; vr += vb;
    rc &= check(vr, r, "a+=b");

    r = a - b;
    vr = va - vb;
    rc &= check(vr, r, "a-b");
    vr = va; vr -= vb;
    rc &= check(vr, r, "a-=b");

    r = a * b;
    vr = va * vb;
    rc &= check(vr, r, "a*b");
    vr = va; vr *= vb;
    rc &= check(vr, r, "a*=b");

    r = do_div(a, b);
    vr = va / vb;
    rc &= check(vr, r, "a/b");
    vr = va; vr /= vb;
    rc &= check(vr, r, "a/=b");

    r = a * a  + b;
    vr = va * va + b;
    rc &= check(vr, r, "a*a +b");

    r=  a* a - b;
    vr = va * va  -b;
    rc &= check(vr, r, "a*a -b");

    r= b -a*a;
    vr = b - va * va;
    rc &= check(vr, r, "b - a * a");

    r = std::max(a, b);
    vr = max(va, vb);
    rc &= check(vr, r, "max");

    r = std::min(a, b);
    vr = min(va, vb);
    rc &= check(vr, r, "min");

    const bool is_signed =
        cftal::is_signed<_T>::value || cftal::is_floating_point<_T>::value;
    rc &= of_signed_ops< _T, _N, is_signed>::v(a, b);

    const bool is_integral =
        cftal::is_integral<_T>::value;
    rc &= of_integral_ops<_T, _N, is_integral>::v(a, b);

    bool br;
    typename vec<_T, _N>::mask_type vcr;

    br = a < b;
    vcr = va < vb;
    rc &= check_cmp(vcr, br, "==");

    r = cftal::select(br, a, b);
    vr = cftal::select(vcr, va, vb);
    rc &= check(vr, r, "select after ==");

    br = a < b;
    vcr = va < vb;
    rc &= check_cmp(vcr, br, "<");

    r = cftal::select(br, a, b);
    vr = cftal::select(vcr, va, vb);
    rc &= check(vr, r, "select after <");

    br = a <= b;
    vcr = va <= vb;
    rc &= check_cmp(vcr, br, "<=");

    r = cftal::select(br, a, b);
    vr = cftal::select(vcr, va, vb);
    rc &= check(vr, r, "select after <=");

    br = a == b;
    vcr = va == vb;
    rc &= check_cmp(vcr, br, "==");

    r = cftal::select(br, a, b);
    vr = cftal::select(vcr, va, vb);
    rc &= check(vr, r, "select after ==");

    br = a != b;
    vcr = va != vb;
    rc &= check_cmp(vcr, br, "!=");

    r = cftal::select(br, a, b);
    vr = cftal::select(vcr, va, vb);
    rc &= check(vr, r, "select after !=");

    br = a >= b;
    vcr = va >= vb;
    rc &= check_cmp(vcr, br, ">=");

    r = cftal::select(br, a, b);
    vr = cftal::select(vcr, va, vb);
    rc &= check(vr, r, "select after >=");

    br = a > b;
    vcr = va > vb;
    rc &= check_cmp(vcr, br, ">");

    r = cftal::select(br, a, b);
    vr = cftal::select(vcr, va, vb);
    rc &= check(vr, r, "select after >");

    if (rc == false) {
        std::cerr << "va: "  << va << '\n'
                  << "vb: " << vb << '\n'
                  << "a:  " << a << '\n'
                  << "b:  " << b << '\n';
        std::exit(3);
    }
    return rc;
}

template <class _T, std::size_t _N>
bool
cftal::test::of_ops<_T, _N>::v()
{
    std::cout << __func__ << _N << ' ' << std::flush;
    bool rc=true;

    static const _T operands[] = {
         _T(4), _T(2),
         _T(-4), _T(-2),
         _T(4), _T(0),
         _T(-4), _T(0),
         _T(0), _T(4),
         _T(0), _T(-4),
         _T(32), _T(21),
         _T(-32), _T(21),
         _T(32), _T(-21),
         _T(-32), _T(-21),
         _T(12), _T(-21),
         _T(-12), _T(21),
         _T(12), _T(21),
         _T(-12), _T(-21),
         _T(1), _T(0),
         _T(0), _T(0),
         _T(-1), _T(0)
    };

    for (auto b=std::begin(operands), e=std::end(operands); b!=e; b+=2) {
        rc &= of_ops<_T, _N>::v(*b, *std::next(b));
        rc &= of_ops<_T, _N>::v(*std::next(b), *b);
    }

    std::mt19937 rnd;

    using distrib_type= typename std::conditional<
        cftal::is_floating_point<_T>::value,
        uniform_real_distribution<_T>,
        std::uniform_int_distribution<_T> >::type;
    distrib_type
    distrib(std::numeric_limits<_T>::lowest(),
            std::numeric_limits<_T>::max());
    const int64_t N0=0x10000ULL;
    for (uint32_t j=0; j<72; ++j) {
        for (std::size_t i=0; i<N0; ++i) {
            _T ah, bh;
            ah = distrib(rnd);
            bh = distrib(rnd);
            _T va=ah, vb=bh;
            rc &= of_ops<_T, _N>::v(va, va);
            rc &= of_ops<_T, _N>::v(va, vb);
            va = -ah;
            rc &= of_ops<_T, _N>::v(va, vb);
            va = ah; vb= -bh;
            rc &= of_ops<_T, _N>::v(va, vb);
            va = -ah;
            rc &= of_ops<_T, _N>::v(va, vb);
        }
        std::cout << '.' << std::flush;
    }
    std::cout << std::endl;
    if (rc == true) {
        std::cout << __func__ << _N << " test passed " << std::endl;
    } else {
        std::cerr << __func__ << _N << " test failed " << std::endl;
    }
    return rc;
}

// local variables:
// mode: c++
// end:
#endif
