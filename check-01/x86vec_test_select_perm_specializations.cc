#include "x86vec_test.h"
#include <iostream>

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
bool chk_u16(__m128i a, x86vec::test::idx& id)
{
        __m128i r(x86vec::perm_u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>(a));
        id.assign(_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7);
        bool rc(x86vec::test::check_u16("perm1_u16", r, id));
        return rc;
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
bool chk_u16(__m128i a, __m128i b, x86vec::test::idx& id)
{
        __m128i r(x86vec::perm_u16<_P0, _P1, _P2, _P3, 
				   _P4, _P5, _P6, _P7>(a, b));
        id.assign(_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7);
        bool rc(x86vec::test::check_u16("perm2_u16", r, id));
        return rc;
}

bool x86vec::test::check_select_perm_specializations()
{
        // we have only to check perm1_u16 specializations because
        // permutations with bigger data sizes are tested completly
        bool r(true);
        __m128i a= load_u16(false);
        idx id(-2,-2);
	r &= chk_u16<-1,-1,-1,-1,-1,-1,-1,-1>(a, id);
	r &= chk_u16< 0, 1, 2, 3, 4, 5, 6, 7>(a, id);
	r &= chk_u16< 0, 0, 1, 1, 2, 2, 3, 3>(a, id);
	r &= chk_u16< 4, 4, 5, 5, 6, 6, 7, 7>(a, id);
	r &= chk_u16< 0, 1, 0, 1, 2, 3, 2, 3>(a, id);
	r &= chk_u16< 4, 5, 4, 5, 6, 7, 6, 7>(a, id);
	r &= chk_u16< 0, 1, 2, 3, 0, 1, 2, 3>(a, id);
	r &= chk_u16< 4, 5, 6, 7, 4, 5, 6, 7>(a, id);
	r &= chk_u16< 0,-1, 1,-1, 2,-1, 3,-1>(a, id);
	r &= chk_u16< 4,-1, 5,-1, 6,-1, 7,-1>(a, id);
	r &= chk_u16<-1, 0,-1, 1,-1, 2,-1, 3>(a, id);
	r &= chk_u16<-1, 4,-1, 5,-1, 6,-1, 7>(a, id);
	r &= chk_u16< 0, 0, 0, 0, 0, 0, 0, 0>(a, id);
	r &= chk_u16< 1, 1, 1, 1, 1, 1, 1, 1>(a, id);
	r &= chk_u16< 2, 2, 2, 2, 2, 2, 2, 2>(a, id);
	r &= chk_u16< 3, 3, 3, 3, 3, 3, 3, 3>(a, id);
	r &= chk_u16< 4, 4, 4, 4, 4, 4, 4, 4>(a, id);
	r &= chk_u16< 5, 5, 5, 5, 5, 5, 5, 5>(a, id);
	r &= chk_u16< 6, 6, 6, 6, 6, 6, 6, 6>(a, id);
	r &= chk_u16< 7, 7, 7, 7, 7, 7, 7, 7>(a, id);
	// vpslldq
	r &= chk_u16<-1, 0, 1, 2, 3, 4, 5, 6>(a, id);
	r &= chk_u16<-1,-1, 0, 1, 2, 3, 4, 5>(a, id);
	r &= chk_u16<-1,-1,-1, 0, 1, 2, 3, 4>(a, id);
	r &= chk_u16<-1,-1,-1,-1, 0, 1, 2, 3>(a, id);
	r &= chk_u16<-1,-1,-1,-1,-1, 0, 1, 2>(a, id);
	r &= chk_u16<-1,-1,-1,-1,-1,-1, 0, 1>(a, id);
	r &= chk_u16<-1,-1,-1,-1,-1,-1,-1, 0>(a, id);
	// vpsrldq
	r &= chk_u16< 1, 2, 3, 4, 5, 6, 7,-1>(a, id); 
	r &= chk_u16< 2, 3, 4, 5, 6, 7,-1,-1>(a, id); 
	r &= chk_u16< 3, 4, 5, 6, 7,-1,-1,-1>(a, id); 
	r &= chk_u16< 4, 5, 6, 7,-1,-1,-1,-1>(a, id);
	r &= chk_u16< 5, 6, 7,-1,-1,-1,-1,-1>(a, id);
	r &= chk_u16< 6, 7,-1,-1,-1,-1,-1,-1>(a, id);
	r &= chk_u16< 7,-1,-1,-1,-1,-1,-1,-1>(a, id); 
	// vpslld
	r &= chk_u16<-1, 0,-1, 2,-1, 4,-1, 6>(a, id);
	// vpsrld
	r &= chk_u16< 1,-1, 3,-1, 5,-1, 7,-1>(a, id);
	// vpsllq
	r &= chk_u16<-1, 0, 1, 2,-1, 4, 5, 6>(a, id);
	r &= chk_u16<-1,-1, 0, 1,-1,-1, 4, 5>(a, id);
	r &= chk_u16<-1,-1,-1, 0,-1,-1,-1, 4>(a, id);
	// vpsrlq
	r &= chk_u16< 1, 2, 3,-1, 5, 6, 7,-1>(a, id);
	r &= chk_u16< 2, 3,-1,-1, 6, 7,-1,-1>(a, id);
	r &= chk_u16< 3,-1,-1,-1, 7,-1,-1,-1>(a, id);

	// low shuffles only
	r &= chk_u16< 0, 0, 1, 1, 4, 5, 6, 7>(a, id);
	r &= chk_u16< 2, 2, 3, 3, 4, 5, 6, 7>(a, id);
	r &= chk_u16< 3, 2, 1, 0, 4, 5, 6, 7>(a, id);
	r &= chk_u16< 1, 0, 3, 2, 4, 5, 6, 7>(a, id);
	// high shuffles ony
	r &= chk_u16< 0, 1, 2, 3, 4, 4, 5, 5>(a, id);
	r &= chk_u16< 0, 1, 2, 3, 6, 6, 7, 7>(a, id);
	r &= chk_u16< 0, 1, 2, 3, 7, 6, 5, 4>(a, id);
	r &= chk_u16< 0, 1, 2, 3, 5, 4, 7, 6>(a, id);
        // low/high shuffles
        r &= chk_u16< 3, 2, 1, 0, 7, 6, 5, 4>(a, id);
        r &= chk_u16<-1, 2,-1, 0, 7, 6, 6, 4>(a, id);
        r &= chk_u16<-1, 2, 5, 1, 0, 0, 7, 1>(a, id);
        // low/high shifts
        r &= chk_u16< 7, 6, 5, 4, 3, 2, 1, 0>(a, id);
        // 32 bit perms
        r &= chk_u16< 6, 7, 4, 5, 2, 3, 0, 1>(a, id);
        // zero only
        r &= chk_u16< 0,-1, 2, 3, 4, 5,-1, 7>(a, id);

        __m128i b= load_u16(true);
	r &= chk_u16< 0, 8, 1, 9, 2,10, 3,11>(a, b, id);
	r &= chk_u16< 8, 0, 9, 1,10, 2,11, 3>(a, b, id);
	r &= chk_u16< 4,12, 5,13, 6,14, 7,15>(a, b, id);
	r &= chk_u16<12, 4,13, 5,14, 6,15, 7>(a, b, id);
	r &= chk_u16< 0, 1, 2, 3, 8, 9,10,11>(a, b, id);
	r &= chk_u16< 8, 9,10,11, 0, 1, 2, 3>(a, b, id);
	r &= chk_u16< 4, 5, 6, 7,12,13,14,15>(a, b, id);
	r &= chk_u16<12,13,14,15, 4, 5, 6, 7>(a, b, id);
        return r;
}
