#pragma once
#include "Index.h"

namespace meta17 {

template<class T>
constexpr auto is_index = false;

template<size_t I>
constexpr auto is_index<Index<I>> = true;

} // namespace meta17
