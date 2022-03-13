//
// Copyright (C) 2010-2022 Axel Zeuner
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
#include <cftal/test/idx.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <set>
#include <random>

namespace cftal {
    namespace test {

        struct _indent {
            unsigned _i;
			explicit
            _indent(unsigned i=4) : _i{i} {}
        };
        static _indent indent;

        std::ostream& operator<<(std::ostream& s, const _indent& i);

        struct cvt_int {
            int _i;
            unsigned _prec;
            cvt_int(int i, unsigned pr) : _i{i}, _prec{pr} {}
        };

        std::ostream& operator<<(std::ostream& s, const cvt_int& i);

        std::string
        make_file_name(const std::string& base,
                       const std::string& func,
                       int i=-2, int prec=-2);


        void gen_v2(const std::string& name_base);
        void gen_v4(const std::string& name_base);
        void gen_v8(const std::string& name_base);
        void gen_v16(const std::string& name_base);
        void gen_v32(const std::string& name_base);
    }
}

std::ostream&
cftal::test::operator<<(std::ostream& s, const _indent& i)
{
    for (unsigned j=0; j<i._i; ++j)
        s << ' ';
    return s;
}

std::ostream&
cftal::test::operator<<(std::ostream& s, const cvt_int& i)
{
    if (i._i < 0) {
        for (unsigned j=0; j<i._prec; ++j)
            s << '_';
    } else {
        char c(s.fill());
        s << std::setfill('0')
          << std::setw(i._prec) << i._i
          << std::setfill(c);
    }
    return s;
}

std::string
cftal::test::make_file_name(const std::string& base,
                            const std::string& func,
                            int i, int prec)
{
    std::stringstream s;
    s << base << '_' << func;
    if (i>-2) {
        s << '_' << cvt_int(i, prec);
    }
    s << ".h";
    return s.str();
}

void
cftal::test::gen_v2(const std::string& name_base)
{
    std::string fname(name_base + "_v2.h");
    std::ofstream f(fname.c_str(), std::ios::out | std::ios::trunc);

    f << "#if !defined __CFTAL_TEST_VEC_2_H__\n"
      << "#define __CFTAL_TEST_VEC_2_H__ 1\n\n"
      << "#include <cftal/test/of_vec.h>\n\n"
      << "template <class _T>\n"
      << "bool cftal::test::check_select_v2()\n"
      << "{\n"
      << indent << "bool rc(true);\n"
      << indent << "vec<_T, 2> a = load_vals<_T, 2>(false);\n"
      << indent << "vec<_T, 2> b = load_vals<_T, 2>(true);\n"
      << indent << "vec<_T, 2> r;\n"
      << indent << "idx id{-2,-2};\n\n";
    for (int i0=0; i0<2; ++i0) {
        for (int i1=0; i1<2; ++i1) {
            f << indent << "r=select<"
              << idx{i0,i1} << ">(a,b);\n";
            f << indent << "id= idx{"
              << idx{((i0!=0) ? 0 : 2),
                    ((i1!=0) ? 1 : 3)}
              << "};\n";
            f << indent
              << "rc &= check_val(r, id, msg_select_v2);\n";
        }
    }
    f << indent << "return rc;\n"
      << "}\n\n";

    // perm1 v2
    f << "template <class _T>\n"
      << "bool cftal::test::check_perm1_v2()\n"
      << "{\n"
      << indent << "bool rc(true);\n"
      << indent << "vec<_T, 2> a = load_vals<_T, 2>(false);\n"
      << indent << "vec<_T, 2> r;\n"
      << indent << "idx id{-2,-2};\n\n";
    for (int i0=-1; i0<2; ++i0) {
        for (int i1=-1; i1<2; ++i1) {
            f << indent << "r=permute<"
              << idx{i0, i1} << ">(a);\n";
            f << indent << "id= idx{"
              << idx{i0, i1}
              << "};\n";
            f << indent
              << "rc &= check_val(r, id, msg_perm1_v2);\n";
        }
    }
    f << indent << "return rc;\n"
      << "}\n\n";

    // perm2 v2
    f << "template <class _T>\n"
      << "bool cftal::test::check_perm2_v2()\n"
      << "{\n"
      << indent << "bool rc(true);\n"
      << indent << "vec<_T, 2> a = load_vals<_T, 2>(false);\n"
      << indent << "vec<_T, 2> b = load_vals<_T, 2>(true);\n"
      << indent << "vec<_T, 2> r;\n"
      << indent << "idx id{-2,-2};\n\n";
    for (int i0=-1; i0<4; ++i0) {
        for (int i1=-1; i1<4; ++i1) {
            f << indent << "r=permute<"
              << idx{i0, i1} << ">(a,b);\n";
            f << indent << "id= idx{"
              << idx{i0, i1}
              << "};\n";
            f << indent
              << "rc &= check_val(r, id, msg_perm2_v2);\n";
        }
    }
    f << indent << "return rc;\n"
      << "}\n\n"
      << "// Local variables:\n"
      << "// mode: c++\n"
      << "// end:\n"
      << "#endif\n";
}

void
cftal::test::gen_v4(const std::string& name_base)
{
    std::string fname(name_base + "_v4.h");
    std::ofstream f(fname.c_str(), std::ios::out | std::ios::trunc);

    f << "#if !defined __CFTAL_TEST_VEC_4_H__\n"
      << "#define __CFTAL_TEST_VEC_4_H__ 1\n\n"
      << "#include <cftal/test/of_vec.h>\n\n"
      << "template <class _T>\n"
      << "bool cftal::test::check_select_v4()\n"
      << "{\n"
      << indent << "bool rc(true);\n"
      << indent << "vec<_T, 4> a = load_vals<_T, 4>(false);\n"
      << indent << "vec<_T, 4> b = load_vals<_T, 4>(true);\n"
      << indent << "vec<_T, 4> r;\n"
      << indent << "idx id{-2,-2,-2,-2};\n\n";
    for (int i0=0; i0<2; ++i0) {
        for (int i1=0; i1<2; ++i1) {
            for (int i2=0; i2<2; ++i2) {
                for (int i3=0; i3<2; ++i3) {
                    f << indent << "r=select<"
                      << idx{i0,i1,i2,i3} << ">(a,b);\n";
                    f << indent << "id= idx{"
                      << idx{ ((i0!=0) ? 0 : 4),
                              ((i1!=0) ? 1 : 5),
                              ((i2!=0) ? 2 : 6),
                              ((i3!=0) ? 3 : 7)
                            }
                    << "};\n";
                    f << indent
                      << "rc &= check_val(r, id, msg_select_v4);\n";
                }
            }
        }
    }
    f << indent << "return rc;\n"
      << "}\n\n";

    // perm1 v4
    f << "template <class _T>\n"
      << "bool cftal::test::check_perm1_v4()\n"
      << "{\n"
      << indent << "bool rc(true);\n"
      << indent << "vec<_T, 4> a = load_vals<_T, 4>(false);\n"
      << indent << "vec<_T, 4> r;\n"
      << indent << "idx id{-2,-2,-2,-2};\n\n";
    for (int i0=-1; i0<4; ++i0) {
        for (int i1=-1; i1<4; ++i1) {
            for (int i2=-1; i2<4; ++i2) {
                for (int i3=-1; i3<4; ++i3) {
                    f << indent << "r=permute<"
                      << idx{i0, i1, i2, i3} << ">(a);\n";
                    f << indent << "id= idx{"
                      << idx{i0, i1, i2, i3}
                    << "};\n";
                    f << indent
                      << "rc &= check_val(r, id, msg_perm1_v4);\n";
                }
            }
        }
    }
    f << indent << "return rc;\n"
      << "}\n\n";

    // perm2 v4
    f << "template <class _T>\n"
      << "bool cftal::test::check_perm2_v4()\n"
      << "{\n"
      << indent << "bool rc(true);\n"
      << indent << "vec<_T, 4> a = load_vals<_T, 4>(false);\n"
      << indent << "vec<_T, 4> b = load_vals<_T, 4>(true);\n"
      << indent << "vec<_T, 4> r;\n"
      << indent << "idx id{-2,-2,-2,-2};\n\n";
    for (int i0=-1; i0<8; ++i0) {
        for (int i1=-1; i1<8; ++i1) {
            for (int i2=-1; i2<8; ++i2) {
                for (int i3=-1; i3<8; ++i3) {
                    f << indent << "r=permute<"
                      << idx{i0, i1, i2, i3} << ">(a,b);\n";
                    f << indent << "id= idx{"
                      << idx{i0, i1, i2, i3}
                    << "};\n";
                    f << indent
                      << "rc &= check_val(r, id, msg_perm2_v4);\n";
                }
            }
        }
    }
    f << indent << "return rc;\n"
      << "}\n\n"
      << "// Local variables:\n"
      << "// mode: c++\n"
      << "// end:\n"
      << "#endif\n";
}

void
cftal::test::gen_v8(const std::string& name_base)
{
    std::string fname(name_base + "_v8.h");
    std::ofstream f(fname.c_str(), std::ios::out | std::ios::trunc);

    f << "#if !defined __CFTAL_TEST_VEC_8_H__\n"
      << "#define __CFTAL_TEST_VEC_8_H__ 1\n\n"
      << "#include <cftal/test/of_vec.h>\n\n"
      << "template <class _T>\n"
      << "bool cftal::test::check_select_v8()\n"
      << "{\n"
      << indent << "bool rc(true);\n"
      << indent << "vec<_T, 8> a = load_vals<_T, 8>(false);\n"
      << indent << "vec<_T, 8> b = load_vals<_T, 8>(true);\n"
      << indent << "vec<_T, 8> r;\n"
      << indent << "idx id{-2,-2,-2,-2,-2,-2,-2,-2};\n\n";
    for (int i0=0; i0<2; ++i0) {
        for (int i1=0; i1<2; ++i1) {
            for (int i2=0; i2<2; ++i2) {
                for (int i3=0; i3<2; ++i3) {
                    for (int i4=0; i4<2; ++i4) {
                        for (int i5=0; i5<2; ++i5) {
                            for (int i6=0; i6<2; ++i6) {
                                for (int i7=0; i7<2; ++i7) {
                                    f << indent << "r=select<"
                                      << idx{i0,i1,i2,i3,i4,i5,i6,i7} << ">(a,b);\n";
                                    f << indent << "id= idx{"
                                      << idx{ ((i0!=0) ? 0 : 8),
                                            ((i1!=0) ? 1 : 9),
                                            ((i2!=0) ? 2 : 10),
                                            ((i3!=0) ? 3 : 11),
                                            ((i4!=0) ? 4 : 12),
                                            ((i5!=0) ? 5 : 13),
                                            ((i6!=0) ? 6 : 14),
                                            ((i7!=0) ? 7 : 15)
                                            }
                                    << "};\n";
                                    f << indent
                                      << "rc &= check_val(r, id, msg_select_v8);\n";
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    f << indent << "return rc;\n"
      << "}\n\n";

    std::set<idx> indices;
    std::mt19937 rnd;
    // perm1 v8
    f << "template <class _T>\n"
      << "bool cftal::test::check_perm1_v8()\n"
      << "{\n"
      << indent << "bool rc(true);\n"
      << indent << "vec<_T, 8> a = load_vals<_T, 8>(false);\n"
      << indent << "vec<_T, 8> r;\n"
      << indent << "idx id{-2,-2,-2,-2,-2,-2,-2,-2};\n\n";
    const int TEST_CASES= 4096;
    std::uniform_int_distribution<> d_m1_7(-1, 7);
    while (indices.size() < TEST_CASES) {
        idx id{ d_m1_7(rnd), d_m1_7(rnd),
                d_m1_7(rnd), d_m1_7(rnd),
                d_m1_7(rnd), d_m1_7(rnd),
                d_m1_7(rnd), d_m1_7(rnd)};
        auto p= indices.insert(id);
        if (p.second == false)
            continue;
        f << indent << "r=permute<"
          << id << ">(a);\n";
        f << indent << "id= idx{"
          << id
        << "};\n";
        f << indent
          << "rc &= check_val(r, id, msg_perm1_v8);\n";
    }
#if 0
    for (int i0=-1; i0<8; ++i0) {
        for (int i1=-1; i1<8; ++i1) {
            for (int i2=-1; i2<8; ++i2) {
                for (int i3=-1; i3<8; ++i3) {
                    for (int i4=-1; i4<8; ++i4) {
                        for (int i5=-1; i5<8; ++i5) {
                            for (int i6=-1; i6<8; ++i6) {
                                for (int i7=-1; i7<8; ++i7) {
                                    f << indent << "r=permute<"
                                      << idx{i0, i1, i2, i3, i4, i5, i6, i7} << ">(a);\n";
                                    f << indent << "id= idx{"
                                      << idx{i0, i1, i2, i3, i4, i5, i6, i7}
                                    << "};\n";
                                    f << indent
                                      << "rc &= check_val(r, id, \"perm1_v8\");\n";
                                }
                            }
                        }
                    }
                }
            }
        }
    }
#endif
    f << indent << "return rc;\n"
      << "}\n\n";

    std::uniform_int_distribution<> d_m1_15(-1, 15);
    indices.clear();
    // perm2 v8
    f << "template <class _T>\n"
      << "bool cftal::test::check_perm2_v8()\n"
      << "{\n"
      << indent << "bool rc(true);\n"
      << indent << "vec<_T, 8> a = load_vals<_T, 8>(false);\n"
      << indent << "vec<_T, 8> b = load_vals<_T, 8>(true);\n"
      << indent << "vec<_T, 8> r;\n"
      << indent << "idx id{-2,-2,-2,-2,-2,-2,-2,-2};\n\n";
    while (indices.size() < TEST_CASES) {
        idx id{ d_m1_15(rnd), d_m1_15(rnd),
                d_m1_15(rnd), d_m1_15(rnd),
                d_m1_15(rnd), d_m1_15(rnd),
                d_m1_15(rnd), d_m1_15(rnd)};
        auto p= indices.insert(id);
        if (p.second == false)
            continue;
        f << indent << "r=permute<"
          << id << ">(a, b);\n";
        f << indent << "id= idx{"
          << id
        << "};\n";
        f << indent
          << "rc &= check_val(r, id, msg_perm2_v8);\n";
    }
#if 0
    for (int i0=-1; i0<16; ++i0) {
        for (int i1=-1; i1<16; ++i1) {
            for (int i2=-1; i2<16; ++i2) {
                for (int i3=-1; i3<16; ++i3) {
                    for (int i4=-1; i4<16; ++i4) {
                        for (int i5=-1; i5<16; ++i5) {
                            for (int i6=-1; i6<16; ++i6) {
                                for (int i7=-1; i7<16; ++i7) {
                                    f << indent << "r=permute<"
                                      << idx{i0, i1, i2, i3, i4, i5, i6, i7} << ">(a,b);\n";
                                    f << indent << "id= idx{"
                                      << idx{i0, i1, i2, i3, i4, i5, i6, i7}
                                    << "};\n";
                                    f << indent
                                      << "rc &= check_val(r, id, \"perm2_v8\");\n";
                                }
                            }
                        }
                    }
                }
            }
        }
    }
#endif
    f << indent << "return rc;\n"
      << "}\n\n"
      << "// Local variables:\n"
      << "// mode: c++\n"
      << "// end:\n"
      << "#endif\n";
}

void
cftal::test::gen_v16(const std::string& name_base)
{
    std::string fname(name_base + "_v16.h");
    std::ofstream f(fname.c_str(), std::ios::out | std::ios::trunc);

    f << "#if !defined __CFTAL_TEST_VEC_16_H__\n"
      << "#define __CFTAL_TEST_VEC_16_H__ 1\n\n"
      << "#include <cftal/test/of_vec.h>\n\n"
      << "template <class _T>\n"
      << "bool cftal::test::check_select_v16()\n"
      << "{\n"
      << indent << "bool rc(true);\n"
      << indent << "vec<_T, 16> a = load_vals<_T, 16>(false);\n"
      << indent << "vec<_T, 16> b = load_vals<_T, 16>(true);\n"
      << indent << "vec<_T, 16> r;\n"
      << indent << "idx id{-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2};\n\n";
    std::set<idx> indices;
    std::mt19937 rnd;
#if 1
    const int SELECT_TEST_CASES= 4096;
    std::uniform_int_distribution<> d_0_1(0, 1);
    while (indices.size() < SELECT_TEST_CASES) {
        idx id{ d_0_1(rnd) != 0 ? 0 : 16,
                d_0_1(rnd) != 0 ? 1 : 17,
                d_0_1(rnd) != 0 ? 2 : 18,
                d_0_1(rnd) != 0 ? 3 : 19,
                d_0_1(rnd) != 0 ? 4 : 20,
                d_0_1(rnd) != 0 ? 5 : 21,
                d_0_1(rnd) != 0 ? 6 : 22,
                d_0_1(rnd) != 0 ? 7 : 23,
                d_0_1(rnd) != 0 ? 8 : 24,
                d_0_1(rnd) != 0 ? 9 : 25,
                d_0_1(rnd) != 0 ? 10 : 26,
                d_0_1(rnd) != 0 ? 11 : 27,
                d_0_1(rnd) != 0 ? 12 : 28,
                d_0_1(rnd) != 0 ? 13 : 29,
                d_0_1(rnd) != 0 ? 14 : 30,
                d_0_1(rnd) != 0 ? 15 : 31 };
        idx idt{
            id[0] < 16 ? 1 : 0,
            id[1] < 16 ? 1 : 0,
            id[2] < 16 ? 1 : 0,
            id[3] < 16 ? 1 : 0,
            id[4] < 16 ? 1 : 0,
            id[5] < 16 ? 1 : 0,
            id[6] < 16 ? 1 : 0,
            id[7] < 16 ? 1 : 0,
            id[8] < 16 ? 1 : 0,
            id[9] < 16 ? 1 : 0,
            id[10] < 16 ? 1 : 0,
            id[11] < 16 ? 1 : 0,
            id[12] < 16 ? 1 : 0,
            id[13] < 16 ? 1 : 0,
            id[14] < 16 ? 1 : 0,
            id[15] < 16 ? 1 : 0
        };
        auto p= indices.insert(id);
        if (p.second == false)
            continue;
        f << indent << "r=select<"
          << idt << ">(a, b);\n";
        f << indent << "id= idx{"
          << id
        << "};\n";
        f << indent
          << "rc &= check_val(r, id, msg_select_v16);\n";
    }
    indices.clear();
#else
    for (int i00=0; i00<2; ++i00) {
        for (int i01=0; i01<2; ++i01) {
            for (int i02=0; i02<2; ++i02) {
                for (int i03=0; i03<2; ++i03) {
                    for (int i04=0; i04<2; ++i04) {
                        for (int i05=0; i05<2; ++i05) {
                            for (int i06=0; i06<2; ++i06) {
                                for (int i07=0; i07<2; ++i07) {
                                for (int i08=0; i08<2; ++i08) {
                                for (int i09=0; i09<2; ++i09) {
                                for (int i10=0; i10<2; ++i10) {
                                for (int i11=0; i11<2; ++i11) {
                                for (int i12=0; i12<2; ++i12) {
                                for (int i13=0; i13<2; ++i13) {
                                for (int i14=0; i14<2; ++i14) {
                                for (int i15=0; i15<2; ++i15) {
                                    f << indent << "r=select<"
                                      << idx{i00,i01,i02,i03,i04,i05,i06,i07,
                                             i08,i09,i10,i11,i12,i13,i14,i15,
                                    } << ">(a,b);\n";
                                    f << indent << "id= idx{"
                                      << idx{
                                            ((i00!=0) ? 0 : 16),
                                            ((i01!=0) ? 1 : 17),
                                            ((i02!=0) ? 2 : 18),
                                            ((i03!=0) ? 3 : 19),
                                            ((i04!=0) ? 4 : 20),
                                            ((i05!=0) ? 5 : 21),
                                            ((i06!=0) ? 6 : 22),
                                            ((i07!=0) ? 7 : 23),
                                            ((i08!=0) ? 8 : 24),
                                            ((i09!=0) ? 9 : 25),
                                            ((i10!=0) ? 10 : 26),
                                            ((i11!=0) ? 11 : 27),
                                            ((i12!=0) ? 12 : 28),
                                            ((i13!=0) ? 13 : 29),
                                            ((i14!=0) ? 14 : 30),
                                            ((i15!=0) ? 15 : 31)
                                            }
                                    << "};\n";
                                    f << indent
                                      << "rc &= check_val(r, id, msg_select_v16);\n";
                                }}}}}}}}
                                }
                            }
                        }
                    }
                }
            }
        }
    }
#endif
    f << indent << "return rc;\n"
      << "}\n\n";

    // perm1 v16
    f << "template <class _T>\n"
      << "bool cftal::test::check_perm1_v16()\n"
      << "{\n"
      << indent << "bool rc(true);\n"
      << indent << "vec<_T, 16> a = load_vals<_T, 16>(false);\n"
      << indent << "vec<_T, 16> r;\n"
      << indent << "idx id{-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2};\n\n";
    const int TEST_CASES= 4096;
    std::uniform_int_distribution<> d_m1_15(-1, 15);
    while (indices.size() < TEST_CASES) {
        idx id{ d_m1_15(rnd), d_m1_15(rnd),
                d_m1_15(rnd), d_m1_15(rnd),
                d_m1_15(rnd), d_m1_15(rnd),
                d_m1_15(rnd), d_m1_15(rnd),
                d_m1_15(rnd), d_m1_15(rnd),
                d_m1_15(rnd), d_m1_15(rnd),
                d_m1_15(rnd), d_m1_15(rnd),
                d_m1_15(rnd), d_m1_15(rnd)};
        auto p= indices.insert(id);
        if (p.second == false)
            continue;
        f << indent << "r=permute<"
          << id << ">(a);\n";
        f << indent << "id= idx{"
          << id
        << "};\n";
        f << indent
          << "rc &= check_val(r, id, msg_perm1_v16);\n";
    }
#if 0
    for (int i0=-1; i0<8; ++i0) {
        for (int i1=-1; i1<8; ++i1) {
            for (int i2=-1; i2<8; ++i2) {
                for (int i3=-1; i3<8; ++i3) {
                    for (int i4=-1; i4<8; ++i4) {
                        for (int i5=-1; i5<8; ++i5) {
                            for (int i6=-1; i6<8; ++i6) {
                                for (int i7=-1; i7<8; ++i7) {
                                    f << indent << "r=permute<"
                                      << idx{i0, i1, i2, i3, i4, i5, i6, i7} << ">(a);\n";
                                    f << indent << "id= idx{"
                                      << idx{i0, i1, i2, i3, i4, i5, i6, i7}
                                    << "};\n";
                                    f << indent
                                      << "rc &= check_val(r, id, \"perm1_v8\");\n";
                                }
                            }
                        }
                    }
                }
            }
        }
    }
#endif
    f << indent << "return rc;\n"
      << "}\n\n";

    std::uniform_int_distribution<> d_m1_31(-1, 31);
    indices.clear();
    // perm2 v8
    f << "template <class _T>\n"
      << "bool cftal::test::check_perm2_v16()\n"
      << "{\n"
      << indent << "bool rc(true);\n"
      << indent << "vec<_T, 16> a = load_vals<_T, 16>(false);\n"
      << indent << "vec<_T, 16> b = load_vals<_T, 16>(true);\n"
      << indent << "vec<_T, 16> r;\n"
      << indent << "idx id{-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2};\n\n";
    while (indices.size() < TEST_CASES) {
        idx id{ d_m1_31(rnd), d_m1_31(rnd),
                d_m1_31(rnd), d_m1_31(rnd),
                d_m1_31(rnd), d_m1_31(rnd),
                d_m1_31(rnd), d_m1_31(rnd),
                d_m1_31(rnd), d_m1_31(rnd),
                d_m1_31(rnd), d_m1_31(rnd),
                d_m1_31(rnd), d_m1_31(rnd),
                d_m1_31(rnd), d_m1_31(rnd)};
        auto p= indices.insert(id);
        if (p.second == false)
            continue;
        f << indent << "r=permute<"
          << id << ">(a, b);\n";
        f << indent << "id= idx{"
          << id
        << "};\n";
        f << indent
          << "rc &= check_val(r, id, msg_perm2_v16);\n";
    }
#if 0
    for (int i0=-1; i0<16; ++i0) {
        for (int i1=-1; i1<16; ++i1) {
            for (int i2=-1; i2<16; ++i2) {
                for (int i3=-1; i3<16; ++i3) {
                    for (int i4=-1; i4<16; ++i4) {
                        for (int i5=-1; i5<16; ++i5) {
                            for (int i6=-1; i6<16; ++i6) {
                                for (int i7=-1; i7<16; ++i7) {
                                    f << indent << "r=permute<"
                                      << idx{i0, i1, i2, i3, i4, i5, i6, i7} << ">(a,b);\n";
                                    f << indent << "id= idx{"
                                      << idx{i0, i1, i2, i3, i4, i5, i6, i7}
                                    << "};\n";
                                    f << indent
                                      << "rc &= check_val(r, id, \"perm2_v8\");\n";
                                }
                            }
                        }
                    }
                }
            }
        }
    }
#endif
    f << indent << "return rc;\n"
      << "}\n\n"
      << "// Local variables:\n"
      << "// mode: c++\n"
      << "// end:\n"
      << "#endif\n";
}

void
cftal::test::gen_v32(const std::string& name_base)
{
    std::string fname(name_base + "_v32.h");
    std::ofstream f(fname.c_str(), std::ios::out | std::ios::trunc);

    f << "#if !defined __CFTAL_TEST_VEC_32_H__\n"
      << "#define __CFTAL_TEST_VEC_32_H__ 1\n\n"
      << "#include <cftal/test/of_vec.h>\n\n"
      << "template <class _T>\n"
      << "bool cftal::test::check_select_v32()\n"
      << "{\n"
      << indent << "bool rc(true);\n"
      << indent << "vec<_T, 32> a = load_vals<_T, 32>(false);\n"
      << indent << "vec<_T, 32> b = load_vals<_T, 32>(true);\n"
      << indent << "vec<_T, 32> r;\n"
      << indent << "idx id{-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,\n"
      << indent << "       -2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2};"
      << "\n\n";

    std::set<idx> indices;
    std::mt19937 rnd;

    const int SELECT_TEST_CASES= 4096;
    std::uniform_int_distribution<> d_0_1(0, 1);
    while (indices.size() < SELECT_TEST_CASES) {
        idx id{ d_0_1(rnd) != 0 ? 0 : 32,
                d_0_1(rnd) != 0 ? 1 : 33,
                d_0_1(rnd) != 0 ? 2 : 34,
                d_0_1(rnd) != 0 ? 3 : 35,
                d_0_1(rnd) != 0 ? 4 : 36,
                d_0_1(rnd) != 0 ? 5 : 37,
                d_0_1(rnd) != 0 ? 6 : 38,
                d_0_1(rnd) != 0 ? 7 : 39,
                d_0_1(rnd) != 0 ? 8 : 40,
                d_0_1(rnd) != 0 ? 9 : 41,
                d_0_1(rnd) != 0 ? 10 : 42,
                d_0_1(rnd) != 0 ? 11 : 43,
                d_0_1(rnd) != 0 ? 12 : 44,
                d_0_1(rnd) != 0 ? 13 : 45,
                d_0_1(rnd) != 0 ? 14 : 46,
                d_0_1(rnd) != 0 ? 15 : 47,
                d_0_1(rnd) != 0 ? 16 : 48,
                d_0_1(rnd) != 0 ? 17 : 49,
                d_0_1(rnd) != 0 ? 18 : 50,
                d_0_1(rnd) != 0 ? 19 : 51,
                d_0_1(rnd) != 0 ? 20 : 52,
                d_0_1(rnd) != 0 ? 21 : 53,
                d_0_1(rnd) != 0 ? 22 : 54,
                d_0_1(rnd) != 0 ? 23 : 55,
                d_0_1(rnd) != 0 ? 24 : 56,
                d_0_1(rnd) != 0 ? 25 : 57,
                d_0_1(rnd) != 0 ? 26 : 58,
                d_0_1(rnd) != 0 ? 27 : 59,
                d_0_1(rnd) != 0 ? 28 : 60,
                d_0_1(rnd) != 0 ? 29 : 61,
                d_0_1(rnd) != 0 ? 30 : 62,
                d_0_1(rnd) != 0 ? 31 : 63
        };
        idx idt{
            id[0] < 32 ? 1 : 0,
            id[1] < 32 ? 1 : 0,
            id[2] < 32 ? 1 : 0,
            id[3] < 32 ? 1 : 0,
            id[4] < 32 ? 1 : 0,
            id[5] < 32 ? 1 : 0,
            id[6] < 32 ? 1 : 0,
            id[7] < 32 ? 1 : 0,
            id[8] < 32 ? 1 : 0,
            id[9] < 32 ? 1 : 0,
            id[10] < 32 ? 1 : 0,
            id[11] < 32 ? 1 : 0,
            id[12] < 32 ? 1 : 0,
            id[13] < 32 ? 1 : 0,
            id[14] < 32 ? 1 : 0,
            id[15] < 32 ? 1 : 0,
            id[16] < 32 ? 1 : 0,
            id[17] < 32 ? 1 : 0,
            id[18] < 32 ? 1 : 0,
            id[19] < 32 ? 1 : 0,
            id[20] < 32 ? 1 : 0,
            id[21] < 32 ? 1 : 0,
            id[22] < 32 ? 1 : 0,
            id[23] < 32 ? 1 : 0,
            id[24] < 32 ? 1 : 0,
            id[25] < 32 ? 1 : 0,
            id[26] < 32 ? 1 : 0,
            id[27] < 32 ? 1 : 0,
            id[28] < 32 ? 1 : 0,
            id[29] < 32 ? 1 : 0,
            id[30] < 32 ? 1 : 0,
            id[31] < 32 ? 1 : 0
        };
        auto p= indices.insert(id);
        if (p.second == false)
            continue;
        f << indent << "r=select<"
          << idt << ">(a, b);\n";
        f << indent << "id= idx{"
          << id
        << "};\n";
        f << indent
          << "rc &= check_val(r, id, msg_select_v32);\n";
    }
    indices.clear();
    f << indent << "return rc;\n"
      << "}\n\n";

    // perm1 v32
    f << "template <class _T>\n"
      << "bool cftal::test::check_perm1_v32()\n"
      << "{\n"
      << indent << "bool rc(true);\n"
      << indent << "vec<_T, 32> a = load_vals<_T, 32>(false);\n"
      << indent << "vec<_T, 32> r;\n"
      << indent << "idx id{-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,\n"
      << indent << "       -2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2};"
      << "\n\n";
    const int TEST_CASES= 4096;
    std::uniform_int_distribution<> d_m1_31(-1, 31);
    while (indices.size() < TEST_CASES) {
        idx id{ d_m1_31(rnd), d_m1_31(rnd),
                d_m1_31(rnd), d_m1_31(rnd),
                d_m1_31(rnd), d_m1_31(rnd),
                d_m1_31(rnd), d_m1_31(rnd),
                d_m1_31(rnd), d_m1_31(rnd),
                d_m1_31(rnd), d_m1_31(rnd),
                d_m1_31(rnd), d_m1_31(rnd),
                d_m1_31(rnd), d_m1_31(rnd),
                d_m1_31(rnd), d_m1_31(rnd),
                d_m1_31(rnd), d_m1_31(rnd),
                d_m1_31(rnd), d_m1_31(rnd),
                d_m1_31(rnd), d_m1_31(rnd),
                d_m1_31(rnd), d_m1_31(rnd),
                d_m1_31(rnd), d_m1_31(rnd),
                d_m1_31(rnd), d_m1_31(rnd),
                d_m1_31(rnd), d_m1_31(rnd)};
        auto p= indices.insert(id);
        if (p.second == false)
            continue;
        f << indent << "r=permute<"
          << id << ">(a);\n";
        f << indent << "id= idx{"
          << id
        << "};\n";
        f << indent
          << "rc &= check_val(r, id, msg_perm1_v32);\n";
    }
    f << indent << "return rc;\n"
      << "}\n\n";

    std::uniform_int_distribution<> d_m1_63(-1, 63);
    indices.clear();
    // perm2 v8
    f << "template <class _T>\n"
      << "bool cftal::test::check_perm2_v32()\n"
      << "{\n"
      << indent << "bool rc(true);\n"
      << indent << "vec<_T, 32> a = load_vals<_T, 32>(false);\n"
      << indent << "vec<_T, 32> b = load_vals<_T, 32>(true);\n"
      << indent << "vec<_T, 32> r;\n"
      << indent << "idx id{-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,\n"
      << indent << "       -2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2};"
      << "\n\n";
    while (indices.size() < TEST_CASES) {
        idx id{ d_m1_63(rnd), d_m1_63(rnd),
                d_m1_63(rnd), d_m1_63(rnd),
                d_m1_63(rnd), d_m1_63(rnd),
                d_m1_63(rnd), d_m1_63(rnd),
                d_m1_63(rnd), d_m1_63(rnd),
                d_m1_63(rnd), d_m1_63(rnd),
                d_m1_63(rnd), d_m1_63(rnd),
                d_m1_63(rnd), d_m1_63(rnd),
                d_m1_63(rnd), d_m1_63(rnd),
                d_m1_63(rnd), d_m1_63(rnd),
                d_m1_63(rnd), d_m1_63(rnd),
                d_m1_63(rnd), d_m1_63(rnd),
                d_m1_63(rnd), d_m1_63(rnd),
                d_m1_63(rnd), d_m1_63(rnd),
                d_m1_63(rnd), d_m1_63(rnd),
                d_m1_63(rnd), d_m1_63(rnd)
        };
        auto p= indices.insert(id);
        if (p.second == false)
            continue;
        f << indent << "r=permute<"
          << id << ">(a, b);\n";
        f << indent << "id= idx{"
          << id
        << "};\n";
        f << indent
          << "rc &= check_val(r, id, msg_perm2_v32);\n";
    }
    f << indent << "return rc;\n"
      << "}\n\n"
      << "// Local variables:\n"
      << "// mode: c++\n"
      << "// end:\n"
      << "#endif\n";
}

int main()
{
    cftal::test::gen_v2("of_vec");
    cftal::test::gen_v4("of_vec");
    cftal::test::gen_v8("of_vec");
    cftal::test::gen_v16("of_vec");
    cftal::test::gen_v32("of_vec");
    return 0;
}
