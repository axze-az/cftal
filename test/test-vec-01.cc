#include <cftal/config.h>
#include <cftal/test/of_vec.h>
#include <cftal/test/of_vec_v2.h>
#include <cftal/test/of_vec_v4.h>

namespace cftal {

    namespace test {

        template <class _T>
        bool check_v2();

        template <class _T>
        bool check_v4();

    }
}

template <class _T>
bool cftal::test::check_v2()
{
    bool rc{check_select_v2<_T>()};
    rc &= check_perm1_v2<_T>();
    rc &= check_perm2_v2<_T>();
    if (rc == true) {
        std::cerr << __PRETTY_FUNCTION__ << " passed\n";
    } else {
        std::cerr << __PRETTY_FUNCTION__ << " failed\n";
    }
    return rc;
}

template <class _T>
bool cftal::test::check_v4()
{
    bool rc{check_select_v4<_T>()};
    rc &= check_perm1_v4<_T>();
    rc &= check_perm2_v4<_T>();
    if (rc == true) {
        std::cerr << __PRETTY_FUNCTION__ << " passed\n";
    } else {
        std::cerr << __PRETTY_FUNCTION__ << " failed\n";
    }
    return rc;
}

int main()
{
    bool rc(true);
    rc &= cftal::test::check_v2<double>();
    rc &= cftal::test::check_v2<int64_t>();
    rc &= cftal::test::check_v2<uint64_t>();

    rc &= cftal::test::check_v4<float>();
    rc &= cftal::test::check_v4<int32_t>();
    rc &= cftal::test::check_v4<uint32_t>();
    
    return rc == true ? 0 : 1;
}
