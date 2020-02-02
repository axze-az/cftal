//
// Copyright Axel Zeuner 2010-2020. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined __CFTAL_TEST_VEC_2_H__
#define __CFTAL_TEST_VEC_2_H__ 1

#include <cftal/test/of_vec.h>

template <class _T>
bool cftal::test::check_select_v2()
{
    bool rc(true);
    vec<_T, 2> a = load_vals<_T, 2>(false);
    vec<_T, 2> b = load_vals<_T, 2>(true);
    vec<_T, 2> r;
    idx id{-2,-2};

    r=select<0, 0>(a,b);
    id= idx{2, 3};
    rc &= check_val(r, id, "select_v2");
    r=select<0, 1>(a,b);
    id= idx{2, 1};
    rc &= check_val(r, id, "select_v2");
    r=select<1, 0>(a,b);
    id= idx{0, 3};
    rc &= check_val(r, id, "select_v2");
    r=select<1, 1>(a,b);
    id= idx{0, 1};
    rc &= check_val(r, id, "select_v2");
    return rc;
}

template <class _T>
bool cftal::test::check_perm1_v2()
{
    bool rc(true);
    vec<_T, 2> a = load_vals<_T, 2>(false);
    vec<_T, 2> r;
    idx id{-2,-2};

    r=permute<-1, -1>(a);
    id= idx{-1, -1};
    rc &= check_val(r, id, "perm1_v2");
    r=permute<-1, 0>(a);
    id= idx{-1, 0};
    rc &= check_val(r, id, "perm1_v2");
    r=permute<-1, 1>(a);
    id= idx{-1, 1};
    rc &= check_val(r, id, "perm1_v2");
    r=permute<0, -1>(a);
    id= idx{0, -1};
    rc &= check_val(r, id, "perm1_v2");
    r=permute<0, 0>(a);
    id= idx{0, 0};
    rc &= check_val(r, id, "perm1_v2");
    r=permute<0, 1>(a);
    id= idx{0, 1};
    rc &= check_val(r, id, "perm1_v2");
    r=permute<1, -1>(a);
    id= idx{1, -1};
    rc &= check_val(r, id, "perm1_v2");
    r=permute<1, 0>(a);
    id= idx{1, 0};
    rc &= check_val(r, id, "perm1_v2");
    r=permute<1, 1>(a);
    id= idx{1, 1};
    rc &= check_val(r, id, "perm1_v2");
    return rc;
}

template <class _T>
bool cftal::test::check_perm2_v2()
{
    bool rc(true);
    vec<_T, 2> a = load_vals<_T, 2>(false);
    vec<_T, 2> b = load_vals<_T, 2>(true);
    vec<_T, 2> r;
    idx id{-2,-2};

    r=permute<-1, -1>(a,b);
    id= idx{-1, -1};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<-1, 0>(a,b);
    id= idx{-1, 0};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<-1, 1>(a,b);
    id= idx{-1, 1};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<-1, 2>(a,b);
    id= idx{-1, 2};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<-1, 3>(a,b);
    id= idx{-1, 3};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<0, -1>(a,b);
    id= idx{0, -1};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<0, 0>(a,b);
    id= idx{0, 0};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<0, 1>(a,b);
    id= idx{0, 1};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<0, 2>(a,b);
    id= idx{0, 2};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<0, 3>(a,b);
    id= idx{0, 3};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<1, -1>(a,b);
    id= idx{1, -1};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<1, 0>(a,b);
    id= idx{1, 0};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<1, 1>(a,b);
    id= idx{1, 1};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<1, 2>(a,b);
    id= idx{1, 2};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<1, 3>(a,b);
    id= idx{1, 3};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<2, -1>(a,b);
    id= idx{2, -1};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<2, 0>(a,b);
    id= idx{2, 0};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<2, 1>(a,b);
    id= idx{2, 1};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<2, 2>(a,b);
    id= idx{2, 2};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<2, 3>(a,b);
    id= idx{2, 3};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<3, -1>(a,b);
    id= idx{3, -1};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<3, 0>(a,b);
    id= idx{3, 0};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<3, 1>(a,b);
    id= idx{3, 1};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<3, 2>(a,b);
    id= idx{3, 2};
    rc &= check_val(r, id, "perm2_v2");
    r=permute<3, 3>(a,b);
    id= idx{3, 3};
    rc &= check_val(r, id, "perm2_v2");
    return rc;
}

// Local variables:
// mode: c++
// end:
#endif
