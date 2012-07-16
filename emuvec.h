#if !defined (__EMUVEC_H__)
#define __EMUVEC_H__ 1

#include <cftal/config.h>
#include <cftal/mem_load.h>
#include <cftal/emuvec_impl.h>
#include <cftal/emuvec_impl_ops.h>

namespace emuvec {

        // constants consisting of 1 uint32_t
        template <std::uint32_t _P>
        struct const_u32 {
                static
                const std::uint32_t val = _P;
        };

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

	class v4f32 : public impl::vec_base<float,4>::type {
	public:
		enum { N = 4 };
		typedef float element_type;
		typedef typename impl::vec_base<float,4>::type
		base_type;
		element_type* operator()();
		const element_type* operator()() const;
		v4f32();
		v4f32(element_type r);
		v4f32(element_type r, bool broadcast);
		v4f32(element_type p00, element_type p01,
		      element_type p02, element_type p03);
		v4f32(const v4f32& r);
		v4f32(v4f32&& r);
		v4f32& operator=(element_type r);
		v4f32& operator=(const v4f32& r);
		v4f32& operator=(v4f32&& r);
		v4f32(const mem::addr_bcast<element_type>& r);
		v4f32(const mem::addr<element_type>& r);
	private:
		element_type* begin();
		const element_type* begin() const;
	};

	v4f32& operator|= (v4f32& a, const v4f32& b);
	v4f32& operator&= (v4f32& a, const v4f32& b);
	v4f32& operator^= (v4f32& a, const v4f32& b);
	v4f32& operator+= (v4f32& a, const v4f32& b);
	v4f32& operator-= (v4f32& a, const v4f32& b);
	v4f32& operator*= (v4f32& a, const v4f32& b);
	v4f32& operator/= (v4f32& a, const v4f32& b);

	v4f32 operator++ (v4f32& a, int);
	v4f32& operator++(v4f32& a);
	v4f32 operator-- (v4f32& a, int);
	v4f32& operator--(v4f32& a);

	v4f32 operator-(const v4f32& a);
	const v4f32& operator+(const v4f32& a);
	v4f32 operator~(const v4f32& a);
	v4f32 operator!(const v4f32& a);

	v4f32 operator| (const v4f32& a, const v4f32& b);
	v4f32 operator|| (const v4f32& a, const v4f32& b);
	v4f32 operator& (const v4f32& a, const v4f32& b);
	v4f32 operator&& (const v4f32& a, const v4f32& b);
	v4f32 operator^(const v4f32& a, const v4f32& b);

	v4f32 operator+ (const v4f32& a, const v4f32& b);
	v4f32 operator- (const v4f32& a, const v4f32& b);
	v4f32 operator* (const v4f32& a, const v4f32& b);
	v4f32 operator/ (const v4f32& a, const v4f32& b);

	v4f32 operator< (const v4f32& a, const v4f32& b);
	v4f32 operator<= (const v4f32& a, const v4f32& b);
	v4f32 operator== (const v4f32& a, const v4f32& b);
	v4f32 operator!= (const v4f32& a, const v4f32& b);
	v4f32 operator>= (const v4f32& a, const v4f32& b);
	v4f32 operator> (const v4f32& a, const v4f32& b);

	// checks the signs
	bool all_signs(const v4f32& a);
	// checks the signs
	bool both_signs(const v4f32& a);
	// checks the signs
	bool no_signs(const v4f32& a);

	v4f32 max(const v4f32& a, const v4f32& b);
	v4f32 min(const v4f32& a, const v4f32& b);
	v4f32 abs(const v4f32& a);
	v4f32 sqrt(const v4f32& a);

	v4f32 rint(const v4f32& a);
	v4f32 floor(const v4f32& a);
	v4f32 ceil(const v4f32& a);
	v4f32 trunc(const v4f32& a);

	template <bool _P0, bool _P1, bool _P2, bool _P3>
	v4f32 select(const v4f32& a, const v4f32& b);
	v4f32 select(const v4f32& msk, const v4f32& on_true,
		     const v4f32& on_false);

	template <int _P0, int _P1, int _P2, int _P3 >
	v4f32 permute(const v4f32& a);
	template <int _P0, int _P1, int _P2, int _P3 >
	v4f32 permute(const v4f32& a, const v4f32& b);

	template <unsigned _I>
	v4f32 insert(const v4f32& a, typename v4f32::element_type v);
	template <unsigned _I>
	typename v4f32::element_type extract(const v4f32& a);

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
        r()[_I] =v;
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
        r()[_I] =v;
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
        r()[_I] =v;
        return r;
}

// v4f32 implementation
inline
emuvec::v4f32::element_type* emuvec::v4f32::begin()
{
        return static_cast<element_type*>(base_type::vbegin());
}

inline
const emuvec::v4f32::element_type* emuvec::v4f32::begin() const
{
        return static_cast<const element_type*>(base_type::vbegin());
}

inline
emuvec::v4f32::element_type* emuvec::v4f32::operator()()
{
        return begin();
}

inline
const emuvec::v4f32::element_type* emuvec::v4f32::operator()() const
{
        return begin();
}

template < bool _P0, bool _P1, bool _P2, bool _P3 >
emuvec::v4f32 emuvec::select(const v4f32& a, const v4f32& b)
{
        v4f32 r;
        impl::select_4<v4f32::element_type, _P0, _P1, _P2, _P3>::
                v(r(), a(), b());
        return r;
}

template < int _P0, int _P1, int _P2, int _P3 >
emuvec::v4f32 emuvec::permute(const v4f32& a)
{
        v4f32 r;
        impl::perm1_4<v4f32::element_type, _P0, _P1, _P2, _P3>::v(r(), a());
        return r;
}

template < int _P0, int _P1, int _P2, int _P3 >
emuvec::v4f32 emuvec::permute(const v4f32& a, const v4f32& b)
{
        v4f32 r;
        impl::perm2_4<v4f32::element_type, _P0, _P1, _P2, _P3>::
                v(r(), a(), b());
        return r;
}

template <unsigned _I>
inline
emuvec::v4f32::element_type emuvec::extract(const v4f32& a)
{
        return a()[_I];
}

template <unsigned _I>
emuvec::v4f32 emuvec::insert(const v4f32& a, v4f32::element_type v)
{
        v4f32 r(a);
        r()[_I] =v;
        return r;
}

// Local variables:
// mode: c++
// end:
#endif
