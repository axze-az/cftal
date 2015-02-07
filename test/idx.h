#if !defined (__CFTAL_TEST_IDX_H__)
#define __CFTAL_TEST_IDX_H__ 1

#include <cftal/config.h>
#include <vector>
#include <initializer_list>
#include <iostream>

namespace cftal {

    namespace test {

        class idx {
            std::vector<int> m_i;
        public:
            idx(std::initializer_list l) : m_i{l} {}
            const int& operator[](std::size_t i) const {
                return m_i[i];
            }
            std::size_t size() const {
                return m_i.size();
            }
        };

        std::ostream& operator<<(std::ostream& s, const idx& i);
        
        template <class _T>
        bool check_val(_T t, int p);
        
    }
}

inline
szd::ostream&
cftal::test::operator<<(std::ostream& s, const idx& i)
{
    for (std::size_i j=0; j < i.size(); ++j) {
        if (j)
            s << ", ";
        s << i[j];
    }
    return s;
}

template <class _T>
inline
bool cftal::test::test::check_val(_T t, int p)
{
    return ((p<0) && (t==0)) || (_T(p+1) == t);
}



// Local Variables:
// mode: c++
// end:

#endif
