#if !defined (__EMUVEC_H__)
#define __EMUVEC_H__ 1

#include <cftal/heap_array.h>
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
		void* begin() {
			return _v;
		}
		const void* begin() const {
			return _v;
		}
		void swap(utvec& r) {
			std::swap(_v, r._v);
		}
		utvec() : _v(alloc_()) {
		}
		utvec(const utvec& r) : _v(alloc_copy_(r)) {
		}
		utvec(utvec&& r) : _v(alloc_()) {
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
		struct vec_size {
			enum {
				value = _N * sizeof(_T)
			};
		};
		
		template <typename _T, std::size_t _N, bool _INIT=true>
		class vec : public utvec<impl::vec_size<_T,_N>::value, cftal::
			cache_allocator<char, impl::vec_size<_T,_N>::value> > {
		protected:
			typedef utvec<impl::vec_size<_T,_N>::value, cftal::
				      cache_allocator<char, impl::
						      vec_size<_T,_N>::value> >
				      base_type;
			typedef _T element_type;
			typedef base_type vector_type;
			_T* begin() { 
				return static_cast<_T*>(base_type::begin());
			}
			const _T* begin() const {
				return static_cast<const _T*>(
					base_type::begin());
			}
			_T* end() { return begin() + _N; }
			const _T* end() const { return begin() + _N; }
			vec() : base_type() {
				if (_INIT)
					std::uninitialized_fill(begin(), 
								end(), _T());
			}
			vec(element_type t) : base_type() {
				std::uninitialized_fill(begin(), end(), t);
			}
			vec(const vec& r) : base_type(r) {}
			vec(vec&& r) : base_type(std::move(r)) {}
			template <typename _U, std::size_t _M>
			vec(const vec<_U, _M>& r) : base_type(r) {}
			template <typename _U, std::size_t _M>
			vec(vec<_U, _M>&& r) : base_type(std::move(r)) {}
			vec& operator=(element_type r) {
				element_type t(r);
				std::fill(begin(), end(), t);
				return *this;
			}
			vec& operator=(const vec& r) {
				base_type::operator=(r);
				return *this;
			}
			vec& operator=(vec&& r) {
				base_type::operator=(std::move(r));
				return *this;
			}
			template <typename _U, std::size_t _M>
			vec& operator=(const vec<_U,_M>& r) {
				base_type::operator=(r);
				return *this;
			}
			template <typename _U, std::size_t _M>
			vec& operator=(vec<_U,_M>&& r) {
				base_type::operator=(std::move(r));
				return *this;
			}
		public:
			enum { N = _N };
			_T* operator()() { return begin(); }
			const _T* operator()() const { return begin(); }
		}; 

		
		template <typename _T, typename _OP>
		inline
		void v_op(_T* r, const _T* s0, const _T* s1, 
			  const _OP& op, std::size_t n)
		{
			for (std::size_t i=0; i<n; ++i)
				r[i] = op (s0[i] , s1[i]);
		}

		template <typename _T, typename _OP>
		inline
		void v_op(_T* r, const _T& s0, const _T* s1,
			  const _OP& op, std::size_t n)
		{
			for (std::size_t i=0; i<n; ++i)
				r[i] = op (s0 , s1[i]);
		}

		template <typename _T, typename _OP>
		inline
		void v_op(_T* r, const _T* s0, const _T& s1,
			  const _OP& op, std::size_t n)
		{
			for (std::size_t i=0; i<n; ++i)
				r[i] = op (s0[i] , s1);
		}
		
		template <typename _T, typename _OP>
		inline
		void v_op(_T* r, const _T* s0, const _OP& op, std::size_t n)
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
		UN_OP(a!=0 ? _T(-1) : _T(0), v_log_not);
		UN_OP(~a, v_not);
		UN_OP(-a, v_neg);
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

#undef BI_OP
		template <typename _T>
		struct v_div : 
			public std::conditional<
			std::is_floating_point<_T>::value,
			v_fdiv<_T>, v_idiv<_T> > {
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
	}
			

	class v8s16;
	class v8u16;
	class v4s32;
	class v4u32;

	class v8s16 : public impl::vec<std::int16_t, 8, false> {
	public:
		typedef std::int16_t element_type;
		typedef impl::vec<element_type, 8, false> base_type;
		typedef v8s16 my_type;
		
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
		
		// conversion from v8u16
		v8s16(const v8u16& r);
		v8s16(v8u16&& r);
		v8s16& operator=(const v8u16& r);
		v8s16& operator=(v8u16&& r);
	};

#define BI_OP(type, op, optype)						\
        inline								\
	type operator op (const type & a, const type& b)		\
	{								\
		type r;							\
		impl:: optype <type ::element_type > ot;		\
		impl::v_op(r(), a(), b(), ot, type::N);			\
		return r;						\
        }								\
									\
        inline								\
	type operator op (const type & a, const type :: element_type& b) \
	{								\
		type r;							\
		impl:: optype <type ::element_type > ot;		\
		impl::v_op(r(), a(), b, ot, type::N);			\
		return r;						\
        }								\
									\
        inline								\
	type operator op (const type ::element_type& a, const type& b)	\
	{								\
		type r;							\
		impl:: optype <type ::element_type > ot;		\
		impl::v_op(r(), a, b(), ot, type::N);			\
		return r;						\
        } 

#define ASSIGN_OP(type, op, optype)					\
        inline								\
	type& operator op (type &a, const type& b)			\
	{								\
		type r;							\
		impl:: optype <type ::element_type > ot;		\
		impl::v_op(r(), a(), b(), ot, type::N);			\
		return a=r;						\
        }								\
									\
        inline								\
	type operator op (type & a, const type :: element_type& b) \
	{								\
		type r;							\
		impl:: optype <type ::element_type > ot;		\
		impl::v_op(r(), a(), b, ot, type::N);			\
		return a=r;						\
        }		
	
#define UN_OP(type, op, func)					\
        inline							\
	type operator op (const type & a)			\
	{							\
		type r;						\
		impl:: optype <type ::element_type > ot;	\
		impl::v_op(r(), a(), ot, type::N);		\
		return r;					\
        }

#define POS_OP(type, op, func)						\
	inline const type& operator+(const type& a) { return a; } 

#define GEN_OPS(type)                           \
        UN_OP(type, !, v_log_not)               \
        UN_OP(type, ~, v_not)                   \
        UN_OP(type, -, v_neg)                   \
        POS_OP(type, +, v_pos)                   \
        BI_OP(type, <, v_lt)                    \
        BI_OP(type, <=, v_le)                   \
        BI_OP(type, ==, v_eq)                   \
        BI_OP(type, !=, v_ne)                   \
        BI_OP(type, >=, v_ge)                   \
        BI_OP(type, >, v_gt)                    \
        BI_OP(type, & , v_and)                  \
        ASSIGN_OP(type, &=, v_and)              \
        BI_OP(type, && , v_and)                 \
        BI_OP(type, | , v_or)                   \
        ASSIGN_OP(type, |=, v_or)               \
        BI_OP(type, || , v_or)                  \
        BI_OP(type, ^ , v_xor)                  \
        ASSIGN_OP(type, ^=, v_xor)		\
        BI_OP(type, + , v_add)			\
        ASSIGN_OP(type, +=, v_add)		\
        BI_OP(type, - , v_sub)			\
        ASSIGN_OP(type, -=, v_sub)		\
        BI_OP(type, * , v_mul)			\
        ASSIGN_OP(type, *=, v_mul)		\
        BI_OP(type, / , v_divd)			\
        ASSIGN_OP(type, *=, v_vdiv)

#define GEN_INT_OPS(type)			 \
        BI_OP(type, % , v_rem)			 \
        ASSIGN_OP(type, %=, v_rem)               


#if 0
        GEN_OPS(v8s16)
        GEN_OPS(v8u16)
        GEN_OPS(v4s32)
        GEN_OPS(v4u32)
#endif

#undef GEN_INT_OPS
#undef GEN_OPS
#undef UN_OP
#undef ASSIGN_OP
#undef BI_OP
}

// Local variables:
// mode: c++
// end:
#endif
