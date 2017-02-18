//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/mul_div.h"
#include "cftal/d_int.h"
#include <iostream> // required by print_rcp_64_table
#include <iomanip> // required by print_rcp_64_table

inline
cftal::uint64_t
cftal::impl::udiv_2by1_rcp_64::reciprocal_word_i(uint64_t d)
{
#define USE_DIV 0
#define USE_CPP 1
#define USE_ASM 2
#define USE_GPL 3
#if defined (__x86_64__)
#define ALG USE_ASM
#else
#define ALG USE_CPP
#endif

#if USE_DIV==ALG
    return udiv_2by1_div_64::d(uint64_t(-1L), uint64_t(-1L)-d, d)._q0;
#endif
#if USE_CPP==ALG
    uint32_t v0 = _tbl[d>>55];
    uint64_t d40 = (d>>24)+1;
    uint32_t v0_v0 = v0*v0;
    uint64_t v0_v0_d40 = d40*v0_v0;
    uint32_t v1= (v0<<11) - uint32_t(v0_v0_d40>>40) -1;
    uint64_t v1_d40 = v1 * d40;
    uint64_t v1_shl_13= uint64_t(v1) << 13;
    uint64_t two_pow_60_m_v1_d40= (1LL<<60) - v1_d40;
    // right part of v2
    uint64_t v2r= (v1*two_pow_60_m_v1_d40)>>47;
    uint64_t v2= v1_shl_13 + v2r;

    // e fits into 64 bits
    uint64_t d0 = d & 1;
    uint64_t nd0 = -d0;
    uint64_t d63 = (d>>1) + d0;
    uint64_t d0_v2_half = nd0 & (v2>>1);
    uint64_t v2_d63 = v2* d63;
    // this is e without 2^96
    uint64_t d0_v2_half_minus_v2_d63 = d0_v2_half - v2_d63;
    std::pair<uint64_t, uint64_t> pe(
        mul_lo_hi(d0_v2_half_minus_v2_d63, v2));
    uint64_t v2e_h=pe.second;
    // v3
    uint64_t v3= (v2<<31) + (v2e_h>>1);
    // v4= v3 - (v3*d +2^64*d +d)
    std::pair<uint64_t, uint64_t> pv3_d(mul_lo_hi(d, v3));
    duint<uint64_t> v3_d(pv3_d.first, pv3_d.second);
    duint<uint64_t> dd(d, d);
    v3_d += dd;
    uint64_t v4= v3- v3_d.uh();
    return v4;
#endif
#if USE_ASM==ALG
    uint32_t v0 = _tbl[d>>55];
    uint64_t d40 = (d>>24)+1;
    uint32_t v0_v0 = v0*v0;
    uint64_t v0_v0_d40 = d40*v0_v0;
    uint32_t v1= (v0<<11) - uint32_t(v0_v0_d40>>40) -1;
    uint64_t v1_d40 = v1 * d40;
    uint64_t v1_shl_13= uint64_t(v1) << 13;
    uint64_t two_pow_60_m_v1_d40= (1LL<<60) - v1_d40;
    // right part of v2
    uint64_t v2r= (v1*two_pow_60_m_v1_d40)>>47;
    uint64_t v2= v1_shl_13 + v2r;

    // calculate d63, nd0
    uint64_t d63, nd0;
    __asm__ ("shr $1, %[d63] \n\t" // CF contains lowest bit
             "sbb %[d0], %[d0] \n\t" // -1 if CF, 0 if not == -d0
             "sub %[d0], %[d63] \n\t" // ceil(d/2)
             : [d63] "=r"(d63), [d0] "=r"(nd0)
             : "0" (d)
             : "cc" );
    uint64_t d0_v2_half = nd0 & (v2>>1);
    uint64_t v2_d63 = v2* d63;
    // this is e without 2^96
    uint64_t d0_v2_half_minus_v2_d63 = d0_v2_half - v2_d63;
    uint64_t v2e_h, v2e_l;
    __asm__ ("mulq %[v2] \n\t"
             : "=a"(v2e_l) , "=d"(v2e_h)
             : "0"(d0_v2_half_minus_v2_d63), [v2] "rm"(v2)
             : "cc" );
    uint64_t v3= (v2<<31) + (v2e_h>>1);
    uint64_t v3d_h, v3d_l;
    __asm__ ("mulq %[v3] \n\t"
             : "=a"(v3d_l) , "=d"(v3d_h)
             : "0"(d), [v3] "rm" (v3)
             : "cc" );
    __asm__ ("add %[d], %[v3d_l] \n\t"
             "adc %[d], %[v3d_h] \n\t"
             : [v3d_l] "+r" (v3d_l), [v3d_h] "+r" (v3d_h)
             : [d] "rm" (d)
             : "cc");
    uint64_t v4= v3 -v3d_h;
    return v4;
#endif

#if USE_GPL == ALG
    uint64_t inv, t0, t1;
    const uint16_t* tblptr= _tbl;
    __asm__ __volatile__(
        "mov %[rdi], %[rax] \n\t"
        "shr $55, %[rax] \n\t"
        "movzwl (%[rcx], %[rax], 2), %k[rcx] \n\t"
        // v1 = (v0 << 11) - (v0*v0*d40 >> 40) - 1
        "mov %[rdi], %[rsi] \n\t"
        "mov %k[rcx], %k[rax] \n\t"
        "imul %k[rcx], %k[rcx] \n\t"
        "shr $24, %[rsi] \n\t"
        "inc %[rsi] \n\t" // %[rsi] = d40
        "imul %[rsi], %[rcx] \n\t"
        "shr $40, %[rcx] \n\t"
        "sal $11, %k[rax] \n\t"
        "dec %k[rax] \n\t"
        "sub %k[rcx], %k[rax] \n\t" // %[rax] = v1

        // v2 = (v1 << 13) + (v1 * (2^60 - v1*d40) >> 47
        "mov $0x1000000000000000, %[rcx] \n\t"
        "imul %[rax], %[rsi] \n\t"
        "sub %[rsi], %[rcx] \n\t"
        "imul %[rax], %[rcx] \n\t"
        "sal $13, %[rax] \n\t"
        "shr $47, %[rcx] \n\t"
        "add %[rax], %[rcx]  \n\t" // %[rcx] = v2

        // v3 = (v2 << 31) +
        // (v2 * (2^96 - v2 * d63 + (v2>>1) & mask) >> 65
        "mov %[rdi], %[rsi] \n\t"
        "shr $1, %[rsi] \n\t" // d/2
        "sbb %[rax], %[rax] \n\t" // -d0 = -(d mod 2)
        "sub %[rax], %[rsi] \n\t" // d63 = ceil(d/2)
        "imul %[rcx], %[rsi] \n\t" // v2 * d63
        "and %[rcx], %[rax] \n\t" // v2 * d0
        "shr $1, %[rax] \n\t" // (v2>>1) * d0
        "sub %[rsi], %[rax] \n\t" // (v2>>1) * d0 - v2 * d63
        "mul %[rcx] \n\t"
        "sal $31, %[rcx] \n\t"
        "shr $1, %[rdx] \n\t"
        "add %[rdx], %[rcx] \n\t" // %[rcx] = v3

        "mov %[rdi], %[rax] \n\t"
        "mul %[rcx] \n\t"
        "add %[rdi], %[rax] \n\t"
        "mov %[rcx], %[rax] \n\t"
        "adc %[rdi], %[rdx] \n\t"
        "sub %[rdx], %[rax] \n\t"
        : [rax] "=&a" (inv), [rdx] "=&d" (t0),
          [rsi] "=&r" (t1), [rcx] "+&r" (tblptr)
        : [rdi] "rm" (d)
        : "cc");
    return inv;
#endif

#undef USE_DIV
#undef USE_CPP
#undef USE_ASM
#undef USE_GPL
#undef ALG
}

inline
cftal::uint64_t
cftal::impl::udiv_2by1_rcp_64::
sd_i(uint64_t u0, uint64_t u1, uint64_t d, uint64_t inv, uint64_t& rem)
{
#if defined (__x86_64__)
    uint64_t p0, p1;
    __asm__("mulq %[u1] \n\t"
            :"=a"(p0), "=d"(p1)
            :"0"(inv), [u1] "rm"(u1)
            : "cc");
    uint64_t q0, q1;
    __asm__ (// "add $1, %1 \n\t"
        "add %4, %0 \n\t"
        "adc %5, %1 \n\t"
        : "=r"(q0), "=r"(q1)
        : "0"(p0), "1"(p1),
          "rm"(u0), "rm"(u1+1)
        : "cc");
#else
    std::pair<uint64_t, uint64_t> p0(mul_lo_hi(u1, inv));
    uint64_t q0= p0.first + u0;
    uint64_t q1= p0.second + u1 +1;
    if (q0 < u0)
        ++q1;
#endif
    uint64_t r = u0 - q1*d;

#if defined (__x86_64__)
    uint64_t corr_r;
    __asm__("xor %k[corr_r], %k[corr_r] \n\t"
            "cmp %[q0], %[r] \n\t"
            "cmovae %[d], %[corr_r] \n\t"
            "adc $-1, %[q1] \n\t"
            "add %[corr_r], %[r] \n\t"
            : [q1] "+r"(q1), [r] "+r"(r) , [corr_r]"=&r"(corr_r)
            : [q0] "rm"(q0), [d] "r"(d)
            : "cc");
#else
#if 0
    if (r > q0) {
        --q1;
        r += d;
    }
#endif
    uint64_t corr_q1= (r>q0) ? 1 : 0;
    uint64_t corr_r= (r>q0) ? d : 0;
    r += corr_r;
    q1 -= corr_q1;
#endif
    if (unlikely(r >= d)) {
        ++q1;
        r -= d;
    }
    rem = r;
    return q1;
}

inline
cftal::impl::udiv_result<uint64_t>
cftal::impl::udiv_2by1_rcp_64::
d_i(uint64_t u0, uint64_t u1, uint64_t v, uint64_t inv, unsigned l_z)
{
    // normalized values of v, u0, u1
    uint64_t u2(0);
#if defined (__x86_64__)
    __asm__ ( "shldq  %[u1], %[u2] \n\t"
              : [u2] "+r"(u2)
              : [u1] "r"(u1), "c"(l_z)
              : "cc");
    __asm__ ( "shldq  %[u0], %[u1] \n\t"
              : [u1] "+r"(u1)
              : [u0] "r"(u0), "c"(l_z)
              : "cc");
    u0 <<= l_z;
#else
    if (likely(l_z!=0)) {
        uint64_t s2, s1, s0;
        unsigned neg_shift = 64 - l_z;
        s0 = u0 << l_z;
        uint64_t u01(u0 >> neg_shift);
        s1 = u1 << l_z;
        s1 |= u01;
        s2 = u1 >> neg_shift;
        // store normalized values.
        u0 = s0;
        u1 = s1;
        u2 = s2;
    }
#endif
    uint64_t q1(0), q0(0), r(u1);
    if (likely(u2 != 0 || u1>=v)) {
        q1=sd_i(u1, u2, v, inv, r);
    }
    q0=sd_i(u0, r, v, inv, r);
    if (l_z)
        r >>= l_z;
    return make_udiv_result(q0, q1, r);
}

cftal::uint64_t
cftal::impl::udiv_2by1_rcp_64::reciprocal_word(uint64_t d)
{
    return reciprocal_word_i(d);
}

cftal::uint64_t
cftal::impl::udiv_2by1_rcp_64::
sd(uint64_t u0, uint64_t u1, uint64_t d, uint64_t inv, uint64_t& rem)
{
    return sd_i(u0, u1, d, inv, rem);
}

cftal::impl::udiv_result<uint64_t>
cftal::impl::udiv_2by1_rcp_64::
d(uint64_t u0, uint64_t u1, uint64_t v, uint64_t inv, unsigned l_z)
{
    return d_i(u0, u1, v, inv, l_z);
}

cftal::impl::udiv_result<uint64_t>
cftal::impl::udiv_2by1_rcp_64::
d(uint64_t u0, uint64_t u1, uint64_t v)
{
#if 1
    if (v==0)
        return make_udiv_result(u0, u1/v, u1);
#else
    if (v<2) {
        if (v==1)
            return make_udiv_result(u0, u1, 0);
        return make_udiv_result(u0, u1/v, u1);
    }
#endif
    unsigned l_z=lzcnt(v);
    v <<= l_z;
    uint64_t inv(reciprocal_word_i(v));
    return d_i(u0, u1, v, inv, l_z);
}

const cftal::uint16_t
cftal::impl::udiv_2by1_rcp_64::_tbl[TABLE_SIZE]={
    // empty lower part
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    // required upper part
    0x7fd, 0x7f5, 0x7ed, 0x7e5, 0x7dd, 0x7d5, 0x7ce, 0x7c6,
    0x7bf, 0x7b7, 0x7b0, 0x7a8, 0x7a1, 0x79a, 0x792, 0x78b,
    0x784, 0x77d, 0x776, 0x76f, 0x768, 0x761, 0x75b, 0x754,
    0x74d, 0x747, 0x740, 0x739, 0x733, 0x72c, 0x726, 0x720,
    0x719, 0x713, 0x70d, 0x707, 0x700, 0x6fa, 0x6f4, 0x6ee,
    0x6e8, 0x6e2, 0x6dc, 0x6d6, 0x6d1, 0x6cb, 0x6c5, 0x6bf,
    0x6ba, 0x6b4, 0x6ae, 0x6a9, 0x6a3, 0x69e, 0x698, 0x693,
    0x68d, 0x688, 0x683, 0x67d, 0x678, 0x673, 0x66e, 0x669,
    0x664, 0x65e, 0x659, 0x654, 0x64f, 0x64a, 0x645, 0x640,
    0x63c, 0x637, 0x632, 0x62d, 0x628, 0x624, 0x61f, 0x61a,
    0x616, 0x611, 0x60c, 0x608, 0x603, 0x5ff, 0x5fa, 0x5f6,
    0x5f1, 0x5ed, 0x5e9, 0x5e4, 0x5e0, 0x5dc, 0x5d7, 0x5d3,
    0x5cf, 0x5cb, 0x5c6, 0x5c2, 0x5be, 0x5ba, 0x5b6, 0x5b2,
    0x5ae, 0x5aa, 0x5a6, 0x5a2, 0x59e, 0x59a, 0x596, 0x592,
    0x58e, 0x58a, 0x586, 0x583, 0x57f, 0x57b, 0x577, 0x574,
    0x570, 0x56c, 0x568, 0x565, 0x561, 0x55e, 0x55a, 0x556,
    0x553, 0x54f, 0x54c, 0x548, 0x545, 0x541, 0x53e, 0x53a,
    0x537, 0x534, 0x530, 0x52d, 0x52a, 0x526, 0x523, 0x520,
    0x51c, 0x519, 0x516, 0x513, 0x50f, 0x50c, 0x509, 0x506,
    0x503, 0x500, 0x4fc, 0x4f9, 0x4f6, 0x4f3, 0x4f0, 0x4ed,
    0x4ea, 0x4e7, 0x4e4, 0x4e1, 0x4de, 0x4db, 0x4d8, 0x4d5,
    0x4d2, 0x4cf, 0x4cc, 0x4ca, 0x4c7, 0x4c4, 0x4c1, 0x4be,
    0x4bb, 0x4b9, 0x4b6, 0x4b3, 0x4b0, 0x4ad, 0x4ab, 0x4a8,
    0x4a5, 0x4a3, 0x4a0, 0x49d, 0x49b, 0x498, 0x495, 0x493,
    0x490, 0x48d, 0x48b, 0x488, 0x486, 0x483, 0x481, 0x47e,
    0x47c, 0x479, 0x477, 0x474, 0x472, 0x46f, 0x46d, 0x46a,
    0x468, 0x465, 0x463, 0x461, 0x45e, 0x45c, 0x459, 0x457,
    0x455, 0x452, 0x450, 0x44e, 0x44b, 0x449, 0x447, 0x444,
    0x442, 0x440, 0x43e, 0x43b, 0x439, 0x437, 0x435, 0x432,
    0x430, 0x42e, 0x42c, 0x42a, 0x428, 0x425, 0x423, 0x421,
    0x41f, 0x41d, 0x41b, 0x419, 0x417, 0x414, 0x412, 0x410,
    0x40e, 0x40c, 0x40a, 0x408, 0x406, 0x404, 0x402, 0x400
};

void
cftal::impl::print_rcp_64_table(std::ostream& s)
{
    const unsigned N = udiv_2by1_rcp_64::TABLE_SIZE;
    s << "const cftal::uint16_t\n"
      << "cftal::impl::udiv_2by1_rcp_64::_tbl[TABLE_SIZE]={\n";
    const uint32_t d64 = (1<<19) - 3*(1<<8);
    // empty lower part of table
    s << "\t// empty lower part\n";
    for (uint32_t i=0; i<N/2; ++i) {
        if ((i & 7) == 0)
            s << "\t0x000,";
        else
            s <<  " 0x000,";
        if (((i+1) & 7)==0)
            s << '\n';
    }
    s << "\t// required upper part\n";
    for (uint32_t i=N/2; i<N; ++i) {
        unsigned q(i==0 ? 0 : d64/i);
        if ((i & 7) == 0)
            s << '\t';
        else
            s << ' ';
        s << "0x"
          <<std::hex << std::setfill('0') << std::setw(3)
          << q
          << std::setfill(' ') << std::dec;
        if (i != N-1)
            s << ',';
        if (((i+1) & 7)==0)
            s << '\n';
    }
    s << "};\n";
}
