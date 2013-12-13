#if !defined (__EMUVEC_H__)
#define __EMUVEC_H__ 1

#include <cftal/config.h>
#include <cftal/mem_load.h>
#include <cftal/emuvec_impl.h>
#include <cftal/emuvec_impl_ops.h>
#include <cftal/emuvec_mask.h>


namespace emuvec {

        template <class _T>
        struct arg {
                using type = const _T&;
        };

        // constants consisting of 1 uint32_t
        template <uint32_t _P>
        struct const_u32 {
                static
                constexpr uint32_t val = _P;
        };

        namespace const_shift {

                static const const_u32<0> _0;
                static const const_u32<1> _1;
                static const const_u32<2> _2;
                static const const_u32<3> _3;
                static const const_u32<4> _4;
                static const const_u32<5> _5;
                static const const_u32<6> _6;
                static const const_u32<7> _7;
                static const const_u32<8> _8;
                static const const_u32<9> _9;

                static const const_u32<10> _10;
                static const const_u32<11> _11;
                static const const_u32<12> _12;
                static const const_u32<13> _13;
                static const const_u32<14> _14;
                static const const_u32<15> _15;
                static const const_u32<16> _16;
                static const const_u32<17> _17;
                static const const_u32<18> _18;
                static const const_u32<19> _19;

                static const const_u32<20> _20;
                static const const_u32<21> _21;
                static const const_u32<22> _22;
                static const const_u32<23> _23;
                static const const_u32<24> _24;
                static const const_u32<25> _25;
                static const const_u32<26> _26;
                static const const_u32<27> _27;
                static const const_u32<28> _28;
                static const const_u32<29> _29;

                static const const_u32<30> _30;
                static const const_u32<31> _31;
                static const const_u32<32> _32;
                static const const_u32<33> _33;
                static const const_u32<34> _34;
                static const const_u32<35> _35;
                static const const_u32<36> _36;
                static const const_u32<37> _37;
                static const const_u32<38> _38;
                static const const_u32<39> _39;

                static const const_u32<40> _40;
                static const const_u32<41> _41;
                static const const_u32<42> _42;
                static const const_u32<43> _43;
                static const const_u32<44> _44;
                static const const_u32<45> _45;
                static const const_u32<46> _46;
                static const const_u32<47> _47;
                static const const_u32<48> _48;
                static const const_u32<49> _49;

                static const const_u32<50> _50;
                static const const_u32<51> _51;
                static const const_u32<52> _52;
                static const const_u32<53> _53;
                static const const_u32<54> _54;
                static const const_u32<55> _55;
                static const const_u32<56> _56;
                static const const_u32<57> _57;
                static const const_u32<58> _58;
                static const const_u32<59> _59;

                static const const_u32<60> _60;
                static const const_u32<61> _61;
                static const const_u32<62> _62;
                static const const_u32<63> _63;
        }


        class v8s16 : public impl::vec_base<int16_t, 8>::type {
        public:
                enum { N = 8 };
                typedef int16_t element_type;
                typedef typename impl::vec_base<element_type, N>::type
                base_type;
                element_type* operator()();
                const element_type* operator()() const;
                // no initialization is done here.
                v8s16() = default;
                v8s16(element_type r);
                v8s16(element_type r, bool broad_cast);
                v8s16(element_type i0, element_type i1,
                      element_type i2, element_type i3,
                      element_type i4, element_type i5,
                      element_type i6, element_type i7);
                v8s16(const v8s16& r) = default;
                v8s16(v8s16&& r) = default;
                v8s16& operator=(element_type r);
                v8s16& operator=(const v8s16& r) = default;
                v8s16& operator=(v8s16&& r) = default;
                // memory load operations
                v8s16(const mem::addr_bcast<element_type>& r);
                v8s16(const mem::addr<element_type>& r);
                masked_vec<v8s16> operator()(const mask<v8s16>& m);
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

        template <uint32_t _P>
        v8s16& operator<<= (v8s16& a, const const_u32<_P>& b);
        v8s16& operator<<= (v8s16& a, uint32_t b);
        template <uint32_t _P>
        v8s16 operator <<(const v8s16& a, const const_u32<_P>& b);
        v8s16 operator <<(const v8s16& a, uint32_t b);

        template <uint32_t _P>
        v8s16& operator>>= (v8s16& a, const const_u32<_P>& b);
        v8s16& operator>>= (v8s16& a, uint32_t b);
        template <uint32_t _P>
        v8s16 operator >>(const v8s16& a, const const_u32<_P>& b);
        v8s16 operator >>(const v8s16& a, uint32_t b);

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
        v8s16 mul_hi(const v8s16& a, const v8s16& b);

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
                typedef uint16_t element_type;
                typedef v8s16 base_type;
                element_type* operator()();
                const element_type* operator()() const;
                v8u16() = default;
                v8u16(const base_type& r);
                v8u16(base_type&& r);
                v8u16(element_type r);
                v8u16(const v8u16& r) = default;
                v8u16(v8u16&& r) = default;
                v8u16(element_type r, bool broadcast);
                v8u16(element_type p00, element_type p01,
                      element_type p02, element_type p03,
                      element_type p04, element_type p05,
                      element_type p06, element_type p07);
                v8u16& operator=(element_type r);
                v8u16& operator=(const v8u16& r) = default;
                v8u16& operator=(v8u16&& r) = default;
                v8u16& operator=(const base_type& r);
                v8u16& operator=(base_type&& r);
                v8u16(const mem::addr_bcast<element_type>& r);
                v8u16(const mem::addr<element_type>& r);
                masked_vec<v8u16> operator()(const mask<v8u16>& m);
        private:
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

        template <uint32_t _P>
        v8u16& operator<<= (v8u16& a, const const_u32<_P>& b);
        v8u16& operator<<= (v8u16& a, uint32_t b);
        template <uint32_t _P>
        v8u16 operator <<(const v8u16& a, const const_u32<_P>& b);
        v8u16 operator <<(const v8u16& a, uint32_t b);

        template <uint32_t _P>
        v8u16& operator>>= (v8u16& a, const const_u32<_P>& b);
        v8u16& operator>>= (v8u16& a, uint32_t b);
        template <uint32_t _P>
        v8u16 operator >>(const v8u16& a, const const_u32<_P>& b);
        v8u16 operator >>(const v8u16& a, uint32_t b);

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
        v8u16 mul_hi(const v8u16& a, const v8u16& b);

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


        class v4s32 : public impl::vec_base<int32_t, 4>::type {
        public:
                enum { N = 4 };
                typedef int32_t element_type;
                typedef typename impl::vec_base<element_type, N>::type
                base_type;
                element_type* operator()();
                const element_type* operator()() const;
                // no initialization is done here.
                v4s32() = default;
                v4s32(element_type r);
                v4s32(element_type r, bool broad_cast);
                v4s32(element_type i0, element_type i1,
                      element_type i2, element_type i3);
                v4s32(const v4s32& r) = default;
                v4s32(v4s32&& r) = default;
                v4s32& operator=(element_type r);
                v4s32& operator=(const v4s32& r) = default;
                v4s32& operator=(v4s32&& r) = default;
                // memory load operations
                v4s32(const mem::addr_bcast<element_type>& r);
                v4s32(const mem::addr<element_type>& r);
                v4s32(const mem::aligned::addr<element_type>& r);
                v4s32(const mem::unaligned::addr<element_type>& r);
                masked_vec<v4s32> operator()(const mask<v4s32>& m);

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

        template <uint32_t _P>
        v4s32& operator<<= (v4s32& a, const const_u32<_P>& b);
        v4s32& operator<<= (v4s32& a, uint32_t b);
        template <uint32_t _P>
        v4s32 operator <<(const v4s32& a, const const_u32<_P>& b);
        v4s32 operator <<(const v4s32& a, uint32_t b);

        template <uint32_t _P>
        v4s32& operator>>= (v4s32& a, const const_u32<_P>& b);
        v4s32& operator>>= (v4s32& a, uint32_t b);
        template <uint32_t _P>
        v4s32 operator >>(const v4s32& a, const const_u32<_P>& b);
        v4s32 operator >>(const v4s32& a, uint32_t b);

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
        v4s32 mul_hi(const v4s32& a, const v4s32& b);

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
                typedef uint32_t element_type;
                typedef v4s32 base_type;
                element_type* operator()();
                const element_type* operator()() const;
                v4u32() = default;
                v4u32(const base_type& r);
                v4u32(base_type&& r);
                v4u32(element_type r);
                v4u32(const v4u32& r) = default;
                v4u32(v4u32&& r) = default;
                v4u32(element_type r, bool broadcast);
                v4u32(element_type p00, element_type p01,
                      element_type p02, element_type p03);
                v4u32& operator=(element_type r);
                v4u32& operator=(const v4u32& r) = default;
                v4u32& operator=(v4u32&& r) = default;
                v4u32& operator=(const base_type& r);
                v4u32& operator=(base_type&& r);
                v4u32(const mem::addr_bcast<element_type>& r);
                v4u32(const mem::addr<element_type>& r);
                masked_vec<v4u32> operator()(const mask<v4u32>& m);
        private:
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

        template <uint32_t _P>
        v4u32& operator<<= (v4u32& a, const const_u32<_P>& b);
        v4u32& operator<<= (v4u32& a, uint32_t b);
        template <uint32_t _P>
        v4u32 operator <<(const v4u32& a, const const_u32<_P>& b);
        v4u32 operator <<(const v4u32& a, uint32_t b);

        template <uint32_t _P>
        v4u32& operator>>= (v4u32& a, const const_u32<_P>& b);
        v4u32& operator>>= (v4u32& a, uint32_t b);
        template <uint32_t _P>
        v4u32 operator >>(const v4u32& a, const const_u32<_P>& b);
        v4u32 operator >>(const v4u32& a, uint32_t b);

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
        v4u32 mul_hi(const v4u32& a, const v4u32& b);

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

        class v2s64 : public impl::vec_base<int64_t, 2>::type {
        public:
                enum { N = 2 };
                typedef int64_t element_type;
                typedef typename impl::vec_base<element_type, N>::type
                base_type;
                element_type* operator()();
                const element_type* operator()() const;
                // no initialization is done here.
                v2s64() = default;
                v2s64(element_type r);
                v2s64(element_type r, bool broad_cast);
                v2s64(element_type i0, element_type i1);
                v2s64(const v2s64& r) = default;
                v2s64(v2s64&& r) = default;
                v2s64& operator=(element_type r);
                v2s64& operator=(const v2s64& r) = default;
                v2s64& operator=(v2s64&& r) = default;
                // memory load operations
                v2s64(const mem::addr_bcast<element_type>& r);
                v2s64(const mem::addr<element_type>& r);
                masked_vec<v2s64> operator()(const mask<v2s64>& m);
        private:
                element_type* begin();
                const element_type* begin() const;
        };

        v2s64& operator|= (v2s64& a, const v2s64& b);
        v2s64& operator&= (v2s64& a, const v2s64& b);
        v2s64& operator^= (v2s64& a, const v2s64& b);
        v2s64& operator+= (v2s64& a, const v2s64& b);
        v2s64& operator-= (v2s64& a, const v2s64& b);
        v2s64& operator*= (v2s64& a, const v2s64& b);
        v2s64& operator/= (v2s64& a, const v2s64& b);
        v2s64& operator%= (v2s64& a, const v2s64& b);

        template <uint32_t _P>
        v2s64& operator<<= (v2s64& a, const const_u32<_P>& b);
        v2s64& operator<<= (v2s64& a, uint64_t b);
        template <uint32_t _P>
        v2s64 operator <<(const v2s64& a, const const_u32<_P>& b);
        v2s64 operator <<(const v2s64& a, uint64_t b);

        template <uint32_t _P>
        v2s64& operator>>= (v2s64& a, const const_u32<_P>& b);
        v2s64& operator>>= (v2s64& a, uint64_t b);
        template <uint32_t _P>
        v2s64 operator >>(const v2s64& a, const const_u32<_P>& b);
        v2s64 operator >>(const v2s64& a, uint64_t b);

        v2s64 operator++ (v2s64& a, int);
        v2s64& operator++(v2s64& a);
        v2s64 operator-- (v2s64& a, int);
        v2s64& operator--(v2s64& a);

        v2s64 operator-(const v2s64& a);
        const v2s64& operator+(const v2s64& a);
        v2s64 operator~(const v2s64& a);
        v2s64 operator!(const v2s64& a);

        v2s64 operator| (const v2s64& a, const v2s64& b);
        v2s64 operator|| (const v2s64& a, const v2s64& b);
        v2s64 operator& (const v2s64& a, const v2s64& b);
        v2s64 operator&& (const v2s64& a, const v2s64& b);
        v2s64 operator^(const v2s64& a, const v2s64& b);

        v2s64 operator+ (const v2s64& a, const v2s64& b);
        v2s64 operator- (const v2s64& a, const v2s64& b);
        v2s64 operator* (const v2s64& a, const v2s64& b);
        v2s64 operator/ (const v2s64& a, const v2s64& b);
        v2s64 operator% (const v2s64& a, const v2s64& b);

        v2s64 operator< (const v2s64& a, const v2s64& b);
        v2s64 operator<= (const v2s64& a, const v2s64& b);
        v2s64 operator== (const v2s64& a, const v2s64& b);
        v2s64 operator!= (const v2s64& a, const v2s64& b);
        v2s64 operator>= (const v2s64& a, const v2s64& b);
        v2s64 operator> (const v2s64& a, const v2s64& b);

        // checks the signs
        bool all_signs(const v2s64& a);
        // checks the signs
        bool both_signs(const v2s64& a);
        // checks the signs
        bool no_signs(const v2s64& a);

        v2s64 max(const v2s64& a, const v2s64& b);
        v2s64 min(const v2s64& a, const v2s64& b);
        v2s64 abs(const v2s64& a);
        v2s64 mul_hi(const v2s64& a, const v2s64& b);

        template < bool _P0, bool _P1>
        v2s64 select(const v2s64& a, const v2s64& b);
        v2s64 select(const v2s64& msk, const v2s64& on_true,
                     const v2s64& on_false);

        template < int _P0, int _P1 >
        v2s64 permute(const v2s64& a);
        template < int _P0, int _P1 >
        v2s64 permute(const v2s64& a, const v2s64& b);

        template <unsigned _I>
        v2s64 insert(const v2s64& a, typename v2s64::element_type v);
        template <unsigned _I>
        typename v2s64::element_type extract(const v2s64& a);

        class v2u64 : public v2s64 {
        public:
                typedef uint64_t element_type;
                typedef v2s64 base_type;
                element_type* operator()();
                const element_type* operator()() const;
                v2u64() = default;
                v2u64(const base_type& r);
                v2u64(base_type&& r);
                v2u64(element_type r);
                v2u64(const v2u64& r) = default;
                v2u64(v2u64&& r) = default;
                v2u64(element_type r, bool broadcast);
                v2u64(element_type p00, element_type p01);
                v2u64& operator=(element_type r);
                v2u64& operator=(const v2u64& r) = default;
                v2u64& operator=(v2u64&& r) = default;
                v2u64& operator=(const base_type& r);
                v2u64& operator=(base_type&& r);
                v2u64(const mem::addr_bcast<element_type>& r);
                v2u64(const mem::addr<element_type>& r);
                masked_vec<v2u64> operator()(const mask<v2u64>& m);
        private:
                element_type* begin();
                const element_type* begin() const;
        };

        v2u64& operator|= (v2u64& a, const v2u64& b);
        v2u64& operator&= (v2u64& a, const v2u64& b);
        v2u64& operator^= (v2u64& a, const v2u64& b);
        v2u64& operator+= (v2u64& a, const v2u64& b);
        v2u64& operator-= (v2u64& a, const v2u64& b);
        v2u64& operator*= (v2u64& a, const v2u64& b);
        v2u64& operator/= (v2u64& a, const v2u64& b);
        v2u64& operator%= (v2u64& a, const v2u64& b);

        template <uint32_t _P>
        v2u64& operator<<= (v2u64& a, const const_u32<_P>& b);
        v2u64& operator<<= (v2u64& a, uint64_t b);
        template <uint32_t _P>
        v2u64 operator <<(const v2u64& a, const const_u32<_P>& b);
        v2u64 operator <<(const v2u64& a, uint64_t b);

        template <uint32_t _P>
        v2u64& operator>>= (v2u64& a, const const_u32<_P>& b);
        v2u64& operator>>= (v2u64& a, uint64_t b);
        template <uint32_t _P>
        v2u64 operator >>(const v2u64& a, const const_u32<_P>& b);
        v2u64 operator >>(const v2u64& a, uint64_t b);

        v2u64 operator++ (v2u64& a, int);
        v2u64& operator++(v2u64& a);
        v2u64 operator-- (v2u64& a, int);
        v2u64& operator--(v2u64& a);

        v2u64 operator-(const v2u64& a);
        const v2u64& operator+(const v2u64& a);
        v2u64 operator~(const v2u64& a);
        v2u64 operator!(const v2u64& a);

        v2u64 operator| (const v2u64& a, const v2u64& b);
        v2u64 operator|| (const v2u64& a, const v2u64& b);
        v2u64 operator& (const v2u64& a, const v2u64& b);
        v2u64 operator&& (const v2u64& a, const v2u64& b);
        v2u64 operator^(const v2u64& a, const v2u64& b);

        v2u64 operator+ (const v2u64& a, const v2u64& b);
        v2u64 operator- (const v2u64& a, const v2u64& b);
        v2u64 operator* (const v2u64& a, const v2u64& b);
        v2u64 operator/ (const v2u64& a, const v2u64& b);
        v2u64 operator% (const v2u64& a, const v2u64& b);

        v2u64 operator< (const v2u64& a, const v2u64& b);
        v2u64 operator<= (const v2u64& a, const v2u64& b);
        v2u64 operator== (const v2u64& a, const v2u64& b);
        v2u64 operator!= (const v2u64& a, const v2u64& b);
        v2u64 operator>= (const v2u64& a, const v2u64& b);
        v2u64 operator> (const v2u64& a, const v2u64& b);

        v2u64 max(const v2u64& a, const v2u64& b);
        v2u64 min(const v2u64& a, const v2u64& b);
        v2u64 mul_hi(const v2u64& a, const v2u64& b);

        template < bool _P0, bool _P1>
        v2u64 select(const v2u64& a, const v2u64& b);
        v2u64 select(const v2u64& msk, const v2u64& on_true,
                     const v2u64& on_false);

        template < int _P0, int _P1>
        v2u64 permute(const v2u64& a);
        template < int _P0, int _P1>
        v2u64 permute(const v2u64& a, const v2u64& b);

        template <unsigned _I>
        v2u64 insert(const v2u64& a, typename v2u64::element_type v);
        template <unsigned _I>
        typename v2u64::element_type extract(const v2u64& a);

        void store(v8u16::element_type* p, const v8u16& r);
        void store(v8s16::element_type* p, const v8s16& r);
        void store(v4u32::element_type* p, const v4u32& r);
        void store(v4s32::element_type* p, const v4s32& r);
        void store(v2u64::element_type* p, const v2u64& r);
        void store(v2s64::element_type* p, const v2s64& r);
        
        namespace aligned {
                using emuvec::store;
        }
        namespace unaligned {
                using emuvec::store;
        }

}

#include <cftal/emuvec_fvec.h>

namespace mem {

        using emuvec::store;
        namespace aligned {
                using emuvec::store;
        }
        namespace unaligned {
                using emuvec::store;
        }
}


namespace emuvec {

        template <typename _D, typename _S>
        _D as(const _S& s);

        namespace impl {
                // convert according to current rounding mode
                template <typename _D, typename _S>
                struct cvt {
                        static 
                        _D l(const _S& s);
                        static
                        _D h(const _S& s);
                };

                // convert with truncation (i.e. round to zero)
                template <typename _D, typename _S>
                struct cvt_rz {
                        static
                        _D l(const _S& s);
                        static
                        _D h(const _S& s);
                };
        }

        template <class _D, class _S>
        _D cvt_lo(const _S& s);
        template <class _D, class _S>
        _D cvt_hi(const _S& s);
        template <class _D, class _S>
        _D cvt(const _S& s);

        v4f32 cvt_f32(const v2f64& l, const v2f64& h);
        // v8f32 cvt_f32(const v4f64& l, const v4f64& h);


        template <class _D, class _S>
        std::pair<_D, _D> cvt_widen(const _S& s);
        
        template <class _D, class _S>
        _D cvt_rz_lo(const _S& s);
        template <class _D, class _S>
        _D cvt_rz_hi(const _S& s);
        template <class _D, class _S>
        _D cvt_rz(const _S& s);
        template <class _D, class _S>
        std::pair<_D, _D> cvt_rz_widen(const _S& s);
}

template <class _D, class _S>
_D emuvec::as(const _S& s)
{
        constexpr std::size_t sn(sizeof(typename _S::element_type)* _S::N);
        constexpr std::size_t dn(sizeof(typename _D::element_type)* _D::N);
        static_assert(sn == dn, "memory size of src and dst must be equal");
        _D d;
        const char* sp= reinterpret_cast<const char*>(s());
        char* dp= reinterpret_cast<char*>(d());
        std::memcpy(dp, sp, sn);
        return d;
}

template <class _D, class _S>
_D emuvec::cvt_lo(const _S& s)
{
        constexpr std::size_t SN= std::size_t(_S::N);
        constexpr std::size_t DN= std::size_t(_D::N);
        constexpr std::size_t N=  SN > DN ? DN : SN ;
        _D d;
        const typename _S::element_type* sp= s();
        typename _D::element_type* dp= d();
        for (std::size_t i=0; i< N; ++i) 
                dp[i] = sp[i];
        return d;
}

template <class _D, class _S>
_D emuvec::cvt_hi(const _S& s)
{
        constexpr std::size_t SN= std::size_t(_S::N);
        constexpr std::size_t DN= std::size_t(_D::N);
        // constexpr std::size_t N=  SN > DN ? DN : SN ;
        static_assert(SN == 2*DN, "invalid size");
        _D d;
        const typename _S::element_type* sp= s();
        typename _D::element_type* dp= d();
        for (std::size_t i=0; i< DN; ++i) 
                dp[i] = sp[DN + i];
        return d;
}

template <class _D, class _S>
_D emuvec::cvt(const _S& s)
{
        constexpr std::size_t SN= std::size_t(_S::N);
        constexpr std::size_t DN= std::size_t(_D::N);
        // constexpr std::size_t N=  SN > DN ? DN : SN ;
        static_assert(SN == DN, "invalid size");
        return cvt_lo<_D>(s);
}

// v8s16 implementation
inline
emuvec::v8s16::element_type* emuvec::v8s16::begin()
{
        return reinterpret_cast<element_type*>(base_type::vbegin());
}

inline
const emuvec::v8s16::element_type* emuvec::v8s16::begin() const
{
        return reinterpret_cast<const element_type*>(base_type::vbegin());
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
emuvec::operator>>= (v8s16& a, const const_u32<_P>& b)
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
        return reinterpret_cast<element_type*>(base_type::vbegin());
}

inline
const emuvec::v8u16::element_type* emuvec::v8u16::begin() const
{
        return reinterpret_cast<const element_type*>(base_type::vbegin());
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
        return reinterpret_cast<element_type*>(base_type::vbegin());
}

inline
const emuvec::v4s32::element_type* emuvec::v4s32::begin() const
{
        return reinterpret_cast<const element_type*>(base_type::vbegin());
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
        return reinterpret_cast<element_type*>(base_type::vbegin());
}

inline
const emuvec::v4u32::element_type* emuvec::v4u32::begin() const
{
        return reinterpret_cast<const element_type*>(base_type::vbegin());
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

// v2s64 implementation
inline
emuvec::v2s64::element_type* emuvec::v2s64::begin()
{
        return reinterpret_cast<element_type*>(base_type::vbegin());
}

inline
const emuvec::v2s64::element_type* emuvec::v2s64::begin() const
{
        return reinterpret_cast<const element_type*>(base_type::vbegin());
}

inline
emuvec::v2s64::element_type* emuvec::v2s64::operator()()
{
        return begin();
}

inline
const emuvec::v2s64::element_type* emuvec::v2s64::operator()() const
{
        return begin();
}

template <unsigned _P>
emuvec::v2s64&
emuvec::operator<<= (v2s64& a, const const_u32< _P >& b)
{
        const int val = b.val;
        impl::v_sl<v2s64::element_type> ot(val);
        impl::v_assign_op(a(), ot, v2s64::N);
        return a;
}

template <unsigned _P>
emuvec::v2s64&
emuvec::operator>>= (v2s64& a, const const_u32< _P >& b)
{
        const int val = b.val;
        impl::v_sr<v2s64::element_type> ot(val);
        impl::v_assign_op(a(), ot, v2s64::N);
        return a;
}

template <unsigned _P>
emuvec::v2s64
emuvec::operator<<(const v2s64& a, const const_u32< _P >& b)
{
        v2s64 r;
        const int val = b.val;
        impl::v_sl<v2s64::element_type> ot(val);
        impl::v_bi_op(r(), a(), ot, v2s64::N);
        return r;
}

template <unsigned _P>
emuvec::v2s64
emuvec::operator>> (const v2s64& a, const const_u32< _P >& b)
{
        v2s64 r;
        const int val = b.val;
        impl::v_sr<v2s64::element_type> ot(val);
        impl::v_bi_op(r(), a(), ot, v2s64::N);
        return r;
}

template < bool _P0, bool _P1 >
emuvec::v2s64 emuvec::select(const v2s64& a, const v2s64& b)
{
        v2s64 r;
        impl::select_2<v2s64::element_type, _P0, _P1>::
                v(r(), a(), b());
        return r;
}

template < int _P0, int _P1 >
emuvec::v2s64 emuvec::permute(const v2s64& a)
{
        v2s64 r;
        impl::perm1_2<v2s64::element_type, _P0, _P1>::v(r(), a());
        return r;
}

template < int _P0, int _P1 >
emuvec::v2s64 emuvec::permute(const v2s64& a, const v2s64& b)
{
        v2s64 r;
        impl::perm2_2<v2s64::element_type, _P0, _P1>::
                v(r(), a(), b());
        return r;
}

template <unsigned _I>
emuvec::v2s64::element_type emuvec::extract(const v2s64& a)
{
        return a()[_I];
}

template <unsigned _I>
emuvec::v2s64 emuvec::insert(const v2s64& a, v2s64::element_type v)
{
        v2s64 r(a);
        r()[_I] =v;
        return r;
}

// v2u64 implementation
inline
emuvec::v2u64::element_type* emuvec::v2u64::begin()
{
        return reinterpret_cast<element_type*>(base_type::vbegin());
}

inline
const emuvec::v2u64::element_type* emuvec::v2u64::begin() const
{
        return reinterpret_cast<const element_type*>(base_type::vbegin());
}

inline
emuvec::v2u64::element_type* emuvec::v2u64::operator()()
{
        return begin();
}

inline
const emuvec::v2u64::element_type* emuvec::v2u64::operator()() const
{
        return begin();
}

template <unsigned _P>
emuvec::v2u64&
emuvec::operator<<= (v2u64& a, const const_u32< _P >& b)
{
        const int val = b.val;
        impl::v_sl<v2u64::element_type> ot(val);
        impl::v_assign_op(a(), ot, v2u64::N);
        return a;
}

template <unsigned _P>
emuvec::v2u64&
emuvec::operator>>= (v2u64& a, const const_u32< _P >& b)
{
        const int val = b.val;
        impl::v_sr<v2u64::element_type> ot(val);
        impl::v_assign_op(a(), ot, v2u64::N);
        return a;
}

template <unsigned _P>
emuvec::v2u64
emuvec::operator<<(const v2u64& a, const const_u32< _P >& b)
{
        v2u64 r;
        const int val = b.val;
        impl::v_sl<v2u64::element_type> ot(val);
        impl::v_bi_op(r(), a(), ot, v2u64::N);
        return r;
}

template <unsigned _P>
emuvec::v2u64
emuvec::operator>> (const v2u64& a, const const_u32< _P >& b)
{
        v2u64 r;
        const int val = b.val;
        impl::v_sr<v2u64::element_type> ot(val);
        impl::v_bi_op(r(), a(), ot, v2u64::N);
        return r;
}

template < bool _P0, bool _P1>
emuvec::v2u64 emuvec::select(const v2u64& a, const v2u64& b)
{
        v2u64 r;
        impl::select_2<v2u64::element_type, _P0, _P1>::
                v(r(), a(), b());
        return r;
}

template < int _P0, int _P1>
emuvec::v2u64 emuvec::permute(const v2u64& a)
{
        v2u64 r;
        impl::perm1_2<v2u64::element_type, _P0, _P1>::v(r(), a());
        return r;
}

template < int _P0, int _P1>
emuvec::v2u64 emuvec::permute(const v2u64& a, const v2u64& b)
{
        v2u64 r;
        impl::perm2_2<v2u64::element_type, _P0, _P1>::
                v(r(), a(), b());
        return r;
}

template <unsigned _I>
emuvec::v2u64::element_type emuvec::extract(const v2u64& a)
{
        return a()[_I];
}

template <unsigned _I>
emuvec::v2u64 emuvec::insert(const v2u64& a, v2u64::element_type v)
{
        v2u64 r(a);
        r()[_I] =v;
        return r;
}

#include <cftal/emuvec_inl.h>

// Local variables:
// mode: c++
// end:
#endif
