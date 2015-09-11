#include <cftal/config.h>
#include <cftal/test/of_vec.h>
#include <cftal/test/of_vec_v8.h>

namespace cftal {
    namespace test {
        bool spec_v8u32();
    }
}

bool cftal::test::spec_v8u32()
{
}

int main()
{
    bool rc(true);
    rc &= cftal::test::check_v8<uint32_t>();
    return rc == true ? 0 : 1;
}
