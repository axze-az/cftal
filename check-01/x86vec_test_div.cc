#include <x86vec_test.h>
#include <x86vec_ref.h>
#include <iostream>
#include <iomanip>

namespace x86vec
{
        namespace test
        {
                bool check_div_s16();
                bool check_div_u16();

                template <class _DIV, class _PR>
                bool check_div_16(const char* msg);
        }
}

template <class _DIV, class _PR>
bool x86vec::test::check_div_16(const char* msg)
{
	std::uint64_t t_d(0), t_r(0);
	std::uint64_t t_dc(0), t_rc(0);
        for(int32_t i = 0; i < 0x10000; ++i) {
                __m128i u = _mm_cvtsi32_si128(i);
                if ((i & 0xff)==0xff) {
                        std::cout << '\r' << msg << ": " 
				  << std::setw(6) << i << std::flush;
		}
                u = impl::splat_u16<0>::v(u);
                for(int32_t j = 0; j < 0x10000; j += 8) {
                        __m128i v = _mm_setr_epi16(j, j + 1, j + 2, j + 3,
                                                   j + 4, j + 5, j + 6, j + 7);
                        __m128i r = impl::make_zero_int::v();
                        __m128i rr = impl::make_zero_int::v();
			t_dc = bitops::rdtsc();
                        __m128i q = _DIV::v(u, v, &r);
			t_rc = bitops::rdtsc();
                        __m128i qr = _DIV::ref(u, v, &rr);
			t_r += bitops::rdtsc() - t_rc;
			t_d += t_rc - t_dc;
                        __m128i qeq = _mm_cmpeq_epi16(qr, q);
                        __m128i req = _mm_cmpeq_epi16(rr, r);
                        if(!all_signs_s16(qeq) || !all_signs_s16(req)) {
                                std::cout << '\r' << msg << std::endl
                                          << _PR(u) << std::endl
                                          << _PR(v) << std::endl
                                          << "/" << std::endl
                                          << _PR(q) << std::endl
                                          << "/ ref: " << std::endl
                                          << _PR(qr) << std::endl
                                          << "%" << std::endl
                                          << _PR(r) << std::endl
                                          << "% ref: " << std::endl
                                          << _PR(rr) << std::endl;
                                return false;
                        }
                }
        }
	std::cout << '\n' << msg << std::endl
		  << "ref: " << double(t_r)/(0x10000LL*0x10000/8)
		  << std::endl
		  << "std: " << double(t_d)/(0x10000LL*0x10000/8)
		  << std::endl;
        return true;
}

bool x86vec::test::check_div_u16()
{
        return check_div_16<impl::div_u16, pr_v8u16>("div_u16");
}

bool x86vec::test::check_div_s16()
{
        return check_div_16<impl::div_s16, pr_v8s16>("div_s16");
}

bool x86vec::test::check_div()
{
        bool rc(true);
        rc &= check_div_u16();
        rc &= check_div_s16();
        return true;
}
// kate: indent-mode cstyle; indent-width 8; replace-tabs on;
