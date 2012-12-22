#if !defined (__EMUVEC_IMPL_H__)
#define __EMUVEC_IMPL_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <cftal/allocator.h>
#include <cstring>
#include <type_traits>

namespace emuvec {

        namespace impl {

		template <typename _S>
		struct __def_lt_z {
			static _S v(const _S& t) {
				return _S(t < _S(0) ? _S(-1) : _S(0)); 
			}
		};

		template <typename _I>
		struct __int_lt_z {
			static _I v(const _I& t) {
				typedef typename std::make_signed<_I>::type _S;
				_S s(t);
				return __def_lt_z<_S>::v(s);
			}
		};

                // returns -1 if lt zero
                template <typename _T>
                inline
                _T lt_z(const _T& j )
                {
                        typedef typename std::conditional<
                                std::is_integral<_T>::value == true,
				__int_lt_z<_T>, 
                                __def_lt_z<_T> >::type type;
			return type::v(j);
                }

                // returns -1 if ge zero
                template <typename _T>
                inline
                _T ge_z(const _T& j) {
                        return ~lt_z(j);
                }

                template <typename _S>
                struct __def_get_signs_32  {
                        static uint32_t v(const _S* s, std::size_t n) {
                                if (n>32)
                                        std::abort();
                                uint32_t r(0), m(1);
                                for (std::size_t i=0; i<n; ++i, m<<=1) {
                                        uint32_t mi( s[i] < _S(0) ? m : 0);
                                        r |= mi;
                                }
                                return r;
                        }
                };

                template <typename _U>
                struct __int_get_signs_32 {
                        static uint32_t v(const _U* p, std::size_t n) {
                                typedef typename std::make_signed<_U>::type _S;
                                const _S* s = static_cast<const _S*>(p);
                                return __def_get_signs_32<_S>::v(s, n);
                        }
                };


                template <typename _T>
		inline
                uint32_t get_signs_32(const _T* p, std::size_t n)
                {
                        typedef typename std::conditional<
                                std::is_integral<_T>::value == true,
				__int_get_signs_32<_T>, 
                                __def_get_signs_32<_T> >::type type;
			return type::v(p, n);
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
				const uint64_t* su=
					static_cast<const uint64_t*>(s);
				uint64_t* du=
					static_cast<uint64_t*>(d);
				du[0] = su[0];
				du[1] = su[1];
				return d;
			}
		};

		// vector with untyped memory, works only
		// with stateless allocators.
		template <std::size_t _N,  class _A = std::allocator<char> >
		class utvec : private _A {
			typedef char aligned_char __attribute__((aligned(16)));
			
			aligned_char* _v;
			aligned_char* alloc_() {
				_A* a= static_cast<_A*>(this);
				return static_cast<aligned_char*>(
					a->allocate(_N));
			}
			void free_(aligned_char* p) {
				if (p) {
					_A* a= static_cast<_A*>(this);
					a->deallocate(p, _N);
				}
			}
			aligned_char* copy_(aligned_char* dst, const void* src) {
				if (src != nullptr) {
					if (dst==nullptr)
						dst = alloc_();
					mem_cpy<_N>::v(dst, src);
				} else {
					free_(dst);
					dst = nullptr;
				}
				return dst;
			}
		protected:
			_A& get_allocator() {
				return *this;
			}
			void* vbegin() {
				if (_v == nullptr)
					_v = alloc_();
				return _v;
			}
			const void* vbegin() const {
				return _v == nullptr ? _d : _v;
			}
			void swap(utvec& r) {
				std::swap(_v, r._v);
			}
			utvec() : _A(), _v(nullptr) {
			}
			utvec(const utvec& r) : _A(r), _v(copy_(nullptr, r._v)) {
			}
			utvec(utvec&& r) : _A(std::move(r)), _v(nullptr) {
				swap(r);
			}
			utvec& operator=(const utvec& r) {
				if (&r != this)
					_v=copy_(_v, r._v);
				return *this;
			}
			utvec& operator=(utvec&& r) {
				swap(r);
				return *this;
			}
			~utvec() {
				free_(_v);
			}
		private:
			static const aligned_char _d[_N];
		};

		template <std::size_t _N,  class _A>
		const typename utvec<_N,_A>::aligned_char 
		utvec<_N,_A>::_d[_N]={0};

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

		template <class _T, int _N, int _P>
		struct perm1 {
			static _T v(const _T* s0) {
				return (_P< 0) ? _T(0) : s0[_P & (_N-1)];
			}
		};
		
		template <class _T, int _P, int _N>
		struct perm2 { 
			static _T v(const _T* s0, const _T* s1) {
				return (_P < _N) ? 
					perm1<_T, _P, _N>::v(s0) :
					s1[ _P & (_N-1)];
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
                                r[0] = perm1<_T, 2, _P0>::v(s0);
                                r[1] = perm1<_T, 2, _P1>::v(s0);
                        }
                };

                template <class _T, int _P0, int _P1>
                struct perm2_2 {
                        static void v(_T* r, const _T* s0, const _T* s1) {
                                r[0] = perm2<_T, 2, _P0>::v(s0, s1);
                                r[1] = perm2<_T, 2, _P1>::v(s0, s1);
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
                                r[0] = perm1<_T, 4, _P0>::v(s0);
                                r[1] = perm1<_T, 4, _P1>::v(s0);
                                r[2] = perm1<_T, 4, _P2>::v(s0);
                                r[3] = perm1<_T, 4, _P3>::v(s0);
                        }
                };

                template <class _T, int _P0, int _P1, int _P2, int _P3>
                struct perm2_4 {
                        static void v(_T* r, const _T* s0, const _T* s1) {
                                r[0] = perm2<_T, 4, _P0>::v(s0, s1);
                                r[1] = perm2<_T, 4, _P1>::v(s0, s1);
                                r[2] = perm2<_T, 4, _P2>::v(s0, s1);
                                r[3] = perm2<_T, 4, _P3>::v(s0, s1);
			}
                };

                template <class _T, 
			  bool _P0, bool _P1, bool _P2, bool _P3,
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

                template <class _T, 
			  int _P0, int _P1, int _P2, int _P3,
                          int _P4, int _P5, int _P6, int _P7>
                struct perm1_8 {
                        static void v(_T* r, const _T* s0) {
                                r[0] = perm1<_T, 8, _P0>::v(s0);
                                r[1] = perm1<_T, 8, _P1>::v(s0);
                                r[2] = perm1<_T, 8, _P2>::v(s0);
                                r[3] = perm1<_T, 8, _P3>::v(s0);
                                r[4] = perm1<_T, 8, _P4>::v(s0);
                                r[5] = perm1<_T, 8, _P5>::v(s0);
                                r[6] = perm1<_T, 8, _P6>::v(s0);
                                r[7] = perm1<_T, 8, _P7>::v(s0);
                        }
                };

                template <class _T, 
			  int _P0, int _P1, int _P2, int _P3,
                          int _P4, int _P5, int _P6, int _P7>
                struct perm2_8 {
                        static void v(_T* r, const _T* s0, const _T* s1) {
                                r[0] = perm2<_T, 8, _P0>::v(s0, s1);
                                r[1] = perm2<_T, 8, _P1>::v(s0, s1);
                                r[2] = perm2<_T, 8, _P2>::v(s0, s1);
                                r[3] = perm2<_T, 8, _P3>::v(s0, s1);
                                r[4] = perm2<_T, 8, _P4>::v(s0, s1);
                                r[5] = perm2<_T, 8, _P5>::v(s0, s1);
                                r[6] = perm2<_T, 8, _P6>::v(s0, s1);
                                r[7] = perm2<_T, 8, _P7>::v(s0, s1);
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
}

// Local variables:
// mode: c++
// end:
#endif
