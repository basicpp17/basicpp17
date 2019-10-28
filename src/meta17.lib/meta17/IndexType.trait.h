#pragma once
#include "IndexType.h"

namespace meta17 {

template<class T>
constexpr auto is_index_type = false;

template<size_t I, class T>
constexpr auto is_index_type<IndexType<I, T>> = true;

} // namespace meta17
