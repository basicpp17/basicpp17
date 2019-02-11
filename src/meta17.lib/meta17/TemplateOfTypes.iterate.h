#pragma once
#include "Type.h"

namespace meta17 {

template<class Callable, template<typename...> class Container, class... Ts>
constexpr void ForEachTemplate(Callable&& callable, Type<Container<Ts...>>) {
    (..., callable(type<Ts>));
}

} // namespace meta17
