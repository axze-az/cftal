#include "cftal/test/f32_f64.h"
#include <random>
#include <limits>

namespace cftal {
    namespace test {


        template <class _T, std::size_t _N>
        struct fp_ops {
            static bool v();
            static bool v(_T ai, _T bi);
        };

        template <class _T, std::size_t _N>
        struct fp_ops_up_to {
            static bool v() {
                bool r=fp_ops<_T, _N>::v();
                r &= fp_ops_up_to<_T, _N/2>::v();
                return r;
            }
        };

        template <class _T>
        struct fp_ops_up_to<_T, 1> {
            static bool v() {
                return fp_ops<_T, 1>::v();
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
cftal::test::fp_ops<_T, _N>::v(_T ai, _T bi)
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

    r = std::abs(a);
    vr = abs(va);
    rc &= check(vr, r, "abs");

    bool br;
    typename vec<_T, _N>::mask_type vcr;

    br = a < b;
    vcr = va < vb;
    rc &= check_cmp(vcr, br, "==");

    br = a < b;
    vcr = va < vb;
    rc &= check_cmp(vcr, br, "<");

    br = a <= b;
    vcr = va <= vb;
    rc &= check_cmp(vcr, br, "<=");

    br = a == b;
    vcr = va == vb;
    rc &= check_cmp(vcr, br, "==");

    br = a != b;
    vcr = va != vb;
    rc &= check_cmp(vcr, br, "!=");

    br = a >= b;
    vcr = va >= vb;
    rc &= check_cmp(vcr, br, ">=");

    br = a > b;
    vcr = va > vb;
    rc &= check_cmp(vcr, br, ">");

    return rc;
}

template <class _T, std::size_t _N>
bool
cftal::test::fp_ops<_T, _N>::v()
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
        rc &= fp_ops<_T, _N>::v(*b, *std::next(b));
        rc &= fp_ops<_T, _N>::v(*std::next(b), *b);
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
        rc &= fp_ops<_T, _N>::v(va, va);
        rc &= fp_ops<_T, _N>::v(va, vb);
        va = -ah;
        rc &= fp_ops<_T, _N>::v(va, vb);
        va = ah; vb= -bh;
        rc &= fp_ops<_T, _N>::v(va, vb);
        va = -ah;
        rc &= fp_ops<_T, _N>::v(va, vb);
    }
    std::cout << std::endl;

    if (rc == true) {
        std::cout << __func__ << _N << " test passed " << std::endl;
    } else {
        std::cerr << __func__ << _N << " test failed " << std::endl;
    }
    return rc;
}

int main()
{
    bool rc=true;
    bool rt;
#if 0
    std::cout << "testing vXf64" << std::endl;
    rt=cftal::test::fp_ops_up_to<double, 8>::v();
    if (rt==false)
        std::cerr << "double test failed" << std::endl;
    rc &= rt;

    std::cout << "testing vXf32" << std::endl;
    rt=cftal::test::fp_ops_up_to<float, 16>::v();
    if (rt==false)
        std::cerr<< "float test failed" << std::endl;
    rc &= rt;

#else
    std::cout << "testing vXu64" << std::endl;
    rt=cftal::test::fp_ops_up_to<uint64_t, 2>::v();
    if (rt==false)
        std::cerr<< "uint64_t test failed" << std::endl;
    rc &= rt;

    std::cout << "testing vXs64" << std::endl;
    rt=cftal::test::fp_ops_up_to<int64_t, 2>::v();
    if (rt==false)
        std::cerr<< "int64_t test failed" << std::endl;
    rc &= rt;
#endif
    return rc==true ? 0 : 1;
}

