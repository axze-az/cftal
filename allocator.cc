#include "allocator.h"

template class cftal::global_ptr_cache<16>;
template class cftal::global_ptr_cache<32>;

template class cftal::cache_allocator<char, 16>;
template class cftal::cache_allocator<char, 32>;
