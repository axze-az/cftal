#if !defined (__XMM_V4F__)
#define __XMM_V4F__ 1

#include <xmmintrin.h>

namespace xmm 
{
	const union {
		int i[4];
		__m128 m;
	} __v4f_not_sign_mask = { 
		0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff};

	const union {
		int i[4];
		__m128 m;
	} __v4f_sign_mask = { 
		0x80000000, 0x80000000, 0x80000000, 0x80000000};
	
	class v4f {
	public:
		// default constructor.
		v4f( ) : m_d( _mm_setzero_ps() ) {
		}
		// constructor from pair 
		v4f( float l0, float l1, float l2 , float l3) 
			: m_d( _mm_set_ps(l3,l2,l1,l0) ) {
		}
		// constructor from single value
		v4f( float l) : m_d( _mm_set1_ps(l) ) {
		}        
		// constructor from pointer. unaligned 
		v4f( const float p[4] ) 
			: m_d( _mm_load_ups(p) ) {
		}
		// constructor from m128 
		v4f( __m128 d ) : m_d(d) {
		}
		// assignment operator double
		v4f& operator=( double _r ) {
			m_d = _mm_set1_ps(_r);
			return *this;
		}
		// assignment operator __m128
		v4f& operator=( __m128 _d ) {
			m_d = _d;
			return *this;
		}        
		// return the stored value
		__m128 v() const {
			return m_d;
		}
		// arithmetic operations: +
		v4f& operator+=( const v4f& r ) {
			m_d = _mm_add_ps(m_d, r.m_d);
			return *this;
		}
		v4f& operator+=( float r) {
			m_d = _mm_add_ps( m_d, _mm_set1_ps(r) );
			return *this;
		}
		// arithmetic operations: -
		v4f& operator-=( const v4f& r ) {
			m_d = _mm_sub_ps(m_d, r.m_d);
			return *this;
		}
		v4f& operator-=( float r) {
			m_d = _mm_sub_ps(m_d, _load(r) );
			return *this;
		}
		// arithmetic operations: *
		v4f& operator*=( const v4f& r ) {
			m_d = _mm_mul_ps(m_d, r.m_d);
			return *this;
		}
		v4f& operator*=( float r ) {
			m_d = _mm_mul_ps(m_d, _load(r)); 
			return *this;
		}
		// arithmetic operations: /
		v4f& operator/=( const v4f& r) {
			m_d = _mm_div_ps(m_d, r.m_d);
			return *this;
		}
		v4f& operator/=( float r ) {
			m_d = _mm_div_ps(m_d, _load(r));
			return *this;
		}
		// negation:
		v4f operator-() const {
			v4f t( _mm_xor_ps(m_d, __v4f_not_sign_mask.m ) );
			return t;
		}                
	private:
		// the data member
		__m128 m_d;
	};
    
	// operator +
	inline
	v4f operator+(const v4f& a, const v4f& b) {
		v4f r( _mm_add_ps(a.v(), b.v()) );
		return r;
	}    
    
	inline
	v4f operator+( float a, const v4f& b ) {
		v4f r( _mm_add_ps( _mm_set1_ps(a), b.v()) );
		return r;
	}
        
	inline
	v4f operator+( const v4f& a, float b ) {
		v4f r( _mm_add_ps( a.v(), _mm_set1_ps(b)) );
		return r;
	}  
    
	// operator -
	inline
	v4f operator-(const v4f& a, const v4f& b) {
		v4f r( _mm_sub_ps(a.v(), b.v()) );
		return r;
	}

	inline
	v4f operator-( float a, const v4f& b ) {
		v4f r( _mm_sub_ps( _mm_set1_ps(a), b.v()) );
		return r;
	}
        
	inline
	v4f operator-( const v4f& a, float b ) {
		v4f r( _mm_sub_ps( a.v(), _mm_set1_ps(b)) );
		return r;
	}
    
	// operator *
	inline
	v4f operator*(const v4f& a, const v4f& b) {
		v4f r( _mm_mul_ps(a.v(), b.v()) );
		return r;
	}

	inline
	v4f operator*( float a, const v4f& b ) {
		v4f r( _mm_mul_ps( _mm_set1_ps(a), b.v()) );
		return r;
	}
        
	inline
	v4f operator*( const v4f& a, float b ) {
		v4f r( _mm_mul_ps( a.v(), _mm_set1_ps(b)) );
		return r;
	}
    
	// operator /
	inline
	v4f operator/(const v4f& a, const v4f& b) {
		v4f r( _mm_div_ps(a.v(), b.v()) );
		return r;
	} 
	inline
	v4f operator/( float a, const v4f& b ) {
		v4f r( _mm_div_ps( _mm_set1_ps(a), b.v()) );
		return r;
	}
        
	inline
	v4f operator/( const v4f& a, float b ) {
		v4f r( _mm_div_ps( a.v(), _mm_set1_ps(b)) );
		return r;
	}
    
	// low value:
	inline
	float val0( const v4f& a ) {
		float r;
		_mm_storel_ps(&r, a.v());
		return r;
	}
    
	// low value set
	inline
	v4f& val0( v4f& v, float l) {
		__m128 _v( _mm_loadl_ps(v.v(),&l ));
		v= _v;
		return v;
	}       
    
	// high value
	inline
	float val1( const v4f& a) {
		float r;
		_mm_storeh_ps(&r, a.v());
		return r;
	}
    
	// high value set
	inline
	v4f& val1( v4f& v, float h ) {
		__m128 _v( _mm_loadh_ps(v.v(),&h));
		v = _v;
		return v;
	}    
	
	// minimum value
	inline
	v4f min( const v4f& a, const v4f& b ) {
		v4f r( _mm_min_ps(a.v(), b.v()) );
		return r;
	}

	inline
	v4f min( float a, const v4f& b ) {
		v4f r( _mm_min_ps(a.v(), b.v()) );
		return r;
	}

	inline
	v4f min( const v4f& a, float b ) {
		v4f r( _mm_min_ps(a.v(), b.v()) );
		return r;
	}

	// minimum value
	inline
	v4f max( const v4f& a, const v4f& b ) {
		v4f r( _mm_max_ps(a.v(), b.v()) );
		return r;
	}
    
	// sqare root
	inline
	v4f sqrt( const v4f& d ) {
		v4f r( _mm_sqrt_ps( d.v()) );
		return r;
	}
    
	// absolute value
	inline
	v4f fabs( const v4f& d ) {
		v4f r( _mm_and_ps( d.v(), __v4f_not_sign_mask.m) );
		return r;
	}
    
	// absolute value
	inline
	v4f abs( const v4f& d ) {
		return fabs(d);
	}
}

// inline implementation
#include <xmm_v4f_inlines.h>

/*
 * Local variables:
 * mode: c++
 * end:
 */
#endif /* xmm_v4f.h */
