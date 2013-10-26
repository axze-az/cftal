#if !defined (__MEM_LOAD_H__)
#define __MEM_LOAD_H__ 1

namespace mem {

	// base template for loading from memory.
	template <class _T>
	class addr_base {
		const _T* _v;
	public:
		addr_base (const _T* t);
		const _T* operator()() const;
	};

	// default load argument without defined alignment
	template <class _T>
	class addr : public addr_base<_T> {
	public:
		addr(const _T* t);
	};

	// load and broadcast argument
	template <class _T>
	class addr_bcast : public addr_base<_T> {
	public:
		addr_bcast(const _T* t);
	};

	// load without defined alignment
	template <class _T>
	addr<_T> load(const _T* p);

	// store without defined alignment
	template <class _E, class _T>
	void store(_E* p, const _T& t);
	
	// load and broadcast
	template <class _T>
	addr_bcast<_T> load_bcast(const _T* p);
	
	// aligned loads and stores
	namespace aligned {
		
		// aligned load argument
		template <class _T>
		class addr : public addr_base<_T> {
		public:
			addr(const _T* t);
		};

		// load aligned
		template <class _T>
		addr<_T> load(const _T* p);

		// store aligned, declaration only
		template <class _E, class _T>
		void store(_E* p, const _T& t);
	}

	// unaligned loads and stores
	namespace unaligned {

		// unaligned load argument
		template <class _T>
		class addr : public addr_base<_T> {
		public:
			addr(const _T* t);
		};

		// load unaligned
		template <class _T>
		addr<_T> load(const _T* p);

		// store aligned, declaration only
		template <class _E, class _T>
		void store(_E* p, const _T& t);
	}

}

template <class _T>
inline
mem::addr_base<_T>::addr_base(const _T* t) : _v(t) 
{
}

template <class _T>
inline
const _T* mem::addr_base<_T>::operator()() const
{
	return _v;
}

template <class _T>
inline
mem::addr<_T>::addr(const _T* t) : addr_base<_T>(t) 
{
}

template <class _T>
inline
mem::aligned::addr<_T>::addr(const _T* t) : addr_base<_T>(t) 
{
}

template <class _T>
inline
mem::unaligned::addr<_T>::addr(const _T* t) : addr_base<_T>(t) 
{
}

template <class _T>
inline
mem::addr_bcast<_T>::addr_bcast(const _T* t) : addr_base<_T>(t) 
{
}
	
template <class _T>
inline
mem::addr<_T> mem::load(const _T* p) 
{
	return addr<_T>(p);
}
	
template <class _T>
inline
mem::addr_bcast<_T> mem::load_bcast(const _T* p) 
{
	return addr_bcast<_T>(p);
}
	
template <class _T>
inline
mem::aligned::addr<_T> mem::aligned::load(const _T* p) 
{
	return addr<_T>(p);
}

template <class _T>
inline
mem::unaligned::addr<_T> mem::unaligned::load(const _T* p) 
{
	return addr<_T>(p);
}
	

// Local variables:
// mode: c++
// end:
#endif
