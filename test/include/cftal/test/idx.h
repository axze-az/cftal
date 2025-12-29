//
// Copyright (C) 2010-2026 Axel Zeuner
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
//
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
            idx(std::initializer_list<int> l) : m_i{l} {}
            const int& operator[](std::size_t i) const {
                return m_i[i];
            }
            std::size_t size() const {
                return m_i.size();
            }
            using const_iterator=std::vector<int>::const_iterator;
            const_iterator cbegin() const { return std::begin(m_i); }
            const_iterator begin() const { return std::begin(m_i); }
            const_iterator cend() const { return std::end(m_i); }
            const_iterator end() const { return std::end(m_i); }
        };

        bool
        operator==(const idx& a, const idx& b);
        
        bool
        operator<(const idx& a, const idx& b);
        
        std::ostream& operator<<(std::ostream& s, const idx& i);
        
        template <class _T>
        bool check_val(_T t, int p);
        
    }
}

inline
bool
cftal::test::operator==(const idx& a, const idx& b)
{
    return (a.size() == b.size()) &&
        (std::equal(std::cbegin(a), std::cend(a),
                    std::cbegin(b), std::cend(b)));
}

inline
bool
cftal::test::operator<(const idx& a, const idx& b)
{
    return std::lexicographical_compare(std::cbegin(a), std::cend(a),
                                        std::cbegin(b), std::cend(b));
}

inline
std::ostream&
cftal::test::operator<<(std::ostream& s, const idx& i)
{
    for (std::size_t j=0; j < i.size(); ++j) {
        if (j)
            s << ", ";
        s << i[j];
    }
    return s;
}

template <class _T>
inline
bool cftal::test::check_val(_T t, int p)
{
    return ((p<0) && (t==0)) || (_T(p+1) == t);
}

// Local Variables:
// mode: c++
// end:

#endif
