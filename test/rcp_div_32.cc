// 
// Copyright (C) 2010-2021 Axel Zeuner
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
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA  
//
#include <cftal/mul_div.h>
#include <cftal/divisor.h>
#include <cftal/test/rcp_div.h>
#include <iostream>
#include <iomanip>
#include <random>

namespace cftal {

    namespace test {

        struct rng_u32_t {
            std::uniform_int_distribution<std::uint32_t> _distribution;
            std::mt19937 _rnd;
            uint32_t next() { return _distribution(_rnd); }
        };

        bool udiv_32_one(std::uint32_t d,
                         std::uint64_t& ops,
                         rng_u32_t& rng,
                         uint64_t* timings);
    }
}

bool
cftal::test::udiv_32_one(uint32_t v,
                         std::uint64_t& ops,
                         rng_u32_t& rng,
                         uint64_t* timings)
{
#if defined (__tune_atom__)
    const int N= 2000;
#else
    const int N= 20000;
#endif
    for (int i=0; i<N; ++i) {
        uint64_t t0, t1, t2;
        uint32_t ul= rng.next();
        uint32_t uh= rng.next();

        t0 = rdtsc();
        impl::udiv_result<uint32_t> qr_ref(
            impl::udiv_2by1_div_32::d(ul, uh, v));
        t1 = rdtsc();
        impl::udiv_result<uint32_t> qr(
            impl::udiv_2by1_rcp_32::d(ul, uh, v));
        t2 = rdtsc();

        timings[0] += t1-t0;
        timings[1] += t2-t1;

        uint32_t r_ref= qr_ref._r;
        uint32_t q_ref_l=qr_ref._q0;
        uint32_t q_ref_h=qr_ref._q1;


        uint32_t r=qr._r;
        uint32_t q_l = qr._q0;
        uint32_t q_h = qr._q1;

        if (q_l != q_ref_l || q_h != q_ref_h || r != r_ref ) {
            std::cout << '\n'
                      << std::hex
                      << "0x"
                      << std::setfill('0')
                      << uh << ':'
                      << std::setw(8)
                      << ul
                      << " / 0x"
                      << v
                      << " = \n"
                      << "0x"
                      << q_h << ':'
                      << std::setw(8)
                      << q_l
                      << " rem: "
                      << "0x"
                      << r
                      << " != (ref:)\n"
                      << "0x"
                      << q_ref_h << ':'
                      << std::setw(8)
                      << q_ref_l
                      << " rem: "
                      << "0x"
                      << r_ref
                      << std::dec
                      << std::setfill(' ')
                      << "\n";

            return false;
        }
    }
    ops += N;
    return true;
}

bool
cftal::test::rcp_div_u32()
{
    bool rc(true);
    uint64_t ops(0), timings[2];
    timings[0] = timings[1] =0;
    rng_u32_t rng;
    rc &= udiv_32_one(1, ops, rng, timings);
    if (!rc)
        return rc;
    rc &= udiv_32_one(-1L, ops, rng, timings);
    if (!rc)
        return rc;
    const int N = 0x10000;
    divisor<double> dd(N);
    for (int i=2; (i< N) && (rc ==true) ; ++i) {
        uint32_t v= rng.next();
        std::cout << std::fixed << std::setprecision(4);
        if ((i & 0x3FF)==0x3FF) {
            std::cout << "udiv_rcp_32: "
                      << std::setw(7)
                      << (double(i)*100)/ dd
                      << " %\r" << std::flush;
        }
        rc &= udiv_32_one(v, ops, rng, timings);
        if (!rc)

            return rc;
    }
    std::cout << "udiv_rcp_32 passed without errors"
              << std::endl;
    std::cout << "timing information\n"
              << "div:     " << double(timings[0])/ops
              << '\n'
              << "rcp_div: " << double(timings[1])/ops
              << std::endl;
    return true;
}

#if defined (MAIN)
int main(int argc, char* argv[])
{
    if (argc > 1) {
        std::string argv1(argv[1]);
        if (argv1 == "--gen-tbl") {
            cftal::impl::print_rcp_32_table(std::cout);
            return 0;
        }
    }
    cftal::test::udiv_32();
    return 0;
}
#endif
