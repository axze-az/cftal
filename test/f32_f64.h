#if !defined (__CFTAL_TEST_F32_F64_H__)
#define __CFTAL_TEST_F32_F64_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>

namespace cftal {
    namespace test {

        double make_double(unsigned sgn, unsigned exp, uint64_t sig);
        float make_float(unsigned sgn, unsigned exp, uint32_t sig);

        // compare a and b, returns also true for a==NAN and b
        // == NAN
        bool f_eq(double a, double b);
        bool f_eq(float a, float b);
        
    }
}


#endif
