#pragma once
#include "Index.h"

#include "Const.wrap.h" // to_value

namespace meta17 {

/// Unwrapping
// use to_value

/// Wrapping
template<class T>
using ToIndex = Index<to_value<T>>;

template<class T>
constexpr auto to_index = ToIndex<T>{};

} // namespace meta17
