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
#define USE_BIT_CAST 0
#include <cftal/as.h>
#include <cftal/type_traits.h>
#include <cftal/vsvec.h>
#include <atomic>

namespace cftal {
    namespace test {
    }
}

namespace cftal::test {
    class rf32 {
        float _v;
        static std::atomic<int32_t> _cnt;
    public:
        static int32_t cnt() { return _cnt; }
        ~rf32() { --_cnt; }
        rf32() : _v(std::numeric_limits<float>::quiet_NaN()) { ++_cnt; }
        rf32(float f) : _v(f) { ++_cnt; }
        rf32(const rf32& r) : _v(r._v) { ++_cnt; }
        rf32(rf32&& r) : _v(std::move(r._v)) { ++_cnt; }
        rf32& operator=(const rf32& v) = default;
        rf32& operator=(rf32&& v) = default;
        float operator()() const { return _v; }
    };


    rf32 operator-(const rf32& a);
    rf32 operator+(const rf32& a, const rf32& b);
    rf32& operator+=(rf32& a, const rf32& b);
    rf32 operator-(const rf32& a, const rf32& b);
    rf32& operator-=(rf32& a, const rf32& b);
    rf32 operator*(const rf32& a, const rf32& b);
    rf32& operator*=(rf32& a, const rf32& b);
    rf32 operator/(const rf32& a, const rf32& b);
    rf32& operator/=(rf32& a, const rf32& b);

    bool operator==(const rf32& a, const rf32& b);

    bool signbit(const rf32& a) { return std::signbit(a()); }

    std::ostream&
    operator<<(std::ostream& o, const rf32& v);

    using lvrf32 = vsvec<float>;

    class vsvec_short_vec_optimizations {
        static
        void failed(int e=1);
        static
        void tl();
    public:
        static
        bool perform();
    };
}

namespace cftal {
    template <>
    struct is_floating_point<test::rf32> : public std::true_type {};
}

std::atomic<cftal::int32_t> cftal::test::rf32::_cnt{0};

inline
cftal::test::rf32
cftal::test::operator-(const rf32& a)
{
    return rf32(-a());
}

inline
cftal::test::rf32
cftal::test::operator+(const rf32& a, const rf32& b)
{
    return rf32(a() + b());
}

inline
cftal::test::rf32&
cftal::test::operator+=(rf32& a, const rf32& b)
{
    a = a+b;
    return a;
}

inline
cftal::test::rf32
cftal::test::operator-(const rf32& a, const rf32& b)
{
    return rf32(a() - b());
}

inline
cftal::test::rf32&
cftal::test::operator-=(rf32& a, const rf32& b)
{
    a = a-b;
    return a;
}

inline
cftal::test::rf32
cftal::test::operator*(const rf32& a, const rf32& b)
{
    return rf32(a() * b());
}

inline
cftal::test::rf32&
cftal::test::operator*=(rf32& a, const rf32& b)
{
    a = a*b;
    return a;
}

inline
cftal::test::rf32
cftal::test::operator/(const rf32& a, const rf32& b)
{
    return rf32(a() / b());
}

inline
cftal::test::rf32&
cftal::test::operator/=(rf32& a, const rf32& b)
{
    a = a/b;
    return a;
}

inline
bool
cftal::test::operator==(const rf32& a, const rf32& b)
{
    return a() == b();
}

std::ostream&
cftal::test::operator<<(std::ostream& o, const rf32& v)
{
    o << v();
    return o;
}

void
cftal::test::vsvec_short_vec_optimizations::failed(int e)
{
    std::cout << "vsvec short vector optimization test FAILED with code "
              << e << '\n';
    throw e;
}

void
cftal::test::vsvec_short_vec_optimizations::tl()
{
    constexpr std::size_t _NS = 1;
    constexpr std::size_t _NL = 127;
    lvrf32 l(42.0f, _NL), s(2.0f, _NS);
    using rf32 = float;
    static_assert(sizeof(l) == sizeof(size_t) + sizeof(void*), "oops");
    static_assert(sizeof(s) == sizeof(size_t) + sizeof(void*), "oops");
    lvrf32 sum=l+s;
    if (size(sum) != _NL)
        failed(0);
    if (!all_of(sum == rf32(42.0f+2.0f))) {
        failed(10);
    }
    lvrf32 prod=l*s;
    if (size(prod) != _NL)
        failed(1);
    if (!all_of(prod == rf32(42.0f*2.0f))) {
        failed(11);
    }
    lvrf32 diff=l-s;
    if (size(diff) != _NL)
        failed(2);
    if (!all_of(diff == rf32(42.0f-2.0f))) {
        failed(12);
    }
    lvrf32 quot=l/s;
    if (size(quot) != _NL)
        failed(3);
    if (!all_of(quot == rf32(42.0f/2.0f))) {
        failed(13);
    }
    lvrf32 t=std::move(l);
    l = std::move(s);
    s = std::move(t);
    std::swap(l, s);
    if (size(s) != _NS) {
        failed(14);
    }
    if (size(l) != _NL) {
        failed(15);
    }

    vxf32 tf32(2.0f, 2);
    if (sizeof(void*)== 8) {
        if (sizeof(tf32) != 16) {
            failed(30);
        }
        const char* pb=reinterpret_cast<const char*>(tf32.cbegin());
        const char* p0=reinterpret_cast<const char*>(&tf32);
        if (p0 + sizeof(size_t) != pb) {
            failed(31);
        }
        const char* pe=reinterpret_cast<const char*>(tf32.cend());
        const char* p1=reinterpret_cast<const char*>((&tf32)+1);
        if (pe != p1) {
            failed(32);
        }
    }

    vxf64 tf64(1.0, 1);
    if (sizeof(void*)== 8) {
        if (sizeof(tf64) != 16) {
            failed(40);
        }
        const char* pb=reinterpret_cast<const char*>(tf64.cbegin());
        const char* p0=reinterpret_cast<const char*>(&tf64);
        if (p0 + sizeof(size_t) != pb) {
            failed(41);
        }
        const char* pe=reinterpret_cast<const char*>(tf64.cend());
        const char* p1=reinterpret_cast<const char*>((&tf64)+1);
        if (pe != p1) {
            failed(42);
        }
    }

    vxs8 ts8(42, 8);
    if (sizeof(void*)== 8) {
        if (sizeof(ts8) != 16) {
            failed(50);
        }
        const char* pb=reinterpret_cast<const char*>(ts8.cbegin());
        const char* p0=reinterpret_cast<const char*>(&ts8);
        if (p0 + sizeof(size_t) != pb) {
            failed(51);
        }
        const char* pe=reinterpret_cast<const char*>(ts8.cend());
        const char* p1=reinterpret_cast<const char*>((&ts8)+1);
        if (pe != p1) {
            failed(52);
        }
    }

    // _n < _SVOPT
    vxs8 tu8(42, 4);
    if (sizeof(void*)== 8) {
        if (sizeof(tu8) != 16) {
            failed(60);
        }
        const char* pb=reinterpret_cast<const char*>(tu8.cbegin());
        const char* p0=reinterpret_cast<const char*>(&tu8);
        if (p0 + sizeof(size_t) != pb) {
            failed(61);
        }
        const char* pe=reinterpret_cast<const char*>(tu8.cend());
        const char* p1=reinterpret_cast<const char*>((&tu8)+1);
        if (pe != p1-4) {
            failed(62);
        }
    }


}

bool
cftal::test::vsvec_short_vec_optimizations::perform()
{
    try {
        uint32_t c0=rf32::cnt();
        tl();
        uint32_t c1=rf32::cnt();
        return c1==c0;
    }
    catch (...) {
        return false;
    }
}

int main()
{
    int r;
    if (cftal::test::vsvec_short_vec_optimizations::perform() == true) {
        r=0;
        std::cout << "vsvec short vector optimization test passed\n";
    } else {
        r=3;
        std::cout << "vsvec short vector optimization test FAILED\n";
    }
    return r;
}
