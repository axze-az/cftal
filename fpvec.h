#if !defined (__DVEC_H__)
#define __DVEC_H__ 1

#include <xmmintrin.h>
#include <emmintrin.h>
// #include <pmmintrin.h>

namespace vec {

	class vec4f {
	private:
		__v4sf _f4;
	public:
		vec4f( float f0123 );
		vec4f( float f0, float f1 , float f2, float f3);
		vec4f& operator+=( const vec4f& f);
		vec4f& operator-=( const vec4f& f);
		vec4f& operator*=( const vec4f& f);
		vec4f& operator/=( const vec4f& f);
		vec4f operator-() const;
	};

	class __attribute__((aligned(16))) vec2d {
	private:
		__v2df _d2;
	public:
		vec2d(__v2df r) : _d2(r) {
		}
		vec2d( ) : _d2( _mm_setzero_pd()) {
		}
		vec2d(double d01 ) : _d2( _mm_set1_pd(d01) )  {
		}
		vec2d(double low, double high ) : _d2( _mm_set_pd(high,low)){
		}
		vec2d(const double* p) : _d2( _mm_load_pd(p)) {
		}
		vec2d& operator+=( const vec2d& f) {
			_d2= _mm_add_pd(_d2,f._d2);
			return *this;
		}
		vec2d& operator-=( const vec2d& f) {
			_d2= _mm_sub_pd(_d2, f._d2 );
			return *this;
		}
		vec2d& operator*=( const vec2d& f) {
			_d2= _mm_mul_pd(_d2,f._d2);
			return *this;
		}
		vec2d& operator/=( const vec2d& f) {
			_d2= _mm_div_pd(_d2, f._d2);
			return *this;
		}
		vec2d operator-() const {
			const __v2df _neg_mask={-0.0,-0.0};
			return vec2d( _mm_xor_pd(_d2, _neg_mask) );
		}
		vec2d operator+( const vec2d& f ) const {
			return vec2d( _mm_add_pd(_d2,f._d2));
		}
		vec2d operator-( const vec2d& f ) const {
			return vec2d( _mm_sub_pd(_d2,f._d2));
		}
		vec2d operator*( const vec2d& f ) const {
			return vec2d( _mm_mul_pd(_d2,f._d2));
		}
		vec2d operator/( const vec2d& f ) const {
			return vec2d( _mm_div_pd(_d2,f._d2));
		}
		double low() const {
			return ((double*)&_d2)[0];
		}
		double high() const {
			return ((double*)&_d2)[1];
		}
	};

}

// Local variables:
// mode: c++
// end:
#endif
