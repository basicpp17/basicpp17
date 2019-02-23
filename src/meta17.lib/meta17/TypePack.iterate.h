#pragma once
#include "Type.h"
#include "TypePack.h"

namespace meta17 {

/// invoke callable with all types of the TypePack
template<class Callable, class... Ts>
constexpr auto forEachType(TypePack<Ts...>, Callable&& callable) {
    return (..., callable(type<Ts>));
}

/// return true if callable is true for every type of TypePack
template<class Callable, class... Ts>
constexpr bool allTypesOf(TypePack<Ts...>, Callable&& callable) {
    return (... && callable(type<Ts>));
}

} // namespace meta17
