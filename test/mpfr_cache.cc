#include <cftal/test/mpfr_cache.h>
#include <cftal/cast.h>
#include <map>
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>

namespace cftal { namespace test { namespace mpfr_cache {

    template <typename _K, typename _R>
    class result_cache : public std::map<_K, std::pair<_R, int32_t> > {
        std::string _file_name;
        bool _dirty;
    public:
        using base_type=std::map<_K, std::pair<_R, int32_t> >;
        using base_type::base_type;
        // file as argument
        result_cache(const std::string& fn);
        // stores if not empty
        ~result_cache();

        void
        load(const std::string& fn);

        void
        load();

        void
        store(const std::string& fn);

        void
        dirty();
    };

    using f1_f64_map = result_cache<int64_t, int64_t>;
    using f1_f32_map = result_cache<int32_t, int32_t>;

    struct f1_cache_entry {
        f1_t _func;
        const char* _name;
        f1_f32_map _m32;
        f1_f64_map _m64;
        f1_cache_entry(f1_t f, const char* name)
            : _func(f), _name(name),
              _m32(file_name(name, "f32")),
              _m64(file_name(name, "f64")) {
        }
        static
        std::string
        file_name(const std::string& a,
                  const std::string& t);
    };


    extern f1_cache_entry f1_caches[];

    f1_cache_entry*
    lookup(f1_t f);


}}}

template <typename _K, typename _R>
cftal::test::mpfr_cache::result_cache<_K, _R>::
result_cache(const std::string& fn)
    : base_type(), _file_name(fn), _dirty(false)
{
}

template <typename _K, typename _R>
cftal::test::mpfr_cache::result_cache<_K, _R>::
~result_cache()
{
    store(_file_name);
}

template <typename _K, typename _R>
void
cftal::test::mpfr_cache::result_cache<_K, _R>::load()
{
    load(_file_name);
}

template <typename _K, typename _R>
void
cftal::test::mpfr_cache::result_cache<_K, _R>::load(const std::string& fn)
{
    std::ifstream f(fn.c_str(), std::ios::binary | std::ios::in);
    this->clear();
    while (!f.eof()) {
        using c_t = std::ifstream::char_type;
#if 1
        std::pair<_K, std::pair<_R, int32_t> > v;
        f.read(reinterpret_cast<c_t*>(&v),
               sizeof(_K) + sizeof(_R)+ sizeof(int32_t));
#else
        typename base_type::key_type k;
        typename base_type::mapped_type vv;
        f.read(reinterpret_cast<c_t*>(&k), sizeof(_K));
        f.read(reinterpret_cast<c_t*>(&vv.first), sizeof(_R));
        f.read(reinterpret_cast<c_t*>(&vv.second), sizeof(int32_t));
        auto v=std::make_pair(v, k);
#endif
        if (!f.good())
            break;
        this->insert(v);
    }
}

template <typename _K, typename _R>
void
cftal::test::mpfr_cache::result_cache<_K, _R>::store(const std::string& fn)
{
    if (this->empty())
        return;
    if (this->_dirty == false)
        return;
    std::cout << "storing cache into " << fn << std::endl;
    std::ofstream f(fn.c_str(),
                    std::ios::binary | std::ios::trunc | std::ios::out);
    for (auto b=std::cbegin(*this), e=std::cend(*this); b!=e; ++b) {
        const auto& c=*b;
        using c_t = std::ifstream::char_type;
        f.write(reinterpret_cast<const c_t*>(&c.first), sizeof(_K));
        f.write(reinterpret_cast<const c_t*>(&c.second.first),
                sizeof(_R));
        f.write(reinterpret_cast<const c_t*>(&c.second.second),
                sizeof(int32_t));
    }
}

template <typename _K, typename _R>
void
cftal::test::mpfr_cache::result_cache<_K, _R>::dirty()
{
    _dirty= true;
}

cftal::test::mpfr_cache::f1_cache_entry
cftal::test::mpfr_cache::f1_caches[]= {
    // {mpfr_cbrt, "cbrt"},
    // {mpfr_exp, "exp"},
    {nullptr, "null"}
};

cftal::test::mpfr_cache::f1_cache_entry*
cftal::test::mpfr_cache::lookup(f1_t f)
{
    f1_cache_entry* r=nullptr;
    for (auto b=std::begin(f1_caches), e=std::end(f1_caches); b!=e; ++b) {
        if (b->_func == f) {
            r = b;
            break;
        }
    }
    return r;
}

std::string
cftal::test::mpfr_cache::f1_cache_entry::
file_name(const std::string& a, const std::string& t)
{
    return a+ "-" + t + ".bin";
}

const cftal::test::mpfr_cache::mpfr_result<double>*
cftal::test::mpfr_cache::result(double a, f1_t f,
                                mpfr_result<double>& r)
{
    mpfr_result<double>* p=nullptr;
    f1_cache_entry* pe=lookup(f);
    if (pe == nullptr)
        return p;
    if (pe->_m64.empty()) {
        pe->_m64.load();
    }
    int64_t ai= as<int64_t>(a);
    auto pi=pe->_m64.find(ai);
    if (pi == std::cend(pe->_m64))
        return p;
    double rd= as<double>(pi->second.first);
    r._res = rd;
    r._mpfr_res = pi->second.second;
    return &r;
}

void
cftal::test::mpfr_cache::update(double a, f1_t f,
                                const mpfr_result<double>& r)
{
    f1_cache_entry* pe=lookup(f);
    if (pe == nullptr)
        return;
    if (pe->_m64.empty()) {
        pe->_m64.load();
    }
    int64_t ai= as<int64_t>(a);
    int64_t ri= as<int64_t>(r._res);
    auto ir=pe->_m64.insert(std::make_pair(ai,
                                           std::make_pair(ri, r._mpfr_res)));
    if (ir.second == true)
        pe->_m64.dirty();
}

