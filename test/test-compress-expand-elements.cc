//
// Copyright (C) 2010-2023 Axel Zeuner
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

#include <cftal/config.h>
#include <cftal/vec.h>
#include <vector>
#include <iomanip>

namespace cftal {

    namespace utils {

	// index generation function for specializations of
	// compress_expand
        template <size_t _BITS>
        void
        gen_vx_idx();
    }

    namespace test {

        std::pair<cftal::vec<float, 4>, cftal::size_t>
        compress_elements(arg_t<vec<float, 4>> src,
                          arg_t<typename vec<float, 4>::mask_type> m);


	// test for type T and vector size _N
        template <typename _T, size_t _N>
        bool
        compress_expand_elements_vec();

	// test for all specialized types _T with vector size _N
        template <size_t _N>
        bool
        compress_expand_elements_size();
    }
}

template <cftal::size_t _BITS>
void
cftal::utils::gen_vx_idx()
{
    const uint32_t BITS=_BITS;
    const uint32_t PERMS=(1<<BITS);
    std::vector<int8_t> compress_vals;
    std::vector<int8_t> expand_vals;
    std::vector<int8_t> pop_cnt;
    for (uint32_t m=0; m<PERMS; ++m) {
        uint32_t cnt=0;
        for (uint32_t b=0; b<BITS; ++b) {
            if ((m & (1<<b)) != 0) {
                expand_vals.push_back(cnt);
                compress_vals.push_back(b);
                ++cnt;
            } else {
                expand_vals.push_back(-1);
            }
        }
        pop_cnt.push_back(cnt);
        for (; cnt < BITS; ++cnt) {
            compress_vals.push_back(-1);
        }
    }
    // output of values
    std::cout << "    // compress\n";
    for (uint32_t m=0; m<PERMS; ++m) {
        std::cout << "    ";
        for (uint32_t b=0; b<BITS; ++b) {
            int32_t ei=compress_vals[m*BITS+b];
            std::cout << std::setw(3) << ei << ',';
        }
        std::cout << '\n';
    }
    std::cout << "    // expand\n";
    for (uint32_t m=0; m<PERMS; ++m) {
        std::cout << "    ";
        for (uint32_t b=0; b<BITS; ++b) {
            int32_t ei=expand_vals[m*BITS+b];
            std::cout << std::setw(3) << ei << ',';
        }
        std::cout << '\n';
    }
    std::cout << "    // pop count\n";
    for (uint32_t m=0; m<PERMS; ++m) {
        std::cout << "    " << int32_t(pop_cnt[m]) << ",\n";
    }
}

template <typename _T, size_t _N>
bool
cftal::test::compress_expand_elements_vec()
{
    using vec_t = vec<_T, _N>;
    alignas(vec_t) _T a[_N];
    for (uint32_t i=0; i<_N; ++i) {
        a[i]= _T(i+1);
    }
    const vec_t ref0=mem<vec_t>::load(a);
    const vec_t zero(_T(0));
    const int64_t _PERMS=1LL<<_N;
    std::cout << std::hex;
    for (uint64_t i=0; i<_PERMS; ++i) {
        // typename vec_t::mask_type m=x86::expand_mask_v2u64(i);
        vec<bit, _N> mi(i);
        mask_t<vec_t> m=expand_mask_to<vec_t>(mi);
        vec_t ref_i=select(m, ref0, zero);
        std::pair<vec_t, size_t> compressed=compress_elements(ref_i, m);
        std::pair<vec_t, size_t> res=expand_elements(compressed.first, m);
        typename vec_t::mask_type cmp=res.first!=ref_i;
        if (any_of(cmp)) {
            std::cout << "msk: " << i << '\n'
                      << "mask: " << m << '\n'
                      << "ref_i: " << ref_i << '\n'
                      << "compressed: " << compressed.first << '\n'
                      << "res: " << res.first << '\n';
            std::cout << __PRETTY_FUNCTION__ << " FAILED\n";
            return false;
        } else {
#if 0
            std::cout << "msk: " << i << '\n'
                      << "mask: " << m << '\n'
                      << "ref_i: " << ref_i << '\n'
                      << "compressed: " << compressed.first << '\n'
                      << "res: " << res.first << '\n'
                      << "PASSED\n";
#endif
        }
    }
    std::cout << __PRETTY_FUNCTION__ << " passed\n";
    return true;
}

template <cftal::size_t _N>
bool
cftal::test::compress_expand_elements_size()
{
    bool r=true;
    r &= compress_expand_elements_vec<int8_t, _N>();
    r &= compress_expand_elements_vec<uint8_t, _N>();
    r &= compress_expand_elements_vec<int16_t, _N>();
    r &= compress_expand_elements_vec<uint16_t, _N>();
    r &= compress_expand_elements_vec<int32_t, _N>();
    r &= compress_expand_elements_vec<uint32_t, _N>();
    r &= compress_expand_elements_vec<int64_t, _N>();
    r &= compress_expand_elements_vec<uint64_t, _N>();
    r &= compress_expand_elements_vec<double, _N>();
    r &= compress_expand_elements_vec<float, _N>();
    return r;
}

std::pair<cftal::vec<float, 4>, cftal::size_t>
cftal::test::compress_elements(arg_t<vec<float, 4>> src,
                               arg_t<typename vec<float, 4>::mask_type> m)
{
    return cftal::compress_elements(src, m);
}

int main()
{
    bool r=true;
    r &= cftal::test::compress_expand_elements_size<16>();
    r &= cftal::test::compress_expand_elements_size<8>();
    r &= cftal::test::compress_expand_elements_size<4>();
    r &= cftal::test::compress_expand_elements_size<2>();
    r &= cftal::test::compress_expand_elements_size<1>();
    return r==true ? 0 : 1;
}
