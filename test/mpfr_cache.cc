//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <cftal/test/mpfr_cache.h>
#include <cftal/test/stream_save_fmt.h>
#include <cftal/test/env_var.h>
#include <cftal/cast.h>
#include <cftal/test/spinlock.h>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <memory>
#include <lzma.h>
#include <mutex>
#include <shared_mutex>

namespace cftal { namespace test { namespace lzma {

    class handle {
        enum mode {
            compress,
            decompress
        };
        lzma_stream _strm;
        handle(const handle& h)=delete;
        handle& operator=(const handle& h)=delete;
        handle (mode m);
        ~handle();
        handle(handle&& op);
        handle& operator=(handle&& h);
        lzma_stream* operator()() { return &_strm; }
    public:
        template <typename _T>
        static
        void
        load(std::ifstream& s, std::vector<_T>& v);

        template <typename _T>
        static
        void
        store(std::ofstream& s,
              const std::vector<_T>& v);

    };
}}}

cftal::test::lzma::handle::handle(mode m)
    : _strm(LZMA_STREAM_INIT)
{
    lzma_ret r= LZMA_OK;
    if (m==mode::decompress) {
        const std::size_t max_size=256*1024*1024;
        r=lzma_stream_decoder(&_strm, max_size, LZMA_CONCATENATED);
        if (r != LZMA_OK) {
            throw std::runtime_error("decompress oops");
        }
    } else if (m==mode::compress) {
#if 0
        r=lzma_easy_encoder(&_strm, LZMA_PRESET_DEFAULT, LZMA_CHECK_CRC64);
#else
        lzma_mt mt= {0};
        mt.preset = 3;
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
    : _strm(LZMA_STREAM_INIT)
{
    std::swap(_strm, r._strm);
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
    handle h(mode::decompress);

    std::vector<uint8_t> ibuf(sizeof(uint8_t)*1024*1024*8, '\0');
    lzma_action action=LZMA_RUN;

    h()->next_out=nullptr;
    h()->avail_out=0;
    h()->avail_in=0;
    h()->next_in=nullptr;

    lzma_ret r=LZMA_OK;

    auto fmt=stream_save_fmt(std::cout);
    std::cout << std::fixed << std::setprecision(2);

    enum state {
        header, payload
    };
    state st=header;
    uint64_t entries;

    std::streamsize opos=f.tellg();
    f.seekg(0, std::ios::end);
    std::streamsize bytes_total=f.tellg();
    f.seekg(opos, std::ios::beg);
    double t=100.0/double(bytes_total);

    do {
        if (h()->avail_in ==0 && !f.eof()) {
            switch (st) {
            case state::header:
                h()->next_out=reinterpret_cast<uint8_t*>(&entries);
                h()->avail_out=sizeof(entries);
                break;
            case state::payload:
                break;
            }
            f.read(reinterpret_cast<char*>(ibuf.data()), ibuf.size());
            std::streamsize br=f.gcount();
            h()->avail_in=br;
            h()->next_in=ibuf.data();
        }
        if (f.eof()) {
            action=LZMA_FINISH;
        }
        r=lzma_code(h(), action);
        uint64_t i, o;
        lzma_get_progress(h(), &i, &o);
        double p=double(i)*t;
        std::cout << std::setw(5) << p << "%\r" << std::flush;
        size_t oa= h()->avail_out;
        if (oa == 0 || r == LZMA_STREAM_END) {
            switch (st) {
            case state::header:
                std::cout << "reading " << entries << " entries" << std::endl;
                v.resize(entries);
                st = state::payload;
                h()->next_out=reinterpret_cast<uint8_t*>(v.data());
                h()->avail_out=entries*sizeof(_T);
                break;
            case state::payload:
                break;
            }
        }
    } while (r == LZMA_OK);
    if (r != LZMA_OK && r != LZMA_STREAM_END) {
        std::cout <<'\n' << r << std::endl;
    }
    std::cout << "read " << v.size() << " entries" << std::endl;
}

template <typename _T>
void
cftal::test::lzma::handle::
store(std::ofstream& f, const std::vector<_T>& v)
{
    handle h(mode::compress);
    const uint8_t* d=reinterpret_cast<const uint8_t*>(v.data());
    uint64_t entries=v.size();
    const std::size_t total_bytes=v.size()*sizeof(_T);
    std::vector<uint8_t> obuf(2*1024*1024*sizeof(uint8_t), '\0');

    lzma_action action = LZMA_RUN;
    h()->next_in=reinterpret_cast<const uint8_t*>(&entries);
    h()->avail_in=sizeof(entries);
    h()->next_out=obuf.data();
    h()->avail_out=obuf.size();

    lzma_ret r= LZMA_OK;
    double t=total_bytes + sizeof(entries);
    t = 100.0/double(t);
    auto fmt=stream_save_fmt(std::cout);
    std::cout << std::fixed << std::setprecision(2);

    do {
        if (h()->avail_in == 0 && action == LZMA_RUN) {
            action = LZMA_FINISH;
            h()->next_in=d;
            h()->avail_in=total_bytes;
        }
        r = lzma_code(h(), action);
        uint64_t i, o;
        lzma_get_progress(h(), &i, &o);
        double p=double(i)*t;
        std::cout << std::setw(5) << p << "%\r" << std::flush;
        size_t oa=h()->avail_out;
        if (oa == 0 || r == LZMA_STREAM_END) {
            size_t ws = obuf.size() - oa;
            f.write(reinterpret_cast<const char*>(obuf.data()), ws);
            h()->next_out = obuf.data();
            h()->avail_out = obuf.size();
        }
    } while (r == LZMA_OK);
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
        // base of the file used as storage, if
        // _compress is true, .xz is appended
        std::string _file_name;
        bool _save;
        bool _compress;
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

    class pmutex {
        using lock_type= std::shared_mutex;
        std::shared_ptr<lock_type> _p_mtx;
    public:
        pmutex() : _p_mtx(std::make_shared<lock_type>()) {}
        void lock() { _p_mtx->lock(); }
        void unlock() { _p_mtx->unlock(); }
        void lock_shared() { _p_mtx->lock_shared(); }
        void unlock_shared() { _p_mtx->unlock_shared(); }
    };

    struct f1_64_cache_entry : private pmutex {
        std::string _name;
        f1_f64_map _m64;
        explicit
        f1_64_cache_entry(const std::string& name)
            : _name(name),
              _m64(file_name(name, "f64")) {
        }
        f1_64_cache_entry(f1_64_cache_entry&& r)
            : pmutex(std::move(pmutex(r))),
             _name(std::move(r._name)),
             _m64(std::move(r._m64)) {
        }
        using pmutex::lock;
        using pmutex::unlock;
        using pmutex::lock_shared;
        using pmutex::unlock_shared;
    };

    struct f1_32_cache_entry : private pmutex {
        std::string _name;
        f1_f32_map _m32;
        explicit
        f1_32_cache_entry(const std::string& name)
            : _name(name),
              _m32(file_name(name, "f32")) {
        }
        f1_32_cache_entry(f1_32_cache_entry&& r)
            : pmutex(std::move(pmutex(r))),
             _name(std::move(r._name)),
             _m32(std::move(r._m32)) {
        }
        using pmutex::lock;
        using pmutex::unlock;
        using pmutex::lock_shared;
        using pmutex::unlock_shared;
    };

    using f1_64_cache_map=std::map<f1_t, f1_64_cache_entry>;
    extern f1_64_cache_map f1_64_entries;
    extern std::mutex f1_64_mtx;

    using f1_32_cache_map=std::map<f1_t, f1_32_cache_entry>;
    extern f1_32_cache_map f1_32_entries;
    extern std::mutex f1_32_mtx;

}}}

template <typename _K, typename _R>
cftal::test::mpfr_cache::result_cache<_K, _R>::
result_cache(const std::string& fn)
    : _file_name(fn), _save(false), _compress(false)
{
    load();
}

template <typename _K, typename _R>
cftal::test::mpfr_cache::result_cache<_K, _R>::
result_cache(result_cache&& r)
    : _v(std::move(r._v)),
      _m(std::move(r._m)),
      _file_name(std::move(r._file_name)),
      _save(std::move(r._save)),
      _compress(std::move(r._compress))
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
                  return a.first < b.first;
              });
    _save = true;
}

template <typename _K, typename _R>
void
cftal::test::mpfr_cache::result_cache<_K, _R>::load()
{
    // look for an uncompressed file first
    std::ifstream f(_file_name.c_str(), std::ios::binary | std::ios::in);
    if (!f.good()) {
        std::string fn(_file_name + ".xz");
        f.open(fn.c_str(), std::ios::binary | std::ios::in);
        if (f.good()) {
            _compress = true;
            std::cout << "reading from " << fn << std::endl;
            lzma::handle::load(f, _v);
            dump();
        }
    } else {
        _compress = false;
        uint64_t us;
        using c_t = std::ifstream::char_type;
        f.read(reinterpret_cast<c_t*>(&us), sizeof(us));
        std::cout << _file_name << ' ';
        if (f.good()) {
            _v.resize(us);
            std::cout << "reading " << us
                      << " entries" << std::endl;
            std::streamsize bytes=us*sizeof(value_type);
            f.read(reinterpret_cast<c_t*>(_v.data()), bytes);
            if (f.gcount() != bytes) {
                std::cout << "read failed\n";
                _v.clear();
            }
        }
        std::cout << "read " << _v.size() << " entries" << std::endl;
    }
}

template <typename _K, typename _R>
void
cftal::test::mpfr_cache::result_cache<_K, _R>::store()
{
    move_map_to_vec();
    if (_save == false)
        return;
    std::string fn=_file_name;
    if (_compress==true)
        fn += ".xz";
    std::ofstream f(fn.c_str(),
                    std::ios::binary | std::ios::trunc | std::ios::out);
    if (!f.good())
        return;
    if (_compress==true) {
        dump();
        std::cout << "writing " << _v.size()  << " entries to "
                  << fn << std::endl;
        lzma::handle::store(f, _v);
    } else {
        std::size_t s=_v.size();
        uint64_t us=s;
        using c_t = std::ifstream::char_type;
        f.write(reinterpret_cast<const c_t*>(&us), sizeof(us));
        if (f.good()) {
            f.write(reinterpret_cast<const c_t*>(_v.data()),
                    s*sizeof(value_type));
        }
        std::cout << "wrote " << _v.size()  << " entries to "
                  << fn << std::endl;
    }
}

template <typename _K, typename _R>
void
cftal::test::mpfr_cache::result_cache<_K, _R>::dump()
{
#if 0
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
std::mutex
cftal::test::mpfr_cache::f1_32_mtx;

cftal::test::mpfr_cache::f1_64_cache_map
cftal::test::mpfr_cache::f1_64_entries;
std::mutex
cftal::test::mpfr_cache::f1_64_mtx;


std::string
cftal::test::mpfr_cache::
file_name(const std::string& a, const std::string& t)
{
    return a+ "-" + t + ".bin";
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
    std::shared_lock<f1_64_cache_entry> _lck(*pe);
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
    std::shared_lock<f1_32_cache_entry> _lck(*pe);
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
    std::lock_guard<f1_64_cache_entry> _lck(*pe);
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
    std::lock_guard<f1_32_cache_entry> _lck(*pe);
    int32_t ai= as<int32_t>(a);
    int32_t ri= as<int32_t>(r._res);
    pe->_m32.insert(std::make_pair(ai, std::make_pair(ri, r._mpfr_res)));
}

void
cftal::test::mpfr_cache::
use(f1_t f, const std::string& fn, double v)
{
    // if (env_use_cache()==false)
    //    return;

    auto e=std::make_pair(f, f1_64_cache_entry(fn.c_str()));
    f1_64_entries.emplace(std::move(e));
    static_cast<void>(v);
}

void
cftal::test::mpfr_cache::
use(f1_t f, const std::string& fn, float v)
{
    // if (env_use_cache()==false)
    //    return;

    auto e=std::make_pair(f, f1_32_cache_entry(fn.c_str()));
    f1_32_entries.emplace(std::move(e));
    static_cast<void>(v);
}
