//
// Copyright (C) 2010-2026 Axel Zeuner
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
//
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

        extern const char* msg_select_v2;
        extern const char* msg_perm1_v2;
        extern const char* msg_perm2_v2;

        // tests of vec<_T, 4>
        template <class _T>
        bool check_select_v4();

        template <class _T>
        bool check_perm1_v4();

        template <class _T>
        bool check_perm2_v4();

        extern const char* msg_select_v4;
        extern const char* msg_perm1_v4;
        extern const char* msg_perm2_v4;

        // tests of vec<_T, 8>
        template <class _T>
        bool check_select_v8();

        template <class _T>
        bool check_perm1_v8();

        template <class _T>
        bool check_perm2_v8();

        extern const char* msg_select_v8;
        extern const char* msg_perm1_v8;
        extern const char* msg_perm2_v8;

        // tests of vec<_T, 16>
        template <class _T>
        bool check_select_v16();

        template <class _T>
        bool check_perm1_v16();

        template <class _T>
        bool check_perm2_v16();

        extern const char* msg_select_v16;
        extern const char* msg_perm1_v16;
        extern const char* msg_perm2_v16;

        // tests of vec<_T, 32>
        template <class _T>
        bool check_select_v32();

        template <class _T>
        bool check_perm1_v32();

        template <class _T>
        bool check_perm2_v32();

        extern const char* msg_select_v32;
        extern const char* msg_perm1_v32;
        extern const char* msg_perm2_v32;


        // combine the tests for v2xxx
        template <class _T>
        bool check_v2();
        // combine the tests for v4xxx
        template <class _T>
        bool check_v4();
        // combine the tests for v8xxx
        template <class _T>
        bool check_v8();
        // combine the tests for v16xxx
        template <class _T>
        bool check_v16();
        // combine the tests for v32xxx
        template <class _T>
        bool check_v32();

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

        // test one permutation for vec<_T, 16>
        template <class _T,
                  int _P00, int _P01, int _P02, int _P03,
                  int _P04, int _P05, int _P06, int _P07,
                  int _P08, int _P09, int _P10, int _P11,
                  int _P12, int _P13, int _P14, int _P15>
        bool perm1_v16();

        // test one permutation for vec<_T, 16>, vec<_T, 16>
        template <class _T,
                  int _P00, int _P01, int _P02, int _P03,
                  int _P04, int _P05, int _P06, int _P07,
                  int _P08, int _P09, int _P10, int _P11,
                  int _P12, int _P13, int _P14, int _P15>
        bool perm2_v16();

        // test one permutation for vec<_T, 32>
        template <class _T,
                  int _P00, int _P01, int _P02, int _P03,
                  int _P04, int _P05, int _P06, int _P07,
                  int _P08, int _P09, int _P10, int _P11,
                  int _P12, int _P13, int _P14, int _P15,
                  int _P16, int _P17, int _P18, int _P19,
                  int _P20, int _P21, int _P22, int _P23,
                  int _P24, int _P25, int _P26, int _P27,
                  int _P28, int _P29, int _P30, int _P31>
        bool perm1_v32();

        // test one permutation for vec<_T, 32>, vec<_T, 32>
        template <class _T,
                  int _P00, int _P01, int _P02, int _P03,
                  int _P04, int _P05, int _P06, int _P07,
                  int _P08, int _P09, int _P10, int _P11,
                  int _P12, int _P13, int _P14, int _P15,
                  int _P16, int _P17, int _P18, int _P19,
                  int _P20, int _P21, int _P22, int _P23,
                  int _P24, int _P25, int _P26, int _P27,
                  int _P28, int _P29, int _P30, int _P31>
        bool perm2_v32();
    }
}

template <typename _T, std::size_t _N>
std::ostream&
cftal::test::operator<<(std::ostream& s, const vec_arr<_T, _N>& v)
{
    using out_t = std::conditional_t<
                    std::is_same_v<_T, int8_t>,
                    int32_t,
                    std::conditional_t<
                        std::is_same_v<_T, uint8_t>,
                        uint32_t,
                        _T>>;
    for (std::size_t i=0; i< _N; ++i) {
        if (i)
            s << "; ";
        s << out_t(v._va[i]);
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

template <class _T>
bool cftal::test::check_v16()
{
    bool rc{check_select_v16<_T>()};
    rc &= check_perm1_v16<_T>();
    rc &= check_perm2_v16<_T>();
    if (rc == true) {
        std::cerr << __PRETTY_FUNCTION__ << " passed\n";
    } else {
        std::cerr << __PRETTY_FUNCTION__ << " failed\n";
    }
    return rc;
}

template <class _T>
bool cftal::test::check_v32()
{
    bool rc{check_select_v32<_T>()};
    rc &= check_perm1_v32<_T>();
    rc &= check_perm2_v32<_T>();
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
    bool rc=check_val(r, id, msg_perm1_v8);
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
    bool rc=check_val(r, id, msg_perm2_v8);
    return rc;
}

template <class _T,
         int _P00, int _P01, int _P02, int _P03,
         int _P04, int _P05, int _P06, int _P07,
         int _P08, int _P09, int _P10, int _P11,
         int _P12, int _P13, int _P14, int _P15>
bool cftal::test::perm1_v16()
{
    vec<_T, 16> a = load_vals<_T, 16>(false);
    vec<_T, 16> r= permute<_P00, _P01, _P02, _P03,
                           _P04, _P05, _P06, _P07,
                           _P08, _P09, _P10, _P11,
                           _P12, _P13, _P14, _P15>(a);
    idx id= idx{_P00, _P01, _P02, _P03,
                _P04, _P05, _P06, _P07,
                _P08, _P09, _P10, _P11,
                _P12, _P13, _P14, _P15};
    bool rc=check_val(r, id, msg_perm1_v16);
    return rc;
}

template <class _T,
         int _P00, int _P01, int _P02, int _P03,
         int _P04, int _P05, int _P06, int _P07,
         int _P08, int _P09, int _P10, int _P11,
         int _P12, int _P13, int _P14, int _P15>
bool cftal::test::perm2_v16()
{
    vec<_T, 16> a = load_vals<_T, 16>(false);
    vec<_T, 16> b = load_vals<_T, 16>(true);
    vec<_T, 16> r= permute<_P00, _P01, _P02, _P03,
                           _P04, _P05, _P06, _P07,
                           _P08, _P09, _P10, _P11,
                           _P12, _P13, _P14, _P15>(a, b);
    idx id= idx{_P00, _P01, _P02, _P03,
                _P04, _P05, _P06, _P07,
                _P08, _P09, _P10, _P11,
                _P12, _P13, _P14, _P15};
    bool rc=check_val(r, id, msg_perm2_v16);
    return rc;
}

template <class _T,
          int _P00, int _P01, int _P02, int _P03,
          int _P04, int _P05, int _P06, int _P07,
          int _P08, int _P09, int _P10, int _P11,
          int _P12, int _P13, int _P14, int _P15,
          int _P16, int _P17, int _P18, int _P19,
          int _P20, int _P21, int _P22, int _P23,
          int _P24, int _P25, int _P26, int _P27,
          int _P28, int _P29, int _P30, int _P31>
bool cftal::test::perm1_v32()
{
    vec<_T, 32> a = load_vals<_T, 32>(false);
    vec<_T, 32> r= permute<_P00, _P01, _P02, _P03,
                           _P04, _P05, _P06, _P07,
                           _P08, _P09, _P10, _P11,
                           _P12, _P13, _P14, _P15,
                           _P16, _P17, _P18, _P19,
                           _P20, _P21, _P22, _P23,
                           _P24, _P25, _P26, _P27,
                           _P28, _P29, _P30, _P31>(a);
    idx id= idx{_P00, _P01, _P02, _P03,
                _P04, _P05, _P06, _P07,
                _P08, _P09, _P10, _P11,
                _P12, _P13, _P14, _P15,
                _P16, _P17, _P18, _P19,
                _P20, _P21, _P22, _P23,
                _P24, _P25, _P26, _P27,
                _P28, _P29, _P30, _P31};
    bool rc=check_val(r, id, msg_perm1_v32);
    return rc;
}

template <class _T,
          int _P00, int _P01, int _P02, int _P03,
          int _P04, int _P05, int _P06, int _P07,
          int _P08, int _P09, int _P10, int _P11,
          int _P12, int _P13, int _P14, int _P15,
          int _P16, int _P17, int _P18, int _P19,
          int _P20, int _P21, int _P22, int _P23,
          int _P24, int _P25, int _P26, int _P27,
          int _P28, int _P29, int _P30, int _P31>
bool cftal::test::perm2_v32()
{
    vec<_T, 32> a = load_vals<_T, 32>(false);
    vec<_T, 32> b = load_vals<_T, 32>(true);
    vec<_T, 32> r= permute<_P00, _P01, _P02, _P03,
                           _P04, _P05, _P06, _P07,
                           _P08, _P09, _P10, _P11,
                           _P12, _P13, _P14, _P15,
                           _P16, _P17, _P18, _P19,
                           _P20, _P21, _P22, _P23,
                           _P24, _P25, _P26, _P27,
                           _P28, _P29, _P30, _P31>(a, b);
    idx id= idx{_P00, _P01, _P02, _P03,
                _P04, _P05, _P06, _P07,
                _P08, _P09, _P10, _P11,
                _P12, _P13, _P14, _P15,
                _P16, _P17, _P18, _P19,
                _P20, _P21, _P22, _P23,
                _P24, _P25, _P26, _P27,
                _P28, _P29, _P30, _P31};
    bool rc=check_val(r, id, msg_perm2_v32);
    return rc;
}

// Local variables:
// mode: c++
// end:
#endif
