#include <cftal/vec.h>
#include <cftal/test/intops.h>
#include <iostream>

namespace cftal {
    namespace test {

        template <class _M>
        inline
        bool
        check_res(bool expected, bool result, const _M& emsg)
        {
            bool r(expected == result);
            if (!r)
                std::cout << emsg << std::endl;
            return r;
        }
        
        template <typename _T, std::size_t _N>
        bool check_xxx_of_t();
    }
}

template <typename _T, std::size_t _N>
bool
cftal::test::check_xxx_of_t()
{
    bool r = true;
    vec<_T, _N> f1(1);
    vec<_T, _N> f2(2);

    using mask_type = typename vec<_T, _N>::mask_type;
    
    mask_type all_set = f1 == f1;
    mask_type none_set = f1 == f2;

    mask_type both_set = mask_type(low_half(all_set),
                                   low_half(none_set));

#if defined (__GNUC__)
#define __fname__ __PRETTY_FUNCTION__
#else
#define __fname__ __func__
#endif
    
    r &= check_res(true, all_of(all_set),
                   std::string(__fname__) + " all_of(all_set)" );
    r &= check_res(false, none_of(all_set),
                   std::string(__fname__) + " none_of(all_set)");
    r &= check_res(true, any_of(all_set),
                   std::string(__fname__) + " any_of(all_set)");

    r &= check_res(false, all_of(none_set),
                   std::string(__fname__) + " all_of(none_set)" );
    r &= check_res(true, none_of(none_set),
                   std::string(__fname__) + " none_of(none_set)");
    r &= check_res(false, any_of(none_set),
                   std::string(__fname__) + " any_of(none_set)");
    
    r &= check_res(false, all_of(both_set),
                   std::string(__fname__) + " all_of(both_set)" );
    r &= check_res(false, none_of(both_set),
                   std::string(__fname__) + " none_of(both_set)");
    r &= check_res(true, any_of(both_set),
                   std::string(__fname__) + " any_of(both_set)");
#undef __fname__
    return r;
}

bool cftal::test::check_xxx_of()
{
    bool r = true;

    r &= check_xxx_of_t<double, 2>();
    r &= check_xxx_of_t<double, 4>();

    r &= check_xxx_of_t<uint64_t, 2>();
    r &= check_xxx_of_t<uint64_t, 4>();

    r &= check_xxx_of_t<int64_t, 2>();
    r &= check_xxx_of_t<int64_t, 4>();
    
    r &= check_xxx_of_t<float, 2>();
    r &= check_xxx_of_t<float, 4>();
    r &= check_xxx_of_t<float, 8>();

    r &= check_xxx_of_t<uint32_t, 2>();
    r &= check_xxx_of_t<uint32_t, 4>();
    r &= check_xxx_of_t<uint32_t, 8>();
    
    r &= check_xxx_of_t<int32_t, 2>();
    r &= check_xxx_of_t<int32_t, 4>();
    r &= check_xxx_of_t<int32_t, 8>();
    
    r &= check_xxx_of_t<uint16_t, 2>();
    r &= check_xxx_of_t<uint16_t, 4>();
    r &= check_xxx_of_t<uint16_t, 8>();
    r &= check_xxx_of_t<uint16_t, 16>();
    
    r &= check_xxx_of_t<int16_t, 2>();
    r &= check_xxx_of_t<int16_t, 4>();
    r &= check_xxx_of_t<int16_t, 8>();
    r &= check_xxx_of_t<int16_t, 16>();
    
    return r;
}
