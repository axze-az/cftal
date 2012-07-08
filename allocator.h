#if !defined (__CFTAL_ALLOCATOR_H__)
#define __CFTAL_ALLOCATOR_H__ 1

#include <cftal/config.h>
#include <memory>
#include <cstdint>
#include <mutex>

namespace cftal {

        class ptr_cache {
                struct block {
                        block* _next;
                };
                std::mutex _mtx;
                block* _free_list;
                std::size_t _free_blocks;
                std::size_t _max_blocks;
        public:
                ptr_cache(const ptr_cache&) = delete;
                ptr_cache& operator(const ptr_cache&) = delete;
                ptr_cache(std::size_t blocks=1024)
                        : _mtx(), _free_list(nullptr), _free_blocks(0),
                          _max_blocks(blocks) {
                }
                void* get() {
                        void* p=nullptr;
                        std::lock_guard<std::mutex> lck(_mtx);
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
                        std::lock_guard<std::mutex> lck(_mtx);
                        if (_free_blocks < _max_blocks) {
                                block* b= static_cast<block*>(p);
                                b->_next = _free_list;
                                ++_free_blocks;
                                r = nullptr;
                        }
                        return r;
                }
                void max_blocks(std::size_t n) {
                        std::lock_guard<std::mutex> lck(_mtx);
                        _max_blocks = n;
                }
                std::size_t max_blocks() {
                        std::lock_guard<std::mutex> lck(_mtx);
                        return _max_blocks;
                }
        };

        template <std::size_t _N>
        class global_ptr_cache {
                static_assert(_N >= sizeof(void*), "_N >= sizeof(void*)");
                ptr_cache _cache;
        public:
                static void* put(void* p) { return _cache.put(p); }
                static void* get(void* p) { return _cache.get(); }
                static void max_blocks(std::size_t n) { _cache.max_blocks(n); }
                static std::size_t max_blocks() { return _cache.max_blocks(); }
        };

        template <std::size_t _N>
        ptr_cache global_ptr_cache<_N>::_cache;

        template <class _T, std::size_t _N>
        class cache_allocator : public std::allocator<_T> {
                static_assert(_N* sizeof(_T) >= sizeof(void*),
                              "_N* sizeof(_T) >= sizeof(void*)");
                typedef std::allocator<_T> base_type;
                static const std::size_t CACHE_SIZE= _N * sizeof(_T);
        public:
                cache_allocator() : base_type() {}
                cache_allocator(const cache_allocator& r) : base_type(r) {};
                ~cache_allocator() {}
                template<typename _Tp1>
                struct rebind { typedef cache_allocator<_Tp1> other; };
                pointer allocate(size_type __n, const void* __p= nullptr) {
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
}

// Local variables:
// mode: c++
// end:
#endif
