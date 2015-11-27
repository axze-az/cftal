#include "cftal/test/f32_f64.h"

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

    r = std::abs(a);
    vr = abs(va);
    rc &= check(vr, r, "abs");
    
    return rc;
}

template <class _T, std::size_t _N>
bool 
cftal::test::fp_ops<_T, _N>::v()
{    
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
    
    std::cout << "testing vXf64" << std::endl;
    bool rd=cftal::test::fp_ops_up_to<double, 32>::v();
    if (rd==false)
        std::cerr << "double test failed" << std::endl;
    std::cout << "testing vXf32" << std::endl;
    bool rf=cftal::test::fp_ops_up_to<float, 64>::v();
    if (rf==false)
        std::cerr<< "float test failed" << std::endl;
    rc = rd && rf;
    return rc==true ? 0 : 1;
}
    
