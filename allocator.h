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

	template <class _T, std::size_t _N1, std::size_t _N2=_N1>
	class allocator : public std::allocator<_T> {
		static_assert((_N1 % sizeof(_T)) ==0, "_N1 invalid");
		static_assert((_N2 % sizeof(_T)) ==0, "_N2 invalid");
		typedef std::allocator<_T> base_type;
	public:
		allocator() : base_type() {}
		allocator(const allocator& r) : base_type(r) {};
		~allocator() {}

		template<typename _Tp1>
		struct rebind { typedef allocator<_Tp1> other; };

		pointer allocate(size_type __n, const void* __p= nullptr) { 
			size_type s= __n * sizeof(_T); 
			if (s==_N1) {
				void* r= ptr_cache<_N1>::get();
				if (r != nullptr)
					return static_cast<pointer>(r);
			}
			if (_N1 != _N2) {
				if (s==_N2) {
					void* r= ptr_cache<_N1>::get();
					if (r != nullptr)
						return static_cast<pointer>(r);
				}
			}
			return base_type::allocate(__n, __p);
		}

		void deallocate(pointer __p, size_type __n) { 
			size_type s= __n* sizeof(_T);
			if (s==_N1 && ptr_cache<_N1>::put(__p)==nullptr)
				return;
			if (_N1 != _N2) {
				if (s==_N2 && ptr_cache<_N1>::put(__p)==nullptr)
					return;
			}
			base_type::deallocate(__p, __n);
		}
	};
}


#endif
