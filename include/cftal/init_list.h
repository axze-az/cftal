#if !defined (__CFTAL_INIT_LIST_H__)
#define __CFTAL_INIT_LIST_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <initializer_list>

namespace cftal {

    template <typename _T>
    class init_list {
        const _T* _begin;
        const _T* _end;
    public:
        constexpr init_list(const _T* b, const _T* e)
            : _begin(b), _end(e) {}
        constexpr const _T* begin() const { return _begin; }
        constexpr const _T* end() const { return _end; }
        constexpr std::size_t size() const { return end() - begin(); }
    };

    template <typename _T, std::size_t _N>
    constexpr init_list<_T>
    low_half(init_list<_T> l) {
        std::size_t s = l.size();
        std::size_t ns= (s < _N/2 ? s : _N/2);
        const _T* p= l.begin();
        return init_list<_T>(p, p+ ns);
    }
    
    template <typename _T, std::size_t _N>
    constexpr init_list<_T>
    high_half(init_list<_T> l) {
        std::size_t s = l.size();
        std::size_t ns= (s > _N/2 ? s - _N/2 : 0);
        const _T* p= l.begin() + _N/2;
        return init_list<_T>(p, p+ ns);
    }    
}


// Local variables:
// mode: c++
// end:
#endif
