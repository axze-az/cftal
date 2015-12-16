#if !defined (__CFTAL_TEST_OF_OPS_H__)
#define __CFTAL_TEST_OF_OPS_H__ 1

#include <cftal/config.h>
#include <cftal/select.h>
#include <cftal/test/f32_f64.h>
#include <iostream>
#include <sstream>
#include <type_traits>
#include <random>
#include <limits>

namespace cftal {
    namespace test {


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
        _T do_div(_T u, _T v) {
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

template <class _T, std::size_t _N>
bool
cftal::test::of_signed_ops<_T, _N, true>::v(_T ai, _T bi)
{
    bool rc=true;
    _T a=ai, b=bi, r;
    vec<_T, _N> va(a), vb(b), vr;
    r = std::abs(a);
    vr = abs(va);
    rc &= check(vr, r, "abs");
    return rc;
}

template <class _T, std::size_t _N>
bool
cftal::test::of_integral_ops<_T, _N, true>::v(_T ai, _T bi)
{
    bool rc=true;
    _T a=ai, b=bi, r;
    vec<_T, _N> va(a), vb(b), vr;

    // mul_lo_hi
    std::pair<_T, _T> rp=mul_lo_hi(a, b);
    std::pair<vec<_T, _N>, vec<_T, _N> > vrp=mul_lo_hi(va, vb);
    rc &= check(vrp.first, rp.first, "mul_lo_hi.first");
    rc &= check(vrp.second, rp.second, "mul_lo_hi.second");

    // left and right shifts by integer
    std::ostringstream s;
    for (std::size_t i=0; i<sizeof(_T); ++i) {

        r = ai << i;
        vr = va << i;
        s << "<< " << i;
        rc &= check(vr, r, s.str());
        s.str("");

        r = ai;
        r <<= i;
        vr = va;
        vr <<= i;
        s << "<<= " << i;
        rc &= check(vr, r, s.str());
        s.str("");

        r = ai >> i;
        vr = va >> i;
        s << ">> " << i;
        rc &= check(vr, r, s.str());
        s.str("");

        r = ai;
        r >>= i;
        vr = va;
        vr >>= i;
        s << ">>= " << i;
        rc &= check(vr, r, s.str());
        s.str("");
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

    r = a; r += b;
    vr = va; vr += vb;
    rc &= check(vr, r, "a+=b");

    r = a - b;
    vr = va - vb;
    rc &= check(vr, r, "a-b");

    r = a; r -= b;
    vr = va; vr -= vb;
    rc &= check(vr, r, "a-=b");

    r = a * b;
    vr = va * vb;
    rc &= check(vr, r, "a*b");

    r = a; r *= b;
    vr = va; vr *= vb;
    rc &= check(vr, r, "a*=b");

    r = do_div(a, b);
    vr = va / vb;
    rc &= check(vr, r, "a/b");

    // r = r /= b;
    vr = va; vr /= vb;
    rc &= check(vr, r, "a/=b");

    r = std::max(a, b);
    vr = max(va, vb);
    rc &= check(vr, r, "max");

    r = std::min(a, b);
    vr = min(va, vb);
    rc &= check(vr, r, "min");

    const bool is_signed =
        std::is_signed<_T>::value || std::is_floating_point<_T>::value;
    rc &= of_signed_ops< _T, _N, is_signed>::v(a, b);

    const bool is_integral =
        std::is_integral<_T>::value;
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
         _T(-12), _T(-21)
    };

    for (auto b=std::begin(operands), e=std::end(operands); b!=e; b+=2) {
        rc &= of_ops<_T, _N>::v(*b, *std::next(b));
        rc &= of_ops<_T, _N>::v(*std::next(b), *b);
    }

    std::mt19937 rnd;

    using distrib_type= typename std::conditional<
        std::is_floating_point<_T>::value,
        std::uniform_real_distribution<_T>,
        std::uniform_int_distribution<_T> >::type;
    distrib_type
    distrib(std::numeric_limits<_T>::lowest(),
            std::numeric_limits<_T>::max());
    const int64_t N0=0x10000ULL;
    const int64_t N=64*N0;
    for (int64_t i=0; i<N; ++i) {
        if ((i & (N0-1)) == (N0-1))
            std::cout << '.' << std::flush;
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
