#include <cftal/config.h>
#include <cftal/test/of_vec.h>
#include <cftal/test/of_vec_v4.h>

int main()
{
    bool rc(true);
    rc &= cftal::test::check_v4<uint32_t>();
    return rc == true ? 0 : 1;
}
