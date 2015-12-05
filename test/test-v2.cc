#include <cftal/config.h>
#include <cftal/test/of_vec.h>
#include <cftal/test/of_vec_v2.h>

int main()
{
    bool rc(true);
    rc &= cftal::test::check_v2<double>();
    rc &= cftal::test::check_v2<int32_t>();
    rc &= cftal::test::check_v2<uint32_t>();
    rc &= cftal::test::check_v2<int64_t>();
    rc &= cftal::test::check_v2<uint64_t>();
    // rc &= cftal::test::check_v4<float>();
    // rc &= cftal::test::check_v4<int32_t>();
    // rc &= cftal::test::check_v4<uint32_t>();
    return rc == true ? 0 : 1;
}
