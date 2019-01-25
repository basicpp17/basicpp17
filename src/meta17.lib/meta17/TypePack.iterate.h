#pragma once

#include "TypePack.h"

namespace meta17 {

/// Iteration
// template<class Callable, class... Ts>
// constexpr void ForEach(Callable&& callable, TypePack<Ts...>) {
//    (..., callable(Type<Ts>{}));
//}

template<class Callable, template<typename...> class Container, class... Ts>
constexpr void ForEach(Callable&& callable, Container<Ts...>) {
    (..., callable(Type<Ts>{}));
}

template<class Callable, class... Ts>
constexpr bool AllOf(Callable&& callable, TypePack<Ts...>) {
    return (... && callable(Type<Ts>{}));
}

} // namespace meta17
