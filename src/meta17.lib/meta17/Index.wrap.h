#pragma once
#include "Index.h"

#include "Bool.wrap.h" // to_value
#include "Const.wrap.h" // toValue

namespace meta17 {

/// Unwrapping
// use to_value

/// Wrapping
template<class T>
using ToIndex = Index<to_value<T>>;

template<class T>
constexpr auto to_index = ToIndex<T>{};

} // namespace meta17
