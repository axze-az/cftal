#if !defined (__CFTAL_HEAP_ARRAY_H__)
#define __CFTAL_HEAP_ARRAY_H__ 1

#include <cftal/config.h>
#include <cftal/normal_iterator.h>

namespace cftal {

	namespace impl {
		void heap_array_throw_range_error(std::size_t _N, 
						  bool from_const)
		__attribute__((__noreturn__));
	}

        template <class _T, std::size_t _N,
                  class _A = std::allocator<_T> >
        class heap_array : private _A {
		static_assert(_N>0, "N>0");
                _T* _v;
		_T* alloc_(_A& a) {
			return a.allocate(_N);
		}
                _T* alloc_(_A& a, const _T& init) {
                        _T* p = alloc_(a);
                        std::size_t i;
                        try {
                                for (i=0; i<_N; ++i)
                                        a.construct(p+i, init);
                        }
                        catch (...) {
                                for (std::size_t j=0; j<i; ++j)
                                        a.destroy(p+j);
                                throw;
                        }
                }
                _T* alloc_and_copy_(_A& a, const _T* rp) {
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
                void destroy_(_A& a) {
                        for (std::size_t j=0; j<_N; ++j)
                                a.destroy(_v+j);
			a.deallocate(_v, _N);
                }
        public:
                // our own type
                typedef heap_array<_T, _N, _A> my_type;
                // value type
                typedef _T value_type;
                // type of allocator
                typedef _A allocator_type;
                // pointer
                typedef typename allocator_type::pointer pointer;
                // const_pointer
                typedef typename allocator_type::const_pointer const_pointer;
                // reference
                typedef typename allocator_type::reference reference;
                // const_reference
                typedef typename allocator_type::const_reference
                const_reference;
                // iterator
                typedef normal_iterator<pointer, my_type> iterator;
                // const_iterator
                typedef normal_iterator<const_pointer, my_type>
                const_iterator;
                // const_reverse_iterator
                typedef std::reverse_iterator<const_iterator>
                const_reverse_iterator;
                // reverse iterator
                typedef std::reverse_iterator<iterator>
                reverse_iterator;
                // size_type
                typedef std::size_t size_type;
                // difference_type
                typedef std::ptrdiff_t difference_type;
		
		// vector interface
		const_iterator begin() const { return const_iterator(_v); }
		const_iterator cbegin() const { return const_iterator(_v); }
		iterator begin() { return iterator(_v); }
		const_iterator end() const { return begin() + _N; }
		const_iterator cend() const { return cbegin() + _N; }
		iterator end() { return begin() + _N; }
		constexpr bool empty() const { return false; }
		constexpr size_type max_size() const {  return _N; }
		constexpr size_type size() const { return _N; }
		const_reference operator[](size_type n) const { 
			return *(cbegin()+_N); 
		}
		reference operator[](size_type n) {
			return *(begin()+_N);
		}
		const_reference at(size_type n) const {
			if (n>=_N)
				impl::heap_array_throw_range_error(_N, true);
			return (*this)[n];
		}
		reference at(size_type n) {
			if (n>=_N)
				impl::heap_array_throw_range_error(_N, false);
			return (*this)[n];
		}

		// default constructor
                heap_array() : _v(alloc_(*this, _T())) {
                }
		// assignment from _T
                heap_array(const _T& t) : _v(alloc_(*this, t)) {
                }
		// copy construction
                heap_array(const heap_array& r) : _v(alloc_and_copy_(*this,
                                                                     r._v)) {
                }
		// move construction
                heap_array(heap_array&& r) : _v(alloc_(*this, _T())) {
                        std::swap(_v, r._v);
                }
		// destruction
		~heap_array() { 
			destroy_(*this); 
		}
		// assignment
                heap_array& operator=(const heap_array& r) {
                        if (this != &r)
                                std::copy(r.begin(), r.end(), begin());
                        return *this;
                }
		// move assignment
                heap_array& operator=(heap_array&& r) {
                        std::swap(_v, r._v);
                        return *this;
                }
		// assignment of all elements.
                heap_array& operator=(const _T& r) {
                        _T t=r;
                        std::fill(begin(), end(), t);
                        return *this;
                }
		// swap
		heap_array& swap(heap_array& r) {
			std::swap(_v, r._v);
		}
        };

	template <typename _T, std::size_t _N, typename _A>
	void swap(heap_array<_T, _N, _A>& a, heap_array<_T, _N, _A>& b) {
		a.swap(b);
	}
}

namespace std {

	template <typename _T, std::size_t _N, typename _A>
	void swap(cftal::heap_array<_T, _N, _A>& a, 
		  cftal::heap_array<_T, _N, _A>& b) {
		return cftal::swap(a, b);
	}

}

// Local variables:
// mode: c++
// end:

#endif
