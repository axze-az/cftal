#if !defined (__EMUVEC_H__)
#define __EMUVEC_H__ 1

#include <cftal/config.h>
#include <cftal/allocator.h>
#include <cftal/mem_load.h>
#include <cftal/emuvec_impl_ops.h>
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
                                std::uint64_t* du=
                                        static_cast<std::uint64_t*>(d);
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
                        void* vbegin() {
                                return _v;
                        }
                        const void* vbegin() const {
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

                template <class _T>
                struct select {
                        static void v(_T* r, const _T* msk,
                                      const _T* ontrue, const _T* onfalse,
                                      std::size_t n) {
                                for (std::size_t i=0; i<n; ++i) {
                                        r[i] = lt_z(msk[i]) ?
                                                ontrue[i] : onfalse[i];
                                }
                        }
                };

                template <class _T, bool _P0, bool _P1>
                struct select_2 {
                        static void v(_T* r, const _T* s0, const _T* s1) {
                                r[0] = _P0 ? s0[0] : s1[0];
                                r[1] = _P1 ? s0[1] : s1[1];
                        }
                };

                template <class _T, int _P0, int _P1>
                struct perm1_2 {
                        static void v(_T* r, const _T* s0) {
                                r[0] = ge_z(_P0) & s0[_P0 & 1] ;
                                r[1] = ge_z(_P1) & s0[_P1 & 1];
                        }
                };

                template <class _T, int _P0, int _P1>
                struct perm2_2 {
                        static void v(_T* r, const _T* s0, const _T* s1) {
                                r[0] = ge_z(_P0) &
                                        (_P0>1 ? s1[_P0 & 1] : s0[_P0 & 1]);
                                r[1] = ge_z(_P1) &
                                        (_P1>1 ? s1[_P1 & 1] : s0[_P1 & 1]);
                        }
                };

                template <class _T, bool _P0, bool _P1, bool _P2, bool _P3>
                struct select_4 {
                        static void v(_T* r, const _T* s0, const _T* s1) {
                                r[0] = _P0 ? s0[0] : s1[0];
                                r[1] = _P1 ? s0[1] : s1[1];
                                r[2] = _P2 ? s0[2] : s1[2];
                                r[3] = _P3 ? s0[3] : s1[3];
                        }
                };

                template <class _T, int _P0, int _P1, int _P2, int _P3>
                struct perm1_4 {
                        static void v(_T* r, const _T* s0) {
                                r[0] = ge_z(_P0) & s0[_P0 & 3] ;
                                r[1] = ge_z(_P1) & s0[_P1 & 3];
                                r[2] = ge_z(_P2) & s0[_P2 & 3];
                                r[3] = ge_z(_P3) & s0[_P3 & 3];
                        }
                };

                template <class _T, int _P0, int _P1, int _P2, int _P3>
                struct perm2_4 {
                        static void v(_T* r, const _T* s0, const _T* s1) {
                                r[0] = ge_z(_P0) &
                                        (_P0>3 ? s1[_P0 & 3] : s0[_P0 & 3]);
                                r[1] = ge_z(_P1) &
                                        (_P1>3 ? s1[_P1 & 3] : s0[_P1 & 3]);
                                r[2] = ge_z(_P2) &
                                        (_P2>3 ? s1[_P2 & 3] : s0[_P2 & 3]);
                                r[3] = ge_z(_P3) &
                                        (_P3>3 ? s1[_P3 & 3] : s0[_P3 & 3]);
                        }
                };

                template <class _T, bool _P0, bool _P1, bool _P2, bool _P3,
                          bool _P4, bool _P5, bool _P6, bool _P7>
                struct select_8 {
                        static void v(_T* r, const _T* s0, const _T* s1) {
                                r[0] = _P0 ? s0[0] : s1[0];
                                r[1] = _P1 ? s0[1] : s1[1];
                                r[2] = _P2 ? s0[2] : s1[2];
                                r[3] = _P3 ? s0[3] : s1[3];
                                r[4] = _P4 ? s0[4] : s1[4];
                                r[5] = _P5 ? s0[5] : s1[5];
                                r[6] = _P6 ? s0[6] : s1[6];
                                r[7] = _P7 ? s0[7] : s1[7];
                        }
                };

                template <class _T, int _P0, int _P1, int _P2, int _P3,
                          int _P4, int _P5, int _P6, int _P7>
                struct perm1_8 {
                        static void v(_T* r, const _T* s0) {
                                r[0] = ge_z(_P0) & s0[_P0 & 7] ;
                                r[1] = ge_z(_P1) & s0[_P1 & 7];
                                r[2] = ge_z(_P2) & s0[_P2 & 7];
                                r[3] = ge_z(_P3) & s0[_P3 & 7];
                                r[4] = ge_z(_P4) & s0[_P4 & 7] ;
                                r[5] = ge_z(_P5) & s0[_P5 & 7];
                                r[6] = ge_z(_P6) & s0[_P6 & 7];
                                r[7] = ge_z(_P7) & s0[_P7 & 7];
                        }
                };

                template <class _T, int _P0, int _P1, int _P2, int _P3,
                          int _P4, int _P5, int _P6, int _P7>
                struct perm2_8 {
                        static void v(_T* r, const _T* s0, const _T* s1) {
                                r[0] = ge_z(_P0) &
                                        (_P0>7 ? s1[_P0 & 7] : s0[_P0 & 7]);
                                r[1] = ge_z(_P1) &
                                        (_P1>7 ? s1[_P1 & 7] : s0[_P1 & 7]);
                                r[2] = ge_z(_P2) &
                                        (_P2>7 ? s1[_P2 & 7] : s0[_P2 & 7]);
                                r[3] = ge_z(_P3) &
                                        (_P3>7 ? s1[_P3 & 7] : s0[_P3 & 7]);
                                r[4] = ge_z(_P4) &
                                        (_P4>7 ? s1[_P4 & 7] : s0[_P4 & 7]);
                                r[5] = ge_z(_P5) &
                                        (_P5>7 ? s1[_P5 & 7] : s0[_P5 & 7]);
                                r[6] = ge_z(_P6) &
                                        (_P6>7 ? s1[_P6 & 7] : s0[_P6 & 7]);
                                r[7] = ge_z(_P7) &
                                        (_P7>7 ? s1[_P7 & 7] : s0[_P7 & 7]);
                        }
                };

                template <typename _T, std::size_t _N>
                struct vec_base {
                        enum {
                                size = _N * sizeof(_T)
                        };
                        typedef utvec<size,
                                      cftal::cache_allocator<char, size> > type;
                };
        }


        class v8s16 : public impl::vec_base<std::int16_t, 8>::type {
        public:
                enum { N = 8 };
                typedef std::int16_t element_type;
                typedef typename impl::vec_base<element_type, N>::type
                base_type;
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
        protected:
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

        class v8u16 : public v8s16 {
        public:
                typedef std::uint16_t element_type;
                typedef v8s16 base_type;
		element_type* operator()();
		const element_type* operator()() const;
                v8u16();
                v8u16(const base_type& r);
		v8u16(base_type&& r);
                v8u16(element_type r);
                v8u16(const v8u16& r);
                v8u16(v8u16&& r);
                v8u16(element_type r, bool broadcast);
                v8u16(element_type p00, element_type p01,
                      element_type p02, element_type p03,
                      element_type p04, element_type p05,
                      element_type p06, element_type p07);
                v8u16& operator=(element_type r);
                v8u16& operator=(const v8u16& r);
                v8u16& operator=(v8u16&& r);
                v8u16& operator=(const base_type& r);
                v8u16& operator=(base_type&& r);
                v8u16(const mem::addr_bcast<element_type>& r);
                v8u16(const mem::addr<element_type>& r);
        protected:
                element_type* begin();
                const element_type* begin() const;
        };

        v8u16& operator|= (v8u16& a, const v8u16& b);
        v8u16& operator&= (v8u16& a, const v8u16& b);
        v8u16& operator^= (v8u16& a, const v8u16& b);
        v8u16& operator+= (v8u16& a, const v8u16& b);
        v8u16& operator-= (v8u16& a, const v8u16& b);
        v8u16& operator*= (v8u16& a, const v8u16& b);
        v8u16& operator/= (v8u16& a, const v8u16& b);
        v8u16& operator%= (v8u16& a, const v8u16& b);

        template <std::uint32_t _P>
        v8u16& operator<<= (v8u16& a, const const_u32<_P>& b);
        v8u16& operator<<= (v8u16& a, std::uint32_t b);
        template <std::uint32_t _P>
        v8u16 operator <<(const v8u16& a, const const_u32<_P>& b);
        v8u16 operator <<(const v8u16& a, std::uint32_t b);

        template <std::uint32_t _P>
        v8u16& operator>>= (v8u16& a, const_u32<_P>& b);
        v8u16& operator>>= (v8u16& a, std::uint32_t b);
        template <std::uint32_t _P>
        v8u16 operator >>(const v8u16& a, const const_u32<_P>& b);
        v8u16 operator >>(const v8u16& a, std::uint32_t b);

        v8u16 operator++ (v8u16& a, int);
        v8u16& operator++(v8u16& a);
        v8u16 operator-- (v8u16& a, int);
        v8u16& operator--(v8u16& a);

        v8u16 operator-(const v8u16& a);
	const v8u16& operator+(const v8u16& a);
        v8u16 operator~(const v8u16& a);
        v8u16 operator!(const v8u16& a);

        v8u16 operator| (const v8u16& a, const v8u16& b);
        v8u16 operator|| (const v8u16& a, const v8u16& b);
        v8u16 operator& (const v8u16& a, const v8u16& b);
        v8u16 operator&& (const v8u16& a, const v8u16& b);
        v8u16 operator^(const v8u16& a, const v8u16& b);

        v8u16 operator+ (const v8u16& a, const v8u16& b);
        v8u16 operator- (const v8u16& a, const v8u16& b);
        v8u16 operator* (const v8u16& a, const v8u16& b);
        v8u16 operator/ (const v8u16& a, const v8u16& b);
        v8u16 operator% (const v8u16& a, const v8u16& b);

        v8u16 operator< (const v8u16& a, const v8u16& b);
        v8u16 operator<= (const v8u16& a, const v8u16& b);
        v8u16 operator== (const v8u16& a, const v8u16& b);
        v8u16 operator!= (const v8u16& a, const v8u16& b);
        v8u16 operator>= (const v8u16& a, const v8u16& b);
        v8u16 operator> (const v8u16& a, const v8u16& b);

        v8u16 max(const v8u16& a, const v8u16& b);
        v8u16 min(const v8u16& a, const v8u16& b);
	v8u16 mulh(const v8u16& a, const v8u16& b);

        template < bool _P0, bool _P1, bool _P2, bool _P3,
		   bool _P4, bool _P5, bool _P6, bool _P7 >
        v8u16 select(const v8u16& a, const v8u16& b);
        v8u16 select(const v8u16& msk, const v8u16& on_true,
                     const v8u16& on_false);

        template < int _P0, int _P1, int _P2, int _P3,
		   int _P4, int _P5, int _P6, int _P7 >
        v8u16 permute(const v8u16& a);
        template < int _P0, int _P1, int _P2, int _P3,
		   int _P4, int _P5, int _P6, int _P7 >
        v8u16 permute(const v8u16& a, const v8u16& b);

	template <unsigned _I>
	v8u16 insert(const v8u16& a, typename v8u16::element_type v);
	template <unsigned _I>
	typename v8u16::element_type extract(const v8u16& a);


        class v4s32 : public impl::vec_base<std::int32_t, 4>::type {
        public:
                enum { N = 4 };
                typedef std::int32_t element_type;
                typedef typename impl::vec_base<element_type, N>::type
                base_type;
                element_type* operator()();
                const element_type* operator()() const;
                // no initialization is done here.
                v4s32();
                v4s32(element_type r);
                v4s32(element_type r, bool broad_cast);
                v4s32(element_type i0, element_type i1,
                      element_type i2, element_type i3);
                v4s32(const v4s32& r);
                v4s32(v4s32&& r);
                v4s32& operator=(element_type r);
                v4s32& operator=(const v4s32& r);
                v4s32& operator=(v4s32&& r);

                // memory load operations
                v4s32(const mem::addr_bcast<element_type>& r);
                v4s32(const mem::addr<element_type>& r);
        protected:
                element_type* begin();
                const element_type* begin() const;
        };

        v4s32& operator|= (v4s32& a, const v4s32& b);
        v4s32& operator&= (v4s32& a, const v4s32& b);
        v4s32& operator^= (v4s32& a, const v4s32& b);
        v4s32& operator+= (v4s32& a, const v4s32& b);
        v4s32& operator-= (v4s32& a, const v4s32& b);
        v4s32& operator*= (v4s32& a, const v4s32& b);
        v4s32& operator/= (v4s32& a, const v4s32& b);
        v4s32& operator%= (v4s32& a, const v4s32& b);

        template <std::uint32_t _P>
        v4s32& operator<<= (v4s32& a, const const_u32<_P>& b);
        v4s32& operator<<= (v4s32& a, std::uint32_t b);
        template <std::uint32_t _P>
        v4s32 operator <<(const v4s32& a, const const_u32<_P>& b);
        v4s32 operator <<(const v4s32& a, std::uint32_t b);

        template <std::uint32_t _P>
        v4s32& operator>>= (v4s32& a, const_u32<_P>& b);
        v4s32& operator>>= (v4s32& a, std::uint32_t b);
        template <std::uint32_t _P>
        v4s32 operator >>(const v4s32& a, const const_u32<_P>& b);
        v4s32 operator >>(const v4s32& a, std::uint32_t b);

        v4s32 operator++ (v4s32& a, int);
        v4s32& operator++(v4s32& a);
        v4s32 operator-- (v4s32& a, int);
        v4s32& operator--(v4s32& a);

        v4s32 operator-(const v4s32& a);
        const v4s32& operator+(const v4s32& a);
        v4s32 operator~(const v4s32& a);
        v4s32 operator!(const v4s32& a);

        v4s32 operator| (const v4s32& a, const v4s32& b);
        v4s32 operator|| (const v4s32& a, const v4s32& b);
        v4s32 operator& (const v4s32& a, const v4s32& b);
        v4s32 operator&& (const v4s32& a, const v4s32& b);
        v4s32 operator^(const v4s32& a, const v4s32& b);

        v4s32 operator+ (const v4s32& a, const v4s32& b);
        v4s32 operator- (const v4s32& a, const v4s32& b);
        v4s32 operator* (const v4s32& a, const v4s32& b);
        v4s32 operator/ (const v4s32& a, const v4s32& b);
        v4s32 operator% (const v4s32& a, const v4s32& b);

        v4s32 operator< (const v4s32& a, const v4s32& b);
        v4s32 operator<= (const v4s32& a, const v4s32& b);
        v4s32 operator== (const v4s32& a, const v4s32& b);
        v4s32 operator!= (const v4s32& a, const v4s32& b);
        v4s32 operator>= (const v4s32& a, const v4s32& b);
        v4s32 operator> (const v4s32& a, const v4s32& b);

        // checks the signs
        bool all_signs(const v4s32& a);
        // checks the signs
        bool both_signs(const v4s32& a);
        // checks the signs
        bool no_signs(const v4s32& a);

        v4s32 max(const v4s32& a, const v4s32& b);
        v4s32 min(const v4s32& a, const v4s32& b);
        v4s32 abs(const v4s32& a);
        v4s32 mulh(const v4s32& a, const v4s32& b);

        template < bool _P0, bool _P1, bool _P2, bool _P3 >
        v4s32 select(const v4s32& a, const v4s32& b);
        v4s32 select(const v4s32& msk, const v4s32& on_true,
                     const v4s32& on_false);

        template < int _P0, int _P1, int _P2, int _P3 >
        v4s32 permute(const v4s32& a);
        template < int _P0, int _P1, int _P2, int _P3 >
        v4s32 permute(const v4s32& a, const v4s32& b);

        template <unsigned _I>
        v4s32 insert(const v4s32& a, typename v4s32::element_type v);
        template <unsigned _I>
        typename v4s32::element_type extract(const v4s32& a);

        class v4u32 : public v4s32 {
        public:
                typedef std::uint32_t element_type;
                typedef v4s32 base_type;
		element_type* operator()();
		const element_type* operator()() const;
                v4u32();
                v4u32(const base_type& r);
		v4u32(base_type&& r);
                v4u32(element_type r);
                v4u32(const v4u32& r);
                v4u32(v4u32&& r);
                v4u32(element_type r, bool broadcast);
                v4u32(element_type p00, element_type p01,
                      element_type p02, element_type p03);
                v4u32& operator=(element_type r);
                v4u32& operator=(const v4u32& r);
                v4u32& operator=(v4u32&& r);
                v4u32& operator=(const base_type& r);
                v4u32& operator=(base_type&& r);
                v4u32(const mem::addr_bcast<element_type>& r);
                v4u32(const mem::addr<element_type>& r);
        protected:
                element_type* begin();
                const element_type* begin() const;
        };

        v4u32& operator|= (v4u32& a, const v4u32& b);
        v4u32& operator&= (v4u32& a, const v4u32& b);
        v4u32& operator^= (v4u32& a, const v4u32& b);
        v4u32& operator+= (v4u32& a, const v4u32& b);
        v4u32& operator-= (v4u32& a, const v4u32& b);
        v4u32& operator*= (v4u32& a, const v4u32& b);
        v4u32& operator/= (v4u32& a, const v4u32& b);
        v4u32& operator%= (v4u32& a, const v4u32& b);

        template <std::uint32_t _P>
        v4u32& operator<<= (v4u32& a, const const_u32<_P>& b);
        v4u32& operator<<= (v4u32& a, std::uint32_t b);
        template <std::uint32_t _P>
        v4u32 operator <<(const v4u32& a, const const_u32<_P>& b);
        v4u32 operator <<(const v4u32& a, std::uint32_t b);

        template <std::uint32_t _P>
        v4u32& operator>>= (v4u32& a, const_u32<_P>& b);
        v4u32& operator>>= (v4u32& a, std::uint32_t b);
        template <std::uint32_t _P>
        v4u32 operator >>(const v4u32& a, const const_u32<_P>& b);
        v4u32 operator >>(const v4u32& a, std::uint32_t b);

        v4u32 operator++ (v4u32& a, int);
        v4u32& operator++(v4u32& a);
        v4u32 operator-- (v4u32& a, int);
        v4u32& operator--(v4u32& a);

        v4u32 operator-(const v4u32& a);
	const v4u32& operator+(const v4u32& a);
        v4u32 operator~(const v4u32& a);
        v4u32 operator!(const v4u32& a);

        v4u32 operator| (const v4u32& a, const v4u32& b);
        v4u32 operator|| (const v4u32& a, const v4u32& b);
        v4u32 operator& (const v4u32& a, const v4u32& b);
        v4u32 operator&& (const v4u32& a, const v4u32& b);
        v4u32 operator^(const v4u32& a, const v4u32& b);

        v4u32 operator+ (const v4u32& a, const v4u32& b);
        v4u32 operator- (const v4u32& a, const v4u32& b);
        v4u32 operator* (const v4u32& a, const v4u32& b);
        v4u32 operator/ (const v4u32& a, const v4u32& b);
        v4u32 operator% (const v4u32& a, const v4u32& b);

        v4u32 operator< (const v4u32& a, const v4u32& b);
        v4u32 operator<= (const v4u32& a, const v4u32& b);
        v4u32 operator== (const v4u32& a, const v4u32& b);
        v4u32 operator!= (const v4u32& a, const v4u32& b);
        v4u32 operator>= (const v4u32& a, const v4u32& b);
        v4u32 operator> (const v4u32& a, const v4u32& b);

        v4u32 max(const v4u32& a, const v4u32& b);
        v4u32 min(const v4u32& a, const v4u32& b);
	v4u32 mulh(const v4u32& a, const v4u32& b);

        template < bool _P0, bool _P1, bool _P2, bool _P3 >
        v4u32 select(const v4u32& a, const v4u32& b);
        v4u32 select(const v4u32& msk, const v4u32& on_true,
                     const v4u32& on_false);

        template < int _P0, int _P1, int _P2, int _P3 >
        v4u32 permute(const v4u32& a);
        template < int _P0, int _P1, int _P2, int _P3 >
        v4u32 permute(const v4u32& a, const v4u32& b);

	template <unsigned _I>
	v4u32 insert(const v4u32& a, typename v4u32::element_type v);
	template <unsigned _I>
	typename v4u32::element_type extract(const v4u32& a);

}

// v8s16 implementation
inline
emuvec::v8s16::element_type* emuvec::v8s16::begin()
{
        return static_cast<element_type*>(base_type::vbegin());
}

inline
const emuvec::v8s16::element_type* emuvec::v8s16::begin() const
{
        return static_cast<const element_type*>(base_type::vbegin());
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

template < bool _P0, bool _P1, bool _P2, bool _P3,
           bool _P4, bool _P5, bool _P6, bool _P7 >
emuvec::v8s16 emuvec::select(const v8s16& a, const v8s16& b)
{
        v8s16 r;
        impl::select_8<v8s16::element_type, _P0, _P1, _P2, _P3,
		_P4, _P5, _P6, _P7>::v(r(), a(), b());
        return r;
}

template < int _P0, int _P1, int _P2, int _P3,
           int _P4, int _P5, int _P6, int _P7 >
emuvec::v8s16 emuvec::permute(const v8s16& a)
{
        v8s16 r;
        impl::perm1_8<v8s16::element_type, _P0, _P1, _P2, _P3,
		_P4, _P5, _P6, _P7>::v(r(), a());
        return r;
}

template < int _P0, int _P1, int _P2, int _P3,
           int _P4, int _P5, int _P6, int _P7 >
emuvec::v8s16 emuvec::permute(const v8s16& a, const v8s16& b)
{
        v8s16 r;
        impl::perm2_8<v8s16::element_type, _P0, _P1, _P2, _P3,
		_P4, _P5, _P6, _P7>::v(r(), a(), b());
        return r;
}

template <unsigned _I>
inline
emuvec::v8s16::element_type emuvec::extract(const v8s16& a)
{
	return a()[_I];
}

template <unsigned _I>
emuvec::v8s16 emuvec::insert(const v8s16& a, v8s16::element_type v)
{
	v8s16 r(a);
	r.begin()[_I] =v;
	return r;
}

// v8u16 implementation
inline
emuvec::v8u16::element_type* emuvec::v8u16::begin()
{
        return static_cast<element_type*>(base_type::vbegin());
}

inline
const emuvec::v8u16::element_type* emuvec::v8u16::begin() const
{
        return static_cast<const element_type*>(base_type::vbegin());
}

inline
emuvec::v8u16::element_type* emuvec::v8u16::operator()()
{
        return begin();
}

inline
const emuvec::v8u16::element_type* emuvec::v8u16::operator()() const
{
        return begin();
}

template <unsigned _P>
emuvec::v8u16&
emuvec::operator<<= (v8u16& a, const const_u32< _P >& b)
{
        const int val = b.val;
        impl::v_sl<v8u16::element_type> ot(val);
        impl::v_assign_op(a(), ot, v8u16::N);
        return a;
}

template <unsigned _P>
emuvec::v8u16&
emuvec::operator>>= (v8u16& a, const const_u32< _P >& b)
{
        const int val = b.val;
        impl::v_sr<v8u16::element_type> ot(val);
        impl::v_assign_op(a(), ot, v8u16::N);
        return a;
}

template <unsigned _P>
emuvec::v8u16
emuvec::operator<<(const v8u16& a, const const_u32< _P >& b)
{
        v8u16 r;
        const int val = b.val;
        impl::v_sl<v8u16::element_type> ot(val);
        impl::v_bi_op(r(), a(), ot, v8u16::N);
        return r;
}

template <unsigned _P>
emuvec::v8u16
emuvec::operator>> (const v8u16& a, const const_u32< _P >& b)
{
        v8u16 r;
        const int val = b.val;
        impl::v_sr<v8u16::element_type> ot(val);
        impl::v_bi_op(r(), a(), ot, v8u16::N);
        return r;
}

template < bool _P0, bool _P1, bool _P2, bool _P3,
           bool _P4, bool _P5, bool _P6, bool _P7 >
emuvec::v8u16 emuvec::select(const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::select_8<v8u16::element_type, _P0, _P1, _P2, _P3,
		_P4, _P5, _P6, _P7>::v(r(), a(), b());
        return r;
}

template < int _P0, int _P1, int _P2, int _P3,
           int _P4, int _P5, int _P6, int _P7 >
emuvec::v8u16 emuvec::permute(const v8u16& a)
{
        v8u16 r;
        impl::perm1_8<v8u16::element_type, _P0, _P1, _P2, _P3,
		_P4, _P5, _P6, _P7>::v(r(), a());
        return r;
}

template < int _P0, int _P1, int _P2, int _P3,
           int _P4, int _P5, int _P6, int _P7 >
emuvec::v8u16 emuvec::permute(const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::perm2_8<v8u16::element_type, _P0, _P1, _P2, _P3,
		_P4, _P5, _P6, _P7>::v(r(), a(), b());
        return r;
}

template <unsigned _I>
inline
emuvec::v8u16::element_type emuvec::extract(const v8u16& a)
{
	return a()[_I];
}

template <unsigned _I>
emuvec::v8u16 emuvec::insert(const v8u16& a, v8u16::element_type v)
{
	v8u16 r(a);
	r.begin()[_I] =v;
	return r;
}

// v4s32 implementation
inline
emuvec::v4s32::element_type* emuvec::v4s32::begin()
{
        return static_cast<element_type*>(base_type::vbegin());
}

inline
const emuvec::v4s32::element_type* emuvec::v4s32::begin() const
{
        return static_cast<const element_type*>(base_type::vbegin());
}

inline
emuvec::v4s32::element_type* emuvec::v4s32::operator()()
{
        return begin();
}

inline
const emuvec::v4s32::element_type* emuvec::v4s32::operator()() const
{
        return begin();
}

template <unsigned _P>
emuvec::v4s32&
emuvec::operator<<= (v4s32& a, const const_u32< _P >& b)
{
        const int val = b.val;
        impl::v_sl<v4s32::element_type> ot(val);
        impl::v_assign_op(a(), ot, v4s32::N);
        return a;
}

template <unsigned _P>
emuvec::v4s32&
emuvec::operator>>= (v4s32& a, const const_u32< _P >& b)
{
        const int val = b.val;
        impl::v_sr<v4s32::element_type> ot(val);
        impl::v_assign_op(a(), ot, v4s32::N);
        return a;
}

template <unsigned _P>
emuvec::v4s32
emuvec::operator<<(const v4s32& a, const const_u32< _P >& b)
{
        v4s32 r;
        const int val = b.val;
        impl::v_sl<v4s32::element_type> ot(val);
        impl::v_bi_op(r(), a(), ot, v4s32::N);
        return r;
}

template <unsigned _P>
emuvec::v4s32
emuvec::operator>> (const v4s32& a, const const_u32< _P >& b)
{
        v4s32 r;
        const int val = b.val;
        impl::v_sr<v4s32::element_type> ot(val);
        impl::v_bi_op(r(), a(), ot, v4s32::N);
        return r;
}

template < bool _P0, bool _P1, bool _P2, bool _P3 >
emuvec::v4s32 emuvec::select(const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::select_4<v4s32::element_type, _P0, _P1, _P2, _P3>::
		v(r(), a(), b());
        return r;
}

template < int _P0, int _P1, int _P2, int _P3 >
emuvec::v4s32 emuvec::permute(const v4s32& a)
{
        v4s32 r;
        impl::perm1_4<v4s32::element_type, _P0, _P1, _P2, _P3>::v(r(), a());
        return r;
}

template < int _P0, int _P1, int _P2, int _P3 >
emuvec::v4s32 emuvec::permute(const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::perm2_4<v4s32::element_type, _P0, _P1, _P2, _P3>::
		v(r(), a(), b());
        return r;
}

template <unsigned _I>
inline
emuvec::v4s32::element_type emuvec::extract(const v4s32& a)
{
	return a()[_I];
}

template <unsigned _I>
emuvec::v4s32 emuvec::insert(const v4s32& a, v4s32::element_type v)
{
	v4s32 r(a);
	r.begin()[_I] =v;
	return r;
}

// v4u32 implementation
inline
emuvec::v4u32::element_type* emuvec::v4u32::begin()
{
        return static_cast<element_type*>(base_type::vbegin());
}

inline
const emuvec::v4u32::element_type* emuvec::v4u32::begin() const
{
        return static_cast<const element_type*>(base_type::vbegin());
}

inline
emuvec::v4u32::element_type* emuvec::v4u32::operator()()
{
        return begin();
}

inline
const emuvec::v4u32::element_type* emuvec::v4u32::operator()() const
{
        return begin();
}

template <unsigned _P>
emuvec::v4u32&
emuvec::operator<<= (v4u32& a, const const_u32< _P >& b)
{
        const int val = b.val;
        impl::v_sl<v4u32::element_type> ot(val);
        impl::v_assign_op(a(), ot, v4u32::N);
        return a;
}

template <unsigned _P>
emuvec::v4u32&
emuvec::operator>>= (v4u32& a, const const_u32< _P >& b)
{
        const int val = b.val;
        impl::v_sr<v4u32::element_type> ot(val);
        impl::v_assign_op(a(), ot, v4u32::N);
        return a;
}

template <unsigned _P>
emuvec::v4u32
emuvec::operator<<(const v4u32& a, const const_u32< _P >& b)
{
        v4u32 r;
        const int val = b.val;
        impl::v_sl<v4u32::element_type> ot(val);
        impl::v_bi_op(r(), a(), ot, v4u32::N);
        return r;
}

template <unsigned _P>
emuvec::v4u32
emuvec::operator>> (const v4u32& a, const const_u32< _P >& b)
{
        v4u32 r;
        const int val = b.val;
        impl::v_sr<v4u32::element_type> ot(val);
        impl::v_bi_op(r(), a(), ot, v4u32::N);
        return r;
}

template < bool _P0, bool _P1, bool _P2, bool _P3 >
emuvec::v4u32 emuvec::select(const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::select_4<v4u32::element_type, _P0, _P1, _P2, _P3>::
		v(r(), a(), b());
        return r;
}

template < int _P0, int _P1, int _P2, int _P3 >
emuvec::v4u32 emuvec::permute(const v4u32& a)
{
        v4u32 r;
        impl::perm1_4<v4u32::element_type, _P0, _P1, _P2, _P3>::v(r(), a());
        return r;
}

template < int _P0, int _P1, int _P2, int _P3 >
emuvec::v4u32 emuvec::permute(const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::perm2_4<v4u32::element_type, _P0, _P1, _P2, _P3>::
		v(r(), a(), b());
        return r;
}

template <unsigned _I>
inline
emuvec::v4u32::element_type emuvec::extract(const v4u32& a)
{
	return a()[_I];
}

template <unsigned _I>
emuvec::v4u32 emuvec::insert(const v4u32& a, v4u32::element_type v)
{
	v4u32 r(a);
	r.begin()[_I] =v;
	return r;
}


// Local variables:
// mode: c++
// end:
#endif
