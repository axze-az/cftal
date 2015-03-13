#if !defined (__CFTAL_ALLOCATOR_H__)
#define __CFTAL_ALLOCATOR_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <memory>
#include <cstdlib> // for abort

namespace cftal {

    template <std::size_t _N>
    class ptr_cache : private std::allocator<char> {
        static_assert(_N >= sizeof(void*), "_N >= sizeof(void*)");
        typedef std::allocator<char> base_type;
        struct block {
            block* _next;
        };
        block* _free_list;
        std::size_t _free_blocks;
        std::size_t _max_blocks;
        int32_t _clients;
        void deallocate(void* p) {
            base_type::deallocate(static_cast<char*>(p), _N);
        }
    public:
        ptr_cache(const ptr_cache&) = delete;
        ptr_cache& operator=(const ptr_cache&) = delete;
        ptr_cache(std::size_t blocks=1024)
            : _free_list(nullptr), _free_blocks(0),
              _max_blocks(blocks), _clients(0) {
        }
        ~ptr_cache() {
            while (_free_blocks)
                deallocate(get());
        }
        void* get() {
            void* p=nullptr;
            block* b= _free_list;
            if (b != nullptr) {
                _free_list= b->_next;
                p = static_cast<void*>(b);
                --_free_blocks;
            }
            return p;
        }
        void* put(void* p) {
            void* r= p;
            if (_free_blocks < _max_blocks) {
                block* b= static_cast<block*>(p);
                b->_next = _free_list;
                ++_free_blocks;
                r = nullptr;
            }
            return r;
        }
        void max_blocks(std::size_t n) {
            _max_blocks = n;
            while (_free_blocks > _max_blocks) {
                void* p= get();
                deallocate(p);
            }
        }
        std::size_t max_blocks() const {
            return _max_blocks;
        }
        template <typename _U>
        int32_t register_client(const std::allocator<_U>& a) {
            if (a != *this)
                std::abort();
            if (_clients >= 0)
                return ++_clients;
            return _clients;
        }
        template <typename _U>
        int32_t deregister_client(const std::allocator<_U>& a) {
            if (a != *this)
                std::abort();
            return --_clients;
        }
    };

    template <std::size_t _N>
    class global_ptr_cache {
        static_assert(_N >= sizeof(void*), "_N >= sizeof(void*)");
        static thread_local ptr_cache<_N>* _cache;
    public:
        template <typename _U>
        static void register_client(const std::allocator<_U>& a) {
            if (_cache == nullptr)
                _cache = new ptr_cache<_N>();
            _cache->register_client(a);
        }
        template <typename _U>
        static void deregister_client(const std::allocator<_U>& a) {
            if (_cache != nullptr) {
                if (_cache->deregister_client(a)<0) {
                    delete _cache;
                    _cache = nullptr;
                }
            }
        }
        static void* put(void* p) {
            if (_cache)
                return _cache->put(p);
            return p;
        }
        static void* get() {
            if (_cache)
                return _cache->get();
            return nullptr;
        }
        static void max_blocks(std::size_t n) {
            if (_cache)
                _cache->max_blocks(n);
        }
        static std::size_t max_blocks() {
            if (_cache)
                return _cache->max_blocks();
            return 0;
        }
    };

    template <std::size_t _N>
    thread_local ptr_cache<_N>* global_ptr_cache<_N>::_cache=nullptr;

    extern template class global_ptr_cache<16>;
    extern template class global_ptr_cache<32>;
    extern template class global_ptr_cache<64>;

    template <class _T, std::size_t _N>
    class cache_allocator : public std::allocator<_T> {
        static_assert(_N* sizeof(_T) >= sizeof(void*),
                      "_N* sizeof(_T) >= sizeof(void*)");
        typedef std::allocator<_T> base_type;
        static const std::size_t CACHE_SIZE= _N * sizeof(_T);
    public:
        typedef typename std::allocator<_T>::size_type size_type;
        typedef typename std::allocator<_T>::pointer pointer;
        cache_allocator() : base_type() {
            global_ptr_cache<CACHE_SIZE>::register_client(*this);
        }
        cache_allocator(const cache_allocator& r) : base_type(r) {
            global_ptr_cache<CACHE_SIZE>::register_client(*this);
        };
        cache_allocator(cache_allocator&& r) : base_type(std::move(r)) {
            global_ptr_cache<CACHE_SIZE>::register_client(*this);
        };
        ~cache_allocator() {
            global_ptr_cache<CACHE_SIZE>::deregister_client(*this);
        }
        template<typename _Tp1>
        struct rebind { typedef cache_allocator<_Tp1, _N> other; };

        pointer
        allocate(size_type __n, const void* __p= nullptr) {
            if (__n==_N) {
                void* r= global_ptr_cache<CACHE_SIZE>::get();
                if (r != nullptr)
                    return static_cast<pointer>(r);
            }
            return base_type::allocate(__n, __p);
        }
        void deallocate(pointer __p, size_type __n) {
            if (__n==_N &&
                global_ptr_cache<CACHE_SIZE>::put(__p)==nullptr)
                return;
            base_type::deallocate(__p, __n);
        }
    };

    extern template class cache_allocator<char, 16>;
    extern template class cache_allocator<char, 32>;
    extern template class cache_allocator<char, 64>;

}

// Local variables:
// mode: c++
// end:
#endif
