#pragma once
#include "Type.h"

namespace meta17 {

template<class T, template<typename...> class Template, class... Ts>
constexpr auto templateContains(Type<Template<Ts...>>, Type<T> = {}) -> bool {
    return ((type<Ts> == type<T>) || ...);
}
template<class T, class Template>
constexpr auto template_contains = templateContains<T>(type<Template>);

} // namespace meta17
