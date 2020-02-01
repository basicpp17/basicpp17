#pragma once
#include "Index.h"
#include "IndexPack.h"

namespace meta17 {

/// "constexpr for": Iterate over a sequence with compile-time available indices
template<class Callable, size_t... Is>
constexpr auto forEachIndex(IndexPack<Is...>, Callable&& callable) {
    return (..., callable(_index<Is>));
}

} // namespace meta17
