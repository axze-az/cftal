#include <cftal/config.h>
#include <cftal/test/of_vec.h>
#include <cftal/test/of_vec_v8.h>

int main()
{
    bool rc(true);
    rc &= cftal::test::check_v8<float>();
    return rc == true ? 0 : 1;
}
