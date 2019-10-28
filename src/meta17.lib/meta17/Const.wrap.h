#pragma once
#include "Const.h"

#include "Bool.wrap.h" // to_value

namespace meta17 {

/// Unwrapping
template<auto V>
constexpr auto to_value<Const<V>> = V;

/// Wrapping
template<class T>
using ToConst = Const<to_value<T>>;

template<class T>
constexpr auto to_const = ToConst<T>{};

} // namespace meta17
