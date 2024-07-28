//
// Copyright (C) 2010-2024 Axel Zeuner
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
#include <cftal/vec.h>
#include <random>

namespace cftal {
    namespace test {

        template <typename _T, typename _I, cftal::size_t _N>
        std::enable_if_t<std::is_signed_v<_I>, cftal::vec<_T, _N>>
        permute_ref(const vec<_T, _N>& s, const vec<_I, _N>& idx, bool v=false);

        template <typename _T, typename _I>
        bool perm_v2();

        template <typename _T, typename _I>
        bool perm_v4();

        template <typename _T, typename _I>
        bool perm_v8();

        template <typename _T, typename _I, size_t _N>
        bool perm_vn();
    }
}

template <typename _T, typename _I, cftal::size_t _N>
std::enable_if_t<std::is_signed_v<_I>, cftal::vec<_T, _N>>
cftal::test::
permute_ref(const vec<_T, _N>& s, const vec<_I, _N>& idx, bool verb)
{
    using idx_t = vec<_I, _N>;
    using v_t=vec<_T, _N>;
    alignas(idx_t) _I ai[_N];
    alignas(v_t) _T as[_N];
    alignas(v_t) _T ar[_N];

    mem<idx_t>::store(ai, idx);
    mem<v_t>::store(as, s);

    for (size_t e=0; e<_N; ++e) {
        int32_t ii=ai[e];
        ar[e] = ii < 0 ? _T(0) : as[ii];
    }
    v_t r=mem<v_t>::load(ar);
    if (verb) {
        std::cout << "idx: " << idx << std::endl;
        std::cout << "s: " << s << std::endl;
        std::cout << "r:" << r << std::endl;
    }
    return r;
}

template <typename _T, typename _I>
bool
cftal::test::perm_v2()
{
    std::cout << "testing permute v2\n";
    const int _N=2;
    for (int i0=-1; i0<_N; ++i0) {
        for (int i1=-1; i1<_N; ++i1) {
            vec<_I, _N> idx{_I(i0), _I(i1)};
            vec<_T, _N> s{_T(1), _T(2) };
            vec<_T, _N> r=permute(s, idx);
            vec<_T, _N> rr=permute_ref(s, idx);
            typename vec<_T, _N>::mask_type neq=r!=rr;
            if (any_of(neq)) {
                std::cerr << "permute failed\n"
                          << "idx: " << idx << '\n'
                          << "src: " << s << '\n'
                          << "exp: " << rr << '\n'
                          << "res: " << r << '\n';
                std::cerr << __PRETTY_FUNCTION__ << " FAILED\n";
                return false;

            }
        }
    }
    std::cout << __PRETTY_FUNCTION__ << " passed\n";
    return true;
}

template <typename _T, typename _I>
bool
cftal::test::perm_v4()
{
    std::cout << "testing permute v4\n";
    const int _N=4;
    for (int i0=-1; i0<_N; ++i0) {
        for (int i1=-1; i1<_N; ++i1) {
            for (int i2=-1; i2<_N; ++i2) {
                for (int i3=-1; i3<_N; ++i3) {
                    vec<_I, _N> idx{_I(i0), _I(i1), _I(i2), _I(i3)};
                    vec<_T, _N> s{_T(1), _T(2), _T(3), _T(4) };
                    vec<_T, _N> r=permute(s, idx);
                    vec<_T, _N> rr=permute_ref(s, idx);
                    typename vec<_T, _N>::mask_type neq=r!=rr;
                    if (any_of(neq)) {
                        std::cerr << "permute failed\n"
                                << "idx: " << idx << '\n'
                                << "src: " << s << '\n'
                                << "exp: " << rr << '\n'
                                << "res: " << r << '\n';
                        std::cerr << __PRETTY_FUNCTION__ << " FAILED\n";
                        return false;
                    }
                }
            }
        }
    }
    std::cout << __PRETTY_FUNCTION__ << " passed\n";
    return true;
}

template <typename _T, typename _I>
bool
cftal::test::perm_v8()
{
    std::cout << "testing permute v8\n";
    const int _N=8;
    for (int i0=-1; i0<_N; ++i0) {
        for (int i1=-1; i1<_N; ++i1) {
            for (int i2=-1; i2<_N; ++i2) {
                for (int i3=-1; i3<_N; ++i3) {
                    for (int i4=-1; i4<_N; ++i4) {
                        for (int i5=-1; i5<_N; ++i5) {
                            for (int i6=-1; i6<_N; ++i6) {
                                for (int i7=-1; i7<_N; ++i7) {
                                    vec<_I, _N> idx{_I(i0), _I(i1),
                                                    _I(i2), _I(i3),
                                                    _I(i4), _I(i5),
                                                    _I(i6), _I(i7)};
                                    vec<_T, _N> s{_T(1), _T(2), _T(3), _T(4),
                                                  _T(5), _T(6), _T(7), _T(8)};
                                    vec<_T, _N> r=permute(s, idx);
                                    vec<_T, _N> rr=permute_ref(s, idx);
                                    typename vec<_T, _N>::mask_type neq=r!=rr;
                                    if (any_of(neq)) {
                                        std::cerr << "permute failed\n"
                                                << "idx: " << idx << '\n'
                                                << "src: " << s << '\n'
                                                << "exp: " << rr << '\n'
                                                << "res: " << r << '\n';
                                        std::cerr << __PRETTY_FUNCTION__
                                                  << " FAILED\n";
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    std::cout << __PRETTY_FUNCTION__ << " passed\n";
    return true;
}

template <typename _T, typename _I, cftal::size_t _N>
bool
cftal::test::perm_vn()
{
    using v_idx_t = vec<_I, _N>;
    using v_t = vec<_T, _N>;

    // setup an index vector
    alignas(v_t) _T as[_N];
    for (uint32_t i=0; i<_N; ++i)
        as[i]=_T(i+1);
    v_t s=mem<v_t>::load(as);
    alignas(v_idx_t) _I aidx[_N];
    std::mt19937 rnd;
    std::uniform_int_distribution<> d_m1_N(-1, int(_N-1));
    constexpr const size_t POWER=24;
    constexpr const size_t CNT=1LL<<POWER;
    constexpr const size_t MSK=(1LL<<(POWER-4))-1;
    for (size_t t=0; t<CNT; ++t) {
        for (uint32_t i=0; i<_N; ++i) {
            aidx[i]=d_m1_N(rnd);
        }
        v_idx_t idx=mem<v_idx_t>::load(aidx);
        vec<_T, _N> r=permute(s, idx);
        vec<_T, _N> rr=permute_ref(s, idx);
        typename vec<_T, _N>::mask_type neq=r!=rr;
        if (any_of(neq)) {
            std::cerr << "permute "<< _N << " failed\n"
                    << "idx: " << idx << '\n'
                    << "src: " << s << '\n'
                    << "exp: " << rr << '\n'
                    << "res: " << r << '\n';
            std::cerr << __PRETTY_FUNCTION__ << " FAILED\n";
            return false;
        }
        if ((t & MSK)==MSK) {
            std::cout << t << '\r' << std::flush;
        }
    }
    // std::cout << "permute "  << _N << " passed\n";
    std::cout << __PRETTY_FUNCTION__ << " passed\n";
    return true;
}

cftal::vec<double, 2>
test_perm(cftal::arg_t<cftal::vec<double, 2>> s,
          cftal::arg_t<cftal::vec<int64_t, 2>> idx)
{
    return permute(s, idx);
}

cftal::vec<double, 4>
test_perm(cftal::arg_t<cftal::vec<double, 4>> s,
          cftal::arg_t<cftal::vec<int64_t, 4>> idx)
{
    return permute(s, idx);
}

cftal::vec<float, 4>
test_perm(cftal::arg_t<cftal::vec<float, 4>> s,
          cftal::arg_t<cftal::vec<int32_t, 4>> idx)
{
    return permute(s, idx);
}

cftal::vec<float, 8>
test_perm(cftal::arg_t<cftal::vec<float, 8>> s,
          cftal::arg_t<cftal::vec<int32_t, 8>> idx)
{
    return permute(s, idx);
}

int main()
{
    using namespace cftal;
    bool r=true;

    r &= test::perm_v2<uint8_t, int8_t>();
    r &= test::perm_v2<int8_t, int8_t>();
    r &= test::perm_v2<uint16_t, int16_t>();
    r &= test::perm_v2<int16_t, int16_t>();
    r &= test::perm_v2<int32_t, int32_t>();
    r &= test::perm_v2<uint32_t, int32_t>();
    r &= test::perm_v2<int64_t, int64_t>();
    r &= test::perm_v2<uint64_t, int64_t>();
    r &= test::perm_v2<float, int32_t>();
    r &= test::perm_v2<double, int64_t>();

    r &= test::perm_v4<uint8_t, int8_t>();
    r &= test::perm_v4<int8_t, int8_t>();
    r &= test::perm_v4<uint16_t, int16_t>();
    r &= test::perm_v4<int16_t, int16_t>();
    r &= test::perm_v4<uint32_t, int32_t>();
    r &= test::perm_v4<int32_t, int32_t>();
    r &= test::perm_v4<int64_t, int64_t>();
    r &= test::perm_v4<uint64_t, int64_t>();
    r &= test::perm_v4<float, int32_t>();
    r &= test::perm_v4<double, int64_t>();

    r &= test::perm_v8<uint8_t, int8_t>();
    r &= test::perm_v8<int8_t, int8_t>();
    r &= test::perm_v8<uint16_t, int16_t>();
    r &= test::perm_v8<int16_t, int16_t>();
    r &= test::perm_v8<uint32_t, int32_t>();
    r &= test::perm_v8<int32_t, int32_t>();
    r &= test::perm_v8<uint64_t, int64_t>();
    r &= test::perm_v8<int64_t, int64_t>();
    r &= test::perm_v8<float, int32_t>();
    r &= test::perm_v8<double, int64_t>();

    r &= test::perm_vn<uint8_t, int8_t, 16>();
    r &= test::perm_vn<int8_t, int8_t, 16>();
    r &= test::perm_vn<uint16_t, int16_t, 16>();
    r &= test::perm_vn<int16_t, int16_t, 16>();
    r &= test::perm_vn<uint32_t, int32_t, 16>();
    r &= test::perm_vn<int32_t, int32_t, 16>();
    r &= test::perm_vn<uint64_t, int64_t, 16>();
    r &= test::perm_vn<int64_t, int64_t, 16>();
    r &= test::perm_vn<float, int32_t, 16>();
    r &= test::perm_vn<double, int64_t, 16>();

    r &= test::perm_vn<uint8_t, int8_t, 32>();
    r &= test::perm_vn<int8_t, int8_t, 32>();
    r &= test::perm_vn<uint16_t, int16_t, 32>();
    r &= test::perm_vn<int16_t, int16_t, 32>();
    r &= test::perm_vn<uint32_t, int32_t, 32>();
    r &= test::perm_vn<int32_t, int32_t, 32>();
    r &= test::perm_vn<uint64_t, int64_t, 32>();
    r &= test::perm_vn<int64_t, int64_t, 32>();
    r &= test::perm_vn<float, int32_t, 32>();
    r &= test::perm_vn<double, int64_t, 32>();

    return r==true ? 0 : 1;
}
