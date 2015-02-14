#include <cftal/config.h>
#include <cftal/test/of_vec.h>
#include <cftal/test/of_vec_v2.h>

namespace cftal {

    namespace test {

        template <class _T>
        bool check_v2();
    }
}

template <class _T>
bool cftal::test::check_v2()
{
    bool rc{true /* check_select_v2<_T>() */ };
    rc &= check_perm1_v2<_T>();
    rc &= check_perm2_v2<_T>();
    return rc;
}


int main()
{
    bool rc = cftal::test::check_v2<double>();
    if (rc == false)
        std::cerr << "cftal::test::check_v2<double>() failed.\n";
    else
        std::cerr << "cftal::test::check_v2<double>() passed.\n";
    return rc == true ? 0 : 1;
}
