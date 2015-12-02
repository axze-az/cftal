#include <cftal/d_real.h>
#include <cftal/test/f32_f64.h>
#include <functional>
#include <iomanip>
#include <random>

#if defined (__x86_64__)

namespace cftal {
    namespace test {
        template <class _T, class _R>
        class check_d_real {
            
            static 
            _R make_ref(d_real<_T> a);

            static 
            bool
            check(d_real<_T> res, _R expected, const char* msg);
                        
            static 
            bool 
            ops(d_real<_T> a0, d_real<_T> a1);
            
            static bool ops();
            
        public:
            static bool v();
        };
        
        template <class _T>
        struct check_d_real_traits;
        
        template <>
        struct check_d_real_traits<double> {
            static
            constexpr __float128 eps() { 
                return std::pow(2, -106);
            }
        };
        
        template <>
        struct check_d_real_traits<float> {
            static
            constexpr double eps() { 
                return std::pow(2, -48);
            }
        };
        
    }
}

   
inline
__float128 abs(__float128 x) {
    return x<0 ? -x : x;
}
    


template <class _T, class _R>
_R 
cftal::test::check_d_real<_T, _R>::make_ref(d_real<_T> a)
{
    _R r = a.h();
    r += a.l();
    return r;
}

template <class _T, class _R>
bool
cftal::test::check_d_real<_T, _R>::
check(d_real<_T> res, _R expected, const char* msg)
{
    _R rs=make_ref(res);
    bool r=true;
    if (rel_err(rs, expected) > check_d_real_traits<_T>::eps() ) {
        std::cerr << double(rs) << ' '  << double(expected) << ' ' 
                  << msg << std::endl;
        std::cerr << "rel_err: " << double(rel_err(rs, expected)) << std::endl;
        std::cerr << "abs_err:" << double(abs_err(rs, expected)) << std::endl;
        r = false;
    }
    return r;
}

template <class _T, class _R>
bool
cftal::test::check_d_real<_T, _R>::
ops(d_real<_T> a0, d_real<_T> b0)
{
    _R a = make_ref(a0);
    _R b = make_ref(b0);
    _R r;
    d_real<_T> va=a0, vb=b0, vr;
    bool rc=true;

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
    
    r = a / b;
    vr = va / vb;
    rc &= check(vr, r, "a/b");    

    r = a; r *= b;
    vr = va; vr *= vb;
    rc &= check(vr, r, "a/=b");        
    
    r = std::max(a, b);
    vr = max(va, vb);
    rc &= check(vr, r, "max");

    r = std::min(a, b);
    vr = min(va, vb);
    rc &= check(vr, r, "min");
    
    r = a > 0 ? a : -a;
    vr = abs(va);
    rc &= check(vr, r, "abs");
    
    return rc;    
}


template <class _T, class _R>
bool
cftal::test::check_d_real<_T, _R>::ops()
{
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

    bool rc =true;    
    for (auto b=std::begin(operands), e=std::end(operands); b!=e; b+=2) {
        rc &= ops(*b, *std::next(b));
        rc &= ops(*std::next(b), *b);
    }
    std::mt19937 rnd;
    std::uniform_real_distribution<_T> 
        distrib(0, std::numeric_limits<_T>::max());
    const int64_t N0=0x10000ULL;
    const int64_t N=72*N0;
    for (int64_t i=0; i<N; ++i) {
        if ((i & (N0-1)) == (N0-1))
            std::cout << '.' << std::flush;
        _T ah, bh;
        ah = distrib(rnd);
        bh = distrib(rnd);        
        d_real<_T> va=ah, vb=bh;        
        rc &= ops(va, vb);
        va = -ah; 
        rc &= ops(va, vb);
        va = ah; vb= -bh;
        rc &= ops(va, vb);
        va = -ah; 
        rc &= ops(va, vb);
    }     
    std::cout << std::endl;    
    if (rc == true) {
        std::cout << __func__ << " test passed " << std::endl;
    } else {
        std::cerr << __func__ << " test failed " << std::endl;        
    }            
    return rc;
}

template <class _T, class _R>
bool
cftal::test::check_d_real<_T, _R>::v()
{
    return ops();
}

int main()
{
    std::cerr << std::setprecision(20);
    std::cerr << "d_real<double>:\n";
    bool rd= cftal::test::check_d_real<double, __float128>::v();
    std::cerr << "d_real<float>:\n";
    bool rf= cftal::test::check_d_real<float, double>::v();
    bool r = rd == true && rf == true;
    return r == true ? 0 : 1;
}

#else
int main()
{
    return 0;
}
#endif
