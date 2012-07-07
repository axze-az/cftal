#if !defined ( __REAL_H__ )
#error "Never include this file directly. Use real.h instead"
#endif

inline
template <typename I>
void math::unchecked::add( I& a, const I& b) {
	a += b;
}

inline
template <typename I>
void math::unchecked::sub( I& a, const I& b) {
	a -= b;
}

inline
template <typename I>
void math::unchecked::mul( I& a, const I& b) {
	a *= b;
}

inline
template <typename I>
void math::unchecked::div( I& a, const I& b) {
	a /= b;
}

/*
 * Local variables:
 * mode: c++
 * end:
 */
