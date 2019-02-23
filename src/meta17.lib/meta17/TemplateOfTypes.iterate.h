#pragma once
#include "Type.h"

namespace meta17 {

/// invoke callable with all types of the type template
template<class Callable, template<typename...> class Container, class... Ts>
constexpr auto forEachTemplateType(Type<Container<Ts...>>, Callable&& callable) {
    return (..., callable(type<Ts>));
}

} // namespace meta17
