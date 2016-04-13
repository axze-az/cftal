#if !defined (__CFTAL_TEST_OF_VEC_H__)
#define __CFTAL_TEST_OF_VEC_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/idx.h>
#include <iostream>

namespace cftal {

    namespace test {

        template <typename _T, std::size_t _N>
        union vec_arr {
            _T _va[_N];
            vec<_T, _N> _vv;
        };

        template <typename _T, std::size_t _N>
        std::ostream& operator<<(std::ostream& s,
                                 const vec_arr<_T, _N>& v);
        
        // returns a vector filled with 1..N
        // or a vector filled with N+1..2N
        template <typename _T, std::size_t _N>
        vec<_T, _N> load_vals(bool second);

        template <typename _T, std::size_t _N, typename _M>
        bool
        check_val(const vec<_T, _N>& v, const idx& i,
                  const _M msg);

        template <class _T, std::size_t _N>
        struct of_vec {
            bool perform() const;
        };

        // tests of vec<_T, 2>
        template <class _T>
        bool check_select_v2();

        template <class _T>
        bool check_perm1_v2();

        template <class _T>
        bool check_perm2_v2();

        // tests of vec<_T, 4>
        template <class _T>
        bool check_select_v4();

        template <class _T>
        bool check_perm1_v4();

        template <class _T>
        bool check_perm2_v4();

        // tests of vec<_T, 8>
        template <class _T>
        bool check_select_v8();

        template <class _T>
        bool check_perm1_v8();

        template <class _T>
        bool check_perm2_v8();
        
        // combine the tests for v2xxx
        template <class _T>
        bool check_v2();
        // combine the tests for v4xxx
        template <class _T>
        bool check_v4();
        // combine the tests for v8xxx
        template <class _T>
        bool check_v8();

        // test one permutation for vec<_T, 8>
        template <class _T,
                  int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        bool perm1_v8();

        // test one permutation for vec<_T, 8>, vec<_T, 8>
        template <class _T,
                  int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        bool perm2_v8();
    }
}

template <typename _T, std::size_t _N>
std::ostream&
cftal::test::operator<<(std::ostream& s, const vec_arr<_T, _N>& v)
{
    for (std::size_t i=0; i< _N; ++i) {
        if (i)
            s << "; ";
        s << v._va[i];
    }
    return s;
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>
cftal::test::load_vals(bool second)
{
    vec_arr<_T, _N> v;
    std::size_t offset( second ? _N+1 : 1);
    for (std::size_t i=0; i<_N; ++i) {
        v._va[i] = _T(i + offset);
    }
    return v._vv;
}

template <typename _T, std::size_t _N, typename _M>
bool
cftal::test::check_val(const vec<_T, _N>& r, const idx& i, const _M m)
{
    vec_arr<_T, _N> v;
    mem< vec<_T, _N> >::store(&v._va[0], r);
    bool rc(true);
    for (std::size_t e=0; e<_N; ++e) {
        if (check_val(v._va[e], i[e])==false) {
            std::cerr << m << "< " << i <<  " > [ "
                      << v << " ] FAILED.\n";
            rc=false;
            break;
        }
    }
    return rc;
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

template <class _T>
bool cftal::test::check_v8()
{
    bool rc{check_select_v8<_T>()};
    rc &= check_perm1_v8<_T>();
    rc &= check_perm2_v8<_T>();
    if (rc == true) {
        std::cerr << __PRETTY_FUNCTION__ << " passed\n";
    } else {
        std::cerr << __PRETTY_FUNCTION__ << " failed\n";
    }
    return rc;
}

template <class _T,
          int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
bool cftal::test::perm1_v8()
{
    vec<_T, 8> a = load_vals<_T, 8>(false);
    vec<_T, 8> r= permute<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>(a);
    idx id= idx{_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7};
    bool rc=check_val(r, id, "perm1_v8");
    return rc;
}

template <class _T,
          int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
bool cftal::test::perm2_v8()
{
    vec<_T, 8> a = load_vals<_T, 8>(false);
    vec<_T, 8> b = load_vals<_T, 8>(true);
    vec<_T, 8> r = permute<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>(a, b);
    idx id= idx{_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7};
    bool rc=check_val(r, id, "perm2_v8");
    return rc;
}



// Local variables:
// mode: c++
// end:
#endif
