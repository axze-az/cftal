#if !defined (__CFTAL_TEST_INTOPS_H__)
#define __CFTAL_TEST_INTOPS_H__ 1

#include <cftal/config.h>

namespace cftal {

    namespace test {

        bool check_div_s16();
        bool check_div_u16();
        bool check_div_s32();
        bool check_div_u32();
        bool check_div_s64();
        bool check_div_u64();
        
        bool check_xxx_of();
        bool check_bitrev();
        bool check_popcnt();
        bool check_div();
        
    }
}

// Local variables:
// mode: c++
// end:
#endif
