#if !defined (__XMM_V2D__)
#define __XMM_V2D__ 1

/* MS intrinsic */
#if defined (_MSC_VER)
#include <intrin.h>
#endif
/* SSE */
#include <xmmintrin.h> 
/* SSE2 */
#include <emmintrin.h> 
#include <cmath>

namespace vec {      

		

	template <class _T>
	class load_arg_base {
		_T _v;
	public:
		load_arg_base (_T t) : _v(t) {
		}
		_T operator()() const {
			return _v;
		}
	};

	template <class _T>
	class load_arg : public load_arg_base<_T> {
	public:
		load_arg(_T t) : load_arg_base<_T>(t) {
		}
	};

	template <class _T>
	load_arg<const _T*> load(_T* p) {
		return load_arg<const _T*>(p);
	}
	
	template <class _T>
	load_arg<const _T*> load(const _T* p) {
		return load_arg<const _T*>(p);
	}
	
	namespace aligned {

		template <class _T>
		class load_arg : public load_arg_base<_T> {
		public:
			load_arg(_T t) : load_arg_base<_T>(t) {
			}
		};

		template <class _T>
		load_arg<const _T*> load(_T* p) {
			return load_arg<const _T*>(p);
		}

		template <class _T>
		load_arg<const _T*> load(const _T* p) {
			return load_arg<const _T*>(p);
		}
		
	}

	namespace unaligned {

		template <class _T>
		class load_arg : public load_arg_base<_T> {
		public:
			load_arg(_T t) : load_arg_base<_T>(t) {
			}
		};
		
		template <class _T>
		load_arg<const _T*> load(_T* p) {
			return load_arg<const _T*>(p);
		}
	
		template <class _T>
		load_arg<const _T*> load(const _T* p) {
			return load_arg<const _T*>(p);
		}
	}
	

	// short vector of _T with _N elements.
	template <typename _T, unsigned _N >
	struct vec_data {
		enum {
			size = _N
		};
		typedef _T e_t;
		_T v[size];
	};

	typedef vec_data<double,2> double_pair;
	typedef vec_data<float,4> float_quad;

	// Non SSE/SSE2 fp operation traits.
	template <class _T>
	struct ftraits {
		// vector type:
		typedef _T v_t;
		// element type:
		typedef typename _T::e_t e_t;
		// size
		enum {
			size = _T::size
		};     
		// alignment      
		enum {
			alignment = sizeof(_T)
		};  
		// load with 0
		static inline
		v_t _set() {
			v_t r;
			for ( int i= 0; i< size; ++i )
				r.v[i] =0;
			return r;
		}                            
		// load from array. Order is defined here:
		static inline
		v_t _set( const e_t* p ) {
			v_t r;
			for ( int i=0; i<size; ++i )
				r.v[i] = p[i];
			return r;
		}  
		// load with two values.
		static inline 
		v_t _set( e_t v1, e_t v0 ) {
			v_t r;    
			r.v[0] = v0;
			for ( int i=1; i<size; ++i)
				r.v[i] = v1;
			return r;
		}
		// load with three values.
		static inline 
		v_t _set( e_t v2, e_t v1, e_t v0 ) {
			v_t r;    
			r.v[0] = v0;
			r.v[1] = v1;
			for ( int i=2; i<size; ++i)
				r.v[i] = v2;
			return r;
		}
		// load with four values.
		static inline 
		v_t _set( e_t v3, e_t v2, e_t v1, e_t v0 ) {
			v_t r;    
			r.v[0] = v0;
			r.v[1] = v1;
			r.v[2] = v2;
			for ( int i=3; i<size; ++i)
				r.v[i] = v3;
			return r;
		}
		// load pair with the same value.
		static inline
		v_t _set( e_t v ) {
			v_t r;
			for ( int i=0; i<size; ++i)
				r.v[i] = v;
			return r;
		}
		// set val0 of v to l
		static inline
		v_t _load0( v_t v, e_t* p) {
			v_t r(v);
			r.v[0] = *p;
			return r;
		}
		// set val1 of v to l
		static inline
		v_t _load1( v_t v, e_t* p) {
			v_t r(v);
			r.v[1] = *p;
			return r;
		}
		// set val2 of v to l
		static inline
		v_t _load2( v_t v, e_t* p) {
			v_t r(v);
			r.v[2] = *p;
			return r;
		}
		// set val3 of v to l
		static inline
		v_t _load3( v_t v, e_t* p) {
			v_t r(v);
			r.v[3] = *p;
			return r;
		}
		// read val0 of object
		static inline
		void _store0( e_t* p, v_t v ) {
			*p = v.v[0];
		}
		// read val1 of pair
		static inline
		void _store1( e_t* p, v_t v) {
			*p = v.v[1];
		}        
		// read val2 of object
		static inline
		void _store2( e_t* p, v_t v ) {
			*p = v.v[2];
		}
		// read val1 of pair
		static inline
		void _store3( e_t* p, v_t v) {
			*p = v.v[3];
		}        
		// add 
		static inline
		v_t _add( v_t a, v_t b) {
			v_t r;
			for ( int i = 0; i< size; ++i )
				r.v[i] = a.v[i] + b.v[i];
			return r;
		}
		// sub
		static inline
		v_t _sub( v_t a, v_t b) {
			v_t r;
			for ( int i = 0; i< size; ++i )
				r.v[i] = a.v[i] - b.v[i];
			return r;
		}
		// mul
		static inline
		v_t _mul( v_t a, v_t b) {
			v_t r;
			for ( int i = 0; i< size; ++i )
				r.v[i] = a.v[i] * b.v[i];
			return r;
		}
		// div
		static inline
		v_t _div( v_t a, v_t b) {
			v_t r;
			for ( int i = 0; i< size; ++i )
				r.v[i] = a.v[i] / b.v[i];
			return r;            
		}                
		// sqrt
		static inline
		v_t _sqrt( v_t a ) {
			v_t r;
			for ( int i= 0; i< size; ++i )
				r.v[i] = std::sqrt(a.v[i]);
			return r;
		}
		// abs:
		static inline
		v_t _abs( v_t a ) {
			v_t r;
			for ( int i=0; i< size; ++i )
				r.v[i] = std::abs(a.v[i]);
			return r;
		}
		// neg
		static inline
		v_t _neg( v_t a ) {
			v_t r;
			for ( int i=0; i< size; ++i) 
				r.v[i]= -a.v[i];
			return r;
		}    
		// min
		static inline
		v_t _min( v_t a, v_t b) {
			v_t r;
			for ( int i=0; i< size; ++i)
				r.v[i]= a.v[i] < b.v[i] ? a.v[i] : b.v[i];
			return r;
		}
		static inline
		v_t _max( v_t a, v_t b) {
			v_t r;
			for ( int i=0; i< size; ++i)
				r.v[i]= a.v[i] > b.v[i] ? a.v[i] : b.v[i];
			return r;
		}
	};

	// helper for ftraits<__m128>
	union __v4f {
		int i[4];
		__m128 m;
	};
	// see above.
	const __v4f __v4f_not_sign_mask = {
		0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff};
	// see above.                
	const __v4f __v4f_sign_mask = {
		0x80000000, 0x80000000, 0x80000000, 0x80000000};
    
	// SSE fp v4f operation traits
	template <>
	struct ftraits<__m128> {            
		// vector type:
		typedef __m128 v_t;
		// element type:
		typedef float e_t;
		// size
		enum {
			size = 2
		};     
		// alignment      
		enum {
			alignment = 16
		};  
		// load with 0
		static inline
		v_t _set() {
			return _mm_setzero_ps();
		}                            
		// load from array. Order is defined here:
		static inline
		v_t _set( const e_t* p ) {
			return _mm_set_ps(*(p+3), *(p+2), *(p+1), *p);
		}  
		// load quad with four values.
		static inline 
		v_t _set( e_t v3, e_t v2, e_t v1 , e_t v0 ) {
			return _mm_set_ps(v3, v2, v1, v0);
		}
		// load quad with the same value.
		static inline
		v_t _set( e_t v ) {
			return _mm_set1_ps(v);
		}
		// set val0 of quad to l
		static inline
		v_t _load0( v_t v, e_t* l) {
			v_t t= _mm_set_ss(*l);
			return _mm_move_ss(v,t);
		}
		// set val1 of quad to l
		static inline
		v_t _load1( v_t v, e_t* s) {
			/* exchange 0 and 1 */
			v_t t0= _mm_shuffle_ps( v, v, _MM_SHUFFLE(3,2,0,1));
			v_t t1= _mm_set_ss(*s);
			/* overwrite 0 */
			v_t t3= _mm_move_ss(t0,t1);
			/* exchange 0 and 1 */
			v_t t4= _mm_shuffle_ps( t3, t3, _MM_SHUFFLE(3,2,0,1));
			return t4;
		}
		// set val2 of quad to l
		static inline
		v_t _load2( v_t v, e_t* s) {
			/* exchange 0 and 2 */
			v_t t0= _mm_shuffle_ps( v, v, _MM_SHUFFLE(3,0,1,2));
			v_t t1= _mm_set_ss(*s);
			/* overwrite 0 */
			v_t t3= _mm_move_ss(t0,t1);
			/* exchange 0 and 2 */
			v_t t4= _mm_shuffle_ps( t3, t3, _MM_SHUFFLE(3,0,1,2));
			return t4;            
		}
		// set val3 of quad to l
		static inline
		v_t _load3( v_t v, e_t* s) {
			/* exchange 0 and 3 */
			v_t t0= _mm_shuffle_ps( v, v, _MM_SHUFFLE(0,2,1,3));
			v_t t1= _mm_set_ss(*s);
			/* overwrite 0 */
			v_t t3= _mm_move_ss(t0,t1);
			/* exchange 0 and 3 */
			v_t t4= _mm_shuffle_ps( t3, t3, _MM_SHUFFLE(0,2,1,3));
			return t4;            
		}
		// read val0 of quad
		static inline
		void _store0( e_t* l, v_t v ) {
			_mm_store_ss(l,v);
		}
		// read val1 of quad
		static inline
		void _store1( e_t* r, v_t v) {
			v_t t= _mm_shuffle_ps( v , v,  _MM_SHUFFLE(3,2,0,1));
			_mm_store_ss(r,t);
		}        
		// read val2 of quad
		static inline
		void _store2( e_t* r, v_t v) {
			v_t t= _mm_shuffle_ps( v , v,  _MM_SHUFFLE(3,0,1,2));
			_mm_store_ss(r,t);
		}        
		// read val3 of quad
		static inline
		void _store3( e_t* r, v_t v) {
			v_t t= _mm_shuffle_ps( v , v,  _MM_SHUFFLE(0,2,1,3));
			_mm_store_ss(r,t);
		}        
		// add 
		static inline
		v_t _add( v_t a, v_t b) {
			return _mm_add_ps( a, b );
		}
		// sub
		static inline
		v_t _sub( v_t a, v_t b) {
			return _mm_sub_ps( a, b );
		}
		// mul
		static inline
		v_t _mul( v_t a, v_t b) {
			return _mm_mul_ps( a, b );
		}
		// div
		static inline
		v_t _div( v_t a, v_t b) {
			return _mm_div_ps( a, b );
		}                
		// sqrt
		static inline
		v_t _sqrt( v_t a ) {
			return _mm_sqrt_ps( a );
		}
		// abs:
		static inline
		v_t _abs( v_t a ) {
			return _mm_and_ps( a, __v4f_not_sign_mask.m );
		}
		// neg
		static inline
		v_t _neg( v_t a ) {
			return _mm_xor_ps( a, __v4f_sign_mask.m );
		}
		// min
		static inline
		v_t _min( v_t a, v_t b) {
			return _mm_min_ps( a, b);
		}
		// max
		static inline
		v_t _max( v_t a, v_t b) {
			return _mm_max_ps( a, b);
		}
	};


	// helper for ftraits<__m128d>
	union __i32_v2d {    
		int i[4];
		__m128d m;
	};
	union __d_v2d {
		double d[2];
		__m128d m;
	};
	// see above.
	const __i32_v2d __v2d_not_sign_mask = {
		0xffffffff, 0x7fffffff, 0xffffffff, 0x7fffffff};
	// see above.                
	const __i32_v2d __v2d_sign_mask = {
		0x00000000, 0x80000000, 0x00000000, 0x80000000};
	// 0.0
	const __d_v2d __v2d_0 = { 0.0, 0.0 };
	// 1.0
	const __d_v2d __v2d_1 = { 1.0, 1.0 };
	// 0.5
	const __d_v2d __v2d_0_dot_5 { 0.5, 0.5 };

	// SSE2 fp v2d operation traits
	template <>
	struct ftraits<__m128d> {            
		// vector type:
		typedef __m128d v_t;
		// element type:
		typedef double e_t;
		// size
		enum {
			size = 2
		};     
		// alignment      
		enum {
			alignment = 16
		};  
		// load with 0
		static inline
		v_t _set() {
			return _mm_setzero_pd();
		}                            
		// load from array. Order is defined here:
		static inline
		v_t _set( const e_t* p ) {
			return _mm_set_pd(*(p+1), *p);
		}  
		// load pair with two values.
		static inline 
		v_t _set( e_t h, e_t l ) {
			return _mm_set_pd(h,l);
		}
		// load pair with the same value.
		static inline
		v_t _set( e_t v ) {
			return _mm_set1_pd(v);
		}
		// set val0 of pair to l
		static inline
		v_t _load0( v_t v, e_t* l) {
			return _mm_loadl_pd(v, l);
		}
		// set val1 of pair to l
		static inline
		v_t _load1( v_t v, e_t* h) {
			return _mm_loadh_pd(v, h);
		}
		// read val0 of pair
		static inline
		void _store0( e_t* l, v_t v ) {
			_mm_storel_pd(l,v);
		}
		// read val1 of pair
		static inline
		void _store1( e_t* h, v_t v) {
			_mm_storeh_pd(h,v);
		}        
		// add 
		static inline
		v_t _add( v_t a, v_t b) {
			return _mm_add_pd( a, b );
		}
		// sub
		static inline
		v_t _sub( v_t a, v_t b) {
			return _mm_sub_pd( a, b );
		}
		// mul
		static inline
		v_t _mul( v_t a, v_t b) {
			return _mm_mul_pd( a, b );
		}
		// div
		static inline
		v_t _div( v_t a, v_t b) {
			return _mm_div_pd( a, b );
		}                
		// sqrt
		static inline
		v_t _sqrt( v_t a ) {
			return _mm_sqrt_pd( a );
		}
		// abs:
		static inline
		v_t _abs( v_t a ) {
			return _mm_and_pd( a, __v2d_not_sign_mask.m );
		}
		// neg
		static inline
		v_t _neg( v_t a ) {
			return _mm_xor_pd( a, __v2d_sign_mask.m );
		}
		// min
		static inline
		v_t _min( v_t a, v_t b) {
			return _mm_min_pd( a, b);
		}
		// max
		static inline
		v_t _max( v_t a, v_t b) {
			return _mm_max_pd( a, b);
		}        
	};
    
	template <class _T>    
	class fvec_t {
	public:
		// internal implementation:
		typedef ftraits<_T> impl;
		// element type
		typedef typename impl::e_t e_t;
		// underlying type
		typedef typename impl::v_t v_t;
		// default constructor.
		fvec_t( ) : m_d( impl::_set() ) {
		}
		// constructor. sets ffvec_t[0..size-1] to v
		fvec_t( e_t v) : m_d( impl::_set(v) ) {
		}        
		// constructor. sets ffvec_t[0] to v0, fvec_t[1
		// .. size) to v1
		fvec_t( e_t v0, e_t v1 ) : m_d( impl::_set(v1, v0) ) {
		}
		// constructor. sets fvec_t[0] to v0, fvec_t[1] to v1, 
		// fvec_t[2 .. size) to v2
		fvec_t( e_t v0, e_t  v1, e_t v2 ) 
			: m_d ( impl::_set(v2, v1,v0)) {
		}
		// constructor. sets fvec_t[0] to v0, fvec_t[1] to v1, 
		// fvec_t[2] to v2, fvec_t[3 .. size) to v3. 
		fvec_t( e_t v0, e_t  v1, e_t v2, e_t v3 ) 
			: m_d ( impl::_set(v3, v2, v1, v0)) {
		}
		// constructor from pointer. 
		fvec_t( const e_t* p ) : m_d( impl::_set(*p) ) {
		}
		// constructor from m128d 
		fvec_t( v_t d ) : m_d(d) {
		}
		// assignment operator e_t
		fvec_t& operator=( e_t _r ) {
			impl::_set(_r);
			return *this;
		}
		// assignment operator v_t
		fvec_t& operator=( v_t _d ) {
			m_d = _d;
			return *this;
		}        
		// return the stored value
		v_t v() const {
			return m_d;
		}
		// arithmetic operations: +
		fvec_t& operator+=( const fvec_t& r ) {
			m_d = impl::_add(m_d, r.m_d);
			return *this;
		}
		fvec_t& operator+=( e_t r) {
			m_d = impl::_add( m_d, impl::_set(r) );
			return *this;
		}
		// arithmetic operations: -
		fvec_t& operator-=( const fvec_t& r ) {
			m_d = impl::_sub(m_d, r.m_d);
			return *this;
		}
		fvec_t& operator-=( e_t r) {
			m_d = impl::_sub(m_d, impl::_set(r) );
			return *this;
		}
		// arithmetic operations: *
		fvec_t& operator*=( const fvec_t& r ) {
			m_d = impl::_mul(m_d, r.m_d);
			return *this;
		}
		fvec_t& operator*=( e_t r ) {
			m_d = impl::_mul(m_d, impl::_set(r)); 
			return *this;
		}
		// arithmetic operations: /
		fvec_t& operator/=( const fvec_t& r) {
			m_d = impl::_div(m_d, r.m_d);
			return *this;
		}
		fvec_t& operator/=( e_t r ) {
			m_d = impl::_div(m_d, impl::_set(r));
			return *this;
		}
		// negation:
		fvec_t operator-() const {
			fvec_t t( impl::_neg(m_d)) ;
			return t;
		}                
	private:
		// the data member
		v_t m_d;
	};   

	// operator +
	template <class _T>
	inline
	fvec_t<_T> operator+(const fvec_t<_T>& a, 
			     const fvec_t<_T>& b) {
		fvec_t<_T> r( fvec_t<_T>::impl::_add(a.v(), b.v()) );
		return r;
	}    
    
	template <class _T>
	inline
	fvec_t<_T> operator+( typename fvec_t<_T>::e_t a, 
			      const fvec_t<_T>& b ) {
		fvec_t<_T> r( 
			fvec_t<_T>::impl::_add( fvec_t<_T>::impl::_set(a), 
						b.v()) );
		return r;
	}
        
	template <class _T>
	inline
	fvec_t<_T> operator+( const fvec_t<_T>& a, 
			      typename fvec_t<_T>::e_t b ) {
		fvec_t<_T> r( 
			fvec_t<_T>::impl::_add( a.v(), 
						fvec_t<_T>::impl::_set(b)) );
		return r;
	}  
    
	// operator -
	template <class _T>
	inline
	fvec_t<_T> operator-(const fvec_t<_T>& a, 
			     const fvec_t<_T>& b) {
		fvec_t<_T> r( fvec_t<_T>::impl::_sub(a.v(), b.v()) );
		return r;
	}

	template <class _T>
	inline
	fvec_t<_T> operator-(typename fvec_t<_T>::e_t a, 
			     const fvec_t<_T>& b ) {
		fvec_t<_T> r( 
			fvec_t<_T>::impl::_sub( fvec_t<_T>::impl::_set(a), 
						b.v()) );
		return r;
	}
        
	template <class _T>
	inline
	fvec_t<_T> operator-( const fvec_t<_T>& a, 
			      typename fvec_t<_T>::e_t b ) {
		fvec_t<_T> r( 
			fvec_t<_T>::impl::_sub( a.v(), 
						fvec_t<_T>::impl::_set(b)) );
		return r;
	}
    
	// operator *
	template <class _T>
	inline
	fvec_t<_T> operator*(const fvec_t<_T>& a, 
			     const fvec_t<_T>& b) {
		fvec_t<_T> r( fvec_t<_T>::impl::_mul(a.v(), b.v()) );
		return r;
	}

	template <class _T>
	inline
	fvec_t<_T> operator*( typename fvec_t<_T>::e_t a, 
			      const fvec_t<_T>& b ) {
		fvec_t<_T> r( 
			fvec_t<_T>::impl::_mul( fvec_t<_T>::impl::_set(a), 
						b.v()) );
		return r;
	}
        
	template <class _T>
	inline
	fvec_t<_T> operator*( const fvec_t<_T>& a, 
			      typename fvec_t<_T>::e_t b ) {
		fvec_t<_T> r( 
			fvec_t<_T>::impl::_mul( a.v(), 
						fvec_t<_T>::impl::_set(b)) );
		return r;
	}
    
	// operator /
	template <class _T>
	inline
	fvec_t<_T> operator/(const fvec_t<_T>& a, 
			     const fvec_t<_T>& b) {
		fvec_t<_T> r( fvec_t<_T>::impl::_div(a.v(), b.v()) );
		return r;
	} 
	template <class _T>
	inline
	fvec_t<_T> operator/( typename fvec_t<_T>::e_t a, 
			      const fvec_t<_T>& b ) {
		fvec_t<_T> r( 
			fvec_t<_T>::impl::_div( fvec_t<_T>::impl::_set(a), 
						b.v()) );
		return r;
	}
        
	template <class _T>
	inline
	fvec_t<_T> operator/( const fvec_t<_T>& a, 
			      typename fvec_t<_T>::e_t b ) {
		fvec_t<_T> r( 
			fvec_t<_T>::impl::_div( a.v(), 
						fvec_t<_T>::impl::_set(b)) );
		return r;
	}
    
	// value 0
	template <class _T>
	inline
	typename fvec_t<_T>::e_t val0( const fvec_t<_T>& a ) {
		typename fvec_t<_T>::e_t r;
		fvec_t<_T>::impl::_store0(&r, a.v());
		return r;
	}
    
	// value 0 set
	template <class _T>
	inline
	fvec_t<_T>& val0( fvec_t<_T>& v, typename fvec_t<_T>::e_t l) {
		v= fvec_t<_T>::impl::_load0(v.v(),&l );
		return v;
	}       
    
	// value 1
	template <class _T>
	inline
	typename fvec_t<_T>::e_t val1( const fvec_t<_T>& a) {
		typename fvec_t<_T>::e_t r;
		fvec_t<_T>::impl::_store1(&r, a.v());
		return r;
	}
    
	// value 1 set
	template <class _T>
	inline
	fvec_t<_T>& val1( fvec_t<_T>& v, typename fvec_t<_T>::e_t h ) {
		v= fvec_t<_T>::impl::_load1(v.v(),&h);
		return v;
	}    

	// value 2
	template <class _T>
	inline
	typename fvec_t<_T>::e_t val2( const fvec_t<_T>& a) {
		typename fvec_t<_T>::e_t r;
		fvec_t<_T>::impl::_store2(&r, a.v());
		return r;
	}
    
	// value 2 set
	template <class _T>
	inline
	fvec_t<_T>& val2( fvec_t<_T>& v, typename fvec_t<_T>::e_t h ) {
		v= fvec_t<_T>::impl::_load2(v.v(),&h);
		return v;
	}    

	// value 3
	template <class _T>
	inline
	typename fvec_t<_T>::e_t val3( const fvec_t<_T>& a) {
		typename fvec_t<_T>::e_t r;
		fvec_t<_T>::impl::_store3(&r, a.v());
		return r;
	}
    
	// value 3 set
	template <class _T>
	inline
	fvec_t<_T>& val3( fvec_t<_T>& v, typename fvec_t<_T>::e_t h ) {
		v= fvec_t<_T>::impl::_load3(v.v(),&h);
		return v;
	}    
       
	// sqare root
	template <class _T>
	inline
	fvec_t<_T> sqrt( const fvec_t<_T>& d ) {
		fvec_t<_T> r( fvec_t<_T>::impl::_sqrt( d.v()) );
		return r;
	}
    
	// absolute value
	template <class _T>
	inline
	fvec_t<_T> fabs( const fvec_t<_T>& d ) {
		fvec_t<_T> r( fvec_t<_T>::impl::_abs( d.v() ) );
		return r;
	}
    
	// absolute value
	template <class _T>
	inline
	fvec_t<_T> abs( const fvec_t<_T>& d ) {
		return fabs(d);
	}
    
	// minumum value
	template <class _T>
	inline
	fvec_t<_T> min( const fvec_t<_T>& a, const fvec_t<_T>& b) {
		fvec_t<_T> r( 
			fvec_t<_T>::impl::_min( a.v(), b.v()) );
		return r;
	}
    
	template <class _T>
	inline
	fvec_t<_T> min( const fvec_t<_T>& a, 
			typename fvec_t<_T>::e_t b) {
		fvec_t<_T> r( 
			fvec_t<_T>::impl::_min( a.v(), 
						fvec_t<_T>::impl::_set(b)) );
		return r;
	}
    
	template <class _T>
	inline
	fvec_t<_T> min( typename fvec_t<_T>::e_t a, 
			const fvec_t<_T>& b) {
		fvec_t<_T> r( 
			fvec_t<_T>::impl::_min( fvec_t<_T>::impl::_set(a), 
						b.v() ));
		return r;
	}
    
	// maximum value
	template <class _T>
	inline
	fvec_t<_T> max( const fvec_t<_T>& a, 
			const fvec_t<_T>& b) {
		fvec_t<_T> r( 
			fvec_t<_T>::impl::_max( a.v(), b.v()) );
		return r;
	}
    
	template <class _T>
	inline
	fvec_t<_T> max( const fvec_t<_T>& a, 
			typename fvec_t<_T>::e_t b) {
		fvec_t<_T> r( 
			fvec_t<_T>::impl::_max( a.v(), 
						fvec_t<_T>::impl::_set(b)) );
		return r;
	}
    
	template <class _T>
	inline
	fvec_t<_T> max( typename fvec_t<_T>::e_t a, 
			const fvec_t<_T>& b) {
		fvec_t<_T> r( 
			fvec_t<_T>::impl::_max( fvec_t<_T>::impl::_set(a), 
						b.v() ));
		return r;
	}
    
	// v2d vector implementation.
	namespace xmm {
		typedef fvec_t<__m128d> v2d;
	}        
	typedef fvec_t<double_pair> v2d;
    
	// v4f vector implementation.
	namespace xmm {
		typedef fvec_t<__m128> v4f;
	}
	typedef fvec_t<float_quad> v4f;
}  

/*
 * Local variables:
 * mode: c++
 * end:
 */
#endif /* xmm_v2d.h */
