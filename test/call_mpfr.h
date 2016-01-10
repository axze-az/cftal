#if !defined (__CFTAL_TEST_CALL_MPFR_H__)
#define __CFTAL_TEST_CALL_MPFR_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <cftal/d_real.h>
#include <mpfr.h>

namespace cftal {
    namespace test {

        namespace call_mpfr {

            using f1_t = int (*)(mpfr_t, const mpfr_t,
                                 mpfr_rnd_t);
            using f2_t = int (*)(mpfr_t, const mpfr_t,
                                 const mpfr_t, mpfr_rnd_t);

            double
            func(double a, f1_t f);

            double
            func(double a, double b, f2_t f);

            template <typename _F>
            float
            func(float a, _F f);

            template <typename _F>
            float
            func(float a, float b, _F f);

        }

        class fpn_handle {
            mpfr_t _v;
        public:
            fpn_handle(std::size_t prec);
            fpn_handle(const fpn_handle& r);
            fpn_handle(fpn_handle&& r);
            fpn_handle& operator=(const fpn_handle& r);
            fpn_handle& operator=(fpn_handle&& r);
            ~fpn_handle();
            // explict mpft_t;
        };
    }
}






// Local variables:
// mode: c++
// end:
#endif
