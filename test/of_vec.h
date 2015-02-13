#if !defined (__CFTAL_TEST_OF_VEC_H__)
#define __CFTAL_TEST_OF_VEC_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/idx.h>
#include <iostream>

namespace cftal {

    namespace test {

        template <typename _T, std::size_t _N>
        union vec_arr {
            _T _va[_N];
            vec<_T, _N> _vv;
        };

        template <typename _T, std::size_t _N>
        std::ostream& operator<<(std::ostream& s,
                                 const vec_arr<_T, _N>& v);
        
        // returns a vector filled with 1..N
        // or a vector filled with N+1..2N
        template <typename _T, std::size_t _N>
        vec<_T, _N> load_vals(bool second);

        template <typename _T, std::size_t _N, typename _M>
        bool
        check_val(const vec<_T, _N>& v, const idx& i,
                  const _M msg);

        template <class _T, std::size_t _N>
        struct of_vec {
            bool perform() const;
        };

        // tests of vec<_T, 2>
        template <class _T>
        bool check_select_v2();

        template <class _T>
        bool check_perm1_v2();

        template <class _T>
        bool check_perm2_v2();

        
        template <class _T>
        struct of_vec<_T, 2> {
            bool perform()
                const;
            bool check_select()
                const;
            bool check_perm1()
                const;
            bool check_perm2()
                const;
            void gen_select()
                const;
        };

        template <class _T>
        struct of_vec<_T, 4> {
            bool perform()
                const;
            bool check_select()
                const;
            bool check_perm1()
                const;
            bool check_perm2()
                const;
        };

        template <class _T>
        struct of_vec<_T, 8> {
            bool perform()
                const;
            bool check_select()
                const;
            bool check_perm1()
                const;
            bool check_perm2()
                const;
        };

    }
}

template <typename _T, std::size_t _N>
std::ostream&
cftal::test::operator<<(std::ostream& s, const vec_arr<_T, _N>& v)
{
    for (std::size_t i=0; i< _N; ++i) {
        if (i)
            s << "; ";
        s << v._va[i];
    }
    return s;
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N>
cftal::test::load_vals(bool second)
{
    vec_arr<_T, _N> v;
    std::size_t offset( second ? _N+1 : 1);
    for (std::size_t i=0; i<_N; ++i) {
        v._va[i] = _T(i + offset);
    }
    return v._vv;
}

template <typename _T, std::size_t _N, typename _M>
bool
cftal::test::check_val(const vec<_T, _N>& r, const idx& i, const _M& m)
{
    vec_arr<_T, _N> v;
    mem< vec<_T, _N> >::store(&v._va[0], r);
    for (std::size_t e=0; e<_N; ++e) {
        if (check_val(v._va[e], i[e])==false) {
            std::cerr << m << "< " << i <<  " > [ "
                      << v << " ] FAILED.\n";
        }
    }
    return true;
}

// Local variables:
// mode: c++
// end:
#endif
