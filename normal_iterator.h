#if !defined (__CFTAL_NORMAL_ITERATOR_H__)
#define __CFTAL_NORMAL_ITERATOR_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <iterator>

namespace cftal {

	// This iterator adapter is 'normal' in the sense that it does
	// not change the semantics of any of the operators of its
	// iterator parameter.  Its primary purpose is to convert an
	// iterator that is not a class, e.g. a pointer, into an
	// iterator that is a class.  The _ContTag parameter exists
	// solely so that different containers using this template can
	// instantiate different types, even if the _Iter
	// parameter is the same.
	template <typename _Iter, typename _ContTag>
	class normal_iterator {
	protected:
		_Iter _M_iter;
	public:
		// iterator category
		typedef typename std::iterator_traits<_Iter>::iterator_category
		iterator_category;
		// value type
		typedef typename std::iterator_traits<_Iter>::value_type 
		value_type;
		// difference type
		typedef typename std::iterator_traits<_Iter>::difference_type
		difference_type;
		// reference
		typedef typename std::iterator_traits<_Iter>::reference 
		reference;
		// pointer
		typedef typename std::iterator_traits<_Iter>::pointer   
		pointer;
		// default constructor
		normal_iterator() : _M_iter(_Iter()) { 
		}
		// constructor from const _Iter
		explicit
		normal_iterator(const _Iter& __i) : _M_iter(__i) { 
		}
		// Allow iterator to const_iterator conversion
		template<typename _Iter2>
		inline 
		normal_iterator(const normal_iterator<_Iter2,_ContTag>& __i)
			: _M_iter(__i.iter()) { 
		}
		// Forward iterator requirements - dereference
		reference operator*() const { 
			return *_M_iter; 
		}
		// member access.
		pointer	operator->() const { 
			return _M_iter; 
		}
		// prefix increment
		normal_iterator& operator++() {
			++_M_iter;
			return *this;
		}
		// postfix increment
		normal_iterator	operator++(int) { 
			return normal_iterator(_M_iter++); 
		}
		// Bidirectional iterator requirements, prefix decrement
		normal_iterator& operator--() {
			--_M_iter;
			return *this;
		}
		// postfix decrement
		normal_iterator operator--(int)	{ 
			return normal_iterator(_M_iter--); 
		}
		// Random access iterator requirements - array operator
		reference operator[](const difference_type& __n) const { 
			return _M_iter[__n]; 
		}
		// addition of a difference type
		normal_iterator& operator+=(const difference_type& __n)	{ 
			_M_iter += __n; 
			return *this; 
		}
		// addition of a difference type
		normal_iterator operator+(const difference_type& __n) const { 
			return normal_iterator(_M_iter + __n); 
		}
		// subtraction of a difference type
		normal_iterator& operator-=(const difference_type& __n)	{ 
			_M_iter -= __n; 
			return *this; 
		}
		// subtraction of a difference type
		normal_iterator	operator-(const difference_type& __n) const { 
			return normal_iterator(_M_iter - __n); 
		}
		// conversion to _Iter
		const _Iter& iter() const { 
			return _M_iter; 
		}
	};

	// Note: In what follows, the left- and right-hand-side
	// iterators are allowed to vary in types (conceptually in
	// cv-qualification) so that comparison between cv-qualified
	// and non-cv-qualified iterators be valid. However, the
	// greedy and unfriendly operators in std::rel_ops will make
	// overload resolution ambiguous (when in scope) if we don't
	// provide overloads whose operands are of the same type.

	// equality operator, forward iterator requirements
	template<typename _IterL, typename _IterR, typename _ContTag>
	inline 
	bool
	operator==( const normal_iterator<_IterL, _ContTag>& __l,
		    const normal_iterator<_IterR, _ContTag>& __r) { 
		return __l.iter() == __r.iter(); 
	}
	// equality operator, forward iterator requirements
	template<typename _Iter, typename _ContTag>
	inline 
	bool
	operator==( const normal_iterator<_Iter, _ContTag>& __l,
		    const normal_iterator<_Iter, _ContTag>& __r) { 
		return __l.iter() == __r.iter(); 
	}
	// inequality operator, forward iterator requirements
	template<typename _IterL, typename _IterR, typename _ContTag>
	inline 
	bool
	operator!=( const normal_iterator<_IterL, _ContTag>& __l,
		    const normal_iterator<_IterR, _ContTag>& __r) { 
		return __l.iter() != __r.iter(); 
	}
	// inequality operator, forward iterator requirements
	template<typename _Iter, typename _ContTag>
	inline 
	bool
	operator!=( const normal_iterator<_Iter, _ContTag>& __l,
		    const normal_iterator<_Iter, _ContTag>& __r) { 
		return __l.iter() != __r.iter(); 
	}
	// less than operator, random access iterator requirements
	template<typename _IterL, typename _IterR, typename _ContTag>
	inline 
	bool
	operator<( const normal_iterator<_IterL, _ContTag>& __l,
		   const normal_iterator<_IterR, _ContTag>& __r) { 
		return __l.iter() < __r.iter(); 
	}
	// less than operator, random access iterator requirements
	template<typename _Iter, typename _ContTag>
	inline 
	bool
	operator<( const normal_iterator<_Iter, _ContTag>& __l,
		   const normal_iterator<_Iter, _ContTag>& __r) { 
		return __l.iter() < __r.iter(); 
	}
	// greater than operator, random access iterator requirements
	template<typename _IterL, typename _IterR, typename _ContTag>
	inline 
	bool
	operator>( const normal_iterator<_IterL, _ContTag>& __l,
		   const normal_iterator<_IterR, _ContTag>& __r) { 
		return __l.iter() > __r.iter(); 
	}
	// greater than operator, random access iterator requirements
	template<typename _Iter, typename _ContTag>
	inline 
	bool
	operator>( const normal_iterator<_Iter, _ContTag>& __l,
		   const normal_iterator<_Iter, _ContTag>& __r) { 
		return __l.iter() > __r.iter(); 
	}
	// less than or equal operator, random access iterator
	// requirements
	template<typename _IterL, typename _IterR, typename _ContTag>
	inline 
	bool
	operator<=( const normal_iterator<_IterL, _ContTag>& __l,
		    const normal_iterator<_IterR, _ContTag>& __r) { 
		return __l.iter() <= __r.iter(); 
	}
	// less than or equal operator, random access iterator
	// requirements
	template<typename _Iter, typename _ContTag>
	inline 
	bool
	operator<=( const normal_iterator<_Iter, _ContTag>& __l,
		    const normal_iterator<_Iter, _ContTag>& __r) { 
		return __l.iter() <= __r.iter(); 
	}
	// greater than or equal operator, random access iterator
	// requirements
	template<typename _IterL, typename _IterR, typename _ContTag>
	inline 
	bool
	operator>=( const normal_iterator<_IterL, _ContTag>& __l,
		    const normal_iterator<_IterR, _ContTag>& __r) { 
		return __l.iter() >= __r.iter(); 
	}
	// greater than or equal operator, random access iterator
	// requirements
	template<typename _Iter, typename _ContTag>
	inline 
	bool
	operator>=( const normal_iterator<_Iter, _ContTag>& __l,
		    const normal_iterator<_Iter, _ContTag>& __r) { 
		return __l.iter() >= __r.iter(); 
	}
	// According to the resolution of DR179 not only the various
	// comparison operators but also operator- must accept mixed
	// iterator/const_iterator parameters.
	template<typename _IterL, typename _IterR, typename _ContTag>
	inline 
	typename normal_iterator<_IterL, _ContTag>::difference_type
	operator-( const normal_iterator<_IterL, _ContTag>& __l,
		   const normal_iterator<_IterR, _ContTag>& __r) { 
		return __l.iter() - __r.iter(); 
	}
	
	// addition of difference_type and iterator.
	template<typename _Iter, typename _ContTag>
	inline 
	normal_iterator<_Iter, _ContTag>
	operator+( typename normal_iterator<_Iter, _ContTag>::difference_type
		   __n, 
		   const normal_iterator<_Iter, _ContTag>& __i) { 
		return normal_iterator<_Iter, _ContTag>(__i.iter() + __n); 
	}
} // namespace cftal


// Local Variables:
// mode: c++
// End:
#endif
