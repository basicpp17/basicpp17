#pragma once
#include "Type.h"
#include "TypePack.h"

namespace meta17 {

/// Iteration
template<class Callable, class... Ts>
constexpr void ForEach(Callable&& callable, TypePack<Ts...>) {
    (..., callable(type<Ts>));
}

template<class Callable, class... Ts>
constexpr bool AllOf(Callable&& callable, TypePack<Ts...>) {
    return (... && callable(type<Ts>));
}

} // namespace meta17
