#include <cftal/test/mpfr_cache.h>
#include <cftal/cast.h>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>

namespace cftal { namespace test { namespace mpfr_cache {

    template <typename _K, typename _R>
    class result_cache {
        using key_type = _K;
    public:
        using mapped_type = std::pair<_R, int32_t>;
    private:
        using map_type = std::map<key_type, mapped_type>;
        using value_type = std::pair<key_type, mapped_type>;
        using vec_type = std::vector<value_type>;
        vec_type _v;
        map_type _m;
        std::string _file_name;
    public:
        // file as argument
        result_cache(const std::string& fn);
        // stores if not empty
        ~result_cache();
        void
        load();
        void
        store();

        const mapped_type*
        find(const key_type& k)
            const;

        void
        insert(const value_type& v);

        bool
        empty()
            const;
    };

    using f1_f64_map = result_cache<int64_t, int64_t>;
    using f1_f32_map = result_cache<int32_t, int32_t>;

    struct f1_cache_entry {
        std::string _name;
        f1_f32_map _m32;
        f1_f64_map _m64;
        f1_cache_entry(const std::string& name)
            : _name(name),
              _m32(file_name(name, "f32")),
              _m64(file_name(name, "f64")) {
        }
        static
        std::string
        file_name(const std::string& a,
                  const std::string& t);
    };

    using f1_cache_map=std::map<f1_t, f1_cache_entry>;
    extern f1_cache_map f1_entries;

    f1_cache_entry*
    lookup(f1_t f);

}}}

template <typename _K, typename _R>
cftal::test::mpfr_cache::result_cache<_K, _R>::
result_cache(const std::string& fn)
    : _file_name(fn)
{
}

template <typename _K, typename _R>
cftal::test::mpfr_cache::result_cache<_K, _R>::
~result_cache()
{
    store();
}

template <typename _K, typename _R>
void
cftal::test::mpfr_cache::result_cache<_K, _R>::load()
{
    std::ifstream f(_file_name.c_str(), std::ios::binary | std::ios::in);
    if (!f.good())
        return;
    f.seekg(0, std::ios::end);
    std::ifstream::off_type s=f.tellg();
    f.seekg(0);
    _v.clear();
    _v.resize(s/sizeof(value_type));
    using c_t = std::ifstream::char_type;
    f.read(reinterpret_cast<c_t*>(_v.data()), s);
}

template <typename _K, typename _R>
void
cftal::test::mpfr_cache::result_cache<_K, _R>::store()
{
    std::size_t vs=_v.size(), ms= _m.size(), s=vs+ms;
    if (ms==0)
        return;
    _v.reserve(s);
    std::cout << "writing cache into " << _file_name << std::endl;
    // sort the results:
    std::cout << "info: moving the results"<< std::endl;
    std::move(std::begin(_m), std::end(_m), std::back_inserter(_v));
    // does not help anything because the memory is not given back
    // to the system :-(
    _m.clear();
    std::cout << "info: sorting the results"<< std::endl;
    std::sort(std::begin(_v), std::end(_v),
              [](const value_type& a, const value_type& b)->bool {
                  return a < b;
              });
    std::cout << "info: writing the results"<< std::endl;
    std::ofstream f(_file_name.c_str(),
                    std::ios::binary | std::ios::trunc | std::ios::out);
    using c_t = std::ifstream::char_type;
    f.write(reinterpret_cast<const c_t*>(_v.data()), s*sizeof(value_type));
}

template <typename _K, typename _R>
const
typename
cftal::test::mpfr_cache::result_cache<_K, _R>::mapped_type*
cftal::test::mpfr_cache::result_cache<_K, _R>::
find(const key_type& k)
    const
{
    // vector lookup
    const mapped_type* pr=nullptr;
    auto ve= std::cend(_v);
    auto vf= std::upper_bound(std::cbegin(_v), ve,
                              value_type(k, std::make_pair(0.0, 0)),
                              [](const value_type& a,
                                 const value_type& b)->bool {
                                return a.first < b.first;
                              });
    if (vf != std::cbegin(_v)) {
        --vf;
        if (vf->first == k) {
            pr = &vf->second;
        }
    }
    // map lookup if nothing was found
    if (pr == nullptr) {
        auto me=std::cend(_m);
        auto mf=_m.find(k);
        if (mf != me) {
            pr = &mf->second;
        }
    }
    return pr;
}

template <typename _K, typename _R>
void
cftal::test::mpfr_cache::result_cache<_K, _R>::
insert(const value_type& v)
{
    _m.insert(v);
}

template <typename _K, typename _R>
bool
cftal::test::mpfr_cache::result_cache<_K, _R>::
empty()
    const
{
    return _v.empty() && _m.empty();
}

cftal::test::mpfr_cache::f1_cache_map
cftal::test::mpfr_cache::f1_entries;

cftal::test::mpfr_cache::f1_cache_entry*
cftal::test::mpfr_cache::lookup(f1_t f)
{
    f1_cache_entry* r=nullptr;
    auto ff= f1_entries.find(f);
    if (ff != std::end(f1_entries)) {
        r = &ff->second;
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
    if (pi == nullptr)
        return p;
    double rd= as<double>(pi->first);
    r._res = rd;
    r._mpfr_res = pi->second;
    return &r;
}

const cftal::test::mpfr_cache::mpfr_result<float>*
cftal::test::mpfr_cache::result(float a, f1_t f,
                                mpfr_result<float>& r)
{
    mpfr_result<float>* p=nullptr;
    f1_cache_entry* pe=lookup(f);
    if (pe == nullptr)
        return p;
    if (pe->_m32.empty()) {
        pe->_m32.load();
    }
    int32_t ai= as<int32_t>(a);
    auto pi=pe->_m32.find(ai);
    if (pi == nullptr)
        return p;
    float rd= as<float>(pi->first);
    r._res = rd;
    r._mpfr_res = pi->second;
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
    pe->_m64.insert(std::make_pair(ai, std::make_pair(ri, r._mpfr_res)));
}

void
cftal::test::mpfr_cache::update(float a, f1_t f,
                                const mpfr_result<float>& r)
{
    f1_cache_entry* pe=lookup(f);
    if (pe == nullptr)
        return;
    if (pe->_m32.empty()) {
        pe->_m32.load();
    }
    int32_t ai= as<int32_t>(a);
    int32_t ri= as<int32_t>(r._res);
    pe->_m32.insert(std::make_pair(ai, std::make_pair(ri, r._mpfr_res)));
}

void
cftal::test::mpfr_cache::
use(f1_t f, const std::string& fn, double v)
{
    auto p=f1_entries.insert(std::make_pair(f, f1_cache_entry(fn.c_str())));
    f1_cache_entry& e=p.first->second;
    if (e._m64.empty())
        e._m64.load();
    static_cast<void>(v);
}

void
cftal::test::mpfr_cache::
use(f1_t f, const std::string& fn, float v)
{
    auto p=f1_entries.insert(std::make_pair(f, f1_cache_entry(fn.c_str())));
    f1_cache_entry& e=p.first->second;
    if (e._m32.empty())
        e._m32.load();
    static_cast<void>(v);
}
