#if !defined (__CFTAL_TEST_MPFR_CACHE_H__)
#define __CFTAL_TEST_MPFR_CACHE_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <cftal/test/call_mpfr.h>

namespace cftal {
    namespace test {
        namespace mpfr_cache {

            using call_mpfr::f1_t;
            using call_mpfr::f2_t;

            template <typename _T>
            struct mpfr_result {
                _T _res;
                int _mpfr_res;
            };

            // returns nullptr if nothing was found
            const mpfr_result<double>*
            result(double a, f1_t f, mpfr_result<double>& spc);
            // update the data base
            void
            update(double a, f1_t f, const mpfr_result<double>& r);

        }
    }
}

#endif
