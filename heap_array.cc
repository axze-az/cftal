#include "heap_array.h"

#include <stdexcept>
#include <sstream>

void cftal::impl::heap_array_throw_range_error(std::size_t _N, bool add_const)
{
    std::stringstream s;
    s << "cftal::heap_array<_T, " << _N << ">::at";
    if (add_const)
        s << " const";
    s << " out of bounds.";
    std::string ss(s.str());
    throw std::range_error(ss);
}
