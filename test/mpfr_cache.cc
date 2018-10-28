//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <cftal/test/mpfr_cache.h>
#include <cftal/cast.h>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <lzma.h>

#define USE_LZMA 0

namespace cftal { namespace test { namespace lzma {

    enum mode {
        compress,
        decompress
    };

    class handle {
        lzma_stream _strm;
        mode _m;
        handle(const handle& h)=delete;
        handle& operator=(const handle& h)=delete;
    public:
        handle(mode m);
        ~handle();
        handle(handle&& op);
        handle& operator=(handle&& h);

        template <typename _T>
        void
        load(std::ifstream& s, std::vector<_T>& v);

        template <typename _T>
        void
        store(std::ofstream& s,
              const std::vector<_T>& v);

    };
}}}

cftal::test::lzma::handle::handle(mode m)
    : _strm(LZMA_STREAM_INIT), _m(m)
{
    lzma_ret r= LZMA_OK;
    if (m==mode::decompress) {
        const std::size_t max_size=64*1024*1024;
        r=lzma_stream_decoder(&_strm, max_size, LZMA_CONCATENATED);
        if (r != LZMA_OK) {
            throw std::runtime_error("decompress oops");
        }
    } else if (m==mode::compress) {
#if 0
        r=lzma_easy_encoder(&_strm, LZMA_PRESET_DEFAULT, LZMA_CHECK_CRC64);
#else
        lzma_mt mt= {0};
        mt.preset = LZMA_PRESET_DEFAULT;
        mt.check = LZMA_CHECK_CRC64;
        mt.threads = std::min(std::max(1u, lzma_cputhreads()), 8u);
        r=lzma_stream_encoder_mt(&_strm, &mt);
#endif
        if (r != LZMA_OK) {
            throw std::runtime_error("compress oops");
        }
    } else {
        throw std::runtime_error("oops");
    }
}

cftal::test::lzma::handle::~handle()
{
    lzma_end(&_strm);
}

cftal::test::lzma::handle::handle(handle&& r)
    : _strm(r._strm)
{
}

cftal::test::lzma::handle&
cftal::test::lzma::handle::operator=(handle&& r)
{
    std::swap(_strm, r._strm);
    return *this;
}

template <typename _T>
void
cftal::test::lzma::handle::
load(std::ifstream& f, std::vector<_T>& v)
{
    if (_m != mode::decompress)
        throw std::runtime_error("load , oops");
    
    v.clear();
    // 1 Mbyte input, 32 MByte output
    std::vector<uint8_t> ibuf(sizeof(_T)*1024*1024, '\0');
    std::vector<uint8_t> obuf(sizeof(_T)*1024*1024, '\0');
    lzma_action action=LZMA_RUN;

    _strm.next_out=obuf.data();
    _strm.avail_out=obuf.size();
    _strm.avail_in=0;
    _strm.next_in=ibuf.data();

    while (true) {
        if (_strm.avail_in ==0 && !f.eof()) {
            f.read(reinterpret_cast<char*>(ibuf.data()), ibuf.size());
            std::size_t b=f.gcount();
            _strm.avail_in=b;
        }
        if (f.eof()) {
            action=LZMA_FINISH;
        }
        lzma_ret r=lzma_code(&_strm, action);
        if (_strm.avail_out == 0 || r == LZMA_STREAM_END) {
            std::size_t cnt=_strm.avail_out;
            std::size_t bytes= obuf.size() - cnt;
            std::size_t entries= bytes / sizeof(_T);
            std::size_t o= entries*sizeof(_T);
            if (o != bytes) {
                throw std::runtime_error("compress error");
            }
            v.reserve(v.size() + entries);
            // insert full entries
            const _T* ps=reinterpret_cast<const _T*>(obuf.data());
            for (std::size_t i=0; i<entries; ++i)
                v.push_back(ps[i]);
            // v.insert(v.cend(), ps, ps + entries);
            // tail handling
            for (std::size_t i=0, j=o; j<bytes; ++j) {
                obuf[i] = obuf[j];
            }
        }
        if (r != LZMA_OK)
            break;
    }
    v.shrink_to_fit();
    std::cout << "read " << v.size() << " entries" << std::endl;
}

template <typename _T>
void
cftal::test::lzma::handle::
store(std::ofstream& f, const std::vector<_T>& v)
{
    if (_m != mode::compress)
        throw std::runtime_error("store , oops");

    const uint8_t* d=reinterpret_cast<const uint8_t*>(v.data());
    const std::size_t total_bytes=v.size()*sizeof(_T);
    std::vector<uint8_t> obuf(4*sizeof(_T), '\0');

    lzma_action action = LZMA_RUN;

    const std::size_t input_chunk=1*sizeof(_T);
    std::size_t bytes = std::min(input_chunk, total_bytes);
    _strm.next_in=d;
    _strm.avail_in=bytes;
    _strm.next_out=obuf.data();
    _strm.avail_out=obuf.size();

    while (true) {
        if (_strm.avail_in == 0 && bytes < total_bytes) {
            std::size_t c=std::min(input_chunk, total_bytes - bytes);
            bytes += c;
            _strm.avail_in= c;
            _strm.next_in = d + bytes;
        }
        if (bytes == total_bytes) {
            action=LZMA_FINISH;
        }
        lzma_ret ret = lzma_code(&_strm, action);
        if (_strm.avail_out == 0 || ret == LZMA_STREAM_END) {
            size_t write_size = obuf.size() - _strm.avail_out;
            f.write(reinterpret_cast<const char*>(obuf.data()),
                    write_size);
            _strm.next_out = obuf.data();
            _strm.avail_out = obuf.size();
        }
        if (ret != LZMA_OK) {
            if (ret == LZMA_STREAM_END)
                break;
            std::cout << "error: " << ret << std::endl;
            std::exit(3);
        }
    }
    std::cout << "wrote " << v.size() << " entries" << std::endl;
}

namespace cftal { namespace test { namespace mpfr_cache {

    // these object may be really large
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
        bool _save;
        // move _m into _v and sort _v
        void
        move_map_to_vec();
        // load from _file_name
        void
        load();
        // save to to _file_name
        void
        store();

        void dump();

        const std::size_t move_treshold= 1<<25;
    public:
        result_cache()= delete;
        result_cache(const result_cache&) = delete;
        result_cache& operator=(const result_cache&)= delete;
        result_cache& operator=(result_cache&&)= delete;
        // file as argument
        explicit
        result_cache(const std::string& fn);
        // move constructor
        result_cache(result_cache&& r);
        // stores if not empty
        ~result_cache();

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

    static
    std::string file_name(const std::string& a, const std::string& t);

    struct f1_64_cache_entry {
        std::string _name;
        f1_f64_map _m64;
        explicit
        f1_64_cache_entry(const std::string& name)
            : _name(name),
              _m64(file_name(name, "f64")) {
        }
    };

    struct f1_32_cache_entry {
        std::string _name;
        f1_f32_map _m32;
        explicit
        f1_32_cache_entry(const std::string& name)
            : _name(name),
              _m32(file_name(name, "f32")) {
        }
    };

    using f1_64_cache_map=std::map<f1_t, f1_64_cache_entry>;
    extern f1_64_cache_map f1_64_entries;

    using f1_32_cache_map=std::map<f1_t, f1_32_cache_entry>;
    extern f1_32_cache_map f1_32_entries;


}}}

template <typename _K, typename _R>
cftal::test::mpfr_cache::result_cache<_K, _R>::
result_cache(const std::string& fn)
    : _file_name(fn), _save(false)
{
    load();
}

template <typename _K, typename _R>
cftal::test::mpfr_cache::result_cache<_K, _R>::
result_cache(result_cache&& r)
    : _v(std::move(r._v)),
      _m(std::move(r._m)),
      _file_name(std::move(r._file_name)),
      _save(std::move(r._save))
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
cftal::test::mpfr_cache::result_cache<_K, _R>::
move_map_to_vec()
{
    if (_m.empty())
        return;
    std::size_t vs=_v.size(), ms= _m.size(), s=vs+ms;
    _v.reserve(s);
    std::move(std::begin(_m), std::end(_m), std::back_inserter(_v));
    // does not help anything because the memory is not given back
    // to the system :-(
    _m.clear();
    std::sort(std::begin(_v), std::end(_v),
              [](const value_type& a, const value_type& b)->bool {
                  return a < b;
              });
    _save = true;
}

template <typename _K, typename _R>
void
cftal::test::mpfr_cache::result_cache<_K, _R>::load()
{
    std::ifstream f(_file_name.c_str(), std::ios::binary | std::ios::in);
    if (!f.good())
        return;
#if USE_LZMA>0
    std::cout << "reading from " << _file_name << std::endl;
    lzma::handle h(lzma::decompress);
    h.load(f, _v);
    dump();
#else
    f.seekg(0, std::ios::end);
    std::ifstream::off_type s=f.tellg();
    f.seekg(0);
    _v.clear();
    _v.resize(s/sizeof(value_type));
    using c_t = std::ifstream::char_type;
    std::cout << "reading from " << _file_name << std::endl;
    f.read(reinterpret_cast<c_t*>(_v.data()), s);
    std::cout << "read " << _v.size() << " entries" << std::endl;
#endif
}

template <typename _K, typename _R>
void
cftal::test::mpfr_cache::result_cache<_K, _R>::store()
{
    move_map_to_vec();
#if USE_LZMA==0
    if (_save == false)
        return;
#endif
    std::ofstream f(_file_name.c_str(),
                    std::ios::binary | std::ios::trunc | std::ios::out);
    if (!f.good())
        return;
#if USE_LZMA>0
    dump();
    std::cout << "writing " << _v.size()  << " entries to "
              << _file_name << std::endl;
    lzma::handle h(lzma::compress);
    h.store(f, _v);
#else
    std::size_t vs=_v.size(), ms= _m.size(), s=vs+ms;
    using c_t = std::ifstream::char_type;
    f.write(reinterpret_cast<const c_t*>(_v.data()), s*sizeof(value_type));
    std::cout << "wrote " << _v.size()  << " entries to "
              << _file_name << std::endl;
#endif
}

template <typename _K, typename _R>
void
cftal::test::mpfr_cache::result_cache<_K, _R>::dump()
{
#if USE_LZMA>1
    for (std::size_t i=0; i<_v.size(); ++i) {
        std::cout << _v[i].first << ' '
                  << _v[i].second.first << ' '
                  << _v[i].second.second << std::endl;
    }
#endif
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
            return pr;
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
    if (_m.size() >= move_treshold)
        move_map_to_vec();
}

template <typename _K, typename _R>
bool
cftal::test::mpfr_cache::result_cache<_K, _R>::
empty()
    const
{
    return _v.empty() && _m.empty();
}

cftal::test::mpfr_cache::f1_32_cache_map
cftal::test::mpfr_cache::f1_32_entries;

cftal::test::mpfr_cache::f1_64_cache_map
cftal::test::mpfr_cache::f1_64_entries;


std::string
cftal::test::mpfr_cache::
file_name(const std::string& a, const std::string& t)
{
#if USE_LZMA>0
    return a+ "-" + t + ".bin.xz";
#else
    return a+ "-" + t + ".bin";
#endif
}

const cftal::test::mpfr_cache::mpfr_result<double>*
cftal::test::mpfr_cache::result(double a, f1_t f,
                                mpfr_result<double>& r)
{
    mpfr_result<double>* p=nullptr;
    auto i= f1_64_entries.find(f);
    if (i== std::cend(f1_64_entries))
        return p;
    f1_64_cache_entry* pe=&i->second;
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
    auto i= f1_32_entries.find(f);
    if (i== std::cend(f1_32_entries))
        return p;
    f1_32_cache_entry* pe=&i->second;
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
    auto i= f1_64_entries.find(f);
    if (i== std::cend(f1_64_entries))
        return;
    f1_64_cache_entry* pe=&i->second;
    int64_t ai= as<int64_t>(a);
    int64_t ri= as<int64_t>(r._res);
    pe->_m64.insert(std::make_pair(ai, std::make_pair(ri, r._mpfr_res)));
}

void
cftal::test::mpfr_cache::update(float a, f1_t f,
                                const mpfr_result<float>& r)
{
    auto i= f1_32_entries.find(f);
    if (i== std::cend(f1_32_entries))
        return;
    f1_32_cache_entry* pe=&i->second;
    int32_t ai= as<int32_t>(a);
    int32_t ri= as<int32_t>(r._res);
    pe->_m32.insert(std::make_pair(ai, std::make_pair(ri, r._mpfr_res)));
}

void
cftal::test::mpfr_cache::
use(f1_t f, const std::string& fn, double v)
{
    f1_64_entries.insert(std::make_pair(f, f1_64_cache_entry(fn.c_str())));
    static_cast<void>(v);
}

void
cftal::test::mpfr_cache::
use(f1_t f, const std::string& fn, float v)
{
    f1_32_entries.insert(std::make_pair(f, f1_32_cache_entry(fn.c_str())));
    static_cast<void>(v);
}
