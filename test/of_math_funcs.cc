#include "cftal/test/of_math_funcs.h"
#include <cftal/fenv.h>
#include <cftal/constants.h>
#include <experimental/filesystem>
#include <fstream>
#include <sstream>

std::string
cftal::test::dirname(const std::string& fn)
{
    using namespace std::experimental::filesystem;
    path pfn(fn);
    path dn(pfn.remove_filename());
    return dn;
}

std::string
cftal::test::append_filename(const std::string& dn, const std::string& fn)
{
    using namespace std::experimental::filesystem;
    path pdn(dn);
    path pfn(fn);
    path pnfn = pdn / pfn;
    return pnfn;
}

std::string
cftal::test::filename_from_argv(const char* argv, const std::string& fn)
{
    using namespace std::experimental::filesystem;
    path pargv(argv);
    path pdn(pargv.remove_filename());
    path pfn(fn);
    path pnfn= pdn / fn;
    return pnfn;
}

std::string
cftal::test::delete_comment(const std::string& s)
{
    std::string::size_type n(s.find('#'));
    std::string r(n == std::string::npos ? s : s.substr(0, n));
    return r;
}

std::vector<cftal::test::func_arg_result< double > >
cftal::test::read_double_file(const std::string& fn, bool two_args)
{
    std::ifstream f(fn.c_str());
    if (!f.is_open()) {
        std::ostringstream e;
        e << "could not open " << fn;
        throw std::runtime_error(e.str());
    }
    std::vector<func_arg_result<double> > vr;

    std::string line;
    std::istringstream t;
    while (!std::getline(f, line).eof()) {
        line = delete_comment(line);
        if (line.empty())
            continue;
        t.str(line);
        std::uint32_t a0l{0}, a0h{0}, a1l{0}, a1h{0}, rl{0}, rh{0};
        std::uint64_t a0{0}, a1{0}, r{0};
        std::string rm;
        t >> rm >> std::hex;
        t >> a0h >> a0l;
        if (two_args) {
            t >> a1h >> a1l;
            a1 = (uint64_t(a1h) << 32) | a1l;
        }
        t >> rh >> rl;
        a0 = (uint64_t(a0h) << 32) | a0l;
        r =  (uint64_t(rh) << 32) | rl;
        unsigned m;
        if (rm == "N" || rm == "RN") {
            m = rounding_mode::nearest;
        } else if (rm == "P" || rm == "RU") {
            m = rounding_mode::upward;
        } else if (rm == "M" || rm == "RD") {
            m = rounding_mode::downward;
        } else if (rm == "Z" || rm == "RZ") {
            m = rounding_mode::towardzero;
        } else {
            continue;
        }
        if (m != rounding_mode::nearest)
            continue;
        bytes8 ua0(a0);
        bytes8 ua1(a1);
        bytes8 ur(r);

        func_arg_result<double> c(ua0._f64, ua1._f64, ur._f64);
        vr.push_back(c);
#if 0
        std::cerr << "inserting "
                  << tf._fname
                  << "( " << c._a0;
        if (tf._f2)
            std::cerr << ", " << c._a1;
        std::cerr << ") ==" << c._res << std::endl;
#endif
    }
    return vr;
}

