#if !defined (__CFTAL_MAT_H__)
#define __CFTAL_MAT_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <extcftal/heap_array.h>
#include <initializer_list>

namespace cftal {

    template <typename _T, std::size_t _S>
    class stride {
        _T* _v;
    public:
        stride(_T* p) : _v{p} {}
        _T operator()(std::size_t i) const { return _v[i*_S]; }
    };
    
    template <typename _T, std::size_t _R, std::size_t _C>
    class col_ref : public stride<_T, 1> {
    };

    template <typename _T, std::size_t _R, std::size_t _C>
    class row_ref : public stride<_T, _C> {
    };
    
    template <typename _T, std::size_t _R, std::size_t _C,
              typename _A = std::allocator<_T> >
    class mat {
        heap_array<_T, _R*_C> _v;
    public:
        mat(std::initializer_list<_T> l);
        constexpr std::size_t rows() const { return _R; }
        constexpr std::size_t cols() const { return _C; }
        const _T& operator()(std::size_t r, std::size_t c) const {
            return r * cols() + c;
        }
        _T& operator()(std::size_t r, std::size_t c) {
            return r * cols() + c;
        }
    };

}

// Local variables:
// mode: c++
// end:
#endif
