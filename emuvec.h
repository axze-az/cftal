#if !defined (__EMUVEC_H__)
#define __EMUVEC_H__ 1

#include <cftal/allocator.h>
#include <cftal/mem_load.h>
#include <cstring>
#include <type_traits>

namespace emuvec {

	// constants consisting of 1 uint32_t
	template <std::uint32_t _P>
	struct const_u32 {
		static
		const std::uint32_t val = _P;
	};

        namespace impl {

		// returns -1 if lt zero
                template <typename _T>
                inline
                _T lt_z(const _T& j )
                {
			typedef typename std::make_signed<_T>::type _S;
			_S s(j);
                        return _T(s < _S(0) ? -1 : 0);
                }

		// returns -1 if ge zero
		template <typename _T>
		inline
		_T ge_z(const _T& j) {
			return ~lt_z(j);
		}

		template <typename _T>
		std::uint32_t get_signs_32(const _T* p, std::size_t n)
		{
			if (n>32)
				std::abort();
			std::uint32_t r(0), m(1);
			typedef typename std::make_signed<_T>::type _S;
			const _S* s= static_cast<const _S*>(p);
			for (std::size_t i=0; i<n; ++i, m<<=1) {
				std::uint32_t mi( s[i] < _S(0) ? m : 0);
				r |= mi;
			}
			return r;
		}


		template <std::size_t _N>
		struct mem_cpy {
			static void* v(void* d, const void* s) {
				return std::memcpy(d, s, _N);
			}
		};

		template <>
		struct mem_cpy<16> {
			static void* v(void* d, const void*s) {
				const std::uint64_t* su=
				static_cast<const std::uint64_t*>(s);
				std::uint64_t* du=static_cast<std::uint64_t*>(d);
				du[0] = su[0];
				du[1] = su[1];
				return d;
			}
		};

		// vector with untyped memory, works only
		// with stateless allocators.
		template <std::size_t _N,  class _A = std::allocator<char> >
		class utvec : private _A {
			void* _v;
			void* alloc_() {
				_A* a= static_cast<_A*>(this);
				return static_cast<void*>(a->allocate(_N));
			}
			void free_() {
				_A* a= static_cast<_A*>(this);
				char* p= static_cast<char*>(_v);
				a->deallocate(p, _N);
			}
			void* copy_(void* dst, const void* src) {
				return mem_cpy<_N>::v(dst, src);
			}
			void* alloc_copy_(const utvec& r) {
				void* p= copy_(alloc_(), r._v);
				return p;
			}
		protected:
			_A& get_allocator() {
				return *this;
			}
			void* begin() {
				return _v;
			}
			const void* begin() const {
				return _v;
			}
			void swap(utvec& r) {
				std::swap(_v, r._v);
			}
			utvec() : _A(), _v(alloc_()) {
			}
			utvec(const utvec& r) : _A(r), _v(alloc_copy_(r)) {
			}
			utvec(utvec&& r) : _A(std::move(r)), _v(alloc_()) {
				swap(r);
			}
			utvec& operator=(const utvec& r) {
				if (&r != this)
					copy_(_v, r._v, _N);
				return *this;
			}
			utvec& operator=(utvec&& r) {
				swap(r);
				return *this;
			}
		};
	}

	namespace impl {

		template <typename _T, std::size_t _N>
		struct vec_base {
			enum {
				size = _N * sizeof(_T)
			};
			typedef	utvec<size, cftal::cache_allocator<char, size> > type;
		};

		template <typename _T, typename _OP>
		inline
		void v_bi_op(_T* r, const _T* s0, const _OP& op, const _T* s1,
			     std::size_t n)
		{
			for (std::size_t i=0; i<n; ++i)
				r[i] = op (s0[i] , s1[i]);
		}

		template <typename _T, typename _OP>
		inline
		void v_bi_op(_T* r, const _T* s0, const _OP& op, std::size_t n)
		{
			for (std::size_t i=0; i<n; ++i)
				r[i] = op (s0[i]);
		}

		template <typename _T, typename _OP>
		void v_assign_op(_T* s0_r,
				 const _OP& op, const _T* s1, std::size_t n)
		{
			for (std::size_t i=0; i<n; ++i)
				s0_r[i] = op (s0_r[i] , s1[i]);
		}

		template <typename _T, typename _OP>
		void v_assign_op(_T* s0_r, const _OP& op, std::size_t n)
		{
			for (std::size_t i=0; i<n; ++i)
				s0_r[i] = op (s0_r[i]);
		}

		template <typename _T, typename _OP>
		inline
		void v_un_op(_T* r, const _OP& op, const _T* s0,
			     std::size_t n)
		{
			for (std::size_t i=0; i<n; ++i)
				r[i] = op(s0[i]);
		}

#define UN_OP(op, v_name)					\
		template <typename _T>				\
		struct v_name {					\
			_T operator()(const _T& a) const {	\
				return op;			\
			}					\
		}
		UN_OP(a!=_T(0) ? _T(-1) : _T(0), v_log_not);
		UN_OP(~a, v_not);
		UN_OP(-a, v_neg);
		UN_OP(a+_T(1), v_inc);
		UN_OP(a-_T(1), v_dec);
		UN_OP(a<_T(0) ? -a : a, v_abs);
#undef UN_OP

#define BI_OP(op, v_name)						\
		template <typename _T>					\
		struct v_name {						\
			_T operator()(const _T& a, const _T& b) const {	\
				return op;				\
			}						\
		};
		BI_OP(a^b, v_xor);
		BI_OP(a|b, v_or);
		BI_OP(a&b, v_and);
		BI_OP(a+b, v_add);
		BI_OP(a-b, v_sub);
		BI_OP(a*b, v_mul);
		BI_OP(a/b, v_fdiv);
		BI_OP(b != 0 ? a/b : _T(-1), v_idiv);
		BI_OP(b != 0 ? a%b : a, v_irem);
		BI_OP(a<b, v_lt);
		BI_OP(a<=b, v_le);
		BI_OP(a==b, v_eq);
		BI_OP(a!=b, v_ne);
		BI_OP(a>=b, v_ge);
		BI_OP(a>b, v_gt);
		BI_OP(a>b ? a : b, v_max);
		BI_OP(a<b ? a : b, v_min);
#undef BI_OP

		template <typename _T>
		struct v_div :
			public std::conditional<
			std::is_floating_point<_T>::value,
			v_fdiv<_T>, v_idiv<_T> >::type {
		};

		template <typename _T>
		class v_sl {
			std::uint32_t _s;
		public:
			v_sl(std::uint32_t s) : _s(s) {}
			_T operator()(const _T& a) const {
				return a << _s;
			}
		};

		template <typename _T>
		class v_sr {
			std::uint32_t _s;
		public:
			v_sr(std::uint32_t s) : _s(s) {}
			_T operator()(const _T& a) const {
				return a >> _s;
			}
		};

		template <typename _T>
		struct v_mulhi {};

		template <>
		struct v_mulhi<std::int16_t> {
			std::int16_t operator()(std::int16_t a, std::int16_t b) const {
				return std::int32_t(a) * std::int32_t(b) >> 16;
			}
		};

		template <>
		struct v_mulhi<std::uint16_t> {
			std::uint16_t operator()(std::uint16_t a, std::uint16_t b) const {
				return std::uint32_t(a) * std::uint32_t(b) >> 16;
			}
		};

		template <>
		struct v_mulhi<std::int32_t> {
			std::int32_t operator()(std::int32_t a, std::int32_t b) const {
				return std::int64_t(a) * std::int64_t(b) >> 32;
			}
		};

		template <>
		struct v_mulhi<std::uint32_t> {
			std::uint32_t operator()(std::uint32_t a, std::uint32_t b) const {
				return std::uint64_t(a) * std::uint64_t(b) >> 32;
			}
		};
	}


	class v8s16;
	class v8u16;
	class v4s32;
	class v4u32;

	class v8s16 : public impl::vec_base<std::int16_t, 8>::type {
	public:
		enum { N = 8 };
		typedef std::int16_t element_type;
		typedef typename impl::vec_base<element_type, N>::type base_type;
		element_type* operator()();
		const element_type* operator()() const;
		// no initialization is done here.
		v8s16();
		v8s16(element_type r);
		v8s16(element_type r, bool broad_cast);
		v8s16(element_type i0, element_type i1,
		      element_type i2, element_type i3,
		      element_type i4, element_type i5,
		      element_type i6, element_type i7);
		v8s16(const v8s16& r);
		v8s16(v8s16&& r);
		v8s16& operator=(element_type r);
		v8s16& operator=(const v8s16& r);
		v8s16& operator=(v8s16&& r);

		// memory load operations
                v8s16(const mem::addr_bcast<element_type>& r);
                v8s16(const mem::addr<element_type>& r);
	private:
		element_type* begin();
		const element_type* begin() const;
	};

        v8s16& operator|= (v8s16& a, const v8s16& b);
        v8s16& operator&= (v8s16& a, const v8s16& b);
        v8s16& operator^= (v8s16& a, const v8s16& b);
        v8s16& operator+= (v8s16& a, const v8s16& b);
        v8s16& operator-= (v8s16& a, const v8s16& b);
        v8s16& operator*= (v8s16& a, const v8s16& b);
        v8s16& operator/= (v8s16& a, const v8s16& b);
        v8s16& operator%= (v8s16& a, const v8s16& b);

        template <std::uint32_t _P>
        v8s16& operator<<= (v8s16& a, const const_u32<_P>& b);
        v8s16& operator<<= (v8s16& a, std::uint32_t b);
        template <std::uint32_t _P>
        v8s16 operator <<(const v8s16& a, const const_u32<_P>& b);
        v8s16 operator <<(const v8s16& a, std::uint32_t b);

        template <std::uint32_t _P>
        v8s16& operator>>= (v8s16& a, const_u32<_P>& b);
        v8s16& operator>>= (v8s16& a, std::uint32_t b);
        template <std::uint32_t _P>
        v8s16 operator >>(const v8s16& a, const const_u32<_P>& b);
        v8s16 operator >>(const v8s16& a, std::uint32_t b);

        v8s16 operator++ (v8s16& a, int);
        v8s16& operator++(v8s16& a);
        v8s16 operator-- (v8s16& a, int);
        v8s16& operator--(v8s16& a);

        v8s16 operator-(const v8s16& a);
	const v8s16& operator+(const v8s16& a);
        v8s16 operator~(const v8s16& a);
        v8s16 operator!(const v8s16& a);

        v8s16 operator| (const v8s16& a, const v8s16& b);
        v8s16 operator|| (const v8s16& a, const v8s16& b);
        v8s16 operator& (const v8s16& a, const v8s16& b);
        v8s16 operator&& (const v8s16& a, const v8s16& b);
        v8s16 operator^(const v8s16& a, const v8s16& b);

        v8s16 operator+ (const v8s16& a, const v8s16& b);
        v8s16 operator- (const v8s16& a, const v8s16& b);
        v8s16 operator* (const v8s16& a, const v8s16& b);
        v8s16 operator/ (const v8s16& a, const v8s16& b);
        v8s16 operator% (const v8s16& a, const v8s16& b);

        v8s16 operator< (const v8s16& a, const v8s16& b);
        v8s16 operator<= (const v8s16& a, const v8s16& b);
        v8s16 operator== (const v8s16& a, const v8s16& b);
        v8s16 operator!= (const v8s16& a, const v8s16& b);
        v8s16 operator>= (const v8s16& a, const v8s16& b);
        v8s16 operator> (const v8s16& a, const v8s16& b);

        // checks the signs
        bool all_signs(const v8s16& a);
        // checks the signs
        bool both_signs(const v8s16& a);
        // checks the signs
        bool no_signs(const v8s16& a);

        v8s16 max(const v8s16& a, const v8s16& b);
        v8s16 min(const v8s16& a, const v8s16& b);
        v8s16 abs(const v8s16& a);
	v8s16 mulh(const v8s16& a, const v8s16& b);

        template < bool _P0, bool _P1, bool _P2, bool _P3,
		   bool _P4, bool _P5, bool _P6, bool _P7 >
        v8s16 select(const v8s16& a, const v8s16& b);
        v8s16 select(const v8s16& msk, const v8s16& on_true,
                     const v8s16& on_false);

        template < int _P0, int _P1, int _P2, int _P3,
		   int _P4, int _P5, int _P6, int _P7 >
        v8s16 permute(const v8s16& a);
        template < int _P0, int _P1, int _P2, int _P3,
		   int _P4, int _P5, int _P6, int _P7 >
        v8s16 permute(const v8s16& a, const v8s16& b);

	template <unsigned _I>
	v8s16 insert(const v8s16& a, typename v8s16::element_type v);
	template <unsigned _I>
	typename v8s16::element_type extract(const v8s16& a);

}

inline
emuvec::v8s16::element_type* emuvec::v8s16::begin()
{
	return static_cast<element_type*>(base_type::begin());
}

inline
const emuvec::v8s16::element_type* emuvec::v8s16::begin() const
{
	return static_cast<const element_type*>(base_type::begin());
}

inline
emuvec::v8s16::element_type* emuvec::v8s16::operator()()
{
	return begin();
}

inline
const emuvec::v8s16::element_type* emuvec::v8s16::operator()() const
{
	return begin();
}

template <unsigned _P>
emuvec::v8s16&
emuvec::operator<<= (v8s16& a, const const_u32< _P >& b)
{
        const int val = b.val;
	impl::v_sl<v8s16::element_type> ot(val);
	impl::v_assign_op(a(), ot, v8s16::N);
        return a;
}

template <unsigned _P>
emuvec::v8s16&
emuvec::operator>>= (v8s16& a, const const_u32< _P >& b)
{
        const int val = b.val;
	impl::v_sr<v8s16::element_type> ot(val);
	impl::v_assign_op(a(), ot, v8s16::N);
        return a;
}

template <unsigned _P>
emuvec::v8s16
emuvec::operator<<(const v8s16& a, const const_u32< _P >& b)
{
	v8s16 r;
        const int val = b.val;
	impl::v_sl<v8s16::element_type> ot(val);
	impl::v_bi_op(r(), a(), ot, v8s16::N);
	return r;
}

template <unsigned _P>
emuvec::v8s16
emuvec::operator>> (const v8s16& a, const const_u32< _P >& b)
{
	v8s16 r;
        const int val = b.val;
	impl::v_sr<v8s16::element_type> ot(val);
	impl::v_bi_op(r(), a(), ot, v8s16::N);
	return r;
}


// Local variables:
// mode: c++
// end:
#endif
