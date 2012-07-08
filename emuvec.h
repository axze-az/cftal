#if !defined (__EMUVEC_H__)
#define __EMUVEC_H__ 1

#include <cftal/heap_array.h>
#include <cftal/allocator.h>
#include <cftal/mem_load.h>

namespace emuvec {

        namespace impl {

                template <typename _T>
                inline
                _T ltz(const _T& j )
                {
                        return j < _T(0) ? -1 : 0;
                }

                inline
                std::uint8_t ltz(std::uint8_t j)
                {
                        return std::int8_t(j) < 0 ? -1 : 0;
                }

                inline
                std::uint16_t ltz(std::uint16_t j)
                {
                        return std::int16_t(j) < 0 ? -1 : 0;
                }

                inline
                std::uint32_t ltz(std::uint32_t j)
                {
                        return std::int32_t(j) < 0 ? -1 : 0;
                }

                inline
                std::uint64_t ltz(std::uint64_t j)
                {
                        return std::int64_t(j) < 0 ? -1 : 0;
                }
        }

        template <typename _T, std::size_t _N>
        class vec {
        public:
                typedef
                cftal::heap_array<_T, _N, cftal::cache_allocator<_T, _N> >
                vec_t;
                typedef _T element_type;
                typedef vec_t vector_type;
                enum { N = _N };
                vec() : _v() {}
                vec(const vec&) = default;
                vec(vec&& r) : _v(r._v) {}
                vec(element_type i) : _v(i) {}
                vec(element_type i, bool broadcast) : _v(i) {
                        if (!broadcast)
                                for (std::size_t j=1; j<_N; ++j)
                                        _v[j] =0;
                }
                vec(element_type i0, element_type i1) : _v() {
                        static_assert(_N == 2, "invalid constructor called");
                        _v[0] = i0;
                        _v[1] = i1;
                }
                vec(element_type i0, element_type i1,
                    element_type i2, element_type i3) : _v() {
                        static_assert(_N == 4, "invalid constructor called");
                        _v[0] = i0;
                        _v[1] = i1;
                        _v[2] = i2;
                        _v[3] = i3;
                }
                vec(element_type i0, element_type i1,
                    element_type i2, element_type i3,
                    element_type i4, element_type i5,
                    element_type i6, element_type i7) : _v() {
                        static_assert(_N == 8, "invalid constructor called");
                        _v[0] = i0;
                        _v[1] = i1;
                        _v[2] = i2;
                        _v[3] = i3;
                        _v[4] = i4;
                        _v[5] = i5;
                        _v[6] = i6;
                        _v[7] = i7;
                }
                vec(const mem::addr<element_type>& r) : _v() {
                        const element_type* p= r();
                        for (std::size_t i; i< _N; ++i)
                                _v[i] = p[i];

                }
                vec(const mem::addr_bcast<element_type>& r) : _v(*r()) {
                }
                vec& operator=(const vec& t) = default;
                vec& operator=(vec&& t) {
                        _v = t._v;
                        return *this;
                }
                vec& operator=(element_type t) {
                        _v = t;
                        return *this;
                }
	protected:
                const element_type& operator[](std::size_t i) const {
                        return _v[i];
                }
                element_type& operator[](std::size_t i) {
                        return _v[i];
                }
	private:
                vec_t _v;
	public:
		// implementation 
#define BI_OP(op, func)                                         \
                static vec func(const vec& a, const vec& b) {   \
                        vec r;                                  \
                        for (std::size_t i=0; i<_N; ++i)        \
                                r[i] = a[i] op b[i];            \
                        return r;                               \
                }
                BI_OP(^, v_xor)
                BI_OP(&, v_and)
                BI_OP(|, v_or)
                BI_OP(+, v_add)
                BI_OP(-, v_sub)
                BI_OP(*, v_mul)
                // division
                static vec v_div(const vec& a, const vec& b) {
                        vec r;
                        for (std::size_t i=0; i<_N; ++i)
                                r[i] = b[i] ? a[i] / b[i] : _T(-1);
                        return r;
                }
                static vec v_mod(const vec& a, const vec& b) {
                        vec r;
                        for (std::size_t i=0; i<_N; ++i)
                                r[i] = b[i] ? a[i] % b[i] : a[i];
                        return r;
                }
                static vec v_log_not(const vec& a) {
                        vec r;
                        for (std::size_t i=0; i<_N; ++i)
                                r[i] = a[i] ? _T(-1) : _T(0);
                        return r;
                }
                static vec v_not(const vec& a) {
                        vec r;
                        for (std::size_t i=0; i<_N; ++i)
                                r[i] = ~a[i];
                        return r;
                }
                static vec v_neg(const vec& a) {
                        vec r;
                        for (std::size_t i=0; i<_N; ++i)
                                r[i] = -a[i];
                        return r;
                }
                static const vec& v_pos(const vec& a) {
                        return a;
                }

#define CMP_OP(op, func)                                                \
                static vec func(const vec& a, const vec& b) {           \
                        vec r;                                          \
                        for (std::size_t i=0; i<_N; ++i)                \
                                r[i] = a[i] op b[i] ? _T(-1) : _T(0);   \
                        return r;                                       \
                }
                CMP_OP(<, v_lt)
                CMP_OP(<=, v_le)
                CMP_OP(==, v_eq)
                CMP_OP(!=, v_ne)
                CMP_OP(>=, v_ge)
                CMP_OP(>, v_gt)

#undef CMP_OP
#undef BI_OP
        };

#define BI_OP(type, op, func)                                           \
        inline type operator op (const type & a, const type& b) {       \
                return type :: func (a, b);                             \
        }

#define MOD_UN_OP(type, op, func)                               \
        inline type& operator op (type & a, const type& b) {    \
                a = type :: func (a, b);                        \
                return a;                                       \
        }

#define UN_OP(type, op, func)                           \
        inline type operator op (const type & a) {      \
                return type :: func(a);                 \
        }

#define GEN_OPS(type)                           \
        UN_OP(type, !, v_log_not)               \
        UN_OP(type, ~, v_not)                   \
        UN_OP(type, -, v_neg)                   \
        UN_OP(type, +, v_pos)                   \
        BI_OP(type, <, v_lt)                    \
        BI_OP(type, <=, v_le)                   \
        BI_OP(type, ==, v_eq)                   \
        BI_OP(type, !=, v_ne)                   \
        BI_OP(type, >=, v_ge)                   \
        BI_OP(type, >, v_gt)                    \
        BI_OP(type, & , v_and)                  \
        MOD_UN_OP(type, &=, v_and)              \
        BI_OP(type, && , v_and)                 \
        BI_OP(type, | , v_or)                   \
        MOD_UN_OP(type, |=, v_or)               \
        BI_OP(type, || , v_or)                  \
        BI_OP(type, ^ , v_xor)                  \
        MOD_UN_OP(type, ^=, v_xor)



// #undef GEN_OPS
	// #define GEN_OPS(type)


        typedef vec<std::int16_t, 8> v8s16;
        GEN_OPS(v8s16)

        typedef vec<std::uint16_t, 8> v8u16;
        GEN_OPS(v8u16)

        typedef vec<std::int32_t, 4> v4s32;
        GEN_OPS(v4s32)

        typedef vec<std::uint32_t, 4> v4u32;
        GEN_OPS(v4u32)

#if 0
        inline
        v8s16 operator|(const v8s16& a, const v8s16& b) {
                return v8s16::v_or(a, b);
        }
        inline
        v8s16& operator|=(v8s16& a, const v8s16& b) {
                a = v8s16::v_or(a, b);
                return a;
        }
#endif

#undef GEN_OPS
#undef UN_OP
#undef MOD_BI_OP
#undef BI_OP

}

// Local variables:
// mode: c++
// end:
#endif
