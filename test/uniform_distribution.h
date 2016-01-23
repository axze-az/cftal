#if !defined (__CFTAL_TEST_UNIFORM_DISTRIBUTION_H__)
#define __CFTAL_TEST_UNIFORM_DISTRIBUTION_H__ 1

#include <cftal/config.h>
#include <cftal/constants.h>
#include <random>
#include <type_traits>

namespace cftal {
    namespace test {

        template <class _T>
        class uniform_real_distribution
            : public std::uniform_real_distribution<_T> {
            using base_type = std::uniform_real_distribution<_T>;

            using int_type = typename
                std::conditional<std::is_same<_T, double>::value,
                                 uint64_t,
                                 uint32_t>::type;
            using bytesx = typename
                std::conditional<std::is_same<_T, double>::value,
                                 bytes8,
                                 bytes4>::type;
            const _T _max_val=
                std::sqrt(std::numeric_limits<_T>::max());
            const _T _min_val=
                -_max_val;

            std::uniform_int_distribution<int_type> _i_dist;
            _T _min;
            _T _max;
            bool _use_int;

            _T trunc_max_val(_T m) {
                return std::min(m, _max_val);
            }

            _T trunc_min_val(_T m) {
                return std::max(m, _min_val);
            }

            static
            double
            make_fp(const bytes8& b) { return b._f64; }

            static
            float
            make_fp(const bytes4& b) { return b._f32; }
            
        public:
            using result_type = typename base_type::result_type;
            uniform_real_distribution(_T min, _T max)
                : base_type(trunc_min_val(min), trunc_max_val(max)),
                  _i_dist(std::numeric_limits<int_type>::lowest(),
                          std::numeric_limits<int_type>::max()),
                  _min(min), _max(max),
                  _use_int((trunc_min_val(min) != min) ||
                           (trunc_max_val(max) != max)) {
            }

            template <class _G>
            result_type
            operator()(_G& g) {
                _T r;
                if (_use_int) {
                    while (1) {
                        bytesx t(_i_dist(g));
                        r = make_fp(t);
                        if (std::isnan(r))
                            continue;
                        if (r>=_max)
                            continue;
                        if (r<_min)
                            continue;
                        break;
                    }
                } else {
                    r = base_type::operator()(g);
                }
                return r;
            }
        };
    }
}

// local variables:
// mode: c++
// end:
#endif
