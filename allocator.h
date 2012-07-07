#if !defined (__CFTAL_ALLOCATOR_H__)
#define __CFTAL_ALLOCATOR_H__ 1

#include <memory>
#include <cstdint>
#include <mutex>

namespace cftal {

	template <std::size_t _N>
	class ptr_cache {
		static_assert(_N >= sizeof(void*), 
			      "_N must be greater than sizeof(void*)");
		struct block {
			block* _next;
		};
		static block* _free_list;
		static std::size_t _free_blocks;
		static std::size_t _max_blocks;
		static std::mutex _head_mtx;
	public:
		static void* get();
		static void* put(void* p);
		static void max_blocks(std::size_t n);
		static std::size_t max_blocks();
	};

	template <class _T, std::size_t _N>
	class cache_allocator : public std::allocator<_T> {
		static_assert((N==0) || ((_N % sizeof(_T)) ==0), 
			      "_N should be an multiple of _T");
		typedef std::allocator<_T> base_type;
	public:
		cache_allocator() : base_type() {}
		cache_allocator(const cache_allocator& r) : base_type(r) {};
		~cache_allocator() {}
		template<typename _Tp1>
		struct rebind { typedef cache_allocator<_Tp1> other; };
		pointer allocate(size_type __n, const void* __p= nullptr) { 
			size_type s= __n * sizeof(_T); 
			if (s==_N1) {
				void* r= ptr_cache<_N>::get();
				if (r != nullptr)
					return static_cast<pointer>(r);
			}
			return base_type::allocate(__n, __p);
		}
		void deallocate(pointer __p, size_type __n) { 
			size_type s= __n* sizeof(_T);
			if (s==_N1 && ptr_cache<_N>::put(__p)==nullptr)
				return;
			base_type::deallocate(__p, __n);
		}
	};

	template <class _T, std::size_t _N,
		  class _A = std::allocator<_T> >
	class heap_array : private _A {
		_T* _v;
		_T* alloc(_A& a) {
			_T* p = a.allocate(_N);
			std::size_t i;
			try {
				for (i=0; i<_N; ++i)
					a.construct(p+i, _T());
			}
			catch (...) {
				for (std::size_t j=0; j<i; ++j)
					a.destroy(p+j);
				throw;
			}
		}
		_T* alloc_and_copy(A& a, const _T* rp) {
			_T* p = a.allocate(_N);
			std::size_t i;
			try {
				for (i=0; i<_N; ++i)
					a.construct(p+i, rp[i]);
			}
			catch (...) {
				for (std::size_t j=0; j<i; ++j)
					a.destroy(p+j);
				throw;
			}
		}
		void destroy(A& a, _T* p) {
			for (std::size_t j=0; j<_N; ++j)
				a.destroy(p+j);
		}
	public:
	};

}


#endif
