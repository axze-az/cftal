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
              << "rc &= check_val(r, id, \"select_v2\");\n";
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
              << "rc &= check_val(r, id, \"perm1_v2\");\n";
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
              << "rc &= check_val(r, id, \"perm2_v2\");\n";
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
                      << "rc &= check_val(r, id, \"select_v4\");\n";
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
                      << "rc &= check_val(r, id, \"perm1_v4\");\n";
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
                      << "rc &= check_val(r, id, \"perm2_v4\");\n";
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
                                      << "rc &= check_val(r, id, \"select_v8\");\n";
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
    const int TEST_CASES= 8192;
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
          << "rc &= check_val(r, id, \"perm1_v8\");\n";
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
          << "rc &= check_val(r, id, \"perm2_v8\");\n";
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



int main()
{
    cftal::test::gen_v2("of_vec");
    cftal::test::gen_v4("of_vec");
    cftal::test::gen_v8("of_vec");
    return 0;
}
