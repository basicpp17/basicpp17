#pragma once
#include "Bool.h"

namespace meta17 {

/// Unwrapping
template<bool B>
constexpr auto toValue(Bool<B>) -> bool {
    return B;
}

template<class T>
constexpr auto to_value = toValue(T{});

} // namespace meta17
