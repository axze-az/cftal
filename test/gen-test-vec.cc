#include <cftal/config.h>
#include <cftal/test/idx.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

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



int main()
{
    cftal::test::gen_v2("of_vec");
    return 0;
}
