#include <x86vec_ops_1.h>
#include <x86vec_test.h>
#include <iostream>

namespace {
        
        bool check_res(bool expected, bool result, 
                       const char* errmsg);
}

namespace {
        bool check_res(bool expected, bool result, const char* emsg)
        {
                bool r(expected == result);
                if (!r) 
                        std::cout << emsg << std::endl;
                return r;
        }

}

bool x86vec::test::check_signs()
{
        const __m128 zf = impl::make_zero_v4f32::v();
        const __m128d zd= impl::make_zero_v2f64::v();
        const __m128i zi = impl::make_zero_int::v();

        typedef const_v4u32<unsigned(-1), unsigned(-1),
                            unsigned(-1), unsigned(-1)> all;

        const __m128 af= all::fv();
        const __m128d ad= all::dv();
        const __m128i ai= all::iv();

        typedef const_v8u16<0, 0x80, 0, uint16_t(-1), 
                            uint16_t(-1), 0x80, uint16_t(-1), 0> mx;
        const __m128 mf= mx::fv();
        const __m128d md= mx::dv();
        const __m128i mi= mx::iv();


        bool r(true);
        r &= check_res(false, all_bits(zi), "all bits on 0");
        r &= check_res(true, no_bits(zi), "no bits on 0");
        r &= check_res(false, both_bits(zi), "both bits on 0");
        r &= check_res(true, all_bits(ai), "all bits on -1");
        r &= check_res(false, no_bits(ai), "no bits on -1");
        r &= check_res(false, both_bits(ai), "both bits on -1");
        r &= check_res(false, all_bits(mi), "all bits on mixed");
        r &= check_res(false, no_bits(mi), "no bits on mixed");
        r &= check_res(true, both_bits(mi), "both bits on mixed");

        r &= check_res(false, all_signs_f64(zd), "all signs_f64 on 0");
        r &= check_res(true, no_signs_f64(zd), "no signs_f64 on 0");
        r &= check_res(false, both_signs_f64(zd), "both signs_f64 on 0");
        r &= check_res(true, all_signs_f64(ad), "all signs_f64 on -1");
        r &= check_res(false, no_signs_f64(ad), "no signs_f64 on -1");
        r &= check_res(false, both_signs_f64(ad), "both signs_f64 on -1");
        r &= check_res(false, all_signs_f64(md), "all signs_f64 on mixed");
        r &= check_res(false, no_signs_f64(md), "no signs_f64 on mixed");
        r &= check_res(true, both_signs_f64(md), "both signs_f64 on mixed");

        r &= check_res(false, all_signs_f32(zf), "all signs_f32 on 0");
        r &= check_res(true, no_signs_f32(zf), "no signs_f32 on 0");
        r &= check_res(false, both_signs_f32(zf), "both signs_f32 on 0");
        r &= check_res(true, all_signs_f32(af), "all signs_f32 on -1");
        r &= check_res(false, no_signs_f32(af), "no signs_f32 on -1");
        r &= check_res(false, both_signs_f32(af), "both signs_f32 on -1");
        r &= check_res(false, all_signs_f32(mf), "all signs_f32 on mixed");
        r &= check_res(false, no_signs_f32(mf), "no signs_f32 on mixed");
        r &= check_res(true, both_signs_f32(mf), "both signs_f32 on mixed");

        r &= check_res(false, all_signs_s16(zi), "all signs_s16 on 0");
        r &= check_res(true, no_signs_s16(zi), "no signs_s16 on 0");
        r &= check_res(false, both_signs_s16(zi), "both signs_s16 on 0");
        r &= check_res(true, all_signs_s16(ai), "all signs_s16 on -1");
        r &= check_res(false, no_signs_s16(ai), "no signs_s16 on -1");
        r &= check_res(false, both_signs_s16(ai), "both signs_s16 on -1");
        r &= check_res(false, all_signs_s16(mi), "all signs_s16 on mixed");
        r &= check_res(false, no_signs_s16(mi), "no signs_s16 on mixed");
        r &= check_res(true, both_signs_s16(mi), "both signs_s16 on mixed");

        r &= check_res(false, all_signs_s32(zi), "all signs_s32 on 0");
        r &= check_res(true, no_signs_s32(zi), "no signs_s32 on 0");
        r &= check_res(false, both_signs_s32(zi), "both signs_s32 on 0");
        r &= check_res(true, all_signs_s32(ai), "all signs_s32 on -1");
        r &= check_res(false, no_signs_s32(ai), "no signs_s32 on -1");
        r &= check_res(false, both_signs_s32(ai), "both signs_s32 on -1");
        r &= check_res(false, all_signs_s32(mi), "all signs_s32 on mixed");
        r &= check_res(false, no_signs_s32(mi), "no signs_s32 on mixed");
        r &= check_res(true, both_signs_s32(mi), "both signs_s32 on mixed");

        r &= check_res(false, all_signs_s64(zi), "all signs_s64 on 0");
        r &= check_res(true, no_signs_s64(zi), "no signs_s64 on 0");
        r &= check_res(false, both_signs_s64(zi), "both signs_s64 on 0");
        r &= check_res(true, all_signs_s64(ai), "all signs_s64 on -1");
        r &= check_res(false, no_signs_s64(ai), "no signs_s64 on -1");
        r &= check_res(false, both_signs_s64(ai), "both signs_s64 on -1");
        r &= check_res(false, all_signs_s64(mi), "all signs_s64 on mixed");
        r &= check_res(false, no_signs_s64(mi), "no signs_s64 on mixed");
        r &= check_res(true, both_signs_s64(mi), "both signs_s64 on mixed");

        return r;
}
