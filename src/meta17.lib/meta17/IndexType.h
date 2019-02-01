#pragma once

#include <cstddef>

namespace meta17 {

/// combines an index with a type
template<size_t I, class T>
struct IndexType {};

template<size_t I, class T>
constexpr auto index_type = IndexType<I, T>{};

} // namespace meta17
