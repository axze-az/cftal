#if !defined (__CFTAL_TEST_PR_FP_H__)
#define __CFTAL_TEST_PR_FP_H__ 1

#include <cftal/config.h>
#include <iostream>

namespace cftal {
    namespace test {
        
        template <typename _T>
        struct out_prec { };

        template <>
        struct out_prec<double> {
            constexpr static const int val= 22;
            constexpr static const int width = 27;
            constexpr static const char* suffix() { return ""; }
        };

        template <>
        struct out_prec<float> {
            constexpr static const int val= 13;
            constexpr static const int width= 18;
            constexpr static const char* suffix() { return "f"; }
        };


        template <typename _T>
        struct pr_fp {
            _T _v;
            pr_fp(const _T& t) : _v(t) {}
        };

        template <typename _T>
        std::ostream& operator<<(std::ostream& s, const pr_fp<_T>& v);
    }
}

template <typename _T>
std::ostream&
cftal::test::operator<<(std::ostream& s, const pr_fp<_T>& v)
{
    s << std::scientific
      << std::setprecision(out_prec<_T>::val)
      << std::showpos
      << std::setw(out_prec<_T>::width)
      << v._v
      << out_prec<_T>::suffix()
      << std::noshowpos;
      return s;
}

// local variables:
// mode: c++
// end:
#endif
